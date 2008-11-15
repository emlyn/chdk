#include "lolevel.h"
#include "stdlib.h"
//#include "core.h"
#include "script.h"
// exception handler hooks
// Extracted method: (ff82786c-ff827894)
void __attribute__((naked,noinline)) sub_FF82786C_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"mov	r0, #12	\n" // ; 0xc
		"BL	sub_FF8627FC \n" // create taks errlog (?)

//	"ldr	r0,  =0xff862858 \n" // assert hook
	"ldr	r0,  =assert_hook \n" //
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF81BDD8 \n" // register

//	"ldr	r0,  =0xff862c50 \n" // cpu abort
	"ldr	r0,  =abort_hook \n" //
		"BL	sub_FF862240 \n" // register

//	"ldr	r0,  =0xff862fcc \n" // os panic
	"ldr	r0,  =panic_hook \n" //
		"BL	sub_FF86224C \n" // register
		"ldmia	sp!, {r4, pc} \n"
	);
}

// #define O_APPEND 0x8
static int crash_fd = 0;
void open_crash() {
	crash_fd = open("A/crash.log", O_WRONLY|O_CREAT|O_APPEND, 0777);
}
void write_crash(char* buf, int len) {
	write(crash_fd, buf, len);
}
void close_crash() {
	close(crash_fd);
}

// all original hooks write crashlog to ROM
// see
// OpLog.Get = OpLog.ReadFromROM, OpLog.WriteToSD
//
void assert_hook() {
	asm volatile(
		"stmdb sp!, {r0, r1} \n"
	);
	script_console_add_line("assert failed: game over :(");
	_OpLog_WriteToSD(0);
	msleep(1000);
	asm volatile(
		"ldmia sp!, {r0, r1} \n"
		"BL sub_FF862858 \n" // original assert handler, no return
	);
	script_console_add_line("assert done");
}

void abort_hook() {
	asm volatile(
		"stmdb sp!, {r0} \n"
	);

	script_console_add_line("abort error: game over :(");
	_OpLog_WriteToSD(0);
	msleep(1000);
	asm volatile(
		"ldmia sp!, {r0} \n"
		"BL sub_FF862C50 \n" // abort default, no return: default shutdown
	);

	script_console_add_line("abort done");
}
// GetLogToFile
void panic_hook_dump();
void panic_hook() {
	asm volatile(
		"stmdb sp!, {r0, r1} \n"
	);
	script_console_add_line("dryos panic: game over :(");
	_OpLog_WriteToSD(0);
	msleep(1000);
	asm volatile(
		"ldmia sp!, {r0, r1} \n"
		"BL sub_FF862FCC \n" // panic_hook_dump();
	);
	script_console_add_line("panic done");
}
#if 0
///////////////////////////////////////
// panic hook
// Extracted method: (ff862fcc-ff86304c)
void __attribute__((naked,noinline)) panic_hook_dump() {
	asm volatile (
		"stmdb	sp!, {r2, r3, r4, r5, r6, r7, r8, lr} \n"
		"ldr	r5,  =0x00005574 \n"
		"mov	r7, r0 \n"
		"ldr	r0, [r5] \n"
		"mov	r8, r1 \n"
		"cmp	r0, #1	\n" // ; 0x1
		"BEQ	sub_FF863114 \n" // <_binary_dump_bin_start+0x53114 +304>
		"mov	r0, #1	\n" // ; 0x1
		"str	r0, [r5] \n"
		"ldr	r0, =0xff8632e0 \n" // ; (7379530a)
		"mov	r2, r8 \n"
		"mov	r1, r7 \n"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r0, [r5, #8] \n"
		"BL	sub_FF82789C \n" // <_binary_dump_bin_start+0x1789c -243560>
		"ldr	r0,  =0xff862798 \n"
		"ldr	r1, [r5, #8] \n"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"mov	r1, sp \n"
		"add	r2, r1, #128	\n" // ; 0x80
		"ldr	r0, =0xff86330c \n" // ; (63617453)  *"StackDump(0x%X - 0x%X):"
		"str	r1, [sp, #4] \n"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r4, [sp, #4] \n"
		"B	loc_FF863040 \n" // <_binary_dump_bin_start+0x53040 +20>
	"loc_FF863030:\n"
		"ldr	r0,  =0xff862c0c \n"
		"ldr	r1, [r4] \n"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"add	r4, r4, #4	\n" // ; 0x4
	"loc_FF863040:\n"
		"ldr	r0, [sp, #4] \n"
		"add	r0, r0, #128	\n" // ; 0x80
		"cmp	r4, r0 \n"
		"BCC	loc_FF863030 \n" // <_binary_dump_bin_start+0x53030 -28>
	// continue ROM
	"B sub_FF863050 \n"
	);
}

///////////////////////////////////////
// cpu abort handler
// Extracted method: (ff862c50-ff862db4)
void __attribute__((naked,noinline)) abort_hook_dump() {
	asm volatile (
		"stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr} \n"
		"ldr	r8,  =0x00005574 \n"
		"mov	r4, r0 \n"
		"ldr	r0, [r8] \n"
		"sub	sp, sp, #128	\n" // ; 0x80
		"cmp	r0, #1	\n" // ; 0x1
		"BEQ	sub_FF862FC4 \n" // <_binary_dump_bin_start+0x52fc4 +860>
		"mov	r0, #1	\n" // ; 0x1
		"str	r0, [r8] \n"
		"ldr	r0, [r4] \n"
		"cmp	r0, #4	\n" // ; 0x4
		"ldreq	r5, =0xff862f44 \n" // ; (65646e75)  *"undefined instruction"
		"BEQ	loc_FF862C90 \n" // <_binary_dump_bin_start+0x52c90 +16>
		"cmp	r0, #12	\n" // ; 0xc
		"ldreq	r5, =0xff862f5c \n" // ; (66657270)  *"prefetch abort"
		"ldrne	r5, =0xff862f6c \n" // ; (61746164)  *"data abort"
	"loc_FF862C90:\n"
		"ldr	r0, [r4, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"movne	r7, #2326528	\n" // ; 0x238000
		"BNE	loc_FF862CBC \n" // <_binary_dump_bin_start+0x52cbc +32>
		"BL	sub_FF812128 \n" // <_binary_dump_bin_start+0x2128 -330616>
		"ldr	r0, [r4, #8] \n"
		"add	r1, sp, #80	\n" // ; 0x50
		"BL	sub_FF81339C \n" // <_binary_dump_bin_start+0x339c -325904>
		"ldr	r0, [sp, #108] \n"
		"ldr	r1, [sp, #112] \n"
		"add	r7, r0, r1 \n"
	"loc_FF862CBC:\n"
		"mov	r1, r5 \n"
		"ldr	r0, =0xff862f78 \n" // ; (6378450a)
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r0, [r8, #8] \n"
		"BL	sub_FF82789C \n" // <_binary_dump_bin_start+0x1789c -242736>
		"ldr	r0, =0xff862798 \n" // ; (7563634f)  *"Occured Time  %s"
		"ldr	r1, [r8, #8] \n"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r0, [r4, #4] \n"
		"ldr	r9,  =0xff810218 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrne	r0, [r9] \n"
		"ldrne	r0, [r0] \n"
		"movne	r1, r0, lsr #2 \n"
		"ldrne	r0,  =0xff8627b0 \n"
		"BNE	loc_FF862D10 \n" // <_binary_dump_bin_start+0x52d10 +24>
		"ldr	r1, [r4, #8] \n"
		"ldr	r0, =0xff862be8 \n" // ; (6b736154)  *"Task ID: %d"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r1, [sp, #124] \n"
		"ldr	r0, =0xff862bf8 \n" // ; (6b736154)  *"Task name: %s"
	"loc_FF862D10:\n"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r0, =0xff862f90 \n" // ; (20637845)  *"Exc Registers:"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"mov	r5, #0	\n" // ; 0x0
	"loc_FF862D20:\n"
		"ldr	r0, [r4, #12] \n"
		"ldr	r1, [r0, r5, lsl #2] \n"
		"ldr	r0, =0xff862c0c \n" // ; (30257830)
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"add	r5, r5, #1	\n" // ; 0x1
		"cmp	r5, #15	\n" // ; 0xf
		"BLT	loc_FF862D20 \n" // <_binary_dump_bin_start+0x52d20 -24>
		"ldr	r0, [r4, #12] \n"
		"ldr	r1, [r0, #60] \n"
		"ldr	r0, =0xff862c0c \n" // ; (30257830)
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r0, [r4, #12] \n"
		"ldr	r1, [r0, #64] \n"
		"ldr	r0, =0xff862c0c \n" // ; (30257830)
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"ldr	r0, [r4, #12] \n"
		"ldr	r5, [r0, #52] \n"
		"ldr	r0, =0xff862c14 \n" // ; (63617453)  *"StackDump:"
		"mov	sl, r5 \n"
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"mov	r6, #0	\n" // ; 0x0
	"loc_FF862D74:\n"
		"cmp	r5, r7 \n"
		"BHI	loc_FF862D98 \n" // <_binary_dump_bin_start+0x52d98 +32>
		"ldr	r1, [r5] \n"
		"ldr	r0, =0xff862c0c \n" // ; (30257830)
//	"BL	sub_FF81351C \n" // ; STDERR
	"BL	sub_FF81351C_my \n" //
		"add	r6, r6, #1	\n" // ; 0x1
		"cmp	r6, #32	\n" // ; 0x20
		"add	r5, r5, #4	\n" // ; 0x4
		"BLT	loc_FF862D74 \n" // <_binary_dump_bin_start+0x52d74 -32>
	"loc_FF862D98:\n"
		"ldr	r0, [r4, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	sub_FF862DBC \n" // <_binary_dump_bin_start+0x52dbc +28>
		"ldr	r0, [r8, #16] \n"
		"cmp	r0, #12	\n" // ; 0xc
		"BEQ	sub_FF862DC8 \n" // <_binary_dump_bin_start+0x52dc8 +28>
		"ldr	r0,  =0xff862268 \n"
		"mov	r1, #0	\n" // ; 0x0
	"B sub_FF862DB8 \n" // continue rom
	);
}
#endif

////////////////////////////////////////
// Watchdog
// Extracted method: (ff82a1fc-ff82a298)
void __attribute__((naked,noinline)) sub_FF82A1FC_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"mov	r1, #4	\n" // ; 0x4
		"mov	r0, #2	\n" // ; 0x2
//	"BL	sub_FF86B9F4 \n" // <taskcreate_WdtReset +268268>
	"BL taskcreate_WdtReset_my \n" // --------------->
		"BL	sub_FF86BA8C \n" // <StartWDT +268416>
		"BL	sub_FF86900C \n" // <EventProcedure +257532>
		"BL	sub_FF864D60 \n" //
		"BL	sub_FF83F1FC \n" //
		"BL	sub_FF86BC74 \n" //
		"ldr	r2,  =0x12cea600 \n"
		"ldr	r1,  =0x7fe8177f \n"
		"BL	sub_FF828348 \n" //
		"BL	sub_FF8411E0 \n" //
		"BL	sub_FF846238 \n" //
		"BL	sub_FF821748 \n" //
		"BL	sub_FF845CC0 \n" //
		"mov	r0, #1	\n" // ; 0x1
		"BL	sub_FF842BBC \n" // <taskcreate_AudioTsk +100732>
		"BL	sub_FF83D9E8 \n" //
		"BL	sub_FF8362B4 \n" //
		"BL	sub_FF840988 \n" //
		"BL	sub_FF84074C \n" //
		"BL	sub_FF840A40 \n" //
		"BL	sub_FF8450B0 \n" // <taskcreate_Thermometer +110168>
		"BL	sub_FF855E80 \n" //
		"BL	sub_FF841FC4 \n" // <taskcreate_LEDCon +97636>
		"BL	sub_FF86CA3C \n" //
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF82A1E0 \n" //
	);
}


// Extracted method: (ff86b9f4-ff86ba88)
void __attribute__((naked,noinline)) taskcreate_WdtReset_my() {
	asm volatile (
		"mov	r1, r1, lsl #8 \n"
		"stmdb	sp!, {r3, r4, r5, lr} \n"
		"orr	r0, r1, r0, lsl #4 \n"
		"ldr	r4,  =0x00005770 \n"
		"ldr	r1,  =0xc0410000 \n"
		"orr	r0, r0, #-1073741824	\n" // ; 0xc0000000
		"str	r0, [r4, #8] \n"
		"str	r0, [r1] \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF8280C8 \n" // <_binary_dump_bin_start+0x180c8 -276816>
		"str	r0, [r4, #16] \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r4, #12] \n"
		"ldr	r0, =0xff86bba0 \n" // ; (49746457)  *"WdtInt"
		"mov	r3, #0	\n" // ; 0x0
		"ldr	r2, =0xff86b9a0 \n" // ; (e59f11f0)
		"mov	r1, #3	\n" // ; 0x3
		"BL	sub_FF81B5A0 \n" // <_binary_dump_bin_start+0xb5a0 -328856>
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
		"ldr	r3, =0xff86b9cc \n" // ; (e92d4070)
		"mov	r2, #512	\n" // ; 0x200
		"mov	r1, #24	\n" // ; 0x18
		"ldr	r0, =0xff86bba8 \n" // ; (52746457)  *"WdtReset"
		"BL	sub_FF81BBB8 \n" // <KernelCreateTask -327324>
		"mov	r1, #0	\n" // ; 0x0
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF81BC34 \n" // <_binary_dump_bin_start+0xbc34 -327212>
		"str	r0, [r4, #20] \n"
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
//	"ldr	r3, =0xff86b918 \n" // ; (e92d40f8)
	"ldr	r3, =WdtPrint_my \n" // ---------->
		"ldr	r0, =0xff86bbb4 \n" // ; (50746457)  *"WdtPrint"
		"mov	r2, #512	\n" // ; 0x200
		"mov	r1, #1	\n" // ; 0x1
		"BL	sub_FF81BBB8 \n" // <KernelCreateTask -327368>
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {r3, r4, r5, pc} \n"
	);
}

//WdtPrint
// Extracted method: (ff86b918-ff86b9c8)
void __attribute__((naked,noinline)) WdtPrint_my() {
	asm volatile (
		"stmdb	sp!, {r3, r4, r5, r6, r7, lr} \n"
		"ldr	r5,  =0x0001a0c0 \n"
		"mov	r6, #0	\n" // ; 0x0
	"loc_FF86B924:\n"
		"mov	r0, #0	\n" // ; 0x0
	"loc_FF86B928:\n"
		"str	r6, [r5, r0, lsl #4] \n"
		"add	r0, r0, #1	\n" // ; 0x1
		"cmp	r0, #10	\n" // ; 0xa
		"BLT	loc_FF86B928 \n" // <_binary_dump_bin_start+0x5b928 -12>
		"ldr	r4,  =0x00005770 \n"
		"mov	r1, #0	\n" // ; 0x0
		"ldr	r0, [r4, #20] \n"
		"BL	sub_FF81B774 \n" // <TakeSemaphore -328144>
		"mov	r0, #800	\n" // ; 0x320
		"BL	sub_FF8284B4 \n" // <SleepTask -275608>
		"mov	r0, #10	\n" // ; 0xa
		"str	r0, [r4, #4] \n"

	"ldr	r0, =0xff86bb4c \n" // ; (21200a0a) "!!!WatchDog expired!!!"
	"BL script_console_add_line \n"
		"ldr	r0, =0xff86bb4c \n" // ; (21200a0a) "!!!WatchDog expired!!!"
	"BL	sub_FF81351C_my \n" // ; STDERR
	"mov r0, #0 \n"
	"BL _OpLog_WriteToSD \n"

		"mov	r4, #0	\n" // ; 0x0
		"B	loc_FF86B98C \n" // <_binary_dump_bin_start+0x5b98c +40>
	"loc_FF86B968:\n"
		"str	r3, [sp] \n"
		"ldr	r2, [r0, #8] \n"
		"ldr	r3, [r0, #12] \n"
		"ldr	r1, [r5, r4, lsl #4] \n"
		"ldr	r0, =0xff86bb6c \n" // ; (73255b20)  *" [%s (LR:0x%08lx , PC:0x%08lx)] -> [%s] "
	"BL	sub_FF81351C_my\n" // ; STDERR
		"add	r4, r4, #1	\n" // ; 0x1
		"cmp	r4, #10	\n" // ; 0xa
		"BGE	loc_FF86B924 \n" // <_binary_dump_bin_start+0x5b924 -100>
	"loc_FF86B98C:\n"
		"add	r0, r5, r4, lsl #4 \n"
		"ldr	r3, [r0, #4] \n"
		"cmp	r3, #0	\n" // ; 0x0
		"BNE	loc_FF86B968 \n" // <_binary_dump_bin_start+0x5b968 -48>
		"B	loc_FF86B924 \n" // <_binary_dump_bin_start+0x5b924 -120>
	);
}

//
// printf STDERR ... whatever ...

// Extracted method: (ff81351c-ff81355c)
void __attribute__((naked,noinline)) sub_FF81351C_my() {
	asm volatile (
		"stmdb	sp!, {r0, r1, r2, r3} \n"
		"stmdb	sp!, {r4, lr} \n"
	);
	open_crash();
	asm volatile (
		"sub	sp, sp, #24	\n" // ; 0x18
		"mov	r0, #2	\n" // ; 0x2
		"strh	r0, [sp, #16] \n"
		"mrs	r4, CPSR \n"
		"orr	r0, r4, #128	\n" // ; 0x80
		"msr	CPSR_c, r0 \n"
		"ldr	r2, [sp, #32] \n"
//	"ldr	r0,  =0xff810904 \n"
	"ldr	r0,  =sub_FF810904_my \n"
		"add	r3, sp, #36	\n" // ; 0x24
		"mov	r1, sp \n"
		"BL	sub_FF818B80 \n" // <_binary_dump_bin_start+0x8b80 +22068>
		"msr	CPSR_c, r4 \n"
		"add	sp, sp, #24	\n" // ; 0x18
	);
	close_crash();
	asm volatile (
		"ldr	r4, [sp], #4 \n"
		"ldr	pc, [sp], #20 \n"
	);
}

// Extracted method: (ff810904-ff810920)
// r0=?
// r1=text
// r2=len
void __attribute__((naked,noinline)) sub_FF810904_my() {
	asm volatile (
		"mov	r0, r1 \n"
		"mov	r1, r2 \n"
		"ldr	r2,  =0x00001900 \n"
		"ldr	r2, [r2] \n"
//		"cmp	r2, #0	\n" // ; 0x0
//		"moveq	r0, r1 \n"
//	"BNE	sub_FF814970 \n" //
	"B	sub_FF814970_my \n" //
//	"bx	lr \n"
	);
}

// Extracted method: (ff814970-ff814994)
// r0=text
// r1=len
void __attribute__((naked,noinline)) sub_FF814970_my() {
	asm volatile (
		"mov	r2, r1 \n"
		"mov	r1, r0 \n"
		"stmdb	sp!, {r3, lr} \n"
		"mov	r3, sp \n"
//	"mov	r0, #0	\n" // ; 0x0
//	"BL	sub_FF81ABFC <<<<<<< writef errlog, *r1=text, r2=len \n"
	"mov r0, r1 \n"
	"mov r1, r2 \n"
	"BL write_crash \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrge	r0, [sp] \n"
		"mvnlt	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {ip, pc} \n"
	);
}
