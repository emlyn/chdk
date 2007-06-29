#define VBATT_DEFAULT_MIN (4550)
#define VBATT_DEFAULT_MAX (5150)

#include "../generic/main.c"

static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
    { MODE_AUTO,                32768 },
    { MODE_P,                   32772 },
    { MODE_TV,                  32771 },
    { MODE_AV,                  32770 },
    { MODE_M,                   32769 },
    { MODE_PORTRAIT,            32781 },
    { MODE_NIGHT,               32782 },
    { MODE_LANDSCAPE,           32780 },
    { MODE_VIDEO_STD,            2590 },
    { MODE_STITCH,              33290 },
    { MODE_MY_COLORS,           16921 },
    { MODE_SCN_NIGHT,           16395 },
    { MODE_SCN_CHILD,           32775 },
    { MODE_SCN_PARTY,           16400 },
    { MODE_SCN_GRASS,           16401 },
    { MODE_SCN_SNOW,            16402 },
    { MODE_SCN_BEACH,           16403 },
    { MODE_SCN_FIREWORK,        16404 }, 
    { MODE_SCN_COLOR_ACCENT,    16920 } 
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

long shooting_get_current_mode() {
    int mode, i, t=0xFF;

    _GetPropertyCase(204, &t, 4);
    mode  = (t==4)?MODE_REC:MODE_PLAY;
    mode |= (physw_status[1] & 0x00000001)?0:MODE_SCREEN_OPENED;
    mode |= (physw_status[1] & 0x00000002)?0:MODE_SCREEN_ROTATED;
    
    t=0xFF;
    _GetPropertyCase(0, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
