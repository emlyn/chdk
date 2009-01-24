#include "platform.h"

int recreview_hold = 0;
char canon_shoot_menu_active = 0;

// comments before addresses are hints from sd450 port

void *hook_raw_fptr()
{
    return (void*)0;  // TODO, was 0x36A90
}

void *hook_raw_ret_addr()
{
    // BL      nullsub_100
    return (void*)0xFF9B28A8;   // nullsub_100
}

char *hook_raw_image_addr()
{
    // ( found on aA08x_crw)
    return (char*)0x105B8AC0;   // same as 100d, found at 0xFF8CA0AC
}

long hook_raw_size()
{
    // 0x644C00 + 0x40 (found on aA08x_crw)
    return 0x75A8F0;    // same as 100d, found at 0xFF8CA0B4
}

/**
 * OSD screen
 */
void *vid_get_bitmap_fb()
{
    // (found on aBmpddev_c)
    return (void*)0x103C79A0;   // same as 100d, found at 0xFF935280
}

/**
 * TODO: ??????
 */
void *vid_get_viewport_live_fb()
{
    return (void*)0;    // not req?
}

/**
 * IMG viewport in 'rec' mode
 */
void *vid_get_viewport_fb()
{
    // found at aImgddev_c, 0xFF9341E0 - 3 potential values for R3, perhaps someone
    // better at assembly can work this one out (my skills are rusty :/)
    return (void*)0x105599A0;   // 0x105599A0 or 0x104AF0cA0, 0x105F17A0?
}

/**
 * IMG viewport in 'play' mode
 */
void *vid_get_viewport_fb_d()
{
    // check around aImageplayer_c, 0xFF937AC8
    return (void*)0x6DB9C;   // TODO, no idea about this one at all
                             // a literal stab in the dark
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
    return (char*)0x10B80;      // TODO, was marked for fixing in sd630??
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

void _EnterToCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
void _ExitFromCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
