#include "stubs_asm.h"

NHSTUB(Open, 0xFF874B90) // OK!
NHSTUB(Close, 0xFF874B9C) // OK!
NHSTUB(Read, 0xFF874BFC) // OK!
NHSTUB(Write, 0xFF874C08) // OK!
NHSTUB(Remove, 0xFF874BA8) // OK!
NHSTUB(free, 0xFFABEC40) // OK!
NHSTUB(Mount_FileSystem, 0xFF873F40) // OK!
NHSTUB(SetPropertyCase, 0xFF8259A0) // OK!
NHSTUB(GetPropertyCase, 0xFF825AA8) // OK!
NHSTUB(VbattGet, 0xFFA62D84) // OK!
NHSTUB(GetZoomLensCurrentPoint, 0xFFA593D4) // OK!
NHSTUB(GetCurrentAvValue, 0xFFA516E0) // OK!
NHSTUB(GetZoomLensCurrentPosition, 0xFFA593E8) // OK!
NHSTUB(GetFocusLensSubjectDistance, 0xFFA66F80) // OK!
NHSTUB(MoveFocusLensToDistance, 0xFFA72C94) // OK!
NHSTUB(UniqueLedOn, 0xFF82DFC8) // OK!
NHSTUB(UniqueLedOff, 0xFF82E024) // OK!


NHSTUB(platformsub_kbd_fetch_data, 0xFF8297A8) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0) OK!
NHSTUB(kbd_p1_f_cont, 0xFF828DE0) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0) OK!
NHSTUB(kbd_p1_1, 0xFF8291F0) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0) OK!
NHSTUB(kbd_p1_2, 0xFF829258) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0) OK!
NHSTUB(kbd_p1_3, 0xFF82963C) // populated from values in wrap_kbd_p1_f (aDerror0x02x0x0) OK!
NSTUB(DisplayImagePhysicalScreen, 0xFF93C9EC) // OK!


//null stubs - OK!
NHSTUB(PhySw_testgpio, 0xFF8118C0)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8118C0)
NHSTUB(kbd_p1_f, 0xFF8118C0)
NHSTUB(kbd_p2_f, 0xFF8118C0)
NHSTUB(kbd_read_keys_r2, 0xFF8118C0)

NHSTUB(UnsetZoomForMovie, 0xFF9A4D1C) // OK!

NHSTUB(GetDrive_ClusterSize, 0xFF8743BC) // OK!
NHSTUB(GetDrive_TotalClusters, 0xFF8743F8) // OK!
NHSTUB(GetDrive_FreeClusters, 0xFF874434) // OK!
NHSTUB(GetBatteryTemperature, 0xFF82D754)
NHSTUB(GetCCDTemperature, 0xFF82D740)
NHSTUB(GetOpticalTemperature, 0xFF82D72C)
NHSTUB(PT_PlaySound, 0xFF96AB58)

NHSTUB(EnterToCompensationEVF, 0xff9590c8)
NHSTUB(ExitFromCompensationEVF, 0xff95911c)
