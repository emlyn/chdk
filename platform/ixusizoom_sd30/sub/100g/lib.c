#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x3F898; //OK  ROM:FF8C7794
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF8D2C94; //OK	=aTgtool_getregi
}

char *hook_raw_image_addr()
{
    return (char*)0x10584DF4; //OK	=aA08x_crw
}

long hook_raw_size()
{
    return 0x658560; //OK	=aA08x_crw
}

// buffer of live picture when shoot button is not pressed
void *vid_get_viewport_live_fb()
{
	return (void*)0;	//????????????????????????????
}

/**
 * OSD screen
  */
void *vid_get_bitmap_fb()
{
    return (void*) 0x103C79A0; //OK		=aA08x_dat
}

/**
 * IMG viewport in 'rec' mode
 */
// buffer of live picture when shoot button is (half-)pressed.
void *vid_get_viewport_fb()
{
    return (void*)0x106027C8;	//OK	loc_FF921AD0
}

/**
 * IMG viewport in 'play' mode
 */
// buffer of picture in play mode
void *vid_get_viewport_fb_d()
{
	return (void*)0x7B6A8; 	//OK	sub_FF9243CC
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
    return (char*)0x88860; //OK
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }