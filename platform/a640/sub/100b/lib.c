#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x34C50;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCC7FF0;
}

char *hook_raw_image_addr()
{
    return (char*)0x105BA490;
}

long hook_raw_size()
{
    return 0xC58758;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0;
}

void *vid_get_bitmap_fb()
{
    return (void*)(0x10361000);
}

void *vid_get_viewport_fb()
{
    return (void*)0x105F3170; //0x1055B370;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x65b2c);
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
    return (char*)0x71200;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

