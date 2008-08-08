#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFF82D11C)
NHSTUB(UniqueLedOff, 0xFF82D160)
NHSTUB(free, 0xFFAD6B78)
NHSTUB(VbattGet, 0xFF82B7D8)

NHSTUB(kbd_pwr_off, 0xFF8277F0) // ok
NHSTUB(kbd_pwr_on, 0xFF8277B0) // ok
NHSTUB(kbd_read_keys_r2, 0xff827334) // ok

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8118C0)

NHSTUB(GetDrive_ClusterSize, 0xFF86DB70)
NHSTUB(GetDrive_TotalClusters, 0xFF86DBAC)
NHSTUB(GetDrive_FreeClusters, 0xFF86DBE8)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF8F2AFC) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF8F2AE4) 
NHSTUB(MakeAFScan,  0xFF94E6F8) 
NHSTUB(GetBatteryTemperature, 0xFF82C7A8)
NHSTUB(GetCCDTemperature, 0xFF82C794)
NHSTUB(GetOpticalTemperature, 0xFF82C780)
NHSTUB(PT_PlaySound, 0xFF9572A0)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
