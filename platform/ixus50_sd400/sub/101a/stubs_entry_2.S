#include "stubs_asm.h"

NHSTUB(Open, 0xFF874B90)
NHSTUB(Close, 0xFF874B9C)
NHSTUB(Read, 0xFF874BFC)
NHSTUB(Write, 0xFF874C08)
NHSTUB(Remove, 0xFF874BA8)
NHSTUB(free, 0xFFABEBEC)
NHSTUB(Mount_FileSystem, 0xFF873F40)
NHSTUB(SetPropertyCase, 0xFF8259A0)
NHSTUB(GetPropertyCase, 0xFF825AA8)
NHSTUB(VbattGet, 0xFFA62D30)
NHSTUB(GetZoomLensCurrentPoint, 0xFFA59380)
NHSTUB(GetCurrentAvValue, 0xFFA5168C)
NHSTUB(GetZoomLensCurrentPosition, 0xFFA59394)
NHSTUB(GetFocusLensSubjectDistance, 0xFFA66F2C)
NHSTUB(MoveFocusLensToDistance, 0xFFA72C40)
NHSTUB(UniqueLedOn, 0xFF82DFC8)
NHSTUB(UniqueLedOff, 0xFF82E024)


NHSTUB(platformsub_kbd_fetch_data, 0xFF8297A8) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0)
NHSTUB(kbd_p1_f_cont, 0xFF828DE0)
NHSTUB(kbd_p1_1, 0xFF8291F0) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0)
NHSTUB(kbd_p1_2, 0xFF829258) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0)
NHSTUB(kbd_p1_3, 0xFF82963C) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0)
NSTUB(DisplayImagePhysicalScreen, 0xFF93C9EC)


//null stubs
NHSTUB(PhySw_testgpio, 0xFF8118C0)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8118C0)
NHSTUB(kbd_p1_f, 0xFF8118C0)
NHSTUB(kbd_p2_f, 0xFF8118C0)
NHSTUB(kbd_read_keys_r2, 0xFF8118C0)

NHSTUB(UnsetZoomForMovie, 0xFF9A4DB0) 

NHSTUB(GetDrive_ClusterSize, 0xFF8743BC)
NHSTUB(GetDrive_TotalClusters, 0xFF8743F8)
NHSTUB(GetDrive_FreeClusters, 0xFF874434)
NHSTUB(GetBatteryTemperature, 0xFF82D754)
NHSTUB(GetCCDTemperature, 0xFF82D740)
NHSTUB(GetOpticalTemperature, 0xFF82D72C)
NHSTUB(PT_PlaySound, 0xFF96AB04)

NHSTUB(EnterToCompensationEVF, 0xff959074)
NHSTUB(ExitFromCompensationEVF, 0xff9590c8) 
