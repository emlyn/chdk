
NSTUB(eventproc_export_memShow, 0xffc00bf4)

NSTUB(eventproc_export_CreateTask, 0xffc0afac)

NSTUB(eventproc_export_ExitTask, 0xffc0b23c)

NSTUB(eventproc_export_RotateConsoleZOder, 0xffc0b98c)

NSTUB(eventproc_export_CPrintf, 0xffc0bb9c)
NSTUB(eventproc_export_CPutChar, 0xffc0bbf8)
NSTUB(eventproc_export_GetCh, 0xffc0bc24)
NSTUB(eventproc_export_GetStringWithPrompt, 0xffc0bc74)
NSTUB(eventproc_export_OpenConsole, 0xffc0bcd4)
NSTUB(eventproc_export_CloseConsole, 0xffc0be40)

NSTUB(eventproc_export_StartRedirectUART, 0xffc0c530)
NSTUB(eventproc_export_StopRedirectUART, 0xffc0c648)

NSTUB(eventproc_export_sprintf, 0xffc0cb5c)

NSTUB(eventproc_export_strcpy, 0xffc0cbdc)
NSTUB(eventproc_export_strcmp, 0xffc0cbf4)
NSTUB(eventproc_export_strlen, 0xffc0cc38)
NSTUB(eventproc_export_memcmp, 0xffc0cc5c)

NSTUB(eventproc_export_Fopen_Fut, 0xffc13624)
NSTUB(eventproc_export_Fclose_Fut, 0xffc13664)
NSTUB(eventproc_export_Fread_Fut, 0xffc13710)
NSTUB(eventproc_export_Fwrite_Fut, 0xffc13764)

NSTUB(eventproc_export_Fseek_Fut, 0xffc13804)

NSTUB(eventproc_export_Open, 0xffc13c14)
NSTUB(eventproc_export_Close, 0xffc13c3c)

NSTUB(eventproc_export_Read, 0xffc13ce4)
NSTUB(eventproc_export_Write, 0xffc13ce8)

NSTUB(eventproc_export_Lseek, 0xffc13e44)

NSTUB(eventproc_export_StartCameraLog, 0xffc1430c)
NSTUB(eventproc_export_ShowCameraLog, 0xffc14310)
NSTUB(eventproc_export_ShowCameraLogInfo, 0xffc14314)
NSTUB(eventproc_export_StopCameraLog, 0xffc14318)
NSTUB(eventproc_export_PutsCameraLogEvent, 0xffc1431c)

NSTUB(eventproc_export_NewTaskShell, 0xffc14384)

NSTUB(eventproc_export_ExMem, 0xffc1439c)

NSTUB(eventproc_export_CreateCountingSemaphore, 0xffc16ad0)
NSTUB(eventproc_export_DeleteSemaphore, 0xffc16b28)

NSTUB(eventproc_export_TakeSemaphore, 0xffc16bd4)
NSTUB(eventproc_export_GiveSemaphore, 0xffc16ca4)

NSTUB(eventproc_export_SleepTask, 0xffc16f0c)

NSTUB(eventproc_export_UnLoadScript, 0xffc53940)

NSTUB(eventproc_export_LoadScript, 0xffc53a3c)

NSTUB(eventproc_export_GetTimeOfSystem, 0xffc54794)

NSTUB(eventproc_export_OpLog_Show, 0xffc57b60)
NSTUB(eventproc_export_OpLog_Stop, 0xffc57c00)

NSTUB(eventproc_export_OpLog_WriteToROM, 0xffc57c5c)

NSTUB(eventproc_export_OpLog_ReadFromROM, 0xffc57c8c)
NSTUB(eventproc_export_OpLog_ReadFromSD, 0xffc57d2c)
NSTUB(eventproc_export_OpLog_WriteToSD, 0xffc58124)
NSTUB(eventproc_export_OpLog_Get, 0xffc58590)
NSTUB(eventproc_export_OpLog_Play, 0xffc585b0)

NSTUB(eventproc_export_OpLog_Start, 0xffc5871c)

NSTUB(eventproc_export_StartWDT, 0xffc58fd4)
NSTUB(eventproc_export_StopWDT, 0xffc59038)

NSTUB(eventproc_export_GetBuildDate, 0xffc59128)
NSTUB(eventproc_export_GetBuildTime, 0xffc59130)
NSTUB(eventproc_export_GetFirmwareVersion, 0xffc59138)

NSTUB(eventproc_export_CheckSumAll, 0xffc59244)
NSTUB(eventproc_export_RomCheckSum, 0xffc5943c)

NSTUB(eventproc_export_CreateController, 0xffc5ca60)
NSTUB(eventproc_export_DeleteController, 0xffc5cb1c)

NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xffc5cca0)

NSTUB(eventproc_export_GetSelfControllerHandle, 0xffc5cdd0)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xffc5d1f8)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xffc5d244)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xffc5d2bc)
NSTUB(eventproc_export_ShowLogicalEventName, 0xffc5d318)

NSTUB(eventproc_export_IsControlEventActive, 0xffc5d8dc)
NSTUB(eventproc_export_UiEvnt_SetLogicalEventActive, 0xffc5d94c)
NSTUB(eventproc_export_SetScriptMode, 0xffc5d99c)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xffc5d9d0)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xffc5d9e0)

NSTUB(eventproc_export_UnlockMainPower, 0xffc5db24)
NSTUB(eventproc_export_LockMainPower, 0xffc5dbd0)
NSTUB(eventproc_export_SetAutoShutdownTime, 0xffc5dc44)

NSTUB(eventproc_export_HardwareDefectWithRestart, 0xffc5de1c)
NSTUB(eventproc_export_HardwareDefect, 0xffc5de6c)

NSTUB(eventproc_export_PTM_AllResetToFactorySetting, 0xffc5e080)
NSTUB(eventproc_export_PTM_AllReset, 0xffc5e090)

NSTUB(eventproc_export_PTM_SetCurrentCaptureMode, 0xffc5e528)

NSTUB(eventproc_export_PTM_GetWorkingCaptureMode, 0xffc5e5f0)
NSTUB(eventproc_export_PTM_SetCurrentItem, 0xffc5e5f4)

NSTUB(eventproc_export_PTM_GetCurrentItem, 0xffc5e600)

NSTUB(eventproc_export_PTM_NextItem, 0xffc5e66c)
NSTUB(eventproc_export_PTM_PrevItem, 0xffc5e670)

NSTUB(eventproc_export_PTM_IsEnableItem, 0xffc5e680)
NSTUB(eventproc_export_PTM_SetProprietyEnable, 0xffc5e684)

NSTUB(eventproc_export_PTM_BackupUIProperty, 0xffc5e69c)
NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xffc5e6a0)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xffc6421c)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xffc64258)

NSTUB(eventproc_export_StartGUISystem, 0xffc6c7c0)

NSTUB(eventproc_export_atol, 0xffc6ca40)

NSTUB(eventproc_export_memcpy, 0xffc6cc38)

NSTUB(eventproc_export_EnableLog, 0xffc84838)

NSTUB(eventproc_export_SetSDPwrPort, 0xffcf87bc)
NSTUB(eventproc_export_GetAdVBattBottom, 0xffcf87e8)
NSTUB(eventproc_export_GetAdChValue, 0xffcf87ec)
NSTUB(eventproc_export_BeepDrive, 0xffcf87f0)
NSTUB(eventproc_export_BeepDriveComp, 0xffcf87f4)
NSTUB(eventproc_export_VbattGet, 0xffcf87f8)
NSTUB(eventproc_export_LEDDrive, 0xffcf87fc)
NSTUB(eventproc_export_ShowPhySwStatus, 0xffcf8800)
NSTUB(eventproc_export_SetRawSWCheckMode, 0xffcf8810)
NSTUB(eventproc_export_OnPrintPhySw, 0xffcf8820)
NSTUB(eventproc_export_OffPrintPhySw, 0xffcf8830)
NSTUB(eventproc_export_GetSwitchStatus, 0xffcf8840)
NSTUB(eventproc_export_ShowSDStatus, 0xffcf8844)
NSTUB(eventproc_export_GetSDDetect, 0xffcf8854)
NSTUB(eventproc_export_GetSDProtect, 0xffcf8858)
NSTUB(eventproc_export_SetIgnoreAVJACK, 0xffcf885c)
NSTUB(eventproc_export_GetDialEventId, 0xffcf886c)
NSTUB(eventproc_export_GetBatteryCoverClose, 0xffcf8870)

NSTUB(eventproc_export_MonSelEvent, 0xffcf8ac8)
NSTUB(eventproc_export_MemoryChecker, 0xffcf8acc)
NSTUB(eventproc_export_VerifyByte, 0xffcf8ad0)
NSTUB(eventproc_export_EraseSignature, 0xffcf8ad4)
NSTUB(eventproc_export_SDump, 0xffcf8ae4)
NSTUB(eventproc_export_Dump, 0xffcf8ae8)
NSTUB(eventproc_export_Dump32, 0xffcf8af8)
NSTUB(eventproc_export_Poke32, 0xffcf8b0c)
NSTUB(eventproc_export_Poke16, 0xffcf8b1c)
NSTUB(eventproc_export_Poke8, 0xffcf8b2c)
NSTUB(eventproc_export_Peek32, 0xffcf8b3c)
NSTUB(eventproc_export_Peek16, 0xffcf8b40)
NSTUB(eventproc_export_Peek8, 0xffcf8b44)
NSTUB(eventproc_export_Wait, 0xffcf8b48)

NSTUB(eventproc_export_ShowAllTaskInfo, 0xffcf8b5c)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xffcf9444)

NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xffcf9550)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xffcf9570)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xffcf95d8)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xffcf9600)
NSTUB(eventproc_export_UIFS_IsAvailableISO3200, 0xffcf9620)
NSTUB(eventproc_export_UIFS_IsCurrentCaptureModeISO3200, 0xffcf9628)
NSTUB(eventproc_export_UIFS_SetCaptureModeToISO3200, 0xffcf9644)
NSTUB(eventproc_export_UIFS_OpenPopupStrobe, 0xffcf9694)
NSTUB(eventproc_export_UIFS_ClosePopupStrobe, 0xffcf96c4)
NSTUB(eventproc_export_UIFS_MountExtFlash, 0xffcf96f4)
NSTUB(eventproc_export_UIFS_UnmountExtFlash, 0xffcf9724)
NSTUB(eventproc_export_UIFS_PressTeleButton, 0xffcf9754)
NSTUB(eventproc_export_UIFS_UnpressTeleButton, 0xffcf9790)
NSTUB(eventproc_export_UIFS_PressWideButton, 0xffcf97c8)
NSTUB(eventproc_export_UIFS_UnpressWideButton, 0xffcf9804)
NSTUB(eventproc_export_UIFS_ConnectVideo, 0xffcf983c)
NSTUB(eventproc_export_UIFS_DisconnectVideo, 0xffcf986c)
NSTUB(eventproc_export_UIFS_ConnectHDMI, 0xffcf989c)
NSTUB(eventproc_export_UIFS_DisconnectHDMI, 0xffcf98a0)
NSTUB(eventproc_export_UIFS_MoveZoomTo, 0xffcf98a4)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xffcf98a8)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xffcf98ac)
NSTUB(eventproc_export_UIFS_SetCaptureModeToTv, 0xffcf98b0)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xffcf98e4)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xffcf9918)
NSTUB(eventproc_export_UIFS_PostModeDial, 0xffcf9920)
NSTUB(eventproc_export_UIFS_Capture, 0xffcf9948)
NSTUB(eventproc_export_UIFS_CaptureNoneStop, 0xffcf994c)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xffcf9950)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xffcf9954)
NSTUB(eventproc_export_UIFS_StartClockMode, 0xffcf9958)
NSTUB(eventproc_export_UIFS_EndClockMode, 0xffcf9960)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xffcf9968)
NSTUB(eventproc_export_UIFS_WriteFirmInfoToFile, 0xffcf996c)
NSTUB(eventproc_export_UIFS_GetMovieRecoadableNumber, 0xffcf9970)
NSTUB(eventproc_export_UIFS_GetStillShotableNumber, 0xffcf99b8)
NSTUB(eventproc_export_UIFS_ChangeShootState, 0xffcf99ec)

NSTUB(eventproc_export_UIFS_ShootSeqToUI, 0xffcf9a10)

NSTUB(eventproc_export_EraseLogSector, 0xffcfea10)

NSTUB(eventproc_export_WriteToRom, 0xffcff0f4)
NSTUB(eventproc_export_EraseSectorOfRom, 0xffcff1a4)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xffd10f90)

NSTUB(eventproc_export_ExecuteResetFactoryWithRomWrite, 0xffd1c354)

NSTUB(eventproc_export_memset, 0xffd65020)
NSTUB(eventproc_export_sscanf, 0xffd6509c)

