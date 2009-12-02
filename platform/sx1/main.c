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

int screen_opened(void) {
//	mode |= (physw_status[1] & 0x01000000)?0:MODE_SCREEN_OPENED;
	return !(physw_status[1] & 0x01000000);
}

int screen_rotated(void) {
//	mode |= (physw_status[1] & 0x00080000)?0:MODE_SCREEN_ROTATED;
	return !(physw_status[1] & 0x00080000);
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

