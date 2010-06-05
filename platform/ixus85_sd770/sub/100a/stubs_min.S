#include "stubs_asm.h"

DEF(physw_status, 0x104D0)                // @ FF821BF8 // OK
DEF(physw_run, 0x1BF4 + 0xC)              // @ FF821ACC // OK
DEF(playrec_mode, 0x5530 + 0x4)           // @ FF860F44 // OK

DEF(zoom_busy, 0x8694 + 0x14)             // @ FF9303E4 // OK
DEF(focus_busy, 0x85AC + 0x8)             // @ FF92BE8C // OK
DEF(FlashParamsTable, 0xFFAF0DB4)         // @ FFA398CC // OK
DEF(canon_menu_active, 0x9604 + 4)        // @ FF94DF80 // OK
DEF(canon_shoot_menu_active, 0x9F4C + 1)  // @ FF96B04C // OK
DEF(recreview_hold, 0x9C80 + 0xAC)        // @ FF95F3F8 // OK
DEF(movie_status, 0x5368 + 0x3C)          // @ FF859694 // OK
DEF(some_flag_for_af_scan, 0xD0AC)        // @ FFA262E0 // OK
DEF(zoom_status, 0xD328)                  // @ FFA3AC78 // OK

DEF(some_f_for_dng, 0xDEAD)          // ??? TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD)      // ??? TODO NOT FOUND!
DEF(levent_table,0xFFACD870)
