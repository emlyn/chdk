#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x3FCF0; // check could be f0,f4,or maybe ec fc ...
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF998A6C; // check should be nullsub
}

char *hook_raw_image_addr()
{
    return (char*)0x1058EBD4; // ( found on aA08x_crw)
}

long hook_raw_size()
{
    return 0x644C40; // 0x644C00 + 0x40 (found on aA08x_crw)
}

/**
 * OSD screen
 */
void *vid_get_bitmap_fb()
{
    return (void*)0x103C79A0; // (found on aBmpddev_c)
}

/**
 * IMG viewport in 'rec' mode
 */
void *vid_get_viewport_fb()
{
	return (void*)0x105F1370; // found at aImgddev_c after loc_FF9231C0
}

/**
 * IMG viewport in 'play' mode
 */
void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x7BAD8); // found on aImageplayer_c
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

void *vid_get_viewport_live_fb()
{
    return (void*)0x0;
}

char *camera_jpeg_count_str()
{
    return (char*)0x9B58;
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
