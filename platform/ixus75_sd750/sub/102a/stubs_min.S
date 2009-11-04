#include "stubs_asm.h"

// Actually found this in ShowPhySwStatus
DEF(physw_status, 0x56908) // find in "PhySw"

// Actually found this at 0xFFA3954C
DEF(physw_run, 0x88C4) // find in "PhySw"

DEF(zoom_busy, 0x96EE4) // find in "ZoomLens"
DEF(focus_busy, 0x96630) // find in "FocusLens"
//DEF(playrec_mode,0xCFD8) // BL      unknown_libname_797 found in "taskcreate_SsStartupTask"
DEF(playrec_mode,0xD2A0) // reyalp - first call in SsStartupTask
DEF(FlashParamsTable,0xFFB4A07C) 
DEF(canon_menu_active,0x3850) // found in "StartRecModeMenu"
DEF(canon_shoot_menu_active,0x27FD) // (0x2800 - 0x4 + 0x1) found in "taskcreate_DSITask"
DEF(recreview_hold, 0x25E4) // (0x25E8 - 0x4) found in "AR:Snd:0x%04x"
DEF(movie_status,0xBBC48)
DEF(zoom_status, 0x26B8) // found near _MoveOpticalToTele, _StopOpticalZoom etc
DEF(some_f_for_dng, 0x7214)
DEF(second_ext_for_dng, 0x7238)
DEF(levent_table,0xFFB3AACC)
