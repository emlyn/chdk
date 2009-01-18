#include "platform.h"
#include "keyboard.h"
#include "stdlib.h"

/*
void *hook_raw_fptr()
{
    return (void*)0x34C50;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCC7FF0;
}
*/

char *hook_raw_image_addr()
{
    return (char*)0x105B8AC0; // OK (find on ".crw")
    
}

long hook_raw_size()
{
    return 0x75A8F0; // OK (find on ".crw")
}

/*
void *vid_get_viewport_live_fb()
{
    return (void*)0;
}
*/

void *vid_get_bitmap_fb()
{
    return (void*)0x103C79A0; // OK (find in _CreatePhysicalVram)
}

void *vid_get_viewport_fb()
{
    return (void*)0x105F17A0; // OK (find on "VRAM Address  : %p")
}

void *vid_get_viewport_fb_d()
{
// from ewavr 
	return (void*)(*(int*)0x63AD0); // found in sub_FFD25770
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

int review_fullscreen_mode(){ //from 710 added
 char r;
 get_parameter_data(53, &r, 1);
 return  r==0;
}

int postreview_fullscreen_mode(){ //from 710 added
 char r;
 get_parameter_data(54, &r, 1);
 return  r==0;
}



static int file_size_table[3][5]={{3110,2562,1666,1057,288},
				  {1954,1441, 928, 608,176},
				  {960,  736, 480, 320,112}};  // in KB   // from 710 added
				  	
				  
long raw_shoot_avail(){ // from 710 added
 long jpegs,size,quality;
 jpegs=atoi((char*)0x6E8D0); // orig.0x7BD98 find -> a9999
 get_property_case(23, (void *)&quality, 4);
 get_property_case(24, (void *)&size, 4);
 if ((size>4) || (quality>2)) return 0; 
 return (file_size_table[quality][size]*jpegs)/(file_size_table[quality][size]+(hook_raw_size()>>10));
}


int mf_slider_active() // from 710 added
{
 return *(long*)0x6C8B0==0x100; // orig.0x798F0  found in "ControlSwitcher.c"
}

void *vid_get_viewport_live_fb() // from 710 added
{
   // return (void*)0x10670ee0;
    void **fb=(void **)0x5288;
    unsigned char buff = *((unsigned char*)0x5298);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}


char *camera_jpeg_count_str()
{
    return (char*)0x6E8D0 ; // from 700 added orig. 0x78688
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

