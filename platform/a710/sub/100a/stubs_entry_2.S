#include "stubs_asm.h"

NHSTUB(kbd_pwr_on, 0xFFC18800)
NHSTUB(kbd_pwr_off, 0xFFC18828)

NHSTUB(VbattGet, 0xFFC1C12C)
NHSTUB(GetZoomLensCurrentPosition, 0xFFE8F684)
NHSTUB(GetZoomLensCurrentPoint, 0xFFE8F670)
NHSTUB(GetFocusLensSubjectDistance, 0xFFEA2F3C)

NHSTUB(GetSystemTime, 0xFFC04D38)
NHSTUB(GetPropertyCase, 0xFFC14DEC)
NHSTUB(SetPropertyCase, 0xFFC14C9C)

NHSTUB(RefreshPhysicalScreen, 0xFFD8752C)

NHSTUB(IsStrobeChargeCompleted, 0xFFD11B24)

