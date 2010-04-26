#include "stubs_asm.h"

NHSTUB(TurnOffBackLight, 0xFF8A49C8) //OK
NHSTUB(TurnOnBackLight,  0xFF8A49B0) //OK
NHSTUB(EnterToCompensationEVF, 0xFF836D3C) //OK
NHSTUB(ExitFromCompensationEVF, 0xFF836D80) //OK
NHSTUB(Lseek, 0xFF835530) //OK
NHSTUB(PT_PlaySound, 0xFF881888) //OK
NHSTUB(RefreshPhysicalScreen, 0xFFA090FC) //OK
NHSTUB(Remove, 0xFF835448) //OK
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF97EC10) //OK
NHSTUB(openfastdir, 0xFFA7D824) //OK
NHSTUB(readfastdir, 0xFFA7D958) //OK
NHSTUB(rename, 0xFF8354F0) //OK
NHSTUB(LEDDrive, 0xFF85D648) //OK
NHSTUB(SetScriptMode, 0xFF810F4C) //OK
NHSTUB(apex2us, 0xFFA0D9B8) //ok
NHSTUB(MakeAFScan, 0xFF9648E4) //OK
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF844700) //OK
NHSTUB(WriteSDCard, 0xFF94A63C) //OK
NHSTUB(UnlockAF, 0xFF836BD0) //OK
NHSTUB(DoAFLock, 0xFF836B98) //OK
NHSTUB(UnsetZoomForMovie, 0xFF8A0F30) // OK
NHSTUB(ScreenLock, 0xFFA0A31C) //OK
NHSTUB(ScreenUnlock,0xFFA0A344) //OK

//nullsub

NHSTUB(kbd_pwr_on, 0xFF810B04)//cannot locate
NHSTUB(rewinddir, 0xFF810B04)//cannot locate
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810B04)//cannot locate
NHSTUB(Unmount_FileSystem, 0xFF810B04)//cannot locate
NHSTUB(Mount_FileSystem, 0xFF810B04)//cannot locate
NSTUB(kbd_pwr_off, 0xFF833350)

NHSTUB(strrchr, 0xFF813FE4) // correction for sig.finder addr.
NHSTUB(strncpy, 0xFF813F38) // sigfinder founds same addr. for strcat
NHSTUB(strcat, 0xFF8ABB3C)  // sigfinder founds same addr. for strncpy
NHSTUB(SetFileTimeStamp, 0xFF8356A0) // filename instead of filehandle
NHSTUB(ExportToEventProcedure,0xFF8897B0)
NHSTUB(UnRegisterEvntProc,0xFF888CE4)
NHSTUB(GetLogToFile,0xFF96B4D0) // OK
NHSTUB(EraseLogSector,0xFF96B4F8) // OK
NHSTUB(closefastdir, 0xFFA7D7E0) //OK
NHSTUB(GiveSemaphore,   0xFF8387E8) //OK
NHSTUB(kbd_p1_sub, 0xFF8335B4)//OK ?
NHSTUB(RenameFile_Fut, 0xFF834D0C) //OK
NHSTUB(ExpCtrlTool_StopContiAE, 0xFF8447D8) // OK
NHSTUB(GetKbdState,      0xFF85E258)


