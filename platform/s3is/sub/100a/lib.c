#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x345B8;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF8D4788;
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
    return (void*)0x103C79A0;
}

void *vid_get_viewport_fb()
{
    return (void*)0x105f17a0;
}

long vid_get_bitmap_width()
{
    return 360;
}

long vid_get_bitmap_height()
{
    return 240;
}
