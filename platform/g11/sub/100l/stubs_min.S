#include "stubs_asm.h"

DEF(physw_status, 0x32578)						//G11
DEF(physw_run, 0x1c44) // 0x1C38 + 0xC  G11
DEF(FlashParamsTable,0xFFBE73C0) // G11@ FFAB4A54
DEF(playrec_mode, 0x2D60+0x4) //G11 (ref@FF8805F4)
DEF(zoom_busy, 0x6CAC+0x14)  //G11 @xFF95EC58
DEF(focus_busy, 0x6BAC+0x8) //G11 @FF959C4C                               0x9CA8+10
DEF(zoom_status, 0xC868) //G11 @FFAB74A4
DEF(led_table, 0x25B4 + 0x04) // G11 @FF85F278
DEF(levent_table,0xFFB95FE0) //G11

DEF(canon_shoot_menu_active,0x8258+0x1) // g11 @FF9AF884
DEF(canon_menu_active,0x3038+0x4) // g11 @FF88E2CC


DEF(recreview_hold, 0x7D00 + 0xD8) 
DEF(movie_status, 0x6D58+0x38)  
DEF(some_flag_for_af_scan, 0x72B4) 

DEF(enabled_refresh_physical_screen, 0x9840) //G11 at FFA0ECB8

