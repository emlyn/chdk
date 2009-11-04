#include "stubs_asm.h"
//NHSTUB(LOLCOWS,	0xFFABCDEF)


NHSTUB(AllocateMemory, 0xFF818678)
NHSTUB(AllocateUncacheableMemory, 0xFF81E5B8)
NHSTUB(Close,	0xFFAA59F0)		// aClose
NHSTUB(CreatePhysicalVram, 0xffa3026c) // Not completely verified
NHSTUB(CreateTask, 0xffb2022c)
NHSTUB(CreateTaskStrict, 0xffb212cc)
NHSTUB(DisableDispatch, 0xffb20050) // Not completely verified
NHSTUB(DisplayImagePhysicalScreen,	0xFFA2F4C8) // Near "ImgDDev.c"
NHSTUB(EnableDispatch, 0xffb200dc) // Not completely verified
NHSTUB(ExecuteEventProcedure, 0xff814a6c)
NHSTUB(ExitTask, 0xffb205ec)
NHSTUB(Fclose_Fut, 0xffaa1138)
NHSTUB(Fopen_Fut, 0xffaa10f8)
NHSTUB(Fread_Fut, 0xffaa11f4)
NHSTUB(FreeMemory,	0xFF818664)
NHSTUB(FreeUncacheableMemory, 0xff81e5ec)
NHSTUB(Fseek_Fut, 0xffaa12e8)
NHSTUB(Fwrite_Fut, 0xffaa1248)
// NHSTUB(GetCurrentAvValue, 0xffa58520)	// aGetcurrentavva
// NHSTUB(GetCurrentTargetDistance, 0xffa5e0a8)	// aGetcurrenttarg
// NHSTUB(GetFocusLensSubjectDistance, 0xFFAE09A4)	// Wrong, corrected
// NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAE09C8)	// Wrong, corrected
NHSTUB(GetParameterData, 0xffb45910)	// Not completely verified
NHSTUB(GetPropertyCase, 0xff81bcac)	// Verified as working
NHSTUB(GetSystemTime, 0xff813700)
NHSTUB(GetZoomLensCurrentPoint, 0xffaf18cc)
NHSTUB(GetZoomLensCurrentPosition, 0xffaf18e0)
NHSTUB(IsStrobeChargeCompleted, 0xff9ae7d4) // EF.IsChargeFull
NHSTUB(LockMainPower, 0xffb42824)
NHSTUB(MakeDirectory, 0xffaa5d20)
NHSTUB(Mount_FileSystem,	0xFFAA4D14)
NHSTUB(MoveFocusLensToDistance, 0xFFAE01B8)	// MoveFocusLensWithDistance (might be wrong), corrected
NHSTUB(MoveZoomLensWithPoint, 0xffaf17a4)
NHSTUB(Open, 0xffaa59c8)	// Not completely verified
NHSTUB(PhySw_testgpio, 0xffa3b2bc)
NHSTUB(ProtectFile, 0xffaa061c)
NHSTUB(PutInNdFilter, 0xffa5bd14)	// Not completely verified
NHSTUB(PutOutNdFilter, 0xffa5bd5c)	// Not completely verified
NHSTUB(Read,		0xFFAA5A84)	// aRead
NHSTUB(RefreshPhysicalScreen, 0xff915ffc)
NHSTUB(Remove,		0xFFAA5A10)	// Not completely verified
NHSTUB(SetAutoShutdownTime, 0xFFB42728)
NHSTUB(SetParameterData, 0xffb45830)		// Not completely verified
NHSTUB(SetPropertyCase, 0xFF81BB74)	// Wrong, corrected
NHSTUB(SleepTask, 0xffb20140)		// Not completely verified
NHSTUB(TakeSemaphore, 0xffb1fbf8)		// Not completely verified
NHSTUB(UnlockMainPower, 0xffb428bc)
NHSTUB(Unmount_FileSystem, 0xffaa4dbc)		// Not completely verified
NHSTUB(UnsetZoomForMovie, 0xff8369cc)		// Not completely verified
NHSTUB(UpdateMBROnFlash, 0xffaa4f10)		// Not completely verified
NHSTUB(VbattGet, 0xffa37158)
NHSTUB(Write,		0xFFAA5A90)

NHSTUB(_log, 0xff91d198)
NHSTUB(_log10, 0xff919f40)
NHSTUB(_pow, 0xff91a0c0)
NHSTUB(_sqrt, 0xff91bf80)
NHSTUB(chdir, 0xff927c24)
NHSTUB(close, 0xff927564)
NHSTUB(closedir, 0xffb5fa38)
NHSTUB(free,		0xFF92A5B0)
NHSTUB(ints_disable, 0xffb1e2dc)
NHSTUB(ints_enable, 0xffb1e2e8)
NHSTUB(ioctl, 0xff9276a4)
NHSTUB(iosDevAdd, 0xff928784)
NHSTUB(iosDrvInstall, 0xff928a48)
NHSTUB(iosDevFind, 0xff928710)
NHSTUB(isalpha, 0xff91eb3c)
NHSTUB(isdigit, 0xff91eb6c)
NHSTUB(islower, 0xff91eb9c)
NHSTUB(isspace, 0xff91ebe4)
NHSTUB(isupper, 0xff91ebfc)
NHSTUB(kbd_p1_f, 0xffa3964c)
NHSTUB(kbd_p1_f_cont, 0xffa39658)
NHSTUB(kbd_p2_f, 0xffa39a7c)
NHSTUB(kbd_pwr_off, 0xFFA3B230)
NHSTUB(kbd_pwr_on, 0xFFA3B1F0)
NHSTUB(localtime, 0xff9233bc)
NHSTUB(lseek, 0xff9276a8)
NHSTUB(malloc, 0xff92a5a4)
NHSTUB(memcmp, 0xff92279c)
NHSTUB(memcpy, 0xff9227d8)
NHSTUB(memset, 0xff922850)
NHSTUB(mkdir, 0xffaa5c58)
NHSTUB(open, 0xff927ba8)
NHSTUB(opendir, 0xffb5fa6c)
NHSTUB(qsort, 0xff921ffc)
NHSTUB(rand, 0xff922020)
NHSTUB(read, 0xff9275c4)
NHSTUB(readdir, 0xffb5fa04)
NHSTUB(rename, 0xff927bb0)
NHSTUB(rewinddir, 0xffb5fa2c)
NHSTUB(srand, 0xff922044)
NHSTUB(stat, 0xffb5fb00)
NHSTUB(strcat, 0xff922870)
NHSTUB(strchr, 0xff92289c)
NHSTUB(strcmp, 0xff9228c0)
NHSTUB(strcpy, 0xff922a54)
NHSTUB(strlen, 0xff922bb8)
NHSTUB(strncmp, 0xff922c1c)
NHSTUB(strncpy, 0xff922c60)
NHSTUB(strpbrk, 0xff922ca8)
NHSTUB(strrchr, 0xff922ce4)
NHSTUB(strtol, 0xff922438)
NHSTUB(taskCreateHookAdd, 0xff92d204)
NHSTUB(taskDeleteHookAdd, 0xff92d140)
NHSTUB(taskIdListGet, 0xff9346ec)
NHSTUB(taskLock, 0xff934da8)
NHSTUB(taskName, 0xff9345e4)
NHSTUB(taskResume, 0xff9349c8)
NHSTUB(taskSuspend, 0xff9347f4)
NHSTUB(taskUnlock, 0xff934e50)
NHSTUB(time, 0xff924108)
NHSTUB(utime, 0xffb5fb94)
NHSTUB(vsprintf, 0xff92630c)
NHSTUB(fprintf, 0xff91f49c)
NHSTUB(fputs, 0xff91f5bc)
NHSTUB(puts, 0xFF9208B4)	// Wrong, corrected

NHSTUB(SetZoomActuatorSpeedPercent,	0xFF9B7BA8) // null
NHSTUB(GetDrive_ClusterSize,	0xFFAA51DC)	// Wrong, corrected
NHSTUB(GetDrive_TotalClusters,	0xFFAA5218)	// Wrong, corrected
NHSTUB(GetDrive_FreeClusters,	0xFFAA5254)	// Wrong, corrected
NHSTUB(kbd_read_keys_r2,	0xFFA3ACC0)


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
NHSTUB(PT_PlaySound, 0xFFB16D08)
NHSTUB(WriteSDCard, 0xFFAB7D7C)

NHSTUB(EnterToCompensationEVF, 0xffb0657c) 
NHSTUB(ExitFromCompensationEVF, 0xffb06600) 
NHSTUB(DoAFLock, 0xffb061d4)
NHSTUB(UnlockAF, 0xffb06254)
NHSTUB(SetScriptMode,0xFFB40230) // by find_eventproc name @ 0xFF81FB34
