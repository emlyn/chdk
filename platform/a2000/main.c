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

//debug_led(1);
    boot();
}

static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
  { MODE_VIDEO_STD,          2600  },  //Verified ok
  { MODE_VIDEO_COMPACT,      2602  },  //Verified
  { MODE_SCN_AQUARIUM,       16408 },  //Verified
  { MODE_SCN_SNOW,           16404 },  //Verified
  { MODE_SCN_FOLIAGE,        16403 },  //verified
  { MODE_SCN_SUNSET,         16402 },  //verified
  { MODE_SCN_NIGHT,          16398 },  //verified ok
  { MODE_SCN_ISO_3200,       16413 },  //verified
  { MODE_SCN_FIREWORK,       16406 },  //verified
  { MODE_SCN_BEACH,          16405 },  //verified
  { MODE_INDOOR,             32785 },  //verified ok
  { MODE_KIDS_PETS,          32784 },  //verified ok
  { MODE_NIGHT_SNAPSHOT,     32779 },  //verified ok
  { MODE_LANDSCAPE,          32780 },  //verified ok
  { MODE_PORTRAIT,           32781 },  //verified ok
  { MODE_AUTO,               32768 },  //verified ok
  { MODE_P,                  32772 },  //verified ok
  { MODE_TV,                 32771 },  //verified
  { MODE_AV,                 32770 },  //verified
  { MODE_M,                  32769 },  //verified
  { MODE_EASY,               33311 }   //verified ok
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
	int mode, i, t=0xFF;
	
	mode  = (playrec_mode==2 || playrec_mode==4 || playrec_mode==5)?MODE_REC:MODE_PLAY;
	
	_GetPropertyCase(PROPCASE_SHOOTING_MODE, &t, 4);
	for (i=0; i<MODESCNT; ++i) {
		if (modemap[i].canonmode == t) {
			return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
		}
	}
	return (mode);
}


static const int fl_tbl[] = {6400, 6800, 7600, 8800, 10500, 12300, 14100, 16100, 18500, 21200, 24000, 27100, 30700, 35100, 38400};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))

// focal length range is 6.4 - 38.4 mm, 36 - 216 in 35-mm equivalent.
// So, CF_EFL = 36/6.4 * 1000 = 56250 or 216/38.4 * 1000 = 56250.
#define CF_EFL 5625

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
	return (CF_EFL*get_focal_length(zp))/1000;
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


long get_vbatt_min()
{
    return 2300;
}

long get_vbatt_max()
{
    return 2550;
}
