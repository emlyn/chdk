#include "stubs_asm.h"

DEF(physw_status, 0xCEF8)
DEF(physw_run, 0x1BE0 + 0x0C)
DEF(FlashParamsTable,0xFFE72138) 
DEF(zoom_busy, 0x5684 + 0x14)
DEF(focus_busy, 0x5598 + 8)
DEF(canon_menu_active, 0x29FC + 4)
DEF(canon_shoot_menu_active, 0xFFC00414) //0x6860 + 1)  it works, but in AFL mode OSD disappers
DEF(recreview_hold, 0xFFC00414) // not found
DEF(zoom_status, 0xA2D4) // "ZoomState"
DEF(movie_status, 0x56C8 + 0x38)
DEF(enabled_refresh_physical_screen, 0x73A0+0x30) //RefreshPhysicalScreen
DEF(playrec_mode, 0x2794+0x4)
DEF(levent_table,0xFFE57A18)
DEF(some_flag_for_af_scan, 0x5BBC)
