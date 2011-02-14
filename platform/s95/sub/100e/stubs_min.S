#include "stubs_asm.h"

DEF(zoom_busy, 0x7070+0x14)					// @FF9809C8
DEF(focus_busy, 0x6f28 + 8)					// @FF97BEC8
DEF(zoom_status, 0x835C) 					// @FF9C21F0
DEF(canon_menu_active, 0x324c + 4)			// @FF896FC0
DEF(movie_status, 0x7128 + 0x44)			// @FF985B9C
DEF(enabled_refresh_physical_screen, 0xA0D4) // @FFA47600
DEF(playrec_mode, 0x2f74+0x4)				// @FF889094
DEF(FlashParamsTable,0xFFC72314)			// @FFB0F19C
DEF(physw_status, 0x34CB4)                 	// @FF8340C8
DEF(physw_run, 0x1C30 + 0x0C)            	// @FF8340A4
DEF(led_table, 0x25d4 + 0x04)				// @FF864814
DEF(some_flag_for_af_scan, 0x7534)			// @FF9894B4
DEF(canon_shoot_menu_active, 0x8758 + 1)	// @FF9D7B70
DEF(levent_table,0xFFBF5C5C)				// @FF9B8348

// none of these work
//DEF(recreview_hold, 0x81f8+0xE8)			// @FF9BDC78
DEF(recreview_hold, 0x81f8+0x94)			// @FF9C115C
//DEF(recreview_hold, 0x81f8+0xA0)			// @FF9C115C
