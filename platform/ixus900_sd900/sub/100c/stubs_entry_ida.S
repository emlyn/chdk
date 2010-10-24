
NSTUB(eventproc_StopClockSaver, 0xff812f78)
NSTUB(eventproc_SetLClk72MHz, 0xff812f94)
NSTUB(eventproc_SetLClk36MHz, 0xff812fa4)
NSTUB(eventproc_SetLClk18MHz, 0xff812fb4)

NSTUB(eventproc_SetHClk72MHz, 0xff81306c)
NSTUB(eventproc_SetHClk36MHz, 0xff8130b0)
NSTUB(eventproc_SetHClk18MHz, 0xff8130d8)
NSTUB(eventproc_SetMClk72MHz, 0xff81311c)
NSTUB(eventproc_SetMClk36MHz, 0xff813128)
NSTUB(eventproc_SetMClk18MHz, 0xff813134)

NSTUB(eventproc_PutsCameraLogEvent, 0xff81824c)
NSTUB(eventproc_ShowCameraLog, 0xff8183f8)

NSTUB(eventproc_StopCameraLog, 0xff8186d8)

NSTUB(eventproc_export_StartWDT, 0xff81a4f8)
NSTUB(eventproc_export_StopWDT, 0xff81a574)

NSTUB(eventproc_export_GetBuildDate, 0xff81a6e8)
NSTUB(eventproc_export_GetBuildTime, 0xff81a700)
NSTUB(eventproc_export_GetFirmwareVersion, 0xff81a724)

NSTUB(eventproc_export_RomCheckSum, 0xff81a80c)
NSTUB(eventproc_export_CheckSumAll, 0xff81a8a0)
NSTUB(eventproc_SystemEventDelete, 0xff81aa48)
NSTUB(eventproc_SystemEventInit, 0xff81aa80)

NSTUB(eventproc_export_Dump32, 0xff81ab48)
NSTUB(eventproc_FreeMemory, 0xff81ac5c)
NSTUB(eventproc_AllocateMemory, 0xff81ac70)
NSTUB(eventproc_Wait, 0xff81ac80)
NSTUB(eventproc_Poke32, 0xff81ac94)
NSTUB(eventproc_Poke16, 0xff81acb8)
NSTUB(eventproc_Poke8, 0xff81acdc)
NSTUB(eventproc_Peek32, 0xff81ad00)
NSTUB(eventproc_Peek16, 0xff81ad1c)
NSTUB(eventproc_Peek8, 0xff81ad38)
NSTUB(eventproc_EraseSignature, 0xff81ad54)
NSTUB(eventproc_GetSystemTime, 0xff81ad84)
NSTUB(eventproc_MonSelEvent, 0xff81ada4)
NSTUB(eventproc_exec, 0xff81addc)

NSTUB(eventproc_init, 0xff81b1b4)

NSTUB(eventproc_StartUARTRedirect, 0xff8206cc)
NSTUB(eventproc_StopUARTRedirect, 0xff8206e4)

NSTUB(eventproc_Driver_EnableEventProc, 0xff826f20)

NSTUB(eventproc_ShowPhySwStatus, 0xff8286dc)
NSTUB(eventproc_OnPrintPhySw, 0xff8287d0)
NSTUB(eventproc_OffPrintPhySw, 0xff8287e8)
NSTUB(eventproc_GetSwitchStatus, 0xff8287fc)

NSTUB(eventproc_OnPrintHVSw, 0xff8298f0)
NSTUB(eventproc_OffPrintHVSw, 0xff829908)
NSTUB(eventproc_GetHVSw, 0xff82991c)
NSTUB(eventproc_OnPrintHVStatus, 0xff82992c)
NSTUB(eventproc_OffPrintHVStatus, 0xff829940)

NSTUB(eventproc_SetFeatherDivision, 0xff82ae14)
NSTUB(eventproc_SetFeatherInterval, 0xff82ae3c)
NSTUB(eventproc_OnPrintFeather, 0xff82ae50)
NSTUB(eventproc_OffPrintFeather, 0xff82ae68)
NSTUB(eventproc_SetFeatherPrintInterval, 0xff82ae7c)

NSTUB(eventproc_GetAdChValue, 0xff82b5bc)
NSTUB(eventproc_GetAdVBattBottom, 0xff82b5ec)

NSTUB(eventproc_SetBattCheckMode, 0xff82cf34)
NSTUB(eventproc_ShowBattCheckMode, 0xff82cfbc)
NSTUB(eventproc_ShowBattChkAdj, 0xff82d0b0)
NSTUB(eventproc_GetLBOffset, 0xff82d28c)
NSTUB(eventproc_LowBat_Result_Print_On, 0xff82d29c)
NSTUB(eventproc_LowBat_Result_Print_Off, 0xff82d2b4)
NSTUB(eventproc_BatVoltageToAd, 0xff82d2c8)

NSTUB(eventproc_VbattGet, 0xff82e420)

NSTUB(eventproc_GetOpticalTemperature, 0xff82f55c)
NSTUB(eventproc_GetCCDTemperature, 0xff82f570)
NSTUB(eventproc_GetBatteryTemperature, 0xff82f584)

NSTUB(eventproc_PrePro_Unpack, 0xff8b06a8)

NSTUB(eventproc_OutPort, 0xff8b5e50)
NSTUB(eventproc_InPort, 0xff8b5e64)

NSTUB(eventproc_ActivateImager, 0xff8e93a0)
NSTUB(eventproc_QuietImager, 0xff8e9450)

NSTUB(eventproc_CancelImager, 0xff8e96c0)
NSTUB(eventproc_ChangeImagerToWholeSerial, 0xff8e96f0)
NSTUB(eventproc_ChangeImagerToWholeSerialLineDef, 0xff8e9708)
NSTUB(eventproc_ChangeImagerToWholeParallel, 0xff8e9720)
NSTUB(eventproc_ChangeImagerToWholeParallelHalf, 0xff8e973c)
NSTUB(eventproc_ChangeImagerToSuperWideDraft, 0xff8e974c)
NSTUB(eventproc_ChangeImagerToWideDraft, 0xff8e975c)
NSTUB(eventproc_ChangeImagerToNarrowDraft, 0xff8e976c)
NSTUB(eventproc_ChangeImagerToAlternateDraft, 0xff8e977c)
NSTUB(eventproc_ChangeImagerToJetDraft, 0xff8e978c)
NSTUB(eventproc_ChangeImagerToPetitNarrow, 0xff8e979c)
NSTUB(eventproc_ChangeImagerToFocusJet, 0xff8e97ac)
NSTUB(eventproc_ChangeImagerToJumboDraft, 0xff8e97bc)
NSTUB(eventproc_ChangeImagerToMillefeAdjust, 0xff8e97cc)
NSTUB(eventproc_ChangeImagerToHoneyFlash, 0xff8e97dc)
NSTUB(eventproc_ChangeImagerToMangoPudding, 0xff8e97ec)
NSTUB(eventproc_ChangeImagerToMontblancWhole, 0xff8e97fc)
NSTUB(eventproc_ChangeImagerToMontblancMillefe, 0xff8e980c)
NSTUB(eventproc_ChangeImagerToOITA_XAVIER, 0xff8e981c)
NSTUB(eventproc_ChangeImagerToQVGA20Fps, 0xff8e982c)
NSTUB(eventproc_ChangeImagerToQVGA15Fps, 0xff8e983c)
NSTUB(eventproc_ChangeImagerToSmearCorrectWide, 0xff8e984c)
NSTUB(eventproc_ChangeImagerToSmearCorrectSuper, 0xff8e985c)
NSTUB(eventproc_ChangeImagerToSmearCorrectAlternate, 0xff8e986c)
NSTUB(eventproc_ChangeImagerToXXX, 0xff8e987c)
NSTUB(eventproc_SetStartLineForNarrowDraft, 0xff8e988c)
NSTUB(eventproc_WithdrawalImagerForEmergency, 0xff8e98a0)
NSTUB(eventproc_StillOnMovieTest, 0xff8e98bc)
NSTUB(eventproc_SetSmearOn, 0xff8e99d8)
NSTUB(eventproc_SetSmearOff, 0xff8e99ec)
NSTUB(eventproc_ChangeUseAf, 0xff8e9a00)

NSTUB(eventproc_SetMontblancVSize, 0xff8ebd88)
NSTUB(eventproc_GetMontblancVSize, 0xff8ebda0)

NSTUB(eventproc_VirtualHeadError, 0xff8ec5a8)

NSTUB(eventproc_export_EnableOBClampField, 0xff8eefd0)
NSTUB(eventproc_export_DisableOBClampField, 0xff8eefe8)

NSTUB(eventproc_export_VirtualImageTimeOut, 0xff8f81c4)

NSTUB(eventproc_EF_StartEFCharge, 0xff933694)
NSTUB(eventproc_EF_StopEFCharge, 0xff9336f4)
NSTUB(eventproc_EF_SetEFChargeTimeOut, 0xff933704)
NSTUB(eventproc_EF_StartInternalPreFlash, 0xff933718)
NSTUB(eventproc_EF_StartInternalMainFlash, 0xff93375c)
NSTUB(eventproc_EF_SetMainFlashTime, 0xff9337ec)
NSTUB(eventproc_EF_IsChargeFull, 0xff933800)
NSTUB(eventproc_EF_AdjPreFlash, 0xff93380c)
NSTUB(eventproc_EF_SetChargeMode, 0xff933874)

NSTUB(eventproc_ChangeGradeTable, 0xff95455c)

NSTUB(eventproc_RenewThermoLogNo, 0xff9546dc)

NSTUB(eventproc_PointDefDetect, 0xff954858)
NSTUB(eventproc_PointKizuCheck, 0xff954980)
NSTUB(eventproc_ClearDefectCount, 0xff954a54)
NSTUB(eventproc_GetDefectCount, 0xff954a64)
NSTUB(eventproc_LineDefDetect, 0xff954a88)
NSTUB(eventproc_LineKizuCheck, 0xff954b44)

NSTUB(eventproc_DispDev_EnableEventProc, 0xff9570a4)

NSTUB(eventproc_CheckLensAndShutdownReason, 0xff98e4bc)
NSTUB(eventproc_StartupZoom, 0xff98e4c4)
NSTUB(eventproc_ActivateImageSystem, 0xff98e550)
NSTUB(eventproc_NotifyStartupImageCreated, 0xff98e5a8)
NSTUB(eventproc_CompleteInitPTM, 0xff98e5b8)

NSTUB(eventproc_StoreLensForShutDown, 0xff98e624)
NSTUB(eventproc_ShutdownImageSystem, 0xff98e6a4)

NSTUB(eventproc_ShutdownRec, 0xff98e790)
NSTUB(eventproc_EmergencyOfLens, 0xff98e80c)
NSTUB(eventproc_StopLens, 0xff98e82c)
NSTUB(eventproc_IsEmptyWriteCache, 0xff98e8c8)
NSTUB(eventproc_FlushWriteCache, 0xff98e8e8)
NSTUB(eventproc_EnterToRecFromPlay, 0xff98e900)
NSTUB(eventproc_EnterToPlayFromRec, 0xff98e914)
NSTUB(eventproc_IsLensExtend, 0xff98e928)

NSTUB(eventproc_MoveOpticalZoomToTele, 0xff98e9a8)
NSTUB(eventproc_MoveOpticalZoomToWide, 0xff98e9c8)
NSTUB(eventproc_StopOpticalZoom, 0xff98e9e8)
NSTUB(eventproc_MoveOpticalZoomAt, 0xff98e9f8)
NSTUB(eventproc_, 0xff98ea24)

NSTUB(eventproc_ChangeZoomSpeed, 0xff98ea7c)

NSTUB(eventproc_MoveDigitalZoomToTele, 0xff98eb24)
NSTUB(eventproc_MoveDigitalZoomToWide, 0xff98eb34)
NSTUB(eventproc_StopDigitalZoom, 0xff98eb44)
NSTUB(eventproc_MoveDigitalZoomAt, 0xff98eb54)

NSTUB(eventproc_PrepareCaptureModeChange, 0xff98ebc0)
NSTUB(eventproc_CaptureModeChange, 0xff98ebfc)
NSTUB(eventproc_StopFocus, 0xff98ed30)
NSTUB(eventproc_AFFrameMoved, 0xff98ed78)
NSTUB(eventproc_AFFrameSettingChanged, 0xff98ed94)

NSTUB(eventproc_GetMFBarData, 0xff98edcc)
NSTUB(eventproc_AFDistanceChanged, 0xff98edf0)
NSTUB(eventproc_GetMacroSupportZoomPoint, 0xff98ee08)
NSTUB(eventproc_DoAFLock, 0xff98ee30)
NSTUB(eventproc_UnlockAF, 0xff98ee7c)
NSTUB(eventproc_AFCOn, 0xff98eea8)
NSTUB(eventproc_AFCOff, 0xff98eecc)
NSTUB(eventproc_GetNextFaceFrame, 0xff98eeec)
NSTUB(eventproc_ResetFaceFrame, 0xff98ef00)
NSTUB(eventproc_SetFaceFrameMovableArea, 0xff98ef10)

NSTUB(eventproc_EnterToCompensationEVF, 0xff98f004)
NSTUB(eventproc_ExitFromCompensationEVF, 0xff98f044)
NSTUB(eventproc_RectifyExposureWithMeasure, 0xff98f054)
NSTUB(eventproc_UpdateEVF, 0xff98f094)
NSTUB(eventproc_DoAELock, 0xff98f09c)
NSTUB(eventproc_UnlockAE, 0xff98f0bc)
NSTUB(eventproc_GetProgramShiftLimitPositive, 0xff98f0d8)
NSTUB(eventproc_GetProgramShiftLimitNegative, 0xff98f0fc)
NSTUB(eventproc_FixProgramShift, 0xff98f13c)
NSTUB(eventproc_GetProgShiftedAv, 0xff98f174)
NSTUB(eventproc_GetProgShiftedTv, 0xff98f19c)
NSTUB(eventproc_StartFinder, 0xff98f1d4)
NSTUB(eventproc_StopFinder, 0xff98f220)
NSTUB(eventproc_StartPCEVF, 0xff98f25c)
NSTUB(eventproc_StopPCEVF, 0xff98f264)
NSTUB(eventproc_SuspendPcEvf, 0xff98f26c)
NSTUB(eventproc_ResumePcEvf, 0xff98f274)
NSTUB(eventproc_StartStitchEVF, 0xff98f27c)
NSTUB(eventproc_StopStitchEVF, 0xff98f2c0)
NSTUB(eventproc_SetPointStitchEVF, 0xff98f2d4)
NSTUB(eventproc_IsHighSensitiveISO, 0xff98f2f0)
NSTUB(eventproc_IsStrobeChargeCompleted, 0xff98f320)
NSTUB(eventproc_StrobeModeChanged, 0xff98f35c)
NSTUB(eventproc_WBModeChanged, 0xff98f36c)
NSTUB(eventproc_ColorModeChanged, 0xff98f37c)
NSTUB(eventproc_ISOSpeedChanged, 0xff98f38c)
NSTUB(eventproc_LightMeteringModeChanged, 0xff98f3a0)
NSTUB(eventproc_DisplayTypeChanged, 0xff98f3a8)
NSTUB(eventproc_MyColorModeChange, 0xff98f3b8)
NSTUB(eventproc_MyColorMenuIn, 0xff98f3c8)
NSTUB(eventproc_MyColorMenuOut, 0xff98f3d8)
NSTUB(eventproc_ShootColor, 0xff98f3e8)
NSTUB(eventproc_NDFilter, 0xff98f418)
NSTUB(eventproc_NotifyResolutionChanged, 0xff98f478)
NSTUB(eventproc_NotifyISModeChanged, 0xff98f4a0)
NSTUB(eventproc_NotifyConvLensSettingChanged, 0xff98f4a8)
NSTUB(eventproc_MenuIn, 0xff98f4b0)
NSTUB(eventproc_PrepareMenuOut, 0xff98f4c8)
NSTUB(eventproc_MenuOut, 0xff98f4e4)
NSTUB(eventproc_MyCameraIn, 0xff98f518)
NSTUB(eventproc_MyCameraOut, 0xff98f528)
NSTUB(eventproc_LcdBrightnessMenuIn, 0xff98f538)
NSTUB(eventproc_LcdBrightnessMenuOut, 0xff98f548)
NSTUB(eventproc_AllSettingReseted, 0xff98f558)
NSTUB(eventproc_UndisplayEVF, 0xff98f588)

NSTUB(eventproc_PrepareStrobeCharge, 0xff98f5e4)

NSTUB(eventproc_PrepareCapture, 0xff98f618)
NSTUB(eventproc_ShootPicture, 0xff98f6ac)
NSTUB(eventproc_SW1Lock, 0xff98f6d0)
NSTUB(eventproc_StartBridgeEVF, 0xff98f6e0)
NSTUB(eventproc_StopContinuousShooting, 0xff98f718)
NSTUB(eventproc_CancelPrepare, 0xff98f728)

NSTUB(eventproc_ShootWhite, 0xff98f798)

NSTUB(eventproc_ExitShooting, 0xff98f8bc)
NSTUB(eventproc_StartRecreview, 0xff98f8d0)
NSTUB(eventproc_StopRecreview, 0xff98f8e0)
NSTUB(eventproc_RecreviewHold, 0xff98f8e8)
NSTUB(eventproc_RecreviewRelease, 0xff98f8f8)
NSTUB(eventproc_MovieParamChanged, 0xff98f908)

NSTUB(eventproc_RecordMovie, 0xff98f9b0)
NSTUB(eventproc_StopRecordMovie, 0xff98f9cc)
NSTUB(eventproc_IsAvailStillOnMovie, 0xff98f9dc)
NSTUB(eventproc_PrepareLensForStandby, 0xff98f9e8)
NSTUB(eventproc_EnterToRemoteCaptureMode, 0xff98f9f0)
NSTUB(eventproc_ExitFromRemoteCaptureMode, 0xff98f9f8)

NSTUB(eventproc_StopClockMode, 0xff98fa08)

NSTUB(eventproc_StartupForTestRec, 0xff98fb40)
NSTUB(eventproc_PrepareTestRec, 0xff98fbc4)
NSTUB(eventproc_ExitTestRec, 0xff98fbd0)
NSTUB(eventproc_MFOn, 0xff98fbf0)
NSTUB(eventproc_MFOff, 0xff98fc20)
NSTUB(eventproc_ExecuteScript, 0xff98fc60)

NSTUB(eventproc_SS_DumpShootInfo, 0xff992098)

NSTUB(eventproc_NR_SetDarkSubType, 0xff999a98)
NSTUB(eventproc_NR_SetDefectCorrectType, 0xff999af4)
NSTUB(eventproc_NR_GetDarkSubType, 0xff999b28)
NSTUB(eventproc_NR_GetDefectCorrectType, 0xff999b74)
NSTUB(eventproc_NR_SetLotasPonyType, 0xff999bc0)

NSTUB(eventproc_PT_CompletePreCapt, 0xff99ee70)
NSTUB(eventproc_PT_RecreviewAvailable, 0xff99ee78)
NSTUB(eventproc_PT_NextShootAvailable, 0xff99ee80)
NSTUB(eventproc_PT_CompleteStopZoom, 0xff99ee88)
NSTUB(eventproc_PT_CompleteStopDigZoom, 0xff99ee90)
NSTUB(eventproc_PT_CompleteStoreLens, 0xff99ee98)
NSTUB(eventproc_PT_CompletePrepareLens, 0xff99eea0)
NSTUB(eventproc_PT_MovieRecordStopped, 0xff99eea8)
NSTUB(eventproc_PT_CompleteCaptModeChange, 0xff99eeb0)
NSTUB(eventproc_PT_CompleteSynchroWrite, 0xff99eeb8)
NSTUB(eventproc_PT_CompleteCharge, 0xff99eec0)
NSTUB(eventproc_export_PT_EraseAllFile, 0xff99eec8)
NSTUB(eventproc_export_PT_mod, 0xff99ef00)
NSTUB(eventproc_export_PT_atoi, 0xff99ef0c)
NSTUB(eventproc_export_PT_GetSystemTime, 0xff99ef18)
NSTUB(eventproc_export_PT_SetPropertyCaseString, 0xff99ef38)
NSTUB(eventproc_export_PT_SetPropertyCaseInt, 0xff99ef4c)
NSTUB(eventproc_export_PT_GetPropertyCaseString, 0xff99ef74)
NSTUB(eventproc_export_PT_GetPropertyCaseInt, 0xff99ef88)
NSTUB(eventproc_export_PT_GetLocalTimeString, 0xff99f034)
NSTUB(eventproc_export_PT_GetLocalDateString, 0xff99f090)
NSTUB(eventproc_export_PT_GetLocalDateAndTimeString, 0xff99f0f4)
NSTUB(eventproc_export_PT_GetLocalYearString, 0xff99f148)
NSTUB(eventproc_export_PT_GetLocalMonthString, 0xff99f19c)
NSTUB(eventproc_export_PT_GetLocalHourMinSecString, 0xff99f1f8)
NSTUB(eventproc_export_PT_GetLocalDayString, 0xff99f28c)
NSTUB(eventproc_export_PT_SetMessage, 0xff99f2dc)
NSTUB(eventproc_export_PT_UndispMessage, 0xff99f304)
NSTUB(eventproc_export_PT_PlaySound, 0xff99f320)
NSTUB(eventproc_export_PT_LCD_BkColor, 0xff99f338)
NSTUB(eventproc_export_PT_LCD_BkColorDef, 0xff99f3f4)
NSTUB(eventproc_export_PT_BatLvChange_PreWeak, 0xff99f428)
NSTUB(eventproc_export_PT_BatLvChange_Weak, 0xff99f430)
NSTUB(eventproc_export_PT_BatLvChange_Low, 0xff99f438)
NSTUB(eventproc_export_PT_BatLvChange_SysLow, 0xff99f440)
NSTUB(eventproc_export_PT_StartBatteryTest, 0xff99f458)
NSTUB(eventproc_export_PT_FinishBatteryTest, 0xff99f4b8)

NSTUB(eventproc_export_PT_GetBatteryLevel, 0xff99f5b0)
NSTUB(eventproc_export_PT_GetPreWeakBatLv, 0xff99f5c8)
NSTUB(eventproc_export_PT_GetWeakBatLv, 0xff99f630)
NSTUB(eventproc_export_PT_GetLowBatLv, 0xff99f698)
NSTUB(eventproc_export_PT_GetSysLowBatLv, 0xff99f700)
NSTUB(eventproc_export_UiMemory_Show, 0xff99f778)

NSTUB(eventproc_export_HardwareDefect, 0xff99fa2c)
NSTUB(eventproc_export_HardwareDefectWithRestart, 0xff99fa5c)

NSTUB(eventproc_ShowErrorNumberList, 0xff99faf4)

NSTUB(eventproc_export_CreateController, 0xff9a0c84)
NSTUB(eventproc_export_DeleteController, 0xff9a0d3c)
NSTUB(eventproc_export_MoveControllerToTopOfZOrder, 0xff9a0e74)
NSTUB(eventproc_export_GetSelfControllerHandle, 0xff9a0fac)

NSTUB(eventproc_export_PostLogicalEventForNotPowerType, 0xff9a4230)
NSTUB(eventproc_export_PostLogicalEventToUI, 0xff9a42ac)
NSTUB(eventproc_export_PostEventShootSeqToUI, 0xff9a4334)
NSTUB(eventproc_export_ShowLogicalEventName, 0xff9a439c)

NSTUB(eventproc_export_LogiEvnt_LoadCameraLog, 0xff9a44e4)

NSTUB(eventproc_export_IsControlEventActive, 0xff9a62a0)

NSTUB(eventproc_export_SetScriptMode, 0xff9a6394)
NSTUB(eventproc_export_UiEvnt_ShowBitMaps, 0xff9a63a4)

NSTUB(eventproc_export_UiEvnt_StartDisguiseCradleStatus, 0xff9a6404)
NSTUB(eventproc_export_UiEvnt_StopDisguiseCradleStatus, 0xff9a6418)

NSTUB(eventproc_export_IsDisableAutoShutdown, 0xff9a8364)

NSTUB(eventproc_export_ShowAutoShutdownTime, 0xff9a8438)
NSTUB(eventproc_export_DisableAutoShutdown, 0xff9a846c)
NSTUB(eventproc_export_EnableAutoShutdown, 0xff9a8484)

NSTUB(eventproc_export_SetAutoShutdownTime, 0xff9a8718)
NSTUB(eventproc_export_LockMainPower, 0xff9a8814)
NSTUB(eventproc_export_UnlockMainPower, 0xff9a88ac)
NSTUB(eventproc_export_GetMainPowerLockCounter, 0xff9a89b0)

NSTUB(eventproc_PTM_AllResetToFactorySetting, 0xff9ab344)
NSTUB(eventproc_PTM_AllResetProperty, 0xff9ab354)

NSTUB(eventproc_PTM_GetWorkingCaptureMode, 0xff9ab54c)

NSTUB(eventproc_export_PTM_RestoreUIProperty, 0xff9ab804)

NSTUB(eventproc_PTM_SetCurrentCaptureMode, 0xff9abec8)
NSTUB(eventproc_PTM_SetCurrentItem, 0xff9abed8)
NSTUB(eventproc_PTM_GetCurrentItem, 0xff9abef8)
NSTUB(eventproc_PTM_NextItem, 0xff9abf10)
NSTUB(eventproc_PTM_PrevItem, 0xff9abf28)
NSTUB(eventproc_PTM_BackupUIProperty, 0xff9abf40)
NSTUB(eventproc_PTM_SetProprietyEnable, 0xff9abf64)

NSTUB(eventproc_export_CreateDialogBox, 0xff9b2a04)
NSTUB(eventproc_export_DeleteDialogBox, 0xff9b2bfc)
NSTUB(eventproc_export_ResizeVirtualWindow, 0xff9b2ca0)
NSTUB(eventproc_export_MoveDialogBoxPosition, 0xff9b2ccc)
NSTUB(eventproc_export_DeleteDialogBoxAfterGetTopOfControl, 0xff9b2d6c)
NSTUB(eventproc_export_SetPropertyToDialogItemWithID, 0xff9b2d90)
NSTUB(eventproc_export_GetPropertyFromDialogItemWithID, 0xff9b2dc0)

NSTUB(eventproc_export_AddItemToDialogBox, 0xff9b2e58)
NSTUB(eventproc_export_DeleteItemFromDialogBox, 0xff9b2f2c)
NSTUB(eventproc_export_SetFocusDirectionToDialogItem, 0xff9b3018)
NSTUB(eventproc_export_SetFocusItemToDialogItem, 0xff9b3028)
NSTUB(eventproc_export_GetFocusedItemIDOfDialogItem, 0xff9b313c)
NSTUB(eventproc_export_GetItemHandleOfDialogBox, 0xff9b3174)
NSTUB(eventproc_export_DisplayDialogBox, 0xff9b3214)
NSTUB(eventproc_export_UndisplayDialogBox, 0xff9b323c)
NSTUB(eventproc_export_SetBackgroundColorToDialogBox, 0xff9b3264)
NSTUB(eventproc_export_RefreshRectangleToDialog, 0xff9b32b8)

NSTUB(eventproc_export_RegisterRefreshToDialog, 0xff9b3340)
NSTUB(eventproc_export_RefreshRegistedRectangleToDialog, 0xff9b3404)
NSTUB(eventproc_export_FillRectangleToDialog, 0xff9b3478)
NSTUB(eventproc_export_DrawStringToDialog, 0xff9b34d8)
NSTUB(eventproc_export_TransferRectangleToDialog, 0xff9b3538)
NSTUB(eventproc_export_TransferBitmapToDialog, 0xff9b35a8)
NSTUB(eventproc_export_DrawBinaryBitmapToDialog, 0xff9b3628)
NSTUB(eventproc_export_GetDialogBoxWindow, 0xff9b3690)
NSTUB(eventproc_export_SetFocusScopeToDialog, 0xff9b36b0)
NSTUB(eventproc_export_GetFocusScopeToDialog, 0xff9b3720)
NSTUB(eventproc_export_MoveViewPortPosition, 0xff9b376c)
NSTUB(eventproc_export_ResizeDialogBox, 0xff9b37d0)
NSTUB(eventproc_export_MoveDialogControllerToTopOfZOrder, 0xff9b381c)
NSTUB(eventproc_export_MoveDialogItemPositionToDialog, 0xff9b3840)
NSTUB(eventproc_export_ResizeDialogItemToDialog, 0xff9b3874)
NSTUB(eventproc_export_GetDialogItemPositionToDialog, 0xff9b38a8)
NSTUB(eventproc_export_GetDialogItemResolutionToDialog, 0xff9b38dc)
NSTUB(eventproc_export_SetOriginTypeToDialog, 0xff9b3910)
NSTUB(eventproc_export_SetDefaultMovingFocusToDialog, 0xff9b3934)
NSTUB(eventproc_export_LockRefreshDialog, 0xff9b3958)
NSTUB(eventproc_export_UnlockRefreshDialog, 0xff9b399c)

NSTUB(eventproc_export_KeepDefaultMoveFocusEventToDialog, 0xff9b3a5c)

NSTUB(eventproc_export_InstallDialogItem, 0xff9b3cd0)
NSTUB(eventproc_export_CreateDialogItem, 0xff9b3dac)
NSTUB(eventproc_export_DeleteDialogItem, 0xff9b3e9c)
NSTUB(eventproc_export_DrawDialogItem, 0xff9b3f1c)
NSTUB(eventproc_export_ControlEventHandler, 0xff9b3fb4)
NSTUB(eventproc_export_SetPropertyToDialogItem, 0xff9b4030)
NSTUB(eventproc_export_GetPropertyFromDialogItem, 0xff9b40a4)
NSTUB(eventproc_export_SetAttributeToDialogItem, 0xff9b4118)
NSTUB(eventproc_export_GetAttributeFromDialogItem, 0xff9b418c)
NSTUB(eventproc_export_MoveDialogItemPosition, 0xff9b41f8)
NSTUB(eventproc_export_ResizeDialogItem, 0xff9b426c)
NSTUB(eventproc_export_GetDialogItemPosition, 0xff9b42ec)
NSTUB(eventproc_export_GetDialogItemResolution, 0xff9b436c)

NSTUB(eventproc_export_StartGUISystem, 0xff9b73bc)

NSTUB(eventproc_ShutdownGUISystem, 0xff9b74e0)

NSTUB(eventproc_export_DeletePalette, 0xff9b7620)
NSTUB(eventproc_export_SetYUVPaletteIndex, 0xff9b7698)

NSTUB(eventproc_export_SetPaletteToPhysicalScreen, 0xff9b77d8)
NSTUB(eventproc_export_GetPaletteFromPhysicalScreen, 0xff9b7830)

NSTUB(eventproc_export_SetCurrentPalette, 0xff9ba2b0)
NSTUB(eventproc_export_SetSystemColorMode, 0xff9ba2c0)

NSTUB(eventproc_export_LockPhysicalScreen, 0xff9be5bc)
NSTUB(eventproc_export_RefreshPhysicalScreen, 0xff9be650)
NSTUB(eventproc_export_EnableRefreshPhysicalScreen, 0xff9be724)
NSTUB(eventproc_export_DisableRefreshPhysicalScreen, 0xff9be738)
NSTUB(eventproc_export_IsEnableRefreshPhysicalScreen, 0xff9be74c)

NSTUB(eventproc_export_PrintBmpVramInfo, 0xff9bf060)
NSTUB(eventproc_export_PrintCurrPalette, 0xff9bf090)

NSTUB(eventproc_export_UI_ShowStateOfRecMode, 0xff9cddd8)
NSTUB(eventproc_export_UIFS_SetDialStillRec, 0xff9cddf0)
NSTUB(eventproc_export_UIFS_SetDialMovieRec, 0xff9cde30)
NSTUB(eventproc_export_UIFS_SetDialPlay, 0xff9cde70)
NSTUB(eventproc_export_UIFS_OpenPopupStrobe, 0xff9cdeb0)
NSTUB(eventproc_export_UIFS_ClosePopupStrobe, 0xff9cdee4)
NSTUB(eventproc_export_UIFS_MountExtFlash, 0xff9cdf18)
NSTUB(eventproc_export_UIFS_UnmountExtFlash, 0xff9cdf4c)
NSTUB(eventproc_export_ModeLevelStillRecForScript, 0xff9cdf80)
NSTUB(eventproc_export_ModeLevelMovieRecForScript, 0xff9cdf8c)
NSTUB(eventproc_export_ModeLevelPlayForScript, 0xff9cdf98)
NSTUB(eventproc_export_UIFS_StopPostingUIEvent, 0xff9cdfa4)
NSTUB(eventproc_export_UIFS_RestartPostingUIEvent, 0xff9cdfb0)
NSTUB(eventproc_export_UIFS_SetCaptureModeToP, 0xff9cdfbc)
NSTUB(eventproc_export_UIFS_SetCaptureModeToM, 0xff9cdff8)
NSTUB(eventproc_export_UIFS_SetCaptureModeToMacro, 0xff9ce034)
NSTUB(eventproc_export_UIFS_Capture, 0xff9ce048)
NSTUB(eventproc_export_UIFS_CaptureNoneStop, 0xff9ce058)
NSTUB(eventproc_export_UIFS_StartMovieRecord, 0xff9ce064)
NSTUB(eventproc_export_UIFS_StopMovieRecord, 0xff9ce070)
NSTUB(eventproc_export_UIFS_SetCradleSetting, 0xff9ce07c)
NSTUB(eventproc_UI_RegistDebugEventProc, 0xff9ce3e8)

NSTUB(eventproc_ExecuteResetFactoryWithRomWrite, 0xff9d3c34)

NSTUB(eventproc_export_SetCurrentCaptureModeType, 0xff9d9b48)
NSTUB(eventproc_export_GetCurrentCaptureModeType, 0xff9d9b98)

NSTUB(eventproc_export_ShootCon_GetStatus, 0xff9dd3dc)

NSTUB(eventproc_export_ShootCon_ShowState, 0xff9e1b08)

NSTUB(eventproc_export_ShootCon_SetEventHook, 0xff9e25b8)
NSTUB(eventproc_export_ShootCon_PrintMemoryDump, 0xff9e25e4)
NSTUB(eventproc_export_ShootCon_ShowAllSemaphores, 0xff9e2670)
NSTUB(eventproc_init_shoot, 0xff9e278c)

NSTUB(eventproc_StartMovieController, 0xff9e3550)
NSTUB(eventproc_EnableMovieController, 0xff9e35bc)
NSTUB(eventproc_DisableMovieController, 0xff9e35d0)
NSTUB(eventproc_ShutdownMovieController, 0xff9e35e4)

NSTUB(eventproc_GetStateOfMovieSequence, 0xff9e451c)

NSTUB(eventproc_ZoomCon_ShowState, 0xff9e7004)

NSTUB(eventproc_export_StartSwitchViewFinder, 0xff9f1788)
NSTUB(eventproc_export_StopSwitchViewFinder, 0xff9f17dc)
NSTUB(eventproc_export_SwitchViewFinder, 0xff9f1808)

NSTUB(eventproc_export_UiComIF_SendEventToUI, 0xff9f5b3c)

NSTUB(eventproc_DeletePlayMyColController, 0xffa34c68)

NSTUB(eventproc_TerminateDpofUI, 0xffa4b764)

NSTUB(eventproc_StartPrintOrderMenu, 0xffa4c728)

NSTUB(eventproc_StartDpofPlayLoading, 0xffa50348)

NSTUB(eventproc_SyncStopDpofPlayLoading, 0xffa5052c)

NSTUB(eventproc_StartTransferOrderMenu, 0xffa50a2c)

NSTUB(eventproc_StartPlayModeMenu, 0xffa53608)

NSTUB(eventproc_StartRecModeMenu, 0xffa536dc)
NSTUB(eventproc_ShutdownRecModeMenu, 0xffa537a0)

NSTUB(eventproc_ShutdownPlayModeMenu, 0xffa53948)
NSTUB(eventproc_ShutdownPlayModeMenuWithoutPbRedraw, 0xffa539f4)

NSTUB(eventproc_InstallRecMenu, 0xffa557d4)

NSTUB(eventproc_InstallPlayMenu, 0xffa58030)

NSTUB(eventproc_InstallSetupMenu, 0xffa5a228)

NSTUB(eventproc_InstallMyCameraMenu, 0xffa5d1a4)

NSTUB(eventproc_IsCalledStopEVF, 0xffa5e7e4)

NSTUB(eventproc_ShutdownRecAllMenu, 0xffa5ecc4)
NSTUB(eventproc_ShutdownPlayAllMenu, 0xffa5ed3c)

NSTUB(eventproc_export_StartFirmInfoMenu, 0xffa654cc)

NSTUB(eventproc_ShowLanguageNameList, 0xffa67e60)
NSTUB(eventproc_SaveLanguageNameList, 0xffa67e9c)
NSTUB(eventproc_RegisterLanguageName, 0xffa67ea0)

NSTUB(eventproc_CreateLanguageMenu, 0xffa68780)
NSTUB(eventproc_DeleteLanguageMenu, 0xffa68944)

NSTUB(eventproc_export_FmtMenu_ExecuteQuickFormat, 0xffa6ac08)

NSTUB(eventproc_export_StartDirectTransferManager, 0xffa75518)

NSTUB(eventproc_export_StoptDtConfirmMenu, 0xffa75c48)

NSTUB(eventproc_export_StoptDtExecuteMenu, 0xffa76530)

NSTUB(eventproc_StartDpConnect, 0xffa7986c)

NSTUB(eventproc_StopDpConnect, 0xffa79ae4)

NSTUB(eventproc_CreateDpConnectController, 0xffa79eb0)
NSTUB(eventproc_DeleteDpConnectController, 0xffa7a120)
NSTUB(eventproc_shutdownDirectPrintUI, 0xffa7a208)

NSTUB(eventproc_StartDpDpofMenu, 0xffa7bc4c)

NSTUB(eventproc_StartDpMainMenu, 0xffa814a8)

NSTUB(eventproc_StartDpPrinting, 0xffa82e94)

NSTUB(eventproc_StartDpsDpofMenu, 0xffa841f8)

NSTUB(eventproc_StartDpsMainMenu, 0xffa8a8cc)

NSTUB(eventproc_StartDpsStop, 0xffa90500)

NSTUB(eventproc_StartDpStopReconfirm, 0xffa9161c)

NSTUB(eventproc_StartDpStyleMenu, 0xffa936c0)

NSTUB(eventproc_StartDpTrimming, 0xffa97210)

NSTUB(eventproc_DBG_changeTraceLevel, 0xffa98dd4)

NSTUB(eventproc_StartDpMovieMenu, 0xffa98fbc)

NSTUB(eventproc_StartClockMode, 0xffa9ccac)

NSTUB(eventproc_EndClockMode, 0xffa9cedc)

NSTUB(eventproc_ControlViewEvent, 0xffaa008c)

NSTUB(eventproc_InstallPrintMenu, 0xffaabee0)

NSTUB(eventproc_DisableNotificationPTP, 0xffab251c)
NSTUB(eventproc_EnableNotificationPTP, 0xffab2530)
NSTUB(eventproc_SetUSBToPTPMode, 0xffab2548)
NSTUB(eventproc_SetUSBToDCPMode, 0xffab255c)
NSTUB(eventproc_RefreshUSBMode, 0xffab2574)
NSTUB(eventproc_NotifyConnectPictBridge, 0xffab25f8)
NSTUB(eventproc_NotifyDisconnectPictBridge, 0xffab2610)

NSTUB(eventproc_PTPRspnd_ShowRemoteStg, 0xffad2124)

NSTUB(eventproc_CreateVcomUart, 0xffae9404)
NSTUB(eventproc_DeleteVcomUart, 0xffae9534)

NSTUB(eventproc_RegComEventProc, 0xffae9f4c)

NSTUB(eventproc_MechaReset, 0xffaea11c)
NSTUB(eventproc_MechaTerminate, 0xffaea154)
NSTUB(eventproc_ShowMechaMacro, 0xffaea1a4)

NSTUB(eventproc_EnableMechaCircuit, 0xffaed410)
NSTUB(eventproc_DisableMechaCircuit, 0xffaed420)
NSTUB(eventproc_EnableFocusPiCircuit, 0xffaed430)
NSTUB(eventproc_DisableFocusPiCircuit, 0xffaed440)
NSTUB(eventproc_GetFocusPiSensorLevel, 0xffaed450)
NSTUB(eventproc_EnableZoomPiCircuit, 0xffaed468)
NSTUB(eventproc_DisableZoomPiCircuit, 0xffaed478)
NSTUB(eventproc_GetZoomPiSensorLevel, 0xffaed488)
NSTUB(eventproc_EnableZoomEncoderCircuit, 0xffaed4a0)
NSTUB(eventproc_DisableZoomEncoderCircuit, 0xffaed4b0)
NSTUB(eventproc_SendMechaCircuitData, 0xffaed4c0)
NSTUB(eventproc_ReceiveMechaCircuitDataAll, 0xffaed4fc)

NSTUB(eventproc_MoveLensToFirstPointEvent, 0xffaf02c0)
NSTUB(eventproc_MoveLensToTerminatePointEvent, 0xffaf0338)
NSTUB(eventproc_PermitLensControllerFocusReset, 0xffaf0388)
NSTUB(eventproc_PermitLensControllerFocusInfinity, 0xffaf0398)
NSTUB(eventproc_IsLensOutside, 0xffaf03a8)
NSTUB(eventproc_GetLensErrorStatus, 0xffaf03b4)

NSTUB(eventproc_ResetZoomLens, 0xffaf1a2c)
NSTUB(eventproc_ResetZoomLensToFirstPoint, 0xffaf1a5c)
NSTUB(eventproc_ResetZoomLensToTermiantePoint, 0xffaf1ad0)
NSTUB(eventproc_MoveZoomLensWithPoint, 0xffaf1b44)
NSTUB(eventproc_MoveZoomLensWithPosition, 0xffaf1bc0)
NSTUB(eventproc_MoveZoomLensToTerminatePosition, 0xffaf1c14)
NSTUB(eventproc_GetZoomLensCurrentPoint, 0xffaf1c64)
NSTUB(eventproc_GetZoomLensCurrentPosition, 0xffaf1c78)
NSTUB(eventproc_GetZoomLensTelePoint, 0xffaf1c8c)

NSTUB(eventproc_SetZoomLensNormalControlGain, 0xffaf3688)

NSTUB(eventproc_SetZoomLensResetControlGain, 0xffaf4fcc)

NSTUB(eventproc_MoveZoomActuator, 0xffaf7a18)
NSTUB(eventproc_SetZoomActuatorSpeedPPS, 0xffaf7a64)
NSTUB(eventproc_GetZoomActuatorSpeedPPS, 0xffaf7a78)
NSTUB(eventproc_SetZoomActuatorSpeedControlGain, 0xffaf7a8c)
NSTUB(eventproc_GetZoomActuatorSpeedControlGain, 0xffaf7aa0)
NSTUB(eventproc_SetZoomActuatorLimitAmpere, 0xffaf7ab4)
NSTUB(eventproc_GetZoomActuatorLimitAmpere, 0xffaf7ac8)
NSTUB(eventproc_SetZoomActuatorPwmDuty, 0xffaf7adc)
NSTUB(eventproc_SetZoomActuatorPwmFixedTime, 0xffaf7af0)
NSTUB(eventproc_GetZoomActuatorCurrentPosition, 0xffaf7b04)
NSTUB(eventproc_IsZoomActuatorResetSensorPlusSide, 0xffaf7b50)
NSTUB(eventproc_SetDCMotorSpeedLevel, 0xffaf7b5c)
NSTUB(eventproc_SetDCMotorChargePump, 0xffaf7b70)
NSTUB(eventproc_SetDCMotorPwmFixedTimeLevel, 0xffaf7b84)
NSTUB(eventproc_SetDCMotorPwmLevel, 0xffaf7b98)
NSTUB(eventproc_SetPM3ByGpio, 0xffaf7bac)
NSTUB(eventproc_ClearPM3ByGpio, 0xffaf7bbc)
NSTUB(eventproc_ClearPM3ByFs, 0xffaf7bcc)
NSTUB(eventproc_MoveDCMotorCW, 0xffaf7bdc)
NSTUB(eventproc_MoveDCMotorCCW, 0xffaf7c38)
NSTUB(eventproc_StopDCMotor, 0xffaf7c94)
NSTUB(eventproc_SetDCMotorWaitTime, 0xffaf7cb4)
NSTUB(eventproc_GetCurrentEncoderPosition, 0xffaf7ccc)

NSTUB(eventproc_ResetIrisEvent, 0xffaf8df4)
NSTUB(eventproc_MoveIrisWithAvEvent, 0xffaf8e24)
NSTUB(eventproc_MoveIrisToTerminatePositionEvent, 0xffaf8e58)
NSTUB(eventproc_GetIrisAvEvent, 0xffaf8e60)
NSTUB(eventproc_MoveIrisWithAvWithoutBacklashEvent, 0xffaf8e74)

NSTUB(eventproc_CloseMechaShutterEvent, 0xffafa118)
NSTUB(eventproc_OpenMechaShutterEvent, 0xffafa148)
NSTUB(eventproc_CloseMechaShutterWithTimingEvent, 0xffafa178)
NSTUB(eventproc_SetMechaShutterDacSettingEvent, 0xffafa1bc)
NSTUB(eventproc_SetMechaShutterOpenDacSettingEvent, 0xffafa1d0)
NSTUB(eventproc_SetMechaShutterFinalDacSettingEvent, 0xffafa1e4)
NSTUB(eventproc_SetMechaShutterOpenFinalDacSettingEvent, 0xffafa1f8)
NSTUB(eventproc_SetMechaShutterWaitTimeSettingEvent, 0xffafa20c)
NSTUB(eventproc_GetMechaShutterStatusEvent, 0xffafa220)
NSTUB(eventproc_SaveMechaShutterCount, 0xffafa22c)
NSTUB(eventproc_GetMechaShutterCount, 0xffafa268)
NSTUB(eventproc_ClearMechaShutterCount, 0xffafa2b8)

NSTUB(eventproc_TurnOnNdFilterEvent, 0xffafadc4)
NSTUB(eventproc_TurnOffNdFilterEvent, 0xffafadf4)
NSTUB(eventproc_SetNdDacSettingEvent, 0xffafae24)

NSTUB(eventproc_MoveFocusLensWithDistance, 0xffb02a2c)
NSTUB(eventproc_ResetFocusLens, 0xffb02af8)
NSTUB(eventproc_MoveFocusLensToTerminate, 0xffb02b58)
NSTUB(eventproc_MoveFocusLensWithPosition, 0xffb02bcc)
NSTUB(eventproc_MoveFocusLensWithPositionWithoutBacklash, 0xffb02c9c)
NSTUB(eventproc_MoveFocusActuator, 0xffb02d6c)
NSTUB(eventproc_GetFocusLensCurrentPosition, 0xffb02e28)
NSTUB(eventproc_GetFocusLensResetPosition, 0xffb02e3c)
NSTUB(eventproc_GetFocusLensResetPositionForInside, 0xffb02e50)
NSTUB(eventproc_GetFocusLensResetPositionForOutside, 0xffb02e64)
NSTUB(eventproc_GetFocusLensResetDefaultPosition, 0xffb02e78)
NSTUB(eventproc_SetFocusLensDefaultCondition, 0xffb02e8c)
NSTUB(eventproc_SetFocusLensCondition, 0xffb02ea4)
NSTUB(eventproc_SetFocusLensSpeedTable, 0xffb02f7c)

NSTUB(eventproc_GetFocusLensMoveCompleteTime, 0xffb03158)
NSTUB(eventproc_GetFocusLensNdCoefficientPulse, 0xffb03164)
NSTUB(eventproc_GetFocusLensSettingMaxSpeed, 0xffb03178)
NSTUB(eventproc_GetFocusLensSettingMaxSpeedByDeltaType, 0xffb0318c)
NSTUB(eventproc_SetFocusLensMaxSpeedLimit, 0xffb031a0)
NSTUB(eventproc_CancelFocusLensMaxSpeedLimit, 0xffb031b8)
NSTUB(eventproc_EscapeFocusLens, 0xffb031cc)
NSTUB(eventproc_GetFocusLensSubjectDistance, 0xffb03260)
NSTUB(eventproc_GetFocusLensSubjectDistanceFromLens, 0xffb03284)
NSTUB(eventproc_EnableFocusLens, 0xffb032a8)
NSTUB(eventproc_SetFocusLensBacklashSpeedToMax, 0xffb0330c)
NSTUB(eventproc_ClearFocusLensBacklashSpeedToMax, 0xffb0331c)
NSTUB(eventproc_CheckFocusLensAfAging, 0xffb033bc)

NSTUB(eventproc_MoveCZToPointEvent, 0xffb05360)
NSTUB(eventproc_MoveCZToWideEvent, 0xffb053b4)
NSTUB(eventproc_MoveCZToTeleEvent, 0xffb053fc)

NSTUB(eventproc_TurnOnAFLampEvent, 0xffb055f4)
NSTUB(eventproc_TurnOffAFLampEvent, 0xffb0560c)

NSTUB(eventproc_FA_Create, 0xffb08b44)
NSTUB(eventproc_FA_Delete, 0xffb08b78)

NSTUB(eventproc_InitializeAdjustmentSystem, 0xffb097c8)
NSTUB(eventproc_TerminateAdjustmentSystem, 0xffb09810)
NSTUB(eventproc_InitializeAdjustmentFunction, 0xffb09858)

NSTUB(eventproc_MakeBootDisk, 0xffb39ba4)
NSTUB(eventproc_MakeScriptDisk, 0xffb39bb8)

NSTUB(eventproc_LoadScript, 0xffb3b600)
NSTUB(eventproc_UnLoadScript, 0xffb3b610)
NSTUB(eventproc_Printf, 0xffb3b624)
NSTUB(eventproc_ScriptDisEnabled, 0xffb3b63c)
NSTUB(eventproc_ScriptEnabled, 0xffb3b650)

NSTUB(eventproc_Script, 0xffb3c2ec)

NSTUB(eventproc_GetLogToFile, 0xffb44520)

NSTUB(eventproc_MemoryChecker, 0xffb45978)
NSTUB(eventproc_VerifyByte, 0xffb45aa8)

