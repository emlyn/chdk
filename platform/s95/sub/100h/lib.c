#include "platform.h"
#include "stdlib.h"
#include "lolevel.h"

/*
sensor size from code at FFB64E84 = (3744*2784)*(12/8) = 0xee9200 = 15634944

@FFB64AAC = 0xea0 = 3744	// raw sensor size
@FFB64AB4 = 0xae0 = 2784
@FFB64ABC = 0xe40 = 3648	// cropped size ??
@FFB64AC4 = 0xab0 = 2736
*/


char *hook_raw_image_addr()
{
	if (*((int*)0x2ECC) != 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x41269150;
}


long hook_raw_size()
{
	return 0xEE9200;							// @FFB64E84 - ok
}


void *vid_get_viewport_live_fb()
{
	    return (void*) 0;

	// TODO - implement for s95 ?

#if 0
	void **fb=(void **)0x94E18;
	unsigned char buff = *((unsigned char*)0x9114+6);
    if (buff == 0) buff = 2;  else buff--;
    return fb[buff];
#endif
}


void *vid_get_bitmap_fb()
{
	return (void*) 0x40471000;					// @FF85E704 - ok
}


void *vid_get_viewport_fb()
{
	return (void*) 0x40587700;					// @FFB619C4 - ok
}


// Histo etc. when in play mode maybe ?
void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*) (0x2c20+0x58));		// @FF87822C, FF878264 - ok
}


void JogDial_CW(void){
	_PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}


void JogDial_CCW(void){
	_PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}


char *camera_jpeg_count_str()
{
    return (char*) 0xBBC9C;						// @FFA3ACC4 - ok
}


long vid_get_bitmap_screen_width()
{
    return 320;
}


long vid_get_bitmap_screen_height()
{
	return 240;
}


int vid_get_viewport_width()
{
	return 720;
}


long vid_get_viewport_height()
{
   return 240;

}


// used when drawing to lcd
long vid_get_bitmap_buffer_width()
{
	return 960;
}


long vid_get_bitmap_buffer_height()
{
	return 270;
}

