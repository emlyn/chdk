#include "../generic/main.c"

long get_vbatt_min()
{
    return 2100;
}

long get_vbatt_max()
{
    return 2800;
}



static const int fl_tbl[] = {5800, 6600, 7900, 9900, 12700, 16000, 19600, 23200};
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
    { MODE_M,                  32769 },
    { MODE_AV,                 32770 },
    { MODE_TV,                 32771 },
    { MODE_P,                  32772 },
    { MODE_AUTO,               32768 },
    { MODE_PORTRAIT,           32781 },
    { MODE_LANDSCAPE,          32780 },
    { MODE_NIGHT,              32782 }, // "night scene" on dial, different from "night snapshot" under "scene" below
    { MODE_STITCH,             33290 },
    { MODE_SCN_NIGHT,          16395 }, // "night snapshot"
    { MODE_SCN_KIDS_PETS,      16399 }, // "kids and pets"
    { MODE_SCN_INDOOR,         16400 }, // "indoor"
    { MODE_SCN_FOLIAGE,        16401 }, // "foliage"
    { MODE_SCN_SNOW,           16402 }, // "snow"
    { MODE_SCN_BEACH,          16403 }, // "beach"
    { MODE_SCN_FIREWORK,       16404 }, // "fireworks"
    { MODE_SCN_WATER,          16405 }, // "under water" (should this be AQUARIUM ?)
    { MODE_SCN_COLOR_ACCENT,   16920 }, // "color accent"
    { MODE_SCN_COLOR_SWAP,     16921 }, // "color swap"
    { MODE_VIDEO_STD,          2593  },
    { MODE_VIDEO_SPEED,        2594  }, // "fast frame rate"
    { MODE_VIDEO_COMPACT,      2595  }, // "compact"
    { MODE_VIDEO_COLOR_ACCENT, 2591  }, // "color accent"
    { MODE_VIDEO_COLOR_SWAP,   2592  }, // "color swap"
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[1] & 0x00000400)?MODE_REC:MODE_PLAY;
  //  mode |= (physw_status[2] & 0x00008000)?0:MODE_SCREEN_OPENED;
  //  mode |= (physw_status[2] & 0x00004000)?0:MODE_SCREEN_ROTATED;
    
    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
/* // seems to be added from ewavr's svn; although not yet used, might become useful...
int is_mode_photo(){ //from 710 added
 int m=mode_get();
 return ((m&MODE_MASK) == MODE_REC )&&
                 !((m&MODE_SHOOTING_MASK)==MODE_VIDEO_STD || (m&MODE_SHOOTING_MASK)==MODE_VIDEO_SPEED || (m&MODE_SHOOTING_MASK)==MODE_VIDEO_COMPACT ||
                   (m&MODE_SHOOTING_MASK)==MODE_VIDEO_MY_COLORS || (m&MODE_SHOOTING_MASK)==MODE_VIDEO_COLOR_ACCENT);
 }
*/