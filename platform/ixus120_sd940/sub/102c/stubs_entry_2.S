#include "stubs_asm.h"

#define NULLSUB 0xFF810B04

NHSTUB(ExpCtrlTool_StartContiAE, 0xFF844034)
NHSTUB(MakeAFScan, 0xFF940504)

// not found by finsig
NHSTUB(PT_PlaySound, 0xFF8708C8)			 // or 0xFF879708 or FFA310EC
NHSTUB(EnterToCompensationEVF, 0xFF8369D4)
NHSTUB(ExitFromCompensationEVF, 0xFF836A18)
NHSTUB(Remove,0xFF8353e8)
NHSTUB(TurnOffBackLight, 0xFF88F4C4)		// or 0xFF89764C
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF95673C)
NHSTUB(kbd_pwr_on,NULLSUB)
NHSTUB(openfastdir, 0xFFA4CFC4)				// ??
NHSTUB(readfastdir, 0xFFA4D0F8)				// ??
NHSTUB(rename, 0xFF835490)
NHSTUB(WriteSDCard, 0xFF8827A8)
NHSTUB(platformsub_kbd_fetch_data, 0xFF858DF8)


// not 100% by finsig
NHSTUB(set_control_event, 0xff88a500)   // *SD940 102c accept stubs_entry.s value per http://chdk.setepontos.com/index.php?topic=4338.msg61396#msg61396
NHSTUB(ExitTask, 0xFF81E844)
NHSTUB(FreeUncacheableMemory, 0xFF8388D8)
NHSTUB(GetBatteryTemperature, 0xFF85BD0C)
NHSTUB(GetCCDTemperature, 0xff85bc98)
NHSTUB(GetCurrentAvValue, 0xff936558)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAD10E4)		// or 0xff935724)
NHSTUB(GetOpticalTemperature, 0xff85bd80)
NHSTUB(GetParameterData, 0xff96b3c8)
NHSTUB(GetPropertyCase, 0xff884948)
NHSTUB(GetSystemTime, 0xffa69d30)
NHSTUB(GetZoomLensCurrentPoint, 0xff93a7a8)
NHSTUB(GetZoomLensCurrentPosition, 0xffa5d940)
NHSTUB(IsStrobeChargeCompleted, 0xff8bc268)
NHSTUB(LockMainPower, 0xff88aa60)
NHSTUB(Lseek, 0xFF8354D0)
NHSTUB(MakeDirectory_Fut, 0xff834db4)
NHSTUB(NewTaskShell, 0xff88440c)
NHSTUB(PostLogicalEventForNotPowerType, 0xff88a298)
NHSTUB(PostLogicalEventToUI, 0xff88a2e4)
NHSTUB(RenameFile_Fut, 0xFF834CAC)  // 0xff834e78) 0xffa39440) 0xffa39490) // 8/7
NHSTUB(SetAutoShutdownTime, 0xff88aad4)
NHSTUB(SetCurrentCaptureModeType, 0xff891b0c)
NHSTUB(SetParameterData, 0xff96b338)
NHSTUB(SetPropertyCase, 0xff88484c)
NHSTUB(SleepTask, 0xff83851c)
NHSTUB(TakeSemaphore, 0xff8381e4)
NHSTUB(TurnOnBackLight, 0xff897634)
NHSTUB(UnlockMainPower, 0xff88a9b4)
NHSTUB(free, 0xFF814138)			// 0xFF8140DC) 	// 0xff814138)
NHSTUB(kbd_p1_f, 0xff8335d0)
NHSTUB(kbd_p1_f_cont, 0xff8335dc)
NHSTUB(kbd_pwr_off, NULLSUB)
NHSTUB(kbd_read_keys, 0xff833554)
NHSTUB(kbd_read_keys_r2, 0xff8587b8)
NHSTUB(rand, 0xff8204e0)
NHSTUB(reboot_fw_update, 0xffa52608)
NHSTUB(srand, 0xff8204d4)
NHSTUB(strcat, 0xFF89E254)				// 0xff813f38)
NHSTUB(strchr, 0xFF813FC0)		//0xff813fc0)
NHSTUB(strncpy, 0xFF813F38)		// 0xff813f38)
NHSTUB(strrchr, 0xFF813FE4)		// 0xff83de20)
NHSTUB(strtol, 0xFF83E128)		//0xff83e128)
NHSTUB(time, 0xff87eae4)
NHSTUB(SetFileTimeStamp, 0xff835640) 

// missing from finsig
NHSTUB(LEDDrive,0xFF8582F4)
NHSTUB(UnlockAF,0xFF870994)
NHSTUB(DoAFLock,0xFF870984)
NHSTUB(UnsetZoomForMovie,0xFF9712e4)
NHSTUB(ScreenLock,0xFF9D1C7C)
NHSTUB(RefreshPhysicalScreen, 0xFF9D1EA4)   // per SD940-1.03c SD90 101a & SD980 1.01c
NHSTUB(ScreenUnlock, 0xFF9D1CBC)
NHSTUB(PutInNdFilter, 0xFFA67C08)
NHSTUB(PutOutNdFilter, 0xFFA67C2C)
NHSTUB(apex2us, 0xFF9D5394)

// ignore
NHSTUB(rewinddir,NULLSUB)
NHSTUB(SetZoomActuatorSpeedPercent,NULLSUB)
NHSTUB(Mount_FileSystem,NULLSUB)
NHSTUB(Unmount_FileSystem,NULLSUB)

/////////////////////////////////////////////////

// need to redo??
NSTUB(MoveFocusLensToDistance, 0xffad10e4)
NHSTUB(SetScriptMode,0xFF88A82C)


NHSTUB(closefastdir, 0xffa4d294)
NHSTUB(stat, 0xff83550c)

// do not need ??
//NHSTUB(MoveZoomLensWithPoint, 0xffa67da4)



