#include "platform.h"

char *hook_raw_image_addr()
{
	return (char*) (*(int*)(0x574C+0x18) ? 0x435627D8 : 0x41B724C0);
}

long hook_raw_size()
{
	return 0x1076D90;
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x2300;
    unsigned char buff = *((unsigned char*)0x2130); // sub_FF839FC8
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
	return (void*)0x40471000; 
}

void *vid_get_viewport_fb()
{
	return (void*)0x46443400;
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x53C8+0x58)); 
}

//got from FF903960: Width 960
//got from FF90395C: Height 270

long vid_get_bitmap_screen_width()
{
	return 480;
}

long vid_get_bitmap_screen_height()
{
	return 240;
}

long vid_get_viewport_width()
{
	return 480;
}
long vid_get_viewport_height()
{
	return 270;
}

char *camera_jpeg_count_str()
{
	return (char*)0x5CED4;
}


long vid_get_bitmap_buffer_width() { return 480; }
long vid_get_bitmap_buffer_height() { return 270; }
