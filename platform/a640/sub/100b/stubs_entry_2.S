#include "stubs_asm.h"

NHSTUB(malloc, 0xFFEFD1A0)
NHSTUB(free, 0xFFEFD1AC)

//NHSTUB(VbattGet, 0xFFC1CD70)
//NHSTUB(GetZoomLensCurrentPosition, 0xFFE912B4)
//NHSTUB(GetZoomLensCurrentPoint, 0xFFE912A0)
//NHSTUB(GetFocusLensSubjectDistance, 0xFFEA4E74)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFEBDC9C)  //null stub
NHSTUB(GetDrive_ClusterSize, 0xffc61d94)
NHSTUB(GetDrive_TotalClusters, 0xffc61dd0)
NHSTUB(GetDrive_FreeClusters, 0xffc61e0c)
