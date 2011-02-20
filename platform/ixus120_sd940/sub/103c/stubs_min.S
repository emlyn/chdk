#include "stubs_asm.h"

DEF(zoom_status, 0xB9DC)                			// SD940 103c  	
DEF(movie_status, 0x6228 + 0x38)        			// SD940 103c routine @ FF93D1A4	
DEF(physw_status, 0x31B78)							// SD940 103c routine @ FF8334B8
DEF(physw_run, 0x1C38 + 0x0C)   					// SD940 103c routine @ FF8331C4 task_PhySw	
DEF(FlashParamsTable, 0xFFB974C8)					// SD940 103c routine @ FFA75BE8 
DEF(zoom_busy, 0x61B8 + 0x14)						//?SD940 103c routine @  FF93A5FC
DEF(focus_busy, 0x6070 + 8)							// SD940 103c routine @ FF934B74 0x6070=FF934B78 0x08=FF934BD4
DEF(canon_menu_active, 0x2D44 + 4 )     			// SD940 103C routine @ FF8857BC
DEF(canon_shoot_menu_active, 0x7750+1)  			// SD940 103C routine @ FF97B90C
DEF(recreview_hold, 0x73D0 + 0xD0)      			// SD940 103c routine @ FF96CD3C	
DEF(some_flag_for_af_scan, 0x673C) 					// SD940 103C @FF940EDC
DEF(levent_table,0xFFB42100) 						// SD940 103c routine @ FF966F20
DEF(playrec_mode, 0x2A78+0x4)						// SD940 103c routine @ FF877E9
DEF(enabled_refresh_physical_screen, 0x8C20+0x20)   // SD940 103C routine @ FF9D2070 per IXUS200-SD980 @ FF9F8298 RefreshPhysicalScreen



