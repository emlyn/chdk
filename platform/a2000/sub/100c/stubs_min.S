#include "stubs_asm.h"

// Found at: ROM:FFC110FC
DEF(physw_status, 0xF418)

// Found at: ROM:FFC11064 and ROM:FFC11080
DEF(physw_run, 0x1BD8 + 0xC)

// Found at: ROM:FFDFBF64
DEF(FlashParamsTable,0xFFEB9CDC)

// Found at ROM:FFD032E0 and ROM:FFD0323C 
DEF(zoom_busy, 0x7FE4 + 0x14) 

// Found at: ROM:FFCFE810 and ROM:FFCFE824
DEF(focus_busy, 0x7EDC + 0x8)

// Found at: ROM:FFC59E44 and ROM:FFC59DA8
DEF(canon_menu_active,0x545C + 0x4)

// Found at: ROM:FFD3BD08 and ROM:FFD3BAF0
DEF(canon_shoot_menu_active,0x9734 + 0x1) 

// Found at: ROM:FFD2F99C and ROM:FFD2FC9C
DEF(recreview_hold, 0x9408 + 0xB8) 

// Found at: ROM:FFDFD488
DEF(zoom_status, 0xC0CC)

// Found at: ROM:FFC47048 and ROM:FFC4C788
DEF(movie_status, 0x5048 + 0x38)  // 0x5538 + 0x38

// Found at: ROM:FFD0AFCC and 
DEF(some_flag_for_af_scan, 0x85A0)

//DEF(some_f_for_dng, 0x8934)
//DEF(second_ext_for_dng, 0x8954)

// Found at ROM:FFC4EBBC and ROM:FFC4E8AC
DEF(playrec_mode, 0x5204+0x4)

// Found at ROM:FFD7AAA8 and ROM:FFD7AF04
DEF(enabled_refresh_physical_screen, 0xA478+0x30 )
DEF(levent_table,0xFFE9AC78)
