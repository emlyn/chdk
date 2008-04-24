#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x440C0; 
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFD4CBD8; 
}

char *hook_raw_image_addr()
{
    return (char*)(0x10800000+0x41000+0x260);      
}

long hook_raw_size()
{
    return 0x63FF60;       // "CRAW BUF","WBIntegPrm.c" -  1/3" 5 MPix -  (2664*1968*10/8=0x63FF60)  
}

void *vid_get_viewport_live_fb()
{
    return (void*)0;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;  //(0x10360000 + 0x1000)
}

void *vid_get_viewport_fb()
{
    return (void*)0x10E81260; //0x10558D30
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x6D048);
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
    return ((mode_get()&MODE_MASK) == MODE_PLAY) ? 240 : 230;
}

char *camera_jpeg_count_str()
{
    return (char*)0x10F70;
} 

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
