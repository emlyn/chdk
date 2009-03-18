#include "platform.h"

char *hook_raw_image_addr()
{
	return (char*) (*(int*)(0x55CC+0x18) ? 0x424F1948 : 0x40F65B18);
}

long hook_raw_size()
{
	return 0xEC04F0;
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x227C;
    unsigned char buff = *((unsigned char*)0x20D0); // sub_FF839DD8
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
	return (void*)0x403B1000; 
}

void *vid_get_viewport_fb()
{
	return (void*)0x4070D9D0;
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x5260+0x58)); 
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
	return (char*)0x4C138;
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
