#include "stubs_asm.h"

DEF(physw_status, 0x01061c)
DEF(physw_run, 0x1ca4)
DEF(FlashParamsTable,0xFFE7D1B4)

DEF(zoom_busy, 0x9DC0)  //0x9DAC + 0x14

DEF(focus_busy, 0x9D50) //  0x9CB8

DEF(canon_menu_active,0xB55C)

#warning incorrect value, points to zero
DEF(canon_shoot_menu_active,0xFFE9CDB4)

#warning incorrect value, points to zero
DEF(recreview_hold, 0xFFE9CDB4)
