
NSTUB(eventproc_export_memShow, 0xff810da8)

NSTUB(eventproc_export_strlen, 0xff81400c)

NSTUB(eventproc_export_CreateTask, 0xff81e5b4)

NSTUB(eventproc_export_ExitTask, 0xff81e844)

NSTUB(eventproc_export_RotateConsoleZOder, 0xff81ef94)

NSTUB(eventproc_export_CPrintf, 0xff81f1a4)
NSTUB(eventproc_export_CPutChar, 0xff81f200)
NSTUB(eventproc_export_GetCh, 0xff81f22c)
NSTUB(eventproc_export_GetStringWithPrompt, 0xff81f27c)
NSTUB(eventproc_export_OpenConsole, 0xff81f2dc)
NSTUB(eventproc_export_CloseConsole, 0xff81f448)

NSTUB(eventproc_export_StartRedirectUART, 0xff81fb38)
NSTUB(eventproc_export_StopRedirectUART, 0xff81fc50)

NSTUB(eventproc_export_sprintf, 0xff8202fc)

NSTUB(eventproc_export_strcpy, 0xff82037c)
NSTUB(eventproc_export_strcmp, 0xff820394)
NSTUB(eventproc_export_memcmp, 0xff8203d8)

NSTUB(eventproc_export_Fopen_Fut, 0xff834d44)
NSTUB(eventproc_export_Fclose_Fut, 0xff834d84)
NSTUB(eventproc_export_Fread_Fut, 0xff834e30)
NSTUB(eventproc_export_Fwrite_Fut, 0xff834e84)

NSTUB(eventproc_export_Fseek_Fut, 0xff834f24)

NSTUB(eventproc_export_Open, 0xff835224)
NSTUB(eventproc_export_Close, 0xff83527c)

NSTUB(eventproc_export_Read, 0xff835308)
NSTUB(eventproc_export_Write, 0xff83530c)

NSTUB(eventproc_export_Lseek, 0xff835398)

NSTUB(eventproc_export_StartCameraLog, 0xff835740)
NSTUB(eventproc_export_ShowCameraLog, 0xff835744)
NSTUB(eventproc_export_ShowCameraLogInfo, 0xff835748)
NSTUB(eventproc_export_StopCameraLog, 0xff83574c)
NSTUB(eventproc_export_PutsCameraLogEvent, 0xff835750)

NSTUB(eventproc_export_NewTaskShell, 0xff8357b8)

NSTUB(eventproc_export_ExMem, 0xff8357d0)

NSTUB(eventproc_export_CreateCountingSemaphore, 0xff838630)
NSTUB(eventproc_export_DeleteSemaphore, 0xff838688)

NSTUB(eventproc_export_TakeSemaphore, 0xff838734)
NSTUB(eventproc_export_GiveSemaphore, 0xff838804)

NSTUB(eventproc_export_SleepTask, 0xff838a6c)

NSTUB(eventproc_export_memcpy, 0xff83e458)

NSTUB(eventproc_export_ChangePowerState, 0xff85d1a4)

NSTUB(eventproc_export_HdmiSimulateModeStop, 0xff85d590)
NSTUB(eventproc_export_HdmiSimulateModeStart, 0xff85d5b8)

NSTUB(eventproc_export_LockHdmiState, 0xff85d684)
NSTUB(eventproc_export_EdidDump, 0xff85d6cc)
NSTUB(eventproc_export_HdmiRegDump, 0xff85d794)

NSTUB(eventproc_export_UnLoadScript, 0xff8885a0)

NSTUB(eventproc_export_LoadScript, 0xff88869c)

NSTUB(eventproc_export_GetTimeOfSystem, 0xff8894e4)

NSTUB(eventproc_export_OpLog_Show, 0xff88cb5c)
NSTUB(eventproc_export_OpLog_Stop, 0xff88cbd4)

NSTUB(eventproc_export_OpLog_WriteToROM, 0xff88cc30)

NSTUB(eventproc_export_OpLog_ReadFromROM, 0xff88cc54)
NSTUB(eventproc_export_OpLog_ReadFromSD, 0xff88cca0)
NSTUB(eventproc_export_OpLog_WriteToSD, 0xff88d0f8)
NSTUB(eventproc_export_OpLog_Get, 0xff88d574)
NSTUB(eventproc_export_OpLog_Play, 0xff88d5d8)

NSTUB(eventproc_export_OpLog_Start, 0xff88d6d4)

NSTUB(eventproc_export_StartWDT, 0xff88df9c)
NSTUB(eventproc_export_StopWDT, 0xff88e000)

NSTUB(eventproc_export_GetBuildDate, 0xff88e0f0)
NSTUB(eventproc_export_GetBuildTime, 0xff88e0f8)
NSTUB(eventproc_export_GetFirmwareVersion, 0xff88e100)

NSTUB(eventproc_export_CheckSumAll, 0xff88e20c)
NSTUB(eventproc_export_RomCheckSum, 0xff88e448)

NSTUB(eventproc_export_CreateController, 0xff8945f0)
NSTUB(eventproc_export_DeleteController, 0xff8946ac)

NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff894830)

NSTUB(eventproc_export_GetSelfControllerHandle, 0xff894960)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff894da8)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff894df4)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff894e6c)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff894ec8)

NSTUB(eventproc_export_IsControlEventActive, 0xff896b8c)
NSTUB(eventproc_export_UiEvnt_SetLogicalEventActive, 0xff896bfc)
NSTUB(eventproc_export_SetScriptMode, 0xff896c4c)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff896c80)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff896c90)

NSTUB(eventproc_export_UnlockMainPower, 0xff896e00)
NSTUB(eventproc_export_LockMainPower, 0xff896eac)
NSTUB(eventproc_export_SetAutoShutdownTime, 0xff896f20)

NSTUB(eventproc_export_HardwareDefectWithRestart, 0xff8970f8)
NSTUB(eventproc_export_HardwareDefect, 0xff897148)

NSTUB(eventproc_export_PTM_AllResetToFactorySetting, 0xff897358)
NSTUB(eventproc_export_PTM_AllReset, 0xff897368)

NSTUB(eventproc_export_PTM_SetCurrentCaptureMode, 0xff89770c)

NSTUB(eventproc_export_PTM_GetWorkingCaptureMode, 0xff8977d0)

NSTUB(eventproc_export_PTM_SetCurrentItem, 0xff8977d8)

NSTUB(eventproc_export_PTM_GetCurrentItem, 0xff8977e4)

NSTUB(eventproc_export_PTM_NextItem, 0xff897850)
NSTUB(eventproc_export_PTM_PrevItem, 0xff897854)

NSTUB(eventproc_export_PTM_IsEnableItem, 0xff897864)
NSTUB(eventproc_export_PTM_SetProprietyEnable, 0xff897868)

NSTUB(eventproc_export_PTM_BackupUIProperty, 0xff897880)

NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff897888)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff89eb28)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff89eb64)

NSTUB(eventproc_export_GUISrv_StartGUISystem, 0xff8ac5fc)

NSTUB(eventproc_export_atol, 0xff8ac870)

NSTUB(eventproc_export_GetLatestHVPosition, 0xff90b9a0)

NSTUB(eventproc_export_SetSDPwrPort, 0xff95d084)
NSTUB(eventproc_export_GetAdVBattBottom, 0xff95d0b0)
NSTUB(eventproc_export_GetAdChValue, 0xff95d0b4)
NSTUB(eventproc_export_BeepDrive, 0xff95d0b8)
NSTUB(eventproc_export_BeepDriveComp, 0xff95d0bc)
NSTUB(eventproc_export_VbattGet, 0xff95d0c0)
NSTUB(eventproc_export_LEDDrive, 0xff95d0c4)
NSTUB(eventproc_export_ShowPhySwStatus, 0xff95d0c8)
NSTUB(eventproc_export_SetRawSWCheckMode, 0xff95d0d8)
NSTUB(eventproc_export_OnPrintPhySw, 0xff95d0e8)
NSTUB(eventproc_export_OffPrintPhySw, 0xff95d0f8)
NSTUB(eventproc_export_GetSwitchStatus, 0xff95d108)
NSTUB(eventproc_export_ShowSDStatus, 0xff95d10c)
NSTUB(eventproc_export_GetSDDetect, 0xff95d11c)
NSTUB(eventproc_export_GetSDProtect, 0xff95d120)
NSTUB(eventproc_export_SetIgnoreAVJACK, 0xff95d124)
NSTUB(eventproc_export_GetDialEventId, 0xff95d134)
NSTUB(eventproc_export_GetBatteryCoverClose, 0xff95d138)

NSTUB(eventproc_export_MonSelEvent, 0xff95d3b8)
NSTUB(eventproc_export_MemoryChecker, 0xff95d3bc)
NSTUB(eventproc_export_VerifyByte, 0xff95d3c0)
NSTUB(eventproc_export_EraseSignature, 0xff95d3c4)
NSTUB(eventproc_export_SDump, 0xff95d3d4)
NSTUB(eventproc_export_Dump, 0xff95d3d8)
NSTUB(eventproc_export_Dump32, 0xff95d3e8)
NSTUB(eventproc_export_Poke32, 0xff95d3fc)
NSTUB(eventproc_export_Poke16, 0xff95d40c)
NSTUB(eventproc_export_Poke8, 0xff95d41c)
NSTUB(eventproc_export_Peek32, 0xff95d42c)
NSTUB(eventproc_export_Peek16, 0xff95d430)
NSTUB(eventproc_export_Peek8, 0xff95d434)
NSTUB(eventproc_export_Wait, 0xff95d438)

NSTUB(eventproc_export_ShowAllTaskInfo, 0xff95d44c)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff95dd10)

NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff95de1c)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff95de3c)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff95de7c)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff95debc)
NSTUB(eventproc_export_UIFS_IsAvailableISO3200, 0xff95dedc)
NSTUB(eventproc_export_UIFS_IsCurrentCaptureModeISO3200, 0xff95dee4)
NSTUB(eventproc_export_UIFS_SetCaptureModeToISO3200, 0xff95df00)
NSTUB(eventproc_export_UIFS_OpenPopupStrobe, 0xff95df5c)
NSTUB(eventproc_export_UIFS_ClosePopupStrobe, 0xff95df8c)
NSTUB(eventproc_export_UIFS_MountExtFlash, 0xff95dfbc)
NSTUB(eventproc_export_UIFS_UnmountExtFlash, 0xff95dfec)
NSTUB(eventproc_export_UIFS_PressTeleButton, 0xff95e01c)
NSTUB(eventproc_export_UIFS_UnpressTeleButton, 0xff95e058)
NSTUB(eventproc_export_UIFS_PressWideButton, 0xff95e090)
NSTUB(eventproc_export_UIFS_UnpressWideButton, 0xff95e0cc)
NSTUB(eventproc_export_UIFS_ConnectVideo, 0xff95e104)
NSTUB(eventproc_export_UIFS_DisconnectVideo, 0xff95e134)
NSTUB(eventproc_export_UIFS_ConnectHDMI, 0xff95e164)
NSTUB(eventproc_export_UIFS_DisconnectHDMI, 0xff95e168)
NSTUB(eventproc_export_UIFS_MoveZoomTo, 0xff95e16c)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff95e170)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff95e174)
NSTUB(eventproc_export_UIFS_SetCaptureModeToTv, 0xff95e178)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xff95e1ac)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xff95e1e0)
NSTUB(eventproc_export_UIFS_PostModeDial, 0xff95e1e8)
NSTUB(eventproc_export_UIFS_Capture, 0xff95e210)
NSTUB(eventproc_export_UIFS_CaptureNoneStop, 0xff95e214)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff95e218)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff95e21c)
NSTUB(eventproc_export_UIFS_StartClockMode, 0xff95e220)
NSTUB(eventproc_export_UIFS_EndClockMode, 0xff95e230)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff95e240)
NSTUB(eventproc_export_UIFS_GetMovieRecoadableNumber, 0xff95e248)
NSTUB(eventproc_export_UIFS_GetStillShotableNumber, 0xff95e290)
NSTUB(eventproc_export_UIFS_ChangeShootState, 0xff95e2c4)

NSTUB(eventproc_export_UIFS_ShootSeqToUI, 0xff95e2e8)
NSTUB(eventproc_export_UIFS_GetLastPath, 0xff95e2f0)
NSTUB(eventproc_export_UIFS_GetAvItemCount, 0xff95e328)
NSTUB(eventproc_export_UIFS_GetTvItemCount, 0xff95e380)
NSTUB(eventproc_export_UIFS_GetAvItem, 0xff95e3d8)
NSTUB(eventproc_export_UIFS_GetTvItem, 0xff95e414)
NSTUB(eventproc_export_UIFS_GetCurrentAvString, 0xff95e510)
NSTUB(eventproc_export_UIFS_GetCurrentTvString, 0xff95e590)
NSTUB(eventproc_export_UIFS_IsAvailableShots, 0xff95e610)

NSTUB(eventproc_export_EraseLogSector, 0xff96669c)

NSTUB(eventproc_export_WriteToRom, 0xff966d70)
NSTUB(eventproc_export_EraseSectorOfRom, 0xff966e20)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xff97ddc0)

NSTUB(eventproc_export_ExecuteResetFactoryWithRomWrite, 0xff9908b8)

NSTUB(eventproc_export_memset, 0xffa070f8)

NSTUB(eventproc_export_sscanf, 0xffa0722c)

