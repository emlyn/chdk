#include "stubs_asm.h"

//DEF(physw_status, 0xFB20)
DEF(physw_status, 0xFBB0) // from wrap_kbd_p1_f + 0x10 OK!
DEF(led_table, 0xFDC8) // In aLedcon Data section OK!

DEF(zoom_busy, 0x76C7C) // above aZoomlenscontro OK!
DEF(focus_busy, 0x76F7C) // in sub after aFocuslenscontr OK!
DEF(FlashParamsTable,0xFF973E60) // OK!
DEF(canon_menu_active,0x76DC) // in sub StartRecModeMenu OK!
DEF(canon_shoot_menu_active,0x68F1) // (0x68F4 - 0x4 + 0x1) found in "taskcreate_DSITask" OK!
DEF(recreview_hold, 0x73CF0) // OK!
DEF(zoom_status, 0x6804)
DEF(movie_status, 0x6F95C)
