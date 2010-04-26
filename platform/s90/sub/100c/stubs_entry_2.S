#include "stubs_asm.h"
//FOUND
NHSTUB(TurnOffBackLight,  0xFF8A494C)
NHSTUB(TurnOnBackLight,  0xFF8A4934)
NHSTUB(EnterToCompensationEVF, 0xFF836D3C)
NHSTUB(ExitFromCompensationEVF, 0xFF836D80)
NHSTUB(Lseek, 0xFF835530)
NHSTUB(PT_PlaySound, 0xFF88180C)
NHSTUB(RefreshPhysicalScreen, 0xFFA08EEC)
NHSTUB(Remove, 0xFF835448)
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF97EA00)
NHSTUB(openfastdir, 0xFFA7D614)
NHSTUB(readfastdir, 0xFFA7D748)
NHSTUB(rename, 0xFF8354F0)
NHSTUB(LEDDrive, 0xFF85D648)
NHSTUB(SetScriptMode, 0xFF810F4C) 
NHSTUB(apex2us, 0xFFA0D7A8)
NHSTUB(MakeAFScan, 0xFF9646D4)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF844700)
NHSTUB(WriteSDCard, 0xFF94A55C)
NHSTUB(UnlockAF, 0xFF836BD0)
NHSTUB(DoAFLock, 0xFF836B98)
NHSTUB(UnsetZoomForMovie, 0xFF8A0EB4)


NHSTUB(ScreenLock, 0xFFA0A10C) 
NHSTUB(ScreenUnlock,0xFFA0A134) 

//NOTFOUND - nullsub
NHSTUB(kbd_pwr_off, 0xFF810B04)
NHSTUB(kbd_pwr_on, 0xFF810B04)//cannot locate
NHSTUB(rewinddir, 0xFF810B04)//cannot locate
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810B04)//cannot locate
NHSTUB(Unmount_FileSystem, 0xFF810B04)//cannot locate
NHSTUB(Mount_FileSystem, 0xFF810B04)//cannot locate

NHSTUB(strrchr, 0xFF813FE4) // correction for sig.finder addr.
NHSTUB(strncpy, 0xFF813F38) // sigfinder founds same addr. for strcat
NHSTUB(strcat, 0xFF8ABAC0)  // sigfinder founds same addr. for strncpy
NHSTUB(SetFileTimeStamp, 0xFF8356A0) // filename instead of filehandle
NHSTUB(ExportToEventProcedure,0xFF889734)
NHSTUB(UnRegisterEvntProc,0xFF888C68)
NHSTUB(GetLogToFile,0xFF96B2C0) // OK
NHSTUB(EraseLogSector,0xFF96B2E8) // OK
NHSTUB(closefastdir, 0xFFA7D5D0)
NHSTUB(GiveSemaphore,   0xFF8387E8)
NHSTUB(RenameFile_Fut, 0xFF834D0C)
NHSTUB(ExpCtrlTool_StopContiAE, 0xFF8447D8) //OK
NHSTUB(GetKbdState,      0xFF85E258) //OK


