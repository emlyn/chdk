#include "platform.h"
#include "stdlib.h"
#include "lolevel.h"


void *hook_raw_fptr()
{
    return (void*)0;
}

void *hook_raw_ret_addr()
{
    return (void*)0;
}

char *hook_raw_image_addr()
{
 return (char*) (*(int*)(0x5854+0x18) ? 0x11F8F740 : 0x108297C0);
}

long hook_raw_size()
{
    return 0xEE9710;//OK
}

void *vid_get_viewport_live_fb()
{
    return (void*)0;
//    void **fb=(void **)0x21D0;
//    unsigned char buff = *((unsigned char*)0x2084);
//    if (buff == 0) {
//        buff = 2;
//    }
//    else {
//        buff--;
//    }
//    return fb[buff];
}

void *vid_get_bitmap_fb()       
{
    return (void*)0x10361000;//OK	
	//THUM VRAM BUFF=0x103F2920 ;  IMG VRAM BUFF=0x108876B0 ; JPEG BUFF=0x11713000 ; MJVRAM Address=0x107F7040 ; MJVRAM Size=0x180000
	//VRAM Address=0x1067B540 ; VRAM Size=0x7E900
}

void *vid_get_viewport_fb()
{
     return (void*)0x1067B540;//OK //0x1065A560;
					
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x55A0); //OK // 0x5558 + 0x48
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

void JogDial_CW(void){
  (*(short*)(0x263C+2))--;
//  *(int*)(0x263C+0x18)=0x0;
  *(int*)(0x263C+0x14)=0x32;
  _GiveSemaphore(*(int*)(0x263C+0x0C));
}

void JogDial_CCW(void){
  (*(short*)(0x263C+2))++;
//  *(int*)(0x263C+0x18)=0x0;
  *(int*)(0x263C+0x14)=0x32;
  _GiveSemaphore(*(int*)(0x263C+0x0C));
}

//from sx100is
//void JogDial_CW(void){
//  (*(short*)(0x2590+2))--;
//  *(int*)(0x2590+0x18)=0x32;
//  _GiveSemaphore(*(int*)(0x2590+0x10));
//}
//
//void JogDial_CCW(void){
//  (*(short*)(0x2590+2))++;
//  *(int*)(0x2590+0x18)=0x32;
//  _GiveSemaphore(*(int*)(0x2590+0x10));
//}
//from sx100is

int review_fullscreen_mode(){
 char r;
 get_parameter_data(53, &r, 1);
 return  r==0;
}
//from g7

char *camera_jpeg_count_str()
{
    return (char*)0x60354;//OK
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
