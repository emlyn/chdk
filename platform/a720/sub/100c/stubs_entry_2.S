#include "stubs_asm.h"

NHSTUB(SleepTask, 0xFFC196d0)
NHSTUB(CreateTask, 0xFFC0BBC0)
NHSTUB(ExitTask, 0xFFC0BE50)
NHSTUB(AllocateMemory, 0xFFDD7DF4)
NHSTUB(ExecuteEventProcedure                  ,0xFFC0C278)
NHSTUB(FreeMemory                             ,0xFFDD7DE0)
NHSTUB(GetCurrentTargetDistance               ,0xFFCFDB3C)
NHSTUB(GetSystemTime                          ,0xFFDD7EFC)
NHSTUB(ints_disable                           ,0xFFC00578)
NHSTUB(ints_enable                            ,0xFFC005A0)
NHSTUB(memcmp                                 ,0xFFC0E8F0)
NHSTUB(memcpy                                 ,0xFFC71BF4)
NHSTUB(memset                                 ,0xFFE0E37C)
NHSTUB(Close                                  ,0xFFC1502C)
NHSTUB(Open                                   ,0xFFC15004)
NHSTUB(Read                                   ,0xFFC0A448)
NHSTUB(Write                                  ,0xFFC150D8)
NHSTUB(Lseek 				      ,0xFFC1516C)
NHSTUB(strcmp                                 ,0xFFC0E888)
NHSTUB(strcpy                                 ,0xFFC0E834)
NHSTUB(strlen                                 ,0xFFC0E8CC)
NHSTUB(TakeSemaphore                          ,0xFFC0BA5C)
NHSTUB(vsprintf, 0xFFC0E7B4)    // first sub called in FADBGPrintf
NHSTUB(GetFocusLensSubjectDistance,	 0xFFCFEF9C)    // returns 0. What's wrong?
NHSTUB(GetZoomLensCurrentPoint,           0xFFD02FDC)
NHSTUB(GetZoomLensCurrentPosition,        0xFFD03B5C)
NHSTUB(RefreshPhysicalScreen,		  0xFFD62184)
NHSTUB(GetPropertyCase,			 0xFFC59c2c)    // PT_GetPropertyCaseString
NHSTUB(SetPropertyCase,			 0xFFC50CC8)    // PT_SetPropertyCaseString
NHSTUB(VbattGet,                          0xFFC119A8)    
NHSTUB(kbd_read_keys, 0xFFC130CC)       // will be replaced in kbd.c
NHSTUB(kbd_p1_f, 0xFFC131D0)
NHSTUB(kbd_p1_f_cont, 0xFFC131DC)
NHSTUB(kbd_p2_f, 0xFFC12A1C)
NHSTUB(kbd_pwr_on, 0xFFC37068)
NHSTUB(kbd_pwr_off, 0xFFC370C0)
NHSTUB(kbd_read_keys_r2, 0xFFC36B14)

NHSTUB(mkdir, 0xFFC153D0)
NHSTUB(GetParameterData, 0xFFD1C5B8)
NHSTUB(SetParameterData, 0xFFD1C528)
NHSTUB(IsStrobeChargeCompleted, 0xFFC974E4)

NHSTUB(open,				 0xFFC0A1B0)
NHSTUB(write,				 0xFFC0A4A8)
NHSTUB(close,				 0xFFC0A260)
NHSTUB(lseek,				 0xFFC1516C)     // = Lseek
NHSTUB(read,                             0xFFC0A448)     // = Read

NHSTUB(Fopen_Fut,                        0xFFC149D0)
NHSTUB(Fwrite_Fut,                       0xFFC14B10)
NHSTUB(Fclose_Fut,                       0xFFC14a10)
NHSTUB(Fread_Fut,                        0xFFC14ABC)
NHSTUB(Fseek_Fut, 0xFFC14BB0)
NHSTUB(Remove, 0xFFC15074)
NHSTUB(rename, 0xFFC15100)

NHSTUB(GetDrive_ClusterSize, 0xFFC3F4C4)
NHSTUB(GetDrive_TotalClusters, 0xFFC3F4F8)
NHSTUB(GetDrive_FreeClusters, 0xFFC3F564)
NHSTUB(LockMainPower ,  0xFFC5BF6C)
NHSTUB(UnlockMainPower, 0xFFC5BEC0)
NHSTUB(GetCurrentAvValue, 0xFFCFFCA8)
NHSTUB(MoveFocusLensToDistance, 0xFFDA6578)
NHSTUB(MoveZoomLensWithPoint, 0xFFD03A88)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00958) // null stub

NHSTUB(_log, 0xFFE3C8DC)
NHSTUB(_log10, 0xFFE3B820)
NHSTUB(_pow, 0xFFE3B990)
NHSTUB(_sqrt, 0xFFE3DC44)

NHSTUB(malloc, 0xFFC039DC)
NHSTUB(free, 0xFFC03AB0)
NHSTUB(FreeUncacheableMemory, 0xFFC1987C)
NHSTUB(AllocateUncacheableMemory, 0xFFC19848)

NHSTUB(rand, 0xFFC0E9F8)
NHSTUB(srand, 0xFFC0E9EC)

NHSTUB(stat, 0xFFC15238)

NHSTUB(openfastdir, 0xFFDC1B04)
NHSTUB(readfastdir, 0xFFDC1B98)
NHSTUB(closefastdir, 0xFFDC1C68)

NHSTUB(qsort, 0xFFD62A14)

//NHSTUB(strstr, 0xFFD62534)
NHSTUB(strncpy, 0xFFC0E84C)
NHSTUB(strrchr, 0xFFC71BCC)
NHSTUB(strncmp, 0xFFC71B5C)
NHSTUB(strchr, 0xFFC71BA8)
NHSTUB(strcat, 0xFFC71B20)
NHSTUB(strtol, 0xFFC1FC0C)

NHSTUB(time, 0xFFC55F0C)
NHSTUB(LocalTime, 0xFFC56058)

NHSTUB(UpdateMBROnFlash, 0xFFC3F28C)

NHSTUB(opendir, 0xFFDC1B04) // OpenFastDir
NHSTUB(ReadFastDir, 0xFFDC1B98)
NHSTUB(closedir, 0xFFDC1C68)  // CloseFastDir
NHSTUB(UnsetZoomForMovie, 0xFFD22418)


NHSTUB(PostLEDMessage, 0xFFC366B8)
NHSTUB(TurnOnMic, 0xFFC376CC)
NHSTUB(TurnOffMic, 0xFFC376F8)

//NHSTUB(ExpCtrlTool_StopContiAE,  0xFFC8DA00) 
//NHSTUB(ExpCtrlTool_StartContiAE, 0xFFC8D9C4) 
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFC00958) // null stub
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFC00958) // null stub
NHSTUB(MakeAFScan,  0xFFDD4AA4) 


// dryos Test
NHSTUB(NewTaskShell, 0xFFC596B0)  // starts new shell on Console. GUI output?
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFFD4A934) // should write 'A/FirmInfo.txt'
NHSTUB(dumpMemoryToFile, 0xFFC141Fa)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)


// !! UNKNOWN !!
// Not found, point to nullsub for immediate return
// nullsub_1: 0xFFC00958

NHSTUB(utime, 0xFFC00958)


//NSTUB(CreatePhysicalVram,		 0xFFC00958)
//NSTUB(CreateTaskStrict,			 0xFFC00958)
//NSTUB(DisableDispatch,			 0xFFC00958)
//NSTUB(DisplayImagePhysicalScreen,	 0xFFC00958)
//NSTUB(EnableDispatch,			 0xFFC00958)
//NSTUB(ioctl,				 0xFFC00958)
//NSTUB(iosDevAdd,			 0xFFC00958)
//NSTUB(iosDrvInstall,			 0xFFC00958)
//NSTUB(memPartAlloc,			 0xFFC00958)
//NSTUB(memPartFindMax,			 0xFFC00958)
//NSTUB(PhySw_testgpio,			 0xFFC00958)
//NSTUB(ProtectFile,			 0xFFC00958)


// Those aren't used or don't exist in DryOS

//NSTUB(taskCreateHookAdd,		 0xFFC00958)
//NSTUB(taskDeleteHookAdd,		 0xFFC00958)
//NSTUB(taskIdListGet,			 0xFFC00958)
NSTUB(taskLock,				 0xFFC00958)
//NSTUB(taskName,			 0xFFC00958)
//NSTUB(taskResume,			 0xFFC00958)
//NSTUB(taskSuspend,			 0xFFC00958)
NSTUB(taskUnlock,			 0xFFC00958)
NSTUB(Mount_FileSystem,			 0xFFC00958)
NSTUB(Unmount_FileSystem,		 0xFFC00958)
NSTUB(rewinddir,			 0xFFC00958)
NSTUB(CreatePhysicalVram,		 0xFFC00958)
NSTUB(CreateTaskStrict,			 0xFFC00958)
NSTUB(DisableDispatch,			 0xFFC00958)
NSTUB(DisplayImagePhysicalScreen,	 0xFFC00958)
NSTUB(EnableDispatch,			 0xFFC00958)
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFC00958)
NSTUB(MakeDirectory,			 0xFFC00958)
NSTUB(PhySw_testgpio,			 0xFFC00958)
NSTUB(ProtectFile,			 0xFFC00958)
NSTUB(chdir,				 0xFFC00958)
NSTUB(ioctl,				 0xFFC00958)
NSTUB(iosDevAdd,			 0xFFC00958)
NSTUB(iosDrvInstall,			 0xFFC00958)
NSTUB(isalpha,				 0xFFC00958)
NSTUB(isdigit,				 0xFFC00958)
NSTUB(islower,				 0xFFC00958)
NSTUB(isspace,				 0xFFC00958)
NSTUB(isupper,				 0xFFC00958)
NSTUB(localtime,			 0xFFC00958)
NSTUB(readdir,				 0xFFC00958)
NSTUB(strpbrk,				 0xFFC00958)
NSTUB(taskCreateHookAdd,		 0xFFC00958)
NSTUB(taskDeleteHookAdd,		 0xFFC00958)
NSTUB(taskIdListGet,			 0xFFC00958)
NSTUB(taskName,				 0xFFC00958)
NSTUB(taskResume,			 0xFFC00958)
NSTUB(taskSuspend,			 0xFFC00958)
