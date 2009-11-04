#include "stubs_asm.h"

/*******************
ROM:FF828060 loc_FF828060                            ; CODE XREF: sub_FF828044+14j
ROM:FF828060                 LDR     R3, =physw_status <------ 0x0000FB60
ROM:FF828064                 LDR     R0, [R3,R4,LSL#2]
ROM:FF828068                 LDMFD   SP!, {R4,PC}
ROM:FF828068 ; End of function sub_FF828044
ROM:FF828068
ROM:FF828068 ; ---------------------------------------------------------------------------
ROM:FF82806C off_FF82806C    DCD aPhysw_c            ; DATA XREF: sub_FF828044+10r
ROM:FF82806C                                         ; "PhySw.c"
ROM:FF828070 off_FF828070    DCD physw_status        ; DATA XREF: sub_FF828044:loc_FF828060r
ROM:FF828074
ROM:FF828074 ; =============== S U B R O U T I N E =======================================
ROM:FF828074
ROM:FF828074 ; Attributes: noreturn
ROM:FF828074
ROM:FF828074 PhySw_task                              ; DATA XREF: ROM:off_FF828038o
ROM:FF828074                 STMFD   SP!, {R4,LR}
ROM:FF828078                 LDR     R2, =physw_run <------ 0x00001FDC
ROM:FF82807C                 LDR     R3, [R2]
ROM:FF828080                 CMP     R3, #0
ROM:FF828084                 BEQ     loc_FF8280B0
ROM:FF828088                 MOV     R4, R2

ROM:FF8280B4 ; ---------------------------------------------------------------------------
ROM:FF8280B8 off_FF8280B8    DCD physw_run           ; DATA XREF: PhySw_task+4r
ROM:FF8280BC
ROM:FF8280BC ; =============== S U B R O U T I N E =======================================
ROM:FF8280BC
ROM:FF8280BC
ROM:FF8280BC kbd_p1_f                                ; CODE XREF: PhySw_task+20p
ROM:FF8280BC                 STMFD   SP!, {R4-R7,LR}
ROM:FF8280C0                 SUB     SP, SP, #0xC
ROM:FF8280C4                 BL      kbd_read_keys
ROM:FF8280C8                 LDR     R7, =physw_status ; kbd_p1_f_cont
ROM:FF8280CC                 MOV     R6, SP
ROM:FF8280D0                 LDR     R5, =unk_FB40
ROM:FF8280D4                 LDR     R4, =unk_FB50
ROM:FF8280D8                 MOV     R12, #2
ROM:FF8280DC                 MOV     LR, R6

*******************/

DEF(physw_status, 0xFB60)	// see PhySw task at FF828074, dword above PhySw_task, 
DEF(physw_run, 0x1FDC)		// dword above kbd_p1_f, used by PhySw_task

/************
ROM:FFAF175C                 LDR     R3, =unk_97B50
ROM:FFAF1760                 LDR     R12, =zoom_busy_0 <--- 0x00097B2C
ROM:FFAF1764                 LDR     R4, =unk_97B28
ROM:FFAF1768                 STR     R0, [R3]
ROM:FFAF176C                 MOV     R2, #0x10
ROM:FFAF1770                 STR     R5, [R12]
ROM:FFAF1774                 MOV     R1, #0xA
ROM:FFAF1778                 LDR     R0, =aZoomlens
ROM:FFAF177C                 STR     R5, [R4]
ROM:FFAF1780                 BL      sub_FFAEA8A4
ROM:FFAF1784                 STR     R0, [R6]
ROM:FFAF1788                 BL      taskcreate_ZoomEvent
*************/

DEF(zoom_busy, 0x97B2C)		// "ZoomLens"

/**************
ROM:FFB016EC aFocuslens      DCB "FocusLens",0       ; DATA XREF: ROM:off_FFB017CCo
ROM:FFB016F6                 DCB    0
ROM:FFB016F7                 DCB    0
ROM:FFB016F8
ROM:FFB016F8 ; =============== S U B R O U T I N E =======================================
ROM:FFB016F8
ROM:FFB016F8
ROM:FFB016F8 sub_FFB016F8                            ; CODE XREF: taskcreate_ISCPUInitTask+14p
ROM:FFB016F8                 STMFD   SP!, {R4-R6,LR}
ROM:FFB016FC                 LDR     R6, =dword_A9B0
ROM:FFB01700                 LDR     R4, [R6]
ROM:FFB01704                 CMP     R4, #0
ROM:FFB01708                 LDR     R0, =unk_97E70
ROM:FFB0170C                 LDR     R5, =unk_97E6C
ROM:FFB01710                 LDMNEFD SP!, {R4-R6,PC}
ROM:FFB01714                 BL      sub_FFAFC2AC
ROM:FFB01718                 BL      sub_FFB03240
ROM:FFB0171C                 MOV     R1, #1
ROM:FFB01720                 MOV     R0, R4
ROM:FFB01724                 BL      CreateBinarySemaphoreStrictly
ROM:FFB01728                 LDR     R3, =unk_97E64
ROM:FFB0172C                 MOV     R1, #1
ROM:FFB01730                 STR     R0, [R3]
ROM:FFB01734                 MOV     R0, R4
ROM:FFB01738                 BL      CreateBinarySemaphoreStrictly
ROM:FFB0173C                 LDR     R3, =unk_97E68
ROM:FFB01740                 LDR     R2, =unk_97E24
ROM:FFB01744                 STR     R0, [R3]
ROM:FFB01748                 LDR     R12, =unk_97E28
ROM:FFB0174C                 LDR     R3, =focus_busy_0 <--------- 0x00097E20
ROM:FFB01750                 MOV     R0, R4
ROM:FFB01754                 STR     R4, [R3]

**************/

DEF(focus_busy, 0x97E20)	// "FocusLens"

DEF(playrec_mode, 0x6DF4)	// in the first called f-n in task_SsStartupTask

/*************
sub_FF9B4150                            ; CODE XREF: sub_FF9B2E94+A4p
ROM:FF9B4150                 MOV     R0, R0,LSL#16
ROM:FF9B4154                 MOV     R3, R3,LSL#16
ROM:FF9B4158                 MOV     R0, R0,LSR#16
ROM:FF9B415C                 STMFD   SP!, {R4-R8,LR}
ROM:FF9B4160                 MOV     R7, R2
ROM:FF9B4164                 MOV     R8, R1
ROM:FF9B4168                 MOV     R4, R3,ASR#16
ROM:FF9B416C                 BL      sub_FF9B0A18 <-----------
ROM:FF9B4170                 MOV     R5, R0
ROM:FF9B4174                 LDRH    R3, [R5,#4]
ROM:FF9B4178                 BIC     R3, R3, #3
ROM:FF9B417C                 MOV     R3, R3,LSL#16
ROM:FF9B4180                 LDR     R2, =unk_911E0
ROM:FF9B4184                 MOV     R3, R3,LSR#16
ROM:FF9B4188                 ADD     R3, R3, R2
ROM:FF9B418C                 CMP     R7, #0
ROM:FF9B4190                 LDR     R0, =aParameterManager_c
ROM:FF9B4194                 MOV     R1, #0x94 ; 'ö'
ROM:FF9B4198                 ADD     R6, R3, #5
ROM:FF9B419C                 BNE     loc_FF9B41A4
ROM:FF9B41A0                 BL      DebugAssert
ROM:FF9B41A4
ROM:FF9B41A4 loc_FF9B41A4                            ; CODE XREF: sub_FF9B4150+4Cj
ROM:FF9B41A4                 MOV     R3, R4,LSL#16
ROM:FF9B41A8                 LDRH    R2, [R5,#6]
ROM:FF9B41AC                 MOV     R4, R3,LSR#16
ROM:FF9B41B0                 CMP     R4, R2
ROM:FF9B41B4                 LDR     R0, =aParameterManager_c
ROM:FF9B41B8                 MOV     R1, #0x95 ; 'ò'
ROM:FF9B41BC                 BLS     loc_FF9B41C4
ROM:FF9B41C0                 BL      DebugAssert
ROM:FF9B41C4
ROM:FF9B41C4 loc_FF9B41C4                            ; CODE XREF: sub_FF9B4150+6Cj
ROM:FF9B41C4                 MOV     R0, R8
ROM:FF9B41C8                 MOV     R1, R6
ROM:FF9B41CC                 MOV     R2, R4
ROM:FF9B41D0                 LDRH    R3, [R5,#8]
ROM:FF9B41D4                 BL      sub_FF9B4454
ROM:FF9B41D8                 MOV     R0, R7
ROM:FF9B41DC                 MOV     R2, R4
ROM:FF9B41E0                 MOV     R1, R6
ROM:FF9B41E4                 LDMFD   SP!, {R4-R8,LR}
ROM:FF9B41E8                 B       memcpy
ROM:FF9B41E8 ; End of function sub_FF9B4150
ROM:FF9B41E8
ROM:FF9B41E8 ; -------------------------------------------------------



ROM:FF9B0A18 sub_FF9B0A18                            ; CODE XREF: sub_FF9B3FB8+18p
ROM:FF9B0A18                                         ; sub_FF9B4084+24p ...
ROM:FF9B0A18                 STMFD   SP!, {R4,LR}
ROM:FF9B0A1C                 MOV     R4, R0
ROM:FF9B0A20                 MOV     R1, #0x1340
ROM:FF9B0A24                 CMP     R4, #0x6D ; 'm'
ROM:FF9B0A28                 ADD     R1, R1, #0x1E
ROM:FF9B0A2C                 LDR     R0, =aPropertytable_c
ROM:FF9B0A30                 BLS     loc_FF9B0A38
ROM:FF9B0A34                 BL      DebugAssert
ROM:FF9B0A38
ROM:FF9B0A38 loc_FF9B0A38                            ; CODE XREF: sub_FF9B0A18+18j
ROM:FF9B0A38                 LDR     R3, =FlashParamsTable <-- 0xFF9B0860
ROM:FF9B0A3C                 LDR     R0, [R3,R4,LSL#2]
ROM:FF9B0A40                 LDMFD   SP!, {R4,PC}

*************/
DEF(FlashParamsTable, 0xFF9B0860)


/**********

ROM:FFA53D10 StartRecModeMenu                        ; CODE XREF: sub_FF9DE684+28p
ROM:FFA53D10                                         ; sub_FF9E6904+3B8p
ROM:FFA53D10                                         ; DATA XREF: ...
ROM:FFA53D10                 STMFD   SP!, {R4-R7,LR}
ROM:FFA53D14                 LDR     R5, =canon_menu_active <-----0x00009054
ROM:FFA53D18                 LDR     R2, =canon_menu_active2
ROM:FFA53D1C                 LDR     R3, [R5]

**********/

DEF(canon_menu_active,0x9054)		// after "StartRecModeMenu", LDR R4, =0x9054

/************
ROM:FF9F3298 taskcreate_DSITask                      ; CODE XREF: sub_FF9DDDA0+40p
ROM:FF9F3298
ROM:FF9F3298 var_10          = -0x10
ROM:FF9F3298
ROM:FF9F3298                 STMFD   SP!, {R4,R5,LR}
ROM:FF9F329C                 LDR     R5, =dword_7EDC

************/

DEF(canon_shoot_menu_active,0x7ED9) // (0x7EDC - 0x4 + 0x1) found in "taskcreate_DSITask"

/************
ROM:FF9E59C8 aArSnd0x04x     DCB "AR:Snd:0x%04x",0   ; DATA XREF: ROM:off_FF9E5A54o
ROM:FF9E59D6                 DCB    0
ROM:FF9E59D7                 DCB    0
ROM:FF9E59D8
ROM:FF9E59D8 ; =============== S U B R O U T I N E =======================================
ROM:FF9E59D8
ROM:FF9E59D8
ROM:FF9E59D8 sub_FF9E59D8                            ; CODE XREF: sub_FF9E5B84-11Cj
ROM:FF9E59D8                                         ; sub_FF9E5A6C+10j ...
ROM:FF9E59D8
ROM:FF9E59D8 var_D           = -0xD
ROM:FF9E59D8
ROM:FF9E59D8                 STMFD   SP!, {R4,R5,LR}
ROM:FF9E59DC                 LDR     R3, =dword_7CF4
ROM:FF9E59E0                 SUB     SP, SP, #4

************/


DEF(recreview_hold, 0x7CF0) // (0x7CF4 - 0x4) found in "AR:Snd:0x%04x", LDR R3, =0x7CF4;
DEF(zoom_status, 0x7DB0)
DEF(movie_status, 0x8BC00)
DEF(some_flag_for_af_scan, 0x6AE0)
DEF(some_f_for_dng, 0x9A68)
DEF(second_ext_for_dng, 0x9A8C)
DEF(levent_table,0xFF9A6CEC)
