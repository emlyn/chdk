#include "stubs_asm.h"

NHSTUB(free, 0xFFB9EA6C)
NHSTUB(platformsub_kbd_fetch_data, 0xFF8293AC)
NHSTUB(kbd_read_keys_r2, 0xFF828E70)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8117E8)  //null

NHSTUB(GiveSemaphore, 0xFF82218C)

NHSTUB(WriteSDCard, 0xFF88BE6C)
NHSTUB(GetDrive_ClusterSize, 0xff87c338)
NHSTUB(GetDrive_TotalClusters, 0xff87c374)
NHSTUB(GetDrive_FreeClusters, 0xff87c3b0)
