#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x67c0;    // ff95f134: at taskcreate_ShutterSoundTask()

#include "../../../generic/capt_seq.c"

// ff87a310: task_CaptSeqTask()
void __attribute__((naked,noinline)) capt_seq_task() {
  asm volatile (
	"push	{r3, r4, r5, r6, r7, r8, r9, lr}\n"
	"ldr	r6, =0x00002b9c\n" // was: "[pc, #-1152]	; ff879e9c" 
	"ldr	r4, =0x00039644\n" // was: "[pc, #-1104]	; ff879ed0" 
	"ldr	r9, =0x1\n" // was: "mov ..., #1"
	"ldr	r7, =0x0\n" // was: "mov ..., #0"
"loc_ff87a324:\n"
	"ldr	r0, [r6, #4]\n"
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
	"mov	r1, sp\n"
	"bl	sub_ff8396e4\n"
	"tst	r0, #1\n"	// 0x1
	"beq	loc_ff87a350\n"
	"ldr	r1, =0x000005b4\n" // was: "[pc, #1352]	; ff87a88c" 
	"ldr	r0, =0xff879ea0\n" // was: "[pc, #1336]	; ff87a880"  **"SsShootTask.c"
	"bl	sub_ff81eb14\n"
	"bl	sub_ff81eacc\n"
	"pop	{r3, r4, r5, r6, r7, r8, r9, pc}\n"
"loc_ff87a350:\n"
	"ldr	r0, [sp]\n"
	"ldr	r1, [r0]\n"
	"cmp	r1, #29\n"	// 0x1d
	"addls	pc, pc, r1, lsl #2\n"
	"b	loc_ff87a5ec\n"
	"b	loc_ff87a3dc\n" // 0 jumptable start
	"b	loc_ff87a440\n" // 1
	"b	loc_ff87a47c\n" // 2
	"b	loc_ff87a490\n" // 3
	"b	loc_ff87a488\n" // 4
	"b	loc_ff87a498\n" // 5
	"b	loc_ff87a4a0\n" // 6
	"b	loc_ff87a4a8\n" // 7
	"b	loc_ff87a500\n" // 8
	"b	loc_ff87a528\n" // 9
	"b	loc_ff87a50c\n" // 10
	"b	loc_ff87a518\n" // 11
	"b	loc_ff87a520\n" // 12
	"b	loc_ff87a530\n" // 13
	"b	loc_ff87a538\n" // 14
	"b	loc_ff87a540\n" // 15
	"b	loc_ff87a548\n" // 16
	"b	loc_ff87a550\n" // 17
	"b	loc_ff87a55c\n" // 18
	"b	loc_ff87a564\n" // 19
	"b	loc_ff87a56c\n" // 20
	"b	loc_ff87a574\n" // 21
	"b	loc_ff87a57c\n" // 22
	"b	loc_ff87a588\n" // 23
	"b	loc_ff87a590\n" // 24
	"b	loc_ff87a598\n" // 25
	"b	loc_ff87a5a0\n" // 26
	"b	loc_ff87a5a8\n" // 27
	"b	loc_ff87a5b4\n" // 28
	"b	loc_ff87a5f8\n" // 29
"loc_ff87a3dc:\n" // jumptable entry 0
	"bl	sub_ff87aca0\n"
        "bl     shooting_expo_param_override\n" // added
	"bl	sub_ff8780ac\n"

        // this code added to avoid some incorrect behavior if overrides are used.
        // but it can cause some unexpected side effects. In this case, remove this code!
        //"mov    r0, #0\n"
        //"str    r0, [r4, #36]\n"  // 0x24 fixes overrides  behavior at short shutter press

	"ldr	r0, [r4, #36]\n"
	"cmp	r0, #0\n"	// 0x0
	"beq	loc_ff87a5f8\n"
	"bl	sub_ff879b80\n"
	"mov	r5, r0\n"
	"ldr	r0, [r4, #36]\n"
	"cmp	r0, #0\n"	// 0x0
	"beq	loc_ff87a424\n"
	"ldr	r0, =0xc\n" // was: "mov ..., #12"
	"bl	sub_ff87f174\n"
	"tst	r0, #1\n"	// 0x1
	"strne	r9, [r6, #16]\n"
	"ldrne	r0, [r5, #8]\n"
	"orrne	r0, r0, #1073741824\n"	// 0x40000000
	"strne	r0, [r5, #8]\n"
	"bne	loc_ff87a5f8\n"
"loc_ff87a424:\n"
	"mov	r0, r5\n"
	"bl	sub_ff879e24\n"
	"mov	r0, r5\n"

	//"bl	sub_ff95f120\n"
	"bl	sub_ff95f120_my\n" // taskcreate_ShutterSoundTask()
        "bl     capt_seq_hook_raw_here\n" // added

	"tst	r0, #1\n"	// 0x1
	"strne	r9, [r6, #16]\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a440:\n" // jumptable entry 1
	"ldr	r0, [r4, #36]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff87a46c\n"
	"ldr	r0, =0xc\n" // was: "mov ..., #12"
	"bl	sub_ff87f174\n"
	"tst	r0, #1\n"	// 0x1
	"ldrne	r0, [sp]\n"
	"ldrne	r1, =0x1\n" // was: "mov ..., #1"
	"ldrne	r2, [r0, #12]\n"
	"ldrne	r0, =0x1\n" // was: "mov ..., #1"
	"bne	loc_ff87a4f8\n"
"loc_ff87a46c:\n"
	"ldr	r0, [sp]\n"
	//"bl	sub_ff87a714\n"
	"bl	sub_ff87a714_my\n"
"loc_ff87a474:\n" // 2 refs
	"str	r7, [r4, #36]\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a47c:\n" // jumptable entry 2
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff87af44\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a488:\n" // jumptable entry 4
	"bl	sub_ff87a8bc\n"
	"b	loc_ff87a474\n"
"loc_ff87a490:\n" // jumptable entry 3
	"bl	sub_ff87ac80\n"
	"b	loc_ff87a474\n"
"loc_ff87a498:\n" // jumptable entry 5
	"bl	sub_ff87ac88\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a4a0:\n" // jumptable entry 6
	"bl	sub_ff87ae54\n"
	"b	loc_ff87a504\n"
"loc_ff87a4a8:\n" // jumptable entry 7
	"ldr	r5, [r0, #12]\n"
	"bl	sub_ff87ac90\n"
	"mov	r0, r5\n"
	"bl	sub_ff95e0f4\n"
	"tst	r0, #1\n"	// 0x1
	"mov	r8, r0\n"
	"bne	loc_ff87a4e8\n"
	"bl	sub_ff88c3d4\n"
	"str	r0, [r5, #24]\n"
	"mov	r0, r5\n"
	"bl	sub_ff95f038\n"
	"mov	r0, r5\n"
	"bl	sub_ff95f3d4\n"
	"mov	r8, r0\n"
	"ldr	r0, [r5, #24]\n"
	"bl	sub_ff88c60c\n"
"loc_ff87a4e8:\n"
	"bl	sub_ff87ac80\n"
	"mov	r2, r5\n"
	"ldr	r1, =0x9\n" // was: "mov ..., #9"
	"mov	r0, r8\n"
"loc_ff87a4f8:\n"
	"bl	sub_ff87856c\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a500:\n" // jumptable entry 8
	"bl	sub_ff87aebc\n"
"loc_ff87a504:\n"
	"bl	sub_ff8780ac\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a50c:\n" // jumptable entry 10
	"ldr	r0, [r4, #84]\n"
	"bl	sub_ff87b2e8\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a518:\n" // jumptable entry 11
	"bl	sub_ff87b59c\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a520:\n" // jumptable entry 12
	"bl	sub_ff87b630\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a528:\n" // jumptable entry 9
	"bl	sub_ff87ac80\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a530:\n" // jumptable entry 13
	"bl	sub_ff95e30c\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a538:\n" // jumptable entry 14
	"bl	sub_ff95e520\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a540:\n" // jumptable entry 15
	"bl	sub_ff95e5b8\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a548:\n" // jumptable entry 16
	"bl	sub_ff95e688\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a550:\n" // jumptable entry 17
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff95e8f0\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a55c:\n" // jumptable entry 18
	"bl	sub_ff95ea40\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a564:\n" // jumptable entry 19
	"bl	sub_ff95ead0\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a56c:\n" // jumptable entry 20
	"bl	sub_ff95eb90\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a574:\n" // jumptable entry 21
	"bl	sub_ff87b0bc\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a57c:\n" // jumptable entry 22
	"bl	sub_ff87b164\n"
	"bl	sub_ff8376fc\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a588:\n" // jumptable entry 23
	"bl	sub_ff95e754\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a590:\n" // jumptable entry 24
	"bl	sub_ff95e7c0\n"
"loc_ff87a594:\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a598:\n" // jumptable entry 25
	"bl	sub_ff87d77c\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a5a0:\n" // jumptable entry 26
	"bl	sub_ff87d804\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a5a8:\n" // jumptable entry 27
	"bl	sub_ff87d860\n"
	"bl	sub_ff87d820\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a5b4:\n" // jumptable entry 28
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff95fd98\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff95fecc\n"
	"ldrh	r0, [r4, #148]\n"
	"cmp	r0, #4\n"	// 0x4
	"ldrneh	r0, [r4]\n" // compiler doesn't like ldrhne, -> ldrneh
	"subne	ip, r0, #33280\n"	// 0x8200
	"subnes	ip, ip, #42\n"	// 0x2a compiler doesn't like subsne, -> subnes
	"bne	loc_ff87a5f8\n"
	"bl	sub_ff87d804\n"
	"bl	sub_ff87dd74\n"
	"bl	sub_ff87dc84\n"
	"b	loc_ff87a5f8\n"
"loc_ff87a5ec:\n" // jumptable default
	"ldr	r1, =0x0000070b\n" // was: "[pc, #668]	; ff87a890" 
	"ldr	r0, =0xff879ea0\n" // was: "[pc, #648]	; ff87a880"  **"SsShootTask.c"
	"bl	sub_ff81eb14\n"
"loc_ff87a5f8:\n" // 30 refs jumptable entry 29
	"ldr	r0, [sp]\n"
	"ldr	r1, [r0, #4]\n"
	"ldr	r0, [r6]\n"
	"bl	sub_ff883f9c\n"
	"ldr	r5, [sp]\n"
	"ldr	r0, [r5, #8]\n"
	"cmp	r0, #0\n"	// 0x0
	"ldreq	r1, =0x00000132\n" // was: "[pc, #632]	; ff87a894" 
	"ldreq	r0, =0xff879ea0\n" // was: "subeq	r0, pc, #1920"   *"SsShootTask.c"
	"bleq	sub_ff81eb14\n"
	"str	r7, [r5, #8]\n"
	"b	loc_ff87a324\n"
    );
}

// ROM:FF970A8C taskcreate_ShutterSoundTask(), LOCATION: SsCaptureSeq.c:0
void __attribute__((naked,noinline)) sub_ff95f120_my() {
  asm volatile (
	"push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, lr}\n"
	"mov	r4, r0\n"
	"bl	sub_ff96009c\n"
	"mvn	r1, #0\n"	// 0x0
	"bl	sub_ff883fd0\n"
	"ldr	r5, =0x000067c0\n" // was: "[pc, #-552]	; ff95ef14" 
	"ldr	r0, [r5, #12]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff95f170\n"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f2c\n"
	"str	r0, [r5, #12]\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	"ldr	r3, =0xff95ec80\n" // was: "[pc, #496]	; ff95f354" 
	"ldr	r0, =0xff95f358\n" // was: "add	r0, pc, #496"   *"ShutterSoundTask"
	"ldr	r2, =0x400\n" // was: "mov ..., #1024"
	"ldr	r1, =0x17\n" // was: "mov ..., #23"
	"bl	sub_ff839ef8\n"
"loc_ff95f170:\n"
	"ldr	r2, =0x4\n" // was: "mov ..., #4"
	"add	r1, sp, #8\n"	// 0x8
	"ldr	r0, =0x8a\n" // was: "mov ..., #138"
	"bl	sub_ff88c244\n"
	"tst	r0, #1\n"	// 0x1
	"ldrne	r1, =0x000003cd\n" // was: "[pc, #480]	; ff95f36c" 
	"ldrne	r0, =0xff95ef18\n" // was: "subne	r0, pc, #632"   *"SsCaptureSeq.c"
	"blne	sub_ff81eb14\n"
	"ldr	r6, =0x00039708\n" // was: "[pc, #420]	; ff95f33c" 
	"ldr	r7, =0x00039644\n" // was: "[pc, #-604]	; ff95ef40" 
	"ldr	r3, [r6]\n"
	"ldrsh	r2, [r6, #12]\n"
	"ldrsh	r1, [r6, #14]\n"
	"ldr	r0, [r7, #136]\n"
	"bl	sub_ff9294cc\n"
	"bl	sub_ff862ca4\n" // GetCCDTemperature()
	"ldr	r3, =0x000067c8\n" // was: "[pc, #440]	; ff95f370" 
	"strh	r0, [r4, #164]\n"
	"sub	r2, r3, #4\n"	// 0x4
	"strd	r2, [sp]\n"
	"mov	r1, r0\n"
	"ldrh	r0, [r7, #92]\n"
	"ldrsh	r2, [r6, #12]\n"
	"sub	r3, r3, #8\n"	// 0x8
	"bl	sub_ff961c40\n"

        "bl     wait_until_remote_button_is_released\n"
        "bl     capt_seq_hook_set_nr\n"
        "b      sub_ff95f1d4\n" // continue in Canon firmware
/*
	"ldr	r0, [r4, #28]\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrne	r0, =0x1\n" // was: "mov ..., #1"
	"strne	r0, [r5]\n"
	"ldr	r0, [r5]\n"
	"lsl	r1, r0, #16\n"
	"ldrh	r0, [r7, #92]\n"
	"lsr	r1, r1, #16\n"
	"bl	sub_ff961d9c\n"
	"str	r0, [r4, #172]\n"
	"ldr	r0, [r5, #4]\n"
	"bl	sub_ff92c5c4\n"
	"ldr	r0, [r5, #8]\n"
	"bl	sub_ff8b1504\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff8b151c\n"
	"mov	r1, r4\n"
	"ldr	r0, =0xff95ecf0\n" // was: "sub	r0, pc, #1328"  
	"bl	sub_ff8b14e0\n"
	"ldr	r0, [r5]\n"
	"cmp	r0, #1\n"	// 0x1
	"beq	loc_ff95f248\n"
	"cmp	r0, #2\n"	// 0x2
	"beq	loc_ff95f260\n"
	"cmp	r0, #3\n"	// 0x3
	"beq	loc_ff95f280\n"
	"cmp	r0, #7\n"	// 0x7
	"bne	loc_ff95f29c\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
"loc_ff95f248:\n"
	"bl	sub_ff8b1510\n"
	"ldr	r2, [sp, #8]\n"
	"add	r1, sp, #12\n"	// 0xc
	"mov	r0, r4\n"
	"bl	sub_ff95ef78\n"
	"b	loc_ff95f278\n"
"loc_ff95f260:\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff8b1510\n"
	"ldr	r2, [sp, #8]\n"
	"add	r1, sp, #12\n"	// 0xc
	"mov	r0, r4\n"
	"bl	sub_ff95f474\n"
"loc_ff95f278:\n" // 2 refs
	"mov	r8, r0\n"
	"b	loc_ff95f2a8\n"
"loc_ff95f280:\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff8b1510\n"
	"ldr	r2, [sp, #8]\n"
	"add	r1, sp, #12\n"	// 0xc
	"mov	r0, r4\n"
	"bl	sub_ff95f540\n"
	"b	loc_ff95f278\n"
"loc_ff95f29c:\n"
	"ldr	r1, =0x00000429\n" // was: "[pc, #208]	; ff95f374" 
	"ldr	r0, =0xff95ef18\n" // was: "sub	r0, pc, #912"   *"SsCaptureSeq.c"
	"bl	sub_ff81eb14\n"
"loc_ff95f2a8:\n"
	"tst	r8, #1\n"	// 0x1
	"movne	r0, r8\n"
	"bne	loc_ff95f32c\n"
	"ldr	r0, =0xff95ed2c\n" // was: "[pc, #188]	; ff95f378" 
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff8b14e0\n"
	"ldrh	r0, [r7]\n"
	"sub	ip, r0, #32768\n"	// 0x8000
	"subs	ip, ip, #524\n"	// 0x20c
	"bleq	sub_ff89d470\n"
	"ldr	r2, =0x000067c4\n" // was: "[pc, #164]	; ff95f37c" 
	"ldr	r0, [r4, #24]\n"
	"ldr	r3, =0x4\n" // was: "mov ..., #4"
	"ldr	r1, =0x45\n" // was: "mov ..., #69"
	"bl	sub_ff88c728\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff929534\n"
	"str	r0, [r4, #216]\n"
	"bl	sub_ff87ce94\n"
	"bl	sub_ff96009c\n"
	"ldr	r5, =0x0000044c\n" // was: "[pc, #128]	; ff95f380" 
	"ldr	r2, =0x00003a98\n" // was: "[pc, #-988]	; ff95ef28" 
	"ldr	r3, =0xff95ef18\n" // was: "sub	r3, pc, #1008"   *"SsCaptureSeq.c"
	"ldr	r1, =0x4\n" // was: "mov ..., #4"
	"str	r5, [sp]\n"
	"bl	sub_ff87f4f0\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrne	r0, =0xff95ef18\n" // was: "[pc, #104]	; ff95f384"  **"SsCaptureSeq.c"
	"movne	r1, r5\n"
	"blne	sub_ff81eb14\n"
	"ldrh	r0, [sp, #12]\n"
	"strh	r0, [r4, #20]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
"loc_ff95f32c:\n"
	"add	sp, sp, #16\n"	// 0x10
	"pop	{r4, r5, r6, r7, r8, pc}\n"
*/
    );
}

void __attribute__((naked,noinline)) sub_ff87a714_my() { // FF87D754
  asm volatile (
	"push	{r4, r5, r6, lr}\n"
	"ldr	r4, [r0, #12]\n"
	"ldr	r6, =0x00039644\n" // was: "[pc, #-2132]	; ff879ed0" 
	"ldr	r0, [r4, #8]\n"
	"ldr	r5, =0x0\n" // was: "mov ..., #0"
	"orr	r0, r0, #1\n"	// 0x1
	"str	r0, [r4, #8]\n"
	"ldr	r0, [r6, #36]\n"
	"cmp	r0, #0\n"	// 0x0
	"ldreq	r0, =0x2\n" // was: "mov ..., #2"
	"bleq	sub_ff876768\n"
	"bl	sub_ff87ac90\n"
	"ldr	r0, [r6, #36]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff87a7dc\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff95fd98\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff95fecc\n"
	"mov	r0, r4\n"
	"bl	sub_ff87b064\n"
	"mov	r0, r4\n"
	"bl	sub_ff95dd38\n"
	"cmp	r0, #0\n"	// 0x0
	"beq	loc_ff87a7a4\n"
	"bl	sub_ff95fdd8\n"
	"bl	sub_ff95ff10\n"
	"bl	sub_ff95ff60\n"
	"mov	r0, r4\n"
	"bl	sub_ff95de1c\n"
	"tst	r0, #1\n"	// 0x1
	"movne	r2, r4\n"
	"popne	{r4, r5, r6, lr}\n"
	"ldrne	r1, =0x1\n" // was: "mov ..., #1"
	"bne	sub_ff87856c\n"
	"b	loc_ff87a7b8\n"
"loc_ff87a7a4:\n"
	"mov	r0, r4\n"
	"bl	sub_ff95ddb8\n"
	"bl	sub_ff95fdd8\n"
	"bl	sub_ff95ff10\n"
	"bl	sub_ff95ff60\n"
"loc_ff87a7b8:\n"
	"mov	r0, r4\n"
	"bl	sub_ff879e24\n"
	"mov	r0, r4\n"
	"bl	sub_ff95f038\n"
	"bl	sub_ff95fb74\n"
	"mov	r0, r4\n"
	//"bl	sub_ff95f120\n"
	"bl	sub_ff95f120_my\n"
	"mov	r5, r0\n"
	"b	loc_ff87a7ec\n"
"loc_ff87a7dc:\n"
	"ldr	r0, =0x00002b9c\n" // was: "[pc, #-2376]	; ff879e9c" 
	"ldr	r0, [r0, #16]\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrne	r5, =0x1d\n" // was: "mov ..., #29"
"loc_ff87a7ec:\n"
	"bl	sub_ff87d804\n"
	"bl	sub_ff87d84c\n"
	"bl	sub_ff87d88c\n"
	"mov	r2, r4\n"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"mov	r0, r5\n"
	"bl	sub_ff87856c\n"
	"bl	sub_ff95f388\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrne	r0, [r4, #8]\n"
	"orrne	r0, r0, #8192\n"	// 0x2000
	"strne	r0, [r4, #8]\n"
	"pop	{r4, r5, r6, pc}\n"
    );
}

// ff8bab28: task_ExpDrvTask()
void __attribute__((naked,noinline)) exp_drv_task() { // was FF8C25DC
  asm volatile (
	"push	{r4, r5, r6, r7, r8, lr}\n"
	"sub	sp, sp, #32\n"	// 0x20
	"ldr	r8, =0x00000bb8\n" // was: "[pc, #-908]	; ff8ba7ac" 
	"ldr	r7, =0x00003f58\n" // was: "[pc, #2736]	; ff8bb5ec" 
	"ldr	r5, =0x00042ab0\n" // was: "[pc, #2764]	; ff8bb60c" 
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"add	r6, sp, #16\n"	// 0x10
	"str	r0, [sp, #12]\n"
"loc_ff8bab48:\n"
	"ldr	r0, [r7, #32]\n"
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
	"add	r1, sp, #28\n"	// 0x1c
	"bl	sub_ff8396e4\n"
	"ldr	r0, [sp, #12]\n"
	"cmp	r0, #1\n"	// 0x1
	"bne	loc_ff8bab94\n"
	"ldr	r0, [sp, #28]\n"
	"ldr	r0, [r0]\n"
	"cmp	r0, #19\n"	// 0x13
	"cmpne	r0, #20\n"	// 0x14
	"cmpne	r0, #21\n"	// 0x15
	"cmpne	r0, #22\n"	// 0x16
	"beq	loc_ff8bacf8\n"
	"cmp	r0, #40\n"	// 0x28
	"beq	loc_ff8bac80\n"
	"add	r1, sp, #12\n"	// 0xc
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff8baad8\n"
"loc_ff8bab94:\n"
	"ldr	r0, [sp, #28]\n"
	"ldr	r1, [r0]\n"
	"cmp	r1, #46\n"	// 0x2e
	"bne	loc_ff8babc4\n"
	"ldr	r0, [sp, #28]\n"
	"bl	sub_ff8bbe38\n"
	"ldr	r0, [r7, #28]\n"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff883f9c\n"
	"bl	sub_ff81eacc\n" // eventproc_export_ExitTask()
	"add	sp, sp, #32\n"	// 0x20
	"pop	{r4, r5, r6, r7, r8, pc}\n"
"loc_ff8babc4:\n"
	"cmp	r1, #45\n"	// 0x2d
	"bne	loc_ff8babe0\n"
	"ldr	r2, [r0, #140]!\n"
	"ldr	r1, [r0, #4]\n"
	"mov	r0, r1\n"
	"blx	r2\n"
	"b	loc_ff8bb120\n"
"loc_ff8babe0:\n"
	"cmp	r1, #38\n"	// 0x26
	"bne	loc_ff8bac30\n"
	"ldr	r0, [r7, #28]\n"
	"ldr	r1, =0x80\n" // was: "mov ..., #128"
	"bl	sub_ff883fd0\n"
	"ldr	r0, =0xff8b723c\n" // was: "[pc, #2580]	; ff8bb610" 
	"ldr	r1, =0x80\n" // was: "mov ..., #128"
	"bl	sub_ff952f00\n"
	"ldr	r0, [r7, #28]\n"
	"mov	r2, r8\n"
	"ldr	r1, =0x80\n" // was: "mov ..., #128"
	"bl	sub_ff883edc\n"
	"tst	r0, #1\n"	// 0x1
	"ldrne	r1, =0x00000e5f\n" // was: "[pc, #2552]	; ff8bb614" 
	"bne	loc_ff8bacec\n"
"loc_ff8bac1c:\n" // 5 refs
	"ldr	r1, [sp, #28]\n"
	"ldr	r0, [r1, #144]\n"
	"ldr	r1, [r1, #140]\n"
	"blx	r1\n"
	"b	loc_ff8bb120\n"
"loc_ff8bac30:\n"
	"cmp	r1, #39\n"	// 0x27
	"bne	loc_ff8bac78\n"
	"add	r1, sp, #12\n"	// 0xc
	"bl	sub_ff8baad8\n"
	"ldr	r0, [r7, #28]\n"
	"ldr	r1, =0x100\n" // was: "mov ..., #256"
	"bl	sub_ff883fd0\n"
	"ldr	r0, =0xff8b724c\n" // was: "[pc, #2500]	; ff8bb618" 
	"ldr	r1, =0x100\n" // was: "mov ..., #256"
	"bl	sub_ff953188\n"
	"ldr	r0, [r7, #28]\n"
	"mov	r2, r8\n"
	"ldr	r1, =0x100\n" // was: "mov ..., #256"
	"bl	sub_ff883edc\n"
	"tst	r0, #1\n"	// 0x1
	"beq	loc_ff8bac1c\n"
	"ldr	r1, =0x00000e69\n" // was: "[pc, #2468]	; ff8bb61c" 
	"b	loc_ff8bacec\n"
"loc_ff8bac78:\n"
	"cmp	r1, #40\n"	// 0x28
	"bne	loc_ff8bac90\n"
"loc_ff8bac80:\n"
	"ldr	r0, [sp, #28]\n"
	"add	r1, sp, #12\n"	// 0xc
	"bl	sub_ff8baad8\n"
	"b	loc_ff8bac1c\n"
"loc_ff8bac90:\n"
	"cmp	r1, #43\n"	// 0x2b
	"bne	loc_ff8baca8\n"
	"bl	sub_ff8aa3b8\n"
	"bl	sub_ff8aafec\n"
	"bl	sub_ff8aab3c\n"
	"b	loc_ff8bac1c\n"
"loc_ff8baca8:\n"
	"cmp	r1, #44\n"	// 0x2c
	"bne	loc_ff8bacf8\n"
	"ldr	r0, [r7, #28]\n"
	"ldr	r1, =0x4\n" // was: "mov ..., #4"
	"bl	sub_ff883fd0\n"
	"ldr	r1, =0xff8b726c\n" // was: "[pc, #-1252]	; ff8ba7e0" 
	"ldr	r0, =0xfffff400\n" // was: "[pc, #-1252]	; ff8ba7e4" 
	"ldr	r2, =0x4\n" // was: "mov ..., #4"
	"bl	sub_ff8a9e34\n"
	"bl	sub_ff8aa0bc\n"
	"ldr	r0, [r7, #28]\n"
	"mov	r2, r8\n"
	"ldr	r1, =0x4\n" // was: "mov ..., #4"
	"bl	sub_ff883df8\n"
	"tst	r0, #1\n"	// 0x1
	"beq	loc_ff8bac1c\n"
	"ldr	r1, =0x00000e91\n" // was: "[pc, #2352]	; ff8bb620" 
"loc_ff8bacec:\n" // 2 refs
	"ldr	r0, =0xff8b78ac\n" // was: "[pc, #-1344]	; ff8ba7b4"  **"ExpDrv.c"
	"bl	sub_ff81eb14\n"
	"b	loc_ff8bac1c\n"
"loc_ff8bacf8:\n" // 2 refs
	"ldr	r0, [sp, #28]\n"
	"ldr	r4, =0x1\n" // was: "mov ..., #1"
	"ldr	r1, [r0]\n"
	"cmp	r1, #17\n"	// 0x11
	"cmpne	r1, #18\n"	// 0x12
	"bne	loc_ff8bad68\n"
	"ldr	r1, [r0, #124]\n"
	"add	r1, r1, r1, lsl #1\n"
	"add	r1, r0, r1, lsl #2\n"
	"sub	r1, r1, #8\n"	// 0x8
	"ldm	r1, {r2, r3, r4}\n"
	"stm	r6, {r2, r3, r4}\n"
	"bl	sub_ff8b93fc\n"
	"ldr	r0, [sp, #28]\n"
	"ldr	r1, [r0, #124]\n"
	"ldr	r3, [r0, #140]\n"
	"ldr	r2, [r0, #144]\n"
	"add	r0, r0, #4\n"	// 0x4
	"blx	r3\n"
	"ldr	r0, [sp, #28]\n"
	"bl	sub_ff8bc1fc\n"
	"ldr	r0, [sp, #28]\n"
	"ldr	r1, [r0, #124]\n"
	"ldr	r3, [r0, #148]\n"
	"ldr	r2, [r0, #152]\n"
	"add	r0, r0, #4\n"	// 0x4
	"blx	r3\n"
	"b	loc_ff8bb060\n"
"loc_ff8bad68:\n"
	"cmp	r1, #19\n"	// 0x13
	"cmpne	r1, #20\n"	// 0x14
	"cmpne	r1, #21\n"	// 0x15
	"cmpne	r1, #22\n"	// 0x16
	"bne	loc_ff8bae20\n"
	"add	r3, sp, #12\n"	// 0xc
	"mov	r2, sp\n"
	"add	r1, sp, #16\n"	// 0x10
	"bl	sub_ff8b96d8\n"
	"cmp	r0, #1\n"	// 0x1
	"mov	r4, r0\n"
	"cmpne	r4, #5\n"	// 0x5
	"bne	loc_ff8badbc\n"
	"ldr	r0, [sp, #28]\n"
	"mov	r2, r4\n"
	"ldr	r1, [r0, #124]!\n"
	"ldr	ip, [r0, #16]!\n"
	"ldr	r3, [r0, #4]\n"
	"mov	r0, sp\n"
	"blx	ip\n"
	"b	loc_ff8badf4\n"
"loc_ff8badbc:\n"
	"ldr	r0, [sp, #28]\n"
	"cmp	r4, #2\n"	// 0x2
	"ldr	r3, [r0, #144]\n"
	"cmpne	r4, #6\n"	// 0x6
	"bne	loc_ff8bae08\n"
	"ldr	ip, [r0, #140]\n"
	"mov	r0, sp\n"
	"mov	r2, r4\n"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"blx	ip\n"
	"ldr	r0, [sp, #28]\n"
	"mov	r2, sp\n"
	"add	r1, sp, #16\n"	// 0x10
	"bl	sub_ff8ba7ec\n"
"loc_ff8badf4:\n"
	"ldr	r0, [sp, #28]\n"
	"ldr	r2, [sp, #12]\n"
	"mov	r1, r4\n"
	"bl	sub_ff8baa78\n"
	"b	loc_ff8bb060\n"
"loc_ff8bae08:\n"
	"ldr	r1, [r0, #124]\n"
	"ldr	ip, [r0, #140]\n"
	"add	r0, r0, #4\n"	// 0x4
	"mov	r2, r4\n"
	"blx	ip\n"
	"b	loc_ff8bb060\n"
"loc_ff8bae20:\n"
	"cmp	r1, #34\n"	// 0x22
	"cmpne	r1, #35\n"	// 0x23
	"bne	loc_ff8bae6c\n"
	"ldr	r1, [r0, #124]\n"
	"add	r1, r1, r1, lsl #1\n"
	"add	r1, r0, r1, lsl #2\n"
	"sub	r1, r1, #8\n"	// 0x8
	"ldm	r1, {r2, r3, r4}\n"
	"stm	r6, {r2, r3, r4}\n"
	"bl	sub_ff8b894c\n"
	"ldr	r0, [sp, #28]\n"
	"ldr	r1, [r0, #124]\n"
	"ldr	r3, [r0, #140]\n"
	"ldr	r2, [r0, #144]\n"
	"add	r0, r0, #4\n"	// 0x4
	"blx	r3\n"
	"ldr	r0, [sp, #28]\n"
	"bl	sub_ff8b8c40\n"
	"b	loc_ff8bb060\n"
"loc_ff8bae6c:\n"
	"add	r1, r0, #4\n"	// 0x4
	"ldm	r1, {r2, r3, ip}\n"
	"stm	r6, {r2, r3, ip}\n"
	"ldr	r1, [r0]\n"
	"cmp	r1, #37\n"	// 0x25
	"addls	pc, pc, r1, lsl #2\n"
	"b	loc_ff8bb040\n"
	"b	loc_ff8baf20\n" // 0 jump table start
	"b	loc_ff8baf20\n"
	"b	loc_ff8baf28\n"
	"b	loc_ff8baf30\n"
	"b	loc_ff8baf30\n"
	"b	loc_ff8baf30\n"
	"b	loc_ff8baf20\n"
	"b	loc_ff8baf28\n"
	"b	loc_ff8baf30\n"
	"b	loc_ff8baf30\n"
	"b	loc_ff8baf48\n" // 10
	"b	loc_ff8baf48\n"
	"b	loc_ff8bb034\n"
	"b	loc_ff8bb03c\n"
	"b	loc_ff8bb03c\n"
	"b	loc_ff8bb03c\n"
	"b	loc_ff8bb03c\n"
	"b	loc_ff8bb040\n"
	"b	loc_ff8bb040\n"
	"b	loc_ff8bb040\n"
	"b	loc_ff8bb040\n" // 20
	"b	loc_ff8bb040\n"
	"b	loc_ff8bb040\n"
	"b	loc_ff8baf38\n"
	"b	loc_ff8baf40\n"
	"b	loc_ff8baf40\n"
	"b	loc_ff8baf54\n"
	"b	loc_ff8baf54\n"
	"b	loc_ff8baf5c\n"
	"b	loc_ff8baf8c\n"
	"b	loc_ff8bafbc\n" // 30
	"b	loc_ff8bafec\n"
	"b	loc_ff8bb01c\n"
	"b	loc_ff8bb01c\n"
	"b	loc_ff8bb040\n"
	"b	loc_ff8bb040\n"
	"b	loc_ff8bb024\n"
	"b	loc_ff8bb02c\n" // 37
"loc_ff8baf20:\n" // jump table entries 0, 1, 6
	"bl	sub_ff8b7754\n"
	"b	loc_ff8bb040\n"
"loc_ff8baf28:\n" // jump table entries 2, 7
	"bl	sub_ff8b79d8\n"
	"b	loc_ff8bb040\n"
"loc_ff8baf30:\n" // jump table entries 3, 4, 5, 8, 9
	"bl	sub_ff8b7be0\n"
	"b	loc_ff8bb040\n"
"loc_ff8baf38:\n" // jump table entry 23
	"bl	sub_ff8b7e58\n"
	"b	loc_ff8bb040\n"
"loc_ff8baf40:\n" // jump table entry 24, 25
	"bl	sub_ff8b8050\n"
	"b	loc_ff8bb040\n"
"loc_ff8baf48:\n" // jump table entries 10, 11
	"bl	sub_ff8b830c\n"
	"ldr	r4, =0x0\n" // was: "mov ..., #0"
	"b	loc_ff8bb040\n"
"loc_ff8baf54:\n" // jump table entry 26, 27
	"bl	sub_ff8b844c\n"
	"b	loc_ff8bb040\n"
"loc_ff8baf5c:\n" // jump table entry 28
	"ldrh	r1, [r0, #4]\n"
	"strh	r1, [sp, #16]\n"
	"ldrh	r1, [r5, #2]\n"
	"strh	r1, [sp, #18]\n"
	"ldrh	r1, [r5, #4]\n"
	"strh	r1, [sp, #20]\n"
	"ldrh	r1, [r5, #6]\n"
	"strh	r1, [sp, #22]\n"
	"ldrh	r1, [r0, #12]\n"
	"strh	r1, [sp, #24]\n"
	"bl	sub_ff8bbeac\n"
	"b	loc_ff8bb040\n"
"loc_ff8baf8c:\n" // jump table entry 29
	"ldrh	r1, [r0, #4]\n"
	"strh	r1, [sp, #16]\n"
	"ldrh	r1, [r5, #2]\n"
	"strh	r1, [sp, #18]\n"
	"ldrh	r1, [r5, #4]\n"
	"strh	r1, [sp, #20]\n"
	"ldrh	r1, [r5, #6]\n"
	"strh	r1, [sp, #22]\n"
	"ldrh	r1, [r5, #8]\n"
	"strh	r1, [sp, #24]\n"
	"bl	sub_ff8bc014\n"
	"b	loc_ff8bb040\n"
"loc_ff8bafbc:\n" // jump table entry 30
	"ldrh	r1, [r5]\n"
	"strh	r1, [sp, #16]\n"
	"ldrh	r1, [r0, #6]\n"
	"strh	r1, [sp, #18]\n"
	"ldrh	r1, [r5, #4]\n"
	"strh	r1, [sp, #20]\n"
	"ldrh	r1, [r5, #6]\n"
	"strh	r1, [sp, #22]\n"
	"ldrh	r1, [r5, #8]\n"
	"strh	r1, [sp, #24]\n"
	"bl	sub_ff8bc0c0\n"
	"b	loc_ff8bb040\n"
"loc_ff8bafec:\n" // jump table entry 31
	"ldrh	r1, [r5]\n"
	"strh	r1, [sp, #16]\n"
	"ldrh	r1, [r5, #2]\n"
	"strh	r1, [sp, #18]\n"
	"ldrh	r1, [r5, #4]\n"
	"strh	r1, [sp, #20]\n"
	"ldrh	r1, [r5, #6]\n"
	"strh	r1, [sp, #22]\n"
	"ldrh	r1, [r0, #12]\n"
	"strh	r1, [sp, #24]\n"
	"bl	sub_ff8bc160\n"
	"b	loc_ff8bb040\n"
"loc_ff8bb01c:\n" // jump table entries 32, 33
	"bl	sub_ff8b87a4\n"
	"b	loc_ff8bb040\n"
"loc_ff8bb024:\n" // jump table entry 36
	"bl	sub_ff8b8d44\n"
	"b	loc_ff8bb040\n"
"loc_ff8bb02c:\n" // jump table entry 37
	"bl	sub_ff8b8f80\n"
	"b	loc_ff8bb040\n"
"loc_ff8bb034:\n" // jump table entry 12
	"bl	sub_ff8b90fc\n"
	"b	loc_ff8bb040\n"
"loc_ff8bb03c:\n" // jump table entries 13, 14, 15, 16
	"bl	sub_ff8b9298\n"
"loc_ff8bb040:\n" // jump table entries 17, 18, 19, 20, 21, 22, 34, 35, default
	"ldr	r0, [sp, #28]\n"
	"ldr	r1, [r0, #124]\n"
	"ldr	r3, [r0, #140]\n"
	"ldr	r2, [r0, #144]\n"
	"add	r0, r0, #4\n"	// 0x4
	"blx	r3\n"
	"cmp	r4, #1\n"	// 0x1
	"bne	loc_ff8bb0a8\n"
"loc_ff8bb060:\n" // 4 refs
	"ldr	r0, [sp, #28]\n"
	"ldr	r2, =0xc\n" // was: "mov ..., #12"
	"ldr	r1, [r0, #124]\n"
	"add	r1, r1, r1, lsl #1\n"
	"add	r0, r0, r1, lsl #2\n"
	"sub	r4, r0, #8\n"	// 0x8
	"ldr	r0, =0x00042ab0\n" // was: "[pc, #1420]	; ff8bb60c" 
	"add	r1, sp, #16\n"	// 0x10
	"bl	sub_ffb39768\n"
	"ldr	r0, =0x00042abc\n" // was: "[pc, #1432]	; ff8bb624" 
	"ldr	r2, =0xc\n" // was: "mov ..., #12"
	"add	r1, sp, #16\n"	// 0x10
	"bl	sub_ffb39768\n"
	"ldr	r0, =0x00042ac8\n" // was: "[pc, #1420]	; ff8bb628" 
	"ldr	r2, =0xc\n" // was: "mov ..., #12"
	"mov	r1, r4\n"
	"bl	sub_ffb39768\n"
	"b	loc_ff8bb120\n"
"loc_ff8bb0a8:\n"
	"ldr	r0, [sp, #28]\n"
	"ldr	r0, [r0]\n"
	"cmp	r0, #11\n"	// 0xb
	"bne	loc_ff8bb0f0\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	"ldr	r3, =0x1\n" // was: "mov ..., #1"
	"ldr	r2, =0x1\n" // was: "mov ..., #1"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff8b755c\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	"ldr	r3, =0x1\n" // was: "mov ..., #1"
	"ldr	r2, =0x1\n" // was: "mov ..., #1"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"b	loc_ff8bb11c\n"
"loc_ff8bb0f0:\n"
	"ldr	r3, =0x1\n" // was: "mov ..., #1"
	"ldr	r2, =0x1\n" // was: "mov ..., #1"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"str	r3, [sp]\n"
	"bl	sub_ff8b755c\n"
	"ldr	r3, =0x1\n" // was: "mov ..., #1"
	"ldr	r2, =0x1\n" // was: "mov ..., #1"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"str	r3, [sp]\n"
"loc_ff8bb11c:\n"
	"bl	sub_ff8b769c\n"
"loc_ff8bb120:\n" // 3 refs
	"ldr	r0, [sp, #28]\n"
	"bl	sub_ff8bbe38\n"
	"b	loc_ff8bab48\n"
    );
}
