#include "stubs_asm.h"

DEF(led_table, 0x11258) //OK
DEF(physw_run, 0x1FBC) //OK
DEF(physw_status, 0x10FF0) //OK
DEF(canon_menu_active,0x8B5C) //OK

//should be ok
DEF(zoom_busy, 0x6E230)
DEF(zoom_status, 0x7124)
        
//a bit unsure but might be ok
DEF(focus_busy, 0x6E488) 
DEF(movie_status, 0x67108)
DEF(FlashParamsTable,0xFF958138) // dk


//FIXME: wrong!
DEF(canon_shoot_menu_active,0x68F1) //WRONG! COPIED FROM SD400
DEF(recreview_hold, 0x117A8) //WRONG


DEF(levent_table,0xFF9575F8)
DEF(playrec_mode, 0x6DA0) // "MenuIn"
