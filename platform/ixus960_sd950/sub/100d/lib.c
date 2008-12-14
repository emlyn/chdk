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
    return (char*) (*(int*)0x5670 ? 0x11F6C720 : 0x108067A0);


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
    return (void*)0x1065B540;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x53B4);  
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
    return (char*)0x5A668;
}

long vid_get_bitmap_screen_width()
{
    return 360;
}

long vid_get_bitmap_screen_height()
{
    return 240;
}

int movie_status = 0;


long vid_get_bitmap_buffer_width() { return 360; }


long vid_get_bitmap_buffer_height() { return 240; }


void _EnterToCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
void _ExitFromCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
