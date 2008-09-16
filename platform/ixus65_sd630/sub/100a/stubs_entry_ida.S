
NSTUB(eventproc_printclock, 0xff812e24)
NSTUB(eventproc_StopClockSaver, 0xff812f28)
NSTUB(eventproc_SetLClk72MHz, 0xff812f44)
NSTUB(eventproc_SetLClk36MHz, 0xff812f54)
NSTUB(eventproc_SetLClk18MHz, 0xff812f64)

NSTUB(eventproc_SetHClk72MHz, 0xff81300c)
NSTUB(eventproc_SetHClk36MHz, 0xff813050)
NSTUB(eventproc_SetHClk18MHz, 0xff813078)
NSTUB(eventproc_SetMClk72MHz, 0xff8130bc)
NSTUB(eventproc_SetMClk36MHz, 0xff813100)
NSTUB(eventproc_SetMClk18MHz, 0xff813128)

NSTUB(eventproc_export_ExecuteEventProcedure, 0xff816bc8)

NSTUB(eventproc_export_ExportToEventProcedure, 0xff816db0)
NSTUB(eventproc_CreateProxyOfEventProcedure, 0xff817548)
NSTUB(eventproc_DeleteProxyOfEventProcedure, 0xff8175d0)

NSTUB(eventproc_PutsCameraLogEvent, 0xff8180d8)
NSTUB(eventproc_ShowCameraLogInfo, 0xff8181e0)
NSTUB(eventproc_ShowCameraLog, 0xff818284)

NSTUB(eventproc_StartCameraLog, 0xff818470)
NSTUB(eventproc_StopCameraLog, 0xff818564)

NSTUB(eventproc_export_StartWDT, 0xff81a384)
NSTUB(eventproc_export_StopWDT, 0xff81a400)

NSTUB(eventproc_export_GetBuildDate, 0xff81a574)
NSTUB(eventproc_export_GetBuildTime, 0xff81a58c)
NSTUB(eventproc_export_GetFirmwareVersion, 0xff81a5b0)

NSTUB(eventproc_export_RomCheckSum, 0xff81a698)
NSTUB(eventproc_export_CheckSumAll, 0xff81a72c)
NSTUB(eventproc_SystemEventDelete, 0xff81a8e8)
NSTUB(eventproc_SystemEventInit, 0xff81a92c)

NSTUB(eventproc_export_Dump32, 0xff81a9f4)
NSTUB(eventproc_FreeMemory, 0xff81ab08)
NSTUB(eventproc_AllocateMemory, 0xff81ab1c)
NSTUB(eventproc_Wait, 0xff81ab2c)
NSTUB(eventproc_Poke32, 0xff81ab40)
NSTUB(eventproc_Poke16, 0xff81ab64)
NSTUB(eventproc_Poke8, 0xff81ab88)
NSTUB(eventproc_Peek32, 0xff81abac)
NSTUB(eventproc_Peek16, 0xff81abc8)
NSTUB(eventproc_Peek8, 0xff81abe4)
NSTUB(eventproc_EraseSignature, 0xff81ac00)
NSTUB(eventproc_GetSystemTime, 0xff81ac30)
NSTUB(eventproc_MonSelEvent, 0xff81ac50)
NSTUB(eventproc_exec, 0xff81ac88)

NSTUB(eventproc_Driver_EnableEventProc, 0xff825f2c)

NSTUB(eventproc_ShowPhySwStatus, 0xff827470)
NSTUB(eventproc_OnPrintPhySw, 0xff827564)
NSTUB(eventproc_OffPrintPhySw, 0xff82757c)
NSTUB(eventproc_GetSwitchStatus, 0xff827590)

NSTUB(eventproc_OffPrintHVSw, 0xff828668)
NSTUB(eventproc_GetHVSw, 0xff82867c)
NSTUB(eventproc_OnPrintHVStatus, 0xff82868c)
NSTUB(eventproc_OffPrintHVStatus, 0xff8286a0)

NSTUB(eventproc_SetFeatherDivision, 0xff829a78)
NSTUB(eventproc_SetFeatherInterval, 0xff829aa0)
NSTUB(eventproc_OnPrintFeather, 0xff829ab4)
NSTUB(eventproc_OffPrintFeather, 0xff829acc)
NSTUB(eventproc_SetFeatherPrintInterval, 0xff829ae0)

NSTUB(eventproc_GetAdChValue, 0xff82a918)
NSTUB(eventproc_GetAdVBattBottom, 0xff82a958)

NSTUB(eventproc_SetBattCheckMode, 0xff82ba90)
NSTUB(eventproc_ShowBattCheckMode, 0xff82bb18)
NSTUB(eventproc_ShowBattChkAdj, 0xff82bbc4)
NSTUB(eventproc_GetLBOffset, 0xff82bde4)
NSTUB(eventproc_LowBat_Result_Print_On, 0xff82bdf4)
NSTUB(eventproc_LowBat_Result_Print_Off, 0xff82be0c)
NSTUB(eventproc_BatVoltageToAd, 0xff82be20)

NSTUB(eventproc_VbattGet, 0xff82d154)

NSTUB(eventproc_CalculateBatSenseOffset, 0xff82d4ec)

NSTUB(eventproc_ExecuteLoadTest, 0xff82d800)
NSTUB(eventproc_TurnOn_LoadTest_DebugMode, 0xff82d810)
NSTUB(eventproc_TurnOff_LoadTest_DebugMode, 0xff82d824)
NSTUB(eventproc_LoadTest_Result_Print_On, 0xff82d838)
NSTUB(eventproc_LoadTest_Result_Print_Off, 0xff82d84c)

NSTUB(eventproc_LEDDrive, 0xff82e778)
NSTUB(eventproc_AFAssistBeam, 0xff82e7c4)
NSTUB(eventproc_PostLEDMessage, 0xff82e7e4)

NSTUB(eventproc_BeepDrive, 0xff82f22c)
NSTUB(eventproc_BeepDriveComp, 0xff82f240)

NSTUB(eventproc_TurnOnVideoOutMode, 0xff82fa54)
NSTUB(eventproc_TurnOffVideoOutMode, 0xff82faa4)

NSTUB(eventproc_PrePro_Unpack, 0xff89ea3c)

NSTUB(eventproc_Capture_Create, 0xff8a1ba0)

NSTUB(eventproc_ActivateImager, 0xff8cf31c)
NSTUB(eventproc_QuietImager, 0xff8cf3cc)

NSTUB(eventproc_CancelImager, 0xff8cf63c)
NSTUB(eventproc_ChangeImagerToWholeSerial, 0xff8cf66c)
NSTUB(eventproc_ChangeImagerToWholeSerialLineDef, 0xff8cf684)
NSTUB(eventproc_ChangeImagerToWholeParallel, 0xff8cf69c)
NSTUB(eventproc_ChangeImagerToWholeParallelHalf, 0xff8cf6b8)
NSTUB(eventproc_ChangeImagerToSuperWideDraft, 0xff8cf6c8)
NSTUB(eventproc_ChangeImagerToWideDraft, 0xff8cf6d8)
NSTUB(eventproc_ChangeImagerToNarrowDraft, 0xff8cf6e8)
NSTUB(eventproc_ChangeImagerToAlternateDraft, 0xff8cf6f8)
NSTUB(eventproc_ChangeImagerToJetDraft, 0xff8cf708)
NSTUB(eventproc_ChangeImagerToPetitNarrow, 0xff8cf718)
NSTUB(eventproc_ChangeImagerToFocusJet, 0xff8cf728)
NSTUB(eventproc_ChangeImagerToJumboDraft, 0xff8cf738)
NSTUB(eventproc_ChangeImagerToDigiconMode, 0xff8cf748)
NSTUB(eventproc_ChangeImagerToQVGA20Fps, 0xff8cf758)
NSTUB(eventproc_ChangeImagerToQVGA15Fps, 0xff8cf768)
NSTUB(eventproc_ChangeImagerToSmearCorrectWide, 0xff8cf778)
NSTUB(eventproc_ChangeImagerToSmearCorrectSuper, 0xff8cf788)
NSTUB(eventproc_ChangeImagerToSmearCorrectAlternate, 0xff8cf798)
NSTUB(eventproc_SetStartLineForNarrowDraft, 0xff8cf7a8)
NSTUB(eventproc_WithdrawalImagerForEmergency, 0xff8cf7bc)
NSTUB(eventproc_StillOnMovieTest, 0xff8cf7d8)
NSTUB(eventproc_SetSmearOn, 0xff8cf8f4)
NSTUB(eventproc_SetSmearOff, 0xff8cf908)

NSTUB(eventproc_VirtualHeadError, 0xff8d2290)

NSTUB(eventproc_export_EnableOBClampField, 0xff8d4710)
NSTUB(eventproc_export_DisableOBClampField, 0xff8d4728)

NSTUB(eventproc_export_VirtualImageTimeOut, 0xff8e3858)

NSTUB(eventproc_EF_StartEFCharge, 0xff914298)
NSTUB(eventproc_EF_StopEFCharge, 0xff9142f8)
NSTUB(eventproc_EF_StartInternalPreFlash, 0xff914308)
NSTUB(eventproc_EF_StartInternalMainFlash, 0xff91434c)
NSTUB(eventproc_EF_SetMainFlashTime, 0xff9143d8)
NSTUB(eventproc_EF_IsChargeFull, 0xff9143ec)

NSTUB(eventproc_ChangeGradeTable, 0xff931a70)

NSTUB(eventproc_MakeDefData, 0xff931d34)
NSTUB(eventproc_KizuMarkCheck, 0xff931e8c)
NSTUB(eventproc_GetDefectCount, 0xff931f14)
NSTUB(eventproc_RenewThermoLogNo, 0xff931f38)

NSTUB(eventproc_DispDev_EnableEventProc, 0xff932940)

NSTUB(eventproc_DispCon_SetVideoAdjParameter, 0xff934518)
NSTUB(eventproc_DispCon_GetVideoAdjParameter, 0xff934588)
NSTUB(eventproc_DispCon_ShowVideoAdjParameter, 0xff9345dc)
NSTUB(eventproc_DispCon_SaveVideoAdjParameter, 0xff9345f8)
NSTUB(eventproc_DispCon_ShowColorBar, 0xff934608)
NSTUB(eventproc_DispCon_ShowFiveStep, 0xff93467c)

NSTUB(eventproc_DispCon_ShowWhiteChart, 0xff934774)
NSTUB(eventproc_DispCon_ShowBlackChart, 0xff9347b8)

NSTUB(eventproc_DispCon_ShowBitmapColorBar, 0xff9347d4)
NSTUB(eventproc_DispCon_ShowCustomColorBar, 0xff93483c)
NSTUB(eventproc_DispCon_SetDisplayType, 0xff9348c4)
NSTUB(eventproc_DispCon_TurnOnDisplay, 0xff9348e8)
NSTUB(eventproc_DispCon_TurnOffDisplay, 0xff9348f8)
NSTUB(eventproc_DispCon_SetMaxBackLightBrightness, 0xff934908)

NSTUB(eventproc_LcdCon_SetLcdDriver, 0xff9373b0)
NSTUB(eventproc_LcdCon_SetLcdAdjParameter, 0xff9374cc)
NSTUB(eventproc_LcdCon_GetLcdAdjParameter, 0xff9375b0)
NSTUB(eventproc_LcdCon_ShowLcdAdjParameter, 0xff937608)
NSTUB(eventproc_LcdCon_SaveLcdAdjParameter, 0xff937658)

NSTUB(eventproc_LcdCon_SetLcdBackLightBrightness, 0xff937800)
NSTUB(eventproc_LcdCon_SetLcdBackLightParameter, 0xff937894)
NSTUB(eventproc_LcdCon_GetLcdBackLightParameter, 0xff937938)
NSTUB(eventproc_LcdCon_ShowLcdBackLightParameter, 0xff937990)
NSTUB(eventproc_LcdCon_SaveLcdBackLightParameter, 0xff9379e0)

NSTUB(eventproc_Movie_NormalCompressionRateMode, 0xff956f14)
NSTUB(eventproc_Movie_HiCompressionRateMode, 0xff956f28)

NSTUB(eventproc_NR_SetDarkSubType, 0xff9657a8)
NSTUB(eventproc_NR_SetDefectCorrectType, 0xff965804)
NSTUB(eventproc_NR_GetDarkSubType, 0xff965838)
NSTUB(eventproc_NR_GetDefectCorrectType, 0xff96587c)

NSTUB(eventproc_export_PT_EraseAllFile, 0xff96a7e0)
NSTUB(eventproc_export_PT_mod, 0xff96a810)
NSTUB(eventproc_export_PT_atoi, 0xff96a81c)
NSTUB(eventproc_export_PT_GetSystemTime, 0xff96a828)
NSTUB(eventproc_export_PT_SetPropertyCaseString, 0xff96a848)
NSTUB(eventproc_export_PT_SetPropertyCaseInt, 0xff96a85c)
NSTUB(eventproc_export_PT_GetPropertyCaseString, 0xff96a884)
NSTUB(eventproc_export_PT_GetPropertyCaseInt, 0xff96a898)
NSTUB(eventproc_export_PT_GetLocalTimeString, 0xff96a944)
NSTUB(eventproc_export_PT_GetLocalDateString, 0xff96a9a0)
NSTUB(eventproc_export_PT_GetLocalDateAndTimeString, 0xff96aa04)
NSTUB(eventproc_export_PT_SetMessage, 0xff96aa54)
NSTUB(eventproc_export_PT_UndispMessage, 0xff96aa7c)
NSTUB(eventproc_export_PT_PlaySound, 0xff96aa98)
NSTUB(eventproc_export_PT_LCD_BkColor, 0xff96aab0)
NSTUB(eventproc_export_PT_LCD_BkColorDef, 0xff96ab6c)
NSTUB(eventproc_export_PT_BatLvChange_PreWeak, 0xff96aba0)
NSTUB(eventproc_export_PT_BatLvChange_Weak, 0xff96aba8)
NSTUB(eventproc_export_PT_BatLvChange_Low, 0xff96abb0)
NSTUB(eventproc_export_PT_BatLvChange_SysLow, 0xff96abb8)
NSTUB(eventproc_export_PT_StartBatteryTest, 0xff96abd0)
NSTUB(eventproc_export_PT_FinishBatteryTest, 0xff96ac30)

NSTUB(eventproc_export_PT_GetBatteryLevel, 0xff96ad28)
NSTUB(eventproc_export_PT_GetPreWeakBatLv, 0xff96ad40)

NSTUB(eventproc_export_PT_GetWeakBatLv, 0xff96ada8)
NSTUB(eventproc_export_PT_GetLowBatLv, 0xff96ae10)
NSTUB(eventproc_export_PT_GetSysLowBatLv, 0xff96ae78)
NSTUB(eventproc_export_UiMemory_Show, 0xff96aef0)

NSTUB(eventproc_export_HardwareDefect, 0xff96b114)

NSTUB(eventproc_ShowErrorNumberList, 0xff96b1a4)

NSTUB(eventproc_export_CreateController, 0xff96c2c0)
NSTUB(eventproc_export_DeleteController, 0xff96c378)
NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff96c4b0)
NSTUB(eventproc_export_GetSelfControllerHandle, 0xff96c5e8)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff96f5c8)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff96f644)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff96f6cc)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff96f734)

NSTUB(eventproc_export_LogiEvnt_LoadCameraLog, 0xff96f87c)

NSTUB(eventproc_export_IsControlEventActive, 0xff9714b8)

NSTUB(eventproc_export_SetScriptMode, 0xff9715ac)
NSTUB(eventproc_export_UiEvnt_ShowBitMaps, 0xff9715bc)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff97161c)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff971630)

NSTUB(eventproc_export_IsDisableAutoShutdown, 0xff9733c4)

NSTUB(eventproc_export_ShowAutoShutdownTime, 0xff973498)
NSTUB(eventproc_export_DisableAutoShutdown, 0xff9734cc)
NSTUB(eventproc_export_EnableAutoShutdown, 0xff9734e4)

NSTUB(eventproc_export_SetAutoShutdownTime, 0xff973778)
NSTUB(eventproc_export_LockMainPower, 0xff973874)
NSTUB(eventproc_export_UnlockMainPower, 0xff97390c)
NSTUB(eventproc_export_GetMainPowerLockCounter, 0xff973a10)

NSTUB(eventproc_PTM_AllResetToFactorySetting, 0xff976248)
NSTUB(eventproc_PTM_AllResetProperty, 0xff976258)

NSTUB(eventproc_PTM_GetWorkingCaptureMode, 0xff97649c)

NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff976830)

NSTUB(eventproc_PTM_SetCurrentCaptureMode, 0xff976f38)
NSTUB(eventproc_PTM_SetCurrentItem, 0xff976f48)
NSTUB(eventproc_PTM_GetCurrentItem, 0xff976f68)
NSTUB(eventproc_PTM_NextItem, 0xff976f80)
NSTUB(eventproc_PTM_PrevItem, 0xff976f98)
NSTUB(eventproc_PTM_BackupUIProperty, 0xff976fb0)
NSTUB(eventproc_PTM_SetProprietyEnable, 0xff976fd4)

NSTUB(eventproc_export_CreateDialogBox, 0xff97d698)
NSTUB(eventproc_export_DeleteDialogBox, 0xff97d8a8)
NSTUB(eventproc_export_ResizeVirtualWindow, 0xff97d964)
NSTUB(eventproc_export_MoveDialogBoxPosition, 0xff97d990)
NSTUB(eventproc_export_DeleteDialogBoxAfterGetTopOfControl, 0xff97da30)
NSTUB(eventproc_export_SetPropertyToDialogItemWithID, 0xff97da54)
NSTUB(eventproc_export_GetPropertyFromDialogItemWithID, 0xff97da84)

NSTUB(eventproc_export_AddItemToDialogBox, 0xff97db1c)
NSTUB(eventproc_export_DeleteItemFromDialogBox, 0xff97dbf0)
NSTUB(eventproc_export_SetFocusDirectionToDialogItem, 0xff97dcdc)
NSTUB(eventproc_export_SetFocusItemToDialogItem, 0xff97dee0)
NSTUB(eventproc_export_GetFocusedItemIDOfDialogItem, 0xff97dff4)
NSTUB(eventproc_export_GetItemHandleOfDialogBox, 0xff97e02c)
NSTUB(eventproc_export_DisplayDialogBox, 0xff97e0cc)
NSTUB(eventproc_export_UndisplayDialogBox, 0xff97e0f4)
NSTUB(eventproc_export_SetBackgroundColorToDialogBox, 0xff97e11c)
NSTUB(eventproc_export_RefreshRectangleToDialog, 0xff97e170)

NSTUB(eventproc_export_RegisterRefreshToDialog, 0xff97e1f8)
NSTUB(eventproc_export_RefreshRegistedRectangleToDialog, 0xff97e2bc)
NSTUB(eventproc_export_FillRectangleToDialog, 0xff97e330)
NSTUB(eventproc_export_DrawStringToDialog, 0xff97e390)
NSTUB(eventproc_export_TransferRectangleToDialog, 0xff97e3f0)
NSTUB(eventproc_export_TransferBitmapToDialog, 0xff97e460)
NSTUB(eventproc_export_DrawBinaryBitmapToDialog, 0xff97e4e0)
NSTUB(eventproc_export_GetDialogBoxWindow, 0xff97e548)
NSTUB(eventproc_export_SetFocusScopeToDialog, 0xff97e568)
NSTUB(eventproc_export_GetFocusScopeToDialog, 0xff97e5d8)
NSTUB(eventproc_export_MoveViewPortPosition, 0xff97e624)
NSTUB(eventproc_export_ResizeDialogBox, 0xff97e688)
NSTUB(eventproc_export_MoveDialogControllerToTopOfZOrder, 0xff97e6d4)
NSTUB(eventproc_export_RegisterChangeLanguageToDialog, 0xff97e6f8)
NSTUB(eventproc_export_UnregisterChangeLanguageToDialog, 0xff97e740)
NSTUB(eventproc_export_MoveDialogItemPositionToDialog, 0xff97e77c)
NSTUB(eventproc_export_ResizeDialogItemToDialog, 0xff97e7b0)
NSTUB(eventproc_export_GetDialogItemPositionToDialog, 0xff97e7e4)
NSTUB(eventproc_export_GetDialogItemResolutionToDialog, 0xff97e818)
NSTUB(eventproc_export_SetOriginTypeToDialog, 0xff97e84c)
NSTUB(eventproc_export_SetDefaultMovingFocusToDialog, 0xff97e870)
NSTUB(eventproc_export_LockRefreshDialog, 0xff97e894)
NSTUB(eventproc_export_UnlockRefreshDialog, 0xff97e8d8)

NSTUB(eventproc_export_KeepDefaultMoveFocusEventToDialog, 0xff97e998)

NSTUB(eventproc_export_InstallDialogItem, 0xff97ed68)
NSTUB(eventproc_export_CreateDialogItem, 0xff97ee44)
NSTUB(eventproc_export_DeleteDialogItem, 0xff97ef34)
NSTUB(eventproc_export_DrawDialogItem, 0xff97efb4)
NSTUB(eventproc_export_ControlEventHandler, 0xff97f04c)
NSTUB(eventproc_export_SetPropertyToDialogItem, 0xff97f0c8)
NSTUB(eventproc_export_GetPropertyFromDialogItem, 0xff97f13c)
NSTUB(eventproc_export_SetAttributeToDialogItem, 0xff97f1b0)
NSTUB(eventproc_export_GetAttributeFromDialogItem, 0xff97f224)
NSTUB(eventproc_export_MoveDialogItemPosition, 0xff97f290)
NSTUB(eventproc_export_ResizeDialogItem, 0xff97f304)
NSTUB(eventproc_export_GetDialogItemPosition, 0xff97f384)
NSTUB(eventproc_export_GetDialogItemResolution, 0xff97f404)

NSTUB(eventproc_StartGUISystem, 0xff982794)

NSTUB(eventproc_ShutdownGUISystem, 0xff9828b8)

NSTUB(eventproc_export_DeletePalette, 0xff982b7c)
NSTUB(eventproc_export_SetYUVPaletteIndex, 0xff982bf4)

NSTUB(eventproc_export_SetPaletteToPhysicalScreen, 0xff982d34)
NSTUB(eventproc_export_GetPaletteFromPhysicalScreen, 0xff982d8c)

NSTUB(eventproc_export_SetCurrentPalette, 0xff985ce4)
NSTUB(eventproc_export_SetSystemColorMode, 0xff985cf4)

NSTUB(eventproc_export_LockPhysicalScreen, 0xff98a5b0)
NSTUB(eventproc_export_RefreshPhysicalScreen, 0xff98a644)
NSTUB(eventproc_export_EnableRefreshPhysicalScreen, 0xff98a718)
NSTUB(eventproc_export_DisableRefreshPhysicalScreen, 0xff98a72c)
NSTUB(eventproc_export_IsEnableRefreshPhysicalScreen, 0xff98a740)

NSTUB(eventproc_export_PrintBmpVramInfo, 0xff98b054)
NSTUB(eventproc_export_PrintCurrPalette, 0xff98b084)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff999bb8)
NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff999bd0)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff999c10)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff999c50)
NSTUB(eventproc_export_ModeLevelStillRecForScript, 0xff999c90)
NSTUB(eventproc_export_ModeLevelMovieRecForScript, 0xff999c9c)
NSTUB(eventproc_export_ModeLevelPlayForScript, 0xff999ca8)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff999cb4)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff999cc0)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff999ccc)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xff999d08)

NSTUB(eventproc_export_UIFS_Capture, 0xff999d58)

NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff999d68)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff999d74)
NSTUB(eventproc_export_UIFS_PCaseToPTMID, 0xff999dac)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff999e0c)
NSTUB(eventproc_UI_RegistDebugEventProc, 0xff99a118)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff9a66a0)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff9a66f0)

NSTUB(eventproc_export_ShootCon_GetStatus, 0xff9a9c98)

NSTUB(eventproc_export_ShootCon_ShowState, 0xff9ada98)

NSTUB(eventproc_export_ShootCon_SetEventHook, 0xff9ae518)
NSTUB(eventproc_export_ShootCon_PrintMemoryDump, 0xff9ae544)
NSTUB(eventproc_export_ShootCon_ShowAllSemaphores, 0xff9ae5d0)

NSTUB(eventproc_StartMovieController, 0xff9af470)
NSTUB(eventproc_EnableMovieController, 0xff9af4d8)
NSTUB(eventproc_DisableMovieController, 0xff9af4ec)
NSTUB(eventproc_ShutdownMovieController, 0xff9af500)

NSTUB(eventproc_GetStateOfMovieSequence, 0xff9b0434)

NSTUB(eventproc_ZoomCon_ShowState, 0xff9b2e50)

NSTUB(eventproc_export_StartSwitchViewFinder, 0xff9bd408)
NSTUB(eventproc_export_StopSwitchViewFinder, 0xff9bd45c)
NSTUB(eventproc_export_SwitchViewFinder, 0xff9bd488)

NSTUB(eventproc_export_UiComIF_SendEventToUI, 0xff9becd4)

NSTUB(eventproc_DeletePlayMyColController, 0xff9fcb88)

NSTUB(eventproc_TerminateDpofUI, 0xffa0ae08)

NSTUB(eventproc_StartPrintOrderMenu, 0xffa0bf50)

NSTUB(eventproc_StartDpofPlayLoading, 0xffa104c8)

NSTUB(eventproc_SyncStopDpofPlayLoading, 0xffa106ac)

NSTUB(eventproc_StartTransferOrderMenu, 0xffa10d24)

NSTUB(eventproc_StartPlayModeMenu, 0xffa13d40)

NSTUB(eventproc_StartRecModeMenu, 0xffa13e14)
NSTUB(eventproc_ShutdownRecModeMenu, 0xffa13ed8)

NSTUB(eventproc_ShutdownPlayModeMenu, 0xffa14060)
NSTUB(eventproc_ShutdownPlayModeMenuWithoutPbRedraw, 0xffa1410c)

NSTUB(eventproc_InstallRecMenu, 0xffa16158)

NSTUB(eventproc_InstallPlayMenu, 0xffa18844)

NSTUB(eventproc_InstallSetupMenu, 0xffa1adfc)

NSTUB(eventproc_InstallMyCameraMenu, 0xffa1debc)

NSTUB(eventproc_IsCalledStopEVF, 0xffa1ef1c)

NSTUB(eventproc_ShutdownRecAllMenu, 0xffa1f6e8)
NSTUB(eventproc_ShutdownPlayAllMenu, 0xffa1f760)

NSTUB(eventproc_export_StartFirmInfoMenu, 0xffa265bc)

NSTUB(eventproc_SaveLanguageNameList, 0xffa29474)
NSTUB(eventproc_RegisterLanguageName, 0xffa29478)

NSTUB(eventproc_CreateLanguageMenu, 0xffa2a034)
NSTUB(eventproc_DeleteLanguageMenu, 0xffa2a1dc)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xffa2c628)

NSTUB(eventproc_export_StartDirectTransferManager, 0xffa31c4c)

NSTUB(eventproc_export_StartDtConfirmMenu, 0xffa3242c)
NSTUB(eventproc_export_StoptDtConfirmMenu, 0xffa3251c)

NSTUB(eventproc_export_StoptDtExecuteMenu, 0xffa32f88)

NSTUB(eventproc_StartDpConnect, 0xffa36650)

NSTUB(eventproc_StopDpConnect, 0xffa368d8)

NSTUB(eventproc_CreateDpConnectController, 0xffa36c78)
NSTUB(eventproc_DeleteDpConnectController, 0xffa36f08)
NSTUB(eventproc_shutdownDirectPrintUI, 0xffa36fdc)

NSTUB(eventproc_StartDpDpofMenu, 0xffa38b2c)

NSTUB(eventproc_StartDpMainMenu, 0xffa3ebc4)

NSTUB(eventproc_StartDpPrinting, 0xffa407b8)

NSTUB(eventproc_StartDpsDpofMenu, 0xffa41ca4)

NSTUB(eventproc_StartDpsMainMenu, 0xffa47ec8)

NSTUB(eventproc_StartDpsStop, 0xffa4e3b8)

NSTUB(eventproc_StartDpStopReconfirm, 0xffa4f6e4)

NSTUB(eventproc_StartDpStyleMenu, 0xffa51978)

NSTUB(eventproc_StartDpTrimming, 0xffa55af8)

NSTUB(eventproc_DBG_changeTraceLevel, 0xffa579d4)

NSTUB(eventproc_ControlViewEvent, 0xffa5f30c)

NSTUB(eventproc_InstallPrintMenu, 0xffa6b864)

NSTUB(eventproc_DisableNotificationPTP, 0xffa71e10)
NSTUB(eventproc_EnableNotificationPTP, 0xffa71e24)
NSTUB(eventproc_SetUSBToPTPMode, 0xffa71e3c)
NSTUB(eventproc_SetUSBToDCPMode, 0xffa71e50)
NSTUB(eventproc_RefreshUSBMode, 0xffa71e68)
NSTUB(eventproc_NotifyConnectPictBridge, 0xffa71eec)
NSTUB(eventproc_NotifyDisconnectPictBridge, 0xffa71f0c)

NSTUB(eventproc_PTPRspnd_StartUpPTPFrameworkClient, 0xffa89aa4)
NSTUB(eventproc_PTPRspnd_ShutDownPTPFrameworkClient, 0xffa89b4c)

NSTUB(eventproc_PTPRspnd_ResetTable, 0xffa933ac)
NSTUB(eventproc_PTPRspnd_EnableGetTreeInfo, 0xffa933b8)
NSTUB(eventproc_PTPRspnd_EnableStorage, 0xffa933f8)

NSTUB(eventproc_PTPRspnd_ShowRemoteStg, 0xffa93760)

NSTUB(eventproc_InitializeDCPClassFunctions, 0xffaa4970)

NSTUB(eventproc_TerminateDCPClassFunctions, 0xffaa5e04)

NSTUB(eventproc_CreateVcomUart, 0xffaa73ac)
NSTUB(eventproc_DeleteVcomUart, 0xffaa74dc)

NSTUB(eventproc_RegComEventProc, 0xffaa7ef4)

NSTUB(eventproc_MechaReset, 0xffaa80c0)
NSTUB(eventproc_MechaTerminate, 0xffaa80f8)
NSTUB(eventproc_ShowMechaMacro, 0xffaa8158)

NSTUB(eventproc_EnableMechaCircuit, 0xffaab4dc)
NSTUB(eventproc_DisableMechaCircuit, 0xffaab4ec)
NSTUB(eventproc_EnableFocusPiCircuit, 0xffaab4fc)
NSTUB(eventproc_DisableFocusPiCircuit, 0xffaab50c)
NSTUB(eventproc_GetFocusPiSensorLevel, 0xffaab51c)

NSTUB(eventproc_EnableZoomPiCircuit, 0xffaab534)
NSTUB(eventproc_DisableZoomPiCircuit, 0xffaab544)
NSTUB(eventproc_GetZoomPiSensorLevel, 0xffaab554)

NSTUB(eventproc_EnableZoomEncoderCircuit, 0xffaab56c)
NSTUB(eventproc_DisableZoomEncoderCircuit, 0xffaab57c)
NSTUB(eventproc_SendMechaCircuitData, 0xffaab58c)
NSTUB(eventproc_ReceiveMechaCircuitDataAll, 0xffaab5cc)

NSTUB(eventproc_MoveLensToFirstPointEvent, 0xffaae118)
NSTUB(eventproc_MoveLensToTerminatePointEvent, 0xffaae190)
NSTUB(eventproc_PermitLensControllerFocusReset, 0xffaae1e0)
NSTUB(eventproc_PermitLensControllerFocusInfinity, 0xffaae1f0)
NSTUB(eventproc_IsLensOutside, 0xffaae200)
NSTUB(eventproc_GetLensErrorStatus, 0xffaae20c)

NSTUB(eventproc_ResetZoomLens, 0xffaaf7d0)
NSTUB(eventproc_ResetZoomLensToFirstPoint, 0xffaaf800)
NSTUB(eventproc_ResetZoomLensToTermiantePoint, 0xffaaf874)
NSTUB(eventproc_MoveZoomLensWithPoint, 0xffaaf8e8)
NSTUB(eventproc_MoveZoomLensWithPosition, 0xffaaf964)
NSTUB(eventproc_MoveZoomLensToTerminatePosition, 0xffaaf9b8)
NSTUB(eventproc_GetZoomLensCurrentPoint, 0xffaafa08)
NSTUB(eventproc_GetZoomLensCurrentPosition, 0xffaafa1c)
NSTUB(eventproc_GetZoomLensTelePoint, 0xffaafa30)

NSTUB(eventproc_SetZoomLensNormalControlGain, 0xffab10dc)

NSTUB(eventproc_SetZoomLensResetControlGain, 0xffab29b4)

NSTUB(eventproc_MoveZoomActuator, 0xffab545c)
NSTUB(eventproc_SetZoomActuatorSpeedPPS, 0xffab54a8)
NSTUB(eventproc_GetZoomActuatorSpeedPPS, 0xffab54bc)
NSTUB(eventproc_SetZoomActuatorSpeedControlGain, 0xffab54d0)
NSTUB(eventproc_GetZoomActuatorSpeedControlGain, 0xffab54e4)
NSTUB(eventproc_SetZoomActuatorLimitAmpere, 0xffab54f8)
NSTUB(eventproc_GetZoomActuatorLimitAmpere, 0xffab550c)
NSTUB(eventproc_SetZoomActuatorPwmDuty, 0xffab5520)
NSTUB(eventproc_SetZoomActuatorPwmFixedTime, 0xffab5534)
NSTUB(eventproc_GetZoomActuatorCurrentPosition, 0xffab5548)
NSTUB(eventproc_IsZoomActuatorResetSensorPlusSide, 0xffab5594)
NSTUB(eventproc_SetDCMotorSpeedLevel, 0xffab55a0)
NSTUB(eventproc_SetDCMotorChargePump, 0xffab55b4)
NSTUB(eventproc_SetDCMotorPwmFixedTimeLevel, 0xffab55c8)
NSTUB(eventproc_SetDCMotorPwmLevel, 0xffab55dc)
NSTUB(eventproc_SetPM3ByGpio, 0xffab55f0)
NSTUB(eventproc_ClearPM3ByGpio, 0xffab5600)
NSTUB(eventproc_ClearPM3ByFs, 0xffab5610)
NSTUB(eventproc_MoveDCMotorCW, 0xffab5620)
NSTUB(eventproc_MoveDCMotorCCW, 0xffab567c)
NSTUB(eventproc_StopDCMotor, 0xffab56d8)
NSTUB(eventproc_SetDCMotorWaitTime, 0xffab56f8)
NSTUB(eventproc_GetCurrentEncoderPosition, 0xffab5710)

NSTUB(eventproc_ResetIrisEvent, 0xffab6838)
NSTUB(eventproc_MoveIrisWithAvEvent, 0xffab6868)
NSTUB(eventproc_MoveIrisToTerminatePositionEvent, 0xffab689c)
NSTUB(eventproc_GetIrisAvEvent, 0xffab68a4)
NSTUB(eventproc_MoveIrisWithAvWithoutBacklashEvent, 0xffab68b8)

NSTUB(eventproc_CloseMechaShutterEvent, 0xffab7bf4)
NSTUB(eventproc_OpenMechaShutterEvent, 0xffab7c24)
NSTUB(eventproc_CloseMechaShutterWithTimingEvent, 0xffab7c54)
NSTUB(eventproc_SetMechaShutterDacSettingEvent, 0xffab7c98)
NSTUB(eventproc_SetMechaShutterOpenDacSettingEvent, 0xffab7cac)
NSTUB(eventproc_SetMechaShutterFinalDacSettingEvent, 0xffab7cc0)
NSTUB(eventproc_SetMechaShutterOpenFinalDacSettingEvent, 0xffab7cd4)
NSTUB(eventproc_SetMechaShutterWaitTimeSettingEvent, 0xffab7ce8)
NSTUB(eventproc_GetMechaShutterStatusEvent, 0xffab7cfc)
NSTUB(eventproc_SaveMechaShutterCount, 0xffab7d08)
NSTUB(eventproc_GetMechaShutterCount, 0xffab7d44)
NSTUB(eventproc_ClearMechaShutterCount, 0xffab7d94)

NSTUB(eventproc_TurnOnNdFilterEvent, 0xffab8668)
NSTUB(eventproc_TurnOffNdFilterEvent, 0xffab8698)
NSTUB(eventproc_SetNdFilterDacSettingEvent, 0xffab86c8)

NSTUB(eventproc_MoveFocusLensWithDistance, 0xffac00b0)
NSTUB(eventproc_ResetFocusLens, 0xffac017c)
NSTUB(eventproc_MoveFocusLensToTerminate, 0xffac01dc)
NSTUB(eventproc_MoveFocusLensWithPosition, 0xffac0250)
NSTUB(eventproc_MoveFocusLensWithPositionWithoutBacklash, 0xffac0320)
NSTUB(eventproc_MoveFocusActuator, 0xffac03f0)
NSTUB(eventproc_GetFocusLensCurrentPosition, 0xffac04ac)
NSTUB(eventproc_GetFocusLensResetPosition, 0xffac04c0)
NSTUB(eventproc_GetFocusLensResetPositionForInside, 0xffac04d4)
NSTUB(eventproc_GetFocusLensResetPositionForOutside, 0xffac04e8)
NSTUB(eventproc_GetFocusLensResetDefaultPosition, 0xffac04fc)
NSTUB(eventproc_SetFocusLensDefaultCondition, 0xffac0510)
NSTUB(eventproc_SetFocusLensCondition, 0xffac0528)
NSTUB(eventproc_GetFocusLensMoveCompleteTime, 0xffac061c)
NSTUB(eventproc_GetFocusLensNdCoefficientPulse, 0xffac0628)
NSTUB(eventproc_GetFocusLensSettingMaxSpeed, 0xffac063c)
NSTUB(eventproc_GetFocusLensSettingMaxSpeedByDeltaType, 0xffac0650)
NSTUB(eventproc_SetFocusLensMaxSpeedLimit, 0xffac0664)
NSTUB(eventproc_CancelFocusLensMaxSpeedLimit, 0xffac067c)
NSTUB(eventproc_EscapeFocusLens, 0xffac0690)
NSTUB(eventproc_GetFocusLensSubjectDistance, 0xffac0724)
NSTUB(eventproc_GetFocusLensSubjectDistanceFromLens, 0xffac0748)
NSTUB(eventproc_EnableFocusLens, 0xffac076c)
NSTUB(eventproc_SetFocusLensBacklashSpeedToMax, 0xffac07d0)
NSTUB(eventproc_ClearFocusLensBacklashSpeedToMax, 0xffac07e0)
NSTUB(eventproc_CheckFocusLensAfAging, 0xffac0880)

NSTUB(eventproc_MoveCZToPointEvent, 0xffac2800)

NSTUB(eventproc_TurnOnAFLampEvent, 0xffac2a94)
NSTUB(eventproc_TurnOffAFLampEvent, 0xffac2aac)

NSTUB(eventproc_DisplayFactoryMode, 0xffac2b9c)
NSTUB(eventproc_UndisplayFactoryMode, 0xffac2bb4)

NSTUB(eventproc_ClearFactoryMode, 0xffac2ef8)
NSTUB(eventproc_SetFactoryMode, 0xffac2f28)

NSTUB(eventproc_IsFactoryMode, 0xffac2fe8)
NSTUB(eventproc_StartFactoryModeController, 0xffac303c)

NSTUB(eventproc_EraseAdjustmentArea, 0xffac39b8)
NSTUB(eventproc_DumpAdjArea, 0xffac39d8)
NSTUB(eventproc_DumpAdjMirror, 0xffac3a00)

NSTUB(eventproc_GetAdjTableVersion, 0xffac3a58)
NSTUB(eventproc_GetAdjTableMapVersion, 0xffac3aa0)
NSTUB(eventproc_GetAdjTableValueVersion, 0xffac3ab0)
NSTUB(eventproc_ShowDefaultAdjTableVersion, 0xffac3af4)
NSTUB(eventproc_LoadAdjustmentTable, 0xffac3b28)
NSTUB(eventproc_SaveAdjustmentTable, 0xffac3b40)
NSTUB(eventproc_SaveAdjustmentValue, 0xffac3b5c)
NSTUB(eventproc_LoadAdjustmentValue, 0xffac3b8c)
NSTUB(eventproc_PrintAdjTableMap, 0xffac3cc8)
NSTUB(eventproc_CreateAdjustmentTableMirror, 0xffac3f8c)

NSTUB(eventproc_WRITEADJTABLETOFROM, 0xffac4278)
NSTUB(eventproc_AddAdjDataToFRom, 0xffac42ac)

NSTUB(eventproc_LoadParamDataFromAdjTableBin, 0xffac592c)
NSTUB(eventproc_LoadDataFromAdjTableBin, 0xffac5a5c)

NSTUB(eventproc_FA_Create, 0xffac5bf8)
NSTUB(eventproc_FA_Delete, 0xffac5c2c)

NSTUB(eventproc_PrintFirmVersion, 0xffac5d98)
NSTUB(eventproc_PrintFaexeVersioin, 0xffac5de8)
NSTUB(eventproc_CreateFADBGSingalID, 0xffac5dfc)
NSTUB(eventproc_FADBGSingal, 0xffac5e14)

NSTUB(eventproc_FADBGPrintf, 0xffac5efc)

NSTUB(eventproc_FAPrintf, 0xffac6090)

NSTUB(eventproc_OutputLogToFile, 0xffac61ac)
NSTUB(eventproc_StopLogOut, 0xffac62e8)

NSTUB(eventproc_GetLogData, 0xffac6528)
NSTUB(eventproc_ActivateAdjLog, 0xffac6618)
NSTUB(eventproc_InactivateAdjLog, 0xffac6638)
NSTUB(eventproc_StartLogOut, 0xffac6658)
NSTUB(eventproc_IsLogOutType, 0xffac6674)

NSTUB(eventproc_InitializeAdjustmentSystem, 0xffac679c)
NSTUB(eventproc_TerminateAdjustmentSystem, 0xffac67e4)
NSTUB(eventproc_InitializeAdjustmentFunction, 0xffac682c)

NSTUB(eventproc_PrintAllAEIntegData, 0xffac6aec)

NSTUB(eventproc_GetAEIntegralValue, 0xffac7934)
NSTUB(eventproc_GETMAINFLASHEVALUATIONVALUE, 0xffac79e0)
NSTUB(eventproc_GETPREFLASHEVALUATIONVALUE, 0xffac7a94)
NSTUB(eventproc_GETALTERNATEEVALUATIONVALUEWITHMECHASHUTTER, 0xffac7b50)
NSTUB(eventproc_GETEVFEVALUATIONVALUEWITHMECHASHUTTER, 0xffac7bf4)
NSTUB(eventproc_GETCRWEVALUATIONVALUEWITHMECHASHUTTER, 0xffac7c98)
NSTUB(eventproc_GETCRWEVALUATIONVALUEWITHOUTMECHASHUTTER, 0xffac7d3c)
NSTUB(eventproc_GETEVFEVALUATIONVALUEWITHOUTMECHASHUTTER, 0xffac7de0)
NSTUB(eventproc_GETMOVIEEVALUATIONVALUEWITHMECHASHUTTER, 0xffac7e84)
NSTUB(eventproc_AbortAEIntegralValue, 0xffac7f28)
NSTUB(eventproc_SetAEIntegStrobeProperty, 0xffac7f88)
NSTUB(eventproc_SetAEIntegralValueProperty, 0xffac7fc4)

NSTUB(eventproc_GetAEIntegralValueWithFix, 0xffac81ec)

NSTUB(eventproc_GetAllAEIntegralAllValueWithFix, 0xffac835c)

NSTUB(eventproc_SetWhiteCoefficient, 0xffac84cc)

NSTUB(eventproc_SetAEIntegWindowsMode, 0xffac8594)

NSTUB(eventproc_SetAEIntegValueBit, 0xffac8654)
NSTUB(eventproc_GetAEIntegralServiceMode, 0xffac8674)
NSTUB(eventproc_StopAEIntegralService, 0xffac869c)
NSTUB(eventproc_StartAEIntegralService, 0xffac8794)

NSTUB(eventproc_SetLineDefMarkThroughMode, 0xffac8ad0)
NSTUB(eventproc_SetAEIntegAverageOBData, 0xffac8b70)

NSTUB(eventproc_SetDeltaCDSGain, 0xffaca278)
NSTUB(eventproc_ReloadCdsAdjustment, 0xffaca2c8)
NSTUB(eventproc_GetObClampValue, 0xffaca2e0)
NSTUB(eventproc_SetObClamp, 0xffaca310)

NSTUB(eventproc_GetCdsGainValue, 0xffaca364)
NSTUB(eventproc_SetCDSGain, 0xffaca39c)

NSTUB(eventproc_SetCDSGainStep, 0xffaca3e4)

NSTUB(eventproc_SetAdjCdsMode, 0xffaca440)
NSTUB(eventproc_CancelAdjCdsMode, 0xffaca45c)
NSTUB(eventproc_IsAdjCdsMode, 0xffaca478)

NSTUB(eventproc_ConvertTvToExposureTime, 0xffaca59c)
NSTUB(eventproc_GetCurrentExposureTime, 0xffaca5d8)
NSTUB(eventproc_GetCurrentShutterSpeed, 0xffaca5f0)
NSTUB(eventproc_SetShutterSpeedWithMecha, 0xffaca604)

NSTUB(eventproc_SetShutterSpeed, 0xffaca678)

NSTUB(eventproc_GetUserSetShutterSPeed, 0xffaca720)
NSTUB(eventproc_GetShutterSpeedRegularMaxLimit, 0xffaca730)
NSTUB(eventproc_GetShutterSpeedRegularMinLimit, 0xffaca754)

NSTUB(eventproc_MoveIrisToAv, 0xffaca8c8)

NSTUB(eventproc_ReloadIrisAdjustment, 0xffaca934)
NSTUB(eventproc_GetCurrentAvValue, 0xffaca940)

NSTUB(eventproc_ReloadNdFilterAdjustment, 0xffacaa9c)
NSTUB(eventproc_PutInNdFilter, 0xffacaac4)

NSTUB(eventproc_PutOutNdFilter, 0xffacab0c)

NSTUB(eventproc_CloseMShutter, 0xffacac18)

NSTUB(eventproc_OpenMShutter, 0xffacac60)

NSTUB(eventproc_CalculateLog2ToApex, 0xffacb6e0)

NSTUB(eventproc_CalculatePow2FromApex, 0xffacb714)
NSTUB(eventproc_CalcLog10, 0xffacb738)

NSTUB(eventproc_ConvertApexToApexStd, 0xffacb7d0)
NSTUB(eventproc_ConvertApexStdToApex, 0xffacb804)

NSTUB(eventproc_OneShotWhigeBalance, 0xffacba04)

NSTUB(eventproc_SetWBYlStandardWidth, 0xffacba84)
NSTUB(eventproc_SetReferenceWBGainForCalibration, 0xffacbac8)
NSTUB(eventproc_SetToolCorrectCoefficient, 0xffacbaf8)

NSTUB(eventproc_ReloadWBAdjustment, 0xffacbb80)

NSTUB(eventproc_ConvertCxCyToWBGain, 0xffacbe44)

NSTUB(eventproc_GetCurrentZoomLensDirection, 0xffacbfc4)
NSTUB(eventproc_GetZoomLensResetPlus, 0xffacbfe4)
NSTUB(eventproc_MoveZoomLensToMechaEnd, 0xffacc00c)

NSTUB(eventproc_MoveZoomLensToPositionByManual, 0xffacc0ec)

NSTUB(eventproc_ResetZoomToAdjTerminatePoint, 0xffacc3cc)

NSTUB(eventproc_ResetZoomToAdjFirstPoint, 0xffacc4b4)

NSTUB(eventproc_GetCurrentZoomLensPoint, 0xffacc57c)
NSTUB(eventproc_GetCurrentZoomLensPosition, 0xffacc590)
NSTUB(eventproc_MoveZoomLensToPoint, 0xffacc5a4)

NSTUB(eventproc_MoveZoomLensToPosition, 0xffacc5fc)

NSTUB(eventproc_ResetZoomToTerminatePoint, 0xffacc654)

NSTUB(eventproc_ResetZoomToFirstPoint, 0xffacc69c)

NSTUB(eventproc_ResetZoom, 0xffacc6e4)
NSTUB(eventproc_ReloadZoomAdjustment, 0xffacc72c)
NSTUB(eventproc_GetZoomLensCurrent, 0xffacc738)
NSTUB(eventproc_GetZoomLensSpeed, 0xffacc74c)

NSTUB(eventproc_ConvertToPositionWithDistanceAndZoomPoint, 0xffacc9d8)

NSTUB(eventproc_ReloadFocusLensAdjustment, 0xffacca1c)
NSTUB(eventproc_GetFocusDefaultResetPosition, 0xffacca28)
NSTUB(eventproc_GetFocusResetPosition, 0xffacca3c)
NSTUB(eventproc_GetCurrentTargetDistance, 0xffacca50)

NSTUB(eventproc_GetCurrentFocusLensPosition, 0xffaccaa8)
NSTUB(eventproc_MoveFocusLensToTerminatePosition, 0xffaccabc)

NSTUB(eventproc_MoveFocusLensToPositionWithMaxSpeed, 0xffaccb4c)

NSTUB(eventproc_MoveFocusLensToPosition, 0xffaccbb0)

NSTUB(eventproc_MoveFocusLensToDistance, 0xffacccf0)

NSTUB(eventproc_ResetFocus, 0xffacce0c)

NSTUB(eventproc_PrintScanTable, 0xffacd1d4)
NSTUB(eventproc_PrintMultiWinScanTable, 0xffacd338)

NSTUB(eventproc_CalculatePeakPositionByLeastSquare, 0xfface860)

NSTUB(eventproc_SetFocusScanAutoStopProperty, 0xffaced24)
NSTUB(eventproc_StartFocusScanWithAutoStopFix, 0xffaced4c)

NSTUB(eventproc_StartFocusScanWithAutoStop, 0xffacee28)

NSTUB(eventproc_StopFocusScan, 0xffaceff0)
NSTUB(eventproc_StartFocusScanWithEnableToStop, 0xffaceffc)

NSTUB(eventproc_StartFocusScanWithRange, 0xffacf1a8)

NSTUB(eventproc_StartFocusScan, 0xffacf2f0)

NSTUB(eventproc_StartMultiWinFocusScan, 0xffacf454)

NSTUB(eventproc_StartDigiconService, 0xffacf5d8)

NSTUB(eventproc_GetDigiconData, 0xffacf658)

NSTUB(eventproc_StartDigiconFocusScan, 0xffacfc60)
NSTUB(eventproc_StopDigiconService, 0xffacfcd0)
NSTUB(eventproc_SetMultiWinPos, 0xffacfcfc)
NSTUB(eventproc_SetAFSensorDriveMode, 0xffacfd68)
NSTUB(eventproc_GetAFSensorDriveMode, 0xffacfe0c)
NSTUB(eventproc_SetBPFForBestPintCorrect, 0xffacfe1c)
NSTUB(eventproc_CancelBPFForBestPintCorrect, 0xffacfe30)
NSTUB(eventproc_ReloadBPCoeffAdjustment, 0xffacfe3c)

NSTUB(eventproc_ReloadEfAdjustment, 0xffad00f8)
NSTUB(eventproc_ChargeStrobe, 0xffad0104)

NSTUB(eventproc_ReloadColorAdjustment, 0xffad0200)

NSTUB(eventproc_RegistColorMatrix, 0xffad02f0)
NSTUB(eventproc_UnregistColorMatrix, 0xffad0334)

NSTUB(eventproc_ShowCurrentExp, 0xffad0500)

NSTUB(eventproc_SetAE_ShutterSpeed, 0xffad0598)

NSTUB(eventproc_FocusAEWithCompensation, 0xffad06fc)

NSTUB(eventproc_SetAE_CdsGainValue, 0xffad07f0)
NSTUB(eventproc_FixAEWithCompensation, 0xffad0808)

NSTUB(eventproc_SetAdj_AEMode, 0xffad08a4)

NSTUB(eventproc_CancelAdj_AEMode, 0xffad08f4)
NSTUB(eventproc_PreFixAE, 0xffad0924)

NSTUB(eventproc_AfAEWithAperturePriority, 0xffad09a0)

NSTUB(eventproc_AdjAEWithAperturePriority, 0xffad0a7c)

NSTUB(eventproc_SleepAE, 0xffad0c0c)

NSTUB(eventproc_AfAEWithCompensation, 0xffad0c54)

NSTUB(eventproc_SwitchOffDisplay, 0xffad0ff0)
NSTUB(eventproc_SwitchOnDisplay, 0xffad1024)
NSTUB(eventproc_GetVideoOutType, 0xffad105c)
NSTUB(eventproc_SetVideoOutType, 0xffad106c)

NSTUB(eventproc_IsEVFDrive, 0xffad109c)
NSTUB(eventproc_StopEVFDrive, 0xffad10fc)
NSTUB(eventproc_StartEVFDriveWithMode, 0xffad114c)
NSTUB(eventproc_StartEVFDrive, 0xffad1198)

NSTUB(eventproc_IsEvfDriveMode, 0xffad1474)

NSTUB(eventproc_GetVRAMHPixelsSize, 0xffad1778)
NSTUB(eventproc_GetVRAMVPixelsSize, 0xffad1784)
NSTUB(eventproc_StopContinuousVRAMData, 0xffad1790)

NSTUB(eventproc_GetContinuousVRAMData, 0xffad1854)

NSTUB(eventproc_GetPixelsOfViewangle, 0xffad1f84)

NSTUB(eventproc_GetModelId, 0xffad26cc)
NSTUB(eventproc_SetInputVoltage, 0xffad26d4)
NSTUB(eventproc_SaveBatSenseOffsetAdjustmentTable, 0xffad26e8)
NSTUB(eventproc_SetImageMode, 0xffad26f8)
NSTUB(eventproc_SetDate, 0xffad2710)
NSTUB(eventproc_SetYear, 0xffad2804)
NSTUB(eventproc_SetMonth, 0xffad286c)
NSTUB(eventproc_SetDay, 0xffad28d0)
NSTUB(eventproc_SetHour, 0xffad2940)
NSTUB(eventproc_SetMinute, 0xffad29ac)
NSTUB(eventproc_SetSecond, 0xffad2a1c)
NSTUB(eventproc_GetYear, 0xffad2a88)
NSTUB(eventproc_GetMonth, 0xffad2ac0)
NSTUB(eventproc_GetDay, 0xffad2af8)
NSTUB(eventproc_GetHour, 0xffad2b28)
NSTUB(eventproc_GetMinute, 0xffad2b58)
NSTUB(eventproc_GetSecond, 0xffad2b88)
NSTUB(eventproc_SetLangMenuType, 0xffad2bb8)

NSTUB(eventproc_GetUnpackCrwIntegralValue, 0xffad3308)

NSTUB(eventproc_ShowTransparentMemory, 0xffad4fb4)
NSTUB(eventproc_DumpTransparentMemoryItem, 0xffad4fe4)
NSTUB(eventproc_AddTransparentMemory, 0xffad5038)
NSTUB(eventproc_AttachToTransparentMemory, 0xffad5080)
NSTUB(eventproc_RemoveTransparentMemory, 0xffad50c8)
NSTUB(eventproc_GetTransparentMemorySize, 0xffad50ec)
NSTUB(eventproc_GetTransparentMemory, 0xffad510c)
NSTUB(eventproc_GetTransparentMemoryPosition, 0xffad5164)

NSTUB(eventproc_CompletePrepareTestRec, 0xffad8294)
NSTUB(eventproc_StrobeChargeCompForTestRec, 0xffad82b0)

NSTUB(eventproc_InitializeTestRec, 0xffad83bc)
NSTUB(eventproc_TerminateTestRec, 0xffad8428)

NSTUB(eventproc_ExecuteTestRec, 0xffad85e0)
NSTUB(eventproc_ExecuteTestRecCF, 0xffad8764)

NSTUB(eventproc_SetDefaultRecParameter, 0xffada65c)
NSTUB(eventproc_SetDefectRecParameter, 0xffada8d8)

NSTUB(eventproc_EnableDebugLogMode, 0xffada92c)
NSTUB(eventproc_DisableDebugLogMode, 0xffada944)

NSTUB(eventproc_FreeBufferForSoundRec, 0xffadaf48)

NSTUB(eventproc_StartSoundRecord, 0xffadb080)

NSTUB(eventproc_StartSoundPlay, 0xffadb2dc)
NSTUB(eventproc_InitializeSoundRec, 0xffadb304)
NSTUB(eventproc_TerminateSoundRec, 0xffadb344)

NSTUB(eventproc_MakeBootDisk, 0xffaf5580)
NSTUB(eventproc_MakeScriptDisk, 0xffaf5594)

NSTUB(eventproc_LoadScript, 0xffaf6fe8)
NSTUB(eventproc_UnLoadScript, 0xffaf6ff8)
NSTUB(eventproc_Printf, 0xffaf700c)
NSTUB(eventproc_ScriptDisEnabled, 0xffaf7024)
NSTUB(eventproc_ScriptEnabled, 0xffaf7038)

NSTUB(eventproc_GetLogToFile, 0xffaff378)

NSTUB(eventproc_MemoryChecker, 0xffb006fc)
NSTUB(eventproc_VerifyByte, 0xffb0082c)

