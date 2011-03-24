#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

//void __attribute__((naked,noinline)) my_blinker(int n) {
//	asm volatile (
//"                STMFD   SP!, {R0-R5,LR}\n"
//);
//	int i, j;
//	for (j=0; j<n; j++)
//	{
//		*((volatile int *) 0xC0220134) = 0x46; // Turn on LED
//		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }
//
//		*((volatile int *) 0xC0220134) = 0x44; // Turn off LED
//		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }
//	}
//	for (i=0; i<0x900000; i++) { asm volatile ( "nop\n" ); }
//	asm volatile (
//"                LDMFD   SP!, {R0-R5,PC}\n"
//	);
//}

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();

void taskHook(context_t **context)
{ 
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_RotaryEncoder)		tcb->entry = (void*)JogDial_task_my;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
}

/*---------------------------------------------------------------------
  Memory Map:
	0001900     MEMBASEADDR             start of data - used for initialized vars
	00108B7                             end of inited data
	00108B8                             start of bss - used for zeroed/uninited vars
	018124B                             end of bss
	018124C     MEMISOSTART             start of our data / bss

	0400000                             raw buffers
	8000000                             end of raw buffers

	C0xxxxxx                            I/O

	FF810000    ROMBASEADDR             start of rom
	FFFFFFFF                            end of rom
----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/

void __attribute__((naked,noinline)) boot() {

    asm volatile (
                 "LDR     R1, =0xC0410000\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R1]\n"
                 "MOV     R1, #0x78\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "MOV     R1, #0\n"
                 "MCR     p15, 0, R1,c7,c10, 4\n"
                 "MCR     p15, 0, R1,c7,c5\n"
                 "MCR     p15, 0, R1,c7,c6\n"
                 "MOV     R0, #0x3D\n"
                 "MCR     p15, 0, R0,c6,c0\n"
                 "MOV     R0, #0xC000002F\n"
                 "MCR     p15, 0, R0,c6,c1\n"
                 "MOV     R0, #0x35\n"
                 "MCR     p15, 0, R0,c6,c2\n"
                 "MOV     R0, #0x40000035\n"
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x80000017\n"
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFF80002D\n"
                 "MCR     p15, 0, R0,c6,c5\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0, 1\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c3,c0\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 2\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 3\n"
                 "MRC     p15, 0, R0,c1,c0\n"
                 "ORR     R0, R0, #0x1000\n"
                 "ORR     R0, R0, #4\n"
                 "ORR     R0, R0, #1\n"
                 "MCR     p15, 0, R0,c1,c0\n"
                 "MOV     R1, #0x80000006\n"
                 "MCR     p15, 0, R1,c9,c1\n"
                 "MOV     R1, #6\n"
                 "MCR     p15, 0, R1,c9,c1, 1\n"
                 "MRC     p15, 0, R1,c1,c0\n"
                 "ORR     R1, R1, #0x50000\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "LDR     R2, =0xC0200000\n"
                 "MOV     R1, #1\n"
                 "STR     R1, [R2,#0x10C]\n"
                 "MOV     R1, #0xFF\n"
                 "STR     R1, [R2,#0xC]\n"
                 "STR     R1, [R2,#0x1C]\n"
                 "STR     R1, [R2,#0x2C]\n"
                 "STR     R1, [R2,#0x3C]\n"
                 "STR     R1, [R2,#0x4C]\n"
                 "STR     R1, [R2,#0x5C]\n"
                 "STR     R1, [R2,#0x6C]\n"
                 "STR     R1, [R2,#0x7C]\n"
                 "STR     R1, [R2,#0x8C]\n"
                 "STR     R1, [R2,#0x9C]\n"
                 "STR     R1, [R2,#0xAC]\n"
                 "STR     R1, [R2,#0xBC]\n"
                 "STR     R1, [R2,#0xCC]\n"
                 "STR     R1, [R2,#0xDC]\n"
                 "STR     R1, [R2,#0xEC]\n"
                 "STR     R1, [R2,#0xFC]\n"
                 "LDR     R1, =0xC0400008\n"
                 "LDR     R2, =0x430005\n"
                 "STR     R2, [R1]\n"
                 "MOV     R1, #1\n"
                 "LDR     R2, =0xC0243100\n"
                 "STR     R2, [R1]\n"
                 "LDR     R2, =0xC0242010\n"
                 "LDR     R1, [R2]\n"
                 "ORR     R1, R1, #1\n"
                 "STR     R1, [R2]\n"

                 "LDR     R0, =0xFFC90928\n" 
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0x108B8\n"
 "loc_FF81013C:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF81013C\n"
                 "LDR     R1, =0x18124C\n"
                 "MOV     R2, #0\n"
 "loc_FF810154:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FF810154\n"
                 "B       sub_FF810354_my" // -->
    );
}

void __attribute__((naked,noinline)) sub_FF810354_my() {

	//http://chdk.setepontos.com/index.php/topic,4194.0.html
	*(int*)0x1938=(int)taskHook;
	*(int*)0x193C=(int)taskHook;	// need this for startup in Playback mode (otherwise init_file_modules_task doesn't hook properly)
    
	// replacement of sub_FF834740 for correct power-on.
	*(int*)(0x2574) = (*(int*)0xC0220128)&1 ? 0x200000 : 0x100000; 

	asm volatile (
                 "LDR     R0, =0xFF8103CC\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFF810404\n"
 "loc_FF810360:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF810360\n"
                 "LDR     R0, =0xFF810404\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFF810618\n"
 "loc_FF81037C:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF81037C\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
 "loc_FF8103B0:\n"
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FF8103B0\n"
//                 "BL      sub_FF811198\n"
                 "BL      sub_FF811198_my\n" // -->
     );
}

void __attribute__((naked,noinline)) sub_FF811198_my() {

     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFB9274C\n"	
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
				 
//               "LDR     R0, =0x18124C\n" // -
                 "LDR     R0, =new_sa\n"   // + patched
                 "LDR     R0, [R0]\n"      // +
				 
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

//"		LDR	R1, =0xFF815EE0 \n"
"		LDR	R1, =sub_FF815EE0_my \n"		// patched

"		B		sub_FF8111F0 \n"		// Continue in firmware
     );
}

void __attribute__((naked,noinline)) sub_FF815EE0_my() {

	asm volatile (
"		STMFD	SP!, {R4,LR} \n"
"		BL	sub_FF810B20 \n"
"		BL	sub_FF81A33C \n"				// dmSetup
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aDmsetup \n"			// "dmSetup"
"		LDRLT	r0, =0xFF815FF4 \n"

"		BLLT	_err_init_task \n"
"		BL	sub_FF815B1C \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aTermdriverinit \n"		// "termDriverInit"
"		LDRLT	R0, =0xFF815FFC \n"

"		BLLT	_err_init_task \n"

//"		ADR	R0, a_term \n"					// "/_term"
"		LDR	R0, =0xFF81600C \n"

"		BL	sub_FF815C04 \n"				// termDeviceCreate
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aTermdevicecrea \n"		// "termDeviceCreate"
"		LDRLT	R0, =0xFF816014 \n"

"		BLLT	_err_init_task \n"

//"		ADR	R0, a_term \n"					// "/_term"
"		LDR	R0, =0xFF81600C \n"

"		BL	sub_FF813CA4 \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aStdiosetup \n"			// "stdioSetup"
"		LDRLT	R0, =0xFF816028 \n"

"		BLLT	_err_init_task \n"
"		BL	sub_FF819CC4 \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aStdlibsetup \n"		// "stdlibSetup"
"		LDRLT	R0, =0xFF816034 \n"

"		BLLT	_err_init_task \n"
"		BL	sub_FF81167C \n"
"		CMP	R0, #0 \n"

//"		ADRLT	R0, aArmlib_setup \n"		// "armlib_setup"
"		LDRLT	R0, =0xFF816040 \n"

"		BLLT	_err_init_task \n"

"		LDMFD	SP!, {R4,LR} \n"

//"		B	sub_FF81FB54 \n"				// taskcreate_Startup
"		B	taskcreate_Startup_my \n"		// patched
        );
};

void __attribute__((naked,noinline)) taskcreate_Startup_my() {

	asm volatile (
		"STMFD	SP!, {R3,LR}\n"
//		"BL		j_nullsub_234\n"
		"BL		sub_FF83C880\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF81FB98\n"
		"BL		sub_FF836160\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF81FB98\n"
		"BL		sub_FF834734\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF81FB98\n"
		"BL		sub_FF833DDC\n"
		"LDR	R1, =0xC0220000\n"
		"MOV	R0, #0x44\n"
		"STR	R0, [R1,#0x1C]\n"
		"BL		sub_FF833FCC\n"
		
"loc_FF81FB94:\n"
		"B		loc_FF81FB94\n"
		
"loc_FF81FB98:\n"
//		"BL		sub_FF834740\n"         // see begin of sub_FF810354_my()
//		"BL		j_nullsub_235\n"
		"BL		sub_FF83AA94\n"
		"LDR	R1, =0x3CE000\n"
		"MOV	R0, #0\n"
		"BL		sub_FF83AEDC\n"
		"BL		sub_FF83AC88\n" // KerSys
		"MOV	R3, #0\n"
		"STR	R3, [SP]\n"

		//"ADR     R3, task_Startup\n"
		"LDR	R3, =task_Startup_my\n"	// patched

		"B		sub_FF81FBC0\n"	// Continue in firmware
     );
}

void __attribute__((naked,noinline)) task_Startup_my() {

	asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL		sub_FF816594\n"	// taskcreate_ClockSave\n"
		"BL		sub_FF835894\n"
		"BL		sub_FF8339A4\n"
//		"BL	j_nullsub_238\n"
		"BL		sub_FF83CAB0\n"
//		"BL		sub_FF83C958\n" // start diskboot.bin
		"BL		sub_FF83CC54\n"
		"BL		sub_FF832474\n"
		"BL		sub_FF83CAE0\n"
		"BL		sub_FF83A238\n"
		"BL		sub_FF83CC58\n"

		"BL		CreateTask_spytask\n" // added

//		"BL		sub_FF83461C\n"	//taskcreate_PhySw\n"
		"BL		taskcreatePhySw_my\n"  // we do this here rather than hook so we don't waste the original stack

		"B		sub_FF81FB24\n"		// Continue in firmware
     );
}

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R4, =0x1C30\n"
"                LDR     R0, [R4,#0x10]\n"
"                CMP     R0, #0\n"
"                BNE     sub_FF834650\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =mykbd_task\n" // task_PhySw
//"                MOV     R2, #0x800\n"
"                MOV     R2, #0x2000\n" // stack size for new task_PhySw so we don't have to do stack switch
"				B	sub_FF834640 \n" // continue in firmware
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
void CreateTask_spytask() {
	_CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}

 ///*----------------------------------------------------------------------
//@ FF8A3B50
void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FF89A298\n"
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    _eventproc_export_PostLogicalEventToUI\n"

				 //"BL      sub_FF89A2C4\n"
                 "BL      sub_FF89A2C4_my\n"			// patched

                 "BL      core_spytask_can_start\n"      // CHDK: Set "it's-safe-to-start" flag for spytask

				 "B			sub_FF8A3B70\n"	// Continue in firmware
 );
}

void __attribute__((naked,noinline)) sub_FF89A2C4_my() {
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
				 "MOV	  R0, #3\n"

                 //"BL      sub_FF876E1C\n"
                 "BL      sub_FF876E1C_my\n"    // patched

				 "B		sub_FF89A2D0\n"	// Continue in firmware
 );
}

void __attribute__((naked,noinline)) sub_FF876E1C_my() {
 asm volatile(
		"STMFD	SP!, {R4-R8,LR}\n"
		"MOV	R8, R0\n"
		"BL		sub_FF876D9C\n"
		"LDR	R1, =0x3A738\n"
		"MOV	R6, R0\n"
		"ADD	R4, R1,	R0,LSL#7\n"
		"LDR	R0, [R4,#0x6C]\n"
		"CMP	R0, #4\n"
		"LDREQ	R1, =0x83f\n"
		"LDREQ	R0, =0xFF8768DC\n"	//=aMounter_c
		"BLEQ	_DebugAssert\n"
		"MOV	R1, R8\n"
		"MOV	R0, R6\n"
		"BL		sub_FF876650\n"
		"LDR	R0, [R4,#0x38]\n"
		"BL		sub_FF8774C0\n"
		"CMP	R0, #0\n"
		"STREQ	R0, [R4,#0x6C]\n"
		"MOV	R0, R6\n"
		"BL		sub_FF8766E0\n"
		"MOV	R0, R6\n"

		//"BL		sub_FF876A44\n"
		"BL		sub_FF876A44_my\n"    // patched

		"B		sub_FF876E74\n"	// Continue in firmware
 );
}

void __attribute__((naked,noinline)) sub_FF876A44_my() {
 asm volatile(
		"STMFD	SP!, {R4-R6,LR}\n"
		"MOV	R5, R0\n"
		"LDR	R0, =0x3A738\n"
		"ADD	R4, R0,	R5,LSL#7\n"
		"LDR	R0, [R4,#0x6C]\n"
		"TST	R0, #2\n"
		"MOVNE	R0, #1\n"
		"LDMNEFD	SP!, {R4-R6,PC}\n"
		"LDR	R0, [R4,#0x38]\n"
		"MOV	R1, R5\n"

		//"BL		sub_FF876764\n"
		"BL		sub_FF876764_my\n"    // patched

		"B		sub_FF876A70\n"	// Continue in firmware
 );
}
//------------------------------------------------------------------
void __attribute__((naked,noinline)) sub_FF876764_my() {
 asm volatile(
		"STMFD	SP!, {R4-R10,LR}\n"
		"MOV	R9, R0\n"
		"LDR	R0, =0x3A738\n"
		"MOV	R8, #0\n"
		"ADD	R5, R0,	R1,LSL#7\n"
		"LDR	R0, [R5,#0x3C]\n"
		"MOV	R7, #0\n"
		"CMP	R0, #7\n"
		"MOV	R6, #0\n"
		"ADDLS	PC, PC,	R0,LSL#2\n"
				"B	loc_FF8768BC\n"
"loc_FF876790:   B	loc_FF8767C8\n"
"loc_FF876794:   B	loc_FF8767B0\n"
"loc_FF876798:   B	loc_FF8767B0\n"
"loc_FF87679C:   B	loc_FF8767B0\n"
"loc_FF8767A0:   B	loc_FF8767B0\n"
"loc_FF8767A4:   B	loc_FF8768B4\n"
"loc_FF8767A8:   B	loc_FF8767B0\n"
"loc_FF8767AC:   B	loc_FF8767B0\n"
"loc_FF8767B0:\n"
		"MOV	R2, #0\n"
		"MOV	R1, #0x200\n"
		"MOV	R0, #2\n"
		"BL		sub_FF894348\n" 
		"MOVS	R4, R0\n"
		"BNE	loc_FF8767D0\n"
"loc_FF8767C8:\n"
		"MOV	R0, #0\n"
		"LDMFD	SP!, {R4-R10,PC}\n"
"loc_FF8767D0:\n"
		"LDR	R12, [R5,#0x50]\n"
		"MOV	R3, R4\n"
		"MOV	R2, #1\n"
		"MOV	R1, #0\n"
		"MOV	R0, R9\n"
		"BLX	R12\n"
		"CMP	R0, #1\n"
		"BNE	loc_FF8767FC\n"
		"MOV	R0, #2\n"
		"BL		sub_FF894498\n" 
		"B		loc_FF8767C8\n"
"loc_FF8767FC:\n"
		"LDR	R1, [R5,#0x64]\n"
		"MOV	R0, R9\n"
		"BLX	R1\n"

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
        "BNE     dg_sd_fat32\n"                // No, it isn't. Loop again.
        "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
        "CMPNE   R2, #0x80\n"
        "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                               // This partition is valid, it's the first one, bingo!
        "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.

"dg_sd_fat32_end:\n"
        // End of DataGhost's FAT32 autodetection code

		"LDRB	R1, [R4,#0x1C9]\n"
		"LDRB	R3, [R4,#0x1C8]\n"
		"LDRB	R12, [R4,#0x1CC]\n"
		"MOV	R1, R1,LSL#24\n"
		"ORR	R1, R1,	R3,LSL#16\n"
		"LDRB	R3, [R4,#0x1C7]\n"
		"LDRB	R2, [R4,#0x1BE]\n"
//		"LDRB	LR, [R4,#0x1FF]\n"
		"ORR	R1, R1,	R3,LSL#8\n"
		"LDRB	R3, [R4,#0x1C6]\n"
		"CMP	R2, #0\n"
		"CMPNE	R2, #0x80\n"
		"ORR	R1, R1,	R3\n"
		"LDRB	R3, [R4,#0x1CD]\n"
		"MOV	R3, R3,LSL#24\n"
		"ORR	R3, R3,	R12,LSL#16\n"
		"LDRB	R12, [R4,#0x1CB]\n"
		"ORR	R3, R3,	R12,LSL#8\n"
		"LDRB	R12, [R4,#0x1CA]\n"
		"ORR	R3, R3,	R12\n"
//		"LDRB    R12, [R4,#0x1FE]\n"
"                LDRB    R12, [LR,#0x1FE]\n" // +
"                LDRB    LR, [LR,#0x1FF]\n" // +
		"BNE	loc_FF876888\n"
		"CMP	R0, R1\n"
		"BCC	loc_FF876888\n"
		"ADD	R2, R1,	R3\n"
		"CMP	R2, R0\n"
		"CMPLS	R12, #0x55\n"
		"CMPEQ	LR, #0xAA\n"
		"MOVEQ	R7, R1\n"
		"MOVEQ	R6, R3\n"
		"MOVEQ	R4, #1\n"
		"BEQ	loc_FF87688C\n"
"loc_FF876888:\n"
		"MOV	R4, R8\n"
"loc_FF87688C:\n"
		"MOV	R0, #2\n"
		"BL		sub_FF894498\n" 
		"CMP	R4, #0\n"
		"BNE	loc_FF8768C8\n"
		"LDR	R1, [R5,#0x64]\n"
		"MOV	R7, #0\n"
		"MOV	R0, R9\n"
		"BLX	R1\n"
		"MOV	R6, R0\n"
		"B		loc_FF8768C8\n"
"loc_FF8768B4:\n"
		"MOV	R6, #0x40\n"
		"B		loc_FF8768C8\n"
"loc_FF8768BC:\n"
		"LDR	R1, =0x597\n"
		"LDR	R0, =0xFF8768DC\n"	//=aMounter_c
		"BL		_DebugAssert\n"
"loc_FF8768C8:\n"
		"STR	R7, [R5,#0x44]!\n"
		"STMIB	R5, {R6,R8}\n"
		"MOV	R0, #1\n"
		"LDMFD	SP!, {R4-R10,PC}\n"
 );
}

// Firmware version @ FF865D08
void __attribute__((naked,noinline)) JogDial_task_my() {
 asm volatile(
"                STMFD   SP!, {R4-R11,LR} \n"
"                SUB     SP, SP, #0x1C \n"
"                BL      sub_FF8660A0 \n"
"                LDR     R1, =0x2588 \n"
"                LDR     R6, =0xFFB97C9C \n"
"                MOV     R0, #0 \n"
"                ADD     R3, SP, #0x10 \n"
"                ADD     R12, SP, #0x14 \n"
"                ADD     R10, SP, #0x08 \n"
"                MOV     R2, #0 \n"
"                ADD     R9, SP, #0x0C \n"

"loc_FF865D34: \n"
"                ADD     R12, SP, #0x14 \n"
"                ADD     LR, R12, R0,LSL#1 \n"
"                MOV     R2, #0 \n"
"                ADD     R3, SP, #0x10 \n"
"                STRH    R2, [LR] \n"
"                ADD     LR, R3, R0,LSL#1 \n"
"                STRH    R2, [LR] \n"
"                STR     R2, [R9,R0,LSL#2] \n"
"                STR     R2, [R10,R0,LSL#2] \n"
"                ADD     R0, R0, #1 \n"
"                CMP     R0, #1 \n"
"                BLT     loc_FF865D34 \n"

"loc_FF865D64: \n"
"                LDR     R0, =0x2588 \n"
"                MOV     R2, #0 \n"
"                LDR     R0, [R0,#8] \n"
"                MOV     R1, SP \n"
"                BL      sub_FF83A4C8 \n"
"                CMP     R0, #0 \n"
"                LDRNE   R1, =0x262 \n"

//"                ADRNE   R0, aRotaryencoder_ ; "RotaryEncoder.c" \n"
"				LDRNE	R0,=0xFF865FC4 \n"

"                BLNE    _DebugAssert \n"
"                LDR     R0, [SP] \n"
"                AND     R4, R0, #0xFF \n"
"                AND     R0, R0, #0xFF00 \n"
"                CMP     R0, #0x100 \n"
"                BEQ     loc_FF865DD4 \n"
"                CMP     R0, #0x200 \n"
"                BEQ     loc_FF865E0C \n"
"                CMP     R0, #0x300 \n"
"                BEQ     loc_FF866004 \n"
"                CMP     R0, #0x400 \n"
"                BNE     loc_FF865D64 \n"
"                CMP     R4, #0 \n"
"                LDRNE   R1, =0x2ED \n"

//"                ADRNE   R0, aRotaryencoder_ ; "RotaryEncoder.c" \n"
"				LDRNE	R0,=0xFF865FC4 \n"

"                BLNE    _DebugAssert \n"
"                RSB     R0, R4, R4,LSL#3 \n"
"                LDR     R0, [R6,R0,LSL#2] \n"

"loc_FF865DCC: \n"
"                BL      sub_FF866084 \n"
"                B       loc_FF865D64 \n"

"loc_FF865DD4: \n"
//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n" //sleep
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
"                LDR     R7, =0x2594 \n"
"                LDR     R0, [R7,R4,LSL#2] \n"
"                BL      sub_FF83B460 \n"

//"                ADR     R2, loc_FF865C54 \n"
"                LDR     R2, =0xFF865C54 \n"

"                ADD     R1, R2, #0 \n"
"                ORR     R3, R4, #0x200 \n"
"                MOV     R0, #0x28 \n"
"                BL      sub_FF83B37C \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R10,R4,LSL#2] \n"
"                BEQ     loc_FF865D64 \n"
"                MOV     R1, #0x274 \n"
"                B       loc_FF865FB0 \n"

"loc_FF865E0C: \n"
"                RSB     R5, R4, R4,LSL#3 \n"
"                LDR     R0, [R6,R5,LSL#2] \n"
"                LDR     R1, =0xC0240104 \n"
"                LDR     R0, [R1,R0,LSL#8] \n"
"                MOV     R2, R0,ASR#16 \n"
"                ADD     R0, SP, #0x14 \n"
"                ADD     R0, R0, R4,LSL#1 \n"
"                STR     R0, [SP,#0x18] \n"
"                STRH    R2, [R0] \n"
"                ADD     R0, SP, #0x10 \n"
"                ADD     R11, R0, R4,LSL#1 \n"
"                LDRSH   R3, [R11] \n"
"                SUB     R0, R2, R3 \n"
"                CMP     R0, #0 \n"
"                BNE     loc_FF865E8C \n"
"                LDR     R0, [R9,R4,LSL#2] \n"
"                CMP     R0, #0 \n"
"                BEQ     loc_FF865F6C \n"
"                LDR     R7, =0x2594 \n"
"                LDR     R0, [R7,R4,LSL#2] \n"
"                BL      sub_FF83B460 \n"

//"                ADR     R2, sub_FF865C60 \n"
"                LDR     R2, =0xFF865C60 \n"

"                ADD     R1, R2, #0 \n"
"                ORR     R3, R4, #0x300 \n"
"                MOV     R0, #0x1F4 \n"
"                BL      sub_FF83B37C \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R7,R4,LSL#2] \n"
"                BEQ     loc_FF865F6C \n"
"                LDR     R1, =0x28D \n"
"                B       loc_FF865F64 \n"

"loc_FF865E8C: \n"
"                MOV     R1, R0 \n"
"                RSBLT   R0, R0, #0 \n"
"                MOVLE   R7, #0 \n"
"                MOVGT   R7, #1 \n"
"                CMP     R0, #0xFF \n"
"                BLS     loc_FF865ECC \n"
"                CMP     R1, #0 \n"
"                RSBLE   R0, R3, #0xFF \n"
"                ADDLE   R0, R0, #0x7F00 \n"
"                ADDLE   R0, R0, R2 \n"
"                RSBGT   R0, R2, #0xFF \n"
"                ADDGT   R0, R0, #0x7F00 \n"
"                ADDGT   R0, R0, R3 \n"
"                ADD     R0, R0, #0x8000 \n"
"                ADD     R0, R0, #1 \n"
"                EOR     R7, R7, #1 \n"

"loc_FF865ECC: \n"
"                STR     R0, [SP,#0x04] \n"
"                LDR     R0, [R9,R4,LSL#2] \n"
"                CMP     R0, #0 \n"
"                ADDEQ   R0, R6, R5,LSL#2 \n"
"                LDREQ   R0, [R0,#8] \n"
"                BEQ     loc_FF865F04 \n"
"                ADD     R8, R6, R5,LSL#2 \n"
"                ADD     R1, R8, R7,LSL#2 \n"
"                LDR     R1, [R1,#0x10] \n"
"                CMP     R1, R0 \n"
"                BEQ     loc_FF865F08 \n"
"                LDR     R0, [R8,#0xC] \n"
"                BL      sub_FF89FEC0 \n" 
"                LDR     R0, [R8,#8] \n"

"loc_FF865F04: \n"
"                BL      sub_FF89FEC0 \n" 

"loc_FF865F08: \n"
"                ADD     R0, R6, R5,LSL#2 \n"
"                ADD     R7, R0, R7,LSL#2 \n"
"                LDR     R0, [R7,#0x10] \n"
"                LDR     R1, [SP,#0x04] \n"
"                BL      sub_FF89FDE8 \n" 
"                LDR     R0, [R7,#0x10] \n"
"                LDR     R7, =0x2594 \n"
"                STR     R0, [R9,R4,LSL#2] \n"
"                LDR     R0, [SP,#0x18] \n"
"                LDRH    R0, [R0] \n"
"                STRH    R0, [R11] \n"
"                LDR     R0, [R7,R4,LSL#2] \n"
"                BL      sub_FF83B460 \n"

//"                ADR     R2, sub_FF865C60 \n"
"                LDR     R2, =0xFF865C60 \n"

"                ADD     R1, R2, #0 \n"
"                ORR     R3, R4, #0x300 \n"
"                MOV     R0, #0x1F4 \n"
"                BL      sub_FF83B37C \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R7,R4,LSL#2] \n"
"                BEQ     loc_FF865F6C \n"
"                LDR     R1, =0x2CF \n"

"loc_FF865F64: \n"
//"                ADR     R0, aRotaryencoder_ ; "RotaryEncoder.c" \n"
"				LDR		R0,=0xFF865FC4 \n"

"                BL      _DebugAssert \n"

"loc_FF865F6C: \n"
"                ADD     R0, R6, R5,LSL#2 \n"
"                LDR     R0, [R0,#0x18] \n"
"                CMP     R0, #1 \n"
"                BNE     loc_FF865FFC \n"
"                LDR     R0, =0x2588 \n"
"                LDR     R0, [R0,#0x10] \n"
"                CMP     R0, #0 \n"
"                BEQ     loc_FF865FFC \n"

//"                ADR     R2, loc_FF865C54 \n"
"                LDR     R2, =0xFF865C54 \n"

"                ADD     R1, R2, #0 \n"
"                ORR     R3, R4, #0x400 \n"
"                BL      sub_FF83B37C \n"
"                TST     R0, #1 \n"
"                CMPNE   R0, #0x15 \n"
"                STR     R0, [R10,R4,LSL#2] \n"
"                BEQ     loc_FF865D64 \n"
"                LDR     R1, =0x2D6 \n"

"loc_FF865FB0: \n"
//"                ADR     R0, aRotaryencoder_ ; "RotaryEncoder.c" \n"
"				LDR		R0,=0xFF865FC4 \n"

"                BL      _DebugAssert \n"
"                B       loc_FF865D64 \n"

"loc_FF865FFC: \n"
"                LDR     R0, [R6,R5,LSL#2] \n"
"                B       loc_FF865DCC \n"

"loc_FF866004: \n"
"                LDR     R0, [R9,R4,LSL#2] \n"
"                CMP     R0, #0 \n"
"                MOVEQ   R1, #0x2E0 \n"

//"                ADREQ   R0, aRotaryencoder_ ; "RotaryEncoder.c" \n"
"				LDRNE	R0,=0xFF865FC4 \n"

"                BLEQ    _DebugAssert \n"
"                RSB     R0, R4, R4,LSL#3 \n"
"                ADD     R0, R6, R0,LSL#2 \n"
"                LDR     R0, [R0,#0xC] \n"
"                BL      sub_FF89FEC0 \n" 
"                MOV     R2, #0 \n"
"                STR     R2, [R9,R4,LSL#2] \n"
"                B       loc_FF865D64 \n"
);
}
