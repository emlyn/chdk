#include "stubs_asm.h"

NHSTUB(VbattGet, 0xFFC1C014)//ok
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFE7D824) //ok
NHSTUB(free, 0xFFEE0F70)//ok  


NHSTUB(StartISDrive, 0xFFEA70CC) //not found
NHSTUB(StopISDrive, 0xFFEA70F0) //not found


NHSTUB(GetDrive_ClusterSize, 0xFFC5DC9C) //ok
NHSTUB(GetDrive_TotalClusters, 0xFFC5DCD8) //ok 
NHSTUB(GetDrive_FreeClusters, 0xFFC5DD14) // ok

NHSTUB(WriteSDCard, 0xFFC6D0E0)//
NHSTUB(TurnOffMic, 0xffc1e788)
NHSTUB(TurnOnMic, 0xffc1e74c)

NHSTUB(ExpCtrlTool_StopContiAE,  0xFFCF11C0) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFCF1190) 
NHSTUB(MakeAFScan,               0xFFD4656C) 
NHSTUB(GetBatteryTemperature, 0xFFC1D044)
NHSTUB(GetCCDTemperature, 0xFFC1D030)
NHSTUB(GetOpticalTemperature, 0xFFC1D01C)
NHSTUB(PT_PlaySound, 0xFFD4FB34)

NHSTUB(EnterToCompensationEVF, 0xffd43ac8)
NHSTUB(ExitFromCompensationEVF, 0xffd43b28)
NHSTUB(SetAE_ShutterSpeed, 0xFFE9D1C4) 
NHSTUB(DoAFLock, 0xffd41c64)
NHSTUB(UnlockAF, 0xffd41ca8)
