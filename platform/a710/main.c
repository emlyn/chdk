#include "../generic/main.c"

long get_vbatt_min()
{
    return 2300;
}

long get_vbatt_max()
{
    return 2550;
}

static const int fl_tbl[] = {5800, 6420, 7060, 7700, 8340, 9950, 11550, 13160, 14750, 17150, 19570, 22760, 26750, 30750, 34800};
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
    { MODE_AUTO,               32768 },
    { MODE_P,                  32772 },
    { MODE_TV,                 32771 },
    { MODE_AV,                 32770 },
    { MODE_M,                  32769 },
    { MODE_PORTRAIT,           32781 },
    { MODE_NIGHT,              32782 },
    { MODE_LANDSCAPE,          32780 },
    { MODE_VIDEO_STD,          2596  },
    { MODE_VIDEO_SPEED,        2597  },
    { MODE_VIDEO_COMPACT,      2598  },
    { MODE_VIDEO_MY_COLORS,    2595  },
    { MODE_VIDEO_COLOR_ACCENT, 2594  },
    { MODE_STITCH,             33290 },
    { MODE_MY_COLORS,          16922 },
    { MODE_SCN_WATER,          16405 },
    { MODE_SCN_NIGHT,          16395 },
    { MODE_SCN_CHILD,          16399 },
    { MODE_SCN_PARTY,          16400 },
    { MODE_SCN_GRASS,          16401 },
    { MODE_SCN_SNOW,           16402 },
    { MODE_SCN_BEACH,          16403 },
    { MODE_SCN_FIREWORK,       16404 },
    { MODE_SCN_COLOR_ACCENT,   16921 }
}; 
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[2] & 0x00002000)?MODE_REC:MODE_PLAY;
    mode |= (physw_status[2] & 0x00008000)?0:MODE_SCREEN_OPENED;
    mode |= (physw_status[2] & 0x00004000)?0:MODE_SCREEN_ROTATED;
    
    _GetPropertyCase(0, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
