#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x34AA8;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCC63E0;
}

char *hook_raw_image_addr()
{
    return (char*)0x1056ADD4;
}

long hook_raw_size()
{
    return 0x9E6F10;
}

void *vid_get_viewport_live_fb()
{
//    return (void*)0;
    void **fb=(void **)0x5230;
    unsigned char buff = *((unsigned char*)0x5240);
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
    return (void*)(0x10361000);
}

void *vid_get_viewport_fb()
{
    return (void*)0x105f20c0; //0x1055A2C0;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x65964);
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
    return (char*)0x70EA0;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

