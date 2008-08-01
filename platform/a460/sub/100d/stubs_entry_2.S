#include "stubs_asm.h"

// maybe 0xFFDBA0A8 but it is not used in CHDK at all
NHSTUB(DisplayImagePhysicalScreen, 0xFFDBA0A8)

NHSTUB(Mount_FileSystem, 0xFFE1CAF4)
NHSTUB(free, 0xFFCCC760)
NHSTUB(kbd_read_keys_r2, 0xFFDC4AC8) 

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC017E8)  //null stub
       
NHSTUB(kbd_pwr_off, 0xFFC017E8)   //null stub
NHSTUB(kbd_pwr_on, 0xFFC017E8)    //null stub                                                      

NHSTUB(SetPropertyCase,0xFFC0B664) 

NHSTUB(GetDrive_ClusterSize, 0xFFE1CFBC)
NHSTUB(GetDrive_TotalClusters, 0xFFE1CFF8)
NHSTUB(GetDrive_FreeClusters, 0xFFE1D034)
NHSTUB(TurnOffMic, 0xFFDC5844)
NHSTUB(TurnOnMic, 0xFFDC5808)
NHSTUB(ExpCtrlTool_StopContiAE,  0xFFD0DCD8) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFFD0DCA8) 
NHSTUB(MakeAFScan,               0xFFE70024) 
NHSTUB(GetBatteryTemperature, 0xFFDC7D84)
NHSTUB(GetCCDTemperature, 0xFFDC7D70)
NHSTUB(GetOpticalTemperature, 0xFFDC7D5C)
NHSTUB(PT_PlaySound, 0xFFE7A9F0)

