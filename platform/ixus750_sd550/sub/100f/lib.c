#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x36708;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF8D41B0;
}

char *hook_raw_image_addr()
{
    return (char*)(0x10400000+0x160000+0x3980);
}

long hook_raw_size()
{
//    return 0x8CAE10;
    return 0x8CAE10; //7mpx (0x8C0000 + 0xAE00 + 0x10)(find on "A/%08x.CRW")
}

void *vid_get_viewport_live_fb()
{
    return (void*)0x0;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x103C79A0;
}

void *vid_get_viewport_fb()
{
//    return (void*)0x104B6C20;
//    return (void*)0x10559670;
    return (void*)0x105F1370;
}

void *vid_get_viewport_fb_d()
{
//    return (void*)(*(int*)0x5BAEC);
 //return (void*)0x104B6C20;
	return (void *)0x72588;

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
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}
char *camera_jpeg_count_str()
{
    return (char*)0x72588;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
