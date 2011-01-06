#include "stubs_asm.h"
#include "stubs_entry_ida.S"

# Confirmed with data from IDA
NHSTUB(Lseek,							0xff835398)
NHSTUB(ExitTask,						0xff81e844)
NHSTUB(LockMainPower,					0xFF896EFC)
NHSTUB(PostLogicalEventForNotPowerType, 0xFF894DF8)
NHSTUB(PostLogicalEventToUI,			0xFF894E44)
NHSTUB(SetAutoShutdownTime,				0xFF896F70)
NHSTUB(SetCurrentCaptureModeType,		0xFF89EB78)
NHSTUB(SleepTask,						0xff838a6c)
NHSTUB(TakeSemaphore,					0xff838734)
NHSTUB(UnlockMainPower,					0xFF896E50)

# FROM IDA (Auto)
NHSTUB(VbattGet,						0xFF95D27C)
NHSTUB(GetSystemTime,					0xFFA9B880)
NHSTUB(GetOpticalTemperature,			0xff8627b8)
NHSTUB(SetLogicalEventActive,			0xFF896C4C)
NHSTUB(NewTaskShell,					0xFF88EDF0)
NHSTUB(SetPropertyCase,					0xFF88F230)	// function PT_GetPropertyCaseString??
NHSTUB(TurnOnBackLight,					0xFF8A5B18)
NHSTUB(kbd_p1_f,						0xff833498)
NHSTUB(time,							0xFF889484)

# Other
NHSTUB(TurnOffBackLight,				0xFF89B6F4)
NHSTUB(PT_PlaySound,					0xFF8840A8) // pretty sure
NHSTUB(RefreshPhysicalScreen,			0xFFA04AD8)
NHSTUB(strcat,							0xFF8AC8CC)
NHSTUB(UpdateMBRonFlash,				0xFF86F048) // looked for all function with strncpy that matched sx10 102b
NHSTUB(UnlockAndRefresh,                0xFFA04B48)
NHSTUB(LockAndRefresh,				    0xFFA04AA4)
NHSTUB(LEDDrive,						0xFF85E338) // looks good
NHSTUB(SetScriptMode,					0xFF896C9C) // looks good
NHSTUB(apex2us,							0xFFA08264) // looks good
NHSTUB(WriteSDCard,						0xFF940C34) // I think this is it
NHSTUB(EnterToCompensationEVF,			0xFF836D84)
NHSTUB(platformsub_kbd_fetch_data,		0xFF85F11C) // yep
NHSTUB(ExitFromCompensationEVF,			0xFF836DC8)
NHSTUB(GetBatteryTemperature,			0xFF862744) // pretty sure
NHSTUB(GetCCDTemperature,				0xFF8626D0) // pretty sure
NHSTUB(GetZoomLensCurrentPosition,		0xFFA8ED0C) // seem good
NHSTUB(GetZoomLensCurrentPoint,			0xFF956864) // looks good
NHSTUB(Remove,							0xFF8352B0)
NHSTUB(RenameFile_Fut,					0xFF834B74) // doesn't look like SX10 but works
NHSTUB(strrchr,							0xFF813FE4) // incorrectly detected
NHSTUB(add_ptp_handler, 				0xFFA49320) 
NHSTUB(Restart,							0xFF83A53C)
NHSTUB(PB2Rec, 0xFF899E38)
NHSTUB(Rec2PB, 0xFF8988A4)

# Might be wrong
NHSTUB(UnlockAF,						0xFF879714) // ? could be right
NHSTUB(DoAFLock,						0xFF879704) // ? could be right

#NULL
NHSTUB(rewinddir,						0xFF810B04) // BX LR
NHSTUB(SetZoomActuatorSpeedPercent,		0xFF810B04) // BX LR
NHSTUB(Unmount_FileSystem,				0xFF810B04) // BX LR
NHSTUB(Mount_FileSystem,				0xFF810B04) // BX LR
NHSTUB(kbd_pwr_off,						0xFF810B04) // BX LR
NHSTUB(kbd_pwr_on,						0xFF810B04) // BX LR
NHSTUB(SetFileTimeStamp,				0xFF810B04) // # incorrect auto detect why can no one find this function!

#0xDEADC0DE
NHSTUB(UIFS_WriteFirmInfoToFile,		0xDEADC0DE) // NA #1
NHSTUB(openfastdir,						0xDEADC0DE) // NA #1
NHSTUB(readfastdir,						0xDEADC0DE) // NA #1
NHSTUB(rename,							0xDEADC0DE)

# Stubs requires for JogDial code
STUB(FF896BD4)
STUB(FF896B04)
STUB(FFA04AA4)
