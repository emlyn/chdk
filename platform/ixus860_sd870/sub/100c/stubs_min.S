#include "stubs_asm.h"

DEF(physw_status, 0x113FC)
DEF(physw_run, 0x1ca4) 
DEF(FlashParamsTable, 0xFFAD00B4) // it seems

// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
 DEF(touch_keys_angle, 0x429F4)
// Semaphore address to disable Feather processing
 DEF(touch_keys_sema, 0x9C2C)  // 0x9C10 + 0x1C

DEF(zoom_busy, 0xA75C)  //0xA748 + 0x14 to double check
DEF(focus_busy, 0xA65C) //0xA648 + 0x14 ??? to double check
DEF(canon_menu_active,0xC04C) //0xC048 + 4
DEF(canon_shoot_menu_active,0xB65D)   // 0xB65C+1
DEF(recreview_hold, 0xB474) // 0xB3C8+0xAC
DEF(movie_status,0x54E0+0x3C)
