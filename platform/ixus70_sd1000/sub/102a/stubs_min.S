#include "stubs_asm.h"

DEF(physw_status, 0x564B0) // find in "PhySw"
DEF(physw_run, 0x87B4) // find in "PhySw"

DEF(zoom_busy, 0x96804) // find in "ZoomLens"
DEF(focus_busy, 0x95F50) // find in "FocusLens"
DEF(playrec_mode,0xD0CC) // BL      unknown_libname_797 found in "taskcreate_SsStartupTask"
DEF(FlashParamsTable,0xFFB3E4BC) // BL      sub_FFB3E678 found in "ParameterManager.c"
DEF(canon_menu_active,0x3760) // found in "StartRecModeMenu"
DEF(canon_shoot_menu_active,0x27C9) // (0x27CC - 0x4 + 0x1) found in "taskcreate_DSITask"
DEF(recreview_hold, 0x25AC) // (0x25B0 - 0x4) found in "AR:Snd:0x%04x"
DEF(zoom_status, 0x2680)
DEF(movie_status, 0xBB558)
DEF(some_flag_for_af_scan, 0xCDB4) // found in _SsPrepareSeq.c__444+0x58, CMP R2,#0 | LDREQ R3,=0xCDB4 | STREQ R2,[R3]
