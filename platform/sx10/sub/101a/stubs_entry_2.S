#include "stubs_asm.h"

//NHSTUB(AllocateUncacheableMemory, 0xFF827FCC)
NHSTUB(GetDrive_ClusterSize, 0xFF85AE98)
NHSTUB(GetDrive_TotalClusters, 0xFF85AECC)
NHSTUB(GetDrive_FreeClusters, 0xFF85AF00)
//NHSTUB(SetPropertyCase, 0xFF8795D0)
//NHSTUB(kbd_read_keys, 0xFF821B14)
NHSTUB(platformsub_kbd_fetch_data, 0xFF84B660)
NHSTUB(kbd_read_keys_r2, 0xFF84AF6C)
NHSTUB(qsort, 0xFFAB815C)
NHSTUB(strchr, 0xFF89B924)
NHSTUB(strrchr, 0xFF9DF438)


NHSTUB(TurnOffBackLight, 0xFF88F28C)
//NHSTUB(vsprintf, 0xFF81CAE8)
NHSTUB(VbattGet, 0xFF82046C)
NHSTUB(GetZoomLensCurrentPoint, 0xFF941130)
NHSTUB(GetZoomLensCurrentPosition, 0xFFA5B24C)
NHSTUB(RefreshPhysicalScreen, 0xFF9DF040)
NHSTUB(EnterToCompensationEVF, 0xFF825B10)
NHSTUB(ExitFromCompensationEVF, 0xFF825B54)
NHSTUB(DoAFLock, 0xFF825864)
NHSTUB(UnlockAF, 0xFF82589C)
NHSTUB(LEDDrive, 0xFF84AB48)
NHSTUB(WriteSDCard, 0xFF92A9A4)
NHSTUB(PostLogicalEventForNotPowerType, 0xFF87EC9C)
NHSTUB(apex2us, 0xFF9E0128)
NHSTUB(Restart, 0xFF829848)

// null sub - point these at nullsub_1 as labelled in IDA

NHSTUB(kbd_pwr_off, 0xFF81093C)
NHSTUB(kbd_pwr_on, 0xFF81093C)
NHSTUB(Mount_FileSystem, 0xFF81093C)
NHSTUB(Unmount_FileSystem, 0xFF81093C)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF81093C)
NHSTUB(rewinddir, 0xFF81093C)
NHSTUB(SetScriptMode, 0xFF880C80) // string

