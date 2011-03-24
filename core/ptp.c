#include "camera.h"
#ifdef CAM_CHDK_PTP
#include "stddef.h"
#include "platform.h"
#include "stdlib.h"
#include "ptp.h"
#include "kbd.h"

#include "core.h"
  
static int buf_size=0;

#ifdef OPT_LUA
#include "script.h"
#include "action_stack.h"
// process id for scripts, increments before each attempt to run script
// does not handle wraparound
static unsigned script_run_id; 
#endif

static int handle_ptp(
                int h, ptp_data *data, int opcode, int sess_id, int trans_id,
                int param1, int param2, int param3, int param4, int param5);

void init_chdk_ptp()
{
  int r;
 
  // wait until ptp_handlers_info is initialised and add CHDK PTP interface
  r = 0x17;
  while ( r==0x17 )
  {
    r = add_ptp_handler(PTP_OC_CHDK,handle_ptp,0);
    msleep(250);
  }

  ExitTask();
}

static int recv_ptp_data(ptp_data *data, char *buf, int size)
  // repeated calls per transaction are ok
{
  while ( size >= buf_size )
  {
    data->recv_data(data->handle,buf,buf_size,0,0);
    // XXX check for success??

    size -= buf_size;
    buf += buf_size;
  }
  if ( size != 0 )
  {
    data->recv_data(data->handle,buf,size,0,0);
    // XXX check for success??
  }

  return 1;
}

// camera will shut down if you ignore a recv data phase
static void flush_recv_ptp_data(ptp_data *data,int size) {
  char *buf;
  buf = malloc((size > buf_size) ? buf_size:size);
  if(!buf) // buf_size should always be less then available memory
    return;
  while ( size > 0 )
  {
    if ( size >= buf_size )
    {
      recv_ptp_data(data,buf,buf_size);
      size -= buf_size;
    } else {
      recv_ptp_data(data,buf,size);
      size = 0;
    }
  }
  free(buf);
}

static int send_ptp_data(ptp_data *data, const char *buf, int size)
  // repeated calls per transaction are *not* ok
{
  int tmpsize;
  
  tmpsize = size;
  while ( size >= buf_size )
  {
    if ( data->send_data(data->handle,buf,buf_size,tmpsize,0,0,0) )
    {
      return 0;
    }

    tmpsize = 0;
    size -= buf_size;
    buf += buf_size;
  }
  if ( size != 0 )
  {
    if ( data->send_data(data->handle,buf,size,tmpsize,0,0,0) )
    {
      return 0;
    }
  }

  return 1;
}

#ifdef OPT_LUA
// TODO this could be a generic ring buffer of words
#define PTP_SCRIPT_MSG_Q_LEN 16
typedef struct {
  unsigned r; // index of current read value
  unsigned w; // index of next write value, if w == r, empty TODO "full" currently wastes a slot
  ptp_script_msg *q[PTP_SCRIPT_MSG_Q_LEN];
} ptp_script_msg_q;

// TODO it would be better to allocate these only when needed
ptp_script_msg_q msg_q_in; // messages to pc from script
ptp_script_msg_q msg_q_out; // messages to script from pc

unsigned script_msg_q_next(unsigned i) {
  if(i == PTP_SCRIPT_MSG_Q_LEN - 1) {
    return 0;
  }
  return i+1;
}

unsigned script_msg_q_full(ptp_script_msg_q *q) {
  return (script_msg_q_next(q->w) == q->r);
}

unsigned script_msg_q_empty(ptp_script_msg_q *q) {
  return (q->w == q->r);
}

int enqueue_script_msg(ptp_script_msg_q *q,ptp_script_msg *msg) {
  unsigned w = script_msg_q_next(q->w);
  if(w == q->r) {
    return 0;
  }
  // zero size messages don't make any sense
  if(msg == NULL || msg->size == 0) {
    return 0;
  }
  q->q[q->w] = msg;
  q->w = w;
  return 1;
}

ptp_script_msg* dequeue_script_msg(ptp_script_msg_q *q) {
  ptp_script_msg *msg;
  if(script_msg_q_empty(q)) {
    return NULL;
  }
  msg = q->q[q->r];
  q->r = script_msg_q_next(q->r);
  return msg;
}

// public interface for script
ptp_script_msg* ptp_script_create_msg(unsigned type, unsigned subtype, unsigned datasize, const void *data) {
  ptp_script_msg *msg;
  if(!datasize) {
    return NULL;
  }
  msg = malloc(sizeof(ptp_script_msg) + datasize);
  msg->size = datasize;
  msg->type = type;
  msg->subtype = subtype;
  // caller may fill in data themselves
  if(data) {
      memcpy(msg->data,data,msg->size);
  }
  return msg;
}

int ptp_script_write_msg(ptp_script_msg *msg) {
  msg->script_id = script_run_id;
  return enqueue_script_msg(&msg_q_out,msg);
}

ptp_script_msg* ptp_script_read_msg(void) {
  ptp_script_msg *msg;
  while(1) {
    msg = dequeue_script_msg(&msg_q_in); 
    // no messages
    if(!msg) {
        return NULL;
    }
    // does message belong to our script
    if(!msg->script_id || msg->script_id == script_run_id) {
      return msg;
    } else {
    // no: discard and keep looking
      free(msg);
    }
  }
}
int ptp_script_write_error_msg(unsigned errtype, const char *err) {
  if(script_msg_q_full(&msg_q_out)) {
    return 0;
  }
  ptp_script_msg *msg = ptp_script_create_msg(PTP_CHDK_S_MSGTYPE_ERR,errtype,strlen(err),err);
  if(!msg) {
    return 0;
  }
  return ptp_script_write_msg(msg);
}

#endif

static int handle_ptp(
               int h, ptp_data *data, int opcode, int sess_id, int trans_id,
               int param1, int param2, int param3, int param4, int param5)
{
  static union {
    char *str;
  } temp_data;
  static int temp_data_kind = 0; // 0: nothing, 1: ascii string, 2: lua object
  static int temp_data_extra; // size (ascii string) or type (lua object)
  PTPContainer ptp;

  // initialise default response
  memset(&ptp,0,sizeof(PTPContainer));
  ptp.code = PTP_RC_OK;
  ptp.sess_id = sess_id;
  ptp.trans_id = trans_id;
  ptp.num_param = 0;
  
  // TODO calling this on every PTP command is not good,
  // since it figures out free memory by repeatedly malloc'ing!
  buf_size=core_get_free_memory()>>1;

  // handle command
  switch ( param1 )
  {

    case PTP_CHDK_Version:
      ptp.num_param = 2;
      ptp.param1 = PTP_CHDK_VERSION_MAJOR;
      ptp.param2 = PTP_CHDK_VERSION_MINOR;
      break;
    case PTP_CHDK_ScriptSupport:
      ptp.num_param = 1;
      ptp.param1 = 0;
#ifdef OPT_LUA
      ptp.param1 |= PTP_CHDK_SCRIPT_SUPPORT_LUA;
#endif
      break;
    case PTP_CHDK_ScriptStatus:
      ptp.num_param = 1;
// TODO script_is_running should always be defined, just ret 0 if script disabled
      ptp.param1 = 0;
#ifdef OPT_SCRIPTING
      ptp.param1 |= script_is_running()?PTP_CHDK_SCRIPT_STATUS_RUN:0;
#ifdef OPT_LUA
      ptp.param1 |= (!script_msg_q_empty(&msg_q_out))?PTP_CHDK_SCRIPT_STATUS_MSG:0;
#endif
#endif
      break;
    case PTP_CHDK_GetMemory:
      if ( param2 == 0 || param3 < 1 ) // null pointer or invalid size?
      {
        ptp.code = PTP_RC_GeneralError;
        break;
      }

      if ( !send_ptp_data(data,(char *) param2,param3) )
      {
        ptp.code = PTP_RC_GeneralError;
      }
      break;
      
    case PTP_CHDK_SetMemory:
      if ( param2 == 0 || param3 < 1 ) // null pointer or invalid size?
      {
        ptp.code = PTP_RC_GeneralError;
        break;
      }

      data->get_data_size(data->handle); // XXX required call before receiving
      if ( !recv_ptp_data(data,(char *) param2,param3) )
      {
        ptp.code = PTP_RC_GeneralError;
      }
      break;

    case PTP_CHDK_CallFunction:
      {
        int s;
        int *buf = (int *) malloc((10+1)*sizeof(int));

        if ( buf == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        s = data->get_data_size(data->handle);
        if ( !recv_ptp_data(data,(char *) buf,s) )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        ptp.num_param = 1;
        ptp.param1 = ((int (*)(int,int,int,int,int,int,int,int,int,int)) buf[0])(buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9],buf[10]);

        free(buf);
        break;
      }

    case PTP_CHDK_TempData:
      if ( param2 & PTP_CHDK_TD_DOWNLOAD )
      {
        const char *s = NULL;
        size_t l = 0;

        if ( temp_data_kind == 0 )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        if ( temp_data_kind == 1 )
        {
          s = temp_data.str;
          l = temp_data_extra;
        }

        if ( !send_ptp_data(data,s,l) )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        
      } else if ( ! (param2 & PTP_CHDK_TD_CLEAR) ) {
        if ( temp_data_kind == 1 )
        {
          free(temp_data.str);
        }
        temp_data_kind = 0;

        temp_data_extra = data->get_data_size(data->handle);

        temp_data.str = (char *) malloc(temp_data_extra);
        if ( temp_data.str == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        if ( !recv_ptp_data(data,temp_data.str,temp_data_extra) )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        temp_data_kind = 1;
      }
      if ( param2 & PTP_CHDK_TD_CLEAR )
      {
        if ( temp_data_kind == 1 )
        {
          free(temp_data.str);
        }
        temp_data_kind = 0;
      }
      break;

    case PTP_CHDK_UploadFile:
      {
        FILE *f;
        int s,r,fn_len;
        char *buf, *fn;

        s = data->get_data_size(data->handle);

        recv_ptp_data(data,(char *) &fn_len,4);
        s -= 4;

        fn = (char *) malloc(fn_len+1);
        if ( fn == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        fn[fn_len] = '\0';

        recv_ptp_data(data,fn,fn_len);
        s -= fn_len;

        f = fopen(fn,"wb");
        if ( f == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          free(fn);
          break;
        }
        free(fn);

        buf = (char *) malloc(buf_size);
        if ( buf == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        while ( s > 0 )
        {
          if ( s >= buf_size )
          {
            recv_ptp_data(data,buf,buf_size);
            fwrite(buf,1,buf_size,f);
            s -= buf_size;
          } else {
            recv_ptp_data(data,buf,s);
            fwrite(buf,1,s,f);
            s = 0;
          }
        }

        fclose(f);

        free(buf);
        break;
      }
      
    case PTP_CHDK_DownloadFile:
      {
        FILE *f;
        int tmp,t,s,r,fn_len;
        char *buf, *fn;

        if ( temp_data_kind != 1 )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        fn = (char *) malloc(temp_data_extra+1);
        if ( fn == NULL )
        {
          free(temp_data.str);
          temp_data_kind = 0;
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        memcpy(fn,temp_data.str,temp_data_extra);
        fn[temp_data_extra] = '\0';

        free(temp_data.str);
        temp_data_kind = 0;

        f = fopen(fn,"rb");
        if ( f == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          free(fn);
          break;
        }
        free(fn);

        fseek(f,0,SEEK_END);
        s = ftell(f);
        fseek(f,0,SEEK_SET);

        buf = (char *) malloc(buf_size);
        if ( buf == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        tmp = s;
        t = s;
        while ( (r = fread(buf,1,(t<buf_size)?t:buf_size,f)) > 0 )
        {
          t -= r;
          // cannot use send_ptp_data here
          data->send_data(data->handle,buf,r,tmp,0,0,0);
          tmp = 0;
        }
        fclose(f);
        // XXX check that we actually read/send s bytes! (t == 0)

        ptp.num_param = 1;
        ptp.param1 = s;

        free(buf);

        break;
      }
      break;

#ifdef OPT_LUA
    // TODO this should flush data even if scripting isn't supported
    case PTP_CHDK_ExecuteScript:
      {
        int s;
        char *buf;

        script_run_id++;
        ptp.num_param = 2;
        ptp.param1 = script_run_id;

        if ( param2 != PTP_CHDK_SL_LUA )
        {
          ptp.code = PTP_RC_ParameterNotSupported;
          break;
        }

        s = data->get_data_size(data->handle);
        
        buf = (char *) malloc(s);
        if ( buf == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        recv_ptp_data(data,buf,s);

        // error details will be passed in a message
        if (script_start_ptp(buf) < 0) {
          ptp.param2 = PTP_CHDK_S_ERRTYPE_COMPILE;
        } else {
          ptp.param2 = PTP_CHDK_S_ERRTYPE_NONE;
        }

        free(buf);
        
        break;
      }
    case PTP_CHDK_ReadScriptMsg:
    {
      ptp_script_msg *msg = dequeue_script_msg(&msg_q_out);
      ptp.num_param = 4;
      if(!msg) {
        // return a fully formed message for easier handling
        ptp.param1 = PTP_CHDK_S_MSGTYPE_NONE;
        ptp.param2 = 0;
        ptp.param3 = 0;
        ptp.param4 = 4;
        // looks like we need to send some data no matter what
        if ( !send_ptp_data(data,"\0\0\0",4) )
        {
          ptp.code = PTP_RC_GeneralError;
        }
        break;
      }
      ptp.param1 = msg->type;
      ptp.param2 = msg->subtype;
      ptp.param3 = msg->script_id;
      ptp.param4 = msg->size;

      // NOTE message is lost if sending failed
      if ( !send_ptp_data(data,msg->data,msg->size) )
      {
        ptp.code = PTP_RC_GeneralError;
      }
      free(msg);
      break;
    }
    case PTP_CHDK_WriteScriptMsg:
    {
      int msg_size;
      ptp_script_msg *msg;
      ptp.num_param = 1;
      ptp.param1 = PTP_CHDK_S_MSGSTATUS_OK;
      if (!script_is_running()) {
        ptp.param1 = PTP_CHDK_S_MSGSTATUS_NOTRUN;
      } else if(param2 && param2 != script_run_id) {// check if target script for message is running
        ptp.param1 = PTP_CHDK_S_MSGSTATUS_BADID;
      } else if(script_msg_q_full(&msg_q_in)) {
        ptp.param1 = PTP_CHDK_S_MSGSTATUS_QFULL;
      }

      msg_size = data->get_data_size(data->handle);

      // if something was wrong, don't bother creating message, just flush
      if(ptp.param1 != PTP_CHDK_S_MSGSTATUS_OK) {
        flush_recv_ptp_data(data,msg_size);
        break;
      }
      msg = ptp_script_create_msg(PTP_CHDK_S_MSGTYPE_USER,PTP_CHDK_TYPE_STRING,msg_size,NULL);
      if ( !msg ) // malloc error or zero size
      {
        // if size is zero, things will get hosed no matter what
        flush_recv_ptp_data(data,msg_size);
        ptp.code = PTP_RC_GeneralError;
        break;
      }
      msg->script_id = param2;
      if ( !recv_ptp_data(data,msg->data,msg->size) )
      {
        ptp.code = PTP_RC_GeneralError;
        free(msg);
        break;
      }
      if( !enqueue_script_msg(&msg_q_in,msg) ) {
        ptp.code = PTP_RC_GeneralError;
        free(msg);
      }
      break;
    }
#endif

    default:
      ptp.code = PTP_RC_ParameterNotSupported;
      break;
  }

  // send response
  data->send_resp( data->handle, &ptp );
  
  return 1;
}

#endif // CAM_CHDK_PTP
