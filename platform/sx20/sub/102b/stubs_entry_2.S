#include "stubs_asm.h"
#include "stubs_entry_ida.S"

# Confirmed with data from IDA
NHSTUB(Lseek,							0xff835398)
NHSTUB(ExitTask,						0xff81e844)
NHSTUB(LockMainPower,					0xff896eac)
NHSTUB(PostLogicalEventForNotPowerType, 0xff894da8)
NHSTUB(PostLogicalEventToUI,			0xff894df4)
NHSTUB(SetAutoShutdownTime,				0xff896f20)
NHSTUB(SetCurrentCaptureModeType,		0xff89eb28)
NHSTUB(SleepTask,						0xff838a6c)
NHSTUB(TakeSemaphore,					0xff838734)
NHSTUB(UnlockMainPower,					0xff896e00)

# FROM IDA (Auto)
NHSTUB(VbattGet,						0xff95d0c0)
NHSTUB(GetSystemTime,					0xffa9b6c4)
NHSTUB(GetOpticalTemperature,			0xff8627b8)
NHSTUB(SetLogicalEventActive,			0xff896bfc)
NHSTUB(NewTaskShell,					0xff88eda0)
NHSTUB(SetPropertyCase,					0xff88f1e0)
NHSTUB(TurnOnBackLight,					0xff8a5ac8)
NHSTUB(kbd_p1_f,						0xff833498)
NHSTUB(time,							0xff889434)

# Other
NHSTUB(TurnOffBackLight,				0xFF89B6A4)
NHSTUB(PT_PlaySound,					0xFF884058) // pretty sure
NHSTUB(RefreshPhysicalScreen,			0xFFA0491C)
NHSTUB(strcat,							0xFF8AC87C)
NHSTUB(UpdateMBRonFlash,				0xFF86F048) // looked for all function with strncpy that matched sx10 102b
NHSTUB(UnlockAndRefresh,                0xFFA0498C)
NHSTUB(LockAndRefresh,				    0xFFA048E8)
NHSTUB(LEDDrive,						0xFF85E338) // looks good
NHSTUB(SetScriptMode,					0xFF896C4C) // looks good
NHSTUB(apex2us,							0xFFA080A8) // looks good
NHSTUB(WriteSDCard,						0xFF940B80) // I think this is it
NHSTUB(EnterToCompensationEVF,			0xFF836D84)
NHSTUB(platformsub_kbd_fetch_data,		0xFF85F11C) // yep
NHSTUB(ExitFromCompensationEVF,			0xFF836DC8)
NHSTUB(GetBatteryTemperature,			0xFF862744) // pretty sure
NHSTUB(GetCCDTemperature,				0xFF8626D0) // pretty sure
NHSTUB(GetZoomLensCurrentPosition,		0xFFA8EB50) // seem good
NHSTUB(GetZoomLensCurrentPoint,			0xFF9566A8) // looks good
NHSTUB(Remove,							0xFF8352B0)
NHSTUB(RenameFile_Fut,					0xFF834B74) // doesn't look like SX10 but works
NHSTUB(strrchr,							0xFF813FE4) // incorrectly detected
NHSTUB(Restart,							0xFF83A53C)

# Might be wrong
NHSTUB(UnlockAF,						0xFF8796C4) // ? could be right
NHSTUB(DoAFLock,						0xFF8796B4) // ? could be right

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
STUB(FF896B84)
STUB(FF896AB4)
STUB(FFA048E8)
