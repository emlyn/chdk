#include "platform.h"
#include "stdlib.h"
#include "lolevel.h"
/*
*********************
G11
**********************
note sensor size for camera.h is from 
@ FFB09A68
0xEE9200  = 15634944 
15634944/12 * 8  = 10423296 ---
                               |
@ FFB09690                     |
0xEA0 and 0xAE0 =              |
3744  *  2784  =  10423296  --- 

ROM:FFB09A68 DC 10 9F E5                             LDR     R1, =0xEE9200   ; Load from Memory
ROM:FFB09A6C DC 00 8F E2                             ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
 
ROM:FFB09690                         loc_FFB09690                            ; CODE XREF: sub_FFB0965C+10j
ROM:FFB09690 EA 0E A0 E3                             MOV     R0, #0xEA0      ; Rd = Op2
ROM:FFB09694 00 00 81 E5                             STR     R0, [R1]        ; Store to Memory
ROM:FFB09698 AE 0E A0 E3                             MOV     R0, #0xAE0      ; Rd = Op2
*/ 

/*
G11:  IMG VRAM BUFF = 0x4161CFC4 
 	  THUM VRAM BUFF= 0x40A1C030
 	  CRAW BUFF     = 0x41C0F460
 	  CRAW BUFF SIZE= 0xEE9200
 	  JPEG BUFF     = 0x42DEAC00 (0x1215400)
 
*/

char *hook_raw_image_addr()
{
    return (char*)0x41C0F460;  // G11 search for aCrwaddressLxCr " CrwAddress %lx, CrwSize H %ld V %ld\r" 0x41c0f460 0xEA0 0xAE0
							   // or for aCrawBuffP      DCB "CRAW BUFF       %p",0
}

long hook_raw_size()
{
	return 0xEE9200;// G11 OK Search for "aCrawBuffSizeP" 0xEE9200
}

void *vid_get_viewport_live_fb()
{
	    return (void*)0;
#if 0
	void **fb=(void **)0x94E18;                               
	unsigned char buff = *((unsigned char*)0x9114+6);         
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
#endif
}

void *vid_get_bitmap_fb()       
{
	return (void*)0x40471000; // G11 OK  loc_FF85A4BC ir 0xFF85A4C0 (at end of function DispCon_ShowBlackChart
}

void *vid_get_viewport_fb()
{
	
		return (void*)0x40587700;
/*
ROM:FFB067B0 28 12 9F E5                             LDR     R1, =0x40587700 ; Load from Memory
ROM:FFB067B4 20 02 9F E5                             LDR     R0, =0x7E900    ; Load from Memory
ROM:FFB067B8 00 10 84 E5                             STR     R1, [R4]        ; Store to Memory
ROM:FFB067BC 04 00 84 E5                             STR     R0, [R4,#4]     ; Store to Memory
ROM:FFB067C0 95 0F 8F E2                             ADR     R0, aVramAddressP ; "VRAM Address  : %p\r"
*/
					
}

// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x2A50+0x58));   // G11
	 // G11: 0x58 @FF871330  0x2A50 @FF8712F8 (Search for aImageplayer_c)
}


/* ERR99: ToDO: Check if this is also ok for G11 (taken from SX200IS port) */
void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}


char *camera_jpeg_count_str()
{
    return (char*)0x97234;// G11 OK /* Search for a9999 ; "9999" */
/*
ROM:FFA010E4                         loc_FFA010E4                            ; CODE XREF: sub_FFA01020+50j
ROM:FFA010E4 27 CC 50 E2                             SUBS    R12, R0, #0x2700 ; Rd = Op1 - Op2
ROM:FFA010E8 0F C0 5C 22                             SUBCSS  R12, R12, #0xF  ; Rd = Op1 - Op2
ROM:FFA010EC 03 00 00 3A                             BCC     loc_FFA01100    ; Branch
ROM:FFA010F0 34 01 9F E5                             LDR     R0, =0x97234    ; Load from Memory <---
ROM:FFA010F4 4A 1F 8F E2                             ADR     R1, a9999       ; "9999"
ROM:FFA010F8 84 7C F8 EB                             BL      eventproc_export_sprintf ; Branch with Link
ROM:FFA010FC 03 00 00 EA                             B       loc_FFA01110    ; Branch
*/

}


long vid_get_bitmap_screen_width()
{
    return 320;
}

long vid_get_bitmap_screen_height()
{
	return 240;
}

int vid_get_viewport_width()
{
	return 720;
}

long vid_get_viewport_height()
{
   return 240;

}

long vid_get_bitmap_buffer_width() { return 960; } // G11 OK @FF916304 (search for aBmpddev_c)

long vid_get_bitmap_buffer_height() { return 270; } // G11 OK @FF916300

