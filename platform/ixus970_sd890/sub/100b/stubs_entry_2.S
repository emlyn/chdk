#include "stubs_asm.h"

//CORRECTIONS
NHSTUB(strrchr,                     0xFF89423C)
//NHSTUB(kbd_read_keys_r2,            0xFF842494)

//REQUIRED
NHSTUB(DoAFLock,                    0xFF825B88)
NHSTUB(UnlockAF,                    0xFF825BCC)
NHSTUB(DebugAssert,                 0xFF81BCF8)
NHSTUB(StartFactoryModeController,  0xFF84637C)
NHSTUB(IsFactoryMode,               0xFF84630C)
NHSTUB(taskcreate_TempCheck,        0xFF820EAC)
NHSTUB(GetAEIntegralServiceMode_0,  0xFF82ADA4)
NHSTUB(taskcreate_FaceFrame,        0xFF8808BC)
NHSTUB(taskcreate_DSITask,          0xFF880B18)
NHSTUB(taskcreate_CommonDrivers,    0xFF879010)
NHSTUB(taskcreate_StartupImage,     0xFF82A4EC)
NHSTUB(GetVRAMHPixelsSize_1,        0xFF87AC5C)
NHSTUB(PostLogicalEventToUI,        0xFF8732C0)
NHSTUB(PTM_SetCurrentCaptureMode,   0xFF875CC0)
NHSTUB(StartGUISystem,              0xFF894044)
NHSTUB(RestartDevice,               0xFF829DE4)
NHSTUB(j_PTM_SetCurrentItem,        0xFF95CEF4)
NHSTUB(CreateController,            0xFF872AB8)
NHSTUB(IsControlEventActive,        0xFF875124)
NHSTUB(UnsetZoomForMovie,           0xFF962ED0)

//Extra
NHSTUB(StartDiskboot,               0xFF829FA8)
NHSTUB(PT_GetPropertyCaseString,    0xFF86CF08)
NHSTUB(PT_SetPropertyCaseString,    0xFF86D008)
NHSTUB(GetVRAMHPixelsSize_0,        0xFF85CF50)
NHSTUB(KernelCreateTask,            0xFF81BAF0)
NHSTUB(PTM_GetCurrentItem,          0xFF875DE8)
NHSTUB(PutInNdFilter,               0xFFA838F8)
NHSTUB(PutOutNdFilter,              0xFFA8392C)

//New
NHSTUB(LEDDrive,                    0xFF84206C)
NHSTUB(WriteSDCard,                 0xFF9227E0)
NHSTUB(PostLogicalEventForNotPowerType, 0xFF873274)
NHSTUB(apex2us,                     0xFF9B2824)

//Nullsubs
NHSTUB(Mount_FileSystem,            0xFF810948)
NHSTUB(Unmount_FileSystem,          0xFF810948)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810948)
NHSTUB(rewinddir,                   0xFF810948)
NHSTUB(nullsub_35,                  0xFF810948)
NHSTUB(nullsub_37,                  0xFF810948)
NHSTUB(unknown_libname_80,          0xFF810948)
NHSTUB(unknown_libname_96,          0xFF810948)
NHSTUB(j_unknown_libname_73,        0xFF810948)
