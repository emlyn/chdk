#include "stubs_asm.h"

DEF(physw_status, 0x11078) // via taskcreate_PhySw (after "PhySwDrv.c")
DEF(physw_run, 0x1C1C + 0x0C) // via task_Startup, 5th BL after nullsub, then 4th BL after BuildInfo.c
DEF(FlashParamsTable,0xFFB2D4D0) // via first bbl in ParameterManager.c__90
DEF(zoom_busy, 0x88A0 + 0x14) // via aZoomlens, 3rd STR above it (highest of the three STRs)
DEF(focus_busy, 0x87A4 + 0x8) // via aFocuslens, 3rd STR above it (lowest of the STRs)
DEF(canon_menu_active, 0x560C + 0x4) // via (aEraseallmenu_c and) _sub_.._EraseAllMenu.c__126, top of calling function
DEF(canon_shoot_menu_active, 0xA160 + 0x1) // via call before aAcStartshuttim, then second call, then second STRB
DEF(recreview_hold, 0x9E18 + 0x84) // via function below function using a_shutdownshoot ??? (0xA78C + 0xDC) via sub_FF977BD8 of sx10
DEF(zoom_status, 0xD570) // via aM_zoomstateD
DEF(movie_status, 0x51A8 + 0x3C) // via first str after cmp in sub_FF...__MovieRecorder.c__0 (the one with call to ExMemMan.c__0)
DEF(enabled_refresh_physical_screen, 0xB268+0x30) // via aScreenLock, after ldr of 0xB268
DEF(playrec_mode, 0x5394+0x4) // @0xff865b40, via aShootseqapi_c (adrne/ldrne ~), between the ZoomCtrl and CameraLog above, the one below MOV R0, #1
