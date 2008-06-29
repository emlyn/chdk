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
//    return (void*)0;
    void **fb=(void **)0x54e8;
    unsigned char buff = *((unsigned char*)0x54f8);
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
    return (void*)0x103C79A0;
}

void *vid_get_viewport_fb()
{
    return (void*)0x105f17a0; //0x105599A0;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x60134);
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
    return (char*)0x6BC28;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
