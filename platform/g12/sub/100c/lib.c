#include "platform.h"

/*
sensor size from code at sub_FFB7861C = (3744*2784)*(12/8) = 0xEE9200 = 15634944

@FFB78650 = 0xea0 = 3744	// raw sensor size
@FFB78658 = 0xae0 = 2784
@FFB78660 = 0xe40 = 3648	// cropped size ??
@FFB78668 = 0xab0 = 2736
*/

char *hook_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FFBBAD50, ref at FF8843F4
	// used in _sub_FF8841BC__SsImgProcBuf.c__0 
	// checks [0x2E88 + 0xc] --> defines which buffer is active

	if (*((int*)0x2E94) != 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x41269150;	// found at (0xFFB789C8) [search CRAW BUF]
}

#if DNG_DOUBLE_BUF
char *hook_alt_raw_image_addr()
{
	// Appears to be two raw buffers (this returns inactive buffer)
	// Addresses below found in table at FFBBAD50, ref at FF8843F4
	// used in _sub_FF8841BC__SsImgProcBuf.c__0 
	// checks [0x2E88 + 0xc] --> defines which buffer is active

	if (*((int*)0x2E94) == 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x41269150;	// found at (0xFFB789C8) [search CRAW BUF]
}
#endif    

long hook_raw_size()
{
	return 0xEE9200; // search CRAW BUF SIZE
}

// TODO - ??? Is this needed ???
void *vid_get_viewport_live_fb()
{
    return 0x0;
}

void *vid_get_bitmap_fb()
{
	return (void*)0x40471000; // DispCon_ShowBitmapColorBar 
}

void *vid_get_viewport_fb()
{
    return (void *)0x40587700; // search on VRAM Address (D10)
//	return (void*)(*((int*)(0x20AC+0x74)));	// sub_FF854368
}

// TODO - check that this works
void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x2C10+0x58)); // @FF8781AC & FF8781E4 (comp S95)
}

long vid_get_bitmap_screen_width() { return 320; }
long vid_get_bitmap_screen_height() { return 240; }

int vid_get_viewport_width()
{
    return 360;	// G12 - buffer is twice as wide as viewport
}

#if defined(CAM_VIEWPORT_BUFFER_WIDTH_FIX)
int vid_get_viewport_buffer_width()
{
    return 720;	// G12 - buffer is twice as wide as viewport
}
#endif

long vid_get_viewport_height() { return 240; }

// TODO - check that this works
char *camera_jpeg_count_str()
{
	return (char*)0xBB618; // loc_FFA435FC (search for "9999", passed to sprintf)
}

long vid_get_bitmap_buffer_width() { return 960; }

long vid_get_bitmap_buffer_height() { return 270; }
