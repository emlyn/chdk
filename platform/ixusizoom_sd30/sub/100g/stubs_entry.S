// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Best match: 79%
NSTUB(AllocateMemory, 0xff811ba0)
NSTUB(AllocateUncacheableMemory, 0xff814d0c)
NSTUB(Close, 0xff870628)
NSTUB(CreatePhysicalVram, 0xff922ba8)
NSTUB(CreateTask, 0xff8228ac)
NSTUB(CreateTaskStrict, 0xff823cb0)
NSTUB(DeleteFile_Fut, 0xff86950c)
NSTUB(DisableDispatch, 0xff82261c)
// Best match: 51%
NSTUB(DisplayImagePhysicalScreen, 0xff921f60)
NSTUB(EnableDispatch, 0xff8226a8)
NSTUB(ExecuteEventProcedure, 0xff816fac)
NSTUB(ExitTask, 0xff822c6c)
NSTUB(Fclose_Fut, 0xff86964c)
NSTUB(Feof_Fut, 0xff869860)
NSTUB(Fflush_Fut, 0xff869898)
NSTUB(Fgets_Fut, 0xff8697d0)
NSTUB(Fopen_Fut, 0xff869610)
NSTUB(Fread_Fut, 0xff869730)
// Best match: 66%
NSTUB(FreeMemory, 0xff811bac)
NSTUB(FreeUncacheableMemory, 0xff814d40)
NSTUB(Fseek_Fut, 0xff869818)
NSTUB(Fwrite_Fut, 0xff869780)
NSTUB(GetCurrentAvValue, 0xffa874ac)
NSTUB(GetCurrentTargetDistance, 0xffa87454)
// Best match: 90%
NSTUB(GetFocusLensSubjectDistance, 0xffa7a8b0)
// ALT: NSTUB(GetFocusLensSubjectDistance, 0xffa7a8b0) // 28/3
// Best match: 52%
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xffa7ae50)
NSTUB(GetParameterData, 0xff962ba0)
NSTUB(GetPropertyCase, 0xff825bb0)
// Best match: 96%
NSTUB(GetSystemTime, 0xff815094)
// ALT: NSTUB(GetSystemTime, 0xff815094) // 26/1
// Best match: 93%
NSTUB(GetZoomLensCurrentPoint, 0xffa6b7cc)
// ALT: NSTUB(GetZoomLensCurrentPoint, 0xffa6b7cc) // 27/2
// Best match: 93%
NSTUB(GetZoomLensCurrentPosition, 0xffa6b7e0)
// ALT: NSTUB(GetZoomLensCurrentPosition, 0xffa6b7e0) // 27/2
NSTUB(IsStrobeChargeCompleted, 0xff8fc68c)
// Best match: 96%
NSTUB(LockMainPower, 0xff95e0f4)
NSTUB(MakeDirectory, 0xff870900)
NSTUB(MakeDirectory_Fut, 0xff869598)
// Best match: 90%
NSTUB(Mount_FileSystem, 0xff86f8dc)
// ALT: NSTUB(Mount_FileSystem, 0xff86f8dc) // 27/3
// Best match: 96%
NSTUB(MoveFocusLensToDistance, 0xffa876e4)
NSTUB(MoveZoomLensWithPoint, 0xffa6b6ac)
// ALT: NSTUB(MoveZoomLensWithPoint, 0xffa6b6ac) // 25/0
NSTUB(Open, 0xff870600)
// Best match: 96%
NSTUB(PhySw_testgpio, 0xff828f68)
NSTUB(ProtectFile, 0xff868c78)
// Best match: 92%
NSTUB(PutInNdFilter, 0xffa854cc)
// ALT: NSTUB(PutInNdFilter, 0xffa854cc) // 25/2
// ALT: NSTUB(PutInNdFilter, 0xffa87058) // 25/2
// ALT: NSTUB(PutInNdFilter, 0xffa87058) // 25/2
// ALT: NSTUB(PutInNdFilter, 0xffa870a0) // 25/2
// ALT: NSTUB(PutInNdFilter, 0xffa870a0) // 25/2
// Best match: 94%
NSTUB(PutOutNdFilter, 0xffa85514)
// ALT: NSTUB(PutOutNdFilter, 0xffa85514) // 16/1
NSTUB(Read, 0xff8706bc)
NSTUB(RefreshPhysicalScreen, 0xff97352c)
NSTUB(Remove, 0xff870648)
NSTUB(RenameFile_Fut, 0xff86948c)
// Best match: 96%
NSTUB(SetAutoShutdownTime, 0xff95dfec)
NSTUB(SetParameterData, 0xff962ac0)
NSTUB(SetPropertyCase, 0xff825a94)
NSTUB(SleepTask, 0xff82270c)
// ALT: NSTUB(SleepTask, 0xff8227c0) // 31/0
NSTUB(TakeSemaphore, 0xff8220c8)
NSTUB(TurnOffBackLight, 0xff9a013c)
NSTUB(TurnOnBackLight, 0xff9a0110)
// Best match: 96%
NSTUB(UnlockMainPower, 0xff95e1a8)
NSTUB(Unmount_FileSystem, 0xff86f9e4)
// Best match: 89%
NSTUB(UnsetZoomForMovie, 0xff995220)
// Best match: 96%
NSTUB(UpdateMBROnFlash, 0xff86fb3c)
// ERROR: VbattGet is not found!
NSTUB(Write, 0xff8706c8)
NSTUB(_log, 0xffabcba0)
// ALT: NSTUB(_log, 0xffabcba0) // 27/0
NSTUB(_log10, 0xffabd248)
// ALT: NSTUB(_log10, 0xffabd248) // 27/0
NSTUB(_pow, 0xffabd738)
// ALT: NSTUB(_pow, 0xffabd738) // 25/0
NSTUB(_sqrt, 0xffac1a84)
// ALT: NSTUB(_sqrt, 0xffac1a84) // 24/0
NSTUB(chdir, 0xffad0ce0)
// ALT: NSTUB(chdir, 0xffad0ce0) // 27/0
NSTUB(close, 0xffad0620)
NSTUB(closedir, 0xffacc5c0)
NSTUB(errnoOfTaskGet, 0xffaccd8c)
// ERROR: free is not found!
NSTUB(ints_disable, 0xff81e7ec)
NSTUB(ints_enable, 0xff81e7f8)
NSTUB(ioctl, 0xffad0760)
NSTUB(iosDevAdd, 0xffad1840)
NSTUB(iosDevDelete, 0xffad1818)
NSTUB(iosDevFind, 0xffad17cc)
NSTUB(iosDrvInstall, 0xffad1b04)
NSTUB(isalpha, 0xffac6534)
NSTUB(isdigit, 0xffac6564)
NSTUB(islower, 0xffac6594)
NSTUB(ispunct, 0xffac65c4)
NSTUB(isspace, 0xffac65dc)
NSTUB(isupper, 0xffac65f4)
NSTUB(isxdigit, 0xffac660c)
NSTUB(kbd_p1_f, 0xff827bec)
NSTUB(kbd_p1_f_cont, 0xff827bf8)
NSTUB(kbd_p2_f, 0xff827fd0)
// Best match: 83%
NSTUB(kbd_pwr_off, 0xff828f30)
// ALT: NSTUB(kbd_pwr_off, 0xff828f4c) // 5/1
// ALT: NSTUB(kbd_pwr_off, 0xff829f24) // 5/1
// ALT: NSTUB(kbd_pwr_off, 0xff829f40) // 5/1
// Best match: 55%
NSTUB(kbd_pwr_on, 0xff921148)
// ALT: NSTUB(kbd_pwr_on, 0xff921174) // 5/4
// ERROR: kbd_read_keys_r2 is not found!
// Best match: 93%
NSTUB(localtime, 0xffacadb4)
NSTUB(lseek, 0xffad0764)
// Best match: 53%
NSTUB(malloc, 0xffad3660)
// ALT: NSTUB(malloc, 0xffad3660) // 15/13
NSTUB(memchr, 0xffaca160)
NSTUB(memcmp, 0xffaca194)
// ALT: NSTUB(memcmp, 0xffad857c) // 9/0
NSTUB(memcpy, 0xffaca1d0)
NSTUB(memset, 0xffaca248)
NSTUB(mkdir, 0xff870844)
NSTUB(mktime, 0xffacaf7c)
NSTUB(open, 0xffad0c64)
NSTUB(opendir, 0xffacc5f4)
NSTUB(qsort, 0xffac99f4)
NSTUB(rand, 0xffac9a18)
// ALT: NSTUB(rand, 0xffac9a18) // 8/0
NSTUB(read, 0xffad0680)
NSTUB(readdir, 0xffacc58c)
NSTUB(rename, 0xffad0c6c)
// ALT: NSTUB(rename, 0xffad0c6c) // 26/0
NSTUB(rewinddir, 0xffacc5b4)
NSTUB(srand, 0xffac9a3c)
// ALT: NSTUB(srand, 0xffac9a3c) // 4/0
NSTUB(stat, 0xffacc688)
NSTUB(strcat, 0xffaca268)
NSTUB(strchr, 0xffaca294)
NSTUB(strcmp, 0xffaca2b8)
NSTUB(strcpy, 0xffaca44c)
NSTUB(strftime, 0xffacbad4)
NSTUB(strlen, 0xffaca5b0)
NSTUB(strncmp, 0xffaca614)
NSTUB(strncpy, 0xffaca658)
// ALT: NSTUB(strncpy, 0xffaca658) // 24/0
NSTUB(strpbrk, 0xffaca6a0)
NSTUB(strrchr, 0xffaca6dc)
// ALT: NSTUB(strrchr, 0xffaca6dc) // 8/0
NSTUB(strtol, 0xffac9e30)
NSTUB(taskCreateHookAdd, 0xffad6ce0)
NSTUB(taskDeleteHookAdd, 0xffad6c1c)
// Best match: 82%
NSTUB(taskIdListGet, 0xffae12a4)
NSTUB(taskLock, 0xffae1960)
NSTUB(taskName, 0xffae119c)
NSTUB(taskResume, 0xffae1580)
NSTUB(taskSuspend, 0xffae13ac)
NSTUB(taskUnlock, 0xffae1a08)
NSTUB(time, 0xffacbb00)
// ALT: NSTUB(time, 0xffacbb00) // 25/0
NSTUB(tolower, 0xffac6624)
NSTUB(toupper, 0xffac6634)
NSTUB(utime, 0xffacc71c)
// ALT: NSTUB(utime, 0xffacc71c) // 26/0
NSTUB(vsprintf, 0xffacdee0)
NSTUB(write, 0xffad06f0)
