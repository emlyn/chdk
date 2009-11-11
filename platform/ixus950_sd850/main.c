#include "../generic/main.c"

long get_vbatt_min()
{
    return 3500;
}

long get_vbatt_max()
{
    return 4100;
}

//ixus800_sd700
//static const int fl_tbl[] = {5800, 6600, 7500, 8600, 10000, 11800, 14300, 18600, 23200};
//ixus950_sd850 (from EXIF), basically the same as in ixus800_sd700 (4x zoom lens)
  static const int fl_tbl[] = {5800, 6630, 7470, 8640, 9970,  11820, 14330, 18630, 23200};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 60345 // 60345 for 1/2.5" sensor, 47946 for 1/1.8" sensor

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
} modemap[] = { // PROPCACE 49
    { MODE_AUTO,               32768 },
//    { MODE_M,                  32772 }, // real manual mode absent here...
    { MODE_P,                  32772 },
    { MODE_DIGITAL_MACRO,      33288 },
    { MODE_PORTRAIT,           16397 }, // in this cam, it is scene->"portrait"
    { MODE_COLOR_ACCENT,       33306 },
    { MODE_MY_COLORS,          33307 }, // "color swap"
    { MODE_SCN_NIGHT,          16395 },
    { MODE_SCN_KIDS_PETS,      16400 },
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_FOLIAGE,        16402 },
    { MODE_SCN_SNOW,           16403 },
    { MODE_SCN_BEACH,          16404 },
    { MODE_SCN_FIREWORK,       16405 },
    { MODE_SCN_AQUARIUM,       16407 },
    { MODE_SCN_WATER,          16406 },
// scene "creative effects",  16911
    { MODE_VIDEO_STD,          2597  },
    { MODE_VIDEO_SPEED,        2598  }, // "fast frame rate"
    { MODE_VIDEO_COMPACT,      2599  },
    { MODE_VIDEO_COLOR_ACCENT, 2595  },
    { MODE_VIDEO_MY_COLORS,    2596  }, // "color swap"
    { MODE_VIDEO_TIME_LAPSE,   2601  },
    { MODE_STITCH,             33290 },

};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

// play/rec without override
//    mode  = (physw_status[2] & 0x1000)?MODE_REC:MODE_PLAY;    

    mode = (playrec_mode==2 || playrec_mode==4 || playrec_mode==5)?MODE_REC:MODE_PLAY;

    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
