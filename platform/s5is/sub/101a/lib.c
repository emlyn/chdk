#include "platform.h"

// Documentation stripped, please refer to the S5IS 1.01b lib.c if you
// need it, or wait until someone feels like updating the documentation for this
// particular model.

void *hook_raw_fptr()
{
	return (void*)0; // What does this do? Doesn't seem to be called
}

void *hook_raw_ret_addr()
{
	return (void*)0; // What does this do? Doesn't seem to be called
}

char *hook_raw_image_addr()
{
	return (char*)0x1163B8E0;
}

long hook_raw_size()
{
	return 0x9DCCE0;
}

void *vid_get_viewport_live_fb()
{
	return (void*)0x0;
}

void *vid_get_bitmap_fb()
{
	return (void*)0x10361000; 
}

void *vid_get_viewport_fb()
{
	return (void*)0x10D29360;
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)0x5724);  // 0x56D8 + 0x4C
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
	return 240;
}

char *camera_jpeg_count_str()
{
	return (char*)0x58304;
}

