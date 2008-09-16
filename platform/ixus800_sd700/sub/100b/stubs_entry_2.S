#include "stubs_asm.h"

NHSTUB(VbattGet, 0xFF82C14C)
NHSTUB(free, 0xFFB0EFE4)
NHSTUB(kbd_pwr_on, 0xFF827EC8)
NHSTUB(kbd_pwr_off, 0xFF827F08)
NHSTUB(GetCurrentAvValue, 0xFFAC401C)

// null stubs
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF966BC4)

NHSTUB(GetDrive_ClusterSize, 0xFF86ED90)
NHSTUB(GetDrive_TotalClusters, 0xFF86EDCC)
NHSTUB(GetDrive_FreeClusters, 0xFF86EE08)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF903550) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF903520) 
NHSTUB(MakeAFScan,  0xFF95FDE8) 
NHSTUB(GetBatteryTemperature, 0xFF82D218)
NHSTUB(GetCCDTemperature, 0xFF82D204)
NHSTUB(GetOpticalTemperature, 0xFF82D1F0)
NHSTUB(PT_PlaySound, 0xFF969540)


//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
