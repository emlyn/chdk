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
 return (char*) (*(int*)0x5684 ? 0x11F6B740 : 0x108057C0);
 //  return (char*)0x108057C0;
}

long hook_raw_size()
{
    return 0xEE9710;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0;
}

void *vid_get_bitmap_fb()       
{
    return (void*)0x10361000;
}

void *vid_get_viewport_fb()
{
    return (void*)0x1065A560;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x53E8);  // 0x53A0 + 0x48
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
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char*)0x5CB38;
}
