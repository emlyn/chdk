#include "stubs_asm.h"
//NHSTUB(LOLCOWS,	0xFFABCDEF)


NHSTUB(AllocateMemory, 0xFF818678)		// Verified
NHSTUB(AllocateUncacheableMemory, 0xFF81E5B8)		// Verified
NHSTUB(Close,	0xFFAA59F0)		// aClose, GOD DAMMIT
NHSTUB(CreatePhysicalVram, 0xFFA3026C) // Pattern matched with 101a
NHSTUB(CreateTask, 0xFFB202AC)		// Verified
NHSTUB(CreateTaskStrict, 0xFFB2134C)		// Verified
NHSTUB(DisableDispatch, 0xFFB200D0) 	// Pattern matched with 101a
NHSTUB(DisplayImagePhysicalScreen,	0xFFA2F4C8) 	// Pattern matched with 101a
NHSTUB(EnableDispatch, 0xFFB2015C) 	// Pattern matched with 101a
NHSTUB(ExecuteEventProcedure, 0xFF814A6C)		// Verified
NHSTUB(ExitTask, 0xFFB2066C) 	// Pattern matched with 101a
NHSTUB(Fclose_Fut, 0xFFAA1138) 	// Pattern matched with 101a
NHSTUB(Fopen_Fut, 0xFFAA10F8) 	// Pattern matched with 101a
NHSTUB(Fread_Fut, 0xFFAA11F4) 	// Pattern matched with 101a
NHSTUB(FreeMemory,	0xFF818664)		// Verified
NHSTUB(FreeUncacheableMemory, 0xFF81E5EC)		// Verified
NHSTUB(Fseek_Fut, 0xFFAA12E8) 	// Pattern matched with 101a
NHSTUB(Fwrite_Fut, 0xFFAA1248) 	// Pattern matched with 101a
NHSTUB(GetCurrentAvValue, 0xffa5bb30)	// stubs_entry.s WRONG, corrected
NHSTUB(GetCurrentTargetDistance, 0xffa5e0a8)	// stubs_entry.s WRONG, corrected
NHSTUB(GetFocusLensSubjectDistance, 0xFFAE09A4)	// stubs_entry.s WRONG, corrected
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAE09C8)	// stubs_entry.s WRONG, corrected
NHSTUB(GetParameterData, 0xFFB45990) 	// Pattern matched with 101a
NHSTUB(GetPropertyCase, 0xFF81BCAC) 	// Pattern matched with 101a
NHSTUB(GetSystemTime, 0xFF813700)		// Verified
NHSTUB(GetZoomLensCurrentPoint, 0xFFAF18DC)		// Verified
NHSTUB(GetZoomLensCurrentPosition, 0xFFAF18F0)		// Verified
NHSTUB(IsStrobeChargeCompleted, 0xFF9AE7D4) 	// Pattern matched with 101a
NHSTUB(LockMainPower, 0xFFB428A4)		// Verified
NHSTUB(MakeDirectory, 0xFFAA5D20) 	// Pattern matched with 101a
NHSTUB(Mount_FileSystem,	0xFFAA4D14) 	// Pattern matched with 101a
NHSTUB(MoveFocusLensToDistance, 0xFFAE01B8)	// MoveFocusLensWithDistance (might be wrong), corrected
NHSTUB(MoveZoomLensWithPoint, 0xFFAF17B4)		// Verified
NHSTUB(Open, 0xFFAA59C8) 	// Pattern matched with 101a
NHSTUB(PhySw_testgpio, 0xFFA3B2BC) 	// Pattern matched with 101a
NHSTUB(ProtectFile, 0xFFAA061C) 	// Pattern matched with 101a
NHSTUB(PutInNdFilter, 0xFFA5BD14) 	// Pattern matched with 101a
NHSTUB(PutOutNdFilter, 0xFFA5BD5C) 	// Pattern matched with 101a
NHSTUB(Read,		0xFFAA5A84) 	// Pattern matched with 101a
NHSTUB(RefreshPhysicalScreen, 0xFF915FFC) 	// Pattern matched with 101a
NHSTUB(Remove,		0xFFAA5A10) 	// Pattern matched with 101a
NHSTUB(SetAutoShutdownTime, 0xFFB427A8)		// Verified
NHSTUB(SetParameterData, 0xFFB458B0) 	// Pattern matched with 101a
NHSTUB(SetPropertyCase, 0xFF81BB74) 	// Pattern matched with 101a
NHSTUB(SleepTask, 0xFFB201C0) 	// Pattern matched with 101a
NHSTUB(TakeSemaphore, 0xFFB1FC78) 	// Pattern matched with 101a
NHSTUB(UnlockMainPower, 0xFFB4293C)		// Verified
NHSTUB(Unmount_FileSystem, 0xFFAA4DBC) 	// Pattern matched with 101a
NHSTUB(UnsetZoomForMovie, 0xFF8369CC) 	// Pattern matched with 101a
NHSTUB(UpdateMBROnFlash, 0xFFAA4F10) 	// Pattern matched with 101a
NHSTUB(VbattGet, 0xFFA37158)		// Verified
NHSTUB(Write,		0xFFAA5A90) 	// Pattern matched with 101a

NHSTUB(_log, 0xff91d198)		// Verified
NHSTUB(_log10, 0xff919f40)		// Verified
NHSTUB(_pow, 0xff91a0c0)		// Verified
NHSTUB(_sqrt, 0xff91bf80)		// Verified
NHSTUB(chdir, 0xff927c24) 	// Pattern matched with 101a
NHSTUB(close, 0xff927564)		// Verified
NHSTUB(closedir, 0xFFB5FAB8) 	// Pattern matched with 101a
NHSTUB(free,		0xFF92A5B0) 	// Pattern matched with 101a
NHSTUB(ints_disable, 0xFFB1E35C) 	// Pattern matched with 101a
NHSTUB(ints_enable, 0xFFB1E368) 	// Pattern matched with 101a
NHSTUB(ioctl, 0xff9276a4)		// Verified
NHSTUB(iosDevAdd, 0xff928784)		// Verified
NHSTUB(iosDrvInstall, 0xff928a48)		// Verified
NHSTUB(iosDevFind, 0xff928710)		// Verified
NHSTUB(isalpha, 0xff91eb3c)		// Verified
NHSTUB(isdigit, 0xff91eb6c)		// Verified
NHSTUB(islower, 0xff91eb9c)		// Verified
NHSTUB(isspace, 0xff91ebe4)		// Verified
NHSTUB(isupper, 0xff91ebfc)		// Verified
NHSTUB(kbd_p1_f, 0xffa3964c) 	// Pattern matched with 101a
NHSTUB(kbd_p1_f_cont, 0xffa39658) 	// Pattern matched with 101a
NHSTUB(kbd_p2_f, 0xffa39a7c) 	// Pattern matched with 101a
NHSTUB(kbd_pwr_off, 0xFFA3B230) 	// Pattern matched with 101a
NHSTUB(kbd_pwr_on, 0xFFA3B1F0) 	// Pattern matched with 101a
NHSTUB(localtime, 0xff9233bc) 	// Pattern matched with 101a
NHSTUB(lseek, 0xff9276a8)		// Verified
NHSTUB(malloc, 0xff92a5a4) 	// Pattern matched with 101a
NHSTUB(memcmp, 0xff92279c)		// Verified
NHSTUB(memcpy, 0xff9227d8)		// Verified
NHSTUB(memset, 0xff922850)		// Verified
NHSTUB(mkdir, 0xffaa5c58) 	// Pattern matched with 101a
NHSTUB(open, 0xff927ba8) 	// Pattern matched with 101a
NHSTUB(opendir, 0xFFB5FAEC) 	// Pattern matched with 101a
NHSTUB(qsort, 0xff921ffc)		// Verified
NHSTUB(rand, 0xff922020)		// Verified
NHSTUB(read, 0xff9275c4) 	// Pattern matched with 101a
NHSTUB(readdir, 0xFFB5FA84) 	// Pattern matched with 101a
NHSTUB(rename, 0xff927bb0)		// Verified
NHSTUB(rewinddir, 0xFFB5FAAC) 	// Pattern matched with 101a
NHSTUB(srand, 0xff922044) 	// Pattern matched with 101a
NHSTUB(stat, 0xFFB5FB80) 	// Pattern matched with 101a
NHSTUB(strcat, 0xff922870)		// Verified
NHSTUB(strchr, 0xff92289c)		// Verified
NHSTUB(strcmp, 0xff9228c0)		// Verified
NHSTUB(strcpy, 0xff922a54)		// Verified
NHSTUB(strlen, 0xff922bb8)		// Verified
NHSTUB(strncmp, 0xff922c1c)		// Verified
NHSTUB(strncpy, 0xff922c60)		// Verified
NHSTUB(strpbrk, 0xff922ca8)		// Verified
NHSTUB(strrchr, 0xff922ce4)		// Verified
NHSTUB(strtol, 0xff922438)		// Verified
NHSTUB(taskCreateHookAdd, 0xff92d204) 	// Pattern matched with 101a
NHSTUB(taskDeleteHookAdd, 0xff92d140)		// Verified
NHSTUB(taskIdListGet, 0xff9346ec)		// Verified
NHSTUB(taskLock, 0xff934da8)		// Verified
NHSTUB(taskName, 0xff9345e4)		// Verified
NHSTUB(taskResume, 0xff9349c8)		// Verified
NHSTUB(taskSuspend, 0xff9347f4)		// Verified
NHSTUB(taskUnlock, 0xff934e50)		// Verified
NHSTUB(time, 0xff924108)		// Verified
NHSTUB(utime, 0xFFB5FC14) 	// Pattern matched with 101a
NHSTUB(vsprintf, 0xff92630c)		// Verified
NHSTUB(fprintf, 0xff91f49c)		// Verified
NHSTUB(fputs, 0xff91f5bc)		// Verified
NHSTUB(puts, 0xFF9208B4)		// Verified

NHSTUB(SetZoomActuatorSpeedPercent,	0xFF9B7BA8) // null
NHSTUB(GetDrive_ClusterSize,	0xFFAA51DC) 	// Pattern matched with 101a
NHSTUB(GetDrive_TotalClusters,	0xFFAA5218) 	// Pattern matched with 101a
NHSTUB(GetDrive_FreeClusters,	0xFFAA5254) 	// Pattern matched with 101a
NHSTUB(kbd_read_keys_r2,	0xFFA3ACC0) 	// Pattern matched with 101a


/*
NHSTUB(Close,		0xFFAA59F0)
NHSTUB(Mount_FileSystem,	0xFFAA4D14)
NHSTUB(AllocateMemory,	0xFF818678)
//NHSTUB(GetFreeCardSpaceKb,	0xFF9B7BA8) // null
//NHSTUB(GetTotalCardSpaceKb,	0xFF9B7BA8) // null
*/
NHSTUB(GetBatteryTemperature, 0xFFA3FCBC)
NHSTUB(GetCCDTemperature, 0xFFA3FCA8)
NHSTUB(GetOpticalTemperature, 0xFFA3FC94)
NHSTUB(PT_PlaySound, 0xFFB16D88)
NHSTUB(EnterToCompensationEVF, 0xff978b78) // not found yet
NHSTUB(ExitFromCompensationEVF, 0xff978bd8) // not found yet
