#include "stubs_asm.h"

DEF(physw_status, 0xFC38) //ok
DEF(physw_run,  0x1FAC) //ok
DEF(zoom_busy, 0x7CFD0) //ok
DEF(focus_busy, 0x7D2E8) //ok
DEF(FlashParamsTable,0xFFD3E68C)
DEF(canon_menu_active,0x8090) //ok
DEF(canon_ev_corr_menu_active, 0xD5D8)
DEF(canon_shoot_menu_active,0x7605) // (0x7608 - 0x4 + 0x1) found in "taskcreate_DSITask"
DEF(recreview_hold, 0x7A620) // 0xFFD71AC4
DEF(movie_status, 0x72564) // ok 0xFFD1F840
DEF(zoom_status, 0x74B8) // ok
DEF(some_f_for_dng, 0x8BE0) // found in 0xFFE11B8C
DEF(some_flag_for_af_scan, 0x72BA0) // 0xFFD2A294
DEF(levent_table, 0xFFD3547C)
DEF(playrec_mode, 0x639C) // FFD32638
