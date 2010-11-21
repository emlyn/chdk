#include "platform.h"

char *hook_raw_image_addr()
{
    return (char*)0x41643DEC; // seach on CRAW BUF
// if multi buffer,
// (0x2AEC + 0x8) ??? sub_FF86274C__SsImgProcBuf_c__0 and table FFAD6A24
}

long hook_raw_size()
{
    return 0x11E4EE0; // CRAW BUF SIZE 4104*3048, like g9, ixus960
}

void *vid_get_viewport_live_fb()
{
	// from sub_FF837020 (similar to sd990 sub_FF839850), via sub_FF8EC2DC ref to table at FFAE28FC
    void **fb=(void **)0x210C;
    unsigned char buff = *((unsigned char*)0x1F74);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
	// d10 adds this extra value.  Didn't ever see the value change from zero, may be wrong
    return fb[buff] + *(int *)(0x1F74 + 0xd4); 
}

void *vid_get_bitmap_fb()       
{
    return (void*)0x403F1000; //  DispCon_ShowBitmapColorBar
}

void *vid_get_viewport_fb()
{
    return (void *)0x40A05158; // search on VRAM Address
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x2884 + 0x54));  // sub_FF8584AC, similar callers to sd990, 3rd, 4th functions following "HFILYUV"
}


long vid_get_bitmap_screen_width()
{
//    return 720;
    return 360; // 720 is the real width but we lie for aspect correction ...
}

long vid_get_bitmap_screen_height()
{
    return 240;
}

int vid_get_viewport_width()
{
	return 360;
}

long vid_get_viewport_height()
{
    return 240;
}

char *camera_jpeg_count_str()
{
    return (char *)0x525E4; // search on "9999" done
}

long vid_get_bitmap_buffer_width() { return 720; }
long vid_get_bitmap_buffer_height() { return 240; }



