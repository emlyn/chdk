#include "stubs_asm.h"

#include "stubs_entry_ida.S"

DEF(physw_run, 0x1FAC)
DEF(physw_status, 0xE758)

// The names below could be found automanically
// by looking up the strings with the same names as these variables
// and function 'ShowPhySwStatus' which is also symbolic
DEF(NotifyMask, 0x0000E728)
DEF(SwitchMask, 0x0000E738)
DEF(InvertData, 0x0000E748)
// This is the real name for 'physw_status'
DEF(GpioStatus, 0x0000E758)
DEF(SwitchStatus, 0x0000E768)


// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
DEF(touch_keys_angle, 0x0000E8C8)

DEF(zoom_busy, 0x79E20)
DEF(focus_busy, 0x7A13C)
DEF(movie_compression, 0x617C)

DEF(FlashParamsTable,0xFF975EB0)

// TODO: !!!!!!!!!!!!! THESE ARE INVALID !!!!!!!!
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

