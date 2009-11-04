#include "stubs_asm.h"

NHSTUB(malloc, 0xFFEFD1A0)
NHSTUB(free, 0xFFEFD1AC)

//NHSTUB(VbattGet, 0xFFC1CD70)
//NHSTUB(GetZoomLensCurrentPosition, 0xFFE912B4)
//NHSTUB(GetZoomLensCurrentPoint, 0xFFE912A0)
//NHSTUB(GetFocusLensSubjectDistance, 0xFFEA4E74)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFEBDC9C)  //null stub
NHSTUB(GetDrive_ClusterSize, 0xffc61d94)
NHSTUB(GetDrive_TotalClusters, 0xffc61dd0)
NHSTUB(GetDrive_FreeClusters, 0xffc61e0c)
NHSTUB(WriteSDCard, 0xFFC718B8)
NHSTUB(TurnOffMic, 0xffc1f588)
NHSTUB(TurnOnMic, 0xffc1f54c)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFCF89F8) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFCF89C8) 
NHSTUB(MakeAFScan,  0xFFD56C30) 
NHSTUB(GetBatteryTemperature, 0xFFC1DE44)
NHSTUB(GetCCDTemperature, 0xFFC1DE30)
NHSTUB(GetOpticalTemperature, 0xFFC1DE1C)
NHSTUB(PT_PlaySound, 0xFFD61A04)

NHSTUB(EnterToCompensationEVF, 0xffd5235c)
NHSTUB(ExitFromCompensationEVF, 0xffd55be0) 
NHSTUB(SetAE_ShutterSpeed, 0xFFEB5E3C)
NHSTUB(DoAFLock, 0xffd521e8)
NHSTUB(UnlockAF, 0xffd5225c)
NHSTUB(SetScriptMode,0xFFD68750) // by find_eventproc name @ 0xFFD8F704
