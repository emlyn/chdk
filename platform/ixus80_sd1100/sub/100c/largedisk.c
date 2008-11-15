
// -----------------
// SDHC-Boot-Support
// -----------------
//
// This is not supported unless I recieve a large SD card
// ...
//
// :P
//
// chr

void __attribute__((naked,noinline)) sub_FF82ACC4_my() { //#fs
    asm volatile (
	"stmdb	sp!, {r4, lr} \n"
	"BL	sub_FF8742C0 \n"
	"BL	sub_FF846180 \n" // <IsFactoryMode +111796>
	"cmp	r0, #1	\n" // ; 0x1
	"BNE	loc_FF82ACE4 \n"
	"BL	sub_FF87729C \n"
	"ldmia	sp!, {r4, lr} \n"
	"B	sub_FF8461F0 \n" // <StartFactoryModeController +111888>
"loc_FF82ACE4:\n"
	"BL	sub_FF876138 \n"
	"ldr	r4,  =0x00001d28 \n"
	"ldr	r0, [r4, #4] \n"
	"cmp	r0, #0	\n" // ; 0x0
	"ldmneia	sp!, {r4, pc} \n"
	"mov	r1, #0	\n" // ; 0x0
	"ldr	r0,  =sub_FF82A85C_my \n" //   ---------------> for SDHC and movie rec
	"BL	sub_FF872748 \n" // <CreateController +293448>
	"str	r0, [r4, #4] \n"
	"ldmia	sp!, {r4, pc} \n"
    );
}; //#fe

void __attribute__((naked,noinline)) sub_FF82A85C_my() {
    asm volatile (
// from 860is:
// sub_FF82C1B0 -> sub_FF82A6E8
// sub_FF86FB00 -> sub_FF875E54
// sub_FF870B0C -> sub_FF876E6C

	"stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr} \n"
	"ldr	r6,  =0x00001d28 \n"
	"mov	r5, r3 \n"
	"ldr	r0, [r6, #20] \n"
	"mov	r4, r1 \n"
	"cmp	r0, #1	\n" // ; 0x1
	"BNE	loc_FF82A880 \n"
	"BL	sub_FF874AFC \n"
	"B	loc_FF82A91C \n"
"loc_FF82A880:\n"
	"ldr	fp,  =0x00001167 \n"
	"mov	r8, #1	\n" // ; 0x1
	"bic	ip, fp, r8, lsl #2 \n"
	"cmp	r4, ip \n"
	"moveq	r0, #0	\n" // ; 0x0
	"mov	r7, #0	\n" // ; 0x0
	"BEQ	loc_FF82ABC8 \n"
	"BGT	loc_FF82A9CC \n"
	"ldr	r3,  =0x00001063 \n"
	"cmp	r4, r3 \n"
	"sub	lr, r3, #13	\n" // ; 0xd
	"sub	r1, r3, #8	\n" // ; 0x8
	"sub	r9, r3, #5	\n" // ; 0x5
	"sub	r2, r3, #2	\n" // ; 0x2
	"sub	r0, r3, #1	\n" // ; 0x1
	"BEQ	loc_FF82AC70 \n"
	"BGT	loc_FF82A93C \n"
	"cmp	r4, lr \n"
	"BEQ	loc_FF82AC70 \n"
	"BGT	loc_FF82A924 \n"
	"sub	ip, r4, #2048	\n" // ; 0x800
	"subs	ip, ip, #3	\n" // ; 0x3
	"BEQ	loc_FF82AAFC \n"
	"sub	ip, r4, #2048	\n" // ; 0x800
	"subs	ip, ip, #344	\n" // ; 0x158
	"BEQ	loc_FF82ACA8 \n"
	"ldr	r5,  =0x000009a5 \n"
	"sub	ip, r4, #2304	\n" // ; 0x900
	"subs	ip, ip, #163	\n" // ; 0xa3
	"cmpne	r4, r5 \n"
	"BNE	loc_FF82ABD8 \n"
	"ldr	r0, [r6, #12] \n"
	"sub	ip, r0, #32768	\n" // ; 0x8000
	"subs	ip, ip, #2	\n" // ; 0x2
	"BEQ	loc_FF82A91C \n"
	"ldr	r0,  =0x000010a5 \n"
	"BL	sub_FF8735C0 \n" // <IsControlEventActive +298160>
	"cmp	r0, #0	\n" // ; 0x0
	"BEQ	loc_FF82ABD0 \n"
"loc_FF82A91C:\n"
	"mov	r0, #0	\n" // ; 0x0
	"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
"loc_FF82A924:\n"
	"cmp	r4, r1 \n"
	"cmpne	r4, r9 \n"
	"cmpne	r4, r2 \n"
	"cmpne	r4, r0 \n"
	"BNE	loc_FF82ABD8 \n"
	"B	loc_FF82AC70 \n"
"loc_FF82A93C:\n"
	"ldr	ip,  =0x000010ae \n"
	"cmp	r4, ip \n"
	"BEQ	loc_FF82AC0C \n"
	"BGT	loc_FF82A984 \n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"subs	ip, ip, #101	\n" // ; 0x65
	"BEQ	loc_FF82AC70 \n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"ldr	r0,  =0x000010a3 \n"
	"subs	ip, ip, #169	\n" // ; 0xa9
	"BEQ	loc_FF82ABE8 \n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"subs	ip, ip, #170	\n" // ; 0xaa
	"BEQ	loc_FF82AC00 \n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"subs	ip, ip, #173	\n" // ; 0xad
	"BNE	loc_FF82ABD8 \n"
	"B	loc_FF82ABF4 \n"
"loc_FF82A984:\n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"subs	ip, ip, #175	\n" // ; 0xaf
	"BEQ	loc_FF82ABF4 \n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"subs	ip, ip, #176	\n" // ; 0xb0
	"BEQ	loc_FF82AC0C \n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"subs	ip, ip, #178	\n" // ; 0xb2
	"ldreq	r0,  =0x00001008 \n"
	"moveq	r1, r5 \n"
	"BEQ	loc_FF82ABE0 \n"
	"sub	ip, r4, #4352	\n" // ; 0x1100
	"subs	ip, ip, #98	\n" // ; 0x62
	"BNE	loc_FF82ABD8 \n"
	"BL	sub_FF87C684 \n"
	"cmp	r0, #0	\n" // ; 0x0
	"BLNE	sub_FF87B52C \n"
	"B	loc_FF82AC10 \n"
"loc_FF82A9CC:\n"
	"ldr	sl,  =0x0000201b \n"
	"ldr	r0,  =0x00001d28 \n"
	"cmp	r4, sl \n"
	"ldr	r2, [r0, #16]! \n"
	"ldr	r1, [r0, #16] \n"
	"sub	r9, sl, #23	\n" // ; 0x17
	"BEQ	loc_FF82ABB4 \n"
	"BGT	loc_FF82AA84 \n"
	"ldr	sl,  =0x0000116a \n"
	"cmp	r4, sl \n"
	"BEQ	loc_FF82ABA0 \n"
	"BGT	loc_FF82AA40 \n"
	"sub	ip, r4, #4096	\n" // ; 0x1000
	"subs	ip, ip, #356	\n" // ; 0x164
	"moveq	r0, #1	\n" // ; 0x1
	"BEQ	loc_FF82ABC8 \n"
	"sub	ip, r4, #4352	\n" // ; 0x1100
	"subs	ip, ip, #101	\n" // ; 0x65
	"BEQ	loc_FF82ABC4 \n"
	"ldr	r5,  =0x00001168 \n"
	"cmp	r4, fp \n"
	"cmpne	r4, r5 \n"
	"BNE	loc_FF82ABD8 \n"
	"str	r8, [r6, #16] \n"
	"ldr	r6,  =0x00004508 \n"
	"cmp	r1, #0	\n" // ; 0x0
	"BEQ	loc_FF82AB88 \n"
	"BL	sub_FF874B30 \n"
	"B	loc_FF82AB94 \n"
"loc_FF82AA40:\n"
	"sub	ip, r4, #8192	\n" // ; 0x2000
	"subs	ip, ip, #2	\n" // ; 0x2
	"BEQ	loc_FF82AC3C \n"
	"cmp	r4, r9 \n"
	"mov	r0, r9 \n"
	"BEQ	loc_FF82AC48 \n"
	"sub	ip, r4, #8192	\n" // ; 0x2000
	"subs	ip, ip, #5	\n" // ; 0x5
	"BEQ	loc_FF82AC3C \n"
	"sub	ip, r4, #8192	\n" // ; 0x2000
	"subs	ip, ip, #25	\n" // ; 0x19
	"BNE	loc_FF82ABD8 \n"
	"cmp	r1, #0	\n" // ; 0x0
	"BEQ	loc_FF82A91C \n"
	"cmp	r2, #0	\n" // ; 0x0
	"BNE	loc_FF82A91C \n"
	"B	loc_FF82ACA0 \n"
"loc_FF82AA84:\n"
	"ldr	ip,  =0x00003110 \n"
	"cmp	r4, ip \n"
	"BEQ	loc_FF82AC10 \n"
	"BGT	loc_FF82AACC \n"
	"sub	ip, r4, #8192	\n" // ; 0x2000
	"subs	ip, ip, #29	\n" // ; 0x1d
	"BEQ	loc_FF82AC3C \n"
	"ldr	r0,  =0x00002027 \n"
	"cmp	r4, r0 \n"
	"BEQ	loc_FF82AC18 \n"
	"sub	ip, r4, #12288	\n" // ; 0x3000
	"subs	ip, ip, #6	\n" // ; 0x6
	"BEQ	loc_FF82AC10 \n"
	"sub	ip, r4, #12288	\n" // ; 0x3000
	"subs	ip, ip, #16	\n" // ; 0x10
	"BNE	loc_FF82ABD8 \n"
	"BL	sub_FF8708E0 \n"
	"B	loc_FF82A91C \n"
"loc_FF82AACC:\n"
	"sub	ip, r4, #12544	\n" // ; 0x3100
	"subs	ip, ip, #17	\n" // ; 0x11
	"BEQ	loc_FF82AC10 \n"
	"cmp	r4, #12608	\n" // ; 0x3140
	"BEQ	loc_FF82AC64 \n"
	"sub	ip, r4, #12800	\n" // ; 0x3200
	"subs	ip, ip, #1	\n" // ; 0x1
	"BEQ	loc_FF82ABD8 \n"
	"sub	ip, r4, #12800	\n" // ; 0x3200
	"subs	ip, ip, #2	\n" // ; 0x2
	"BNE	loc_FF82ABD8 \n"
	"B	loc_FF82AC10 \n"
"loc_FF82AAFC:\n"
	"mov	r4, #1	\n" // ; 0x1
	"mov	r0, #2	\n" // ; 0x2
	"BL	sub_FF874354 \n"
	"cmp	r0, #1	\n" // ; 0x1
	"moveq	r4, #2	\n" // ; 0x2
	"mov	r0, r4 \n"
	"BL	sub_FF821320 \n"
	"cmp	r0, #0	\n" // ; 0x0
	"strne	r8, [r6, #20] \n"
	"BNE	loc_FF82AB54 \n"
	"BL	sub_FF87A440 \n"
	"BL	sub_FF877C0C \n"
	"BL	sub_FF8787EC \n"
	"BL	sub_FF877544 \n"
	"BL	sub_FF878DF8 \n" // <GetVRAMHPixelsSize_0 +320196>
	"cmp	r0, #0	\n" // ; 0x0
	"BEQ	loc_FF82AB5C \n"
	"BL	sub_FF82A5C8 \n"
	"BL	sub_FF878D5C \n"
	"mov	r1, r0 \n"
	"mov	r0, fp \n"
	"BL	sub_FF872F50 \n" // <PostLogicalEventToUI +295936>
"loc_FF82AB54:\n"
	"mov	r0, r7 \n"
	"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
"loc_FF82AB5C:\n"
	"BL	sub_FF8253F0 \n"
	"cmp	r0, #1	\n" // ; 0x1
	"ldrne	r0,  =0x0000310b \n"
	"ldreq	r0,  =0x0000310c \n"
	"mov	r1, #0	\n" // ; 0x0
	"BL	sub_FF872F50 \n" // <PostLogicalEventToUI +295904>
"BL	sub_FF876E6C_my \n"
	"B	loc_FF82AB54 \n"
"loc_FF82AB7C:\n"
	"mov	r0, r6 \n"
	"BL	sub_FF85B090 \n"
	"B	loc_FF82A91C \n"
"loc_FF82AB88:\n"
	"BL	sub_FF877E84 \n"
	"BL	sub_FF877DE8 \n"
	"BL	sub_FF825098 \n"
"loc_FF82AB94:\n"
	"cmp	r4, r5 \n"
	"BNE	loc_FF82A91C \n"
	"B	loc_FF82AB7C \n"
"loc_FF82ABA0:\n"
	"mov	r0, #1	\n" // ; 0x1
	"BL	sub_FF874C5C \n"
	"ldr	r0,  =0x00001005 \n"
	"mov	r1, sl \n"
	"B	loc_FF82ABE0 \n"
"loc_FF82ABB4:\n"
	"cmp	r2, #1	\n" // ; 0x1
	"BNE	loc_FF82AC10 \n"
	"BL	sub_FF874B30 \n"
	"B	loc_FF82A91C \n"
"loc_FF82ABC4:\n"
	"mov	r0, #2	\n" // ; 0x2
"loc_FF82ABC8:\n"
	"BL	sub_FF82B230 \n"
	"B	loc_FF82A91C \n"
"loc_FF82ABD0:\n"
	"cmp	r4, r5 \n"
	"streq	r8, [r6, #48] \n"
"loc_FF82ABD8:\n"
	"mov	r1, #0	\n" // ; 0x0
"loc_FF82ABDC:\n"
	"mov	r0, r4 \n"
"loc_FF82ABE0:\n"
	"BL	sub_FF875E54_my \n"
	"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
"loc_FF82ABE8:\n"
	"BL	sub_FF8735C0 \n" // <IsControlEventActive +297432>
	"cmp	r0, #0	\n" // ; 0x0
	"BNE	loc_FF82A91C \n"
"loc_FF82ABF4:\n"
	"mov	r0, r4 \n"
	"BL	sub_FF82A6E8 \n" /// XXX movie rec.
//"BL	sub_FF82A6E8_my \n" /// XXX movie rec.
	"ldmia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
"loc_FF82AC00:\n"
	"BL	sub_FF8735C0 \n" // <IsControlEventActive +297408>
	"cmp	r0, #0	\n" // ; 0x0
	"BNE	loc_FF82A91C \n"
"loc_FF82AC0C:\n"
	"BL	sub_FF82B200 \n"
"loc_FF82AC10:\n"
	"mov	r1, r5 \n"
	"B	loc_FF82ABDC \n"
"loc_FF82AC18:\n"
	"mov	r1, #0	\n" // ; 0x0
	"BL	sub_FF875E54_my \n"
	"mov	r1, #0	\n" // ; 0x0
	"mov	r0, sl \n"
	"BL	sub_FF875E54_my \n"
	"mov	r1, #0	\n" // ; 0x0
	"mov	r0, r9 \n"
"loc_FF82AC34:\n"
	"BL	sub_FF875E54_my \n"
	"B	loc_FF82A91C \n"
"loc_FF82AC3C:\n"
	"str	r7, [r6, #32] \n"
	"BL	sub_FF82AEBC \n"
	"B	loc_FF82AC10 \n"
"loc_FF82AC48:\n"
	"str	r7, [r6, #32] \n"
	"BL	sub_FF82AEBC \n"
	"ldr	r0, [r6, #16] \n"
	"cmp	r0, #1	\n" // ; 0x1
	"BNE	loc_FF82AC10 \n"
	"BL	sub_FF874B74 \n"
	"B	loc_FF82A91C \n"
"loc_FF82AC64:\n"
	"cmp	r1, #0	\n" // ; 0x0
	"BLEQ	sub_FF82AEBC \n"
	"B	loc_FF82A91C \n"
"loc_FF82AC70:\n"
	"cmp	r4, r2 \n"
	"moveq	r0, r2 \n"
	"BEQ	loc_FF82ACA0 \n"
	"BGT	loc_FF82AC90 \n"
	"cmp	r4, lr \n"
	"cmpne	r4, r9 \n"
	"BEQ	loc_FF82ACA0 \n"
	"B	loc_FF82AC9C \n"
"loc_FF82AC90:\n"
	"cmp	r4, r0 \n"
	"cmpne	r4, r3 \n"
	"BEQ	loc_FF82ACA0 \n"
"loc_FF82AC9C:\n"
	"mov	r0, r1 \n"
"loc_FF82ACA0:\n"
	"mov	r1, #0	\n" // ; 0x0
	"B	loc_FF82AC34 \n"
"loc_FF82ACA8:\n"
	"tst	r5, #-2147483648	\n" // ; 0x80000000
	"movne	r0, #1	\n" // ; 0x1
	"ldmneia	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc} \n"
	"BL	sub_FF87DDF8 \n"
	"cmp	r0, #0	\n" // ; 0x0
	"BLEQ	sub_FF827740 \n"
	"B	loc_FF82A91C \n"
	);
}


// Extracted method: sub_FF876E6C
// Overridden calls:
//     sub_FF870958
//     sub_FF870958 => sub_FF876E08
void __attribute__((naked,noinline)) sub_FF876E6C_my() {
    asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"BL	sub_FF82AE70 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0,  =0x00001061 \n"
		"BNE	loc_FF876E94 \n"
		"BL	sub_FF82AE54 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0,  =0x0000105b \n"
		"BNE	loc_FF876E94 \n"
		"BL	sub_FF82AE88 \n"
	"loc_FF876E94:\n"
		"mov	r4, r0 \n"
		"BL	sub_FF876FF4 \n"
		"mov	r0, r4 \n"
		"BL	sub_FF877094 \n"
		"ldr	r0,  =0x00005a80 \n"
		"ldr	r0, [r0] \n"
		"tst	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF876EC0 \n"
	"loc_FF876EB4:\n"
		"mov	r1, r4 \n"
		"mov	r0, #2	\n" // ; 0x2
		"B	loc_FF876F28 \n"
	"loc_FF876EC0:\n"
		"tst	r0, #8192	\n" // ; 0x2000
		"BEQ	loc_FF876EDC \n"
		"tst	r0, #512	\n" // ; 0x200
		"ldreq	r1,  =0x00004004 \n"
		"ldrne	r1,  =0x00008002 \n"
		"mov	r0, #3	\n" // ; 0x3
		"B	loc_FF876F28 \n"
	"loc_FF876EDC:\n"
		"tst	r0, #16	\n" // ; 0x10
		"BNE	loc_FF876EB4 \n"
		"tst	r0, #64	\n" // ; 0x40
		"BEQ	loc_FF876EF8 \n"
	"loc_FF876EEC:\n"
		"mov	r1, r4 \n"
		"mov	r0, #1	\n" // ; 0x1
		"B	loc_FF876F28 \n"
	"loc_FF876EF8:\n"
		"tst	r0, #32	\n" // ; 0x20
		"BEQ	loc_FF876F14 \n"
		"tst	r0, #16384	\n" // ; 0x4000
		"BNE	loc_FF876F14 \n"
	"loc_FF876F08:\n"
		"mov	r1, r4 \n"
		"mov	r0, #0	\n" // ; 0x0
		"B	loc_FF876F28 \n"
	"loc_FF876F14:\n"
		"ldr	r1,  =0x00000102 \n"
		"bics	r1, r1, r0 \n"
		"BNE	loc_FF876F30 \n"
		"mov	r1, r4 \n"
		"mov	r0, #6	\n" // ; 0x6
	"loc_FF876F28:\n"
		"ldmia	sp!, {r4, lr} \n"
	"B	sub_FF876E08_my \n"
	"loc_FF876F30:\n"
		"tst	r0, #256	\n" // ; 0x100
		"BNE	loc_FF876EB4 \n"
		"tst	r0, #1024	\n" // ; 0x400
		"BNE	loc_FF876EEC \n"
		"tst	r0, #512	\n" // ; 0x200
		"tsteq	r0, #2	\n" // ; 0x2
		"BNE	loc_FF876F08 \n"
		"tst	r0, #262144	\n" // ; 0x40000
		"BEQ	loc_FF876EB4 \n"
		"tst	r0, #2097152	\n" // ; 0x200000
		"moveq	r1, r4 \n"
		"moveq	r0, #1	\n" // ; 0x1
	"BLEQ	sub_FF876E08_my \n"
		"B	loc_FF876EB4 \n"

	);
}

// Extract sub_FF876E08
// Overridden calls:
//     sub_FF86FB00 -> sub_FF875E54
void __attribute__((naked,noinline)) sub_FF876E08_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"movs	r4, r0 \n"
		"mov	r0, #1	\n" // ; 0x1
		"mov	r5, r1 \n"
		"BNE	loc_FF876E48 \n"
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8742E4 \n"
		"BL	sub_FF82AE88 \n"
		"sub	ip, r0, #4096	\n" // ; 0x1000
		"subs	ip, ip, #91	\n" // ; 0x5b
		"BNE	loc_FF876E40 \n"
	"loc_FF876E38:\n"
		"BL	sub_FF876D5C \n"
		"B	loc_FF876E50 \n"
	"loc_FF876E40:\n"
		"BL	sub_FF876D9C \n"
		"B	loc_FF876E50 \n"
	"loc_FF876E48:\n"
		"cmp	r4, #5	\n" // ; 0x5
		"BEQ	loc_FF876E38 \n"
	"loc_FF876E50:\n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldreq	r5,  =0x00001162 \n"
		"moveq	r4, #2	\n" // ; 0x2
		"mov	r0, r4 \n"
		"mov	r1, r5 \n"
		"ldmia	sp!, {r4, r5, r6, lr} \n"
	"B	sub_FF875E54_my \n" // <_binary_dump_bin_start+0x65e54 -4116>
    );
}

// sub_FF875E54:
//     sub_FF82BE84 -> sub_FF82A3B4
//     sub_FF86E38C -> sub_FF874A3C
//     sub_FF86EDAC -> sub_FF875380
//     sub_FF86EE0C -> sub_FF875414
//     sub_FF86EFE4 -> sub_FF8755A4
//     sub_FF86F224 -> sub_FF875774
//     sub_FF86F5E8 -> sub_FF875B14
//     sub_FF86F6F0 -> sub_FF8769E0
//     sub_FF86F89C -> sub_FF875BF4
//     sub_FF86F9F8 -> sub_FF875D50
//     sub_FF870430 -> sub_FF876798
//     sub_FF870468 -> sub_FF8767D0
//     sub_FF870550 -> sub_FF87689C
//     sub_FF870694 -> sub_FF876B4C

void __attribute__((naked,noinline)) sub_FF875E54_my () {
    asm volatile (
	"stmdb	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"mov	r7, r1 \n"
	"mov	r6, r0 \n"
	"BL	sub_FF878DF8 \n" // <GetVRAMHPixelsSize_0 +12184>
	"cmp	r0, #0	\n" // ; 0x0
	"BNE	loc_FF876130 \n"
	"mov	r1, r7 \n"
	"mov	r0, r6 \n"
	"BL	sub_FF874DF0 \n"
	"ldr	r4,  =0x000059c0 \n"
	"mov	r5, #0	\n" // ; 0x0
	"ldr	r0, [r4, #16] \n"
	"cmp	r0, #22	\n" // ; 0x16
	"addls	pc, pc, r0, lsl #2 \n"
	"B	loc_FF876130 \n"
	"B	loc_FF875EEC \n"
	"B	loc_FF875F14 \n"
	"B	loc_FF875F48 \n"
	"B	loc_FF875FF8 \n"
	"B	loc_FF876008 \n"
	"B	loc_FF876130 \n"
	"B	loc_FF876130 \n"
	"B	loc_FF87608C \n"
	"B	loc_FF875EFC \n"
	"B	loc_FF875F08 \n"
	"B	loc_FF87608C \n"
	"B	loc_FF875F3C \n"
	"B	loc_FF876130 \n"
	"B	loc_FF876130 \n"
	"B	loc_FF875F54 \n"
	"B	loc_FF875F60 \n"
	"B	loc_FF875FD0 \n"
	"B	loc_FF875F20 \n"
	"B	loc_FF876118 \n"
	"B	loc_FF876098 \n"
	"B	loc_FF8760C8 \n"
	"B	loc_FF8760C8 \n"
	"B	loc_FF876014 \n"
"loc_FF875EEC:\n"
	"mov	r1, r7 \n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF875774_my \n"
"loc_FF875EFC:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF87689C \n"
//	"B	sub_FF87689C_my \n" // XXX movierec
"loc_FF875F08:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF8769E0 \n"
//	"B	sub_FF8769E0_my \n" // XXX movierec
"loc_FF875F14:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF875414 \n"
//	"B	sub_FF875414_my \n" // XX movierec
"loc_FF875F20:\n"
	"sub	ip, r6, #12288	\n" // ; 0x3000
	"subs	ip, ip, #6	\n" // ; 0x6
	"BNE	loc_FF876130 \n"
	"mov	r0, #0	\n" // ; 0x0
	"BL	sub_FF82A460 \n"
	"BL	sub_FF876798 \n"
//	"BL	sub_FF876798_my \n" // XXX movierec
	"B	loc_FF876128 \n"
"loc_FF875F3C:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF8767D0 \n"
//	"B	sub_FF8767D0_my \n" // XXX movierec
"loc_FF875F48:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
//	"B	sub_FF8755A4_my \n" // XXX movierec
"loc_FF875F54:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF875BF4 \n"
//	"B	sub_FF875BF4_my \n" // XXX movierec
"loc_FF875F60:\n"
	"sub	ip, r6, #12800	\n" // ; 0x3200
	"subs	ip, ip, #2	\n" // ; 0x2
	"BNE	loc_FF876130 \n"
	"mov	r0, #3	\n" // ; 0x3
	"BL	sub_FF874CFC \n"
	"mov	r0, #8	\n" // ; 0x8
	"BL	sub_FF82A3B4 \n"
//	"BL	sub_FF82A3B4_my \n" // XXX movierec
	"mov	r1, #0	\n" // ; 0x0
	"mov	r0, #25	\n" // ; 0x19
	"BL	sub_FF838D84 \n"
	"BL	sub_FF877E84 \n"
	"BL	sub_FF87811C \n"
	"BL	sub_FF8775B4 \n"
	"B	loc_FF876128 \n"
"loc_FF875FD0:\n"
	"sub	ip, r6, #13056	\n" // ; 0x3300
	"subs	ip, ip, #1	\n" // ; 0x1
	"BNE	loc_FF876130 \n"
	"ldr	r0,  =0x00004010 \n"
	"BL	sub_FF82A3B4 \n"
//	"BL	sub_FF82A3B4_my \n" // XXX movierec
	"BL	sub_FF99A9A8 \n"
	"BL	sub_FF8775B4 \n"
	"mov	r0, #4	\n" // ; 0x4
	"BL	sub_FF874CFC \n"
	"B	loc_FF876128 \n"
"loc_FF875FF8:\n"
	"mov	r1, r7 \n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF875D50 \n"
//	"B	sub_FF875D50_my \n" // XXX movierec
"loc_FF876008:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF876B4C \n"
//	"B	sub_FF876B4C_my \n" // XXX movierec
"loc_FF876014:\n"
	"ldr	r7,  =0x00001182 \n"
	"mov	r0, r6 \n"
	"cmp	r0, r7 \n"
	"mov	r6, #1	\n" // ; 0x1
	"streq	r6, [r4, #172] \n"
	"BEQ	loc_FF876128 \n"
	"sub	ip, r0, #4096	\n" // ; 0x1000
	"subs	ip, ip, #428	\n" // ; 0x1ac
	"BEQ	loc_FF876074 \n"
	"sub	ip, r0, #12288	\n" // ; 0x3000
	"subs	ip, ip, #548	\n" // ; 0x224
	"BNE	loc_FF876130 \n"
	"mov	r0, #8	\n" // ; 0x8
	"BL	sub_FF82A3B4 \n"
//	"BL	sub_FF82A3B4_my \n" // XXX movierec
	"mov	r0, #3	\n" // ; 0x3
	"BL	sub_FF874CFC \n"
	"str	r5, [r4, #176] \n"
	"ldr	r0, [r4, #172] \n"
	"cmp	r0, #0	\n" // ; 0x0
	"movne	r1, #0	\n" // ; 0x0
	"movne	r0, r7 \n"
	"strne	r5, [r4, #172] \n"
	"BLNE	sub_FF875D50 \n"
//	"BLNE	sub_FF875D50_my \n" // XXX movierec
	"B	loc_FF876128 \n"
"loc_FF876074:\n"
	"ldr	r0, [r4, #176] \n"
	"cmp	r0, #0	\n" // ; 0x0
	"BNE	loc_FF876128 \n"
	"BL	sub_FF99888C \n"
	"str	r6, [r4, #176] \n"
	"B	loc_FF876128 \n"
"loc_FF87608C:\n"
	"mov	r0, r6 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, lr} \n"
	"B	sub_FF875B14 \n"
//	"B	sub_FF875B14_my \n" // XXX movierec
"loc_FF876098:\n"
	"ldr	ip,  =0x000010b0 \n"
	"cmp	r6, ip \n"
	"BEQ	loc_FF8760C4 \n"
	"BGT	loc_FF8760D0 \n"
	"cmp	r6, #4	\n" // ; 0x4
	"BEQ	loc_FF8760F8 \n"
	"sub	ip, r6, #4096	\n" // ; 0x1000
	"subs	ip, ip, #170	\n" // ; 0xaa
	"subne	ip, r6, #4096	\n" // ; 0x1000
	"subnes	ip, ip, #174	\n" // ; 0xae
	"BNE	loc_FF876130 \n"
"loc_FF8760C4:\n"
	"BL	sub_FF874A00 \n"
"loc_FF8760C8:\n"
	"mov	r0, r5 \n"
	"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
"loc_FF8760D0:\n"
	"sub	ip, r6, #8192	\n" // ; 0x2000
	"subs	ip, ip, #4	\n" // ; 0x4
	"BEQ	loc_FF876110 \n"
	"sub	ip, r6, #20480	\n" // ; 0x5000
	"subs	ip, ip, #1	\n" // ; 0x1
	"subne	ip, r6, #20480	\n" // ; 0x5000
	"subnes	ip, ip, #6	\n" // ; 0x6
	"BNE	loc_FF876130 \n"
	"BL	sub_FF875380 \n"
//	"BL	sub_FF875380_my \n" // XXX movierec
	"B	loc_FF876128 \n"
"loc_FF8760F8:\n"
	"ldr	r0, [r4, #44] \n"
	"cmp	r0, #0	\n" // ; 0x0
	"BNE	loc_FF876110 \n"
	"BL	sub_FF876318 \n"
	"BL	sub_FF825050 \n"
	"B	loc_FF876128 \n"
"loc_FF876110:\n"
	"BL	sub_FF874A3C \n"
//	"BL	sub_FF874A3C_my \n" // XXX movierec
	"B	loc_FF876128 \n"
"loc_FF876118:\n"
	"sub	ip, r6, #12288	\n" // ; 0x3000
	"subs	ip, ip, #304	\n" // ; 0x130
	"BNE	loc_FF876130 \n"
	"BL	sub_FF874AFC \n"
"loc_FF876128:\n"
	"mov	r0, #0	\n" // ; 0x0
	"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
"loc_FF876130:\n"
	"mov	r0, #1	\n" // ; 0x1
	"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	);
}

// sub_FF875774
// Overridden calls:
//     sub_FF82BE84 -> sub_FF82A3B4
//     sub_FF86ED10 -> sub_FF875320
//     sub_FF870D38 -> sub_FF877190 // taskcreate_InitFileModules
void __attribute__((naked,noinline)) sub_FF875774_my() {
    asm volatile (
		"stmdb	sp!, {r4, r5, r6, r7, r8, lr} \n"
		"ldr	r7,  =0x00008002 \n"
		"ldr	r4,  =0x000059c0 \n"
		"cmp	r0, #3	\n" // ; 0x3
		"mov	r6, r1 \n"
		"mov	r5, #1	\n" // ; 0x1
		"BEQ	loc_FF8758CC \n"
		"BGT	loc_FF8757B0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF8757F4 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BEQ	loc_FF87586C \n"
		"cmp	r0, #2	\n" // ; 0x2
		"BNE	loc_FF875954 \n"
		"B	loc_FF8757C8 \n"
	"loc_FF8757B0:\n"
		"cmp	r0, #6	\n" // ; 0x6
		"streq	r5, [r4, #40] \n"
		"BEQ	loc_FF8758C4 \n"
		"sub	ip, r0, #8192	\n" // ; 0x2000
		"subs	ip, ip, #4	\n" // ; 0x4
		"BNE	loc_FF875954 \n"
	"loc_FF8757C8:\n"
		"sub	ip, r6, #4352	\n" // ; 0x1100
		"subs	ip, ip, #98	\n" // ; 0x62
		"BNE	loc_FF8757E4 \n"
		"mov	r1, r7 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8788AC \n"
		"str	r5, [r4, #96] \n"
	"loc_FF8757E4:\n"
		"BL	sub_FF877E84 \n"
		"BL	sub_FF87811C \n"
		"BL	sub_FF875320 \n"
	//	"BL	sub_FF875320_my \n" // XXX movierec
		"B	loc_FF87594C \n"
	"loc_FF8757F4:\n"
		"mov	r0, #7	\n" // ; 0x7
		"BL	sub_FF874CFC \n"
		"mov	r0, r7 \n"
		"BL	sub_FF82A3B4 \n"
	//	"BL	sub_FF82A3B4_my \n" // XXX movierec
		"BL	sub_FF8771CC \n" // <taskcreate_CommonDrivers +6600>
		"BL	sub_FF877CEC \n"
		"ldr	r1, =0xff875ab4 \n" // ; (423a4341)  *"AC:BootRec"
		"mov	r0, #32	\n" // ; 0x20
		"str	r6, [r4, #24] \n"
		"BL	sub_FF86A150 \n"
		"ldr	r1, =0xff875ac0 \n" // ; (493a4341)  *"AC:InitLens"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"str	r5, [r4, #40] \n"
		"BL	sub_FF82A534 \n"
		"BL	sub_FF82A488 \n"
		"ldr	r0, [r4, #28] \n"
		"ldr	r1, [r4, #32] \n"
		"orrs	r0, r0, r1 \n"
		"BLNE	sub_FF8762F4 \n"
		"ldr	r0, [r4, #104] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF875858 \n"
		"BL	sub_FF82A5A4 \n" // <taskcreate_StartupImage -307884>
		"B	loc_FF875860 \n"
	"loc_FF875858:\n"
		"BL	sub_FF824DE0 \n"
		"BL	sub_FF82AE10 \n"
	"loc_FF875860:\n"
//	"BL	sub_FF877190 \n"
	"BL	taskcreate_InitFileModules_my \n"
		"BL	sub_FF877208 \n"
		"B	loc_FF87594C \n"
	"loc_FF87586C:\n"
		"mov	r0, #8	\n" // ; 0x8
		"BL	sub_FF874CFC \n"
		"BL	sub_FF8771CC \n" // <taskcreate_CommonDrivers +6488>
		"BL	sub_FF877CEC \n"
		"ldr	r1, =0xff875acc \n" // ; (423a4341)  *"AC:BootPB"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
//	"BL	sub_FF877190 \n"
	"BL	taskcreate_InitFileModules_my \n"
		"BL	sub_FF87729C \n"
		"BL	sub_FF82ADD4 \n"
		"ldr	r0,  =0x00004004 \n"
		"BL	sub_FF82A3B4 \n"
	//	"BL	sub_FF82A3B4_my \n" // XXX movierec
		"ldr	r0, [r4, #104] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF8758B0 \n"
		"BL	sub_FF82A5A4 \n" // <taskcreate_StartupImage -307972>
		"B	loc_FF8758B4 \n"
	"loc_FF8758B0:\n"
		"BL	sub_FF824DE0 \n"
	"loc_FF8758B4:\n"
		"BL	sub_FF877238 \n"
		"ldr	r0, [r4, #48] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BEQ	loc_FF87594C \n"
	"loc_FF8758C4:\n"
		"BL	sub_FF87633C \n"
		"B	loc_FF87594C \n"
	"loc_FF8758CC:\n"
		"mov	r1, r6 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8788AC \n"
		"ldr	r1, =0xff875adc \n" // ; (423a4341)  *"AC:BootClock"
		"mov	r0, #32	\n" // ; 0x20
		"BL	sub_FF86A150 \n"
		"str	r5, [r4, #104] \n"
		"BL	sub_FF87729C \n"
		"BL	sub_FF82ADD4 \n"
		"BL	sub_FF8762D0 \n"
		"BL	sub_FF82AE6C \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0,  =0x0000804d \n"
		"movne	r1, #0	\n" // ; 0x0
		"BLNE	sub_FF8741BC \n" // <j_PTM_SetCurrentItem -5960>
		"BL	sub_FF8786E0 \n"
		"mov	r0, #128	\n" // ; 0x80
		"BL	sub_FF82A3B4 \n"
	//	"BL	sub_FF82A3B4_my \n" // XXX movierec
		"BL	sub_FF878064 \n"
		"BL	sub_FF891ED4 \n" // <StartGUISystem +116156>
		"BL	sub_FF95B868 \n"
		"BL	sub_FF99D97C \n"
		"BL	sub_FF8779E8 \n"
		"BL	sub_FF877EBC \n"
		"mov	r0, #9	\n" // ; 0x9
		"BL	sub_FF874CFC \n"
		"ldr	r0,  =0x0000300e \n"
		"mov	r1, r6 \n"
		"BL	sub_FF872F50 \n" // <PostLogicalEventToUI -10732>
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #1	\n" // ; 0x1
		"BL	sub_FF8788AC \n"
	"loc_FF87594C:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	"loc_FF875954:\n"
		"mov	r0, #1	\n" // ; 0x1
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	);
}

// Extracted method: (ff877190-ff8771c8)
// Overridden calls:
// sub_FF877140 task_InitFileModules_my
void __attribute__((naked,noinline)) taskcreate_InitFileModules_my() {
	asm volatile (
		"ldr	r0,  =0x00005a8c \n"
		"stmdb	sp!, {r3, lr} \n"
		"ldr	r1, [r0, #4] \n"
		"cmp	r1, #0	\n" // ; 0x0
		"BNE	loc_FF8771C8 \n"
		"mov	r1, #1	\n" // ; 0x1
		"str	r1, [r0, #4] \n"
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
//	"ldr	r3, =0xff877140 \n" // ; (e92d4070)
	"ldr	r3, =task_InitFileModules_my \n"
		"mov	r1, #25	\n" // ; 0x19
		"ldr	r0, =0xff8772f4 \n" // ; (74696e49)  *"InitFileModules"
		"mov	r2, #4096	\n" // ; 0x1000
		"BL	sub_FF81B8E0 \n" // <CreateTask -375012>
	"loc_FF8771C8:\n"
		"ldmia	sp!, {ip, pc} \n"
        );
}; //#fe

// Overridden calls:
// sub_FF86D638
void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs
        asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"BL	sub_FF86D60C \n"
		"ldr	r5,  =0x00005006 \n"
		"movs	r4, r0 \n"
		"movne	r1, #0	\n" // ; 0x0
		"movne	r0, r5 \n"
		"BLNE	sub_FF872F50 \n" // <PostLogicalEventToUI -16904>
//	"BL	sub_FF86D638 \n"
	"BL	sub_FF86D638_my \n"       // continue to SDHC-hook here!
	"BL	core_spytask_can_start\n" // CHDK: Set "it's-save-to-start"-Flag for spytask
		"cmp	r4, #0	\n" // ; 0x0
		"moveq	r0, r5 \n"
		"ldmeqia	sp!, {r4, r5, r6, lr} \n"
		"moveq	r1, #0	\n" // ; 0x0
		"BEQ	sub_FF872F50 \n" // <PostLogicalEventToUI -16928>
		"ldmia	sp!, {r4, r5, r6, pc} \n"
        );
}; //#fe

// Overridden calls:
// sub_FF84ED48
void __attribute__((naked,noinline)) sub_FF86D638_my() { //#fs
        asm volatile (
		"stmdb	sp!, {r4, lr} \n"
	//"BL	sub_FF84ED48 \n"
	"BL	sub_FF84ED48_my \n" // continue to SDHC-hook here!
		"ldr	r4,  =0x000057a8 \n"
		"ldr	r0, [r4, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF86D668 \n"
		"BL	sub_FF87FB54 \n"
		"BL	sub_FF901C5C \n"
		"BL	sub_FF87FB54 \n"
		"BL	sub_FF84C738 \n"
		"BL	sub_FF87FB64 \n"
		"BL	sub_FF901D28 \n"
	"loc_FF86D668:\n"
		"mov	r0, #1	\n" // ; 0x1
		"str	r0, [r4] \n"
		"ldmia	sp!, {r4, pc} \n"
        );
}; //#fe

// Overridden calls:
// sub_FF84EB84
void __attribute__((naked,noinline)) sub_FF84ED48_my() { //#fs
        asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"mov	r6, #0	\n" // ; 0x0
		"mov	r0, r6 \n"
		"BL	sub_FF84E808 \n"
		"ldr	r4,  =0x00011544 \n"
		"mov	r5, #0	\n" // ; 0x0
		"ldr	r0, [r4, #56] \n"
		"BL	sub_FF84F23C \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldreq	r0,  =0x000029ac \n"
		"streq	r5, [r0, #16] \n"
		"streq	r5, [r0, #20] \n"
		"streq	r5, [r0, #24] \n"
		"mov	r0, r6 \n"
		"BL	sub_FF84E848 \n"
		"mov	r0, r6 \n"
//	"BL	sub_FF84EB84 \n"
		"BL	sub_FF84EB84_my \n" // continue to SDHC-hook here!
		"mov	r5, r0 \n"
		"mov	r0, r6 \n"
		"BL	sub_FF84EBF0 \n"
		"ldr	r1, [r4, #60] \n"
		"and	r2, r5, r0 \n"
		"cmp	r1, #0	\n" // ; 0x0
		"mov	r0, #0	\n" // ; 0x0
		"moveq	r0, #-2147483647	\n" // ; 0x80000001
		"BEQ	loc_FF84EDDC \n"
		"ldr	r3, [r4, #44] \n"
		"cmp	r3, #2	\n" // ; 0x2
		"moveq	r0, #4	\n" // ; 0x4
		"cmp	r1, #5	\n" // ; 0x5
		"orrne	r0, r0, #1	\n" // ; 0x1
		"biceq	r0, r0, #1	\n" // ; 0x1
		"cmp	r2, #0	\n" // ; 0x0
		"biceq	r0, r0, #2	\n" // ; 0x2
		"orreq	r0, r0, #-2147483648	\n" // ; 0x80000000
		"bicne	r0, r0, #-2147483648	\n" // ; 0x80000000
		"orrne	r0, r0, #2	\n" // ; 0x2
	"loc_FF84EDDC:\n"
		"str	r0, [r4, #64] \n"
		"ldmia	sp!, {r4, r5, r6, pc} \n"
        );
}; //#fe

// Overridden calls:
// sub_FF84E914
void __attribute__((naked,noinline)) sub_FF84EB84_my() { //#fs
        asm volatile (
		"stmdb	sp!, {r4, r5, r6, lr} \n"
		"ldr	r5,  =0x000029ac \n"
		"mov	r6, r0 \n"
		"ldr	r0, [r5, #20] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r0, #1	\n" // ; 0x1
		"ldmneia	sp!, {r4, r5, r6, pc} \n"
		"mov	r0, #23	\n" // ; 0x17
		"mul	r1, r0, r6 \n"
		"ldr	r0,  =0x00011544 \n"
		"add	r4, r0, r1, lsl #2 \n"
		"ldr	r0, [r4, #56] \n"
		"mov	r1, r6 \n"
//	"BL	sub_FF84E914 \n"
	"BL	sub_FF84E914_my \n" // continue to SDHC-hook here
		"cmp	r0, #0	\n" // ; 0x0
		"ldmeqia	sp!, {r4, r5, r6, pc} \n"
		"ldr	r0, [r4, #56] \n"
		"mov	r1, r6 \n"
		"BL	sub_FF84EA7C \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldmeqia	sp!, {r4, r5, r6, pc} \n"
		"mov	r0, r6 \n"
		"BL	sub_FF84E410 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r1, #1	\n" // ; 0x1
		"strne	r1, [r5, #20] \n"
		"ldmia	sp!, {r4, r5, r6, pc} \n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF84E914_my() { //#fs  ; Partition table parse takes place here. => SDHC-boot
        asm volatile (
		"stmdb	sp!, {r4, r5, r6, r7, r8, lr} \n"
		"mov	r8, r0 \n"
		"mov	r0, #23	\n" // ; 0x17
		"mul	r1, r0, r1 \n"
		"ldr	r0,  =0x00011544 \n"
		"mov	r6, #0	\n" // ; 0x0
		"add	r7, r0, r1, lsl #2 \n"
		"ldr	r0, [r7, #60] \n"
		"mov	r5, #0	\n" // ; 0x0
		"cmp	r0, #6	\n" // ; 0x6
		"addls	pc, pc, r0, lsl #2 \n"
		"B	loc_FF84EA60 \n"
		"B	loc_FF84E978 \n"
		"B	loc_FF84E960 \n"
		"B	loc_FF84E960 \n"
		"B	loc_FF84E960 \n"
		"B	loc_FF84E960 \n"
		"B	loc_FF84EA58 \n"
		"B	loc_FF84E960 \n"
	"loc_FF84E960:\n"
		"mov	r2, #0	\n" // ; 0x0
		"mov	r1, #512	\n" // ; 0x200
		"mov	r0, #3	\n" // ; 0x3
		"BL	sub_FF8677B8 \n"
		"movs	r4, r0 \n"
		"BNE	loc_FF84E980 \n"
	"loc_FF84E978:\n"
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	"loc_FF84E980:\n"
		"ldr	ip, [r7, #76] \n"
		"mov	r3, r4 \n"
		"mov	r2, #1	\n" // ; 0x1
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, r8 \n"
		"blx	ip \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BNE	loc_FF84E9AC \n"
		"mov	r0, #3	\n" // ; 0x3
		"BL	sub_FF8678F8 \n"
		"B	loc_FF84E978 \n"

	"loc_FF84E9AC:\n"
		"mov	r0, r8 \n"
		"BL	sub_FF91F484 \n"

		// Add FAT32 autodetect-code after this line

        // Start of DataGhost's FAT32 autodetection code
        // Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
        // According to the code below, we can use R1, R2, R3 and R12.
        // LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
        // that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
        "MOV     R12, R4\n"                    // Copy the MBR start address so we have something to work with
        "MOV     LR, R4\n"                     // Save old offset for MBR signature
        "MOV     R1, #1\n"                     // Note the current partition number
        "B       dg_sd_fat32_enter\n"          // We actually need to check the first partition as well, no increments yet!
   "dg_sd_fat32:\n"
        "CMP     R1, #4\n"                     // Did we already see the 4th partition?
        "BEQ     dg_sd_fat32_end\n"            // Yes, break. We didn't find anything, so don't change anything.
        "ADD     R12, R12, #0x10\n"            // Second partition
        "ADD     R1, R1, #1\n"                 // Second partition for the loop
   "dg_sd_fat32_enter:\n"
        "LDRB    R2, [R12, #0x1BE]\n"          // Partition status
        "LDRB    R3, [R12, #0x1C2]\n"          // Partition type (FAT32 = 0xB)
        "CMP     R3, #0xB\n"                   // Is this a FAT32 partition?
		"CMPNE   R3, #0xC\n"                   // Not 0xB, is it 0xC (FAT32 LBA) then?
        "BNE     dg_sd_fat32\n"                // No, it isn't.
        "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
        "CMPNE   R2, #0x80\n"
        "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                               // This partition is valid, it's the first one, bingo!
        "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.

   "dg_sd_fat32_end:\n"
        // End of DataGhost's FAT32 autodetection code

		"ldrb	r1, [r4, #457] \n" // Continue with firmware
		"ldrb	r3, [r4, #456] \n"
		"ldrb	ip, [r4, #460] \n"
		"mov	r1, r1, lsl #24 \n"
		"orr	r1, r1, r3, lsl #16 \n"
		"ldrb	r3, [r4, #455] \n"
		"ldrb	r2, [r4, #446] \n"
//	"ldrb	lr, [r4, #511] \n" // replaced, see below
		"orr	r1, r1, r3, lsl #8 \n"
		"ldrb	r3, [r4, #454] \n"
		"cmp	r2, #0	\n" // ; 0x0
		"cmpne	r2, #128	\n" // ; 0x80
		"orr	r1, r1, r3 \n"
		"ldrb	r3, [r4, #461] \n"
		"mov	r3, r3, lsl #24 \n"
		"orr	r3, r3, ip, lsl #16 \n"
		"ldrb	ip, [r4, #459] \n"
		"orr	r3, r3, ip, lsl #8 \n"
		"ldrb	ip, [r4, #458] \n"
		"orr	r3, r3, ip \n"
//	"ldrb	ip, [r4, #510] \n" // replaced, see below

	"LDRB    R12, [LR,#0x1FE]\n" // New! First MBR signature byte (0x55)
	"LDRB    LR, [LR,#0x1FF]\n"  //      Last MBR signature byte (0xAA)

		"mov	r4, #0	\n" // ; 0x0
		"BNE	loc_FF84EA34 \n"
		"cmp	r0, r1 \n"
		"BCC	loc_FF84EA34 \n"
		"add	r2, r1, r3 \n"
		"cmp	r2, r0 \n"
		"cmpls	ip, #85	\n" // ; 0x55
		"cmpeq	lr, #170	\n" // ; 0xaa
		"moveq	r6, r1 \n"
		"moveq	r5, r3 \n"
		"moveq	r4, #1	\n" // ; 0x1
	"loc_FF84EA34:\n"
		"mov	r0, #3	\n" // ; 0x3
		"BL	sub_FF8678F8 \n"
		"cmp	r4, #0	\n" // ; 0x0
		"BNE	loc_FF84EA6C \n"
		"mov	r6, #0	\n" // ; 0x0
		"mov	r0, r8 \n"
		"BL	sub_FF91F484 \n"
		"mov	r5, r0 \n"
		"B	loc_FF84EA6C \n"
	"loc_FF84EA58:\n"
		"mov	r5, #64	\n" // ; 0x40
		"B	loc_FF84EA6C \n"
	"loc_FF84EA60:\n"
		"mov	r1, #884	\n" // ; 0x374
		"ldr	r0, =0xff84e908 \n" // ; (6e756f4d)  *"Mounter.c"
		"BL	sub_FF81BDB8 \n" // <DebugAssert -208048>
	"loc_FF84EA6C:\n"
		"str	r6, [r7, #68]! \n"
		"mov	r0, #1	\n" // ; 0x1
		"str	r5, [r7, #4] \n"
		"ldmia	sp!, {r4, r5, r6, r7, r8, pc} \n"
	);
}; //#fe

/*
grep 'void.*_my' boot.c | cut -d' ' -f3 | cut -d_ -f1,2 | sort | while read i; do grep $i boot.c; done | grep -v void | less

*/

