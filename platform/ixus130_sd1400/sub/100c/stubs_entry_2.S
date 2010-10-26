#include "stubs_asm.h"

// 0xff811800 is a nullsub (points to a "bx lr" instruction)

// First round, these are not found
NHSTUB(DoAFLock, 0xff83809c)                     // "AFL*"
NHSTUB(EnterToCompensationEVF, 0xff8381e8)       // "ExpOn"
NHSTUB(ExitFromCompensationEVF, 0xff83822c)      // "ExpOff"
NHSTUB(ExpCtrlTool_StartContiAE, 0xff845e30)     //
NHSTUB(GetDrive_FreeClusters, 0xff86f510)
NHSTUB(MakeAFScan, 0xff95d380)                   // "SsPrepareSeqBase.c"
NHSTUB(Mount_FileSystem, 0xff811800)             // nullsub
NHSTUB(OpLog_Get, 0xff88a4b0)                    // just before "OpePlay"
NHSTUB(PT_PlaySound, 0xff880eb4)                 // (000001ef)
NHSTUB(PutInNdFilter, 0xffafb2e4)                // (e59f00b0)
NHSTUB(PutOutNdFilter, 0xffafb31c)               //   ditto
NHSTUB(ReadFastDir, 0xffa751f8)                  // how to find this? same as readfastdir (below)?
NHSTUB(RefreshPhysicalScreen, 0xff9f786c)        // "ScreenUnLock"
NHSTUB(Remove, 0xff836bac)                       // ixus300 - 0x240
NHSTUB(ScreenLock, 0xff9f8cb4)                   // "ScreenLock"
NHSTUB(SetScriptMode, 0xff890a68)                // "EventReciever.c"
NHSTUB(SetZoomActuatorSpeedPercent, 0xff811800) 
NHSTUB(TurnOffBackLight, 0xff89df30)             // "TurnOffBackLight"
NHSTUB(TurnOnBackLight, 0xff89df18)              // "TurnOnBackLight"
NHSTUB(UnlockAF, 0xff838120)                     // "AFUL"
NHSTUB(Unmount_FileSystem, 0xff811800)
NHSTUB(UnsetZoomForMovie, 0xff811800)
NHSTUB(WriteSDCard, 0xff942b50)                  // "SdDrv.c", compare to sx210is
NHSTUB(apex2us, 0xff9fc310)                      // (fffffdc0)
NHSTUB(qsort, 0xffae54e8)                        // search 'orr r2, r0, r2' near 'tst r2, #3'
NHSTUB(rename, 0xff836c54)                       // search 'mvnne r4, #0' then compare
NHSTUB(rewinddir, 0xff811800)                    // nullsub

// Then these are sometimes not found
NHSTUB(Lseek, 0xff836c94)                        // search 'asr r1, r1, #31'
NHSTUB(UIFS_WriteFirmInfoToFile, 0xff9734d0)     // "A/FirmInfo.txt"
NHSTUB(kbd_pwr_on, 0xff811800)
NHSTUB(kbd_read_keys, 0xff83459c)                // "SD Protect"
NHSTUB(openfastdir, 0xffa750a4)                  // "ReadFDir.c"
NHSTUB(readfastdir, 0xffa751f8)                  // "ReadFDir.c"

NHSTUB(lseek, 0xff836c94)                        // same as Lseek (?)

// Fixing some that were found incorrectly
//NHSTUB(MoveFocusLensToDistance, 0xffafd558)      // like ixus300_sd4000
NHSTUB(MoveFocusLensToDistance, 0xffafd56c)      // like sx210is
NHSTUB(RenameFile_Fut, 0xff83645c)
NHSTUB(SetFileTimeStamp, 0xff836e14)
NHSTUB(UpdateMBROnFlash, 0xff86f330)
NHSTUB(closedir, 0xffa75054)
NHSTUB(closefastdir, 0xffa75054)                 // same as closedir
NHSTUB(strcat, 0xff8a5290)
NHSTUB(strrchr, 0xff814008)
NHSTUB(GetZoomLensCurrentPosition, 0xffa861d8)
NHSTUB(kbd_pwr_off, 0xff811800)

// Check:
// GetCurrentAvValue, GetZoomLensCurrentPoint

// Fix screen redraw
NHSTUB(LockAndRefresh, 0xff9f8a9c)               // (000005bc) near "Window.c"
NHSTUB(UnlockAndRefresh, 0xff9f8ae0)             // ditto
