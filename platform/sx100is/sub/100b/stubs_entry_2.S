#include "stubs_asm.h"

//NHSTUB(SleepTask, 0xFFC19CB8)
//NHSTUB(CreateTask, 0xFFC0BBB8)
//NHSTUB(ExitTask, 0xFFC0BE48)
//NHSTUB(AllocateMemory, 0xFFDF2EC0)
//NHSTUB(ExecuteEventProcedure                  ,0xFFC0C270)
//NHSTUB(FreeMemory                             ,0xFFDF2EAC)	//NOTE 94% mutch in stubs_entry.S
//NHSTUB(GetCurrentTargetDistance               ,0xFFD08E68)
//NHSTUB(GetSystemTime                          ,0xFFDF2FC8)
NHSTUB(ints_disable                           ,0xFFC00578)
NHSTUB(ints_enable                            ,0xFFC005A0)
//NHSTUB(memcmp                                 ,0xFFC0E8F0)
//NHSTUB(memcpy                                 ,0xFFC76644)
//NHSTUB(memset                                 ,0xFFE2AA8C)
//NHSTUB(Close                                  ,0xFFC1504C)
//NHSTUB(Open                                   ,0xFFC0A1A8)
//NHSTUB(Read                                   ,0xFFC0A440)
//NHSTUB(Write                                  ,0xFFC0A4A0)
//NHSTUB(Lseek								  ,0xFFC1518C)
//NHSTUB(strcmp                                 ,0xFFC0E888)
//NHSTUB(strcpy                                 ,0xFFC0E834)
//NHSTUB(strlen                                 ,0xFFC0E8CC)
//NHSTUB(TakeSemaphore                          ,0xFFC0BA54)
//NHSTUB(vsprintf, 0xFFC0E7B4)    // first sub called in FADBGPrintf
//NHSTUB(GetFocusLensSubjectDistance,	 0xFFD0A2C8)    //NOTE 87% mutch in stubs_entry.S
//NHSTUB(GetZoomLensCurrentPoint,           0xFFD0E394)
NHSTUB(GetZoomLensCurrentPosition,        0xFFD0E36C)
//NHSTUB(RefreshPhysicalScreen,		  0xFFD79FA0)
//NHSTUB(GetPropertyCase,			 0xFFC5BC8C)    // PT_GetPropertyCaseString
//NHSTUB(SetPropertyCase,			 0xFFC52D28)    // PT_SetPropertyCaseString
//NHSTUB(VbattGet,                          0xFFC119CC)
NHSTUB(kbd_read_keys, 0xFFC130F4)       // will be replaced in kbd.c   // !!!NOT CHECKED YET!!!
//NHSTUB(kbd_p1_f, 0xFFC131F0)
//NHSTUB(kbd_p1_f_cont, 0xFFC131FC)
//NHSTUB(kbd_p2_f, 0xFFC12A40)
NHSTUB(kbd_pwr_on, 0xFFC00958)				// There is no such func
NHSTUB(kbd_pwr_off, 0xFFC00958)				// There is no such func
NHSTUB(kbd_read_keys_r2, 0xFFC378CC)
//NHSTUB(platformsub_kbd_fetch_data, 0xFFC37DC0)	// EWAVR указал на этот адрес в форуме iXBT, не используется. клава сделана на основе s5is

NHSTUB(taskcreate_jogDial, 0xFFC380F4)

//NHSTUB(mkdir, 0xFFC153F0)
//NHSTUB(GetParameterData, 0xFFD26868)
//NHSTUB(SetParameterData, 0xFFD267D8)
//NHSTUB(IsStrobeChargeCompleted, 0xFFC9EF68)

//NHSTUB(open,				 0xFFC0A1A8)	//NOTE mentioned in stubs_entry.S
//NHSTUB(write,				 0xFFC0A4A0)	//NOTE mentioned in stubs_entry.S
//NHSTUB(close,				 0xFFC0A258)
//NHSTUB(lseek,				 0xFFC1518C)     // = Lseek
//NHSTUB(read,                             0xFFC0A440)     // = Read

//NHSTUB(Fopen_Fut,                        0xFFC149F0)
//NHSTUB(Fwrite_Fut,                       0xFFC14B30)
//NHSTUB(Fclose_Fut,                       0xFFC14A30)
//NHSTUB(Fread_Fut,                        0xFFC14ADC)
//NHSTUB(Fseek_Fut,						0xFFC14BD0)
//NHSTUB(Remove,							0xFFC15094)
//NHSTUB(rename,							0xFFC15120)

//NHSTUB(GetDrive_ClusterSize, 0xFFC4066C)
//NHSTUB(GetDrive_TotalClusters, 0xFFC406A0)
//NHSTUB(GetDrive_FreeClusters, 0xFFC4070C)
//NHSTUB(LockMainPower ,  0xFFC5F714)
//NHSTUB(UnlockMainPower, 0xFFC5F668)
//NHSTUB(GetCurrentAvValue, 0xFFD0AFD4)
NHSTUB(MoveFocusLensToDistance, 0xFFDC0C60)	// In SX100 MoveIrisToAvWithoutBacklash_2  
//NHSTUB(MoveZoomLensWithPoint, 0xFFD0EE40)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00958) // null stub

//NHSTUB(_log, 0xFFE57FF0)	// Not found!
//NHSTUB(_log10, 0xFFE56F34)	// Not found!
//NHSTUB(_pow, 0xFFE570A4)	// Not found!
//NHSTUB(_sqrt, 0xFFE59358)	// Not found!

//NHSTUB(malloc, 0xFFC039DC)
//NHSTUB(free, 0xFFC03AB0)
//NHSTUB(FreeUncacheableMemory, 0xFFC19E64)
NHSTUB(AllocateUncacheableMemory, 0xFFC19E30)

//NHSTUB(rand, 0xFFC0E9F8)
//NHSTUB(srand, 0xFFC0E9EC)

//NHSTUB(stat, 0xFFC15258)

//NHSTUB(openfastdir, 0xFFDDC5E8)
//NHSTUB(readfastdir, 0xFFDDC67C)
//NHSTUB(closefastdir, 0xFFDDC74C)

//NHSTUB(qsort, 0xFFD7A830)

//NHSTUB(strstr, 0xFFD62534) //???
//NHSTUB(strncpy, 0xFFC0E84C)
//NHSTUB(strrchr, 0xFFC7661C)
//NHSTUB(strncmp, 0xFFC765AC)
//NHSTUB(strchr, 0xFFC765F8)
//NHSTUB(strcat, 0xFFC76570)
//NHSTUB(strtol, 0xFFC20338)

//NHSTUB(time, 0xFFC57F6C)
//NHSTUB(LocalTime, 0xFFC580B8)

//NHSTUB(UpdateMBROnFlash, 0xFFC40434)

//NHSTUB(opendir, 0xFFDDC5E8) // OpenFastDir
//NHSTUB(ReadFastDir, 0xFFDDC67C)
//NHSTUB(closedir, 0xFFDDC74C)  // CloseFastDir
NHSTUB(UnsetZoomForMovie, 0xFFD2CF98)


NHSTUB(PostLEDMessage, 0xFFC37434)
NHSTUB(TurnOnMic, 0xFFC38870)
NHSTUB(TurnOffMic, 0xFFC3889C)

NHSTUB(ExpCtrlTool_StopContiAE,  0xFFC24B78) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFC249B8) 
NHSTUB(MakeAFScan,  0xFFDEFB38) 

NHSTUB(GiveSemaphore,  0xFFC0BB24)

// dryos Test
//NHSTUB(NewTaskShell, 0xFFC5B710)  // starts new shell on Console. GUI output?
//NHSTUB(UIFS_WriteFirmInfoToFile, 0xFFD61640) // should write 'A/FirmInfo.txt'
NHSTUB(dumpMemoryToFile, 0xFFC14214)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)


// !! UNKNOWN !!
// Not found, point to nullsub for immediate return
// nullsub_1: 0xFFC00958

NHSTUB(utime, 0xFFC00958)

//NSTUB(memPartAlloc,			 0xFFC00958)
//NSTUB(memPartFindMax,			 0xFFC00958)


// Those aren't used or don't exist in DryOS

//NSTUB(taskCreateHookAdd,		 0xFFC00958)
//NSTUB(taskDeleteHookAdd,		 0xFFC00958)
//NSTUB(taskIdListGet,		0xFFC00958)
NSTUB(taskLock,				0xFFC00958)
NSTUB(taskUnlock,			0xFFC00958)
NSTUB(Mount_FileSystem,		0xFFC00958)
NSTUB(Unmount_FileSystem,	0xFFC00958)
NSTUB(rewinddir,			0xFFC00958)
NSTUB(CreatePhysicalVram,	0xFFC00958)
NSTUB(CreateTaskStrict,		0xFFC00958)
NSTUB(DisableDispatch,		0xFFC00958)
NSTUB(DisplayImagePhysicalScreen,	 0xFFC00958)
NSTUB(EnableDispatch,		0xFFC00958)
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFC00958)
NSTUB(MakeDirectory,		0xFFC00958)
NSTUB(PhySw_testgpio,		0xFFC00958)
NSTUB(ProtectFile,			0xFFC00958)
NSTUB(chdir,				0xFFC00958)
NSTUB(ioctl,				0xFFC00958)
NSTUB(iosDevAdd,			0xFFC00958)
NSTUB(iosDrvInstall,		0xFFC00958)
NSTUB(isalpha,				0xFFC00958)
NSTUB(isdigit,				0xFFC00958)
NSTUB(islower,				0xFFC00958)
NSTUB(isspace,				0xFFC00958)
NSTUB(isupper,				0xFFC00958)
NSTUB(localtime,			0xFFC00958)
NSTUB(readdir,				0xFFC00958)
NSTUB(strpbrk,				0xFFC00958)
NSTUB(taskCreateHookAdd,	0xFFC00958)
NSTUB(taskDeleteHookAdd,	0xFFC00958)
NSTUB(taskIdListGet,		0xFFC00958)
NSTUB(taskName,				0xFFC00958)
NSTUB(taskResume,			0xFFC00958)
NSTUB(taskSuspend,			0xFFC00958)
NHSTUB(GetBatteryTemperature, 0xFFC3A31C)
NHSTUB(GetCCDTemperature, 0xFFC3A2AC)
NHSTUB(GetOpticalTemperature, 0xFFC3A38C)
NHSTUB(PT_PlaySound, 0xFFC52FA0)
//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(SetFileTimeStamp, 0xFFC15328)
