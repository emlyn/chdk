#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
//extern void createHook (void *pNewTcb);
//extern void deleteHook (void *pTcb);

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void boot();



#define DEBUG_LED 0xC02200CC
void boot() { //#fs
    long *canon_data_src = (void*)0xFFAF47EC;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xFEBC - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xFEBC; // just after data 
    long canon_bss_len = 0x9FE50 - 0xFEBC; 

    long i;


    // Code taken from VxWorks CHDK. Changes CPU speed?
    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;

/*    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"BIC     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
*/
    // jump to init-sequence that follows the data-copy-routine 
    asm volatile ("B      sub_FF8101a4_my\n");
}; //#fe


// init
void __attribute__((naked,noinline)) sub_FF8101a4_my() { //#fs 
        asm volatile (
		"LDR	R0, =0xFF81021C\n"
		"MOV	R1, #0\n"
		"LDR	R3, =0xFF810254\n"

        "loc_FF8101B0:\n"
		"CMP	R0, R3\n"
		"LDRCC	R2, [R0],#4\n"
		"STRCC	R2, [R1],#4\n"
		"BCC	loc_FF8101B0\n"
		"LDR	R0, =0xFF810254\n"
		"MOV	R1, #0x4B0\n"
		"LDR	R3, =0xFF810468\n"

        "loc_FF8101CC:\n"
		"CMP	R0, R3\n"
		"LDRCC	R2, [R0],#4\n"
		"STRCC	R2, [R1],#4\n"
		"BCC	loc_FF8101CC\n"
		"MOV	R0, #0xD2\n"
		"MSR	CPSR_cxsf, R0\n"
		"MOV	SP, #0x1000\n"
		"MOV	R0, #0xD3\n"
		"MSR	CPSR_cxsf, R0\n"
		"MOV	SP, #0x1000\n"
		"LDR	R0, =0x6C4\n"
		"LDR	R2, =0xEEEEEEEE\n"
		"MOV	R3, #0x1000\n"

        "loc_FF810200:\n"
		"CMP	R0, R3\n"
		"STRCC	R2, [R0],#4\n"
		"BCC	loc_FF810200\n"
		//"BL	sub_FF810FB8\n"
                "BL      sub_FF810FB8_my\n"
        );

} //#fe

void __attribute__((naked,noinline)) sub_FF810FB8_my() { //#fs 
        asm volatile (
        	"STR	LR, [SP,#-4]!\n"            // inspired by original CHDK-code
		"SUB	SP, SP,	#0x74\n"
		"MOV	R0, SP\n"
		"MOV	R1, #0x74\n"
		"BL	sub_FFA8C05C\n"
		"MOV	R0, #0x53000\n"
		"STR	R0, [SP,#0x74-0x70]\n"
        );
//              "LDR     R0, =0x0x9FE50\n"          // 0x9fe50 + 0x40000, 
        asm volatile (
                "LDR    R0, =new_sa\n"
                "LDR    R0, [R0]\n"
        );
        asm volatile (
		"LDR	R2, =0x2ABC00\n"
		"LDR	R1, =0x2A4968\n"
		"STR	R0, [SP,#0x74-0x6C]\n"
		"SUB	R0, R1,	R0\n"
		"ADD	R3, SP,	#0x74-0x68\n"
		"STR	R2, [SP,#0x74-0x74]\n"
		"STMIA	R3, {R0-R2}\n"
		"MOV	R0, #0x22\n"
		"STR	R0, [SP,#0x74-0x5C]\n"
		"MOV	R0, #0x68\n"
		"STR	R0, [SP,#0x74-0x58]\n"
		"LDR	R0, =0x19B\n"
		"MOV	R1, #0x64\n"
                //"STRD   R0, [SP,#0x74-0x54]\n"        // "strd not supported by cpu" claims gcc
                "STR    R0, [SP,#0x74-0x54]\n"          // split in two single-word STRs
                "STR    R1, [SP,#0x74-0x50]\n"

                "MOV    R0, #0x78\n"
                //"STRD   R0, [SP,#0x74-0x4C]\n"        // "strd not supported by cpu" claims gcc
                "STR    R0, [SP,#0x74-0x4C]\n"          // split in two single-word STRs
                "STR    R1, [SP,#0x74-0x48]\n"

		"MOV	R0, #0\n"
		"STR	R0, [SP,#0x74-0x44]\n"
		"STR	R0, [SP,#0x74-0x40]\n"
		"MOV	R0, #0x10\n"
		"STR	R0, [SP,#0x74-0x18]\n"
		"MOV	R0, #0x800\n"
		"STR	R0, [SP,#0x74-0x14]\n"
		"MOV	R0, #0xA0\n"
		"STR	R0, [SP,#0x74-0x10]\n"
		"MOV	R0, #0x280\n"
		"STR	R0, [SP,#0x74-0x0C]\n"

		//"LDR    R1, =0xFF814DBC\n"         // uHwSetup = 0xFFC04DBC
                "LDR    R1, =uHwSetup_my\n"          // followup to own function
		
                "MOV	R0, SP\n"
		"MOV	R2, #0\n"
		"BL	sub_FF812D70\n"
		"ADD	SP, SP,	#0x74\n"
		"LDR	PC, [SP],#4\n"
        );
}; //#fe

void __attribute__((naked,noinline)) uHwSetup_my() { //#fs 
        asm volatile (
        	"STMFD	SP!, {R4,LR}\n"
		"BL	sub_FF81095C\n"
		"BL	sub_FF819A10\n"
		"CMP	R0, #0\n"
		"LDRLT	R0, =0xFF814ED0\n"
		"BLLT	sub_FF814EB0\n"
		"BL	sub_FF8149E0\n"
		"CMP	R0, #0\n"
		"LDRLT	R0, =0xFF814ED8\n"
		"BLLT	sub_FF814EB0\n"
		"LDR	R0, =0xFF814EE8\n"
		"BL	sub_FF814ACC\n"
		"CMP	R0, #0\n"
		"LDRLT	R0, =0xFF814EF0\n"
		"BLLT	sub_FF814EB0\n"
		"LDR	R0, =0xFF814EE8\n"
		"BL	sub_FF81357C\n"
		"CMP	R0, #0\n"
		"LDRLT	R0, =0xFF814F04\n"
		"BLLT	sub_FF814EB0\n"
		"BL	sub_FF819598\n"
		"CMP	R0, #0\n"
		"LDRLT	R0, =0xFF814F10\n"
		"BLLT	sub_FF814EB0\n"
		"BL	sub_FF8114D0\n"
		"CMP	R0, #0\n"
		"LDRLT	R0, =0xFF814F1C\n"
		"BLLT	sub_FF814EB0\n"
		"LDMFD	SP!, {R4,LR}\n"
        	//"B	sub_FF81DCD4\n"        //taskcreate_Startup
		"B	taskcreate_Startup_my\n"
        );
}; //#fe

void __attribute__((naked,noinline)) taskcreate_Startup_my() { //#fs 
        asm volatile (
		"STMFD	SP!, {R3,LR}	\n"
		"BL	sub_FF822E08	\n"
		"BL	sub_FF82BA7C	\n"
		"CMP	R0, #0		\n"
		"BNE	loc_FF81DD0C	\n"
		"LDR	R2, =0xC0220000	\n"
		"LDR	R0, [R2,#0x78]	\n"
		"LDR	R1, [R2,#0x7C]	\n"
		"AND	R0, R0,	R1	\n"
		"TST	R0, #1		\n"
		"BEQ	loc_FF81DD0C	\n"
		"MOV	R0, #0x44	\n"
		"STR	R0, [R2,#0x4C]	\n"

        "loc_FF81DD08:\n"
		"B	loc_FF81DD08	\n"

        "loc_FF81DD0C:\n"
		"BL	sub_FF822E10	\n"
		"BL	sub_FF822E0C	\n"
		"BL	sub_FF829608	\n"
		"MOV	R1, #0x300000	\n"
		"MOV	R0, #0		\n"
		"BL	sub_FF829850	\n"
		"BL	sub_FF8297FC	\n"
		"MOV	R3, #0		\n"
		"STR	R3, [SP,#8-8]   \n"

        	//"LDR	R3, =0xFF81DC78 \n"
                "LDR    R3, =task_Startup_my\n"      // followup to own function

                "MOV	R2, #0		\n"
		"MOV	R1, #0x19	\n"
		"LDR	R0, =0xFF81DD50	\n"
		"BL	sub_FF81BBB8	\n"
		"MOV	R0, #0		\n"
		"LDMFD	SP!, {R12,PC}	\n"
        );
}; //#fe

// Extracted method: task_Startup (FF81DC78-FF81DCD0)
void __attribute__((naked,noinline)) task_Startup_my() { //#fs 
        asm volatile (
        "STMFD	SP!, {R4,LR}	\n"
		"BL	_taskcreate_ClockSave    \n"
		"BL	sub_FF823FA8	\n"
		"BL	sub_FF820E84	\n"
		//"BL	j_nullsub_191	\n"
		"BL	sub_FF82BC5C	\n"
		//"BL	sub_FF82BB44	\n"       //StartDiskboot
        );

        CreateTask_spytask();

		//*((int*)0x9C10) = 1; // this turns on wheel debug mode
		//*((int*)0x9C18) = 1; // this completely disables the wheel and buttons

        asm volatile (
		"BL	sub_FF82BE24	\n"
		"BL	sub_FF82BCAC_my	\n"  // ---------> touch_wheel.c
		"BL	sub_FF828B4C	\n"
		"BL	sub_FF82BE28	\n"
        );

        CreateTask_PhySw();

        asm volatile (
		//"BL	sub_FF822DAC    \n"       //taskcreate_PhySw
		"BL	sub_FF825C34_my	\n"       //divert to intercept task_ShootSeqTask
		"BL	sub_FF82BE40	\n"
		//"BL	nullsub_2	\n"
		"BL	sub_FF82213C	\n"
		"BL	_taskcreate_Bye	\n"
		"BL	sub_FF8228D8	\n"
		"BL	_taskcreate_TempCheck    \n"
		"BL	sub_FF82C8E4_my	\n"       //   ---------------> for SDHC and movie rec
		"BL	sub_FF822004	\n"

                // modification: BL instead of B to last function to control action after its return
        	"BL	sub_FF815088	\n"
		"LDMFD	SP!, {R4,PC}	\n"       // restore stack to PC instead of LR to return to caller
//		"LDMFD	SP!, {R4,LR}	\n"
//        	"B	sub_FF815088	\n"
        );
}; //#fe

void CreateTask_spytask() { //#fs 
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

void CreateTask_PhySw() { //#fs 
        _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
}; //#fe


void __attribute__((naked,noinline)) sub_FF825C34_my() { //#fs 
        asm volatile (
                "STMFD   SP!, {R4,LR}   \n"
                "LDR     R4, =0x1CB8    \n"
                "MOV     R0, #0         \n"
                "MOV     R1, #4         \n"
                "STR     R0, [R4,#0xC]  \n"
                "BL      sub_FF81BEE8   \n"
                "STR     R0, [R4,#4]    \n"
                "MOV     R0, #0         \n"
                "MOV     R1, #1         \n"
                "BL      sub_FF81BF0C   \n"
                "STR     R0, [R4,#8]    \n"
                "BL      sub_FF85EE84   \n"
                "BL      sub_FF85DE2C   \n"
                "BL      sub_FF85AFF4_my\n"         // divert this for ShootSeqTask
                "BL      sub_FF85F14C   \n"
                "LDR     R0, [R4,#4]    \n"
                "LDMFD   SP!, {R4,LR}   \n"
                "MOV     R1, #0x1000    \n"
                "B       sub_FF828EAC   \n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF85AFF4_my() { //#fs 
        asm volatile (
        	"STMFD	SP!, {R4,LR}		 \n"
		"LDR	R4, =0x55F4		 \n"
		"LDR	R0, [R4,#8]		 \n"
		"CMP	R0, #0			 \n"
		"BNE	loc_FF85B060		 \n"
		//"BL	nullsub_29		 \n"
		"MOV	R1, #1			 \n"
		"MOV	R0, #0			 \n"
		"BL	sub_FF81BF0C		 \n"
		"STR	R0, [R4,#0x1C]		 \n"
		"MOV	R0, #0			 \n"
		"MOV	R1, #0			 \n"
		"BL	sub_FF81BEE8		 \n"
		"STR	R0, [R4,#0x20]		 \n"
		"BL	sub_FF85B3C0		 \n"
		"BL	sub_FF85B1C4      	 \n"     // continue here for task_ShootSeqTask (this is nonsense. We just need CaptSeqTask)
		"MOV	R0, #0			 \n"
		"STR	R0, [R4,#0x18]		 \n"
		"ADD	R0, R4,	#0x24		 \n"
		"MOV	R1, #0			 \n"
		"STR	R1, [R0],#4		 \n"
		"STR	R1, [R0]		 \n"
		"BL	sub_FF85B6D8		 \n"
		"BL	sub_FF85F2F8		 \n"
		"BL	sub_FF85D7B8		 \n"
		"BL	sub_FF85BF7C_my	         \n"     // continue here for task_CaptSeqTask
		"BL	sub_FF85D270             \n"

        "loc_FF85B060:          		 \n"
		"MOV	R0, #1			 \n"
		"STR	R0, [R4,#8]		 \n"
		"LDMFD	SP!, {R4,PC}		 \n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF85BF7C_my() { //#fs  // CreateTask_CaptSeqTask
        asm volatile (
        	"STMFD	SP!, {R3-R5,LR}		\n"
		"LDR	R2, =0x1A018		\n"
		"MOV	R0, #0			\n"
		"MOV	R1, #0			\n"

        "loc_FF85BF8C:				\n"
		"ADD	R3, R2,	R0,LSL#4	\n"
		"ADD	R0, R0,	#1		\n"
		"CMP	R0, #5			\n"
		"STR	R1, [R3,#8]		\n"
		"BCC	loc_FF85BF8C		\n"
		"BL	sub_FF930274		\n"
		"BL	sub_FF931FE8		\n"
		"MOV	R1, #5			\n"
		"MOV	R0, #0			\n"
		"BL	sub_FF81BEC4		\n"
		"LDR	R4, =0x5640		\n"
		"LDR	R1, =0x1001FF		\n"
		"STR	R0, [R4,#0xC]		\n"
		"MOV	R0, #0			\n"
		"BL	sub_FF81BEE8		\n"
		"STR	R0, [R4,#8]		\n"
		"MOV	R3, #0			\n"
		//"STR	R3, [SP,#0x10+var_10]	\n"
                "STR     R3, [SP]               \n"
		//"LDR	R3, =0xFF85BD10	        \n"    // task_CaptSeqTask
                "LDR    R3, =task_CaptSeqTask_my\n"    // task_CaptSeqTask
		"LDR	R0, =0xFF85C148  	\n"    // aCaptseqtask ; "CaptSeqTask"
		"MOV	R2, #0x1000		\n"
		"MOV	R1, #0x17		\n"
		"BL	sub_FF81BE90		\n"
		"LDMFD	SP!, {R3-R5,PC}		\n"
        ".ltorg\n"
        );
}; //#fe


// -----------------
// SDHC-Boot-Support
// -----------------

// Extracted method: sub_FF82C8E4 (FF82C8E4-FF82C928)
// Overridden calls:
//     sub_FF82C3F0
void __attribute__((naked,noinline)) sub_FF82C8E4_my() { //#fs  
    asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL	sub_FF86DC24\n"
		"BL	_IsFactoryMode\n"
		"CMP	R0, #1\n"
		"BNE	loc_FF82C904\n"
		"BL	sub_FF870E44\n"
		"LDMFD	SP!, {R4,LR}\n"
		"B	_StartFactoryModeController\n"


	"loc_FF82C904:\n"
		"BL	sub_FF86FE00\n"
		"LDR	R4, =0x1DD0\n"
		"LDR	R0, [R4,#4]\n"
		"CMP	R0, #0\n"
		"LDMNEFD	SP!, {R4,PC}\n"
		"MOV	R1, #0\n"
		"LDR	R0, =sub_FF82C3F0_my\n"    //   ---------------> for SDHC and movie rec
		"BL	_CreateController\n"
		"STR	R0, [R4,#4]\n"
		"LDMFD	SP!, {R4,PC}\n"
    );
}; //#fe

// Extracted method: sub_FF82C3F0 (FF82C3F0-FF82C8E0)
// Overridden calls:
//     sub_FF82C1B0
//     sub_FF86FB00
//     sub_FF870B0C
void __attribute__((naked,noinline)) sub_FF82C3F0_my() {
    asm volatile (
        "     STMFD   SP!, {R3-R11,LR}\n"
        "     LDR     R6, =0x1DD0\n"
        "     MOV     R5, R1\n"
        "     LDR     R0, [R6,#0x14]\n"
        "     MOV     R4, R3\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF82C414\n"
        "     BL         sub_FF86E44C\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C414:\n"    // CODE XREF: sub_FF82C3F0+18j
        "     LDR     R12, =0x1162\n"
        "     LDR     R10, =0x1005\n"
        "     CMP     R5, R12\n"
        "     MOV     R7, #0\n"
        "     MOV     R8, #1\n"
        "     BEQ     loc_FF82C840\n"
        "     BGT     loc_FF82C568\n"
        "     LDR     R12, =0x1062\n"
        "     CMP     R5, R12\n"
        "     BEQ     loc_FF82C8DC\n"
        "     BGT     loc_FF82C4DC\n"
        "     CMP     R5, R10\n"
        "     BEQ     loc_FF82C86C\n"
        "     BGT     loc_FF82C4B4\n"
        "     LDR     R9, =0x9A3\n"
        "     CMP     R5, R9\n"
        "     ADD     R10, R9, #2\n"
        "     BEQ     loc_FF82C7F4\n"
        "     BGT     loc_FF82C494\n"
        "     SUB     R12, R5, #0x800\n"
        "     SUBS    R12, R12, #3\n"
        "     BEQ     loc_FF82C6EC\n"
        "     SUB     R12, R5, #0x800\n"
        "     SUBS    R12, R12, #0x158\n"
        "     BNE     loc_FF82C830\n"
        "     TST     R4, #0x80000000\n"
        "     MOVNE   R0, #1\n"
        "     BNE     locret_FF82C750\n"
        "     BL         sub_FF8781D0\n"
        "     CMP     R0, #0\n"
        "     BLEQ    sub_FF828A3C\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C494:\n"    // CODE XREF: sub_FF82C3F0+6Cj
        "     CMP     R5, R10\n"
        "     BEQ     loc_FF82C7F4\n"
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #3\n"
        "     BNE     loc_FF82C830\n"
        "     BL         sub_FF82C324\n"
        "     MOV     R1, R4\n"
        "     B         loc_FF82C838\n"


    "loc_FF82C4B4:\n"    // CODE XREF: sub_FF82C3F0+58j
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #0x56\n"
        "     SUBNE   R12, R5, #0x1000\n"
        "     SUBNES  R12, R12, #0x5B\n"
        "     SUBNE   R12, R5, #0x1000\n"
        "     SUBNES  R12, R12, #0x5E\n"
        "     SUBNE   R12, R5, #0x1000\n"
        "     SUBNES  R12, R12, #0x61\n"
        "     BNE     loc_FF82C830\n"
        "     B         loc_FF82C8DC\n"


    "loc_FF82C4DC:\n"    // CODE XREF: sub_FF82C3F0+4Cj
        "     LDR     R12, =0x10AD\n"
        "     CMP     R5, R12\n"
        "     BEQ     loc_FF82C85C\n"
        "     BGT     loc_FF82C52C\n"
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #0x63\n"
        "     SUBNE   R12, R5, #0x1000\n"
        "     SUBNES  R12, R12, #0x65\n"
        "     BEQ     loc_FF82C8DC\n"
        "     SUB     R12, R5, #0x1000\n"
        "     LDR     R0, =0x10A3\n"
        "     SUBS    R12, R12, #0xA9\n"
        "     BEQ     loc_FF82C850\n"
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #0xAA\n"
        "     BNE     loc_FF82C830\n"
        "     BL         _IsControlEventActive\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF82C868\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C52C:\n"    // CODE XREF: sub_FF82C3F0+F8j
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #0xAE\n"
        "     BEQ     loc_FF82C868\n"
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #0xAF\n"
        "     BEQ     loc_FF82C85C\n"
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #0xB0\n"
        "     BEQ     loc_FF82C868\n"
        "     SUB     R12, R5, #0x1000\n"
        "     SUBS    R12, R12, #0xB2\n"
        "     BNE     loc_FF82C830\n"
        "     LDR     R0, =0x1008\n"
        "     MOV     R1, R4\n"
        "     B         loc_FF82C838\n"


    "loc_FF82C568:\n"    // CODE XREF: sub_FF82C3F0+3Cj
        "     LDR     R11, =0x201B\n"
        "     LDR     R0, =0x1DD0\n"
        "     CMP     R5, R11\n"
        "     LDR     R2, [R0,#0x10]!\n"
        "     LDR     R1, [R0,#0x10]\n"
        "     SUB     R9, R11, #0x17\n"
        "     BEQ     loc_FF82C7C8\n"
        "     BGT     loc_FF82C600\n"
        "     LDR     R11, =0x116A\n"
        "     CMP     R5, R11\n"
        "     BEQ     loc_FF82C7B4\n"
        "     BGT     loc_FF82C5C4\n"
        "     SUB     R0, R5, #0x1100\n"
        "     SUB     R0, R0, #0x63\n"
        "     CMP     R0, #5\n"
        "     ADDLS   PC, PC, R0,LSL#2\n"
        "     B         loc_FF82C830\n"


    "loc_FF82C5AC:\n"    // CODE XREF: sub_FF82C3F0+1B4j
        "     B         loc_FF82C7EC\n"


    "loc_FF82C5B0:\n"    // CODE XREF: sub_FF82C3F0+1B4j
        "     B         loc_FF82C7E0\n"


    "loc_FF82C5B4:\n"    // CODE XREF: sub_FF82C3F0+1B4j
        "     B         loc_FF82C7D8\n"


    "loc_FF82C5B8:\n"    // CODE XREF: sub_FF82C3F0+1B4j
        "     B         loc_FF82C830\n"


    "loc_FF82C5BC:\n"    // CODE XREF: sub_FF82C3F0+1B4j
        "     B         loc_FF82C774\n"


    "loc_FF82C5C0:\n"    // CODE XREF: sub_FF82C3F0+1B4j
        "     B         loc_FF82C774\n"


    "loc_FF82C5C4:\n"    // CODE XREF: sub_FF82C3F0+1A4j
        "     SUB     R12, R5, #0x2000\n"
        "     SUBS    R12, R12, #2\n"
        "     BEQ     loc_FF82C8A8\n"
        "     CMP     R5, R9\n"
        "     MOV     R0, R9\n"
        "     BEQ     loc_FF82C8B4\n"
        "     SUB     R12, R5, #0x2000\n"
        "     SUBS    R12, R12, #5\n"
        "     BEQ     loc_FF82C8A8\n"
        "     SUB     R12, R5, #0x2000\n"
        "     SUBS    R12, R12, #0x19\n"
        "     BNE     loc_FF82C830\n"
        "     CMP     R1, #0\n"
        "     BNE     loc_FF82C894\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C600:\n"    // CODE XREF: sub_FF82C3F0+194j
        "     LDR     R12, =0x3110\n"
        "     CMP     R5, R12\n"
        "     BEQ     loc_FF82C86C\n"
        "     BGT     loc_FF82C648\n"
        "     SUB     R12, R5, #0x2000\n"
        "     SUBS    R12, R12, #0x1D\n"
        "     BEQ     loc_FF82C8A8\n"
        "     LDR     R0, =0x2027\n"
        "     CMP     R5, R0\n"
        "     BEQ     loc_FF82C874\n"
        "     SUB     R12, R5, #0x3000\n"
        "     SUBS    R12, R12, #6\n"
        "     BEQ     loc_FF82C86C\n"
        "     SUB     R12, R5, #0x3000\n"
        "     SUBS    R12, R12, #0x10\n"
        "     BNE     loc_FF82C830\n"
        "     BL         sub_FF88D5E4\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C648:\n"    // CODE XREF: sub_FF82C3F0+21Cj
        "     SUB     R12, R5, #0x3100\n"
        "     SUBS    R12, R12, #0x11\n"
        "     BEQ     loc_FF82C86C\n"
        "     CMP     R5, #0x3140\n"
        "     BEQ     loc_FF82C8D0\n"
        "     SUB     R12, R5, #0x3200\n"
        "     SUBS    R12, R12, #1\n"
        "     BEQ     loc_FF82C830\n"
        "     SUB     R12, R5, #0x3200\n"
        "     SUBS    R12, R12, #2\n"
        "     BNE     loc_FF82C830\n"
        "     B         loc_FF82C86C\n"





    "loc_FF82C6EC:\n"    // CODE XREF: sub_FF82C3F0+78j
        "     MOV     R4, #1\n"
        "     MOV     R0, #2\n"
        "     CMP     R0, #1\n"
        "     MOVEQ   R4, #2\n"
        "     MOV     R0, R4\n"
        "     BL         sub_FF8224B4\n"
        "     CMP     R0, #0\n"
        "     STRNE   R8, [R6,#0x14]\n"
        "     BNE     loc_FF82C74C\n"
        "     BL         sub_FF874AD4\n"
        "     BL         sub_FF871808\n"
        "     BL         sub_FF872390\n"
        "     BL         sub_FF8710D4\n"
        "     BL         sub_FF872BD4\n"
        "     BL         sub_FF873024\n"
        "     BL         _GetVRAMHPixelsSize_0\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF82C754\n"
        "     BL         sub_FF82C090\n"
        "     BL         sub_FF87340C\n"
        "     MOV     R1, R0\n"
        "     LDR     R0, =0x1167\n"
        "     BL         _PostLogicalEventToUI\n"    // "DryOS Canon Firmware; A720-based"

    "loc_FF82C74C:\n"    // CODE XREF: sub_FF82C3F0+320j

        "     MOV     R0, R7\n"

    "locret_FF82C750:\n"    // CODE XREF: sub_FF82C3F0+90j
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF82C754:\n"    // CODE XREF: sub_FF82C3F0+344j
        "     BL         sub_FF82622C\n"
        "     CMP     R0, #1\n"
        "     LDRNE   R0, =0x310B\n"
        "     LDREQ   R0, =0x310C\n"
        "     MOV     R1, #0\n"
        "     BL         _PostLogicalEventToUI\n"    // "DryOS Canon Firmware; A720-based"
        "     BL         sub_FF870B0C_my\n"    //   ---------------> for SDHC and movie rec
        "     B         loc_FF82C74C\n"


    "loc_FF82C774:\n"    // CODE XREF: sub_FF82C3F0+1B4j


        "     STR     R8, [R6,#0x10]\n"
        "     LDR     R6, =0x4508\n"
        "     LDR     R4, =0x1168\n"
        "     CMP     R1, #0\n"
        "     BEQ     loc_FF82C79C\n"
        "     BL         sub_FF86E480\n"
        "     B         loc_FF82C7A8\n"


    "loc_FF82C790:\n"    // CODE XREF: sub_FF82C3F0+3BCj
        "     MOV     R0, R6\n"
        "     BL         sub_FF8595B4\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C79C:\n"    // CODE XREF: sub_FF82C3F0+394j
        "     BL         sub_FF871AB0\n"
        "     BL         sub_FF871A14\n"
        "     BL         sub_FF825F4C\n"

    "loc_FF82C7A8:\n"    // CODE XREF: sub_FF82C3F0+39Cj
        "     CMP     R5, R4\n"
        "     BEQ     loc_FF82C790\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C7B4:\n"    // CODE XREF: sub_FF82C3F0+1A0j
        "     MOV     R0, #1\n"
        "     BL         sub_FF86E5AC\n"
        "     MOV     R1, R11\n"
        "     MOV     R0, R10\n"
        "     B         loc_FF82C838\n"


    "loc_FF82C7C8:\n"    // CODE XREF: sub_FF82C3F0+190j
        "     CMP     R2, #1\n"
        "     BNE     loc_FF82C86C\n"
        "     BL         sub_FF86E480\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C7D8:\n"    // CODE XREF: sub_FF82C3F0+1B4j


        "     MOV     R0, #2\n"
        "     B         loc_FF82C7E4\n"


    "loc_FF82C7E0:\n"    // CODE XREF: sub_FF82C3F0+1B4j


        "     MOV     R0, #1\n"

    "loc_FF82C7E4:\n"    // CODE XREF: sub_FF82C3F0+3ECj

        "     BL         sub_FF82CE18\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C7EC:\n"    // CODE XREF: sub_FF82C3F0+1B4j


        "     MOV     R0, #0\n"
        "     B         loc_FF82C7E4\n"


    "loc_FF82C7F4:\n"    // CODE XREF: sub_FF82C3F0+68j

        "     LDR     R0, [R6,#0xC]\n"
        "     SUB     R12, R0, #0x8000\n"
        "     SUBS    R12, R12, #2\n"
        "     BEQ     loc_FF82C814\n"
        "     LDR     R0, =0x10A5\n"
        "     BL         _IsControlEventActive\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF82C81C\n"

    "loc_FF82C814:\n"    // CODE XREF: sub_FF82C3F0+20j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF82C81C:\n"    // CODE XREF: sub_FF82C3F0+420j
        "     CMP     R5, R9\n"
        "     STREQ   R8, [R6,#0x34]\n"
        "     BEQ     loc_FF82C830\n"
        "     CMP     R5, R10\n"
        "     STREQ   R8, [R6,#0x30]\n"

    "loc_FF82C830:\n"    // CODE XREF: sub_FF82C3F0+84j



        "     MOV     R1, #0\n"

    "loc_FF82C834:\n"    // CODE XREF: sub_FF82C3F0+480j
        "     MOV     R0, R5\n"

    "loc_FF82C838:\n"    // CODE XREF: sub_FF82C3F0+C0j

        "     BL         sub_FF86FB00_my\n"    //   ---------------> for SDHC and movie rec
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF82C840:\n"    // CODE XREF: sub_FF82C3F0+38j
        "     BL         sub_FF876BDC\n"
        "     CMP     R0, #0\n"
        "     BLNE    sub_FF875AB8\n"
        "     B         loc_FF82C86C\n"


    "loc_FF82C850:\n"    // CODE XREF: sub_FF82C3F0+11Cj
        "     BL         _IsControlEventActive\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF82C814\n"

    "loc_FF82C85C:\n"    // CODE XREF: sub_FF82C3F0+F4j

        "     MOV     R0, R5\n"
        "     BL         sub_FF82C1B0_my\n"    //   ---------------> for movie rec
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF82C868:\n"    // CODE XREF: sub_FF82C3F0+134j

        "     BL         sub_FF82CDE8\n"

    "loc_FF82C86C:\n"    // CODE XREF: sub_FF82C3F0+54j

        "     MOV     R1, R4\n"
        "     B         loc_FF82C834\n"


    "loc_FF82C874:\n"    // CODE XREF: sub_FF82C3F0+234j
        "     MOV     R1, #0\n"
        "     BL         sub_FF86FB00_my\n"    //   ---------------> for SDHC and movie rec
        "     MOV     R1, #0\n"
        "     MOV     R0, R11\n"
        "     BL         sub_FF86FB00_my\n"    //   ---------------> for SDHC and movie rec
        "     MOV     R1, #0\n"
        "     MOV     R0, R9\n"
        "     B         loc_FF82C8A0\n"


    "loc_FF82C894:\n"    // CODE XREF: sub_FF82C3F0+208j
        "     CMP     R2, #0\n"
        "     BNE     loc_FF82C814\n"

    "loc_FF82C89C:\n"    // CODE XREF: sub_FF82C3F0+4F0j
        "     MOV     R1, #0\n"

    "loc_FF82C8A0:\n"    // CODE XREF: sub_FF82C3F0+4A0j
        "     BL         sub_FF86FB00_my\n"    //   ---------------> for SDHC and movie rec
        "     B         loc_FF82C814\n"


    "loc_FF82C8A8:\n"    // CODE XREF: sub_FF82C3F0+1DCj

        "     STR     R7, [R6,#0x20]\n"
        "     BL         sub_FF82CADC\n"
        "     B         loc_FF82C86C\n"


    "loc_FF82C8B4:\n"    // CODE XREF: sub_FF82C3F0+1E8j
        "     STR     R7, [R6,#0x20]\n"
        "     BL         sub_FF82CADC\n"
        "     LDR     R0, [R6,#0x10]\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF82C86C\n"
        "     BL         sub_FF86E4C4\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C8D0:\n"    // CODE XREF: sub_FF82C3F0+268j
        "     CMP     R1, #0\n"
        "     BLEQ    sub_FF82CADC\n"
        "     B         loc_FF82C814\n"


    "loc_FF82C8DC:\n"    // CODE XREF: sub_FF82C3F0+48j

        "     MOV    R0, #0xFFFFFFFF\n"
        "     B         loc_FF82C89C\n"
        ".LTORG\n" // make literal pool
    );
}


// Extracted method: sub_FF870B0C (FF870B0C-FF870BF0)
// Overridden calls:
//     sub_FF870958
//     sub_FF870958
void __attribute__((naked,noinline)) sub_FF870B0C_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     BL         sub_FF82CAA8\n"
        "     MOV     R4, R0\n"
        "     BL         sub_FF870C28\n"
        "     MOV     R0, R4\n"
        "     BL         sub_FF8709BC\n"
        "     BL         sub_FF82CAA8\n"
        "     MOV     R4, R0\n"
        "     LDR     R0, =0x5E1C\n"
        "     LDR     R0, [R0]\n"
        "     TST     R0, #1\n"
        "     BEQ     loc_FF870B48\n"

    "loc_FF870B3C:\n"    // CODE XREF: sub_FF870B0C+5Cj

        "     MOV     R1, R4\n"
        "     MOV     R0, #2\n"
        "     B         loc_FF870BB0\n"


    "loc_FF870B48:\n"    // CODE XREF: sub_FF870B0C+2Cj
        "     TST     R0, #0x2000\n"
        "     BEQ     loc_FF870B64\n"
        "     TST     R0, #0x200\n"
        "     LDREQ   R1, =0x4004\n"
        "     LDRNE   R1, =0x8002\n"
        "     MOV     R0, #3\n"
        "     B         loc_FF870BB0\n"


    "loc_FF870B64:\n"    // CODE XREF: sub_FF870B0C+40j
        "     TST     R0, #0x10\n"
        "     BNE     loc_FF870B3C\n"
        "     TST     R0, #0x40\n"
        "     BEQ     loc_FF870B80\n"

    "loc_FF870B74:\n"    // CODE XREF: sub_FF870B0C+BCj
        "     MOV     R1, R4\n"
        "     MOV     R0, #1\n"
        "     B         loc_FF870BB0\n"


    "loc_FF870B80:\n"    // CODE XREF: sub_FF870B0C+64j
        "     TST     R0, #0x20\n"
        "     BEQ     loc_FF870B9C\n"
        "     TST     R0, #0x4000\n"
        "     BNE     loc_FF870B9C\n"

    "loc_FF870B90:\n"    // CODE XREF: sub_FF870B0C+C8j
        "     MOV     R1, R4\n"
        "     MOV     R0, #0\n"
        "     B         loc_FF870BB0\n"


    "loc_FF870B9C:\n"    // CODE XREF: sub_FF870B0C+78j

        "     LDR     R1, =0x102\n"
        "     BICS    R1, R1, R0\n"
        "     BNE     loc_FF870BB8\n"
        "     MOV     R1, R4\n"
        "     MOV     R0, #6\n"

    "loc_FF870BB0:\n"    // CODE XREF: sub_FF870B0C+38j

        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF870958_my\n"    //   ---------------> for SDHC and movie rec


    "loc_FF870BB8:\n"    // CODE XREF: sub_FF870B0C+98j
        "     TST     R0, #0x100\n"
        "     BNE     loc_FF870B3C\n"
        "     TST     R0, #0x4000\n"
        "     TSTEQ   R0, #0x400\n"
        "     BNE     loc_FF870B74\n"
        "     TST     R0, #0x200\n"
        "     TSTEQ   R0, #2\n"
        "     BNE     loc_FF870B90\n"
        "     TST     R0, #0x40000\n"
        "     BEQ     loc_FF870B3C\n"
        "     TST     R0, #0x200000\n"
        "     MOVEQ   R1, R4\n"
        "     MOVEQ   R0, #1\n"
        "     BLEQ    sub_FF870958_my\n"    //   ---------------> for SDHC and movie rec
        "     B         loc_FF870B3C\n"
    );
}


// Extracted method: sub_FF870958 (FF870958-FF8709B8)
// Overridden calls:
//     sub_FF86FB00
//     sub_FF86FB00
void __attribute__((naked,noinline)) sub_FF870958_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R6,LR}\n"
        "     MOVS    R4, R0\n"
        "     MOV     R0, #1\n"
        "     MOV     R5, R1\n"
        "     BNE     loc_FF870998\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF86DC48\n"
        "     BL         sub_FF82CAA8\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x5B\n"
        "     BNE     loc_FF870990\n"

    "loc_FF870988:\n"    // CODE XREF: sub_FF870958+44j
        "     BL         sub_FF8708A0\n"
        "     B         loc_FF8709A0\n"


    "loc_FF870990:\n"    // CODE XREF: sub_FF870958+2Cj
        "     BL         sub_FF8708E0\n"
        "     B         loc_FF8709A0\n"


    "loc_FF870998:\n"    // CODE XREF: sub_FF870958+10j
        "     CMP     R4, #5\n"
        "     BEQ     loc_FF870988\n"

    "loc_FF8709A0:\n"    // CODE XREF: sub_FF870958+34j

        "     CMP     R0, #0\n"
        "     LDREQ   R5, =0x1162\n"
        "     MOVEQ   R4, #2\n"
        "     MOV     R0, R4\n"
        "     MOV     R1, R5\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF86FB00_my\n"    //   ---------------> for SDHC and movie rec
    );
}


// Extracted method: sub_FF86FB00 (FF86FB00-FF86FDFC)
// Overridden calls:
//     sub_FF82BE84
//     sub_FF86E38C
//     sub_FF86EDAC
//     sub_FF86EE0C
//     sub_FF86EFE4
//     sub_FF86F224
//     sub_FF86F5E8
//     sub_FF86F6F0
//     sub_FF86F89C
//     sub_FF86F9F8
//     sub_FF870430
//     sub_FF870468
//     sub_FF870550
//     sub_FF870694
//     sub_FF86F224
//     sub_FF870550
//     sub_FF86F6F0
//     sub_FF86EE0C
//     sub_FF870468
//     sub_FF86EFE4
//     sub_FF86F89C
//     sub_FF86F9F8
//     sub_FF870694
//     sub_FF86F5E8
void __attribute__((naked,noinline)) sub_FF86FB00_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R8,LR}\n"
        "     MOV     R8, R1\n"
        "     MOV     R4, R0\n"
        "     BL         _GetVRAMHPixelsSize_0\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86FDF8\n"
        "     MOV     R1, R8\n"
        "     MOV     R0, R4\n"
        "     BL         sub_FF86E768\n"
        "     LDR     R5, =0x5D50\n"
        "     MOV     R7, #1\n"
        "     LDR     R0, [R5,#0x10]\n"
        "     MOV     R6, #0\n"
        "     CMP     R0, #0x16\n"
        "     ADDLS   PC, PC, R0,LSL#2\n"
        "     B         loc_FF86FDF8\n"


    "loc_FF86FB40:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FB9C\n"


    "loc_FF86FB44:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FBC4\n"


    "loc_FF86FB48:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FC08\n"


    "loc_FF86FB4C:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FCC8\n"


    "loc_FF86FB50:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FCD8\n"


    "loc_FF86FB54:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FDF8\n"


    "loc_FF86FB58:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FDF8\n"


    "loc_FF86FB5C:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FD54\n"


    "loc_FF86FB60:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FBAC\n"


    "loc_FF86FB64:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FBB8\n"


    "loc_FF86FB68:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FD54\n"


    "loc_FF86FB6C:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FBFC\n"


    "loc_FF86FB70:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FDF8\n"


    "loc_FF86FB74:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FDF8\n"


    "loc_FF86FB78:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FC14\n"


    "loc_FF86FB7C:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FC5C\n"


    "loc_FF86FB80:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FC94\n"


    "loc_FF86FB84:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FBD0\n"


    "loc_FF86FB88:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FDE0\n"


    "loc_FF86FB8C:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FD60\n"


    "loc_FF86FB90:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FD90\n"


    "loc_FF86FB94:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FD90\n"


    "loc_FF86FB98:\n"    // CODE XREF: sub_FF86FB00+38j
        "     B         loc_FF86FCE4\n"


    "loc_FF86FB9C:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R1, R8\n"
        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF86F224_my\n"    //   --------------->


    "loc_FF86FBAC:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF870550_my\n"    //   --------------->


    "loc_FF86FBB8:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF86F6F0_my\n"    //   --------------->


    "loc_FF86FBC4:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF86EE0C_my\n"    //   --------------->


    "loc_FF86FBD0:\n"    // CODE XREF: sub_FF86FB00+38j


        "     SUB     R12, R4, #0x1000\n"
        "     SUBS    R12, R12, #0xA5\n"
        "     STREQ   R7, [R5,#0x88]\n"
        "     BEQ     loc_FF86FDF0\n"
        "     SUB     R12, R4, #0x3000\n"
        "     SUBS    R12, R12, #6\n"
        "     BNE     loc_FF86FDF8\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF82BF28\n"
        "     BL         sub_FF870430_my\n"    //   --------------->
        "     B         loc_FF86FDF0\n"


    "loc_FF86FBFC:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF870468_my\n"    //   --------------->


    "loc_FF86FC08:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF86EFE4_my\n"    //   --------------->


    "loc_FF86FC14:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF86F89C_my\n"    //   --------------->





    "loc_FF86FC5C:\n"    // CODE XREF: sub_FF86FB00+38j


        "     SUB     R12, R4, #0x3200\n"
        "     SUBS    R12, R12, #2\n"
        "     BNE     loc_FF86FDF8\n"
        "     MOV     R0, #3\n"
        "     BL         sub_FF86E64C\n"
        "     MOV     R0, #8\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     MOV     R1, #0\n"
        "     MOV     R0, #0x19\n"
        "     BL         sub_FF83A068\n"
        "     BL         sub_FF871AB0\n"
        "     BL         sub_FF871D48\n"
        "     BL         sub_FF871144\n"
        "     B         loc_FF86FDF0\n"


    "loc_FF86FC94:\n"    // CODE XREF: sub_FF86FB00+38j


        "     SUB     R12, R4, #0x3300\n"
        "     SUBS    R12, R12, #1\n"
        "     BNE     loc_FF86FDF8\n"
        "     LDR     R0, =0x4010\n"
        "     STR     R6, [R5,#0x80]\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     BL         sub_FF98BE68\n"
        "     BL         sub_FF871144\n"
        "     MOV     R0, #4\n"
        "     BL         sub_FF86E64C\n"
        "     MOV     R0, #1\n"
        "     BL         sub_FF872CA8\n"
        "     B         loc_FF86FDF0\n"


    "loc_FF86FCC8:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R1, R8\n"
        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF86F9F8_my\n"    //   --------------->


    "loc_FF86FCD8:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF870694_my\n"    //   --------------->


    "loc_FF86FCE4:\n"    // CODE XREF: sub_FF86FB00+38j


        "     LDR     R8, =0x1182\n"
        "     CMP     R4, R8\n"
        "     STREQ   R7, [R5,#0xB8]\n"
        "     BEQ     loc_FF86FDF0\n"
        "     SUB     R12, R4, #0x1000\n"
        "     SUBS    R12, R12, #0x1AC\n"
        "     BEQ     loc_FF86FD3C\n"
        "     SUB     R12, R4, #0x3000\n"
        "     SUBS    R12, R12, #0x224\n"
        "     BNE     loc_FF86FDF8\n"
        "     MOV     R0, #8\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     MOV     R0, #3\n"
        "     BL         sub_FF86E64C\n"
        "     STR     R6, [R5,#0xBC]\n"
        "     LDR     R0, [R5,#0xB8]\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R1, #0\n"
        "     MOVNE   R0, R8\n"
        "     STRNE   R6, [R5,#0xB8]\n"
        "     BLNE    sub_FF86F9F8_my\n"    //   --------------->
        "     B         loc_FF86FDF0\n"


    "loc_FF86FD3C:\n"    // CODE XREF: sub_FF86FB00+1FCj
        "     LDR     R0, [R5,#0xBC]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86FDF0\n"
        "     BL         sub_FF989F50\n"
        "     STR     R7, [R5,#0xBC]\n"
        "     B         loc_FF86FDF0\n"


    "loc_FF86FD54:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF86F5E8_my\n"    //   --------------->


    "loc_FF86FD60:\n"    // CODE XREF: sub_FF86FB00+38j


        "     LDR     R12, =0x10B0\n"
        "     CMP     R4, R12\n"
        "     BEQ     loc_FF86FD8C\n"
        "     BGT     loc_FF86FD98\n"
        "     CMP     R4, #4\n"
        "     BEQ     loc_FF86FDC0\n"
        "     SUB     R12, R4, #0x1000\n"
        "     SUBS    R12, R12, #0xAA\n"
        "     SUBNE   R12, R4, #0x1000\n"
        "     SUBNES  R12, R12, #0xAE\n"
        "     BNE     loc_FF86FDF8\n"

    "loc_FF86FD8C:\n"    // CODE XREF: sub_FF86FB00+268j
        "     BL         sub_FF86E350\n"

    "loc_FF86FD90:\n"    // CODE XREF: sub_FF86FB00+38j


        "     MOV     R0, R6\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"


    "loc_FF86FD98:\n"    // CODE XREF: sub_FF86FB00+26Cj
        "     SUB     R12, R4, #0x2000\n"
        "     SUBS    R12, R12, #4\n"
        "     BEQ     loc_FF86FDD8\n"
        "     SUB     R12, R4, #0x5000\n"
        "     SUBS    R12, R12, #1\n"
        "     SUBNE   R12, R4, #0x5000\n"
        "     SUBNES  R12, R12, #6\n"
        "     BNE     loc_FF86FDF8\n"
        "     BL         sub_FF86EDAC_my\n"    //   --------------->
        "     B         loc_FF86FDF0\n"


    "loc_FF86FDC0:\n"    // CODE XREF: sub_FF86FB00+274j
        "     LDR     R0, [R5,#0x2C]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86FDD8\n"
        "     BL         sub_FF86FFD8\n"
        "     BL         sub_FF825F04\n"
        "     B         loc_FF86FDF0\n"


    "loc_FF86FDD8:\n"    // CODE XREF: sub_FF86FB00+2A0j

        "     BL         sub_FF86E38C_my\n"    //   --------------->
        "     B         loc_FF86FDF0\n"


    "loc_FF86FDE0:\n"    // CODE XREF: sub_FF86FB00+38j


        "     SUB     R12, R4, #0x3000\n"
        "     SUBS    R12, R12, #0x130\n"
        "     BNE     loc_FF86FDF8\n"
        "     BL         sub_FF86E44C\n"

    "loc_FF86FDF0:\n"    // CODE XREF: sub_FF86FB00+DCj

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"


    "loc_FF86FDF8:\n"    // CODE XREF: sub_FF86FB00+14j



        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"
        ".LTORG\n" // make literal pool
    );
}


// Extracted method: sub_FF86F224 (FF86F224-FF86F424)
// Overridden calls:
//     sub_FF82BE84
//     sub_FF86ED10
void __attribute__((naked,noinline)) sub_FF86F224_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R8,LR}\n"
        "     LDR     R7, =0x8002\n"
        "     LDR     R4, =0x5D50\n"
        "     CMP     R0, #3\n"
        "     MOV     R6, R1\n"
        "     MOV     R5, #1\n"
        "     BEQ     loc_FF86F398\n"
        "     BGT     loc_FF86F260\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86F2A4\n"
        "     CMP     R0, #1\n"
        "     BEQ     loc_FF86F328\n"
        "     CMP     R0, #2\n"
        "     BNE     loc_FF86F420\n"
        "     B         loc_FF86F278\n"


    "loc_FF86F260:\n"    // CODE XREF: sub_FF86F224+1Cj
        "     CMP     R0, #6\n"
        "     STREQ   R5, [R4,#0x28]\n"
        "     BEQ     loc_FF86F390\n"
        "     SUB     R12, R0, #0x2000\n"
        "     SUBS    R12, R12, #4\n"
        "     BNE     loc_FF86F420\n"

    "loc_FF86F278:\n"    // CODE XREF: sub_FF86F224+38j
        "     SUB     R12, R6, #0x1100\n"
        "     SUBS    R12, R12, #0x62\n"
        "     BNE     loc_FF86F294\n"
        "     MOV     R1, R7\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF872404\n"
        "     STR     R5, [R4,#0x60]\n"

    "loc_FF86F294:\n"    // CODE XREF: sub_FF86F224+5Cj
        "     BL         sub_FF871AB0\n"
        "     BL         sub_FF871D48\n"
        "     BL         sub_FF86ED10_my\n"    //   ---------------> movie rec
        "     B         loc_FF86F418\n"


    "loc_FF86F2A4:\n"    // CODE XREF: sub_FF86F224+24j
        "     MOV     R0, #7\n"
        "     BL         sub_FF86E64C\n"
        "     MOV     R0, R7\n"
        "     BL         sub_FF82BE84_my\n"    //   ---------------> movie rec
        "     BL         _taskcreate_CommonDrivers\n"
        "     BL         sub_FF871908\n"
        "     MOV     R1, R7\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF872404\n"
        "     LDR     R1, =0xFF86F458\n"    // aAcBootrec = "AC:BootRec"
        "     MOV     R0, #0x20\n"
        "     STR     R6, [R4,#0x18]\n"
        "     BL         sub_FF867708\n"
        "     LDR     R1, =0xFF86F464\n"    // aAcInitlens = "AC:InitLens"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     STR     R5, [R4,#0x28]\n"
        "     BL         sub_FF82BFFC\n"
        "     BL         sub_FF82BF50\n"
        "     LDR     R0, [R4,#0x1C]\n"
        "     LDR     R1, [R4,#0x20]\n"
        "     ORRS    R0, R0, R1\n"
        "     BLNE    sub_FF86FFB4\n"
        "     LDR     R0, [R4,#0x68]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F314\n"
        "     BL         _taskcreate_StartupImage\n"
        "     B         loc_FF86F31C\n"


    "loc_FF86F314:\n"    // CODE XREF: sub_FF86F224+E4j
        "     BL         sub_FF825C94\n"
        "     BL         sub_FF82CA40\n"

    "loc_FF86F31C:\n"    // CODE XREF: sub_FF86F224+ECj
        "     BL         taskcreate_InitFileModules_my\n"  //  ------------->
        "     BL         sub_FF870DB0\n"
        "     B         loc_FF86F418\n"


    "loc_FF86F328:\n"    // CODE XREF: sub_FF86F224+2Cj
        "     MOV     R0, #8\n"
        "     BL         sub_FF86E64C\n"
        "     BL         _taskcreate_CommonDrivers\n"
        "     BL         sub_FF871908\n"
        "     LDR     R5, =0x4004\n"
        "     MOV     R0, #0\n"
        "     MOV     R1, R5\n"
        "     BL         sub_FF872404\n"
        "     LDR     R1, =0xFF86F474\n"    // aAcBootpb = "AC:BootPB"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         taskcreate_InitFileModules_my\n"  //  ------------->
        "     BL         sub_FF870E44\n"
        "     BL         sub_FF82CA04\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF82BE84_my\n"    //   ---------------> movie rec
        "     LDR     R0, [R4,#0x68]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F37C\n"
        "     BL         _taskcreate_StartupImage\n"
        "     B         loc_FF86F380\n"


    "loc_FF86F37C:\n"    // CODE XREF: sub_FF86F224+14Cj
        "     BL         sub_FF825C94\n"

    "loc_FF86F380:\n"    // CODE XREF: sub_FF86F224+154j
        "     BL         sub_FF870DE0\n"
        "     LDR     R0, [R4,#0x30]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86F418\n"

    "loc_FF86F390:\n"    // CODE XREF: sub_FF86F224+44j
        "     BL         sub_FF86FFFC\n"
        "     B         loc_FF86F418\n"


    "loc_FF86F398:\n"    // CODE XREF: sub_FF86F224+18j
        "     MOV     R1, R6\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF872404\n"
        "     LDR     R1, =0xFF86F480\n"    // aAcBootclock = "AC:BootClock"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     STR     R5, [R4,#0x68]\n"
        "     BL         sub_FF870E44\n"
        "     BL         sub_FF82CA04\n"
        "     BL         sub_FF86FF90\n"
        "     BL         sub_FF82CA9C\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, =0x804B\n"
        "     MOVNE   R1, #0\n"
        "     BLNE    _j_PTM_SetCurrentItem\n"
        "     BL         sub_FF872284\n"
        "     MOV     R0, #0x80\n"
        "     BL         sub_FF82BE84_my\n"    //   ---------------> movie rec
        "     BL         sub_FF871C90\n"
        "     BL         _StartGUISystem\n"
        "     BL         sub_FF944944\n"
        "     BL         sub_FF98ECE8\n"
        "     BL         sub_FF871630\n"
        "     BL         sub_FF871AE8\n"
        "     MOV     R0, #9\n"
        "     BL         sub_FF86E64C\n"
        "     LDR     R0, =0x300E\n"
        "     MOV     R1, R6\n"
        "     BL         _PostLogicalEventToUI\n"    // "DryOS Canon Firmware; A720-based"
        "     MOV     R1, #0\n"
        "     MOV     R0, #1\n"
        "     BL         sub_FF872404\n"

    "loc_FF86F418:\n"    // CODE XREF: sub_FF86F224+7Cj

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"


    "loc_FF86F420:\n"    // CODE XREF: sub_FF86F224+34j

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"
    );
}






void __attribute__((naked,noinline)) taskcreate_InitFileModules_my() { //#fs
        asm volatile (

		"LDR     R0, =0x5E28\n"
		"STMFD   SP!, {R3,LR}\n"
		"LDR     R1, [R0,#4]\n"
		"CMP     R1, #0\n"
		"BNE     locret_FF870D70\n"
		"MOV     R1, #1\n"
		"STR     R1, [R0,#4]\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP]\n"
		"LDR     R3, =task_InitFileModules_my\n" // continue for SDHC-boot
		"MOV     R1, #0x19\n"
		"LDR     R0, =0xFF870E9C\n"  // aInitfilemodule
		"MOV     R2, #0x1000\n"
		"BL     _CreateTask\n"

	"locret_FF870D70:\n"
		"LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs  
        asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"BL      sub_FF869D00\n"
		"LDR     R5, =0x5006\n"
		"MOVS    R4, R0\n"
		"MOVNE   R1, #0\n"
		"MOVNE   R0, R5\n"
		"BLNE    _PostLogicalEventToUI \n" // "DryOS Canon Firmware; A720-based"
		"BL      sub_FF869D2C_my\n"  // continue to SDHC-hook here!
		"BL      core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask
		"CMP     R4, #0\n"
		"MOVEQ   R0, R5\n"
		"LDMEQFD SP!, {R4-R6,LR}\n"
		"MOVEQ   R1, #0\n"
		"BEQ     _PostLogicalEventToUI\n" // it's save to run this after spytask has started
		"LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF869D2C_my() { //#fs  
        asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL	sub_FF84D4A8_my\n" // continue to SDHC-hook here!
		"LDR	R4, =0x58A8\n"
		"LDR	R0, [R4,#4]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF869D5C\n"
		"BL	sub_FF879F20\n"
		"BL	sub_FF8FB3B0\n"
		"BL	sub_FF879F20\n"
		"BL	sub_FF907F04\n"
		"BL	sub_FF879F30\n"
		"BL	sub_FF8FB458\n"

	"loc_FF869D5C:\n"
		"MOV	R0, #1\n"
		"STR	R0, [R4]\n"
		"LDMFD	SP!, {R4,PC}\n"

        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF84D4A8_my() { //#fs  
        asm volatile (
		"STMFD	SP!, {R4-R6,LR}\n"
		"MOV	R6, #0\n"
		"MOV	R0, R6\n"
		"BL	sub_FF84D078\n"
		"LDR	R4, =0x125D4\n"
		"MOV	R5, #0\n"
		"LDR	R0, [R4,#0x38]\n"
		"BL	sub_FF84DA40\n"
		"CMP	R0, #0\n"
		"LDREQ	R0, =0x2B3C\n"
		"STREQ	R5, [R0,#0xC]\n"
		"STREQ	R5, [R0,#0x10]\n"
		"STREQ	R5, [R0,#0x14]\n"
		"MOV	R0, R6\n"
		"BL	sub_FF84D0B8\n" // uMounter (u=unknown, just to prevent misunderstandings)
		"MOV	R0, R6\n"
		"BL	sub_FF84D2E4_my\n" // continue to SDHC-hook here!
		"MOV	R5, R0\n"
		"MOV	R0, R6\n"
		"BL	sub_FF84D350\n"
		"LDR	R1, [R4,#0x3C]\n"
		"AND	R2, R5,	R0\n"
		"CMP	R1, #0\n"
		"MOV	R0, #0\n"
		"MOVEQ	R0, #0x80000001\n"
		"BEQ	loc_FF84D53C\n"
		"LDR	R3, [R4,#0x2C]\n"
		"CMP	R3, #2\n"
		"MOVEQ	R0, #4\n"
		"CMP	R1, #5\n"
		"ORRNE	R0, R0,	#1\n"
		"BICEQ	R0, R0,	#1\n"
		"CMP	R2, #0\n"
		"BICEQ	R0, R0,	#2\n"
		"ORREQ	R0, R0,	#0x80000000\n"
		"BICNE	R0, R0,	#0x80000000\n"
		"ORRNE	R0, R0,	#2\n"

	"loc_FF84D53C:\n"
		"STR	R0, [R4,#0x40]\n"
		"LDMFD	SP!, {R4-R6,PC}\n"

        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF84D2E4_my() { //#fs  
        asm volatile (
		"STMFD	SP!, {R4-R6,LR}\n"
		"LDR	R5, =0x2B3C\n"
		"MOV	R6, R0\n"
		"LDR	R0, [R5,#0x10]\n"
		"CMP	R0, #0\n"
		"MOVNE	R0, #1\n"
		"LDMNEFD	SP!, {R4-R6,PC}\n"
		"MOV	R0, #0x17\n"
		"MUL	R1, R0,	R6\n"
		"LDR	R0, =0x125D4\n"
		"ADD	R4, R0,	R1,LSL#2\n"
		"LDR	R0, [R4,#0x38]\n"
		"MOV	R1, R6\n"
		"BL	sub_FF84D17C_my\n"  // continue to SDHC-hook here
		"CMP	R0, #0\n"
		"LDMEQFD	SP!, {R4-R6,PC}\n"
		"LDR	R0, [R4,#0x38]\n"
		"MOV	R1, R6\n"
		"BL	sub_FF84DB58\n"
		"CMP	R0, #0\n"
		"LDMEQFD	SP!, {R4-R6,PC}\n"
		"MOV	R0, R6\n"
		"BL	sub_FF84CC98\n"
		"CMP	R0, #0\n"
		"MOVNE	R1, #1\n"
		"STRNE	R1, [R5,#0x10]\n"
		"LDMFD	SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF84D17C_my() { //#fs  ; Partition table parse takes place here. => SDHC-boot
        asm volatile (
		"STMFD	SP!, {R4-R8,LR}\n"
		"MOV	R8, R0\n"
		"MOV	R0, #0x17\n"
		"MUL	R1, R0,	R1\n"
		"LDR	R0, =0x125D4\n"
		"MOV	R6, #0\n"
		"ADD	R7, R0,	R1,LSL#2\n"
		"LDR	R0, [R7,#0x3C]\n"
		"MOV	R5, #0\n"
		"CMP	R0, #6\n"
		"ADDLS	PC, PC,	R0,LSL#2\n"
		"B	loc_FF84D2C8\n"

	"loc_FF84D1AC:\n"
		"B	loc_FF84D1E0\n"

	"loc_FF84D1B0:\n"
		"B	loc_FF84D1C8\n"

	"loc_FF84D1B4:\n"
		"B	loc_FF84D1C8\n"

	"loc_FF84D1B8:\n"
		"B	loc_FF84D1C8\n"

	"loc_FF84D1BC:\n"
		"B	loc_FF84D1C8\n"

	"loc_FF84D1C0:\n"
		"B	loc_FF84D2C0\n"

	"loc_FF84D1C4:\n"
		"B	loc_FF84D1C8\n"

	"loc_FF84D1C8:\n"
		"MOV	R2, #0\n"
		"MOV	R1, #0x200\n"
		"MOV	R0, #3\n"
		"BL	sub_FF8661D8\n"
		"MOVS	R4, R0\n"
		"BNE	loc_FF84D1E8\n"

	"loc_FF84D1E0:\n"
		"MOV	R0, #0\n"
		"LDMFD	SP!, {R4-R8,PC}\n"


	"loc_FF84D1E8:\n"
		"LDR	R12, [R7,#0x4C]\n"
		"MOV	R3, R4\n"
		"MOV	R2, #1\n"
		"MOV	R1, #0\n"
		"MOV	R0, R8\n"
        
		//"BLX     R12\n"       // !! Workaround !!
        "MOV     LR, PC\n"      // gcc won't compile "BLX R12" nor "BL R12".
        "MOV     PC, R12\n"     // workaround: make your own "BL" and hope we don't need the change to thumb-mode

		"CMP	R0, #1\n"
		"BNE	loc_FF84D214\n"
		"MOV	R0, #3\n"
		"BL	sub_FF866318\n"
		"B	loc_FF84D1E0\n"

	"loc_FF84D214:\n"
		"MOV	R0, R8\n"
		"BL	sub_FF9186B8\n" // Add FAT32 autodetect-code after this line

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
		"LDRB	R1, [R4,#0x1C9]\n" // Continue with firmware
		"LDRB	R3, [R4,#0x1C8]\n"
		"LDRB	R12, [R4,#0x1CC]\n"
		"MOV	R1, R1,LSL#24\n"
		"ORR	R1, R1,	R3,LSL#16\n"
		"LDRB	R3, [R4,#0x1C7]\n"
		"LDRB	R2, [R4,#0x1BE]\n"
		//"LDRB	LR, [R4,#0x1FF]\n"		// replaced, see below
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
		//"LDRB	R12, [R4,#0x1FE]\n"		// replaced, see below

		"LDRB    R12, [LR,#0x1FE]\n"            // New! First MBR signature byte (0x55)
		"LDRB    LR, [LR,#0x1FF]\n"             //      Last MBR signature byte (0xAA)

		"MOV	R4, #0\n"
		"BNE	loc_FF84D29C\n"
		"CMP	R0, R1\n"
		"BCC	loc_FF84D29C\n"
		"ADD	R2, R1,	R3\n"
		"CMP	R2, R0\n"
		"CMPLS	R12, #0x55\n"
		"CMPEQ	LR, #0xAA\n"
		"MOVEQ	R6, R1\n"
		"MOVEQ	R5, R3\n"
		"MOVEQ	R4, #1\n"

	"loc_FF84D29C:\n"
		"MOV	R0, #3\n"
		"BL	sub_FF866318\n"
		"CMP	R4, #0\n"
		"BNE	loc_FF84D2D4\n"
		"MOV	R6, #0\n"
		"MOV	R0, R8\n"
		"BL	sub_FF9186B8\n"
		"MOV	R5, R0\n"
		"B	loc_FF84D2D4\n"


	"loc_FF84D2C0:\n"
		"MOV	R5, #0x40\n"
		"B	loc_FF84D2D4\n"


	"loc_FF84D2C8:\n"
		"LDR	R1, =0x365\n"
		"LDR	R0, =0xFF84D170\n" // aMounter_c
		"BL	_DebugAssert\n"

	"loc_FF84D2D4:\n"
		"STR	R6, [R7,#0x44]!\n"
		"MOV	R0, #1\n"
		"STR	R5, [R7,#4]\n"
		"LDMFD	SP!, {R4-R8,PC}\n"

	);
}; //#fe
