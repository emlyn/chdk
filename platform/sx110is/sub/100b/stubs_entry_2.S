#include "stubs_asm.h"
NHSTUB(GetBatteryTemperature, 0xffc387ec)	//found at 0xffc3885c but camera crashs if used, so point to GetCCDTemperature

//functions not found in firmware
NHSTUB(EnterToCompensationEVF, 0xFFC15318) // "ExpComp On"
NHSTUB(ExitFromCompensationEVF, 0xFFC1535C) // "ExpComp Off"
NHSTUB(RefreshPhysicalScreen, 0xFFD8FC00)	//function looks different from other fw, but might be the right one
NHSTUB(TurnOffBackLight, 0xFFC6F9FC)	//found similar code as sx100 at this address 
//NHSTUB(VbattGet, 0xFFC10314)	//found similar code as sx100 at this address
NHSTUB(kbd_pwr_on, 0xFFC3642C)				// Hmm, function looks very different from other cams but it might be the right...
NHSTUB(kbd_pwr_off, 0xFFC36444)				// Hmm, function looks very different from other cams but it might be the right...
NHSTUB(strchr, 0xFFC74A0C)	//found similar code as sx100 at this address
//NHSTUB(vsprintf, 0xFFC0D7F8)	//found similar code as sx100 at this address

// functions corrected (wrong in stubs_entry.S)
//NHSTUB(AllocateUncacheableMemory, 0xFFC17828) //wrong: 0xffc17834, correct: 0xFFC17828 
NHSTUB(ExecuteEventProcedure, 0xFFC5B5B8)
NHSTUB(GetDrive_TotalClusters, 0xffc44e00)	//wrong: 0xffc44dcc, correct: 0xffc44e00, ALT address of GetDrive_TotalClusters
NHSTUB(GetDrive_FreeClusters, 0xffc44e34)	//wrong: 0xffc44dcc, correct: 0xffc44e34
NHSTUB(GetPropertyCase, 0xFFC5F2A0)
NHSTUB(kbd_read_keys_r2, 0xFFC35D7C)
//NHSTUB(SetPropertyCase, 0xFFC5F198)
NHSTUB(strrchr, 0xFFD8FF2C) //wrong: 0xffc74a08, correct: 0xFFD8FF2C


//functions not found by finsig and not declared in signatures_dryos.h but needed by chdk
NHSTUB(DoAFLock, 0xFFC15048)
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFC20894)
NHSTUB(ExpCtrlTool_StopContiAE, 0xFFC209D8)
NHSTUB(GiveSemaphore, 0xFFC0B81C)
NHSTUB(MakeAFScan, 0xFFD19824)	//differ from other cams
NHSTUB(PostLEDMessage, 0xFFC357C8 ) //questionable, might be wrong...
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00940) //nullsub, there are things like SetZoomActuatorSpeedPPS in fw
NHSTUB(TurnOffMic, 0xFFC36DD8)
NHSTUB(TurnOnMic, 0xFFC36DAC)
NHSTUB(UnlockAF, 0xFFC1509C)
NHSTUB(UnsetZoomForMovie, 0xFFD3E944)
NHSTUB(WriteSDCard, 0xFFD02B30)
NHSTUB(PostLogicalEventForNotPowerType, 0xffc61bb4)
NHSTUB(LEDDrive, 0xffd17758)
NHSTUB(platformsub_kbd_fetch_data, 0xFFC362CC)
NHSTUB(eventproc_export_PostLogicalEventToUI, 0xffc61c00)
NHSTUB(eventproc_export_SleepTask, 0xffc176ac)
NHSTUB(eventproc_export_ExitTask, 0xffc0bb50)

//do they really exists in dryos? --> point to nullsub
NHSTUB(Mount_FileSystem, 0xFFC00940)
NHSTUB(rewinddir, 0xFFC00940)
NHSTUB(Unmount_FileSystem, 0xFFC00940)

