#include "stubs_asm.h"

// from kbd_read_keys
// found at ROM:FF8238C8
DEF(physw_status, 0x11ABC)


// from task_physw, exit-condition. R4 = base; R0 = [R4 + offset] => physw_run
// found at ROM:FF8235A4
// ROM:FF8235A4   LDR     R4, =0x1CD0
// ..
// ROM:FF8235C0   LDR     R0, [R4,#8]
// ROM:FF8235C4   CMP     R0, #0
// ROM:FF8235C8   BNE     loc_FF8235AC
// ROM:FF8235CC   LDMFD   SP!, {R4,LR}
// ROM:FF8235D0   B       ExitTask
DEF(physw_run, 0x1CD8)


// found in taskcreate_LEDCon (sub_FF84CCD0)
// ROM:FF84CCD4   LDR     R4, =0x270C     @ Base addr
// ROM:FF84CCD8   LDR     R0, [R4]        @ Load value (dereference)
// ROM:FF84CCDC   CMP     R0, #0          @ If it's not 0, it's already initialized,
// ROM:FF84CCE0   BNE     locret_FF84CDC8 @ so return.
// ROM:FF84CCE4   MOV     R0, #0x3C0      @ Else (if it's 1)
// ROM:FF84CCE8   BL      sub_FF82AC28    @ R0 = malloc(0x3C0); // allocate the LED table
// ..
// ROM:FF84CCFC   STR     R0, [R4,#4]     @ Store the address of the LED table (base+4)
DEF(led_table, 0x2710) // 0x270C + 4


// found at ROM:FFA4503C
DEF(FlashParamsTable,0xFFAEFF98)


// found in sub_FF957174 (called from MoveZoomLensWithPoint (sub_FF957B34))
// ROM:FF957178   LDR     R4, =0xB37C
// ..
// ROM:FF9571BC   LDR     R0, [R4,#0x34]
// ROM:FF9571C0   CMP     R0, #0
// ROM:FF9571C4   MOVNE   R1, #0xE0
// ROM:FF9571C8   ADRNE   R0, aZoomlenscontro @ "ZoomLensController.c"
// ROM:FF9571CC   BLNE    assert
DEF(zoom_busy, 0xB3B0)  //0xB37C + 0x34


// Found in sub_FF950718 (<- sub_FFA0D148 <- sub_FFA0D394 <- sub_FFA0D408
//                                    <- MoveFocusLensToDistance (sub_FFA0D41C))
// ROM:FF95071C   LDR     R4, =0xB274
// ..
// ROM:FF950770   LDR     R0, [R4,#8]
// ROM:FF950774   CMP     R0, #0
// ROM:FF950778   MOVNE   R1, #0x90
// ROM:FF95077C   ADRNE   R0, aFocuslenscontr @ "FocusLensController.c"
// ROM:FF950780   BLNE    assert
DEF(focus_busy, 0xB27C) //0xB274 + 8


// Found in StartRecModeMenu (sub_FF897010)
// ROM:FF897014   LDR     R5, =0x6E38
// ROM:FF897018   LDR     R0, [R5,#4]
// ROM:FF89701C   ADD     R1, R5, #0
// ROM:FF897020   CMP     R0, R1
// ROM:FF897024   LDMNEFD SP!, {R4-R6,PC}
DEF(canon_menu_active,0x6E3C) // 0x63E8 + 4

// Same as previous variable, unusable. Originally found it by peeking through
// memory and it looked suitable at first. This address along with 0xBE64
// (suitable as canon_shoot_menu_active, code agrees) looked suitable but I got
// the basic idea wrong. Listed for completeness.
//DEF(canon_menu_active,0xBEB4)


// Found in sub_FF982310 (deactivates shoot menu?). Ewavr found it but didn't
// clearly specify where, so this is a guess.
// ROM:FF982310   LDR     R1, =0xC05C
// ROM:FF982314   MOV     R0, #0
// ROM:FF982318   STRB    R0, [R1]
// ROM:FF98231C   STRB    R0, [R1,#1]
DEF(canon_shoot_menu_active,0xC05D) // 0xC05C + 1


// Found in sub_FF9754AC. Again, ewavr found this one, he did supply one pointer
// 'search for LDR R12, =0x3007'. I guess this is the right one then :)
// ROM:FF9754AC 000                 STMFD   SP!, {R4,LR}
// ROM:FF9754B0 008                 LDR     R1, =0xBD60
// ROM:FF9754B4 008                 LDR     R12, =0x3007
// ROM:FF9754B8 008                 LDR     R2, [R1,#0xCC]
DEF(recreview_hold, 0xBE2C) // 0xBD60 + 0xCC
DEF (movie_state,0x5868 + 0x38)





