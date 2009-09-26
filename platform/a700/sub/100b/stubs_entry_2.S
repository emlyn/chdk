#include "stubs_asm.h"

NHSTUB(VbattGet, 0xFFC1B990)
NHSTUB(GetZoomLensCurrentPosition, 0xFFE7F694)
NHSTUB(GetZoomLensCurrentPoint, 0xFFE7F680)
NHSTUB(GetFocusLensSubjectDistance, 0xFFE92C14)

NHSTUB(malloc, 0xFFEE84BC)
NHSTUB(free, 0xFFEE84C8)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC22854)  //null stub

NHSTUB(GetDrive_ClusterSize, 0xFFC5D2B4)
NHSTUB(GetDrive_TotalClusters, 0xFFC5D2F0)
NHSTUB(GetDrive_FreeClusters, 0xFFC5D32C)
NHSTUB(TurnOffMic, 0xffc1e100)
NHSTUB(TurnOnMic, 0xffc1e0c4)

NHSTUB(ExpCtrlTool_StopContiAE,  0xFFCF1958) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFCF1928) 
NHSTUB(MakeAFScan,  0xFFD46CF0) 
NHSTUB(GetBatteryTemperature, 0xFFC1C9BC)
NHSTUB(GetCCDTemperature, 0xFFC1C9A8)
NHSTUB(GetOpticalTemperature, 0xFFC1C994)
NHSTUB(PT_PlaySound, 0xFFD5030C)

NHSTUB(EnterToCompensationEVF, 0xffd4424c)
NHSTUB(ExitFromCompensationEVF, 0xffd442ac)
NHSTUB(SetAE_ShutterSpeed, 0xFFEA481C) 
NHSTUB(DoAFLock, 0xffd423e8)
NHSTUB(UnlockAF, 0xffd4242c)
NHSTUB(PostLEDMessage, 0xFFC1CF80)

