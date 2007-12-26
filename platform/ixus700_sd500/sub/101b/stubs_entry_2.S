#include "stubs_asm.h"

NHSTUB(Open, 0xFF86A938)
NHSTUB(Close, 0xFF86A944)
NHSTUB(Read, 0xFF86A9A4)
NHSTUB(Write, 0xFF86A9B0)
NHSTUB(Remove, 0xFF86A950)
NHSTUB(free, 0xFFABCC78)
NHSTUB(Mount_FileSystem, 0xFF869CD4)
NHSTUB(SetPropertyCase, 0xFF825B9C)
NHSTUB(GetPropertyCase, 0xFF825CA4)
NHSTUB(VbattGet, 0xFFA60A9C)
NHSTUB(GetZoomLensCurrentPoint, 0xFFA56FBC)
NHSTUB(GetCurrentAvValue, 0xFFA6F28C)
NHSTUB(GetZoomLensCurrentPosition, 0xFFA56FD0)
NHSTUB(GetFocusLensSubjectDistance, 0xFFA64C98)
NHSTUB(MoveFocusLensToDistance, 0xFFA715D8)
NHSTUB(UniqueLedOn, 0xFFA6887C)
NHSTUB(UniqueLedOff, 0xFFA688D8)


NHSTUB(platformsub_kbd_fetch_data, 0xFF8299B4)
NHSTUB(kbd_p1_f_cont, 0xFF828FEC)
NHSTUB(kbd_p1_1, 0xFF8293FC)
NHSTUB(kbd_p1_2, 0xFF829464)
NHSTUB(kbd_p1_3, 0xFF829848)


//null stub
NHSTUB(PhySw_testgpio, 0xFF8118C0)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8118C0)
NHSTUB(kbd_p1_f, 0xFF8118C0)
NHSTUB(kbd_p2_f, 0xFF8118C0)
NHSTUB(kbd_read_keys_r2, 0xFF8118C0)

NHSTUB(GetDrive_ClusterSize, 0xFF86A150)
NHSTUB(GetDrive_TotalClusters, 0xFF86A18C)
NHSTUB(GetDrive_FreeClusters, 0xFF86A1C8)




