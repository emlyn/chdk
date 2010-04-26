#include "stubs_asm.h"
DEF(zoom_busy, 0x7a00+0x14)          
DEF(focus_busy, 0x78d4 + 8)               
DEF(zoom_status, 0x8AA4) //S90                 
DEF(physw_status, 0x330d8)                 
DEF(physw_run, 0x1C38 + 0x0C)            
DEF(FlashParamsTable,0xFFBEFB70)      
DEF(canon_menu_active, 0x3034 + 4)        
DEF(canon_shoot_menu_active, 0x8944 + 1)  
DEF(recreview_hold, 0x8944+0xE4)  //S90@0xFF99693C 
DEF(movie_status, 0x7ab0 + 0x38)         
DEF(enabled_refresh_physical_screen, 0xa36c) 
DEF(playrec_mode, 0x2d60+0x4)         
DEF(some_flag_for_af_scan, 0x7FF4)	     
DEF(led_table, 0x24AC + 0x04)             
DEF(levent_table,0xFFB8B470)
DEF(enabled_refresh_physical_screen, 0xA36C) //S90 at FFA07D50

