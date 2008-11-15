#include "camera.h"
#include "conf.h"

void debug_led(int state);

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table[24]={0x2000, 0x38D,0x788,0x5800,0x9C5,0x14B8,0x10000,0x1C6A,0x3C45,0x8000,0xE35,0x1E23,0x1CCD,
                    -0x2E1,-0x579,0x4F33,-0x7EB,-0xF0C,0xE666,-0x170A,-0x2BC6,0x7333,-0xB85,-0x15E3}; // @ 0xffac134c -> 0xFFAA8CCC

long table[24];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<24;i++) table[i]=(def_table[i]*a)/b;
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};




// Extracted method: taskcreate_MovieRecord (ff859f30-ff85a014)
// Overridden calls:
//     task_MovieRecord
void __attribute__((naked,noinline)) taskcreate_MovieRecord_my() {
    asm volatile (
		"stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr} \n"
		"ldr	r5,  =0x00005368 \n"
		"mov	r6, #0	\n" // ; 0x0
		"str	r6, [r5, #36] \n"
		"ldr	r0, [r5, #8] \n"
		"ldr	r8,  =0x00002710 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF859FE8 \n"
		"mov	r0, #1	\n" // ; 0x1
		"str	r0, [r5, #8] \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF81BC34 \n"
		"str	r0, [r5, #20] \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF81BC34 \n"
		"str	r0, [r5, #24] \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #10	\n" // ; 0xa
		"BL	sub_FF81BBEC \n"
		"str	r0, [r5, #28] \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #10	\n" // ; 0xa
		"BL	sub_FF81BBEC \n"
		"ldr	r7,  =0x00019674 \n"
		"mov	r4, #9	\n" // ; 0x9
		"add	r9, r4, #724	\n" // ; 0x2d4
		"str	r0, [r5, #32] \n"
	"loc_FF859FA4:\n"
		"rsb	r0, r4, r4, lsl #3 \n"
		"str	r6, [r7, r0, lsl #2] \n"
		"add	r1, r7, r0, lsl #2 \n"
		"str	r9, [sp] \n"
		"ldr	r0, [r5, #32] \n"
		"ldr	r3,  =0xff8591bc \n"
		"mov	r2, r8 \n"
		"BL	sub_FF81BCF8 \n"
		"subs	r4, r4, #1	\n" // ; 0x1
		"BPL	loc_FF859FA4 \n"
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
//	"ldr	r3, =0xff859e28 \n" // ; (e92d41fc)
	"ldr	r3, =task_MovieRecord_my \n" // ----------------->
		"mov	r2, #4096	\n" // ; 0x1000
		"mov	r1, #20	\n" // ; 0x14
		"ldr	r0, =0xff85a134 \n" // ; (69766f4d)  *"MovieRecord"
		"BL	sub_FF81BBB8 \n" // <KernelCreateTask -255020>
	"loc_FF859FE8:\n"
		"BL	sub_FF9344F8 \n" // <taskcreate_AviWrite +894224>
		"BL	sub_FF85A04C \n"
		"mov	r1, r0 \n"
		"mov	r0, #11	\n" // ; 0xb
		"add	r3, r0, #732	\n" // ; 0x2dc
		"str	r0, [r1] \n"
		"str	r3, [sp] \n"
		"ldr	r3, =0xff8591bc \n" // ; (69766f4d)  *"MovieRecorder.c"
		"mov	r2, r8 \n"
		"ldr	r0, [r5, #28] \n"
		"BL	sub_FF81BCF8 \n"
		"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, pc} \n"
    );
}

// Extracted method: task_MovieRecord (ff859e28 - ff859f2c)
// Overridden calls:
// sub_FF8598C0
void __attribute__((naked,noinline)) task_MovieRecord_my() {
	asm volatile (
		"stmdb	sp!, {r2, r3, r4, r5, r6, r7, r8, lr} \n"
		"ldr	r8,  =0x0000032b \n"
		"ldr	r7,  =0x00002710 \n"
		"ldr	r4,  =0x00005368 \n"
		"mov	r6, #0	\n" // ; 0x0
		"mov	r5, #1	\n" // ; 0x1
	"loc_FF859E40:\n"
		"ldr	r0, [r4, #28] \n"
		"mov	r2, #0	\n" // ; 0x0
		"add	r1, sp, #4	\n" // ; 0x4
		"BL	sub_FF827E54 \n"
		"ldr	r0, [r4, #36] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF859F10 \n"
		"ldr	r0, [sp, #4] \n"
		"ldr	r1, [r0] \n"
		"sub	r1, r1, #2	\n" // ; 0x2
		"cmp	r1, #9	\n" // ; 0x9
		"addls	pc, pc, r1, lsl #2 \n"
		"B	loc_FF859F10 \n"
		"B	loc_FF859EC4 \n"
		"B	loc_FF859EE4 \n"
		"B	loc_FF859EF4 \n"
		"B	loc_FF859EFC \n"
		"B	loc_FF859ECC \n"
		"B	loc_FF859F04 \n"
		"B	loc_FF859ED4 \n"
		"B	loc_FF859F10 \n"
		"B	loc_FF859F0C \n"
		"B	loc_FF859E9C \n"
	"loc_FF859E9C:\n"
		"str	r6, [r4, #56] \n"
		"ldr	r0, =0xff859afc \n" // ; (e12fff1e)
		"ldr	r2, =0xff85942c \n" // ; (e92d4038)
		"ldr	r1,  =0x0001979c \n"
		"str	r0, [r4, #164] \n"
		"ldr	r0,  =0xff859510 \n"
		"str	r6, [r4, #40] \n"
		"BL	sub_FF8C5714 \n"
		"str	r5, [r4, #60] \n"
		"B	loc_FF859F10 \n"
	"loc_FF859EC4:\n"
		"BL	sub_FF859BF4 \n"
		"B	loc_FF859F10 \n"
	"loc_FF859ECC:\n"
//	"BL	sub_FF8598C0 \n"
	"BL	sub_FF8598C0_my \n" // -------------------->
		"B	loc_FF859F10 \n"
	"loc_FF859ED4:\n"
		"ldr	r1, [r0, #16] \n"
		"ldr	r0, [r0, #4] \n"
		"BL	sub_FF935104 \n"
		"B	loc_FF859F10 \n"
	"loc_FF859EE4:\n"
		"ldr	r0, [r4, #60] \n"
		"cmp	r0, #5	\n" // ; 0x5
		"strne	r5, [r4, #44] \n"
		"B	loc_FF859F10 \n"
	"loc_FF859EF4:\n"
		"BL	sub_FF8596C4 \n"
		"B	loc_FF859F10 \n"
	"loc_FF859EFC:\n"
		"BL	sub_FF85955C \n"
		"B	loc_FF859F10 \n"
	"loc_FF859F04:\n"
		"BL	sub_FF8593B8 \n"
		"B	loc_FF859F10 \n"
	"loc_FF859F0C:\n"
		"BL	sub_FF85A078 \n"
	"loc_FF859F10:\n"
		"ldr	r1, [sp, #4] \n"
		"ldr	r3,  =0xff8591bc \n"
		"str	r6, [r1] \n"
		"str	r8, [sp] \n"
		"ldr	r0, [r4, #32] \n"
		"mov	r2, r7 \n"
		"BL	sub_FF81BCF8 \n"
		"B	loc_FF859E40 \n"
    );
}

// Extracted method: (ff8598c0-ff859af8)
// Overridden calls:
// sub_FF9334AC_my
void __attribute__((naked,noinline)) sub_FF8598C0_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr} \n"
		"sub	sp, sp, #60	\n" // ; 0x3c
		"mov	r7, #0	\n" // ; 0x0
		"ldr	r5,  =0x00005368 \n"
		"mov	r4, r0 \n"
		"str	r7, [sp, #44] \n"
		"str	r7, [sp, #36] \n"
		"ldr	r0, [r5, #60] \n"
		"mov	r8, #4	\n" // ; 0x4
		"cmp	r0, #3	\n" // ; 0x3
		"streq	r8, [r5, #60] \n"
		"ldr	r0, [r5, #164] \n"
		"mov	r6, #0	\n" // ; 0x0
		"blx	r0 \n"
		"ldr	r0, [r5, #60] \n"
		"cmp	r0, #4	\n" // ; 0x4
		"BNE	loc_FF8599D0 \n"
		"ldrh	r0, [r5, #2] \n"
		"mov	r9, #1	\n" // ; 0x1
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF85993C \n"
		"ldrh	r1, [r5, #4] \n"
		"ldr	r0, [r5, #76] \n"
		"mul	r0, r1, r0 \n"
		"mov	r1, #1000	\n" // ; 0x3e8
		"BL	sub_FFAA663C \n"
		"mov	r1, r0 \n"
		"ldr	r0, [r5, #84] \n"
		"BL	sub_FFAA663C \n"
		"cmp	r1, #0	\n" // ; 0x0
		"BNE	loc_FF859958 \n"
	"loc_FF85993C:\n"
		"add	r3, sp, #36	\n" // ; 0x24
		"add	r2, sp, #40	\n" // ; 0x28
		"add	r1, sp, #44	\n" // ; 0x2c
		"add	r0, sp, #48	\n" // ; 0x30
		"BL	sub_FF935298 \n"
		"movs	r6, r0 \n"
		"BNE	loc_FF859974 \n"
	"loc_FF859958:\n"
		"ldr	r0, [r5, #44] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF8599D8 \n"
		"ldr	r0, [r5, #84] \n"
		"ldr	r1, [r5, #64] \n"
		"cmp	r0, r1 \n"
		"BCC	loc_FF8599D8 \n"
	"loc_FF859974:\n"
		"cmp	r6, #-2147483647	\n" // ; 0x80000001
		"streq	r8, [r5, #88] \n"
		"BEQ	loc_FF8599AC \n"
		"cmp	r6, #-2147483645	\n" // ; 0x80000003
		"streq	r9, [r5, #88] \n"
		"BEQ	loc_FF8599AC \n"
		"cmp	r6, #-2147483643	\n" // ; 0x80000005
		"moveq	r0, #2	\n" // ; 0x2
		"BEQ	loc_FF8599A8 \n"
		"cmp	r6, #-2147483641	\n" // ; 0x80000007
		"strne	r7, [r5, #88] \n"
		"BNE	loc_FF8599AC \n"
		"mov	r0, #3	\n" // ; 0x3
	"loc_FF8599A8:\n"
		"str	r0, [r5, #88] \n"
	"loc_FF8599AC:\n"
		"ldr	r0,  =0x000197cc \n"
		"ldr	r0, [r0, #8] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF8599C4 \n"
		"BL	sub_FF8440F0 \n"
		"B	loc_FF8599C8 \n"
	"loc_FF8599C4:\n"
		"BL	sub_FF8593B8 \n"
	"loc_FF8599C8:\n"
		"mov	r0, #5	\n" // ; 0x5
		"str	r0, [r5, #60] \n"
	"loc_FF8599D0:\n"
		"add	sp, sp, #60	\n" // ; 0x3c
		"ldmia	sp!, {r4, r5, r6, r7, r8, r9, pc} \n"
	"loc_FF8599D8:\n"
		"ldr	ip, [sp, #44] \n"
		"cmp	ip, #0	\n" // ; 0x0
		"BEQ	loc_FF859AA4 \n"
		"str	r9, [r5, #48] \n"
		"ldr	r0, [r5, #112] \n"
		"ldr	r1, [r4, #20] \n"
		"ldr	r2, [r4, #24] \n"
		"ldr	lr, [r4, #12] \n"
		"add	r3, sp, #52	\n" // ; 0x34
		"add	r6, sp, #20	\n" // ; 0x14
		"stmia	r6, {r0, r1, r2, r3} \n"
		"ldr	r0, [sp, #36] \n"
		"ldr	r3, [r5, #92] \n"
		"ldr	r1, [sp, #40] \n"
		"add	r2, sp, #56	\n" // ; 0x38
		"add	r6, sp, #8	\n" // ; 0x8
		"stmia	r6, {r0, r2, r3} \n"
		"str	r1, [sp, #4] \n"
		"str	ip, [sp] \n"
		"ldmib	r4, {r0, r1} \n"
		"ldr	r3, [sp, #48] \n"
		"mov	r2, lr \n"
		"BL	sub_FF8ED004 \n"
		"ldr	r0, [r5, #20] \n"
		"mov	r1, #1000	\n" // ; 0x3e8
		"BL	sub_FF81B774 \n" // <TakeSemaphore -254664>
		"cmp	r0, #9	\n" // ; 0x9
		"BNE	loc_FF859A58 \n"
		"BL	sub_FF935874 \n"
		"mov	r0, #589824	\n" // ; 0x90000
		"str	r9, [r5, #60] \n"
		"B	loc_FF859A70 \n"
	"loc_FF859A58:\n"
		"ldr	r0, [sp, #52] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF859A78 \n"
		"BL	sub_FF935874 \n"
		"mov	r0, #655360	\n" // ; 0xa0000
		"str	r9, [r5, #60] \n"
	"loc_FF859A70:\n"
		"BL	sub_FF873B30 \n" // <HardwareDefect +106688>
		"B	loc_FF8599D0 \n"
	"loc_FF859A78:\n"
		"BL	sub_FF8ED0C8 \n"
		"ldr	r0, [sp, #48] \n"
		"ldr	r1, [sp, #56] \n"
		"BL	sub_FF93561C \n"
		"ldr	r0, [r5, #80] \n"
		"ldr	r1,  =0x000053d8 \n"
		"add	r0, r0, #1	\n" // ; 0x1
		"str	r0, [r5, #80] \n"
		"ldr	r0, [sp, #56] \n"
		"mov	r2, #0	\n" // ; 0x0
//	"BL	sub_FF9334AC \n"
	"BL	sub_FF9334AC_my \n"
	"loc_FF859AA4:\n"
		"ldr	r0, [r5, #84] \n"
		"add	r0, r0, #1	\n" // ; 0x1
		"str	r0, [r5, #84] \n"
		"ldr	r1, [r5, #124] \n"
		"mul	r0, r1, r0 \n"
		"ldr	r1, [r5, #120] \n"
		"BL	sub_FFAA663C \n"
		"mov	r4, r0 \n"
		"BL	sub_FF9358AC \n"
		"ldr	r1, [r5, #116] \n"
		"cmp	r1, r4 \n"
		"BNE	loc_FF859AE0 \n"
		"ldr	r0, [r5, #52] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF859AF4 \n"
	"loc_FF859AE0:\n"
		"ldr	r1, [r5, #136] \n"
		"mov	r0, r4 \n"
		"blx	r1 \n"
		"str	r4, [r5, #116] \n"
		"str	r7, [r5, #52] \n"
	"loc_FF859AF4:\n"
		"str	r7, [r5, #48] \n"
		"B	loc_FF8599D0 \n"
    );
}

// Extracted method: (ff9334ac-ff93358c)
// Overridden calls:
void __attribute__((naked,noinline)) sub_FF9334AC_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, r7, r8, lr} \n"
		"ldr	r4,  =0x00008794 \n"
		"ldr	lr, [r4] \n"
		"ldr	r2, [r4, #8] \n"
		"cmp	lr, #0	\n" // ; 0x0
		"ldrne	r3, [r4, #12] \n"
		"mov	r5, r2 \n"
		"cmpne	r3, #1	\n" // ; 0x1
		"moveq	r2, #0	\n" // ; 0x0
		"streq	r0, [r4] \n"
		"streq	r2, [r4, #12] \n"
		"BEQ	loc_FF933578 \n"
		"ldr	r3, [r4, #4] \n"

//	"ldr	r7,  =0xffac134c \n"
	"ldr	r7,  =table \n" // +

		"add	ip, r3, r3, lsl #1 \n"
		"ldr	r3, [r7, ip, lsl #2] \n"
		"add	r6, r7, #48	\n" // ; 0x30
		"ldr	r8, [r6, ip, lsl #2] \n"
		"sub	r3, lr, r3 \n"
		"cmp	r3, #0	\n" // ; 0x0
		"sub	lr, lr, r8 \n"
		"BLE	loc_FF933534 \n"
		"add	ip, r7, ip, lsl #2 \n"
		"ldr	lr, [ip, #4] \n"
		"cmp	lr, r3 \n"
		"addge	r2, r2, #1	\n" // ; 0x1
		"BGE	loc_FF933528 \n"
		"ldr	ip, [ip, #8] \n"
		"cmp	ip, r3 \n"
		"addlt	r2, r2, #3	\n" // ; 0x3
		"addge	r2, r2, #2	\n" // ; 0x2

	"loc_FF933528:\n"
//	"cmp	r2, #23	\n" // ; 0x17
//	"movge	r2, #22	\n" // ; 0x16
	"CMP     R2, #0x1A\n"   // +
	"MOVGE   R2, #0x19\n"   // +
		"B	loc_FF933568 \n"

	"loc_FF933534:\n"
		"cmp	lr, #0	\n" // ; 0x0
		"BGE	loc_FF933568 \n"
		"add	r3, r6, ip, lsl #2 \n"
		"ldr	ip, [r3, #4] \n"
		"cmp	ip, lr \n"
		"suble	r2, r2, #1	\n" // ; 0x1
		"BLE	loc_FF933560 \n"
		"ldr	r3, [r3, #8] \n"
		"cmp	r3, lr \n"
		"subgt	r2, r2, #3	\n" // ; 0x3
		"suble	r2, r2, #2	\n" // ; 0x2
	"loc_FF933560:\n"
		"cmp	r2, #0	\n" // ; 0x0
		"movlt	r2, #0	\n" // ; 0x0
	"loc_FF933568:\n"
		"cmp	r2, r5 \n"
		"strne	r2, [r4, #8] \n"
		"movne	r2, #1	\n" // ; 0x1
		"strne	r2, [r4, #12] \n"
	"loc_FF933578:\n"
//	"ldr	r2,  =0xffac12f0 \n"
	"ldr	r2,  =CompressionRateTable \n" // +

		"ldr	r3, [r4, #8] \n"
		"ldr	r2, [r2, r3, lsl #2] \n"

	"LDR     R3, =video_mode\n"      // +
	"LDR     R3, [R3]\n"             // +
	"LDR     R3, [R3]\n"             // +
	"CMP     R3, #1\n"               // +
	"LDREQ   R3, =video_quality\n"   // +
	"LDREQ   R3, [R3]\n"             // +
	"LDREQ   R2, [R3]\n"             // +

		"str	r2, [r1] \n"
		"str	r0, [r4] \n"
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
    );
}

// Extracted method: (ff85ef0c-ff85f17c)
// Overridden calls:
//     taskcreate_MovieRecord
void __attribute__((naked,noinline)) sub_FF85EF0C_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, r7, r8, lr} \n"
		"mov	r8, r0 \n"
		"mov	r0, #65	\n" // ; 0x41
		"sub	sp, sp, #56	\n" // ; 0x38
		"mov	r5, #0	\n" // ; 0x0
		"str	r0, [sp, #52] \n"
		"BL	sub_FF85EEDC \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r1,  =0x00000163 \n"
		"BNE	loc_FF85F0B8 \n"
		"ldr	r4,  =0x000054f8 \n"
		"mov	r1, #94	\n" // ; 0x5e
		"ldr	r0, [r4, #8] \n"
		"BL	sub_FF827C04 \n"
		"BL	sub_FF86CF10 \n"
		"str	r0, [r4, #4] \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF866D48 \n" // <time +32248>
		"str	r0, [sp, #40] \n"
		"add	r0, sp, #40	\n" // ; 0x28
		"mov	r1, sp \n"
		"BL	sub_FF866844 \n" // <LocalTime +30948>
		"mov	r0, sp \n"
		"BL	sub_FF86672C \n"
		"str	r0, [sp, #44] \n"
		"ldr	r0, [r4, #4] \n"
		"mov	r3, #4	\n" // ; 0x4
		"add	r2, sp, #44	\n" // ; 0x2c
		"mov	r1, #52	\n" // ; 0x34
		"BL	sub_FF86D224 \n"
		"ldr	r7, [sp, #44] \n"
		"BL	sub_FF85F3FC \n"
		"mov	r6, #0	\n" // ; 0x0
		"add	r1, sp, #40	\n" // ; 0x28
		"add	r0, sp, #44	\n" // ; 0x2c
		"str	r6, [sp, #44] \n"
		"str	r6, [sp, #40] \n"
		"BL	sub_FF830154 \n"
		"ldr	r0, [r4, #4] \n"
		"mov	r3, #2	\n" // ; 0x2
		"add	r2, sp, #44	\n" // ; 0x2c
		"mov	r1, #47	\n" // ; 0x2f
		"BL	sub_FF86D224 \n"
		"ldr	r0, [r4, #4] \n"
		"mov	r3, #2	\n" // ; 0x2
		"add	r2, sp, #40	\n" // ; 0x28
		"mov	r1, #45	\n" // ; 0x2d
		"BL	sub_FF86D224 \n"
		"add	r1, sp, #40	\n" // ; 0x28
		"add	r0, sp, #44	\n" // ; 0x2c
		"BL	sub_FF834304 \n"
		"ldr	r0, [r4, #4] \n"
		"mov	r3, #2	\n" // ; 0x2
		"add	r2, sp, #44	\n" // ; 0x2c
		"mov	r1, #48	\n" // ; 0x30
		"BL	sub_FF86D224 \n"
		"add	r1, sp, #40	\n" // ; 0x28
		"add	r0, sp, #44	\n" // ; 0x2c
		"BL	sub_FF83092C \n"
		"ldr	r0, [r4, #4] \n"
		"mov	r3, #2	\n" // ; 0x2
		"add	r2, sp, #40	\n" // ; 0x28
		"mov	r1, #46	\n" // ; 0x2e
		"BL	sub_FF86D224 \n"
		"ldr	r0, [r4, #4] \n"
		"mov	r3, #2	\n" // ; 0x2
		"add	r2, sp, #44	\n" // ; 0x2c
		"mov	r1, #184	\n" // ; 0xb8
		"BL	sub_FF86D2D0 \n"
		"tst	r0, #1	\n" // ; 0x1
		"ldrne	r1,  =0x00000142 \n"
		"ldrne	r0, =0xff85f330 \n" // ; (6f4d7353)  *"SsMovieRec.c"
		"BLNE	sub_FF81BDB8 \n" // <DebugAssert -275060>
		"ldrh	r0, [sp, #44] \n"
		"mov	r3, #4	\n" // ; 0x4
		"add	r2, sp, #40	\n" // ; 0x28
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r0, #1	\n" // ; 0x1
		"str	r0, [sp, #40] \n"
		"ldr	r0, [r4, #4] \n"
		"mov	r1, #146	\n" // ; 0x92
		"BL	sub_FF86D224 \n"
		"mov	r2, #1	\n" // ; 0x1
		"add	r1, sp, #52	\n" // ; 0x34
		"mov	r0, #250	\n" // ; 0xfa
		"BL	sub_FF86CD80 \n" // <PT_GetPropertyCaseString +56608>
		"tst	r0, #1	\n" // ; 0x1
		"ldrne	r1,  =0x0000017a \n"
		"ldrne	r0, =0xff85f330 \n" // ; (6f4d7353)  *"SsMovieRec.c"
		"BLNE	sub_FF81BDB8 \n" // <DebugAssert -275128>
		"ldrb	r0, [sp, #52] \n"
		"mov	r3, r8 \n"
		"mov	r2, #20	\n" // ; 0x14
		"and	r1, r0, #255	\n" // ; 0xff
		"add	r0, sp, #48	\n" // ; 0x30
		"str	r7, [sp] \n"
		"BL	sub_FF90F24C \n"
		"tst	r0, #1	\n" // ; 0x1
		"ldrne	r1,  =0x0000017e \n"
		"BNE	loc_FF85F0B8 \n"
		"ldr	r0,  =0x00019a60 \n"
		"ldr	r1, [sp, #48] \n"
		"mov	r2, #16	\n" // ; 0x10
		"BL	sub_FF901F00 \n"
		"tst	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF85F0C8 \n"
		"ldr	r1,  =0x00000186 \n"
	"loc_FF85F0B8:\n"
		"ldr	r0, =0xff85f330 \n" // ; (6f4d7353)  *"SsMovieRec.c"
		"BL	sub_FF81BDB8 \n" // <DebugAssert -275204>
	"loc_FF85F0C0:\n"
		"add	sp, sp, #56	\n" // ; 0x38
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	"loc_FF85F0C8:\n"
		"ldr	r0, [r4, #4] \n"
		"mov	r3, #4	\n" // ; 0x4
		"add	r2, sp, #48	\n" // ; 0x30
		"mov	r1, #43	\n" // ; 0x2b
		"BL	sub_FF86D224 \n"
		"BL	sub_FF87FB64 \n"
		"ldrsb	r1, [sp, #52] \n"
		"cmp	r0, r1 \n"
		"moveq	r7, #0	\n" // ; 0x0
		"BEQ	loc_FF85F11C \n"
		"ldr	r5,  =0x00019a60 \n"
		"mov	r0, r5 \n"
		"BL	sub_FF87FCE0 \n"
		"mov	r8, r0 \n"
		"BL	sub_FF8B8308 \n"
		"cmp	r8, r0 \n"
		"mov	r7, r0 \n"
		"ldrls	r1,  =0x00000193 \n"
		"ldrls	r0, =0xff85f330 \n" // ; (6f4d7353)  *"SsMovieRec.c"
		"BLLS	sub_FF81BDB8 \n" // <DebugAssert -275292>
		"sub	r7, r8, r7 \n"
	"loc_FF85F11C:\n"
//	"BL	sub_FF859F30 \n" // --------------->
	"BL	taskcreate_MovieRecord_my \n" // --------------->
		"ldr	r0,  =0x00019a84 \n"
		"ldrh	r3, [r0, #78] \n"
		"ldrh	r2, [r0, #76] \n"
		"ldr	r1, [r0, #72] \n"
		"ldr	r0, [r0, #68] \n"
		"BL	sub_FF858EC0 \n"
		"mov	r3, #0	\n" // ; 0x0
		"ldr	r2, =0xff85eea4 \n" // ; (e59f0478)
		"mov	r1, #0	\n" // ; 0x0
		"ldr	r0, =0xff85eeb8 \n" // ; (e59f0464)
		"add	r8, sp, #12	\n" // ; 0xc
		"stmia	r8, {r0, r1, r2, r3} \n"
		"ldr	r2, =0xff85eec8 \n" // ; (e59f0454)
		"ldr	r1, =0xff85eeb4 \n" // ; (eaff17ab)
		"stmia	sp, {r1, r2, r3} \n"
		"ldr	r1, [r4, #4] \n"
		"mov	r3, r6 \n"
		"mov	r2, r7 \n"
		"mov	r0, r5 \n"
		"BL	sub_FF85921C \n"
		"ldr	r0, [r4, #8] \n"
		"mov	r1, #32	\n" // ; 0x20
		"BL	sub_FF827BD0 \n"
		"B	loc_FF85F0C0 \n"
		".ltorg \n"
    );
}

// Extracted method: (ff8273f0-ff827424)
// Overridden calls: sub_FF85EF0C
// -> sub_FF8273F0
void __attribute__((naked,noinline)) sub_FF8273F0_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"mov	r4, r0 \n"
		"mov	r0, #32	\n" // ; 0x20
		"ldr	r1, =0xff82759c \n" // ; (50415353)  *"SSAPI::RecordMovie"
		"BL	sub_FF86A150 \n"
		"BL	sub_FF82778C \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldmneia	sp!, {r4, pc} \n"
		"mov	r0, #4	\n" // ; 0x4
		"BL	sub_FF8581D0 \n"
		"BL	sub_FF85CC50 \n"
		"mov	r0, r4 \n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF85EF0C \n"
	"B	sub_FF85EF0C_my \n" // --------------->
    );
}

// Extracted method: (ff87de44-ff87ded0)
// Overridden calls:
//     sub_FF828534 -> sub_FF8273F0
//  -> sub_FF87DE44
void __attribute__((naked,noinline)) sub_FF87DE44_my() {
    asm volatile (
		"stmdb	sp!, {r3, r4, r5, lr} \n"
		"ldr	r4,  =0x00005e18 \n"
		"ldr	r0, [r4, #68] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF87DE8C \n"
		"BL	sub_FF8741B8 \n" // <j_PTM_GetWorkingCaptureMode -40096>
		"sub	ip, r0, #2560	\n" // ; 0xa00
		"subs	ip, ip, #43	\n" // ; 0x2b
		"mov	r5, #1	\n" // ; 0x1
		"BNE	loc_FF87DE84 \n"
		"ldr	r0,  =0x00008051 \n"
		"mov	r2, #1	\n" // ; 0x1
		"mov	r1, #1	\n" // ; 0x1
		"BL	sub_FF8741C0 \n" // <j_PTM_SetCurrentItem_0 -40120>
		"str	r5, [r4, #68] \n"
		"B	loc_FF87DE8C \n"
	"loc_FF87DE84:\n"
		"str	r5, [r4, #68] \n"
		"BL	sub_FF873894 \n" // <LockMainPower -42484>
	"loc_FF87DE8C:\n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #128	\n" // ; 0x80
		"BL	sub_FF87EBD0 \n"
		"mov	r2, #2	\n" // ; 0x2
		"mov	r1, sp \n"
		"mov	r0, #107	\n" // ; 0x6b
		"BL	sub_FF86CD80 \n" // <PT_GetPropertyCaseString -69924>
		"mov	r2, #2	\n" // ; 0x2
		"mov	r1, sp \n"
		"mov	r0, #163	\n" // ; 0xa3
		"BL	sub_FF86CC80 \n" // <PT_SetPropertyCaseString -70196>
		"BL	sub_FF85B108 \n"
		"BL	sub_FF87CDE0 \n"
//	"BL	sub_FF8273F0 \n"
	"BL	sub_FF8273F0_my \n" // -------------------->
		"BL	sub_FF8724CC \n"
		"str	r0, [r4, #76] \n"
		"BL	sub_FF87D5E8 \n"
		"ldmia	sp!, {r3, r4, r5, pc} \n"
    );
}

// Extracted method: (ff87e780-ff87e7a8)
// Overridden calls:
//     sub_FF87821C -> sub_FF87DE44
void __attribute__((naked,noinline)) sub_FF87E780_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff87e958 \n" // ; (746e455f)  *"_EntryActionOnMoving"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"ldr	r1,  =0x00005e68 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r1, #12] \n"
		"mov	r0, #4	\n" // ; 0x4
		"BL	sub_FF87E6C4 \n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF87DE44 \n"
	"B	sub_FF87DE44_my \n"
    );
}

// Extracted method: (ff87e1c8-ff87e21c)
// Overridden calls:
//     sub_FF878B58 -> sub_FF87E780
void __attribute__((naked,noinline)) sub_FF87E1C8_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff87e4a4 \n" // ; (746e455f)  *"_EntryActionOnPreMoving"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"ldr	r4,  =0x00005e68 \n"
		"ldr	r0, [r4, #16] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldmeqia	sp!, {r4, lr} \n"
//	"BEQ	sub_FF87E780 \n"
	"BEQ	sub_FF87E780_my \n"
		"ldr	r1, =0xff87e4c0 \n" // ; (746e455f)  *"_EntryActionOnSelfTimer"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"BL	sub_FF960BEC \n"
		"ldr	r0, [r4, #24] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"movne	r0, #1	\n" // ; 0x1
		"strne	r0, [r4, #24] \n"
		"BLNE	sub_FF873894 \n" // <LockMainPower -43384>
		"mov	r0, #9	\n" // ; 0x9
		"BL	sub_FF87E6C4 \n"
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF95FAC0 \n"
    );
}

//     sub_FF878688 -> sub_FF87E2B0
// Extracted method: ff87e2b0-ff87e61c
// Overridden calls:
//     sub_FF8785AC -> sub_FF87E1C8
//     sub_FF878B58 -> sub_FF87E780
//     sub_FF878C50 -> sub_FF87E87C
void __attribute__((naked,noinline)) sub_FF87E2B0_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, r7, r8, lr} \n"
		"mov	r7, r1 \n"
		"mov	r4, r0 \n"
		"BL	sub_FF87E6DC \n"
		"ldr	r5,  =0x00005e68 \n"
		"ldr	r3,  =0x0000201f \n"
		"ldr	ip, [r5] \n"
		"ldr	r2,  =0x00004008 \n"
		"ldr	r6,  =0x000009a3 \n"
		"ldr	r0,  =0x00003007 \n"
		"ldr	r1,  =0x00001051 \n"
		"cmp	ip, #9	\n" // ; 0x9
		"sub	lr, r3, #21	\n" // ; 0x15
		"addls	pc, pc, ip, lsl #2 \n"
		"B	loc_FF87E618 \n"
		"B	loc_FF87E314 \n"
		"B	loc_FF87E324 \n"
		"B	loc_FF87E334 \n"
		"B	loc_FF87E3A8 \n"
		"B	loc_FF87E3E8 \n"
		"B	loc_FF87E478 \n"
		"B	loc_FF87E514 \n"
		"B	loc_FF87E560 \n"
		"B	loc_FF87E524 \n"
		"B	loc_FF87E588 \n"
	"loc_FF87E314:\n"
		"mov	r1, r7 \n"
		"mov	r0, r4 \n"
		"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
		"B	sub_FF87E224 \n"
	"loc_FF87E324:\n"
		"mov	r1, r7 \n"
		"mov	r0, r4 \n"
		"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
//	"B	sub_FF87E87C \n"
	"B	sub_FF87E87C_my \n" // ------------------------------>
	"loc_FF87E334:\n"
		"cmp	r4, r1 \n"
		"BEQ	loc_FF87E398 \n"
		"sub	ip, r4, #8192	\n" // ; 0x2000
		"subs	ip, ip, #6	\n" // ; 0x6
		"BEQ	loc_FF87E35C \n"
		"cmp	r4, r0 \n"
		"BEQ	loc_FF87E3A0 \n"
		"sub	ip, r4, #12544	\n" // ; 0x3100
		"subs	ip, ip, #75	\n" // ; 0x4b
		"BNE	loc_FF87E618 \n"
	"loc_FF87E35C:\n"
		"BL	sub_FF87D630 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF87E6C4 \n"
		"ldr	r0, [r5, #8] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r1, #0	\n" // ; 0x0
		"movne	r0, r6 \n"
		"BNE	loc_FF87E390 \n"
		"ldr	r0, [r5, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87E5C8 \n"
		"ldr	r0,  =0x000009a1 \n"
		"mov	r1, #0	\n" // ; 0x0
	"loc_FF87E390:\n"
		"BL	sub_FF87E224 \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E398:\n"
		"BL	sub_FF87E7D0 \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E3A0:\n"
		"BL	sub_FF87E808 \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E3A8:\n"
		"sub	ip, r4, #2304	\n" // ; 0x900
		"subs	ip, ip, #162	\n" // ; 0xa2
		"BEQ	loc_FF87E3D8 \n"
		"cmp	r4, r6 \n"
		"BEQ	loc_FF87E3D0 \n"
		"cmp	r4, r1 \n"
		"BEQ	loc_FF87E3E0 \n"
		"cmp	r4, r0 \n"
		"BLEQ	sub_FF87E808 \n"
		"B	loc_FF87E618 \n"

	"loc_FF87E3D0:\n"
//	"BL	sub_FF87E1C8 \n"
	"BL	sub_FF87E1C8_my \n" // --------------------->
		"B	loc_FF87E618 \n"

	"loc_FF87E3D8:\n"
		"BL	sub_FF87E7AC \n"
		"B	loc_FF87E618 \n"
	"loc_FF87E3E0:\n"
		"BL	sub_FF87E7D0 \n"
		"B	loc_FF87E618 \n"
	"loc_FF87E3E8:\n"
		"cmp	r4, lr \n"
		"BEQ	loc_FF87E458 \n"
		"BGT	loc_FF87E418 \n"
		"cmp	r4, r6 \n"
		"subne	ip, r4, #2304	\n" // ; 0x900
		"subnes	ip, ip, #165	\n" // ; 0xa5
		"BEQ	loc_FF87E434 \n"
		"cmp	r4, r1 \n"
		"BNE	loc_FF87E618 \n"
		"BL	sub_FF827428 \n"
		"BL	sub_FF87E858 \n"
		"B	loc_FF87E51C \n"
	"loc_FF87E418:\n"
		"cmp	r4, r3 \n"
		"BEQ	loc_FF87E44C \n"
		"cmp	r4, r0 \n"
		"BEQ	loc_FF87E464 \n"
	"loc_FF87E428:\n"
		"cmp	r4, r2 \n"
		"BNE	loc_FF87E618 \n"
		"B	loc_FF87E458 \n"
	"loc_FF87E434:\n"
		"BL	sub_FF827428 \n"
		"mov	r0, #5	\n" // ; 0x5
		"BL	sub_FF87E6C4 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r5, #12] \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E44C:\n"
		"mov	r0, #5	\n" // ; 0x5
		"BL	sub_FF87E6C4 \n"
		"B	loc_FF87E508 \n"
	"loc_FF87E458:\n"
		"BL	sub_FF87E858 \n"
		"BL	sub_FF87E7AC \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E464:\n"
		"BL	sub_FF827428 \n"
		"BL	sub_FF87E858 \n"
		"B	loc_FF87E558 \n"
	"loc_FF87E470:\n"
		"BL	sub_FF87E6C4 \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E478:\n"
		"cmp	r4, r3 \n"
		"BEQ	loc_FF87E508 \n"
		"BGT	loc_FF87E498 \n"
		"cmp	r4, r1 \n"
		"BEQ	loc_FF87E51C \n"
		"cmp	r4, lr \n"
		"BEQ	loc_FF87E458 \n"
		"B	loc_FF87E618 \n"
	"loc_FF87E498:\n"
		"cmp	r4, r0 \n"
		"BNE	loc_FF87E428 \n"
		"B	loc_FF87E558 \n"
	// strings ...
	"loc_FF87E508:\n"
		"mov	r0, r7 \n"
		"BL	sub_FF87E824 \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E514:\n"
		"cmp	r4, r1 \n"
		"BNE	loc_FF87E618 \n"
	"loc_FF87E51C:\n"
		"mov	r0, #8	\n" // ; 0x8
		"B	loc_FF87E470 \n"
	"loc_FF87E524:\n"
		"cmp	r4, r0 \n"
		"BEQ	loc_FF87E558 \n"
		"BGT	loc_FF87E544 \n"
		"cmp	r4, lr \n"
		"BEQ	loc_FF87E398 \n"
		"cmp	r4, r3 \n"
		"BEQ	loc_FF87E508 \n"
		"B	loc_FF87E618 \n"
	"loc_FF87E544:\n"
		"cmp	r4, r2 \n"
		"subne	ip, r4, #16384	\n" // ; 0x4000
		"subnes	ip, ip, #14	\n" // ; 0xe
		"BEQ	loc_FF87E398 \n"
		"B	loc_FF87E618 \n"
	"loc_FF87E558:\n"
		"mov	r0, #7	\n" // ; 0x7
		"B	loc_FF87E470 \n"
	"loc_FF87E560:\n"
		"cmp	r4, lr \n"
		"BEQ	loc_FF87E578 \n"
		"cmp	r4, r3 \n"
		"BEQ	loc_FF87E508 \n"
		"cmp	r4, r2 \n"
		"BNE	loc_FF87E618 \n"
	"loc_FF87E578:\n"
		"BL	sub_FF87E7AC \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF87D7F8 \n"
		"B	loc_FF87E5C8 \n"
	"loc_FF87E588:\n"
		"sub	ip, r4, #2048	\n" // ; 0x800
		"subs	ip, ip, #74	\n" // ; 0x4a
		"BEQ	loc_FF87E5D0 \n"
		"cmp	r4, r1 \n"
		"BEQ	loc_FF87E608 \n"
		"cmp	r4, r0 \n"
		"BEQ	loc_FF87E5F8 \n"
		"sub	ip, r4, #12544	\n" // ; 0x3100
		"subs	ip, ip, #42	\n" // ; 0x2a
		"BNE	loc_FF87E618 \n"
		"BL	sub_FF87E764 \n"
		"ldr	r0, [r5, #20] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87E5C8 \n"
//	"BL	sub_FF87E780 \n"
	"BL	sub_FF87E780_my \n" // ------------------------->
		"BL	sub_FF960BC0 \n"
	"loc_FF87E5C8:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	"loc_FF87E5D0:\n"
		"BL	sub_FF87E764 \n"
		"ldr	r0,  =0x00008007 \n"
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF8741BC \n" // <j_PTM_SetCurrentItem -42016>
		"BL	sub_FF95FC04 \n"
		"BL	sub_FF87E7AC \n"
		"BL	sub_FF960BC0 \n"
		"BL	sub_FF87D630 \n"
		"mov	r0, #0	\n" // ; 0x0
		"B	loc_FF87E470 \n"
	"loc_FF87E5F8:\n"
		"BL	sub_FF87E764 \n"
		"BL	sub_FF95FC04 \n"
		"BL	sub_FF960BC0 \n"
		"B	loc_FF87E3A0 \n"
	"loc_FF87E608:\n"
		"BL	sub_FF87E764 \n"
		"BL	sub_FF95FC04 \n"
		"BL	sub_FF960BC0 \n"
		"B	loc_FF87E398 \n"
	"loc_FF87E618:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	);
}

// sub_FF878C50 -> sub_FF87E87C
// Extracted method: (ff87e87c-ff87e93c)
// Overridden calls:
//     sub_FF8785AC -> sub_FF87E1C8
void __attribute__((naked,noinline)) sub_FF87E87C_my() {
    asm volatile (
		"ldr	r3,  =0x00005e68 \n"
		"ldr	ip,  =0x00002006 \n"
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, [r3, #12] \n"
		"ldr	r2, [r3, #20] \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF87E8F0 \n"
		"BGT	loc_FF87E8BC \n"
		"sub	ip, r0, #2304	\n" // ; 0x900
		"subs	ip, ip, #162	\n" // ; 0xa2
		"BEQ	loc_FF87E914 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #81	\n" // ; 0x51
		"BNE	loc_FF87E938 \n"
		"BL	sub_FF87E7D0 \n"
		"B	loc_FF87E930 \n"
	"loc_FF87E8BC:\n"
		"sub	ip, r0, #12288	\n" // ; 0x3000
		"subs	ip, ip, #7	\n" // ; 0x7
		"BEQ	loc_FF87E92C \n"
		"sub	ip, r0, #12544	\n" // ; 0x3100
		"subs	ip, ip, #75	\n" // ; 0x4b
		"BNE	loc_FF87E938 \n"
		"cmp	r2, #0	\n" // ; 0x0
		"BNE	loc_FF87E930 \n"
		"ldr	r0, [r3, #8] \n"
		"orrs	r0, r0, r1 \n"
		"BEQ	loc_FF87E8FC \n"
//	"BL	sub_FF87E1C8 \n"
//	"BL	sub_FF87E1C8_my \n" // ---------------------->
		"B	loc_FF87E930 \n"
	"loc_FF87E8F0:\n"
		"cmp	r2, #0	\n" // ; 0x0
		"BLEQ	sub_FF87CB10 \n"
		"B	loc_FF87E930 \n"
	"loc_FF87E8FC:\n"
		"ldr	r0, [r3, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r0, #3	\n" // ; 0x3
		"BNE	loc_FF87E924 \n"
		"BL	sub_FF87E7AC \n"
		"B	loc_FF87E930 \n"
	"loc_FF87E914:\n"
		"cmp	r1, #0	\n" // ; 0x0
		"BNE	loc_FF87E930 \n"
		"BL	sub_FF826EA4 \n"
		"mov	r0, #2	\n" // ; 0x2
	"loc_FF87E924:\n"
		"BL	sub_FF87E6C4 \n"
		"B	loc_FF87E930 \n"
	"loc_FF87E92C:\n"
		"BL	sub_FF87E808 \n"
	"loc_FF87E930:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
	"loc_FF87E938:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, pc} \n"
    );
}

// sub_FF877C0C -> sub_FF87D834
// Extracted method:
// Overridden calls:
//     sub_FF877AA4 -> sub_FF87D6CC
//     sub_FF878688 -> sub_FF87E2B0
void __attribute__((naked,noinline)) sub_FF87D834_my() {
    asm volatile (
		"stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr} \n"
		"ldr	r5,  =0x00005e18 \n"
		"mov	r4, r1 \n"
		"ldr	r1, [r5, #44] \n"
		"add	r0, r5, #0	\n" // ; 0x0
		"ldr	r0, [r0, #20] \n"
		"ldr	fp,  =0x00003007 \n"
		"ldr	sl,  =0x000009a5 \n"
		"cmp	r1, #0	\n" // ; 0x0
		"mov	r9, r3 \n"
		"mvn	r8, #0	\n" // ; 0x0
		"BEQ	loc_FF87D8D8 \n"
		"cmp	r4, fp \n"
		"BEQ	loc_FF87DB68 \n"
		"cmp	r4, #2048	\n" // ; 0x800
		"ldreq	r1, [r5, #60] \n"
		"moveq	r4, r5 \n"
		"cmpeq	r9, r1 \n"
		"BNE	loc_FF87DCB8 \n"
		"mov	r1, #0	\n" // ; 0x0
		"str	r1, [r4, #44] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"str	r8, [r4, #60] \n"
		"BNE	loc_FF87D8B0 \n"
		"BL	sub_FF82AD44 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF87D8AC \n"
		"BL	sub_FF82AD4C \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87D8B0 \n"
	"loc_FF87D8AC:\n"
		"BL	sub_FF87D65C \n"
	"loc_FF87D8B0:\n"
		"ldr	r0, [r4, #72] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87D8C8 \n"
		"BL	sub_FF82AD54 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87DC1C \n"
	"loc_FF87D8C8:\n"
		"BL	sub_FF87D65C \n"
		"mov	r1, #1	\n" // ; 0x1
		"mov	r0, sl \n"
		"B	loc_FF87DC54 \n"
	"loc_FF87D8D8:\n"
		"cmp	r0, #1	\n" // ; 0x1
		"subeq	ip, r4, #8192	\n" // ; 0x2000
		"subeqs	ip, ip, #28	\n" // ; 0x1c
		"BNE	loc_FF87D8F4 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF87E0A4 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87D8F4:\n"
		"BL	sub_FF8719F0 \n"
		"ldr	r6,  =0x000009a1 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"add	r7, r6, #2	\n" // ; 0x2
		"BNE	loc_FF87D924 \n"
		"cmp	r4, sl \n"
		"cmpne	r4, r6 \n"
		"cmpne	r4, r7 \n"
		"BNE	loc_FF87D924 \n"
		"BL	sub_FF870B94 \n"
		"str	r4, [r5, #64] \n"
		"B	loc_FF87DCB8 \n"
	"loc_FF87D924:\n"
		"BL	sub_FF960BB4 \n" // <GetAEIntegralServiceMode_7 +930448>
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87D944 \n"
		"mov	r0, r4 \n"
		"BL	sub_FF872C88 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"cmpne	r4, sl \n"
		"BEQ	loc_FF87DCB8 \n"
	"loc_FF87D944:\n"
		"BL	sub_FF82AE4C \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87D95C \n"
		"cmp	r4, r6 \n"
		"cmpne	r4, r7 \n"
		"BEQ	loc_FF87DC1C \n"
	"loc_FF87D95C:\n"
		"BL	sub_FF87A108 \n"
		"ldr	r1,  =0x000009a2 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"add	r2, r1, #2	\n" // ; 0x2
		"BNE	loc_FF87D984 \n"
		"cmp	r4, r6 \n"
		"cmpne	r4, r1 \n"
		"cmpne	r4, r7 \n"
		"cmpne	r4, r2 \n"
		"BEQ	loc_FF87DC1C \n"
	"loc_FF87D984:\n"
		"sub	ip, r4, #2048	\n" // ; 0x800
		"subs	ip, ip, #87	\n" // ; 0x57
		"BNE	loc_FF87D9AC \n"
		"ldr	r0, [r5, #16] \n"
		"ldr	r1, [r5, #20] \n"
		"orr	r0, r0, r1 \n"
		"ldr	r1, [r5, #28] \n"
		"orrs	r0, r0, r1 \n"
		"BLEQ	sub_FF99D95C \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87D9AC:\n"
		"ldr	ip,  =0x000009a5 \n"
		"mov	sl, #1	\n" // ; 0x1
		"cmp	r4, ip \n"
		"BEQ	loc_FF87DC3C \n"
		"BGT	loc_FF87DA64 \n"
		"ldr	ip,  =0x00000907 \n"
		"cmp	r4, ip \n"
		"moveq	r1, #2	\n" // ; 0x2
		"BEQ	loc_FF87DC34 \n"
		"BGT	loc_FF87DA40 \n"
		"ldr	ip,  =0x00000829 \n"
		"ldr	r6,  =0x00002003 \n"
		"cmp	r4, ip \n"
		"BEQ	loc_FF87DBA8 \n"
		"BGT	loc_FF87DA14 \n"
		"cmp	r4, #2048	\n" // ; 0x800
		"BEQ	loc_FF87DB38 \n"
		"sub	ip, r4, #2048	\n" // ; 0x800
		"subs	ip, ip, #38	\n" // ; 0x26
		"BNE	loc_FF87DCD0 \n"
		"BL	sub_FF87A108 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87DB7C \n"
		"mov	r0, r4 \n"
		"BL	sub_FF87A6D4 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DA14:\n"
		"cmp	r4, #2144	\n" // ; 0x860
		"BEQ	loc_FF87DBF8 \n"
		"sub	ip, r4, #2048	\n" // ; 0x800
		"subs	ip, ip, #97	\n" // ; 0x61
		"BNE	loc_FF87DCD0 \n"
		"BL	sub_FF87E1A8 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87DCB8 \n"
		"ldr	r0,  =0x000009a6 \n"
		"mov	r1, r9 \n"
		"B	loc_FF87DC74 \n"
	"loc_FF87DA40:\n"
		"cmp	r4, r6 \n"
		"BEQ	loc_FF87DC4C \n"
		"cmp	r4, r1 \n"
		"BEQ	loc_FF87DD1C \n"
		"cmp	r4, r7 \n"
		"BEQ	loc_FF87DC4C \n"
		"cmp	r4, r2 \n"
		"BEQ	loc_FF87DD1C \n"
		"B	loc_FF87DCD0 \n"
	"loc_FF87DA64:\n"
		"ldr	ip,  =0x00003149 \n"
		"cmp	r4, ip \n"
		"moveq	r1, #0	\n" // ; 0x0
		"moveq	r0, #132	\n" // ; 0x84
		"BEQ	loc_FF87DCC8 \n"
		"BGT	loc_FF87DAD0 \n"
		"cmp	r4, fp \n"
		"BEQ	loc_FF87DB58 \n"
		"BGT	loc_FF87DAAC \n"
		"sub	ip, r4, #8192	\n" // ; 0x2000
		"subs	ip, ip, #10	\n" // ; 0xa
		"BEQ	loc_FF87DD1C \n"
		"sub	ip, r4, #8192	\n" // ; 0x2000
		"subs	ip, ip, #32	\n" // ; 0x20
		"BNE	loc_FF87DCD0 \n"
		"mov	r1, r9 \n"
		"mov	r0, #131	\n" // ; 0x83
		"B	loc_FF87DCC8 \n"
	"loc_FF87DAAC:\n"
		"sub	ip, r4, #12544	\n" // ; 0x3100
		"subs	ip, ip, #53	\n" // ; 0x35
		"BEQ	loc_FF87DB0C \n"
		"sub	ip, r4, #12288	\n" // ; 0x3000
		"subs	ip, ip, #328	\n" // ; 0x148
		"BNE	loc_FF87DCD0 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #134	\n" // ; 0x86
		"B	loc_FF87DCC8 \n"
	"loc_FF87DAD0:\n"
		"sub	ip, r4, #12544	\n" // ; 0x3100
		"subs	ip, ip, #74	\n" // ; 0x4a
		"BEQ	loc_FF87DCC0 \n"
		"sub	ip, r4, #16384	\n" // ; 0x4000
		"subs	ip, ip, #3	\n" // ; 0x3
		"BEQ	loc_FF87DC7C \n"
		"sub	ip, r4, #16384	\n" // ; 0x4000
		"subs	ip, ip, #8	\n" // ; 0x8
		"BEQ	loc_FF87DC5C \n"
		"sub	ip, r4, #16384	\n" // ; 0x4000
		"subs	ip, ip, #15	\n" // ; 0xf
		"BNE	loc_FF87DCD0 \n"
		"mov	r0, #130	\n" // ; 0x82
		"BL	sub_FF87EC10 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DB0C:\n"
		"BL	sub_FF87E654 \n" // <GetVRAMHPixelsSize_1 +2888>
		"cmp	r0, #4	\n" // ; 0x4
		"BEQ	loc_FF87DD1C \n"
		"ldr	r0, [r5, #28] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87DC1C \n"
		"ldr	r0, [r5, #72] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLNE	sub_FF87D630 \n"
		"BL	sub_FF87D584 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DB38:\n"
		"ldr	r0, [r5, #76] \n"
		"cmp	r9, r0 \n"
		"BNE	loc_FF87DCB8 \n"
		"ldr	r1, =0xff87dd4c \n" // ; (4369764d)  *"MviCon_ClrEvt"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"str	r8, [r5, #76] \n"
		"B	loc_FF87DCB8 \n"
	"loc_FF87DB58:\n"
		"str	sl, [r5, #28] \n"
		"ldr	r0, [r5, #24] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87DB70 \n"
	"loc_FF87DB68:\n"
		"BL	sub_FF87D584 \n"
		"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
	"loc_FF87DB70:\n"
		"mov	r0, r4 \n"
		"BL	sub_FF87D7F8 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DB7C:\n"
		"ldr	r0, [r5, #16] \n"
		"ldr	r1, [r5, #20] \n"
		"orr	r0, r0, r1 \n"
		"ldr	r1, [r5, #28] \n"
		"orrs	r0, r0, r1 \n"
		"BNE	loc_FF87DC1C \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, r6 \n"
		"BL	sub_FF85B064 \n"
		"BL	sub_FF94CB38 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DBA8:\n"
		"ldr	r0, [r5, #16] \n"
		"ldr	r1, [r5, #20] \n"
		"orrs	r0, r0, r1 \n"
		"BNE	loc_FF87DC1C \n"
		"BL	sub_FF87A6E0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldreq	r0, [r5, #28] \n"
		"cmpeq	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87DC1C \n"
		"BL	sub_FF87A108 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87DC1C \n"
		"BL	sub_FF96CF94 \n" // <j_IsEvfDriveMode_16 +979900>
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87DC1C \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, r6 \n"
		"BL	sub_FF85B064 \n"
		"BL	sub_FF947A8C \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DBF8:\n"
		"BL	sub_FF87E1A8 \n"
		"cmp	r0, #2	\n" // ; 0x2
		"BEQ	loc_FF87DCB8 \n"
		"BL	sub_FF87E1A8 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87DCB8 \n"
		"ldr	r0, [r5, #76] \n"
		"cmn	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF87DC24 \n"
	"loc_FF87DC1C:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
	"loc_FF87DC24:\n"
		"ldr	r0, [r5, #52] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"streq	sl, [r5, #56] \n"
	"loc_FF87DC30:\n"
		"mov	r1, #1	\n" // ; 0x1
	"loc_FF87DC34:\n"
		"ldr	r0,  =0x000009a5 \n"
		"B	loc_FF87DC54 \n"
	"loc_FF87DC3C:\n"
		"ldr	r0, [r5, #76] \n"
		"cmn	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF87DC30 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DC4C:\n"
		"mov	r1, #1	\n" // ; 0x1
		"mov	r0, r4 \n"

	"loc_FF87DC54:\n"
//	"BL	sub_FF87D6CC \n"
	"BL	sub_FF87D6CC_my \n" // ------------------>

		"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
	"loc_FF87DC5C:\n"
		"mov	r0, r9 \n"
		"BL	sub_FF87882C \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87DCB8 \n"
		"mov	r1, r9 \n"
		"mov	r0, r4 \n"

	"loc_FF87DC74:\n"
//	"BL	sub_FF87E2B0 \n"
	"BL	sub_FF87E2B0_my \n" // -------------------->
		"B	loc_FF87DCB8 \n"

	"loc_FF87DC7C:\n"
		"ldr	r0, [r5, #64] \n"
		"cmn	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF87DCB8 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF86D7EC \n"
		"ldr	r0, [r5, #64] \n"
		"cmp	r0, r6 \n"
		"BNE	loc_FF87DCA8 \n"
		"BL	sub_FF82AD44 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87DCB4 \n"
	"loc_FF87DCA8:\n"
		"ldr	r0, [r5, #64] \n"
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF872F04 \n" // <PostLogicalEventForNotPowerType -44460>
	"loc_FF87DCB4:\n"
		"str	r8, [r5, #64] \n"
	"loc_FF87DCB8:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
	"loc_FF87DCC0:\n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #133	\n" // ; 0x85
	"loc_FF87DCC8:\n"
		"BL	sub_FF87EBD0 \n"
		"B	loc_FF87DC1C \n"
	"loc_FF87DCD0:\n"
		"ldr	ip,  =0x00000855 \n"
		"cmp	r4, ip \n"
		"BEQ	loc_FF87DD0C \n"
		"BGT	loc_FF87DCF8 \n"
		"sub	ip, r4, #2048	\n" // ; 0x800
		"subs	ip, ip, #56	\n" // ; 0x38
		"subne	ip, r4, #2048	\n" // ; 0x800
		"subnes	ip, ip, #57	\n" // ; 0x39
		"BNE	loc_FF87DD1C \n"
		"B	loc_FF87DD0C \n"
	"loc_FF87DCF8:\n"
		"sub	ip, r4, #2048	\n" // ; 0x800
		"subs	ip, ip, #86	\n" // ; 0x56
		"subne	ip, r4, #2048	\n" // ; 0x800
		"subnes	ip, ip, #93	\n" // ; 0x5d
		"BNE	loc_FF87DD1C \n"
	"loc_FF87DD0C:\n"
		"ldr	r0, [r5, #16] \n"
		"ldr	r1, [r5, #20] \n"
		"orrs	r0, r0, r1 \n"
		"BNE	loc_FF87DC1C \n"
	"loc_FF87DD1C:\n"
		"mov	r1, r9 \n"
		"mov	r0, r4 \n"
//	"BL	sub_FF87E2B0 \n"
	"BL	sub_FF87E2B0_my \n" // -------------------->
		"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
        ".ltorg\n" // make literal pool
    );
}

// sub_FF877AA4 -> sub_FF87D6CC
// Extracted method: (ff87d6cc-ff87d794)
// Overridden calls:
//     sub_FF878688 -> sub_FF87E2B0
void __attribute__((naked,noinline)) sub_FF87D6CC_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"mov	r4, r0 \n"
		"ldr	r0,  =0x00005e18 \n"
		"mov	r5, r1 \n"
		"ldr	r0, [r0, #28] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r1, =0xff87d7d4 \n" // ; (4369764d)  *"MviCon_fShtDwn"
		"BNE	loc_FF87D780 \n"
		"BL	sub_FF87E660 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87D708 \n"
	"loc_FF87D6F8:\n"
		"mov	r0, r4 \n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"mov	r1, #0	\n" // ; 0x0
//	"B	sub_FF87E2B0 \n"
	"B	sub_FF87E2B0_my \n" // ----------------->
	"loc_FF87D708:\n"
		"cmp	r5, #2	\n" // ; 0x2
		"BNE	loc_FF87D720 \n"
		"BL	sub_FF87E090 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87D770 \n"
		"B	loc_FF87D73C \n"
	"loc_FF87D720:\n"
		"cmp	r5, #1	\n" // ; 0x1
		"BNE	loc_FF87D770 \n"
		"ldr	r0,  =0x00000a24 \n"
		"BL	sub_FF87CEB8 \n"
		"BL	sub_FF87CAF0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87D770 \n"
	"loc_FF87D73C:\n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF86D7EC \n"
		"sub	ip, r4, #2304	\n" // ; 0x900
		"subs	ip, ip, #161	\n" // ; 0xa1
		"subne	ip, r4, #2304	\n" // ; 0x900
		"subnes	ip, ip, #163	\n" // ; 0xa3
		"subne	ip, r4, #2304	\n" // ; 0x900
		"subnes	ip, ip, #165	\n" // ; 0xa5
		"ldreq	r0,  =0x0000c507 \n"
		"moveq	r1, #0	\n" // ; 0x0
		"BLEQ	sub_FF85B064 \n"
	"loc_FF87D768:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, r5, r6, pc} \n"
	"loc_FF87D770:\n"
		"BL	sub_FF87D65C \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87D78C \n"
		"ldr	r1, =0xff87d7e4 \n" // ; (4369764d)  *"MviCon_InitChkBuf"
	"loc_FF87D780:\n"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"B	loc_FF87D768 \n"
	"loc_FF87D78C:\n"
		"mov	r0, r5 \n"
		"BL	sub_FF95FC50 \n"
		"B	loc_FF87D6F8 \n"
    );
}

// Extracted method: (ff87dd60-ff87ddd4)
// Overridden calls:
//     sub_FF877C0C -> sub_FF87D834
void __attribute__((naked,noinline)) sub_FF87DD60_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x00005e18 \n"
		"mov	r1, #0	\n" // ; 0x0
		"cmp	r0, #0	\n" // ; 0x0
		"str	r1, [r4, #48] \n"
		"BEQ	loc_FF87DD88 \n"
		"BL	sub_FF877CEC \n"
		"BL	sub_FF87E044 \n"
		"mov	r0, #1	\n" // ; 0x1
		"str	r0, [r4, #72] \n"
	"loc_FF87DD88:\n"
		"ldr	r0, [r4, #8] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87DDA4 \n"
//	"ldr	r0,  =0xff87d834 \n"
	"ldr	r0,  =sub_FF87D834_my \n" // ----------------->
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF872748 \n" // <CreateController -46676>
		"str	r0, [r4, #8] \n"
	"loc_FF87DDA4:\n"
		"ldr	r0, [r4, #12] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87DDC0 \n"
		"ldr	r0,  =0xff87d488 \n"
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF87A4F8 \n"
		"str	r0, [r4, #12] \n"
	"loc_FF87DDC0:\n"
		"BL	sub_FF87E620 \n"
		"BL	sub_FF87D4EC \n"
		"BL	sub_FF96B058 \n"
		"BL	sub_FF96D620 \n"
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF961C54 \n"
    );
}

// sub_FF875018 -> sub_FF87AA88
// Extracted method: (ff87aa88-ff87aab0)
// Overridden calls:
//     sub_FF878138 -> sub_FF87DD60
void __attribute__((naked,noinline)) sub_FF87AA88_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff87abec \n" // ; (6174535f)  *"_StartMovie"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"ldr	r4,  =0x00005c4c \n"
		"ldr	r0, [r4, #40] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLNE	sub_FF87B52C \n"
		"ldr	r0, [r4, #76] \n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF87DD60 \n"
	"B	sub_FF87DD60_my \n" // -------------------->
    );
}

// Extracted method: (ff878e44-ff879000)
// Overridden calls:
//     sub_FF875018 -> sub_FF87AA88
void __attribute__((naked,noinline)) sub_FF878E44_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"mov	r5, r0 \n"
		"mov	r4, r1 \n"
		"ldr	r1, =0xff879060 \n" // ; (6365445f)  *"_DecideCaptureMode"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"ldr	r6,  =0x00005c4c \n"
		"ldr	r0, [r6, #16] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF878FFC \n"
		"ldr	r0, [r6, #24] \n"
		"ldr	r1,  =0x0000820a \n"
		"ldr	r2,  =0xfffe0000 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF878EC4 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"ldmeqia	sp!, {r4, r5, r6, pc} \n"
		"cmp	r4, #0	\n" // ; 0x0
		"BNE	loc_FF878EC4 \n"
		"cmp	r5, r1 \n"
		"BNE	loc_FF878EA4 \n"
		"BL	sub_FF87ACAC \n"
		"BL	sub_FF87A9E0 \n"
		"B	loc_FF878FFC \n"
	"loc_FF878EA4:\n"
		"cmp	r2, r5, lsl #17 \n"
		"tstne	r5, #3072	\n" // ; 0xc00
		"BEQ	loc_FF878EB8 \n"
//	"BL	sub_FF87AA88 \n"
	"BL	sub_FF87AA88_my \n" // ------------->
		"B	loc_FF878EBC \n"
	"loc_FF878EB8:\n"
		"BL	sub_FF87AA3C \n"
	"loc_FF878EBC:\n"
		"BL	sub_FF87ACAC \n"
		"B	loc_FF878FFC \n"
	"loc_FF878EC4:\n"
		"cmp	r5, r1 \n"
		"BNE	loc_FF878F18 \n"
		"ldrh	r0, [r6, #2] \n"
		"cmp	r0, r1 \n"
		"BEQ	loc_FF878FF4 \n"
		"cmp	r2, r0, lsl #17 \n"
		"tstne	r0, #3072	\n" // ; 0xc00
		"BEQ	loc_FF878EFC \n"
		"ldr	r1, =0xff879080 \n" // ; (766f4d5f)  *"_MovieToStitch"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BEQ	loc_FF878FCC \n"
		"B	loc_FF878F10 \n"
	"loc_FF878EFC:\n"
		"ldr	r1, =0xff879090 \n" // ; (6974535f)  *"_StillToStitch"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BEQ	loc_FF878FE8 \n"
	"loc_FF878F10:\n"
		"BL	sub_FF87A9E0 \n"
		"B	loc_FF878FF4 \n"
	"loc_FF878F18:\n"
		"cmp	r2, r5, lsl #17 \n"
		"ldrh	r0, [r6, #2] \n"
		"tstne	r5, #3072	\n" // ; 0xc00
		"BEQ	loc_FF878F88 \n"
		"cmp	r0, r1 \n"
		"BNE	loc_FF878F48 \n"
		"ldr	r1, =0xff8790a0 \n" // ; (6974535f)  *"_StitchToMovie"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BEQ	loc_FF878FA4 \n"
		"B	loc_FF878F80 \n"
	"loc_FF878F48:\n"
		"cmp	r2, r0, lsl #17 \n"
		"tstne	r0, #3072	\n" // ; 0xc00
		"BEQ	loc_FF878F6C \n"
		"ldr	r1, =0xff8790b0 \n" // ; (766f4d5f)  *"_MovieToMovie"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BEQ	loc_FF878FCC \n"
		"B	loc_FF878F80 \n"
	"loc_FF878F6C:\n"
		"ldr	r1, =0xff8790c0 \n" // ; (6974535f)  *"_StillToMovie"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BEQ	loc_FF878FE8 \n"
	"loc_FF878F80:\n"
//	"BL	sub_FF87AA88 \n"
	"BL	sub_FF87AA88_my \n" // ------------->
		"B	loc_FF878FF4 \n"
	"loc_FF878F88:\n"
		"cmp	r0, r1 \n"
		"BNE	loc_FF878FAC \n"
		"ldr	r1, =0xff8790d0 \n" // ; (6974535f)  *"_StitchToStill"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BNE	loc_FF878FF0 \n"
	"loc_FF878FA4:\n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"B	sub_FF87AA10 \n"
	"loc_FF878FAC:\n"
		"cmp	r2, r0, lsl #17 \n"
		"tstne	r0, #3072	\n" // ; 0xc00
		"BEQ	loc_FF878FD4 \n"
		"ldr	r1, =0xff8790e0 \n" // ; (766f4d5f)  *"_MovieToStill"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BNE	loc_FF878FF0 \n"
	"loc_FF878FCC:\n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"B	sub_FF87AAB4 \n"
	"loc_FF878FD4:\n"
		"ldr	r1, =0xff8790f0 \n" // ; (6974535f)  *"_StillToStill"
		"mov	r0, #96	\n" // ; 0x60
		"BL	sub_FF86A150 \n"
		"cmp	r4, #1	\n" // ; 0x1
		"BNE	loc_FF878FF0 \n"
	"loc_FF878FE8:\n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"B	sub_FF87AA64 \n"
	"loc_FF878FF0:\n"
		"BL	sub_FF87AA3C \n"
	"loc_FF878FF4:\n"
		"cmp	r4, #0	\n" // ; 0x0
		"ldmneia	sp!, {r4, r5, r6, pc} \n"
	"loc_FF878FFC:\n"
		"strh	r5, [r6, #2] \n"
		"ldmia	sp!, {r4, r5, r6, pc} \n"
    );
}

// Extracted method: (ff87a1e8-ff87a328a)
// Overridden calls:
//     sub_FF8734F4 -> sub_FF878E44
void __attribute__((naked,noinline)) sub_FF87A1E8_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"ldr	r5,  =0x00005c4c \n"
		"mov	r4, #0	\n" // ; 0x0
		"ldrh	r0, [r5, #4] \n"
		"BL	sub_FF9625B8 \n"
		"BL	sub_FF960D6C \n"
		"BL	sub_FF964998 \n"
		"BL	sub_FF945EE8 \n"
		"BL	sub_FF962CF8 \n"
		"BL	sub_FF94A0A8 \n"
		"ldr	r0, [r5, #76] \n"
		"mov	r1, #3	\n" // ; 0x3
		"cmp	r0, #0	\n" // ; 0x0
		"strne	r1, [r5, #112] \n"
		"ldr	r2, [r5, #96] \n"
		"sub	ip, r2, #4096	\n" // ; 0x1000
		"subs	ip, ip, #91	\n" // ; 0x5b
		"cmpne	r0, #0	\n" // ; 0x0
		"ldr	r0, [r5, #88] \n"
		"movne	r4, #2	\n" // ; 0x2
		"cmp	r2, r0 \n"
		"BNE	loc_FF87A250 \n"
		"ldr	r0, [r5, #80] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r4, #3	\n" // ; 0x3
		"strne	r1, [r5, #112] \n"
	"loc_FF87A250:\n"
		"mov	r6, #0	\n" // ; 0x0
		"str	r6, [r5, #36] \n"
		"BL	sub_FF87AB70 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r0, r4 \n"
		"BLNE	sub_FF825988 \n"
		"BL	sub_FF94977C \n"
		"str	r6, [r5, #60] \n"
		"ldrh	r0, [r5, #4] \n"
		"mov	r1, #0	\n" // ; 0x0
//	"BL	sub_FF878E44 \n"
	"BL	sub_FF878E44_my \n" // -------->
		"BL	sub_FF87CAD8 \n"
		"ldr	r0, [r5, #116] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87A298 \n"
		"BL	sub_FF94FFF8 \n"
		"str	r6, [r5, #116] \n"
		"BL	sub_FF87A99C \n"
	"loc_FF87A298:\n"
		"ldr	r1, [r5, #112] \n"
		"mov	r0, #65	\n" // ; 0x41
		"BL	sub_FF87EBD0 \n"
		"BL	sub_FF87A99C \n"
		"BL	sub_FF960D5C \n"
		"BL	sub_FF95C2C0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLEQ	sub_FF960D70 \n"
		"BL	sub_FF962520 \n"
		"BL	sub_FF946C40 \n"
		"BL	sub_FF8724CC \n"
		"str	r0, [r5, #108] \n"
		"str	r6, [r5, #44] \n"
		"ldr	r0, [r5, #80] \n"
		"mov	r4, r5 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87A2F4 \n"
		"ldr	r0, [r4, #16] \n"
		"mov	r1, r4 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"mvneq	r0, #0	\n" // ; 0x0
		"streq	r0, [r1, #88] \n"
		"streq	r0, [r1, #96] \n"
	"loc_FF87A2F4:\n"
		"ldr	r0,  =0x00008003 \n"
		"str	r6, [r4, #80] \n"
		"BL	sub_FF8741C8 \n" // <PTM_GetCurrentItem -24884>
		"strh	r0, [r4] \n"
		"ldr	r0,  =0x0000313d \n"
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF872F50 \n" // <PostLogicalEventToUI -29628>
		"BL	sub_FF87AC7C \n"
		"ldr	r0, [r4, #48] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"streq	r6, [r4, #48] \n"
		"ldmeqia	sp!, {r4, r5, r6, lr} \n"
		"BEQ	sub_FF879970 \n"
		"ldmia	sp!, {r4, r5, r6, pc} \n"
    );
}

// Extracted method: ff87aae4-ff87ab6c
// Overridden calls:
//     sub_FF8734F4 -> sub_FF878E44
void __attribute__((naked,noinline)) sub_FF87AAE4_my() {
    asm volatile (
		"stmdb	sp!, {r3, r4, r5, lr} \n"
		"ldr	r4,  =0x00005c4c \n"
		"ldr	r0, [r4, #76] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF87AB14 \n"
		"ldr	r0, [r4, #96] \n"
		"ldr	r1, [r4, #88] \n"
		"cmp	r0, r1 \n"
		"BNE	loc_FF87AB1C \n"
		"ldr	r0, [r4, #80] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87AB1C \n"
	"loc_FF87AB14:\n"
		"mov	r0, #3	\n" // ; 0x3
		"str	r0, [r4, #112] \n"
	"loc_FF87AB1C:\n"
		"ldrh	r0, [r4, #4] \n"
		"mov	r1, sp \n"
		"strh	r0, [sp] \n"
		"ldr	r0, [r4, #112] \n"
		"strh	r0, [sp, #2] \n"
		"mov	r0, #64	\n" // ; 0x40
		"BL	sub_FF87EBD0 \n"
		"ldr	r0, [r4, #76] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87AB50 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF95C3C4 \n"
		"B	loc_FF87AB60 \n"
	"loc_FF87AB50:\n"
		"ldr	r0, [r4, #28] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldreqh	r0, [r4, #4] \n"
		"BLEQ	sub_FF8740A0 \n" // <PTM_SetCurrentCaptureMode -27324>
	"loc_FF87AB60:\n"
		"ldrh	r0, [r4, #4] \n"
		"mov	r1, #1	\n" // ; 0x1
//	"BL	sub_FF878E44 \n"
	"BL	sub_FF878E44_my \n" // -------------------------->
		"ldmia	sp!, {r3, r4, r5, pc} \n"
    );
}

// Extracted method: ff87a354-ff87a370
// Overridden calls:
//     sub_FF8747B0 -> ff87a114
//     sub_FF874884 -> ff87a1e8
void __attribute__((naked,noinline)) sub_FF87A354_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r0,  =0x00005cd8 \n"
//	"ldr	r1, =0xff87a114 \n" // ; (e92d4070)
	"ldr	r1, =sub_FF87A114_my \n" // ----------------->
		"BL	sub_FF880278 \n"
		"ldr	r1,  =0x00005c4c \n"
//	"ldr	r0, =0xff87a1e8 \n" // ; (e92d4070)
	"ldr	r0, =sub_FF87A1E8_my \n" // ----------------->
		"str	r0, [r1, #128] \n"
		"ldmia	sp!, {r4, pc} \n"
    );
}

// Extracted method: ff87a114 - ff87a1e4
// Overridden calls:
//     sub_FF875074 -> sub_FF87AAE4
void __attribute__((naked,noinline)) sub_FF87A114_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"ldr	r5,  =0x00005c4c \n"
		"mov	r4, #0	\n" // ; 0x0
		"ldr	r0, [r5, #96] \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #91	\n" // ; 0x5b
		"ldrne	r1, [r5, #76] \n"
		"cmpne	r1, #0	\n" // ; 0x0
		"ldr	r1, [r5, #88] \n"
		"movne	r4, #2	\n" // ; 0x2
		"cmp	r0, r1 \n"
		"BNE	loc_FF87A150 \n"
		"ldr	r0, [r5, #80] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r4, #3	\n" // ; 0x3
	"loc_FF87A150:\n"
		"BL	sub_FF87AB70 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87A174 \n"
		"cmp	r4, #0	\n" // ; 0x0
		"BNE	loc_FF87A174 \n"
		"ldr	r0, [r5, #60] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLEQ	sub_FF946DD0 \n"
		"BL	sub_FF96C924 \n"
	"loc_FF87A174:\n"
		"ldr	r0, [r5, #48] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF87A1A0 \n"
		"ldr	r1, =0xff87a378 \n" // ; (72505f5f)  *"__PrepareCaptureModeChange__"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r5, #48] \n"
		"str	r0, [r5, #44] \n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"B	sub_FF879970 \n"
	"loc_FF87A1A0:\n"
		"BL	sub_FF87AB70 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLNE	sub_FF8258A4 \n"
		"ldr	r0, [r5, #80] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r0, #1	\n" // ; 0x1
		"BLNE	sub_FF95C3C4 \n"
//	"BL	sub_FF87AAE4 \n"
	"BL	sub_FF87AAE4_my \n" // ------------------>
		"BL	sub_FF87AB70 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r5, #124] \n"
		"BLNE	sub_FF87AD64 \n"
		"mov	r0, #3	\n" // ; 0x3
		"str	r0, [r5, #124] \n"
		"ldr	r1, [r5, #128] \n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"mov	r0, #0	\n" // ; 0x0
		"bx	r1 \n"
    );
}

// Extracted method: ff87a3b4-ff87a3d4
// Overridden calls:
//     sub_FF8749E8 -> sub_FF87A354
void __attribute__((naked,noinline)) sub_FF87A3B4_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff87a5dc \n" // ; (7466415f)  *"_AfterCBRForPlay"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF8724CC \n"
		"ldr	r1,  =0x00005c4c \n"
		"str	r0, [r1, #108] \n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF87A354 \n"
	"B	sub_FF87A354_my \n" // ------------------->
    );
}

// Extracted method: ff87acb0-ff87acf8
// Overridden calls:
//     sub_FF8749E8
void __attribute__((naked,noinline)) sub_FF87ACB0_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r0,  =0x00000855 \n"
		"BL	sub_FF9587B0 \n"
		"BL	sub_FF82A3A0 \n"
//	"BL	sub_FF87A354 \n"
	"BL	sub_FF87A354_my \n" // ----------------->
		"BL	sub_FF95B868 \n"
		"BL	sub_FF94812C \n"
		"BL	sub_FF9642C0 \n"
		"BL	sub_FF9646DC \n"
		"BL	sub_FF96A868 \n"
		"BL	sub_FF96CC74 \n"
		"BL	sub_FF964908 \n"
		"BL	sub_FF9644C0 \n"
		"BL	sub_FF96B344 \n"
		"BL	sub_FF962B24 \n"
		"BL	sub_FF96A478 \n"
		"BL	sub_FF87ECB0 \n" // <taskcreate_DSITask +16320>
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF87EAE0 \n" // <taskcreate_FaceFrame +15848>
    );
}

// Extracted method: ff87a468-ff87a4ac
// Overridden calls:
//     sub_FF874A48 -> sub_FF87A3B4_my
void __attribute__((naked,noinline)) sub_FF87A468_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x00005c4c \n"
		"ldrh	r0, [r4, #4] \n"
		"BL	sub_FF8740A0 \n" // <PTM_SetCurrentCaptureMode -25556>
		"BL	sub_FF82AD0C \n" // <GetAEIntegralServiceMode_0 -325484>
		"sub	ip, r0, #16384	\n" // ; 0x4000
		"subs	ip, ip, #4	\n" // ; 0x4
		"ldmneia	sp!, {r4, pc} \n"
		"ldr	r0,  =0x00005cd8 \n"
		"ldr	r1, =0xff87a32c \n" // ; (e92d4010)
		"BL	sub_FF880278 \n"
//	"ldr	r0, =0xff87a3b4 \n" // ; (e92d4010)
	"ldr	r0, =sub_FF87A3B4_my \n" // ---------------->
		"str	r0, [r4, #128] \n"
		"BL	sub_FF87ADA8 \n"
		"ldr	r1,  =0x00005ce4 \n"
		"ldmia	sp!, {r4, lr} \n"
		"sub	r0, r1, #12	\n" // ; 0xc
		"B	sub_FF880224 \n"
    );
}

// Extracted method: ff87a57c-ff87a5d8
// Overridden calls:
//     sub_FF875294 -> sub_FF87ACB0
void __attribute__((naked,noinline)) sub_FF87A57C_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"ldr	r1, =0xff87a630 \n" // ; (72617453)  *"StartRecMode"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"ldr	r4,  =0x00005c4c \n"
		"mov	r0, #6	\n" // ; 0x6
		"mov	r5, #1	\n" // ; 0x1
		"str	r0, [r4, #112] \n"
		"str	r5, [r4, #16] \n"
		"BL	sub_FF95C14C \n"
		"BL	sub_FF962360 \n"
		"BL	sub_FF960BAC \n"
//	"BL	sub_FF87ACB0 \n"
	"BL	sub_FF87ACB0_my \n" // --------------------->
		"BL	sub_FF96B774 \n"
		"BL	sub_FF96AC30 \n"
		"mov	r0, #1	\n" // ; 0x1
		"str	r5, [r4, #24] \n"
		"BL	sub_FF87AD64 \n"
		"mov	r0, #3	\n" // ; 0x3
		"str	r0, [r4, #124] \n"
		"ldr	r1, [r4, #128] \n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"mov	r0, #0	\n" // ; 0x0
		"bx	r1 \n"
    );
}

// ff82a3b4
// Extracted method: (ff82a3b4-ff82a45c)
// Overridden calls:
//     sub_FF874AFC -> sub_FF87A468
void __attribute__((naked,noinline)) sub_FF82A3B4_my() {
	asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"mov	r6, r0, lsl #16 \n"
		"mov	r6, r6, lsr #16 \n"
		"mov	r4, r0 \n"
		"mov	r0, r6 \n"
		"BL	sub_FF873D58 \n"
		"ldr	r5,  =0x00001d28 \n"
		"cmp	r4, #128	\n" // ; 0x80
		"ldrne	r0, [r5, #12] \n"
		"cmpne	r0, r4 \n"
		"movne	r1, r4 \n"
		"movne	r0, #0	\n" // ; 0x0
		"BLNE	sub_FF8788AC \n"
		"ldr	ip,  =0x00004010 \n"
		"str	r4, [r5, #12] \n"
		"cmp	r4, ip \n"
		"BEQ	loc_FF82A440 \n"
		"BGT	loc_FF82A418 \n"
		"cmp	r4, #8	\n" // ; 0x8
		"BEQ	loc_FF82A434 \n"
		"cmp	r4, #128	\n" // ; 0x80
		"subne	ip, r4, #16384	\n" // ; 0x4000
		"subnes	ip, ip, #4	\n" // ; 0x4
		"BEQ	loc_FF82A440 \n"
		"B	loc_FF82A438 \n"
	"loc_FF82A418:\n"
		"sub	ip, r4, #16384	\n" // ; 0x4000
		"subs	ip, ip, #64	\n" // ; 0x40
		"cmpne	r4, #16640	\n" // ; 0x4100
		"BEQ	loc_FF82A440 \n"
		"sub	ip, r4, #32768	\n" // ; 0x8000
		"subs	ip, ip, #32	\n" // ; 0x20
		"BNE	loc_FF82A438 \n"
	"loc_FF82A434:\n"
//	"BL	sub_FF87A468 \n"
	"BL	sub_FF87A468_my \n" // ------------------->
	"loc_FF82A438:\n"
		"mov	r0, #2	\n" // ; 0x2
		"B	loc_FF82A448 \n"
	"loc_FF82A440:\n"
//	"BL	sub_FF87A468 \n"
	"BL	sub_FF87A468_my \n" // ------------------->
		"mov	r0, #0	\n" // ; 0x0
	"loc_FF82A448:\n"
		"BL	sub_FF820E4C \n"
		"mov	r0, r6 \n"
		"BL	sub_FF89193C \n"
		"BL	sub_FF820F74 \n" // <taskcreate_TempCheck -38112>
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"B	sub_FF8785EC \n"
        ".ltorg\n" // make literal pool
    );
}

// Extracted method: (ff876768-ff876794)
// Overridden calls:
//     sub_FF874C1C -> sub_FF87A57C
//     sub_FF86EE0C -> sub_FF875414
void __attribute__((naked,noinline)) sub_FF876768_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff876988 \n" // ; (453a4341)  *"AC:EntryRecBoot"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF82A5C8 \n"
		"BL	sub_FF8762D0 \n"
//	"BL	sub_FF87A57C \n"
	"BL	sub_FF87A57C_my \n" // ------------------------>
		"mov	r0, #1	\n" // ; 0x1
		"BL	sub_FF874CFC \n"
		"BL	sub_FF8751A4 \n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF875414 \n"
	"B	sub_FF875414_my \n" // ------------------------>
    );
}

// Extracted method: (ff875bf4-ff875d4c)
// Overridden calls:
// . . .
void __attribute__((naked,noinline)) sub_FF875BF4_my() {
	asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"sub	ip, r0, #8192	\n" // ; 0x2000
		"ldr	r5,  =0x000059c0 \n"
		"subs	ip, ip, #4	\n" // ; 0x4
		"mov	r4, #1	\n" // ; 0x1
		"BEQ	loc_FF875C20 \n"
		"sub	ip, r0, #12800	\n" // ; 0x3200
		"subs	ip, ip, #2	\n" // ; 0x2
		"movne	r0, #1	\n" // ; 0x1
		"ldmneia	sp!, {r4, r5, r6, pc} \n"
		"str	r4, [r5, #152] \n"
	"loc_FF875C20:\n"
		"ldr	r0, [r5, #44] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF875D48 \n"
		"ldr	r0, [r5, #152] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875D48 \n"
		"BL	sub_FF875300 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875C88 \n"
		"ldr	r0, [r5, #156] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF875C88 \n"
		"ldr	r0, [r5, #28] \n"
		"ldr	r1, [r5, #32] \n"
		"orrs	r0, r0, r1 \n"
		"BEQ	loc_FF875C68 \n"
		"BL	sub_FF875220 \n"
		"B	loc_FF875C6C \n"
	"loc_FF875C68:\n"
		"BL	sub_FF874980 \n"
	"loc_FF875C6C:\n"
		"ldr	r0, [r5, #52] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r5, #48] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"streq	r4, [r5, #156] \n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
//	"B	sub_FF8766E0 \n"
	"B	sub_FF8766E0_my \n" // ---------------------->
	"loc_FF875C88:\n"
		"ldr	r1, [r5, #36] \n"
		"mov	r6, r5 \n"
		"mov	r0, #0	\n" // ; 0x0
		"ldr	r5,  =0x00008002 \n"
		"cmp	r1, #0	\n" // ; 0x0
		"str	r0, [r6, #152] \n"
		"BEQ	loc_FF875CDC \n"
		"ldr	r1, =0xff875f9c \n" // ; (746e455f)  *"_EntryToRec"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"mov	r0, r5 \n"
//	"BL	sub_FF82A3B4 \n"
	"BL	sub_FF82A3B4_my \n" // ------------------------>
		"BL	sub_FF878290 \n" // <unknown_libname_80 +9688>
		"BL	sub_FF8764C0 \n"
		"BL	sub_FF825388 \n"
		"BL	sub_FF87CAD8 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #72	\n" // ; 0x48
		"BL	sub_FF87EBD0 \n"
//	"BL	sub_FF876768 \n"
	"BL	sub_FF876768_my \n" // ---------------------->
		"B	loc_FF875D48 \n"
	"loc_FF875CDC:\n"
		"ldr	r1, =0xff875fa8 \n" // ; (746e455f)  *"_EntryToPrepareLens"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"mov	r0, #10	\n" // ; 0xa
		"BL	sub_FF874CFC \n"
		"mov	r0, r5 \n"
//	"BL	sub_FF82A3B4 \n"
	"BL	sub_FF82A3B4_my \n" // ------------------------>
		"BL	sub_FF878290 \n" // <unknown_libname_80 +9624>
		"ldr	r1, =0xff875fbc \n" // ; (503a4341)  *"AC:PrepareLens"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF8764C0 \n"
		"BL	sub_FF876FC0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF875D20 \n"
		"BL	sub_FF876518 \n"
		"B	loc_FF875D48 \n"
	"loc_FF875D20:\n"
		"BL	sub_FF825388 \n"
		"BL	sub_FF82A534 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r4, [r6, #40] \n"
		"BL	sub_FF824E1C \n"
		"BL	sub_FF824F30 \n"
		"BL	sub_FF82AE0C \n"
		"mov	r0, r5 \n"
//	"BL	sub_FF82A3B4 \n"
	"BL	sub_FF82A3B4_my \n" // ------------------------>
		"BL	sub_FF877208 \n"
	"loc_FF875D48:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, r5, r6, pc} \n"
    );
}

// sub_FF86F9F8 -> sub_FF875D50
// Extracted method: (ff875d50-ff875e50)
// Overridden calls:
//     sub_FF82BE84 -> sub_FF82A3B4
//     sub_FF86EDAC -> sub_FF875380
//     sub_FF870430 -> sub_FF876798
void __attribute__((naked,noinline)) sub_FF875D50_my() {
	asm volatile (
		"ldr	ip,  =0x00001162 \n"
		"stmdb	sp!, {r4, lr} \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF875E44 \n"
		"BGT	loc_FF875DAC \n"
		"ldr	ip,  =0x000010a9 \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF875DA0 \n"
		"BGT	loc_FF875D8C \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #5	\n" // ; 0x5
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #8	\n" // ; 0x8
		"BNE	loc_FF875DF0 \n"
		"B	loc_FF875DA4 \n"
	"loc_FF875D8C:\n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #173	\n" // ; 0xad
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #175	\n" // ; 0xaf
		"BNE	loc_FF875DF0 \n"
	"loc_FF875DA0:\n"
		"BL	sub_FF875220 \n"
	"loc_FF875DA4:\n"
//	"BL	sub_FF875380 \n"
	"BL	sub_FF875380_my \n" // ------------------------>
		"B	loc_FF875E4C \n"
	"loc_FF875DAC:\n"
		"ldr	ip,  =0x0000119b \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF875E18 \n"
		"BGT	loc_FF875DD8 \n"
		"sub	ip, r0, #4352	\n" // ; 0x1100
		"subs	ip, ip, #130	\n" // ; 0x82
		"BEQ	loc_FF875E18 \n"
		"sub	ip, r0, #4352	\n" // ; 0x1100
		"subs	ip, ip, #133	\n" // ; 0x85
		"BNE	loc_FF875DF0 \n"
		"B	loc_FF875DF8 \n"
	"loc_FF875DD8:\n"
		"sub	ip, r0, #4352	\n" // ; 0x1100
		"subs	ip, ip, #171	\n" // ; 0xab
		"BEQ	loc_FF875DF8 \n"
		"sub	ip, r0, #4608	\n" // ; 0x1200
		"subs	ip, ip, #3	\n" // ; 0x3
		"BEQ	loc_FF875E4C \n"
	"loc_FF875DF0:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, pc} \n"
	"loc_FF875DF8:\n"
		"BL	sub_FF877DE4 \n"
		"BL	sub_FF877E18 \n"
		"mov	r0, #16640	\n" // ; 0x4100
//	"BL	sub_FF82A3B4 \n"
	"BL	sub_FF82A3B4_my \n" // ------------------------>
		"BL	sub_FF998878 \n"
		"mov	r0, #22	\n" // ; 0x16
		"BL	sub_FF874CFC \n"
		"B	loc_FF875E4C \n"
	"loc_FF875E18:\n"
		"ldr	r0,  =0x000059c0 \n"
		"ldr	r1, [r0, #88] \n"
		"ldr	r0, [r0, #84] \n"
		"orrs	r0, r1, r0 \n"
		"BEQ	loc_FF875E34 \n"
		"BL	sub_FF874B2C \n"
		"B	loc_FF875DA4 \n"
	"loc_FF875E34:\n"
		"BL	sub_FF877DE4 \n"
		"BL	sub_FF877E18 \n"
//	"BL	sub_FF876798 \n"
	"BL	sub_FF876798_my \n" // ------------------------>
		"B	loc_FF875E4C \n"
	"loc_FF875E44:\n"
		"BL	sub_FF874B2C \n"
		"BL	sub_FF874AFC \n"
	"loc_FF875E4C:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
    );
}

// Extracted method: (ff876798-ff8767cc)
// Overridden calls:
//     sub_FF82BE84 -> sub_FF82A3B4
void __attribute__((naked,noinline)) sub_FF876798_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff876998 \n" // ; (493a4341)  *"AC:InitPB"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF877238 \n"
		"ldr	r0,  =0x00004004 \n"
//	"BL	sub_FF82A3B4 \n"
	"BL	sub_FF82A3B4_my \n" // ------------------------>
		"mov	r0, #11	\n" // ; 0xb
		"BL	sub_FF874CFC \n"
		"BL	sub_FF878290 \n" // <unknown_libname_80 +6868>
		"BL	sub_FF8253BC \n"
		"BL	sub_FF876BF8 \n"
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF82A4F4 \n"
    );
}

// sub_FF870694 -> sub_FF876B4C
// Extracted method: (ff876b4c-ff876bf4)
// Overridden calls:
//     sub_FF82BE84 -> sub_FF82A3B4
//     sub_FF82C130 -> ? FF82A668 no call here ...
void __attribute__((naked,noinline)) sub_FF876B4C_my() {
	asm volatile (
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #388	\n" // ; 0x184
		"stmdb	sp!, {r4, lr} \n"
		"BEQ	loc_FF876BB0 \n"
		"sub	ip, r0, #13056	\n" // ; 0x3300
		"subs	ip, ip, #2	\n" // ; 0x2
		"movne	r0, #1	\n" // ; 0x1
		"ldmneia	sp!, {r4, pc} \n"
		"BL	sub_FF99AAD8 \n"
		"ldr	r0,  =0x00004004 \n"
//	"BL	sub_FF82A3B4 \n"
	"BL	sub_FF82A3B4_my \n" // ------------------------>
		"mov	r0, #2	\n" // ; 0x2
		"BL	sub_FF874CFC \n"
		"ldr	r1, =0xff876c48 \n" // ; (433a4341)  *"AC:CheckTermCom2PB"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF875300 \n"
		"ldr	r1,  =0x000059c0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldr	r0, [r1, #84] \n"
		"BNE	loc_FF876BBC \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF876BC4 \n"
		"BL	sub_FF87756C \n"
		"B	loc_FF876BF0 \n"
	"loc_FF876BB0:\n"
		"mov	r0, #1	\n" // ; 0x1
		"BL	sub_FF8E4710 \n"
		"B	loc_FF876BF0 \n"
	"loc_FF876BBC:\n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF876BCC \n"
	"loc_FF876BC4:\n"
		"BL	sub_FF876538 \n"
		"B	loc_FF876BF0 \n"
	"loc_FF876BCC:\n"
		"mov	r0, r1 \n"
		"ldr	r0, [r0, #32] \n"
		"ldr	r1, [r1, #28] \n"
		"orrs	r0, r1, r0 \n"
		"BEQ	loc_FF876BE8 \n"
		"BL	sub_FF875220 \n"
		"B	loc_FF876BEC \n"
	"loc_FF876BE8:\n"
		"BL	sub_FF874980 \n"
	"loc_FF876BEC:\n"
		"BL	sub_FF8765B4 \n"
	"loc_FF876BF0:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
    );
}

// sub_FF86F498 -> sub_FF87595C
// Extracted method: (ff87595c-ff875aac)
// Overridden calls:
//     sub_FF86EDAC -> sub_FF875380
//     sub_FF870400 -> sub_FF876768
void __attribute__((naked,noinline)) sub_FF87595C_my() {
	asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"BL	sub_FF87661C \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BLEQ	sub_FF876724 \n"
		"ldr	r4,  =0x000059c0 \n"
		"mov	r5, #1	\n" // ; 0x1
		"ldr	r0, [r4, #36] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #76] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF8759C8 \n"
		"BL	sub_FF87661C \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF8759C8 \n"
		"BL	sub_FF876724 \n"
		"ldr	r0, [r4, #120] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF8759C8 \n"
		"ldr	r1, =0xff875af4 \n" // ; (533a4341)  *"AC:StartupShowInfo"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF9AAC68 \n"
		"BL	sub_FF9AABF8 \n" // <RefreshPhysicalScreen +1266244>
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #81	\n" // ; 0x51
		"BL	sub_FF87EBD0 \n"
		"str	r5, [r4, #120] \n"
	"loc_FF8759C8:\n"
		"BL	sub_FF87661C \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF875A14 \n"
		"ldr	r0, [r4, #68] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875A14 \n"
		"ldr	r0, [r4, #116] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF875A14 \n"
		"ldr	r1, =0xff875b08 \n" // ; (443a4341)  *"AC:DispShot"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #140	\n" // ; 0x8c
		"BL	sub_FF87EBD0 \n"
		"BL	sub_FF87CAD8 \n"
		"mov	r0, #33	\n" // ; 0x21
		"BL	sub_FF87EC10 \n"
		"str	r5, [r4, #116] \n"
	"loc_FF875A14:\n"
		"ldr	r0, [r4, #56] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #60] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #68] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #72] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #28] \n"
		"ldrne	r1, [r4, #32] \n"
		"orrnes	r0, r0, r1 \n"
		"BEQ	loc_FF875A50 \n"
		"BL	sub_FF875220 \n"
//	"BL	sub_FF875380 \n"
	"BL	sub_FF875380_my \n" // ------------------------>
		"B	loc_FF875A78 \n"
	"loc_FF875A50:\n"
		"ldr	r0, [r4, #88] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875A80 \n"
		"BL	sub_FF875268 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF875A80 \n"
		"BL	sub_FF877E84 \n"
		"BL	sub_FF877E40 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8764E0 \n"
	"loc_FF875A78:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, r5, r6, pc} \n"
	"loc_FF875A80:\n"
		"BL	sub_FF875268 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF875AA8 \n"
		"ldr	r0, [r4, #124] \n"
		"cmp	r0, #0	\n" // ; 0x0
//	"BLEQ	sub_FF876768 \n"
	"BLEQ	sub_FF876768_my \n" // ------------------------>
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r4, #112] \n"
		"str	r0, [r4, #116] \n"
		"str	r0, [r4, #120] \n"
	"loc_FF875AA8:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, r5, r6, pc} \n"
    );
}

// sub_FF86F6F0 -> sub_FF8769E0
// Extracted method: (ff8769e0-ff876b48)
// Overridden calls:
//     sub_FF86F224 -> sub_FF875774
void __attribute__((naked,noinline)) sub_FF8769E0_my() {
	asm volatile (
		"ldr	ip,  =0x00001062 \n"
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x000059c0 \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF876AE8 \n"
		"BGT	loc_FF876A50 \n"
		"ldr	ip,  =0x00001005 \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF876B24 \n"
		"BGT	loc_FF876A2C \n"
		"sub	ip, r0, #2304	\n" // ; 0x900
		"subs	ip, ip, #161	\n" // ; 0xa1
		"BEQ	loc_FF876ADC \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #1	\n" // ; 0x1
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #3	\n" // ; 0x3
		"BNE	loc_FF876B44 \n"
		"B	loc_FF876AE8 \n"
	"loc_FF876A2C:\n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #8	\n" // ; 0x8
		"BEQ	loc_FF876B24 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #91	\n" // ; 0x5b
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #97	\n" // ; 0x61
		"BNE	loc_FF876B44 \n"
		"B	loc_FF876AE8 \n"
	"loc_FF876A50:\n"
		"ldr	ip,  =0x000010ad \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF876B20 \n"
		"BGT	loc_FF876A88 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #101	\n" // ; 0x65
		"BEQ	loc_FF876AE8 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #165	\n" // ; 0xa5
		"BEQ	loc_FF876ADC \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #169	\n" // ; 0xa9
		"BNE	loc_FF876B44 \n"
		"B	loc_FF876B20 \n"
	"loc_FF876A88:\n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #175	\n" // ; 0xaf
		"BEQ	loc_FF876B20 \n"
		"sub	ip, r0, #4352	\n" // ; 0x1100
		"subs	ip, ip, #98	\n" // ; 0x62
		"BEQ	loc_FF876B24 \n"
		"sub	ip, r0, #12288	\n" // ; 0x3000
		"subs	ip, ip, #12	\n" // ; 0xc
		"BNE	loc_FF876B44 \n"
		"ldr	r0, [r4, #144] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"moveq	r1, #0	\n" // ; 0x0
		"moveq	r0, #2	\n" // ; 0x2
		"BEQ	loc_FF876AD4 \n"
		"BL	sub_FF82AE70 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF876AF0 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #1	\n" // ; 0x1
	"loc_FF876AD4:\n"
//	"BL	sub_FF875774 \n"
	"BL	sub_FF875774_my \n" // ------------------------>
		"B	loc_FF876B3C \n"
	"loc_FF876ADC:\n"
		"BL	sub_FF82AE70 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF876B3C \n"
	"loc_FF876AE8:\n"
		"BL	sub_FF876C1C \n"
		"B	loc_FF876B3C \n"
	"loc_FF876AF0:\n"
		"BL	sub_FF876FC0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF876B04 \n"
		"BL	sub_FF876518 \n"
		"B	loc_FF876B3C \n"
	"loc_FF876B04:\n"
		"BL	sub_FF82AE88 \n"
		"str	r0, [r4, #24] \n"
		"BL	sub_FF8764A4 \n"
		"BL	sub_FF82A3A0 \n"
		"ldr	r1, [r4, #24] \n"
		"mov	r0, #0	\n" // ; 0x0
		"B	loc_FF876AD4 \n"
	"loc_FF876B20:\n"
		"BL	sub_FF875220 \n"
	"loc_FF876B24:\n"
		"ldr	r0, [r4, #144] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF876B3C \n"
		"BL	sub_FF876C1C \n"
		"mov	r0, #1	\n" // ; 0x1
		"str	r0, [r4, #144] \n"
	"loc_FF876B3C:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
	"loc_FF876B44:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, pc} \n"
    );
}

// sub_FF82CD9C -> sub_FF82B1B4
// Extracted method: (ff82b1b4-ff82b1dc)
// Overridden calls:
//     sub_FF86FB00 -> sub_FF875E54
void __attribute__((naked,noinline)) sub_FF82B1B4_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x00001d28 \n"
		"ldr	r0, [r4] \n"
		"cmp	r0, #31	\n" // ; 0x1f
		"ldmneia	sp!, {r4, pc} \n"
		"mov	r1, #0	\n" // ; 0x0
		"ldr	r0,  =0x0000313e \n"
//	"BL	sub_FF875E54 \n" //
	"BL	sub_FF875E54_my \n" // // ------------------------>
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r4] \n"
		"ldmia	sp!, {r4, pc} \n"
    );
}

// sub_FF82C1B0 -> sub_FF82A6E8
// Extracted method: (ff82a6e8-ff82a7c0)
// Overridden calls:
//     sub_FF86FB00 -> sub_FF875E54
void __attribute__((naked,noinline)) sub_FF82A6E8_my() {
	asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"ldr	r4,  =0x00001d28 \n"
		"mov	r5, #1	\n" // ; 0x1
		"mov	r6, r0 \n"
		"str	r5, [r4, #40] \n"
		"ldr	r0, [r4, #8] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF82A724 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF82B1E0 \n"
		"ldr	r0, [r4, #8] \n"
		"BL	sub_FF8722C0 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r4, #8] \n"
	"loc_FF82A724:\n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF884130 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF82A750 \n"
		"ldr	r1, =0xff82a7d4 \n" // ; (6143794d)  *"MyCamFunc_PlaySound_MYCAM_COVER_OPEN"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"ldr	r0,  =0x0000400d \n"
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF85B064 \n"
		"B	loc_FF82A7B4 \n"
	"loc_FF82A750:\n"
		"BL	sub_FF82AED8 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"streq	r5, [r4, #24] \n"
		"ldr	r0, [r4, #12] \n"
		"sub	ip, r0, #16384	\n" // ; 0x4000
		"subs	ip, ip, #4	\n" // ; 0x4
		"subne	ip, r0, #16384	\n" // ; 0x4000
		"subnes	ip, ip, #16	\n" // ; 0x10
		"BEQ	loc_FF82A7B0 \n"
		"BL	sub_FF87E68C \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF82A7B0 \n"
		"BL	sub_FF87E654 \n" // <GetVRAMHPixelsSize_1 +343764>
		"cmp	r0, #7	\n" // ; 0x7
		"BEQ	loc_FF82A7B0 \n"
		"BL	sub_FF87E654 \n" // <GetVRAMHPixelsSize_1 +343752>
		"cmp	r0, #8	\n" // ; 0x8
		"BEQ	loc_FF82A7B0 \n"
		"BL	sub_FF87E654 \n" // <GetVRAMHPixelsSize_1 +343740>
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF82A7B0 \n"
		"BL	sub_FF87CDF8 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF82A7B4 \n"
	"loc_FF82A7B0:\n"
		"BL	sub_FF82A554 \n"
	"loc_FF82A7B4:\n"
		"mov	r0, r6 \n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
		"mov	r1, #0	\n" // ; 0x0
//	"B	sub_FF875E54 \n"
	"B	sub_FF875E54_my \n" // ------------------------>
    );
}

// sub_FF86E320 -> sub_FF8749D0
// Extracted method: (ff8749d0-ff8749fc)
// Overridden calls:
//     sub_FF86FB00 -> sub_FF875E54
void __attribute__((naked,noinline)) sub_FF8749D0_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff874bfc \n" // ; (4f3a4341)  *"AC:OpCoverTimeout"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"ldr	r1,  =0x000059b0 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r1, #4] \n"
		"str	r0, [r1] \n"
		"ldmia	sp!, {r4, lr} \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #4	\n" // ; 0x4
//	"B	sub_FF875E54 \n"
	"B	sub_FF875E54_my \n" // ------------------------>
    );
}

// sub_FF86F5E8 -> sub_FF875B14
// Extracted method: (ff875b14-ff875bf0)
// Overridden calls:
//     sub_FF86EDAC -> sub_FF875380
//     sub_FF86F498 -> sub_FF87595C
void __attribute__((naked,noinline)) sub_FF875B14_my() {
	asm volatile (
		"ldr	ip,  =0x0000201e \n"
		"stmdb	sp!, {r4, lr} \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF875BD4 \n"
		"BGT	loc_FF875B70 \n"
		"ldr	ip,  =0x00002004 \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF875BDC \n"
		"BGT	loc_FF875B58 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #169	\n" // ; 0xa9
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #173	\n" // ; 0xad
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #175	\n" // ; 0xaf
		"BNE	loc_FF875BEC \n"
		"B	loc_FF875BD4 \n"
	"loc_FF875B58:\n"
		"sub	ip, r0, #8192	\n" // ; 0x2000
		"subs	ip, ip, #5	\n" // ; 0x5
		"subne	ip, r0, #8192	\n" // ; 0x2000
		"subnes	ip, ip, #29	\n" // ; 0x1d
		"BNE	loc_FF875BEC \n"
		"B	loc_FF875BD4 \n"
	"loc_FF875B70:\n"
		"ldr	ip,  =0x00005004 \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF875BD4 \n"
		"BGT	loc_FF875B9C \n"
		"sub	ip, r0, #12288	\n" // ; 0x3000
		"subs	ip, ip, #10	\n" // ; 0xa
		"BEQ	loc_FF875BD0 \n"
		"sub	ip, r0, #20480	\n" // ; 0x5000
		"subs	ip, ip, #1	\n" // ; 0x1
		"BNE	loc_FF875BEC \n"
		"B	loc_FF875BD4 \n"
	"loc_FF875B9C:\n"
		"sub	ip, r0, #20480	\n" // ; 0x5000
		"subs	ip, ip, #6	\n" // ; 0x6
		"BEQ	loc_FF875BD4 \n"
		"sub	ip, r0, #20480	\n" // ; 0x5000
		"subs	ip, ip, #7	\n" // ; 0x7
		"BNE	loc_FF875BEC \n"
		"BL	sub_FF82AE10 \n"
		"ldr	r1,  =0x000059c0 \n"
		"ldr	r0, [r1, #16] \n"
		"cmp	r0, #7	\n" // ; 0x7
		"ldreq	r0, [r1, #24] \n"
		"BLEQ	sub_FF8764A4 \n"
		"B	loc_FF875BE4 \n"
	"loc_FF875BD0:\n"
		"BL	sub_FF82A3A0 \n"
	"loc_FF875BD4:\n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF87595C \n"
	"B	sub_FF87595C_my \n" // ------------------------>
	"loc_FF875BDC:\n"
		"BL	sub_FF874980 \n"
//	"BL	sub_FF875380 \n"
	"BL	sub_FF875380_my \n" // ------------------------>
	"loc_FF875BE4:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
	"loc_FF875BEC:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, pc} \n"
    );
}

//     sub_FF82C0CC -> sub_FF82A604
// Extracted method: (ff82a604-ff82a614)
// Overridden calls:
//     sub_FF82CD9C -> sub_FF82B1B4
void __attribute__((naked,noinline)) sub_FF82A604_my() {
	asm volatile (
		"ldr	r0,  =0x00001d28 \n"
		"ldr	r1, [r0] \n"
		"orr	r1, r1, #1	\n" // ; 0x1
		"str	r1, [r0] \n"
//	"B	sub_FF82B1B4 \n"
	"B	sub_FF82B1B4_my \n" // ------------------------>
    );
}

//     sub_FF82C0E0 -> sub_FF82A618
// Extracted method: (ff82a618-ff82a628)
// Overridden calls:
//     sub_FF82CD9C -> sub_FF82B1B4
void __attribute__((naked,noinline)) sub_FF82A618_my() {
	asm volatile (
		"ldr	r0,  =0x00001d28 \n"
		"ldr	r1, [r0] \n"
		"orr	r1, r1, #2	\n" // ; 0x2
		"str	r1, [r0] \n"
//	"B	sub_FF82B1B4 \n"
	"B	sub_FF82B1B4_my \n" // ------------------------>
    );
}

//     sub_FF82C0F4 -> sub_FF82A62C
// Extracted method: (ff82a62c-ff82a63c)
// Overridden calls:
//     sub_FF82CD9C -> sub_FF82B1B4
void __attribute__((naked,noinline)) sub_FF82A62C_my() {
	asm volatile (
		"ldr	r0,  =0x00001d28 \n"
		"ldr	r1, [r0] \n"
		"orr	r1, r1, #8	\n" // ; 0x8
		"str	r1, [r0] \n"
//	"B	sub_FF82B1B4 \n"
	"B	sub_FF82B1B4_my \n" // ------------------------>
    );
}

//     sub_FF82C108 -> sub_FF82A640
// Extracted method: (ff82a640-ff82a650)
// Overridden calls:
//     sub_FF82CD9C -> sub_FF82B1B4
void __attribute__((naked,noinline)) sub_FF82A640_my() {
	asm volatile (
		"ldr	r0,  =0x00001d28 \n"
		"ldr	r1, [r0] \n"
		"orr	r1, r1, #16	\n" // ; 0x10
		"str	r1, [r0] \n"
//	"B	sub_FF82B1B4 \n"
	"B	sub_FF82B1B4_my \n" // ------------------------>
    );
}

//     sub_FF82C11C -> sub_FF82A654
// Extracted method: (ff82a654-ff82a664)
// Overridden calls:
//     sub_FF82CD9C -> sub_FF82B1B4
void __attribute__((naked,noinline)) sub_FF82A654_my() {
	asm volatile (
		"ldr	r0,  =0x00001d28 \n"
		"ldr	r1, [r0] \n"
		"orr	r1, r1, #4	\n" // ; 0x4
		"str	r1, [r0] \n"
//	"B	sub_FF82B1B4 \n"
	"B	sub_FF82B1B4_my \n" // ------------------------>
    );
}

// sub_FF86E38C -> sub_FF874A3C
// Extracted method: (ff874a3c-ff874af8)
// Overridden calls:
//     sub_FF86E320 -> sub_FF8749D0
void __attribute__((naked,noinline)) sub_FF874A3C_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x000059b0 \n"
		"ldr	r0, [r4, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF874AA8 \n"
		"ldr	r0,  =0x000010b0 \n"
		"BL	sub_FF8735C0 \n" // <IsControlEventActive -5268>
		"cmp	r0, #0	\n" // ; 0x0
		"ldmneia	sp!, {r4, lr} \n"
		"BNE	sub_FF874A00 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8742E4 \n"
		"BL	sub_FF874C94 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #3	\n" // ; 0x3
		"BL	sub_FF874C68 \n"
		"ldr	r1, =0xff874c18 \n" // ; (533a4341)  *"AC:StartShutTimer"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
//	"ldr	r2, =0xff8749d0 \n" // ; (e92d4010)
	"ldr	r2, =sub_FF8749D0_my \n" // ------------------->
		"ldr	r0,  =0x0002bf20 \n"
		"add	r1, r2, #0	\n" // ; 0x0
		"mov	r3, #0	\n" // ; 0x0
		"BL	sub_FF872210 \n"
		"str	r0, [r4] \n"
		"ldmia	sp!, {r4, pc} \n"
	"loc_FF874AA8:\n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8742E4 \n"
		"BL	sub_FF874C94 \n"
		"ldr	r0, [r4, #8] \n"
		"cmp	r0, #1	\n" // ; 0x1
		"ldmneia	sp!, {r4, lr} \n"
		"movne	r1, #0	\n" // ; 0x0
		"mov	r0, #1	\n" // ; 0x1
		"BNE	sub_FF874C68 \n"
		"ldmeqia	sp!, {r4, lr} \n"
		"BEQ	sub_FF829EA8 \n" // <RestartDevice -306220>
		"stmdb	sp!, {r4, lr} \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8742E4 \n"
		"BL	sub_FF874C94 \n"
		"ldmia	sp!, {r4, lr} \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #2	\n" // ; 0x2
		"B	sub_FF874C68 \n"
    );
}

// sub_FF82C130 -> sub_FF82A668
// Extracted method: (ff82a668-ff82a694)
// Overridden calls:
//     sub_FF82C0CC -> sub_FF82A604
//     sub_FF82C0E0 -> sub_FF82A618
//     sub_FF82C0F4 -> sub_FF82A62C
//     sub_FF82C108 -> sub_FF82A640
//     sub_FF82C11C -> sub_FF82A654
void __attribute__((naked,noinline)) sub_FF82A668_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
//	"ldr	r0, =0xff82a604 \n" // ; (e59f01bc)
	"ldr	r0, =sub_FF82A604_my \n" // ------------------->
		"BL	sub_FF886678 \n"
//	"ldr	r0, =0xff82a618 \n" // ; (e59f01a8)
	"ldr	r0, =sub_FF82A618_my \n" // ------------------->
		"BL	sub_FF884130 \n"
//	"ldr	r0, =0xff82a62c \n" // ; (e59f0194)
	"ldr	r0, =sub_FF82A62C_my \n" // ------------------->
		"BL	sub_FF884ED8 \n"
//	"ldr	r0, =0xff82a640 \n" // ; (e59f0180)
	"ldr	r0, =sub_FF82A640_my \n" // ------------------->
		"BL	sub_FF88A1B4 \n"
		"ldmia	sp!, {r4, lr} \n"
//	"ldr	r0, =0xff82a654 \n" // ; (e59f016c)
	"ldr	r0, =sub_FF82A654_my \n" // ------------------->
		"B	sub_FF8814D8 \n"
    );
}

//     sub_FF86ED10 -> sub_FF875320
// Extracted method: (ff875320-ff87537c)
// Overridden calls:
//     sub_FF86E38C -> sub_FF874A3C
void __attribute__((naked,noinline)) sub_FF875320_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x000059c0 \n"
		"ldr	r0, [r4, #96] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875348 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #5	\n" // ; 0x5
		"BL	sub_FF8742E4 \n"
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF876518 \n"
	"loc_FF875348:\n"
		"ldr	r1, [r4, #132] \n"
		"mov	r0, #5	\n" // ; 0x5
		"BL	sub_FF8742E4 \n"
		"ldr	r0, [r4, #92] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875370 \n"
		"mov	r0, #20	\n" // ; 0x14
		"BL	sub_FF874CFC \n"
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF874AD8 \n"
	"loc_FF875370:\n"
		"mov	r0, #19	\n" // ; 0x13
		"BL	sub_FF874CFC \n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF874A3C \n"
	"B	sub_FF874A3C_my \n" // ------------------------>
    );
}

// -> ff8751f0
// sub_FF86EB84 -> sub_FF8751F0
// Extracted method: (ff8751f0-ff87521c)
// Overridden calls:
//     sub_FF82C130 -> sub_FF82A668
void __attribute__((naked,noinline)) sub_FF8751F0_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff8753e8 \n" // ; (543a4341)  *"AC:TStoreLensT"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"ldr	r1,  =0x000059c0 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r1, #136] \n"
		"BL	sub_FF8253F0 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"ldmeqia	sp!, {r4, lr} \n"
//	"BEQ	sub_FF82A668 \n"
	"BEQ	sub_FF82A668_my \n" // ------------------------>
		"ldmia	sp!, {r4, pc} \n"
    );
}

// sub_FF86EFE4 -> sub_FF8755A4
// Extracted method: (ff8755a4-ff87573c)
// Overridden calls:
//     sub_FF82C130 -> sub_FF82A668 (??? no call here)
//     sub_FF86EDAC -> sub_FF875380
//     sub_FF870378 -> sub_FF8766E0
void __attribute__((naked,noinline)) sub_FF8755A4_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x000059c0 \n"
		"ldr	r3,  =0x00003202 \n"
		"ldr	r1, [r4, #164] \n"
		"ldr	lr,  =0x00002004 \n"
		"cmp	r1, #0	\n" // ; 0x0
		"cmpne	r0, r3 \n"
		"cmpne	r0, lr \n"
		"BNE	loc_FF875738 \n"
		"ldr	ip,  =0x000010af \n"
		"mov	r2, #1	\n" // ; 0x1
		"cmp	r0, ip \n"
		"BEQ	loc_FF875640 \n"
		"BGT	loc_FF87564C \n"
		"ldr	ip,  =0x00001062 \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF8756D8 \n"
		"BGT	loc_FF875620 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #1	\n" // ; 0x1
		"BEQ	loc_FF8756D8 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #5	\n" // ; 0x5
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #8	\n" // ; 0x8
		"streq	r2, [r4, #164] \n"
		"BEQ	loc_FF875730 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #91	\n" // ; 0x5b
		"BNE	loc_FF8756D0 \n"
		"B	loc_FF8756D8 \n"
	"loc_FF875620:\n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #101	\n" // ; 0x65
		"BEQ	loc_FF8756D8 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #169	\n" // ; 0xa9
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #173	\n" // ; 0xad
		"BNE	loc_FF8756D0 \n"
	"loc_FF875640:\n"
		"str	r2, [r4, #164] \n"
		"BL	sub_FF875220 \n"
		"B	loc_FF875734 \n"
	"loc_FF87564C:\n"
		"ldr	r1,  =0x00001183 \n"
		"add	ip, r1, #18	\n" // ; 0x12
		"cmp	r0, ip \n"
		"BEQ	loc_FF87567C \n"
		"BGT	loc_FF8756A8 \n"
		"sub	ip, r0, #4352	\n" // ; 0x1100
		"subs	ip, ip, #98	\n" // ; 0x62
		"BEQ	loc_FF875728 \n"
		"sub	ip, r0, #4352	\n" // ; 0x1100
		"subs	ip, ip, #129	\n" // ; 0x81
		"cmpne	r0, r1 \n"
		"BNE	loc_FF8756D0 \n"
	"loc_FF87567C:\n"
		"cmp	r0, r1 \n"
		"str	r0, [r4, #160] \n"
		"BNE	loc_FF8756E0 \n"
		"BL	sub_FF8775E8 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875738 \n"
		"mov	r0, #16	\n" // ; 0x10
		"BL	sub_FF874CFC \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8E4710 \n"
		"B	loc_FF875738 \n"
	"loc_FF8756A8:\n"
		"cmp	r0, lr \n"
		"BEQ	loc_FF875710 \n"
		"sub	ip, r0, #12288	\n" // ; 0x3000
		"subs	ip, ip, #1	\n" // ; 0x1
		"streq	r2, [r4, #164] \n"
		"BEQ	loc_FF875734 \n"
		"cmp	r0, r3 \n"
		"streq	r2, [r4, #168] \n"
		"ldmeqia	sp!, {r4, lr} \n"
//	"BEQ	sub_FF8766E0 \n"
	"BEQ	sub_FF8766E0_my \n" // ------------------------>
	"loc_FF8756D0:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, pc} \n"
	"loc_FF8756D8:\n"
		"BL	sub_FF876538 \n"
		"B	loc_FF875738 \n"
	"loc_FF8756E0:\n"
		"ldr	r1, =0xff875768 \n" // ; (503a4341)  *"AC:PB2PC"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"ldr	r0, [r4, #36] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLNE	sub_FF87633C \n"
		"BL	sub_FF877E84 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF876480 \n"
		"mov	r0, #15	\n" // ; 0xf
		"BL	sub_FF874CFC \n"
		"B	loc_FF875738 \n"
	"loc_FF875710:\n"
		"ldr	r0, [r4, #52] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #168] \n"
		"cmpne	r0, #0	\n" // ; 0x0
//	"BLNE	sub_FF875380 \n"
	"BLNE	sub_FF875380_my \n" // ------------------------>
		"B	loc_FF875738 \n"
	"loc_FF875728:\n"
		"str	r2, [r4, #164] \n"
		"BL	sub_FF87FF9C \n" // <unknown_libname_96 +43120>
	"loc_FF875730:\n"
		"BL	sub_FF874980 \n"
	"loc_FF875734:\n"
		"BL	sub_FF8765B4 \n"
	"loc_FF875738:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
        ".LTORG\n" // make literal pool
    );
}

// sub_FF86EDAC -> sub_FF875380
// Extracted method: (ff875380-ff8753dc)
// Overridden calls:
//     sub_FF86ED10 -> sub_FF875320
void __attribute__((naked,noinline)) sub_FF875380_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r1, =0xff875404 \n" // ; (453a4341)  *"AC:EntryNShtDwn"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"ldr	r4,  =0x000059c0 \n"
		"ldr	r0, [r4, #56] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldmeqia	sp!, {r4, pc} \n"
		"BL	sub_FF877298 \n" // <j_unknown_libname_73 +7928>
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF8753B8 \n"
		"ldr	r0, [r4, #68] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF8753D0 \n"
	"loc_FF8753B8:\n"
		"ldr	r0, [r4, #56] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldmeqia	sp!, {r4, pc} \n"
		"BL	sub_FF877298 \n" // <j_unknown_libname_73 +7892>
		"cmp	r0, #0	\n" // ; 0x0
		"ldmneia	sp!, {r4, pc} \n"
	"loc_FF8753D0:\n"
		"BL	sub_FF877E84 \n"
		"BL	sub_FF87811C \n"
		"ldmia	sp!, {r4, lr} \n"
	//	"B	sub_FF875320 \n"
		"B	sub_FF875320_my \n" // ------------------------>
    );
}

// sub_FF870468 -> sub_FF8767D0
// Extracted method: (ff8767d0-ff876898)
// Overridden calls:
// sub_FF86EFE4 -> sub_FF8755A4
// sub_FF86EB84 -> sub_FF8751F0
void __attribute__((naked,noinline)) sub_FF8767D0_my() {
	asm volatile (
		"sub	ip, r0, #12800	\n" // ; 0x3200
		"subs	ip, ip, #1	\n" // ; 0x1
		"movne	r0, #1	\n" // ; 0x1
		"stmdb	sp!, {r3, r4, r5, lr} \n"
		"BNE	loc_FF876898 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #1	\n" // ; 0x1
		"BL	sub_FF8788AC \n"
		"mov	r0, #2	\n" // ; 0x2
		"BL	sub_FF874CFC \n"
		"ldr	r4,  =0x000059c0 \n"
		"ldr	r0, [r4, #48] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF876848 \n"
		"ldr	r1, =0xff8769a4 \n" // ; (533a4341)  *"AC:SStoreLensT"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF876318 \n"
		"ldr	r0,  =0x0000406c \n"
		"mov	r2, #4	\n" // ; 0x4
		"mov	r1, sp \n"
		"BL	sub_FF874268 \n"
		"ldr	r0, [sp] \n"
		"mov	r1, #1000	\n" // ; 0x3e8
//	"ldr	r2,  =0xff8751f0 \n" //
	"ldr	r2,  =sub_FF8751F0_my \n" // ------------------->
		"mul	r0, r1, r0 \n"
		"add	r1, r2, #0	\n" // ; 0x0
		"mov	r3, #0	\n" // ; 0x0
		"BL	sub_FF872210 \n"
		"str	r0, [r4, #136] \n"
	"loc_FF876848:\n"
		"BL	sub_FF881DE4 \n"
		"BL	sub_FF877D20 \n"
		"BL	sub_FF9AAC68 \n"
		"BL	sub_FF9AABF8 \n" // <RefreshPhysicalScreen +1262500>
		"BL	sub_FF8779E8 \n"
		"BL	sub_FF877EBC \n"
		"BL	sub_FF82A478 \n"
		"ldr	r1, =0xff8769bc \n" // ; (453a4341)  *"AC:EntryPB"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF8751A4 \n"
		"cmn	r0, #1	\n" // ; 0x1
		"BLEQ	sub_FF87756C \n"
		"BL	sub_FF8751A4 \n"
//	"BL	sub_FF8755A4 \n"
	"BL	sub_FF8755A4_my \n" // ------------------------>
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #84] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"BLNE	sub_FF876538 \n"
		"mov	r0, #0	\n" // ; 0x0
	"loc_FF876898:\n"
		"ldmia	sp!, {r3, r4, r5, pc} \n"
    );
}

//     sub_FF86EE0C -> sub_FF875414
// Extracted method: (ff875414-ff8755a0)
// Overridden calls:
// sub_FF86EDAC -> sub_FF875380
// sub_FF870378 -> sub_FF8766E0
void __attribute__((naked,noinline)) sub_FF875414_my() {
	asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"ldr	r4,  =0x000059c0 \n"
		"ldr	r3,  =0x0000201b \n"
		"ldr	r2, [r4, #148] \n"
		"sub	lr, r3, #23	\n" // ; 0x17
		"cmp	r2, #0	\n" // ; 0x0
		"cmpne	r0, r3 \n"
		"cmpne	r0, lr \n"
		"subne	ip, r0, #12288	\n" // ; 0x3000
		"subnes	ip, ip, #6	\n" // ; 0x6
		"BNE	loc_FF875594 \n"
		"ldr	ip,  =0x00001162 \n"
		"mov	r5, #0	\n" // ; 0x0
		"cmp	r0, ip \n"
		"mov	r1, #1	\n" // ; 0x1
		"BEQ	loc_FF8754C0 \n"
		"BGT	loc_FF8754CC \n"
		"ldr	ip,  =0x000010a9 \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF875548 \n"
		"BGT	loc_FF87549C \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #3	\n" // ; 0x3
		"BEQ	loc_FF875494 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #5	\n" // ; 0x5
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #8	\n" // ; 0x8
		"BEQ	loc_FF8754C0 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #97	\n" // ; 0x61
		"BNE	loc_FF87559C \n"
	"loc_FF875494:\n"
		"str	r5, [r4, #108] \n"
		"B	loc_FF875540 \n"
	"loc_FF87549C:\n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #173	\n" // ; 0xad
		"subne	ip, r0, #4096	\n" // ; 0x1000
		"subnes	ip, ip, #175	\n" // ; 0xaf
		"BEQ	loc_FF875548 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #184	\n" // ; 0xb8
		"BNE	loc_FF87559C \n"
		"str	r1, [r4, #52] \n"
	"loc_FF8754C0:\n"
		"str	r1, [r4, #148] \n"
		"BL	sub_FF874980 \n"
		"B	loc_FF875550 \n"
	"loc_FF8754CC:\n"
		"cmp	r0, r3 \n"
		"BEQ	loc_FF875558 \n"
		"BGT	loc_FF8754FC \n"
		"sub	ip, r0, #4352	\n" // ; 0x1100
		"subs	ip, ip, #133	\n" // ; 0x85
		"subne	ip, r0, #4352	\n" // ; 0x1100
		"subnes	ip, ip, #134	\n" // ; 0x86
		"BEQ	loc_FF875594 \n"
		"cmp	r0, lr \n"
		"BNE	loc_FF87559C \n"
	//	"BL	sub_FF875380 \n"
		"BL	sub_FF875380_my \n" // ------------------------>
		"B	loc_FF875594 \n"
	"loc_FF8754FC:\n"
		"sub	ip, r0, #12288	\n" // ; 0x3000
		"subs	ip, ip, #1	\n" // ; 0x1
		"BEQ	loc_FF8754C0 \n"
		"sub	ip, r0, #12288	\n" // ; 0x3000
		"subs	ip, ip, #272	\n" // ; 0x110
		"subne	ip, r0, #12544	\n" // ; 0x3100
		"subnes	ip, ip, #17	\n" // ; 0x11
		"BNE	loc_FF87559C \n"
		"ldr	r1, =0xff875748 \n" // ; (746e455f)  *"_EntryStartRecMode"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #1	\n" // ; 0x1
		"BL	sub_FF8788AC \n"
		"ldr	r0, [r4, #80] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF875574 \n"
	"loc_FF875540:\n"
		"BL	sub_FF876568 \n"
		"B	loc_FF875594 \n"
	"loc_FF875548:\n"
		"str	r1, [r4, #148] \n"
		"BL	sub_FF875220 \n"
	"loc_FF875550:\n"
		"BL	sub_FF8765F4 \n"
		"B	loc_FF875594 \n"
	"loc_FF875558:\n"
		"cmp	r2, #0	\n" // ; 0x0
		"BEQ	loc_FF87559C \n"
		"ldr	r0, [r4, #96] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLNE	sub_FF87FF9C \n" // <unknown_libname_96 +43572>
		"ldmia	sp!, {r4, r5, r6, lr} \n"
	//	"B	sub_FF8766E0 \n"
		"B	sub_FF8766E0_my \n" // ------------------------>
	"loc_FF875574:\n"
		"ldr	r0, [r4, #104] \n"
		"ldr	r1, [r4, #124] \n"
		"orrs	r0, r0, r1 \n"
		"BLEQ	sub_FF87A524 \n"
		"BL	sub_FF877D20 \n"
		"BL	sub_FF877EBC \n"
		"BL	sub_FF82A478 \n"
		"str	r5, [r4, #104] \n"
	"loc_FF875594:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, r5, r6, pc} \n"
	"loc_FF87559C:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, r5, r6, pc} \n"
    );
}

// sub_FF870378 -> sub_FF8766E0
// Extracted method: (ff8766e0-ff876720)
// Overridden calls:
// sub_FF86EDAC -> sub_FF875380
void __attribute__((naked,noinline)) sub_FF8766E0_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"BL	sub_FF874B2C \n"
		"ldr	r1,  =0x000059c0 \n"
		"ldr	r0, [r1, #52] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r1, #48] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF876710 \n"
		"BL	sub_FF87633C \n"
		"BL	sub_FF877EBC \n"
		"BL	sub_FF87811C \n"
		"B	loc_FF87671C \n"
	"loc_FF876710:\n"
		"BL	sub_FF877EBC \n"
		"BL	sub_FF87811C \n"
//	"BL	sub_FF875380 \n"
	"BL	sub_FF875380_my \n" // ------------------------>
	"loc_FF87671C:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
    );
}

// sub_FF870550 -> sub_FF87689C
// Extracted method: (ff87689c-ff876974)
// Overridden calls:
// sub_FF86EDAC -> sub_FF875380
void __attribute__((naked,noinline)) sub_FF87689C_my() {
	asm volatile (
		"ldr	ip,  =0x00005001 \n"
		"stmdb	sp!, {r4, lr} \n"
		"cmp	r0, ip \n"
		"BEQ	loc_FF8768D8 \n"
		"BGT	loc_FF876914 \n"
		"sub	ip, r0, #8192	\n" // ; 0x2000
		"subs	ip, ip, #4	\n" // ; 0x4
		"BEQ	loc_FF8768D8 \n"
		"sub	ip, r0, #12288	\n" // ; 0x3000
		"subs	ip, ip, #10	\n" // ; 0xa
		"BNE	loc_FF876928 \n"
		"ldr	r1, =0xff8769cc \n" // ; (61657243)  *"CreatePBController"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"BL	sub_FF880DDC \n"
	"loc_FF8768D8:\n"
		"ldr	r4,  =0x000059c0 \n"
		"ldr	r0, [r4, #56] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #64] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #68] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #72] \n"
		"cmpne	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #28] \n"
		"ldrne	r1, [r4, #32] \n"
		"orrnes	r0, r0, r1 \n"
		"BEQ	loc_FF876930 \n"
		"BL	sub_FF875220 \n"
		"B	loc_FF876948 \n"
	"loc_FF876914:\n"
		"sub	ip, r0, #20480	\n" // ; 0x5000
		"subs	ip, ip, #3	\n" // ; 0x3
		"subne	ip, r0, #20480	\n" // ; 0x5000
		"subnes	ip, ip, #6	\n" // ; 0x6
		"BEQ	loc_FF8768D8 \n"
	"loc_FF876928:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, pc} \n"
	"loc_FF876930:\n"
		"BL	sub_FF8752BC \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF876970 \n"
		"BL	sub_FF8751A4 \n"
		"cmn	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF876950 \n"
	"loc_FF876948:\n"
//	"BL	sub_FF875380 \n"
	"BL	sub_FF875380_my \n" // ------------------------>
		"B	loc_FF876970 \n"
	"loc_FF876950:\n"
		"BL	sub_FF876BF8 \n"
		"ldr	r0, [r4, #104] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BLEQ	sub_FF82A4F4 \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r4, #104] \n"
		"mov	r0, #11	\n" // ; 0xb
		"BL	sub_FF874CFC \n"
	"loc_FF876970:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, pc} \n"
    );
}
