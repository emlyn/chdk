#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"
#include "console.h"
#if DNG_SUPPORT
    #include "dng.h"
    #include "math.h"
    #include "keyboard.h"
    #include "action_stack.h"
    #include "gui_draw.h"
    #include "gui_mbox.h"
    #include "gui_lang.h"
#endif
#ifdef OPT_CURVES
    #include "curves.h"
#endif
#include "shot_histogram.h"

//-------------------------------------------------------------------
#define RAW_TARGET_DIRECTORY    "A/DCIM/%03dCANON"
//#define RAW_TMP_FILENAME        "HDK_RAW.TMP"
#define RAW_TARGET_FILENAME     "%s%04d%s"
#define RAW_BRACKETING_FILENAME "%s%04d_%02d%s" 

#define PATH_BADPIXEL_BIN "A/CHDK/badpixel.bin"
#define PATH_BAD_TMP_BIN "A/CHDK/bad_tmp.bin"

//-------------------------------------------------------------------
static char fn[64];
static char dir[32];
static int develop_raw=0;
//-------------------------------------------------------------------
void raw_prepare_develop(const char* filename){
 if (filename) {
  develop_raw=1; 
  strcpy(fn,filename);
 }
 else {
  develop_raw=0;
 }
}

//-------------------------------------------------------------------
void patch_bad_pixels(void);
//-------------------------------------------------------------------

char* get_raw_image_addr(void){
 if (!conf.raw_cache) return hook_raw_image_addr();
 else return (char*) ((int)hook_raw_image_addr()&~CAM_UNCACHED_BIT);
}

char* get_alt_raw_image_addr(void){    // return inactive buffer for cameras with multiple RAW buffers (otherwise return active buffer)
 if (!conf.raw_cache) return hook_alt_raw_image_addr();
 else return (char*) ((int)hook_alt_raw_image_addr()&~CAM_UNCACHED_BIT);
}

//-------------------------------------------------------------------

#if DNG_SUPPORT
unsigned int get_bad_count_and_write_file(const char *fn){
 int count=0;
 unsigned short c[2];
 FILE*f;
 f=fopen(fn,"w+b");
 for (c[1]=CAM_ACTIVE_AREA_Y1; c[1]<CAM_ACTIVE_AREA_Y2; c[1]++)
   for (c[0]=CAM_ACTIVE_AREA_X1; c[0]<CAM_ACTIVE_AREA_X2; c[0]++)
    if (get_raw_pixel(c[0],c[1])==0) { fwrite(c, 1, 4, f); count++;}
 fclose(f);
 return count;
}

unsigned short get_raw_pixel(unsigned int x,unsigned  int y);

static unsigned char gamma[256];

void fill_gamma_buf(void){
 int i;
 if (gamma[255]) return;
#if defined(CAMERA_sx30) || defined(CAMERA_g12)
 for (i=0; i<12; i++) gamma[i]=255*pow(i/255.0, 0.5);
 for (i=12; i<64; i++) gamma[i]=255*pow(i/255.0, 0.4);
 for (i=64; i<=255; i++) gamma[i]=255*pow(i/255.0, 0.25);
#else
 for (i=0; i<=255; i++) gamma[i]=255*pow(i/255.0, 0.5);
#endif
}


void create_thumbnail(char* buf){
 unsigned int i, j, x, y;
 unsigned char r, g, b;
 for (i=0; i<DNG_TH_HEIGHT; i++)
   for (j=0; j<DNG_TH_WIDTH; j++) {
    x=CAM_ACTIVE_AREA_X1+((CAM_ACTIVE_AREA_X2-CAM_ACTIVE_AREA_X1)*j)/DNG_TH_WIDTH;
    y=CAM_ACTIVE_AREA_Y1+((CAM_ACTIVE_AREA_Y2-CAM_ACTIVE_AREA_Y1)*i)/DNG_TH_HEIGHT;
#if cam_CFAPattern==0x02010100    // Red  Green  Green  Blue
    r=gamma[get_raw_pixel((x/2)*2,(y/2)*2)>>(CAM_SENSOR_BITS_PER_PIXEL-8)]; // red pixel
    g=gamma[6*(get_raw_pixel((x/2)*2+1,(y/2)*2)>>(CAM_SENSOR_BITS_PER_PIXEL-8))/10]; // green pixel
    b=gamma[get_raw_pixel((x/2)*2+1,(y/2)*2+1)>>(CAM_SENSOR_BITS_PER_PIXEL-8)]; //blue pixel
#elif cam_CFAPattern==0x01000201 // Green  Blue  Red  Green
    r=gamma[get_raw_pixel((x/2)*2,(y/2)*2+1)>>(CAM_SENSOR_BITS_PER_PIXEL-8)]; // red pixel
    g=gamma[6*(get_raw_pixel((x/2)*2,(y/2)*2)>>(CAM_SENSOR_BITS_PER_PIXEL-8))/10]; // green pixel
    b=gamma[get_raw_pixel((x/2)*2+1,(y/2)*2)>>(CAM_SENSOR_BITS_PER_PIXEL-8)]; //blue pixel
#else 
 #error please define new pattern here
#endif
    *buf++=r; *buf++=g; *buf++=b; 
   }
}
#endif
//-------------------------------------------------------------------

int raw_savefile() {
    int ret = 0;  
    int fd, m=(mode_get()&MODE_SHOOTING_MASK);
    static struct utimbuf t;
    static int br_counter; 
#if DNG_SUPPORT
     struct t_data_for_exif* exif_data = NULL;  
     char *thumbnail_buf = NULL;
     if (conf.dng_raw) exif_data=capture_data_for_exif();
#endif    
    if (state_kbd_script_run && shot_histogram_isenabled()) build_shot_histogram();

    // Get pointers to RAW buffers (will be the same on cameras that don't have two or more buffers)
    char* rawadr = get_raw_image_addr();
    char* altrawadr = get_alt_raw_image_addr();

    // ! ! ! exclusively for badpixel creation ! ! !
    // NOTE: get_bad_count_and_write_file() must be called from here and cannot be called
    // outside of this function.
    // TODO now that we make badpixel in code, special use of save_raw is not needed
    // also don't need to actually save a raw when making bad pixel
#if DNG_SUPPORT
    if (conf.save_raw==255) conf.save_raw=get_bad_count_and_write_file(PATH_BAD_TMP_BIN);
#endif
    //

    if (develop_raw) {
     started();
     fd = open(fn, O_RDONLY, 0777);
     if (fd>=0) {
      read(fd, get_raw_image_addr(), hook_raw_size());
      close(fd);
      }
#ifdef OPT_CURVES
     if (conf.curve_enable) curve_apply();
#endif
     finished();
     develop_raw=0;
     return 0;
    }

    if (conf.bad_pixel_removal) patch_bad_pixels();

    shooting_bracketing();

    if(conf.tv_bracket_value || conf.av_bracket_value || conf.iso_bracket_value || conf.subj_dist_bracket_value) {
        if(state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)
            br_counter = 1;
        else
            br_counter++;
    }
    else
        br_counter=0;


    // got here second time in a row. Skip second RAW saving.
    if (conf.raw_save_first_only && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) {
        return 0;
    }
    
    state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

    if (conf.save_raw
        && (!(shooting_get_prop(PROPCASE_RESOLUTION)==5))
        && (!((movie_status > 1) && conf.save_raw_in_video)) 
        && (!((m==MODE_SPORTS) && conf.save_raw_in_sports)) 
        && (!((m==MODE_AUTO) && conf.save_raw_in_auto)) 
        && (!(conf.edge_overlay_enable && conf.save_raw_in_edgeoverlay))
        && (!((shooting_get_drive_mode()==1) && conf.save_raw_in_burst && !(m==MODE_SPORTS))) 
        && (!((shooting_get_drive_mode()>=2) && conf.save_raw_in_timer))
        && (!((shooting_get_prop(PROPCASE_BRACKET_MODE)==1) && conf.save_raw_in_ev_bracketing)) )
    {
        long v;
        int timer; char txt[30];

        started();

        t.actime = t.modtime = time(NULL);

        mkdir("A/DCIM");
#if defined(CAM_DATE_FOLDER_NAMING)
        if (conf.raw_in_dir)
            get_target_dir_name(dir);
        else
            sprintf(dir, RAW_TARGET_DIRECTORY, 100);
#else
        sprintf(dir, RAW_TARGET_DIRECTORY, (conf.raw_in_dir)?get_target_dir_num():100);
#endif
        mkdir(dir);

        sprintf(fn, "%s/", dir);
        if(br_counter && conf.bracketing_add_raw_suffix && (shooting_get_drive_mode()!=1)) {
            sprintf(fn+strlen(fn), 
                    RAW_BRACKETING_FILENAME,
                    img_prefixes[conf.raw_prefix],
                    get_target_file_num(),
                    br_counter,
                    conf.dng_raw&&conf.raw_dng_ext ? ".DNG" : img_exts[conf.raw_ext]);
        } else {
            sprintf(fn+strlen(fn),
                    RAW_TARGET_FILENAME,
                    img_prefixes[conf.raw_prefix],
                    get_target_file_num(),
                    conf.dng_raw&&conf.raw_dng_ext ? ".DNG" : img_exts[conf.raw_ext]); 
        }
        fd = open(fn, O_WRONLY|O_CREAT, 0777);
        if (fd>=0) {
            timer=get_tick_count();
#if DNG_SUPPORT
            if (conf.dng_raw) {
             fill_gamma_buf();
             create_dng_header(exif_data);
             thumbnail_buf = malloc(DNG_TH_WIDTH*DNG_TH_HEIGHT*3);
              if (get_dng_header() && thumbnail_buf) {
               patch_bad_pixels_b();
               create_thumbnail(thumbnail_buf);
               write(fd, get_dng_header(), get_dng_header_size());
               write(fd, thumbnail_buf, DNG_TH_WIDTH*DNG_TH_HEIGHT*3);
               reverse_bytes_order2(rawadr, altrawadr, hook_raw_size());
             }
            }
#endif
            if (conf.dng_raw) {
                // Write alternate (inactive) buffer that we reversed the bytes into above (if only one buffer then it will be the active buffer instead)
                write(fd, (char*)(((unsigned long)altrawadr)|CAM_UNCACHED_BIT), hook_raw_size());
            }
            else
            {
                // Write active RAW buffer
                write(fd, (char*)(((unsigned long)rawadr)|CAM_UNCACHED_BIT), hook_raw_size());
            }
            close(fd);
            utime(fn, &t);
#if DNG_SUPPORT
            if (conf.dng_raw) {
             if (get_dng_header() && thumbnail_buf) {
                 if (rawadr == altrawadr)    // If only one RAW buffer then we have to swap the bytes back
                    reverse_bytes_order2(rawadr, altrawadr, hook_raw_size());
          //   unpatch_bad_pixels_b();
              }
             if (get_dng_header()) free_dng_header();
             if (thumbnail_buf) free(thumbnail_buf);
            }
#endif
            if (conf.raw_timer) {
                timer=get_tick_count()-timer;
                sprintf(txt, "saving time=%d", timer);
                console_add_line(txt);
            }
        }

        finished();

        ret = (fd >= 0);
    }

#ifdef OPT_CURVES
    if (conf.curve_enable) curve_apply();
#endif
    return ret;
}

//-------------------------------------------------------------------
void raw_postprocess() {
}

//-------------------------------------------------------------------

void set_raw_pixel(unsigned int x, unsigned int y, unsigned short value){
#if CAM_SENSOR_BITS_PER_PIXEL==10
 unsigned char* addr=(unsigned char*)get_raw_image_addr()+y*RAW_ROWLEN+(x/8)*CAM_SENSOR_BITS_PER_PIXEL;
 switch (x%8) {
  case 0: addr[0]=(addr[0]&0x3F)|(value<<6); addr[1]=value>>2;                  break;
  case 1: addr[0]=(addr[0]&0xC0)|(value>>4); addr[3]=(addr[3]&0x0F)|(value<<4); break;
  case 2: addr[2]=(addr[2]&0x03)|(value<<2); addr[3]=(addr[3]&0xF0)|(value>>6); break;
  case 3: addr[2]=(addr[2]&0xFC)|(value>>8); addr[5]=value;                     break;
  case 4: addr[4]=value>>2;                  addr[7]=(addr[7]&0x3F)|(value<<6); break;
  case 5: addr[6]=(addr[6]&0x0F)|(value<<4); addr[7]=(addr[7]&0xC0)|(value>>4); break;
  case 6: addr[6]=(addr[6]&0xF0)|(value>>6); addr[9]=(addr[9]&0x03)|(value<<2); break;
  case 7: addr[8]=value;                     addr[9]=(addr[9]&0xFC)|(value>>8); break;
 }
#elif CAM_SENSOR_BITS_PER_PIXEL==12
 unsigned char* addr=(unsigned char*)get_raw_image_addr()+y*RAW_ROWLEN+(x/4)*6;
 switch (x%4) {
  case 0: addr[0] = (addr[0]&0x0F) | (unsigned char)(value << 4);  addr[1] = (unsigned char)(value >> 4);  break;
  case 1: addr[0] = (addr[0]&0xF0) | (unsigned char)(value >> 8);  addr[3] = (unsigned char)value;         break;
  case 2: addr[2] = (unsigned char)(value >> 4);  addr[5] = (addr[5]&0x0F) | (unsigned char)(value << 4);  break;
  case 3: addr[4] = (unsigned char)value; addr[5] = (addr[5]&0xF0) | (unsigned char)(value >> 8);  break;
 }
#else 
 #error define set_raw_pixel for sensor bit depth
#endif
}

//-------------------------------------------------------------------
unsigned short get_raw_pixel(unsigned int x,unsigned  int y){
#if CAM_SENSOR_BITS_PER_PIXEL==10
 unsigned char* addr=(unsigned char*)get_raw_image_addr()+y*RAW_ROWLEN+(x/8)*CAM_SENSOR_BITS_PER_PIXEL;
 switch (x%8) {
  case 0: return ((0x3fc&(((unsigned short)addr[1])<<2)) | (addr[0] >> 6));
  case 1: return ((0x3f0&(((unsigned short)addr[0])<<4)) | (addr[3] >> 4));
  case 2: return ((0x3c0&(((unsigned short)addr[3])<<6)) | (addr[2] >> 2));
  case 3: return ((0x300&(((unsigned short)addr[2])<<8)) | (addr[5])); 
  case 4: return ((0x3fc&(((unsigned short)addr[4])<<2)) | (addr[7] >> 6)); 
  case 5: return ((0x3f0&(((unsigned short)addr[7])<<4)) | (addr[6] >> 4)); 
  case 6: return ((0x3c0&(((unsigned short)addr[6])<<6)) | (addr[9] >> 2)); 
  case 7: return ((0x300&(((unsigned short)addr[9])<<8)) | (addr[8])); 
 }
#elif CAM_SENSOR_BITS_PER_PIXEL==12
 unsigned char* addr=(unsigned char*)get_raw_image_addr()+y*RAW_ROWLEN+(x/4)*6;
 switch (x%4) {
  case 0: return ((unsigned short)(addr[1]) << 4) | (addr[0] >> 4);
  case 1: return ((unsigned short)(addr[0] & 0x0F) << 8) | (addr[3]);
  case 2: return ((unsigned short)(addr[2]) << 4) | (addr[5] >> 4);
  case 3: return ((unsigned short)(addr[5] & 0x0F) << 8) | (addr[4]);
 }
#else 
 #error define get_raw_pixel for sensor bit depth
#endif
 return 0;
}

//-------------------------------------------------------------------
void patch_bad_pixel(unsigned int x,unsigned  int y){
 int sum=0;
 int nzero=0;
 int i,j;
 int val;
 if ((x>=2) && (x<CAM_RAW_ROWPIX-2) && (y>=2) && (y<CAM_RAW_ROWS-2)) {
  if ((conf.bad_pixel_removal==1) || conf.dng_raw) {  // interpolation or DNG saving 
   for (i=-2; i<=2; i+=2)
    for (j=-2; j<=2; j+=2) 
     if ((i!=0) && (j!=0)) {
      val=get_raw_pixel(x+i, y+j);
      if (val) {sum+=val; nzero++;}
     }
   if (nzero) set_raw_pixel(x,y,sum/nzero);
  }
  else if (conf.bad_pixel_removal==2)  // or this makes RAW converter (internal/external) 
   set_raw_pixel(x,y,0);   
 }
}

struct point{
 int x;
 int y;
 struct point *next;
} *pixel_list=NULL;

void patch_bad_pixels(void){
 struct point *pixel=pixel_list;
 while (pixel){
  patch_bad_pixel((*pixel).x,(*pixel).y);
  pixel=(*pixel).next;
 }
}

void make_pixel_list(char * ptr){
 int x,y;
 struct point *pixel;
 char *endptr;
 while(*ptr){
  while (*ptr==' ' || *ptr=='\t') ++ptr; // whitespaces
   x=strtol(ptr, &endptr, 0);
   if (endptr != ptr) { 
    ptr = endptr;
    if (*ptr++==',') {
     while (*ptr==' ' || *ptr=='\t') ++ptr; // whitespaces
     if (*ptr!='\n' && *ptr!='\r'){
      y=strtol(ptr, &endptr, 0);
      if (endptr != ptr) { 
       ptr = endptr;
       pixel=malloc(sizeof(struct point));
       if (pixel) {
        (*pixel).x=x;
        (*pixel).y=y;
        (*pixel).next=pixel_list;
        pixel_list=pixel;
       }
      }
     }
    }
   }
   while (*ptr && *ptr!='\n') ++ptr; // unless end of line
   if (*ptr) ++ptr;
 }
}

#define PIXELS_BUF_SIZE 8192
void load_bad_pixels_list(const char* filename){
    char *buf;
    int fd;

    if (filename) {
        buf = umalloc(PIXELS_BUF_SIZE);
        if (!buf) return;

        fd = open(filename, O_RDONLY, 0777);
        if (fd>=0) {
            int rcnt = read(fd, buf, PIXELS_BUF_SIZE);
            if (rcnt > 0) {
                if (rcnt == PIXELS_BUF_SIZE) 
                buf[PIXELS_BUF_SIZE-1] = 0;
                else
                buf[rcnt] = 0;
            }
            close(fd);
        }
        make_pixel_list(buf);    
        ufree(buf);
    }

}

#if DNG_SUPPORT
short* binary_list=NULL;
int binary_count=0;

void load_bad_pixels_list_b(char* filename){
 struct stat st;
 long filesize;
 void* ptr;
 FILE *fd;
 binary_count=0;
 if (stat(filename,&st)!=0) return;
 filesize=st.st_size;
 if ((filesize==0) || (filesize%(2*sizeof(short))!=0)) return;
 ptr=malloc(filesize);
 if (!ptr) return;
 fd=fopen(filename, "rb");
 if (fd) {
  fread(ptr,1, filesize,fd);
  fclose(fd);
  binary_list=ptr;
  binary_count=filesize/(2*sizeof(short));
 }
 else free(ptr);
}

void unload_bad_pixels_list_b(void){
 if (binary_list) free(binary_list);
 binary_list=NULL;
 binary_count=0;
}

void patch_bad_pixels_b(void){
 int i;
 short* ptr=binary_list;
 for (i=0; i<binary_count; i++, ptr+=2) if (get_raw_pixel(ptr[0], ptr[1])==0) patch_bad_pixel(ptr[0], ptr[1]);
}
/*
void unpatch_bad_pixels_b(void){
 int i;
 short* ptr=binary_list;
 for (i=0; i<binary_count; i++, ptr+=2) set_raw_pixel(ptr[0], ptr[1], 0);
}
*/
int badpixel_list_loaded_b(void){
 return binary_count;
}

// -----------------------------------------------

enum BadpixelFSM
{
    BADPIX_START,
    BADPIX_S1,
    BADPIX_S2
};

int badpixel_task_stack(long p)
{
    static unsigned int badpix_cnt1, badpix_cnt2;
    static int raw_conf_bck;

    switch(p)
    {

    case BADPIX_START:
        action_pop();

        console_clear();
        console_add_line("Wait please... ");
        console_add_line("This takes a few seconds,");
        console_add_line("don't panic!");
        
        raw_conf_bck = conf.save_raw;
        conf.save_raw = 255;
        
        shooting_set_tv96_direct(96, SET_LATER);
        action_push(BADPIX_S1);
        action_push(AS_SHOOT);
        action_push_delay(3000);
        break;
    case BADPIX_S1:
        action_pop();        

        badpix_cnt1 = conf.save_raw;
        conf.save_raw = 255;
        shooting_set_tv96_direct(96, SET_LATER);

        action_push(BADPIX_S2);
        action_push(AS_SHOOT);
        break;
    case BADPIX_S2:
        action_pop();

        badpix_cnt2 = conf.save_raw;
        conf.save_raw = raw_conf_bck;

        console_clear();
        if (badpix_cnt1 == badpix_cnt2)
        {
            // TODO script asked confirmation first
            // should sanity check bad pixel count at least,
            /// wrong buffer address could make badpixel bigger than available mem
            char msg[32];
            console_add_line("badpixel.bin created.");
            sprintf(msg, "Bad pixel count: %d", badpix_cnt1);
            console_add_line(msg);
            DeleteFile_Fut(PATH_BADPIXEL_BIN);
            RenameFile_Fut(PATH_BAD_TMP_BIN,PATH_BADPIXEL_BIN);
        }
        else
        {
            console_add_line("badpixel.bin failed.");
            console_add_line("Please try again.");
        }
        DeleteFile_Fut(PATH_BAD_TMP_BIN);

        action_push_delay(3000);
        break;
    default:
        action_stack_standard(p);
        break;
    }
   
    return 1;
}


void create_badpixel_bin()
{
    if (!(mode_get() & MODE_REC))
    {
        gui_mbox_init(LANG_ERROR, LANG_MSG_RECMODE_REQUIRED, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
        return;
    }
        
    gui_set_mode(GUI_MODE_ALT);
    action_stack_create(&badpixel_task_stack, BADPIX_START);
}

#endif
