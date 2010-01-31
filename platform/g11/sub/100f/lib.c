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
/*
G11:  IMG VRAM BUFF = 0x4161CFC4 
 	  THUM VRAM BUFF= 0x40A1C030
 	  CRAW BUFF     = 0x41C0F460
 	  CRAW BUFF SIZE= 0xEE9200
 	  JPEG BUFF     = 0x42DEAC00 (0x1215400)
 
*/

void *vid_get_bitmap_fb()       
{
	return (void*)0x40471000; // G11 OK  loc_FF85A4BC ir 0xFF85A4C0 (at end of function DispCon_ShowBlackChart
}

void *vid_get_viewport_fb()
{
	
		return (void*)0x40587700;//g11 OK
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

long vid_get_bitmap_buffer_width() { return 960; } 

long vid_get_bitmap_buffer_height() { return 270; }

