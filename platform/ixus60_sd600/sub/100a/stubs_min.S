#include "stubs_asm.h"

#include "stubs_entry_ida.S"

DEF(physw_run, 0x1FAC)      // ok
DEF(physw_status, 0xE5D8)   // 0xFF826ADC, in sub_FF826AA0

// The names below could be found automanically
// by looking up the strings with the same names as these variables
// and function 'ShowPhySwStatus' which is also symbolic
DEF(NotifyMask, 0x0000E5A8) // also in above sub
DEF(SwitchMask, 0x0000E5B8)
DEF(InvertData, 0x0000E5C8)
DEF(GpioStatus, 0x0000E5D8) // This is the real name for 'physw_status'
DEF(SwitchStatus, 0x0000E5E8)


// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
// DEF(touch_keys_angle, 0x0000E8C8)            // no idea??

DEF(zoom_busy, 0x79BA0)         // "ZoomLens", 0xFFAA4E24
DEF(focus_busy, 0x79EBC)        // FocusLensController, 0xFFAB4DD0 (zoom_busy + 0xFFAC)
DEF(movie_compression, 0x6134)  // 0xFF955B1C (focus_busy - 15F2B4)

DEF(FlashParamsTable,0xFF9749F0)

//DEF(canon_menu_active, 0x6CBC)
//DEF(canon_shoot_menu_active, 0x6CBC)
//DEF(recreview_hold, 0x6CBC)

//DEF(canon_menu_active, 0x6CBC)
//DEF(canon_shoot_menu_active, 0x6CBC)


canon_menu_active_prev:
	.word 0x10

.globl canon_menu_active
canon_menu_active:
 	.word canon_menu_active_prev

