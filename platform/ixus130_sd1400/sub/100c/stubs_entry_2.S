#include "stubs_asm.h"

// 0xffff1134 is a nullsub

NHSTUB(DoAFLock, 0xff83809c)                    // "AFL*"
NHSTUB(EnterToCompensationEVF, 0xff8381e8)      // "ExpOn"
NHSTUB(ExitFromCompensationEVF, 0xff83822c)     // "ExpOff"
NHSTUB(ExpCtrlTool_StartContiAE, 0xff845e30)    //
NHSTUB(GetDrive_FreeClusters,0xff86f198)        // ?
NHSTUB(MakeAFScan,0xffff1134)                   // nullsub
NHSTUB(Mount_FileSystem,0xffff1134)             // nullsub
NHSTUB(OpLog_Get,0xff88a4b0)                    // search just before "OpePlay"
NHSTUB(PT_PlaySound,0xff880eb4)                 // (000001ef)
NHSTUB(PutInNdFilter,0xffafb2e4)                // (e59f00b0)
NHSTUB(PutOutNdFilter,0xffafb31c)               //   ditto
NHSTUB(ReadFastDir,0xffff1134)                  // how to find this?
NHSTUB(RefreshPhysicalScreen,0xff9f786c)        // "ScreenUnLock"
NHSTUB(Remove,0xff836bac)                       // ixus300 - 0x240
NHSTUB(ScreenLock,0xff9f8cb4)                   // "ScreenLock"
NHSTUB(SetScriptMode,0xff810f04)                // (0000192c)
NHSTUB(SetZoomActuatorSpeedPercent,0xffff1134) 
NHSTUB(TurnOffBackLight,0xff89df30)             // "TurnOffBackLight"
NHSTUB(TurnOnBackLight,0xff89df18)              // "TurnOnBackLight"
NHSTUB(UnlockAF,0xff838120)                     // "AFUL"
NHSTUB(Unmount_FileSystem,0xffff1134)
NHSTUB(UnsetZoomForMovie,0xffff1134)
NHSTUB(WriteSDCard,0xffff1134)
NHSTUB(apex2us,0xffff1134)
NHSTUB(qsort,0xffae54e8)                        // search 'orr r2, r0, r2' near 'tst r2, #3'
NHSTUB(rename,0xff836c54)                       // search 'mvnne r4, #0' then compare
NHSTUB(rewinddir,0xffff1134)                    // nullsub
