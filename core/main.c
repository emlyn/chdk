#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui.h"

#define FN_RAWDIR   "A/DCIM/100CANON"
#define FN_RAWF     (FN_RAWDIR "/" "CRW_%04d.JPG")

static char fn[64];
static long (*prev_hhandler)(long a);

#if 0
int taskop_txt_p;
char taskop_txt[6][32];
#endif

void core_hook_task_create(void *tcb)
{
#if 0
    char *name = (char*)(*(long*)((char*)tcb+0x34));
    strcpy(taskop_txt[taskop_txt_p]+1, name);
    taskop_txt[taskop_txt_p][0] = 'S';
    taskop_txt_p++;
    if (taskop_txt_p>5)
	taskop_txt_p = 0;
#endif
}

void core_hook_task_delete(void *tcb)
{
#if 0
    char *name = (char*)(*(long*)((char*)tcb+0x34));
    strcpy(taskop_txt[taskop_txt_p]+1, name);
    taskop_txt[taskop_txt_p][0] = 'E';

    taskop_txt_p++;
    if (taskop_txt_p>5)
	taskop_txt_p = 0;
#endif
}


void makedump()
{
    int fd;

    // got here second time in a row. Skip second RAW saveing.
    if (state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){
	return;
    }

    state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

    if (conf_save_raw){
	started();

	sprintf(fn, FN_RAWF, conf_raw_fileno++);
	fd = fopen(fn, "w+");
	if (fd >= 0) {
	    fwrite(hook_raw_image_addr(), 1, hook_raw_size(), fd);
	    fclose(fd);
	}
	conf_save(0);
	finished();
    }

}


void myhook1(long a)
{
    // only this caller allowed
    if (__builtin_return_address(0) == hook_raw_ret_addr()){
	makedump();
    }
    prev_hhandler(a);
}

void core_spytask()
{
    long *p = hook_raw_fptr();
    int cnt = 0;

    SleepTask(1000);

    gui_init();
    mkdir(FN_RAWDIR);
    conf_restore();

    started();
    SleepTask(50);
    finished();

    while (1){
	if (((cnt++) & 3) == 0)
	    gui_redraw();

	taskLock();
	if ((*p) != (long)myhook1){
	    prev_hhandler = (void*)*p;
	    *p=(long)myhook1;
	}
	taskUnlock();

	if ((state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) && (!shooting_in_progress()))
	    state_shooting_progress = SHOOTING_PROGRESS_DONE;

	SleepTask(20);
    }
}

