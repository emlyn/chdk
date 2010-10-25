#include "platform.h"

// RAM addresses

// search String "CRAW BUFF"
char *hook_raw_image_addr() {
    return (char*)0x41db3b80;           // first RAW buffer address
}


// ffb03ef8: 0x41db3b80 First RAW address
// ffb401ec Table contains first RAW address
// function ff87bc38: references the table with first RAW address (SsImgProcBuf.c)
// ff87bc3c: 0x2bec
// ff87bc68: 0xC
//char *hook_raw_image_addr() {
//    return (char*) (*(int*)(0x2bec + 0xC)? 0x???????? : 0x41db3b80);
//}

// search String "CRAW BUFF SIZE"
long hook_raw_size() {
    return 0x14d2400;
}

void *vid_get_viewport_live_fb() {
    return (void*)0;
}

/*
// ?!?
// Live picture buffer (shoot not pressed)
// ROM:FF84FB50 ?!?
void *vid_get_viewport_live_fb() {
    //void **fb=(void **)0x21E8;      // ?!?
    //void **fb=(void **)0x21EC;      // ?!?
    void **fb=(void **)0x21F8;      // ROM:FF85078C ?!? more or less guesswork
    unsigned char buff = *((unsigned char*)0x204C);   // ROM:FF850904
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}
*/

// OSD buffer
// search dispcon* functions and BmpDDev.c
// ff90ce04: 	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
// ff90ce08: 	e51f8040 	ldr	r8, [pc, #-64]	; ff90cdd0: (0000556c) 
// ff90ce0c: 	e1a04000 	mov	r4, r0
// ff90ce10: 	e5980010 	ldr	r0, [r8, #16]
// ff90ce14: 	e1a05001 	mov	r5, r1
// ff90ce18: 	e3500001 	cmp	r0, #1	; 0x1
// ff90ce1c: 	059f123c 	ldreq	r1, [pc, #572]	; ff90d060: (0000013f) 
// ff90ce20: 	024f004c 	subeq	r0, pc, #76	; ff90cddc: (44706d42)  *"BmpDDev.c"
// ff90ce24: 	e1a07003 	mov	r7, r3
// ff90ce28: 	e1a06002 	mov	r6, r2
// ff90ce2c: 	0bfc4738 	bleq	loc_ff81eb14
// ff90ce30: 	e3540000 	cmp	r4, #0	; 0x0
// ff90ce34: 	13550000 	cmpne	r5, #0	; 0x0
// ff90ce38: 	13560000 	cmpne	r6, #0	; 0x0
// ff90ce3c: 	13570000 	cmpne	r7, #0	; 0x0
// ff90ce40: 	059f121c 	ldreq	r1, [pc, #540]	; ff90d064: (00000142) 
// ff90ce44: 	024f0070 	subeq	r0, pc, #112	; ff90cddc: (44706d42)  *"BmpDDev.c"
// ff90ce48: 	0bfc4731 	bleq	loc_ff81eb14
// ff90ce4c: 	e59f1214 	ldr	r1, [pc, #532]	; ff90d068: (0000010e) 
// ff90ce50: 	e3a00d0f 	mov	r0, #960	; 0x3c0
// ff90ce54: 	e5840000 	str	r0, [r4]
// ff90ce58: 	e5851000 	str	r1, [r5]
// ff90ce5c: 	e5860000 	str	r0, [r6]
// ff90ce60: 	e59f0204 	ldr	r0, [pc, #516]	; ff90d06c: (40431000) ; <----
// ff90ce64: 	e5870000 	str	r0, [r7]
// ff90ce68: 	e3a00001 	mov	r0, #1	; 0x1
// ff90ce6c: 	e5880010 	str	r0, [r8, #16]
// ff90ce70: 	e3a00000 	mov	r0, #0	; 0x0
// ff90ce74: 	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
void *vid_get_bitmap_fb() {
    return (void*)0x40431000;
}

// Live picture buffer (shoot half-pressed)
// search for String "VRAM Address" (like SX10)
// or search for String "MaxY %ld MinY %ld" and look below
void *vid_get_viewport_fb() {
    return (void*)0x40547700;
}

// ?!?
// possible future use
void *vid_get_viewport_fb_d() {
    return (void*)(*(int*)0x29f4);         // ff871dec: 0x29a0 + 0x54
}

// vid_* stuff is related to BmpDDev() stuff (ROM:FF919A78 and other) and LiveImage.c

// ROM:FF9013D8 0x2D0 = 720 ?!?
// SD990 ROM:FF83CFC8 ?!?
//long vid_get_bitmap_screen_width() { return 320; }
//long vid_get_bitmap_screen_width() { return 360; }
//long vid_get_bitmap_screen_width() { return 480; }
long vid_get_bitmap_screen_width() { return 480; }
//long vid_get_bitmap_screen_width() { return 720; }
//long vid_get_bitmap_screen_width() { return 960; }

//long vid_get_bitmap_screen_height() { return 240; }
//long vid_get_bitmap_screen_height() { return 270; }
long vid_get_bitmap_screen_height() { return 240; }

//int vid_get_viewport_width() { return 360; }    // viewport is still 360, even though live view is 720 (from SD990)
int vid_get_viewport_width() { return 480; }

/*
int vid_get_viewport_width() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?480:360;
}
*/

//long vid_get_viewport_height() { return 240; }
long vid_get_viewport_height() { return 270; }

// ?!?
// search for String "9999"
// ff9eacb0: 	e250cc27 	subs	ip, r0, #9984	; 0x2700
// ff9eacb4: 	225cc00f 	subscs	ip, ip, #15	; 0xf
// ff9eacb8: 	3a000003 	bcc	loc_ff9eaccc
// ff9eacbc: 	e59f013c 	ldr	r0, [pc, #316]	; ff9eae00: (0009eb4c) 
// ff9eacc0: 	e28f1e13 	add	r1, pc, #304	; ff9eadf8: (39393939)  *"9999"
// ff9eacc4: 	ebf8d631 	bl	loc_ff820590
// ff9eacc8: 	ea000003 	b	loc_ff9eacdc
char *camera_jpeg_count_str() {
    return (char*)0x9eb4c;
}

// if buffer width was to small, Logo was shown as distorted "row" on Display
//long vid_get_bitmap_buffer_width() { return 360; }
//long vid_get_bitmap_buffer_width() { return 720; }
long vid_get_bitmap_buffer_width() { return 960; }

//long vid_get_bitmap_buffer_height() { return 240; }
//long vid_get_bitmap_buffer_height() { return 270; }
long vid_get_bitmap_buffer_height() { return 270; }
