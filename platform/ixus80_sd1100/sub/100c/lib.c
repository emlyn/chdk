#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0;
}

void *hook_raw_ret_addr()
{
    return (void*)0;
}

/* found at ff9c7368 near "A/%08x.CRW"
 * ff9c7368: 	e59f51c8 	ldr	r5, [pc, #456]	; ff9c7538: (10f3f400)
 */
char *hook_raw_image_addr()
{
    return (char*)0x10f3f400;
}

long hook_raw_size()
{
    return 0x9dcce0;
}

void *vid_get_viewport_live_fb() // live picture buffer (shoot not pressed)
{
    // 00007040 found at ff8c4c70 "LiveImage.c"
    // 00006ebc found at ff8c4a6c
    void **fb=(void **)0x7040;
    unsigned char buff = *((unsigned char*)0x6ebc);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}
/* found at ff9f32ec
 */
void *vid_get_bitmap_fb() // OSD buffer
{
    return (void*)0x10361000;
}

/* found:
 * ffa7ff48: 	1065ade0 	rsbne	sl, r5, r0, ror #27
 * "SumY %ld Size %ld":
 *
 * found at ffa7fd18
 * "VRAM Address  : %p"
 *
 // return (void*)0x1065ade0;
 */
void *vid_get_viewport_fb() // live picture buffer (shoot half-pressed)
{
    return ((void **)0x7040)[*((unsigned char*)0x6ebc)];
}

/*
 * found with this memory browser hack:
    #include "conf.h"
    extern Conf conf;
    return (void*)(*(int*)conf.mem_view_addr_init);
    use zebra mode in review mode

    ... in ROM possibly here:
    ff85442c: 	e59f0058 	ldr	r0, [pc, #88]	; ff85448c: (00018a5c)
    ff854430: 	e590100c 	ldr	r1, [r0, #12]
    ...
    ff854470: 	151f0ed8 	ldrne	r0, [pc, #-3800]	; ff8535a0: (ff852688)  **"ImagePlayer.c"
*/

void *vid_get_viewport_fb_d() // picture buffer (play mode)
{
    return (void*)(*(int*)0x18a68);
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
    return (char*)0x4c2c4;
}

long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }
