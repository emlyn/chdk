#include "stubs_asm.h"

# Confirmed
NHSTUB(qsort,							0xFFB40804) // ok (comp 1.00h)
NHSTUB(strtol,							0xFF840A30) // ok (comp 1.00h)
NHSTUB(EnterToCompensationEVF,			0xFF838D44) // ok (comp 1.00h)
NHSTUB(ExitFromCompensationEVF,			0xFF838D88) // ok (comp 1.00h)
NHSTUB(GetBatteryTemperature,			0xFF8697AC) // ok (comp 1.00h)
NHSTUB(GetCCDTemperature,				0xFF869738) // ok (comp 1.00h)
NHSTUB(GetCurrentAvValue,				0xFF980680) // ok (comp 1.00h)
NHSTUB(GetParameterData,				0xFF9C2814) // ok (comp 1.00h)
NHSTUB(GetZoomLensCurrentPoint,			0xFF87EE4C)	// ok (comp 1.00h)
NHSTUB(GetZoomLensCurrentPosition,		0xFF9864AC) // ok (comp 1.00h)
NHSTUB(PT_PlaySound,					0xFF88E660) // ok (comp 1.00h)
NHSTUB(ReadFastDir,						0xFFACE02C) // ok (comp 1.00h)
NHSTUB(readfastdir,						0xFFACE02C) // alias for ReadFastDir
NHSTUB(Remove,							0xFF837110) // ok (comp 1.00h)
NHSTUB(SetParameterData,				0xFF9C26EC) // ok (comp 1.00h)
NHSTUB(TurnOffBackLight,				0xFF8B059C) // ok (comp 1.00h)
NHSTUB(TurnOnBackLight,					0xFF8B0584) // ok (comp 1.00h)
NHSTUB(Lseek,							0xff8371f8) // ok (comp 1.00h)
NHSTUB(free,							0xFF814244) // ok (comp 1.00h)
NHSTUB(Close,							0xff8370dc) // ok (comp 1.00h)
NHSTUB(ExitTask,						0xff81eb30) // ok (comp 1.00h)
NHSTUB(FreeUncacheableMemory,			0xff83afd8) // ok (comp 1.00h)
NHSTUB(GetDrive_ClusterSize,			0xFF87724C) // ok (comp 1.00h)
NHSTUB(GetDrive_TotalClusters,			0xFF877280) // ok (comp 1.00h)
NHSTUB(GetDrive_FreeClusters,			0xFF8772AC) // ok (comp 1.00h)
NHSTUB(GetFocusLensSubjectDistance,		0xff97ea80) // ok (comp 1.00h)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xff97eef8) // ok (comp 1.00h)
NHSTUB(GetOpticalTemperature,			0xff869820) // ok (comp 1.00h)
NHSTUB(GetPropertyCase,					0xFF8999CC) // ok (comp 1.00h)
NHSTUB(GetSystemTime,					0xFFAEE208) // ok (comp 1.00h)
NHSTUB(IsStrobeChargeCompleted,			0xFF8EC16C) // ok (comp 1.00h)
NHSTUB(LockMainPower,					0xFF8A0294) // ok (comp 1.00h)
NHSTUB(MakeDirectory_Fut,				0xff836ac8) // ok (comp 1.00h)
NHSTUB(MoveFocusLensToDistance,			0xFFB52FB8) // ok (comp 1.00h)
NHSTUB(MoveZoomLensWithPoint,			0xFFAE96B4)	// ok (comp 1.00h)
NHSTUB(NewTaskShell,					0xff8993e8) // ok (comp 1.00h)
NHSTUB(Open,							0xFF81AADC)	// update 5/3/2011 to fix crash startup
NHSTUB(PostLogicalEventForNotPowerType, 0xff89e02c) // ok (comp 1.00h)
NHSTUB(PostLogicalEventToUI,			0xff89e078) // ok (comp 1.00h)
NHSTUB(RenameFile_Fut,					0xFF8369C0) // ok (comp 1.00h)
NHSTUB(rename,							0xFF8369C0) // same as RenameFile_Fut
NHSTUB(SetAutoShutdownTime,				0xff8a0308) // ok (comp 1.00h)
NHSTUB(SetCurrentCaptureModeType,		0xff8a922c) // ok (comp 1.00h)
NHSTUB(SetFileTimeStamp,				0xFF837378) // ok (comp 1.00h)
NHSTUB(SetLogicalEventActive,			0xff89ffd0) // ok (comp 1.00h)
NHSTUB(SetPropertyCase,					0xff8998a4) // ok (comp 1.00h)
NHSTUB(SleepTask,						0xff83ac1c) // ok (comp 1.00h)
NHSTUB(TakeSemaphore,					0xff83a8e4) // ok (comp 1.00h)
NHSTUB(UnlockMainPower,					0xff8a01e8) // ok (comp 1.00h)
NHSTUB(VbattGet,						0xFF833178) // ok (comp 1.00h)
NHSTUB(closedir,						0xFFACDE88) // ok (comp 1.00h)
NHSTUB(closefastdir,					0xFFACDE88) // same as closedir
NHSTUB(kbd_p1_f,						0xff834a68) // ok (comp 1.00h)
NHSTUB(kbd_p1_f_cont,					0xff834a74) // ok (comp 1.00h)
NHSTUB(kbd_read_keys,					0xFF8349F0) // ok (comp 1.00h)
NHSTUB(kbd_p2_f,						0xff8342b8) // ok (comp 1.00h)
NHSTUB(kbd_read_keys_r2,				0xff8651a4) // ok (comp 1.00h)
NHSTUB(lseek,							0xff8371f8) // same as Lseek
NHSTUB(mkdir,							0xff837578) // ok (comp 1.00h)
NHSTUB(opendir,							0xFFACDED8) // ok (comp 1.00h)
NHSTUB(openfastdir,						0xFFACDED8) // same as opendir
NHSTUB(reboot_fw_update,				0xFFAD344C) // ok (comp 1.00h)
NHSTUB(strcat,							0xFF8B9A20) // ok (comp 1.00h)
NHSTUB(strchr,							0xff8140b4) // ok (comp 1.00h)
NHSTUB(strlen,							0xff814100) // ok (comp 1.00h)
NHSTUB(strncpy,							0xFF81402C) // ok (comp 1.00h)
NHSTUB(strrchr,							0xFF8140D8) // ok (comp 1.00h)
NHSTUB(time,							0xff893b8c) // ok (comp 1.00h)
NHSTUB(LEDDrive,						0xFF98EE30) // ok (comp 1.00h)
NHSTUB(SetScriptMode,					0xff8a0020) // ok (comp 1.00h)
NHSTUB(UnlockAndRefresh,				0xFF8B823C) // ok (comp 1.00h)
NHSTUB(RefreshPhysicalScreen,			0xFF8B823C) // alias for UnlockAndRefresh
NHSTUB(LockAndRefresh,				    0xFF8B97DC) // ok (comp 1.00h)
NHSTUB(apex2us,							0xFFA4E9F0) // ok (comp 1.00h)
NHSTUB(WriteSDCard,						0xFF96DAB4) // ok (comp 1.00h)
NHSTUB(GetKbdState,						0xFF865A28) // ok (comp 1.00h)
NHSTUB(UnlockAF,						0xFF838AF0) // ok (comp 1.00h)
NHSTUB(DoAFLock,						0xFF838AB8) // ok (comp 1.00h)
NHSTUB(PT_MoveOpticalZoomAt,			0xFF883C08)	// ok (comp 1.00h)
NHSTUB(GetImageFolder,					0xFF95F0F0)	// function before 'GetCameraObjectTmpPath ERROR' string
NHSTUB(UpdateMBROnFlash,				0xFF8770CC) // Search for 'BOOTDISK', function branches to this at end (after setting up R0,R1,R2)
NHSTUB(PB2Rec,                          0xFF8A30FC)
NHSTUB(Rec2PB,                          0xFF8A1B40)
NHSTUB(exmem_alloc,						0xFF8944F8)	// search for ExMem.AllocCacheable (from reyalp)

# from stubs_entry_ida.S
NHSTUB(eventproc_export_PostLogicalEventToUI, 0xff89e078)
NHSTUB(eventproc_export_SleepTask, 0xff83ac1c)
NHSTUB(eventproc_export_ExitTask, 0xff81eb30)
NHSTUB(eventproc_export_TakeSemaphore, 0xff83a8e4)
NHSTUB(eventproc_export_GiveSemaphore, 0xff83a9b4)
NHSTUB(eventproc_export_HardwareDefect, 0xff8a0538)

# Misc
NHSTUB(DebugAssert,						0xFF81EB78)
NHSTUB(PT_GetPropertyCaseString,			0xFF8999CC)
NHSTUB(takeSemaphore,						0xFF83ADC4)
NHSTUB(err_init_task,						0xFF815FD4)

# Addresses for firmware task handlers (used in taskHook)
DEF(task_CaptSeq,						0xFF8868C4)
DEF(task_InitFileModules,				0xFF8A3B50)
DEF(task_RotaryEncoder,					0xFF865D08)
DEF(task_MovieRecord,					0xFF88334C)
DEF(task_ExpDrv,						0xFF8D081C)

# Missing
NHSTUB(kbd_pwr_off,						0xFF810B1C)								// ??? not on sx20 or s95
NHSTUB(kbd_pwr_on,						0xFF810B1C)								// ??? not on sx20 or s95
NSTUB(rand,								0xFF810B1C) // ??? could not find use C version from S95 wrappers
NSTUB(srand,							0xFF810B1C) // ??? could not find use C version from S95 wrappers
NHSTUB(UIFS_WriteFirmInfoToFile,		0xFF810B1C)	// Is this needed?
NHSTUB(rewinddir,						0xFF810B1C)
NHSTUB(SetZoomActuatorSpeedPercent,		0xFF810B1C)
NHSTUB(Unmount_FileSystem,				0xFF810B1C)
NHSTUB(Mount_FileSystem,				0xFF810B1C)
