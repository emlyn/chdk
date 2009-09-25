
NSTUB(eventproc_export_memShow, 0xff810bf4)

NSTUB(eventproc_export_CreateTask, 0xff81afac)

NSTUB(eventproc_export_ExitTask, 0xff81b23c)

NSTUB(eventproc_export_RotateConsoleZOder, 0xff81b98c)

NSTUB(eventproc_export_CPrintf, 0xff81bb9c)
NSTUB(eventproc_export_CPutChar, 0xff81bbf8)
NSTUB(eventproc_export_GetCh, 0xff81bc24)
NSTUB(eventproc_export_GetStringWithPrompt, 0xff81bc74)
NSTUB(eventproc_export_OpenConsole, 0xff81bcd4)
NSTUB(eventproc_export_CloseConsole, 0xff81be40)

NSTUB(eventproc_export_StartRedirectUART, 0xff81c530)
NSTUB(eventproc_export_StopRedirectUART, 0xff81c648)

NSTUB(eventproc_export_sprintf, 0xff81cb5c)

NSTUB(eventproc_export_strcpy, 0xff81cbdc)
NSTUB(eventproc_export_strcmp, 0xff81cbf4)
NSTUB(eventproc_export_strlen, 0xff81cc38)
NSTUB(eventproc_export_memcmp, 0xff81cc5c)

NSTUB(eventproc_export_Fopen_Fut, 0xff8236d8)
NSTUB(eventproc_export_Fclose_Fut, 0xff823718)
NSTUB(eventproc_export_Fread_Fut, 0xff8237c4)
NSTUB(eventproc_export_Fwrite_Fut, 0xff823818)

NSTUB(eventproc_export_Fseek_Fut, 0xff8238b8)

NSTUB(eventproc_export_Open, 0xff823cc8)
NSTUB(eventproc_export_Close, 0xff823cf0)

NSTUB(eventproc_export_Read, 0xff823d98)
NSTUB(eventproc_export_Write, 0xff823d9c)

NSTUB(eventproc_export_Lseek, 0xff823ef8)

NSTUB(eventproc_export_StartCameraLog, 0xff8243c0)
NSTUB(eventproc_export_ShowCameraLog, 0xff8243c4)
NSTUB(eventproc_export_ShowCameraLogInfo, 0xff8243c8)
NSTUB(eventproc_export_StopCameraLog, 0xff8243cc)
NSTUB(eventproc_export_PutsCameraLogEvent, 0xff8243d0)

NSTUB(eventproc_export_NewTaskShell, 0xff824438)

NSTUB(eventproc_export_ExMem, 0xff824450)

NSTUB(eventproc_export_CreateCountingSemaphore, 0xff827054)
NSTUB(eventproc_export_DeleteSemaphore, 0xff8270ac)

NSTUB(eventproc_export_TakeSemaphore, 0xff827158)
NSTUB(eventproc_export_GiveSemaphore, 0xff827228)

NSTUB(eventproc_export_SleepTask, 0xff827490)

NSTUB(eventproc_export_HdmiHpd5VOutput, 0xff846b14)
NSTUB(eventproc_export_LockHdmiState, 0xff846b24)
NSTUB(eventproc_export_EdidDump, 0xff846b68)
NSTUB(eventproc_export_HdmiRegDump, 0xff846c30)

NSTUB(eventproc_export_UnLoadScript, 0xff86d650)

NSTUB(eventproc_export_LoadScript, 0xff86d74c)

NSTUB(eventproc_export_GetTimeOfSystem, 0xff86e594)

NSTUB(eventproc_export_OpLog_Show, 0xff871b88)
NSTUB(eventproc_export_OpLog_Stop, 0xff871c00)

NSTUB(eventproc_export_OpLog_WriteToROM, 0xff871c5c)

NSTUB(eventproc_export_OpLog_ReadFromROM, 0xff871c80)
NSTUB(eventproc_export_OpLog_ReadFromSD, 0xff871ccc)
NSTUB(eventproc_export_OpLog_WriteToSD, 0xff872124)
NSTUB(eventproc_export_OpLog_Get, 0xff8725a0)
NSTUB(eventproc_export_OpLog_Play, 0xff872604)

NSTUB(eventproc_export_OpLog_Start, 0xff872700)

NSTUB(eventproc_export_StartWDT, 0xff872fcc)
NSTUB(eventproc_export_StopWDT, 0xff873030)

NSTUB(eventproc_export_GetBuildDate, 0xff873120)
NSTUB(eventproc_export_GetBuildTime, 0xff873128)
NSTUB(eventproc_export_GetFirmwareVersion, 0xff873130)

NSTUB(eventproc_export_CheckSumAll, 0xff87323c)
NSTUB(eventproc_export_RomCheckSum, 0xff873434)

NSTUB(eventproc_export_CreateController, 0xff879268)
NSTUB(eventproc_export_DeleteController, 0xff879324)

NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff8794a8)

NSTUB(eventproc_export_GetSelfControllerHandle, 0xff8795d8)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff879a08)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff879a54)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff879acc)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff879b28)

NSTUB(eventproc_export_IsControlEventActive, 0xff87b9c0)
NSTUB(eventproc_export_UiEvnt_SetLogicalEventActive, 0xff87ba30)
NSTUB(eventproc_export_SetScriptMode, 0xff87ba80)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff87bab4)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff87bac4)

NSTUB(eventproc_export_UnlockMainPower, 0xff87bc34)
NSTUB(eventproc_export_LockMainPower, 0xff87bce0)
NSTUB(eventproc_export_SetAutoShutdownTime, 0xff87bd54)

NSTUB(eventproc_export_HardwareDefectWithRestart, 0xff87bf2c)
NSTUB(eventproc_export_HardwareDefect, 0xff87bf7c)

NSTUB(eventproc_export_PTM_AllResetToFactorySetting, 0xff87c190)
NSTUB(eventproc_export_PTM_AllReset, 0xff87c1a0)

NSTUB(eventproc_export_PTM_SetCurrentCaptureMode, 0xff87c638)

NSTUB(eventproc_export_PTM_GetWorkingCaptureMode, 0xff87c700)
NSTUB(eventproc_export_PTM_SetCurrentItem, 0xff87c704)

NSTUB(eventproc_export_PTM_GetCurrentItem, 0xff87c710)

NSTUB(eventproc_export_PTM_NextItem, 0xff87c77c)
NSTUB(eventproc_export_PTM_PrevItem, 0xff87c780)

NSTUB(eventproc_export_PTM_IsEnableItem, 0xff87c790)
NSTUB(eventproc_export_PTM_SetProprietyEnable, 0xff87c794)

NSTUB(eventproc_export_PTM_BackupUIProperty, 0xff87c7ac)
NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff87c7b0)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff882d6c)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff882da8)

NSTUB(eventproc_export_StartGUISystem, 0xff88f994)

NSTUB(eventproc_export_atol, 0xff88fc18)

NSTUB(eventproc_export_memcpy, 0xff88fe10)

NSTUB(eventproc_export_EnableLog, 0xff8a7be4)

NSTUB(eventproc_export_SetSDPwrPort, 0xff9392d4)
NSTUB(eventproc_export_GetAdVBattBottom, 0xff939300)
NSTUB(eventproc_export_GetAdChValue, 0xff939304)
NSTUB(eventproc_export_BeepDrive, 0xff939308)
NSTUB(eventproc_export_BeepDriveComp, 0xff93930c)
NSTUB(eventproc_export_VbattGet, 0xff939310)
NSTUB(eventproc_export_LEDDrive, 0xff939314)
NSTUB(eventproc_export_ShowPhySwStatus, 0xff939318)
NSTUB(eventproc_export_SetRawSWCheckMode, 0xff939328)
NSTUB(eventproc_export_OnPrintPhySw, 0xff939338)
NSTUB(eventproc_export_OffPrintPhySw, 0xff939348)
NSTUB(eventproc_export_GetSwitchStatus, 0xff939358)
NSTUB(eventproc_export_ShowSDStatus, 0xff93935c)
NSTUB(eventproc_export_GetSDDetect, 0xff93936c)
NSTUB(eventproc_export_GetSDProtect, 0xff939370)
NSTUB(eventproc_export_SetIgnoreAVJACK, 0xff939374)
NSTUB(eventproc_export_GetDialEventId, 0xff939384)
NSTUB(eventproc_export_GetBatteryCoverClose, 0xff939388)

NSTUB(eventproc_export_MonSelEvent, 0xff9395e4)
NSTUB(eventproc_export_MemoryChecker, 0xff9395e8)
NSTUB(eventproc_export_VerifyByte, 0xff9395ec)
NSTUB(eventproc_export_EraseSignature, 0xff9395f0)
NSTUB(eventproc_export_SDump, 0xff939600)
NSTUB(eventproc_export_Dump, 0xff939604)
NSTUB(eventproc_export_Dump32, 0xff939614)
NSTUB(eventproc_export_Poke32, 0xff939628)
NSTUB(eventproc_export_Poke16, 0xff939638)
NSTUB(eventproc_export_Poke8, 0xff939648)
NSTUB(eventproc_export_Peek32, 0xff939658)
NSTUB(eventproc_export_Peek16, 0xff93965c)
NSTUB(eventproc_export_Peek8, 0xff939660)
NSTUB(eventproc_export_Wait, 0xff939664)

NSTUB(eventproc_export_ShowAllTaskInfo, 0xff939678)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff939f60)

NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff93a06c)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff93a08c)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff93a0cc)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff93a0f4)
NSTUB(eventproc_export_UIFS_IsAvailableISO3200, 0xff93a114)
NSTUB(eventproc_export_UIFS_IsCurrentCaptureModeISO3200, 0xff93a11c)
NSTUB(eventproc_export_UIFS_SetCaptureModeToISO3200, 0xff93a138)
NSTUB(eventproc_export_UIFS_OpenPopupStrobe, 0xff93a194)
NSTUB(eventproc_export_UIFS_ClosePopupStrobe, 0xff93a1c4)
NSTUB(eventproc_export_UIFS_MountExtFlash, 0xff93a1f4)
NSTUB(eventproc_export_UIFS_UnmountExtFlash, 0xff93a224)
NSTUB(eventproc_export_UIFS_PressTeleButton, 0xff93a254)
NSTUB(eventproc_export_UIFS_UnpressTeleButton, 0xff93a290)
NSTUB(eventproc_export_UIFS_PressWideButton, 0xff93a2c8)
NSTUB(eventproc_export_UIFS_UnpressWideButton, 0xff93a304)
NSTUB(eventproc_export_UIFS_ConnectVideo, 0xff93a33c)
NSTUB(eventproc_export_UIFS_DisconnectVideo, 0xff93a36c)
NSTUB(eventproc_export_UIFS_ConnectHDMI, 0xff93a39c)
NSTUB(eventproc_export_UIFS_DisconnectHDMI, 0xff93a3a0)
NSTUB(eventproc_export_UIFS_MoveZoomTo, 0xff93a3a4)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff93a3a8)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff93a3ac)
NSTUB(eventproc_export_UIFS_SetCaptureModeToTv, 0xff93a3b0)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xff93a3e4)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xff93a418)
NSTUB(eventproc_export_UIFS_PostModeDial, 0xff93a420)
NSTUB(eventproc_export_UIFS_Capture, 0xff93a448)
NSTUB(eventproc_export_UIFS_CaptureNoneStop, 0xff93a44c)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff93a450)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff93a454)
NSTUB(eventproc_export_UIFS_StartClockMode, 0xff93a458)
NSTUB(eventproc_export_UIFS_EndClockMode, 0xff93a468)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff93a478)
NSTUB(eventproc_export_UIFS_WriteFirmInfoToFile, 0xff93a47c)
NSTUB(eventproc_export_UIFS_GetMovieRecoadableNumber, 0xff93a480)
NSTUB(eventproc_export_UIFS_GetStillShotableNumber, 0xff93a4c8)
NSTUB(eventproc_export_UIFS_ChangeShootState, 0xff93a4fc)

NSTUB(eventproc_export_UIFS_ShootSeqToUI, 0xff93a520)

NSTUB(eventproc_export_EraseLogSector, 0xff940b28)

NSTUB(eventproc_export_WriteToRom, 0xff9411dc)
NSTUB(eventproc_export_EraseSectorOfRom, 0xff94128c)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xff9537ec)

NSTUB(eventproc_export_ExecuteResetFactoryWithRomWrite, 0xff963644)

NSTUB(eventproc_export_memset, 0xff9d7458)
NSTUB(eventproc_export_sscanf, 0xff9d74d4)

