#include "stubs_asm.h"

NHSTUB(VbattGet, 0xFF82C328)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAE8474)
NHSTUB(GetZoomLensCurrentPoint, 0xFFAE8460)
NHSTUB(MoveZoomLensWithPoint, 0xFFAE8280)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFAE83F8)
//NHSTUB(GetFocusLensSubjectDistance, 0xFFEA2F3C)

NHSTUB(platformsub_kbd_fetch_data, 0xFF8281C4)
NHSTUB(kbd_read_keys_r2, 0xFF827BC0)

NHSTUB(free, 0xFFB571E4)
NHSTUB(malloc, 0xFFB571D8)

NHSTUB(UniqueLedOn, 0xFF82DC3C)
NHSTUB(UniqueLedOff, 0xFF82DCA0)

NHSTUB(GetDrive_ClusterSize, 0xFF870710)
NHSTUB(GetDrive_TotalClusters, 0xFF87076C)
NHSTUB(GetDrive_FreeClusters, 0xFF8707A8)
