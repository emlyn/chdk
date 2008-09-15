#include "platform.h"
#include "keyboard.h"

/***********
for the next two functions, see in loc_FF9B84F0:
FF9B8510  LDR     R3, =0x55EA4
FF9B8514  LDR     R2, =0x55EA0    ; <- *raw_fptr
FF9B8518  LDR     R0, [R3]
FF9B851C  MOV     LR, PC
FF9B8520  LDR     PC, [R2]
FF9B8524  BL      nullsub_106     ; <- raw_ret_addr should point here
FF9B8528  LDR     R3, =0x6F14
***********/

void *hook_raw_fptr()
{
    return (void*)0x55EA0;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF9B8524;
}

/***********
for the next two functions, see after "A/%08x.CRW" at FF9A7A60:
  MOVL    R7, 0x10F3C000
  MOV     R3, #0x9D0000
  ADD     R7, R7, #0x1A00
  ADD     R3, R3, #0xCC00
  ...
  ADD     R3, R3, #0xE0
***********/

char *hook_raw_image_addr()
{
    return (char*)(0x10F3DA00);	// 0x10F3C000 + 0x1A00
}

long hook_raw_size()
{
    return 0x9DCCE0;		// 0x9D0000 + 0xCC00 + 0xE0
}

void *vid_get_viewport_live_fb() // live picture buffer (shoot not pressed)
{
//	return ((void **)0x8C58)[*((unsigned char*)0x8C74)];
    void **fb=(void **)0x8C58;
    unsigned char buff = *((unsigned char*)0x8C74);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

void *vid_get_bitmap_fb()	// OSD buffer
{
    return (void*)0x10361000;	// 0x10360000 + 0x1000, see after "BmpDDev.c" in loc_FFA2DDEC
}

void *vid_get_viewport_fb()	// live picture buffer (shoot half-pressed)
{
	return ((void **)0x8C58)[*((unsigned char*)0x8C74)];
}

void *vid_get_viewport_fb_d()	// picture buffer (play mode)
{
    return (void*)(*(int*)0x812C8); // see before "ImagePlayer.c" in loc_FFAC3E90
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
    return (char*)0x143D0;
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

void _EnterToCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
void _ExitFromCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
