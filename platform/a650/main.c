#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"


extern long link_bss_start;
extern long link_bss_end;
extern void boot();


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


    boot();
}


static const int fl_tbl[] = {7400, 8210, 9040, 9860, 10670, 12730, 14780, 16820, 18890, 21970, 25030, 29170, 36780, 44400};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 47297

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

int screen_opened(void) {
	return !(physw_status[0] & 0x04000000);
}

int screen_rotated(void) {
	return !(physw_status[0] & 0x08000000);
}

#if 0
int rec_switch_state(void) {
//    mode  = (physw_status[1] & 0x02000000)?MODE_PLAY:MODE_REC;
	return !(physw_status[1] & 0x02000000);
}
#endif

long get_vbatt_min()
{
    return 4550;
}

long get_vbatt_max()
{
    return 5150;
}
