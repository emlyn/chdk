#include "stubs_asm.h"


NHSTUB(free, 0xFFB9ECCC)
NHSTUB(platformsub_kbd_fetch_data, 0xFF8293AC)
NHSTUB(kbd_read_keys_r2, 0xFF828E70)

NHSTUB(GiveSemaphore, 0xFF82218C)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF9EA4EC)  //null

NHSTUB(WriteSDCard, 0xFF88BE6C)
NHSTUB(GetDrive_ClusterSize, 0xff87c338)
NHSTUB(GetDrive_TotalClusters, 0xff87c374)
NHSTUB(GetDrive_FreeClusters, 0xff87c3b0)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF925F3C) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF925F0C) 
NHSTUB(MakeAFScan,               0xFF9A0560) 
NHSTUB(GetBatteryTemperature, 0xFF82EB20)
NHSTUB(GetCCDTemperature, 0xFF82EB0C)
NHSTUB(GetOpticalTemperature, 0xFF82EAF8)
NHSTUB(PT_PlaySound, 0xFF9ACA78)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
