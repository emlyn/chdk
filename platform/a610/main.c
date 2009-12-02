#include "../generic/main.c"

long get_vbatt_min()
{
    return 4550;
}

long get_vbatt_max()
{
    return 5150;
}

static const int fl_tbl[] = {7300, 8460, 9565, 10835, 12565, 14926, 17342, 21709, 29200};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 47946

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
//    mode  = (physw_status[2] & 0x00002000)?MODE_REC:MODE_PLAY;
	return (physw_status[2] & 0x00002000);
}
#endif

int screen_opened(void) {
//    mode |= (physw_status[2] & 0x00008000)?0:MODE_SCREEN_OPENED;
	return !(physw_status[2] & 0x00008000);
}

int screen_rotated(void) {
//    mode |= (physw_status[2] & 0x00004000)?0:MODE_SCREEN_ROTATED;
	return !(physw_status[2] & 0x00004000);
}

