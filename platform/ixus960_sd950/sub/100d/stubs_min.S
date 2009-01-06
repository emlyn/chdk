#include "stubs_asm.h"

DEF(physw_status, 0x14CFC)
DEF(physw_run, 0x1ca4) 
DEF(FlashParamsTable, 0xFFAD6F9C) 

// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
 DEF(touch_keys_angle, 0x46464)
// Semaphore address to disable Feather processing
 DEF(touch_keys_sema, 0xD2A0)  // 0xD284 + 0x1C

DEF(zoom_busy, 0xDE7C)  //0xDE68 + 0x14 to double check
DEF(focus_busy, 0xDD7C) //0xDD68 + 0x14 ??? to double check
DEF(canon_menu_active,0xF7D4) //0xF7D0 + 4
DEF(canon_shoot_menu_active,0xEDE5)   // 0xEDE4+1
DEF(recreview_hold, 0xEBFC) // 0xEB50+0xAC
DEF(zoom_status, 0x11E48)
DEF(movie_status, 0x5524)  // 0x54E8+0x3C
