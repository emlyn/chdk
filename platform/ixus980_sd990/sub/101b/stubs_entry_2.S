#include "stubs_asm.h"
// not found correctly by finsig
//NHSTUB(AllocateUncacheableMemory, 0xFF827F3C) // add 0x40 to size then call malloc. sig_ref found 0xff827f48
//NHSTUB(kbd_read_keys_r2, 0xFF849F24) // similar to a720, but called at end of kbd_read_keys
NHSTUB(GetDrive_FreeClusters, 0xFF8596B0) // similar to a720, based on calling functions
NHSTUB(GetDrive_TotalClusters, 0xFF85967C) // similar to a720, callers and constants
//NHSTUB(SetPropertyCase, 0xFF876250) // from PT_SetPropertyCaseInt
NHSTUB(qsort, 0xFFA93DC0) // similar to qsort, near sscanf


// not in sig_ref
NHSTUB(UnsetZoomForMovie, 0xFF9689EC) // string "ZoomCon_UnsetZoomForMovie"
NHSTUB(ScreenLock,0xFF9C7C40) // related to RefreshPysicalScreen/ScreenUnLock
NHSTUB(ScreenUnLock,0xFF9C7C94) // AKA RefreshPhysicalScreen called from PT_LCD_BkColorDef, similar to sd1100
NHSTUB(PutInNdFilter,0xFFA46ED0) // string TurnOnNdFilter
NHSTUB(PutOutNdFilter,0xFFA46EF4) // string TurnOffNdFilter
NHSTUB(DoAFLock,0xFF863A80) // PT_DoAFLock 
NHSTUB(UnlockAF,0xFF863A90) // PT_UnlockAF 
NHSTUB(WriteSDCard,0xFF9210A4) // similar to SX10, search on BOOTDISK and SCRIPT
NHSTUB(LEDDrive,0xFF849B2C) // string LEDDrive
NHSTUB(PostLogicalEventForNotPowerType,0xFF87B858) // string PostLogicalEventForNotPowerType

// not found by finsig
NHSTUB(EnterToCompensationEVF,0xFF825B7C) // string "ExpComp On" NOTE old "SSAPI::EnterToCompensationEVF" not found, but propcase 0xCF is used in both
NHSTUB(ExitFromCompensationEVF,0xFF825BC0) // string "ExpComp Off"
NHSTUB(RefreshPhysicalScreen,0xFF9C7C94) // called from PT_LCD_BkColorDef, similar to sd1100
NHSTUB(TurnOffBackLight,0xFF88ACA0) // string
//NHSTUB(VbattGet,0xFF820560) // string, eventproc
NHSTUB(kbd_pwr_on,0xFF81093C) // NULLSUB ... no corresponding call in kbd_read_keys ?
//NHSTUB(kbd_read_keys,0xFF821C24) // via 0xFF821D20 kbd_p1_f 
NHSTUB(kbd_pwr_off,0xFF81093C) // NULLSUB ... pwr_on doesn't exist, last function in readkeys looks more like kbd_read_keys_r2
NHSTUB(strchr,0xFF897640) 
//NHSTUB(vsprintf,0xFF81CAE8) // via CPrintf

// These don't exist/aren't found in dryos
NHSTUB(Mount_FileSystem,0xFF81093C) // NULLSUB
NHSTUB(Unmount_FileSystem,0xFF81093C) // NULLSUB
NHSTUB(rewinddir,0xFF81093C) // NULLSUB
NHSTUB(SetZoomActuatorSpeedPercent,0xFF81093C) // NULLSUB

