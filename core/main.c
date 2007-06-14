#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui.h"
#include "histogram.h"

#define FN_RAWDIR   "A/DCIM/%03dCANON"
#define FN_RAWF     (FN_RAWDIR "/" "CRW_%04d.CRW")

static long ramdump_num;
static char fn[64];

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

void dump_memory()
{
    int fd;
    long dirnum;

    started();

	dirnum = get_target_dir_num();
	sprintf(fn, FN_RAWDIR, dirnum);
	mkdir(fn);

	sprintf(fn, FN_RAWDIR "/" "DMP_%04d.JPG", dirnum, ++ramdump_num);
	fd = open(fn, O_WRONLY|O_CREAT, 0777);
	if (fd >= 0) {
	    write(fd, (void*)0, 0x1900);
	    write(fd, (void*)0x1900, 32*1024*1024-0x1900);
	    close(fd);
	}
    finished();
}

static long raw_data_available;

/* called from another process */
void core_rawdata_available()
{
    raw_data_available = 1;
}

static void process_rawsave()
{
    int fd;
    long dirnum;

    state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

    if (conf_save_raw){
	started();

	dirnum = get_target_dir_num();
	sprintf(fn, FN_RAWDIR, dirnum);
	mkdir(fn);

	sprintf(fn, FN_RAWF, dirnum, get_target_file_num());
	fd = open(fn, O_WRONLY|O_CREAT, 0777);
	if (fd >= 0) {
	    write(fd, hook_raw_image_addr(), hook_raw_size());
	    close(fd);
	}

	finished();
    }
}


void core_spytask()
{
    int cnt = 0;

    msleep(2000);

    gui_init();
    conf_restore();

    started();
    msleep(50);
    finished();

    while (1){

	if (raw_data_available){
	    process_rawsave();
	    hook_raw_save_complete();
	    raw_data_available = 0;
	    continue;
	}

	if (((cnt++) & 3) == 0)
	    gui_redraw();

	histogram_process();

	if ((state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) && (!shooting_in_progress()))
	    state_shooting_progress = SHOOTING_PROGRESS_DONE;

	msleep(20);
    }
}

