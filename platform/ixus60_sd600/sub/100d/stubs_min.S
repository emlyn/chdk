#include "stubs_asm.h"

#include "stubs_entry_ida.S"

DEF(physw_run, 0x1FAC)      // ok
DEF(physw_status, 0xE5F8)   // 0xFF826ADC, in sub_FF826AA0

// The names below could be found automanically
// by looking up the strings with the same names as these variables
// and function 'ShowPhySwStatus' which is also symbolic
DEF(NotifyMask, 0x0000E5C8) // also in above sub
DEF(SwitchMask, 0x0000E5D8)
DEF(InvertData, 0x0000E5E8)
DEF(GpioStatus, 0x0000E5F8) // This is the real name for 'physw_status'
DEF(SwitchStatus, 0x0000E608)


// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
// DEF(touch_keys_angle, 0x0000E8C8)            // no idea??

DEF(zoom_busy, 0x79C18)         // ZoomLens, 0xFFAA591C
DEF(focus_busy, 0x79F34)        // FocusLensController, 0xFFAB58C8
DEF(movie_compression, 0x6140)  // 0xFF956614
DEF(zoom_status, 0x73D8)
DEF(FlashParamsTable,0xFF9754E8)

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

