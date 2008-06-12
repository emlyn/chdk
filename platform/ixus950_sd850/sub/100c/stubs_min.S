#include "stubs_asm.h"

// based on quietschi's port to SD1000

DEF(physw_status, 0x587E0)	// see PhySw task at FFA370D4
DEF(physw_run, 0xA4A0)		// Ibid

DEF(zoom_busy, 0x835B4)		// "ZoomLens"
DEF(focus_busy, 0x82E18)	// "FocusLens"

DEF(playrec_mode, 0xF074)	// after "SsStartupTask.c", in the first called f-n

DEF(FlashParamsTable, 0xFFB4DCB8)	// in GetReservedClusters_Fut_7 (sub_FFB4DE74), LDR R3, =off_FFB4DCB8
DEF(canon_menu_active,0x389C)		// after "StartRecModeMenu", LDR R4, =0x389C
DEF(canon_shoot_menu_active,0x27FD)	// after "DSITask.c", LDR R5, =0x2800; then
					// 0x2800-4+1=0x27FD (quietschi's prescription, SD1000)
DEF(recreview_hold, 0x25E0)		// after "AR:Snd:0x%04x", LDR R3, =0x25E4; then
					// 0x25E4-4=0x25E0 (quietschi's prescription, SD1000)
DEF (movie_state,0xA8638)
