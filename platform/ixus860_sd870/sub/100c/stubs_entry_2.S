#include "stubs_asm.h"


NHSTUB(GetCurrentAvValue, 0xFF924F7C)
NHSTUB(kbd_pwr_off, 0xFF84448C)
NHSTUB(kbd_pwr_on, 0xFF84443C)
NHSTUB(kbd_read_keys_r2, 0xFF843FA8)
NHSTUB(time, 0xFF865744)
//NHSTUB(OnPrintTouchWheel, 0xFF8E7130)
//NHSTUB(OffPrintTouchWheel, 0xFF8E7120)


NHSTUB(SetZoomActuatorSpeedPercent, 0xFF810958)  //null stub


//!!! dryos Test
NHSTUB(NewTaskShell, 0xFFC596B0)  // starts new shell on Console. GUI output?
NHSTUB(UIFS_WriteFirmInfoToFile, 0xFFD4A934) // should write 'A/FirmInfo.txt'
NHSTUB(dumpMemoryToFile, 0xFFC141Fa)         // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)


// !! UNKNOWN !!
// Not found, point to nullsub for immediate return
// nullsub_1: 0xFF810958

NHSTUB(utime, 0xFF810958)


//NSTUB(CreatePhysicalVram,		 0xFF810958)
//NSTUB(CreateTaskStrict,			 0xFF810958)
//NSTUB(DisableDispatch,			 0xFF810958)
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
//NSTUB(taskName,			 0xFF810958)
//NSTUB(taskResume,			 0xFF810958)
//NSTUB(taskSuspend,			 0xFF810958)
NSTUB(taskUnlock,			 0xFF810958)
NSTUB(Mount_FileSystem,			 0xFF810958)
NSTUB(Unmount_FileSystem,		 0xFF810958)
NSTUB(rewinddir,			 0xFF810958)
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
NSTUB(iosDevAdd,			 0xFF810958)
NSTUB(iosDrvInstall,			 0xFF810958)
NSTUB(isalpha,				 0xFF810958)
NSTUB(isdigit,				 0xFF810958)
NSTUB(islower,				 0xFF810958)
NSTUB(isspace,				 0xFF810958)
NSTUB(isupper,				 0xFF810958)
NSTUB(localtime,			 0xFF810958)
NSTUB(readdir,				 0xFF810958)
NSTUB(strpbrk,				 0xFF810958)
NSTUB(taskCreateHookAdd,		 0xFF810958)
NSTUB(taskDeleteHookAdd,		 0xFF810958)
NSTUB(taskIdListGet,			 0xFF810958)
NSTUB(taskName,				 0xFF810958)
NSTUB(taskResume,			 0xFF810958)
NSTUB(taskSuspend,			 0xFF810958)

NSTUB(PutInNdFilter,    		 0xFF810958)
NSTUB(PutOutNdFilter,   		 0xFF810958)
NSTUB(UnsetZoomForMovie,       	         0xFF810958)
