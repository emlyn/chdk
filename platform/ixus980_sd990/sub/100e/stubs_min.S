#include "stubs_asm.h"

DEF(physw_status, 0x11318) // 0xFF8219DC ShowPhySwStatus
DEF(physw_run, 0x1c28) // 0x1C1C + 0xC @0xFF821894 task_PhySw
DEF(FlashParamsTable,0xFFB499F4) // sub_FFA58670, search for ParameterManager.c
DEF(zoom_busy, 0x8A1c)  // 0x8A08 + 0x14, found in sub_FF93368 search on "ZoomLens" OK
DEF(focus_busy, 0x8914) //  0x890C + 0x8, via _sub_FF92E770__FocusLensController_c__201 and comparison to s5is OK
DEF(canon_menu_active,0x5830) // 0x582C+4, StartRecModeMenu OK
DEF(canon_shoot_menu_active,0xA351)   // 0xA350+1, search on "AC:StartShutTimer", similar to a720 OK
DEF(recreview_hold, 0xA0A0) // 0x9FDC + 0xC4 sub_FF9659B4, via search on int 0x3007, similar to s5 101b. Doesn't appear to work.
DEF(movie_status, 0x53DC)  // 0x53A0 + 0x3C via  loc_FF861EAC and _sub_FF860E64__MovieRecorder_c__0 OK
DEF(some_flag_for_af_scan, 0x93E0) // search on "SsPrepareSeq.c", refs at FF93BF9C similar to a720 OK
DEF(zoom_status, 0xD890) // sub_FFA599D4, search on ZoomCon_EnterCaptModeChange OK, NOTE may have more values than other cams ?
DEF(some_f_for_dng, 0xDEAD) // TODO NOT FOUND!
DEF(second_ext_for_dng, 0xDEAD) // TODO NOT FOUND!
