#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0;
}

void *hook_raw_ret_addr()
{
    return (void*)0x0; 
}

char *hook_raw_image_addr()
{
    return (char*)0x115FC320; 
}                   

long hook_raw_size()
{
 //   return 0x8D0A68; 
      return 0x8CAE10;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000; // found at 0xFFA3869C
}

void *vid_get_viewport_fb()  // found at 0xFFA3706C
{
	return (void*)0x10D295E0; 
}

void *vid_get_viewport_fb_d() // found at 0xFFAD08E8
{
    return (void*)(*(int*)0x8D628); 
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

void *vid_get_viewport_live_fb()
{
    return (void*)0x0;
}

char *camera_jpeg_count_str()
{
    return (char*)0x12988;
}
 
long vid_get_bitmap_buffer_width() { return 480; }

long vid_get_bitmap_buffer_height() { return 271; }

void _EnterToCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
void _ExitFromCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
