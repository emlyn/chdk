#include "platform.h"

void *hook_raw_fptr()
{
    //return (void*)0x2F490;
	return (void*)0x2EC10; // find on "taskcreate_ImageSensorTask" OK!
}

void *hook_raw_ret_addr()
{
    //return (void*)0xFF8D8BDC;
	return (void*)0xFF8E0EEC; // From inside the TgTool_Delete OK!
}

char *hook_raw_image_addr()
{
    //return (char*)(0x10400000+0x160000+0x3A80); // Loc FF8B6AB0
	return (char*)0x10595D54; // function below aWaitgetaeinteg OK!
}

long hook_raw_size()
{
    return 0x644C40; // 0x644C00 + 0x40 OK!
}

// buffer of live picture when shoot button is not pressed
void *vid_get_viewport_live_fb()
{
    return (void*)0x0;
}

/**
 * OSD screen
  */
void *vid_get_bitmap_fb()
{
    return (void*)0x103CEB20; // (found on aBmpddev_c) OK!
}

/**
 * IMG viewport in 'rec' mode
 */
// buffer of live picture when shoot button is (half-)pressed.
void *vid_get_viewport_fb()
{
//    return (void*)0x104B6C20;
//    return (void*)0x10559670;
    return (void*)0x105F84F0; // Next function after CreateImagePhysicalVramForStitch OK!
}

/**
 * IMG viewport in 'play' mode
 */
// buffer of picture in play mode
void *vid_get_viewport_fb_d()
{
//    return (void*)(*(int*)0x5BAEC);
 return (void*)(*(int*)0x6EAD0); // found on aImageplayer_c OK!
 //return (void*)(*(int*)0x104B6C20);
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
    return (char*)0x75EC0; // OK!
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
