#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x2F490;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF8D8BB4;
}

char *hook_raw_image_addr()
{
    return (char*)(0x10595D54);
}

long hook_raw_size()
{
    return 0x644C40;
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
    return (void*)0x105F84F0; // 0x104B6C20;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x5BAEC);   //0x5BAD8, 0x5BAEC, 0x5BB00
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
    return (char*)0x63518;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

