#include "stubs_asm.h"

DEF(physw_status, 0x34474)							// found in kbd_read_keys (comp 1.00c)
DEF(full_screen_refresh, 0xA5DC)					// found in FFA53B58, (comp 1.00c)
DEF(enabled_refresh_physical_screen, 0x45C0 + 0x14)	// possible in FF8B4F34 (comp 1.00c)
DEF(physw_run, 0x1C30 + 0xC)						// found in FF8345EC, (comp 1.00c)
DEF(canon_menu_active, 0x3210 + 4)					// found in FF896370 (comp 1.00c)
DEF(canon_shoot_menu_active, 0x8AFC + 1)			// possible in FF9DC4B0 (comp 1.00c)
DEF(FlashParamsTable,0xFFC89910)					// found in FFB1EE54 (comp 1.00c)
DEF(levent_table, 0xFFC0C040)						// Searched for string 00 08 00 00 02 00 00 00 (comp 1.00c)
DEF(playrec_mode, 0x2F34 + 0x4)						// FF888084 (comp 1.00c)
DEF(focus_len_table, 0xFFFE2A80)					// search for 30500 (longest focus length in micrometers) & 6100 (shortest length)
DEF(zoom_busy, 0x71d4 + 0x14)						// (comp 1.00c)
DEF(focus_busy,0x70B8 + 0x8)						// (comp 1.00c)
DEF(movie_status, 0x7290 + 0x44)					// in FF9860E4 (comp 1.00c)
DEF(recreview_hold, 0x84C0 + 0xE0)					// in FF9C06A0 (comp 1.00c)
DEF(some_flag_for_af_scan, 0x76B4)					// @FF98A814 (comp 1.00c)

//DEF(zoom_status, 0xE7C4)							// ??? doesn't appear to work, can't find equivalent code
