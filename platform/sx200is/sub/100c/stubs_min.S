#include "stubs_asm.h"

DEF(physw_status, 0xF058)                 // found at FF821B30
DEF(physw_run, 0x1C28 + 0x0C)             // found at FF821A94 and FF821AB0
DEF(FlashParamsTable,0xFFB6D284)          // found at FFA751F4
DEF(zoom_busy, 0x64DC + 0x14)             // found at FF9342B4
DEF(focus_busy, 0x63F0 + 8)               // found at FF92E980
//DEF(canon_menu_active, 0x2FC0 + 4)        // found at FF874CF8, doesn't behave like other cams
DEF(canon_menu_active, 0x2F0C + 4)        // StarRecModeMenu @FF874E38

//DEF(canon_shoot_menu_active, 0x7878 + 1)  // found at FF9657F8, doesn't behave like other cams
DEF(canon_shoot_menu_active, 0x786C + 1)  // sub_FF9773AC
DEF(recreview_hold, 0x7434 + 0xD4)        // found at FF964C10 was + 0xDC
DEF(zoom_status, 0xb850)                  // found at FFA77128
DEF(movie_status, 0x6588 + 0x38)          // found at FFC4C12
DEF(enabled_refresh_physical_screen, 0x8e04+0x30) //found at FF9D4918 and FF9D4F38
DEF(playrec_mode, 0x2C6C+0x4)              // found at FF86833C
DEF(some_flag_for_af_scan, 0x6AF8)	       //found at FF93BCF0   ??????



DEF(led_table, 0x24AC + 0x04)              // found at FF847374


DEF(levent_table,0xFFB399F0)
