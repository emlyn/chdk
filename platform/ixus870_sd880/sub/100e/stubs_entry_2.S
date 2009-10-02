#include "stubs_asm.h"

#define NULL_SUB 0xFF81093C

// Not set in stubs_entry.S

NHSTUB(EnterToCompensationEVF, 0xFF82582C)  // via aExpcompOn
NHSTUB(ExitFromCompensationEVF, 0xFF825870)  // via aExpcompOff
NHSTUB(RefreshPhysicalScreen, 0xFF9B8420)  // via aScreenunlock
NHSTUB(TurnOffBackLight, 0xFF886078)  // via aTurnofbacklig
NHSTUB(VbattGet, 0xFF820570)  // called by eventproc_export_VbattGet
NHSTUB(kbd_pwr_on,NULL_SUB)
NHSTUB(kbd_read_keys, 0xFF821BA4)  // first call in kbd_p1_f
NHSTUB(strchr, 0xFF892790)  // search for "AND R2, R1, #0xFF" (E20120FF)
NHSTUB(vsprintf, 0xFF81CAF8)  // via eventproc_export_CPrintf (call before aCprintfSizeOve)


// Used outside the range of stubs_entry.S generation

NHSTUB(PostLogicalEventForNotPowerType, 0xFF876CA4) // eventproc_export_PostLogicalEventForNotPowerType
NHSTUB(LEDDrive, 0xFF8459E8) // via eventproc_export_LEDDrive
NHSTUB(apex2us, 0xFF9B943C)  // via capt_seq.c
NHSTUB(WriteSDCard, 0xFF918854) // via _sub_FF85522C_Mounter.c__0, call after debug, then last LDR
NHSTUB(UnlockAF, 0xFF825610)  // via aAfUnlock
NHSTUB(DoAFLock, 0xFF8255D8)  // via aAfLock
NHSTUB(rewinddir,NULL_SUB)
NHSTUB(SetZoomActuatorSpeedPercent,NULL_SUB)
NHSTUB(Mount_FileSystem,NULL_SUB)
NHSTUB(Unmount_FileSystem,NULL_SUB)
NHSTUB(platformsub_kbd_fetch_data, 0xFF846248)  // GetKbdState
NHSTUB(UnsetZoomForMovie,0xFF96079C) // via aZoomcon_Unsetz (used ixus980 dump)
//NHSTUB(PutInNdFilter,0xFFA9C1C4)   // function table
NHSTUB(PutInNdFilter,0xFFA3AD18)   // function table TurnOnNdFilter (used ixus980)
//NHSTUB(PutOutNdFilter,0xFFA9C1FC)  // function table
NHSTUB(PutOutNdFilter,0xFFA3AD3C)  // function table TurnOffNdFilter (used ixus980)
NHSTUB(ScreenLock, 0xFF9B83CC)  // via aScreenlock
NHSTUB(MakeAFScan,  0xFF933E50)  // via aSsprepareseqba (function with most uses)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF830D00)  // via aStartcontiae


// Corrections for uncertain entries in stubs_entry.S

NHSTUB(AllocateUncacheableMemory, 0xFF827B68)  // via task_UartLog, 2nd call
NHSTUB(GetDrive_FreeClusters, 0xff855514)  // via _sub_???__Mounter.c__1424
NHSTUB(GetDrive_TotalClusters, 0xff85557c)  // ok, via _sub_???__Mounter.c__0
NHSTUB(GetZoomLensCurrentPoint, 0xFF92B9C8)  // function table
NHSTUB(SetPropertyCase, 0xff8716a0)  // PT_GetPropertyCaseString
NHSTUB(kbd_pwr_off,NULL_SUB)
NHSTUB(kbd_read_keys_r2, 0xff845de0)  // visual compare (auto generated address was slightly of)
NHSTUB(qsort, 0xffa84fb8)  // search 01 00 50 E1 1E FF 2F 01
NHSTUB(strrchr, 0xff9b874C)  // via memset (strrchr is above it)
