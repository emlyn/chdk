#include "stubs_asm.h"
// NOTE: 0xFFFF1134 is a dummy routine for functions that haven't been found yet, it is just a BX LR instruction
// not found correctly by finsig

//Autofound Required!
NHSTUB(TurnOffBackLight,0xFF878DEC)	//DispSwCon_TurnOffBackLight
NHSTUB(VbattGet,0xFF91B708)		//eventproc_export_VbattGet
NHSTUB(vsprintf,0xFF81CBA0)		//eventproc_export_CPrintf look for function called before error txt
NHSTUB(Mount_FileSystem,0xFF858BEC)		//Do we fix? Not in Dryos?
NHSTUB(Unmount_FileSystem,0xFF858BEC)		//Do we fix? Not in Dryos?
NHSTUB(rewinddir,0xFF858BEC)			//Do we fix? Not in Dryos?
NHSTUB(SetZoomActuatorSpeedPercent,0xFF858BEC)	//Do we fix? Not in Dryos?
NHSTUB(strchr,0xFF88779C)			//search AND R2, R1, #0xFF then LDRB R1, [R0]
NHSTUB(kbd_pwr_on,0xFF858BEC)			//Do we fix?
NHSTUB(kbd_read_keys,0xFF821DCC)		//Look for LDR R0, =YYYY then BL GetKbdState then LDR R0, =YYYY
NHSTUB(DoAFLock,0xFF85B170)			//Look for AFL*
NHSTUB(UnlockAF,0xFF85B180)			//Look for AFUL*
NHSTUB(LEDDrive,0xFF842698)
NHSTUB(ScreenLock,0xFF99CEC4)			//Look for ScreenLock
NHSTUB(RefreshPhysicalScreen,0xFF99CF18)	//Look for ScreenUnLock
NHSTUB(EnterToCompensationEVF,0xFF825420)	//Look for ExpOn
NHSTUB(ExitFromCompensationEVF,0xFF825464)	//Look for ExpOff
NHSTUB(PT_PlaySound,0xFF85B05C)			//Look for LDRH R0, [R0] follow by LDR R1, [R1]
NHSTUB(WriteSDCard,0xFF903B38)			//Look for ADD     R7, R1, R2,LSL#2
NHSTUB(GetDrive_FreeClusters,0xFF852440)	//Not certain
NHSTUB(GetDrive_TotalClusters,0xFF852414)	//Not certain
NHSTUB(GetDrive_ClusterSize,0xFF8523E8)		//Not certain
NHSTUB(GetOpticalTemperature,0xFF845FA4)	//Not certain	
NHSTUB(GetCurrentTargetDistance,0xFF912430)
NHSTUB(kbd_p2_f,0xFF82170C)			//task_PhySw+1C
NHSTUB(qsort,0xFFA79A4C)			//Look for "ORR     R2, R0, R2" (second hit)
NHSTUB(PutInNdFilter,0xFFA3C4A4)
NHSTUB(PutOutNdFilter,0xFFA3C4C8)  //Search for "NdActuator.c" and compare to SD990...
NHSTUB(SetPropertyCase,0xFF86E17C)
NHSTUB(OpLog_Get,0xFF86C53C)		//OpLog.Get()
NHSTUB(qprintf,0xFF8115A8)
NHSTUB(UnsetZoomForMovie,0xFF94AFC4)  //"ZoomCon_UnsetZoomForMovie"
NHSTUB(ShowAllTaskInfo,0xFF91BA70) //HMMM
NHSTUB(MoveIrisFullClose,0xFFA9237C)

NHSTUB(AllocateUncacheableMemory, 0xFF827448) //Override default found version Replaced found one based on missed location..
NHSTUB(kbd_pwr_off, 0xFF858BEC)  //Override default found version
NHSTUB(stdioSetup, 0xFF813578)
NHSTUB(HdmiRegDump,0xFF841CB0)
NHSTUB(EdidDump,0xFF841BE8)
NHSTUB(drvInfo,0xFF81E33C);
NHSTUB(blah,0xFF8462F8);
NHSTUB(open2,0xFF823C70);

NHSTUB(ExpCtrlTool_StartContiAE, 0xFF82FF40) //"StartContiAE"
NHSTUB(ExpCtrlTool_StopContiAE, 0xFF830084)  //"StopContiAE"

NHSTUB(MakeAFScan, 0xFF85B170)  //DoAFLock   Well we don't know if this is the best way but it works for now....
NHSTUB(apex2us,0xFF9A010C)  //See 0xFF888F4C
NHSTUB(SetAE_ShutterSpeed, 0xFFA96F60)

//Build Required!
NHSTUB(PostLogicalEventForNotPowerType,0xFF858BEC)


NHSTUB(GetFocusLensSubjectDistance,0xFFFF1134)
NHSTUB(SetScriptMode, 0xFFFF1134)

// Needed after moving to Mac OS X
NHSTUB(Lseek,0xFFFF1134)
NHSTUB(ReadFastDir,0xFFFF1134)
NHSTUB(Remove,0xFFFF1134)
NHSTUB(TurnOnBackLight,0xFFFF1134)
NHSTUB(UIFS_WriteFirmInfoToFile,0xFFFF1134)
NHSTUB(openfastdir,0xFFFF1134)
NHSTUB(readfastdir,0xFFFF1134)
NHSTUB(rename,0xFFFF1134)

