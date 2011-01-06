#include "stubs_asm.h"

DEF(physw_status, 0x34594)							// found in FF8349F0 [kbd_read_keys] (OK)
DEF(full_screen_refresh, 0xB198)					// found in FFA467FC, (comp to sx20)
DEF(enabled_refresh_physical_screen, 0x4CF8 + 0x14)	// possible in FF8B95E0
DEF(physw_run, 0x1C30 + 0xC)						// found in FF8345E8, (comp to sx20)
DEF(canon_menu_active, 0x3A28 + 4)					// found in FF89A848 (comp to sx20)
DEF(canon_shoot_menu_active, 0x9900 + 1)			// possible in FF9DE724 (comp to sx20)
DEF(FlashParamsTable,0xFFC67B58)					// found in FFB00D28 (comp to sx20)
DEF(levent_table, 0xFFC0E88C)						// Searched for string 00 08 00 00 02 00 00 00 (to match sx20 & s95)
DEF(playrec_mode, 0x3754 + 0x4)						// FF88C69C (comp s95)
DEF(focus_len_table, 0xFFFEA5CC)					// search for 150500 (longest focus length in micrometers) & 4300 (shortest length)
DEF(zoom_busy, 0x342c + 0x1c)						// found by trial and error in the zoom lens controller code
DEF(focus_busy,0x7A6C + 0x8)						// found by trial and error in the focus controller code
DEF(movie_status, 0x34E0 + 0x44)					// in FF8829D4 (comp s95)
DEF(recreview_hold, 0x933C + 0xF0)					// in FF9C4900 (comp s95)

// TODO - Not Done Yet (SX20 values below)
//DEF(zoom_status, 0xE7C4)							// ??? doesn't appear to work, can't find equivalent code
