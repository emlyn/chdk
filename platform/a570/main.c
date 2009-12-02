#include "../generic/main.c"

long get_vbatt_min()
{
    return 2250;
}

long get_vbatt_max()
{
    return 2550;
}

// aperture 2.6 2.8 3.2 3.5 4.0 4.5 5.0 5.5 
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

#if 0
int rec_switch_state(void) {
//    mode  = (physw_status[1] & 0x02000000)?MODE_REC:MODE_PLAY;
	return (physw_status[1] & 0x02000000);
}
#endif
