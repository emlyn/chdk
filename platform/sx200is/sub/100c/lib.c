#include "platform.h"

/*
*********************
SX200IS
**********************
note sensor size for camera.h is from 
@ FFAC8D6C
0x11CA240 = 18653760
18653760/12 * 8 - 12435840 ---
                              |
@ FFAC8A40                    |
0xFF0 and 0xBE8 =             |
4080  *  3048  = 12435840  ---
*/

char *hook_raw_image_addr()
{
	//found at FFAC8D10
	//ROM:FFAC8D10                 LDR     R6, =0x424B41C0
	//...
	//ROM:FFAC8D60                 MOV     R1, R6
	//ROM:FFAC8D64                 ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"

	return (char*)(0x424B41C0);
}

long hook_raw_size()
{
	//found at FFAC8D6C
	//ROM:FFAC8D6C                 LDR     R1, =0x11CA240
	//ROM:FFAC8D70                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
	//ROM:FFAC8D74                 BL      sub_FF9037E8

	return 0x11CA240;
}

// Live picture buffer (shoot not pressed)
void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x2180;                               // 0x2150 or 0x2180 (suggested by ADamb)
    unsigned char buff = *((unsigned char*)0xF1D8);          // found at FF838090
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	return (void*)0x403F1000;                              // found at FF842AC4 and FFA2BED4
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	return (void*)0x415F9E20;                              // found by search for VRAM Address @FFAC67F0
}

// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d() 
{
	return (void*)(*(int*)(0x2950+0x50));                  // found at FF858A84 and FF859398 (0x58 at FF8594F0)
}



// found at FF8E5F40                 LDR     R1, =0x10E   - height 270
// found at FF8E5F44                 MOV     R0, #0x3C0   - width 960

long vid_get_bitmap_screen_width()
{
//    return SCREENX;  // -------------------------------------yes, the buffer is greater, and de 
	return 320;
}

long vid_get_bitmap_screen_height()
{
//    return SCREENY;  // ---- yes, the buffer is also greater, 
                     //   seems a 16/9 buffer (i.e. 480x270) but duplicating pixels at x : (480x2)x270
	return 240;
}


int vid_get_viewport_width()
{
    return 360;                                               // stays at 360 as IN SD990
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
 return (void*)0x5408C;                                      // found at FF9C1F28
}

long vid_get_bitmap_buffer_width() { return 960; }

long vid_get_bitmap_buffer_height() { return 270; }

