#include "fdlibm.h"

#ifndef __VFP_FP__
#define USE_ASM_D2D

double d2d(double value) {
#ifndef USE_ASM_D2D
    unsigned int h, l;

    EXTRACT_WORDS(h, l, value);
    INSERT_WORDS(value, l, h);
#else
    asm volatile (
         "EOR     %Q0, %R0\n"
         "EOR     %R0, %Q0\n"
         "EOR     %Q0, %R0\n"
         :"=r" (value)
         :"0" (value)
         );
#endif
    return value;
}
#endif

