#include "platform.h"

char *hook_raw_image_addr()
{
//    return (char*)0x40EBAFA0; // seach on CRAW BUF
 	return (char*) (*(int*)(0x5520 + 0x18)? 0x42CFB780 : 0x40EBAFA0); 
	// similar to a560, searched for first raw address in a table with others, get variable from functions that use table
}

long hook_raw_size()
{
    return 0x1574D00; // CRAW BUF SIZE
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x2254;
    unsigned char buff = *((unsigned char*)0x20B8); // sub_FF839850
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
    return (void*)0x40471000; // dispcon* functions and BmpDDev.c
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
    return (void *)0x407F6DC0; // search on VRAM Address
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x5210 + 0x54));  // sub_FF85BE10, similar callers to a720, ref string "HFILYUV"
}


long vid_get_bitmap_screen_width()
{
//    return 720;
    return 360; // real is 720, lie for aspect correction
}

long vid_get_bitmap_screen_height()
{
    return 240;
}

long vid_get_viewport_height()
{
    return 240;
}

int vid_get_viewport_width()
{
	return 360; // viewport is still 360, even though live view is 720
}

char *camera_jpeg_count_str()
{
    return (char *)0x4AF18; // search on "9999"
}

long vid_get_bitmap_buffer_width() { return 720; } // _sub_FF8EA47C__BmpDDev_c__134... 
                                                   // or maybe not, some 360x240 cams have this too ?

long vid_get_bitmap_buffer_height() { return 240; }


