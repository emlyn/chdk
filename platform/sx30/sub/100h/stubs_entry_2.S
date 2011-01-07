#include "stubs_asm.h"

# Confirmed
NHSTUB(qsort,							0xFFB4065C) // ok (comp s95)
NHSTUB(strtol,							0xFF840A30) // ok (comp sx20)
NHSTUB(EnterToCompensationEVF,			0xFF838D44) // ok (comp sx20)
NHSTUB(ExitFromCompensationEVF,			0xFF838D88) // ok (comp sx20)
NHSTUB(GetBatteryTemperature,			0xFF8697AC) // probable (comp sx20)
NHSTUB(GetCCDTemperature,				0xFF869738) // probable (comp sx20)
NHSTUB(GetCurrentAvValue,				0xFF98067C) // possible (comp sx20)
NHSTUB(GetParameterData,				0xFF9C266C) // probable (comp sx20)
NHSTUB(GetZoomLensCurrentPoint,			0xFF87E9C4)	// ok
NHSTUB(GetZoomLensCurrentPosition,		0xFF9864A8) // ok
NHSTUB(PT_PlaySound,					0xFF88E65C) // ok (comp s95)
NHSTUB(ReadFastDir,						0xFFACDE84) // ok (comp s95)
NHSTUB(readfastdir,						0xFFACDE84) // alias for ReadFastDir
NHSTUB(Remove,							0xFF837110) // ok (comp s95)
NHSTUB(SetParameterData,				0xFF9C2544) // probable (comp sx20)
NHSTUB(TurnOffBackLight,				0xFF8B0598) // ok (comp s95)
NHSTUB(TurnOnBackLight,					0xFF8B0580) // ok (comp s95)
NHSTUB(Lseek,							0xff8371f8) // ok
NHSTUB(free,							0xFF814244) // looks ok (comp S95)
NHSTUB(Close,							0xff8370dc) // ok
NHSTUB(ExitTask,						0xff81eb30) // ok
NHSTUB(FreeUncacheableMemory,			0xff83afd8) // ok
NHSTUB(GetDrive_ClusterSize,			0xFF87724C) // ok (comp sx20 / s95)
NHSTUB(GetDrive_TotalClusters,			0xFF877280) // ok (comp sx20 / s95)
NHSTUB(GetDrive_FreeClusters,			0xFF8772AC) // ok (comp sx20 / s95)
NHSTUB(GetFocusLensSubjectDistance,		0xff97ea7c) // looks ok (comp sx20 / s95)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xff97eef4) // looks ok (comp sx20 / s95)
NHSTUB(GetOpticalTemperature,			0xff869820) // looks ok (comp sx20 / s95)
NHSTUB(GetPropertyCase,					0xff8999c8) // ok (comp sx20 / s95)
NHSTUB(GetSystemTime,					0xffaee060) // ok (comp sx20)
NHSTUB(IsStrobeChargeCompleted,			0xff8ec168) // ok (comp sx20 / s95)
NHSTUB(LockMainPower,					0xff8a0290) // ok (comp sx20)
NHSTUB(MakeDirectory_Fut,				0xff836ac8) // ok (comp sx20)
NHSTUB(MoveFocusLensToDistance,			0xffb52e10) // ok (comp sx20 / s95)
NHSTUB(MoveZoomLensWithPoint,			0xffae950c)	// ok (from function table @FFC4F0AC)
NHSTUB(NewTaskShell,					0xff8993e4) // ok (comp sx20)
NHSTUB(Open,							0xff874500) // ok
NHSTUB(PostLogicalEventForNotPowerType, 0xff89e028) // ok (comp sx20)
NHSTUB(PostLogicalEventToUI,			0xff89e074) // ok
NHSTUB(RenameFile_Fut,					0xFF8369C0) // ok (comp sx20)
NHSTUB(rename,							0xFF8369C0) // same as RenameFile_Fut
NHSTUB(SetAutoShutdownTime,				0xff8a0304) // ok (comp sx20)
NHSTUB(SetCurrentCaptureModeType,		0xff8a9228) // ok (comp sx20)
NHSTUB(SetFileTimeStamp,				0xFF837378) // ok (comp s95)
NHSTUB(SetLogicalEventActive,			0xff89ffcc) // ok (comp s95)
NHSTUB(SetPropertyCase,					0xff8998a0) // probable (comp sx20 / s95)
NHSTUB(SleepTask,						0xff83ac1c) // ok
NHSTUB(TakeSemaphore,					0xff83a8e4) // ok (comp sx20)
NHSTUB(UnlockMainPower,					0xff8a01e4) // ok (comp sx20)
NHSTUB(VbattGet,						0xFF833178) // ok (comp s95)
NHSTUB(closedir,						0xFFACDCE0) // ok (comp s95)
NHSTUB(closefastdir,					0xFFACDCE0) // same as closedir
NHSTUB(kbd_p1_f,						0xff834a68) // ok (comp sx20)
NHSTUB(kbd_p1_f_cont,					0xff834a74) // ok (comp sx20)
NHSTUB(kbd_read_keys,					0xFF8349F0) // ok
NHSTUB(kbd_p2_f,						0xff8342b8) // ok (comp sx20)
NHSTUB(kbd_read_keys_r2,				0xff8651a4) // ok (comp sx20)
NHSTUB(lseek,							0xff8371f8) // same as Lseek
NHSTUB(mkdir,							0xff837578) // ok (comp sx20)
NHSTUB(opendir,							0xffacdd30) // ok (comp sx20)
NHSTUB(openfastdir,						0xffacdd30) // same as opendir
NHSTUB(reboot_fw_update,				0xffad32a4) // ok (comp sx20)
NHSTUB(strcat,							0xFF8B9A1C) // ok
NHSTUB(strchr,							0xff8140b4) // ok
NHSTUB(strlen,							0xff814100) // ok
NHSTUB(strncpy,							0xFF81402C) // ok
NHSTUB(strrchr,							0xFF8140D8) // ok
NHSTUB(time,							0xff893b88) // ok
NHSTUB(LEDDrive,						0xff98ec88) // ok
NHSTUB(SetScriptMode,					0xff8a001c) // ok
NHSTUB(UnlockAndRefresh,				0xFF8B8238) // seems to work
NHSTUB(RefreshPhysicalScreen,			0xFF8B8238) // alias for UnlockAndRefresh
NHSTUB(LockAndRefresh,				    0xFF8B97D8) // seems to work
NHSTUB(apex2us,							0xFFA4E848) // ok (comp sx20)
NHSTUB(WriteSDCard,						0xFF96DAB0)	// ok (comp sx20)
NHSTUB(GetKbdState,						0xFF865A28) // ok (comp sx20)
NHSTUB(UnlockAF,						0xFF838AF0) // ok (comp sx20 / s95)
NHSTUB(DoAFLock,						0xFF838AB8) // ok (comp sx20 / s95)
NHSTUB(PT_MoveOpticalZoomAt,			0xFF883C04)	// found in table @ FFB99054
NHSTUB(GetImageFolder,					0xFF95F0EC)	// function before 'GetCameraObjectTmpPath ERROR' string
NHSTUB(UpdateMBROnFlash,				0xFF8770CC) // Search for 'BOOTDISK', function branches to this at end (after setting up R0,R1,R2)
NHSTUB(PB2Rec,                          0xFF8A30F8)
NHSTUB(Rec2PB,                          0xFF8A1B3C)
NHSTUB(exmem_alloc,						0xFF8944F4)	// search for ExMem.AllocCacheable (from reyalp)

# from stubs_entry_ida.S (only used in ARM code so do not need stub)
DEF(_eventproc_export_PostLogicalEventToUI, 0xff89e074)
DEF(_eventproc_export_SleepTask, 0xff83ac1c)
DEF(_eventproc_export_ExitTask, 0xff81eb30)
DEF(_eventproc_export_TakeSemaphore, 0xff83a8e4)
DEF(_eventproc_export_GiveSemaphore, 0xff83a9b4)
DEF(_eventproc_export_HardwareDefect, 0xff8a0534)

# Misc (only used in ARM code so do not need stub)
DEF(_DebugAssert,						0xFF81EB78)
DEF(_PT_GetPropertyCaseString,			0xFF8999C8)
DEF(_takeSemaphore,						0xFF83ADC4)
DEF(_err_init_task,						0xFF815FD4)

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
