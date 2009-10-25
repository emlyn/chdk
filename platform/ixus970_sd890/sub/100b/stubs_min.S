#include "stubs_asm.h"

DEF(physw_status, 0x10650)                // @ FF821BFC
DEF(physw_run, 0x1BF4 + 0xC)              // @ FF821ACC
DEF(playrec_mode, 0x5558 + 0x4)           // @ FF861170

DEF(zoom_busy, 0x8A8C + 0x14)             // @ FF932C6C
DEF(focus_busy, 0x8984 + 0x8)             // @ FF92E214
DEF(FlashParamsTable, 0xFFAF9620)         // @ FFA3EEE4
DEF(canon_menu_active, 0x99DC + 4)        // @ FF950194
DEF(canon_shoot_menu_active, 0x9FD8 + 1)  // @ FF96CB00
DEF(recreview_hold, 0x9CEC + 0xAC)        // @ FF960408
DEF(movie_status, 0x5390 + 0x3C)          // @ FF8598A0
DEF(some_flag_for_af_scan, 0xD228)        // @ FFA2B598
DEF(zoom_status, 0xD4A4)                  // @ FFA40290

DEF(some_f_for_dng, 0xDEAD)          // ??? TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD)      // ??? TODO NOT FOUND!
