#include "stubs_asm.h"

# Confirmed
NHSTUB(qsort,							0xFFB5FA2C)	// ok (comp s95)
NHSTUB(strtol,							0xFF840954)	// ok (comp sx30)
NHSTUB(EnterToCompensationEVF,			0xFF838D24)	// ok (comp sx30)
NHSTUB(ExitFromCompensationEVF,			0xFF838D68)	// ok (comp sx30)
NHSTUB(GetBatteryTemperature,			0xff868f80) // ok (comp sx30)
NHSTUB(GetCCDTemperature,				0xff868f0c)	// ok (comp sx30)
NHSTUB(GetCurrentAvValue,				0xff97fcb8)	// ok (comp sx30)
NHSTUB(GetParameterData,				0xFF9BECE4)	// ok (comp sx30)
NHSTUB(GetZoomLensCurrentPoint,			0xFF9819E0)	// ok (comp sx30)
NHSTUB(GetZoomLensCurrentPosition,		0xFFAF6874)	// ok (comp sx30)
NHSTUB(PT_PlaySound,					0xFF88A140)	// ok (comp sx30)
NHSTUB(ReadFastDir,						0xFFAE2C14)	// ok (comp sx30)
NHSTUB(readfastdir,						0xFFAE2C14) // alias for ReadFastDir
NHSTUB(Remove,							0xFF837114)	// ok (comp sx30)
NHSTUB(SetParameterData,				0xFF9BEBBC)	// ok (comp s95)
NHSTUB(TurnOffBackLight,				0xFF8ABD94)	// ok (comp sx30)
NHSTUB(TurnOnBackLight,					0xFF8ABD7C)	// ok (comp sx30)
NHSTUB(Lseek,							0xFF8371FC)	// ok (comp sx30)
NHSTUB(free,							0xFF814244)	// ok (comp sx30)
NHSTUB(Close,							0xff8370e0)	// ok (comp sx30)
NHSTUB(ExitTask,						0xff81eb30)	// ok (comp sx30)
NHSTUB(FreeUncacheableMemory,			0xff83af70)	// ok (comp sx30)
NHSTUB(GetDrive_ClusterSize,			0xff876948)	// ok (comp sx30)
NHSTUB(GetDrive_TotalClusters,			0xff87697c)	// ok (comp sx30)
NHSTUB(GetDrive_FreeClusters,			0xFF8769A8)	// ok (comp sx30)
NHSTUB(GetFocusLensSubjectDistance,		0xff97e348)	// ok (comp sx30)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xff97e794)	// ok (comp sx30)
NHSTUB(GetOpticalTemperature,			0xff868ff4)	// ok (comp sx30)
NHSTUB(GetPropertyCase,					0xff8954f0)	// ok (comp sx30)
NHSTUB(GetSystemTime,					0xffb08d38)	// ok (comp sx30)
NHSTUB(IsStrobeChargeCompleted,			0xff8ea5f0)	// ok (comp sx30)
NHSTUB(LockMainPower,					0xff89c204)	// ok (comp sx30)
NHSTUB(MakeDirectory_Fut,				0xff836acc)	// ok (comp sx30)
NHSTUB(MoveFocusLensToDistance,			0xffb71f98)	// ok (comp sx30)
NHSTUB(MoveZoomLensWithPoint,			0xffb05008)	// ok (comp sx30)
NHSTUB(NewTaskShell,					0xff894f0c)	// ok (comp sx30)
NHSTUB(Open,							0xFF873BFC)	// ok (comp sx30)
NHSTUB(PostLogicalEventForNotPowerType, 0xff899b70)	// ok (comp sx30)
NHSTUB(PostLogicalEventToUI,			0xff899bbc)	// ok (comp sx30)
NHSTUB(RenameFile_Fut,					0xFF8369C4)	// ok (comp sx30)
NHSTUB(rename,							0xFF8369C4) // same as RenameFile_Fut
NHSTUB(SetAutoShutdownTime,				0xff89c278)	// ok (comp sx30)
NHSTUB(SetCurrentCaptureModeType,		0xff8a4d44)	// ok (comp sx30)
NHSTUB(SetFileTimeStamp,				0xFF83737C)	// ok (comp sx30)
NHSTUB(SetLogicalEventActive,			0xff89bf40)	// ok (comp sx30)
NHSTUB(SetPropertyCase,					0xff8953c8)	// ok (comp sx30)
NHSTUB(SleepTask,						0xff83abb4)	// ok (comp sx30)
NHSTUB(TakeSemaphore,					0xff83a87c)	// ok (comp sx30)
NHSTUB(UnlockMainPower,					0xff89c158)	// ok (comp sx30)
NHSTUB(VbattGet,						0xff833180)	// ok (comp sx30)
NHSTUB(closedir,						0xFFAE2A70)	// ok (comp sx30)
NHSTUB(closefastdir,					0xFFAE2A70) // same as closedir
NHSTUB(kbd_p1_f,						0xff834a6c)	// ok (comp sx30)
NHSTUB(kbd_p1_f_cont,					0xff834a78)	// ok (comp sx30)
NHSTUB(kbd_read_keys,					0xFF8349F4)	// ok (comp sx30)
NHSTUB(kbd_p2_f,						0xff8342bc)	// ok (comp sx30)
NHSTUB(kbd_read_keys_r2,				0xFF864D8C)	// ok (comp sx30)
NHSTUB(lseek,							0xFF8371FC) // same as Lseek
NHSTUB(mkdir,							0xff83757c)	// ok (comp sx30)
NHSTUB(opendir,							0xffae2ac0)	// ok (comp sx30)
NHSTUB(openfastdir,						0xffae2ac0) // same as opendir
NHSTUB(reboot_fw_update,				0xffae8034)	// ok (comp sx30)
NHSTUB(strcat,							0xFF8B5328)	// ok (comp sx30)
NHSTUB(strchr,							0xff8140b4)	// ok (comp sx30)
NHSTUB(strlen,							0xFF814100)	// ok (comp sx30)
NHSTUB(strncpy,							0xff81402c)	// ok (comp sx30)
NHSTUB(strrchr,							0xFF8140D8)	// ok (comp sx30)
NHSTUB(time,							0xff88f66c)	// ok (comp sx30)
NHSTUB(MakeAFScan,						0xFF98AA04)	// ok (comp s95)
NHSTUB(ExpCtrlTool_StartContiAE,		0xFF8475EC)	// ok (comp s95)
NHSTUB(UnsetZoomForMovie,				0xFF9C57D0)	// ok (comp s95)
NHSTUB(LEDDrive,						0xFF8647EC)	// ok (comp sx30)
NHSTUB(SetScriptMode,					0xFF89BF90)	// ok (comp sx30)
NHSTUB(UnlockAndRefresh,				0xFF8B3A68)	// ok (comp sx30)
NHSTUB(RefreshPhysicalScreen,			0xFF8B3A68) // alias for UnlockAndRefresh
NHSTUB(LockAndRefresh,				    0xFF8B50E4)	// ok (comp sx30)
NHSTUB(ScreenLock,						0xFF8B4C98)	// ??? S95
NHSTUB(ScreenUnlock,					0xFF8B4CFC)	// ??? S95
NHSTUB(apex2us,							0xFFA5C23C)	// ok (comp sx30)
NHSTUB(WriteSDCard,						0xFF96E820)	// ok (comp sx30)
NHSTUB(GetKbdState,						0xFF865678)	// ok (called in kbd_read_keys)
NHSTUB(UnlockAF,						0xFF838978)	// ok (comp sx30)
NHSTUB(DoAFLock,						0xFF838940)	// ok (comp sx30)
NHSTUB(GetImageFolder,					0xFF95F2FC)	// function before 'GetCameraObjectTmpPath ERROR' string
NHSTUB(UpdateMBROnFlash,				0xFF8767C8) // Search for 'BOOTDISK', function branches to this at end (after setting up R0,R1,R2)
NHSTUB(exmem_alloc,						0xFF88FFD8)	// search for ExMem.AllocCacheable (from reyalp)

# From stubs_entry_ida.s
NHSTUB(_eventproc_export_PostLogicalEventToUI, 0xff899bbc)
NHSTUB(_eventproc_export_SleepTask, 0xff83abb4)
NHSTUB(_eventproc_export_ExitTask, 0xff81eb30)
NHSTUB(_eventproc_export_TakeSemaphore, 0xff83a87c)
NHSTUB(_eventproc_export_HardwareDefect, 0xff89c4a8)

# Misc - needs a stub anyway, to far for B/BL
NTHSTUB(_DebugAssert,						0xFF81EB78)
NTHSTUB(_PT_GetPropertyCaseString,			0xFF8954F0)
NTHSTUB(_takeSemaphore,						0xFF83AD5C)
NTHSTUB(_err_init_task,						0xFF815FD4)

# Addresses for firmware task handlers (used in taskHook)
DEF(task_CaptSeq,						0xFF88261C)
DEF(task_InitFileModules,				0xFF89FC7C)
DEF(task_RotaryEncoder,					0xFF8657EC)
DEF(task_MovieRecord,					0xFF987088)
DEF(task_ExpDrv,						0xFF8CC0D0)

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
