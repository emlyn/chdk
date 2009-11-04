#include "stubs_asm.h"

DEF(physw_status, 0x1007C) //Found for A470 (GPIOStatus)
DEF(physw_run, 0x1BF0) //Found for A470 in task_PhySw, same as A590
DEF(FlashParamsTable,  0xFFE961CC) // via GetReservedClusters_Fut_9
DEF(zoom_busy, 0x8050)  //0x803c+14 same as in a590
DEF(focus_busy, 0x82B0) // 0x82A8+0x08 found in sub_FFD02310

DEF(canon_menu_active,0x9014)		// 0x9010+4

//-

DEF(canon_shoot_menu_active,0x9718) // from http://chdk.setepontos.com/index.php/topic,3368.msg37738.html#msg37738

DEF(recreview_hold, 0x95E4) // from http://chdk.setepontos.com/index.php/topic,3368.msg37738.html#msg37738

DEF(movie_status, 0x5200)  // 0x51C8 + 0x38
DEF(some_flag_for_af_scan, 0xCDEC) 
DEF(zoom_status, 0xD7C4) 
DEF(led_table, 0x22AC) //Found using LEDDrv.c
DEF(levent_table,0xFFE72EC4)
DEF(playrec_mode,0x5344+4) // SSAPI:MenuIn
