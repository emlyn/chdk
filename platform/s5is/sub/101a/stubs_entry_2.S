    #include "stubs_asm.h"

NHSTUB(SleepTask                              ,0xFF82AC20)
NHSTUB(CreateTask                             ,0xFF81B9C4)
NHSTUB(ExitTask                               ,0xFF81BC54)
NHSTUB(AllocateMemory                         ,0xFFA41170)

// Look over all these again, some point to a B sub_.... so that's unnecessary.
NHSTUB(ExecuteEventProcedure                  ,0xFF81BF64)
NHSTUB(FreeMemory                             ,0xFFA4115C)
NHSTUB(GetCurrentTargetDistance               ,0xFF95126C)
NHSTUB(GetSystemTime                          ,0xFFA4126C)
NHSTUB(ints_disable                           ,0xFF81058C) // Actually identified as IRQdisable by signatures
NHSTUB(ints_enable                            ,0xFF8105B4) // Actually identified as IRQenable by signatures
NHSTUB(memcmp                                 ,0xFF81E72C)
NHSTUB(memcpy                                 ,0xFF8B32C8)
NHSTUB(memset                                 ,0xFFA64C5C)
NHSTUB(Close                                  ,0xFF825D8C)
NHSTUB(Open                                   ,0xFF825D64)
NHSTUB(Read                                   ,0xFF825E34)
NHSTUB(Write                                  ,0xFF825E38)
NHSTUB(Lseek                                  ,0xFF825F94)
NHSTUB(strcmp                                 ,0xFF81E6C4)
NHSTUB(strcpy                                 ,0xFF81E670)
NHSTUB(strlen                                 ,0xFF81E708)
NHSTUB(TakeSemaphore                          ,0xFF81B860)
NHSTUB(vsprintf                               ,0xFF81E5F0)    // first sub called in FADBGPrintf
NHSTUB(GetFocusLensSubjectDistance            ,0xFF95250C)    // returns 0. What's wrong?
NHSTUB(GetZoomLensCurrentPoint                ,0xFF957D84)
NHSTUB(GetZoomLensCurrentPosition             ,0xFF957D88)
NHSTUB(RefreshPhysicalScreen                  ,0xFF8B2E58)
NHSTUB(GetPropertyCase                        ,0xFF874864)    // PT_GetPropertyCaseString
NHSTUB(SetPropertyCase                        ,0xFF874774)    // PT_SetPropertyCaseString
NHSTUB(VbattGet                               ,0xFF8222CC)    
NHSTUB(GetParameterData                       ,0xFF973028) // Guess but it seems correct. IDA incorrectly identified sub_FF972524 as GetParameterData
NHSTUB(SetParameterData                       ,0xFF972F9C) // Idem, with different address though :)
NHSTUB(IsStrobeChargeCompleted                ,0xFF8DB5FC)


// these (open, write, close) are educated guesses but not 100% certain
NHSTUB(open                                   ,0xFF81A030)
NHSTUB(write                                  ,0xFF81A328)
NHSTUB(close                                  ,0xFF81A0E0)
NHSTUB(lseek                                  ,0xFF825ECC) // Lseek_0
NHSTUB(read                                   ,0xFF81A2C8) // Read

NHSTUB(Fopen_Fut                              ,0xFF825730)
NHSTUB(Fwrite_Fut                             ,0xFF825870)
NHSTUB(Fclose_Fut                             ,0xFF825770)
NHSTUB(Fread_Fut                              ,0xFF82581C)
NHSTUB(Fseek_Fut                              ,0xFF825910)

NHSTUB(Remove                                 ,0xFF825DD4)
NHSTUB(rename                                 ,0xFF825E60)

NHSTUB(stat                                   ,0xFF825F98)
NHSTUB(openfastdir                            ,0xFFA27934)
NHSTUB(readfastdir                            ,0xFFA279C8)
NHSTUB(closefastdir                           ,0xFFA27A98)

NHSTUB(opendir                                ,0xFFA27934) // OpenFastDir
NHSTUB(ReadFastDir                            ,0xFFA279C8)
NHSTUB(closedir                               ,0xFFA27A98) // CloseFastDir
NHSTUB(mkdir                                  ,0xFF826130)

NHSTUB(GetDrive_ClusterSize                   ,0xFF856DD0)
NHSTUB(GetDrive_TotalClusters                 ,0xFF856E04)
NHSTUB(GetDrive_FreeClusters                  ,0xFF856E70)

NHSTUB(LockMainPower                          ,0xFF877DF8)
NHSTUB(UnlockMainPower                        ,0xFF877D54)

NHSTUB(GetCurrentAvValue                      ,0xFF952E5C)
NHSTUB(MoveFocusLensToDistance                ,0xFFA0D4E4)
NHSTUB(MoveZoomLensWithPoint                  ,0xFF957BFC)
NHSTUB(SetZoomActuatorSpeedPercent            ,0xFF957D38)

NHSTUB(malloc                                 ,0xFF813A2C)
NHSTUB(free                                   ,0xFF813B00)
NHSTUB(FreeUncacheableMemory                  ,0xFF82ADD0)
NHSTUB(AllocateUncacheableMemory              ,0xFF82AD9C)

NHSTUB(rand                                   ,0xFF81E834)
NHSTUB(srand                                  ,0xFF81BDB4)
NHSTUB(_log10                                 ,0xFFA92F04)
NHSTUB(_pow                                   ,0xFFA93074)
NHSTUB(_log                                   ,0xFFA93FC0)
NHSTUB(_sqrt                                  ,0xFFA95328)

NHSTUB(qsort                                  ,0xFF9CA2EC)

//NHSTUB(strstr                                 ,0xFF9C9E0C)
NHSTUB(strncpy                                ,0xFF81E688)
NHSTUB(strrchr                                ,0xFF8B32A0)
NHSTUB(strncmp                                ,0xFF8B3230)
NHSTUB(strchr                                 ,0xFF8B327C)
NHSTUB(strcat                                 ,0xFF8B31F4)
NHSTUB(strtol                                 ,0xFF831DAC)

NHSTUB(LocalTime                              ,0xFF8706CC)

NHSTUB(UpdateMBROnFlash                       ,0xFF856B98)

NHSTUB(UniqueLedOn                            ,0xFF913BBC)
NHSTUB(UniqueLedOff                           ,0xFF913C44)

NHSTUB(SetAutoShutdownTime                    ,0xFF877F58)


NHSTUB(phySw                                  ,0xFF823668)
NHSTUB(phySw_p1                               ,0xFF823A6C) // called from phySw
NHSTUB(phySw_p2                               ,0xFF82330C) // called when phySw_p1 returns 1
NHSTUB(NewTaskShell                           ,0xFF874330) // starts new shell on Console. GUI output?

NHSTUB(kbd_read_keys                          ,0xFF823990) // Called in kbd.c (originally called from phySw_p1, line 3)
NHSTUB(kbd_p1_f                               ,0xFF823A6C) // is phySw_p1
NHSTUB(kbd_p1_f_cont                          ,0xFF823A78) // after call to kbd_read_keys
NHSTUB(kbd_p2_f                               ,0xFF82330C) // is phySw_p2
NHSTUB(kbd_read_keys_r2                       ,0xFF84D4AC) // called from kbd_read_keys



// Possibly useful but not yet necessary
NHSTUB(GetCCDTemperature                      ,0xFF8505BC) // Unknown units, doesn't really seem to respond
NHSTUB(GetBatteryTemperature                  ,0xFF85062C) // Unknown units, doesn't really seem to respond to frozen batteries
NHSTUB(GetOpticalTemperature                  ,0xFF85069C) // Unknown units, doesn't really seem to respond
NHSTUB(OpenMShutter                           ,0xFFA0BED0)
NHSTUB(CloseMShutter                          ,0xFFA0BE98)
NHSTUB(PutOutNdFilter                         ,0xFFA0BE00) // Doesn't really work on S5, sometimes crashes camera
NHSTUB(PutInNdFilter                          ,0xFFA0BDC8) // Doesn't really work on S5, sometimes crashes camera
NHSTUB(SSAPI_ExtStrobeCharged                 ,0xFF8288B4) // Functionality unknown. Implied effect implemented in IsStrobeChargeCompleted



///////////
// FOLLOWING FUNCTION NOT FOUND, points to nullsub. Function does not exist
// where it is to be expected according to A720 firmware. Copied it from A720
// and hooked in boot.c
//NHSTUB(time, 0xFF81096C)


///////////
// The following functions were not found in the S5 firmware. They do not
// seem to be required but for some reason someone made this list.
// Point to nullsub for immediate return
// nullsub_1: 0xFF81096C (S5)
NSTUB(CreatePhysicalVram,		 0xFF81096C)
NSTUB(CreateTaskStrict,			 0xFF81096C)
NSTUB(DisableDispatch,			 0xFF81096C)
NSTUB(DisplayImagePhysicalScreen,	 0xFF81096C)
NSTUB(EnableDispatch,			 0xFF81096C)
NSTUB(ioctl,					 0xFF81096C)
NSTUB(iosDevAdd,				 0xFF81096C)
NSTUB(iosDrvInstall,			 0xFF81096C)
NSTUB(isalpha,					 0xFF81096C)
NSTUB(isdigit,					 0xFF81096C)
NSTUB(islower,					 0xFF81096C)
NSTUB(isspace,					 0xFF81096C)
NSTUB(isupper,					 0xFF81096C)
NSTUB(localtime,				 0xFF81096C)
NSTUB(MakeDirectory,			 0xFF81096C)
NSTUB(memPartAlloc,				 0xFF81096C)
NSTUB(memPartFindMax,			 0xFF81096C)
NSTUB(Mount_FileSystem,			 0xFF81096C)
NSTUB(PhySw_testgpio,			 0xFF81096C)
NSTUB(ProtectFile,				 0xFF81096C)
NSTUB(readdir,					 0xFF81096C)
NSTUB(rewinddir,				 0xFF81096C)
NSTUB(taskCreateHookAdd,			 0xFF81096C)
NSTUB(taskDeleteHookAdd,			 0xFF81096C)
NSTUB(taskIdListGet,			 0xFF81096C)
NSTUB(taskLock,				 0xFF81096C)
NSTUB(taskName,				 0xFF81096C)
NSTUB(taskResume,				 0xFF81096C)
NSTUB(taskSuspend,				 0xFF81096C)
NSTUB(taskUnlock,				 0xFF81096C)
NSTUB(utime,					 0xFF81096C)
NSTUB(Unmount_FileSystem,		 0xFF81096C)
NSTUB(UIFS_WriteFirmInfoToFile,	 0xFF81096C)
NSTUB(kbd_pwr_off,				 0xFF81096C) // Does not even exist, I think
NSTUB(kbd_pwr_on,				 0xFF81096C) // Does not even exist, I think
NHSTUB(PT_PlaySound, 0xFF86B5A4)
NHSTUB(EnterToCompensationEVF, 0xff828070) 
NHSTUB(ExitFromCompensationEVF, 0xff828164) 
