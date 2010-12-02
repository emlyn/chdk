#include "stubs_asm.h"

// RAM addresses

DEF(physw_status, 0x32800)    // "GpioStatus  "

DEF(physw_run, 0x1c2c)    // ff8341fc, in task_PhySw() 0x1c20 + 0xc = 0x1c2c

//ff85eb64: 	e59f02e4 	ldr	r0, [pc, #740]	; ff85ee50: (0000246c) <---
//ff85eb68: 	e92d4010 	push	{r4, lr}
//ff85eb6c: 	e5900008 	ldr	r0, [r0, #8] <---
//ff85eb70: 	ebff6b5c 	bl	loc_ff8398e8
//ff85eb74: 	e3100001 	tst	r0, #1	; 0x1
//ff85eb78: 	18bd4010 	popne	{r4, lr}
//ff85eb7c: 	13a01042 	movne	r1, #66	; 0x42
//ff85eb80: 	128f0fb3 	addne	r0, pc, #716	; ff85ee54: (4444454c)  *"LEDDrv.c"
//ff85eb84: 	1afeffe2 	bne	loc_ff81eb14
//ff85eb88: 	e8bd8010 	pop	{r4, pc}
DEF(led_table, 0x2474)    // R0 -> 0x246c + 0x8

DEF(playrec_mode,0x2c98)    // ff8388bc (ff87f238) search for String "MenuIn" 0x2c94 + 4, play: 0x3, rec: 0x2

//ff9f8cb4:       e92d4010        push    {r4, lr}
//ff9f8cb8:       e51f41a4        ldr     r4, [pc, #-420] ; ff9f8b1c: (00008e10) <---
//ff9f8cbc:       e5940020        ldr     r0, [r4, #32] <---
//ff9f8cc0:       e3500000        cmp     r0, #0  ; 0x0
//ff9f8cc4:       1a000003        bne     loc_ff9f8cd8
//ff9f8cc8:       e28f1084        add     r1, pc, #132    ; ff9f8d54: (65726353)  *"ScreenLock"
//ff9f8ccc:       e3a00060        mov     r0, #96 ; 0x60
//ff9f8cd0:       ebfa420e        bl      loc_ff889510
//ff9f8cd4:       ebfab0c0        bl      loc_ff8a4fdc
DEF(enabled_refresh_physical_screen, 0x8e30)    // ff9f8cb8, 0x8e10 + 0x20 = 0x8e30

//ffaa2b40:       e59f1018        ldr     r1, [pc, #24]   ; ffaa2b60: (ffbd0d60) 
//ffaa2b44:       e7910100        ldr     r0, [r1, r0, lsl #2]
//ffaa2b48:       e12fff1e        bx      lr
DEF(FlashParamsTable, 0xFFBD0CAC)//ffbd0d60)   // referenced at ffaa2b40

// ff88ce14, search for (00000858) near (0000085c)
DEF(canon_menu_active, 0x2f60)   // 0x2f5c + 4 ?!!

// ff89c90c, search for "DSITask"
DEF(canon_shoot_menu_active, 0x3d360)   // ?!?

// search for 00000800 near 00000801
DEF(levent_table, 0xffb7a384)

// ff959398
DEF(movie_status, 0x6434)   // 0x63f8 + 0x3C

// ff98ae80
DEF(recreview_hold, 0x74ee)   // 0x74ec + 2 ?!?

// ff955ec0 search for "ZoomLens"
DEF(zoom_busy, 0x6398)  // 0x637c + 0x1C ?!?

// ff951720 search for "FocusLens"
DEF(focus_busy, 0x6234) //  0x622c + 0x8 ?!?

// ffaa5d30
DEF(zoom_status, 0x315B)   // ?!?

// ROM:FFA114FC, called by RefreshPhysicalScreen()
//DEF(full_screen_refresh, 0x926C)

// ff95dbbc, search for "Ver.005.003" (or other numbers)
DEF(some_flag_for_af_scan, 0x67e8)

DEF(full_screen_refresh, 0x8dcc) // ??? not sure

// --- ToDo
//DEF(some_f_for_dng, 0xDEAD)          // ??? TODO NOT FOUND!
//DEF(second_ext_for_dng, 0xDEAD)      // ??? TODO NOT FOUND!
