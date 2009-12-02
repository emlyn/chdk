//A540 + A560

#include "../generic/main.c"

long get_vbatt_min()
{
	return 2100;
}

long get_vbatt_max()
{
	return 2800;
}

static const int fl_tbl[] =
{ 5800, 6600, 7900, 9900, 12700, 16000, 19600, 23200 };
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 60345

const int zoom_points= NUM_FL;

int get_effective_focal_length(int zp)
{
	return (CF_EFL*get_focal_length(zp))/10000;
}

int get_focal_length(int zp)
{
	if (zp<0)
		return fl_tbl[0];
	else if (zp>NUM_FL-1)
		return fl_tbl[NUM_FL-1];
	else
		return fl_tbl[zp];
}

int get_zoom_x(int zp)
{
	if (zp<1)
		return 10;
	else if (zp>NUM_FL-1)
		return fl_tbl[NUM_FL-1]*10/fl_tbl[0];
	else
		return fl_tbl[zp]*10/fl_tbl[0];
}

#if 0
int rec_switch_state(void) {
//	mode = (physw_status[1] & 0x00000040) ? MODE_REC : MODE_PLAY; //eb5ccdc0 ( 110111000000 ):eb5cc980 ( 100110000000 )
	return (physw_status[1] & 0x00000040);
}
#endif
