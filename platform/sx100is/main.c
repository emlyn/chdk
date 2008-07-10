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

	debug_led(1);
    boot();
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
    { MODE_VIDEO_STD,          2597  },
    { MODE_VIDEO_COMPACT,      2599  },
    { MODE_STITCH,             33290 },
    { MODE_SCN_WATER,          16406 },  
    { MODE_SCN_AQUARIUM,       16407 },  
    { MODE_SCN_NIGHT,          16398 },  
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_GRASS,          16402 },   
    { MODE_SCN_SNOW,           16403 },  
    { MODE_SCN_BEACH,          16404 },  
    { MODE_SCN_FIREWORK,       16405 },  
    { MODE_INDOOR,             32785 },
    { MODE_KIDS_PETS,          32784 },	
    { MODE_NIGHT_SNAPSHOT,     32779 },
    { MODE_LANDSCAPE,          32780 },	
    { MODE_PORTRAIT,           32781 },
}; 


#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))


static const int fl_tbl[] = {6000, 6700, 7300, 8200, 9100, 10300, 11500, 12800, 14400, 16100, 18100, 20100, 22400, 25200, 28100, 31500, 34900, 38900, 42500, 46600, 51100, 55900, 60000};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 6000

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
    return 2300;
}

long get_vbatt_max()
{
    return 2550;
}
