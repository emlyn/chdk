#include "stubs_asm.h"
#define NULL_STUB 0xFF8391E0

// all addresses were found by similarity to s90 port unless otherwise stated

// "not found" in stubs_entry.s
NHSTUB(EnterToCompensationEVF, 0xFF838B40)
NHSTUB(ExitFromCompensationEVF, 0xFF838BE4)
NHSTUB(GetDrive_FreeClusters, 0xFF876A28)
NHSTUB(GetParameterData, 0xFF9BBE98)
NHSTUB(Lseek, 0xff83714c)
NHSTUB(PT_PlaySound, 0xFF88B0A8)
NHSTUB(ReadFastDir, 0xFFAD4130)
NHSTUB(RefreshPhysicalScreen, 0xFF8B81C4)
NHSTUB(Remove, 0xFF837064)
NHSTUB(SetParameterData, 0xFF9BBD70)
NHSTUB(TurnOffBackLight, 0xFF8AF278)
NHSTUB(TurnOnBackLight,  0xFF8AF260)
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF9A7D60)
NHSTUB(free, 0xFF814244)
NHSTUB(kbd_read_keys, 0xFF83498C)
NHSTUB(openfastdir, 0xFFAD3FDC)
NHSTUB(qsort, 0xFFB4BE88)								// different from s90
NHSTUB(readfastdir, 0xFFAD4130)							// different from s90
NHSTUB(rename, 0xFF83710C)
NHSTUB(strtol, 0xFF840868)
NHSTUB(Restart, 0xFF83C5B8)

// less than 100% in stubs_entry.s
// some of these may be the same as stubs_entry.s, but that is OK
NHSTUB(Close, 0xff837030)
NHSTUB(ExitTask, 0xff81eb30)
NHSTUB(FreeUncacheableMemory, 0xFF83AE08)
NHSTUB(GetBatteryTemperature, 0xFF869038)
NHSTUB(GetCCDTemperature, 0xFF868FC4)
NHSTUB(GetCurrentAvValue, 0xFF97E4B4)
NHSTUB(GetDrive_ClusterSize, 0xFF8769C8)
NHSTUB(GetDrive_TotalClusters, 0xFF8769FC)
NHSTUB(GetFocusLensSubjectDistance, 0xFF97CB44)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFF97CF90)
NHSTUB(GetOpticalTemperature, 0xFF8690AC)//ok
NHSTUB(GetPropertyCase, 0xFF896414)
NHSTUB(GetSystemTime, 0xFFAFAD34)
NHSTUB(GetZoomLensCurrentPoint, 0xFF980D38)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAE90E8)
NHSTUB(IsStrobeChargeCompleted, 0xFF8EAE58)
NHSTUB(LockMainPower, 0xff89d078)
NHSTUB(MakeDirectory_Fut, 0xFF836A1C)
NHSTUB(MoveFocusLensToDistance, 0xFFB5E3EC)
NHSTUB(MoveZoomLensWithPoint, 0xFFAF7954)
NHSTUB(NewTaskShell, 0xff895e30)						// ida scan says:0xff837598
NHSTUB(Open, 0xFF836FC4)
NHSTUB(PostLogicalEventForNotPowerType, 0xff89aa88)
NHSTUB(PostLogicalEventToUI, 0xff89aad4)
NHSTUB(RenameFile_Fut, 0xFF836914)
NHSTUB(SetAutoShutdownTime, 0xff89d0ec)
NHSTUB(SetCurrentCaptureModeType, 0xff8a5444)
NHSTUB(SetFileTimeStamp, 0xFF8372CC)
NHSTUB(SetLogicalEventActive, 0xff89cdb4)
NHSTUB(SetPropertyCase, 0xFF8962EC)
NHSTUB(SleepTask, 0xff83aa4c)
NHSTUB(TakeSemaphore, 0xff83a714)
NHSTUB(UnlockMainPower, 0xff89cfcc)
NHSTUB(VbattGet, 0xff833188)
NHSTUB(closedir, 0xFFAD3F8C)
NHSTUB(closefastdir, 0xFFAD3F8C)
NHSTUB(kbd_p1_f, 0xFF834A04)
NHSTUB(kbd_p1_f_cont, 0xFF834A10)
NHSTUB(kbd_p2_f, 0xFF83424C)
NHSTUB(kbd_read_keys_r2, 0xFF864EE8)
NHSTUB(lseek, 0xFF83714C)
NHSTUB(mkdir, 0xFF8374CC)
NHSTUB(opendir, 0xFFAD3FDC)
NHSTUB(strcat, 0xFF8B8414)
NHSTUB(strchr, 0xFF8140B4)
NHSTUB(strncpy, 0xFF81402C)
NHSTUB(strlen, 0xff814100)
NHSTUB(time, 0xFF8905D4)

// missing from stubs_entry.s
NHSTUB(LEDDrive, 0xff987118)						// different from s90
NHSTUB(SetScriptMode, 0xff89ce04)					// different from s90
NHSTUB(ScreenLock, 0xFF8B7E50)
NHSTUB(ScreenUnlock, 0xFF8B7EB4)
NHSTUB(apex2us, 0xFFA50D88)
NHSTUB(MakeAFScan, 0xFF9896B4)
NHSTUB(WriteSDCard, 0xFF96DD64)
NHSTUB(UnlockAF, 0xFF8388D8)
NHSTUB(DoAFLock, 0xFF8388A0)
NHSTUB(UnsetZoomForMovie, 0xFF8AB114)
NHSTUB(GetKbdState, 0xFF8655F0)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF84734C)

// could not find in firmware
// we use our own implementaion in wrappers.c
//NHSTUB(srand, NULL_STUB)
//NHSTUB(rand, NULL_STUB)
//NHSTUB(strrchr, NULL_STUB)
// still need NSTUBs to keep finsig happy - reyalp
NSTUB(srand, NULL_STUB)
NSTUB(rand, NULL_STUB)

// could not find on s90 or s95 - ignore
NHSTUB(kbd_pwr_on, NULL_STUB)
NHSTUB(kbd_pwr_off, NULL_STUB)
NHSTUB(rewinddir, NULL_STUB)
NHSTUB(SetZoomActuatorSpeedPercent, NULL_STUB)
NHSTUB(Unmount_FileSystem, NULL_STUB)
NHSTUB(Mount_FileSystem, NULL_STUB)

// added for PTP support
// addresses found by comparing to ixus870 patches
NHSTUB(add_ptp_handler, 0xFFA8E7F4)
NHSTUB(set_control_event, 0xFF89C9A4)
NHSTUB(PB2Rec, 0xFF8A0008)
NHSTUB(Rec2PB, 0xFF8A0048)
NHSTUB(reboot_fw_update, 0xFFAD9550)
