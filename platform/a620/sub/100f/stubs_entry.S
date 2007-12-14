// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

NSTUB(AllocateMemory, 0xffc01b1c)
NSTUB(AllocateUncacheableMemory, 0xffc048d8)
NSTUB(Close, 0xffc5ce8c)
NSTUB(CreatePhysicalVram, 0xffd12304)
NSTUB(CreateTask, 0xffc11230)
NSTUB(CreateTaskStrict, 0xffc12398)
NSTUB(DisableDispatch, 0xffc11054)
NSTUB(DisplayImagePhysicalScreen, 0xffd116cc)
NSTUB(EnableDispatch, 0xffc110e0)
NSTUB(ExecuteEventProcedure, 0xffc067f0)
NSTUB(ExitTask, 0xffc115f0)
NSTUB(FreeMemory, 0xffc01b28)
NSTUB(FreeUncacheableMemory, 0xffc0490c)
NSTUB(GetCurrentAvValue, 0xffe77ff0)
// ALT: NSTUB(GetCurrentAvValue, 0xffe7a3f0) // 13/0
NSTUB(GetCurrentTargetDistance, 0xffe7a398)
// Best match: 96%
NSTUB(GetFocusLensSubjectDistance, 0xffe6d4ac)
//ARM BEGIN
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xffe6da4c)
//NSTUB(GetFlashLightValue, 0xffe8538c)
//NSTUB(Setcdsgainapex, 0xffe77a70)
//ARM END
NSTUB(GetParameterData, 0xffd4f350)
NSTUB(GetPropertyCase, 0xffc14188)
NSTUB(GetSystemTime, 0xffc04b10)
// Best match: 93%
NSTUB(GetZoomLensCurrentPoint, 0xffe59d18)
// ALT: NSTUB(GetZoomLensCurrentPoint, 0xffe59d18) // 27/2
// Best match: 93%
NSTUB(GetZoomLensCurrentPosition, 0xffe59d2c)
// ALT: NSTUB(GetZoomLensCurrentPosition, 0xffe59d2c) // 27/2
NSTUB(IsStrobeChargeCompleted, 0xffcec238)
// Best match: 96%
NSTUB(LockMainPower, 0xffd49d9c)
NSTUB(MakeDirectory, 0xffc5d130)
// Best match: 90%
NSTUB(Mount_FileSystem, 0xffc5c140)
// ALT: NSTUB(Mount_FileSystem, 0xffc5c140) // 27/3
// Best match: 96%
NSTUB(MoveFocusLensToDistance, 0xffe7a628)
NSTUB(MoveZoomLensWithPoint, 0xffe59bf8)
// ALT: NSTUB(MoveZoomLensWithPoint, 0xffe59bf8) // 25/0
NSTUB(Open, 0xffc5ce64)
NSTUB(PhySw_testgpio, 0xffc17638)
NSTUB(ProtectFile, 0xffc55aac)
NSTUB(Read, 0xffc5cf20)
NSTUB(RefreshPhysicalScreen, 0xffd60708)
NSTUB(Remove, 0xffc5ceac)
NSTUB(SetParameterData, 0xffd4f270)
NSTUB(SetPropertyCase, 0xffc1406c)
NSTUB(SleepTask, 0xffc11144)
NSTUB(TakeSemaphore, 0xffc10c40)
// Best match: 96%
NSTUB(UnlockMainPower, 0xffd49e50)
NSTUB(Unmount_FileSystem, 0xffc5c248)
NSTUB(UpdateMBROnFlash, 0xffc5c3a0)
// Best match: 96%
NSTUB(VbattGet, 0xffc1b4ac)
NSTUB(Write, 0xffc5cf2c)
NSTUB(_log, 0xffeaf100)
// ALT: NSTUB(_log, 0xffeaf100) // 27/0
NSTUB(_log10, 0xffeaf7a8)
// ALT: NSTUB(_log10, 0xffeaf7a8) // 27/0
NSTUB(_pow, 0xffeafc98)
// ALT: NSTUB(_pow, 0xffeafc98) // 25/0
NSTUB(_sqrt, 0xffeb3fe4)
// ALT: NSTUB(_sqrt, 0xffeb3fe4) // 24/0
NSTUB(chdir, 0xffec3240)
// ALT: NSTUB(chdir, 0xffec3240) // 27/0
NSTUB(close, 0xffec2b80)
NSTUB(closedir, 0xffebeb20)
// ERROR: free is not found!
NSTUB(ints_disable, 0xffc0d5cc)
NSTUB(ints_enable, 0xffc0d5d8)
NSTUB(ioctl, 0xffec2cc0)
NSTUB(iosDevAdd, 0xffec3da0)
NSTUB(iosDrvInstall, 0xffec4064)
NSTUB(isalpha, 0xffeb8a94)
// ALT: NSTUB(isalpha, 0xffeb8a94) // 4/0
NSTUB(isdigit, 0xffeb8ac4)
// ALT: NSTUB(isdigit, 0xffeb8ac4) // 4/0
NSTUB(islower, 0xffeb8af4)
// ALT: NSTUB(islower, 0xffeb8af4) // 4/0
NSTUB(isspace, 0xffeb8b3c)
// ALT: NSTUB(isspace, 0xffeb8b3c) // 4/0
NSTUB(isupper, 0xffeb8b54)
// ALT: NSTUB(isupper, 0xffeb8b54) // 4/0
NSTUB(kbd_p1_f, 0xffc16164)
NSTUB(kbd_p1_f_cont, 0xffc16170)
NSTUB(kbd_p2_f, 0xffc16548)
NSTUB(kbd_pwr_off, 0xffc1756c)
// ALT: NSTUB(kbd_pwr_off, 0xffc17600) // 6/0
// ALT: NSTUB(kbd_pwr_off, 0xffc1761c) // 6/0
NSTUB(kbd_pwr_on, 0xffc17544)
NSTUB(kbd_read_keys_r2, 0xffc16fb8)
// Best match: 93%
NSTUB(localtime, 0xffebd314)
NSTUB(lseek, 0xffec2cc4)
// Best match: 53%
NSTUB(malloc, 0xffec5bc0)
// ALT: NSTUB(malloc, 0xffec5bc0) // 15/13
NSTUB(memcmp, 0xffebc6f4)
// ALT: NSTUB(memcmp, 0xffecaadc) // 9/0
NSTUB(memcpy, 0xffebc730)
NSTUB(memset, 0xffebc7a8)
NSTUB(mkdir, 0xffc5d074)
NSTUB(open, 0xffec31c4)
NSTUB(opendir, 0xffebeb54)
NSTUB(qsort, 0xffebbf54)
NSTUB(rand, 0xffebbf78)
// ALT: NSTUB(rand, 0xffebbf78) // 8/0
NSTUB(read, 0xffec2be0)
NSTUB(readdir, 0xffebeaec)
NSTUB(rename, 0xffec31cc)
// ALT: NSTUB(rename, 0xffec31cc) // 26/0
NSTUB(rewinddir, 0xffebeb14)
NSTUB(srand, 0xffebbf9c)
// ALT: NSTUB(srand, 0xffebbf9c) // 4/0
NSTUB(stat, 0xffebebe8)
NSTUB(strcat, 0xffebc7c8)
NSTUB(strchr, 0xffebc7f4)
NSTUB(strcmp, 0xffebc818)
NSTUB(strcpy, 0xffebc9ac)
NSTUB(strlen, 0xffebcb10)
NSTUB(strncmp, 0xffebcb74)
NSTUB(strncpy, 0xffebcbb8)
// ALT: NSTUB(strncpy, 0xffebcbb8) // 24/0
NSTUB(strpbrk, 0xffebcc00)
NSTUB(strrchr, 0xffebcc3c)
// ALT: NSTUB(strrchr, 0xffebcc3c) // 8/0
NSTUB(strtol, 0xffebc390)
NSTUB(taskCreateHookAdd, 0xffec9240)
NSTUB(taskDeleteHookAdd, 0xffec917c)
// Best match: 82%
NSTUB(taskIdListGet, 0xffed3804)
NSTUB(taskLock, 0xffed3ec0)
NSTUB(taskName, 0xffed36fc)
NSTUB(taskResume, 0xffed3ae0)
NSTUB(taskSuspend, 0xffed390c)
NSTUB(taskUnlock, 0xffed3f68)
NSTUB(time, 0xffebe060)
// ALT: NSTUB(time, 0xffebe060) // 25/0
NSTUB(utime, 0xffebec7c)
// ALT: NSTUB(utime, 0xffebec7c) // 26/0
NSTUB(vsprintf, 0xffec0440)
NSTUB(write, 0xffec2c50)
