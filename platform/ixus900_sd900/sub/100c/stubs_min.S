#include "stubs_asm.h"

// This stuff is mostly memory (RAM) related
// some things are based on quietschi's port to SD1000

/******************* physw_status & physw_run
ROM:FF827EFC sub_FF827EFC                            ; CODE XREF: ROM:FF827EF4
ROM:FF827EFC                 LDR     R3, =0xFBA0     ; <--- ### physw_status ###
ROM:FF827F00                 LDR     R0, [R3,R4,LSL#2]
ROM:FF827F04                 LDMFD   SP!, {R4,PC}
ROM:FF827F04 ; End of function sub_FF827EFC
ROM:FF827F08 off_FF827F08    DCD aPhysw_c            ; DATA XREF: ROM:FF827EF0 "PhySw.c"
ROM:FF827F0C dword_FF827F0C  DCD 0xFBA0              ; DATA XREF: sub_FF827EFC
ROM:FF827F10 PhySw_task                              ; DATA XREF: ROM:off_FF827ED4
ROM:FF827F10                 STMFD   SP!, {R4,LR}
ROM:FF827F14                 LDR     R2, =0x1FDC     ; <--- ### physw_run ###
ROM:FF827F18                 LDR     R3, [R2]
ROM:FF827F1C                 CMP     R3, #0
ROM:FF827F20                 BEQ     loc_FF827F4C
ROM:FF827F24                 MOV     R4, R2
*******************/
DEF(physw_status, 0xFBA0)   // ROM:FF827F0C search function "PhySw_task" #
DEF(physw_run, 0x1FDC)   // ROM:FF827F54 look one function above function "PhySw_task" #


/******************* zoom_busy
ROM:FFAF04C4 dword_FFAF04C4  DCD 0xAB18              ; DATA XREF: sub_FFAF04B4
ROM:FFAF04C8 aZoomlens       DCB "ZoomLens",0        ; DATA XREF: ROM:off_FFAF0578
ROM:FFAF04D4 sub_FFAF04D4                            ; CODE XREF: sub_FFAE9F90+18
ROM:FFAF04D4                 STMFD   SP!, {R4-R7,LR}
ROM:FFAF04D8                 LDR     R7, =0xAB1C
ROM:FFAF04DC                 LDR     R5, [R7]
ROM:FFAF04E0                 CMP     R5, #0
ROM:FFAF04E4                 LDR     R6, =0x823E8
ROM:FFAF04E8                 LDMNEFD SP!, {R4-R7,PC}
ROM:FFAF04EC                 BL      RegisterEventProcedureForLcdDrv
ROM:FFAF04F0                 MOV     R1, #1
ROM:FFAF04F4                 MOV     R0, R5
ROM:FFAF04F8                 BL      CreateBinarySemaphoreStrictly ; LOCATION: StrictWrapper.c:61
ROM:FFAF04FC                 LDR     R3, =0x823E4
ROM:FFAF0500                 LDR     R12, =0x823C0   ; <--- ### zoom_busy_0 ###
ROM:FFAF0504                 LDR     R4, =0x823BC
ROM:FFAF0508                 STR     R0, [R3]
ROM:FFAF050C                 MOV     R2, #0x10
ROM:FFAF0510                 STR     R5, [R12]
ROM:FFAF0514                 MOV     R1, #0xA
ROM:FFAF0518                 LDR     R0, =aZoomlens
ROM:FFAF051C                 STR     R5, [R4]
ROM:FFAF0520                 BL      sub_FFAEA214
ROM:FFAF0524                 STR     R0, [R6]
ROM:FFAF0528                 BL      taskcreate_ZoomEvent
*******************/
DEF(zoom_busy, 0x823C0)   // ROM:FFAF0500 search above string "ZoomLens" #


DEF(focus_busy, 0x82E18)   // ROM:FFB00A90 search below string "FocusLensController" #


/******************* playrec_mode
ROM:FF991D80 ; LOCATION: StartupTask.c:360
ROM:FF991D80 task_SsStartupTask                      ; DATA XREF: ROM:off_FF991C44
ROM:FF991D80                 STMFD   SP!, {R4-R6,LR}
ROM:FF991D84                 BL      unknown_libname_449 ; "Canon A-Series Firmware"  ; <--- ### follow this call, look at ROM:FF99CD0C ###
ROM:FF991D88                 CMP     R0, #1
ROM:FF991D8C                 BEQ     loc_FF991DA0
ROM:FF991D90                 MOV     R1, #0x168
ROM:FF991D94                 LDR     R0, =aStartuptask_c
ROM:FF991D98                 ADD     R1, R1, #1
ROM:FF991D9C                 BL      DebugAssert
ROM:FF991DA0 loc_FF991DA0                            ; CODE XREF: task_SsStartupTask+C
ROM:FF991DA0                 LDR     R6, =0x76B14
ROM:FF991DA4                 MOV     R1, #0x10
ROM:FF991DA8                 LDR     R0, [R6]
ROM:FF991DAC                 MOV     R2, #0
ROM:FF991DB0                 BL      unknown_libname_22 ; "Canon A-Series Firmware"
ROM:FF991DB4                 ANDS    R4, R0, #1
ROM:FF991DB8                 BEQ     loc_FF991DD0
ROM:FF991DBC                 MOV     R1, #0x17C
ROM:FF991DC0                 LDR     R0, =aStartuptask_c
ROM:FF991DC4                 ADD     R1, R1, #2
ROM:FF991DC8                 BL      DebugAssert
ROM:FF991DCC                 B       loc_FF991EB0
ROM:FF99CD0C unknown_libname_449                     ; CODE XREF: ROM:FF98ED98
ROM:FF99CD0C                 LDR     R3, =0x6F6C     ; <--- ### playrec_mode ##
ROM:FF99CD10                 LDR     R0, [R3]
ROM:FF99CD14                 RET
*******************/
DEF(playrec_mode, 0x6F6C)   // ROM:FF99CD0C look at function unknown_libname_449 #


/******************* FlashParamsTable
ROM:FF9AE938 _sub_FF9AE938__ParameterManager.c__148  ; CODE XREF: GetParameterData+A4
ROM:FF9AE938                 MOV     R0, R0,LSL#16
ROM:FF9AE93C                 MOV     R3, R3,LSL#16
ROM:FF9AE940                 MOV     R0, R0,LSR#16
ROM:FF9AE944                 STMFD   SP!, {R4-R8,LR}
ROM:FF9AE948                 MOV     R7, R2
ROM:FF9AE94C                 MOV     R8, R1
ROM:FF9AE950                 MOV     R4, R3,ASR#16
ROM:FF9AE954                 BL      _sub_FF9AB204__PropertyTable.c__4928 ; follow call for FlashParamsTable
ROM:FF9AE958                 MOV     R5, R0
ROM:FF9AE95C                 LDRH    R3, [R5,#4]
ROM:FF9AE960                 BIC     R3, R3, #3
ROM:FF9AE964                 MOV     R3, R3,LSL#16
ROM:FF9AE968                 LDR     R2, =0x7BAB8
ROM:FF9AE96C                 MOV     R3, R3,LSR#16
ROM:FF9AE970                 ADD     R3, R3, R2
ROM:FF9AE974                 CMP     R7, #0
ROM:FF9AE978                 LDR     R0, =aParametermanager_c
ROM:FF9AE97C                 MOV     R1, #0x94
ROM:FF9AE980                 ADD     R6, R3, #5
ROM:FF9AE984                 BNE     loc_FF9AE98C
ROM:FF9AE988                 BL      DebugAssert
ROM:FF9B0A18 _sub_FF9B0A18__PropertyTable.c__4928    ; CODE XREF: sub_FF9B3FB8+18
ROM:FF9B0A18                 STMFD   SP!, {R4,LR}
ROM:FF9B0A1C                 MOV     R4, R0
ROM:FF9B0A20                 MOV     R1, #0x1340
ROM:FF9B0A24                 CMP     R4, #0x6D
ROM:FF9B0A28                 ADD     R1, R1, #0x1E
ROM:FF9B0A2C                 LDR     R0, =aPropertytable_c
ROM:FF9B0A30                 BLS     loc_FF9B0A38
ROM:FF9B0A34                 BL      DebugAssert
ROM:FF9B0A38 loc_FF9B0A38                            ; CODE XREF: _sub_FF9B0A18__PropertyTable.c__4928+18
ROM:FF9B0A38                 LDR     R3, =off_FF9B0860 ; FlashParamsTable
ROM:FF9B0A3C                 LDR     R0, [R3,R4,LSL#2]
ROM:FF9B0A40                 LDMFD   SP!, {R4,PC}
ROM:FF9B0A40 ; End of function _sub_FF9B0A18__PropertyTable.c__4928
*******************/
DEF(FlashParamsTable, 0xFF9AB04C)   // ROM:FF9AB224 #


/******************* canon_menu_active
ROM:FFA536DC eventproc_StartRecModeMenu              ; CODE XREF: sub_FF9DAA88+28
ROM:FFA536DC                 STMFD   SP!, {R4-R7,LR}
ROM:FFA536E0                 LDR     R5, =0x9278     ; <--- ### canon_menu_active ###
ROM:FFA536E4                 LDR     R2, =0x9274     ; <--- canon_menu_active2
ROM:FFA536E8                 LDR     R3, [R5]
ROM:FFA536EC                 CMP     R3, R2
ROM:FFA536F0                 MOV     R7, #0x840
ROM:FFA536F4                 LDMNEFD SP!, {R4-R7,PC}
ROM:FFA536F8                 BL      sub_FFA535A4
ROM:FFA536FC                 MOVL    R0, 0xFFFFFFFF
ROM:FFA53700                 BL      sub_FF9A5798
ROM:FFA53704                 BL      eventproc_export_LockPhysicalScreen
ROM:FFA53708                 BL      sub_FF9F3E34
ROM:FFA5370C                 BL      eventproc_export_IsEnableRefreshPhysicalScreen
ROM:FFA53710                 MOV     R6, R0
ROM:FFA53714                 CMP     R6, #1
ROM:FFA53718                 BNE     loc_FFA53720
ROM:FFA5371C                 BL      eventproc_export_DisableRefreshPhysicalScreen
ROM:FFA53720 loc_FFA53720                            ; CODE XREF: eventproc_StartRecModeMenu+3C
*******************/
DEF(canon_menu_active,0x9278)   // ROM:FFA536E0 look for function "eventproc_StartRecModeMenu" #


/******************* canon_shoot_menu_active
ROM:FF9EF87C taskcreate_DSITask                      ; CODE XREF: sub_FF9DA020+3C
ROM:FF9EF87C var_10          = -0x10
ROM:FF9EF87C                 STMFD   SP!, {R4,R5,LR}
ROM:FF9EF880                 LDR     R5, =0x809C     ; <--- ### canon_shoot_menu_active ###
ROM:FF9EF884                 LDR     R4, [R5]
ROM:FF9EF888                 SUB     SP, SP, #4
ROM:FF9EF88C                 CMP     R4, #0
ROM:FF9EF890                 MOV     R1, #0xA
ROM:FF9EF894                 MOV     R0, R4
ROM:FF9EF898                 BNE     loc_FF9EF8E0
ROM:FF9EF89C                 BL      CreateMessageQueueStrictly ; LOCATION: StrictWrapper.c:37
ROM:FF9EF8A0                 MOV     R1, #0x19
ROM:FF9EF8A4                 STR     R0, [R5,#8]
ROM:FF9EF8A8                 LDR     R3, =task_DSITask
ROM:FF9EF8AC                 LDR     R0, =aDsitask
ROM:FF9EF8B0                 MOV     R2, #0x1000
ROM:FF9EF8B4                 STR     R4, [SP]
ROM:FF9EF8B8                 BL      CreateTaskStrictly ; LOCATION: StrictWrapper.c:25
ROM:FF9EF8BC                 MOV     R3, R0
ROM:FF9EF8C0                 TST     R3, #1
ROM:FF9EF8C4                 MOV     R1, #0xF9
ROM:FF9EF8C8                 LDR     R0, =aDsitask_c
ROM:FF9EF8CC                 STR     R3, [R5,#4]
ROM:FF9EF8D0                 BEQ     loc_FF9EF8D8
ROM:FF9EF8D4                 BL      DebugAssert
*******************/
DEF(canon_shoot_menu_active,0x8099)   // ROM:FF9EF880 in taskcreate_DSITask() , LDR R5, =0x809C; then 0x809C - 0x4 + 0x1 = 0x8099 (quietschi's prescription, SD1000) #


/******************* recreview_hold
ROM:FF9E1F14 sub_FF9E1F14                            ; CODE XREF: sub_FF9E20C0-11C
ROM:FF9E1F14 var_D           = -0xD
ROM:FF9E1F14                 STMFD   SP!, {R4,R5,LR}
ROM:FF9E1F18                 LDR     R3, =0x7EB4     ; <--- ### recreview_hold ###
ROM:FF9E1F1C                 SUB     SP, SP, #4
ROM:FF9E1F20                 LDRH    R12, [R3]
ROM:FF9E1F24                 MOV     R5, #0
ROM:FF9E1F28                 MOV     R3, R0,LSL#16
ROM:FF9E1F2C                 CMP     R12, #0
ROM:FF9E1F30                 MOV     R0, #0x4000
ROM:FF9E1F34                 ADD     R1, SP, #0x10+var_D
ROM:FF9E1F38                 MOV     R2, #1
ROM:FF9E1F3C                 ADD     R0, R0, #0xE
ROM:FF9E1F40                 MOV     R4, R3,ASR#16
ROM:FF9E1F44                 STRB    R5, [SP,#0x10+var_D]
ROM:FF9E1F48                 BEQ     loc_FF9E1F80
ROM:FF9E1F4C                 BL      eventproc_export_PTM_RestoreUIProperty ; LOCATION: BootParam.c:316
*******************/
DEF(recreview_hold, 0x7EB0)   // ROM:FF9E1F18 after function string "AR:Snd:0x%04x", LDR R3, =0x7EB4; then 0x7EB4 - 0x4 = 0x7EB0 (quietschi's prescription, SD1000)


//DEF(zoom_status, 0x7DB0)   // from SD800 ROM:FF9EAADC ?
DEF(zoom_status, 0x7F70)


//DEF(movie_status, 0x8BC00)   // from SD800 ROM:FF98BE98 ?
DEF(movie_status, 0x76410)


//DEF(some_flag_for_af_scan, 0x6AE0)   // from SD800 ROM:FF99923C or ROM:FF99B358 ?
DEF(some_flag_for_af_scan, 0x6B8C)   // ??? ROM:FF992F68 or ROM:FF99524C


// DEF(some_f_for_dng, 0x9A68)   // ??? from SD800 ROM:FFAB182C ?
//DEF(some_f_for_dng, 0x9CD4)   // ??? ROM:FFAB1180
DEF(some_f_for_dng, 0x9C84)   // ??? ROM:FFAB1184

//DEF(second_ext_for_dng, 0x9A8C)   // from SD800 (0x9A8C does not exist in SD800 -> wrong?)
//DEF(second_ext_for_dng, 0x9CD4)   // ??? ROM:FFAB1180
DEF(second_ext_for_dng, 0x9CA8)   // ??? some_f_for_dng + 0x24

// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
DEF(touch_keys_angle, 0x429F4)

// Semaphore address to disable Feather processing
DEF(touch_keys_sema, 0x9C2C)  // 0x9C10 + 0x1C

// ROM:FF8286DC eventproc_ShowPhySwStatus()
DEF(NotifyMask, 0x0000FB70)
DEF(SwitchMask, 0x0000FB80)
DEF(InvertData, 0x0000FB90)
// This is the real name for 'physw_status'
DEF(GpioStatus, 0x0000FBA0)
DEF(SwitchStatus, 0x0000FBB0)

// Logical Event Table
DEF(levent_table,0xFF9A1124)   // search for "DCD aPressrightbutton" and look above
