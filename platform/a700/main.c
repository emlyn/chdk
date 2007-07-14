#define VBATT_DEFAULT_MIN (2550)
#define VBATT_DEFAULT_MAX (2300)

#include "../generic/main.c"

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

long shooting_get_current_mode() {
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
