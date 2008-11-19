#include "stubs_asm.h"

DEF(physw_status, 0xF11C) //OK
DEF(physw_run, 0x1BF0) //OK
DEF(FlashParamsTable,0xFFE7D1B4)
DEF(zoom_busy, 0x8050)  //0x803c+14 found at 0xFFD0FCC0 ok
DEF(focus_busy, 0x9D50) //  0x9CB8 OK?
DEF(canon_menu_active,0x8D20)		// 0x8d1c+4 OK
DEF(canon_shoot_menu_active,0x9641)   // 0x9640+1 OK

DEF(recreview_hold, 0x93ec) // found at FFD3837C??

DEF(movie_status, 0x53c8)  // 0x5390 + 0x38 OK
DEF(some_flag_for_af_scan, 0xD688)
DEF(zoom_status, 0xBFBC)   // found at 0xFFE000B8
DEF(led_table, 0x242C)
