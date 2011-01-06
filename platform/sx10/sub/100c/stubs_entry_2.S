#include "stubs_asm.h"

//NHSTUB(AllocateUncacheableMemory, 0xFF827FCC)
NHSTUB(GetDrive_ClusterSize, 0xFF85AE90) //done
NHSTUB(GetDrive_TotalClusters, 0xFF85AEC4) //done
NHSTUB(GetDrive_FreeClusters, 0xFF85AEF8) //done
//NHSTUB(SetPropertyCase, 0xFF8795C8) //done
//NHSTUB(kbd_read_keys, 0xFF821B14)
NHSTUB(platformsub_kbd_fetch_data, 0xFF84B660)
NHSTUB(kbd_read_keys_r2, 0xFF84AF6C)
NHSTUB(qsort, 0xFFAB814C) //done
NHSTUB(strchr, 0xFF89B91C) //done
NHSTUB(strrchr, 0xFF9DF430) //done


NHSTUB(TurnOffBackLight, 0xFF88F284) //done
//NHSTUB(vsprintf, 0xFF81CAE8)
NHSTUB(VbattGet, 0xFF82046C)
NHSTUB(GetZoomLensCurrentPoint, 0xFF941128) //done
NHSTUB(GetZoomLensCurrentPosition, 0xFFA5B23C) //done -0x10 offset rather than the -0x8 that usually happens
NHSTUB(RefreshPhysicalScreen, 0xFF9DF030) //done
NHSTUB(EnterToCompensationEVF, 0xFF825B10)
NHSTUB(ExitFromCompensationEVF, 0xFF825B54)
NHSTUB(DoAFLock, 0xFF825864)
NHSTUB(UnlockAF, 0xFF82589C)
NHSTUB(LEDDrive, 0xFF84AB48)
NHSTUB(WriteSDCard, 0xFF92A99C) //done
NHSTUB(PostLogicalEventForNotPowerType, 0xFF87EC94) //done
NHSTUB(apex2us, 0xFF9E0118) //done -0x10 diff rather that -0x8
NHSTUB(SetScriptMode, 0xFF880C78) // "SetScriptMode"
NHSTUB(Restart, 0xFF829848)
NHSTUB(PB2Rec, 0xFF883FD0)
NHSTUB(Rec2PB, 0xFF882958)

// null sub - point these at nullsub_1 as labelled in IDA

NHSTUB(kbd_pwr_off, 0xFF81093C)
NHSTUB(kbd_pwr_on, 0xFF81093C)
NHSTUB(Mount_FileSystem, 0xFF81093C)
NHSTUB(Unmount_FileSystem, 0xFF81093C)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF81093C)
NHSTUB(rewinddir, 0xFF81093C)

