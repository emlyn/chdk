#include "stubs_asm.h"

NHSTUB(VbattGet, 0xFFC1B990)
NHSTUB(GetZoomLensCurrentPosition, 0xFFE7F694)
NHSTUB(GetZoomLensCurrentPoint, 0xFFE7F680)
NHSTUB(GetFocusLensSubjectDistance, 0xFFE92C14)

NHSTUB(malloc, 0xFFEE84BC)
NHSTUB(free, 0xFFEE84C8)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC22854)  //null stub

NHSTUB(GetDrive_ClusterSize, 0xFFC5D2B4)
NHSTUB(GetDrive_TotalClusters, 0xFFC5D2F0)
NHSTUB(GetDrive_FreeClusters, 0xFFC5D32C)
