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

    // sanity check (pointless with automemiso)
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
	started();
	shutdown();
    }

    // initialize .bss senment
    while (bss<&link_bss_end)
	*bss++ = 0;


    boot();
}

// TODO setting the DP button as a shortcut to movie in canon menu
// gives a value of (current mode)+1024 while movie is recording, unless
// already in movie mode
static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
    { MODE_AUTO,               32768 }, 
    { MODE_M,                  32769 },
    { MODE_P,                  32772 },
    { MODE_PORTRAIT,           16397 },
    { MODE_NIGHT_SNAPSHOT,     16395 },
    { MODE_SCN_KIDS_PETS,      16400 },
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_SUNSET,         16402 },
    { MODE_SCN_FOLIAGE,        16403 },
    { MODE_SCN_SNOW,           16404 },
    { MODE_SCN_BEACH,          16405 },
    { MODE_SCN_FIREWORK,       16406 },
    { MODE_SCN_UNDERWATER,     16407 },
    { MODE_SCN_AQUARIUM,       16408 },
    { MODE_SCN_ISO_3200,       16413 },
    { MODE_DIGITAL_MACRO,      33288 }, // SCN
    { MODE_SCN_COLOR_ACCENT,   16923 },
    { MODE_SCN_COLOR_SWAP,     16924 },
    { MODE_STITCH,             16906 }, // SCN, either direction
    { MODE_QUICK,              33312 },

    { MODE_VIDEO_STD,          2600  },
    { MODE_VIDEO_COLOR_ACCENT, 2598  },
    { MODE_VIDEO_COLOR_SWAP,   2599  },
};


#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

// from sd950, zoom steps and sensor size same
static const int fl_tbl[] = {7700, 9572, 11454, 13683, 16293, 19548, 23495, 28500};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
// sd950 uses wrong value
// #define CF_EFL 60869
// ewavr
// SD990 focal length range is 7,7 - 28,5 mm, 36 - 133 in 35-mm equivalent.
// So, CF_EFL = 36/7.7*10000=46753 or 133/28.5*10000=46666.
#define CF_EFL 46710 // split the difference

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

/*
physw_ bit OK
*/
int mode_get() {
    int mode, i, t=0xFF;
    mode  = (physw_status[0] & 0x00200000)?MODE_REC:MODE_PLAY;

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
    return 3425; // hnikesch on forum
}

long get_vbatt_max()
{
    return 4000; // fresh off charger slightly greater
}
