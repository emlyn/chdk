#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
extern long link_bss_start;
extern long link_bss_end;
extern void boot();
long get_sensor_width()
{
return 5760;
}
void startup()
{
long *bss = &link_bss_start;
long *ptr;
 
if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
started();
shutdown();
}
 
while (bss<&link_bss_end)
*bss++ = 0;
boot();
}


static const int fl_tbl[] = {7700, 9572, 11454, 13683, 16293, 19548, 23495, 28500};
#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
#define CF_EFL 60869
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
// both were in the original mode_get() function, status unknown
//	mode  = (physw_status[1] & 0x08000000)?MODE_PLAY:MODE_REC;
//	mode  = (physw_status[0] & 0x00000040)?MODE_REC:MODE_PLAY;
	return (physw_status[0] & 0x00000040);
}
#endif

long get_vbatt_min()
{
return 3500;
}
long get_vbatt_max()
{
return 4100;
}
