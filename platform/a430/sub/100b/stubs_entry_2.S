#include "stubs_asm.h"

NHSTUB(free, 0xFFEB1EB0)//ok
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC017E8)//ok, null stub
NHSTUB(VbattGet, 0xFFC1BCA0)//ok


NHSTUB(GetDrive_ClusterSize, 0xFFC5CF80) //ok
NHSTUB(GetDrive_TotalClusters, 0xFFC5CFBC) //ok
NHSTUB(GetDrive_FreeClusters, 0xFFC5CFF8) // ok


NHSTUB(TurnOffMic, 0xFFC1E40C) //ok
NHSTUB(TurnOnMic, 0xFFC1E3D0) //ok


NHSTUB(ExpCtrlTool_StopContiAE,  0xFFCDBB1C) //ok
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFCDBAEC) //ok
NHSTUB(MakeAFScan,               0xFFD2AC58) //ok
NHSTUB(GetBatteryTemperature, 0xFFC1CCD0) //ok
NHSTUB(GetCCDTemperature,     0xFFC1CCBC) //ok
NHSTUB(GetOpticalTemperature, 0xFFC1CCA8) //ok
NHSTUB(PT_PlaySound, 0xFFD33988) //ok

NHSTUB(EnterToCompensationEVF, 0xFFD28268) //found by zfeet
NHSTUB(ExitFromCompensationEVF, 0xFFD282C4) //found by zfeet
NHSTUB(SetAE_ShutterSpeed, 0xFFE6CB9C) //ok
NHSTUB(DoAFLock, 0xFFD2647C) //ok
NHSTUB(UnlockAF, 0xFFD264C0) //ok

NHSTUB(kbd_pwr_on, 0xFFC017E8) //wrong, null stub
NHSTUB(kbd_pwr_off, 0xFFC017E8) //wrong, null stub
NHSTUB(apex2us, 0xFFC96F4C) //ok
NHSTUB(WriteSDCard, 0xFFC6C3DC) //

NHSTUB(SetScriptMode,0xFFD3A12C) // by find_eventproc name @ 0xFFD7F194
