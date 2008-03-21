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
    { MODE_AUTO,               6  },
    { MODE_P,                  1  },
    { MODE_TV,                 3  },
    { MODE_AV,                 2  },
    { MODE_M,                  0  },
    { MODE_PORTRAIT,           9  },
    { MODE_NIGHT,              8  },
    { MODE_LANDSCAPE,          7  },
    { MODE_VIDEO_STD,          18 },
    { MODE_STITCH,             5  },
    { MODE_MY_COLORS,          4  },
    { MODE_SCN_WATER,          13 },
    { MODE_SCN_NIGHT,          15 },
    { MODE_SCN_CHILD,          16 },
    { MODE_SCN_PARTY,          14 },
    { MODE_SCN_GRASS,          10 },
    { MODE_SCN_SNOW,           11 },
    { MODE_SCN_BEACH,          12 },
    { MODE_SCN_FIREWORK,       17 }
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[1] & 0x00000400)?MODE_REC:MODE_PLAY;
  //  mode |= (physw_status[2] & 0x00008000)?0:MODE_SCREEN_OPENED;
  //  mode |= (physw_status[2] & 0x00004000)?0:MODE_SCREEN_ROTATED;
    
    _GetPropertyCase(0, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}

int is_mode_photo(){ //from 710 added
 int m=mode_get();
 return ((m&MODE_MASK) == MODE_REC )&&
                 !((m&MODE_SHOOTING_MASK)==MODE_VIDEO_STD || (m&MODE_SHOOTING_MASK)==MODE_VIDEO_SPEED || (m&MODE_SHOOTING_MASK)==MODE_VIDEO_COMPACT ||
                   (m&MODE_SHOOTING_MASK)==MODE_VIDEO_MY_COLORS || (m&MODE_SHOOTING_MASK)==MODE_VIDEO_COLOR_ACCENT);
 }
