#include "stubs_asm.h"

// Documentation stripped, please refer to the S5IS 1.01b stubs_min.S if you
// need it, or wait until someone feels like updating the documentation for this
// particular model.

DEF(physw_status, 0x11ABC)

DEF(physw_run, 0x1CD8)

DEF(led_table, 0x2710) // 0x270C + 4

DEF(FlashParamsTable,0xFFAF0088) 

DEF(zoom_busy, 0xB3B0)  //0xB37C + 0x34

DEF(focus_busy, 0xB27C) //0xB274 + 8

DEF(canon_menu_active,0x6E3C) // 0x63E8 + 4

DEF(canon_shoot_menu_active,0xC05D) // 0xC05C + 1

DEF(recreview_hold, 0xBE2C) // 0xBD60 + 0xCC

DEF(zoom_status, 0x68F8)
DEF(some_f_for_dng, 0x9B94)
DEF(second_ext_for_dng, 0x9BB8)
DEF(movie_status,0x5868 + 0x38)