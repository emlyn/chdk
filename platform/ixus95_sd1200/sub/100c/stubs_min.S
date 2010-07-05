#include "stubs_asm.h"

DEF(physw_status, 0xC338) // 0xFFC11B90 ShowPhySwStatus
DEF(physw_run, 0x1C28 + 0x0C) // SD1200: 0xFFC119E4 task_PhySw
DEF(FlashParamsTable, 0xFFEB37A8) // SD1200 0xFFDF737C ParameterManager.c__90
DEF(zoom_busy, 0x559C + 0x14) // SD1200 0xFFCF4AB0 ZoomLensController.c 
DEF(focus_busy, 0x54A0 + 0x08) // SD1200 0xFFCEF6B0 FocusLensController.c
DEF(canon_menu_active, 0x2BAC + 0x04) // SD1200 0xFFC5ACDC calls sub from EraseAllMenu.c

DEF(canon_shoot_menu_active, 0x681C + 0x01) // SD1200 0xFFD2A0D0
// Search on "CtrlSav.c:0", there are a bunch of them, the function looks like
// this, on the SD1200 with 0x681C (+1) the value of interest. Note it appears
// above the CtrlSrv.c:0 and below it (next sub).
// And R4 is offset by #4 (twice in the same sub).
// SD990 and SD780 match this too.
/*
sub_FFD2A0CC                            ; CODE XREF: sub_FFD29F3C+10j
                                        ; sub_FFD29F94+4p ...
        STMFD   SP!, {R4,LR}
        LDR     R4, =0x681C
        LDR     R0, [R4,#4]
        CMP     R0, #0
        LDMEQFD SP!, {R4,PC}
        BL      _sub_FFC5C5E0__CtrlSrv.c__0 ; LOCATION: CtrlSrv.c:0
        MOV     R0, #0
        STR     R0, [R4,#4]
        LDMFD   SP!, {R4,PC}
; End of function sub_FFD2A0CC

; =============== S U B R O U T I N E =======================================
sub_FFD2A0F0                            ; CODE XREF: sub_FFD29F50+4p
                                        ; sub_FFD29F64+4p ...
                LDR     R1, =0x681C
*/


    // SD990 suggests this but also says "Doesn't appear to work"
DEF(recreview_hold, 0x6548 + 0xC4) // Above Immediate #0x3007 at beginning of function
    // Search for immediate 0x3007, it's immediate prior to it, at
    // the beginning of a function (not 0x2000)
/* SD1200
sub_FFD1D67C                            ; CODE XREF: sub_FFD1F2D4+1F4p
                                        ; sub_FFD2007C+20Fp
        STMFD   SP!, {R4-R6,LR}
        LDR     R1, =0x6548
        LDR     R12, =0x3007
        LDR     R2, [R1,#0x64]
*/


DEF(movie_status, 0x5648 + 0x3c) // SD1200: 0xFFCF8060, Regex Search for BLNE.*SoundDevice_CODEC.c

DEF(some_flag_for_af_scan, 0x5B4C) // LOCATION SsPrepareSeq.c:4, SD1200: 0xFFC4A5D0 LDR R10, =
DEF(zoom_status, 0x96B4) // below DCB "Backupwrapper", sub is called from ZoomController.c sub
			
DEF(some_f_for_dng, 0xDEAD) // TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD) // TODO NOT FOUND!

DEF(levent_table, 0xFFE8C7C4) // Yossar
//DEF(playrec_mode, 0xDEAD) //0x2A04+4// Searched on "MenuIn" and it's the last jump.  Similar jump if you look for "MenuOut"
DEF(playrec_mode, 0x2924) // 0x0x2920+4  Yossar