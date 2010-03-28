#include "stubs_asm.h"

// not found automatically

NHSTUB(EnterToCompensationEVF, 0xFFC148E0)
NHSTUB(ExitFromCompensationEVF, 0xFFC14924)
NHSTUB(GetBatteryTemperature, 0xFFC2EB38)  // =GetCCDTemperature 
NHSTUB(GetCCDTemperature, 0xFFC2EB38)
NHSTUB(GetDrive_ClusterSize, 0xFFC3A924)
NHSTUB(GetDrive_TotalClusters, 0xFFC3A950)
NHSTUB(GetDrive_FreeClusters, 0xFFC3A97C)
NHSTUB(RefreshPhysicalScreen, 0xFFD4BE50)
NHSTUB(TurnOffBackLight, 0xFFC5FCEC)
NHSTUB(strchr, 0xFFC634D4)

// found automatically with errors

NHSTUB(UpdateMBROnFlash, 0xFFC3A77C)
NHSTUB(qsort, 0xFFDF2A18)
NHSTUB(strrchr, 0xFFD4C1C8)
NHSTUB(kbd_read_keys_r2, 0xFFC1138C)

// found manually

NHSTUB(DoAFLock, 0xFFC14830)
NHSTUB(UnlockAF, 0xFFC14868)
NHSTUB(SetScriptMode, 0xFFC54FDC)
NHSTUB(LEDDrive, 0xFFC2C020)
NHSTUB(PutInNdFilter, 0xFFE01E0C)
NHSTUB(PutOutNdFilter, 0xFFE01E44)
NHSTUB(UnsetZoomForMovie, 0xFFD0E960)
NHSTUB(platformsub_kbd_fetch_data, 0xFFC2C8AC)
NHSTUB(WriteSDCard, 0xFFCD598C)
NHSTUB(apex2us, 0xFFD4CF08)
NHSTUB(MakeAFScan, 0xFFCE7CC0)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFC1EEE4)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFC1F028) 
NHSTUB(SetAE_ShutterSpeed, 0xFFE06860) 
NHSTUB(TurnOnMic, 0xFFC2CF08) 
NHSTUB(TurnOffMic, 0xFFC2CF34)

//null subs

NHSTUB(kbd_pwr_on, 0xFFC00954)
NHSTUB(rewinddir, 0xFFC00954)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00954)
NHSTUB(Mount_FileSystem, 0xFFC00954)
NHSTUB(Unmount_FileSystem, 0xFFC00954)


