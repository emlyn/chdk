
#include "../generic/main.c"

void movie_record_task()
{
}

long get_vbatt_min()
{
    return 3550;
}

long get_vbatt_max()
{
    return 4110;
}

static const int fl_tbl[] = {5800, 7109, 8462, 10093, 12120, 14421, 17400};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 60345

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
    { MODE_P,                  32772 }, // note, this is called Manual, but eqivalent to P on cameras with real manual
    { MODE_AUTO,               32768 },
    { MODE_DIGITAL_MACRO,      33288 },
    { MODE_PORTRAIT,           32781 },
    { MODE_NIGHT_SNAPSHOT,     32779 }, // "night scene" on dial, different from "night snapshot" under "scene" below
    { MODE_SCN_COLOR_ACCENT,   16920 }, // "color accent"
    { MODE_SCN_COLOR_SWAP,     16921 }, // "color swap"
    { MODE_SCN_KIDS_PETS,      16399 }, // "kids and pets"
    { MODE_SCN_INDOOR,         16400 }, // "indoor"
    { MODE_SCN_FOLIAGE,        16401 }, // "foliage"
    { MODE_SCN_SNOW,           16402 }, // "snow"
    { MODE_SCN_BEACH,          16403 }, // "beach"
    { MODE_STITCH,             33290 },
    { MODE_SCN_FIREWORK,       16404 }, // "fireworks"
    { MODE_SCN_UNDERWATER,     16405 }, // "under water"
    { MODE_VIDEO_STD,          2593  },
    { MODE_VIDEO_SPEED,        2594  }, // "fast frame rate"
    { MODE_VIDEO_COMPACT,      2595  }, // "compact"
    { MODE_VIDEO_COLOR_ACCENT, 2591  }, // "color accent"
    { MODE_VIDEO_COLOR_SWAP,   2592  }, // "color swap"
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

/*
   9xxxx - view
   3xxxx - video
   bxxxx - photo
*/


int mode_get() {
    int mode, i, t=0xFF;

// play/rec without override
//    mode  = (physw_status[2] & 0x00002000)?MODE_REC:MODE_PLAY;
    
    mode = (playrec_mode==2 || playrec_mode==4 || playrec_mode==5)?MODE_REC:MODE_PLAY;

    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
