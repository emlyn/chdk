#include "stubs_asm.h"

NSTUB(kbd_pwr_on, 0xFFC18800)
NSTUB(kbd_pwr_off, 0xFFC18828)

NSTUB(VbattGet, 0xFFC1C12C)
NSTUB(GetZoomLensCurrentPosition, 0xFFE8F684)
NSTUB(GetZoomLensCurrentPoint, 0xFFE8F670)
NSTUB(GetFocusLensSubjectDistance, 0xFFEA2F3C)

NSTUB(GetSystemTime, 0xFFC04D38)
NSTUB(GetPropertyCase, 0xFFC14DEC)
NSTUB(SetPropertyCase, 0xFFC14C9C)
