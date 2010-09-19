#include "stubs_asm.h"
NHSTUB(TurnOffBackLight, 0xFF8A33A8)
NHSTUB(TurnOnBackLight,  0xFF8A3390)
NHSTUB(GiveSemaphore,    0xFF838E08)
NHSTUB(GetKbdState,      0xFF8603D4)
NHSTUB(kbd_read_keys_r2, 0xFF85FB44)
NHSTUB(SetScriptMode,    0xFF810F4C)
NHSTUB(EnterToCompensationEVF,  0xFF8373A8)
NHSTUB(ExitFromCompensationEVF, 0xFF8373EC)
NHSTUB(PT_PlaySound,            0xFF882344)
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF98047C)
NHSTUB(MakeAFScan,               0xFF96604C)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF844CB0)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF844D88)
NHSTUB(Remove,                   0xFF8359B4)
NHSTUB(readfastdir,              0xFFA8416C)
NHSTUB(WriteSDCard,              0xFF94B66C)
NHSTUB(UnlockAF,                 0xFF837160)
NHSTUB(DoAFLock,                 0xFF837128)
NHSTUB(UnsetZoomForMovie,        0xFF99CDB4)
NHSTUB(PutInNdFilter,            0xFFB00E18)
NHSTUB(PutOutNdFilter,           0xFFB00E50)
NHSTUB(closefastdir,             0xFFA83FF4)
NHSTUB(openfastdir,              0xFFA84038)
NHSTUB(kbd_p1_sub,               0xFF833554)
NHSTUB(ExportToEventProcedure,   0xFF88A26C)
NHSTUB(UnRegisterEvntProc,       0xFF8897A0)
NHSTUB(SetFileTimeStamp,         0xFF835C0C) 
NHSTUB(GetLogToFile,             0xFF96D020)
NHSTUB(apex2us,                  0xFFA1484C)
NHSTUB(strrchr,                  0xFF813FE4) 
NHSTUB(strncpy,                  0xff813f38) 
NHSTUB(strcat,                   0xFF8AA728) 
NHSTUB(LEDDrive,                 0xFF85F624)
NHSTUB(RefreshPhysicalScreen,    0xFFA0FE64)
NHSTUB(ScreenLock,               0xFFA11094)
NHSTUB(ScreenUnlock,             0xFFA110BC)
NHSTUB(Lseek,                    0xFF835A9C) // same address as lseek
NHSTUB(rename,                   0xFF835A5C) 
NHSTUB(RenameFile_Fut,           0xFF835278)
NHSTUB(Restart,                  0xFF83AB40)

// nullsubs
NHSTUB(kbd_pwr_on, 0xFF810B04) // nullsub
NHSTUB(rewinddir,  0xFF810B04)  // nullsub
NHSTUB(Unmount_FileSystem, 0xFF810B04)  // nullsub
NHSTUB(Mount_FileSystem,   0xFF810B04)  // nullsub
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810B04)  // nullsub
