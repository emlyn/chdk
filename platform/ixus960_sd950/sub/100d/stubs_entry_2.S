#include "stubs_asm.h"


NHSTUB(GetCurrentAvValue, 0xFF9275C4)
NHSTUB(kbd_pwr_off, 0xFF844640)
NHSTUB(kbd_pwr_on, 0xFF8445F0)
NHSTUB(kbd_read_keys_r2, 0xFF84415C)
NHSTUB(time, 0xFF865AC8)
//NHSTUB(OnPrintTouchWheel, 0xFF8E7130)
//NHSTUB(OffPrintTouchWheel, 0xFF8E7120)


NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810958)  //null stub

//NHSTUB(TurnOnMic, 0xFFC376CC)
//NHSTUB(TurnOffMic, 0xFFC376F8)

//!!! dryos Test
NHSTUB(NewTaskShell, 0xFFC596B0)  // starts new shell on Console. GUI output?
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFFD4A934) // should write 'A/FirmInfo.txt'
NHSTUB(dumpMemoryToFile, 0xFFC141Fa)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)


// !! UNKNOWN !!
// Not found, point to nullsub for immediate return
// nullsub_1: 0xFF810958

NHSTUB(utime, 0xFF810958)


//NSTUB(CreatePhysicalVram,		 0xFF810958)
//NSTUB(CreateTaskStrict,	       0xFF810958)
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


// Those aren't used or don't exist in DryOS

//NSTUB(taskCreateHookAdd,		 0xFF810958)
//NSTUB(taskDeleteHookAdd,		 0xFF810958)
//NSTUB(taskIdListGet,			 0xFF810958)
NSTUB(taskLock,				 0xFF810958)
//NSTUB(taskName,			       0xFF810958)
//NSTUB(taskResume,			 0xFF810958)
//NSTUB(taskSuspend,			 0xFF810958)
NSTUB(taskUnlock,			       0xFF810958)
NSTUB(Mount_FileSystem,			 0xFF810958)
NSTUB(Unmount_FileSystem,		 0xFF810958)
NSTUB(rewinddir,			       0xFF810958)
NSTUB(CreatePhysicalVram,		 0xFF810958)
NSTUB(CreateTaskStrict,			 0xFF810958)
NSTUB(DisableDispatch,			 0xFF810958)
NSTUB(DisplayImagePhysicalScreen,	 0xFF810958)
NSTUB(EnableDispatch,			 0xFF810958)
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFF810958)
NSTUB(MakeDirectory,			 0xFF810958)
NSTUB(PhySw_testgpio,			 0xFF810958)
NSTUB(ProtectFile,			 0xFF810958)
NSTUB(chdir,				 0xFF810958)
NSTUB(ioctl,				 0xFF810958)
NSTUB(iosDevAdd,			       0xFF810958)
NSTUB(iosDrvInstall,			 0xFF810958)
NSTUB(isalpha,				 0xFF810958)
NSTUB(isdigit,				 0xFF810958)
NSTUB(islower,				 0xFF810958)
NSTUB(isspace,				 0xFF810958)
NSTUB(isupper,				 0xFF810958)
NSTUB(localtime,			       0xFF810958)
NSTUB(readdir,				 0xFF810958)
NSTUB(strpbrk,				 0xFF810958)
NSTUB(taskCreateHookAdd,		 0xFF810958)
NSTUB(taskDeleteHookAdd,		 0xFF810958)
NSTUB(taskIdListGet,			 0xFF810958)
NSTUB(taskName,				 0xFF810958)
NSTUB(taskResume,			       0xFF810958)
NSTUB(taskSuspend,			 0xFF810958)

NSTUB(PutInNdFilter,    		 0xFF9E8AC4)
NSTUB(PutOutNdFilter,   		 0xFF9E8AFC)
NSTUB(UnsetZoomForMovie,       	 0xFF94CA38)

NHSTUB(GetBatteryTemperature, 0xFF846CE4)
NHSTUB(GetCCDTemperature, 0xFF846E08)
NHSTUB(GetOpticalTemperature, 0xFF846CE4) //same as battery for now, havent found it yet (dryos thing :D)
NHSTUB(PT_PlaySound, 0xFF8604E0)
//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(DoAFLock, 0xff826b54)
NHSTUB(UnlockAF, 0xff826ba4)

