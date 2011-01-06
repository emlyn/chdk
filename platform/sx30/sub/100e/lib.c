#include "platform.h"

/*
sensor size from code at sub_FFB59B8C = (4464*3276)*(12/8) = 0x14EB7E0 = 21936096

@FFB59BCC = 0xea0 = 4464	// raw sensor size
@FFB59BD4 = 0xae0 = 3276
@FFB59BDC = 0xe40 = 4320	// cropped size ??
@FFB59BE4 = 0xab0 = 3240
*/

char *hook_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FFB9922C, ref at FF88883C
	// used in _sub_FF888630__SsImgProcBuf.c__0 
	// checks [0x36a0 + 0xc] --> defines which buffer is active

	if (*((int*)0x36ac) != 0)
		return (char*) 0x443B4960;
	else
		return (char*) 0x4235F6B0;	// found at (0xFFB59F40) [search CRAW BUF]
}

#if DNG_SUPPORT
char *hook_alt_raw_image_addr()
{
	// Appears to be two raw buffers (this returns inactive buffer)
	// Addresses below found in table at FFB9922C, ref at FF88883C
	// used in _sub_FF888630__SsImgProcBuf.c__0 
	// checks [0x36a0 + 0xc] --> defines which buffer is active

	if (*((int*)0x36ac) == 0)
		return (char*) 0x443B4960;
	else
		return (char*) 0x4235F6B0;	// found at (0xFFB59F40) [search CRAW BUF]
}
#endif    

long hook_raw_size()
{
	return 0x14EB7E0; // search CRAW BUF SIZE
}


char *camera_jpeg_count_str()
{
	return (char*)0xCF2FC; // loc_FFA3BA74 (search "9999", passed to sprintf)
}


void *vid_get_bitmap_fb()
{
	return (void*)0x40471000; // sub_FF93062C 
}


void *vid_get_viewport_live_fb() // ???
{
    return 0x0;
}

void *vid_get_viewport_fb()
{
	return (void*)0x40587700; // sub_FF8E8C58
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x32B0+0x58)); // @FF878AB0 & FF878AE8 (comp to S95)
}
