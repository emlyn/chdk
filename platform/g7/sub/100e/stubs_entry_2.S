#include "stubs_asm.h"

NHSTUB(free, 0xFFB9EA6C)
NHSTUB(platformsub_kbd_fetch_data, 0xFF8293AC)
NHSTUB(kbd_read_keys_r2, 0xFF828E70)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8117E8)  //null

NHSTUB(GiveSemaphore, 0xFF82218C)

NHSTUB(WriteSDCard, 0xFF88BE6C)
NHSTUB(GetDrive_ClusterSize, 0xff87c338)
NHSTUB(GetDrive_TotalClusters, 0xff87c374)
NHSTUB(GetDrive_FreeClusters, 0xff87c3b0)

NHSTUB(ExpCtrlTool_StopContiAE,  0xFF925F18) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF925EE8) 
NHSTUB(MakeAFScan,               0xFF9A04E0) 
NHSTUB(GetBatteryTemperature, 0xFF82EB20)
NHSTUB(GetCCDTemperature, 0xFF82EB0C)
NHSTUB(GetOpticalTemperature, 0xFF82EAF8)
NHSTUB(PT_PlaySound, 0xFF9AC9D0)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(taskNameToId, 0xFFBAB5A4)
NHSTUB(DoAFLock, 0xff99af54)
NHSTUB(UnlockAF, 0xff99afc8)
NHSTUB(SetScriptMode,0xFF9B38E4) // by find_eventproc name @ 0xFF9DFDBC
