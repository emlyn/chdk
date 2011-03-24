#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "stdlib.h"

const char * const new_sa = &_end;


// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
extern volatile int jogdial_stopped;
void JogDial_task_my(void);


/*---------------------------------------------------------------------
  Memory Map:
	00001900     MEMBASEADDR             start of data - used for initialized vars
	00010FE3                             end of inited data
	00010FE4                             start of bss - used for zeroed/uninited vars
	00016E2F                             end of bss
	0016EE30     MEMISOSTART             start of CHDK code / data / bss
	001B0000							 end of CHDK data (approx)
	001B0001							 start of DRYOS heap (approx)
	0037FFFF							 end of heap (?)

	41269150							 raw buffer 0
	46000000                             raw buffer 1

	C0xxxxxx                            I/O

	FF810000    ROMBASEADDR             start of rom
	FFFFFFFF                            end of rom
----------------------------------------------------------------------*/


/*----------------------------------------------------------------------
	taskCreateHook()
-----------------------------------------------------------------------*/
void taskCreateHook(int *p)
{
	p-=17;

	if (p[0] == 0xFF88322C)
		p[0] = (int) capt_seq_task;

	if (p[0] == 0xFF98642C)
		p[0] = (int) movie_record_task;

	if (p[0] == 0xFF8A0AA0)
		p[0] = (int) init_file_modules_task;

	if (p[0] == 0xFF8CF1A8)
		p[0] = (int) exp_drv_task;

	if (p[0] == 0xFF865894)
		p[0] = (int) JogDial_task_my;
}


/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) boot()
{

    asm volatile (
"		LDR	R1, =0xC0410000 \n"
"		MOV	R0, #0 \n"
"		STR	R0, [R1] \n"

"		MOV	R1, #0x78 \n"
"		MCR	p15, 0,	R1,c1,c0 \n"		// control reg

"		MOV	R1, #0 \n"
"		MCR	p15, 0,	R1,c7,c10, 4 \n"	// drain write buffer
"		MCR	p15, 0,	R1,c7,c5 \n"		// flush instruction cache
"		MCR	p15, 0,	R1,c7,c6 \n"		// flush data cache

"		MOV	R0, #0x3D \n"				// size 2GB base 0x00000000
"		MCR	p15, 0,	R0,c6,c0 \n"		// protection region 0
"		MOV	R0, #0xC000002F \n"			// size 16M base 0xc0000000
"		MCR	p15, 0,	R0,c6,c1 \n"		// protection region 1
"		MOV	R0, #0x35 \n"				// size 128M base 0x00000000 (s90 is 64M)
"		MCR	p15, 0,	R0,c6,c2 \n"		// protection region 2
"		MOV	R0, #0x40000035 \n"			// size 128M base 0x40000000 (s90 is 64M)
"		MCR	p15, 0,	R0,c6,c3 \n"		// protection region 3
"		MOV	R0, #0x80000017 \n"			// size  4k base 0x80000000
"		MCR	p15, 0,	R0,c6,c4 \n"		// protection region 4
"		LDR	R0, =0xFF80002D \n"			// size  8M base 0xff800000
"		MCR	p15, 0,	R0,c6,c5 \n"		// protection region 5

"		MOV	R0, #0x34 \n"				// regions 2,4,5
"		MCR	p15, 0,	R0,c2,c0 \n"		// data cachable bits
"		MOV	R0, #0x34 \n"				// regions 2,4,5
"		MCR	p15, 0,	R0,c2,c0, 1 \n"		// instruction cachable bits

"		MOV	R0, #0x34 \n"				// regions 2,4,5
"		MCR	p15, 0,	R0,c3,c0 \n"		// data bufferable bits
"		LDR	R0, =0x3333330 \n"			// region 0,7 = --, 1-6 = rw
"		MCR	p15, 0,	R0,c5,c0, 2 \n"		// data access permission
"		LDR	R0, =0x3333330 \n"			// region 0,7 = --, 1-6 = rw
"		MCR	p15, 0,	R0,c5,c0, 3 \n"		// instruction access permission

"		MRC	p15, 0,	R0,c1,c0 \n"		// control reg
"		ORR	R0, R0,	#0x1000 \n"			// enable L1 instruction cache
"		ORR	R0, R0,	#4 \n"				// L1 unified/data cache enable
"		ORR	R0, R0,	#1 \n"				// MMU or Protection Unit enable
"		MCR	p15, 0,	R0,c1,c0 \n"		// control reg

"		MOV	R1, #0x80000006 \n"			// size 4K base 0x80000000
"		MCR	p15, 0,	R1,c9,c1 \n"		// data tightly-coupled memory
"		MOV	R1, #6 \n"					// size 4K base 0x00000000
"		MCR	p15, 0,	R1,c9,c1, 1 \n"		// instruction tightly-coupled memory
"		MRC	p15, 0,	R1,c1,c0 \n"		// control reg

"		ORR	R1, R1,	#0x50000 \n"		// DRAM bit | IRAM bit
"		MCR	p15, 0,	R1,c1,c0 \n"		// control reg

"		LDR	R2, =0xC0200000 \n"
"		MOV	R1, #1 \n"
"		STR	R1, [R2,#0x10C] \n"

"		MOV	R1, #0xFF \n"
"		STR	R1, [R2,#0xC] \n"
"		STR	R1, [R2,#0x1C] \n"
"		STR	R1, [R2,#0x2C] \n"
"		STR	R1, [R2,#0x3C] \n"
"		STR	R1, [R2,#0x4C] \n"
"		STR	R1, [R2,#0x5C] \n"
"		STR	R1, [R2,#0x6C] \n"
"		STR	R1, [R2,#0x7C] \n"
"		STR	R1, [R2,#0x8C] \n"
"		STR	R1, [R2,#0x9C] \n"
"		STR	R1, [R2,#0xAC] \n"
"		STR	R1, [R2,#0xBC] \n"
"		STR	R1, [R2,#0xCC] \n"
"		STR	R1, [R2,#0xDC] \n"
"		STR	R1, [R2,#0xEC] \n"
"		STR	R1, [R2,#0xFC] \n"

"		LDR	R1, =0xC0400008 \n"
"		LDR	R2, =0x430005 \n"
"		STR	R2, [R1] \n"

"		MOV	R1, #1 \n"
"		LDR	R2, =0xC0243100 \n"
"		STR	R2, [R1] \n"

"		LDR	R2, =0xC0242010 \n"
"		LDR	R1, [R2] \n"
"		ORR	R1, R1,	#1 \n"
"		STR	R1, [R2] \n"

"		LDR	R0, =0xFFC9A23C \n"					// init data section
"		LDR	R1, =0x1900 \n"
"		LDR	R3, =0x10FE4 \n"
"loc_FF81013C: \n"
"		CMP	R1, R3 \n"
"		LDRCC	R2, [R0],#4 \n"
"		STRCC	R2, [R1],#4 \n"
"		BCC	loc_FF81013C \n"

"		LDR	R1, =0x16EE30 \n"					// clear bss section
"		MOV	R2, #0 \n"
"loc_FF810154: \n"
"		CMP	R3, R1 \n"
"		STRCC	R2, [R3],#4 \n"
"		BCC	loc_FF810154 \n"

//"		B	sub_FF810354 \n"
"		B	sub_FF810354_my \n"					// patched
    );
};


/*----------------------------------------------------------------------
	sub_FF810354_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF810354_my()
{
    *(int*)0x1938 = (int)taskCreateHook;
    *(int*)0x193C = (int)taskCreateHook;

	// s95 @FF864D68
	// fix for correct power-on
	// must also comment out function in taskcreate_Startup_my

	if ((*(int*) 0xC0220128) & 1)					// look at play switch
		*(int*)(0x25E8) = 0x200000;					// start in play mode
	else
		*(int*)(0x25E8) = 0x100000;					// start in rec mode

	asm volatile (
"		LDR	R0, =0xFF8103CC \n"
"		MOV	R1, #0 \n"
"		LDR	R3, =0xFF810404 \n"
"loc_FF810360: \n"
"		CMP	R0, R3 \n"
"		LDRCC	R2, [R0],#4 \n"
"		STRCC	R2, [R1],#4 \n"
"		BCC	loc_FF810360 \n"
"		LDR	R0, =0xFF810404 \n"
"		MOV	R1, #0x4B0 \n"
"		LDR	R3, =0xFF810618 \n"
"loc_FF81037C: \n"
"		CMP	R0, R3 \n"
"		LDRCC	R2, [R0],#4 \n"
"		STRCC	R2, [R1],#4 \n"
"		BCC	loc_FF81037C \n"
"		MOV	R0, #0xD2 \n"
"		MSR	CPSR_cxsf, R0 \n"
"		MOV	SP, #0x1000 \n"
"		MOV	R0, #0xD3 \n"
"		MSR	CPSR_cxsf, R0 \n"
"		MOV	SP, #0x1000 \n"
"		LDR	R0, =0x6C4 \n"
"		LDR	R2, =0xEEEEEEEE \n"
"		MOV	R3, #0x1000 \n"
"loc_FF8103B0: \n"
"		CMP	R0, R3 \n"
"		STRCC	R2, [R0],#4 \n"
"		BCC	loc_FF8103B0 \n"

//"		BL	sub_FF811198 \n"
"		BL	sub_FF811198_my \n"				// patched

"loc_FF8103C0: \n"
"		ANDEQ	R0, R0,	R4,ASR#13 \n"
"loc_FF8103C4: \n"
"		ANDEQ	R0, R0,	R0,ROR R6 \n"
"loc_FF8103C8: \n"
"		ANDEQ	R0, R0,	R4,ROR R6 \n"
"loc_FF8103CC: \n"
"		NOP \n"
"		LDR	PC, =0xFF810618 \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF811198_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF811198_my()
{
	asm volatile (
"		STR	LR, [SP,#-4]! \n"
"		SUB	SP, SP,	#0x74 \n"
"		MOV	R0, SP \n"
"		MOV	R1, #0x74 \n"
"		BL	sub_FFB9F330 \n"
"		MOV	R0, #0x53000 \n"
"		STR	R0, [SP,#4] \n"

//"		LDR	R0, =0x16EE30 \n"
"		LDR	R0, =new_sa \n"					// patched
"		LDR R0, [R0] \n"

"		LDR	R1, =0x379C00 \n"
"		STR	R0, [SP,#8] \n"
"		RSB	R0, R0,	#0x1F80 \n"
"		ADD	R0, R0,	#0x370000 \n"
"		STR	R0, [SP,#0x0c] \n"
"		LDR	R0, =0x371F80 \n"
"		STR	R1, [SP,#0] \n"
"		STRD	R0, [SP,#0x10] \n"
"		MOV	R0, #0x22 \n"
"		STR	R0, [SP,#0x18] \n"
"		MOV	R0, #0x68 \n"
"		STR	R0, [SP,#0x1c] \n"
"		LDR	R0, =0x19B \n"

//"		LDR	R1, =sub_FF815EE0 \n"
"		LDR	R1, =sub_FF815EE0_my \n"		// patched

"		STR	R0, [SP,#0x20] \n"
"		MOV	R0, #0x96 \n"
"		STR	R0, [SP,#0x24] \n"
"		STR	R0, [SP,#0x28] \n"
"		MOV	R0, #0x64 \n"
"		STR	R0, [SP,#0x2c] \n"
"		MOV	R0, #0 \n"
"		STR	R0, [SP,#0x30] \n"
"		STR	R0, [SP,#0x34] \n"
"		MOV	R0, #0x10 \n"
"		STR	R0, [SP,#0x5c] \n"
"		MOV	R0, #0x800 \n"
"		STR	R0, [SP,#0x60] \n"
"		MOV	R0, #0xA0 \n"
"		STR	R0, [SP,#0x64] \n"
"		MOV	R0, #0x280 \n"
"		STR	R0, [SP,#0x68] \n"
"		MOV	R0, SP \n"
"		MOV	R2, #0 \n"
"		BL	sub_FF8134B8 \n"
"		ADD	SP, SP,	#0x74 \n"
"		LDR	PC, [SP],#4 \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF815EE0_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF815EE0_my()
{
	asm volatile (
"		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF810B20 \n"
"		BL	sub_FF81A33C \n"				// dmSetup
"		CMP	R0, #0 \n"
"		LDRLT	r0, =0xFF815FF4 \n"			// "dmSetup"
"		BLLT	sub_FF815FD4 \n"			// err_init_task
"		BL	sub_FF815B1C \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF815FFC \n"			// "termDriverInit"
"		BLLT	sub_FF815FD4 \n"			// err_init_task
"		LDR	R0, =0xFF81600C \n"				// "/_term"
"		BL	sub_FF815C04 \n"				// termDeviceCreate
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF816014 \n"			// "termDeviceCreate"
"		BLLT	sub_FF815FD4 \n"			// err_init_task
"		LDR	R0, =0xFF81600C \n"				// "/_term"
"		BL	sub_FF813CA4 \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF816028 \n"			// "stdioSetup"
"		BLLT	sub_FF815FD4 \n"			// err_init_task
"		BL	sub_FF819CC4 \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF816034 \n"			// "stdlibSetup"
"		BLLT	sub_FF815FD4 \n"			// err_init_task
"		BL	sub_FF81167C \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF816040 \n"			// "armlib_setup"
"		BLLT	sub_FF815FD4 \n"			// err_init_task
"		LDMFD	SP!, {R4,LR} \n"

//"		B	sub_FF81FB54 \n"				// taskcreate_Startup
"		B	taskcreate_Startup_my \n"		// patched

"		MOV	R0, #0 \n"
"		LDMFD	SP!, {R3-R5,PC} \n"
	);
}


/*----------------------------------------------------------------------
	taskcreate_Startup_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) taskcreate_Startup_my()
{
    asm volatile (
"		STMFD	SP!, {R3-R5,LR} \n"
"		BL	sub_FF8346CC \n"				// j_nullsub_60
"		BL	sub_FF83C6B0 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF81FBA8 \n"
"		BL	sub_FF8360B8 \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF81FBA8 \n"
"		LDR	R4, =0xC0220000 \n"
"		LDR	R0, [R4,#0x12C] \n"
"		TST	R0, #1 \n"
"		MOVEQ	R0, #0x12C \n"
"		BLEQ	sub_FF83AA4C \n"			// eventproc_export_SleepTask
"		BL	sub_FF8346C8 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF81FBA8 \n"
"		BL	sub_FF833D5C \n"
"		MOV	R0, #0x44 \n"
"		STR	R0, [R4,#0x1C] \n"
"		BL	sub_FF833F4C \n"
"loc_FF81FBA4: \n"
"		B	loc_FF81FBA4 \n"
"loc_FF81FBA8: \n"

// we must remove this for power-on mode handling in sub_FF810354_my to work
//"		BL	sub_FF8346D4 \n"

"		BL	sub_FF8346D0 \n"				// j_nullsub_61
"		BL	sub_FF83A8C4 \n"
"		LDR	R1, =0x3CE000 \n"
"		MOV	R0, #0 \n"
"		BL	sub_FF83AD0C \n"
"		BL	sub_FF83AAB8 \n"
"		MOV	R3, #0 \n"
"		STR	R3, [SP] \n"

//"		LDR	R3, =0xFF81FAF0 \n"				// task_Startup
"		LDR	R3, =task_Startup_my \n"		// patched

"		MOV	R2, #0 \n"
"		MOV	R1, #0x19 \n"
"		LDR	R0, =0xFF81FBF0 \n"				// "Startup"
"		BL	sub_FF81E8A0 \n"				// eventproc_export_CreateTask
"		MOV	R0, #0 \n"
"		LDMFD	SP!, {R3-R5,PC} \n"

	);
}


/*----------------------------------------------------------------------
	task_Startup_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) task_Startup_my()
{
   	asm volatile (
"		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF816594 \n"				// taskcreate_ClockSave
"		BL	sub_FF835830 \n"
"		BL	sub_FF8339B4 \n"
"		BL	sub_FF83C6F4 \n"				// j_nullsub_63
"		BL	sub_FF83C8E0 \n"

//"		BL	sub_FF83C788 \n"				// Skip starting diskboot.bin again

"		BL	sub_FF83CA88 \n"
"		BL	sub_FF832484 \n"
"		BL	sub_FF83C910 \n"
"		BL	sub_FF83A068 \n"
"		BL	sub_FF83CA8C \n"

//"		BL	sub_FF8345B0 \n"				// taskcreate_PhySw
	);

		CreateTask_PhySw();					// our keyboard task

		CreateTask_spytask();				// chdk initialization

    asm volatile (
"		BL	sub_FF837D14 \n"
"		BL	sub_FF83CAA4 \n"
"		BL	sub_FF831888 \n"				// nullsub_2
"		BL	sub_FF833318 \n"
"		BL	sub_FF83C478 \n"				// taskcreate_Bye
"		BL	sub_FF833968 \n"
"		BL	sub_FF8332B4 \n"
"		BL	sub_FF8324B8 \n"
"		BL	sub_FF83D670 \n"
"		BL	sub_FF833278 \n"
"		LDMFD	SP!, {R4,LR} \n"
"		B	sub_FF8166B4 \n"
	);
}


/*----------------------------------------------------------------------
	spytask
-----------------------------------------------------------------------*/
void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}


/*----------------------------------------------------------------------
	CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask()
{
	_CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}


/*----------------------------------------------------------------------
	CreateTask_PhySw
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) CreateTask_PhySw()
{
    asm volatile (
"		STMFD	SP!, {R3-R5,LR} \n"
"		LDR	R4, =0x1C30 \n"
"		LDR	R0, [R4,#0x10] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF8345E4 \n"
"		MOV	R3, #0 \n"
"		STR	R3, [SP] \n"

//"		ADR	R3, task_PhySw \n"
//"		LDR R3, =sub_FF83457C \n"
//"		MOV	R2, #0x800 \n"

"		LDR	R3, =mykbd_task \n"				// PhySw Task patch
"		MOV	R2, #0x2000 \n"					// larger stack

"		MOV	R1, #0x17 \n"
"		LDR	R0, =0xFF8347DC \n"				// "PhySw"
"		BL	sub_FF83AB0C \n"				// KernelCreateTask
"		STR	R0, [R4,#0x10] \n"
"loc_FF8345E4: \n"
"		BL	sub_FF865BC0 \n"
"		BL	sub_FF894834 \n"
"		BL	sub_FF836030 \n"
"		CMP	R0, #0 \n"
"		LDREQ	R1, =0x34CC0 \n"
"		LDMEQFD	SP!, {R3-R5,LR} \n"
"		BEQ	sub_FF8947BC \n"				// eventproc_export_OpLog.Start
"		LDMFD	SP!, {R3-R5,PC} \n"
	);
}


/*----------------------------------------------------------------------
	init_file_modules_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) init_file_modules_task()
{
	asm volatile (
"		STMFD	SP!, {R4-R6,LR} \n"
"		BL	sub_FF896CE0 \n"
"		LDR	R5, =0x5006 \n"
"		MOVS	R4, R0 \n"
"		MOVNE	R1, #0 \n"
"		MOVNE	R0, R5 \n"
"		BLNE	sub_FF89AAD4 \n"			// eventproc_export_PostLogicalEventToUI

//"		BL	sub_FF896D0C \n"
"		BL	sub_FF896D0C_my \n"				// patched

"		BL      core_spytask_can_start\n"	// added

"		CMP	R4, #0 \n"
"		MOVEQ	R0, R5 \n"
"		LDMEQFD	SP!, {R4-R6,LR} \n"
"		MOVEQ	R1, #0 \n"
"		BEQ		sub_FF89AAD4 \n"			// eventproc_export_PostLogicalEventToUI
"		LDMFD	SP!, {R4-R6,PC} \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF896D0C_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF896D0C_my()
{
	asm volatile (
"		STMFD	SP!, {R4,LR} \n"
"		MOV	R0, #3 \n"

//"		BL	sub_FF876598 \n"
"		BL	sub_FF876598_my \n"				// patched

"		BL	sub_FF96A8E8 \n"				// nullsub_94
"		LDR	R4, =0x3244 \n"
"		LDR	R0, [R4,#4] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF896D44 \n"
"		BL	sub_FF8757DC \n"
"		BL	sub_FF95D878 \n"
"		BL	sub_FF8757DC \n"
"		BL	sub_FF871B80 \n"
"		BL	sub_FF8756DC \n"
"		BL	sub_FF95D914 \n"
"loc_FF896D44: \n"
"		MOV	R0, #1 \n"
"		STR	R0, [R4] \n"
"		LDMFD	SP!, {R4,PC} \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF876598_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF876598_my()
{
	asm volatile (
"		STMFD	SP!, {R4-R8,LR} \n"
"		MOV	R8, R0 \n"
"		BL	sub_FF876518 \n"
"		LDR	R1, =0x3B0A8 \n"
"		MOV	R6, R0 \n"
"		ADD	R4, R1,	R0,LSL#7 \n"
"		LDR	R0, [R4,#0x6C] \n"
"		CMP	R0, #4 \n"
"		LDREQ	R1, =0x83F \n"
"		LDREQ	R0, =0xFF876058 \n"
"		BLEQ	sub_FF81EB78 \n"			// DebugAssert
"		MOV	R1, R8 \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF875DCC \n"
"		LDR	R0, [R4,#0x38] \n"
"		BL	sub_FF876C3C \n"
"		CMP	R0, #0 \n"
"		STREQ	R0, [R4,#0x6C] \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF875E5C \n"
"		MOV	R0, R6 \n"

//"		BL	sub_FF8761C0 \n"
"		BL	sub_FF8761C0_my \n"				// patched

"		MOV	R5, R0 \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF8763F0 \n"
"		LDR	R6, [R4,#0x3C] \n"
"		AND	R7, R5,	R0 \n"
"		CMP	R6, #0 \n"
"		LDR	R1, [R4,#0x38] \n"
"		MOVEQ	R0, #0x80000001 \n"
"		MOV	R5, #0 \n"
"		BEQ	loc_FF876648 \n"
"		MOV	R0, R1 \n"
"		BL	sub_FF875944 \n"
"		CMP	R0, #0 \n"
"		MOVNE	R5, #4 \n"
"		CMP	R6, #5 \n"
"		ORRNE	R0, R5,	#1 \n"
"		BICEQ	R0, R5,	#1 \n"
"		CMP	R7, #0 \n"
"		BICEQ	R0, R0,	#2 \n"
"		ORREQ	R0, R0,	#0x80000000 \n"
"		BICNE	R0, R0,	#0x80000000 \n"
"		ORRNE	R0, R0,	#2 \n"

"loc_FF876648: \n"
"		CMP	R8, #7 \n"
"		STR	R0, [R4,#0x40] \n"
"		LDMNEFD	SP!, {R4-R8,PC} \n"
"		MOV	R0, R8 \n"
"		BL	sub_FF876568 \n"
"		CMP	R0, #0 \n"
"		LDMEQFD	SP!, {R4-R8,LR} \n"
"		LDREQ	R0, =0xFF876694 \n"		// "EMEM MOUNT ERROR"
"		BEQ		sub_FF81177C \n"		// qPrintf
"		LDMFD	SP!, {R4-R8,PC} \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF8761C0_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF8761C0_my()
{
	asm volatile (
"		STMFD	SP!, {R4-R6,LR} \n"
"		MOV	R5, R0 \n"
"		LDR	R0, =0x3B0A8 \n"
"		ADD	R4, R0,	R5,LSL#7 \n"
"		LDR	R0, [R4,#0x6C] \n"
"		TST	R0, #2 \n"
"		MOVNE	R0, #1 \n"
"		LDMNEFD	SP!, {R4-R6,PC} \n"
"		LDR	R0, [R4,#0x38] \n"
"		MOV	R1, R5 \n"

//"		BL	sub_FF875EE0 \n"
"		BL	sub_FF875EE0_my \n"					// patched

"		CMP	R0, #0 \n"
"		LDRNE	R0, [R4,#0x38] \n"
"		MOVNE	R1, R5 \n"
"		BLNE	sub_FF87607C \n"
"		LDR	R2, =0x3B128 \n"
"		ADD	R1, R5,	R5,LSL#4 \n"
"		LDR	R1, [R2,R1,LSL#2] \n"
"		CMP	R1, #4 \n"
"		BEQ	loc_FF876220 \n"
"		CMP	R0, #0 \n"
"		LDMEQFD	SP!, {R4-R6,PC} \n"
"		MOV	R0, R5 \n"
"		BL	sub_FF8759D4 \n"
"loc_FF876220: \n"
"		CMP	R0, #0 \n"
"		LDRNE	R1, [R4,#0x6C] \n"
"		ORRNE	R1, R1,	#2 \n"
"		STRNE	R1, [R4,#0x6C] \n"
"		LDMFD	SP!, {R4-R6,PC} \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF875EE0_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF875EE0_my()
{
	asm volatile (
"		STMFD	SP!, {R4-R10,LR} \n"
"		MOV	R9, R0 \n"
"		LDR	R0, =0x3B0A8 \n"
"		MOV	R8, #0 \n"
"		ADD	R5, R0,	R1,LSL#7 \n"
"		LDR	R0, [R5,#0x3C] \n"
"		MOV	R7, #0 \n"
"		CMP	R0, #7 \n"
"		MOV	R6, #0 \n"
"		ADDLS	PC, PC,	R0,LSL#2 \n"
"		B	loc_FF876038 \n"
"loc_FF875F0C: \n"
"		B	loc_FF875F44 \n"
"loc_FF875F10: \n"
"		B	loc_FF875F2C \n"
"loc_FF875F14: \n"
"		B	loc_FF875F2C \n"
"loc_FF875F18: \n"
"		B	loc_FF875F2C \n"
"loc_FF875F1C: \n"
"		B	loc_FF875F2C \n"
"loc_FF875F20: \n"
"		B	loc_FF876030 \n"
"loc_FF875F24: \n"
"		B	loc_FF875F2C \n"
"loc_FF875F28: \n"
"		B	loc_FF875F2C \n"
"loc_FF875F2C: \n"
// jumptable FF875F04 entries 1-4,6,7
"		MOV	R2, #0 \n"
"		MOV	R1, #0x200 \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF890D90 \n"
"		MOVS	R4, R0 \n"
"		BNE	loc_FF875F4C \n"
"loc_FF875F44: \n"
// jumptable FF875F04 entry 0
"		MOV	R0, #0 \n"
"		LDMFD	SP!, {R4-R10,PC} \n"
"loc_FF875F4C: \n"
"		LDR	R12, [R5,#0x50] \n"
"		MOV	R3, R4 \n"
"		MOV	R2, #1 \n"
"		MOV	R1, #0 \n"
"		MOV	R0, R9 \n"
"		BLX	R12 \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF875F78 \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF890EE0 \n"
"		B	loc_FF875F44 \n"
"loc_FF875F78: \n"
"		LDR	R1, [R5,#0x64] \n"
"		MOV	R0, R9 \n"
"		BLX	R1 \n"

//------------------  begin added code ---------------
		"MOV   R1, R4\n"           //  pointer to MBR in R1
		"BL    mbr_read_dryos\n"   //  total sectors count in R0 before and after call

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
//------------------  end added code ---------------

"		LDRB	R1, [R4,#0x1C9] \n"
"		LDRB	R3, [R4,#0x1C8] \n"
"		LDRB	R12, [R4,#0x1CC] \n"
"		MOV	R1, R1,LSL#24 \n"
"		ORR	R1, R1,	R3,LSL#16 \n"
"		LDRB	R3, [R4,#0x1C7] \n"
"		LDRB	R2, [R4,#0x1BE] \n"

//"		LDRB	LR, [R4,#0x1FF] \n"				// replaced, see below

"		ORR	R1, R1,	R3,LSL#8 \n"
"		LDRB	R3, [R4,#0x1C6] \n"
"		CMP	R2, #0 \n"
"		CMPNE	R2, #0x80 \n"
"		ORR	R1, R1,	R3 \n"
"		LDRB	R3, [R4,#0x1CD] \n"
"		MOV	R3, R3,LSL#24 \n"
"		ORR	R3, R3,	R12,LSL#16 \n"
"		LDRB	R12, [R4,#0x1CB] \n"
"		ORR	R3, R3,	R12,LSL#8 \n"
"		LDRB	R12, [R4,#0x1CA] \n"
"		ORR	R3, R3,	R12 \n"

//"		LDRB	R12, [R4,#0x1FE] \n"
		"LDRB    R12, [LR,#0x1FE]\n"        // New! First MBR signature byte (0x55)
        "LDRB    LR, [LR,#0x1FF]\n"         //      Last MBR signature byte (0xAA)

"		BNE	loc_FF876004 \n"
"		CMP	R0, R1 \n"
"		BCC	loc_FF876004 \n"
"		ADD	R2, R1,	R3 \n"
"		CMP	R2, R0 \n"
"		CMPLS	R12, #0x55 \n"
"		CMPEQ	LR, #0xAA \n"
"		MOVEQ	R7, R1 \n"
"		MOVEQ	R6, R3 \n"
"		MOVEQ	R4, #1 \n"
"		BEQ	loc_FF876008 \n"
"loc_FF876004: \n"
"		MOV	R4, R8 \n"
"loc_FF876008: \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF890EE0 \n"
"		CMP	R4, #0 \n"
"		BNE	loc_FF876044 \n"
"		LDR	R1, [R5,#0x64] \n"
"		MOV	R7, #0 \n"
"		MOV	R0, R9 \n"
"		BLX	R1 \n"
"		MOV	R6, R0 \n"
"		B	loc_FF876044 \n"
"loc_FF876030: \n"
// jumptable FF875F04 entry 5
"		MOV	R6, #0x40 \n"
"		B	loc_FF876044 \n"
"loc_FF876038: \n"
// jumptable FF875F04 default entry
"		LDR	R1, =0x597 \n"
"		LDR	R0, =0xFF876058 \n"			// "Mounter.c"
"		BL	sub_FF81EB78 \n"			// DebugAssert
"loc_FF876044: \n"
"		STR	R7, [R5,#0x44]! \n"
"		STMIB	R5, {R6,R8} \n"
"		MOV	R0, #1 \n"
"		LDMFD	SP!, {R4-R10,PC} \n"
	);
}


/*----------------------------------------------------------------------
	JogDial_task_my()

	Patched jog dial task
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) JogDial_task_my()
{
	asm volatile (
"		STMFD	SP!, {R4-R11,LR} \n"
"		SUB	SP, SP,	#0x24 \n"
"		BL	sub_FF865C2C \n"
"		LDR	R1, =0x25FC \n"
"		LDR	R6, =0xFFBA5474 \n"
"		MOV	R0, #0 \n"
"		ADD	R3, SP,	#0x18 \n"
"		ADD	R12, SP, #0x1c \n"
"		ADD	R10, SP, #0x08 \n"
"		MOV	R2, #0 \n"
"		ADD	R9, SP,	#0x10 \n"

"loc_FF8658C0: \n"
"		ADD	R12, SP, #0x1c \n"
"		ADD	LR, R12, R0,LSL#1 \n"
"		MOV	R2, #0 \n"
"		ADD	R3, SP,	#0x18 \n"
"		STRH	R2, [LR] \n"
"		ADD	LR, R3,	R0,LSL#1 \n"
"		STRH	R2, [LR] \n"
"		STR	R2, [R9,R0,LSL#2] \n"
"		STR	R2, [R10,R0,LSL#2] \n"
"		ADD	R0, R0,	#1 \n"
"		CMP	R0, #2 \n"
"		BLT	loc_FF8658C0 \n"

"loc_FF8658F0: \n"
"		LDR	R0, =0x25FC \n"
"		MOV	R2, #0 \n"
"		LDR	R0, [R0,#8] \n"
"		MOV	R1, SP \n"
"		BL	sub_FF83A2F8 \n"
"		CMP	R0, #0 \n"
"		LDRNE	R1, =0x262 \n"
"		LDRNE	R0, =0xFF865B50 \n"			// "RotaryEncoder.c"
"		BLNE	sub_FF81EB78 \n"			// DebugAssert

//------------------  begin added code ---------------
"labelA:\n"
		"LDR     R0, =jogdial_stopped\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #1\n"
		"BNE     labelB\n"					// continue on if jogdial_stopped = 0
		"MOV     R0, #40\n"
		"BL      _SleepTask\n"				// jogdial_stopped=1 -- give time back to OS and suspend jogdial task
		"B       labelA\n"
"labelB:\n"
//------------------  end added code -----------------

"		LDR	R0, [SP] \n"
"		AND	R4, R0,	#0xFF \n"
"		AND	R0, R0,	#0xFF00 \n"
"		CMP	R0, #0x100 \n"
"		BEQ	loc_FF865960 \n"
"		CMP	R0, #0x200 \n"
"		BEQ	loc_FF865998 \n"
"		CMP	R0, #0x300 \n"
"		BEQ	loc_FF865B90 \n"
"		CMP	R0, #0x400 \n"
"		BNE	loc_FF8658F0 \n"
"		CMP	R4, #0 \n"
"		LDRNE	R1, =0x2ED \n"
"		LDRNE	R0, =0xFF865B50 \n"			// "RotaryEncoder.c"
"		BLNE	sub_FF81EB78 \n"			// DebugAssert
"		RSB	R0, R4,	R4,LSL#3 \n"
"		LDR	R0, [R6,R0,LSL#2] \n"

"loc_FF865958: \n"
"		BL	sub_FF865C10 \n"
"		B	loc_FF8658F0 \n"

"loc_FF865960: \n"
"		LDR	R7, =0x260C \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83B290 \n"
"		LDR	R2, =0xFF8657E0 \n"
"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x200 \n"
"		MOV	R0, #0x28 \n"
"		BL	sub_FF83B1AC \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R10,R4,LSL#2] \n"
"		BEQ	loc_FF8658F0 \n"
"		MOV	R1, #0x274 \n"
"		B	loc_FF865B3C \n"

"loc_FF865998: \n"
"		RSB	R5, R4,	R4,LSL#3 \n"
"		LDR	R0, [R6,R5,LSL#2] \n"
"		LDR	R1, =0xC0240104 \n"
"		LDR	R0, [R1,R0,LSL#8] \n"
"		MOV	R2, R0,ASR#16 \n"
"		ADD	R0, SP,	#0x1c \n"
"		ADD	R0, R0,	R4,LSL#1 \n"
"		STR	R0, [SP,#0x20] \n"
"		STRH	R2, [R0] \n"
"		ADD	R0, SP,	#0x18 \n"
"		ADD	R11, R0, R4,LSL#1 \n"
"		LDRSH	R3, [R11] \n"
"		SUB	R0, R2,	R3 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF865A18 \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF865AF8 \n"
"		LDR	R7, =0x260C \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83B290 \n"
"		LDR	R2, =0xFF8657EC \n"
"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x300 \n"
"		MOV	R0, #0x1F4 \n"
"		BL	sub_FF83B1AC \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R7,R4,LSL#2] \n"
"		BEQ	loc_FF865AF8 \n"
"		LDR	R1, =0x28D \n"
"		B	loc_FF865AF0 \n"

"loc_FF865A18: \n"
"		MOV	R1, R0 \n"
"		RSBLT	R0, R0,	#0 \n"
"		MOVLE	R7, #0 \n"
"		MOVGT	R7, #1 \n"
"		CMP	R0, #0xFF \n"
"		BLS	loc_FF865A58 \n"
"		CMP	R1, #0 \n"
"		RSBLE	R0, R3,	#0xFF \n"
"		ADDLE	R0, R0,	#0x7F00 \n"
"		ADDLE	R0, R0,	R2 \n"
"		RSBGT	R0, R2,	#0xFF \n"
"		ADDGT	R0, R0,	#0x7F00 \n"
"		ADDGT	R0, R0,	R3 \n"
"		ADD	R0, R0,	#0x8000 \n"
"		ADD	R0, R0,	#1 \n"
"		EOR	R7, R7,	#1 \n"

"loc_FF865A58: \n"
"		STR	R0, [SP,#0x04] \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		ADDEQ	R0, R6,	R5,LSL#2 \n"
"		LDREQ	R0, [R0,#8] \n"
"		BEQ	loc_FF865A90 \n"
"		ADD	R8, R6,	R5,LSL#2 \n"
"		ADD	R1, R8,	R7,LSL#2 \n"
"		LDR	R1, [R1,#0x10] \n"
"		CMP	R1, R0 \n"
"		BEQ	loc_FF865A94 \n"
"		LDR	R0, [R8,#0xC] \n"
"		BL	sub_FF89CCA4 \n"
"		LDR	R0, [R8,#8] \n"

"loc_FF865A90: \n"
"		BL	sub_FF89CCA4 \n"

"loc_FF865A94: \n"
"		ADD	R0, R6,	R5,LSL#2 \n"
"		ADD	R7, R0,	R7,LSL#2 \n"
"		LDR	R0, [R7,#0x10] \n"
"		LDR	R1, [SP,#0x04] \n"
"		BL	sub_FF89CBCC \n"
"		LDR	R0, [R7,#0x10] \n"
"		LDR	R7, =0x260C \n"
"		STR	R0, [R9,R4,LSL#2] \n"
"		LDR	R0, [SP,#0x20] \n"
"		LDRH	R0, [R0] \n"
"		STRH	R0, [R11] \n"
"		LDR	R0, [R7,R4,LSL#2] \n"
"		BL	sub_FF83B290 \n"
"		LDR	R2, =0xFF8657EC \n"
"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x300 \n"
"		MOV	R0, #0x1F4 \n"
"		BL	sub_FF83B1AC \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R7,R4,LSL#2] \n"
"		BEQ	loc_FF865AF8 \n"
"		LDR	R1, =0x2CF \n"

"loc_FF865AF0: \n"
"		LDR	R0, =0xFF865B50 \n"			// "RotaryEncoder.c"
"		BL	sub_FF81EB78 \n"			// DebugAssert

"loc_FF865AF8: \n"
"		ADD	R0, R6,	R5,LSL#2 \n"
"		LDR	R0, [R0,#0x18] \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF865B88 \n"
"		LDR	R0, =0x25FC \n"
"		LDR	R0, [R0,#0xC] \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF865B88 \n"
"		LDR	R2, =0xFF8657E0 \n"
"		ADD	R1, R2,	#0 \n"
"		ORR	R3, R4,	#0x400 \n"
"		BL	sub_FF83B1AC \n"
"		TST	R0, #1 \n"
"		CMPNE	R0, #0x15 \n"
"		STR	R0, [R10,R4,LSL#2] \n"
"		BEQ	loc_FF8658F0 \n"
"		LDR	R1, =0x2D6 \n"

"loc_FF865B3C: \n"
"		LDR	R0, =0xFF865B50 \n"			// "RotaryEncoder.c"
"		BL	sub_FF81EB78 \n"			// DebugAssert
"		B	loc_FF8658F0 \n"

		"NOP \n"

"loc_FF865B88: \n"
"		LDR	R0, [R6,R5,LSL#2] \n"
"		B	loc_FF865958 \n"

"loc_FF865B90: \n"
"		LDR	R0, [R9,R4,LSL#2] \n"
"		CMP	R0, #0 \n"
"		MOVEQ	R1, #0x2E0 \n"
"		LDREQ	R0, =0xFF865B50 \n"			// "RotaryEncoder.c"
"		BLEQ	sub_FF81EB78 \n"			// DebugAssert
"		RSB	R0, R4,	R4,LSL#3 \n"
"		ADD	R0, R6,	R0,LSL#2 \n"
"		LDR	R0, [R0,#0xC] \n"
"		BL	sub_FF89CCA4 \n"
"		MOV	R2, #0 \n"
"		STR	R2, [R9,R4,LSL#2] \n"
"		B	loc_FF8658F0 \n"
	);
};
