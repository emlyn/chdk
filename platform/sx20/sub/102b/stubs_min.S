#include "stubs_asm.h"

DEF(physw_status, 0x32464)				// in FF833128
DEF(physw_run, 0x1C38 + 0xC)				// in FF832B90
DEF(zoom_busy, 0x6EA4 + 0x1C)				// in sub_FF9568C8
DEF(focus_busy, 0x6D48 + 8)				// in sub_FF94FED4 99% SX10 wiki page has a good example
DEF(canon_menu_active, 0x3128 + 4)			// in FF8903B4
DEF(recreview_hold, 0x82E0 + 0xF8)			// in FF9931F4
DEF(enabled_refresh_physical_screen, 0x9D68 + 0x28)	// in FFA0499C
DEF(full_screen_refresh, 0x9CF4)	// found in FFA02598, based on work found in the sd980 port
DEF(movie_status, 0x2BF8 + 0x38)			// in FF878924
DEF(canon_shoot_menu_active, 0x8844 + 1)		// in FF9A9F6C FF890168
DEF(playrec_mode, 0x2E54 + 0x4)				// in FF882228, FF83705C
DEF(FlashParamsTable,0xFFBE87E0)			// look for ParameterManager.c and follow sub_FFAAC774
DEF(zoom_status, 0xC6C0)				// in FFAAEFC8
DEF(levent_table, 0xFFBA31EC) // look for RegisterEventProcedure and follow first sub of function ie 0xFF8943D4
