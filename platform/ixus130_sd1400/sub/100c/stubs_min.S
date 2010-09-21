#include "stubs_asm.h"

//Next two retained from SD990
DEF(some_f_for_dng, 0xDEAD) // TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD) // TODO NOT FOUND!


//BELOW are good and //VERIFY_SD780 Confirmed
DEF(zoom_status, 0xAC68)  //sub_FFA4B984 - Search "ADDLS   PC, PC, R12,LSL#2" or "_StopDigitalZoom"
DEF(movie_status, 0x5B10) // 0x5AD8 + 0x9C - loc_FF91A454  ACTUALLY 0x5AD8 + 0x38 see "ADR     R0, loc_FF91A3C4"
DEF(physw_status, 0xE238) // 0xFF821B80 ShowPhySwStatus
DEF(physw_run, 0x1C34) // 0x1C28 + 0xC @ 0xFF821A3C
DEF(FlashParamsTable,0xFFB2E6AC) // sub_FFA4A620 SD780
DEF(zoom_busy, 0x5A3C)  // 0x5A28 + 0x14  found in sub_FF9165F0 search on "aZoomlens" OK
DEF(focus_busy, 0x5938) //  0x5930 + 0x8, via _sub_FF9115C8__FocusLensController.c__201
DEF(canon_menu_active,0x2CA0) // sub_FF86EC90 0x2C9C + 4 look for EraseAllMenu
DEF(canon_shoot_menu_active,0x6E29)   //sub_FF953AA8  0x6E28+1
DEF(recreview_hold, 0x6C0C) // 0x6B4C + 0xC0 sub_FF946A18, via search on int 0x3007
DEF(some_flag_for_af_scan, 0x6068) //0x6068 0xFF91E078 Search on "LDMFD   SP!, {R1-R11,PC}"  I know it sucks
DEF(levent_table,0xFFB009F0)
DEF(playrec_mode, 0x2A08) //0x2A04+4// Searched on "MenuIn" and it's the last jump.  Similar jump if you look for "MenuOut"
