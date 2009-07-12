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
    return (char*)0x10F06B20; //found at 0xFFD82C10
}

long hook_raw_size()
{
    return 0x8D0A68; //found at 0xFFE2DC64
}

void *vid_get_viewport_live_fb()
{
    return (void*)0; //Apparently deprecated
}

void *vid_get_bitmap_fb()  //OSD buffer     
{
    return (void*)0x10361000; //found at 0xFFCC2F24
}

void *vid_get_viewport_fb()
{
	 return (void*)0x10659D50; // found at 0xFFE2B904
}

void *vid_get_viewport_fb_d()
{
    //return (void*)(*(int*)0x5228);  // same as 100e, eg FFC44B58
	// http://chdk.setepontos.com/index.php/topic,2361.msg27125.html#msg27125
	// sub_FFC45328
	return (void*)(*(int*)(0x5080+0x4C));  //might wanna check this, found above ImagePlayer.c
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
    return (char*)0x49A00; // found above a9999
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

