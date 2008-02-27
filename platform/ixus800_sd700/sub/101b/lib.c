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
    return (char*)(0x105B8AC0);
}

long hook_raw_size()
{
    return 0x75A8F0;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x103C79A0 ;
}

void *vid_get_viewport_fb()
{
    return (void*)0x105F17A0;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x6DC7C);
}

long vid_get_bitmap_width()
{
    return 360;
}

long vid_get_bitmap_height()
{
    return 240;
}

long vid_get_viewport_height()
{
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}

char *camera_jpeg_count_str()
{
    return (char*)0x79248;
}
