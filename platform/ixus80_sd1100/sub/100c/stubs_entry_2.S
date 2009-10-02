#include "stubs_asm.h"

NHSTUB(dumpMemoryToFile, 0xffc141f4)
NHSTUB(ExpCtrlTool_StartContiAE, 0xff832a98)
NHSTUB(ExpCtrlTool_StopContiAE, 0xff832bdc)
NHSTUB(PostLEDMessage, 0xff8420c0)

// not found on other dryos cams here, so not in sig
NHSTUB(OpLog_WriteToSD, 0xff86ab44)
NHSTUB(PutInNdFilter, 0xffa7aad0)
NHSTUB(PutOutNdFilter, 0xffa7ab08)
NHSTUB(UnsetZoomForMovie,0xff960a4c)


// not found :(
#define do_nothing 0xffa7b658

NHSTUB(TurnOffMic, do_nothing)
NHSTUB(TurnOnMic,do_nothing)


// vx stuff
// not found or used in dryos
NHSTUB(rewinddir, do_nothing)
NHSTUB(SetZoomActuatorSpeedPercent, do_nothing)
NHSTUB(Unmount_FileSystem, do_nothing)
NHSTUB(Mount_FileSystem, do_nothing)
NHSTUB(taskUnlock, do_nothing)
NHSTUB(taskLock, do_nothing)
NHSTUB(DoAFLock, 0xff825c4c)
NHSTUB(UnlockAF, 0xff825c90)
NHSTUB(apex2us, 0xFF9AC134)
