#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFF82D048)
NHSTUB(UniqueLedOff, 0xFF82D08C)
NHSTUB(free, 0xFFAD6AA4)
NHSTUB(VbattGet, 0xFF82B704)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8117EC)

NHSTUB(kbd_p1_1, 0xFF82DB90)
NHSTUB(kbd_p1_2, 0xFF82DBC4)
NHSTUB(kbd_p1_3, 0xFF82DBF8)

NHSTUB(GetDrive_ClusterSize, 0xFF86DA9C)
NHSTUB(GetDrive_TotalClusters, 0xFF86DAD8)
NHSTUB(GetDrive_FreeClusters, 0xFF86DB14)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF8F2A28) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF8F2A10) 
NHSTUB(MakeAFScan,  0xFF94E624) 
NHSTUB(GetBatteryTemperature, 0xFF82C6D4)
NHSTUB(GetCCDTemperature, 0xFF82C6C0)
NHSTUB(GetOpticalTemperature, 0xFF82C6AC)
NHSTUB(PT_PlaySound, 0xFF9571CC)


//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(DoAFLock, 0xff94a1d0)
NHSTUB(UnlockAF, 0xff94a210)
NHSTUB(SetScriptMode,0xFF95DA14) // by find_eventproc name @ 0xFF982940
