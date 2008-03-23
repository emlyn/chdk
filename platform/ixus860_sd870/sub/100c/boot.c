#include "lolevel.h"
#include "platform.h"
#include "core.h"

const long new_sa = MEMISOSTART + MEMISOSIZE;

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

void __attribute__((naked,noinline)) task_Startup_my() { //#fs 
        asm volatile (
        	"STMFD	SP!, {R4,LR}	\n"
		"BL	sub_FF8151CC    \n"       //taskcreate_ClockSave
		"BL	sub_FF823FA8	\n"
		"BL	sub_FF820E84	\n"
		//"BL	j_nullsub_191	\n"
		"BL	sub_FF82BC5C	\n"
		//"BL	sub_FF82BB44	\n"       //StartDiskboot
        );

        CreateTask_spytask();

        asm volatile (
		"BL	sub_FF82BE24	\n"
		"BL	sub_FF82BCAC	\n"
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
		"BL	sub_FF82B828	\n"       //taskcreate_Bye
		"BL	sub_FF8228D8	\n"
		"BL	sub_FF822048    \n"       //taskcreate_TempCheck
		"BL	sub_FF82C8E4	\n"       // !!!divert for SDHC-bootdisk-support
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
// Required subs:
//   Startup -> FFC1C6C4 -> FFC1C294 ->           FFC5E6C0 -> uAC_Boot -> CreateTask_InitFileModules -> task_InitFileModules -> FFC5A4E8 -> FFC3F0CC -> FFC3EF08 -> FFC3EDA0
//                           \->FFC5F474 -> FFC5F410 ->/|
//                   -> StartFactoryModeController =>||
//
// uAC_Boot:                   FFC5E06C
// CreateTask_InitFileModules: FFC5F7A4 
// task_InitFileModules:       FFC5F754 

/*
void __attribute__((naked,noinline)) sub_FFC1C6C4_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC5CB64\n"
                "BL      sub_FFC3A27C\n"    // IsFactoryMode"
                "CMP     R0, #1\n"
                "BNE     loc_FFC1C6E4\n"
                "BL      sub_FFC5F8B0\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFC3A2BC\n"    // StartFactoryModeController"
                "loc_FFC1C6E4:\n"
                "BL      sub_FFC5E998\n"
                "LDR     R4, =0x1DCC\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "LDMNEFD SP!, {R4,PC}\n"
                "MOV     R1, #0\n"
                "LDR     R0, =sub_FFC1C294_my\n"        // continue here for SDHC-boot-support
                "BL      sub_FFC5AEA0\n"    // CreateController"
                "STR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC1C294_my() { //#fs  
        asm volatile (
                //"B sub_FFC1C294\n" // test: branch to original function
                "STMFD   SP!, {R3-R11,LR}\n"
                "LDR     R6, =0x1DCC\n"
                "MOV     R5, R3\n"
                "LDR     R0, [R6,#0x14]\n"
                "MOV     R4, R1\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC1C2B8\n"
                "BL      sub_FFC5D36C\n"
                "B       loc_FFC1C348\n"
        "loc_FFC1C2B8:\n"
                "LDR     R11, =0x1167\n"
                "MOV     R7, #0\n"
                "SUB     R12, R11, #5\n"
                "CMP     R4, R12\n"
                "MOV     R9, #1\n"
                "BEQ     loc_FFC1C5EC\n"
                "BGT     loc_FFC1C3E8\n"
                "LDR     R0, =0x1061\n"
                "ORR     R12, R0, R0,ASR#11\n"
                "CMP     R4, R12\n"
                "ADD     R1, R0, #4\n"
                "BEQ     loc_FFC1C684\n"
                "BGT     loc_FFC1C374\n"
                "LDR     R12, =0x1056\n"
                "CMP     R4, R12\n"
                "BEQ     loc_FFC1C684\n"
                "BGT     loc_FFC1C350\n"
                "SUB     R12, R4, #0x800\n"
                "SUBS    R12, R12, #3\n"
                "BEQ     loc_FFC1C508\n"
                "SUB     R12, R4, #0x800\n"
                "SUBS    R12, R12, #0x158\n"
                "BEQ     loc_FFC1C6A0\n"
                "SUB     R12, R4, #0x900\n"
                "SUBS    R12, R12, #0xA3\n"
                "SUBNE   R12, R4, #0x900\n"
                "SUBNES  R12, R12, #0xA5\n"
                "BNE     loc_FFC1C6BC\n"
                "LDR     R0, [R6,#0xC]\n"
                "SUB     R12, R0, #0x8000\n"
                "SUBS    R12, R12, #2\n"
                "BEQ     loc_FFC1C348\n"
                "LDR     R0, =0x10A5\n"
                "BL      sub_FFC5BC60\n"        // IsControlEventActive
                "CMP     R0, #0\n"
                "BEQ     loc_FFC1C6BC\n"
        "loc_FFC1C348:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
        "loc_FFC1C350:\n"
                "SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0x5B\n"
                "SUBNE   R12, R4, #0x1000\n"
                "SUBNES  R12, R12, #0x5E\n"
                "CMPNE   R4, R0\n"
                "SUBNE   R12, R4, #0x1000\n"
                "SUBNES  R12, R12, #0x62\n"
                "BNE     loc_FFC1C6BC\n"
                "B       loc_FFC1C684\n"
        "loc_FFC1C374:\n"
                "LDR     R12, =0x10AE\n"
                "CMP     R4, R12\n"
                "BEQ     loc_FFC1C620\n"
                "BGT     loc_FFC1C3B8\n"
                "CMP     R4, R1\n"
                "BEQ     loc_FFC1C684\n"
                "SUB     R12, R4, #0x1000\n"
                "LDR     R0, =0x10A3\n"
                "SUBS    R12, R12, #0xA9\n"
                "BEQ     loc_FFC1C5FC\n"
                "SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0xAA\n"
                "BEQ     loc_FFC1C614\n"
                "SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0xAD\n"
                "BNE     loc_FFC1C6BC\n"
                "B       loc_FFC1C608\n"
        "loc_FFC1C3B8:\n"
                "SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0xAF\n"
                "BEQ     loc_FFC1C608\n"
                "SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0xB0\n"
                "BEQ     loc_FFC1C620\n"
                "SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0xB2\n"
                "BNE     loc_FFC1C6BC\n"
                "LDR     R0, =0x1008\n"
                "MOV     R1, R5\n"
                "B       loc_FFC1C5E4\n"
        "loc_FFC1C3E8:\n"
                "LDR     R10, =0x201B\n"
                "LDR     R0, =0x1DCC\n"
                "CMP     R4, R10\n"
                "LDR     R2, [R0,#0x10]!\n"
                "LDR     R1, [R0,#0x10]\n"
                "SUB     R8, R10, #0x17\n"
                "BEQ     loc_FFC1C5C0\n"
                "BGT     loc_FFC1C4A4\n"
                "LDR     R10, =0x116A\n"
                "CMP     R4, R10\n"
                "BEQ     loc_FFC1C5AC\n"
                "BGT     loc_FFC1C460\n"
                "SUB     R12, R4, #0x1100\n"
                "SUBS    R12, R12, #0x63\n"
                "MOVEQ   R1, #0\n"
                "MOVEQ   R0, #0x82\n"
                "BEQ     loc_FFC1C5D8\n"
                "SUB     R12, R4, #0x1100\n"
                "SUBS    R12, R12, #0x65\n"
                "BEQ     loc_FFC1C5D0\n"
                "LDR     R5, =0x1168\n"
                "CMP     R4, R11\n"
                "CMPNE   R4, R5\n"
                "BNE     loc_FFC1C6BC\n"
                "STR     R9, [R6,#0x10]\n"
                "LDR     R6, =0x4508\n"
                "CMP     R1, #0\n"
                "BEQ     loc_FFC1C594\n"
                "BL      sub_FFC5D3A0\n"
                "B       loc_FFC1C5A0\n"
        "loc_FFC1C460:\n"
                "SUB     R12, R4, #0x2000\n"
                "SUBS    R12, R12, #2\n"
                "BEQ     loc_FFC1C650\n"
                "CMP     R4, R8\n"
                "MOV     R0, R8\n"
                "BEQ     loc_FFC1C65C\n"
                "SUB     R12, R4, #0x2000\n"
                "SUBS    R12, R12, #5\n"
                "BEQ     loc_FFC1C650\n"
                "SUB     R12, R4, #0x2000\n"
                "SUBS    R12, R12, #0x19\n"
                "BNE     loc_FFC1C6BC\n"
                "CMP     R1, #0\n"
                "BEQ     loc_FFC1C348\n"
                "CMP     R2, #0\n"
                "BNE     loc_FFC1C348\n"
                "B       loc_FFC1C698\n"
        "loc_FFC1C4A4:\n"
                "LDR     R12, =0x3111\n"
                "CMP     R4, R12\n"
                "BEQ     loc_FFC1C624\n"
                "BGT     loc_FFC1C4E4\n"
                "SUB     R12, R4, #0x2000\n"
                "SUBS    R12, R12, #0x1D\n"
                "BEQ     loc_FFC1C650\n"
                "LDR     R0, =0x2027\n"
                "CMP     R4, R0\n"
                "BEQ     loc_FFC1C62C\n"
                "SUB     R12, R4, #0x3000\n"
                "SUBS    R12, R12, #6\n"
                "SUBNE   R12, R4, #0x3000\n"
                "SUBNES  R12, R12, #0x110\n"
                "BNE     loc_FFC1C6BC\n"
                "B       loc_FFC1C624\n"
        "loc_FFC1C4E4:\n"
                "CMP     R4, #0x3140\n"
                "BEQ     loc_FFC1C678\n"
                "SUB     R12, R4, #0x3200\n"
                "SUBS    R12, R12, #1\n"
                "BEQ     loc_FFC1C6BC\n"
                "SUB     R12, R4, #0x3200\n"
                "SUBS    R12, R12, #2\n"
                "BNE     loc_FFC1C6BC\n"
                "B       loc_FFC1C624\n"
        "loc_FFC1C508:\n"
                "MOV     R4, #1\n"
                "MOV     R0, #2\n"
                "BL      sub_FFC5CBF8\n"
                "CMP     R0, #1\n"
                "MOVEQ   R4, #2\n"
                "MOV     R0, R4\n"
                "BL      sub_FFC124B4\n"        // uLoadTest1
                "CMP     R0, #0\n"
                "STRNE   R9, [R6,#0x14]\n"
                "BNE     loc_FFC1C560\n"
                "BL      sub_FFC620DC\n"
                "BL      sub_FFC600F8\n"
                "BL      sub_FFC60C54\n"
                "BL      sub_FFC5FB20\n"
                "BL      sub_FFC611F8\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC1C568\n"
                "BL      sub_FFC1BFB8\n"
                "BL      sub_FFC6115C\n"
                "MOV     R1, R0\n"
                "MOV     R0, R11\n"
                "BL      sub_FFC5B69C\n"
        "loc_FFC1C560:\n"
                "MOV     R0, R7\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
        "loc_FFC1C568:\n"
                "BL      sub_FFC16188\n"
                "CMP     R0, #1\n"
                "LDRNE   R0, =0x310B\n"
                "LDREQ   R0, =0x310C\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC5B69C\n"
                "BL      sub_FFC5F474_my\n"        // Continue here (possibility 1) for SDHC-boot
                "B       loc_FFC1C560\n"
        "loc_FFC1C588:\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC4A858\n"
                "B       loc_FFC1C348\n"
        "loc_FFC1C594:\n"
                "BL      sub_FFC6039C\n"
                "BL      sub_FFC60300\n"
                "BL      sub_FFC15EF0\n"
        "loc_FFC1C5A0:\n"
                "CMP     R4, R5\n"
                "BNE     loc_FFC1C348\n"
                "B       loc_FFC1C588\n"
        "loc_FFC1C5AC:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFC5D4CC\n"
                "LDR     R0, =0x1005\n"
                "MOV     R1, R10\n"
                "B       loc_FFC1C5E4\n"
        "loc_FFC1C5C0:\n"
                "CMP     R2, #1\n"
                "BNE     loc_FFC1C624\n"
                "BL      sub_FFC5D3A0\n"
                "B       loc_FFC1C348\n"
        "loc_FFC1C5D0:\n"
                "MOV     R1, #0\n"
                "MOV     R0, #0x83\n"
        "loc_FFC1C5D8:\n"
                "BL      sub_FFC60D1C\n"
                "B       loc_FFC1C348\n"
        "loc_FFC1C5E0:\n"
                "MOV     R0, R4\n"
        "loc_FFC1C5E4:\n"
                "BL      sub_FFC5E6C0_my\n"        // Continue here (possibility 2) for SDHC-boot
                "LDMFD   SP!, {R3-R11,PC}\n"
        "loc_FFC1C5EC:\n"
                "BL      sub_FFC64100\n"
                "CMP     R0, #0\n"
                "BLNE    sub_FFC63060\n"
                "B       loc_FFC1C624\n"
        "loc_FFC1C5FC:\n"
                "BL      sub_FFC5BC60\n"        // IsControlEventActive
                "CMP     R0, #0\n"
                "BNE     loc_FFC1C348\n"
        "loc_FFC1C608:\n"
                "MOV     R0, R4\n"
                "BL      sub_FFC1C084\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
        "loc_FFC1C614:\n"
                "BL      sub_FFC5BC60\n"        // IsControlEventActive
                "CMP     R0, #0\n"
                "BNE     loc_FFC1C348\n"
        "loc_FFC1C620:\n"
                "BL      sub_FFC1CAC0\n"
        "loc_FFC1C624:\n"
                "MOV     R1, R5\n"
                "B       loc_FFC1C5E0\n"
        "loc_FFC1C62C:\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC5E6C0_my\n"        // Continue here (possibility 2) for SDHC-boot
                "MOV     R1, #0\n"
                "MOV     R0, R10\n"
                "BL      sub_FFC5E6C0_my\n"        // Continue here (possibility 2) for SDHC-boot
                "MOV     R1, #0\n"
                "MOV     R0, R8\n"
        "loc_FFC1C648:\n"
                "BL      sub_FFC5E6C0_my\n"        // Continue here (possibility 2) for SDHC-boot
                "B       loc_FFC1C348\n"
        "loc_FFC1C650:\n"
                "STR     R7, [R6,#0x20]\n"
                "BL      sub_FFC1C888\n"
                "B       loc_FFC1C624\n"
        "loc_FFC1C65C:\n"
                "STR     R7, [R6,#0x20]\n"
                "BL      sub_FFC1C888\n"
                "LDR     R0, [R6,#0x10]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC1C624\n"
                "BL      sub_FFC5D3E4\n"
                "B       loc_FFC1C348\n"
        "loc_FFC1C678:\n"
                "CMP     R1, #0\n"
                "BLEQ    sub_FFC1C888\n"
                "B       loc_FFC1C348\n"
        "loc_FFC1C684:\n"
                "CMP     R4, R0\n"
                "BEQ     loc_FFC1C698\n"
                "CMP     R4, R1\n"
                "MVNNE   R0, #0\n"
                "MOVEQ   R0, R1\n"
        "loc_FFC1C698:\n"
                "MOV     R1, #0\n"
                "B       loc_FFC1C648\n"
        "loc_FFC1C6A0:\n"
                "TST     R5, #0x80000000\n"
                "MOVNE   R0, #1\n"
                "LDMNEFD SP!, {R3-R11,PC}\n"
                "BL      sub_FFC65400\n"
                "CMP     R0, #0\n"
                "BLEQ    sub_FFC18934\n"
                "B       loc_FFC1C348\n"
        "loc_FFC1C6BC:\n"
                "MOV     R1, #0\n"
                "B       loc_FFC1C5E0\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5F474_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC1C83C\n"
                "CMP     R0, #0\n"
                "LDRNE   R0, =0x1061\n"
                "BNE     loc_FFC5F49C\n"
                "BL      sub_FFC1C824\n"
                "CMP     R0, #0\n"
                "LDRNE   R0, =0x105B\n"
                "BNE     loc_FFC5F49C\n"
                "BL      sub_FFC1C854\n"
        "loc_FFC5F49C:\n"
                "MOV     R4, R0\n"
                "BL      sub_FFC5F608\n"
                "MOV     R0, R4\n"
                "BL      sub_FFC5F6A8\n"
                "BL      sub_FFC1C854\n"
                "MOV     R4, R0\n"
                "LDR     R0, =0x5AA8\n"
                "LDR     R0, [R0]\n"
                "TST     R0, #1\n"
                "TSTEQ   R0, #0x10\n"
                "BEQ     loc_FFC5F4D4\n"
        "loc_FFC5F4C8:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #2\n"
                "B       loc_FFC5F518\n"
        "loc_FFC5F4D4:\n"
                "TST     R0, #0x40\n"
                "BEQ     loc_FFC5F4E8\n"
        "loc_FFC5F4DC:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #1\n"
                "B       loc_FFC5F518\n"
        "loc_FFC5F4E8:\n"
                "TST     R0, #0x20\n"
                "BEQ     loc_FFC5F504\n"
                "TST     R0, #0x4000\n"
                "BNE     loc_FFC5F504\n"
        "loc_FFC5F4F8:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #0\n"
                "B       loc_FFC5F518\n"
        "loc_FFC5F504:\n"
                "LDR     R1, =0x102\n"
                "BICS    R1, R1, R0\n"
                "BNE     loc_FFC5F520\n"
                "MOV     R1, R4\n"
                "MOV     R0, #6\n"
        "loc_FFC5F518:\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFC5F410_my\n"        // cont. for SDHC-boot
        "loc_FFC5F520:\n"
                "TST     R0, #0x100\n"
                "BNE     loc_FFC5F4C8\n"
                "TST     R0, #0x400\n"
                "BNE     loc_FFC5F4DC\n"
                "TST     R0, #0x200\n"
                "TSTEQ   R0, #2\n"
                "BNE     loc_FFC5F4F8\n"
                "TST     R0, #0x40000\n"
                "BEQ     loc_FFC5F4C8\n"
                "TST     R0, #0x200000\n"
                "MOVEQ   R1, R4\n"
                "MOVEQ   R0, #1\n"
                "BLEQ    sub_FFC5F410_my\n"        // cont. for SDHC-boot
                "B       loc_FFC5F4C8\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5F410_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOVS    R4, R0\n"
                "MOV     R0, #1\n"
                "MOV     R5, R1\n"
                "BNE     loc_FFC5F450\n"
                "MOV     R1, #0\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC5CB88\n"
                "BL      sub_FFC1C854\n"
                "SUB     R12, R0, #0x1000\n"
                "SUBS    R12, R12, #0x5B\n"
                "BNE     loc_FFC5F448\n"
        "loc_FFC5F440:\n"
                "BL      sub_FFC5F338\n"
                "B       loc_FFC5F458\n"
        "loc_FFC5F448:\n"
                "BL      sub_FFC5F398\n"
                "B       loc_FFC5F458\n"
        "loc_FFC5F450:\n"
                "CMP     R4, #5\n"
                "BEQ     loc_FFC5F440\n"
        "loc_FFC5F458:\n"
                "CMP     R0, #0\n"
                "LDREQ   R5, =0x1162\n"
                "MOVEQ   R4, #2\n"
                "MOV     R0, R4\n"
                "MOV     R1, R5\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FFC5E6C0_my\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5E6C0_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R7, R1\n"
                "MOV     R6, R0\n"
                "BL      sub_FFC611F8\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5E990\n"
                "MOV     R1, R7\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC5D6D8\n"
                "LDR     R4, =0x59EC\n"
                "MOV     R5, #0\n"
                "LDR     R0, [R4,#0x10]\n"
                "CMP     R0, #0x16\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
                "B       loc_FFC5E990\n"
        "loc_FFC5E6FC:\n"
                "B       loc_FFC5E758\n"
        "loc_FFC5E700:\n"
                "B       loc_FFC5E774\n"
        "loc_FFC5E704:\n"
                "B       loc_FFC5E7A8\n"
        "loc_FFC5E708:\n"
                "B       loc_FFC5E858\n"
        "loc_FFC5E70C:\n"
                "B       loc_FFC5E868\n"
        "loc_FFC5E710:\n"
                "B       loc_FFC5E990\n"
        "loc_FFC5E714:\n"
                "B       loc_FFC5E990\n"
        "loc_FFC5E718:\n"
                "B       loc_FFC5E8EC\n"
        "loc_FFC5E71C:\n"
                "B       loc_FFC5E768\n"
        "loc_FFC5E720:\n"
                "B       loc_FFC5E990\n"
        "loc_FFC5E724:\n"
                "B       loc_FFC5E8EC\n"
        "loc_FFC5E728:\n"
                "B       loc_FFC5E79C\n"
        "loc_FFC5E72C:\n"
                "B       loc_FFC5E990\n"
        "loc_FFC5E730:\n"
                "B       loc_FFC5E990\n"
        "loc_FFC5E734:\n"
                "B       loc_FFC5E7B4\n"
        "loc_FFC5E738:\n"
                "B       loc_FFC5E7C0\n"
        "loc_FFC5E73C:\n"
                "B       loc_FFC5E830\n"
        "loc_FFC5E740:\n"
                "B       loc_FFC5E780\n"
        "loc_FFC5E744:\n"
                "B       loc_FFC5E978\n"
        "loc_FFC5E748:\n"
                "B       loc_FFC5E8F8\n"
        "loc_FFC5E74C:\n"
                "B       loc_FFC5E928\n"
        "loc_FFC5E750:\n"
                "B       loc_FFC5E928\n"
        "loc_FFC5E754:\n"
                "B       loc_FFC5E874\n"
        "loc_FFC5E758:\n"
                "MOV     R1, R7\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5E06C_my\n"    // uAC_Boot // divert for SDHC-boot
        "loc_FFC5E768:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5F030\n"
        "loc_FFC5E774:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5DD0C\n"
        "loc_FFC5E780:\n"
                "SUB     R12, R6, #0x3000\n"
                "SUBS    R12, R12, #6\n"
                "BNE     loc_FFC5E990\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC1BE50\n"
                "BL      sub_FFC5EED0\n"        // uAC_InitPB
                "B       loc_FFC5E988\n"
        "loc_FFC5E79C:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5EF64\n"
        "loc_FFC5E7A8:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5DE9C\n"
        "loc_FFC5E7B4:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5E460\n"
        "loc_FFC5E7C0:\n"
                "SUB     R12, R6, #0x3200\n"
                "SUBS    R12, R12, #2\n"
                "BNE     loc_FFC5E990\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC5D5B0\n"        // uCameraConState
                "MOV     R0, #8\n"
                "BL      sub_FFC1BDB8\n"
                "MOV     R1, #0\n"
                "MOV     R0, #0x19\n"
                "BL      sub_FFC2C874\n"
                "BL      sub_FFC6039C\n"
                "BL      sub_FFC60610\n"
                "BL      sub_FFC5FB90\n"
                "B       loc_FFC5E988\n"
                "\n"
        "loc_FFC5E830:\n"
                "SUB     R12, R6, #0x3300\n"
                "SUBS    R12, R12, #1\n"
                "BNE     loc_FFC5E990\n"
                "LDR     R0, =0x4010\n"
                "BL      sub_FFC1BDB8\n"
                "BL      sub_FFD51F70\n"
                "BL      sub_FFC5FB90\n"
                "MOV     R0, #4\n"
                "BL      sub_FFC5D5B0\n"        // uCameraConState
                "B       loc_FFC5E988\n"
        "loc_FFC5E858:\n"
                "MOV     R1, R7\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5E5BC\n"
        "loc_FFC5E868:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5F10C\n"
        "loc_FFC5E874:\n"
                "LDR     R7, =0x1182\n"
                "MOV     R0, R6\n"
                "CMP     R0, R7\n"
                "MOV     R6, #1\n"
                "STREQ   R6, [R4,#0xA8]\n"
                "BEQ     loc_FFC5E988\n"
                "SUB     R12, R0, #0x1000\n"
                "SUBS    R12, R12, #0x1AC\n"
                "BEQ     loc_FFC5E8D4\n"
                "SUB     R12, R0, #0x3000\n"
                "SUBS    R12, R12, #0x224\n"
                "BNE     loc_FFC5E990\n"
                "MOV     R0, #8\n"
                "BL      sub_FFC1BDB8\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC5D5B0\n"        // uCameraConState
                "STR     R5, [R4,#0xAC]\n"
                "LDR     R0, [R4,#0xA8]\n"
                "CMP     R0, #0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R7\n"
                "STRNE   R5, [R4,#0xA8]\n"
                "BLNE    sub_FFC5E5BC\n"
                "B       loc_FFC5E988\n"
        "loc_FFC5E8D4:\n"
                "LDR     R0, [R4,#0xAC]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5E988\n"
                "BL      sub_FFD500D0\n"
                "STR     R6, [R4,#0xAC]\n"
                "B       loc_FFC5E988\n"
        "loc_FFC5E8EC:\n"
                "MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC5E380\n"
        "loc_FFC5E8F8:\n"
                "LDR     R12, =0x10B0\n"
                "CMP     R6, R12\n"
                "BEQ     loc_FFC5E924\n"
                "BGT     loc_FFC5E930\n"
                "CMP     R6, #4\n"
                "BEQ     loc_FFC5E958\n"
                "SUB     R12, R6, #0x1000\n"
                "SUBS    R12, R12, #0xAA\n"
                "SUBNE   R12, R6, #0x1000\n"
                "SUBNES  R12, R12, #0xAE\n"
                "BNE     loc_FFC5E990\n"
        "loc_FFC5E924:\n"
                "BL      sub_FFC5D288\n"
        "loc_FFC5E928:\n"
                "MOV     R0, R5\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        "loc_FFC5E930:\n"
                "SUB     R12, R6, #0x2000\n"
                "SUBS    R12, R12, #4\n"
                "BEQ     loc_FFC5E970\n"
                "SUB     R12, R6, #0x5000\n"
                "SUBS    R12, R12, #1\n"
                "SUBNE   R12, R6, #0x5000\n"
                "SUBNES  R12, R12, #6\n"
                "BNE     loc_FFC5E990\n"
                "BL      sub_FFC5DC74\n"
                "B       loc_FFC5E988\n"
        "loc_FFC5E958:\n"
                "LDR     R0, [R4,#0x2C]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5E970\n"
                "BL      sub_FFC5EB30\n"
                "BL      sub_FFC15EA8\n"
                "B       loc_FFC5E988\n"
        "loc_FFC5E970:\n"
                "BL      sub_FFC5D2C4\n"
                "B       loc_FFC5E988\n"
        "loc_FFC5E978:\n"
                "SUB     R12, R6, #0x3000\n"
                "SUBS    R12, R12, #0x130\n"
                "BNE     loc_FFC5E990\n"
                "BL      sub_FFC5D36C\n"
        "loc_FFC5E988:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        "loc_FFC5E990:\n"
                "MOV     R0, #1\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5E06C_my() { //#fs  uAC_Boot
        asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R7, =0x8002\n"
                "LDR     R4, =0x59EC\n"
                "CMP     R0, #2\n"
                "MOV     R6, R1\n"
                "MOV     R5, #1\n"
                "BEQ     loc_FFC5E108\n"
                "BGT     loc_FFC5E0F0\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC5E134\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC5E1D8\n"
                "MOV     R0, #8\n"
                "BL      sub_FFC5D5B0\n"        // uCameraConState
                "BL      sub_FFC5F7E0\n"        // CreateTask_CommonDrivers
                "BL      sub_FFC601B4\n"        // uDispSwLock
                "LDR     R5, =0x4004\n"
                "MOV     R0, #0\n"
                "MOV     R1, R5\n"
                "BL      sub_FFC60D1C\n"
                "LDR     R1, =0xFFC5E33C\n"        // aAcBootpb\n"   // "AC:BootPB"
                "MOV     R0, #0x20\n"
                "BL      sub_FFC57EC4\n"        // qCameraLog
                "BL      sub_FFC5F7A4_my\n"        // CreateTask_InitFileModules
                "BL      sub_FFC5F8B0\n"
                "BL      sub_FFC1C7B4\n"
                "MOV     R0, R5\n"
                "BL      sub_FFC1BDB8\n"
                "LDR     R0, [R4,#0x68]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5E1B8\n"
                "BL      sub_FFC1BF94\n"        // CreateTask_StartupImage
                "B       loc_FFC5E1BC\n"
        "loc_FFC5E0F0:\n"
                "CMP     R0, #6\n"
                "STREQ   R5, [R4,#0x28]\n"
                "BEQ     loc_FFC5E1CC\n"
                "SUB     R12, R0, #0x2000\n"
                "SUBS    R12, R12, #4\n"
                "BNE     loc_FFC5E1D8\n"
        "loc_FFC5E108:\n"
                "SUB     R12, R6, #0x1100\n"
                "SUBS    R12, R12, #0x62\n"
                "BNE     loc_FFC5E124\n"
                "MOV     R1, R7\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC60D1C\n"
                "STR     R5, [R4,#0x60]\n"
        "loc_FFC5E124:\n"
                "BL      sub_FFC6039C\n"
                "BL      sub_FFC60610\n"
                "BL      sub_FFC5DC14\n"
                "B       loc_FFC5E1D0\n"
        "loc_FFC5E134:\n"
                "MOV     R0, #7\n"
                "BL      sub_FFC5D5B0\n"        // uCameraConState
                "MOV     R0, R7\n"
                "BL      sub_FFC1BDB8\n"
                "BL      sub_FFC5F7E0\n"        // CreateTask_CommonDrivers
                "BL      sub_FFC601B4\n"        // uDispSwLock
                "MOV     R1, R7\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC60D1C\n"
                "LDR     R1, =0xFFC5E348\n"     // aAcBootrec\n"  // "AC:BootRec"
                "MOV     R0, #0x20\n"
                "STR     R6, [R4,#0x18]\n"
                "BL      sub_FFC57EC4\n"        // qCameraLog
                "LDR     R1, =0xFFC5E354\n"     // aAcInitlens  // "AC:InitLens"
                "MOV     R0, #0x20\n"
                "BL      sub_FFC57EC4\n"        // qCameraLog
                "STR     R5, [R4,#0x28]\n"
                "BL      sub_FFC1BF24\n"
                "BL      sub_FFC1BE78\n"
                "LDR     R0, [R4,#0x1C]\n"
                "LDR     R1, [R4,#0x20]\n"
                "ORRS    R0, R0, R1\n"
                "BLNE    sub_FFC5EB0C\n"
                "LDR     R0, [R4,#0x68]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5E1A4\n"
                "BL      sub_FFC1BF94\n"        // CreateTask_StartupImage
                "B       loc_FFC5E1AC\n"
        "loc_FFC5E1A4:\n"
                "BL      sub_FFC15C28\n"
                "BL      sub_FFC1C7EC\n"
        "loc_FFC5E1AC:\n"
                "BL      sub_FFC5F7A4_my\n"        // CreateTask_InitFileModules
                "BL      sub_FFC5F81C\n"
                "B       loc_FFC5E1D0\n"
        "loc_FFC5E1B8:\n"
                "BL      sub_FFC15C28\n"
        "loc_FFC5E1BC:\n"
                "BL      sub_FFC5F84C\n"
                "LDR     R0, [R4,#0x30]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC5E1D0\n"
        "loc_FFC5E1CC:\n"
                "BL      sub_FFC5D664\n"
        "loc_FFC5E1D0:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        "loc_FFC5E1D8:\n"
                "MOV     R0, #1\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5F7A4_my() { //#fs  CreateTask_InitFileModules
        asm volatile (
                "LDR     R0, =0x5AB4\n"
                "STMFD   SP!, {R3,LR}\n"
                "LDR     R1, [R0,#4]\n"
                "CMP     R1, #0\n"
                "BNE     locret_FFC5F7DC\n"
                "MOV     R1, #1\n"
                "STR     R1, [R0,#4]\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
                "LDR     R3, =task_InitFileModules_my\n"        // continue for SDHC-boot (orig: FFC5F754)
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFFC5F908\n"     // aInitfilemodule ; "InitFileModules"
                "MOV     R2, #0x1000\n"
                "BL      sub_FFC0BBC0\n"         // CreateTask, 0xFFC0BBC0
        "locret_FFC5F7DC:\n"
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FFC5A4BC\n"
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FFC5B69C\n"
                "BL      sub_FFC5A4E8_my\n"    // continue to SDHC-hook here!

                "BL      core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask

                "CMP     R4, #0\n"
                "MOVEQ   R0, R5\n"
                "LDMEQFD SP!, {R4-R6,LR}\n"
                "MOVEQ   R1, #0\n"
                "BEQ     sub_FFC5B69C\n"        // cameralog "LogicalEvent...", it's save to run this after spytask has started
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5A4E8_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC3F0CC_my\n"    // continue to SDHC-hook here!
                "LDR     R4, =0x58D0\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5A518\n"
                "BL      sub_FFC674CC\n"
                "BL      sub_FFCDCA24\n"
                "BL      sub_FFC674CC\n"
                "BL      sub_FFCE6504\n"
                "BL      sub_FFC674DC\n"
                "BL      sub_FFCDCAC4\n"
                "loc_FFC5A518:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3F0CC_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOV     R6, #0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3EC9C\n"
                "LDR     R4, =0x11800\n"
                "MOV     R5, #0\n"
                "LDR     R0, [R4,#0x38]\n"
                "BL      sub_FFC3F664\n"
                "CMP     R0, #0\n"
                "LDREQ   R0, =0x2BA0\n"
                "STREQ   R5, [R0,#0xC]\n"
                "STREQ   R5, [R0,#0x10]\n"
                "STREQ   R5, [R0,#0x14]\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3ECDC\n"        // uMounter (u=unknown, just to prevent misunderstandings)
                "MOV     R0, R6\n"
                "BL      sub_FFC3EF08_my\n"    // continue to SDHC-hook here!
                "MOV     R5, R0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3EF74\n"
                "LDR     R1, [R4,#0x3C]\n"
                "AND     R2, R5, R0\n"
                "CMP     R1, #0\n"
                "MOV     R0, #0\n"
                "MOVEQ   R0, #0x80000001\n"
                "BEQ     loc_FFC3F160\n"
                "LDR     R3, [R4,#0x2C]\n"
                "CMP     R3, #2\n"
                "MOVEQ   R0, #4\n"
                "CMP     R1, #5\n"
                "ORRNE   R0, R0, #1\n"
                "BICEQ   R0, R0, #1\n"
                "CMP     R2, #0\n"
                "BICEQ   R0, R0, #2\n"
                "ORREQ   R0, R0, #0x80000000\n"
                "BICNE   R0, R0, #0x80000000\n"
                "ORRNE   R0, R0, #2\n"
        "loc_FFC3F160:\n"
                "STR     R0, [R4,#0x40]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3EF08_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R5, =0x2BA0\n"
                "MOV     R6, R0\n"
                "LDR     R0, [R5,#0x10]\n"
                "CMP     R0, #0\n"
                "MOVNE   R0, #1\n"
                "LDMNEFD SP!, {R4-R6,PC}\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R6\n"
                "LDR     R0, =0x11800\n"
                "ADD     R4, R0, R1,LSL#2\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC3EDA0_my\n"        //    continue to SDHC-hook here!
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC3F77C\n"
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3E8BC\n"
                "CMP     R0, #0\n"
                "MOVNE   R1, #1\n"
                "STRNE   R1, [R5,#0x10]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3EDA0_my() { //#fs  ; Partition table parse takes place here. => SDHC-boot
        asm volatile (
                "STMFD   SP!, {R4-R8,LR} \n"
                "MOV     R8, R0\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R1\n"
                "LDR     R0, =0x11800\n"
                "MOV     R6, #0\n"
                "ADD     R7, R0, R1,LSL#2\n"
                "LDR     R0, [R7,#0x3C]\n"
                "MOV     R5, #0\n"
                "CMP     R0, #6\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
                "B       loc_FFC3EEEC\n"
        "loc_FFC3EDD0:\n"
                "B       loc_FFC3EE04\n"
        "loc_FFC3EDD4:\n"
                "B       loc_FFC3EDEC\n"
        "loc_FFC3EDD8:\n"
                "B       loc_FFC3EDEC\n"
        "loc_FFC3EDDC:\n"
                "B       loc_FFC3EDEC\n"
        "loc_FFC3EDE0:\n"
                "B       loc_FFC3EDEC\n"
        "loc_FFC3EDE4:\n"
                "B       loc_FFC3EEE4\n"
        "loc_FFC3EDE8:\n"
                "B       loc_FFC3EDEC\n"
        "loc_FFC3EDEC:\n"
                "MOV     R2, #0\n"
                "MOV     R1, #0x200\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC56994\n"
                "MOVS    R4, R0\n"
                "BNE     loc_FFC3EE0C\n"
        "loc_FFC3EE04:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        "loc_FFC3EE0C:\n"
                "LDR     R12, [R7,#0x4C]\n"
                "MOV     R3, R4\n"
                "MOV     R2, #1\n"
                "MOV     R1, #0\n"
                "MOV     R0, R8\n"

                //"BLX     R12\n"       // !! Workaround !!
                "MOV     LR, PC\n"      // gcc won't compile "BLX R12" nor "BL R12".
                "MOV     PC, R12\n"     // workaround: make your own "BL" and hope we don't need the change to thumb-mode

                "CMP     R0, #1\n"
                "BNE     loc_FFC3EE38\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC56AD4\n"
                "B       loc_FFC3EE04\n"

        "loc_FFC3EE38:\n"
                "MOV     R0, R8\n"
                "BL      sub_FFCF554C\n"        // Add FAT32 autodetect-code after this line\n"

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
                "BNE     dg_sd_fat32\n"                // No, it isn't.
                "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
                "CMPNE   R2, #0x80\n"
                "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                                       // This partition is valid, it's the first one, bingo!
                "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.
                
           "dg_sd_fat32_end:\n"
                // End of DataGhost's FAT32 autodetection code                
      
                "LDRB    R1, [R4,#0x1C9]\n"     // Continue with firmware
                "LDRB    R3, [R4,#0x1C8]\n"
                "LDRB    R12, [R4,#0x1CC]\n"
                "MOV     R1, R1,LSL#24\n"
                "ORR     R1, R1, R3,LSL#16\n"
                "LDRB    R3, [R4,#0x1C7]\n"
                "LDRB    R2, [R4,#0x1BE]\n"
               //"LDRB    LR, [R4,#0x1FF]\n"            // replaced, see below
                "ORR     R1, R1, R3,LSL#8\n"
                "LDRB    R3, [R4,#0x1C6]\n"
                "CMP     R2, #0\n"
                "CMPNE   R2, #0x80\n"
                "ORR     R1, R1, R3\n"
                "LDRB    R3, [R4,#0x1CD]\n"
                "MOV     R3, R3,LSL#24\n"
                "ORR     R3, R3, R12,LSL#16\n"
                "LDRB    R12, [R4,#0x1CB]\n"
                "ORR     R3, R3, R12,LSL#8\n"
                "LDRB    R12, [R4,#0x1CA]\n"
                "ORR     R3, R3, R12\n"
               //"LDRB    R12, [R4,#0x1FE]\n"           // replaced, see below

                "LDRB    R12, [LR,#0x1FE]\n"            // New! First MBR signature byte (0x55)
                "LDRB    LR, [LR,#0x1FF]\n"             //      Last MBR signature byte (0xAA)

                "MOV     R4, #0\n"
                "BNE     loc_FFC3EEC0\n"
                "CMP     R0, R1\n"
                "BCC     loc_FFC3EEC0\n"
                "ADD     R2, R1, R3\n"
                "CMP     R2, R0\n"
                "CMPLS   R12, #0x55\n"
                "CMPEQ   LR, #0xAA\n"
                "MOVEQ   R6, R1\n"
                "MOVEQ   R5, R3\n"
                "MOVEQ   R4, #1\n"
        "loc_FFC3EEC0:\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC56AD4\n"
                "CMP     R4, #0\n"
                "BNE     loc_FFC3EEF8\n"
                "MOV     R6, #0\n"
                "MOV     R0, R8\n"
                "BL      sub_FFCF554C\n"
                "MOV     R5, R0\n"
                "B       loc_FFC3EEF8\n"
        "loc_FFC3EEE4:\n"
                "MOV     R5, #0x40\n"
                "B       loc_FFC3EEF8\n"
        "loc_FFC3EEEC:\n"
                "LDR     R1, =0x365\n"
                "LDR     R0, =0xFFC3ED94\n"             // aMounter_c  ; "Mounter.c"
                "BL      sub_FFC0C098\n"                // Assert
        "loc_FFC3EEF8:\n"
                "STR     R6, [R7,#0x44]!\n"
                "MOV     R0, #1\n"
                "STR     R5, [R7,#4]\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe
*/

