#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x0; 
}

void *hook_raw_ret_addr()
{
    return (void*)0x0; 
}

char *hook_raw_image_addr()//
{
    return (char*) (0x10587D78);
    //return (char*)0x10B85AA4;
    //return (char*) (0x10D45400);
}

long hook_raw_size()//
{
//	2592x1944 image - compatible with dng4ps2
//	return 0x644c40;
//	2672x1968 image - like most other 5m sensors
	return 0x644C40;
//	2672x1992 image - real sensor size
//	return 0x658560;
        //return 0xA26F00;
}

void *vid_get_viewport_live_fb()
{
    return (void*)0x0;
}

void *vid_get_bitmap_fb()//
{
    return (void*)0x103c79a0;  
}

void *vid_get_viewport_fb()//
{
    return (void*)(0x10605748);
    //return (void*)(0x103f1ea0);
    //return (void*)(0x1069d548);
}

void *vid_get_viewport_fb_d()//
{
    return (void*)(*(int*)0x63a40);
    //return (void*)(*(int*)0x639a8);
    //return (void*)(*(int*)0x63908);
    //return (void*)(*(int*)0x638fc);
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
    return 240;//((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}

char *camera_jpeg_count_str() /* XXXA530XXX */
{
    return (char*)0x6E820;
}
