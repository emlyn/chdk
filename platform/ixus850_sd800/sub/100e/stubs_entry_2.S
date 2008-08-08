#include "stubs_asm.h"

NHSTUB(free, 0xFFB617C0)
NHSTUB(Open, 0xFF87A3E4)	// before Close
NHSTUB(Rename, 0xFF87A4CC)	// after Write

NSTUB(kbd_p1_f, 0xFF8280BC) // ok
NSTUB(kbd_p1_f_cont, 0xFF8280C8) // ok
NSTUB(kbd_p2_f, 0xFF8284A0) // ok
NHSTUB(kbd_pwr_off, 0xFF82930C) // corrected
NHSTUB(kbd_pwr_on, 0xFF8292CC) // corrected
NHSTUB(kbd_read_keys_r2, 0xFF828E30) // added

NSTUB(GetCurrentAvValue, 0xFFB132B0)

NHSTUB(AllocateMemory, 0xFF81AD84)
NHSTUB(FreeMemory, 0xFF81AD70)
NHSTUB(GetFocusLensSubjectDistance, 0xFFB021E8) 
NHSTUB(SetPropertyCase, 0xFF8258C4) // see "PropertyCase.c" and refs to it

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8E68F4)

NHSTUB(GetDrive_ClusterSize, 0xFF879BF8)	// note "GetCatFs_ClusterSize"
NHSTUB(GetDrive_TotalClusters, 0xFF879C34)	// note "GetCatFs_TotalClusters"
NHSTUB(GetDrive_FreeClusters, 0xFF879C70)	// note "GetCatFs_FreeClusters"

NSTUB(Fwrite_Fut, 0xFF873550)
NSTUB(Fseek_Fut, 0xFF8735F0)
 

NHSTUB(MFOn, 0xFF996198)
NHSTUB(MFOff, 0xFF9961C8)

NHSTUB(SetAutoShutdownTime, 0xFF9ADF84)
NHSTUB(CreateTaskStrict, 0xFF823780)

NHSTUB(ExpCtrlTool_StopContiAE,  0xFF926F10) 
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF926EE0) 
NHSTUB(MakeAFScan,  0xFF999CF8) 
NHSTUB(GetBatteryTemperature, 0xFF82E4F0)
NHSTUB(GetCCDTemperature, 0xFF82E4DC)
NHSTUB(GetOpticalTemperature, 0xFF82E4C8)
NHSTUB(PT_PlaySound, 0xFF9A4EE8)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
