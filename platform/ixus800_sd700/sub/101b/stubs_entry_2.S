#include "stubs_asm.h"

NHSTUB(VbattGet, 0xFF82C150)
NHSTUB(free, 0xFFB0EFDC)
NHSTUB(kbd_pwr_on, 0xFF827ECC)
NHSTUB(kbd_pwr_off, 0xFF827F0C)
NHSTUB(GetCurrentAvValue, 0xFFAC4014)

// null stubs
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF966BC4)

NHSTUB(GetDrive_ClusterSize, 0xFF86ED94)
NHSTUB(GetDrive_TotalClusters, 0xFF86EDD0)
NHSTUB(GetDrive_FreeClusters, 0xFF86EE0C)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF903554) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF903524) 
NHSTUB(MakeAFScan,  0xFF95FDEC) 
NHSTUB(GetBatteryTemperature, 0xFF82D21C)
NHSTUB(GetCCDTemperature, 0xFF82D208)
NHSTUB(GetOpticalTemperature, 0xFF82D1F4)
NHSTUB(PT_PlaySound, 0xFF969544)


//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
