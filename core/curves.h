#ifndef CURVES_H
#define CURVES_H

#define CURVE_DIR "A/CHDK/CURVES"
#define CURVE_SIZE 1024

//-------------------------------------------------------------------
extern unsigned short curve[][];

//-------------------------------------------------------------------
extern void curve_load();
extern void curve_apply();
// extern void default_curve(int n);
//-------------------------------------------------------------------

#endif
