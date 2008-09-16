#include "stubs_asm.h"

NHSTUB(free, 0xFFB0B858)    // B memPartFree (xref back)

//NSTUB(realloc, 0xFFB1475C)
//NSTUB(memmove, 0xFFB0D584)
//NSTUB(calloc,  0xFFB1472C)
NSTUB(printf,  0xFFB07970)  // its in the names window


// NHSTUB(kbd_pwr_off, 0xFF827FF8)
NHSTUB(kbd_pwr_on, 0xFF827EE0)  // same as 100d


// Function reads Gpio Status into physw_status variable
// call located at start of the 'kbd_p1_f' => 'PhySWTask'
NHSTUB(kbd_read_keys, 0xFF826D30)   // same as 100d


NHSTUB(VbattGet, 0xFF82C1A0)    // same as 100d
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8117EC) // same as 100d

NHSTUB(ZZZ, 0x0)


//NSTUB(taskName, 0xFFB22A50)
//NSTUB(taskIdListGet, 0xFFB22B58)
//NSTUB(taskResume, 0xFFB22E34)
//NSTUB(taskSuspend, 0xFFB22C60)
NSTUB(taskNameToId, 0xFFB18DB0)     // in names window

// These two are indistinguishable!!!!
// ????
//NSTUB(feof, 0xffb09d18)
//NSTUB(ferror, 0xffb09d84)


//STUB_DIR(vsprintf,0xFFB11278)

//NHSTUB(UnsetZoomForMovie ,0xFF9B1680)

NHSTUB(GetDrive_ClusterSize, 0xFF86EE78)    // same as 100d
NHSTUB(GetDrive_TotalClusters, 0xFF86EEB4)  //   "  "
NHSTUB(GetDrive_FreeClusters, 0xFF867C04)   //   "  "
NHSTUB(GetBatteryTemperature, 0xFF82D270)
NHSTUB(GetCCDTemperature, 0xFF82D25C)
NHSTUB(GetOpticalTemperature, 0xFF82D248)
NHSTUB(PT_PlaySound, 0xFF969874)


//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
