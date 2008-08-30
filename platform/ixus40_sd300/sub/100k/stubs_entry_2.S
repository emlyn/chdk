#include "stubs_asm.h"
NHSTUB(GetBatteryTemperature, 0xFFA48900)  //ok
NHSTUB(GetCCDTemperature, 0xFFA488EC) //ok
NHSTUB(GetOpticalTemperature, 0xFFA488D8) //ok but returns -10deg all the time

NHSTUB(GetDrive_ClusterSize, 0xFF8707EC) //OK
NHSTUB(GetDrive_TotalClusters, 0xFF87082C) //OK
NHSTUB(GetDrive_FreeClusters, 0xFF87086C) //OK

NHSTUB(iosInit, 0xFFAC3B64) //should be ok
NHSTUB(iosDevFind, 0xFFAC3A60) //should be ok
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFA600D8) //should be ok
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF811A38) //just a "RET" from any random address. should work
NHSTUB(MoveFocusLensToDistance, 0xFFA6B0EC) //should be ok
NHSTUB(GetZoomLensCurrentPoint, 0xFFA57CCC) //should be ok
NHSTUB(GetZoomLensCurrentPosition, 0xFFA57CE0) //should be ok
NHSTUB(SetAutoShutdownTime, 0xFF95608C) //should be ok

NHSTUB(GetFocusLensSubjectDistance, 0xFFA5FA64) //ok, getting values that make sense :)
NHSTUB(GetCurrentAvValue, 0xFFA6AEB4) //getting values, should be ok


NHSTUB(Open,  0xFF87167C) //OK
NHSTUB(Read,  0xFF8716E8) //OK
NHSTUB(Write, 0xFF8716F4) //OK
NHSTUB(Close, 0xFF871688) //OK
NHSTUB(Remove, 0xFF871694) //SHOULD BE OK

NHSTUB(Mount_FileSystem, 0xFF8702E4) //ok
NHSTUB(VbattGet, 0xFFA5BCC4) //should be ok

/**********************************************************/
//as sd300 doesnt seem to have uniqueled stuff we do it our own way
//see ixus40_sd300(lib.c for details
//we need the af set/get methods:
NHSTUB(SetAFBeamBrightness, 0xFFA62C34)
NHSTUB(SetAFBeamOff, 0xFFA62CB0);
//and uniqueled is set to NULL dummy
NHSTUB(UniqueLedOn, 0xFFAAAED0)
NHSTUB(UniqueLedOff, 0xFFAAAED0)
/**********************************************************/

//looks like there is no strobechargecompletet flag ?!
//do it in my own way. found some code to get the eventflag
//at 0xFF941A14. copied the call there in my own c-code
//looking at sd400 asm showed that flash info is (val>>20)&1
//seems correct here as well... see ixus40.../lib.c
NHSTUB(IsStrobeChargeCompleted, IsStrobeChargeCompleted_my)
NHSTUB(sub_FF821D04, 0xFF821D04)

//test to use this for kbd action
NHSTUB(semBCreate, 0xFFACF180)
NHSTUB(GiveSemaphore, 0xFF823144)
         
//should be ok but sd300 doesnt have all cases :(
//NHSTUB(GetPropertyCase, 0xFF82CB54)
NHSTUB(GetPropertyCase, GetPropertyCase_my)
NHSTUB(GetPropertyCase_orig, 0xFF82CB54)
NHSTUB(SetPropertyCase, SetPropertyCase_my)
NHSTUB(SetPropertyCase_orig, 0xFF82CAD0)


//adresses are ok but sd300 pdata differs, | 0x4000 lets it return 0 all the time,
//without it you get crashes at some data addr :(
//NHSTUB(GetParameterData, 0xFF95A55C) //should be ok!
NHSTUB(GetParameterData, GetParameterData_my) //hack to work around file number issue
NHSTUB(GetParameterData_orig, 0xFF95A55C) //should be ok!
NHSTUB(SetParameterData, 0xFF95A49C)

//custom stuff
NHSTUB(ShowCameraLog, 0xFF81A1A8) //ok
NHSTUB(ShowAllTaskInfo, 0xFFA9E8E4) 
NHSTUB(SetTimerWhen, 0xFF815828) //ok 

//ovveride autodetect for LockMainPower
NHSTUB(LockMainPower, 0xff95619C) //OK!
NHSTUB(UnlockMainPower, 0xff956258) //OK!
//NHSTUB(LockMainPower, dummy_nop)
//NHSTUB(UnlockMainPower, dummy_nop)
//Manually entered
NHSTUB(AllocateMemory, 0xFF81F56C)
NHSTUB(FreeMemory, 0xFF81F578)
NHSTUB(ExecuteEventProcedure, 0xFF81756C) //checked

NHSTUB(CreatePhysicalVram, 0xFF927B0C)
NHSTUB(DisplayImagePhysicalScreen, 0xFF927098)
NHSTUB(FreeUncacheableMemory, 0xFF8152BC)

NHSTUB(GetCurrentMachineTime, 0xFF81FEFC)
NHSTUB(free, 0xFFAC5900)

//Keyboard stuff - Check it, not very similar to SD500
NHSTUB(kbd_p1_f_cont, 0xFF830AB4)
NHSTUB(PhySw_testgpio, 0xFF82FA8C)



//null stub

NHSTUB(kbd_p1_f, 0xFFAAAED0)
NHSTUB(kbd_p2_f, 0xFFAAAED0)
NHSTUB(kbd_read_keys_r2, 0xFFAAAED0)

//from sd400

//sd300 doesnt seem to have this feature !
NHSTUB(UnsetZoomForMovie, 0xFFAAAED0) //00xFF9A4D1C) 

NHSTUB(PT_PlaySound, 0xFF94EB3C)


NHSTUB(EnterToCompensationEVF, 0xff93e1e0) 
NHSTUB(ExitFromCompensationEVF, 0xff93e220) 

