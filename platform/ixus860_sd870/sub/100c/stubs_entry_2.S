#include "stubs_asm.h"


NHSTUB(GetCurrentAvValue, 0xFF924F7C)
NHSTUB(kbd_pwr_off, 0xFF84448C)
NHSTUB(kbd_pwr_on, 0xFF84443C)
NSTUB(kbd_read_keys, 0xFF8230CC)
NHSTUB(kbd_read_keys_r2, 0xFF843FA8)
NHSTUB(time, 0xFF865744)

NSTUB(PutInNdFilter,  0xFF9E448C)
NSTUB(PutOutNdFilter, 0xFF9E44C4)

NSTUB(UnsetZoomForMovie,     0xFF94A2C4)

NSTUB(CreateController, 0xFF86A6E4)
NSTUB(DebugAssert, 0xFF81C090)
NSTUB(EventProcedure, 0xFF81C0EC)
NSTUB(GetAEIntegralServiceMode_0, 0xFF82C92C)
NSTUB(GetAEIntegralServiceMode_7, 0xFF94A430)
NSTUB(GetVRAMHPixelsSize_0, 0xFF8734A8)
NSTUB(GetVRAMHPixelsSize_1, 0xFF878A2C)
NSTUB(HardwareDefect, 0xFF86D2D8)
NSTUB(IsControlEventActive, 0xFF86CC0C)
NSTUB(IsFactoryMode, 0xFF847C34)
NSTUB(KernelCreateTask, 0xFF81BE90)
NSTUB(LockMainPower, 0xFF86D04C)
NSTUB(PTM_GetCurrentItem, 0xFF86DB08)
NSTUB(PTM_SetCurrentCaptureMode, 0xFF86D9C4)
NSTUB(PT_GetPropertyCaseString, 0xFF869470)
NSTUB(PT_SetPropertyCaseString, 0xFF869368)
NSTUB(PostLogicalEventForNotPowerType, 0xFF86AE94)
NSTUB(PostLogicalEventToUI, 0xFF86AEE0)
NSTUB(RestartDevice, 0xFF82B964)
NSTUB(StartDiskboot, 0xFF82BB44)
NSTUB(StartFactoryModeController, 0xFF847C74)
NSTUB(StartGUISystem, 0xFF88F8E0)
NSTUB(StartRecModeMenu, 0xFF980908)
NSTUB(StartWDT, 0xFF868080)
NSTUB(TakeSemaphore, 0xFF81BA54)
NSTUB(j_IsEvfDriveMode_16, 0xFF956658)
NSTUB(j_PTM_GetWorkingCaptureMode, 0xFF86DAF8)
NSTUB(j_PTM_SetCurrentItem, 0xFF86DAFC)
NSTUB(j_PTM_SetCurrentItem_0, 0xFF86DB00)
NSTUB(j_nullsub_192, 0xFF82BABC)
NSTUB(j_unknown_libname_73, 0xFF870E40)
NSTUB(nullsub_2, 0xFF820BC0)
NSTUB(nullsub_206, 0xFF857EF0)
NSTUB(nullsub_35, 0xFF86E47C)
NSTUB(nullsub_37, 0xFF875398)
NSTUB(nullsub_96, 0xFF93D744)
NSTUB(qPrintf, 0xFF8115D0)
NSTUB(taskcreate_AudioTsk, 0xFF8445B0)
NSTUB(taskcreate_AviWrite, 0xFF92DB10)
NSTUB(taskcreate_Bye, 0xFF82B828)
NSTUB(taskcreate_ClockSave, 0xFF8151CC)
NSTUB(taskcreate_CommonDrivers, 0xFF870D74)
NSTUB(taskcreate_DSITask, 0xFF879048)
NSTUB(taskcreate_FaceFrame, 0xFF878E78)
NSTUB(taskcreate_LEDCon, 0xFF843798)
NSTUB(taskcreate_PhySw, 0xFF822DAC)
NSTUB(taskcreate_StartupImage, 0xFF82C06C)
NSTUB(taskcreate_TempCheck, 0xFF822048)
NSTUB(taskcreate_Thermometer, 0xFF8469CC)
NSTUB(taskcreate_WdtReset, 0xFF867FE8)
NSTUB(unknown_libname_80, 0xFF871E70)
NSTUB(unknown_libname_96, 0xFF87A340)





//NHSTUB(OnPrintTouchWheel, 0xFF8E7130)
//NHSTUB(OffPrintTouchWheel, 0xFF8E7120)

//NSTUB(TurnOnMic, 0xFF845074)  // these functions don't actually work, although they do appear similar to those in the A650
//NSTUB(TurnOffMic, 0xFF8450AC)


NHSTUB(eventproc_ShowCameraLog, 0xFF867498)
NHSTUB(eventproc_export_ShowAllTaskInfo, 0xFF860D2C)
NHSTUB(eventproc_GetLogToFile, 0xFF861FF8)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810958)  //null stub


//!!! dryos Test
NHSTUB(NewTaskShell, 0xFFC596B0)  // starts new shell on Console. GUI output?
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFFD4A934) // should write 'A/FirmInfo.txt'
NHSTUB(dumpMemoryToFile, 0xFFC141Fa)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)


// !! UNKNOWN !!
// Not found, point to nullsub for immediate return
// nullsub_1: 0xFF810958

NHSTUB(utime, 0xFF810958)


//NSTUB(CreatePhysicalVram,		 0xFF810958)
//NSTUB(CreateTaskStrict,			 0xFF810958)
//NSTUB(DisableDispatch,			 0xFF810958)
//NSTUB(DisplayImagePhysicalScreen,	 0xFF810958)
//NSTUB(EnableDispatch,			 0xFF810958)
//NSTUB(ioctl,				 0xFF810958)
//NSTUB(iosDevAdd,			 0xFF810958)
//NSTUB(iosDrvInstall,			 0xFF810958)
//NSTUB(memPartAlloc,			 0xFF810958)
//NSTUB(memPartFindMax,			 0xFF810958)
//NSTUB(PhySw_testgpio,			 0xFF810958)
//NSTUB(ProtectFile,			 0xFF810958)


// Those aren't used or don't exist in DryOS

//NSTUB(taskCreateHookAdd,		 0xFF810958)
//NSTUB(taskDeleteHookAdd,		 0xFF810958)
//NSTUB(taskIdListGet,			 0xFF810958)
NSTUB(taskLock,				 0xFF810958)
//NSTUB(taskName,			 0xFF810958)
//NSTUB(taskResume,			 0xFF810958)
//NSTUB(taskSuspend,			 0xFF810958)
NSTUB(taskUnlock,			 0xFF810958)
NSTUB(Mount_FileSystem,			 0xFF810958)
NSTUB(Unmount_FileSystem,		 0xFF810958)
NSTUB(rewinddir,			 0xFF810958)
NSTUB(CreatePhysicalVram,		 0xFF810958)
NSTUB(CreateTaskStrict,			 0xFF810958)
NSTUB(DisableDispatch,			 0xFF810958)
NSTUB(DisplayImagePhysicalScreen,	 0xFF810958)
NSTUB(EnableDispatch,			 0xFF810958)
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFF810958)
NSTUB(MakeDirectory,			 0xFF810958)
NSTUB(PhySw_testgpio,			 0xFF810958)
NSTUB(ProtectFile,			 0xFF810958)
NSTUB(chdir,				 0xFF810958)
NSTUB(ioctl,				 0xFF810958)
NSTUB(iosDevAdd,			 0xFF810958)
NSTUB(iosDrvInstall,			 0xFF810958)
NSTUB(isalpha,				 0xFF810958)
NSTUB(isdigit,				 0xFF810958)
NSTUB(islower,				 0xFF810958)
NSTUB(isspace,				 0xFF810958)
NSTUB(isupper,				 0xFF810958)
NSTUB(localtime,			 0xFF810958)
NSTUB(readdir,				 0xFF810958)
NSTUB(strpbrk,				 0xFF810958)
NSTUB(taskCreateHookAdd,		 0xFF810958)
NSTUB(taskDeleteHookAdd,		 0xFF810958)
NSTUB(taskIdListGet,			 0xFF810958)
NSTUB(taskName,				 0xFF810958)
NSTUB(taskResume,			 0xFF810958)
NSTUB(taskSuspend,			 0xFF810958)
NHSTUB(GetBatteryTemperature, 0xFF846B30)
NHSTUB(GetCCDTemperature, 0xFF846C54)
NHSTUB(GetOpticalTemperature, 0xFF846BA0)
NHSTUB(PT_PlaySound, 0xFF86015C)


//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(SetFileTimeStamp, 0xFF825308)
