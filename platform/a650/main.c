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


static const int fl_tbl[] = {7400, 8210, 9040, 9860, 10670, 12730, 14780, 16820, 18890, 21970, 25030, 29170, 36780, 44400};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 47297

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

// play/rec without override
//    mode  = (physw_status[1] & 0x02000000)?MODE_PLAY:MODE_REC;

    mode = (playrec_mode==2 || playrec_mode==4 || playrec_mode==5)?MODE_REC:MODE_PLAY;

    mode |= (physw_status[0] & 0x04000000)?0:MODE_SCREEN_OPENED;
    mode |= (physw_status[0] & 0x08000000)?0:MODE_SCREEN_ROTATED;

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
    return 4550;
}

long get_vbatt_max()
{
    return 5150;
}
