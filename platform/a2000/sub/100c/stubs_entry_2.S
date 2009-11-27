#include "stubs_asm.h"

NHSTUB(AllocateMemory, 									0xFFDF0A50)
NHSTUB(FreeMemory, 											0xffdf0a48)

NHSTUB(FreeUncacheableMemory, 					0xffc171b4)

NHSTUB(strcpy, 													0xFFC0D834)
NHSTUB(strcmp, 													0xFFC0D84C)
NHSTUB(sprintf, 												0xFFC0D7B4)
NHSTUB(strchr,													0xFFC6C964)

NHSTUB(memcpy, 													0xffc6cac8)
NHSTUB(memset, 													0xffd7b2ac)
NHSTUB(memcmp, 													0xffc0d8b4)

NHSTUB(sscanf, 													0xFFD7B328)
NHSTUB(atol, 														0xFFC6C8D0)

NHSTUB(Open, 														0xffc1331c)
NHSTUB(Read, 														0xFFC133EC)
NHSTUB(Write, 													0xFFC133F0)
NHSTUB(Close, 													0xffc13344)
NHSTUB(Lseek, 													0xFFC1354C)

NHSTUB(Fopen_Fut, 											0xffc12d2c)
NHSTUB(Fread_Fut, 											0xffc12e18)
NHSTUB(Fwrite_Fut, 											0xffc12e6c)
NHSTUB(Fclose_Fut, 											0xffc12d6c)
NHSTUB(Fseek_Fut, 											0xffc12f0c)
NHSTUB(RenameFile_Fut, 									0xffc12b9c)
NHSTUB(DeleteFile_Fut, 									0xffc12bf0)
NHSTUB(Feof_Fut, 												0xffc12f58)
NHSTUB(Fflush_Fut, 											0xffc12f94)
NHSTUB(Fgets_Fut, 											0xffc12ec0)
NHSTUB(MakeDirectory_Fut, 							0xffc12c64)

NHSTUB(CreateCountingSemaphore, 				0xFFC0B648)
NHSTUB(DeleteSemaphore, 								0xFFC0B6A0)
NHSTUB(TakeSemaphore, 									0xffc0b74c)
NHSTUB(GiveSemaphore, 									0xFFC0B81C)

NHSTUB(GetTimeOfSystem, 								0xFFD15828)

NHSTUB(CreateTask, 											0xffc0b8c0)
NHSTUB(ExitTask, 												0xffc0bb50)
NHSTUB(SleepTask, 											0xffc16ff8)

NHSTUB(CPrintf, 												0xFFC0C6B0)
NHSTUB(CPutChar, 												0xFFC0C70C)
NHSTUB(GetCh, 													0xFFC0C738)

NHSTUB(OpenConsole, 										0xFFC0C7E8)
NHSTUB(CloseConsole, 										0xFFC0C954)

NHSTUB(GetStringWithPrompt, 						0xFFC0C788)
NHSTUB(RotateConsoleZOder,	 						0xFFC0C4A0)

NHSTUB(ExecuteEventProcedure, 					0xffc5543c)
NHSTUB(ExportToEventProcedure, 					0xFFC55DFC)
NHSTUB(DeleteProxyOfEventProcedure, 		0xFFC55E60)
NHSTUB(CreateProxyOfEventProcedure, 		0xFFC55E08)

NHSTUB(WriteToRom, 											0xFFD117F0)

NHSTUB(GetSystemTime, 									0xffdf0aa8)

NHSTUB(GetBatteryTemperature, 					0xFFC33494) //found at 0xffc33504 but camera crashs if used, so point to GetCCDTemperature
NHSTUB(GetCCDTemperature, 							0xFFC33494)
NHSTUB(GetCurrentAvValue, 							0xffd0025c)
//NHSTUB(GetCurrentTargetDistance, 			  0xffcff354)

NHSTUB(GetDrive_ClusterSize, 						0xffc3fc24)
NHSTUB(GetDrive_FreeClusters, 					0xFFC3FC8C)
NHSTUB(GetDrive_TotalClusters, 					0xFFC3FC58)

//NHSTUB(GetFocusLensSubjectDistance, 		0xffded04c)
NHSTUB(MoveFocusLensToDistance, 				0xffe4135c)
NHSTUB(GetOpticalTemperature, 					0xffc33574)

NHSTUB(GetParameterData, 								0xffd2d4ec)
NHSTUB(SetParameterData, 								0xffd2d45c)

NHSTUB(GetPropertyCase, 								0xFFC590AC)

NHSTUB(GetZoomLensCurrentPoint, 				0xffd0349c)
NHSTUB(GetZoomLensCurrentPosition, 			0xffdea9dc)
NHSTUB(MoveZoomLensWithPoint, 					0xffded808)

NHSTUB(IsStrobeChargeCompleted, 				0xffc8aef4)
NHSTUB(LocalTime, 											0xffc533c8)
NHSTUB(LockMainPower, 									0xffc5c9b0)

NHSTUB(NewTaskShell, 										0xffc58b54)
NHSTUB(ReadFastDir, 										0xffddce7c)
NHSTUB(Remove, 													0xffc1338c)

NHSTUB(SetAutoShutdownTime, 						0xffc5ca24)
NHSTUB(SetFileTimeStamp, 								0xffc13620)

NHSTUB(TurnOnBackLight, 								0xffc67af8)
NHSTUB(TurnOffBackLight, 								0xFFC67B10)

NHSTUB(UIFS_WriteFirmInfoToFile, 				0xffd20598)
NHSTUB(UnlockMainPower, 								0xffc5c904)
NHSTUB(UpdateMBROnFlash, 								0xffc3fa64)

NHSTUB(_log, 														0xffe7368c)
NHSTUB(_log10, 													0xffe725d0)
NHSTUB(_pow, 														0xffe72740)
NHSTUB(_sqrt, 													0xffe749f4)

NHSTUB(close, 													0xffc09f50)
NHSTUB(closedir, 												0xffddcf4c)
NHSTUB(closefastdir, 										0xffddcf4c)
NHSTUB(free, 														0xffc03a80)

NHSTUB(kbd_p1_f, 												0xffc114f0)
NHSTUB(kbd_p1_f_cont, 									0xffc114fc)
NHSTUB(kbd_p2_f, 												0xffc10d04)
NHSTUB(kbd_pwr_on, 											0xffc313c8)
NHSTUB(kbd_read_keys, 									0xffc113ec)
NHSTUB(kbd_read_keys_r2, 								0xFFC30E84)

NHSTUB(lseek, 													0xffc13484)
NHSTUB(malloc, 													0xffc039ac)
NHSTUB(mkdir, 													0xffc136e8)
NHSTUB(mktime_ext, 											0xffc6d334)
NHSTUB(open, 														0xffc09ea0)
NHSTUB(opendir, 												0xffddcde8)
NHSTUB(openfastdir, 										0xffddcde8)

NHSTUB(qsort, 													0xFFE2CB98)
NHSTUB(rand, 														0xffc0d9bc)

NHSTUB(read, 														0xffc0a138)
NHSTUB(readfastdir, 										0xffddce7c)
NHSTUB(rename, 													0xffc13418)
NHSTUB(srand, 													0xffc0d9b0)
NHSTUB(stat, 														0xffc13550)
NHSTUB(strcat, 													0xffc6c8dc)
NHSTUB(strftime, 												0xffc6cd3c)
NHSTUB(strlen, 													0xffc0d890)
NHSTUB(strncmp, 												0xffc6c918)
NHSTUB(strncpy, 												0xffc1cb54)
NHSTUB(strrchr, 												0xFFD7B284)
NHSTUB(strtol, 													0xffc1cd8c)
NHSTUB(time, 														0xffc5327c)
NHSTUB(write, 													0xffc0a198)


NHSTUB(kbd_pwr_off,											0xFFC31418)

NHSTUB(RefreshPhysicalScreen,						0xFFD7AF58)
NHSTUB(DoAFLock,												0xFFC14D9C)
NHSTUB(UnlockAF,												0xFFC14DD4)
NHSTUB(UnsetZoomForMovie,								0xFFD32AD8)

NHSTUB(EnterToCompensationEVF, 					0xFFC14FEC)
NHSTUB(ExitFromCompensationEVF, 				0xFFC15030)

NHSTUB(PostLEDMessage,									0xFFC30908) // Similar code in sx110

NHSTUB(PutInNdFilter,										0xFFDED66C) // Look for two references to NdActuator_c at the same gap
NHSTUB(PutOutNdFilter,									0xFFDED690) //

// not found
NHSTUB(SetZoomActuatorSpeedPercent,	0xFFC00940) // nullsub

// Those aren't used or don't exist in DryOS
NHSTUB(Unmount_FileSystem,					0xFFC00940)
NHSTUB(Mount_FileSystem,						0xFFC00940)
NHSTUB(rewinddir,										0xFFC00940)

NHSTUB(SetScriptMode,										0xFFC5C77C) // string
