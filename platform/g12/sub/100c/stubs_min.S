#include "stubs_asm.h"

DEF(physw_status, 0x34474)							// found in kbd_read_keys (OK)
DEF(full_screen_refresh, 0xA5DC)					// found in FFA53B4C, (comp to sx30)
DEF(enabled_refresh_physical_screen, 0x45C0 + 0x14)	// possible in FF8B4F34
DEF(physw_run, 0x1C30 + 0xC)						// found in FF8345EC, (comp to sx30)
DEF(canon_menu_active, 0x3210 + 4)					// found in FF896370 (comp to sx30)
DEF(canon_shoot_menu_active, 0x8AFC + 1)			// possible in FF9DC4A4 (comp to sx30)
DEF(FlashParamsTable,0xFFC89760)					// found in FFB1ECA4 (comp to sx30)
DEF(levent_table, 0xFFC0BE90)						// Searched for string 00 08 00 00 02 00 00 00 (to match sx30 & s95)
DEF(playrec_mode, 0x2F34 + 0x4)						// FF888084 (comp sx30)
DEF(focus_len_table, 0xFFFE2A80)					// search for 30500 (longest focus length in micrometers) & 6100 (shortest length)
DEF(zoom_busy, 0x71d4 + 0x14)						// found by trial and error in the zoom lens controller code
DEF(focus_busy,0x70B8 + 0x8)						// found by trial and error in the focus controller code
DEF(movie_status, 0x7290 + 0x44)					// in FF9860EC (comp s95)
DEF(recreview_hold, 0x84C0 + 0xE0)					// in FF9C0694 (comp s95)
DEF(some_flag_for_af_scan, 0x76B4)					// @FF98A808 (comp s95)

//DEF(zoom_status, 0xE7C4)							// ??? doesn't appear to work, can't find equivalent code
