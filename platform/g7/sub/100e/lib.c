#include "platform.h"
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
 return (char*) (*(int*)0x6E9C ? 0x11BE3A80 : 0x1082C520);
}

long hook_raw_size()
{
    return 0xC58758;         
}

void *vid_get_viewport_live_fb()
{
    return (void*)0;
}

void *vid_get_bitmap_fb()
{
    return (void*)(0x10361000);  
}

void *vid_get_viewport_fb()
{
    return (void*)0x1065B130; //0x105C3330;
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x74FB4);
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
  (*(short*)0x106EE)++;
  *(int*)0x106F4=0x32;
  _GiveSemaphore(*(int*)0x106E4);
}

void JogDial_CCW(void){
  (*(short*)0x106EE)--;
  *(int*)0x106F4=0x32;
  _GiveSemaphore(*(int*)0x106E4);
}

int review_fullscreen_mode(){
 char r;
 get_parameter_data(53, &r, 1);
 return  r==0;
}
char *camera_jpeg_count_str()
{
    return (char*)0x82F88;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
