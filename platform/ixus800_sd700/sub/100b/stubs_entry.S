// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

NSTUB(AllocateMemory, 0xff811ac4)
NSTUB(AllocateUncacheableMemory, 0xff814cb0)
NSTUB(Close, 0xff86f5a4)
NSTUB(CreatePhysicalVram, 0xff935150)
NSTUB(CreateTask, 0xff82161c)
NSTUB(CreateTaskStrict, 0xff8226bc)
NSTUB(DisableDispatch, 0xff821440)
// Best match: 96%
NSTUB(DisplayImagePhysicalScreen, 0xff934484)
NSTUB(EnableDispatch, 0xff8214cc)
NSTUB(ExecuteEventProcedure, 0xff816bc8)
NSTUB(ExitTask, 0xff8219dc)
NSTUB(Fclose_Fut, 0xff868884)
NSTUB(Fopen_Fut, 0xff868848)
NSTUB(Fread_Fut, 0xff868968)
NSTUB(FreeMemory, 0xff811ad0)
NSTUB(FreeUncacheableMemory, 0xff814ce4)
NSTUB(Fseek_Fut, 0xff868a50)
NSTUB(Fwrite_Fut, 0xff8689b8)
NSTUB(GetCurrentAvValue, 0xffac6198)
NSTUB(GetCurrentTargetDistance, 0xffac6140)
// Best match: 54%
NSTUB(GetFocusLensSubjectDistance, 0xffab4f50)
// ALT: NSTUB(GetFocusLensSubjectDistance, 0xffab4f50) // 17/14
// Best match: 92%
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xffab54ec)
// Best match: 86%
NSTUB(GetParameterData, 0xff976f2c)
NSTUB(GetPropertyCase, 0xff8248e0)
// Best match: 96%
NSTUB(GetSystemTime, 0xff814ee8)
// ALT: NSTUB(GetSystemTime, 0xff814ee8) // 26/1
// Best match: 93%
NSTUB(GetZoomLensCurrentPoint, 0xffaa5f18)
// ALT: NSTUB(GetZoomLensCurrentPoint, 0xffaa5f18) // 27/2
// Best match: 93%
NSTUB(GetZoomLensCurrentPosition, 0xffaa5f2c)
// ALT: NSTUB(GetZoomLensCurrentPosition, 0xffaa5f2c) // 27/2
NSTUB(IsStrobeChargeCompleted, 0xff910478)
NSTUB(LockMainPower, 0xff972100)
NSTUB(MakeDirectory, 0xff86f848)
// Best match: 90%
NSTUB(Mount_FileSystem, 0xff86e8d4)
// ALT: NSTUB(Mount_FileSystem, 0xff86e8d4) // 27/3
// Best match: 96%
NSTUB(MoveFocusLensToDistance, 0xffac63e0)
NSTUB(MoveZoomLensWithPoint, 0xffaa5df8)
// ALT: NSTUB(MoveZoomLensWithPoint, 0xffaa5df8) // 25/0
NSTUB(Open, 0xff86f57c)
// Best match: 89%
NSTUB(PhySw_testgpio, 0xff827f94)
NSTUB(ProtectFile, 0xff867eb0)
NSTUB(Read, 0xff86f638)
NSTUB(RefreshPhysicalScreen, 0xff988eec)
NSTUB(Remove, 0xff86f5c4)
NSTUB(SetAutoShutdownTime, 0xff972004)
// Best match: 86%
NSTUB(SetParameterData, 0xff976e4c)
NSTUB(SetPropertyCase, 0xff8247c4)
NSTUB(SleepTask, 0xff821530)
NSTUB(TakeSemaphore, 0xff82102c)
NSTUB(UnlockMainPower, 0xff972198)
NSTUB(Unmount_FileSystem, 0xff86e978)
NSTUB(UpdateMBROnFlash, 0xff86eac8)
// ERROR: VbattGet is not found!
NSTUB(Write, 0xff86f644)
NSTUB(_log, 0xffb01b34)
// ALT: NSTUB(_log, 0xffb01b34) // 27/0
NSTUB(_log10, 0xffafded4)
// ALT: NSTUB(_log10, 0xffafded4) // 27/0
NSTUB(_pow, 0xffafe05c)
// ALT: NSTUB(_pow, 0xffafe05c) // 25/0
NSTUB(_sqrt, 0xffafff30)
// ALT: NSTUB(_sqrt, 0xffafff30) // 24/0
NSTUB(chdir, 0xffb0c658)
// ALT: NSTUB(chdir, 0xffb0c658) // 27/0
NSTUB(close, 0xffb0bf98)
NSTUB(closedir, 0xffb09420)
// ERROR: free is not found!
NSTUB(ints_disable, 0xff81da9c)
NSTUB(ints_enable, 0xff81daa8)
NSTUB(ioctl, 0xffb0c0d8)
NSTUB(iosDevAdd, 0xffb0d1b8)
NSTUB(iosDrvInstall, 0xffb0d47c)
NSTUB(isalpha, 0xffb034c4)
// ALT: NSTUB(isalpha, 0xffb034c4) // 4/0
NSTUB(isdigit, 0xffb034f4)
// ALT: NSTUB(isdigit, 0xffb034f4) // 4/0
NSTUB(islower, 0xffb03524)
// ALT: NSTUB(islower, 0xffb03524) // 4/0
NSTUB(isspace, 0xffb0356c)
// ALT: NSTUB(isspace, 0xffb0356c) // 4/0
NSTUB(isupper, 0xffb03584)
// ALT: NSTUB(isupper, 0xffb03584) // 4/0
NSTUB(kbd_p1_f, 0xff826cf0)
NSTUB(kbd_p1_f_cont, 0xff826cfc)
NSTUB(kbd_p2_f, 0xff8270d4)
// Best match: 83%
NSTUB(kbd_pwr_off, 0xff827f50)
// ALT: NSTUB(kbd_pwr_off, 0xff827f6c) // 5/1
// ALT: NSTUB(kbd_pwr_off, 0xff8291b4) // 5/1
// ALT: NSTUB(kbd_pwr_off, 0xff8291d0) // 5/1
// ERROR: kbd_pwr_on is not found!
NSTUB(kbd_read_keys_r2, 0xff827a3c)
// Best match: 93%
NSTUB(localtime, 0xffb07c14)
NSTUB(lseek, 0xffb0c0dc)
// Best match: 53%
NSTUB(malloc, 0xffb0efd8)
// ALT: NSTUB(malloc, 0xffb0efd8) // 15/13
NSTUB(memcmp, 0xffb06ff4)
// ALT: NSTUB(memcmp, 0xffb13bb8) // 9/0
NSTUB(memcpy, 0xffb07030)
NSTUB(memset, 0xffb070a8)
NSTUB(mkdir, 0xff86f78c)
NSTUB(open, 0xffb0c5dc)
NSTUB(opendir, 0xffb09454)
NSTUB(qsort, 0xffb06854)
NSTUB(rand, 0xffb06878)
// ALT: NSTUB(rand, 0xffb06878) // 8/0
NSTUB(read, 0xffb0bff8)
NSTUB(readdir, 0xffb093ec)
NSTUB(rename, 0xffb0c5e4)
// ALT: NSTUB(rename, 0xffb0c5e4) // 26/0
NSTUB(rewinddir, 0xffb09414)
NSTUB(srand, 0xffb0689c)
// ALT: NSTUB(srand, 0xffb0689c) // 4/0
NSTUB(stat, 0xffb094e8)
NSTUB(strcat, 0xffb070c8)
NSTUB(strchr, 0xffb070f4)
NSTUB(strcmp, 0xffb07118)
NSTUB(strcpy, 0xffb072ac)
NSTUB(strlen, 0xffb07410)
NSTUB(strncmp, 0xffb07474)
NSTUB(strncpy, 0xffb074b8)
// ALT: NSTUB(strncpy, 0xffb074b8) // 24/0
NSTUB(strpbrk, 0xffb07500)
NSTUB(strrchr, 0xffb0753c)
// ALT: NSTUB(strrchr, 0xffb0753c) // 8/0
NSTUB(strtol, 0xffb06c90)
NSTUB(taskCreateHookAdd, 0xffb12658)
NSTUB(taskDeleteHookAdd, 0xffb12594)
// Best match: 82%
NSTUB(taskIdListGet, 0xffb1c620)
NSTUB(taskLock, 0xffb1ccdc)
NSTUB(taskName, 0xffb1c518)
NSTUB(taskResume, 0xffb1c8fc)
NSTUB(taskSuspend, 0xffb1c728)
NSTUB(taskUnlock, 0xffb1cd84)
NSTUB(time, 0xffb08960)
// ALT: NSTUB(time, 0xffb08960) // 25/0
NSTUB(utime, 0xffb0957c)
// ALT: NSTUB(utime, 0xffb0957c) // 26/0
NSTUB(vsprintf, 0xffb0ad40)
NSTUB(write, 0xffb0c068)
