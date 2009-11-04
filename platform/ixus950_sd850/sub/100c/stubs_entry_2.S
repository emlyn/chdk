#include "stubs_asm.h"

//NHSTUB(MFOn, 0xFFB1AF88) // added
//NHSTUB(MFOff, 0xFFB1AF98) // added
// or, equivalently, one step "deeper":
NHSTUB(MFOn, 0xFFB0B14C) // added
NHSTUB(MFOff, 0xFFB0B1B0) // added

//NSTUB(SetAutoShutdownTime, 0xFFB45EF8) // ok	// "AutoShut.c", added in 303 (fingalo, ubasic)

NHSTUB(Close, 0xFFAA2FBC) // note "aClose"
NHSTUB(DisplayImagePhysicalScreen, 0xFFA2CFCC)	// note "ImgDDev.c"
NHSTUB(Mount_FileSystem, 0xFFAA22E4)	// note "Mounter.c"
NHSTUB(Remove, 0xFFAA2FDC)	// note "remove"
NHSTUB(Read, 0xFFAA3050)	// after Remove
NHSTUB(Write, 0xFFAA305C)	// after Read
NHSTUB(free, 0xFF92BA0C)

//NSTUB(kbd_p1_f, 0xffa3711c) // ok
//NSTUB(kbd_p1_f_cont, 0xffa37128) // ok
//NSTUB(kbd_p2_f, 0xffa3754c) // ok
NHSTUB(kbd_pwr_off, 0xFFA38C14) // corrected
NHSTUB(kbd_pwr_on, 0xFFA38BD4) // corrected
NHSTUB(kbd_read_keys_r2, 0xFFA386C8) // added

NHSTUB(TakeSemaphore, 0xFFB22F70) // after "TakeSemaphore" strings

// see at FF818B60
NHSTUB(AllocateMemory, 0xFF818664)
NHSTUB(FreeMemory, 0xFF818650)

NHSTUB(SetPropertyCase, 0xFF81BB60) // see "PropertyCase.c" and refs to it

// null stub (RET):
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF9B4BA4)	// nullsub_100

// note FFADB724 "FocusLensController.c"
//NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFADC9E8) // ok

NHSTUB(GetDrive_ClusterSize, 0xFFAA27AC)	// note "GetCatFs_ClusterSize"
NHSTUB(GetDrive_TotalClusters, 0xFFAA27E8)	// note "GetCatFs_TotalClusters"
NHSTUB(GetDrive_FreeClusters, 0xFFAA2820)	// note "GetCatFs_FreeClusters"

//NSTUB(Fopen_Fut, 0xFFA9E6AC) // ok
//NSTUB(Fread_Fut, 0xFFA9E7A8) // ok
//NSTUB(Fwrite_Fut, 0xFFA9E7FC) // ok
//NSTUB(Fclose_Fut, 0xFFA9E6EC) // ok
//NSTUB(Fseek_Fut, 0xFFA9E89C) // ok

NHSTUB(UnsetZoomForMovie, 0xFF83656C)
NHSTUB(WriteSDCard, 0xFFAB536C)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF971658) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF971628) 
NHSTUB(MakeAFScan,  0xFFB0ECB0) 
NHSTUB(GetBatteryTemperature, 0xFFA3D408)
NHSTUB(GetCCDTemperature, 0xFFA3D3F4)
NHSTUB(GetOpticalTemperature, 0xFFA3D3E0)
NHSTUB(PT_PlaySound, 0xFFB1A0A4)
NHSTUB(taskNameToId, 0xFF935A64)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(DoAFLock, 0xffb09200)
NHSTUB(UnlockAF, 0xffb09280)
NHSTUB(apex2us,0xFF93CE88);
NHSTUB(SetScriptMode,0xFFB43A00) // by find_eventproc name @ 0xFF81FB58
