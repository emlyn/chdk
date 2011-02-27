#include "stubs_asm.h"

//NHSTUB(VbattGet, 0xFFC1B4CC)
//NHSTUB(GetZoomLensCurrentPosition, 0xFFE53070)
//NHSTUB(GetZoomLensCurrentPoint, 0xFFE5305C)
//NHSTUB(GetFocusLensSubjectDistance, 0xFFE667F0)
//NHSTUB(malloc, 0xFFEBEE9C)
//NHSTUB(free, 0xFFEBEEA8)

//NHSTUB(MoveFocusLensWithDistance, 0xFFE67B14)
//NHSTUB(MoveZoomLensWithPoint, 0xFFE52F3C)
//NHSTUB(MoveZoomLensWithPosition, 0xFFE52FB8)
//NHSTUB(GetFocusLensCurrentPosition, 0xFFE67F10)
//NHSTUB(MoveFocusLensWithPosition, 0xFFE67CB4)


NHSTUB(GetDrive_ClusterSize, 0xFFC5BEE8)
NHSTUB(GetDrive_TotalClusters, 0xFFC5BF24)
NHSTUB(GetDrive_FreeClusters, 0xFFC5BF60)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC20AD4)  //null stub
NHSTUB(TurnOffMic, 0xffc1ec78)
NHSTUB(TurnOnMic, 0xffc1ec30)

NHSTUB(ExpCtrlTool_StopContiAE,  0xFFCE05B8) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFCE05A0) 
NHSTUB(MakeAFScan,  0xFFD377B0) 
NHSTUB(GetBatteryTemperature, 0xFFC1C488)
NHSTUB(GetCCDTemperature, 0xFFC1C474)
NHSTUB(GetOpticalTemperature, 0xFFC1C460)
NHSTUB(PT_PlaySound, 0xFFD4074C)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(SetAE_ShutterSpeed, 0xFFE76A00)
NHSTUB(DoAFLock, 0xffd33094)
NHSTUB(UnlockAF, 0xffd330d4)
NHSTUB(SetScriptMode,0xFFD46FE4) // by find_eventproc name @ 0xFFD6D3DC
NHSTUB(WriteSDCard, 0xFFC6AFD8)

NHSTUB(exmem_alloc, 0xFFC02830)
NHSTUB(exmem_free ,0xFFC0287C)

NHSTUB(apex2us, 0xFFC987EC) //for extra long exposures