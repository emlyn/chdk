// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Best match: 95%
NSTUB(AllocateMemory, 0xff811e38)
// ALT: NSTUB(AllocateMemory, 0xff811e38) // 23/1
NSTUB(AllocateUncacheableMemory, 0xff81e664)
// ERROR: Close is not found!
// Best match: 75%
NSTUB(CreatePhysicalVram, 0xffa386a8)
NSTUB(CreateTask, 0xffb41b48)
NSTUB(CreateTaskStrict, 0xffb42be8)
NSTUB(DeleteFile_Fut, 0xffaaa2b0)
NSTUB(DisableDispatch, 0xffb4196c)
// ERROR: DisplayImagePhysicalScreen is not found!
NSTUB(EnableDispatch, 0xffb419f8)
NSTUB(ExecuteEventProcedure, 0xff814adc)
NSTUB(ExitTask, 0xffb41f08)
NSTUB(Fclose_Fut, 0xffaaa424)
NSTUB(Feof_Fut, 0xffaaa620)
NSTUB(Fflush_Fut, 0xffaaa65c)
NSTUB(Fgets_Fut, 0xffaaa588)
NSTUB(Fopen_Fut, 0xffaaa3e4)
NSTUB(Fread_Fut, 0xffaaa4e0)
// Best match: 95%
NSTUB(FreeMemory, 0xff811e44)
// ALT: NSTUB(FreeMemory, 0xff811e44) // 23/1
// Best match: 90%
NSTUB(FreeUncacheableMemory, 0xff81e698)
NSTUB(Fseek_Fut, 0xffaaa5d4)
NSTUB(Fwrite_Fut, 0xffaaa534)
NSTUB(GetCurrentAvValue, 0xffa63598)
// ALT: NSTUB(GetCurrentAvValue, 0xffa63690) // 13/0
// ALT: NSTUB(GetCurrentAvValue, 0xffa6608c) // 13/0
NSTUB(GetCurrentTargetDistance, 0xffa66034)
// Best match: 74%
NSTUB(GetFocusLensSubjectDistance, 0xffaea6d0)
// ALT: NSTUB(GetFocusLensSubjectDistance, 0xffaea6d0) // 23/8
// ERROR: GetFocusLensSubjectDistanceFromLens is not found!
// Best match: 86%
NSTUB(GetParameterData, 0xffb66c14)
// Best match: 89%
NSTUB(GetPropertyCase, 0xff81bd58)
// Best match: 96%
NSTUB(GetSystemTime, 0xff813770)
// ALT: NSTUB(GetSystemTime, 0xff813770) // 26/1
// Best match: 58%
NSTUB(GetZoomLensCurrentPoint, 0xffaec72c)
// ALT: NSTUB(GetZoomLensCurrentPoint, 0xffaec72c) // 17/12
// ERROR: GetZoomLensCurrentPosition is not found!
NSTUB(IsStrobeChargeCompleted, 0xff9b8f54)
NSTUB(LockMainPower, 0xffb63900)
// Best match: 61%
NSTUB(MakeDirectory, 0xffaaf00c)
NSTUB(MakeDirectory_Fut, 0xffaaa364)
// ERROR: Mount_FileSystem is not found!
// Best match: 73%
NSTUB(MoveFocusLensToDistance, 0xffa662cc)
// ERROR: MoveZoomLensWithPoint is not found!
// Best match: 66%
NSTUB(Open, 0xffaaecb4)
// Best match: 93%
NSTUB(PhySw_testgpio, 0xffa44cac)
NSTUB(ProtectFile, 0xffaa9908)
// Best match: 92%
NSTUB(PutInNdFilter, 0xffa63a14)
// ALT: NSTUB(PutInNdFilter, 0xffa63a14) // 25/2
// Best match: 94%
NSTUB(PutOutNdFilter, 0xffa63a5c)
// ALT: NSTUB(PutOutNdFilter, 0xffa63a5c) // 16/1
// ERROR: Read is not found!
// Best match: 58%
NSTUB(RefreshPhysicalScreen, 0xff916bd8)
NSTUB(Remove, 0xffaaecfc)
NSTUB(RenameFile_Fut, 0xffaaa208)
NSTUB(SetAutoShutdownTime, 0xffb63804)
// Best match: 86%
NSTUB(SetParameterData, 0xffb66b34)
// Best match: 73%
NSTUB(SetPropertyCase, 0xff81bc1c)
NSTUB(SleepTask, 0xffb41a5c)
// Best match: 61%
NSTUB(TakeSemaphore, 0xffb41514)
NSTUB(UnlockMainPower, 0xffb63998)
NSTUB(Unmount_FileSystem, 0xffaae0a8)
// ERROR: UnsetZoomForMovie is not found!
NSTUB(UpdateMBROnFlash, 0xffaae1fc)
// Best match: 82%
NSTUB(VbattGet, 0xffa40a4c)
// ERROR: Write is not found!
NSTUB(_log, 0xff91e554)
// ALT: NSTUB(_log, 0xff91e554) // 27/0
NSTUB(_log10, 0xff91ac9c)
// ALT: NSTUB(_log10, 0xff91ac9c) // 27/0
NSTUB(_pow, 0xff91ae1c)
// ALT: NSTUB(_pow, 0xff91ae1c) // 25/0
NSTUB(_sqrt, 0xff91ccdc)
// ALT: NSTUB(_sqrt, 0xff91ccdc) // 24/0
NSTUB(chdir, 0xff928afc)
// ALT: NSTUB(chdir, 0xff928afc) // 27/0
NSTUB(close, 0xff92843c)
NSTUB(closedir, 0xffb7cca4)
NSTUB(errnoOfTaskGet, 0xff926090)
// ERROR: free is not found!
NSTUB(ints_disable, 0xffb3fc18)
NSTUB(ints_enable, 0xffb3fc24)
NSTUB(ioctl, 0xff92857c)
NSTUB(iosDevAdd, 0xff92965c)
NSTUB(iosDevFind, 0xff9295e8)
NSTUB(iosDrvInstall, 0xff929920)
NSTUB(isalpha, 0xff91fa14)
NSTUB(isdigit, 0xff91fa44)
NSTUB(islower, 0xff91fa74)
NSTUB(ispunct, 0xff91faa4)
NSTUB(isspace, 0xff91fabc)
NSTUB(isupper, 0xff91fad4)
NSTUB(isxdigit, 0xff91faec)
NSTUB(kbd_p1_f, 0xffa42fa8)
NSTUB(kbd_p1_f_cont, 0xffa42fb4)
// Best match: 56%
NSTUB(kbd_p2_f, 0xffa433d0)
// Best match: 83%
NSTUB(kbd_pwr_off, 0xffa42270)
// ALT: NSTUB(kbd_pwr_off, 0xffa4228c) // 5/1
// Best match: 55%
NSTUB(kbd_pwr_on, 0xffa39bac)
// ALT: NSTUB(kbd_pwr_on, 0xffa39bd8) // 5/4
// Best match: 76%
NSTUB(kbd_read_keys_r2, 0xffa44644)
// Best match: 93%
NSTUB(localtime, 0xff924294)
NSTUB(lseek, 0xff928580)
// Best match: 53%
NSTUB(malloc, 0xff92b47c)
// ALT: NSTUB(malloc, 0xff92b47c) // 15/13
NSTUB(memchr, 0xff923640)
NSTUB(memcmp, 0xff923674)
// ALT: NSTUB(memcmp, 0xff92f63c) // 9/0
NSTUB(memcpy, 0xff9236b0)
NSTUB(memset, 0xff923728)
// Best match: 51%
NSTUB(mkdir, 0xffaaef44)
// ALT: NSTUB(mkdir, 0xffaaf018) // 16/15
NSTUB(mktime, 0xff92445c)
NSTUB(open, 0xff928a80)
NSTUB(opendir, 0xffb7ccd8)
NSTUB(qsort, 0xff922ed4)
NSTUB(rand, 0xff922ef8)
// ALT: NSTUB(rand, 0xff922ef8) // 8/0
NSTUB(read, 0xff92849c)
NSTUB(readdir, 0xffb7cc70)
NSTUB(rename, 0xff928a88)
// ALT: NSTUB(rename, 0xff928a88) // 26/0
NSTUB(rewinddir, 0xffb7cc98)
NSTUB(srand, 0xff922f1c)
// ALT: NSTUB(srand, 0xff922f1c) // 4/0
NSTUB(stat, 0xffb7cd6c)
NSTUB(strcat, 0xff923748)
NSTUB(strchr, 0xff923774)
NSTUB(strcmp, 0xff923798)
NSTUB(strcpy, 0xff92392c)
NSTUB(strftime, 0xff924fb4)
NSTUB(strlen, 0xff923a90)
NSTUB(strncmp, 0xff923af4)
NSTUB(strncpy, 0xff923b38)
// ALT: NSTUB(strncpy, 0xff923b38) // 24/0
NSTUB(strpbrk, 0xff923b80)
NSTUB(strrchr, 0xff923bbc)
// ALT: NSTUB(strrchr, 0xff923bbc) // 8/0
NSTUB(strtol, 0xff923310)
NSTUB(taskCreateHookAdd, 0xff92e0dc)
NSTUB(taskDeleteHookAdd, 0xff92e018)
// Best match: 82%
NSTUB(taskIdListGet, 0xff9355c4)
NSTUB(taskLock, 0xff935c80)
NSTUB(taskName, 0xff9354bc)
NSTUB(taskResume, 0xff9358a0)
NSTUB(taskSuspend, 0xff9356cc)
NSTUB(taskUnlock, 0xff935d28)
NSTUB(time, 0xff924fe0)
// ALT: NSTUB(time, 0xff924fe0) // 25/0
NSTUB(tolower, 0xff91fb04)
NSTUB(toupper, 0xff91fb14)
// Best match: 57%
NSTUB(utime, 0xffb7ce00)
// ALT: NSTUB(utime, 0xffb7ce00) // 15/11
NSTUB(vsprintf, 0xff9271e4)
NSTUB(write, 0xff92850c)
