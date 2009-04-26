#include "stubs_asm.h"

DEF(physw_status, 0xFB38)	//found at ROM:FFC11100
DEF(physw_run, 0x1BD8 + 0xC)  //found at  ROM:FFC11064 and ROM:FFC11080
DEF(FlashParamsTable,0xFFEDD7C4)	//found at ROM:FFE14238
DEF(zoom_busy, 0x86B8+0x14)	//found at ROM:FFD121B4 and ROM:FFD1206C
DEF(focus_busy, 0x85B4+0x8)	//found at ROM:FFD0CD90 and ROM:FFD0CDA8
DEF(canon_menu_active, 0x93D0+0x4)	//found at ROM:FFD2CAA0 AND ROM:FFD2C87C , not 100% sure
DEF(canon_shoot_menu_active, 0x9B0C+0x1)	//found at ROM:FFD49AD4 and ROM:FFD498BC
DEF(recreview_hold, 0x9770+0xD0)	//found at ROM:FFD3AE34 and ROM:FFD3AA58
DEF(zoom_status, 0xC79C)	//found at ROM:FFE1575C  
DEF(movie_status, 0x5240+0x38)		//ROM:FFC4C120 and ROM:FFC4C788 (compare ROM:FF8634E8 in SX10!!!!)
DEF(enabled_refresh_physical_screen, 0xAA2C+0x30 )	//found at ROM:FFD8F750 and ROM:FFD8FBAC
DEF(playrec_mode, 0x5408+0x4)	//found at ROM:FFC545B4 and ROM:FFC542A4 (?????)
DEF(some_flag_for_af_scan, 0x8C78 )	//found at ROM:FFD19814
