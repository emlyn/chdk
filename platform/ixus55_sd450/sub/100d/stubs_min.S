#include "stubs_asm.h"

DEF(physw_run, 0x1FAC)  // ok From PhySw sub_FF8264BC (0x1FB0 - 4)
DEF(physw_status, 0x11500) // ok From Dword before sub_FF8264BC

// The names below could be found automanically
// by looking up the strings with the same names as these variables
// and function 'ShowPhySwStatus' which is also symbolic
DEF(NotifyMask, 0x000114D0)
DEF(SwitchMask, 0x000114E0)
DEF(InvertData, 0x000114F0)
// This is the real name for 'physw_status'
DEF(GpioStatus, 0x00011500)
DEF(SwitchStatus, 0x00011510)

DEF(FlashParamsTable,0xFF962180) // ok BL sub_FF961F70 in ParameterManager.c
DEF(canon_menu_active,0x8D88) // ok found in StartRecModeMenu
DEF(canon_shoot_menu_active,0x80C5) // ok (0x80C8 -0x4 + 0x1) found in taskcreate_DSITask
DEF(zoom_busy, 0x89638)  // ok found in "aZoomLens" sub_FFA6D684
DEF(focus_busy, 0x89950) // ok found in "aFocuslenscontr" 
DEF(playrec_mode, 0x6FA0) // found at unknown_libname_442 within task_SsStartupTask
DEF(recreview_hold, 0x86838)
DEF(zoom_status, 0x7FBC)
DEF(movie_status, 0x7CDBC)
DEF(some_flag_for_af_scan, 0x7D4B0)
DEF(parameter_for_af_scan, 0x7D4A8)
DEF(some_f_for_dng, 0x9BE8)
DEF(second_ext_for_dng, 0x9C0C)
DEF(levent_table,0xFF959098)
