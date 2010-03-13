#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFF82df20)
NHSTUB(UniqueLedOff, 0xFF82df64)
NHSTUB(free, 0xFFAD6A08)
NHSTUB(VbattGet, 0xFF82c54c)

NHSTUB(GetDrive_ClusterSize, 0xFF86F2EC)
NHSTUB(GetDrive_TotalClusters, 0xFF86F328)
NHSTUB(GetDrive_FreeClusters, 0xFF86F364)
NHSTUB(WriteSDCard, 0xFF87ED54)
NHSTUB(iosDevFind, 0xFFAD4B68)

//null stubs
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF82e080)
NHSTUB(GetBatteryTemperature, 0xFF82D5AC)
NHSTUB(GetCCDTemperature, 0xFF82D598)
NHSTUB(GetOpticalTemperature, 0xFF82D584)
NHSTUB(PT_PlaySound, 0xFF957E18)





//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(DoAFLock, 0xff94ae54)
NHSTUB(UnlockAF, 0xff94ae94)
NHSTUB(SetScriptMode,0xFF95E63C) // by find_eventproc name @ 0xFF983394
