#include "platform.h"

// RAM addresses

char *hook_raw_image_addr() {
    return (char*)0x41db3b80;           // first RAW buffer address, search String "CRAW BUFF"
    // table at 0xffb40208, no second buffer
}

// search String "CRAW BUFF SIZE"
long hook_raw_size() {
    return 0x14d2400;
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

/*
from http://chdk.setepontos.com/index.php?topic=5045.msg54035#msg54035
this must be completely opaque to an uninitiated scholar...

First, a quick suggestion: for a start, return 0 in *vid_get_viewport_live_fb(),
and return the correct viewport base address in *vid_get_viewport_fb(),
which is easy to find from the code that references the "VRAM Address: %p" string.

Now in more detail. Actually, Canon uses (or used to anyway) three buffers,
one (first) of them located at the base address, and switches between them about 30 times a second,
if I remember correctly. We only need to know which one of them is most recently updated,
if we want to speed up motion detection by about 30ms.
There is a table somewhere in RAM with the addresses of the buffers, and a variable with the index 0,1,2 into this table.
It's these two locations that you may want to find, but I'm afraid there's no generic recipe...
They are usually referenced in the code just before, or around "LiveView.c".
Here're sample code snippets from the Ixus950 and A720 (sorry, don't have disasms of later cameras):

FF9C9E84                 LDR     R3, =0x8C74
FF9C9E88                 LDR     R2, =0x8C58
FF9C9E8C                 LDRB    R0, [R3]
FF9C9E90                 LDR     R1, [R2,R0,LSL#2]

FFC2936C                 LDR     R4, =0x2084
...
FFC293B8                 LDRB    R2, [R4]
FFC293BC                 LDR     R0, =0x21D0
FFC293C0                 LDR     R2, [R0,R2,LSL#2]

You can verify them in memory browser: the index variable should circle through 0,1,2,
and the table should contain three addresses, starting with the VRAM base address.
*/
void *vid_get_viewport_live_fb() {
    return (void*)0;
    // sub_ff84e0e0??? (cf sd990 FF839850)
    void **fb=(void **)0x; // ???
    unsigned char buff = *((unsigned char*)0x2040);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

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

// if buffer width was to small, Logo was shown as distorted "row" on Display
long vid_get_bitmap_buffer_width() { return 960; }
long vid_get_bitmap_buffer_height() { return 270; }

long vid_get_bitmap_screen_width() { return 480; }
long vid_get_bitmap_screen_height() { return 240; }

// buffer containing live view (when shutter half pressed)
// check by looking at edge overlay
int vid_get_viewport_width() { return 360; }
long vid_get_viewport_height() { return 270; }
/*
int vid_get_viewport_width() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?480:360;
}
*/


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
