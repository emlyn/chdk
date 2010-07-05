#include "stubs_asm.h"
// not found correctly by finsig

NHSTUB(AllocateUncacheableMemory, 0xFFC17288) // Calls j_malloc
NHSTUB(UpdateMBROnFlash, 0xFFC3F674) // Autodetect was too early
NHSTUB(qsort, 0xFFE1CC78) // Similar to SD990's qsort

//Autofound Required!
NHSTUB(TurnOnBackLight,0xFFC68A90)	//"TurnOnBackLight" string
NHSTUB(TurnOffBackLight,0xFFC68AA8)	//"TurnOffBackLight" string

NHSTUB(EnterToCompensationEVF,0xFFC15348)	//Look for ExpOn
NHSTUB(ExitFromCompensationEVF,0xFFC1538C)	//Look for ExpOff

//NHSTUB(GetCurrentTargetDistance, 0xFFCCA6B4) // Sub uses "Error GetTargetDistanceResult"
NHSTUB(GetCurrentTargetDistance, 0xFFCF0434) // Yossar: changed to FFCF0434 
NHSTUB(VbattGet,0xFFC10644) // string, eventproc

NHSTUB(vsprintf, 0xFFC0CBA0) // via eventproc_export_CPrintf (call before aCprintfSizeOve)

NHSTUB(PostLogicalEventForNotPowerType, 0xFFC5D1F8) // string "PostLogicalEventForNotPowerType"
//NHSTUB(PT_PlaySound, 0xFFC47A78)
NHSTUB(PT_PlaySound, 0xFFC47764)
    /* Similar to SD780. They said look for "LDRH R0, [R0]"
     * Followed by LDR R1, [R1]. (True, but hard to search like that).
     * I found by looking for "%Y/%m/%d %H:%M:%S" in the function _prior_ to this
     */

NHSTUB(GetOpticalTemperature, 0xFFC33940) // Similar to SD780, which is also not certain.
    // References Temperature.c and near GetBatteryTemperature

NHSTUB(UnsetZoomForMovie, 0xFFD21B70) // string "ZoomCon_UnsetZoomForMovie"

NHSTUB(LEDDrive, 0xFFC3043C) // string "LEDDrive"
NHSTUB(OpLog_Get, 0xFFC58590) // IDA eventproc_export_OpLog.Get
NHSTUB(WriteSDCard, 0xFFCE4118) // Similar to SD990, searched SdCon.c
NHSTUB(DoAFLock, 0xFFC47B8C) // Similar to SD990, AFL and AFL* strings
NHSTUB(UnlockAF, 0xFFC47B9C) // Similar to SD990, AFUL and AFUL* strings

NHSTUB(PutInNdFilter, 0xFFDEADB0) // Yossar: edited
NHSTUB(PutOutNdFilter, 0xFFDEADD4) // Yossar: edited

NHSTUB(kbd_p2_f, 0xFFC116B0) // Similar to SD780, PhySw+1C
NHSTUB(kbd_read_keys, 0xFFC11D80) // Look for LDR R0, =YYYY then,
    // BL GetKbdState then LDR R0, =YYYY
    
NHSTUB(kbd_read_keys_r2, 0xFFC30824) // autodetect basically right, just go to beginning of function
NHSTUB(strchr, 0xFFC6CAD4) // Similar to SD780. AND R2, R1, #0xFF then LDRB R1, [R0]

NHSTUB(ScreenLock, 0xFFD64C2C) // aScreenlock
NHSTUB(ScreenUnLock, 0xFFD64C80) // sScreenunlock
NHSTUB(RefreshPhysicalScreen, 0xFFD64C80) // Same as ScreenUnLock

NHSTUB(GetDrive_FreeClusters, 0xFFC3F874) // Similar to 990 based on callers
NHSTUB(GetDrive_TotalClusters, 0xFFC3F848) // Similar to 990, Above FreeClusters
NHSTUB(GetDrive_ClusterSize, 0xFFC3F81C) // Similar to 990, Above TotalClusters

NHSTUB(kbd_pwr_off, 0xFFC00950) // SD1200 doesn't use
NHSTUB(kbd_pwr_on, 0xFFC00950) // SD1200 doesn't use

// Don't exist in dryos
NHSTUB(Mount_FileSystem, 0xFFC00950) // NULLSUB
NHSTUB(Unmount_FileSystem, 0xFFC00950) // NULLSUB
NHSTUB(rewinddir, 0xFFC00950) // NULLSUB
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00950) // NULLSUB

// could not find
NHSTUB(GetFocusLensSubjectDistance, 0xFFC00950) // NULLSUB
NHSTUB(SetScriptMode, 0xFFC00950) //NULLSUB