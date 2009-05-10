#include "platform.h"

char *hook_raw_image_addr()
{
  // _sub_FF863178__SsImgProcBuf.c__0: STR after label
  // 0xFF86317C -> 0x5324
  // 0xFF8631A8 -> 0x18
  //
  // via aCrawBufP -> 0x412007FC (as with ixus980)
  //
  // just before aEscapeOriginal (" Escape Original Raw to CRAW2 BUFFER. ")
  // 0xFF84D020: 0x429AAA2C
	return (char*) (*(int*)(0x5324+0x18) ? 0x429AAA2C : 0x412007FC);
}

long hook_raw_size()
{
  // just before aEscapeOriginal (" Escape Original Raw to CRAW2 BUFFER. ")
  // 0xFF84D024: 0xEC04F0
	return 0xEC04F0;
}

void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x227C;
    unsigned char buff = *((unsigned char*)0x20DC);
    if (buff == 0) buff = 2;  else buff--;    
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
  // 0xFF841DE0 (below DispCon_ShowBitmapColorBar
	return (void*)0x403B1000; 
}

void *vid_get_viewport_fb()
{
  // In data block with aLiveimage_c
  // look for use of 0x7E9
  // instruction above contains address
  // XXX guessed
	return (void*)0x40A2F2D0;
}

void *vid_get_viewport_fb_d()
{
  // in _sub_FF856D78__ImagePlayer.c__0
  // 3rd instruction -> 0x501C
  // 3nd use -> 0x58
	return (void*)(*(int*)(0x501C+0x58)); 
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
	return 240;
}

char *camera_jpeg_count_str()
{
  // 0xFF9AD200 (directly above use of "9999")
	return (char*)0x4A980;
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
