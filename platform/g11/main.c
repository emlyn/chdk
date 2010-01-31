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

//zoom position is get_parameter_data(87)
static const struct {
	int zp, fl;
} fl_tbl[] = {
  {   0,   6100},
  {   1,   6800},
  {   2,   7400},
  {   3,   8100},
  {   4,   8900},
  {   5,   9800},
  {   6,   10800},
  {   7,   12100},
  {   8,   13800},
  {   9,   15700},
  {  10,   18100},
  {  11,   21500},
  {  12,   25000},
  {  13,   30500},
};

#define NUM_FL (sizeof(fl_tbl)/sizeof(fl_tbl[0]))
// G11 focal lenght range 6.1 - 30.5 mm (35 mm equivalent: 27.8 - 139.1 mm)(1/1.7" Type CCD, Scale Factor To 35 mm Equivalent: 4.6)
// 27,8/6,1*10000=45574
// 139,1/30,5*10000=45607
#define CF_EFL 45574

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/10000;
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
    return 6600; /* G11 shuts down after reaching 6,6V*/
}

long get_vbatt_max()
{
    return 8100;
}

