#include "stubs_asm.h"

//DEF(physw_status, 0xFB20)
DEF(physw_status, 0xFBB0) // from wrap_kbd_p1_f + 0x10
DEF(led_table, 0xFDC8) // In aLedcon Data section

DEF(zoom_busy, 0x76C7C) // above aZoomlenscontro
DEF(focus_busy, 0x76F7C) // in sub after aFocuslenscontr 
DEF(FlashParamsTable,0xFF973E0C)
DEF(canon_menu_active,0x76DC) // in sub StartRecModeMenu
DEF(canon_shoot_menu_active,0x68F1) // (0x68F4 - 0x4 + 0x1) found in "taskcreate_DSITask"
DEF(recreview_hold, 0x73CF0)
DEF(zoom_status, 0x6804)
DEF(movie_status, 0x6F95C)
