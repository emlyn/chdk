#include "stubs_asm.h"
NHSTUB(GetBatteryTemperature, 0xFFA48900)  //ok dk
NHSTUB(GetCCDTemperature, 0xFFA488EC) //ok ok
NHSTUB(GetOpticalTemperature, 0xFFA488D8) //ok but returns -10deg all the time dk

NHSTUB(GetDrive_ClusterSize, 0xFF8707EC) //OK dk
NHSTUB(GetDrive_TotalClusters, 0xFF87082C) //OK dk
NHSTUB(GetDrive_FreeClusters, 0xFF87086C) //OK dk

NHSTUB(iosInit, 0xFFAC3B3C) //should be ok dk
NHSTUB(iosDevFind, 0xFFAC3A38) //should be ok dk
NSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFA600D8) //should be ok dk
NHSTUB(SetZoomActuatorSpeedPercent, 0xFF811A38) //just a "RET" from any random address. should work dk
NHSTUB(MoveFocusLensToDistance, 0xFFA6B0E8) //should be ok dk
NHSTUB(GetZoomLensCurrentPoint, 0xFFA57CCC) //should be ok dk
NHSTUB(GetZoomLensCurrentPosition, 0xFFA57CE0) //should be ok dk
NHSTUB(SetAutoShutdownTime, 0xFF95608C) //should be ok dk

NHSTUB(GetFocusLensSubjectDistance, 0xFFA5FA64) //ok, getting values that make sense :) dk
NHSTUB(GetCurrentAvValue, 0xFFA6AEB0) //getting values, should be ok dk


NHSTUB(Open,  0xFF87167C) //OK dk
NHSTUB(Read,  0xFF8716E8) //OK dk
NHSTUB(Write, 0xFF8716F4) //OK dk
NHSTUB(Close, 0xFF871688) //OK dk
NHSTUB(Remove, 0xFF871694) //SHOULD BE OK dk

NHSTUB(Mount_FileSystem, 0xFF8702E4) //ok dk
NHSTUB(VbattGet, 0xFFA5BCC4) //should be ok dk

/**********************************************************/
//as sd300 doesnt seem to have uniqueled stuff we do it our own way
//see ixus40_sd300(lib.c for details
//we need the af set/get methods:
NHSTUB(SetAFBeamBrightness, 0xFFA62C34) // dk
NHSTUB(SetAFBeamOff, 0xFFA62CB0); // dk
//and uniqueled is set to NULL dummy
NHSTUB(UniqueLedOn, 0xFFAAAEA8) // dk
NHSTUB(UniqueLedOff, 0xFFAAAEA8) // dk
/**********************************************************/

//looks like there is no strobechargecompletet flag ?!
//do it in my own way. found some code to get the eventflag
//at 0xFF941A14. copied the call there in my own c-code
//looking at sd400 asm showed that flash info is (val>>20)&1
//seems correct here as well... see ixus40.../lib.c
NHSTUB(IsStrobeChargeCompleted, IsStrobeChargeCompleted_my)
NHSTUB(sub_FF821D04, 0xFF821D04) // dk

//test to use this for kbd action
NHSTUB(semBCreate, 0xFFACF158) //dk
NHSTUB(GiveSemaphore, 0xFF823144) // dk
         
//should be ok but sd300 doesnt have all cases :(
//NHSTUB(GetPropertyCase, 0xFF82CB54)
NHSTUB(GetPropertyCase, GetPropertyCase_my)
NHSTUB(GetPropertyCase_orig, 0xFF82CB54) // dk
NHSTUB(SetPropertyCase, SetPropertyCase_my)
NHSTUB(SetPropertyCase_orig, 0xFF82CAD0) // dk


//adresses are ok but sd300 pdata differs, | 0x4000 lets it return 0 all the time,
//without it you get crashes at some data addr :(
//NHSTUB(GetParameterData, 0xFF95A55C) //should be ok!
NHSTUB(GetParameterData, GetParameterData_my) //hack to work around file number issue
NHSTUB(GetParameterData_orig, 0xFF95A55C) //should be ok! dk
NHSTUB(SetParameterData, 0xFF95A49C) // dk

//custom stuff
NHSTUB(ShowCameraLog, 0xFF81A1A8) //ok dk
NHSTUB(ShowAllTaskInfo, 0xFFA9E8BC) // dk
NHSTUB(SetTimerWhen, 0xFF815828) //ok dk 

//ovveride autodetect for LockMainPower
NHSTUB(LockMainPower, 0xff95619C) //OK! dk
NHSTUB(UnlockMainPower, 0xff956258) //OK! dk
//NHSTUB(LockMainPower, dummy_nop)
//NHSTUB(UnlockMainPower, dummy_nop)
//Manually entered
NHSTUB(AllocateMemory, 0xFF81F56C) // dk
NHSTUB(FreeMemory, 0xFF81F578) // dk
NHSTUB(ExecuteEventProcedure, 0xFF81756C) //checked dk

NHSTUB(CreatePhysicalVram, 0xFF927B0C) // dk
NHSTUB(DisplayImagePhysicalScreen, 0xFF927098) // dk
NHSTUB(FreeUncacheableMemory, 0xFF8152BC) // dk

NHSTUB(GetCurrentMachineTime, 0xFF81FEFC) // dk
NHSTUB(free, 0xFFAC58D8) // dk

//Keyboard stuff - Check it, not very similar to SD500
NHSTUB(kbd_p1_f_cont, 0xFF830AB4) // dk
NHSTUB(PhySw_testgpio, 0xFF82FA8C) // dk



//null stub

NHSTUB(kbd_p1_f, 0xFFAAAEA8) // dk
NHSTUB(kbd_p2_f, 0xFFAAAEA8) // dk
NHSTUB(kbd_read_keys_r2, 0xFFAAAEA8) // dk

//from sd400

//sd300 doesnt seem to have this feature !
NHSTUB(UnsetZoomForMovie, 0xFFAAAEA8) //00xFF9A4D1C) // dk

NHSTUB(PT_PlaySound, 0xff94f2bc) // dk - wrong in 100k version!
// see jump table beginnning ff94ed08

// see also jump table beginning ff94e780 fcor other PT entrypoints


NHSTUB(EnterToCompensationEVF, 0xff93e1e0)  // dk
NHSTUB(ExitFromCompensationEVF, 0xff93e220) // dk
NHSTUB(DoAFLock, 0xff93e07c)
NHSTUB(UnlockAF, 0xff93e0dc)

NHSTUB(SetScriptMode,0xFF955C24) // "EvntTbl_SetScriptMode"
NHSTUB(SetCurrentCaptureModeType,0xFFAAAEA8) // NOT FOUND, NULLSUB
NHSTUB(SetLogicalEventActive,0xFFAAAEA8) // NOT FOUND, NULLSUB
