#include "stubs_asm.h"
#define NULLSUB 0xFF810950

// Not found by finsig
NHSTUB(GetDrive_ClusterSize,0xFF855D3C) // via string "MovEdit", sub_FFA448EC (taskcreate_MovEdit)
NHSTUB(GetDrive_FreeClusters,0xFF855D94) // via sub_FFAB159C, near GetDriveClusterSize, near function referring to string "/"
NHSTUB(GetDrive_TotalClusters,0xFF855D68) // via sub_FF854D98, just before call to GetDrive_ClusterSize
NHSTUB(GetFocusLensSubjectDistance,0xFF927428) //string GetFocusLensSubjectDistance, function called by eventproc, eventproc just prints
NHSTUB(kbd_pwr_on,NULLSUB)  // not needed on this camera
NHSTUB(kbd_pwr_off,NULLSUB)  // "

NHSTUB(EnterToCompensationEVF,NULLSUB) 
NHSTUB(ExitFromCompensationEVF,NULLSUB) 

NHSTUB(RefreshPhysicalScreen,0xFF9B96D0)  // string ScreenUnLock
NHSTUB(TurnOffBackLight,0xFF88527C)  // string
NHSTUB(strchr,0xFF88B690)  // via sub_FF8DAF9C refs to strings "000" and "01"

// found incorrectly by finsig
NHSTUB(qsort, 0xFFA83B3C)  // near sscanf, via sscanf eventproc
NHSTUB(strrchr, 0xFF9B9A34 )  // just before memset eventproc, similar to sd990

// Not in sig_ref
NHSTUB(ScreenLock,0xFF9B967C)  // string ScreenLock
NHSTUB(UnsetZoomForMovie,0xFF960E78) // "ZoomCon_UnsetZoomForMovie"
//NHSTUB(ScreenUnLock,0xFF9B96D0) // AKA RefreshPhysicalScreen
NHSTUB(PutInNdFilter,0xFFA46B10) // string TurnOnNdFilter
NHSTUB(PutOutNdFilter,0xFFA46B34) // string TurnOffNdFilter
NHSTUB(DoAFLock,0xFF85E914) // PT_DoAFLock 
NHSTUB(UnlockAF,0xFF85E924) // PT_UnlockAF 
NHSTUB(WriteSDCard,0xFF918B18) // via sub_FF855348, near "SCRIPT", same as found by err99 udumper
NHSTUB(LEDDrive,0xFF846818) // string LEDDrive
NHSTUB(SetScriptMode,0xFF877B2C) // "SetScriptMode"
NHSTUB(MakeAFScan,0xFF932820) // from sub_FF861864 called from CaptSeqTask jumptable entry 0
NHSTUB(ExpCtrlTool_StartContiAE,0xFF83024C) // "StartContiAE"

// These don't exist/aren't found in dryos
NHSTUB(Mount_FileSystem,NULLSUB) // NULLSUB
NHSTUB(Unmount_FileSystem,NULLSUB) // NULLSUB
NHSTUB(rewinddir,NULLSUB) // NULLSUB
NHSTUB(SetZoomActuatorSpeedPercent,NULLSUB) // NULLSUB

// useful for debugging with uart redirect or crash log
NHSTUB(LogPrintf,0xFF86EF38)
// allocate from given EXMEM pool
NHSTUB(exmem_alloc, 0xFF86C810)
// not needed yet
//NHSTUB(exmem_free, 0xFF86C7B0)
