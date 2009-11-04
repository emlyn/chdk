#include "stubs_asm.h"

//NHSTUB(VbattGet, 0xFFC1B4AC)
//NHSTUB(GetZoomLensCurrentPosition, 0xFFE59D2C)
//NHSTUB(GetZoomLensCurrentPoint, 0xFFE59D18)
//NHSTUB(GetFocusLensSubjectDistance, 0xFFE6D4AC)

NHSTUB(malloc, 0xFFEC5BC0)
NHSTUB(free, 0xFFEC5BCC)

//NHSTUB(isalpha, 0xFFEB8A94)
//NHSTUB(isdigit, 0xFFEB8AC4)
//NHSTUB(islower, 0xFFEB8AF4)
//NHSTUB(isspace, 0xFFEB8B3C)
//NHSTUB(isupper, 0xFFEB8B54)
//NHSTUB(rand, 0xFFEBBF78)
//NHSTUB(srand, 0xFFEBBF9C)

NHSTUB(GetDrive_ClusterSize, 0xffc5c668)
NHSTUB(GetDrive_TotalClusters, 0xffc5c6a4)
NHSTUB(GetDrive_FreeClusters, 0xffc5c6e0)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC19688)  //null stub

//NHSTUB(PutInNdFilter, 0xFFE78410) 
//NHSTUB(PutOutNdFilter, 0xFFE78458)
NHSTUB(TurnOffMic, 0xffc1ec58)
NHSTUB(TurnOnMic, 0xffc1ec10)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFCE0A10) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFCE09F8) 
NHSTUB(MakeAFScan,  0xFFD384E4) 
NHSTUB(GetBatteryTemperature, 0xFFC1C468)
NHSTUB(GetCCDTemperature, 0xFFC1C454)
NHSTUB(GetOpticalTemperature, 0xFFC1C440)
NHSTUB(PT_PlaySound, 0xFFD41638)
NHSTUB(EnterToCompensationEVF, 0xffd35c44)
NHSTUB(ExitFromCompensationEVF, 0xffd35ca4)
NHSTUB(SetAE_ShutterSpeed, 0xFFE7D6DC)
NHSTUB(DoAFLock, 0xffd33b2c)
NHSTUB(UnlockAF, 0xffd33b94)
NHSTUB(SetScriptMode,0xFFD47EA4) // by find_eventproc name @ 0xFFD6E424
