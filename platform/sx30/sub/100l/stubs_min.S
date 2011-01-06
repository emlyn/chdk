#include "stubs_asm.h"

DEF(physw_status, 0x34594)							// ok (comp 1.00h)
DEF(full_screen_refresh, 0xB198)					// ok (comp 1.00h)
DEF(enabled_refresh_physical_screen, 0x4CF8 + 0x14)	// ok (comp 1.00h)
DEF(physw_run, 0x1C30 + 0xC)						// ok (comp 1.00h)
DEF(canon_menu_active, 0x3A28 + 4)					// ok (comp 1.00h)
DEF(canon_shoot_menu_active, 0x9900 + 1)			// ok (comp 1.00h)
DEF(FlashParamsTable,0xFFC67D00)					// ok (comp 1.00h) [changed in 1.00l]
DEF(levent_table, 0xFFC0EA34)						// ok (comp 1.00h) [changed in 1.00l]
DEF(playrec_mode, 0x3754 + 0x4)						// ok (comp 1.00h)
DEF(focus_len_table, 0xFFFEA5CC)					// ok (comp 1.00h)
DEF(zoom_busy, 0x342c + 0x1c)						// ok (comp 1.00h)
DEF(focus_busy,0x7A6C + 0x8)						// ok (comp 1.00h)
DEF(movie_status, 0x34E0 + 0x44)					// ok (comp 1.00h)
DEF(recreview_hold, 0x933C + 0xF0)					// ok (comp 1.00h)

// TODO - Not Done Yet (SX20 values below)
//DEF(zoom_status, 0xE7C4)							// ??? doesn't appear to work, can't find equivalent code
