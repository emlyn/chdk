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
	return !(physw_status[1] & 0x02000000);
}

int screen_rotated(void) {
//	mode |= (physw_status[1] & 0x00080000)?0:MODE_SCREEN_ROTATED;
	return !(physw_status[1] & 0x00800000);
}

// Focus length table in firmware @ FFFEA5CC
#define NUM_FL 201		// 0 - 200, entries in firmware
extern int focus_len_table[NUM_FL];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 4.3       24       (24/4.3) * 43 = 240  (min FL)
// 150.5     840      (840/150.5) * 43 = 240  (max FL)
#define CF_EFL 240
#define CF_EFL_DIV 43

const int zoom_points = 201;

int get_effective_focal_length(int zp) {
	return (CF_EFL*get_focal_length(zp))/CF_EFL_DIV;
}

int get_focal_length(int zp) {
	if (zp < 0) zp = 0;
	else if (zp >= NUM_FL) zp = NUM_FL-1;
	return focus_len_table[zp];
}

int get_zoom_x(int zp) {
	return get_focal_length(zp)*10/focus_len_table[0];
}

// TODO
long get_vbatt_min()
{
	return 6500;	// from condor
}

// TODO
long get_vbatt_max()
{
	return 8100;	// from condor
}

