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

static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
    { MODE_AUTO,               32768 }, // PROPCACE 49
    { MODE_P,                  32772 },
    { MODE_DIGITAL_MACRO,      33288 },
    { MODE_PORTRAIT,           16397 },
    { MODE_NIGHT_SNAPSHOT,     16395 },
    { MODE_COLOR_ACCENT,       33306 }, //  { MODE_SCN_COLOR_ACCENT,   33306 },
    { MODE_MY_COLORS,          33307 },
    { MODE_SCN_KIDS_PETS,      16400 }, //  { MODE_SCN_CHILD,          16400 },
    { MODE_SCN_INDOOR,         16401 }, //  { MODE_SCN_PARTY,          16401 },
    { MODE_SCN_FOLIAGE,        16402 }, //  { MODE_SCN_GRASS,          16402 },
    { MODE_SCN_SNOW,           16403 },
    { MODE_SCN_BEACH,          16404 },
    { MODE_SCN_FIREWORK,       16405 },
    { MODE_SCN_AQUARIUM,       16407 },
    { MODE_SCN_WATER,          16406 },
    { MODE_VIDEO_STD,          2597  },
//    { MODE_VIDEO_SPEED,        2598  },
    { MODE_VIDEO_COMPACT,      2599  },
    { MODE_VIDEO_COLOR_ACCENT, 2595  },
    { MODE_VIDEO_MY_COLORS,    2596  },
    { MODE_VIDEO_TIME_LAPSE,   2601  },
    { MODE_STITCH,             33290 },
}; 


#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))


static const int fl_tbl[] = {4600, 6140, 7560, 9110, 10830, 12670, 14690, 17300};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 60869

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


int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[1] & 0x08000000)?MODE_PLAY:MODE_REC;
    
    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}

long get_vbatt_min()
{
    return 3500;
}

long get_vbatt_max()
{
    return 4100;
}

void change_video_tables(int a, int b){

}
