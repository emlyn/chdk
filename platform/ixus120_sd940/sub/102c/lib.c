#include "platform.h"

char *hook_raw_image_addr()
{
 	// return (char*) (*(int*)(0x29D4 + 0x0C)? 0 : 0x40B28560); 	// "CRAW BUF", "SsImgProcBuf.c:0"

 	return (char*)0x4219D120;									// @FFAD6E84
}

long hook_raw_size()
{
    return 0x11CA240; 									// @FFAD6EE0
}

void *vid_get_viewport_live_fb()
{													// Matched IXUS100-SD780 100c code at 0xFF8B02F4 with IXUS120-SD940 at address 0xFF8D9014
													// Matched IXUS200-SD980 101c code at 0xFF8E0788 with IXUS120-SD940 at address 0xFF8D9014 
	// return (void*) 0;							// __LiveImage.c__  ok
    void **fb=(void **)0x4B34; 			  			// SD940 102C @ 0xFF8D9280  
    unsigned char buff = *((unsigned char*)0x497C); // SD940 103C @ 0xFF8D9018
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
	// 0x7080 determined empirically, but 0x7080 = 2*(960-720)*240
   // return (void*) (0x403F1000 + 0x7080); // dispcon* functions and BmpDDev.c


    return (void*) 0x403F1000;
}

// possible future use, current (or previous ?) bitmap buffer
/*
char *vid_get_bitmap_fb_d()
{
	int *p =(int *)(*(int*)(0xB550 + 0x4));
	return ((char *)(*(p+2)));
}
*/

void *vid_get_viewport_fb()
{
    return (void *) (0x4088B700); // search on VRAM Address
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x2790 + 0x54));  // sub_FF86AE98, similar to sd990  /// +64, +68
}


long vid_get_bitmap_screen_width()
{
    //return 320;

    return 360;
}


long vid_get_bitmap_screen_height()
{
    return 240;
}


long vid_get_viewport_height()
{
    return 240;
}

/// check this
int vid_get_viewport_width()
{
	return 960;
}

char *camera_jpeg_count_str()
{
    return (char *) 0x700B0; // search on "9999"
}

long vid_get_bitmap_buffer_width()
{
	return 960;
}


long vid_get_bitmap_buffer_height()
{
	//return 240;

	return 270;
}
