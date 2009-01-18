#include "stubs_asm.h"

NHSTUB(SleepTask, 0xFF82A610)
NHSTUB(CreateTask, 0xFF81BAF0)
NHSTUB(ExitTask, 0xFF81BD80)
NHSTUB(AllocateMemory, 0xFFA47CC8)
NHSTUB(ExecuteEventProcedure                  ,0xFF81C1A8)
NHSTUB(FreeMemory                             ,0xFFA47CB4)
NHSTUB(GetCurrentTargetDistance               ,0xff934c5c) 
NHSTUB(GetSystemTime                          ,0xFFA47DD0)
NHSTUB(ints_disable                           ,0xFF810578) // used IRQdisable was FFC00578
NHSTUB(ints_enable                            ,0xFF8105A0) // used IRQenable was FFC005A0
NHSTUB(memcmp                                 ,0xFF81E834)
NHSTUB(memcpy                                 ,0xFF895CF0)
NHSTUB(memset                                 ,0xFFA8D404)
NHSTUB(Close                                  ,0xFF82552C)
NHSTUB(Open                                   ,0xFF825504)
NHSTUB(Read                                   ,0xFF81A378)
NHSTUB(Write                                  ,0xFF8255D8)
NHSTUB(Lseek 				      ,0xFF82566C)
NHSTUB(strcmp                                 ,0xFF81E7F4)
NHSTUB(strcpy                                 ,0xFF81E778)
NHSTUB(strlen                                 ,0xff81e810)	//0xFF816098
NHSTUB(TakeSemaphore                          ,0xFF81B98C)
NHSTUB(vsprintf, 0xff81e6f8)    // first sub called in FADBGPrintf 
NHSTUB(GetFocusLensSubjectDistance,	 0xff9360bc)    // returns 0. What's wrong? 
NHSTUB(GetZoomLensCurrentPoint,           0xFF93A290) 
NHSTUB(GetZoomLensCurrentPosition,        0xFFA3E658)
NHSTUB(RefreshPhysicalScreen,		  0xFF9BDBE4) 
NHSTUB(GetPropertyCase,			 0xFF86F768)    // PT_GetPropertyCaseString
NHSTUB(SetPropertyCase,			 0xFF86F660)    // PT_SetPropertyCaseString
NHSTUB(VbattGet,                          0xFF82199C)    
NHSTUB(kbd_read_keys, 0xFF8230CC)       // will be replaced in kbd.c no was ff8230c4
NHSTUB(kbd_p1_f, 0xFF8231C8)			// g9 ok
NHSTUB(kbd_p1_f_cont, 0xff8231d4) 		//g9 ok
NHSTUB(kbd_p2_f, 0xFF822A18)			// g9 ok
NHSTUB(kbd_pwr_on, 0xFF810958)  //no was FFC37068 pointed to nullsub
NHSTUB(kbd_pwr_off, 0xFF810958) //no was FFC370C0    "     "    "
NHSTUB(kbd_read_keys_r2, 0xFF848DC8)
//0xFF848DE4) 
//NHSTUB(platformsub_kbd_fetch_data, 0xFFC37DF4)	// (в sx100is?) EWAVR указал на этот адрес в форуме iXBT, не используется. клава сделана на основе s5is
NHSTUB(GetKbdState, 0xFF849300)

//NHSTUB(taskcreate_jogDial, 0xFFC38128)
NHSTUB(GiveSemaphore, 0xFF81BA5C)	//+++
 

NHSTUB(mkdir, 0xFF8258D0) 
NHSTUB(GetParameterData, 0xFF95695C) 
NHSTUB(SetParameterData, 0xFF956838) 
NHSTUB(IsStrobeChargeCompleted, 0xFF8C1344) 

NHSTUB(open,				 0xFF81A0E0)
NHSTUB(write,				 0xff81a3d8)	//0xFF8255D8
NHSTUB(close,				 0xFF81A190)
NHSTUB(lseek,				 0xFF82566C)     // = Lseek
NHSTUB(read,                             0xFF81A378)     // = Read

NHSTUB(Fopen_Fut,                        0xFF824ED0)
NHSTUB(Fwrite_Fut,                       0xff825010) 
NHSTUB(Fclose_Fut,                       0xFF824F10)
NHSTUB(Fread_Fut,                        0xff824fbc) 
NHSTUB(Fseek_Fut, 0xFF8250B0)
NHSTUB(Remove, 0xFF825574) 
NHSTUB(rename, 0xFF825600) 

NHSTUB(GetDrive_ClusterSize, 0xFF852754) 
NHSTUB(GetDrive_TotalClusters, 0xFF852788) 
NHSTUB(GetDrive_FreeClusters, 0xFF8527f4) 
NHSTUB(LockMainPower ,  0xFF8731F0)
NHSTUB(UnlockMainPower, 0xFF873144)
NHSTUB(GetCurrentAvValue, 0xff936dc8) 
NHSTUB(MoveFocusLensToDistance, 0xFFA0E134) 
NHSTUB(MoveZoomLensWithPoint, 0xFF93AD3C)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810958) // used nullsub_1 FF810958 was FFC00958

NHSTUB(_log, 0xffabe6b4) 
NHSTUB(_log10, 0xffabd5f8) 
NHSTUB(_pow, 0xffabd768) 
NHSTUB(_sqrt, 0xffabfa1c) 

NHSTUB(malloc, 0xFF8139DC)
NHSTUB(free, 0xff813ab0) 
NHSTUB(FreeUncacheableMemory, 0xff82a7bc) 
NHSTUB(AllocateUncacheableMemory, 0xff82a788) 

NHSTUB(rand, 0xff81e93c) 
NHSTUB(srand, 0xff81e930)

NHSTUB(stat, 0xff825738) 

NHSTUB(openfastdir, 0xffa2cb18) 
NHSTUB(readfastdir, 0xffa2cbac) 
NHSTUB(closefastdir, 0xffa2cc7c) 

NHSTUB(qsort, 0xff9be474) 

//NHSTUB(strstr,  0xFF81E778) //?
NHSTUB(strncpy, 0xff81e790) 	//+
NHSTUB(strrchr, 0xff895cc8) 	//+
NHSTUB(strncmp, 0xff895c58) 	//+
NHSTUB(strchr,  0xff895ca4) 	//+
NHSTUB(strcat,  0xff895c1c) 	//+
NHSTUB(strtol,  0xff830d90) 	//+

//NHSTUB(time, 0xff86b3ec) 
NHSTUB(LocalTime, 0xff86b538) 

NHSTUB(UpdateMBROnFlash, 0xff85251c) 

NHSTUB(opendir, 0xFFA2CB18) 
NHSTUB(ReadFastDir, 0xFFA2CBAC) 
NHSTUB(closedir, 0xFFA2CC7C)  // CloseFastDir 
NHSTUB(UnsetZoomForMovie, 0xFF95D03C) // used aZoomcon_unset FF95D234 was 0xFFD22418 


NHSTUB(PostLEDMessage, 0xFF848910) 
NHSTUB(TurnOnMic, 0xFF810958)		// nullsub_1
NHSTUB(TurnOffMic, 0xFF810958)		// nullsub_1
 
NHSTUB(ExpCtrlTool_StopContiAE,  0xFF8357C0) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF835600) 
NHSTUB(MakeAFScan,  0xFFA449D0) 
NHSTUB(SetAE_ShutterSpeed, 0xFFA10490) 
 
// dryos Test
NHSTUB(NewTaskShell, 0xff86f1ec)  // starts new shell on Console. GUI output?
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFF99C390) // should write 'A/FirmInfo.txt'
// NHSTUB(dumpMemoryToFile, 0xFFC141Fa)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length) //no

NHSTUB(PT_PlaySound, 0xFF866454) 


NHSTUB(ExitFromCompensationEVF, 0xFF8279F8)



// !! UNKNOWN !!
//// Not found, point to nullsub for immediate return
// nullsub_1: 0xFF810958 



//NSTUB(CreatePhysicalVram,		 0xFF810958) 
//NSTUB(CreateTaskStrict,		 0xFF810958) 
//NSTUB(DisableDispatch,		 0xFF810958) 
//NSTUB(DisplayImagePhysicalScreen,	 0xFF810958) 
//NSTUB(EnableDispatch,			 0xFF810958) 
//NSTUB(ioctl,				 0xFF810958) 
//NSTUB(iosDevAdd,			 0xFF810958) 
//NSTUB(iosDrvInstall,			 0xFF810958) 
//NSTUB(memPartAlloc,			 0xFF810958) 
//NSTUB(memPartFindMax,			 0xFF810958) 
//NSTUB(PhySw_testgpio,			 0xFF810958) 
//NSTUB(ProtectFile,			 0xFF810958) 


//// Those aren't used or don't exist in DryOS

// NSTUB(taskCreateHookAdd,		 0xFF810958)
// NSTUB(taskDeleteHookAdd,		 0xFF810958)
// NSTUB(taskIdListGet,			 0xFF810958)
NSTUB(taskLock,				 0xFF810958) 
// NSTUB(taskName,			 0xFF810958)
// NSTUB(taskResume,			 0xFF810958)
// NSTUB(taskSuspend,			 0xFF810958)
NSTUB(taskUnlock,			 0xFF810958) 
NSTUB(Mount_FileSystem,			 0xFF810958) 
NSTUB(Unmount_FileSystem,		 0xFF810958) 
NSTUB(rewinddir,			 0xFF810958) 
NSTUB(CreatePhysicalVram,		 0xFF810958)  
NSTUB(CreateTaskStrict,			 0xFF810958)  
NSTUB(DisableDispatch,			 0xFF810958)  
NSTUB(DisplayImagePhysicalScreen,	 0xFF810958)  
NSTUB(EnableDispatch,			 0xFF810958)  
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFF810958) // GetFocusLensSubjectDistance  FF9360BC  GetFocusLensLoadSubjectDistance  FF9360E8 used was FFC00958
NSTUB(MakeDirectory,			 0xFF810958) 
NSTUB(PhySw_testgpio,			 0xFF810958)  
NSTUB(ProtectFile,			 0xFF810958)  
NSTUB(chdir,				 0xFF810958)  
NSTUB(ioctl,				 0xFF810958)  
NSTUB(iosDevAdd,			 0xFF810958)  
NSTUB(iosDrvInstall,			 0xFF810958)  
NSTUB(isalpha,				 0xFF810958)  
NSTUB(isdigit,				 0xFF810958)  
NSTUB(islower,				 0xFF810958)  
NSTUB(isspace,				 0xFF810958) 
NSTUB(isupper,				 0xFF810958) 
NSTUB(localtime,			 0xff86b538) 
NSTUB(readdir,				 0xFF810958) 
NSTUB(strpbrk,				 0xFF810958) 
NSTUB(taskCreateHookAdd,		 0xFF810958) 
NSTUB(taskDeleteHookAdd,		 0xFF810958) 
NSTUB(taskIdListGet,			 0xFF810958) 
NSTUB(taskName,				 0xFF810958) 
NSTUB(taskResume,			 0xFF810958) 
NSTUB(taskSuspend,			 0xFF810958) 
// not found
NSTUB(PutInNdFilter, 0xFF810958)
NSTUB(PutOutNdFilter, 0xFF810958)

NHSTUB(WriteSDCard, 0xFF928CF4)
NHSTUB(DoAFLock, 0xff8275cc)
NHSTUB(UnlockAF, 0xff827638)

