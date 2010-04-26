#include "stubs_asm.h"

NHSTUB(TurnOffBackLight, 0xFF8A4978)
NHSTUB(TurnOnBackLight,  0xFF8A4960)
NHSTUB(EnterToCompensationEVF, 0xFF836D3C)
NHSTUB(ExitFromCompensationEVF, 0xFF836D80)
NHSTUB(Lseek, 0xFF835530)
NHSTUB(PT_PlaySound, 0xFF881838)
NHSTUB(RefreshPhysicalScreen, 0xFFA08F40)
NHSTUB(Remove, 0xFF835448)
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF97EA54)
NHSTUB(openfastdir, 0xFFA7D668)
NHSTUB(readfastdir, 0xFFA7D79C)
NHSTUB(rename, 0xFF8354F0)
NHSTUB(LEDDrive, 0xFF85D648)
NHSTUB(SetScriptMode, 0xFF810F4C)
NHSTUB(apex2us, 0xFFA0D7FC)
NHSTUB(MakeAFScan, 0xFF964728)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF844700)
NHSTUB(WriteSDCard, 0xFF94A588)
NHSTUB(UnlockAF, 0xFF836BD0)
NHSTUB(DoAFLock, 0xFF836B98)
NHSTUB(UnsetZoomForMovie, 0xFF8A0EE0) // Check in other FW too


NHSTUB(ScreenLock, 0xFFA0A160)
NHSTUB(ScreenUnlock,0xFFA0A188) 

//nullsub

NHSTUB(kbd_pwr_on, 0xFF810B04)//cannot locate
NHSTUB(rewinddir, 0xFF810B04)//cannot locate
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810B04)//cannot locate
NHSTUB(Unmount_FileSystem, 0xFF810B04)//cannot locate
NHSTUB(Mount_FileSystem, 0xFF810B04)//cannot locate
NSTUB(kbd_pwr_off, 0xFF833350)

NHSTUB(strrchr, 0xFF813FE4) // correction for sig.finder addr.
NHSTUB(strncpy, 0xFF813F38) // sigfinder founds same addr. for strcat
NHSTUB(strcat, 0xFF8ABAEC)  // sigfinder founds same addr. for strncpy
NHSTUB(SetFileTimeStamp, 0xFF8356A0) // filename instead of filehandle
NHSTUB(ExportToEventProcedure,0xFF889760)
NHSTUB(UnRegisterEvntProc,0xFF888C94)
NHSTUB(GetLogToFile,0xFF96B314) // OK
NHSTUB(EraseLogSector,0xFF96B33C) // OK
NHSTUB(closefastdir, 0xFFA7D624)
NHSTUB(GiveSemaphore,   0xFF8387E8)
NHSTUB(kbd_p1_sub, 0xFF8335B4)
NHSTUB(RenameFile_Fut, 0xFF834D0C)
NHSTUB(ExpCtrlTool_StopContiAE, 0xFF8447D8)
NHSTUB(GetKbdState,      0xFF85E258)


