#include "stubs_asm.h"

NHSTUB(Close, 0xFF877374)
NHSTUB(Remove, 0xFF877380)
NHSTUB(DisplayImagePhysicalScreen, 0xFF93DCB0)
NHSTUB(free, 0xFFAF750C)
NHSTUB(Open, 0xFF877368)
NHSTUB(Read, 0xFF8773D4)
NHSTUB(Write, 0xFF8773E0)
NHSTUB(VbattGet, 0xFF82D570)
NHSTUB(Mount_FileSystem, 0xFF876264)
NHSTUB(SetParameterData, 0xFF987F0C)
NHSTUB(GetPropertyCase, 0xFF825D08)
NHSTUB(SetPropertyCase, 0xFF825C00)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAA87B8)
NHSTUB(GetZoomLensCurrentPoint, 0xFFAA87A4)
NHSTUB(MoveZoomLensWithPoint, 0xFFA87F80)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFA880F8)

NHSTUB(kbd_p1_f, 0xFF829470)
NHSTUB(kbd_p1_f_cont, 0xFF829484)
NHSTUB(kbd_read_keys_r2, 0xFF829E58)
NHSTUB(platformsub_kbd_fetch_data, 0xFF829F8C)
NHSTUB(kbd_p2_f, 0xFF829364)

// null stubs
NHSTUB(PhySw_testgpio, 0xFF8118C0)

NHSTUB(UniqueLedOn, 0xFF82EBDC)
NHSTUB(UniqueLedOff, 0xFF82EC54)
