#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"


extern long link_bss_start;
extern long link_bss_end;
extern void boot();


void startup()
{
	long *bss = &link_bss_start;
	long *ptr;
	
	// sanity check
	if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
		started();
		shutdown();
	}

	// initialize .bss senment
	while (bss<&link_bss_end)
		*bss++ = 0;

	boot();
}


static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
	{ MODE_AUTO,               32768  },
	{ MODE_P,                  32772  },
	{ MODE_TV,                 32771  },
	{ MODE_AV,                 32770  },
	{ MODE_M,                  32769  },
	{ MODE_EASY,               33311  },
	{ MODE_PORTRAIT,           32781  },
	{ MODE_NIGHT_SNAPSHOT,     32779  }, 
	{ MODE_LANDSCAPE,          32780  },
	{ MODE_VIDEO_COLOR_ACCENT ,3599   },
	{ MODE_VIDEO_COLOR_SWAP,   3600   },
	{ MODE_VIDEO_STD,          2601   },
	{ MODE_KIDS_PETS,          32784  },
	{ MODE_INDOOR,             32785  },

	{ MODE_SCN_SUNSET,         16402  },
	{ MODE_SCN_NIGHT,          16398  },
	{ MODE_SCN_FIREWORK,       16406  },
	{ MODE_SCN_BEACH,          16405  },
	{ MODE_SCN_AQUARIUM,       16408  },
	{ MODE_SCN_FOLIAGE,        16403  },
	{ MODE_SCN_SNOW,           16404  },
	{ MODE_SCN_ISO_3200,       16413  },
	{ MODE_SCN_COLOR_ACCENT,   16923  },
	{ MODE_SCN_COLOR_SWAP,     16924  },
	{ MODE_SCN_STITCH,         16906  }

};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

static const int fl_tbl[] = {5000, 6100, 13100, 17500, 23500, 33800, 52300, 60000};

#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))

// Focal length range is 5.0 - 60,0 mm, 27.3 - 327.4 in 35-mm equivalent.
// So, CF_EFL = 27.3/5.0*10000=54600 or327.4/60*10000=54566.6
// diff = 54600 - 54566.6 = 33.3, split it 33.3 / 2 = 16.6
// add to base 54566.6 + 16.6 = 54583.2
#define CF_EFL  54583

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

int mode_get() {
    int mode, i, t=0xFF;
    mode  = (playrec_mode==2 || playrec_mode==5)?MODE_REC:MODE_PLAY;

    _GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}

long get_vbatt_min()
{
	return 3280;  // min observed was 3.408, then it died
}

long get_vbatt_max()
{
	return 4057;  // fresh from change (actual was 4.127)
}

