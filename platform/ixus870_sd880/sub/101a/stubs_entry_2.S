#include "stubs_asm.h"

#define NULL_SUB 0xFF81093C

// Not set in stubs_entry.S

NHSTUB(EnterToCompensationEVF, 0xFF82582C)  // via aExpcompOn
NHSTUB(ExitFromCompensationEVF, 0xFF825870)  // via aExpcompOff
NHSTUB(RefreshPhysicalScreen, 0xFF9B8424)  // via aScreenunlock
NHSTUB(TurnOffBackLight, 0xFF886078)  // via aTurnofbacklig
//NHSTUB(VbattGet, 0xFF820570)  // called by eventproc_export_VbattGet
NHSTUB(kbd_pwr_on,NULL_SUB)
//NHSTUB(kbd_read_keys, 0xFF821BA4)  // first call in kbd_p1_f
NHSTUB(strchr, 0xFF892790)  // search for "AND R2, R1, #0xFF" (E20120FF)
NHSTUB(vsprintf, 0xFF81CAF8)  // via eventproc_export_CPrintf (call before aCprintfSizeOve)


// Used outside the range of stubs_entry.S generation

NHSTUB(PostLogicalEventForNotPowerType, 0xFF876CA4) // eventproc_export_PostLogicalEventForNotPowerType
NHSTUB(LEDDrive, 0xFF8459E8) // via eventproc_export_LEDDrive
NHSTUB(apex2us, 0xFF9B9440)  // via capt_seq.c
NHSTUB(WriteSDCard, 0xFF918858) // via _sub_FF85522C_Mounter.c__0, call after debug, then last LDR
NHSTUB(UnlockAF, 0xFF825610)  // via aAfUnlock
NHSTUB(DoAFLock, 0xFF8255D8)  // via aAfLock
NHSTUB(rewinddir,NULL_SUB)
NHSTUB(SetZoomActuatorSpeedPercent,NULL_SUB)
NHSTUB(Mount_FileSystem,NULL_SUB)
NHSTUB(Unmount_FileSystem,NULL_SUB)
NHSTUB(platformsub_kbd_fetch_data, 0xFF846248)  // GetKbdState
NHSTUB(UnsetZoomForMovie,0xFF9607A0) // via aZoomcon_Unsetz (used ixus980 dump)
//NHSTUB(PutInNdFilter,0xFFA9C1D4)   // function table
NHSTUB(PutInNdFilter,0xFFA3AD28)   // function table TurnOnNdFilter (used ixus980)
//NHSTUB(PutOutNdFilter,0xFFA9C20C)  // function table
NHSTUB(PutOutNdFilter,0xFFA3AD4C)  // function table TurnOffNdFilter (used ixus980)
NHSTUB(ScreenLock, 0xFF9B83D0)  // via aScreenlock
NHSTUB(MakeAFScan,  0xFF933E54)  // via aSsprepareseqba (function with most uses)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF830D00)  // via aStartcontiae
NHSTUB(set_control_event, 0xFF878894) // via eventproc_export_IsControlEventActive (last call)
NHSTUB(PB2Rec, 0xFF87BF0C) // via aAcPb2rec
NHSTUB(Rec2PB, 0xFF87A8A4) // via aAcRec2pb


// Corrections for uncertain entries in stubs_entry.S

//NHSTUB(AllocateUncacheableMemory, 0xFF827B68)  // via task_UartLog, 2nd call
// NHSTUB(ExitTask, 0xff81b184)  // ok, eventproc_export_ExitTask
// NHSTUB(FreeUncacheableMemory, 0xff827ba8)  // ok, via task_UartLog, call before the last one
// NHSTUB(GetCurrentTargetDistance, 0xff927344)  // ok, _sub_???__FocusLensController.c__0
// NHSTUB(GetDrive_ClusterSize, 0xff8554ac)  // ok, via _sub_???__Mounter.c__0
NHSTUB(GetDrive_FreeClusters, 0xff855514)  // via _sub_???__Mounter.c__1424
NHSTUB(GetDrive_TotalClusters, 0xff85557c)  // ok, via _sub_???__Mounter.c__0
// NHSTUB(GetFocusLensSubjectDistance, 0xffa3a710) // ok, via aSubjectdista_0
// NHSTUB(GetOpticalTemperature, 0xff848d64)  // ok, via GetCCDTemperature (first BEQ loc_)
// NHSTUB(GetParameterData, 0xff95a770)  // ok, via first call in eventproc_export_PTM_RestoreUIProperty
// NHSTUB(GetPropertyCase, 0xff8717a8)  // ok, PT_GetPropertyCaseString_0
// NHSTUB(GetSystemTime, 0xffa3d910)  // ok, GetSystemTime
NHSTUB(GetZoomLensCurrentPoint, 0xFF92B9CC)  // function table
// NHSTUB(IsStrobeChargeCompleted, 0xff8ab714)  // ok, via _sub_???__EFCharge.c__856
// NHSTUB(LockMainPower, 0xff878ec8)  // ok, eventproc_export_LockMainPower
// NHSTUB(MakeDirectory_Fut, 0xff823414)  // ok, visual compare
// NHSTUB(MoveFocusLensToDistance, 0xffa9e3fc)  // ok, visual compare
// NHSTUB(MoveZoomLensWithPoint, 0xffa3aec4)  // ok, visual compare + func.tbl.
// NHSTUB(NewTaskShell, 0xff871250)  // ok, NewTaskShell
// NHSTUB(RenameFile_Fut, 0xff82334c)  // ok, visual compare
// NHSTUB(SetAutoShutdownTime, 0xff878f3c)  // ok, eventproc_export_SetAutoShutdownTime
// NHSTUB(SetParameterData, 0xff95a6e0)  // ok, PTM_BackupUIProperty
//NHSTUB(SetPropertyCase, 0xff8716a0)  // PT_GetPropertyCaseString
// NHSTUB(SleepTask, 0xff8277ec)  // ok, eventproc_export_SleepTask
// NHSTUB(TakeSemaphore, 0xff8274b4)  // ok, eventproc_export_TakeSemaphore
// NHSTUB(TurnOnBackLight, 0xff886060)  // ok, via aTurnonbackligh
// NHSTUB(UIFS_WriteFirmInfoToFile, 0xff94b858)  // ok, via usage of aUifs_writefirm, look for value of R1
// NHSTUB(UnlockMainPower, 0xff878e1c)  // ok, eventproc_export_UnlockMainPower
// NHSTUB(UpdateMBROnFlash, 0xff8552ec)  // ok, visual compare
// NHSTUB(kbd_p1_f, 0xff821ca0)  // ok, kbd_p1_f
// NHSTUB(kbd_p1_f_cont, 0xff821cac)  // ok, kbd_p1_f+0xc
// NHSTUB(kbd_p2_f, 0xff8214b8)  // ok, kbd_p2_f
NHSTUB(kbd_pwr_off,NULL_SUB)
//NHSTUB(kbd_read_keys_r2, 0xff845de0)  // visual compare (auto generated address was slightly of)
NHSTUB(qsort, 0xffa84fc8)  // search 01 00 50 E1 1E FF 2F 01
// NHSTUB(rand, 0xff81ccbc)  // ok, visual compare (and via aRandsem)
// NHSTUB(srand, 0xff81ccb0)  // ok, visual compare (and via aRandsem)
// NHSTUB(strncmp, 0xff892744)  // ok, visual compare
NHSTUB(strrchr, 0xff9b8750)  // via memset (strrchr is above it)
// NHSTUB(time, 0xff86b83c)  // ok, via _sub_???_SystemTime.c__1
NHSTUB(SetScriptMode, 0xFF878C68)  // string
NHSTUB(Restart, 0xFF8293DC)
