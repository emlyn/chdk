#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFFA42B88)
NHSTUB(UniqueLedOff, 0xFFA42C30)
NHSTUB(free, 0xFF92B488)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF841CC0)  // null stub
NHSTUB(UnsetZoomForMovie, 0xFF841CC0)  // null stub

NHSTUB(GetDrive_ClusterSize, 0xFFAAE448)
NHSTUB(GetDrive_TotalClusters, 0xFFAAE484)
NHSTUB(GetDrive_FreeClusters, 0xFFAAE4C0)

NHSTUB(DisplayImagePhysicalScreen, 0xFFA37828)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAFF748)
NHSTUB(Mount_FileSystem, 0xFFAADF80)
NHSTUB(MoveZoomLensWithPoint, 0xFFAFF658)
NHSTUB(Remove, 0xFFAAEC7C)
NHSTUB(Write, 0xFFAAECFC)
NHSTUB(Close, 0xFFAAEC5C)
NHSTUB(Read, 0xFFAAECF0)

NHSTUB(kbd_read_keys_r2, 0xFFA444FC)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAEAB54)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAEA654)
NHSTUB(GetZoomLensCurrentPoint, 0xFFAFF734)
NHSTUB(SetPropertyCase, 0xFF81BC20)
NHSTUB(PostLEDMessage, 0xFFA4288C)
NHSTUB(PutInNdFilter, 0xffa63994)
NHSTUB(PutOutNdFilter, 0xffa639DC)
NHSTUB(WriteSDCard, 0xFFAC0FF8)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF9779CC) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF97799C) 
NHSTUB(MakeAFScan,               0xFFB2C7E4) 
NHSTUB(GetBatteryTemperature, 0xFFA48D00)
NHSTUB(GetCCDTemperature, 0xFFA48CEC)
NHSTUB(GetOpticalTemperature, 0xFFA48CD8)
NHSTUB(PT_PlaySound, 0xFFB38300)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
