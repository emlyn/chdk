#include "stubs_asm.h"

DEF(physw_status, 0x13FDC)
DEF(physw_run, 0x1CA4) // 0x1C98+0xC

DEF(FlashParamsTable,0xFFE8E7E4)

DEF(zoom_busy, 0xD5A8) //  0xD594 + 0x14

DEF(focus_busy, 0xD530) 

DEF(canon_menu_active,0xEE9C)  // 0xEE98+4

DEF(canon_shoot_menu_active,0xE6CD) 

DEF(recreview_hold, 0xE480)

DEF(movie_status, 0x5550)    // 0x5518 + 0x38
DEF(some_flag_for_af_scan, 0x11040)
DEF(zoom_status, 0x11174)
DEF(some_f_for_dng, 0xC058)
DEF(second_ext_for_dng, 0xC078)
DEF(levent_table,0xFFE6F8B0)
DEF(playrec_mode,0x56E4) // "MenuIn" 0x56E0+4
