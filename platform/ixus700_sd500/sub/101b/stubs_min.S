#include "stubs_asm.h"

DEF(physw_status, 0xFB20)
DEF(led_table, 0x7703C)

DEF(zoom_busy, 0x76B4C)
DEF(focus_busy, 0x76E4C)
DEF(FlashParamsTable,0xFF9697E0)
DEF(canon_menu_active,0x72C8)
DEF(canon_shoot_menu_active,0x65B5)
DEF(recreview_hold, 0x739F8)
DEF(movie_status,0x6F684)
DEF(some_flag_for_af_scan, 0x6F2E0) // found in _PrepareSeq.c__1056+0x59, CMP R2,#0 | LDREQ R3,=0x6F2E0 | STREQ R2,[R3]