#include "stubs_asm.h"

DEF(physw_status, 0x10C1C)
DEF(physw_run, 0x1CA4)  // 0x1C98 + 0xC

DEF(playrec_mode, 0x5724) // 0x5720+4
DEF(FlashParamsTable,0xFFE9E9DC)
DEF(zoom_busy, 0xA424)  // 0xA410 + 0x14
DEF(focus_busy, 0xA318) // 0xA308 + 0x10
DEF(canon_menu_active,0xBAFC)
DEF(canon_shoot_menu_active,0xB1FD)	// 0xB1FC+1
DEF(recreview_hold, 0xAF6C)			// 0xAEA4+0xC8
DEF(movie_status, 0x5588)  // 0x5550 + 0x38
DEF(zoom_status, 0xDE14)
DEF(some_flag_for_af_scan, 0xDD08)
DEF(some_f_for_dng, 0x8E8C)
DEF(second_ext_for_dng, 0x8EAC)
