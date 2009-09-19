
NSTUB(eventproc_export_memShow, 0xffc00bc8)

NSTUB(eventproc_export_CreateCountingSemaphore, 0xffc0b648)
NSTUB(eventproc_export_DeleteSemaphore, 0xffc0b6a0)

NSTUB(eventproc_export_TakeSemaphore, 0xffc0b74c)
NSTUB(eventproc_export_GiveSemaphore, 0xffc0b81c)

NSTUB(eventproc_export_CreateTask, 0xffc0b8c0)

//NSTUB(eventproc_export_ExitTask, 0xffc0bb50)

NSTUB(eventproc_export_RotateConsoleZOder, 0xffc0c4a0)

NSTUB(eventproc_export_CPrintf, 0xffc0c6b0)
NSTUB(eventproc_export_CPutChar, 0xffc0c70c)
NSTUB(eventproc_export_GetCh, 0xffc0c738)
NSTUB(eventproc_export_GetStringWithPrompt, 0xffc0c788)
NSTUB(eventproc_export_OpenConsole, 0xffc0c7e8)
NSTUB(eventproc_export_CloseConsole, 0xffc0c954)

NSTUB(eventproc_export_StartRedirectUART, 0xffc0d038)
NSTUB(eventproc_export_StopRedirectUART, 0xffc0d150)

NSTUB(eventproc_export_sprintf, 0xffc0d7b4)

NSTUB(eventproc_export_strcpy, 0xffc0d834)
NSTUB(eventproc_export_strcmp, 0xffc0d84c)
NSTUB(eventproc_export_strlen, 0xffc0d890)
NSTUB(eventproc_export_memcmp, 0xffc0d8b4)

NSTUB(eventproc_export_Fopen_Fut, 0xffc12d30)
NSTUB(eventproc_export_Fclose_Fut, 0xffc12d70)
NSTUB(eventproc_export_Fread_Fut, 0xffc12e1c)
NSTUB(eventproc_export_Fwrite_Fut, 0xffc12e70)

NSTUB(eventproc_export_Fseek_Fut, 0xffc12f10)

NSTUB(eventproc_export_Open, 0xffc13320)
NSTUB(eventproc_export_Close, 0xffc13348)

NSTUB(eventproc_export_Read, 0xffc133f0)
NSTUB(eventproc_export_Write, 0xffc133f4)

NSTUB(eventproc_export_Lseek, 0xffc13550)

NSTUB(eventproc_export_StartCameraLog, 0xffc13a18)
NSTUB(eventproc_export_ShowCameraLog, 0xffc13a1c)
NSTUB(eventproc_export_ShowCameraLogInfo, 0xffc13a20)
NSTUB(eventproc_export_StopCameraLog, 0xffc13a24)
NSTUB(eventproc_export_PutsCameraLogEvent, 0xffc13a28)

NSTUB(eventproc_export_NewTaskShell, 0xffc13a90)

NSTUB(eventproc_export_ExMem, 0xffc13aa8)

//NSTUB(eventproc_export_SleepTask, 0xffc176ac)

NSTUB(eventproc_export_UnLoadScript, 0xffc58c74)

NSTUB(eventproc_export_LoadScript, 0xffc58d70)

NSTUB(eventproc_export_OpLog_Show, 0xffc5cb70)
NSTUB(eventproc_export_OpLog_Stop, 0xffc5cc10)
NSTUB(eventproc_export_OpLog_WriteToROM, 0xffc5cc3c)

NSTUB(eventproc_export_OpLog_ReadFromROM, 0xffc5cc98)
NSTUB(eventproc_export_OpLog_ReadFromSD, 0xffc5cd38)
NSTUB(eventproc_export_OpLog_WriteToSD, 0xffc5d104)
NSTUB(eventproc_export_OpLog_Get, 0xffc5d530)
NSTUB(eventproc_export_OpLog_Play, 0xffc5d550)

NSTUB(eventproc_export_OpLog_Start, 0xffc5d6d0)

NSTUB(eventproc_export_StartWDT, 0xffc5df88)
NSTUB(eventproc_export_StopWDT, 0xffc5dfec)

NSTUB(eventproc_export_GetBuildDate, 0xffc5e0dc)
NSTUB(eventproc_export_GetBuildTime, 0xffc5e0e4)
NSTUB(eventproc_export_GetFirmwareVersion, 0xffc5e0ec)

NSTUB(eventproc_export_CheckSumAll, 0xffc5e1f8)

NSTUB(eventproc_export_RomCheckSum, 0xffc5e3f0)

NSTUB(eventproc_export_CreateController, 0xffc61410)
NSTUB(eventproc_export_DeleteController, 0xffc614cc)

NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xffc61650)

NSTUB(eventproc_export_GetSelfControllerHandle, 0xffc61780)

//NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xffc61bb4)
//NSTUB(eventproc_export_PostLogicalEventToUI, 0xffc61c00)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xffc61c78)
NSTUB(eventproc_export_ShowLogicalEventName, 0xffc61cd4)

NSTUB(eventproc_export_IsControlEventActive, 0xffc63a80)
NSTUB(eventproc_export_UiEvnt_SetLogicalEventActive, 0xffc63af0)
NSTUB(eventproc_export_SetScriptMode, 0xffc63b40)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xffc63b74)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xffc63b84)

NSTUB(eventproc_export_UnlockMainPower, 0xffc63cf4)
NSTUB(eventproc_export_LockMainPower, 0xffc63da0)
NSTUB(eventproc_export_SetAutoShutdownTime, 0xffc63e14)

NSTUB(eventproc_export_HardwareDefectWithRestart, 0xffc63fec)
NSTUB(eventproc_export_HardwareDefect, 0xffc6403c)

NSTUB(eventproc_export_PTM_AllResetToFactorySetting, 0xffc64250)
NSTUB(eventproc_export_PTM_AllReset, 0xffc64260)

NSTUB(eventproc_export_PTM_SetCurrentCaptureMode, 0xffc6463c)

NSTUB(eventproc_export_PTM_GetWorkingCaptureMode, 0xffc6470c)
NSTUB(eventproc_export_PTM_SetCurrentItem, 0xffc64710)

NSTUB(eventproc_export_PTM_GetCurrentItem, 0xffc6471c)

NSTUB(eventproc_export_PTM_NextItem, 0xffc64788)
NSTUB(eventproc_export_PTM_PrevItem, 0xffc6478c)

NSTUB(eventproc_export_PTM_IsEnableItem, 0xffc6479c)
NSTUB(eventproc_export_PTM_SetProprietyEnable, 0xffc647a0)

NSTUB(eventproc_export_PTM_BackupUIProperty, 0xffc647b8)
NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xffc647bc)

NSTUB(eventproc_export_PTM_NotifyStartRemoteCapture, 0xffc647d8)
NSTUB(eventproc_export_PTM_NotifyEndRemoteCapture, 0xffc64930)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xffc6a8c4)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xffc6a900)

NSTUB(eventproc_export_StartGUISystem, 0xffc74838)

NSTUB(eventproc_export_atol, 0xffc74978)

NSTUB(eventproc_export_memcpy, 0xffc74b70)

NSTUB(eventproc_export_SetSDPwrPort, 0xffd1771c)
NSTUB(eventproc_export_GetAdVBattBottom, 0xffd17748)
NSTUB(eventproc_export_GetAdChValue, 0xffd1774c)
NSTUB(eventproc_export_BeepDrive, 0xffd17750)
NSTUB(eventproc_export_VbattGet, 0xffd17754)
NSTUB(eventproc_export_LEDDrive, 0xffd17758)
NSTUB(eventproc_export_ShowPhySwStatus, 0xffd1775c)
NSTUB(eventproc_export_SetRawSWCheckMode, 0xffd1776c)
NSTUB(eventproc_export_OnPrintPhySw, 0xffd1777c)
NSTUB(eventproc_export_OffPrintPhySw, 0xffd1778c)
NSTUB(eventproc_export_GetSwitchStatus, 0xffd1779c)
NSTUB(eventproc_export_ShowSDStatus, 0xffd177a0)
NSTUB(eventproc_export_GetSDDetect, 0xffd177b0)
NSTUB(eventproc_export_GetSDProtect, 0xffd177b4)
NSTUB(eventproc_export_SetIgnoreAVJACK, 0xffd177b8)
NSTUB(eventproc_export_GetDialEventId, 0xffd177c8)
NSTUB(eventproc_export_GetBatteryCoverClose, 0xffd177cc)

NSTUB(eventproc_export_MonSelEvent, 0xffd17a08)
NSTUB(eventproc_export_MemoryChecker, 0xffd17a0c)
NSTUB(eventproc_export_VerifyByte, 0xffd17a10)
NSTUB(eventproc_export_EraseSignature, 0xffd17a14)
NSTUB(eventproc_export_SDump, 0xffd17a24)
NSTUB(eventproc_export_Dump, 0xffd17a28)
NSTUB(eventproc_export_Dump32, 0xffd17a38)
NSTUB(eventproc_export_Poke32, 0xffd17a4c)
NSTUB(eventproc_export_Poke16, 0xffd17a5c)
NSTUB(eventproc_export_Poke8, 0xffd17a6c)
NSTUB(eventproc_export_Peek32, 0xffd17a7c)
NSTUB(eventproc_export_Peek16, 0xffd17a80)
NSTUB(eventproc_export_Peek8, 0xffd17a84)
NSTUB(eventproc_export_Wait, 0xffd17a88)

NSTUB(eventproc_export_ShowAllTaskInfo, 0xffd17a9c)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xffd18384)

NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xffd18490)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xffd184b0)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xffd184e8)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xffd18510)
NSTUB(eventproc_export_UIFS_OpenPopupStrobe, 0xffd18530)
NSTUB(eventproc_export_UIFS_ClosePopupStrobe, 0xffd18560)
NSTUB(eventproc_export_UIFS_MountExtFlash, 0xffd18590)
NSTUB(eventproc_export_UIFS_UnmountExtFlash, 0xffd185c0)
NSTUB(eventproc_export_UIFS_PressTeleButton, 0xffd185f0)
NSTUB(eventproc_export_UIFS_UnpressTeleButton, 0xffd1862c)
NSTUB(eventproc_export_UIFS_PressWideButton, 0xffd18664)
NSTUB(eventproc_export_UIFS_UnpressWideButton, 0xffd186a0)
NSTUB(eventproc_export_UIFS_ConnectVideo, 0xffd186d8)
NSTUB(eventproc_export_UIFS_DisconnectVideo, 0xffd18708)
NSTUB(eventproc_export_UIFS_MoveZoomTo, 0xffd18738)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xffd1873c)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xffd18740)
NSTUB(eventproc_export_UIFS_SetCaptureModeToTv, 0xffd18744)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xffd18778)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xffd187ac)
NSTUB(eventproc_export_UIFS_SetCaptureModeToISO3200, 0xffd187b4)
NSTUB(eventproc_export_UIFS_PostModeDial, 0xffd187d4)
NSTUB(eventproc_export_UIFS_Capture, 0xffd187fc)
NSTUB(eventproc_export_UIFS_CaptureNoneStop, 0xffd18800)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xffd18804)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xffd18808)
NSTUB(eventproc_export_UIFS_StartClockMode, 0xffd1880c)
NSTUB(eventproc_export_UIFS_EndClockMode, 0xffd18814)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xffd1881c)
NSTUB(eventproc_export_UIFS_WriteFirmInfoToFile, 0xffd18820)
NSTUB(eventproc_export_UIFS_GetMovieRecoadableNumber, 0xffd18824)

NSTUB(eventproc_export_UIFS_ChangeShootState, 0xffd188a0)

NSTUB(eventproc_export_UIFS_ShootSeqToUI, 0xffd188c4)

NSTUB(eventproc_export_EraseLogSector, 0xffd1fc74)

NSTUB(eventproc_export_WriteToRom, 0xffd20380)
NSTUB(eventproc_export_EraseSectorOfRom, 0xffd20430)

NSTUB(eventproc_export_GetTimeOfSystem, 0xffd24468)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xffd3087c)

NSTUB(eventproc_export_ExecuteResetFactoryWithRomWrite, 0xffd38cdc)

NSTUB(eventproc_export_StartDirectTransferManager, 0xffd7ca40)

NSTUB(eventproc_export_memset, 0xffd8ff54)

NSTUB(eventproc_export_sscanf, 0xffd90498)

NSTUB(eventproc_export_StoptDtConfirmMenu, 0xffe1e53c)

NSTUB(eventproc_export_StartDtConfirmMenu, 0xffe1e680)

NSTUB(eventproc_export_StoptDtExecuteMenu, 0xffe1e84c)

NSTUB(eventproc_export_StartDtExecuteMenu, 0xffe1ead8)

