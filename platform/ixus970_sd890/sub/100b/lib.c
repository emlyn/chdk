#include "platform.h"

// obsolete
void *hook_raw_fptr() { return (void*)0; }
void *hook_raw_ret_addr() { return (void*)0; }

char *hook_raw_image_addr()
{
	// 0x54F4 + 0x18 @ FF85E534
	// @ FFAB1C48
	// @ FFAB1C54
	return (char*) (*(int*)(0x550C) ? 0x11B97B60 : 0x107D68C0);
}

long hook_raw_size()
{
	// (3720 x 2772 * 12bit) / 8bit
	// @ FFA8AD80
	return 0xEC04F0;
}

// Live picture buffer (shoot not pressed)
void *vid_get_viewport_live_fb()
{
	// @ FF8C5AB0
	void **fb=(void **)0x7420;
	unsigned char buff = *((unsigned char*)0x729C);
	if (buff == 0) {
		buff = 2;
	} else {
		buff--;
	}
	return fb[buff];
}

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	// @ FFA88AFC
	return (void*)0x1065ADC0;
}

// Picture buffer (play mode)
void *vid_get_viewport_fb_d()
{
	// 0x51FC + 0x4C @ FF853E50
	return (void*)(*(int*)0x5248);
}

// OSD buffer
void *vid_get_bitmap_fb()
{
	// @ FF8EA9F8
	return (void*)0x10361000;
}

// possible future use
/*
char *vid_get_bitmap_fb_d() 
{
	// 0xAEF0+0x4 @ FF9AE274
	int *p =(int *)(*(int*)(0xAEF4));
	return ((char *)(*(p+2)));
}
*/

char *camera_jpeg_count_str()
{
	// @ FF9A6FDC
	return (char*)0x4CA80;
}

long vid_get_bitmap_screen_width() { return 360; }

long vid_get_bitmap_screen_height() { return 240; }

long vid_get_viewport_height() { return 240; }

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
