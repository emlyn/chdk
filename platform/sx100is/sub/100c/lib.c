#include "platform.h"

//NOTE These functions not used

/*void *hook_raw_fptr()
{
	return (void*)0;
}*/

/*void *hook_raw_ret_addr()
{
	return (void*)0;
}*/

char *hook_raw_image_addr()
{
//	Found at ROM:FFDC5D60
//	ROM:FFDC5D60                 LDR     R6, =0x10F6C860
//	...
//	ROM:FFDC5DB0                 MOV     R1, R6
//	ROM:FFDC5DB4                 ADR     R0, aCrawBuffP  ; "CRAW BUFF       %p"


    return (char*)0x10F6C860;		// Same as A720
}

long hook_raw_size()
{
//	Found at ROM:FFDC5DBC
//	ROM:FFDC5DBC                 LDR     R1, =0x9DCCE0
//	ROM:FFDC5DC0                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
//	ROM:FFDC5DC4                 BL      sub_FFDC7578

	return 0x9DCCE0;
}

void *vid_get_viewport_live_fb()
{
	return (void*)0;//0x10670ee0;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;		// Same as A720
}

void *vid_get_viewport_fb()
{
    return (void*)0x1065A4D0; // 0x107D5FD0
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x5420);   // 0x53D8 + 0x48
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
	// Fount at ROM:FFD6D358
 return (void*)0x59A1C;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
