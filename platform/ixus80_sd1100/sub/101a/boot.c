#include "lolevel.h"
#include "platform.h"
#include "core.h"
// test:
#include "../../leds.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_blinker();
void CreateTask_PhySw();
void CreateTask_spytask();

void boot();
void __attribute__((naked,noinline)) task_blinker();

void taskCreateHook(int *p) { 
 p-=16;
 if (p[0]==0xFF8B3D68)  p[0]=(int)exp_drv_task;
}

void taskCreateHook2(int *p) { 
 p-=16;
 if (p[0]==0xFF8B3D68)  p[0]=(int)exp_drv_task;
}



void boot() { //#fs
    long *canon_data_src = (void*)0xffb126f4;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xee8c - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xee8c; // just after data
    long canon_bss_len = MEMISOSTART - 0xee8c;

    long i;

    // Code taken from VxWorks CHDK. Changes CPU speed?
	// nope.
	// sets System Configuration Bits. (B3.2.2)
    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n" // enable L1 instruction cache
	"ORR     R0, R0, #4\n" // L1 unified/data cache enable
	"ORR     R0, R0, #1\n" // MMU or Protection Unit enable
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;

    *(int*)0x1930=(int)taskCreateHook; 
    *(int*)0x1934=(int)taskCreateHook2; 

/*
    asm volatile (
    "MRC     p15, 0, R0,c1,c0\n"
    "ORR     R0, R0, #0x1000\n"
    "BIC     R0, R0, #4\n"
    "ORR     R0, R0, #1\n"
    "MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
*/
    // jump to init-sequence that follows the data-copy-routine
    asm volatile ("B      sub_FF8101A4_my\n");
}; //#fe


// init #1
// Extracted method: (ff8101a4-ff81020c)
void __attribute__((naked,noinline)) sub_FF8101A4_my() {
	asm volatile (
		"ldr	r0,  =0xff81021c \n"
		"mov	r1, #0	\n" // ; 0x0
		"ldr	r3,  =0xff810254 \n"
	"loc_FF8101B0:\n"
		"cmp	r0, r3 \n"
		"ldrcc	r2, [r0], #4 \n"
		"strcc	r2, [r1], #4 \n"
		"BCC	loc_FF8101B0 \n"
		"ldr	r0,  =0xff810254 \n"
		"mov	r1, #1200	\n" // ; 0x4b0
		"ldr	r3,  =0xff810468 \n"
	"loc_FF8101CC:\n"
		"cmp	r0, r3 \n"
		"ldrcc	r2, [r0], #4 \n"
		"strcc	r2, [r1], #4 \n"
		"BCC	loc_FF8101CC \n"
		"mov	r0, #210	\n" // ; 0xd2
		"msr	CPSR_fsxc, r0 \n"
		"mov	sp, #4096	\n" // ; 0x1000
		"mov	r0, #211	\n" // ; 0xd3
		"msr	CPSR_fsxc, r0 \n"
		"mov	sp, #4096	\n" // ; 0x1000
		"ldr	r0,  =0x000006c4 \n"
		"ldr	r2,  =0xeeeeeeee \n"
		"mov	r3, #4096	\n" // ; 0x1000
	"loc_FF810200:\n"
		"cmp	r0, r3 \n"
		"strcc	r2, [r0], #4 \n"
		"BCC	loc_FF810200 \n"
//	"bl	sub_ff810fa0 \n"
	"bl	sub_FF810FA0_my \n"
		".pool \n"
        );

} //#fe

//init#2
// Extracted method: (ff810fa0-ff811040)
void __attribute__((naked,noinline)) sub_FF810FA0_my() {
	asm volatile (
		"str	lr, [sp, #-4]! \n"
		"sub	sp, sp, #116	\n" // ; 0x74
		"mov	r0, sp \n"
		"mov	r1, #116	\n" // ; 0x74
		"BL	sub_FFAA4D88 \n"
		"mov	r0, #339968	\n" // ; 0x53000
		"str	r0, [sp, #4] \n"
//	"ldr	r0,  =0x000bff60 \n"
	"ldr	r0,  =new_sa \n"
	"ldr	r0, [r0] \n"
		"ldr	r2,  =0x00279c00 \n"
		"ldr	r1,  =0x00272968 \n"
		"str	r0, [sp, #8] \n"
		"sub	r0, r1, r0 \n"
		"add	r3, sp, #12	\n" // ; 0xc
		"str	r2, [sp] \n"
		"stmia	r3, {r0, r1, r2} \n"
		"mov	r0, #34	\n" // ; 0x22
		"str	r0, [sp, #24] \n"
		"mov	r0, #104	\n" // ; 0x68
		"str	r0, [sp, #28] \n"
		"ldr	r0,  =0x0000019b \n"
		"mov	r1, #100	\n" // ; 0x64
		"strd	r0, [sp, #32] \n"
		"mov	r0, #120	\n" // ; 0x78
		"strd	r0, [sp, #40] \n"
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [sp, #48] \n"
		"str	r0, [sp, #52] \n"
		"mov	r0, #16	\n" // ; 0x10
		"str	r0, [sp, #92] \n"
		"mov	r0, #2048	\n" // ; 0x800
		"str	r0, [sp, #96] \n"
		"mov	r0, #160	\n" // ; 0xa0
		"str	r0, [sp, #100] \n"
		"mov	r0, #640	\n" // ; 0x280
		"str	r0, [sp, #104] \n"
//	"ldr	r1,  =0xff814da4 \n"
	"ldr	r1,  =uHwSetup_my \n"
		"mov	r0, sp \n"
		"mov	r2, #0	\n" // ; 0x0
		"BL	sub_FF812D58 \n"
		"add	sp, sp, #116	\n" // ; 0x74
		"ldr	pc, [sp], #4 \n"
		".pool \n"
        );
}; //#fe

// Extracted method: (ff814da4-ff814e18)
void __attribute__((naked,noinline)) uHwSetup_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"BL	sub_FF81094C \n"
		"BL	sub_FF81972C \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrlt	r0, =0xff814eb8 \n" // ; (65536d64)  *"dmSetup"
		"BLLT	sub_FF814E98 \n"
		"BL	sub_FF8149C8 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrlt	r0, =0xff814ec0 \n" // ; (6d726574)  *"termDriverInit"
		"BLLT	sub_FF814E98 \n"
		"ldr	r0, =0xff814ed0 \n" // ; (65745f2f)  *"/_term"
		"BL	sub_FF814AB4 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrlt	r0, =0xff814ed8 \n" // ; (6d726574)  *"termDeviceCreate"
		"BLLT	sub_FF814E98 \n"
		"ldr	r0, =0xff814ed0 \n" // ; (65745f2f)  *"/_term"
		"BL	sub_FF813564 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrlt	r0, =0xff814eec \n" // ; (69647473)  *"stdioSetup"
		"BLLT	sub_FF814E98 \n"
		"BL	sub_FF8192B4 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrlt	r0, =0xff814ef8 \n" // ; (6c647473)  *"stdlibSetup"
		"BLLT	sub_FF814E98 \n"
		"BL	sub_FF8114B8 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"ldrlt	r0, =0xff814f04 \n" // ; (6c6d7261)  *"armlib_setup"
		"BLLT	sub_FF814E98 \n"
		"ldmia	sp!, {r4, lr} \n"
//	"B	sub_FF81CD84 \n"
	"B	taskcreate_Startup_my \n"
	);
}

// Extracted method: (ff81cd84-ff81cdf0)
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
	asm volatile (
		"stmdb	sp!, {r3, lr} \n"
		"BL	sub_FF821CB4 \n"
		"BL	sub_FF829FA4 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF81CDB4 \n"
		"BL	sub_FF821CB0 \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF81CDB4 \n"
		"ldr	r1,  =0xc0220000 \n"
		"mov	r0, #68	\n" // ; 0x44
		"str	r0, [r1, #76] \n"
	"loc_FF81CDB0:\n"
		"B	loc_FF81CDB0 \n"
	"loc_FF81CDB4:\n"
		"BL	sub_FF821CBC \n"
		"BL	sub_FF821CB8 \n"
		"BL	sub_FF82832C \n"
		"ldr	r1,  =0x002ce000 \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF828574 \n"
		"BL	sub_FF828520 \n"
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
//	"ldr	r3, =0xff81cd28 \n" // ; (e92d4010)
	"ldr	r3, =task_Startup_my  \n" // ; (e92d4010)
		"mov	r2, #0	\n" // ; 0x0
		"mov	r1, #25	\n" // ; 0x19
		"ldr	r0, =0xff81cdfc \n" // ; (72617453)  *"Startup"
		"BL	sub_FF81B8E0 \n" // <CreateTask -5384>
"BL core_spytask_can_start \n" // save to start flag
		"mov	r0, #0	\n" // ; 0x0
		"ldmia	sp!, {ip, pc} \n"
		".pool \n"
        );
}; //#fe

// Extracted method: (ff81cd28-ff81cd80)
void __attribute__((naked,noinline)) task_Startup_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"BL	sub_FF8151BC \n" // <taskcreate_ClockSave -31600>
		"BL	sub_FF822E14 \n"
		"BL	sub_FF81FEB8 \n"
		"BL	sub_FF829FE4 \n"
		"BL	sub_FF82A1AC \n"
//	"BL	sub_FF82A06C \n" // <StartDiskboot +54060>
	);

	// CreateTask_blinker();
	CreateTask_spytask(); // +

	asm volatile (
		"BL	sub_FF82A360 \n"

//	"BL	sub_FF82A1FC \n"
	"BL	sub_FF82A1FC_my \n" // --> hook watchdog

//	"BL	sub_FF82786C \n"
	"BL	sub_FF82786C_my \n" // --> hook exception handlers

		"BL	sub_FF82A364 \n"

//	"BL	sub_FF821BC8 \n" // <taskcreate_PhySw +20084>
	"BL	sub_FF821BC8_my \n" // mykbd_task

//	"BL	sub_FF824D7C \n"
	"BL	sub_FF824D7C_my \n"

		"BL	sub_FF82A37C \n"
		"BL	sub_FF81FBD8 \n"
		"BL	sub_FF821084 \n"
		"BL	sub_FF829D6C \n" // <taskcreate_Bye +53252>
		"BL	sub_FF8216F8 \n"
		"BL	sub_FF820F74 \n" // <taskcreate_TempCheck +16900>
		"BL	sub_FF82ACC4 \n"
		"BL	sub_FF820F30 \n"
		"ldmia	sp!, {r4, lr} \n"
		"B	sub_FF815070 \n"
	);
}; //#fe

void CreateTask_spytask() { //#fs
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

/*
void CreateTask_PhySw() {
        _CreateTask("PhySw", 0x17, 0x800, mykbd_task, 0);
}; //#fe
*/

// taskcreate_PhySw / CreateTask_PhySw
// Extracted method: (ff821bc8-ff821c0c)
void __attribute__((naked,noinline)) sub_FF821BC8_my() {
	asm volatile (
		"stmdb	sp!, {r3, r4, r5, lr} \n"
		"ldr	r4,  =0x00001bf4 \n"
		"ldr	r0, [r4, #16] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF821BFC \n"
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
//	"ldr	r3, =0xff821b94 \n" // ; (e92d4010)
	"ldr	r3, =mykbd_task \n" // ; (e92d4010)
		"mov	r2, #2048	\n" // ; 0x800
		"mov	r1, #23	\n" // ; 0x17
		"ldr	r0, =0xff821df0 \n" // ; (53796850)  *"PhySw"
		"BL	sub_FF81BBB8 \n" // <KernelCreateTask -24636>
		"str	r0, [r4, #16] \n"
	"loc_FF821BFC:\n"
		"BL	sub_FF86B294 \n"
		"ldr	r1,  =0x0001037c \n"
		"ldmia	sp!, {r3, r4, r5, lr} \n"
		"mov	r0, #0	\n" // ; 0x0
		"B	sub_FF86B164 \n"
	);
}


//FIXME: dummmy while movie rec is out
void change_video_tables(int a, int b){}

// Extracted method: (ff824d7c-ff824dc8)
void __attribute__((naked,noinline)) sub_FF824D7C_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x00001c14 \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #4	\n" // ; 0x4
		"str	r0, [r4, #12] \n"
		"BL	sub_FF81BC10 \n" //
		"str	r0, [r4, #4] \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #1	\n" // ; 0x1
		"BL	sub_FF81BC34 \n" //
		"str	r0, [r4, #8] \n"
		"BL	sub_FF860E9C \n" //
		"BL	sub_FF862138 \n" //
		"BL	sub_FF85FF04 \n" //
//	"BL	sub_FF85CC94 \n" //
	"BL	sub_FF85CC94_my \n" // // divert this for ShootSeqTask
		"BL	sub_FF861170 \n" //
		"ldr	r0, [r4, #4] \n"
		"ldmia	sp!, {r4, lr} \n"
		"mov	r1, #4096	\n" // ; 0x1000
		"B	sub_FF827BD0 \n" //
        );
}; //#fe

// Extracted method: (ff85cc94-ff85cd08)
void __attribute__((naked,noinline)) sub_FF85CC94_my() {
	asm volatile (
		"stmdb	sp!, {r4, lr} \n"
		"ldr	r4,  =0x00005484 \n"
		"ldr	r0, [r4, #4] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FF85CD00 \n" //
		"BL	sub_FF85F500 \n" //
		"mov	r1, #1	\n" // ; 0x1
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF81BC34 \n" //
		"str	r0, [r4, #12] \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #0	\n" // ; 0x0
		"BL	sub_FF81BC10 \n" //
		"str	r0, [r4, #16] \n"
		"BL	sub_FF85D050 \n" //
		"BL	sub_FF85D4FC \n" //
		"mov	r0, #0	\n" // ; 0x0
		"str	r0, [r4, #8] \n"
		"add	r0, r4, #20	\n" // ; 0x14
		"mov	r1, #0	\n" // ; 0x0
		"str	r1, [r0], #4 \n"
		"str	r1, [r0] \n"
		"BL	sub_FF85D714 \n" //
		"BL	sub_FF86131C \n" //
		"BL	sub_FF85F8C0 \n" //
//	"BL	sub_FF85E0A4 \n" //
	"BL	sub_FF85E0A4_my \n" //  // task_CaptSeqTask
		"BL	sub_FF85F384 \n" //
	"loc_FF85CD00:\n"
		"mov	r0, #1	\n" // ; 0x1
		"str	r0, [r4, #4] \n"
		"ldmia	sp!, {r4, pc} \n"
        );
}; //#fe

// Extracted method: (ff85e0a4-ff85e120)
void __attribute__((naked,noinline)) sub_FF85E0A4_my() {
	asm volatile (
		"stmdb	sp!, {r3, r4, r5, lr} \n"
		"ldr	r2,  =0x00019a10 \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #0	\n" // ; 0x0
	"loc_FF85E0B4:\n"
		"add	r3, r2, r0, lsl #4 \n"
		"add	r0, r0, #1	\n" // ; 0x1
		"cmp	r0, #5	\n" // ; 0x5
		"str	r1, [r3, #8] \n"
		"BCC	loc_FF85E0B4 \n" //
		"BL	sub_FF938AEC \n" //
		"BL	sub_FF93A8FC \n" //
		"mov	r1, #5	\n" // ; 0x5
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF81BBEC \n" //
		"ldr	r4,  =0x000054b8 \n"
		"ldr	r1,  =0x001001ff \n"
		"str	r0, [r4, #12] \n"
		"mov	r0, #0	\n" // ; 0x0
		"BL	sub_FF81BC10 \n" //
		"str	r0, [r4, #8] \n"
		"mov	r0, #0	\n" // ; 0x0
		"mov	r1, #1	\n" // ; 0x1
		"BL	sub_FF81BC34 \n" //
		"str	r0, [r4, #16] \n"
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
//	"ldr	r3, =0xff85de08 \n" // ; (e92d43f8)
	"ldr	r3, =task_CaptSeqTask_my \n" // ; (e92d43f8)
		"ldr	r0, =0xff85e2a4 \n" // ; (74706143)  *"CaptSeqTask"
		"mov	r2, #4096	\n" // ; 0x1000
		"mov	r1, #23	\n" // ; 0x17
		"BL	sub_FF81BBB8 \n" // <KernelCreateTask -271716>
		"ldmia	sp!, {r3, r4, r5, pc} \n"
		".pool \n"
        );
}; //#fe

