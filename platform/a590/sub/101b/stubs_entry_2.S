#include "stubs_asm.h"

//NSTUB(AllocateMemory, 				0xFFDF1D70)
//NSTUB(FreeMemory, 					0xFFDF1D68)
//NSTUB(dumpMemoryToFile, 			0xffc00948)
//NSTUB(GetDrive_FreeClusters,		0xFFC416F0)
//NSTUB(GetDrive_TotalClusters,		0xFFC416BC)
//NSTUB(strcpy, 						0xFFC0D88C)
NHSTUB(ExecuteEventProcedure, 0xffc59eb4)
NHSTUB(ExitFromCompensationEVF, 0xffc15fa4)
//NSTUB(ExpCtrlTool_StopContiAE,		0xFFC22054)
NHSTUB(ExpCtrlTool_StartContiAE,	0xFFC21F10)
//NSTUB(GetAEIntegralServiceMode_0,	0xFFC1A9C4)
//NSTUB(IsFactoryMode,				0xFFC38838)
//NSTUB(PhySw_testgpio,				0xFFC356EC)
NHSTUB(LEDDrive,	    		0xFFC34CE0)

// NOT found, using NULLSUB
//NSTUB(taskcreate_AudioTsk,			0xFFC3591C)
//NSTUB(TurnOnBackLight,				0xFFC6C558)
//NSTUB(TurnOffBackLight,			0xFFC6C570)
//NSTUB(unknown_libname_80, 			0xFFC668B0)
//NSTUB(unknown_libname_96, 			0xFFC6C77C)
NHSTUB(MakeAFScan, 					0xFFDEEA08)       // was 0xFFC00948 (nullsub_1) OldGit 20-Jan-2010
//NHSTUB(OpLog_WriteToSD, 			0xFFC5B878)
//NSTUB(open, 						0xFFC09EC4)
//NSTUB(close, 						0xFFC09F74)

NHSTUB(UnsetZoomForMovie, 0xffd3a34c)

// NULLSUBS
NHSTUB(Unmount_FileSystem, 0xffc00948)
NHSTUB(Mount_FileSystem, 0xffc00948)
NHSTUB(rewinddir, 0xffc00948)
NHSTUB(SetZoomActuatorSpeedPercent, 0xffc00948)

NHSTUB(DoAFLock, 0xffc15b04)
NHSTUB(UnlockAF, 0xffc15c1c)
NHSTUB(apex2us, 0xFFD7DD6C)
NHSTUB(WriteSDCard,0xFFD01548)

NHSTUB(SetScriptMode,0xFFC61F08) // string
