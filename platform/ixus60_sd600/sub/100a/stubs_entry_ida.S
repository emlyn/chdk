
NSTUB(eventproc_StopClockSaver, 0xff812ea4)
NSTUB(eventproc_SetLClk72MHz, 0xff812ec0)
NSTUB(eventproc_SetLClk36MHz, 0xff812ed0)
NSTUB(eventproc_SetLClk18MHz, 0xff812ee0)

NSTUB(eventproc_SetHClk72MHz, 0xff812f88)
NSTUB(eventproc_SetHClk36MHz, 0xff812fcc)
NSTUB(eventproc_SetHClk18MHz, 0xff812ff4)
NSTUB(eventproc_SetMClk72MHz, 0xff813038)
NSTUB(eventproc_SetMClk36MHz, 0xff81307c)
NSTUB(eventproc_SetMClk18MHz, 0xff8130a4)

NSTUB(eventproc_PutsCameraLogEvent, 0xff818054)
NSTUB(eventproc_ShowCameraLog, 0xff818200)

NSTUB(eventproc_StopCameraLog, 0xff8184e0)

NSTUB(eventproc_export_StartWDT, 0xff81a300)
NSTUB(eventproc_export_StopWDT, 0xff81a37c)

NSTUB(eventproc_export_GetBuildDate, 0xff81a4f0)
NSTUB(eventproc_export_GetBuildTime, 0xff81a508)
NSTUB(eventproc_export_GetFirmwareVersion, 0xff81a52c)

NSTUB(eventproc_export_RomCheckSum, 0xff81a614)
NSTUB(eventproc_export_CheckSumAll, 0xff81a6a8)
NSTUB(eventproc_SystemEventDelete, 0xff81a864)
NSTUB(eventproc_SystemEventInit, 0xff81a8a8)

NSTUB(eventproc_export_Dump32, 0xff81a970)
NSTUB(eventproc_FreeMemory, 0xff81aa84)
NSTUB(eventproc_AllocateMemory, 0xff81aa98)
NSTUB(eventproc_Wait, 0xff81aaa8)
NSTUB(eventproc_Poke32, 0xff81aabc)
NSTUB(eventproc_Poke16, 0xff81aae0)
NSTUB(eventproc_Poke8, 0xff81ab04)
NSTUB(eventproc_Peek32, 0xff81ab28)
NSTUB(eventproc_Peek16, 0xff81ab44)
NSTUB(eventproc_Peek8, 0xff81ab60)
NSTUB(eventproc_EraseSignature, 0xff81ab7c)
NSTUB(eventproc_GetSystemTime, 0xff81abac)
NSTUB(eventproc_MonSelEvent, 0xff81abcc)
NSTUB(eventproc_exec, 0xff81ac04)

NSTUB(eventproc_Driver_EnableEventProc, 0xff825ea4)

NSTUB(eventproc_ShowPhySwStatus, 0xff8273e8)
NSTUB(eventproc_OnPrintPhySw, 0xff8274dc)
NSTUB(eventproc_OffPrintPhySw, 0xff8274f4)
NSTUB(eventproc_GetSwitchStatus, 0xff827508)

NSTUB(eventproc_OnPrintHVSw, 0xff828538)
NSTUB(eventproc_OffPrintHVSw, 0xff828550)
NSTUB(eventproc_GetHVSw, 0xff828564)
NSTUB(eventproc_OnPrintHVStatus, 0xff828574)
NSTUB(eventproc_OffPrintHVStatus, 0xff828588)

NSTUB(eventproc_GetAdChValue, 0xff829994)
NSTUB(eventproc_GetAdVBattBottom, 0xff8299d4)

NSTUB(eventproc_SetBattCheckMode, 0xff82ab0c)
NSTUB(eventproc_ShowBattCheckMode, 0xff82ab94)
NSTUB(eventproc_ShowBattChkAdj, 0xff82ac40)
NSTUB(eventproc_GetLBOffset, 0xff82ae60)
NSTUB(eventproc_LowBat_Result_Print_On, 0xff82ae70)
NSTUB(eventproc_LowBat_Result_Print_Off, 0xff82ae88)
NSTUB(eventproc_BatVoltageToAd, 0xff82ae9c)

NSTUB(eventproc_VbattGet, 0xff82c1a0)

NSTUB(eventproc_GetOpticalTemperature, 0xff82d248)
NSTUB(eventproc_GetCCDTemperature, 0xff82d25c)
NSTUB(eventproc_GetBatteryTemperature, 0xff82d270)

NSTUB(eventproc_PrePro_Unpack, 0xff89dbc8)

NSTUB(eventproc_OutPort, 0xff8a0cec)
NSTUB(eventproc_InPort, 0xff8a0d00)

NSTUB(eventproc_ActivateImager, 0xff8ce4b0)
NSTUB(eventproc_QuietImager, 0xff8ce560)

NSTUB(eventproc_CancelImager, 0xff8ce7d0)
NSTUB(eventproc_ChangeImagerToWholeSerial, 0xff8ce800)
NSTUB(eventproc_ChangeImagerToWholeSerialLineDef, 0xff8ce818)
NSTUB(eventproc_ChangeImagerToWholeParallel, 0xff8ce830)
NSTUB(eventproc_ChangeImagerToWholeParallelHalf, 0xff8ce84c)
NSTUB(eventproc_ChangeImagerToSuperWideDraft, 0xff8ce85c)
NSTUB(eventproc_ChangeImagerToWideDraft, 0xff8ce86c)
NSTUB(eventproc_ChangeImagerToNarrowDraft, 0xff8ce87c)
NSTUB(eventproc_ChangeImagerToAlternateDraft, 0xff8ce88c)
NSTUB(eventproc_ChangeImagerToJetDraft, 0xff8ce89c)
NSTUB(eventproc_ChangeImagerToPetitNarrow, 0xff8ce8ac)
NSTUB(eventproc_ChangeImagerToFocusJet, 0xff8ce8bc)
NSTUB(eventproc_ChangeImagerToJumboDraft, 0xff8ce8cc)
NSTUB(eventproc_ChangeImagerToOITA_XAVIER, 0xff8ce8dc)
NSTUB(eventproc_ChangeImagerToQVGA20Fps, 0xff8ce8ec)
NSTUB(eventproc_ChangeImagerToQVGA15Fps, 0xff8ce8fc)
NSTUB(eventproc_ChangeImagerToSmearCorrectWide, 0xff8ce90c)
NSTUB(eventproc_ChangeImagerToSmearCorrectSuper, 0xff8ce91c)
NSTUB(eventproc_ChangeImagerToSmearCorrectAlternate, 0xff8ce92c)
NSTUB(eventproc_SetStartLineForNarrowDraft, 0xff8ce93c)
NSTUB(eventproc_WithdrawalImagerForEmergency, 0xff8ce950)
NSTUB(eventproc_StillOnMovieTest, 0xff8ce96c)
NSTUB(eventproc_SetSmearOn, 0xff8cea88)
NSTUB(eventproc_SetSmearOff, 0xff8cea9c)
NSTUB(eventproc_ChangeUseAf, 0xff8ceab0)

NSTUB(eventproc_VirtualHeadError, 0xff8d1424)

NSTUB(eventproc_export_EnableOBClampField, 0xff8d38a4)
NSTUB(eventproc_export_DisableOBClampField, 0xff8d38bc)

NSTUB(eventproc_export_VirtualImageTimeOut, 0xff8e29ec)

NSTUB(eventproc_EF_StartEFCharge, 0xff9134e4)
NSTUB(eventproc_EF_StopEFCharge, 0xff913544)
NSTUB(eventproc_EF_StartInternalPreFlash, 0xff913554)
NSTUB(eventproc_EF_StartInternalMainFlash, 0xff913598)
NSTUB(eventproc_EF_SetMainFlashTime, 0xff913624)
NSTUB(eventproc_EF_IsChargeFull, 0xff913638)

NSTUB(eventproc_ChangeGradeTable, 0xff930cc8)

NSTUB(eventproc_MakeDefData, 0xff930f8c)
NSTUB(eventproc_KizuMarkCheck, 0xff9310e4)
NSTUB(eventproc_GetDefectCount, 0xff93116c)
NSTUB(eventproc_RenewThermoLogNo, 0xff931190)

NSTUB(eventproc_DispDev_EnableEventProc, 0xff931b98)

NSTUB(eventproc_export_PT_EraseAllFile, 0xff9695bc)
NSTUB(eventproc_export_PT_mod, 0xff9695ec)
NSTUB(eventproc_export_PT_atoi, 0xff9695f8)
NSTUB(eventproc_export_PT_GetSystemTime, 0xff969604)
NSTUB(eventproc_export_PT_SetPropertyCaseString, 0xff969624)
NSTUB(eventproc_export_PT_SetPropertyCaseInt, 0xff969638)
NSTUB(eventproc_export_PT_GetPropertyCaseString, 0xff969660)
NSTUB(eventproc_export_PT_GetPropertyCaseInt, 0xff969674)
NSTUB(eventproc_export_PT_GetLocalTimeString, 0xff969720)
NSTUB(eventproc_export_PT_GetLocalDateString, 0xff96977c)
NSTUB(eventproc_export_PT_GetLocalDateAndTimeString, 0xff9697e0)
NSTUB(eventproc_export_PT_SetMessage, 0xff969830)
NSTUB(eventproc_export_PT_UndispMessage, 0xff969858)
NSTUB(eventproc_export_PT_PlaySound, 0xff969874)
NSTUB(eventproc_export_PT_LCD_BkColor, 0xff96988c)
NSTUB(eventproc_export_PT_LCD_BkColorDef, 0xff969948)
NSTUB(eventproc_export_PT_BatLvChange_PreWeak, 0xff96997c)
NSTUB(eventproc_export_PT_BatLvChange_Weak, 0xff969984)
NSTUB(eventproc_export_PT_BatLvChange_Low, 0xff96998c)
NSTUB(eventproc_export_PT_BatLvChange_SysLow, 0xff969994)
NSTUB(eventproc_export_PT_StartBatteryTest, 0xff9699ac)
NSTUB(eventproc_export_PT_FinishBatteryTest, 0xff969a0c)

NSTUB(eventproc_export_PT_GetBatteryLevel, 0xff969b04)
NSTUB(eventproc_export_PT_GetPreWeakBatLv, 0xff969b1c)
NSTUB(eventproc_export_PT_GetWeakBatLv, 0xff969b74)
NSTUB(eventproc_export_PT_GetLowBatLv, 0xff969bcc)
NSTUB(eventproc_export_PT_GetSysLowBatLv, 0xff969c24)
NSTUB(eventproc_export_UiMemory_Show, 0xff969c8c)

NSTUB(eventproc_export_HardwareDefect, 0xff969eb0)

NSTUB(eventproc_ShowErrorNumberList, 0xff969f40)

NSTUB(eventproc_export_CreateController, 0xff96b05c)
NSTUB(eventproc_export_DeleteController, 0xff96b114)
NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff96b24c)
NSTUB(eventproc_export_GetSelfControllerHandle, 0xff96b384)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff96e370)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff96e3ec)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff96e474)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff96e4dc)

NSTUB(eventproc_export_LogiEvnt_LoadCameraLog, 0xff96e624)

NSTUB(eventproc_export_IsControlEventActive, 0xff9700ac)

NSTUB(eventproc_export_SetScriptMode, 0xff9701a0)
NSTUB(eventproc_export_UiEvnt_ShowBitMaps, 0xff9701b0)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff970210)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff970224)

NSTUB(eventproc_export_IsDisableAutoShutdown, 0xff971f04)

NSTUB(eventproc_export_ShowAutoShutdownTime, 0xff971fd8)
NSTUB(eventproc_export_DisableAutoShutdown, 0xff97200c)
NSTUB(eventproc_export_EnableAutoShutdown, 0xff972024)

NSTUB(eventproc_export_SetAutoShutdownTime, 0xff9722b8)
NSTUB(eventproc_export_LockMainPower, 0xff9723b4)
NSTUB(eventproc_export_UnlockMainPower, 0xff97244c)
NSTUB(eventproc_export_GetMainPowerLockCounter, 0xff972550)

NSTUB(eventproc_PTM_AllResetToFactorySetting, 0xff974d88)
NSTUB(eventproc_PTM_AllResetProperty, 0xff974d98)

NSTUB(eventproc_PTM_GetWorkingCaptureMode, 0xff974fd0)

NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff975364)

NSTUB(eventproc_PTM_SetCurrentCaptureMode, 0xff975a6c)
NSTUB(eventproc_PTM_SetCurrentItem, 0xff975a7c)
NSTUB(eventproc_PTM_GetCurrentItem, 0xff975a9c)
NSTUB(eventproc_PTM_NextItem, 0xff975ab4)
NSTUB(eventproc_PTM_PrevItem, 0xff975acc)
NSTUB(eventproc_PTM_BackupUIProperty, 0xff975ae4)
NSTUB(eventproc_PTM_SetProprietyEnable, 0xff975b08)

NSTUB(eventproc_export_CreateDialogBox, 0xff97c1cc)
NSTUB(eventproc_export_DeleteDialogBox, 0xff97c3dc)
NSTUB(eventproc_export_ResizeVirtualWindow, 0xff97c498)
NSTUB(eventproc_export_MoveDialogBoxPosition, 0xff97c4c4)
NSTUB(eventproc_export_DeleteDialogBoxAfterGetTopOfControl, 0xff97c564)
NSTUB(eventproc_export_SetPropertyToDialogItemWithID, 0xff97c588)
NSTUB(eventproc_export_GetPropertyFromDialogItemWithID, 0xff97c5b8)

NSTUB(eventproc_export_AddItemToDialogBox, 0xff97c650)
NSTUB(eventproc_export_DeleteItemFromDialogBox, 0xff97c724)
NSTUB(eventproc_export_SetFocusDirectionToDialogItem, 0xff97c810)
NSTUB(eventproc_export_SetFocusItemToDialogItem, 0xff97ca14)
NSTUB(eventproc_export_GetFocusedItemIDOfDialogItem, 0xff97cb28)
NSTUB(eventproc_export_GetItemHandleOfDialogBox, 0xff97cb60)
NSTUB(eventproc_export_DisplayDialogBox, 0xff97cc00)
NSTUB(eventproc_export_UndisplayDialogBox, 0xff97cc28)
NSTUB(eventproc_export_SetBackgroundColorToDialogBox, 0xff97cc50)
NSTUB(eventproc_export_RefreshRectangleToDialog, 0xff97cca4)

NSTUB(eventproc_export_RegisterRefreshToDialog, 0xff97cd2c)
NSTUB(eventproc_export_RefreshRegistedRectangleToDialog, 0xff97cdf0)
NSTUB(eventproc_export_FillRectangleToDialog, 0xff97ce64)
NSTUB(eventproc_export_DrawStringToDialog, 0xff97cec4)
NSTUB(eventproc_export_TransferRectangleToDialog, 0xff97cf24)
NSTUB(eventproc_export_TransferBitmapToDialog, 0xff97cf94)
NSTUB(eventproc_export_DrawBinaryBitmapToDialog, 0xff97d014)
NSTUB(eventproc_export_GetDialogBoxWindow, 0xff97d07c)
NSTUB(eventproc_export_SetFocusScopeToDialog, 0xff97d09c)
NSTUB(eventproc_export_GetFocusScopeToDialog, 0xff97d10c)
NSTUB(eventproc_export_MoveViewPortPosition, 0xff97d158)
NSTUB(eventproc_export_ResizeDialogBox, 0xff97d1bc)
NSTUB(eventproc_export_MoveDialogControllerToTopOfZOrder, 0xff97d208)
NSTUB(eventproc_export_RegisterChangeLanguageToDialog, 0xff97d22c)
NSTUB(eventproc_export_UnregisterChangeLanguageToDialog, 0xff97d274)
NSTUB(eventproc_export_MoveDialogItemPositionToDialog, 0xff97d2b0)
NSTUB(eventproc_export_ResizeDialogItemToDialog, 0xff97d2e4)
NSTUB(eventproc_export_GetDialogItemPositionToDialog, 0xff97d318)
NSTUB(eventproc_export_GetDialogItemResolutionToDialog, 0xff97d34c)
NSTUB(eventproc_export_SetOriginTypeToDialog, 0xff97d380)
NSTUB(eventproc_export_SetDefaultMovingFocusToDialog, 0xff97d3a4)
NSTUB(eventproc_export_LockRefreshDialog, 0xff97d3c8)
NSTUB(eventproc_export_UnlockRefreshDialog, 0xff97d40c)

NSTUB(eventproc_export_KeepDefaultMoveFocusEventToDialog, 0xff97d4cc)

NSTUB(eventproc_export_InstallDialogItem, 0xff97d89c)
NSTUB(eventproc_export_CreateDialogItem, 0xff97d978)
NSTUB(eventproc_export_DeleteDialogItem, 0xff97da68)
NSTUB(eventproc_export_DrawDialogItem, 0xff97dae8)
NSTUB(eventproc_export_ControlEventHandler, 0xff97db80)
NSTUB(eventproc_export_SetPropertyToDialogItem, 0xff97dbfc)
NSTUB(eventproc_export_GetPropertyFromDialogItem, 0xff97dc70)
NSTUB(eventproc_export_SetAttributeToDialogItem, 0xff97dce4)
NSTUB(eventproc_export_GetAttributeFromDialogItem, 0xff97dd58)
NSTUB(eventproc_export_MoveDialogItemPosition, 0xff97ddc4)
NSTUB(eventproc_export_ResizeDialogItem, 0xff97de38)
NSTUB(eventproc_export_GetDialogItemPosition, 0xff97deb8)
NSTUB(eventproc_export_GetDialogItemResolution, 0xff97df38)

NSTUB(eventproc_export_StartGUISystem, 0xff9812c8)

NSTUB(eventproc_ShutdownGUISystem, 0xff9813ec)

NSTUB(eventproc_export_DeletePalette, 0xff9816b0)
NSTUB(eventproc_export_SetYUVPaletteIndex, 0xff981728)

NSTUB(eventproc_export_SetPaletteToPhysicalScreen, 0xff981868)
NSTUB(eventproc_export_GetPaletteFromPhysicalScreen, 0xff9818c0)

NSTUB(eventproc_export_SetCurrentPalette, 0xff984818)
NSTUB(eventproc_export_SetSystemColorMode, 0xff984828)

NSTUB(eventproc_export_LockPhysicalScreen, 0xff9890dc)
NSTUB(eventproc_export_RefreshPhysicalScreen, 0xff989170)
NSTUB(eventproc_export_EnableRefreshPhysicalScreen, 0xff989244)
NSTUB(eventproc_export_DisableRefreshPhysicalScreen, 0xff989258)
NSTUB(eventproc_export_IsEnableRefreshPhysicalScreen, 0xff98926c)

NSTUB(eventproc_export_PrintBmpVramInfo, 0xff989b80)
NSTUB(eventproc_export_PrintCurrPalette, 0xff989bb4)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff998730)
NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff998748)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff998788)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff9987c8)
NSTUB(eventproc_export_ModeLevelStillRecForScript, 0xff998808)
NSTUB(eventproc_export_ModeLevelMovieRecForScript, 0xff998814)
NSTUB(eventproc_export_ModeLevelPlayForScript, 0xff998820)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff99882c)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff998838)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff998844)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xff998858)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xff99886c)
NSTUB(eventproc_export_UIFS_Capture, 0xff998880)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff998890)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff99889c)
NSTUB(eventproc_export_UIFS_PCaseToPTMID, 0xff9988d4)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff998934)
NSTUB(eventproc_UI_RegistDebugEventProc, 0xff998c40)

NSTUB(eventproc_ExecuteResetFactoryWithRomWrite, 0xff99e5e8)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff9a34b0)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff9a3500)

NSTUB(eventproc_export_ShootCon_GetStatus, 0xff9a6aa8)

NSTUB(eventproc_export_ShootCon_ShowState, 0xff9aa8ac)

NSTUB(eventproc_export_ShootCon_SetEventHook, 0xff9ab32c)
NSTUB(eventproc_export_ShootCon_PrintMemoryDump, 0xff9ab358)
NSTUB(eventproc_export_ShootCon_ShowAllSemaphores, 0xff9ab3e4)

NSTUB(eventproc_StartMovieController, 0xff9ac284)
NSTUB(eventproc_EnableMovieController, 0xff9ac2ec)
NSTUB(eventproc_DisableMovieController, 0xff9ac300)
NSTUB(eventproc_ShutdownMovieController, 0xff9ac314)

NSTUB(eventproc_GetStateOfMovieSequence, 0xff9ad248)

NSTUB(eventproc_ZoomCon_ShowState, 0xff9afc6c)

NSTUB(eventproc_export_StartSwitchViewFinder, 0xff9ba150)
NSTUB(eventproc_export_StopSwitchViewFinder, 0xff9ba1a4)
NSTUB(eventproc_export_SwitchViewFinder, 0xff9ba1d0)

NSTUB(eventproc_export_UiComIF_SendEventToUI, 0xff9bb960)

NSTUB(eventproc_DeletePlayMyColController, 0xff9f3628)

NSTUB(eventproc_TerminateDpofUI, 0xffa018c4)

NSTUB(eventproc_StartPrintOrderMenu, 0xffa02a0c)

NSTUB(eventproc_StartDpofPlayLoading, 0xffa06f84)

NSTUB(eventproc_SyncStopDpofPlayLoading, 0xffa07168)

NSTUB(eventproc_StartTransferOrderMenu, 0xffa077e0)

NSTUB(eventproc_StartPlayModeMenu, 0xffa0a7fc)

NSTUB(eventproc_StartRecModeMenu, 0xffa0a8d0)
NSTUB(eventproc_ShutdownRecModeMenu, 0xffa0a994)

NSTUB(eventproc_ShutdownPlayModeMenu, 0xffa0ab1c)
NSTUB(eventproc_ShutdownPlayModeMenuWithoutPbRedraw, 0xffa0abc8)

NSTUB(eventproc_InstallRecMenu, 0xffa0cc18)

NSTUB(eventproc_InstallPlayMenu, 0xffa0f2f4)

NSTUB(eventproc_InstallSetupMenu, 0xffa11874)

NSTUB(eventproc_InstallMyCameraMenu, 0xffa1483c)

NSTUB(eventproc_IsCalledStopEVF, 0xffa1589c)

NSTUB(eventproc_ShutdownRecAllMenu, 0xffa16068)
NSTUB(eventproc_ShutdownPlayAllMenu, 0xffa160e0)

NSTUB(eventproc_export_StartFirmInfoMenu, 0xffa1ce88)

NSTUB(eventproc_ShowLanguageNameList, 0xffa1fd04)
NSTUB(eventproc_SaveLanguageNameList, 0xffa1fd40)
NSTUB(eventproc_RegisterLanguageName, 0xffa1fd44)

NSTUB(eventproc_CreateLanguageMenu, 0xffa20900)
NSTUB(eventproc_DeleteLanguageMenu, 0xffa20aa8)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xffa22ef4)

NSTUB(eventproc_export_StartDirectTransferManager, 0xffa28950)

NSTUB(eventproc_export_StoptDtConfirmMenu, 0xffa29220)

NSTUB(eventproc_export_StoptDtExecuteMenu, 0xffa29c7c)

NSTUB(eventproc_StartDpConnect, 0xffa2d318)

NSTUB(eventproc_StopDpConnect, 0xffa2d5a0)

NSTUB(eventproc_CreateDpConnectController, 0xffa2d938)
NSTUB(eventproc_DeleteDpConnectController, 0xffa2dbcc)
NSTUB(eventproc_shutdownDirectPrintUI, 0xffa2dca0)

NSTUB(eventproc_StartDpDpofMenu, 0xffa2f7f0)

NSTUB(eventproc_StartDpMainMenu, 0xffa35878)

NSTUB(eventproc_StartDpPrinting, 0xffa3746c)

NSTUB(eventproc_StartDpsDpofMenu, 0xffa38958)

NSTUB(eventproc_StartDpsMainMenu, 0xffa3eb64)

NSTUB(eventproc_StartDpsStop, 0xffa45054)

NSTUB(eventproc_StartDpStopReconfirm, 0xffa46380)

NSTUB(eventproc_StartDpStyleMenu, 0xffa48614)

NSTUB(eventproc_StartDpTrimming, 0xffa4c780)

NSTUB(eventproc_DBG_changeTraceLevel, 0xffa4e608)

NSTUB(eventproc_StartDpMovieMenu, 0xffa4e800)

NSTUB(eventproc_ControlViewEvent, 0xffa55f40)

NSTUB(eventproc_InstallPrintMenu, 0xffa621b4)

NSTUB(eventproc_DisableNotificationPTP, 0xffa6872c)
NSTUB(eventproc_EnableNotificationPTP, 0xffa68740)
NSTUB(eventproc_SetUSBToPTPMode, 0xffa68758)
NSTUB(eventproc_SetUSBToDCPMode, 0xffa6876c)
NSTUB(eventproc_RefreshUSBMode, 0xffa68784)
NSTUB(eventproc_NotifyConnectPictBridge, 0xffa68808)
NSTUB(eventproc_NotifyDisconnectPictBridge, 0xffa68828)

NSTUB(eventproc_PTPRspnd_ShowRemoteStg, 0xffa8a0ec)

NSTUB(eventproc_CreateVcomUart, 0xffa9de58)
NSTUB(eventproc_DeleteVcomUart, 0xffa9df88)

NSTUB(eventproc_RegComEventProc, 0xffa9e9a0)

NSTUB(eventproc_MechaReset, 0xffa9eb6c)
NSTUB(eventproc_MechaTerminate, 0xffa9eba4)
NSTUB(eventproc_ShowMechaMacro, 0xffa9ec18)

NSTUB(eventproc_EnableMechaCircuit, 0xffaa1fa8)
NSTUB(eventproc_DisableMechaCircuit, 0xffaa1fb8)
NSTUB(eventproc_EnableFocusPiCircuit, 0xffaa1fc8)
NSTUB(eventproc_DisableFocusPiCircuit, 0xffaa1fd8)
NSTUB(eventproc_GetFocusPiSensorLevel, 0xffaa1fe8)
NSTUB(eventproc_EnableZoomPiCircuit, 0xffaa2000)
NSTUB(eventproc_DisableZoomPiCircuit, 0xffaa2010)
NSTUB(eventproc_GetZoomPiSensorLevel, 0xffaa2020)
NSTUB(eventproc_EnableZoomEncoderCircuit, 0xffaa2038)
NSTUB(eventproc_DisableZoomEncoderCircuit, 0xffaa2048)
NSTUB(eventproc_SendMechaCircuitData, 0xffaa2058)
NSTUB(eventproc_ReceiveMechaCircuitDataAll, 0xffaa2098)

NSTUB(eventproc_MoveLensToFirstPointEvent, 0xffaa4be4)
NSTUB(eventproc_MoveLensToTerminatePointEvent, 0xffaa4c5c)
NSTUB(eventproc_PermitLensControllerFocusReset, 0xffaa4cac)
NSTUB(eventproc_PermitLensControllerFocusInfinity, 0xffaa4cbc)
NSTUB(eventproc_IsLensOutside, 0xffaa4ccc)
NSTUB(eventproc_GetLensErrorStatus, 0xffaa4cd8)

NSTUB(eventproc_ResetZoomLens, 0xffaa629c)
NSTUB(eventproc_ResetZoomLensToFirstPoint, 0xffaa62cc)
NSTUB(eventproc_ResetZoomLensToTermiantePoint, 0xffaa6340)
NSTUB(eventproc_MoveZoomLensWithPoint, 0xffaa63b4)
NSTUB(eventproc_MoveZoomLensWithPosition, 0xffaa6430)
NSTUB(eventproc_MoveZoomLensToTerminatePosition, 0xffaa6484)
NSTUB(eventproc_GetZoomLensCurrentPoint, 0xffaa64d4)
NSTUB(eventproc_GetZoomLensCurrentPosition, 0xffaa64e8)
NSTUB(eventproc_GetZoomLensTelePoint, 0xffaa64fc)

NSTUB(eventproc_SetZoomLensNormalControlGain, 0xffaa7ba8)

NSTUB(eventproc_SetZoomLensResetControlGain, 0xffaa9480)

NSTUB(eventproc_MoveZoomActuator, 0xffaabf28)
NSTUB(eventproc_SetZoomActuatorSpeedPPS, 0xffaabf74)
NSTUB(eventproc_GetZoomActuatorSpeedPPS, 0xffaabf88)
NSTUB(eventproc_SetZoomActuatorSpeedControlGain, 0xffaabf9c)
NSTUB(eventproc_GetZoomActuatorSpeedControlGain, 0xffaabfb0)
NSTUB(eventproc_SetZoomActuatorLimitAmpere, 0xffaabfc4)
NSTUB(eventproc_GetZoomActuatorLimitAmpere, 0xffaabfd8)
NSTUB(eventproc_SetZoomActuatorPwmDuty, 0xffaabfec)
NSTUB(eventproc_SetZoomActuatorPwmFixedTime, 0xffaac000)
NSTUB(eventproc_GetZoomActuatorCurrentPosition, 0xffaac014)
NSTUB(eventproc_IsZoomActuatorResetSensorPlusSide, 0xffaac060)
NSTUB(eventproc_SetDCMotorSpeedLevel, 0xffaac06c)
NSTUB(eventproc_SetDCMotorChargePump, 0xffaac080)
NSTUB(eventproc_SetDCMotorPwmFixedTimeLevel, 0xffaac094)
NSTUB(eventproc_SetDCMotorPwmLevel, 0xffaac0a8)
NSTUB(eventproc_SetPM3ByGpio, 0xffaac0bc)
NSTUB(eventproc_ClearPM3ByGpio, 0xffaac0cc)
NSTUB(eventproc_ClearPM3ByFs, 0xffaac0dc)
NSTUB(eventproc_MoveDCMotorCW, 0xffaac0ec)
NSTUB(eventproc_MoveDCMotorCCW, 0xffaac148)
NSTUB(eventproc_StopDCMotor, 0xffaac1a4)
NSTUB(eventproc_SetDCMotorWaitTime, 0xffaac1c4)
NSTUB(eventproc_GetCurrentEncoderPosition, 0xffaac1dc)

NSTUB(eventproc_ResetIrisEvent, 0xffaad304)
NSTUB(eventproc_MoveIrisWithAvEvent, 0xffaad334)
NSTUB(eventproc_MoveIrisToTerminatePositionEvent, 0xffaad368)
NSTUB(eventproc_GetIrisAvEvent, 0xffaad370)
NSTUB(eventproc_MoveIrisWithAvWithoutBacklashEvent, 0xffaad384)

NSTUB(eventproc_CloseMechaShutterEvent, 0xffaae6c0)
NSTUB(eventproc_OpenMechaShutterEvent, 0xffaae6f0)
NSTUB(eventproc_CloseMechaShutterWithTimingEvent, 0xffaae720)
NSTUB(eventproc_SetMechaShutterDacSettingEvent, 0xffaae764)
NSTUB(eventproc_SetMechaShutterOpenDacSettingEvent, 0xffaae778)
NSTUB(eventproc_SetMechaShutterFinalDacSettingEvent, 0xffaae78c)
NSTUB(eventproc_SetMechaShutterOpenFinalDacSettingEvent, 0xffaae7a0)
NSTUB(eventproc_SetMechaShutterWaitTimeSettingEvent, 0xffaae7b4)
NSTUB(eventproc_GetMechaShutterStatusEvent, 0xffaae7c8)
NSTUB(eventproc_SaveMechaShutterCount, 0xffaae7d4)
NSTUB(eventproc_GetMechaShutterCount, 0xffaae810)
NSTUB(eventproc_ClearMechaShutterCount, 0xffaae860)

NSTUB(eventproc_TurnOnNdFilterEvent, 0xffaaf134)
NSTUB(eventproc_TurnOffNdFilterEvent, 0xffaaf164)
NSTUB(eventproc_SetNdFilterDacSettingEvent, 0xffaaf194)

NSTUB(eventproc_MoveFocusLensWithDistance, 0xffab6b7c)
NSTUB(eventproc_ResetFocusLens, 0xffab6c48)
NSTUB(eventproc_MoveFocusLensToTerminate, 0xffab6ca8)
NSTUB(eventproc_MoveFocusLensWithPosition, 0xffab6d1c)
NSTUB(eventproc_MoveFocusLensWithPositionWithoutBacklash, 0xffab6dec)
NSTUB(eventproc_MoveFocusActuator, 0xffab6ebc)
NSTUB(eventproc_GetFocusLensCurrentPosition, 0xffab6f78)
NSTUB(eventproc_GetFocusLensResetPosition, 0xffab6f8c)
NSTUB(eventproc_GetFocusLensResetPositionForInside, 0xffab6fa0)
NSTUB(eventproc_GetFocusLensResetPositionForOutside, 0xffab6fb4)
NSTUB(eventproc_GetFocusLensResetDefaultPosition, 0xffab6fc8)
NSTUB(eventproc_SetFocusLensDefaultCondition, 0xffab6fdc)
NSTUB(eventproc_SetFocusLensCondition, 0xffab6ff4)
NSTUB(eventproc_GetFocusLensMoveCompleteTime, 0xffab70e8)
NSTUB(eventproc_GetFocusLensNdCoefficientPulse, 0xffab70f4)
NSTUB(eventproc_GetFocusLensSettingMaxSpeed, 0xffab7108)
NSTUB(eventproc_GetFocusLensSettingMaxSpeedByDeltaType, 0xffab711c)
NSTUB(eventproc_SetFocusLensMaxSpeedLimit, 0xffab7130)
NSTUB(eventproc_CancelFocusLensMaxSpeedLimit, 0xffab7148)
NSTUB(eventproc_EscapeFocusLens, 0xffab715c)
NSTUB(eventproc_GetFocusLensSubjectDistance, 0xffab71f0)
NSTUB(eventproc_GetFocusLensSubjectDistanceFromLens, 0xffab7214)
NSTUB(eventproc_EnableFocusLens, 0xffab7238)
NSTUB(eventproc_SetFocusLensBacklashSpeedToMax, 0xffab729c)
NSTUB(eventproc_ClearFocusLensBacklashSpeedToMax, 0xffab72ac)
NSTUB(eventproc_CheckFocusLensAfAging, 0xffab734c)

NSTUB(eventproc_MoveCZToPointEvent, 0xffab92cc)
NSTUB(eventproc_MoveCZToWideEvent, 0xffab9320)
NSTUB(eventproc_MoveCZToTeleEvent, 0xffab9368)

NSTUB(eventproc_TurnOnAFLampEvent, 0xffab9560)
NSTUB(eventproc_TurnOffAFLampEvent, 0xffab9578)

NSTUB(eventproc_FA_Create, 0xffabc6e8)
NSTUB(eventproc_FA_Delete, 0xffabc71c)

NSTUB(eventproc_InitializeAdjustmentSystem, 0xffabd28c)
NSTUB(eventproc_TerminateAdjustmentSystem, 0xffabd2d4)
NSTUB(eventproc_InitializeAdjustmentFunction, 0xffabd31c)

NSTUB(eventproc_MakeBootDisk, 0xffaebec8)
NSTUB(eventproc_MakeScriptDisk, 0xffaebedc)

NSTUB(eventproc_LoadScript, 0xffaed930)
NSTUB(eventproc_UnLoadScript, 0xffaed940)
NSTUB(eventproc_Printf, 0xffaed954)
NSTUB(eventproc_ScriptDisEnabled, 0xffaed96c)
NSTUB(eventproc_ScriptEnabled, 0xffaed980)

NSTUB(eventproc_GetLogToFile, 0xffaf5d28)

NSTUB(eventproc_MemoryChecker, 0xffaf70ac)
NSTUB(eventproc_VerifyByte, 0xffaf71dc)

