#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x2F7E8; //0x2F490;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF8D0824; //OK
}

char *hook_raw_image_addr()
{
return (char*)0x10A795A8; //OK: 0x10A795A8
}

long hook_raw_size()
{
    return 0x50D750; //OK
}

// buffer of live picture when shoot button is not pressed
void *vid_get_viewport_live_fb()
{
return (void*)0x10B02560;
}

/**
 * OSD screen
  */
void *vid_get_bitmap_fb()
{
    return (void*) 0x108CEB20; //OK!!!
}

/**
 * IMG viewport in 'rec' mode
 */
// buffer of live picture when shoot button is (half-)pressed.
void *vid_get_viewport_fb()
{
    return (void*)0x10B02560; //OK!!!
}

/**
 * IMG viewport in 'play' mode
 */
// buffer of picture in play mode
void *vid_get_viewport_fb_d()
{
	//return (void*)0x10A6A760; //OK!
	return (void*)0x109CBD20; //OK as well ?!
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
    return (char*)0x75F30; //ok
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
