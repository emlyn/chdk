#include "stubs_asm.h"

//CORRECTIONS
NHSTUB(strrchr,                     0xFF8941C0)
NHSTUB(kbd_read_keys_r2,            0xFF842490)

//REQUIRED
NHSTUB(DoAFLock,                    0xFF825B84)
NHSTUB(UnlockAF,                    0xFF825BC8)
NHSTUB(DebugAssert,                 0xFF81BCF0)
NHSTUB(StartFactoryModeController,  0xFF846378)
NHSTUB(IsFactoryMode,               0xFF846308)
NHSTUB(taskcreate_TempCheck,        0xFF820EAC)
NHSTUB(GetAEIntegralServiceMode_0,  0xFF82ADA0)
NHSTUB(taskcreate_FaceFrame,        0xFF880840)
NHSTUB(taskcreate_DSITask,          0xFF880A9C)
NHSTUB(taskcreate_CommonDrivers,    0xFF878F94)
NHSTUB(taskcreate_StartupImage,     0xFF82A4E8)
NHSTUB(GetVRAMHPixelsSize_1,        0xFF87ABE0)
NHSTUB(PostLogicalEventToUI,        0xFF873244)
NHSTUB(PTM_SetCurrentCaptureMode,   0xFF875C44)
NHSTUB(StartGUISystem,              0xFF893FC8)
NHSTUB(RestartDevice,               0xFF829DE0)
NHSTUB(j_PTM_SetCurrentItem,        0xFF95CE64)
NHSTUB(CreateController,            0xFF872A3C)
NHSTUB(IsControlEventActive,        0xFF8750A8)
NHSTUB(UnsetZoomForMovie,           0xFF962E40)

//Extra
NHSTUB(StartDiskboot,               0xFF829FA4)
NHSTUB(PT_GetPropertyCaseString,    0xFF86CE8C)
NHSTUB(PT_SetPropertyCaseString,    0xFF86CF8C)
NHSTUB(GetVRAMHPixelsSize_0,        0xFF85CED4)
NHSTUB(KernelCreateTask,            0xFF81BAF0)
NHSTUB(PTM_GetCurrentItem,          0xFF875D6C)
NHSTUB(PutInNdFilter,               0xFFA83868)
NHSTUB(PutOutNdFilter,              0xFFA8389C)
NHSTUB(PT_PlaySound,                0xFF85B1C4)

//New
NHSTUB(LEDDrive,                    0xFF842068)
NHSTUB(WriteSDCard,                 0xFF922764)
NHSTUB(PostLogicalEventForNotPowerType, 0xFF8731F8)
NHSTUB(apex2us,                     0xFF9B2794)

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
