#include "../generic/main.c"

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
    { MODE_P,                   0 },
    { MODE_DIGITAL_MACRO,       2 },
    { MODE_MY_COLORS,           3 },
    { MODE_STITCH,              4 }, 
    { MODE_AUTO,                5 },
    { MODE_PORTRAIT,            6 },
    { MODE_SCN_SNOW,            8 },
    { MODE_SCN_NIGHT,          12 },
    { MODE_VIDEO_STD,          15 }
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

/*
   9xxxx - view
   3xxxx - video
   bxxxx - photo
*/


int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[1] & 0x2)?MODE_REC:MODE_PLAY; 
    _GetPropertyCase(0, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
