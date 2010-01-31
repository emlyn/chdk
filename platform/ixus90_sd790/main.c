#include "camera.h"
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "stdlib.h"

extern long link_bss_start;
extern long link_bss_end;
extern void boot();


void startup()
{
    long *bss = &link_bss_start;

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

// Ixus 90 focal length range is 6.2 - 18.6 mm, 35-105 in 35-mm equivalent.
// So, CF_EFL = 35/6.2*10000=56452 or 105/18.6*10000=56452.
static const int fl_tbl[] = {6200, 7230, 8295, 9681, 11614, 14303, 18600};
#define CF_EFL 56452
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))

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


long get_vbatt_min()
{
    return 3500;
}

long get_vbatt_max()
{
    return 4100;
}

