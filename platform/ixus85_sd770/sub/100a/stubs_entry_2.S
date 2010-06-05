#include "stubs_asm.h"

//CORRECTIONS
NHSTUB(strrchr,                     0xFF892128) // OK
//NHSTUB(kbd_read_keys_r2,            0xFF842494) // NAO

//REQUIRED
NHSTUB(DoAFLock,                    0xFF825B84) // OK
NHSTUB(UnlockAF,                    0xFF825BC8) // OK
NHSTUB(DebugAssert,                 0xFF81BCF8) // OK
NHSTUB(StartFactoryModeController,  0xFF84613C) // OK
NHSTUB(IsFactoryMode,               0xFF8460CC) // OK
NHSTUB(taskcreate_TempCheck,        0xFF820EAC) // OK
NHSTUB(GetAEIntegralServiceMode_0,  0xFF82AC44) // OK
NHSTUB(taskcreate_FaceFrame,        0xFF87EB3C) // OK
NHSTUB(taskcreate_DSITask,          0xFF87ED0C) // OK
NHSTUB(taskcreate_CommonDrivers,    0xFF877228) // OK
NHSTUB(taskcreate_StartupImage,     0xFF82A4DC) // OK
NHSTUB(GetVRAMHPixelsSize_1,        0xFF878e54) // OK
NHSTUB(PostLogicalEventToUI,        0xFF872FAC) // OK
NHSTUB(PTM_SetCurrentCaptureMode,   0xFF8740FC) // OK
NHSTUB(StartGUISystem,              0xFF891F30) // OK
NHSTUB(RestartDevice,               0xFF829DE0) // OK
NHSTUB(j_PTM_SetCurrentItem,        0xFF95BE20) // OK
NHSTUB(CreateController,            0xFF8727A4) // OK
NHSTUB(IsControlEventActive,        0xFF87361C) // OK
NHSTUB(UnsetZoomForMovie,           0xFF961EBC) // OK

//Extra
NHSTUB(StartDiskboot,               0xFF829FA4) // OK
NHSTUB(PT_GetPropertyCaseString,    0xFF86CCDC) // OK
NHSTUB(PT_SetPropertyCaseString,    0xFF86CDDC) // OK
NHSTUB(GetVRAMHPixelsSize_0,        0xFF85CD44) // OK
NHSTUB(KernelCreateTask,            0xFF81BAF0) // OK
NHSTUB(PTM_GetCurrentItem,          0xFF874224) // OK
NHSTUB(PutInNdFilter,               0xFFA7CBDC) // OK
NHSTUB(PutOutNdFilter,              0xFFA7CC10) // OK

//New
NHSTUB(LEDDrive,                    0xFF842174) // OK
NHSTUB(WriteSDCard,                 0xFF920458) // OK
NHSTUB(PostLogicalEventForNotPowerType, 0xFF872F60) // OK
NHSTUB(apex2us,                     0xFF9AD5A8) // OK

//Nullsubs
#define do_nothing 0xFFA7D820
NHSTUB(Mount_FileSystem,            do_nothing)
NHSTUB(Unmount_FileSystem,          do_nothing)
NHSTUB(SetZoomActuatorSpeedPercent, do_nothing)
NHSTUB(rewinddir,                   do_nothing)
NHSTUB(nullsub_35,                  do_nothing)
NHSTUB(nullsub_37,                  do_nothing)
NHSTUB(unknown_libname_80,          do_nothing)
NHSTUB(unknown_libname_96,          do_nothing)
NHSTUB(j_unknown_libname_73,        do_nothing)

NHSTUB(SetScriptMode,        0xFF8736DC) // "SetScriptMode" OK
