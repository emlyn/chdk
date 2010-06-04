#include "platform.h"

char *hook_raw_image_addr()
{
	return (char*) 0x41F723E0; // found at (0xFF8B8514) near sub_FF8B8510EvfCaptureSystem.c
}

long hook_raw_size()
{
	return 0x11CA240; // FF867B38
}

void *vid_get_viewport_live_fb() // found in sub_FF84DDB8
{
    return 0x0;
}

void *vid_get_bitmap_fb()
{
	return (void*)0x403F1000; // sub_FF90A344 
}

void *vid_get_viewport_fb()
{
	return (void*)0x41020120; // sub_FF8CB908
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x2A30+0x58)); // sub_FF8718D0
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
    return 360;                                               // stays at 360 as IN SD990
}

long vid_get_viewport_height()
{
	return 240;
}

char *camera_jpeg_count_str()
{
	return (char*)0x72DFC; // loc_FF9F71A0
}

long vid_get_bitmap_buffer_width() { return 960; }

long vid_get_bitmap_buffer_height() { return 270; }
