#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFF82df20)
NHSTUB(UniqueLedOff, 0xFF82df64)
NHSTUB(free, 0xFFAD6680)
NHSTUB(VbattGet, 0xFF82c54c)

NHSTUB(GetDrive_ClusterSize, 0xFF86EF64)
NHSTUB(GetDrive_TotalClusters, 0xFF86EFA0)
NHSTUB(GetDrive_FreeClusters, 0xFF86EFDC)
NHSTUB(WriteSDCard, 0xFF87E9CC)
NHSTUB(iosDevFind, 0xFFAD47E0)

//null stubs
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF82e080)


