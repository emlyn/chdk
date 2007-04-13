#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x3F960;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCC6640;
}

char *hook_raw_image_addr()
{
    return (char*)(0x10400000+0x164000+0xBF0);
}

long hook_raw_size()
{
    return 0x8CAE10;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0x10670ee0;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;
}

void *vid_get_viewport_fb()
{
    return (void*)0x105f25e0;
}

long vid_get_bitmap_width()
{
    return 360;
}

long vid_get_bitmap_height()
{
    return 240;
}
