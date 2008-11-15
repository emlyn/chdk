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
    return (char*)0x10f3f400;
}

long hook_raw_size()
{
    return 0x9dcce0;
}

void *vid_get_viewport_live_fb()
{
	//21d0 // 00007040 found at ff8c4c70 "LiveImage.c"
	//2084 // 00006ebc found at ff8c4a6c
    void **fb=(void **)0x7040;
    unsigned char buff = *((unsigned char*)0x6ebc);
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
    return (void*)0x10361000;
}

void *vid_get_viewport_fb()
{
    return ((void **)0x7040)[*((unsigned char*)0x6ebc)];
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x18a68);
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
    return (char*)0x4c2c4;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
