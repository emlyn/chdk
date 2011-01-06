#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "stdlib.h"
#include "gui.h"
#include "histogram.h"
#include "raw.h"
#include "motion_detector.h"
#ifdef OPT_EDGEOVERLAY
    #include "edgeoverlay.h"
#endif
#include "led.h"
static int raw_need_postprocess;
static volatile int spytask_can_start;

void core_hook_task_create(void *tcb) {
}

void core_hook_task_delete(void *tcb) {
    char *name = (char*)(*(long*)((char*)tcb+0x34));
    if (strcmp(name,"tInitFileM")==0) core_spytask_can_start();
}

long core_get_noise_reduction_value() {
    return conf.raw_nr;
}

void dump_memory() {
    int fd;
    static int cnt=1;
    static char fn[32];

    started();
    mkdir("A/DCIM");
    mkdir("A/DCIM/100CANON");
    sprintf(fn, "A/DCIM/100CANON/CRW_%04d.JPG", cnt++);
    fd = open(fn, O_WRONLY|O_CREAT, 0777);
    if (fd) {
#ifdef CAMERA_ixus65_sd630    // Zero is not readable on ixus65!
        write(fd, (int*)0xFFFF0000, 4);
        write(fd, (int*)4, 0x1900-4);
#else
        write(fd, (void*)0, 0x1900);
#endif
        // TODO actual memory size is larger than 32 MB on many cameras!
        write(fd, (void*)0x1900, 32*1024*1024-0x1900);
        close(fd);
    }
    vid_bitmap_refresh();
    finished();
}

int core_get_free_memory() {
    int size, l_size, d;
    char* ptr;

    size = 16;
    while (1) {
        ptr= malloc(size);
        if (ptr) {
            free(ptr);
            size <<= 1;
        } else
            break;
    }

    l_size = size;
    size >>= 1;
    d=1024;
    while (d) {
        ptr = malloc(size);
        if (ptr) {
            free(ptr);
            d = l_size-size;
            if (d<0) d=-d;
            l_size = size;
            size += d>>1;
        } else {
            d = size-l_size;
            if (d<0) d=-d;
            l_size = size;
            size -= d>>1;
        }
        
    }
    return size-1;
}

static volatile long raw_data_available;

// called from another process
void core_rawdata_available() {
    raw_data_available = 1;
}

void core_spytask_can_start() {
    spytask_can_start = 1;
}

void core_spytask() {
    int cnt = 1;
    int i=0;

    raw_need_postprocess = 0;

    spytask_can_start=0;

#ifdef OPT_EXMEM_MALLOC
	exmem_malloc_init();
#endif

#ifdef CAM_CHDK_PTP
    init_chdk_ptp_task();
#endif

    //led_flash(LED_RED, 1);
    while((i++<400) && !spytask_can_start) msleep(10);
    //while((i++<100) && !spytask_can_start) msleep(10);
    //led_flash(LED_RED, 2);

    started();
    msleep(100);
    finished();
    drv_self_unhide();

    conf_restore();
    gui_init();

#if CAM_CONSOLE_LOG_ENABLED
    cam_console_init();
#endif

    mkdir("A/CHDK");
    mkdir("A/CHDK/FONTS");
    mkdir("A/CHDK/SYMBOLS");
    mkdir("A/CHDK/SCRIPTS");
    mkdir("A/CHDK/LANG");
    mkdir("A/CHDK/BOOKS");
    mkdir("A/CHDK/GRIDS");
#ifdef OPT_CURVES
    mkdir("A/CHDK/CURVES");
#endif
    mkdir("A/CHDK/DATA");
    mkdir("A/CHDK/LOGS");
#ifdef OPT_EDGEOVERLAY
    mkdir("A/CHDK/EDGE");
#endif
    auto_started = 0;

    if (conf.script_startup==1) script_autostart();    // remote autostart
    if (conf.script_startup==2) {
        conf.script_startup=0;
        conf_save();
        script_autostart();
    }

    while (1) {
        if (raw_data_available) {
            raw_need_postprocess = raw_savefile();
            hook_raw_save_complete();
            raw_data_available = 0;
            continue;
        }

        if (state_shooting_progress != SHOOTING_PROGRESS_PROCESSING) {
            if (((cnt++) & 3) == 0)
                gui_redraw();

            histogram_process();
#ifdef OPT_EDGEOVERLAY
            if(conf.edge_overlay_thresh && conf.edge_overlay_enable) edge_overlay();
#endif
        }

        if ((state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) && (!shooting_in_progress())) {
            state_shooting_progress = SHOOTING_PROGRESS_DONE;
            if (raw_need_postprocess) raw_postprocess();
        }

        msleep(20);
    }
}
