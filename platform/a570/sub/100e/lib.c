#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x0; 
}

void *hook_raw_ret_addr()
{
    return (void*)0x0; 
}

char *hook_raw_image_addr()
{
    return (char*)0x10E6C640; 
}

long hook_raw_size()
{
    return 0x8CAE10; 
}

void *vid_get_viewport_live_fb()
{
//    return (void*)0x0; 
    void **fb=(void **)0x65CC;
    unsigned char buff = *((unsigned char*)0x65DC);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;  
}

void *vid_get_viewport_fb()
{
    return (void*)0x10657A00;
}

void *vid_get_viewport_fb_d()
{
  #define BASE_FB_D (0x7C090)
  return (void*) (*(int*)(BASE_FB_D+0x10) ? *(int*)(BASE_FB_D+0x0) : *(int*)(BASE_FB_D+0x14));
//    return (void*)(*(int*)0x7C090); 
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
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}
char *camera_jpeg_count_str()
{
    return (char*)0x10F28;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

