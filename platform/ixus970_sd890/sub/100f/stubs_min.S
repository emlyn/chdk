#include "stubs_asm.h"

DEF(physw_status, 0x10650)                // @ FF821BFC
DEF(physw_run, 0x1BF4 + 0xC)              // @ FF821ACC
DEF(playrec_mode, 0x5558 + 0x4)           // @ FF8610F4

DEF(zoom_busy, 0x8A8C + 0x14)             // @ FF932BF4
DEF(focus_busy, 0x8984 + 0x8)             // @ FF92E198
DEF(FlashParamsTable, 0xFFAF96D8)         // @ FFA3EE54
DEF(canon_menu_active, 0x99DC + 4)        // @ FF950104
DEF(canon_shoot_menu_active, 0x9FD8 + 1)  // @ FF96CA70
DEF(recreview_hold, 0x9CEC + 0xAC)        // @ FF960378
DEF(movie_status, 0x5390 + 0x3C)          // @ FF859824
DEF(some_flag_for_af_scan, 0xD228)        // @ FFA2B508
DEF(zoom_status, 0xD4A4)                  // @ FFA40200

DEF(some_f_for_dng, 0xDEAD)          // ??? TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD)      // ??? TODO NOT FOUND!
