// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

NSTUB(AllocateMemory, 0xff811ab0)
NSTUB(AllocateUncacheableMemory, 0xff814ea0)
NSTUB(Close, 0xff87cb4c)
NSTUB(CreatePhysicalVram, 0xff966168)
NSTUB(CreateTask, 0xff822594)
NSTUB(CreateTaskStrict, 0xff823634)
NSTUB(DisableDispatch, 0xff8223b8)
// Best match: 93%
NSTUB(DisplayImagePhysicalScreen, 0xff9653f8)
// ALT: NSTUB(DisplayImagePhysicalScreen, 0xff9653f8) // 29/2
NSTUB(EnableDispatch, 0xff822444)
NSTUB(ExecuteEventProcedure, 0xff816d3c)
NSTUB(ExitTask, 0xff822954)
NSTUB(FreeMemory, 0xff811abc)
NSTUB(FreeUncacheableMemory, 0xff814ed4)
NSTUB(GetCurrentAvValue, 0xffb501d0)
// ALT: NSTUB(GetCurrentAvValue, 0xffb502c8) // 13/0
// ALT: NSTUB(GetCurrentAvValue, 0xffb52740) // 13/0
NSTUB(GetCurrentTargetDistance, 0xffb526e8)
// Best match: 83%
NSTUB(GetFocusLensSubjectDistance, 0xffb3d8c4)
// ALT: NSTUB(GetFocusLensSubjectDistance, 0xffb3d8c4) // 26/5
NSTUB(GetParameterData, 0xff9bbe08)
// Best match: 92%
NSTUB(GetPropertyCase, 0xff8258d4)
// Best match: 96%
NSTUB(GetSystemTime, 0xff8150d8)
// ALT: NSTUB(GetSystemTime, 0xff8150d8) // 26/1
// Best match: 93%
NSTUB(GetZoomLensCurrentPoint, 0xffb29cc8)
// ALT: NSTUB(GetZoomLensCurrentPoint, 0xffb29cc8) // 27/2
// Best match: 93%
NSTUB(GetZoomLensCurrentPosition, 0xffb29cdc)
// ALT: NSTUB(GetZoomLensCurrentPosition, 0xffb29cdc) // 27/2
NSTUB(IsStrobeChargeCompleted, 0xff939f98)
NSTUB(LockMainPower, 0xff9b60f8)
NSTUB(MakeDirectory, 0xff87ce60)
// Best match: 90%
NSTUB(Mount_FileSystem, 0xff87be74)
// ALT: NSTUB(Mount_FileSystem, 0xff87be74) // 27/3
// Best match: 96%
NSTUB(MoveFocusLensToDistance, 0xffb52988)
NSTUB(MoveZoomLensWithPoint, 0xffb29ba8)
// ALT: NSTUB(MoveZoomLensWithPoint, 0xffb29ba8) // 25/0
NSTUB(Open, 0xff87cb24)
// Best match: 86%
NSTUB(PhySw_testgpio, 0xff8295b0)
// ALT: NSTUB(PhySw_testgpio, 0xff8295b0) // 25/4
NSTUB(ProtectFile, 0xff875130)
NSTUB(Read, 0xff87cbe0)
NSTUB(RefreshPhysicalScreen, 0xff9ce31c)
NSTUB(Remove, 0xff87cb6c)
NSTUB(SetParameterData, 0xff9bbd28)
NSTUB(SetPropertyCase, 0xff825784)
NSTUB(SleepTask, 0xff8224a8)
NSTUB(TakeSemaphore, 0xff821fa4)
NSTUB(UnlockMainPower, 0xff9b6190)
NSTUB(Unmount_FileSystem, 0xff87bf18)
NSTUB(UpdateMBROnFlash, 0xff87c06c)
// Best match: 96%
NSTUB(VbattGet, 0xff82d9bc)
NSTUB(Write, 0xff87cbec)
NSTUB(_log, 0xffb910c4)
// ALT: NSTUB(_log, 0xffb910c4) // 27/0
NSTUB(_log10, 0xffb8cf80)
// ALT: NSTUB(_log10, 0xffb8cf80) // 27/0
NSTUB(_pow, 0xffb8d108)
// ALT: NSTUB(_pow, 0xffb8d108) // 25/0
NSTUB(_sqrt, 0xffb8f2f8)
// ALT: NSTUB(_sqrt, 0xffb8f2f8) // 24/0
NSTUB(chdir, 0xffb9c340)
// ALT: NSTUB(chdir, 0xffb9c340) // 27/0
NSTUB(close, 0xffb9bc80)
NSTUB(closedir, 0xffb99108)
// ERROR: free is not found!
NSTUB(ints_disable, 0xff81e2d0)
NSTUB(ints_enable, 0xff81e2dc)
NSTUB(ioctl, 0xffb9bdc0)
NSTUB(iosDevAdd, 0xffb9cea0)
NSTUB(iosDrvInstall, 0xffb9d164)
NSTUB(isalpha, 0xffb9307c)
// ALT: NSTUB(isalpha, 0xffb9307c) // 4/0
NSTUB(isdigit, 0xffb930ac)
// ALT: NSTUB(isdigit, 0xffb930ac) // 4/0
NSTUB(islower, 0xffb930dc)
// ALT: NSTUB(islower, 0xffb930dc) // 4/0
NSTUB(isspace, 0xffb93124)
// ALT: NSTUB(isspace, 0xffb93124) // 4/0
NSTUB(isupper, 0xffb9313c)
// ALT: NSTUB(isupper, 0xffb9313c) // 4/0
NSTUB(kbd_p1_f, 0xff828014)
NSTUB(kbd_p1_f_cont, 0xff828020)
NSTUB(kbd_p2_f, 0xff8283f0)
// Best match: 83%
NSTUB(kbd_pwr_off, 0xff82ab3c)
// ALT: NSTUB(kbd_pwr_off, 0xff82ab58) // 5/1
// Best match: 55%
NSTUB(kbd_pwr_on, 0xff96715c)
// ALT: NSTUB(kbd_pwr_on, 0xff967188) // 5/4
// ERROR: kbd_read_keys_r2 is not found!
// Best match: 93%
NSTUB(localtime, 0xffb978fc)
NSTUB(lseek, 0xffb9bdc4)
// Best match: 53%
NSTUB(malloc, 0xffb9ecc0)
// ALT: NSTUB(malloc, 0xffb9ecc0) // 15/13
NSTUB(memcmp, 0xffb96cdc)
// ALT: NSTUB(memcmp, 0xffba2e80) // 9/0
NSTUB(memcpy, 0xffb96d18)
NSTUB(memset, 0xffb96d90)
NSTUB(mkdir, 0xff87cda4)
NSTUB(open, 0xffb9c2c4)
NSTUB(opendir, 0xffb9913c)
NSTUB(qsort, 0xffb9653c)
NSTUB(rand, 0xffb96560)
// ALT: NSTUB(rand, 0xffb96560) // 8/0
NSTUB(read, 0xffb9bce0)
NSTUB(readdir, 0xffb990d4)
NSTUB(rename, 0xffb9c2cc)
// ALT: NSTUB(rename, 0xffb9c2cc) // 26/0
NSTUB(rewinddir, 0xffb990fc)
NSTUB(srand, 0xffb96584)
// ALT: NSTUB(srand, 0xffb96584) // 4/0
NSTUB(stat, 0xffb991d0)
NSTUB(strcat, 0xffb96db0)
NSTUB(strchr, 0xffb96ddc)
NSTUB(strcmp, 0xffb96e00)
NSTUB(strcpy, 0xffb96f94)
NSTUB(strlen, 0xffb970f8)
NSTUB(strncmp, 0xffb9715c)
NSTUB(strncpy, 0xffb971a0)
// ALT: NSTUB(strncpy, 0xffb971a0) // 24/0
NSTUB(strpbrk, 0xffb971e8)
NSTUB(strrchr, 0xffb97224)
// ALT: NSTUB(strrchr, 0xffb97224) // 8/0
NSTUB(strtol, 0xffb96978)
NSTUB(taskCreateHookAdd, 0xffba1920)
NSTUB(taskDeleteHookAdd, 0xffba185c)
// Best match: 82%
NSTUB(taskIdListGet, 0xffbab8e8)
NSTUB(taskLock, 0xffbabfa4)
NSTUB(taskName, 0xffbab7e0)
NSTUB(taskResume, 0xffbabbc4)
NSTUB(taskSuspend, 0xffbab9f0)
NSTUB(taskUnlock, 0xffbac04c)
NSTUB(time, 0xffb98648)
// ALT: NSTUB(time, 0xffb98648) // 25/0
NSTUB(utime, 0xffb99264)
// ALT: NSTUB(utime, 0xffb99264) // 26/0
NSTUB(vsprintf, 0xffb9aa28)
NSTUB(write, 0xffb9bd50)
NSTUB(Fclose_Fut, 0xff875b80)
NSTUB(Fopen_Fut, 0xff875b40)
NSTUB(Fread_Fut, 0xff875c3c)
NSTUB(Fseek_Fut, 0xff875d30)
NSTUB(Fwrite_Fut, 0xff875c90)
