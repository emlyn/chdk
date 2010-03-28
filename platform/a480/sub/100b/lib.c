#include "platform.h"

char *hook_raw_image_addr()
{
	return (char*) 0x10C5FA60; // "CRAW BUFF"
}

long hook_raw_size()
{
	return 0xEC04F0;           // "CRAW BUFF SIZE"
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x3E80;
    unsigned char buff = *((unsigned char*)0x3CF0); // sub_FFC87F0C
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
	return (void*)0x10361000; // "BmpDDev.c"
}

void *vid_get_viewport_fb()
{
	return (void*)0x10659EC0;  // "VRAM Address"
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x2554+0x54)); // sub_FFC3C050
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
	return (char*)0x2CFF8;  // "9999"
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
