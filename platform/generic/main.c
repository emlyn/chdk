#include "camera.h"
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"

/* Ours stuff */
extern long link_bss_start;
extern long link_bss_end;
extern void boot();


static int stop_hooking;

static void (*task_prev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);

static void (*init_file_modules_prev)(
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

    task_prev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
}



static void init_file_modules_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    remount_filesystem();
    init_file_modules_prev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
}


static void capt_seq_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    capt_seq_task();
}


static void physw_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{
    mykbd_task();
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
	task_prev = (void*)(*entry);
	*entry = (long)task_start_hook;
	stop_hooking = 1;
    } else {
	// hook/replace another tasks
	if (my_ncmp(name, "tPhySw", 6) == 0){
	    *entry = (long)physw_hook;
	}

	if (my_ncmp(name, "tInitFileM", 10) == 0){
	    init_file_modules_prev = (void*)(*entry);
	  #if CAM_MULTIPART
	    *entry = (long)init_file_modules_task;
	  #else
	    *entry = (long)init_file_modules_hook;
	  #endif
	}

	if (my_ncmp(name, "tCaptSeqTa", 10) == 0){
	    *entry = (long)capt_seq_hook;
	}

	if (my_ncmp(name, "tMovieReco", 10) == 0){
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

