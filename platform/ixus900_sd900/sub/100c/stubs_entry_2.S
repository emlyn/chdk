#include "stubs_asm.h"

// manually searched / corrected adresses in canon firmware

NHSTUB(AllocateMemory, 0xFF81AC70)
NHSTUB(FreeMemory, 0xFF81AC5C)

NHSTUB(Open, 0xFF87B55C)   // before Close()
NHSTUB(free, 0xFFB5ABC8)
NHSTUB(Rename, 0xFF87B644)   // after Write()

NHSTUB(GetDrive_ClusterSize, 0xFF87AD70)   // note "GetCatFs_ClusterSize"
NHSTUB(GetDrive_TotalClusters, 0xFF87ADAC)   // note "GetCatFs_TotalClusters"
NHSTUB(GetDrive_FreeClusters, 0xFF87ADE8)   // note "GetCatFs_FreeClusters"

NHSTUB(WriteSDCard, 0xFF88A8A4)

NHSTUB(kbd_pwr_on, 0xFF8291F8)
NHSTUB(kbd_pwr_off, 0xFF829238)
NHSTUB(kbd_read_keys, 0xFF828024)
NHSTUB(kbd_read_keys_r2, 0xFF828D40)   // search for "MOVL    R4, 0x223000"
NHSTUB(taskNameToId, 0xFFB67700)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8E5AAC)

NHSTUB(MFOn, 0xFF98FBF0)
NHSTUB(MFOff, 0xFF98FC20)

NHSTUB(ExpCtrlTool_StopContiAE,  0xFF91F0FC)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF91F0CC)
NHSTUB(MakeAFScan,  0xFF993BE4)

NHSTUB(GetBatteryTemperature, 0xFF82F584)
NHSTUB(GetCCDTemperature, 0xFF82F570)
NHSTUB(GetOpticalTemperature, 0xFF82F55C)
NHSTUB(PT_PlaySound, 0xFF99F320)

NHSTUB(EnterToCompensationEVF, 0xFF98F004)
NHSTUB(ExitFromCompensationEVF, 0xFF98F044)

NHSTUB(DoAFLock, 0xFF98EE30)
NHSTUB(UnlockAF, 0xFF98EE7C)

NHSTUB(SetScriptMode, 0xFF9A6394)   // search for SetScriptMode in IDA

// CAM_CONSOLE_LOG_ENABLED
NHSTUB(iosInit, 0xFFB58E2C)
NHSTUB(ttyDrv_Start, 0xFF811874)   // VxWorks console
NHSTUB(GetLogToFile, 0xFFB44520)   // GetLogToFile() -> A/ROMLOG.txt

NHSTUB(GetSystemTime, 0xFF8150D8)   // not in use yet, maybe usefull for CAM_CONSOLE_LOG_ENABLED

NHSTUB(TurnOnBackLight, 0xFF9F5308)
NHSTUB(TurnOffBackLight, 0xFF9F5338)
