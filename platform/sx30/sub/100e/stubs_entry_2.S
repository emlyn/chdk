#include "stubs_asm.h"

# Confirmed
NHSTUB(qsort,							0xFFB405A0) // ok (comp 1.00h)
NHSTUB(strtol,							0xFF840A30) // ok (comp 1.00h)
NHSTUB(EnterToCompensationEVF,			0xFF838D44) // ok (comp 1.00h)
NHSTUB(ExitFromCompensationEVF,			0xFF838D88) // ok (comp 1.00h)
NHSTUB(GetBatteryTemperature,			0xFF8697AC) // ok (comp 1.00h)
NHSTUB(GetCCDTemperature,				0xFF869738) // ok (comp 1.00h)
NHSTUB(GetCurrentAvValue,				0xFF980648) // ok (comp 1.00h)
NHSTUB(GetParameterData,				0xFF9C25E0) // ok (comp 1.00h)
NHSTUB(GetZoomLensCurrentPoint,			0xFF87EE4C)	// ok (comp 1.00h)
NHSTUB(GetZoomLensCurrentPosition,		0xFF986474) // ok (comp 1.00h)
NHSTUB(PT_PlaySound,					0xFF88E65C) // ok (comp 1.00h)
NHSTUB(ReadFastDir,						0xFFACDDC8) // ok (comp 1.00h)
NHSTUB(readfastdir,						0xFFACDDC8) // alias for ReadFastDir
NHSTUB(Remove,							0xFF837110) // ok (comp 1.00h)
NHSTUB(SetParameterData,				0xFF9C24B8) // ok (comp 1.00h)
NHSTUB(TurnOffBackLight,				0xFF8B0598) // ok (comp 1.00h)
NHSTUB(TurnOnBackLight,					0xFF8B0580) // ok (comp 1.00h)
NHSTUB(Lseek,							0xff8371f8) // ok (comp 1.00h)
NHSTUB(free,							0xFF814244) // ok (comp 1.00h)
NHSTUB(Close,							0xff8370dc) // ok (comp 1.00h)
NHSTUB(ExitTask,						0xff81eb30) // ok (comp 1.00h)
NHSTUB(FreeUncacheableMemory,			0xff83afd8) // ok (comp 1.00h)
NHSTUB(GetDrive_ClusterSize,			0xFF87724C) // ok (comp 1.00h)
NHSTUB(GetDrive_TotalClusters,			0xFF877280) // ok (comp 1.00h)
NHSTUB(GetDrive_FreeClusters,			0xFF8772AC) // ok (comp 1.00h)
NHSTUB(GetFocusLensSubjectDistance,		0xFF97EA48) // ok (comp 1.00h)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFF97EEC0) // ok (comp 1.00h)
NHSTUB(GetOpticalTemperature,			0xff869820) // ok (comp 1.00h)
NHSTUB(GetPropertyCase,					0xff8999c8) // ok (comp 1.00h)
NHSTUB(GetSystemTime,					0xFFAEDFA4) // ok (comp 1.00h)
NHSTUB(IsStrobeChargeCompleted,			0xff8ec168) // ok (comp 1.00h)
NHSTUB(LockMainPower,					0xff8a0290) // ok (comp 1.00h)
NHSTUB(MakeDirectory_Fut,				0xff836ac8) // ok (comp 1.00h)
NHSTUB(MoveFocusLensToDistance,			0xFFB52D54) // ok (comp 1.00h)
NHSTUB(MoveZoomLensWithPoint,			0xFFAE9450)	// ok (comp 1.00h) (from function table @FFC4EFF0)
NHSTUB(NewTaskShell,					0xff8993e4) // ok (comp 1.00h)
NHSTUB(Open,							0xff874500) // ok (comp 1.00h)
NHSTUB(PostLogicalEventForNotPowerType, 0xff89e028) // ok (comp 1.00h)
NHSTUB(PostLogicalEventToUI,			0xff89e074) // ok (comp 1.00h)
NHSTUB(RenameFile_Fut,					0xFF8369C0) // ok (comp 1.00h)
NHSTUB(rename,							0xFF8369C0) // same as RenameFile_Fut
NHSTUB(SetAutoShutdownTime,				0xff8a0304) // ok (comp 1.00h)
NHSTUB(SetCurrentCaptureModeType,		0xff8a9228) // ok (comp 1.00h)
NHSTUB(SetFileTimeStamp,				0xFF837378) // ok (comp 1.00h)
NHSTUB(SetLogicalEventActive,			0xff89ffcc) // ok (comp 1.00h)
NHSTUB(SetPropertyCase,					0xff8998a0) // ok (comp 1.00h)
NHSTUB(SleepTask,						0xff83ac1c) // ok (comp 1.00h)
NHSTUB(TakeSemaphore,					0xff83a8e4) // ok (comp 1.00h)
NHSTUB(UnlockMainPower,					0xff8a01e4) // ok (comp 1.00h)
NHSTUB(VbattGet,						0xFF833178) // ok (comp 1.00h)
NHSTUB(closedir,						0xFFACDC24) // ok (comp 1.00h)
NHSTUB(closefastdir,					0xFFACDC24) // same as closedir
NHSTUB(kbd_p1_f,						0xff834a68) // ok (comp 1.00h)
NHSTUB(kbd_p1_f_cont,					0xff834a74) // ok (comp 1.00h)
NHSTUB(kbd_read_keys,					0xFF8349F0) // ok (comp 1.00h
NHSTUB(kbd_p2_f,						0xff8342b8) // ok (comp 1.00h)
NHSTUB(kbd_read_keys_r2,				0xff8651a4) // ok (comp 1.00h)
NHSTUB(lseek,							0xff8371f8) // same as Lseek
NHSTUB(mkdir,							0xff837578) // ok (comp 1.00h)
NHSTUB(opendir,							0xFFACDC74) // ok (comp 1.00h)
NHSTUB(openfastdir,						0xFFACDC74) // same as opendir
NHSTUB(reboot_fw_update,				0xFFAD31E8) // ok (comp 1.00h)
NHSTUB(strcat,							0xFF8B9A1C) // ok (comp 1.00h)
NHSTUB(strchr,							0xff8140b4) // ok (comp 1.00h)
NHSTUB(strlen,							0xff814100) // ok (comp 1.00h)
NHSTUB(strncpy,							0xFF81402C) // ok (comp 1.00h)
NHSTUB(strrchr,							0xFF8140D8) // ok (comp 1.00h)
NHSTUB(time,							0xff893b88) // ok (comp 1.00h)
NHSTUB(LEDDrive,						0xFF98EC54) // ok (comp 1.00h)
NHSTUB(SetScriptMode,					0xff8a001c)	// ok (comp 1.00h)
NHSTUB(UnlockAndRefresh,				0xFF8B8238) // ok (comp 1.00h)
NHSTUB(RefreshPhysicalScreen,			0xFF8B8238) // alias for UnlockAndRefresh
NHSTUB(LockAndRefresh,				    0xFF8B97D8) // ok (comp 1.00h)
NHSTUB(apex2us,							0xFFA4E78C) // ok (comp 1.00h)
NHSTUB(WriteSDCard,						0xFF96DA7C) // ok (comp 1.00h)
NHSTUB(GetKbdState,						0xFF865A28) // ok (comp 1.00h)
NHSTUB(UnlockAF,						0xFF838AF0) // ok (comp 1.00h)
NHSTUB(DoAFLock,						0xFF838AB8) // ok (comp 1.00h)
NHSTUB(PT_MoveOpticalZoomAt,			0xFF883C04)	// ok (comp 1.00h) (found in table @ FFB98F98)
NHSTUB(GetImageFolder,					0xFF95F0B8)	// function before 'GetCameraObjectTmpPath ERROR' string
NHSTUB(UpdateMBROnFlash,				0xFF8770CC) // Search for 'BOOTDISK', function branches to this at end (after setting up R0,R1,R2)
NHSTUB(PB2Rec,                          0xFF8A30F8)
NHSTUB(Rec2PB,                          0xFF8A1B3C)
NHSTUB(exmem_alloc,						0xFF8944F4)	// search for ExMem.AllocCacheable (from reyalp)

# from stubs_entry_ida.S
NHSTUB(eventproc_export_PostLogicalEventToUI, 0xff89e074)
NHSTUB(eventproc_export_SleepTask, 0xff83ac1c)
NHSTUB(eventproc_export_ExitTask, 0xff81eb30)
NHSTUB(eventproc_export_TakeSemaphore, 0xff83a8e4)
NHSTUB(eventproc_export_GiveSemaphore, 0xff83a9b4)
NHSTUB(eventproc_export_HardwareDefect, 0xff8a0534)

# Misc
NHSTUB(DebugAssert,						0xFF81EB78)
NHSTUB(PT_GetPropertyCaseString,			0xFF8999C8)
NHSTUB(takeSemaphore,						0xFF83ADC4)
NHSTUB(err_init_task,						0xFF815FD4)

# Addresses for firmware task handlers (used in taskHook)
DEF(task_CaptSeq,						0xFF8868C0)
DEF(task_InitFileModules,				0xFF8A3B4C)
DEF(task_RotaryEncoder,					0xFF865D08)
DEF(task_MovieRecord,					0xFF883348)
DEF(task_ExpDrv,						0xFF8D0818)

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
