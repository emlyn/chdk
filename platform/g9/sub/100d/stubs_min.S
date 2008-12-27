#include "stubs_asm.h"

DEF(physw_status, 0x01563C)						//OK
DEF(physw_run, 0x1ca4)			// 0x1C98 + 0xC	//OK

DEF(playrec_mode, 0x58cc) 		//0x58c8+4		//OK 
DEF(FlashParamsTable,0xFFB08248)				//OK  in FFA4C754
DEF(zoom_busy, 0xE260)  //0xE24C + 0x14			//OK
DEF(focus_busy, 0xE150) //  0xE140+10			//OK?   //in 720 0x9D50<-0x9CB8   0x9CA8+10
DEF(canon_menu_active,0xFDC8)		//0xFDC4+4	//OK
DEF(canon_shoot_menu_active,0xF33D)// 0xF33C+1	//OK
DEF(recreview_hold, 0xF050) // 0xEFA0+0xB0		//OK

DEF(movie_status, 0x5714)  // 0x56D8 + 0x3C		//OK
DEF(some_flag_for_af_scan, 0x1253C)				//OK
DEF(zoom_status, 0x1264C)						//OK
