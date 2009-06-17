#include "stubs_asm.h"

// reversed from what finsig finds ?!?
// going by a720, finsig is right
// NHSTUB(GetDrive_FreeClusters, 0xffc416bc)
// NHSTUB(GetDrive_TotalClusters,		0xffc416f0)
NHSTUB(kbd_pwr_off,		0xFFC356C8)
//NHSTUB(MakeBootDisk,		0xFFDF24E4)
//NHSTUB(MakeScriptDisk,		0xFFDF24F8)

// incorrect, using nullsub for now
//NHSTUB(PostLEDMessage,	    0xFFC34B78)
NHSTUB(PostLEDMessage,	    0xFFC00948)

//NHSTUB(TurnOnAFLamp,		0xFFDB9BAC)

//NSTUB(dumpMemoryToFile, 0xffc00948)
NHSTUB(ExecuteEventProcedure, 0xffc59eb4)

//NSTUB(GetAEIntegralServiceMode_0,	0xFFC1A9C4)
//NSTUB(IsFactoryMode,				0xFFC38838)
//NSTUB(taskcreate_AudioTsk,			0xFFC3591C)
//NSTUB(unknown_libname_80, 			0xFFC668B0)
//NSTUB(unknown_libname_96, 			0xFFC6C77C)



//NHSTUB(TurnOnBackLight,		0xFFC6C558)
//NHSTUB(TurnOffBackLight,	0xFFC6C570)
//NHSTUB(SetPanelBrightnessToLcdController,	0xFFC6C5F0)
//NHSTUB(SetCvfBrightnessToLcdController,		0xFFC6C5FC)
//NHSTUB(TurnOnDisplay,		0xFFC6C528)
//NHSTUB(TurnOffDisplay,		0xFFC6C540)
NHSTUB(MuteOnPhysicalScreen,		0xFFC6C588)
NHSTUB(MuteOffPhysicalScreen,		0xFFC6C5A0)
//NHSTUB(ShutDownDisplay,		0xFFC6C754)
//NHSTUB(CameraLog_EmergencyShutDownDisplay,		0xFFC6C760) 	
//NHSTUB(CameraLog_TurnOnDisplayForStartup,		0xFFC6C794)
//NHSTUB(NewTaskShell, 0xFFC5d578)
//NHSTUB(EmergencyMuteOn,		0xFFC6C77C)
NHSTUB(TurnOnMic,		0xFFC35CFC)
NHSTUB(TurnOffMic,		0xFFC35D28)		
NHSTUB(UIFS_WriteFirmInfoToFile,		0xFFD2AA58)
//NHSTUB(EnterToCompensationEVF,		0xFFC15F54)
NHSTUB(ExitFromCompensationEVF,		0xFFC15FA4)
//NHSTUB(StartCameraLog,				0xFFC14258)
//NHSTUB(ShowCameraLog,				0xFFC5AC18)


// these doesnt exist in DryOs
//NSTUB(taskCreateHookAdd,		 0xFFC00948)
//NSTUB(taskDeleteHookAdd,		 0xFFC00948)
//NSTUB(taskIdListGet,			 0xFFC00948)
//NSTUB(taskLock,				 0xFFC00948)
//NSTUB(taskName,			 0xFFC00948)
//NSTUB(taskResume,			 0xFFC00948)
//NSTUB(taskSuspend,			 0xFFC00948)
//NSTUB(taskUnlock,			 0xFFC00948)

// NULLSUBS
NSTUB(Mount_FileSystem,			 0xFFC00948)
NSTUB(Unmount_FileSystem,		 0xFFC00948)
NSTUB(rewinddir,			 0xFFC00948)

//NSTUB(CreatePhysicalVram,		 0xFFC00948)
//NSTUB(CreateTaskStrict,			 0xFFC00948)
//NSTUB(DisableDispatch,			 0xFFC00948)
//NSTUB(DisplayImagePhysicalScreen,	 0xFFC00948)
//NSTUB(EnableDispatch,			 0xFFC00948)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFC00948)
//NSTUB(MakeDirectory,			 0xFFC00948)
//NSTUB(PhySw_testgpio,			 0xFFC356EC)
//NSTUB(ProtectFile,			 0xFFC00948)
//NSTUB(chdir,				 0xFFC00948)
//NSTUB(ioctl,				 0xFFC00948)
//NSTUB(iosDevAdd,			 0xFFC00948)
//NSTUB(iosDrvInstall,			 0xFFC00948)
// implemented in CHDK
//NSTUB(isalpha,				 0xFFC00948)
//NSTUB(isdigit,				 0xFFC00948)
//NSTUB(islower,				 0xFFC00948)
//NSTUB(isspace,				 0xFFC00948)
//NSTUB(isupper,				 0xFFC00948)
//NSTUB(strpbrk,				 0xFFC00948)

//NSTUB(localtime,			 0xFFC00948)
//NSTUB(readdir,				 0xFFC00948)

//NSTUB(taskCreateHookAdd,		 0xFFC00948)
//NSTUB(taskDeleteHookAdd,		 0xFFC00948)
//NSTUB(taskIdListGet,			 0xFFC00948)
//NSTUB(taskName,				 0xFFC00948)
//NSTUB(taskResume,			 0xFFC00948)
//NSTUB(taskSuspend,			 0xFFC00948)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC00948)
NHSTUB(PT_PlaySound, 0xFFC4C8B8)
//NHSTUB(GetBatteryTemperature,	0xFFC377B4)
//NHSTUB(GetOpticalTemperature,	0xFFC37824)
//NHSTUB(GetCCDTemperature,		0xFFC37744)
NHSTUB(MakeAFScan,		0xFFC00948)
//NHSTUB(utime, 0xFFC00948)
NHSTUB(ExpCtrlTool_StopContiAE,		0xFFC22054)
NHSTUB(ExpCtrlTool_StartContiAE,	0xFFC21F10)
NHSTUB(SetZoomForMovie,		0xFFD3A2C4)
NHSTUB(UnsetZoomForMovie,		0xFFD3A34C)
NHSTUB(SetAE_ShutterSpeed,		0xFFE41C40)
NHSTUB(DoAFLock, 0xffc15b04)
NHSTUB(UnlockAF, 0xffc15c1c)
NHSTUB(apex2us, 0xFFD7DD6C)


