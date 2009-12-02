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
//	mode |= (physw_status[1] & 0x00000100)?0:MODE_SCREEN_OPENED;
	return !(physw_status[1] & 0x00000100);
}

int screen_rotated(void) {
//	mode |= (physw_status[1] & 0x00000200)?0:MODE_SCREEN_ROTATED;
	return !(physw_status[1] & 0x00000200);
}

#if 0
int rec_switch_state(void) {
// not sure what this was checking
//	volatile int *physw_mmio = (int *) 0xC0220200; // I don't know where else I can find this...
//	mode  = (physw_mmio[1] & 0x00010000)?MODE_REC:MODE_PLAY;
}
#endif

static const struct {
	int zp, fl;
} fl_tbl[] = {
	{   0,   6000 },
	{  11,   6400 },
	{  41,  12100 },
	{  64,  21300 },
	{  86,  41600 },
	{ 105,  61400 },
	{ 128,  72000 },
};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 6000

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
	return 4700;
}

long get_vbatt_max()
{
	return 5500;
}

