#define VBATT_DEFAULT_MIN (4550)
#define VBATT_DEFAULT_MAX (5150)

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
	    taskfsprev = (void*)(*entry);
	    *entry = (long)task_fs;
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
    return 4550;
}

long get_vbatt_max()
{
    return 5150;
}

static const struct {
    int zp, fl;
} fl_tbl[] = {
    {   0,   6000 },
    {  11,   6400 },
    {  41,  12100 },
    {  64,  21300 },
    {  86,  41600 },
    { 105,  61400 },
    { 128,  72000 },
};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 6000

const int zoom_points = 129;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/1000;
}

int get_focal_length(int zp) {
    int i;

    if (zp<fl_tbl[0].zp)
        return fl_tbl[0].fl;
    else if (zp>fl_tbl[NUM_FL-1].zp)
        return fl_tbl[NUM_FL-1].fl;
    else 
        for (i=1; i<NUM_FL; ++i) {
           if (zp==fl_tbl[i-1].zp) 
               return fl_tbl[i-1].fl;
           else if (zp==fl_tbl[i].zp) 
               return fl_tbl[i].fl;
           else if (zp<fl_tbl[i].zp)
               return fl_tbl[i-1].fl+(zp-fl_tbl[i-1].zp)*(fl_tbl[i].fl-fl_tbl[i-1].fl)/(fl_tbl[i].zp-fl_tbl[i-1].zp);
        }
    return fl_tbl[NUM_FL-1].fl;
}

int get_zoom_x(int zp) {
    return get_focal_length(zp)*10/fl_tbl[0].fl;
}


int screen_opened(void) {
//    mode |= (physw_copy[1] & 0x00000001)?0:MODE_SCREEN_OPENED;
	return !(physw_copy[1] & 0x00000001);
}

int screen_rotated(void) {
//    mode |= (physw_copy[1] & 0x00000002)?0:MODE_SCREEN_ROTATED;
	return !(physw_copy[1] & 0x00000002);
}

int rec_mode_active(void) {
//    mode  = (playrec_mode==1)?MODE_REC:MODE_PLAY;
	return (playrec_mode==1);
}
