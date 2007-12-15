#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x2F490;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF8D8BDC;
}

char *hook_raw_image_addr()
{
    return (char*)(0x10400000+0x160000+0x3A80);
}

long hook_raw_size()
{
    return 0x8CAE10;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0x0;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x103CEB20;
}

void *vid_get_viewport_fb()
{
//    return (void*)0x104B6C20;
//    return (void*)0x10559670;
    return (void*)0x105F1470;
}

void *vid_get_viewport_fb_d()
{
//    return (void*)(*(int*)0x5BAEC);
 return (void*)0x104B6C20;
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
