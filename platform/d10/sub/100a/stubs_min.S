#include "stubs_asm.h"

DEF(physw_status, 0xE238) // ShowPhySwStatus, "GpioStatus  "
DEF(physw_run, 0x1C2C + 0xC) // task_PhySw
DEF(playrec_mode,0x2B88 + 0x4) // "MenuIn"
DEF(canon_menu_active,0x2E28 + 0x4) // "StartRecModeMenu"
DEF(canon_shoot_menu_active,0x7404 + 0x1)   // sub_FF96B3C0, via loc_FF87913C sub_FF878FF4 calls reboot: sub_FF828E54, near HwErrPreShtDwn
DEF(FlashParamsTable,0xFFB330F4) // sub_FFA54AB8, near pointer to canon mode list FFB32F18
DEF(levent_table,0xFFB08638) // find_levent 
DEF(recreview_hold,0x70B0 + 0xC4) // from sub_FF95C814 via search on int 0x3007, similar to sd990, TODO may not be right
DEF(zoom_status, 0xAD70) // sub_FFA56810, search on ZoomCon_EnterCaptModeChange similar to sd990
DEF(zoom_busy, 0x5EFC + 0x14)  // 0x5EFC + 0x14, found in sub_FF92B59C search on "ZoomLens", similar to sd990
DEF(focus_busy, 0x5E00 + 0x8) //  0x5E00 + 0x8, via sub_FF9265C0 and found by search on "M:IS_RST_E"
DEF(movie_status, 0x4B29C + 0x38)  // 0x4B29C + 0x38 via task_MovieRecord -> sub_FF92F3E8 -> loc_FF92F36C
DEF(some_flag_for_af_scan, 0x6508) // search on "SsPrepareSeq.c" -> sub_FF932650 -> sub_FF9325DC -> FF932628 similar to sd990

DEF(some_f_for_dng, 0xDEAD) // TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD) // TODO NOT FOUND!
