#include "stubs_asm.h"

DEF(zoom_status, 0xB9DC) 					// @FFA77D3C
DEF(movie_status, 0x6260)  					// @FF93D360   0x6228 + 0x38
DEF(physw_status, 0x31B78) 					// @FF833374
DEF(physw_run, 0x1c44) 						// @FF8331C8   0x1C38 + 0x0C
DEF(FlashParamsTable, 0xFFB97300) 			// @FFA75A20
DEF(zoom_busy, 0x61CC)  					// @FF93A3A0   0x61B8 + 0x14
DEF(focus_busy, 0x6078) 					// @FF9349B0   0x6070 + 0x08
DEF(canon_menu_active, 0x2D48) 				// @FF8853D4   0x2D44 + 0x04
DEF(canon_shoot_menu_active,0x7751)   		// @FF97B7E0   0x7750 + 0x01
DEF(recreview_hold, 0x74A0) 				// @FF96CB78   0x73D0 + 0xD0
DEF(some_flag_for_af_scan, 0x673C) 			// @FF940D14
DEF(levent_table, 0xFFB41F38)
DEF(playrec_mode, 0x2A7C) 					// @FF877AE4   0x2A78 + 0x04
DEF(enabled_refresh_physical_screen, 0x8C20+0x20)   // SD940 102C routine @ FF9D1EA8 per IXUS200-SD980 @ FF9F8298 RefreshPhysicalScreen

// will need to fix these if we care about dng support
DEF(some_f_for_dng, 0xDEAD) 				// TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD) 			// TODO NOT FOUND!
