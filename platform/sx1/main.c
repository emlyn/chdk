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
	{ MODE_PORTRAIT,           32781  },
	{ MODE_NIGHT_SNAPSHOT,     32779  }, 
	{ MODE_LANDSCAPE,          32780  },
	{ MODE_VIDEO_STD,          2597   }, // video standby
	{ MODE_VIDEO_STD,          3622   }, // video in progress
	{ MODE_STITCH,             33290  },
	{ MODE_SPORTS,             33287  },

	{ MODE_SCN_NIGHT,          16398  },
	{ MODE_SCN_INDOOR,         16401  },
	{ MODE_SCN_SUNSET,         16402  },
	{ MODE_SCN_FOLIAGE,        16403  },
	{ MODE_SCN_SNOW,           16404  },
	{ MODE_SCN_BEACH,          16405  },
	{ MODE_SCN_FIREWORK,       16406  },
	{ MODE_SCN_AQUARIUM,       16408  },
	{ MODE_SCN_ISO_3200,       16413  },
	{ MODE_SCN_COLOR_ACCENT,   16923  },
        { MODE_SCN_COLOR_SWAP,     16924  }
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
	int mode, i, t=0xFF;
	
	mode  = (playrec_mode==2 || playrec_mode==4 || playrec_mode==5)?MODE_REC:MODE_PLAY;
	mode |= (physw_status[1] & 0x01000000)?0:MODE_SCREEN_OPENED;
	mode |= (physw_status[1] & 0x00080000)?0:MODE_SCREEN_ROTATED;
	
	_GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
	for (i=0; i<MODESCNT; ++i) {
		if (modemap[i].canonmode == t) {
			return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
		}
	}
	return (mode);
}

static const struct {
	int zp, fl;
} fl_tbl[] = {
	{   0,   5000 },
	{  11,   6190 },
	{  41,  12610 },
	{  64,  25240 },
	{  86,  45470 },
	{ 105,  65880 },
	{ 128, 100000 },
};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 5600

const int zoom_points = 129;

int get_effective_focal_length(int zp) {
	return (CF_EFL*get_focal_length(zp))/1000;
}

int get_focal_length(int zp) {
	int i;

	if (zp<fl_tbl[0].zp)
		return fl_tbl[0].fl;
	else if (zp>fl_tbl[NUM_FL-1].zp)
		return fl_tbl[NUM_FL-1].fl;
	else 
		for (i=1; i<NUM_FL; ++i) {
			if (zp==fl_tbl[i-1].zp) 
				return fl_tbl[i-1].fl;
			else if (zp==fl_tbl[i].zp) 
				return fl_tbl[i].fl;
			else if (zp<fl_tbl[i].zp)
				return fl_tbl[i-1].fl+(zp-fl_tbl[i-1].zp)*(fl_tbl[i].fl-fl_tbl[i-1].fl)/(fl_tbl[i].zp-fl_tbl[i-1].zp);
		}
	return fl_tbl[NUM_FL-1].fl;
}

int get_zoom_x(int zp) {
	return get_focal_length(zp)*10/fl_tbl[0].fl;
}

long get_vbatt_min()
{
	return 4550;
}

long get_vbatt_max()
{
	return 5150;
}

