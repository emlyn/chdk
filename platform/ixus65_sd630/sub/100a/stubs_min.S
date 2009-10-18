#include "stubs_asm.h"

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
DEF(zoom_status, 0x7450) // maybe 0x7460 ? sub_FF9B2050, "_MoveOpticalToTele"
DEF(FlashParamsTable,0xFF975EB0)

DEF(canon_menu_active, 0x8300) // FFA13E14 StartRecModeMenu
DEF(canon_shoot_menu_active, 0x75AC+1) // FF9BB06C
DEF(recreview_hold, 0x76E50) // sub_FF9ACFC8

DEF(some_f_for_dng, 0x8CBC)
DEF(second_ext_for_dng, 0x8CE0)
