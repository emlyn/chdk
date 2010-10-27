#include "conf.h"

//int *video_quality = &conf.video_quality;
//int *video_mode    = &conf.video_mode;

void change_video_tables(int a, int b) {
    //int i;
    //for (i=0;i<24;i++) table[i]=(def_table[i]*a)/b;
}

// like other cameras
void  set_quality(int *x) { // -17 highest; +12 lowest
    if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// ff95a5f4: movie_record_task() aka. task_MovieRecord()
void __attribute__((naked,noinline)) movie_record_task() { // was FF96BD30
  asm volatile (
	"push	{r2, r3, r4, r5, r6, r7, r8, lr}\n"
	"ldr	r8, =0x000004b3\n" // was: "[pc, #756]	; ff95a8f4" 
	"ldr	r7, =0x00002710\n" // was: "[pc, #-2512]	; ff959c34" 
	"ldr	r4, =0x000063f8\n" // was: "[pc, #-4020]	; ff959654" 
	"ldr	r6, =0x0\n" // was: "mov ..., #0"
	"ldr	r5, =0x1\n" // was: "mov ..., #1"
"loc_ff95a60c:\n"
	"ldr	r0, [r4, #24]\n"
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
	"add	r1, sp, #4\n"	// 0x4
	"bl	sub_ff8396e4\n"
	"ldr	r0, [r4, #32]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff95a6dc\n"
	"ldr	r0, [sp, #4]\n"
	"ldr	r1, [r0]\n"
	"sub	r1, r1, #2\n"	// 0x2
	"cmp	r1, #9\n"	// 0x9
	"addls	pc, pc, r1, lsl #2\n"
	"b	loc_ff95a6dc\n"
	"b	loc_ff95a690\n" // 0 jump table start
	"b	loc_ff95a6b0\n"
	"b	loc_ff95a6c0\n"
	"b	loc_ff95a6c8\n"
	"b	loc_ff95a698\n"
	"b	loc_ff95a6d0\n"
	"b	loc_ff95a6a0\n"
	"b	loc_ff95a6dc\n"
	"b	loc_ff95a6d8\n"
	"b	loc_ff95a668\n" // 9
"loc_ff95a668:\n" // jump table entry 9
	"ldr	r0, =0xff95a308\n" // was: "sub	r0, pc, #872"  
	"str	r6, [r4, #52]\n"
	"str	r0, [r4, #164]\n"
/*
        // Ixus300 has this, referenced in case 4: (what does it do?)
        //"ADR     R0, =0xFF96BA00\n"
        "LDR     R0, =sub_FF96BA00_my\n"      // +
        "STR     R0, [R4,#0xAC]\n"
*/
	"ldr	r2, =0xff959820\n" // was: "[pc, #636]	; ff95a8f8" 
	"ldr	r1, =0x0009668c\n" // was: "[pc, #-2604]	; ff959c54" 
	"ldr	r0, =0xff959904\n" // was: "sub	r0, pc, #3456"  
	"str	r6, [r4, #36]\n" // 0x24
	"bl	sub_ff85021c\n"
	"str	r5, [r4, #56]\n" // 0x38
	"b	loc_ff95a6dc\n"
"loc_ff95a690:\n" // jump table entry 0
        "b      unlock_optical_zoom\n" // added
	"bl	sub_ff95a410\n"
	"b	loc_ff95a6dc\n"
"loc_ff95a698:\n" // jump table entry 4
/*
        // Ixus300 has the next 2 lines instead of the following one: (what does it do?)
        "LDR     R1, [R4,#0xAC]\n"
        "BLX     R1\n"
*/
	//"bl	sub_ff959f88\n"
	"bl	sub_ff959f88_my\n"
	"b	loc_ff95a6dc\n"
"loc_ff95a6a0:\n" // jump table entry 6
	"ldr	r1, [r0, #24]\n"
	"ldr	r0, [r0, #4]\n"
	"bl	sub_ffa8cc28\n"
	"b	loc_ff95a6dc\n"
"loc_ff95a6b0:\n" // jump table entry 1
	"ldr	r0, [r4, #56]\n"
	"cmp	r0, #5\n"	// 0x5
	"strne	r5, [r4, #40]\n"
	"b	loc_ff95a6dc\n"
"loc_ff95a6c0:\n" // jump table entry 2
	"bl	sub_ff959c84\n"
	"b	loc_ff95a6dc\n"
"loc_ff95a6c8:\n" // jump table entry 3
	"bl	sub_ff959950\n"
	"b	loc_ff95a6dc\n"
"loc_ff95a6d0:\n" // jump table entry 5
	"bl	sub_ff9597ac\n"
	"b	loc_ff95a6dc\n"
"loc_ff95a6d8:\n" // jump table entry 8
	"bl	sub_ff95a844\n"
"loc_ff95a6dc:\n" // jump table entry 7, default
	"ldr	r1, [sp, #4]\n"
	"ldr	r3, =0xff959640\n" // was: "[pc, #-2696]	; ff959c60"  **"MovieRecorder.c"
	"str	r6, [r1]\n"
	"str	r8, [sp]\n"
	"ldr	r0, [r4, #28]\n"
	"mov	r2, r7\n"
	"bl	sub_ff83a038\n"
	"b	loc_ff95a60c\n"
    );
}

void __attribute__((naked,noinline)) sub_ff959f88_my() { // was FF96BA00
  asm volatile (
	"push	{r4, r5, r6, r7, r8, lr}\n"
	"sub	sp, sp, #64\n"	// 0x40
	"ldr	r7, =0x0\n" // was: "mov ..., #0"
	"ldr	r6, =0x000063f8\n" // was: "[pc, #-2376]	; ff959654" 
	"mov	r4, r0\n"
	"str	r7, [sp, #48]\n"
	"str	r7, [sp, #40]\n"
	"ldr	r0, [r6, #56]\n"
	"ldr	r8, =0x4\n" // was: "mov ..., #4"
	"cmp	r0, #3\n"	// 0x3
	"streq	r8, [r6, #56]\n"
	"ldr	r0, [r6, #164]\n"
	"blx	r0\n"
	"ldr	r0, [r6, #56]\n"
	"cmp	r0, #4\n"	// 0x4
	"bne	loc_ff95a0f8\n"
	"add	r3, sp, #40\n"	// 0x28
	"add	r2, sp, #44\n"	// 0x2c
	"add	r1, sp, #48\n"	// 0x30
	"add	r0, sp, #52\n"	// 0x34
	"bl	sub_ffa8ccc4\n"
	"cmp	r0, #0\n"	// 0x0
	"ldr	r5, =0x1\n" // was: "mov ..., #1"
	"bne	loc_ff95a004\n"
	"ldr	r1, [r6, #40]\n"
	"cmp	r1, #1\n"	// 0x1
	"bne	loc_ff95a100\n"
	"ldr	r1, [r6, #92]\n"
	"ldr	r2, [r6, #60]\n"
	"cmp	r1, r2\n"
	"bcc	loc_ff95a100\n"
"loc_ff95a004:\n"
	"cmp	r0, #-2147483647\n"	// 0x80000001
	"streq	r8, [r6, #96]\n"
	"beq	loc_ff95a03c\n"
	"cmp	r0, #-2147483645\n"	// 0x80000003
	"streq	r5, [r6, #96]\n"
	"beq	loc_ff95a03c\n"
	"cmp	r0, #-2147483643\n"	// 0x80000005
	"ldreq	r0, =0x2\n" // was: "mov ..., #2"
	"beq	loc_ff95a038\n"
	"cmp	r0, #-2147483641\n"	// 0x80000007
	"strne	r7, [r6, #96]\n"
	"bne	loc_ff95a03c\n"
	"ldr	r0, =0x3\n" // was: "mov ..., #3"
"loc_ff95a038:\n"
	"str	r0, [r6, #96]\n"
"loc_ff95a03c:\n" // 3 refs
	"ldr	r0, =0x000966c0\n" // was: "[pc, #-2512]	; ff959674" 
	"ldr	r0, [r0, #8]\n"
	"cmp	r0, #0\n"	// 0x0
	"beq	loc_ff95a054\n"
	"bl	sub_ff861870\n"
	"b	loc_ff95a058\n"
"loc_ff95a054:\n"
	"bl	sub_ff9597ac\n"
"loc_ff95a058:\n"
	"ldr	r0, [r4, #28]\n"
	"add	r4, sp, #24\n"	// 0x18
	"add	r3, sp, #56\n"	// 0x38
	"mvn	r2, #1\n"	// 0x1
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"stm	r4, {r0, r1, r2, r3}\n"
	"ldr	r2, [r6, #116]\n"
	"ldr	r3, [r6, #120]\n"
	"add	r1, sp, #60\n"	// 0x3c
	"add	r4, sp, #8\n"	// 0x8
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"stm	r4, {r0, r1, r2, r3}\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"ldr	r2, =0x40\n" // was: "mov ..., #64"
	"strd	r2, [sp]\n"
	"ldr	r3, =0x000966d8\n" // was: "[pc, #2112]	; ff95a8dc" 
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ffa4b708\n"
	"ldr	r0, [r6, #16]\n"
	"ldr	r1, [r6, #84]\n"
	"bl	sub_ff839b00\n" // eventproc_export_TakeSemaphore()
	"cmp	r0, #9\n"	// 0x9
	"bne	loc_ff95a0c8\n"
"loc_ff95a0b8:\n"
	"bl	sub_ffa8d198\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"str	r5, [r6, #56]\n"
	"b	loc_ff95a228\n"
"loc_ff95a0c8:\n"
	"ldr	r0, [sp, #56]\n"
	"cmp	r0, #0\n"	// 0x0
	"beq	loc_ff95a0e4\n"
"loc_ff95a0d4:\n"
	"bl	sub_ffa8d198\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"str	r5, [r6, #56]\n"
	"b	loc_ff95a254\n"
"loc_ff95a0e4:\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ffa4b7ac\n"
	"bl	sub_ffa4b808\n"
	"ldr	r0, =0x5\n" // was: "mov ..., #5"
	"str	r0, [r6, #56]\n"
"loc_ff95a0f8:\n" // 3 refs
	"add	sp, sp, #64\n"	// 0x40
	"pop	{r4, r5, r6, r7, r8, pc}\n"
"loc_ff95a100:\n" // 2 refs
	"ldr	ip, [sp, #48]\n"
	"cmp	ip, #0\n"	// 0x0
	"beq	loc_ff95a2b0\n"
	"str	r5, [r6, #44]\n"
	"ldr	r0, [r6, #92]\n"
	"ldr	r8, [r4, #12]\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrne	lr, [sp, #52]\n"
	"bne	loc_ff95a1ac\n"
	"ldr	r0, [r4, #28]\n"
	"ldr	r1, [r4, #32]\n"
	"add	r3, sp, #56\n"	// 0x38
	"mvn	r2, #0\n"	// 0x0
	"add	lr, sp, #24\n"	// 0x18
	"stm	lr, {r0, r1, r2, r3}\n"
	"ldr	r0, [sp, #40]\n"
	"ldr	r2, [r6, #116]\n"
	"ldr	r3, [r6, #120]\n"
	"add	r1, sp, #60\n"	// 0x3c
	"add	lr, sp, #8\n"	// 0x8
	"stm	lr, {r0, r1, r2, r3}\n"
	"ldr	r3, [sp, #44]\n"
	"str	ip, [sp]\n"
	"str	r3, [sp, #4]\n"
	"ldmib	r4, {r0, r1}\n"
	"ldr	r3, [sp, #52]\n"
	"mov	r2, r8\n"
	"bl	sub_ffa4b708\n"
	"ldr	r0, [r6, #16]\n"
	"ldr	r1, [r6, #84]\n"
	"bl	sub_ff839b00\n" // eventproc_export_TakeSemaphore()
	"cmp	r0, #9\n"	// 0x9
	"beq	loc_ff95a0b8\n"
	"ldr	r0, [sp, #56]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff95a0d4\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ffa4b7ac\n"
	"ldr	r0, [sp, #60]\n"
	"ldr	r1, [sp, #52]\n"
	"add	lr, r1, r0\n"
	"ldr	r1, [sp, #48]\n"
	"sub	ip, r1, r0\n"
"loc_ff95a1ac:\n"
	"ldr	r2, [r6, #88]\n"
	"ldr	r0, [r4, #28]\n"
	"ldr	r1, [r4, #32]\n"
	"add	r3, sp, #56\n"	// 0x38
	"str	r0, [sp, #24]\n"
	"str	r1, [sp, #28]\n"
	"str	r3, [sp, #36]\n"
	"str	r2, [sp, #32]\n"
	"ldr	r2, [r6, #116]\n"
	"ldr	r3, [r6, #120]\n"
	"ldr	r0, [sp, #40]\n"
	"str	r3, [sp, #20]\n"
	"ldr	r3, [sp, #44]\n"
	"add	r1, sp, #60\n"	// 0x3c
	"str	r2, [sp, #16]\n"
	"str	r3, [sp, #4]\n"
	"str	r1, [sp, #12]\n"
	"str	ip, [sp]\n"
	"str	r0, [sp, #8]\n"
	"ldmib	r4, {r0, r1}\n"
	"mov	r3, lr\n"
	"mov	r2, r8\n"
	"bl	sub_ffa4b708\n"
	"ldr	r0, [r6, #16]\n"
	"ldr	r1, [r6, #84]\n"
	"bl	sub_ff839b00\n" // eventproc_export_TakeSemaphore()
	"cmp	r0, #9\n"	// 0x9
	"bne	loc_ff95a23c\n"
	"bl	sub_ffa8d198\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r5, [r6, #56]\n"
"loc_ff95a228:\n"
	"bl	sub_ffa4b7ac\n"
	"ldr	r0, =0xc\n" // was: "mov ..., #12"
	"bl	sub_ff886d0c\n"
	"ldr	r0, =0x90000\n" // was: "mov ..., #589824"
	"b	loc_ff95a264\n"
"loc_ff95a23c:\n"
	"ldr	r0, [sp, #56]\n"
	"cmp	r0, #0\n"	// 0x0
	"beq	loc_ff95a278\n"
	"bl	sub_ffa8d198\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r5, [r6, #56]\n"
"loc_ff95a254:\n"
	"bl	sub_ffa4b7ac\n"
	"ldr	r0, =0xc\n" // was: "mov ..., #12"
	"bl	sub_ff886d0c\n"
	"ldr	r0, =0xa0000\n" // was: "mov ..., #655360"
"loc_ff95a264:\n"
	"bl	sub_ff890f40\n" // eventproc_export_HardwareDefect()
	"ldr	r1, [r6, #148]!\n"
	"ldr	r0, [r6, #12]\n"
	"blx	r1\n"
	"b	loc_ff95a0f8\n"
"loc_ff95a278:\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ffa4b7ac\n"
	"ldr	r0, [sp, #52]\n"
	"ldr	r1, [sp, #60]\n"
	"bl	sub_ffa8cef0\n"
	"ldr	r0, [r6, #88]\n"
	"ldr	r3, =0x00006470\n" // <----
	"add	r1, r0, #1\n"	// 0x1
	"str	r1, [r6, #88]\n"
	"str	r3, [sp]\n"
	"ldr	r0, [sp, #60]\n"
	"sub	r3, r3, #4\n"	// <----
	"ldr	r2, =0xf\n" // was: "mov ..., #15"
	"bl	sub_ffa8b040\n"

        "ldr    r0, =0x6470-4\n" // added
        "bl     set_quality\n" // added

"loc_ff95a2b0:\n"
	"ldr	r0, [r6, #92]\n"
	"add	r0, r0, #1\n"	// 0x1
	"str	r0, [r6, #92]\n"
	"ldr	r1, [r6, #72]\n"
	"mul	r0, r1, r0\n"
	"ldr	r1, [r6, #68]\n"
	"bl	sub_ffb3b51c\n"
	"mov	r4, r0\n"
	"bl	sub_ffa8d1d0\n"
	"ldr	r1, [r6, #124]\n"
	"cmp	r1, r4\n"
	"bne	loc_ff95a2ec\n"
	"ldr	r0, [r6, #48]\n"
	"cmp	r0, #1\n"	// 0x1
	"bne	loc_ff95a300\n"
"loc_ff95a2ec:\n"
	"ldr	r1, [r6, #136]\n"
	"mov	r0, r4\n"
	"blx	r1\n"
	"str	r4, [r6, #124]\n"
	"str	r7, [r6, #48]\n"
"loc_ff95a300:\n"
	"str	r7, [r6, #44]\n"
	"b	loc_ff95a0f8\n"
    );
}
