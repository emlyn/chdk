#include "stubs_asm.h"

NHSTUB(Open, 0xFF86A938)
NHSTUB(Close, 0xFF86A944)
NHSTUB(Read, 0xFF86A9A4)
NHSTUB(Write, 0xFF86A9B0)
NHSTUB(Remove, 0xFF86A950)
NHSTUB(free, 0xFFABCC28)
NHSTUB(Mount_FileSystem, 0xFF869CD4)
NHSTUB(SetPropertyCase, 0xFF825B9C)
NHSTUB(GetPropertyCase, 0xFF825CA4)
NHSTUB(VbattGet, 0xFFA60A4C)
NHSTUB(GetZoomLensCurrentPoint, 0xFFA56F6C)
NHSTUB(GetCurrentAvValue, 0xFFA4F304)
NHSTUB(GetZoomLensCurrentPosition, 0xFFA56F80)
NHSTUB(GetFocusLensSubjectDistance, 0xFFA64C48)
NHSTUB(MoveFocusLensToDistance, 0xFFA71588)
NHSTUB(UniqueLedOn, 0xFFA6882C)
NHSTUB(UniqueLedOff, 0xFFA68888)


NHSTUB(platformsub_kbd_fetch_data, 0xFF8299B4)
NHSTUB(kbd_p1_f_cont, 0xFF828FEC)
NHSTUB(kbd_p1_1, 0xFF8293FC)
NHSTUB(kbd_p1_2, 0xFF829464)
NHSTUB(kbd_p1_3, 0xFF829848)


//null stubs
NHSTUB(PhySw_testgpio, 0xFF8118C0)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF8118C0)
NHSTUB(kbd_p1_f, 0xFF8118C0)
NHSTUB(kbd_p2_f, 0xFF8118C0)
NHSTUB(kbd_read_keys_r2, 0xFF8118C0)

NHSTUB(UnsetZoomForMovie, 0xFF999F50) 

NHSTUB(GetDrive_ClusterSize, 0xFF86A150)
NHSTUB(GetDrive_TotalClusters, 0xFF86A18C)
NHSTUB(GetDrive_FreeClusters, 0xFF86A1C8)
NHSTUB(WriteSDCard, 0xFF87CACC)
NHSTUB(GetBatteryTemperature, 0xFFA4DA28)
NHSTUB(GetCCDTemperature, 0xFFA4DA14)
NHSTUB(GetOpticalTemperature, 0xFFA4DA00)
NHSTUB(PT_PlaySound, 0xFF960080)

//NHSTUB(EnterToCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
//NHSTUB(ExitFromCompensationEVF, 0xFFFFFFFF) // Stub not found. When found, remove dummy function from lib.c.
NHSTUB(MakeAFScan, 0xFF94EF7C)  //DoAFLock
NHSTUB(ExpCtrlTool_StartContiAE, 0xFF8F94B8)  
