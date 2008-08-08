#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFFA42C08)
NHSTUB(UniqueLedOff, 0xFFA42CB0)
NHSTUB(free, 0xFF92B488)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF841CC0)  // null stub
NHSTUB(UnsetZoomForMovie, 0xFF841CC0)  // null stub

NHSTUB(GetDrive_ClusterSize, 0xFFAAE4C8)
NHSTUB(GetDrive_TotalClusters, 0xFFAAE504)
NHSTUB(GetDrive_FreeClusters, 0xFFAAE540)
NHSTUB(DisplayImagePhysicalScreen, 0xFFA378A8)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAFF7C8)
NHSTUB(Mount_FileSystem, 0xFFAAE000)
NHSTUB(MoveZoomLensWithPoint, 0xFFAFF6D8)
NHSTUB(Remove, 0xFFAAECFC)
NHSTUB(Write, 0xFFAAED7C)
NHSTUB(Close, 0xFFAAECDC)
NHSTUB(Read, 0xFFAAED70)
NHSTUB(kbd_read_keys_r2, 0xFFA4457C)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAEABD4)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAEA6D4)
NHSTUB(GetZoomLensCurrentPoint, 0xFFAFF7B4)
NHSTUB(SetPropertyCase, 0xFF81BC20)
NHSTUB(PostLEDMessage, 0xFFA4290C)
NHSTUB(WriteSDCard, 0xFFAC1078)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF9779CC) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF97799C) 
NHSTUB(MakeAFScan,  0xFFB2C864) 
NHSTUB(GetBatteryTemperature, 0xFFA48D80)
NHSTUB(GetCCDTemperature, 0xFFA48D6C)
NHSTUB(GetOpticalTemperature, 0xFFA48D58)
NHSTUB(PT_PlaySound, 0xFFB38380)


//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
