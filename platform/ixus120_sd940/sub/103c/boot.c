#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
void CreateTask_spytask();
void boot();
void capt_seq_task();

#define LED_GREEN  0xC0220130 
#define LED_ORANGE 0xC0220134
#define LED_AF     0xC0223030 


void taskCreateHook(int *p) {
 p-=17;

//	if(p[0]==0xFF8331C4) p[0]=(int)mykbd_task;   			//done
	if(p[0]==0xFF88E57C) p[0]=(int)init_file_modules_task;	//done 
	if(p[0]==0xFF872FE0) p[0]=(int)capt_seq_task;  			//done
	if(p[0]==0xFF8B2FD0) p[0]=(int)exp_drv_task;			//done
	if(p[0]==0xFF93D810) p[0]=(int)movie_record_task;		//done
}

void taskCreateHook2(int *p) {	
	p-=17;
	
	if(p[0]==0xFF88E57C) p[0]=(int)init_file_modules_task;  	//done
	if(p[0]==0xFF8B2FD0) p[0]=(int)exp_drv_task;				//done
	if(p[0]==0xFF93D810) p[0]=(int)movie_record_task;			//done
}

void CreateTask_spytask() {

         _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

};

/*-------------------------------------------------------
	Memory Map:
		1900		MEMBASEADDR				start of data	used for initialized vars
		df03								end of data
		df04								start of bss - used for zeroed/uninited vars
		13ca17								end of bss
		13ca18		MEMISOSTART				start of our data / bss
		174000		MEMISOSTART+MEMIOSIZE	end of our data/bss (approx)
		???									end of memory

		400000								video buffers ??

		ff810000	ROMBASEADDR				start of rom
		ffffffff							end of rom

-------------------------------------------------------*/

/*----------------------------------------------------------------------
	boot()
-----------------------------------------------------------------------*/

void __attribute__((naked,noinline)) boot() {
	*((volatile int *) LED_AF) = 0x46;
    asm volatile (
"		LDR	R1, =0xC0410000 \n"
"		MOV	R0, #0 \n"
"		STR	R0, [R1] \n"
"		MOV	R1, #0x78 \n"
"		MCR	p15, 0,	R1,c1,c0 \n"
"		MOV	R1, #0 \n"
"		MCR	p15, 0,	R1,c7,c10, 4 \n"
"		MCR	p15, 0,	R1,c7,c5 \n"
"		MCR	p15, 0,	R1,c7,c6 \n"
"		MOV	R0, #0x3D \n"
"		MCR	p15, 0,	R0,c6,c0 \n"
"		MOV	R0, #0xC000002F \n"
"		MCR	p15, 0,	R0,c6,c1 \n"
"		MOV	R0, #0x33 \n"
"		MCR	p15, 0,	R0,c6,c2 \n"
"		MOV	R0, #0x40000033 \n"
"		MCR	p15, 0,	R0,c6,c3 \n"
"		MOV	R0, #0x80000017 \n"
"		MCR	p15, 0,	R0,c6,c4 \n"
"		LDR	R0, =0xFF80002D \n"
"		MCR	p15, 0,	R0,c6,c5 \n"
"		MOV	R0, #0x34 \n"
"		MCR	p15, 0,	R0,c2,c0 \n"
"		MOV	R0, #0x34 \n"
"		MCR	p15, 0,	R0,c2,c0, 1 \n"
"		MOV	R0, #0x34 \n"
"		MCR	p15, 0,	R0,c3,c0 \n"
"		LDR	R0, =0x3333330 \n"
"		MCR	p15, 0,	R0,c5,c0, 2 \n"
"		LDR	R0, =0x3333330 \n"
"		MCR	p15, 0,	R0,c5,c0, 3 \n"
"		MRC	p15, 0,	R0,c1,c0 \n"
"		ORR	R0, R0,	#0x1000 \n"
"		ORR	R0, R0,	#4 \n"
"		ORR	R0, R0,	#1 \n"
"		MCR	p15, 0,	R0,c1,c0 \n"
"		MOV	R1, #0x80000006 \n"
"		MCR	p15, 0,	R1,c9,c1 \n"
"		MOV	R1, #6 \n"
"		MCR	p15, 0,	R1,c9,c1, 1 \n"
"		MRC	p15, 0,	R1,c1,c0 \n"
"		ORR	R1, R1,	#0x50000 \n"
"		MCR	p15, 0,	R1,c1,c0 \n"
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
"		LDR	R0, =0xFFBBECD0 \n"
"		LDR	R1, =0x1900 \n"
"		LDR	R3, =0xDF04 \n"
"loc_FF81013C: \n" 
"		CMP	R1, R3 \n"
"		LDRCC	R2, [R0],#4 \n"
"		STRCC	R2, [R1],#4 \n"
"		BCC	loc_FF81013C \n"
"		LDR	R1, =0x13CA18 \n"
"		MOV	R2, #0 \n"
"loc_FF810154: \n" 
"		CMP	R3, R1 \n"
"		STRCC	R2, [R3],#4 \n"
"		BCC	loc_FF810154 \n"
"		B  sub_FF810354_my \n"   
    );
};

void __attribute__((naked,noinline)) sub_FF810354_my() {

   *(int*)0x1938=(int)taskCreateHook;
   *(int*)0x1940=(int)taskCreateHook2;  

	// @FF8586DC
	if ((*(int*) 0xC0220128) & 1)					// look at play switch
		*(int*)(0x22FC) = 0x400000;					// start in play mode
	else
		*(int*)(0x22FC) = 0x200000;					// start in rec mode

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
"		LDR	R0, =0x6C4 \n"        // loc_FF8103C0
"		LDR	R2, =0xEEEEEEEE \n"
"		MOV	R3, #0x1000 \n"
"loc_FF8103B0: \n" 
"		CMP	R0, R3 \n"
"		STRCC	R2, [R0],#4 \n"
"		BCC	loc_FF8103B0 \n"
"		BL	sub_FF811178_my \n"
     );
}

/*----------------------------------------------------------------------
	sub_FF811178_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF811178_my() {
     asm volatile (
"	 	STR	LR, [SP,#0xFFFFFFFC]! \n"
"		SUB	SP, SP,	#0x74 \n"
"		MOV	R0, SP \n"
"		MOV	R1, #0x74 \n"
"		BL	sub_FFB07C00 \n"
"		MOV	R0, #0x53000 \n"
"		STR	R0, [SP,#0x04] \n"

//"		LDR	R0, =0x13CA18 \n"
"		LDR     R0, =new_sa\n"					/// patched
"		LDR     R0, [R0]\n"

"		LDR	R2, =0x2F9C00 \n"
"		LDR	R1, =0x2F24A8 \n"
"		STR	R0, [SP,#0x08] \n"
"		SUB	R0, R1,	R0 \n"
"		ADD	R3, SP,	#0x0C \n"
"		STR	R2, [SP,#0x00] \n"
"		STMIA	R3, {R0-R2} \n"
"		MOV	R0, #0x22 \n"
"		STR	R0, [SP,#0x18] \n"
"		MOV	R0, #0x68 \n"
"		STR	R0, [SP,#0x1C] \n"
"		LDR	R0, =0x19B \n"

//"		LDR	R1, =0xFF815E34 \n"
"		LDR	R1, =sub_FF815E34_my \n"

"		STR	R0, [SP,#0x20] \n"
"		MOV	R0, #0x96 \n"
"		STR	R0, [SP,#0x24] \n"
"		MOV	R0, #0x78 \n"
"		STR	R0, [SP,#0x28] \n"
"		MOV	R0, #0x64 \n"
"		STR	R0, [SP,#0x2C] \n"
"		MOV	R0, #0 \n"
"		STR	R0, [SP,#0x30] \n"
"		STR	R0, [SP,#0x34] \n"
"		MOV	R0, #0x10 \n"
"		STR	R0, [SP,#0x5C] \n"
"		MOV	R0, #0x800 \n"
"		STR	R0, [SP,#0x60] \n"
"		MOV	R0, #0xA0 \n"
"		STR	R0, [SP,#0x64] \n"
"		MOV	R0, #0x280 \n"
"		STR	R0, [SP,#0x68] \n"
"		MOV	R0, SP \n"
"		MOV	R2, #0 \n"
"		BL	sub_FF8133E4 \n"
"		ADD	SP, SP,	#0x74 \n"
"		LDR	PC, [SP],#4 \n"
     );
}

/*----------------------------------------------------------------------
	sub_FF815E34_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF815E34_my() {	
   asm volatile (
"		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF810B08 \n"
"		BL	sub_FF81A148 \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF815F48 \n"
"		BLLT	sub_FF815F28 \n"
"		BL		sub_FF815A70 \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF815F50 \n"
"		BLLT	sub_FF815F28 \n"
"		LDR	R0, =0xFF815F60 \n"
"		BL		sub_FF815B58 \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF815F68 \n"
"		BLLT	sub_FF815F28 \n"
"		LDR	R0, =0xFF815F60 \n"
"		BL		sub_FF813BE0 \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF815F7C \n"
"		BLLT	sub_FF815F28 \n"
"		BL		sub_FF819B5C \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF815F88 \n"
"		BLLT	sub_FF815F28 \n"
"		BL		sub_FF81165C \n"
"		CMP	R0, #0 \n"
"		LDRLT	R0, =0xFF815F94 \n"
"		BLLT	sub_FF815F28 \n"
"		LDMFD	SP!, {R4,LR} \n"

//"		B	sub_FF81F868 \n"
"       B	taskcreate_Startup_my\n"				/// patched

    );
};

/*----------------------------------------------------------------------
	taskcreate_Startup_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
     asm volatile (
"	 	STMFD	SP!, {R3,LR} \n"   //>>
"		BL	sub_FF8332FC \n"
"		BL	sub_FF83A0E4 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF81F8A0 \n"
"		BL	sub_FF8332F8 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF81F8A0 \n"
"		BL	sub_FF8329A4 \n"
"		LDR	R1, =0xC0220000 \n"    //>>
"		MOV	R0, #0x44 \n"
"		STR	R0, [R1,#0x1C] \n"
"		BL	sub_FF832B94 \n"
"loc_FF81F89C: \n" 
"		B	loc_FF81F89C \n"

"loc_FF81F8A0: \n" 
//"		BL	sub_FF833304 \n"  //**** removed for correct power-on on 'on/off' button

"		BL	sub_FF833300 \n"
"		BL	sub_FF838394 \n"
"		LDR	R1, =0x34E000 \n"
"		MOV	R0, #0 \n"
"		BL	sub_FF8387DC \n"
"		BL	sub_FF838588 \n"
"		MOV	R3, #0 \n"
"		STR	R3, [SP,#0x00] \n"

//"		LDR	R3, =0xFF81F804 \n"
"       LDR     R3, =task_Startup_my\n"		// patched

"		MOV	R2, #0 \n"
"		MOV	R1, #0x19 \n"
"		LDR	R0, =0xFF81F8E8 \n"			//"Startup" ??????
"		BL	sub_FF81E5B4 \n"
"		MOV	R0, #0 \n"
"		LDMFD	SP!, {R12,PC} \n"      	//>>
     );
}

/*----------------------------------------------------------------------
	task_Startup_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (
" 		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF816490 \n"
"		BL	sub_FF8343EC \n"
"		BL	sub_FF832660 \n"
"		BL	sub_FF83A124 \n"
"		BL	sub_FF83A308 \n"

//"		BL	sub_FF83A1B8 \n"     		// Skip starting diskboot.bin again

"       BL  CreateTask_spytask\n"		// added

"		BL	sub_FF83A4A8 \n"
"		BL	sub_FF83135C \n"
"		BL	sub_FF83A338 \n"
"		BL	sub_FF837B38 \n"
"		BL	sub_FF83A4AC \n"

//"		BL	sub_FF8331F8 \n"    		// taskcreate_PhySw
"       BL  taskcreatePhySw_my\n"       // we do this here rather than hook so we don't waste the original stack


"		BL	sub_FF835FB4 \n"    		// captseqtask
"		BL	sub_FF83A4C4 \n"
"		BL	sub_FF830694_my \n"
"		BL	sub_FF831FB8 \n"
"		BL	sub_FF839EC0 \n"
"		BL	sub_FF832614 \n"
"		BL	sub_FF831EC4 \n"
"		BL	sub_FF831390 \n"
"		BL	sub_FF83AF44 \n"
"		BL	sub_FF831E9C \n"
"		LDMFD	SP!, {R4,LR} \n"
"		B	sub_FF8165B0 \n"
     );
}

void __attribute__((naked,noinline)) sub_FF830694_my() {  // loop hack that allows startup with battery door open
  asm volatile (
"		STMFD   SP!, {R4-R6,LR} \n"
"		LDR     R0, =0x400000 \n"
"loop1: \n"
"		nop\n"
"       SUBS   R0,R0,#1 \n"
"		BNE    loop1 \n"
"       LDMFD   SP!, {R4-R6,PC} \n"
		);
}


/*----------------------------------------------------------------------
	taskcreatePhySw_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) taskcreatePhySw_my() {
	asm volatile (
"		STMFD	SP!, {R3-R5,LR}\n"
"		LDR	R4, =0x1C38\n"
"		LDR	R0, [R4,#0x10]\n"
"		CMP	R0, #0\n"					// don't install physw task if *1c38 != 0
"		BNE	loc_FF83322C\n"
"		MOV	R3, #0\n"
"		STR	R3, [SP]\n"
//"		LDR	R3, task_PhySw\n"
"		LDR	R3, =mykbd_task\n"
//"		MOV	R2, #0x800\n"
"		MOV	R2, #0x2000\n"  			// larger stack
"		MOV	R1, #0x17\n"
"		LDR	R0, =0xFF833400\n"
"		BL	sub_FF8385DC\n"
"		STR	R0, [R4,#0x10]\n"
"loc_FF83322C:\n"
"		BL	sub_FF882E58\n"
"		BL	sub_FF85C53C\n"
"		CMP	R0, #0\n"
"		LDREQ	R1, =0x31B84\n"
"		LDMEQFD	SP!, {R3-R5,LR}\n"
"		BEQ	sub_FF882DE0\n"
"		LDMFD	SP!, {R3-R5,PC}\n"
	);
}


/*----------------------------------------------------------------------
	init_file_modules_task()
-----------------------------------------------------------------------*/

void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
" 		STMFD	SP!, {R4-R6,LR} \n"
"		BL	sub_FF885224 \n"
"		LDR	R5, =0x5006 \n"
"		MOVS	R4, R0 \n"
"		MOVNE	R1, #0 \n"
"		MOVNE	R0, R5 \n"
"		BLNE	sub_FF88A340 \n"

//"		BL	sub_FF885250 \n"
"		BL	sub_FF885250_my \n"		//-------->

"		BL	core_spytask_can_start\n"		//-------->

"		CMP	R4, #0 \n"
"		MOVEQ	R0, R5 \n"
"		LDMEQFD	SP!, {R4-R6,LR} \n"
"		MOVEQ	R1, #0 \n"
"		BEQ	sub_FF88A340 \n"
"		LDMFD	SP!, {R4-R6,PC} \n"
 );
}

/*----------------------------------------------------------------------
	sub_FF885250_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF885250_my() {
 asm volatile(
" 		STMFD	SP!, {R4,LR} \n"
"		MOV	R0, #3 \n"

//"		BL	sub_FF8683A0 \n"
"		BL	sub_FF8683A0_my \n"	//-------->

"		BL	sub_FF92416C \n"
"		LDR	R4, =0x2D3C \n"
"		LDR	R0, [R4,#4] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF885288 \n"
"		BL	sub_FF8676AC \n"
"		BL	sub_FF918258 \n"
"		BL	sub_FF8676AC \n"
"		BL	sub_FF8639D8 \n"
"		BL	sub_FF8675AC \n"
"		BL	sub_FF918320 \n"
"loc_FF885288: \n"
"		MOV	R0, #1 \n"
"		STR	R0, [R4] \n"
"		LDMFD	SP!, {R4,PC} \n"
 );
}


/*----------------------------------------------------------------------
	sub_FF8683A0_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF8683A0_my() {
 asm volatile(
"		STMFD	SP!, {R4-R8,LR} \n"
"		MOV	R8, R0 \n"
"		BL	sub_FF868320 \n"
"		LDR	R1, =0x366A0 \n"
"		MOV	R6, R0 \n"
"		ADD	R4, R1,	R0,LSL#7 \n"
"		LDR	R0, [R4,#0x6C] \n"
"		CMP	R0, #4 \n"
"		LDREQ	R1, =0x804 \n"
"		LDREQ	R0, =0xFF867E6C \n"
"		BLEQ	sub_FF81E88C \n"
"		MOV	R1, R8 \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF867BC0 \n"
"		LDR	R0, [R4,#0x38] \n"
"		BL	sub_FF8689BC \n"
"		CMP	R0, #0 \n"
"		STREQ	R0, [R4,#0x6C] \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF867C50 \n"
"		MOV	R0, R6 \n"

//"		BL	sub_FF867FD4 \n"
"		BL	sub_FF867FD4_my \n"		//--------------->>

"		MOV	R5, R0 \n"
"		MOV	R0, R6 \n"
"		BL	sub_FF8681FC \n"
"		LDR	R6, [R4,#0x3C] \n"
"		AND	R7, R5,	R0 \n"
"		CMP	R6, #0 \n"
"		LDR	R1, [R4,#0x38] \n"
"		MOVEQ	R0, #0x80000001 \n"
"		MOV	R5, #0 \n"
"		BEQ	loc_FF868450 \n"
"		MOV	R0, R1 \n"
"		BL	sub_FF867814 \n"
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

"loc_FF868450: \n"
"		CMP	R8, #7 \n"
"		STR	R0, [R4,#0x40] \n"
"		LDMNEFD	SP!, {R4-R8,PC} \n"
"		MOV	R0, R8 \n"
"		BL	sub_FF868370 \n"
"		CMP	R0, #0 \n"
"		LDMEQFD	SP!, {R4-R8,LR} \n"
"		LDREQ	R0, =0xFF86849C  \n"
"		BEQ	sub_FF81175C \n"
"		LDMFD	SP!, {R4-R8,PC} \n"
	) ;
}

/*----------------------------------------------------------------------
	sub_FF867FD4_my()
-----------------------------------------------------------------------*/

void __attribute__((naked,noinline)) sub_FF867FD4_my() {
 asm volatile(
"		STMFD	SP!, {R4-R6,LR} \n"
"		MOV	R5, R0 \n"
"		LDR	R0, =0x366A0 \n"
"		ADD	R4, R0,	R5,LSL#7 \n"
"		LDR	R0, [R4,#0x6C] \n"
"		TST	R0, #2 \n"
"		MOVNE	R0, #1 \n"
"		LDMNEFD	SP!, {R4-R6,PC} \n"
"		LDR	R0, [R4,#0x38] \n"
"		MOV	R1, R5 \n"

//"		BL	sub_FF867CD0 \n"
"		BL	sub_FF867CD0_my \n"			//------->>

"		CMP	R0, #0 \n"
"		LDRNE	R0, [R4,#0x38] \n"
"		MOVNE	R1, R5 \n"
"		BLNE	sub_FF867E90 \n"
"		LDR	R2, =0x36720 \n"
"		ADD	R1, R5,	R5,LSL#4 \n"
"		LDR	R1, [R2,R1,LSL#2] \n"
"		CMP	R1, #4 \n"
"		BEQ	loc_FF868034 \n"
"		CMP	R0, #0 \n"
"		LDMEQFD	SP!, {R4-R6,PC} \n"
"		MOV	R0, R5 \n"
"		BL	sub_FF8678A4 \n"
"loc_FF868034: \n"
"		CMP	R0, #0 \n"
"		LDRNE	R1, [R4,#0x6C] \n"
"		ORRNE	R1, R1,	#2 \n"
"		STRNE	R1, [R4,#0x6C] \n"
"		LDMFD	SP!, {R4-R6,PC} \n"
 );
}


		
/*----------------------------------------------------------------------
		sub_FF867CD0_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF867CD0_my() {
 asm volatile(
" 		STMFD	SP!, {R4-R10,LR} \n"
"		MOV	R9, R0 \n"
"		LDR	R0, =0x366A0 \n"
"		MOV	R8, #0 \n"
"		ADD	R5, R0,	R1,LSL#7 \n"
"		LDR	R0, [R5,#0x3C] \n"
"		MOV	R7, #0 \n"
"		CMP	R0, #7 \n"
"		MOV	R6, #0 \n"
"		ADDLS	PC, PC,	R0,LSL#2 \n"
"		B	loc_FF867E28 \n"

"		B	loc_FF867D34 \n"
"		B	loc_FF867D1C \n"
"		B	loc_FF867D1C \n"
"		B	loc_FF867D1C \n"
"		B	loc_FF867D1C \n"
"		B	loc_FF867E20 \n"
"		B	loc_FF867D1C \n"
"		B	loc_FF867D1C \n"

"loc_FF867D1C: \n"
"		MOV	R2, #0 \n"
"		MOV	R1, #0x200 \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF87F2DC \n"
"		MOVS	R4, R0 \n"
"		BNE	loc_FF867D3C \n"

"loc_FF867D34: \n"
"		MOV	R0, #0 \n"
"		LDMFD	SP!, {R4-R10,PC} \n"

"loc_FF867D3C: \n"
"		LDR	R12, [R5,#0x50] \n"
"		MOV	R3, R4 \n"
"		MOV	R2, #1 \n"
"		MOV	R1, #0 \n"
"		MOV	R0, R9 \n"
"		BLX	R12 \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF867D68 \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF87F428 \n"
"		B	loc_FF867D34 \n"
"loc_FF867D68: \n"
"		LDR	R1, [R5,#0x64] \n"
"		MOV	R0, R9 \n"
"		BLX	R1 \n"
		
		

 // Start of DataGhost's FAT32 autodetection code
  
 	//	 "B     dg_sd_fat32_end\n" 	         // delete for FAT32 (plus other stuff below)
		  "MOV   R1, R4\n"           		//  pointer to MBR in R1
		  "BL    mbr_read_dryos\n"   		//  total sectors count in R0 before and after call
		  "MOV     R12, R4\n"               // Copy the MBR start address so we have something to work with
          "MOV     LR, R4\n"                // Save old offset for MBR signature
          "MOV     R1, #1\n"                // Note the current partition number
          "B       dg_sd_fat32_enter\n"     // We actually need to check the first partition as well, no increments yet!
"dg_sd_fat32:\n"                            //
          "CMP     R1, #4\n"                // Did we already see the 4th partition?
          "BEQ     dg_sd_fat32_end\n"       // Yes, break. We didn't find anything, so don't change anything.
          "ADD     R12, R12, #0x10\n"       // Second partition
          "ADD     R1, R1, #1\n"            // Second partition for the loop
"dg_sd_fat32_enter:\n"                      //
          "LDRB    R2, [R12, #0x1BE]\n"     // Partition status
          "LDRB    R3, [R12, #0x1C2]\n"     // Partition type (FAT32 = 0xB)
          "CMP     R3, #0xB\n"              // Is this a FAT32 partition?
          "CMPNE   R3, #0xC\n"              // Not 0xB, is it 0xC (FAT32 LBA) then?
          "BNE     dg_sd_fat32\n"           // No, it isn't. Loop again.
          "CMP     R2, #0x00\n"             // It is, check the validity of the partition type
          "CMPNE   R2, #0x80\n"             //
          "BNE     dg_sd_fat32\n"           // Invalid, go to next partition
                                            // This partition is valid, it's the first one, bingo!
          "MOV     R4, R12\n"               // Move the new MBR offset for the partition detection.
"dg_sd_fat32_end:\n"
	 
    // End of DataGhost's FAT32 autodetection code
	
"		LDRB	R1, [R4,#0x1C9] \n"
"		LDRB	R3, [R4,#0x1C8] \n"
"		LDRB	R12, [R4,#0x1CC] \n"
"		MOV	R1, R1,LSL#24 \n"
"		ORR	R1, R1,	R3,LSL#16 \n"
"		LDRB	R3, [R4,#0x1C7] \n"
"		LDRB	R2, [R4,#0x1BE] \n"

//"		LDRB	LR, [R4,#0x1FF] \n"  			// delete for FAT32

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

//"		LDRB	R12, [R4,#0x1FE] \n"			// delete for FAT32
"		LDRB    R12, [LR,#0x1FE]\n"        		// Added - First MBR signature byte (0x55), LR is original offset.
"		LDRB    LR, [LR,#0x1FF]\n"          	// Added - Last MBR signature byte (0xAA), LR is original offset.

"		BNE	loc_FF867DF4 \n"
"		CMP	R0, R1 \n"
"		BCC	loc_FF867DF4 \n"
"		ADD	R2, R1,	R3 \n"
"		CMP	R2, R0 \n"
"		CMPLS	R12, #0x55 \n"
"		CMPEQ	LR, #0xAA \n"
"		MOVEQ	R7, R1 \n"
"		MOVEQ	R6, R3 \n"
"		MOVEQ	R4, #1 \n"
"		BEQ	loc_FF867DF8 \n"
"loc_FF867DF4: \n"
"		MOV	R4, R8 \n"
"loc_FF867DF8: \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF87F428 \n"
"		CMP	R4, #0 \n"
"		BNE	loc_FF867E34 \n"
"		LDR	R1, [R5,#0x64] \n"
"		MOV	R7, #0 \n"
"		MOV	R0, R9 \n"
"		BLX	R1 \n"
"		MOV	R6, R0 \n"
"		B	loc_FF867E34 \n"

"loc_FF867E20: \n"
"		MOV	R6, #0x40 \n"
"		B	loc_FF867E34 \n"

"loc_FF867E28: \n"
"		LDR	R1, =0x568 \n"
"		LDR	R0, =0xFF867E6C \n"
"		BL	sub_FF81E88C \n"

"loc_FF867E34: \n"
"		STR	R7, [R5,#0x44]! \n"
"		STMIB	R5, {R6,R8} \n"
"		MOV	R0, #1 \n"
"		LDMFD	SP!, {R4-R10,PC} \n"
 );
}
