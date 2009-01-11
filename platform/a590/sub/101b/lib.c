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
    return (char*)0x10F63920; //found at 0xFFD987A8
}

long hook_raw_size()
{
    return 0x9DCCE0;
}

void *vid_get_viewport_live_fb()
{
//    return (void*)0;//0x10670ee0;
    void **fb=(void **)0x2168;
    unsigned char buff = *((unsigned char*)0x1FE8); //0x1fe8 found at 0xFFC294D
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

void *vid_get_bitmap_fb()  //OSD buffer     
{
    return (void*)0x10361000; //found at FFDC0F84
}

void *vid_get_viewport_fb()
{
	 return (void*)0x10659E80; // same as 100e, search on constant

}

void *vid_get_viewport_fb_d()
{
    //return (void*)(*(int*)0x5228);  // same as 100e, eg FFC44B58
	// http://chdk.setepontos.com/index.php/topic,2361.msg27125.html#msg27125
	// sub_FFC45328
	return (void*)(*(int*)(0x520C+0x4C));  //0x5258
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
    return (char*)0x49344; // same as 100e, found @ FFD727B0
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

