#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "../../leds.h"

static long *nrflag = (long*)0x9F90;

#include "../../../generic/capt_seq.c"

// sub_FF931550 -> sub_FF939E24
// Extracted method: (ff939e24-ff939e94)
void __attribute__((naked,noinline)) sub_FF939E24_my(long p) {
	asm volatile (
		"stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, lr} \n"
		"mov	r6, #0	\n" // ; 0x0
		"mov	r4, r0 \n"
		"BL	sub_FF93A94C \n"
		"mvn	r1, #0	\n" // ; 0x0
		"BL	sub_FF827C04 \n"
		"mov	r2, #4	\n" // ; 0x4
		"add	r1, sp, #8	\n" // ; 0x8
		"mov	r0, #138	\n" // ; 0x8a
		"BL	sub_FF86CD80 \n" // <PT_GetPropertyCaseString -839880>
		"tst	r0, #1	\n" // ; 0x1
		"movne	r1, #536	\n" // ; 0x218
		"ldrne	r0, =0xff939ff4 \n" // ; (61437353)  *"SsCaptureSeq.c"
		"BLNE	sub_FF81BDB8 \n" // <DebugAssert -1171616>
		"ldr	r8,  =0x00019b38 \n"
		"ldr	r5,  =0x00019a84 \n"
		"ldrsh	r1, [r8, #14] \n"
		"ldr	r0, [r5, #124] \n"
		"BL	sub_FF8F09B8 \n"
		"BL	sub_FF8451A4 \n"
		"ldr	r2,  =0x00008d18 \n"
		"add	r3, r4, #140	\n" // ; 0x8c
		"strh	r0, [r4, #136] \n"
		"strd	r2, [sp] \n"
		"mov	r1, r0 \n"
		"ldrh	r0, [r5, #84] \n"
		"ldrsh	r2, [r8, #12] \n"
		"ldr	r3,  =0x00008d14 \n"
		"BL	sub_FF93AE38 \n"
			"BL     capt_seq_hook_set_nr \n" // +
			"BL		sub_FF939E98 \n" // + continue code in rom
 );
}

// sub_FF85C054 -> sub_FF86CF10
// Extracted method: (ff85e18c-ff85e248)
// Overridden calls:
// sub_FF931550 -> sub_FF939E24
// 1 add
void __attribute__((naked,noinline)) sub_FF85E18C_my() {
	asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"ldr	r4, [r0, #12] \n"
		"ldr	r6,  =0x00019a84 \n"
		"ldr	r0, [r4, #8] \n"
		"mov	r5, #0	\n" // ; 0x0
		"orr	r0, r0, #1	\n" // ; 0x1
		"str	r0, [r4, #8] \n"
		"ldr	r0, [r6, #36] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"moveq	r0, #2	\n" // ; 0x2
		"BLEQ	sub_FF8581D0 \n"
		"BL	sub_FF938748 \n"
		"ldr	r0, [r6, #36] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF85E20C \n"
		"mov	r0, r4 \n"
		"BL	sub_FF938BDC \n"
		"tst	r0, #1	\n" // ; 0x1
		"movne	r2, r4 \n"
		"ldmneia	sp!, {r4, r5, r6, lr} \n"
		"movne	r1, #1	\n" // ; 0x1
		"BNE	sub_FF85C418 \n"
		"BL	sub_FF95B8EC \n"
		"BL	sub_FF86CF10 \n"
		"str	r0, [r4, #20] \n"
		"mov	r0, r4 \n"
		"BL	sub_FF939D3C \n"
		"BL	sub_FF93A7D4 \n"
		"mov	r0, r4 \n"
//	"BL	sub_FF939E24 \n"
	"BL	sub_FF939E24_my \n" // ------------------------>
			"BL     capt_seq_hook_raw_here\n"  // +
		"mov	r5, r0 \n"
		"B	loc_FF85E21C \n"
	"loc_FF85E20C:\n"
		"ldr	r0,  =0x000054b8 \n"
		"ldr	r0, [r0, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r5, #29	\n" // ; 0x1d
	"loc_FF85E21C:\n"
		"BL	sub_FF93B7EC \n"
		"BL	sub_FF93B828 \n"
		"mov	r2, r4 \n"
		"mov	r1, #1	\n" // ; 0x1
		"mov	r0, r5 \n"
		"BL	sub_FF85C418 \n"
		"BL	sub_FF93A1F0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r4, #8] \n"
		"orrne	r0, r0, #8192	\n" // ; 0x2000
		"strne	r0, [r4, #8] \n"
		"ldmia	sp!, {r4, r5, r6, pc} \n"
 );
}

// Extracted method: (ff85de08-ff85e0a0)
// sub_FF85DE08
// Overridden calls:
// sub_FF85C054 -> sub_FF85E18C
// 1 added
void __attribute__((naked,noinline)) task_CaptSeqTask_my() {
	asm volatile (
		"stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr} \n"
		"ldr	r6,  =0x00019a84 \n"
		"ldr	r5,  =0x000054b8 \n"
		"mov	r9, #1	\n" // ; 0x1
		"mov	r7, #0	\n" // ; 0x0
	"loc_FF85DE1C:\n"
		"ldr	r0, [r5, #12] \n"
		"mov	r2, #0	\n" // ; 0x0
		"mov	r1, sp \n"
		"BL	sub_FF827E54 \n"
		"tst	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF85DE48 \n"
		"ldr	r1,  =0x0000048e \n"
		"ldr	r0, =0xff85dae0 \n" // ; (68537353)  *"SsShootTask.c"
		"BL	sub_FF81BDB8 \n" // <DebugAssert -270468>
		"BL	sub_FF81BB70 \n" // <ExitTask -271056>
		"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, pc} \n"
	"loc_FF85DE48:\n"
		"ldr	r0, [sp] \n"
		"ldr	r1, [r0] \n"
		"cmp	r1, #27	\n" // ; 0x1b
		"addls	pc, pc, r1, lsl #2 \n"
		"B	loc_FF85E068 \n"
		"B	loc_FF85DECC \n"
		"B	loc_FF85DF34 \n"
		"B	loc_FF85DF3C \n"
		"B	loc_FF85DF54 \n"
		"B	loc_FF85DF48 \n"
		"B	loc_FF85DF5C \n"
		"B	loc_FF85DF64 \n"
		"B	loc_FF85DF6C \n"
		"B	loc_FF85DFC4 \n"
		"B	loc_FF85DFD0 \n"
		"B	loc_FF85DFD8 \n"
		"B	loc_FF85DFE0 \n"
		"B	loc_FF85DFE8 \n"
		"B	loc_FF85DFF0 \n"
		"B	loc_FF85DFF8 \n"
		"B	loc_FF85E000 \n"
		"B	loc_FF85E008 \n"
		"B	loc_FF85E014 \n"
		"B	loc_FF85E01C \n"
		"B	loc_FF85E024 \n"
		"B	loc_FF85E02C \n"
		"B	loc_FF85E038 \n"
		"B	loc_FF85E040 \n"
		"B	loc_FF85E048 \n"
		"B	loc_FF85E050 \n"
		"B	loc_FF85E058 \n"
		"B	loc_FF85E060 \n"
		"B	loc_FF85E074 \n"

	"loc_FF85DECC:\n"
		"BL	sub_FF93876C \n"
                "BL     shooting_expo_param_override\n"  // +
		"BL	sub_FF85BFE8 \n"
		"ldr	r0, [r6, #36] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF85E074 \n"
		"BL	sub_FF85D7B0 \n"
		"mov	r4, r0 \n"
		"ldr	r0, [r6, #36] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF85DF14 \n"
		"mov	r0, #12	\n" // ; 0xc
		"BL	sub_FF860E24 \n"
		"tst	r0, #1	\n" // ; 0x1
		"strne	r9, [r5, #4] \n"
		"ldrne	r0, [r4, #8] \n"
		"orrne	r0, r0, #1073741824	\n" // ; 0x40000000
		"strne	r0, [r4, #8] \n"
		"BNE	loc_FF85E074 \n"
	"loc_FF85DF14:\n"
		"BL	sub_FF95B8EC \n"
		"BL	sub_FF86CF10 \n"
		"str	r0, [r4, #20] \n"
		"mov	r0, r4 \n"

//	"BL	sub_FF939E24 \n"
	"BL	sub_FF939E24_my \n"
			"BL     capt_seq_hook_raw_here\n"  // +

		"tst	r0, #1	\n" // ; 0x1
		"strne	r9, [r5, #4] \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DF34:\n"
//	"BL	sub_FF85E18C \n"
	"BL	sub_FF85E18C_my \n" // ------------------------>
		"B	loc_FF85DF4C \n"
	"loc_FF85DF3C:\n"
		"mov	r0, #1	\n" // ; 0x1
		"BL	sub_FF938914 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DF48:\n"
		"BL	sub_FF938404 \n"
	"loc_FF85DF4C:\n"
		"str	r7, [r6, #36] \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DF54:\n"
		"BL	sub_FF938738 \n"
		"B	loc_FF85DF4C \n"
	"loc_FF85DF5C:\n"
		"BL	sub_FF938740 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DF64:\n"
		"BL	sub_FF938834 \n"
		"B	loc_FF85DFC8 \n"
	"loc_FF85DF6C:\n"
		"ldr	r4, [r0, #12] \n"
		"BL	sub_FF938748 \n"
		"mov	r0, r4 \n"
		"BL	sub_FF938F5C \n"
		"tst	r0, #1	\n" // ; 0x1
		"mov	r8, r0 \n"
		"BNE	loc_FF85DFAC \n"
		"BL	sub_FF86CF10 \n"
		"str	r0, [r4, #20] \n"
		"mov	r0, r4 \n"
		"BL	sub_FF939D3C \n"
		"mov	r0, r4 \n"
		"BL	sub_FF93A250 \n"
		"mov	r8, r0 \n"
		"ldr	r0, [r4, #20] \n"
		"BL	sub_FF86D11C \n"
	"loc_FF85DFAC:\n"
		"BL	sub_FF938738 \n"
		"mov	r2, r4 \n"
		"mov	r1, #9	\n" // ; 0x9
		"mov	r0, r8 \n"
		"BL	sub_FF85C418 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DFC4:\n"
		"BL	sub_FF938894 \n"
	"loc_FF85DFC8:\n"
		"BL	sub_FF85BFE8 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DFD0:\n"
		"BL	sub_FF938738 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DFD8:\n"
		"BL	sub_FF9391C8 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DFE0:\n"
		"BL	sub_FF9393B0 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DFE8:\n"
		"BL	sub_FF939440 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DFF0:\n"
		"BL	sub_FF9394F4 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85DFF8:\n"
		"BL	sub_FF9396EC \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E000:\n"
		"BL	sub_FF93973C \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E008:\n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF9397C0 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E014:\n"
		"BL	sub_FF939910 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E01C:\n"
		"BL	sub_FF9399A4 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E024:\n"
		"BL	sub_FF939A6C \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E02C:\n"
		"BL	sub_FF938A38 \n"
		"BL	sub_FF824CFC \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E038:\n"
		"BL	sub_FF9395B0 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E040:\n"
		"BL	sub_FF93961C \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E048:\n"
		"BL	sub_FF93B7D0 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E050:\n"
		"BL	sub_FF93B7EC \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E058:\n"
		"BL	sub_FF93B7FC \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E060:\n"
		"BL	sub_FF93B828 \n"
		"B	loc_FF85E074 \n"
	"loc_FF85E068:\n"
		"ldr	r1,  =0x0000058e \n"
		"ldr	r0,  =0xff85dae0 \n"
		"BL	sub_FF81BDB8 \n" // <DebugAssert -271032>
	"loc_FF85E074:\n"
		"ldr	r0, [sp] \n"
		"ldr	r1, [r0, #4] \n"
		"ldr	r0, [r5, #8] \n"
		"BL	sub_FF827BD0 \n"
		"ldr	r4, [sp] \n"
		"ldr	r0, [r4, #8] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldreq	r1,  =0x0000010d \n"
		"ldreq	r0,  =0xff85dae0 \n"
		"BLEQ	sub_FF81BDB8 \n" // <DebugAssert -271072>
		"str	r7, [r4, #8] \n"
		"B	loc_FF85DE1C \n"
    );
} //#fe
