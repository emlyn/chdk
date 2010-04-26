#include "platform.h"
#include "stdlib.h"
#include "lolevel.h"
/*
*********************
S90
**********************
note sensor size for camera.h is from 
0xEE9200  = 15634944 
15634944/12 * 8  = 10423296 ---
                               |
                               |
0xEA0 and 0xAE0 =              |
3744  *  2784  =  10423296  --- 

*/ 



char *hook_raw_image_addr()
{
    return (char*)0x4213A6EC;  // search for aCrwaddressLxCr " CrwAddress %lx, CrwSize H %ld V %ld\r" 0x41c0f460 0xEA0 0xAE0
							   // or for aCrawBuffP      DCB "CRAW BUFF       %p",0
}

long hook_raw_size()
{
	return 0xEE9200;// Search for "aCrawBuffSizeP" 0xEE9200
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
	return (void*)0x40471000; // G11 OK  @FF858728 (at end of function DispCon_ShowBlackChart
}

void *vid_get_viewport_fb()
{
	
		return (void*)0x407E8A00;
/*
ROM:FFAFF2DC                 LDR     R1, =0x407E8A00
ROM:FFAFF2E0                 LDR     R0, =0x7E900
ROM:FFAFF2E4                 STR     R1, [R4]
ROM:FFAFF2E8                 STR     R0, [R4,#4]
ROM:FFAFF2EC                 ADR     R0, aVramAddressP ; "VRAM Address  : %p\r"
ROM:FFAFF2F0                 BL      sub_FF93500C
ROM:FFAFF2F4                 LDR     R1, [R4,#4]
ROM:FFAFF2F8                 ADR     R0, aVramSize0xX ; "VRAM Size     : 0x%x\r"

*/
					
}

// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x2A20+0x58));   
	 // S90: 0x58 @FF86FA30  0x2A50 @FF86F9F8 (Search for aImageplayer_c)
}


/* ERR99: ToDO: Check if this is also ok for S90 (taken from SX200IS port) */
void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}


char *camera_jpeg_count_str()
{
    return (char*)0x9792C;// S90 OK /* Search for a9999 ; "9999" */
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

