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
    return (void*)(0x105F3170);
}

long vid_get_bitmap_width()
{
    return 360;
}

long vid_get_bitmap_height()
{
    return 240;
}
