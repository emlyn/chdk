#include "platform.h"
#include "keyboard.h"

void *hook_raw_fptr()
{
    return (void*)0x53B98; // find on "taskcreate_ImageSensorTask" 
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF9AB668; // BL      nullsub_100
}

char *hook_raw_image_addr()
{
    return (char*)0x10E706A0; //(0x10E70000 + 0x6A0) (find on "A/%08x.CRW")
}

long hook_raw_size()
{
    return 0x8CAE10; //7mpx (0x8C0000 + 0xAE00 + 0x10)(find on "A/%08x.CRW")
}

void *vid_get_viewport_live_fb()
{
//    return (void*)0; // 0x1065BA50 + 0x7E900 (find on "VRAM Address  : %p")
    void **fb=(void **)0x6F8C;
    unsigned char buff = *((unsigned char*)0x6F9C);
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
    return (void*)0x10361000; //(0x10360000 + 0x1000) (find on "BmpDDev.c")
}

void *vid_get_viewport_fb()
{
    return (void*)(0x1065BA50); // 0x107F5B60 (find on "A/%08x.CRW") "0x1065BA50 (find on "VRAM Address  : %p")
}

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x94408); // 0x94550 (find on "TerminateLowLevelConsole_3" )0x94408 (find on "ImagePlayer.c") 0x4D398 (find on "WBTblAdj.c")
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
    return (char*)0x12298;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

