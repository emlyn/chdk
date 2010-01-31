#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0;
}

void *hook_raw_ret_addr()
{
    return (void*)0;
}

char *hook_raw_image_addr()
{
	return (char*) (*(int*)(0x550C) ? 0x11B97B60 : 0x107D68C0);
}

long hook_raw_size()
{
    return 0xEC04F0; // (3720 x 2772 * 12bit) / 8bit // ixus90 from 0xFFA812AC
}

void *vid_get_viewport_live_fb()
{
	void **fb=(void **)0x7424;
    unsigned char buff = *((unsigned char*)0x72A0);
    if (buff == 0) buff = 2;  else buff--;
    return fb[buff];
}

void *vid_get_bitmap_fb()       
{
    return (void*)0x10361000; // ixus90
}

void *vid_get_viewport_fb()
{
    return (void*)0x1065ADC0; //  ixus90
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x5248);  // ixus 90
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
    return (char*)0x4C97C; // ixus90
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
