#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x42990;	//sync with a630
}

void *hook_raw_ret_addr()
{
    return (void*)0x0;
}

char *hook_raw_image_addr()
{
    return (char*)0x10563530;	//sync with a630
}

long hook_raw_size()	//sync with a560 (on wiki page)
{
    return 0x8CAE10;
}

void *vid_get_viewport_live_fb() // 0x105F0000 + 0xF20 + 0x7E000 + 0x900 (find on "VRAM Address  : %p")
{
    return (void*)0x1066F820;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000; //(0x10360000 + 0x1000)	//sync with ixus70 (on forum)
}

void *vid_get_viewport_fb()
{
	return (void*)0x10559120; //sync with a610	
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x3C2E0); //sync with a540 and ixus70 (on forum)
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
    return 240;		//((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}

char *camera_jpeg_count_str()
{
    return (char*)0xF840;		//find on "DCB "9999",0"
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
