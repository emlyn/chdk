#include "stubs_asm.h"

#define NULLSUB 0xFF810B04

NHSTUB(ExpCtrlTool_StartContiAE, 0xFF844034)
NHSTUB(MakeAFScan, 0xFF9406CC)

//** subs in signatures_dryos.h but not auto found 

NHSTUB(EnterToCompensationEVF , 0xFF8369D4)		// SD940 103c matched with SD90 101a
NHSTUB(ExitFromCompensationEVF  , 0xFF836A18)	// SD940 103c matched with SD90 101a

NHSTUB(TurnOffBackLight , 0xFF8976A8)			// SD940 103c matched with SD90 101a
NHSTUB(TurnOnBackLight, 0xFF897690)				// SD940 103c matched with SD90 101a

NHSTUB(Lseek , 0xFF8354D0)						// SD940 103c matched with SD90 101a

NHSTUB(PT_PlaySound , 0xFF879764)				// SD940 103c matched with SD90 101a

NHSTUB(openfastdir , 0xFFA4D18C)				// SD940 103c matched with SD90 101a
NHSTUB(readfastdir , 0xFFA4D2C0)				// SD940 103c matched with SD90 101a

NHSTUB(RefreshPhysicalScreen , 0xFF9D206C)		// SD940 103c matched with SD90 101a & SD980 1.01c
NHSTUB(ScreenLock, 0xFF9D1E44)					// SD940 103c close to SD90 101a (extra code in SD940 sub)
NHSTUB(ScreenUnlock,0xFF9D1E84) 				// SD940 103c matched with SD90 101a

NHSTUB(Remove , 0xFF8353E8)						// SD940 103c matched with SD90 101a
NHSTUB(rename , 0xFF835490)						// SD940 103c matched with SD90 101a
NHSTUB(UIFS_WriteFirmInfoToFile , 0xFF956904)	// SD940 103c matched with SD90 101a

//** subs not in signatures_dryos.h

NHSTUB(SetScriptMode, 0xFF810F4C)				// SD940 103c matched with SD90 101a
NHSTUB(LEDDrive, 0xFF8582F4)					// SD940 103c matched with SD90 101a
NHSTUB(apex2us, 0xFF9D555C)						// SD940 103c matched with SD90 101a
NHSTUB(WriteSDCard, 0xFF926538)					// SD940 103c matched with SD90 101a
NHSTUB(UnlockAF, 0xFF8368B4)					// SD940 103c matched with SD90 101a
NHSTUB(DoAFLock, 0xFF83687C)					// FFA4D148
NHSTUB(UnsetZoomForMovie, 0xFF9714AC)			// SD940 103c matched with SD90 101a

NHSTUB(PutInNdFilter, 0xFFA67DD0)				// SD940 103c matched with SD940 102c NHSTUB(PutInNdFilter, 0xFFA67C08)
NHSTUB(PutOutNdFilter, 0xFFA67DF4)				// SD940 103c matched with SD940 102c NHSTUB(PutOutNdFilter, 0xFFA67C2C)

NHSTUB(platformsub_kbd_fetch_data, 0xFF858DF8)	//????????????

//** subs with less than 100% match

NHSTUB(set_control_event, 0xff88a55c)			// *SD940 103c accept stubs_entry.s value per http://chdk.setepontos.com/index.php?topic=4338.msg61396#msg61396
NHSTUB(closefastdir, 0xFFA4D148)				// *SD940 103c matched with SD90 101a was 0xffa4d45c = best match: 71%
NHSTUB(ExitTask, 0xff81e844)					//	SD940 103c matched with SD90 101a & finsig best match: 57%
NHSTUB(free, 0xff814138)						//	SD940 103c matched with SD90 101a & finsig best match: 95%
NHSTUB(FreeUncacheableMemory, 0xff8388d8)		//	SD940 103c matched with SD90 101a & finsig best match: 91%
NHSTUB(GetBatteryTemperature, 0xff85bd0c)		//	SD940 103c matched with SD90 101a & finsig best match: 52%
NHSTUB(GetCCDTemperature, 0xff85bc98)			//	SD940 103c matched with SD90 101a & finsig best match: 52%
NHSTUB(GetCurrentAvValue, 0xff936720)			// ?SD940 103c no match with SD90 101a -> finsig best match: 93%
NHSTUB(GetFocusLensSubjectDistance, 0xff9358ec)	//	SD940 103c matched with SD90 101a & finsig best match: 64%
NHSTUB(GetOpticalTemperature, 0xff85bd80)		//	SD940 103c matched with SD90 101a & finsig best match: 96%
NHSTUB(GetParameterData, 0xff96b590)			//	SD940 103c matched with SD90 101a & finsig best match: 96%
NHSTUB(GetPropertyCase, 0xff8849a4)				//	SD940 103c matched with SD90 101a & finsig best match: 68%
NHSTUB(GetSystemTime, 0xffa69ef8)				//	SD940 103c matched with SD90 101a & finsig best match: 96%
NHSTUB(GetZoomLensCurrentPoint, 0xff93a970)		//	SD940 103c matched with SD90 101a & finsig best match: 74%
NHSTUB(GetZoomLensCurrentPosition, 0xffa5db08)	//	SD940 103c matched with SD90 101a & finsig best match: 95%
NHSTUB(IsStrobeChargeCompleted, 0xff8bc2c4)		//	SD940 103c matched with SD90 101a & finsig best match: 77%
NHSTUB(kbd_p1_f, 0xff8335d0)					//	SD940 103c matched with SD90 101a & finsig best match: 86%
NHSTUB(kbd_p1_f_cont, 0xff8335dc)				//	SD940 103c matched with SD90 101a & finsig best match: 86%
NHSTUB(kbd_read_keys, 0xff833554)				//	SD940 103c matched with SD90 101a & finsig best match: 84%
NHSTUB(kbd_read_keys_r2, 0xff8587b8) 			//	SD940 103c matched with SD90 101a & finsig best match: 86%
NHSTUB(LockMainPower, 0xff88aabc)				//	SD940 103c matched with SD90 101a & finsig best match: 93%
NHSTUB(MakeDirectory_Fut, 0xff834db4)			//	SD940 103c matched with SD90 101a & finsig best match: 92%
NHSTUB(MoveFocusLensToDistance, 0xffad12ac)		//	SD940 103c matched with SD90 101a & finsig best match: 57%
NHSTUB(MoveZoomLensWithPoint, 0xffa67f6c)		//	SD940 103c matched with SD90 101a & finsig best match: 58%
NHSTUB(NewTaskShell, 0xff884468)				//	SD940 103c matched with SD90 101a & finsig best match: 62%
NHSTUB(PostLogicalEventForNotPowerType, 0xff88a2f4) 	//	SD940 103c matched with SD90 101a & finsig best match: 86%
NHSTUB(PostLogicalEventToUI, 0xff88a340)		//	SD940 103c matched with SD90 101a & finsig best match: 92%
NHSTUB(rand, 0xff8204e0)						//	SD940 103c matched with SD90 101a & finsig best match: 95%
NHSTUB(reboot_fw_update, 0xffa527d0)			//	SD940 103c matched with SD90 101a & finsig best match: 82%
NHSTUB(RenameFile_Fut, 0xFF834CAC)				// *SD940 103c matched with SD90 101a was 0xff834e78 Best match: 53% ALT: NHSTUB(RenameFile_Fut, 0xffa39608) NHSTUB(RenameFile_Fut, 0xffa39658)
NHSTUB(SetAutoShutdownTime, 0xff88ab30)			//	SD940 103c matched with SD90 101a & finsig best match: 93%
NHSTUB(SetCurrentCaptureModeType, 0xff891b68)	//	SD940 103c matched with SD90 101a & finsig best match: 81%
NHSTUB(SetFileTimeStamp, 0xFF835640)			// ?SD940 103c match with SD90 101a  -> Best match: 55%
NHSTUB(SetLogicalEventActive, 0xff88a838)		//	SD940 103c matched with SD90 101a & finsig best match: 64%
NHSTUB(SetParameterData, 0xff96b500)			//	SD940 103c matched with SD90 101a & finsig best match: 96%
NHSTUB(SetPropertyCase, 0xff8848a8)				//	SD940 103c matched with SD90 101a & finsig best match: 79%
NHSTUB(SleepTask, 0xff83851c)					//	SD940 103c matched with SD90 101a & finsig best match: 92%
NHSTUB(srand, 0xff8204d4)						//  SD940 103c matched with SD90 101a & finsig (its DCB stuff only?) Best match: 95%
NHSTUB(stat, 0xff83550c) 						//	SD940 103c matched with SD90 101a & finsig  ALT: NHSTUB(stat, 0xff865bb8) 
NHSTUB(strcat, 0xFF89E2B0)						//  SD940 103c matched with SD90 101a was 0xff813f38 = best match: 61%
NHSTUB(strchr, 0xff813fc0)						//	SD940 103c matched with SD90 101a & finsig best match: 56%
NHSTUB(strncpy, 0xff813f38)						//	SD940 103c matched with SD90 101a & finsig best match: 73%
NHSTUB(strrchr, 0xFF813FE4)						//  SD940 103c matched with SD90 101a was 0xff83de20 = best match: 71% ALT: NHSTUB(strrchr, 0xff89e2c4) 
NHSTUB(strtol, 0xff83e128)						//	SD940 103c matched with SD90 101a & finsig best match: 96%
NHSTUB(TakeSemaphore, 0xff8381e4)				//	SD940 103c matched with SD90 101a & finsig best match: 60%
NHSTUB(time, 0xff87eb40)						//	SD940 103c matched with SD90 101a & finsig best match: 86%
NHSTUB(UnlockMainPower, 0xff88aa10)				//	SD940 103c matched with SD90 101a & finsig best match: 93%


//** obsolete / unknown / not found subs

NHSTUB(kbd_pwr_on , NULLSUB)					//** not found in SD90 or SD940-102c
NHSTUB(kbd_pwr_off, NULLSUB)					//** 0xff858e10 = best match: 51% in finsig
NHSTUB(rewinddir, NULLSUB)						//** not found in SD90 or SD940-102c
NHSTUB(SetZoomActuatorSpeedPercent, NULLSUB)	//** not found in SD90 or SD940-102c
NHSTUB(Unmount_FileSystem, NULLSUB)				//** not found in SD90 or SD940-102c
NHSTUB(Mount_FileSystem, NULLSUB)				//** not found in SD90 or SD940-102c
