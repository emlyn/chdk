// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Best match: 79%
NSTUB(AllocateMemory, 0xff811ba0)
NSTUB(AllocateUncacheableMemory, 0xff814810)
// ERROR: Close is not found!
NSTUB(CreatePhysicalVram, 0xff93e4f4)
NSTUB(CreateTask, 0xff82239c)
NSTUB(CreateTaskStrict, 0xff823964)
NSTUB(DisableDispatch, 0xff82210c)
// ERROR: DisplayImagePhysicalScreen is not found!
NSTUB(EnableDispatch, 0xff822198)
NSTUB(ExecuteEventProcedure, 0xff816ab4)
NSTUB(ExitTask, 0xff82275c)
NSTUB(Fclose_Fut, 0xff86fd34)
NSTUB(Fopen_Fut, 0xff86fcf8)
NSTUB(Fread_Fut, 0xff86fe18)
// Best match: 66%
NSTUB(FreeMemory, 0xff811bac)
NSTUB(FreeUncacheableMemory, 0xff814844)
NSTUB(Fseek_Fut, 0xff86ff00)
NSTUB(Fwrite_Fut, 0xff86fe68)
NSTUB(GetCurrentAvValue, 0xffaa6cc4)
// ALT: NSTUB(GetCurrentAvValue, 0xffaa8c78) // 13/0
NSTUB(GetCurrentTargetDistance, 0xffaa8c20)
// Best match: 87%
NSTUB(GetFocusLensSubjectDistance, 0xffa8e96c)
// ALT: NSTUB(GetFocusLensSubjectDistance, 0xffa8e96c) // 27/4
// ERROR: GetFocusLensSubjectDistanceFromLens is not found!
// Best match: 76%
NSTUB(GetParameterData, 0xff987fe0)
// ALT: NSTUB(GetParameterData, 0xff987fe0) // 23/7
// Best match: 71%
NSTUB(GetPropertyCase, 0xff825d04)
// Best match: 96%
NSTUB(GetSystemTime, 0xff814b98)
// ALT: NSTUB(GetSystemTime, 0xff814b98) // 26/1
// Best match: 68%
NSTUB(GetZoomLensCurrentPoint, 0xffa88174)
// ALT: NSTUB(GetZoomLensCurrentPoint, 0xffa88174) // 20/9
// Best match: 51%
NSTUB(GetZoomLensCurrentPosition, 0xffa88188)
// ALT: NSTUB(GetZoomLensCurrentPosition, 0xffa88188) // 15/14
NSTUB(IsStrobeChargeCompleted, 0xff912f08)
// Best match: 96%
NSTUB(LockMainPower, 0xff9834f0)
// Best match: 70%
NSTUB(MakeDirectory, 0xff8775b0)
// ERROR: Mount_FileSystem is not found!
// Best match: 96%
NSTUB(MoveFocusLensToDistance, 0xffaa8eb0)
// ERROR: MoveZoomLensWithPoint is not found!
// ERROR: Open is not found!
// ERROR: PhySw_testgpio is not found!
NSTUB(ProtectFile, 0xff86f360)
NSTUB(PutInNdFilter, 0xffaa6cd8)
// ALT: NSTUB(PutInNdFilter, 0xffaa6d20) // 27/0
// Best match: 94%
NSTUB(PutOutNdFilter, 0xffaa7130)
// ALT: NSTUB(PutOutNdFilter, 0xffaa7130) // 16/1
// ERROR: Read is not found!
NSTUB(RefreshPhysicalScreen, 0xff9988dc)
// ERROR: Remove is not found!
// Best match: 96%
NSTUB(SetAutoShutdownTime, 0xff9833e8)
// Best match: 66%
NSTUB(SetParameterData, 0xff987fdc)
// ERROR: SetPropertyCase is not found!
NSTUB(SleepTask, 0xff8221fc)
// ALT: NSTUB(SleepTask, 0xff8222b0) // 31/0
NSTUB(TakeSemaphore, 0xff821b6c)
// Best match: 96%
NSTUB(UnlockMainPower, 0xff9835a4)
NSTUB(Unmount_FileSystem, 0xff8762d4)
// Best match: 96%
NSTUB(UpdateMBROnFlash, 0xff876480)
// ERROR: VbattGet is not found!
// ERROR: Write is not found!
NSTUB(_log, 0xffae0a40)
// ALT: NSTUB(_log, 0xffae0a40) // 27/0
NSTUB(_log10, 0xffae10e8)
// ALT: NSTUB(_log10, 0xffae10e8) // 27/0
NSTUB(_pow, 0xffae15d8)
// ALT: NSTUB(_pow, 0xffae15d8) // 25/0
NSTUB(_sqrt, 0xffae5924)
// ALT: NSTUB(_sqrt, 0xffae5924) // 24/0
NSTUB(chdir, 0xffaf4b80)
// ALT: NSTUB(chdir, 0xffaf4b80) // 27/0
NSTUB(close, 0xffaf44c0)
NSTUB(closedir, 0xffaf0460)
// ERROR: free is not found!
NSTUB(ints_disable, 0xff81e254)
NSTUB(ints_enable, 0xff81e260)
NSTUB(ioctl, 0xffaf4600)
NSTUB(iosDevAdd, 0xffaf56e0)
NSTUB(iosDrvInstall, 0xffaf59a4)
NSTUB(isalpha, 0xffaea3d4)
// ALT: NSTUB(isalpha, 0xffaea3d4) // 4/0
NSTUB(isdigit, 0xffaea404)
// ALT: NSTUB(isdigit, 0xffaea404) // 4/0
NSTUB(islower, 0xffaea434)
// ALT: NSTUB(islower, 0xffaea434) // 4/0
NSTUB(isspace, 0xffaea47c)
// ALT: NSTUB(isspace, 0xffaea47c) // 4/0
NSTUB(isupper, 0xffaea494)
// ALT: NSTUB(isupper, 0xffaea494) // 4/0
// ERROR: kbd_p1_f is not found!
// ERROR: kbd_p1_f_cont is not found!
// ERROR: kbd_p2_f is not found!
// Best match: 83%
NSTUB(kbd_pwr_off, 0xff82b0d4)
// ALT: NSTUB(kbd_pwr_off, 0xff82b0f0) // 5/1
// Best match: 55%
NSTUB(kbd_pwr_on, 0xff9402d8)
// ALT: NSTUB(kbd_pwr_on, 0xff940304) // 5/4
// ERROR: kbd_read_keys_r2 is not found!
// Best match: 93%
NSTUB(localtime, 0xffaeec54)
NSTUB(lseek, 0xffaf4604)
// Best match: 53%
NSTUB(malloc, 0xffaf7500)
// ALT: NSTUB(malloc, 0xffaf7500) // 15/13
NSTUB(memcmp, 0xffaee034)
// ALT: NSTUB(memcmp, 0xffafc41c) // 9/0
NSTUB(memcpy, 0xffaee070)
NSTUB(memset, 0xffaee0e8)
// Best match: 61%
NSTUB(mkdir, 0xff8774fc)
// ALT: NSTUB(mkdir, 0xff8775bc) // 19/12
NSTUB(open, 0xffaf4b04)
NSTUB(opendir, 0xffaf0494)
NSTUB(qsort, 0xffaed894)
NSTUB(rand, 0xffaed8b8)
// ALT: NSTUB(rand, 0xffaed8b8) // 8/0
NSTUB(read, 0xffaf4520)
NSTUB(readdir, 0xffaf042c)
NSTUB(rename, 0xffaf4b0c)
// ALT: NSTUB(rename, 0xffaf4b0c) // 26/0
NSTUB(rewinddir, 0xffaf0454)
NSTUB(srand, 0xffaed8dc)
// ALT: NSTUB(srand, 0xffaed8dc) // 4/0
NSTUB(stat, 0xffaf0528)
NSTUB(strcat, 0xffaee108)
NSTUB(strchr, 0xffaee134)
NSTUB(strcmp, 0xffaee158)
NSTUB(strcpy, 0xffaee2ec)
NSTUB(strlen, 0xffaee450)
NSTUB(strncmp, 0xffaee4b4)
NSTUB(strncpy, 0xffaee4f8)
// ALT: NSTUB(strncpy, 0xffaee4f8) // 24/0
NSTUB(strpbrk, 0xffaee540)
NSTUB(strrchr, 0xffaee57c)
// ALT: NSTUB(strrchr, 0xffaee57c) // 8/0
NSTUB(strtol, 0xffaedcd0)
NSTUB(taskCreateHookAdd, 0xffafab80)
NSTUB(taskDeleteHookAdd, 0xffafaabc)
// Best match: 82%
NSTUB(taskIdListGet, 0xffb02664)
NSTUB(taskLock, 0xffb02d20)
NSTUB(taskName, 0xffb0255c)
NSTUB(taskResume, 0xffb02940)
NSTUB(taskSuspend, 0xffb0276c)
NSTUB(taskUnlock, 0xffb02dc8)
NSTUB(time, 0xffaef9a0)
// ALT: NSTUB(time, 0xffaef9a0) // 25/0
NSTUB(utime, 0xffaf05bc)
// ALT: NSTUB(utime, 0xffaf05bc) // 26/0
NSTUB(vsprintf, 0xffaf1d80)
NSTUB(write, 0xffaf4590)
