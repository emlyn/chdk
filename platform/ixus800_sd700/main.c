#include "../generic/main.c"

long get_vbatt_min()
{
    return 3500;
}

long get_vbatt_max()
{
    return 4100;
}

static const int fl_tbl[] = {5800, 6600, 7500, 8600, 10000, 11800, 14300, 18600, 23200};
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
    { MODE_M,                  32772 },
    { MODE_DIGITAL_MACRO,      33288 }, 
    { MODE_VIDEO_STD,          2593  },
    { MODE_STITCH,             33290 },
    { MODE_MY_COLORS,          16921 },
    { MODE_SCN_WATER,          16405 },
    { MODE_SCN_NIGHT,          16395 },
    { MODE_PORTRAIT,           16397 },
    { MODE_SCN_CHILD,          16399 },
    { MODE_SCN_PARTY,          16400 },
    { MODE_LANDSCAPE,          16401 },
    { MODE_SCN_SNOW,           16402 },
    { MODE_SCN_BEACH,          16403 },
    { MODE_SCN_FIREWORK,       16404 },
    { MODE_SCN_COLOR_ACCENT,   16920 }
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[2] & 0x00002000)?MODE_REC:MODE_PLAY;    
    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
