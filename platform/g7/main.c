#include "../generic/main.c"

long get_vbatt_min()
{
    return 7000;
}

long get_vbatt_max()
{
    return 8300;
}

static const int fl_tbl[] = {7400, 8210, 9040, 9860, 10670, 12730, 14780, 16820, 18890, 21970, 25030, 29170, 36780, 44400};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 47946

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
    { MODE_AUTO,               32768 },
    { MODE_P,                  32772 },
    { MODE_TV,                 32771 },
    { MODE_AV,                 32770 },
    { MODE_M,                  32769 },
    { MODE_VIDEO_STD,          2596  },
    { MODE_VIDEO_HIRES,        2599  },
    { MODE_VIDEO_COMPACT,      2598  },
    { MODE_VIDEO_MY_COLORS,    2595  },
    { MODE_VIDEO_COLOR_ACCENT, 2594  },
    { MODE_STITCH,             33290 },
    { MODE_MY_COLORS,      16922 },
    { MODE_SCN_WATER,          16405 },
    { MODE_SCN_AQUARIUM,       16406 },
    { MODE_SCN_NIGHT,          16395 },
    { MODE_SCN_NIGHT1,         16398 },
    { MODE_SCN_CHILD,          16399 },
    { MODE_SCN_PARTY,          16400 },
    { MODE_SCN_GRASS,          16401 },
    { MODE_SCN_SNOW,           16402 },
    { MODE_SCN_BEACH,          16403 },
    { MODE_SCN_FIREWORK,       16404 },
    { MODE_SCN_ISO_3200,       16411 },
    { MODE_PORTRAIT,           16397 },
    { MODE_LANDSCAPE,          16396 },
    { MODE_SCN_SPORT,          16903 },
    { MODE_SCN_COLOR_ACCENT,   16921 }
}; 

#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (playrec_mode==2)?MODE_REC:MODE_PLAY;
    
    _GetPropertyCase(0, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
