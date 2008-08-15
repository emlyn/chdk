#define VBATT_DEFAULT_MIN (3500)
#define VBATT_DEFAULT_MAX (4100)

#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "stdlib.h"

/* Ours stuff */
extern long link_bss_start;
extern long link_bss_end;
extern void boot();
extern void mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf);
extern void kbd_process_task(long ua, long ub, long uc, long ud, long ue, long uf);

static int stop_hooking;

static void (*taskprev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);

static void (*taskfsprev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);



void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
	{
    core_spytask(); // This is the main CHDK loop
	}


static void task_start_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
	{
    _CreateTask("SpyTask", 0x19, 0x2000, spytask, 0); // First creates the SpyTask, i.e. the main CHDK loop
    
    //create our second keypress task
		_CreateTask("SpyTask2", 0x18, 0x2000, kbd_process_task, 0); 
    
    taskprev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); // then, whatever was the call intended to be...
	}



static void task_fs(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
	{
    remount_filesystem();
    taskfsprev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
	}


static void capt_seq_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
	{
    capt_seq_task();
	}

static void movie_record_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
	{
    movie_record_task();
	}



static int my_ncmp(const char *s1, const char *s2, long len)
	{
    int i;
    for (i=0;i<len;i++)
		{
		if (s1[i] != s2[i])
			return 1;
		}
    return 0;
	}

void createHook (void *pNewTcb)
{
    char *name = (char*)(*(long*)((char*)pNewTcb+0x34));
    long *entry = (long*)((char*)pNewTcb+0x74);
    
    //volatile long *p; p=(void*) 0xc02200E0; *p=0x46; //debug led
    
    // always hook first task creation
    // to create SpyTask
    if (!stop_hooking){
        taskprev = (void*)(*entry);
        *entry = (long)task_start_hook;
        stop_hooking = 1;
    }else{
        // hook/replace another tasks
        // Replace the call to "SwitchCheckTask" with our own procedure
        if (my_ncmp(name, "tSwitchChe", 10) == 0){
            *entry = (long)mykbd_task;
        }
        
        // Replace the call to "InitFileModules" with our own procedure
        if (my_ncmp(name, "tInitFileM", 10) == 0){
            taskfsprev = (void*)(*entry);
            *entry = (long)task_fs;
        }
        
        // Replace the call to "CaptSeqTask" with our own procedure
        if (my_ncmp(name, "tCaptSeqTa", 10) == 0){
            *entry = (long)capt_seq_hook;
        }

        if (my_ncmp(name, "tMovieRecT", 10) == 0){
            *entry = (long)movie_record_hook;
        }

core_hook_task_create(pNewTcb);
}
	}

void deleteHook (void *pTcb)
	{
    core_hook_task_delete(pTcb);
	}

void startup()
	{
    long *bss = &link_bss_start;
    long *ptr;
    long i,l;

    //volatile long *p; p=(void*) 0xc02200E0; *p=0x46; //debug led

    // sanity check
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)) {
			started();
			shutdown();
    }

    // initialize .bss segment
    while (bss<&link_bss_end)
		*bss++ = 0;

    // fill memory with this magic value so we could see what
    // parts of memory were or not used
    
    // update:
    // this seems to be required for unknown reason
    // or else sryproc startup will fail from
    // time to time...
#if 0
    for (ptr=(void*)MEMBASEADDR;((long)ptr)<MEMISOSTART;ptr+=4)
		{
		ptr[0]=0x55555555;
		ptr[1]=0x55555555;
		ptr[2]=0x55555555;
		ptr[3]=0x55555555;
		}
#endif

    boot();
	}

long get_vbatt_min()
	{
    return 3500;
	}

long get_vbatt_max()
	{
    return 4100;
	}


static const int fl_tbl[] = {7700,9030,10490,12520,15600,18780,23100};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 47946

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) 
	{
    return (CF_EFL*get_focal_length(zp))/10000;
	}

int get_focal_length(int zp) 
	{
    if (zp<0) return fl_tbl[0];
		else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1];
				else return fl_tbl[zp];
	}

int get_zoom_x(int zp) 
	{
    if (zp<1) return 10;
		else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1]*10/fl_tbl[0];
				else return fl_tbl[zp]*10/fl_tbl[0];
	}


static struct
	{
	int hackmode;
	int canonmode;
	}
	modemap[] =
	{
    { MODE_P,                   1 },
    { MODE_AUTO,                3 },
    { MODE_MY_COLORS,           4 },
    { MODE_PORTRAIT,            5 },
    { MODE_SCN_GRASS,           6 },
    { MODE_SCN_SNOW,            7 },
    { MODE_SCN_BEACH,           8 },
    { MODE_SCN_FIREWORK,        9 }, 
    { MODE_SCN_WATER,          10 },
    { MODE_SCN_PARTY,          11 },
    { MODE_SCN_CHILD,          12 },
    { MODE_SCN_NIGHT,          13 },
    { MODE_STITCH,             14 },
    { MODE_VIDEO_STD,          15 }
	};

#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() 
	{
    int mode, i, t=0xFF;
    mode  = (physw_status[0]&0x03)==0x01 ?  MODE_PLAY : MODE_REC;
    t=0xFF;
    _GetPropertyCase(0, &t, 4);
    for (i=0; i<MODESCNT; ++i)
		{
		if (modemap[i].canonmode == t)
			{
			return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
			}
		}
    return (mode);
	}

#if 0
  //CAM_CONSOLE_LOG_ENABLED
#define DEV_HDR_WRITE_OFFSET (0x14C/4)

typedef int DEV_HDR;

int (*_tyWriteOrig)(DEV_HDR *hdr, char *buf, int len);


int hook_tyWriteOrig(DEV_HDR *hdr, char *buf, int len)
{
	// Slow, but stable writes
	FILE *fd = fopen("A/stdout.txt", "a");
	if (fd) {
	    fwrite(buf, 1, len, fd);
	    fclose(fd);
	}

    return _tyWriteOrig(hdr, buf, len);

}

void console_init()
{
    DEV_HDR *DRV_struct;

    DRV_struct = _iosDevFind("/tyCo/0", 0);

    _tyWriteOrig = (void*)DRV_struct[DEV_HDR_WRITE_OFFSET];

	FILE *fd = fopen("A/chdklog.txt", "a");
	if (fd) {
	    // can't be used with "Fut" API
	    //fprintf(fd, "DRV_struct: %x, _tyWriteOrig: %x\n", DRV_struct, _tyWriteOrig);
	    char buf[256];
	    int buflen = sprintf(buf, "DRV_struct: %x, _tyWriteOrig: %x\n", DRV_struct, _tyWriteOrig);
	    fwrite(buf, 1, buflen, fd);
	}

	FILE *fdout = fopen("A/stdout.txt", "r");
	if (fdout)
	{
        DRV_struct[DEV_HDR_WRITE_OFFSET] = (int)hook_tyWriteOrig;
        fclose(fdout);
	    // fprintf(fd, "tyWrite replaced, camera log enabled\n");
	    fwrite("tyWrite replaced, camera log enabled\n", 1, sizeof("tyWrite replaced, camera log enabled\n"), fd);
    }

	if (fd)
	{
	    fclose(fd);
	}

}
xx
#endif
