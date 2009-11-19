#define VBATT_DEFAULT_MIN (3500)
#define VBATT_DEFAULT_MAX (4100)

#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"

/* Ours stuff */
extern long link_bss_start;
extern long link_bss_end;
extern void boot();
extern void mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf);


static int stop_hooking;

static void (*taskprev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);

static void (*taskfsprev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);



void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}


static void task_start_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    _CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);

    taskprev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
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
    for (i=0;i<len;i++){
	if (s1[i] != s2[i])
	    return 1;
    }
    return 0;
}

void createHook (void *pNewTcb)
{
    char *name = (char*)(*(long*)((char*)pNewTcb+0x34));
    long *entry = (long*)((char*)pNewTcb+0x74);

    // always hook first task creation
    // to create SpyProc
    if (!stop_hooking){
	taskprev = (void*)(*entry);
	*entry = (long)task_start_hook;
	stop_hooking = 1;
    } else {
	// hook/replace another tasks
	if (my_ncmp(name, "tSwitchChe", 10) == 0){
	    *entry = (long)mykbd_task;
	}
	if (my_ncmp(name, "tInitFileM", 10) == 0){
	 //   taskfsprev = (void*)(*entry);
	    *entry = (long)init_file_modules_task;
	}

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

    // sanity check
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
	started();
	shutdown();
    }

    // initialize .bss senment
    while (bss<&link_bss_end)
	*bss++ = 0;

    // fill memory with this magic value so we could see what
    // parts of memory were or not used
    
    // update:
    // this seems to be required for unknown reason
    // or else sryproc startup will fail from
    // time to time...
#if 0
    for (ptr=(void*)MEMBASEADDR;((long)ptr)<MEMISOSTART;ptr+=4){
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
#define CF_EFL 48052

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/10000;
}

int get_focal_length(int zp) {
    if (zp<0) return fl_tbl[0];
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1];
    else return fl_tbl[zp];
}

int get_zoom_x(int zp) {
    if (zp<1) return 10;
    else if (zp>NUM_FL-1) return fl_tbl[NUM_FL-1]*10/fl_tbl[0];
    else return fl_tbl[zp]*10/fl_tbl[0];
}


static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
    { MODE_DIGITAL_MACRO,       0 },
    { MODE_P,                   1 },
    { MODE_NIGHT,               2 }, // 1-15s
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

int mode_get() {
    int mode, i, t=0xFF;
// play/rec without override
//    mode  = (physw_status[0]&0x0F)==0x0B ?  MODE_PLAY : MODE_REC;

// note: different from later cams
    mode = (playrec_mode==1)?MODE_REC:MODE_PLAY;

    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
