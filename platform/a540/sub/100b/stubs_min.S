#include "stubs_asm.h"

DEF(physw_status, 0xE298)
DEF(physw_run, 0x1FB0)

DEF(canon_menu_active,0x7F80) // StartRecModeMenu sub_FFDE4FAC
DEF(canon_shoot_menu_active,0x74c1)

DEF(recreview_hold, 0x6C878) 


DEF(zoom_busy, 0x6F3A4)  
DEF(focus_busy,0x6F764) //?

DEF(FlashParamsTable,0xFFD5AF48) 

DEF(lcd_brightness,0xC0910080) 
DEF(lcd_brightness_saved,0x63570) 

DEF(movie_status, 0x64794)  
DEF(some_flag_for_af_scan, 0x64DD0)
DEF(parameter_for_af_scan, 0x64DC8)
DEF(zoom_status, 0x733C)

DEF(some_f_for_dng, 0x887C) // found in sub_FFE39174
DEF(second_ext_for_dng, 0x88A0) // .THM
DEF(levent_table, 0xFFD517BC) // PressBlahBLah
DEF(playrec_mode, 0x63C4) // "MenuIn", "MenuOut"
