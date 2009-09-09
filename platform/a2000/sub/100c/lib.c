#include "platform.h"

char *hook_raw_image_addr()
{
	// Found 0x11B96B80 at ROM:FFC377A0
	// Found 0x107D58E0 at ROM:FFC756CC
	// 0x51A0 + 0x18 found at ROM:FFC4C15C	
	return (char*) (*(int*)(0x51A0+0x18) ? 0x11B96B80 : 0x107D58E0);
}

long hook_raw_size()
{
	// Found at: FFE46CBC
	return 0xEC04F0;
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x6A68;  // at: ROM:FFC9FB74
    unsigned char buff = *((unsigned char*)0x68DC);	// at: ROM:FFC9FB6C
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
	return (void*)0x10361000; // at: ROM:FFDC306C
}

void *vid_get_viewport_fb()
{
	return (void*)0x10659DE0;		// at ROM:FFE44B48
}

void *vid_get_viewport_fb_d()
{

    return (void*)(*(int*)(0x4ECC + 0x54));   // found at ROM:FFC40CD0 and ROM:FFC46554
}


void *hook_raw_fptr()
{
	// found at ROM:FFE46CBC
	return 0xEC04F0;
}

void *hook_raw_ret_addr()
{
	return (void*)0; // What does this do? Doesn't seem to be called
}


long vid_get_bitmap_screen_width()
{
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

char *camera_jpeg_count_str()
{
	return (char*)0x45100;
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

//int zoom_status = 0;
