#ifndef CURVES_H
#define CURVES_H

#define CURVE_DIR "A/CHDK/CURVES"
#define CURVE_SIZE 1024
#define DRCURVE_CNT 4


//-------------------------------------------------------------------
extern unsigned char curve_loaded;
extern unsigned char drcurve_loaded;
extern void curve_load();
extern void drcurve_load(const char *fn);
extern void curve_apply();
extern unsigned short drcurve0[][];
// extern void default_curve(int n);
//-------------------------------------------------------------------

#endif
