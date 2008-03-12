#include "stubs_asm.h"

NHSTUB(Close,  0xFFE221A0)	//sync with a560
NHSTUB(Read,   0xFFE22234)	//sync with a560	 
NHSTUB(Write,  0xFFE22240)	//sync with a560 
NHSTUB(Remove, 0xFFE221C0)	//sync with a560
NHSTUB(Mount_FileSystem, 0xFFE214C4)	//sync with a560
NHSTUB(kbd_read_keys_r2, 0xFFDCB384)	//sync with a560
NHSTUB(DisplayImagePhysicalScreen, 0xFFDC0374)	//sync with a560, but some differnce
NHSTUB(free, 0xFFCC8154)	//sync with a560
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFDCD668) //nullsub_130

//overwrite incorrect in stubs_entry.s
NHSTUB(SetPropertyCase, 0xFFC0B68C)	//sync with a560
NHSTUB(FreeMemory, 0xFFC0819C)	//sync with a560
NHSTUB(GetFocusLensSubjectDistance, 0xFFE43B08)	//sync with ixus sd1000
NHSTUB(GetDrive_ClusterSize, 0xFFE2198C)	//sync with a560
NHSTUB(GetDrive_TotalClusters, 0xFFE219C8)	//sync with a560
NHSTUB(WriteSDCard, 0xFFE34524)	//after the only call to CMD12_StopTransmission
NHSTUB(GetDrive_FreeClusters, 0xFFE21A04)

//NSTUB(TakeSemaphore, 0xFFE835C4)	//sync with old a560 on ZShare and a540
//NSTUB(kbd_pwr_off, 0xFFDC90E4)	//sync with stubs_entry.s of a560
//NSTUB(kbd_p1_f_cont, 0xffdc9d24) //punta a met… funzione, ma sembra corretto...


