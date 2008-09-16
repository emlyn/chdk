#include "stubs_asm.h"

NHSTUB(free, 0xFFECB53C)	//FreeMemory
NHSTUB(VbattGet, 0xffc1c000)
NHSTUB(SetZoomActuatorSpeedPercent, 0xffc017e8) //null stub
NHSTUB(GetDrive_ClusterSize, 0xFFC5DC88)
NHSTUB(GetDrive_TotalClusters, 0xFFC5DCC4)
NHSTUB(GetDrive_FreeClusters, 0xFFC5DD00)
NHSTUB(WriteSDCard, 0xFFC6D0CC)
NHSTUB(TurnOffMic, 0xffc1e774)
NHSTUB(TurnOnMic, 0xffc1e738)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFCE0A58) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFCE0A28) 
NHSTUB(MakeAFScan,               0xFFD35C10) 
NHSTUB(GetBatteryTemperature, 0xFFC1D030)
NHSTUB(GetCCDTemperature, 0xFFC1D01C)
NHSTUB(GetOpticalTemperature, 0xFFC1D008)
NHSTUB(PT_PlaySound, 0xFFD3F224)

NHSTUB(EnterToCompensationEVF, 0xffd33148) 
NHSTUB(ExitFromCompensationEVF, 0xffd331a8) 
NHSTUB(SetAE_ShutterSpeed, 0xFFE87778)
