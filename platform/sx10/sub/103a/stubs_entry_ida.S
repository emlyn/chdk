
NSTUB(eventproc_export_memShow, 0xff810bc4)

NSTUB(eventproc_export_CreateTask, 0xff81aef4)

NSTUB(eventproc_export_ExitTask, 0xff81b184)

NSTUB(eventproc_export_RotateConsoleZOder, 0xff81b8d4)

NSTUB(eventproc_export_CPrintf, 0xff81bae4)
NSTUB(eventproc_export_CPutChar, 0xff81bb40)
NSTUB(eventproc_export_GetCh, 0xff81bb6c)
NSTUB(eventproc_export_GetStringWithPrompt, 0xff81bbbc)
NSTUB(eventproc_export_OpenConsole, 0xff81bc1c)
NSTUB(eventproc_export_CloseConsole, 0xff81bd88)

NSTUB(eventproc_export_StartRedirectUART, 0xff81c478)
NSTUB(eventproc_export_StopRedirectUART, 0xff81c590)

NSTUB(eventproc_export_sprintf, 0xff81caa4)

NSTUB(eventproc_export_strcpy, 0xff81cb24)
NSTUB(eventproc_export_strcmp, 0xff81cb3c)
NSTUB(eventproc_export_strlen, 0xff81cb80)
NSTUB(eventproc_export_memcmp, 0xff81cba4)

NSTUB(eventproc_export_Fopen_Fut, 0xff82344c)
NSTUB(eventproc_export_Fclose_Fut, 0xff82348c)
NSTUB(eventproc_export_Fread_Fut, 0xff823538)
NSTUB(eventproc_export_Fwrite_Fut, 0xff82358c)

NSTUB(eventproc_export_Fseek_Fut, 0xff82362c)

NSTUB(eventproc_export_Open, 0xff823a3c)
NSTUB(eventproc_export_Close, 0xff823a64)

NSTUB(eventproc_export_Read, 0xff823b0c)
NSTUB(eventproc_export_Write, 0xff823b10)

NSTUB(eventproc_export_Lseek, 0xff823c6c)

NSTUB(eventproc_export_StartCameraLog, 0xff824134)
NSTUB(eventproc_export_ShowCameraLog, 0xff824138)
NSTUB(eventproc_export_ShowCameraLogInfo, 0xff82413c)
NSTUB(eventproc_export_StopCameraLog, 0xff824140)
NSTUB(eventproc_export_PutsCameraLogEvent, 0xff824144)

NSTUB(eventproc_export_NewTaskShell, 0xff8241ac)

NSTUB(eventproc_export_ExMem, 0xff8241c4)

NSTUB(eventproc_export_CreateCountingSemaphore, 0xff827814)
NSTUB(eventproc_export_DeleteSemaphore, 0xff82786c)

NSTUB(eventproc_export_TakeSemaphore, 0xff827918)
NSTUB(eventproc_export_GiveSemaphore, 0xff8279e8)

NSTUB(eventproc_export_SleepTask, 0xff827c50)

NSTUB(eventproc_export_EnableLog, 0xff8331b4)

NSTUB(eventproc_export_UnLoadScript, 0xff872918)

NSTUB(eventproc_export_LoadScript, 0xff872a14)

NSTUB(eventproc_export_GetTimeOfSystem, 0xff8738bc)

NSTUB(eventproc_export_OpLog_Show, 0xff877048)
NSTUB(eventproc_export_OpLog_Stop, 0xff8770e8)
NSTUB(eventproc_export_OpLog_WriteToROM, 0xff877114)

NSTUB(eventproc_export_OpLog_ReadFromROM, 0xff877170)
NSTUB(eventproc_export_OpLog_ReadFromSD, 0xff877210)
NSTUB(eventproc_export_OpLog_WriteToSD, 0xff8775dc)
NSTUB(eventproc_export_OpLog_Get, 0xff877a08)
NSTUB(eventproc_export_OpLog_Play, 0xff877a28)

NSTUB(eventproc_export_OpLog_Start, 0xff877ba8)

NSTUB(eventproc_export_StartWDT, 0xff878460)
NSTUB(eventproc_export_StopWDT, 0xff8784c4)

NSTUB(eventproc_export_GetBuildDate, 0xff8785b4)
NSTUB(eventproc_export_GetBuildTime, 0xff8785bc)
NSTUB(eventproc_export_GetFirmwareVersion, 0xff8785c4)

NSTUB(eventproc_export_CheckSumAll, 0xff8786d0)
NSTUB(eventproc_export_RomCheckSum, 0xff8788c8)

NSTUB(eventproc_export_CreateController, 0xff87e598)
NSTUB(eventproc_export_DeleteController, 0xff87e654)

NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff87e7d8)

NSTUB(eventproc_export_GetSelfControllerHandle, 0xff87e908)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff87ed3c)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff87ed88)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff87ee00)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff87ee5c)

NSTUB(eventproc_export_IsControlEventActive, 0xff880c60)
NSTUB(eventproc_export_UiEvnt_SetLogicalEventActive, 0xff880cd0)
NSTUB(eventproc_export_SetScriptMode, 0xff880d20)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff880d54)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff880d64)

NSTUB(eventproc_export_UnlockMainPower, 0xff880f64)
NSTUB(eventproc_export_LockMainPower, 0xff881010)
NSTUB(eventproc_export_SetAutoShutdownTime, 0xff881084)

NSTUB(eventproc_export_HardwareDefectWithRestart, 0xff88125c)
NSTUB(eventproc_export_HardwareDefect, 0xff8812ac)

NSTUB(eventproc_export_PTM_AllResetToFactorySetting, 0xff8814c0)
NSTUB(eventproc_export_PTM_AllReset, 0xff8814d0)

NSTUB(eventproc_export_PTM_SetCurrentCaptureMode, 0xff8817c8)

NSTUB(eventproc_export_PTM_GetWorkingCaptureMode, 0xff88187c)

NSTUB(eventproc_export_PTM_SetCurrentItem, 0xff881884)

NSTUB(eventproc_export_PTM_GetCurrentItem, 0xff881890)

NSTUB(eventproc_export_PTM_NextItem, 0xff8818fc)
NSTUB(eventproc_export_PTM_PrevItem, 0xff881900)

NSTUB(eventproc_export_PTM_IsEnableItem, 0xff881910)
NSTUB(eventproc_export_PTM_SetProprietyEnable, 0xff881914)

NSTUB(eventproc_export_PTM_BackupUIProperty, 0xff88192c)

NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff881934)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff888754)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff888790)

NSTUB(eventproc_export_StartGUISystem, 0xff89b6b0)

NSTUB(eventproc_export_atol, 0xff89b930)

NSTUB(eventproc_export_memcpy, 0xff89bb28)

NSTUB(eventproc_export_SetSDPwrPort, 0xff9483b0)
NSTUB(eventproc_export_GetAdVBattBottom, 0xff9483dc)
NSTUB(eventproc_export_GetAdChValue, 0xff9483e0)
NSTUB(eventproc_export_BeepDrive, 0xff9483e4)
NSTUB(eventproc_export_VbattGet, 0xff9483e8)
NSTUB(eventproc_export_LEDDrive, 0xff9483ec)
NSTUB(eventproc_export_ShowPhySwStatus, 0xff9483f0)
NSTUB(eventproc_export_SetRawSWCheckMode, 0xff948400)
NSTUB(eventproc_export_OnPrintPhySw, 0xff948410)
NSTUB(eventproc_export_OffPrintPhySw, 0xff948420)
NSTUB(eventproc_export_GetSwitchStatus, 0xff948430)
NSTUB(eventproc_export_ShowSDStatus, 0xff948434)
NSTUB(eventproc_export_GetSDDetect, 0xff948444)
NSTUB(eventproc_export_GetSDProtect, 0xff948448)
NSTUB(eventproc_export_SetIgnoreAVJACK, 0xff94844c)
NSTUB(eventproc_export_GetDialEventId, 0xff94845c)
NSTUB(eventproc_export_GetBatteryCoverClose, 0xff948460)

NSTUB(eventproc_export_MonSelEvent, 0xff94869c)
NSTUB(eventproc_export_MemoryChecker, 0xff9486a0)
NSTUB(eventproc_export_VerifyByte, 0xff9486a4)
NSTUB(eventproc_export_EraseSignature, 0xff9486a8)
NSTUB(eventproc_export_SDump, 0xff9486b8)
NSTUB(eventproc_export_Dump, 0xff9486bc)
NSTUB(eventproc_export_Dump32, 0xff9486cc)
NSTUB(eventproc_export_Poke32, 0xff9486e0)
NSTUB(eventproc_export_Poke16, 0xff9486f0)
NSTUB(eventproc_export_Poke8, 0xff948700)
NSTUB(eventproc_export_Peek32, 0xff948710)
NSTUB(eventproc_export_Peek16, 0xff948714)
NSTUB(eventproc_export_Peek8, 0xff948718)
NSTUB(eventproc_export_Wait, 0xff94871c)

NSTUB(eventproc_export_ShowAllTaskInfo, 0xff948730)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff949018)

NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff949124)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff949144)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff94917c)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff9491a4)
NSTUB(eventproc_export_UIFS_OpenPopupStrobe, 0xff9491c4)
NSTUB(eventproc_export_UIFS_ClosePopupStrobe, 0xff9491f4)
NSTUB(eventproc_export_UIFS_MountExtFlash, 0xff949224)
NSTUB(eventproc_export_UIFS_UnmountExtFlash, 0xff949254)
NSTUB(eventproc_export_UIFS_PressTeleButton, 0xff949284)
NSTUB(eventproc_export_UIFS_UnpressTeleButton, 0xff9492c0)
NSTUB(eventproc_export_UIFS_PressWideButton, 0xff9492f8)
NSTUB(eventproc_export_UIFS_UnpressWideButton, 0xff949334)
NSTUB(eventproc_export_UIFS_ConnectVideo, 0xff94936c)
NSTUB(eventproc_export_UIFS_DisconnectVideo, 0xff94939c)
NSTUB(eventproc_export_UIFS_MoveZoomTo, 0xff9493cc)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff9493d0)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff9493d4)
NSTUB(eventproc_export_UIFS_SetCaptureModeToTv, 0xff9493d8)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xff94940c)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xff949440)
NSTUB(eventproc_export_UIFS_SetCaptureModeToISO3200, 0xff949448)
NSTUB(eventproc_export_UIFS_PostModeDial, 0xff949468)
NSTUB(eventproc_export_UIFS_Capture, 0xff949490)
NSTUB(eventproc_export_UIFS_CaptureNoneStop, 0xff949494)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff949498)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff94949c)
NSTUB(eventproc_export_UIFS_StartClockMode, 0xff9494a0)
NSTUB(eventproc_export_UIFS_EndClockMode, 0xff9494b0)
NSTUB(eventproc_export_UIFS_StartRecordSound, 0xff9494c0)
NSTUB(eventproc_export_UIFS_StopRecordSound, 0xff9494c4)

NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff9494cc)
NSTUB(eventproc_export_UIFS_WriteFirmInfoToFile, 0xff9494d0)
NSTUB(eventproc_export_UIFS_GetMovieRecoadableNumber, 0xff9494d4)
NSTUB(eventproc_export_UIFS_GetStillShotableNumber, 0xff94951c)
NSTUB(eventproc_export_UIFS_ChangeShootState, 0xff949550)

NSTUB(eventproc_export_UIFS_ShootSeqToUI, 0xff949574)

NSTUB(eventproc_export_EraseLogSector, 0xff951964)

NSTUB(eventproc_export_WriteToRom, 0xff9520d4)
NSTUB(eventproc_export_EraseSectorOfRom, 0xff952184)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xff966ffc)

NSTUB(eventproc_export_ExecuteResetFactoryWithRomWrite, 0xff9757ec)

NSTUB(eventproc_export_memset, 0xff9df514)
NSTUB(eventproc_export_sscanf, 0xff9df590)

NSTUB(eventproc_export_StartDirectTransferManager, 0xffa8c250)

NSTUB(eventproc_export_StoptDtConfirmMenu, 0xffa8ce9c)

NSTUB(eventproc_export_StartDtConfirmMenu, 0xffa8cfe0)

NSTUB(eventproc_export_StoptDtExecuteMenu, 0xffaf12a8)

NSTUB(eventproc_export_StartDtExecuteMenu, 0xffaf1534)

