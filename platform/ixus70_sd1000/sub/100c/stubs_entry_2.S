#include "stubs_asm.h"

NHSTUB(Close,  0xFFA99F94)
NHSTUB(DisplayImagePhysicalScreen, 0xFFA24FF4)
NHSTUB(Mount_FileSystem, 0xFFA992B8)
NHSTUB(Read,   0xFFA9A028)
NHSTUB(Remove, 0xFFA99FB4)
NHSTUB(Write,  0xFFA9A034)
NHSTUB(free, 0xFF9201CC)
NHSTUB(kbd_read_keys_r2, 0xFFA306B0)

NSTUB(GetCurrentAvValue, 0xFFAD9E20)

NHSTUB(AllocateMemory, 0xFF818664)
NHSTUB(FreeMemory, 0xFF818650) 
NHSTUB(GetFocusLensSubjectDistance, 0xFFAD2F88) 
NHSTUB(TakeSemaphore, 0xFFB140E0)
NHSTUB(kbd_pwr_off, 0xFFA30BE4)
NHSTUB(kbd_pwr_on, 0xFFA30BA4)
NHSTUB(SetPropertyCase, 0xFF81BB60)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF9AD778) //null stub

NHSTUB(GetDrive_ClusterSize, 0xFFA99780)
NHSTUB(GetDrive_TotalClusters, 0xFFA997BC)
NHSTUB(GetDrive_FreeClusters, 0xFFA997F8)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF96556C) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF96553C) 
NHSTUB(MakeAFScan,  0xFFAFFFDC) 
NHSTUB(GetBatteryTemperature, 0xFFA34470)
NHSTUB(GetCCDTemperature, 0xFFA3445C)
NHSTUB(GetOpticalTemperature, 0xFFA34448)
NHSTUB(PT_PlaySound, 0xFFB0B1F8)


