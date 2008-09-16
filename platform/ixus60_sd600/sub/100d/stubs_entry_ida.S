
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

NSTUB(eventproc_DispDev_EnableEventProc, 0xff931b9c)

NSTUB(eventproc_export_PT_EraseAllFile, 0xff96a0b4)
NSTUB(eventproc_export_PT_mod, 0xff96a0e4)
NSTUB(eventproc_export_PT_atoi, 0xff96a0f0)
NSTUB(eventproc_export_PT_GetSystemTime, 0xff96a0fc)
NSTUB(eventproc_export_PT_SetPropertyCaseString, 0xff96a11c)
NSTUB(eventproc_export_PT_SetPropertyCaseInt, 0xff96a130)
NSTUB(eventproc_export_PT_GetPropertyCaseString, 0xff96a158)
NSTUB(eventproc_export_PT_GetPropertyCaseInt, 0xff96a16c)
NSTUB(eventproc_export_PT_GetLocalTimeString, 0xff96a218)
NSTUB(eventproc_export_PT_GetLocalDateString, 0xff96a274)
NSTUB(eventproc_export_PT_GetLocalDateAndTimeString, 0xff96a2d8)
NSTUB(eventproc_export_PT_SetMessage, 0xff96a328)
NSTUB(eventproc_export_PT_UndispMessage, 0xff96a350)
NSTUB(eventproc_export_PT_PlaySound, 0xff96a36c)
NSTUB(eventproc_export_PT_LCD_BkColor, 0xff96a384)
NSTUB(eventproc_export_PT_LCD_BkColorDef, 0xff96a440)
NSTUB(eventproc_export_PT_BatLvChange_PreWeak, 0xff96a474)
NSTUB(eventproc_export_PT_BatLvChange_Weak, 0xff96a47c)
NSTUB(eventproc_export_PT_BatLvChange_Low, 0xff96a484)
NSTUB(eventproc_export_PT_BatLvChange_SysLow, 0xff96a48c)
NSTUB(eventproc_export_PT_StartBatteryTest, 0xff96a4a4)
NSTUB(eventproc_export_PT_FinishBatteryTest, 0xff96a504)

NSTUB(eventproc_export_PT_GetBatteryLevel, 0xff96a5fc)
NSTUB(eventproc_export_PT_GetPreWeakBatLv, 0xff96a614)
NSTUB(eventproc_export_PT_GetWeakBatLv, 0xff96a66c)
NSTUB(eventproc_export_PT_GetLowBatLv, 0xff96a6c4)
NSTUB(eventproc_export_PT_GetSysLowBatLv, 0xff96a71c)
NSTUB(eventproc_export_UiMemory_Show, 0xff96a784)

NSTUB(eventproc_export_HardwareDefect, 0xff96a9a8)

NSTUB(eventproc_ShowErrorNumberList, 0xff96aa38)

NSTUB(eventproc_export_CreateController, 0xff96bb54)
NSTUB(eventproc_export_DeleteController, 0xff96bc0c)
NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff96bd44)
NSTUB(eventproc_export_GetSelfControllerHandle, 0xff96be7c)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff96ee68)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff96eee4)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff96ef6c)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff96efd4)

NSTUB(eventproc_export_LogiEvnt_LoadCameraLog, 0xff96f11c)

NSTUB(eventproc_export_IsControlEventActive, 0xff970ba4)

NSTUB(eventproc_export_SetScriptMode, 0xff970c98)
NSTUB(eventproc_export_UiEvnt_ShowBitMaps, 0xff970ca8)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff970d08)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff970d1c)

NSTUB(eventproc_export_IsDisableAutoShutdown, 0xff9729fc)

NSTUB(eventproc_export_ShowAutoShutdownTime, 0xff972ad0)
NSTUB(eventproc_export_DisableAutoShutdown, 0xff972b04)
NSTUB(eventproc_export_EnableAutoShutdown, 0xff972b1c)

NSTUB(eventproc_export_SetAutoShutdownTime, 0xff972db0)
NSTUB(eventproc_export_LockMainPower, 0xff972eac)
NSTUB(eventproc_export_UnlockMainPower, 0xff972f44)
NSTUB(eventproc_export_GetMainPowerLockCounter, 0xff973048)

NSTUB(eventproc_PTM_AllResetToFactorySetting, 0xff975880)
NSTUB(eventproc_PTM_AllResetProperty, 0xff975890)

NSTUB(eventproc_PTM_GetWorkingCaptureMode, 0xff975ac8)

NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff975e5c)

NSTUB(eventproc_PTM_SetCurrentCaptureMode, 0xff976564)
NSTUB(eventproc_PTM_SetCurrentItem, 0xff976574)
NSTUB(eventproc_PTM_GetCurrentItem, 0xff976594)
NSTUB(eventproc_PTM_NextItem, 0xff9765ac)
NSTUB(eventproc_PTM_PrevItem, 0xff9765c4)
NSTUB(eventproc_PTM_BackupUIProperty, 0xff9765dc)
NSTUB(eventproc_PTM_SetProprietyEnable, 0xff976600)

NSTUB(eventproc_export_CreateDialogBox, 0xff97ccc4)
NSTUB(eventproc_export_DeleteDialogBox, 0xff97ced4)
NSTUB(eventproc_export_ResizeVirtualWindow, 0xff97cf90)
NSTUB(eventproc_export_MoveDialogBoxPosition, 0xff97cfbc)
NSTUB(eventproc_export_DeleteDialogBoxAfterGetTopOfControl, 0xff97d05c)
NSTUB(eventproc_export_SetPropertyToDialogItemWithID, 0xff97d080)
NSTUB(eventproc_export_GetPropertyFromDialogItemWithID, 0xff97d0b0)

NSTUB(eventproc_export_AddItemToDialogBox, 0xff97d148)
NSTUB(eventproc_export_DeleteItemFromDialogBox, 0xff97d21c)
NSTUB(eventproc_export_SetFocusDirectionToDialogItem, 0xff97d308)
NSTUB(eventproc_export_SetFocusItemToDialogItem, 0xff97d50c)
NSTUB(eventproc_export_GetFocusedItemIDOfDialogItem, 0xff97d620)
NSTUB(eventproc_export_GetItemHandleOfDialogBox, 0xff97d658)
NSTUB(eventproc_export_DisplayDialogBox, 0xff97d6f8)
NSTUB(eventproc_export_UndisplayDialogBox, 0xff97d720)
NSTUB(eventproc_export_SetBackgroundColorToDialogBox, 0xff97d748)
NSTUB(eventproc_export_RefreshRectangleToDialog, 0xff97d79c)

NSTUB(eventproc_export_RegisterRefreshToDialog, 0xff97d824)
NSTUB(eventproc_export_RefreshRegistedRectangleToDialog, 0xff97d8e8)
NSTUB(eventproc_export_FillRectangleToDialog, 0xff97d95c)
NSTUB(eventproc_export_DrawStringToDialog, 0xff97d9bc)
NSTUB(eventproc_export_TransferRectangleToDialog, 0xff97da1c)
NSTUB(eventproc_export_TransferBitmapToDialog, 0xff97da8c)
NSTUB(eventproc_export_DrawBinaryBitmapToDialog, 0xff97db0c)
NSTUB(eventproc_export_GetDialogBoxWindow, 0xff97db74)
NSTUB(eventproc_export_SetFocusScopeToDialog, 0xff97db94)
NSTUB(eventproc_export_GetFocusScopeToDialog, 0xff97dc04)
NSTUB(eventproc_export_MoveViewPortPosition, 0xff97dc50)
NSTUB(eventproc_export_ResizeDialogBox, 0xff97dcb4)
NSTUB(eventproc_export_MoveDialogControllerToTopOfZOrder, 0xff97dd00)
NSTUB(eventproc_export_RegisterChangeLanguageToDialog, 0xff97dd24)
NSTUB(eventproc_export_UnregisterChangeLanguageToDialog, 0xff97dd6c)
NSTUB(eventproc_export_MoveDialogItemPositionToDialog, 0xff97dda8)
NSTUB(eventproc_export_ResizeDialogItemToDialog, 0xff97dddc)
NSTUB(eventproc_export_GetDialogItemPositionToDialog, 0xff97de10)
NSTUB(eventproc_export_GetDialogItemResolutionToDialog, 0xff97de44)
NSTUB(eventproc_export_SetOriginTypeToDialog, 0xff97de78)
NSTUB(eventproc_export_SetDefaultMovingFocusToDialog, 0xff97de9c)
NSTUB(eventproc_export_LockRefreshDialog, 0xff97dec0)
NSTUB(eventproc_export_UnlockRefreshDialog, 0xff97df04)

NSTUB(eventproc_export_KeepDefaultMoveFocusEventToDialog, 0xff97dfc4)

NSTUB(eventproc_export_InstallDialogItem, 0xff97e394)
NSTUB(eventproc_export_CreateDialogItem, 0xff97e470)
NSTUB(eventproc_export_DeleteDialogItem, 0xff97e560)
NSTUB(eventproc_export_DrawDialogItem, 0xff97e5e0)
NSTUB(eventproc_export_ControlEventHandler, 0xff97e678)
NSTUB(eventproc_export_SetPropertyToDialogItem, 0xff97e6f4)
NSTUB(eventproc_export_GetPropertyFromDialogItem, 0xff97e768)
NSTUB(eventproc_export_SetAttributeToDialogItem, 0xff97e7dc)
NSTUB(eventproc_export_GetAttributeFromDialogItem, 0xff97e850)
NSTUB(eventproc_export_MoveDialogItemPosition, 0xff97e8bc)
NSTUB(eventproc_export_ResizeDialogItem, 0xff97e930)
NSTUB(eventproc_export_GetDialogItemPosition, 0xff97e9b0)
NSTUB(eventproc_export_GetDialogItemResolution, 0xff97ea30)

NSTUB(eventproc_export_StartGUISystem, 0xff981dc0)

NSTUB(eventproc_ShutdownGUISystem, 0xff981ee4)

NSTUB(eventproc_export_DeletePalette, 0xff9821a8)
NSTUB(eventproc_export_SetYUVPaletteIndex, 0xff982220)

NSTUB(eventproc_export_SetPaletteToPhysicalScreen, 0xff982360)
NSTUB(eventproc_export_GetPaletteFromPhysicalScreen, 0xff9823b8)

NSTUB(eventproc_export_SetCurrentPalette, 0xff985310)
NSTUB(eventproc_export_SetSystemColorMode, 0xff985320)

NSTUB(eventproc_export_LockPhysicalScreen, 0xff989bd4)
NSTUB(eventproc_export_RefreshPhysicalScreen, 0xff989c68)
NSTUB(eventproc_export_EnableRefreshPhysicalScreen, 0xff989d3c)
NSTUB(eventproc_export_DisableRefreshPhysicalScreen, 0xff989d50)
NSTUB(eventproc_export_IsEnableRefreshPhysicalScreen, 0xff989d64)

NSTUB(eventproc_export_PrintBmpVramInfo, 0xff98a678)
NSTUB(eventproc_export_PrintCurrPalette, 0xff98a6ac)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff999228)
NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff999240)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff999280)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff9992c0)
NSTUB(eventproc_export_ModeLevelStillRecForScript, 0xff999300)
NSTUB(eventproc_export_ModeLevelMovieRecForScript, 0xff99930c)
NSTUB(eventproc_export_ModeLevelPlayForScript, 0xff999318)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff999324)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff999330)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff99933c)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xff999350)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xff999364)
NSTUB(eventproc_export_UIFS_Capture, 0xff999378)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff999388)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff999394)
NSTUB(eventproc_export_UIFS_PCaseToPTMID, 0xff9993cc)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff99942c)
NSTUB(eventproc_UI_RegistDebugEventProc, 0xff999738)

NSTUB(eventproc_ExecuteResetFactoryWithRomWrite, 0xff99f0e0)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff9a3fa8)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff9a3ff8)

NSTUB(eventproc_export_ShootCon_GetStatus, 0xff9a75a0)

NSTUB(eventproc_export_ShootCon_ShowState, 0xff9ab3a4)

NSTUB(eventproc_export_ShootCon_SetEventHook, 0xff9abe24)
NSTUB(eventproc_export_ShootCon_PrintMemoryDump, 0xff9abe50)
NSTUB(eventproc_export_ShootCon_ShowAllSemaphores, 0xff9abedc)

NSTUB(eventproc_StartMovieController, 0xff9acd7c)
NSTUB(eventproc_EnableMovieController, 0xff9acde4)
NSTUB(eventproc_DisableMovieController, 0xff9acdf8)
NSTUB(eventproc_ShutdownMovieController, 0xff9ace0c)

NSTUB(eventproc_GetStateOfMovieSequence, 0xff9add40)

NSTUB(eventproc_ZoomCon_ShowState, 0xff9b0764)

NSTUB(eventproc_export_StartSwitchViewFinder, 0xff9bac48)
NSTUB(eventproc_export_StopSwitchViewFinder, 0xff9bac9c)
NSTUB(eventproc_export_SwitchViewFinder, 0xff9bacc8)

NSTUB(eventproc_export_UiComIF_SendEventToUI, 0xff9bc458)

NSTUB(eventproc_DeletePlayMyColController, 0xff9f4120)

NSTUB(eventproc_TerminateDpofUI, 0xffa023bc)

NSTUB(eventproc_StartPrintOrderMenu, 0xffa03504)

NSTUB(eventproc_StartDpofPlayLoading, 0xffa07a7c)

NSTUB(eventproc_SyncStopDpofPlayLoading, 0xffa07c60)

NSTUB(eventproc_StartTransferOrderMenu, 0xffa082d8)

NSTUB(eventproc_StartPlayModeMenu, 0xffa0b2f4)

NSTUB(eventproc_StartRecModeMenu, 0xffa0b3c8)
NSTUB(eventproc_ShutdownRecModeMenu, 0xffa0b48c)

NSTUB(eventproc_ShutdownPlayModeMenu, 0xffa0b614)
NSTUB(eventproc_ShutdownPlayModeMenuWithoutPbRedraw, 0xffa0b6c0)

NSTUB(eventproc_InstallRecMenu, 0xffa0d710)

NSTUB(eventproc_InstallPlayMenu, 0xffa0fdec)

NSTUB(eventproc_InstallSetupMenu, 0xffa1236c)

NSTUB(eventproc_InstallMyCameraMenu, 0xffa15334)

NSTUB(eventproc_IsCalledStopEVF, 0xffa16394)

NSTUB(eventproc_ShutdownRecAllMenu, 0xffa16b60)
NSTUB(eventproc_ShutdownPlayAllMenu, 0xffa16bd8)

NSTUB(eventproc_export_StartFirmInfoMenu, 0xffa1d980)

NSTUB(eventproc_ShowLanguageNameList, 0xffa207fc)
NSTUB(eventproc_SaveLanguageNameList, 0xffa20838)
NSTUB(eventproc_RegisterLanguageName, 0xffa2083c)

NSTUB(eventproc_CreateLanguageMenu, 0xffa213f8)
NSTUB(eventproc_DeleteLanguageMenu, 0xffa215a0)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xffa239ec)

NSTUB(eventproc_export_StartDirectTransferManager, 0xffa29448)

NSTUB(eventproc_export_StoptDtConfirmMenu, 0xffa29d18)

NSTUB(eventproc_export_StoptDtExecuteMenu, 0xffa2a774)

NSTUB(eventproc_StartDpConnect, 0xffa2de10)

NSTUB(eventproc_StopDpConnect, 0xffa2e098)

NSTUB(eventproc_CreateDpConnectController, 0xffa2e430)
NSTUB(eventproc_DeleteDpConnectController, 0xffa2e6c4)
NSTUB(eventproc_shutdownDirectPrintUI, 0xffa2e798)

NSTUB(eventproc_StartDpDpofMenu, 0xffa302e8)

NSTUB(eventproc_StartDpMainMenu, 0xffa36370)

NSTUB(eventproc_StartDpPrinting, 0xffa37f64)

NSTUB(eventproc_StartDpsDpofMenu, 0xffa39450)

NSTUB(eventproc_StartDpsMainMenu, 0xffa3f65c)

NSTUB(eventproc_StartDpsStop, 0xffa45b4c)

NSTUB(eventproc_StartDpStopReconfirm, 0xffa46e78)

NSTUB(eventproc_StartDpStyleMenu, 0xffa4910c)

NSTUB(eventproc_StartDpTrimming, 0xffa4d278)

NSTUB(eventproc_DBG_changeTraceLevel, 0xffa4f100)

NSTUB(eventproc_StartDpMovieMenu, 0xffa4f2f8)

NSTUB(eventproc_ControlViewEvent, 0xffa56a38)

NSTUB(eventproc_InstallPrintMenu, 0xffa62cac)

NSTUB(eventproc_DisableNotificationPTP, 0xffa69224)
NSTUB(eventproc_EnableNotificationPTP, 0xffa69238)
NSTUB(eventproc_SetUSBToPTPMode, 0xffa69250)
NSTUB(eventproc_SetUSBToDCPMode, 0xffa69264)
NSTUB(eventproc_RefreshUSBMode, 0xffa6927c)
NSTUB(eventproc_NotifyConnectPictBridge, 0xffa69300)
NSTUB(eventproc_NotifyDisconnectPictBridge, 0xffa69320)

NSTUB(eventproc_PTPRspnd_ShowRemoteStg, 0xffa8abe4)

NSTUB(eventproc_CreateVcomUart, 0xffa9e950)
NSTUB(eventproc_DeleteVcomUart, 0xffa9ea80)

NSTUB(eventproc_RegComEventProc, 0xffa9f498)

NSTUB(eventproc_MechaReset, 0xffa9f664)
NSTUB(eventproc_MechaTerminate, 0xffa9f69c)
NSTUB(eventproc_ShowMechaMacro, 0xffa9f710)

NSTUB(eventproc_EnableMechaCircuit, 0xffaa2aa0)
NSTUB(eventproc_DisableMechaCircuit, 0xffaa2ab0)
NSTUB(eventproc_EnableFocusPiCircuit, 0xffaa2ac0)
NSTUB(eventproc_DisableFocusPiCircuit, 0xffaa2ad0)
NSTUB(eventproc_GetFocusPiSensorLevel, 0xffaa2ae0)
NSTUB(eventproc_EnableZoomPiCircuit, 0xffaa2af8)
NSTUB(eventproc_DisableZoomPiCircuit, 0xffaa2b08)
NSTUB(eventproc_GetZoomPiSensorLevel, 0xffaa2b18)
NSTUB(eventproc_EnableZoomEncoderCircuit, 0xffaa2b30)
NSTUB(eventproc_DisableZoomEncoderCircuit, 0xffaa2b40)
NSTUB(eventproc_SendMechaCircuitData, 0xffaa2b50)
NSTUB(eventproc_ReceiveMechaCircuitDataAll, 0xffaa2b90)

NSTUB(eventproc_MoveLensToFirstPointEvent, 0xffaa56dc)
NSTUB(eventproc_MoveLensToTerminatePointEvent, 0xffaa5754)
NSTUB(eventproc_PermitLensControllerFocusReset, 0xffaa57a4)
NSTUB(eventproc_PermitLensControllerFocusInfinity, 0xffaa57b4)
NSTUB(eventproc_IsLensOutside, 0xffaa57c4)
NSTUB(eventproc_GetLensErrorStatus, 0xffaa57d0)

NSTUB(eventproc_ResetZoomLens, 0xffaa6d94)
NSTUB(eventproc_ResetZoomLensToFirstPoint, 0xffaa6dc4)
NSTUB(eventproc_ResetZoomLensToTermiantePoint, 0xffaa6e38)
NSTUB(eventproc_MoveZoomLensWithPoint, 0xffaa6eac)
NSTUB(eventproc_MoveZoomLensWithPosition, 0xffaa6f28)
NSTUB(eventproc_MoveZoomLensToTerminatePosition, 0xffaa6f7c)
NSTUB(eventproc_GetZoomLensCurrentPoint, 0xffaa6fcc)
NSTUB(eventproc_GetZoomLensCurrentPosition, 0xffaa6fe0)
NSTUB(eventproc_GetZoomLensTelePoint, 0xffaa6ff4)

NSTUB(eventproc_SetZoomLensNormalControlGain, 0xffaa86a0)

NSTUB(eventproc_SetZoomLensResetControlGain, 0xffaa9f78)

NSTUB(eventproc_MoveZoomActuator, 0xffaaca20)
NSTUB(eventproc_SetZoomActuatorSpeedPPS, 0xffaaca6c)
NSTUB(eventproc_GetZoomActuatorSpeedPPS, 0xffaaca80)
NSTUB(eventproc_SetZoomActuatorSpeedControlGain, 0xffaaca94)
NSTUB(eventproc_GetZoomActuatorSpeedControlGain, 0xffaacaa8)
NSTUB(eventproc_SetZoomActuatorLimitAmpere, 0xffaacabc)
NSTUB(eventproc_GetZoomActuatorLimitAmpere, 0xffaacad0)
NSTUB(eventproc_SetZoomActuatorPwmDuty, 0xffaacae4)
NSTUB(eventproc_SetZoomActuatorPwmFixedTime, 0xffaacaf8)
NSTUB(eventproc_GetZoomActuatorCurrentPosition, 0xffaacb0c)
NSTUB(eventproc_IsZoomActuatorResetSensorPlusSide, 0xffaacb58)
NSTUB(eventproc_SetDCMotorSpeedLevel, 0xffaacb64)
NSTUB(eventproc_SetDCMotorChargePump, 0xffaacb78)
NSTUB(eventproc_SetDCMotorPwmFixedTimeLevel, 0xffaacb8c)
NSTUB(eventproc_SetDCMotorPwmLevel, 0xffaacba0)
NSTUB(eventproc_SetPM3ByGpio, 0xffaacbb4)
NSTUB(eventproc_ClearPM3ByGpio, 0xffaacbc4)
NSTUB(eventproc_ClearPM3ByFs, 0xffaacbd4)
NSTUB(eventproc_MoveDCMotorCW, 0xffaacbe4)
NSTUB(eventproc_MoveDCMotorCCW, 0xffaacc40)
NSTUB(eventproc_StopDCMotor, 0xffaacc9c)
NSTUB(eventproc_SetDCMotorWaitTime, 0xffaaccbc)
NSTUB(eventproc_GetCurrentEncoderPosition, 0xffaaccd4)

NSTUB(eventproc_ResetIrisEvent, 0xffaaddfc)
NSTUB(eventproc_MoveIrisWithAvEvent, 0xffaade2c)
NSTUB(eventproc_MoveIrisToTerminatePositionEvent, 0xffaade60)
NSTUB(eventproc_GetIrisAvEvent, 0xffaade68)
NSTUB(eventproc_MoveIrisWithAvWithoutBacklashEvent, 0xffaade7c)

NSTUB(eventproc_CloseMechaShutterEvent, 0xffaaf1b8)
NSTUB(eventproc_OpenMechaShutterEvent, 0xffaaf1e8)
NSTUB(eventproc_CloseMechaShutterWithTimingEvent, 0xffaaf218)
NSTUB(eventproc_SetMechaShutterDacSettingEvent, 0xffaaf25c)
NSTUB(eventproc_SetMechaShutterOpenDacSettingEvent, 0xffaaf270)
NSTUB(eventproc_SetMechaShutterFinalDacSettingEvent, 0xffaaf284)
NSTUB(eventproc_SetMechaShutterOpenFinalDacSettingEvent, 0xffaaf298)
NSTUB(eventproc_SetMechaShutterWaitTimeSettingEvent, 0xffaaf2ac)
NSTUB(eventproc_GetMechaShutterStatusEvent, 0xffaaf2c0)
NSTUB(eventproc_SaveMechaShutterCount, 0xffaaf2cc)
NSTUB(eventproc_GetMechaShutterCount, 0xffaaf308)
NSTUB(eventproc_ClearMechaShutterCount, 0xffaaf358)

NSTUB(eventproc_TurnOnNdFilterEvent, 0xffaafc2c)
NSTUB(eventproc_TurnOffNdFilterEvent, 0xffaafc5c)
NSTUB(eventproc_SetNdFilterDacSettingEvent, 0xffaafc8c)

NSTUB(eventproc_MoveFocusLensWithDistance, 0xffab7674)
NSTUB(eventproc_ResetFocusLens, 0xffab7740)
NSTUB(eventproc_MoveFocusLensToTerminate, 0xffab77a0)
NSTUB(eventproc_MoveFocusLensWithPosition, 0xffab7814)
NSTUB(eventproc_MoveFocusLensWithPositionWithoutBacklash, 0xffab78e4)
NSTUB(eventproc_MoveFocusActuator, 0xffab79b4)
NSTUB(eventproc_GetFocusLensCurrentPosition, 0xffab7a70)
NSTUB(eventproc_GetFocusLensResetPosition, 0xffab7a84)
NSTUB(eventproc_GetFocusLensResetPositionForInside, 0xffab7a98)
NSTUB(eventproc_GetFocusLensResetPositionForOutside, 0xffab7aac)
NSTUB(eventproc_GetFocusLensResetDefaultPosition, 0xffab7ac0)
NSTUB(eventproc_SetFocusLensDefaultCondition, 0xffab7ad4)
NSTUB(eventproc_SetFocusLensCondition, 0xffab7aec)
NSTUB(eventproc_GetFocusLensMoveCompleteTime, 0xffab7be0)
NSTUB(eventproc_GetFocusLensNdCoefficientPulse, 0xffab7bec)
NSTUB(eventproc_GetFocusLensSettingMaxSpeed, 0xffab7c00)
NSTUB(eventproc_GetFocusLensSettingMaxSpeedByDeltaType, 0xffab7c14)
NSTUB(eventproc_SetFocusLensMaxSpeedLimit, 0xffab7c28)
NSTUB(eventproc_CancelFocusLensMaxSpeedLimit, 0xffab7c40)
NSTUB(eventproc_EscapeFocusLens, 0xffab7c54)
NSTUB(eventproc_GetFocusLensSubjectDistance, 0xffab7ce8)
NSTUB(eventproc_GetFocusLensSubjectDistanceFromLens, 0xffab7d0c)
NSTUB(eventproc_EnableFocusLens, 0xffab7d30)
NSTUB(eventproc_SetFocusLensBacklashSpeedToMax, 0xffab7d94)
NSTUB(eventproc_ClearFocusLensBacklashSpeedToMax, 0xffab7da4)
NSTUB(eventproc_CheckFocusLensAfAging, 0xffab7e44)

NSTUB(eventproc_MoveCZToPointEvent, 0xffab9dc4)
NSTUB(eventproc_MoveCZToWideEvent, 0xffab9e18)
NSTUB(eventproc_MoveCZToTeleEvent, 0xffab9e60)

NSTUB(eventproc_TurnOnAFLampEvent, 0xffaba058)
NSTUB(eventproc_TurnOffAFLampEvent, 0xffaba070)

NSTUB(eventproc_FA_Create, 0xffabd2c8)
NSTUB(eventproc_FA_Delete, 0xffabd2fc)

NSTUB(eventproc_InitializeAdjustmentSystem, 0xffabde6c)
NSTUB(eventproc_TerminateAdjustmentSystem, 0xffabdeb4)
NSTUB(eventproc_InitializeAdjustmentFunction, 0xffabdefc)

NSTUB(eventproc_MakeBootDisk, 0xffaecaa8)
NSTUB(eventproc_MakeScriptDisk, 0xffaecabc)

NSTUB(eventproc_LoadScript, 0xffaee510)
NSTUB(eventproc_UnLoadScript, 0xffaee520)
NSTUB(eventproc_Printf, 0xffaee534)
NSTUB(eventproc_ScriptDisEnabled, 0xffaee54c)
NSTUB(eventproc_ScriptEnabled, 0xffaee560)

NSTUB(eventproc_GetLogToFile, 0xffaf6908)

NSTUB(eventproc_MemoryChecker, 0xffaf7c8c)
NSTUB(eventproc_VerifyByte, 0xffaf7dbc)

