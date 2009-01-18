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
NHSTUB(GetBatteryTemperature, 0xFF82D5AC)
NHSTUB(GetCCDTemperature, 0xFF82D598)
NHSTUB(GetOpticalTemperature, 0xFF82D584)
NHSTUB(PT_PlaySound, 0xFF957A90)



//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(DoAFLock, 0xff94aacc)
NHSTUB(UnlockAF, 0xff94ab0c)
