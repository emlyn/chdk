// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

NSTUB(AllocateMemory, 0xffaa353c)
NSTUB(AllocateUncacheableMemory, 0xff83941c)
NSTUB(Close, 0xff8359b0)
NSTUB(CreateTask, 0xff81e5b4)
NSTUB(DeleteFile_Fut, 0xff83533c)
// ERROR: EnterToCompensationEVF is not found!
NSTUB(ExecuteEventProcedure, 0xff889904)
// ERROR: ExitFromCompensationEVF is not found!
// Best match: 57%
NSTUB(ExitTask, 0xff81e844)
NSTUB(Fclose_Fut, 0xff8354b8)
NSTUB(Feof_Fut, 0xff8356a4)
NSTUB(Fflush_Fut, 0xff8356e0)
NSTUB(Fgets_Fut, 0xff83560c)
NSTUB(Fopen_Fut, 0xff835478)
NSTUB(Fread_Fut, 0xff835564)
NSTUB(FreeMemory, 0xffaa3534)
// Best match: 91%
NSTUB(FreeUncacheableMemory, 0xff83945c)
NSTUB(Fseek_Fut, 0xff835658)
NSTUB(Fwrite_Fut, 0xff8355b8)
// Best match: 52%
NSTUB(GetBatteryTemperature, 0xff8635d8)
// Best match: 52%
NSTUB(GetCCDTemperature, 0xff863564)
// Best match: 85%
NSTUB(GetCurrentAvValue, 0xff95c230)
NSTUB(GetDrive_ClusterSize, 0xff86fc80)
NSTUB(GetDrive_FreeClusters, 0xff86fce0)
NSTUB(GetDrive_TotalClusters, 0xff86fcb4)
// Best match: 64%
NSTUB(GetFocusLensSubjectDistance, 0xff95a804)
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xff95ac4c)
// Best match: 96%
NSTUB(GetOpticalTemperature, 0xff86364c)
// Best match: 66%
NSTUB(GetParameterData, 0xff99687c)
// Best match: 72%
NSTUB(GetPropertyCase, 0xff88d6b0)
// Best match: 96%
NSTUB(GetSystemTime, 0xffaa3594)
// Best match: 74%
NSTUB(GetZoomLensCurrentPoint, 0xff95ee0c)
NSTUB(GetZoomLensCurrentPosition, 0xffa967a0)
// Best match: 64%
NSTUB(IsStrobeChargeCompleted, 0xff8db3f0)
NSTUB(LocalTime, 0xff887278)
// Best match: 93%
NSTUB(LockMainPower, 0xff895344)
// ERROR: Lseek is not found!
// Best match: 92%
NSTUB(MakeDirectory_Fut, 0xff8353b0)
// Best match: 57%
NSTUB(MoveFocusLensToDistance, 0xffb031cc)
// Best match: 58%
NSTUB(MoveZoomLensWithPoint, 0xffaa0b60)
// Best match: 62%
NSTUB(NewTaskShell, 0xff88d15c)
NSTUB(Open, 0xff835958)
// ERROR: PT_PlaySound is not found!
// Best match: 86%
NSTUB(PostLogicalEventForNotPowerType, 0xff893170)
// Best match: 92%
NSTUB(PostLogicalEventToUI, 0xff8931bc)
NSTUB(Read, 0xff81ab78)
NSTUB(ReadFastDir, 0xffa84270)
// ERROR: RefreshPhysicalScreen is not found!
// ERROR: Remove is not found!
// Best match: 53%
NSTUB(RenameFile_Fut, 0xff835474)
// ALT: NSTUB(RenameFile_Fut, 0xffa7057c) // 8/7
// ALT: NSTUB(RenameFile_Fut, 0xffa705cc) // 8/7
// Best match: 96%
NSTUB(Restart, 0xff83ab74)
// Best match: 93%
NSTUB(SetAutoShutdownTime, 0xff8953b8)
// Best match: 81%
NSTUB(SetCurrentCaptureModeType, 0xff89cb1c)
// Best match: 55%
NSTUB(SetFileTimeStamp, 0xff94a8dc)
// Best match: 64%
NSTUB(SetLogicalEventActive, 0xff895094)
// Best match: 68%
NSTUB(SetParameterData, 0xff996758)
// Best match: 89%
NSTUB(SetPropertyCase, 0xff88d5ac)
// Best match: 92%
NSTUB(SleepTask, 0xff8390a0)
// Best match: 60%
NSTUB(TakeSemaphore, 0xff838d68)
// ERROR: TurnOffBackLight is not found!
// ERROR: TurnOnBackLight is not found!
// ERROR: UIFS_WriteFirmInfoToFile is not found!
// Best match: 93%
NSTUB(UnlockMainPower, 0xff895298)
NSTUB(UpdateMBROnFlash, 0xff813f74)
NSTUB(VbattGet, 0xff831e08)
NSTUB(Write, 0xff835a40)
NSTUB(_log, 0xffb3de8c)
NSTUB(_log10, 0xffb3cdd0)
NSTUB(_pow, 0xffb3cf40)
NSTUB(_sqrt, 0xffb3f1f4)
NSTUB(add_ptp_handler, 0xffa4de90)
NSTUB(close, 0xff81a990)
NSTUB(closedir, 0xffa840f8)
// Best match: 71%
NSTUB(closefastdir, 0xffa8440c)
// Best match: 95%
NSTUB(free, 0xff814138)
// Best match: 86%
NSTUB(kbd_p1_f, 0xff833600)
// Best match: 86%
NSTUB(kbd_p1_f_cont, 0xff83360c)
// Best match: 86%
NSTUB(kbd_p2_f, 0xff832ec0)
// Best match: 51%
NSTUB(kbd_pwr_off, 0xff86043c)
// ERROR: kbd_pwr_on is not found!
// Best match: 84%
NSTUB(kbd_read_keys, 0xff833584)
// Best match: 78%
NSTUB(kbd_read_keys_r2, 0xff85fbb8)
// ALT: NSTUB(kbd_read_keys_r2, 0xff85fb9c) // 17/5
NSTUB(lseek, 0xff835acc)
NSTUB(malloc, 0xff8140dc)
NSTUB(memcmp, 0xff8203ec)
NSTUB(memcpy, 0xff83ea1c)
NSTUB(memset, 0xffa13910)
NSTUB(mkdir, 0xff835e24)
NSTUB(mktime_ext, 0xff8ab050)
NSTUB(open, 0xff81a8e0)
NSTUB(opendir, 0xffa8413c)
// ERROR: openfastdir is not found!
NSTUB(qsort, 0xffaf38dc)
// Best match: 95%
NSTUB(rand, 0xff8204f4)
NSTUB(read, 0xff81ab78)
// ERROR: readfastdir is not found!
// Best match: 82%
NSTUB(reboot_fw_update, 0xffa89780)
// ERROR: rename is not found!
// Best match: 95%
NSTUB(srand, 0xff8204e8)
NSTUB(stat, 0xff835b08)
// ALT: NSTUB(stat, 0xff86d0c4) // 30/0
// Best match: 61%
NSTUB(strcat, 0xff813f38)
// Best match: 56%
NSTUB(strchr, 0xff813fc0)
NSTUB(strcmp, 0xff8203a8)
NSTUB(strcpy, 0xff820390)
NSTUB(strftime, 0xff8aaa58)
NSTUB(strlen, 0xff81400c)
NSTUB(strncmp, 0xff813f74)
// Best match: 73%
NSTUB(strncpy, 0xff813f38)
// Best match: 71%
NSTUB(strrchr, 0xff83e9f4)
// ALT: NSTUB(strrchr, 0xff8aa820) // 18/8
// Best match: 96%
NSTUB(strtol, 0xff83ecfc)
NSTUB(strtolx, 0xff83eb00)
// Best match: 86%
NSTUB(time, 0xff8877f0)
NSTUB(vsprintf, 0xff820354)
NSTUB(write, 0xff81abd8)
