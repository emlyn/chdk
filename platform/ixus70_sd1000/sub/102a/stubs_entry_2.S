#include "stubs_asm.h"

NHSTUB(Close,  0xFFA9A008)
NHSTUB(DisplayImagePhysicalScreen, 0xFFA25068)
NHSTUB(Mount_FileSystem, 0xFFA9932C)
NHSTUB(Read,   0xFFA9A09C)
NHSTUB(Remove, 0xFFA9A028)
NHSTUB(Write,  0xFFA9A0A8)
NHSTUB(free, 0xFF9201CC)
NHSTUB(kbd_read_keys_r2, 0xFFA30724)

NSTUB(GetCurrentAvValue, 0xFFAD9E94)

NHSTUB(AllocateMemory, 0xFF818664)
NHSTUB(FreeMemory, 0xFF818650) 
NHSTUB(GetFocusLensSubjectDistance, 0xFFAD2FB4) 
NHSTUB(TakeSemaphore, 0xFFB141D4)
NHSTUB(kbd_pwr_off, 0xFFA30C58)
NHSTUB(kbd_pwr_on, 0xFFA30C18)
NHSTUB(SetPropertyCase, 0xFF81BB60)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF9AD778) //null stub

NHSTUB(GetDrive_ClusterSize, 0xFFA997F4)
NHSTUB(GetDrive_TotalClusters, 0xFFA99830)
NHSTUB(GetDrive_FreeClusters, 0xFFA9986C)

NHSTUB(MakeAFScan, 0xFFB000D0) // _sub_FFB000D0__SsPrepareSeqBase.c__572
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF96553C) // SetFocusLensDefaultCondition_3
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF96556C) // SetFocusLensDefaultCondition_5
NHSTUB(GetBatteryTemperature, 0xFFA344E4)
NHSTUB(GetCCDTemperature, 0xFFA344D0)
NHSTUB(GetOpticalTemperature, 0xFFA344BC)
NHSTUB(PT_PlaySound, 0xFFB0B2EC)

