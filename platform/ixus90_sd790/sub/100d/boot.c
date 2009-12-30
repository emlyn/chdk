#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

void __attribute__((naked,noinline)) jogdial_task_my();

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void taskCreateHook(int *p)
{
	p-=16;
	if (p[0]==0xFF821ADC)  p[0]=(int)mykbd_task;
	if (p[0]==0xFF842C84)  p[0]=(int)jogdial_task_my; 
	if (p[0]==0xFF85A278)  p[0]=(int)movie_record_task;
	if (p[0]==0xFF85E2b0)  p[0]=(int)capt_seq_task;
	if (p[0]==0xFF8791D0)  p[0]=0xFF8791D0;	//(int)init_file_modules_task;
	if (p[0]==0xFF8b6A80)  p[0]=0xFF8b6A80;	//(int)exp_drv_task;
}

void boot();

void boot() { //#fs
    long *canon_data_src = (void*)0xFFB1CDDC;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xF134 - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xF134; // just after data
    long canon_bss_len = 0xCBC48 - 0xF134; //0xFEBC;

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

	// asm volatile ("B   sub_FF810000\n" );

 	 // Captain Hook
	 *(int*)0x1930 = (int)taskCreateHook;

    // jump to init-sequence that follows the data-copy-routine 
    asm volatile ("B  sub_FF8101A4_my\n" );
}; //#fe


// init
void __attribute__((naked,noinline)) sub_FF8101A4_my() { //#fs 
        asm volatile (

"loc_FF8101A4:\n" //                               ; CODE XREF: ROM:FF810160j
        "LDR     R0, =0xFF81021C\n"
        "MOV     R1, #0\n"
        "LDR     R3, =0xFF810254\n"

"loc_FF8101B0:\n" //                               ; CODE XREF: ROM:FF8101BCj
        "CMP     R0, R3\n"
        "LDRCC   R2, [R0],#4\n"
        "STRCC   R2, [R1],#4\n"
        "BCC     loc_FF8101B0\n"
        "LDR     R0, =0xFF810254\n"
        "MOV     R1, #0x4B0\n"
        "LDR     R3, =0xFF810468\n"

"loc_FF8101CC:\n" //                               ; CODE XREF: ROM:FF8101D8j
        "CMP     R0, R3\n"
        "LDRCC   R2, [R0],#4\n"
        "STRCC   R2, [R1],#4\n"
        "BCC     loc_FF8101CC\n"
        "MOV     R0, #0xD2\n"
        "MSR     CPSR_cxsf, R0\n"
        "MOV     SP, #0x1000\n"
        "MOV     R0, #0xD3\n"
        "MSR     CPSR_cxsf, R0\n"
        "MOV     SP, #0x1000\n"
//        "LDR     R0, loc_FF810210\n" // =0x6C4\n" //loc_FF810210\n"
			  "LDR     R0, =0x6C4\n" // +
        "LDR     R2, =0xEEEEEEEE\n"
        "MOV     R3, #0x1000\n"

"loc_FF810200:\n" //                               ; CODE XREF: ROM:FF810208j
        "CMP     R0, R3\n"
        "STRCC   R2, [R0],#4\n"
        "BCC     loc_FF810200\n"
        "BL      sub_FF810FA0_my\n"
	);
	// Working
} //#fe

void __attribute__((naked,noinline)) sub_FF810FA0_my() { //#fs 
        asm volatile (
        "STR     LR, [SP,#-4]!\n"
        "SUB     SP, SP, #0x74\n"
        "MOV     R0, SP\n"
        "MOV     R1, #0x74\n"
        "BL      sub_FFAACA58\n"
        "MOV     R0, #0x53000\n"
        "STR     R0, [SP,#0x74-0x70]\n"
        //"LDR     R0, =0xCBC48\n"
        "LDR     R0, =new_sa\n"
        "LDR     R0, [R0]\n"
        "LDR     R2, =0x279C00\n"
        "LDR     R1, =0x272968\n"
        "STR     R0, [SP,#0x74-0x6C]\n"
        "SUB     R0, R1, R0\n"
        "ADD     R3, SP, #0x74-0x68\n"
        "STR     R2, [SP,#0x74-0x74]\n"
        "STMIA   R3, {R0-R2}\n"
        "MOV     R0, #0x22\n"
        "STR     R0, [SP,#0x74-0x5C]\n"
        "MOV     R0, #0x68\n"
        "STR     R0, [SP,#0x74-0x58]\n"
        "LDR     R0, =0x19B\n"
        "MOV     R1, #0x64\n"
        //"STRD    R0, [SP,#0x74-0x54]\n"
        "STR     R0, [SP,#0x74-0x54]\n"
        "STR     R1, [SP,#0x74-0x50]\n"
        "MOV     R0, #0x78\n"
        //"STRD    R0, [SP,#0x74-0x4C]\n"
        "STR     R0, [SP,#0x74-0x4C]\n"
        "STR     R1, [SP,#0x74-0x48]\n"
        "MOV     R0, #0\n"
        "STR     R0, [SP,#0x74-0x44]\n"
        "STR     R0, [SP,#0x74-0x40]\n"
        "MOV     R0, #0x10\n"
        "STR     R0, [SP,#0x74-0x18]\n"
        "MOV     R0, #0x800\n"
        "STR     R0, [SP,#0x74-0x14]\n"
        "MOV     R0, #0xA0\n"
        "STR     R0, [SP,#0x74-0x10]\n"
        "MOV     R0, #0x280\n"
        "STR     R0, [SP,#0x74-0xC]\n"
        //"LDR     R1, =0xFF814DA4\n"
        "LDR     R1, =uHwSetup_my\n"
        "MOV     R0, SP\n"
        "MOV     R2, #0\n"
        "BL      sub_FF812D58\n"

        "ADD     SP, SP, #0x74\n"
        "LDR     PC, [SP],#4\n"
	);
	// Working
}; //#fe

// Extracted method: uHwSetup (FF814DA4)
void __attribute__((naked,noinline)) uHwSetup_my() { //#fs 
        asm volatile (
        "STMFD   SP!, {R4,LR}\n"
        "BL      sub_FF81094C\n"
        "BL      sub_FF819664\n"
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF814EB8\n" //    ; "dmSetup"\n"
        "BLLT    sub_FF814E98\n"
        "BL      sub_FF8149C8\n"
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF814EC0\n" // ; "termDriverInit"\n"
        "BLLT    sub_FF814E98\n"
        "LDR     R0, =0xFF814ED0\n" //      ; "/_term"\n"
        "BL      sub_FF814AB4\n"
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF814ED8\n" // ; "termDeviceCreate"\n"
        "BLLT    sub_FF814E98\n"
        "LDR     R0, =0xFF814ED0\n" //      ; "/_term"\n"
        "BL      sub_FF813564\n"
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF814EEC\n" // ; "stdioSetup"\n"
        "BLLT    sub_FF814E98\n"
        "BL      sub_FF8191EC\n"
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF814EF8\n" // ; "stdlibSetup"\n"
        "BLLT    sub_FF814E98\n"
        "BL      sub_FF8114B8\n"
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF814F04\n" // ; "armlib_setup"\n"
        "BLLT    sub_FF814E98\n"
        "LDMFD   SP!, {R4,LR}\n"
        "B       taskcreate_Startup_my\n"
        );
}; //#fe

// Extracted method: taskcreate_Startup (FF81CCBC)
void __attribute__((naked,noinline)) taskcreate_Startup_my() { //#fs 
        asm volatile (
        "STMFD   SP!, {R3-R5,LR}\n"
        "BL      sub_FF821C00\n"
        "BL      sub_FF829EF0\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF81CCFC\n"
        "LDR     R4, =0xC0220000\n"
        "LDR     R0, [R4,#0xFC]\n"
        "TST     R0, #1\n"
        "MOVEQ   R0, #0x12C\n"
        "BLEQ    sub_FF828400\n"
        "BL      sub_FF821BFC\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF81CCFC\n"
        "MOV     R0, #0x44\n"
        "STR     R0, [R4,#0x4C]\n"

"loc_FF81CCF8:\n" //                               ; CODE XREF: taskcreate_Startup:loc_FF81CCF8j
        "B       loc_FF81CCF8\n"

"loc_FF81CCFC:\n" //                               ; CODE XREF: taskcreate_Startup+10j
        "BL      sub_FF821C08\n"
        "BL      sub_FF821C04\n"
        "BL      sub_FF828278\n"
        "LDR     R1, =0x2CE000\n"
        "MOV     R0, #0\n"
        "BL      sub_FF8284C0\n"
        "BL      sub_FF82846C\n"
        "MOV     R3, #0\n"
        "STR     R3, [SP,#0x10-0x10]\n"
        "LDR     R3, =task_Startup_my\n" //task_Startup
        "MOV     R2, #0\n"
        "MOV     R1, #0x19\n"
        "LDR     R0, =0xFF81CD44\n"   // ; "Startup"\n"
        "BL      sub_FF81B818\n"
        "MOV     R0, #0\n"
        //"LDMFD   SP!, {R3-R5,PC}\n"
        "LDMFD   SP!, {ip, pc}\n"
		);
}; //#fe

// Extracted method: task_Startup (FF81CC60)
void __attribute__((naked,noinline)) task_Startup_my() { //#fs 
        asm volatile (
        "STMFD   SP!, {R4,LR}\n"
        "BL      sub_FF81516C\n" // clockSave
        "BL      sub_FF822D60\n"
        "BL      sub_FF81FE00\n"
        //"BL      sub_FF829F30\n"			// hl??
        "BL      sub_FF82A0F8\n"
        //"BL      sub_FF829FB8\n" // StartDiskBoot
        );

		CreateTask_spytask();

        asm volatile (
        "BL      sub_FF82A2AC\n"
        "BL      sub_FF82A148\n" // good question.... equiv of touch_wheel.c ?
        "BL      sub_FF8277B8\n"
        "BL      sub_FF82A2B0\n"
		);

//		CreateTask_PhySw();

		asm volatile (
        "BL      sub_FF821B10\n" // taskcreate_PhySw
        "BL      sub_FF824CC8_my\n" // task_ShootSeqTask
        "BL      sub_FF82A2C8\n"
        //"BL      sub_FF81FB20\n" // nullsub_2
        "BL      sub_FF820FCC\n"
        "BL      sub_FF829CB8\n" // taskcreate_Bye
        "BL      sub_FF821640\n"
        "BL      sub_FF820EBC\n" // taskcreate_TempCheck\n"
        "BL      sub_FF82AD6C_my\n"
        "BL      sub_FF820E78\n"
        //"LDMFD   SP!, {R4,LR}\n"
        "BL       sub_FF815070\n"
		"LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void CreateTask_spytask() { //#fs 
    _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}; //#fe

//void CreateTask_PhySw() { //#fs 
//    _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
//}; //#fe


void __attribute__((naked,noinline)) sub_FF824CC8_my() { //#fs 
        asm volatile (
        "STMFD   SP!, {R4,LR}\n"
        "LDR     R4, =0x1C14\n"
        "MOV     R0, #0\n"
        "MOV     R1, #4\n"
        "STR     R0, [R4,#0xC]\n"
        "BL      sub_FF81BB48\n"
        "STR     R0, [R4,#4]\n"
        "MOV     R0, #0\n"
        "MOV     R1, #1\n"
        "BL      sub_FF81BB6C\n"
        "STR     R0, [R4,#8]\n"
        "BL      sub_FF861378\n"
        "BL      sub_FF862614\n" // taskcreate_SsTask\n"
        "BL      sub_FF8603E0\n"
        "BL      sub_FF85D214_my\n" //my
        "BL      sub_FF86164C\n"
        "LDR     R0, [R4,#4]\n"
        "LDMFD   SP!, {R4,LR}\n"
        "MOV     R1, #0x1000\n"
        "B       sub_FF827B1C\n"
		);
}; //#fe

void __attribute__((naked,noinline)) sub_FF85D214_my() { //#fs 
        asm volatile (
        "STMFD   SP!, {R4,LR}\n"
        "LDR     R4, =0x54AC\n"
        "LDR     R0, [R4,#4]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF85D280\n"
        //"BL      nullsub_31\n"
        "MOV     R1, #1\n"
        "MOV     R0, #0\n"
        "BL      sub_FF81BB6C\n"
        "STR     R0, [R4,#0xC]\n"
        "MOV     R0, #0\n"
        "MOV     R1, #0\n"
        "BL      sub_FF81BB48\n"
        "STR     R0, [R4,#0x10]\n"
        "BL      sub_FF85D4F8\n"
        "BL      sub_FF85D9B4\n"
        "MOV     R0, #0\n"
        "STR     R0, [R4,#8]\n"
        "ADD     R0, R4, #0x14\n"
        "MOV     R1, #0\n"
        "STR     R1, [R0],#4\n"
        "STR     R1, [R0]\n"
        "BL      sub_FF85DBBC\n"
        "BL      sub_FF8617F8\n"
        "BL      sub_FF85FD9C\n"
        "BL      sub_FF85E54C_my\n"    // taskcreate_CaptSeqTask
        "BL      sub_FF85F860\n"    // taskcreate_MovieCtrlTask

"loc_FF85D280:\n" //                               ; CODE XREF: submy_FF85D214+10j
        "MOV     R0, #1\n"
        "STR     R0, [R4,#4]\n"
        "LDMFD   SP!, {R4,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FF85E54C_my() { //#fs  // CreateTask_CaptSeqTask
        asm volatile (
        "STMFD   SP!, {R3-R5,LR}\n"
        "LDR     R2, =0x19E18\n"
        "MOV     R0, #0\n"
        "MOV     R1, #0\n"

"loc_FF85E55C:\n" //                               ; CODE XREF: taskcreate_CaptSeqTask+20j
        "ADD     R3, R2, R0,LSL#4\n"
        "ADD     R0, R0, #1\n"
        "CMP     R0, #5\n"
        "STR     R1, [R3,#8]\n"
        "BCC     loc_FF85E55C\n"
        "BL      sub_FF93C4E8\n"
        "BL      sub_FF93E33C\n"
        "MOV     R1, #5\n"
        "MOV     R0, #0\n"
        "BL      sub_FF81BB24\n"
        "LDR     R4, =0x54E0\n"
        "LDR     R1, =0x1001FF\n"
        "STR     R0, [R4,#0xC]\n"
        "MOV     R0, #0\n"
        "BL      sub_FF81BB48\n"
        "STR     R0, [R4,#8]\n"
        "MOV     R0, #0\n"
        "MOV     R1, #1\n"
        "BL      sub_FF81BB6C\n"
        "STR     R0, [R4,#0x10]\n"
        "MOV     R3, #0\n"
        "STR     R3, [SP,#0x10-0x10]\n"
//        "ADR     R3, task_CaptSeqTask\n"
        "LDR     R3, =0xFF85E2B0\n"
//        "LDR     R3, =task_CaptSeqTask_my\n"
        "LDR     R0, =0xFF85E74C\n" // aCaptseqtask\n" ; "CaptSeqTask"\n"
        "MOV     R2, #0x1000\n"
        "MOV     R1, #0x17\n"
        "BL      sub_FF81BAF0\n" // KernelCreateTask
        "LDMFD   SP!, {R3-R5,PC}\n"
        ".ltorg\n"
        );
}; //#fe


// -----------------
// SDHC-Boot-Support
// -----------------

// Extracted method: sub_FF82C8E4 (FF82C8E4-FF82C928)
// Overridden calls:
//     sub_FF82C3F0
void __attribute__((naked,noinline)) sub_FF82AD6C_my() { //#fs  

    asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL	sub_FF876134\n"
		"BL	_IsFactoryMode\n"
		"CMP	R0, #1\n"
		"BNE	loc_FF82AD8C\n"
		"BL	sub_FF87932C\n"
		"LDMIA	SP!, {R4,LR}\n"
		"B	_StartFactoryModeController\n"


	"loc_FF82AD8C:\n"
		"BL	     sub_FF8782F8\n"
		"LDR	 R4, =0x1D28\n"
		"LDR	 R0, [R4,#4]\n"
		"CMP	 R0, #0\n"
		"LDMNEFD SP!, {R4,PC}\n"
		"MOV	 R1, #0\n"
		"LDR	 R0, =sub_FF82A880_my\n"    //   ---------------> for SDHC and movie rec
		"BL	     _CreateController\n"
		"STR     R0, [R4,#4]\n"
		"LDMFD	 SP!, {R4,PC}\n"
	);
}; //#fe

// Extracted method: sub_FF82C3F0 (FF82C3F0-FF82C8E0)
// Overridden calls:
//     sub_FF82A640
//     sub_FF878000
//     sub_FF870B0C
void __attribute__((naked,noinline)) sub_FF82A880_my() {
    asm volatile (
        "STMFD   SP!, {R3-R11,LR}\n"
        "LDR     R6, =0x1D28\n"
        "MOV     R5, R1\n"
        "LDR     R0, [R6,#0x14]\n"
        "MOV     R4, R3\n"
        "CMP     R0, #1\n"
        "BNE     loc_FF82A8A4\n"
        "BL      sub_FF876970\n"
        "B       loc_FF82AC9C\n"


"loc_FF82A8A4:\n" //                               ; CODE XREF: submy_FF82A880+18j
        "LDR     R12, =0x1162\n"
        "LDR     R10, =0x1005\n"
        "CMP     R5, R12\n"
        "MOV     R7, #0\n"
        "MOV     R8, #1\n"
        "BEQ     loc_FF82ACC8\n"
        "BGT     loc_FF82A9F8\n"
        "LDR     R12, =0x1062\n"
        "CMP     R5, R12\n"
        "BEQ     loc_FF82AD64\n"
        "BGT     loc_FF82A96C\n"
        "CMP     R5, R10\n"
        "BEQ     loc_FF82ACF4\n"
        "BGT     loc_FF82A944\n"
        "LDR     R9, =0x9A3\n"
        "CMP     R5, R9\n"
        "ADD     R10, R9, #2\n"
        "BEQ     loc_FF82AC7C\n"
        "BGT     loc_FF82A924\n"
        "SUB     R12, R5, #0x800\n"
        "SUBS    R12, R12, #3\n"
        "BEQ     loc_FF82AB7C\n"
        "SUB     R12, R5, #0x800\n"
        "SUBS    R12, R12, #0x158\n"
        "BNE     loc_FF82ACB8\n"
        "TST     R4, #0x80000000\n"
        "MOVNE   R0, #1\n"
        "BNE     locret_FF82ABD8\n"
        "BL      sub_FF87FE48\n"
        "CMP     R0, #0\n"
        "BLEQ    sub_FF82768C\n"
        "B       loc_FF82AC9C\n"


"loc_FF82A924:\n" //                               ; CODE XREF: submy_FF82A880+6Cj
        "CMP     R5, R10\n"
        "BEQ     loc_FF82AC7C\n"
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #3\n"
        "BNE     loc_FF82ACB8\n"
        "BL      sub_FF82A7B4\n"
        "MOV     R1, R4\n"
        "B       loc_FF82ACC0\n"


"loc_FF82A944:\n" //                               ; CODE XREF: submy_FF82A880+58j
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #0x56\n"
        "SUBNE   R12, R5, #0x1000\n"
        "SUBNES  R12, R12, #0x5B\n"
        "SUBNE   R12, R5, #0x1000\n"
        "SUBNES  R12, R12, #0x5E\n"
        "SUBNE   R12, R5, #0x1000\n"
        "SUBNES  R12, R12, #0x61\n"
        "BNE     loc_FF82ACB8\n"
        "B       loc_FF82AD64\n"


"loc_FF82A96C:\n" //                               ; CODE XREF: submy_FF82A880+4Cj
        "LDR     R12, =0x10AD\n"
        "CMP     R5, R12\n"
        "BEQ     loc_FF82ACE4\n"
        "BGT     loc_FF82A9BC\n"
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #0x63\n"
        "SUBNE   R12, R5, #0x1000\n"
        "SUBNES  R12, R12, #0x65\n"
        "BEQ     loc_FF82AD64\n"
        "SUB     R12, R5, #0x1000\n"
        "LDR     R0, =0x10A3\n"
        "SUBS    R12, R12, #0xA9\n"
        "BEQ     loc_FF82ACD8\n"
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #0xAA\n"
        "BNE     loc_FF82ACB8\n"
        "BL      _IsControlEventActive\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FF82ACF0\n"
        "B       loc_FF82AC9C\n"


"loc_FF82A9BC:\n" //                               ; CODE XREF: submy_FF82A880+F8j
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #0xAE\n"
        "BEQ     loc_FF82ACF0\n"
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #0xAF\n"
        "BEQ     loc_FF82ACE4\n"
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #0xB0\n"
        "BEQ     loc_FF82ACF0\n"
        "SUB     R12, R5, #0x1000\n"
        "SUBS    R12, R12, #0xB2\n"
        "BNE     loc_FF82ACB8\n"
        "LDR     R0, =0x1008\n"
        "MOV     R1, R4\n"
        "B       loc_FF82ACC0\n"


"loc_FF82A9F8:\n" //                               ; CODE XREF: submy_FF82A880+3Cj
        "LDR     R11, =0x201B\n"
        "LDR     R0, =0x1D28\n"
        "CMP     R5, R11\n"
        "LDR     R2, [R0,#0x10]!\n"
        "LDR     R1, [R0,#0x10]\n"
        "SUB     R9, R11, #0x17\n"
        "BEQ     loc_FF82AC50\n"
        "BGT     loc_FF82AA90\n"
        "LDR     R11, =0x116A\n"
        "CMP     R5, R11\n"
        "BEQ     loc_FF82AC3C\n"
        "BGT     loc_FF82AA54\n"
        "SUB     R0, R5, #0x1100\n"
        "SUB     R0, R0, #0x63\n"
        "CMP     R0, #5\n"
        "ADDLS   PC, PC, R0,LSL#2\n"
        "B       loc_FF82ACB8\n"


"loc_FF82AA3C:\n" //                               ; CODE XREF: submy_FF82A880+1B4j
        "B       loc_FF82AC74\n"


"loc_FF82AA40:\n" //                               ; CODE XREF: submy_FF82A880+1B4j
        "B       loc_FF82AC68\n"


"loc_FF82AA44:\n" //                               ; CODE XREF: submy_FF82A880+1B4j
        "B       loc_FF82AC60\n"


"loc_FF82AA48:\n" //                               ; CODE XREF: submy_FF82A880+1B4j
        "B       loc_FF82ACB8\n"


"loc_FF82AA4C:\n" //                               ; CODE XREF: submy_FF82A880+1B4j
        "B       loc_FF82ABFC\n"


"loc_FF82AA50:\n" //                               ; CODE XREF: submy_FF82A880+1B4j
        "B       loc_FF82ABFC\n"


"loc_FF82AA54:\n" //                               ; CODE XREF: submy_FF82A880+1A4j
        "SUB     R12, R5, #0x2000\n"
        "SUBS    R12, R12, #2\n"
        "BEQ     loc_FF82AD30\n"
        "CMP     R5, R9\n"
        "MOV     R0, R9\n"
        "BEQ     loc_FF82AD3C\n"
        "SUB     R12, R5, #0x2000\n"
        "SUBS    R12, R12, #5\n"
        "BEQ     loc_FF82AD30\n"
        "SUB     R12, R5, #0x2000\n"
        "SUBS    R12, R12, #0x19\n"
        "BNE     loc_FF82ACB8\n"
        "CMP     R1, #0\n"
        "BNE     loc_FF82AD1C\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AA90:\n" //                               ; CODE XREF: submy_FF82A880+194j
        "LDR     R12, =0x3110\n"
        "CMP     R5, R12\n"
        "BEQ     loc_FF82ACF4\n"
        "BGT     loc_FF82AAD8\n"
        "SUB     R12, R5, #0x2000\n"
        "SUBS    R12, R12, #0x1D\n"
        "BEQ     loc_FF82AD30\n"
        "LDR     R0, =0x2027\n"
        "CMP     R5, R0\n"
        "BEQ     loc_FF82ACFC\n"
        "SUB     R12, R5, #0x3000\n"
        "SUBS    R12, R12, #6\n"
        "BEQ     loc_FF82ACF4\n"
        "SUB     R12, R5, #0x3000\n"
        "SUBS    R12, R12, #0x10\n"
        "BNE     loc_FF82ACB8\n"
        "BL      sub_FF870E88\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AAD8:\n" //                               ; CODE XREF: submy_FF82A880+21Cj
        "SUB     R12, R5, #0x3100\n"
        "SUBS    R12, R12, #0x11\n"
        "BEQ     loc_FF82ACF4\n"
        "CMP     R5, #0x3140\n"
        "BEQ     loc_FF82AD58\n"
        "SUB     R12, R5, #0x3200\n"
        "SUBS    R12, R12, #1\n"
        "BEQ     loc_FF82ACB8\n"
        "SUB     R12, R5, #0x3200\n"
        "SUBS    R12, R12, #2\n"
        "BNE     loc_FF82ACB8\n"
        "B       loc_FF82ACF4\n"


"loc_FF82AB7C:\n" //                               ; CODE XREF: submy_FF82A880+78j
        "MOV     R4, #1\n"
        "MOV     R0, #2\n"
        "BL      sub_FF8761C8\n"
        "CMP     R0, #1\n"
        "MOVEQ   R4, #2\n"
        "MOV     R0, R4\n"
        "BL      sub_FF821268\n"
        "CMP     R0, #0\n"
        "STRNE   R8, [R6,#0x14]\n"
        "BNE     loc_FF82ABD4\n"
        "BL      sub_FF87C548\n"
        "BL      sub_FF879CE8\n"
        "BL      sub_FF87A89C\n"
        "BL      sub_FF8795BC\n"
        "BL      sub_FF87AEE4\n" // GetVRAMHPixelsSize_1\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FF82ABDC\n"
        "BL      sub_FF82A520\n"
        "BL      sub_FF87AE48\n"
        "MOV     R1, R0\n"
        "LDR     R0, =0x1167\n"
        "BL      _PostLogicalEventToUI\n"

"loc_FF82ABD4:\n" //                               ; CODE XREF: submy_FF82A880+320j

        "MOV     R0, R7\n"

"locret_FF82ABD8:\n" //                       ; CODE XREF: submy_FF82A880+90j
        "LDMFD   SP!, {R3-R11,PC}\n"


"loc_FF82ABDC:\n" //                               ; CODE XREF: submy_FF82A880+33Cj
        "BL      sub_FF82533C\n"
        "CMP     R0, #1\n"
        "LDRNE   R0, =0x310B\n"
        "LDREQ   R0, =0x310C\n"
        "MOV     R1, #0\n"
        "BL      _PostLogicalEventToUI\n"
        "BL      sub_FF878FF4_my\n" // + SDHC and MovieRec
        "B       loc_FF82ABD4\n"


"loc_FF82ABFC:\n" //                               ; CODE XREF: submy_FF82A880+1B4j


        "STR     R8, [R6,#0x10]\n"
        "LDR     R6, =0x4508\n"
        "LDR     R4, =0x1168\n"
        "CMP     R1, #0\n"
        "BEQ     loc_FF82AC24\n"
        "BL      sub_FF8769A4\n"
        "B       loc_FF82AC30\n"


"loc_FF82AC18:\n" //                               ; CODE XREF: submy_FF82A880+3B4j
        "MOV     R0, R6\n"
        "BL      sub_FF85B4E0\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AC24:\n" //                               ; CODE XREF: submy_FF82A880+38Cj
        "BL      sub_FF879F7C\n"
        "BL      sub_FF879EE0\n"
        "BL      sub_FF824FE4\n"

"loc_FF82AC30:\n" //                               ; CODE XREF: submy_FF82A880+394j
        "CMP     R5, R4\n"
        "BEQ     loc_FF82AC18\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AC3C:\n" //                               ; CODE XREF: submy_FF82A880+1A0j
        "MOV     R0, #1\n"
        "BL      sub_FF876AD0\n"
        "MOV     R1, R11\n"
        "MOV     R0, R10\n"
        "B       loc_FF82ACC0\n"


"loc_FF82AC50:\n" //                               ; CODE XREF: submy_FF82A880+190j
        "CMP     R2, #1\n"
        "BNE     loc_FF82ACF4\n"
        "BL      sub_FF8769A4\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AC60:\n" //                               ; CODE XREF: submy_FF82A880+1B4j


        "MOV     R0, #2\n"
        "B       loc_FF82AC6C\n"


"loc_FF82AC68:\n" //                               ; CODE XREF: submy_FF82A880+1B4j


        "MOV     R0, #1\n"

"loc_FF82AC6C:\n" //                               ; CODE XREF: submy_FF82A880+3E4j

        "BL      sub_FF82B2AC\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AC74:\n" //                               ; CODE XREF: submy_FF82A880+1B4j


        "MOV     R0, #0\n"
        "B       loc_FF82AC6C\n"


"loc_FF82AC7C:\n" //                               ; CODE XREF: submy_FF82A880+68j

        "LDR     R0, [R6,#0xC]\n"
        "SUB     R12, R0, #0x8000\n"
        "SUBS    R12, R12, #2\n"
        "BEQ     loc_FF82AC9C\n"
        "LDR     R0, =0x10A5\n"
        "BL      _IsControlEventActive\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FF82ACA4\n"

"loc_FF82AC9C:\n" //                               ; CODE XREF: submy_FF82A880+20j

        "MOV     R0, #0\n"
        "LDMFD   SP!, {R3-R11,PC}\n"


"loc_FF82ACA4:\n" //                               ; CODE XREF: submy_FF82A880+418j
        "CMP     R5, R9\n"
        "STREQ   R8, [R6,#0x34]\n"
        "BEQ     loc_FF82ACB8\n"
        "CMP     R5, R10\n"
        "STREQ   R8, [R6,#0x30]\n"

"loc_FF82ACB8:\n" //                               ; CODE XREF: submy_FF82A880+84j



        "MOV     R1, #0\n"

"loc_FF82ACBC:\n" //                               ; CODE XREF: submy_FF82A880+478j
        "MOV     R0, R5\n"

"loc_FF82ACC0:\n" //                               ; CODE XREF: submy_FF82A880+C0j

        "BL      sub_FF878000_my\n" // + for SDHC and MovieRec
        "LDMFD   SP!, {R3-R11,PC}\n"


"loc_FF82ACC8:\n" //                               ; CODE XREF: submy_FF82A880+38j
        "BL      sub_FF87E79C\n"
        "CMP     R0, #0\n"
        "BLNE    sub_FF87D59C\n"
        "B       loc_FF82ACF4\n"


"loc_FF82ACD8:\n" //                               ; CODE XREF: submy_FF82A880+11Cj
        "BL      _IsControlEventActive\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF82AC9C\n"

"loc_FF82ACE4:\n" //                               ; CODE XREF: submy_FF82A880+F4j

        "MOV     R0, R5\n"
        "BL      sub_FF82A640\n" // + ____my\n"
        "LDMFD   SP!, {R3-R11,PC}\n" // + for SDHC and MovieRec


"loc_FF82ACF0:\n" //                               ; CODE XREF: submy_FF82A880+134j

        "BL      sub_FF82B27C\n"

"loc_FF82ACF4:\n" //                               ; CODE XREF: submy_FF82A880+54j

        "MOV     R1, R4\n"
        "B       loc_FF82ACBC\n"


"loc_FF82ACFC:\n" //                               ; CODE XREF: submy_FF82A880+234j
        "MOV     R1, #0\n"
        "BL      sub_FF878000_my\n" // +
        "MOV     R1, #0\n"
        "MOV     R0, R11\n"
        "BL      sub_FF878000_my\n" // +
        "MOV     R1, #0\n"
        "MOV     R0, R9\n"
        "B       loc_FF82AD28\n"


"loc_FF82AD1C:\n" //                               ; CODE XREF: submy_FF82A880+208j
        "CMP     R2, #0\n"
        "BNE     loc_FF82AC9C\n"

"loc_FF82AD24:\n" //                               ; CODE XREF: submy_FF82A880+4E8j
        "MOV     R1, #0\n"

"loc_FF82AD28:\n" //                               ; CODE XREF: submy_FF82A880+498j
        "BL      sub_FF878000_my\n" // for SDHC and MovieRec
        "B       loc_FF82AC9C\n"


"loc_FF82AD30:\n" //                               ; CODE XREF: submy_FF82A880+1DCj

        "STR     R7, [R6,#0x20]\n"
        "BL      sub_FF82AF64\n"
        "B       loc_FF82ACF4\n"


"loc_FF82AD3C:\n" //                               ; CODE XREF: submy_FF82A880+1E8j
        "STR     R7, [R6,#0x20]\n"
        "BL      sub_FF82AF64\n"
        "LDR     R0, [R6,#0x10]\n"
        "CMP     R0, #1\n"
        "BNE     loc_FF82ACF4\n"
        "BL      sub_FF8769E8\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AD58:\n" //                               ; CODE XREF: submy_FF82A880+268j
        "CMP     R1, #0\n"
        "BLEQ    sub_FF82AF64\n"
        "B       loc_FF82AC9C\n"


"loc_FF82AD64:\n" //                               ; CODE XREF: submy_FF82A880+48j

        "MOV     R0, #0xFFFFFFFF\n"
        "B       loc_FF82AD24\n"
        ".LTORG\n" // make literal pool
    );
}


// Extracted method: sub_FF870B0C (FF870B0C-FF870BF0)
// Overridden calls:
//     sub_FF878E44
//     sub_FF878E44
void __attribute__((naked,noinline)) sub_FF878FF4_my() {
    asm volatile (
	  "STMFD   SP!, {R4,LR}\n"
	  "BL      sub_FF82AF30\n"
	  "MOV     R4, R0\n"
	  "BL      sub_FF879110\n"
	  "MOV     R0, R4\n"
	  "BL      sub_FF878EA8\n"
	  "BL      sub_FF82AF30\n"
	  "MOV     R4, R0\n"
	  "LDR     R0, =0x5E5C\n"
	  "LDR     R0, [R0]\n"
	  "TST     R0, #1\n"
	  "BEQ     loc_FF879030\n"
"loc_FF879024:\n" //                            ; CODE XREF: sub_FF878FF4+5Cj
	  "MOV     R1, R4\n"
	  "MOV     R0, #2\n"
	  "B       loc_FF879098\n"
"loc_FF879030:\n" //                            ; CODE XREF: sub_FF878FF4+2Cj
	  "TST     R0, #0x2000\n"
	  "BEQ     loc_FF87904C\n"
	  "TST     R0, #0x200\n"
	  "LDREQ   R1, =0x4004\n"
	  "LDRNE   R1, =0x8002\n"
	  "MOV     R0, #3\n"
	  "B       loc_FF879098\n"
"loc_FF87904C:\n" //                            ; CODE XREF: sub_FF878FF4+40j
	  "TST     R0, #0x10\n"
	  "BNE     loc_FF879024\n"
	  "TST     R0, #0x40\n"
	  "BEQ     loc_FF879068\n"
"loc_FF87905C:\n" //                            ; CODE XREF: sub_FF878FF4+BCj
	  "MOV     R1, R4\n"
	  "MOV     R0, #1\n"
	  "B       loc_FF879098\n"
"loc_FF879068:\n" //                            ; CODE XREF: sub_FF878FF4+64j
	  "TST     R0, #0x20\n"
	  "BEQ     loc_FF879084\n"
	  "TST     R0, #0x4000\n"
	  "BNE     loc_FF879084\n"
"loc_FF879078:\n" //                            ; CODE XREF: sub_FF878FF4+C8j
	  "MOV     R1, R4\n"
	  "MOV     R0, #0\n"
	  "B       loc_FF879098\n"
"loc_FF879084:\n" //                            ; CODE XREF: sub_FF878FF4+78j
	  "LDR     R1, =0x102\n"
	  "BICS    R1, R1, R0\n"
	  "BNE     loc_FF8790A0\n"
	  "MOV     R1, R4\n"
	  "MOV     R0, #6\n"
"loc_FF879098:\n" //                            ; CODE XREF: sub_FF878FF4+38j
	  "LDMFD   SP!, {R4,LR}\n"
	  "B       sub_FF878E44_my\n"	// BBK_CHECK
"loc_FF8790A0:\n" //                            ; CODE XREF: sub_FF878FF4+98j
	  "TST     R0, #0x100\n"
	  "BNE     loc_FF879024\n"
	  "TST     R0, #0x4000\n"
	  "TSTEQ   R0, #0x400\n"
	  "BNE     loc_FF87905C\n"
	  "TST     R0, #0x200\n"
	  "TSTEQ   R0, #2\n"
	  "BNE     loc_FF879078\n"
	  "TST     R0, #0x40000\n"
	  "BEQ     loc_FF879024\n"
	  "TST     R0, #0x200000\n"
	  "MOVEQ   R1, R4\n"
	  "MOVEQ   R0, #1\n"
	  "BLEQ    sub_FF878E44_my\n" // BBK_CHECK
	  "B       loc_FF879024\n"
    );
}


// Extracted method: sub_FF878E44 (FF878E44-FF8709B8)
// Overridden calls:
//     sub_FF878000
//     sub_FF878000
void __attribute__((naked,noinline)) sub_FF878E44_my() {
    asm volatile (
        "STMFD   SP!, {R4-R6,LR}\n"
        "MOVS    R4, R0\n"
        "MOV     R0, #1\n"
        "MOV     R5, R1\n"
        "BNE     loc_FF878E84\n"
        "MOV     R1, #0\n"
        "MOV     R0, #0\n"
        "BL      sub_FF876158\n"
        "BL      sub_FF82AF30\n"
        "SUB     R12, R0, #0x1000\n"
        "SUBS    R12, R12, #0x5B\n"
        "BNE     loc_FF878E7C\n"

"loc_FF878E74:\n" //                            ; CODE XREF: sub_FF878E44+44j
        "BL      sub_FF878D98\n"
        "B       loc_FF878E8C\n"
 

"loc_FF878E7C:\n" //                            ; CODE XREF: sub_FF878E44+2Cj
        "BL      sub_FF878DD8\n"
        "B       loc_FF878E8C\n"
 

"loc_FF878E84:\n" //                            ; CODE XREF: sub_FF878E44+10j
        "CMP     R4, #5\n"
        "BEQ     loc_FF878E74\n"

"loc_FF878E8C:\n" //                            ; CODE XREF: sub_FF878E44+34j

        "CMP     R0, #0\n"
        "LDREQ   R5, =0x1162\n"
        "MOVEQ   R4, #2\n"
        "MOV     R0, R4\n"
        "MOV     R1, R5\n"
        "LDMFD   SP!, {R4-R6,LR}\n"
        "B       sub_FF878000\n"
    );
}


// Extracted method: sub_FF878000 (FF86FB00-FF86FDFC)
// Overridden calls:
void __attribute__((naked,noinline)) sub_FF878000_my() {
    asm volatile (
        "STMFD   SP!, {R4-R8,LR}\n"
        "MOV     R8, R1\n"
        "MOV     R4, R0\n"
        "BL      _GetVRAMHPixelsSize_1\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF8782F0\n"
        "MOV     R1, R8\n"
        "MOV     R0, R4\n"
        "BL      sub_FF876C8C\n"
        "LDR     R5, =0x5D90\n"
        "MOV     R7, #1\n"
        "LDR     R0, [R5,#0x10]\n"
        "MOV     R6, #0\n"
        "CMP     R0, #0x16\n"
        "ADDLS   PC, PC, R0,LSL#2\n"
        "B       loc_FF8782F0\n"
 

"loc_FF878040:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF87809C\n"
 

"loc_FF878044:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8780C4\n"
 

"loc_FF878048:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF878108\n"
 

"loc_FF87804C:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8781C0\n"
 

"loc_FF878050:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8781D0\n"
 

"loc_FF878054:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8782F0\n"
 

"loc_FF878058:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8782F0\n"
 

"loc_FF87805C:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF87824C\n"
 

"loc_FF878060:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8780AC\n"
 

"loc_FF878064:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8780B8\n"
 

"loc_FF878068:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF87824C\n"
 

"loc_FF87806C:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8780FC\n"
 

"loc_FF878070:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8782F0\n"
 

"loc_FF878074:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8782F0\n"
 

"loc_FF878078:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF878114\n"
 

"loc_FF87807C:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF878120\n"
 

"loc_FF878080:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF878194\n"
 

"loc_FF878084:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8780D0\n"
 

"loc_FF878088:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8782D8\n"
 

"loc_FF87808C:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF878258\n"
 

"loc_FF878090:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF878288\n"
 

"loc_FF878094:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF878288\n"
 

"loc_FF878098:\n" //                            ; CODE XREF: sub_FF878000+38j
        "B       loc_FF8781DC\n"
 

"loc_FF87809C:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R1, R8\n"
        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF877744_my\n"
 

"loc_FF8780AC:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF878A48\n"
 

"loc_FF8780B8:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF877BF8\n"
 

"loc_FF8780C4:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF877328\n"
 

"loc_FF8780D0:\n" //                            ; CODE XREF: sub_FF878000+38j


        "SUB     R12, R4, #0x1000\n"
        "SUBS    R12, R12, #0xA5\n"
        "STREQ   R7, [R5,#0x88]\n"
        "BEQ     loc_FF8782E8\n"
        "SUB     R12, R4, #0x3000\n"
        "SUBS    R12, R12, #6\n"
        "BNE     loc_FF8782F0\n"
        "MOV     R0, #0\n"
        "BL      sub_FF82A3B8\n"
        "BL      sub_FF878928\n"
        "B       loc_FF8782E8\n"
 

"loc_FF8780FC:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF878960\n"
 

"loc_FF878108:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF877500\n"
 

"loc_FF878114:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF877DA4\n"
 

"loc_FF878120:\n" //                            ; CODE XREF: sub_FF878000+38j


        "SUB     R12, R4, #0x3200\n"
        "SUBS    R12, R12, #2\n"
        "BNE     loc_FF8782F0\n"
        "MOV     R0, #3\n"
        "BL      sub_FF876B70\n"
        "MOV     R0, #8\n"
        "BL      sub_FF82A30C\n"
        "MOV     R1, #0\n"
        "MOV     R0, #0x19\n"
        "BL      sub_FF838E14\n"
        "BL      sub_FF879F7C\n"
        "BL      sub_FF87A214\n"
        "BL      sub_FF87962C\n"
        "B       loc_FF8782E8\n"

"loc_FF878194:\n" //                            ; CODE XREF: sub_FF878000+38j

        "SUB     R12, R4, #0x3300\n"
        "SUBS    R12, R12, #1\n"
        "BNE     loc_FF8782F0\n"
        "LDR     R0, =0x4010\n"
        "STR     R6, [R5,#0x80]\n"
        "BL      sub_FF82A30C\n"
        "BL      sub_FF9A0080\n"
        "BL      sub_FF87962C\n"
        "MOV     R0, #4\n"
        "BL      sub_FF876B70\n"
        "B       loc_FF8782E8\n"
 

"loc_FF8781C0:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R1, R8\n"
        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF877F00\n"
 

"loc_FF8781D0:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF878B8C\n"
 

"loc_FF8781DC:\n" //                            ; CODE XREF: sub_FF878000+38j


        "LDR     R8, =0x1182\n"
        "CMP     R4, R8\n"
        "STREQ   R7, [R5,#0xB8]\n"
        "BEQ     loc_FF8782E8\n"
        "SUB     R12, R4, #0x1000\n"
        "SUBS    R12, R12, #0x1AC\n"
        "BEQ     loc_FF878234\n"
        "SUB     R12, R4, #0x3000\n"
        "SUBS    R12, R12, #0x224\n"
        "BNE     loc_FF8782F0\n"
        "MOV     R0, #8\n"
        "BL      sub_FF82A30C\n"
        "MOV     R0, #3\n"
        "BL      sub_FF876B70\n"
        "STR     R6, [R5,#0xBC]\n"
        "LDR     R0, [R5,#0xB8]\n"
        "CMP     R0, #0\n"
        "MOVNE   R1, #0\n"
        "MOVNE   R0, R8\n"
        "STRNE   R6, [R5,#0xB8]\n"
        "BLNE    sub_FF877F00\n"
        "B       loc_FF8782E8\n"
 

"loc_FF878234:\n" //                            ; CODE XREF: sub_FF878000+1F4j
        "LDR     R0, [R5,#0xBC]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF8782E8\n"
        "BL      sub_FF99DF60\n"
        "STR     R7, [R5,#0xBC]\n"
        "B       loc_FF8782E8\n"
 

"loc_FF87824C:\n" //                            ; CODE XREF: sub_FF878000+38j


        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4-R8,LR}\n"
        "B       sub_FF877AF0\n"
 

"loc_FF878258:\n" //                            ; CODE XREF: sub_FF878000+38j


        "LDR     R12, =0x10B0\n"
        "CMP     R4, R12\n"
        "BEQ     loc_FF878284\n"
        "BGT     loc_FF878290\n"
        "CMP     R4, #4\n"
        "BEQ     loc_FF8782B8\n"
        "SUB     R12, R4, #0x1000\n"
        "SUBS    R12, R12, #0xAA\n"
        "SUBNE   R12, R4, #0x1000\n"
        "SUBNES  R12, R12, #0xAE\n"
        "BNE     loc_FF8782F0\n"

"loc_FF878284:\n" //                            ; CODE XREF: sub_FF878000+260j
        "BL      sub_FF876874\n"

"loc_FF878288:\n" //                            ; CODE XREF: sub_FF878000+38j

        "MOV     R0, R6\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
 

"loc_FF878290:\n" //                            ; CODE XREF: sub_FF878000+264j
        "SUB     R12, R4, #0x2000\n"
        "SUBS    R12, R12, #4\n"
        "BEQ     loc_FF8782D0\n"
        "SUB     R12, R4, #0x5000\n"
        "SUBS    R12, R12, #1\n"
        "SUBNE   R12, R4, #0x5000\n"
        "SUBNES  R12, R12, #6\n"
        "BNE     loc_FF8782F0\n"
        "BL      sub_FF8772C8\n"
        "B       loc_FF8782E8\n"
 

"loc_FF8782B8:\n" //                            ; CODE XREF: sub_FF878000+26Cj
        "LDR     R0, [R5,#0x2C]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF8782D0\n"
        "BL      sub_FF8784CC\n"
        "BL      sub_FF824F9C\n"
        "B       loc_FF8782E8\n"
 

"loc_FF8782D0:\n" //                            ; CODE XREF: sub_FF878000+298j

        "BL      sub_FF8768B0\n"
        "B       loc_FF8782E8\n"
 

"loc_FF8782D8:\n" //                            ; CODE XREF: sub_FF878000+38j


        "SUB     R12, R4, #0x3000\n"
        "SUBS    R12, R12, #0x130\n"
        "BNE     loc_FF8782F0\n"
        "BL      sub_FF876970\n"

"loc_FF8782E8:\n" //                            ; CODE XREF: sub_FF878000+DCj

        "MOV     R0, #0\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
 

"loc_FF8782F0:\n" //                            ; CODE XREF: sub_FF878000+14j



        "MOV     R0, #1\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
        ".LTORG\n"
    );
}


// Extracted method: sub_FF86F224 (FF86F224-FF86F424)
// Overridden calls:
//     sub_FF82BE84
//     sub_FF86ED10
void __attribute__((naked,noinline)) sub_FF877744_my() {
    asm volatile (
        "STMFD   SP!, {R4-R8,LR}\n"
        "LDR     R7, =0x8002\n"
        "LDR     R4, =0x5D90\n"
        "CMP     R0, #3\n"
        "MOV     R6, R1\n"
        "MOV     R5, #1\n"
        "BEQ     loc_FF87789C\n"
        "BGT     loc_FF877780\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FF8777C4\n"
        "CMP     R0, #1\n"
        "BEQ     loc_FF87783C\n"
        "CMP     R0, #2\n"
        "BNE     loc_FF877924\n"
        "B       loc_FF877798\n"
 

"loc_FF877780:\n" //                            ; CODE XREF: sub_FF877744+1Cj
        "CMP     R0, #6\n"
        "STREQ   R5, [R4,#0x28]\n"
        "BEQ     loc_FF877894\n"
        "SUB     R12, R0, #0x2000\n"
        "SUBS    R12, R12, #4\n"
        "BNE     loc_FF877924\n"

"loc_FF877798:\n" //                            ; CODE XREF: sub_FF877744+38j
        "SUB     R12, R6, #0x1100\n"
        "SUBS    R12, R12, #0x62\n"
        "BNE     loc_FF8777B4\n"
        "MOV     R1, R7\n"
        "MOV     R0, #0\n"
        "BL      sub_FF87A95C\n"
        "STR     R5, [R4,#0x60]\n"

"loc_FF8777B4:\n" //                            ; CODE XREF: sub_FF877744+5Cj
        "BL      sub_FF879F7C\n"
        "BL      sub_FF87A214\n"
        "BL      sub_FF87722C\n"
        "B       loc_FF87791C\n"
 

"loc_FF8777C4:\n" //                            ; CODE XREF: sub_FF877744+24j
        "MOV     R0, #7\n"
        "BL      sub_FF876B70\n"
        "MOV     R0, R7\n"
        "BL      sub_FF82A30C\n"
        "BL      _taskcreate_CommonDrivers\n"
        "BL      sub_FF879DE4\n"
        "LDR     R1, =0xFF87795C\n" // aAcBootrec  ; "AC:BootRec"\n"
        "MOV     R0, #0x20\n"
        "STR     R6, [R4,#0x18]\n"
        "BL      sub_FF86A62C\n"
        "LDR     R1, =0xFF87796\n" // "AC:InitLens"\n"
        "MOV     R0, #0x20\n"
        "BL      sub_FF86A62C\n"
        "STR     R5, [R4,#0x28]\n"
        "BL      sub_FF82A48C\n"
        "BL      sub_FF82A3E0\n"
        "LDR     R0, [R4,#0x1C]\n"
        "LDR     R1, [R4,#0x20]\n"
        "ORRS    R0, R0, R1\n"
        "BLNE    sub_FF8784A8\n"
        "LDR     R0, [R4,#0x68]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF877828\n"
        "BL      _taskcreate_StartupImage\n"
        "B       loc_FF877830\n"
 

"loc_FF877828:\n" //                            ; CODE XREF: sub_FF877744+D8j
        "BL      sub_FF824D2C\n"
        "BL      sub_FF82AEC8\n"

"loc_FF877830:\n" //                            ; CODE XREF: sub_FF877744+E0j
        "BL      taskcreate_InitFileModules_my\n"
        "BL      sub_FF879298\n"
        "B       loc_FF87791C\n"
 

"loc_FF87783C:\n" //                            ; CODE XREF: sub_FF877744+2Cj
        "MOV     R0, #8\n"
        "BL      sub_FF876B70\n"
        "BL      _taskcreate_CommonDrivers\n"
        "BL      sub_FF879DE4\n"
        "LDR     R1, =0xFF877974\n"  // ; "AC:BootPB"\n"
        "MOV     R0, #0x20\n"
        "BL      sub_FF86A62C\n"
        "BL      taskcreate_InitFileModules_my\n"
        "BL      sub_FF87932C\n"
        "BL      sub_FF82AE8C\n"
        "LDR     R0, =0x4004\n"
        "BL      sub_FF82A30C\n"        // ----------------> movie rec
        "LDR     R0, [R4,#0x68]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF877880\n"
        "BL      _taskcreate_StartupImage\n"
        "B       loc_FF877884\n"
 

"loc_FF877880:\n" //                            ; CODE XREF: sub_FF877744+130j
        "BL      sub_FF824D2C\n"

"loc_FF877884:\n" //                            ; CODE XREF: sub_FF877744+138j
        "BL      sub_FF8792C8\n"
        "LDR     R0, [R4,#0x30]\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FF87791C\n"

"loc_FF877894:\n" //                            ; CODE XREF: sub_FF877744+44j
        "BL      sub_FF8784F0\n"
        "B       loc_FF87791C\n"
 

"loc_FF87789C:\n" //                            ; CODE XREF: sub_FF877744+18j
        "MOV     R1, R6\n"
        "MOV     R0, #0\n"
        "BL      sub_FF87A95C\n"
        "LDR     R1, =0xFF877984\n"            //aAcBootclock ; "AC:BootClock"\n"
        "MOV     R0, #0x20\n"
        "BL      sub_FF86A62C\n"
        "STR     R5, [R4,#0x68]\n"
        "BL      sub_FF87932C\n"
        "BL      sub_FF82AE8C\n"
        "BL      sub_FF878484\n"
        "BL      sub_FF82AF24\n"
        "CMP     R0, #0\n"
        "LDRNE   R0, =0x804D\n"
        "MOVNE   R1, #0\n"
        "BLNE    _j_PTM_SetCurrentItem\n"
        "BL      sub_FF87A790\n"
        "MOV     R0, #0x80\n"
        "BL      sub_FF82A30C\n"     // movie rec
        "BL      sub_FF87A15C\n"
        "BL      _StartGUISystem\n"
        "BL      sub_FF95DA78\n"
        "BL      sub_FF9A307C\n"
        "BL      sub_FF879B18\n"
        "BL      sub_FF879FB4\n"
        "MOV     R0, #9\n"
        "BL      sub_FF876B70\n"
        "LDR     R0, =0x300E\n"
        "MOV     R1, R6\n"
        "BL      _PostLogicalEventToUI\n"
        "MOV     R1, #0\n"
        "MOV     R0, #1\n"
        "BL      sub_FF87A95C\n"

"loc_FF87791C:\n" //                            ; CODE XREF: sub_FF877744+7Cj

        "MOV     R0, #0\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
 

"loc_FF877924:\n" //                            ; CODE XREF: sub_FF877744+34j

        "MOV     R0, #1\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
    );
}



void __attribute__((naked,noinline)) taskcreate_InitFileModules_my() { //#fs
        asm volatile (
		"LDR     R0, =0x5E68\n"
		"STMFD   SP!, {R3,LR}\n"
		"LDR     R1, [R0,#4]\n"
		"CMP     R1, #0\n"
		"BNE     locret_FF879258\n"
		"MOV     R1, #1\n"
		"STR     R1, [R0,#4]\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP]\n"
		"LDR     R3, =task_InitFileModules_my\n" // continue for SDHC-boot
		"MOV     R1, #0x19\n"
		"LDR     R0, =0xFF879384\n"  // aInitfilemodule
		"MOV     R2, #0x1000\n"
		"BL     _CreateTask\n"

	"locret_FF879258:\n"
		"LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe


void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs  
        asm volatile (
        "STMFD   SP!, {R4-R6,LR}\n"
        "BL      sub_FF86DAE8\n"
        "LDR     R5, =0x5006\n"
        "MOVS    R4, R0\n"
        "MOVNE   R1, #0\n"
        "MOVNE   R0, R5\n"
        "BLNE    _PostLogicalEventToUI\n"
        "BL      sub_FF86DB14_my\n"
        "BL      core_spytask_can_start\n"  // CHDK: Set "it's-safe-to-start" -flag for spytask
        "CMP     R4, #0\n"
        "MOVEQ   R0, R5\n"
        "LDMEQFD SP!, {R4-R6,LR}\n"
        "MOVEQ   R1, #0\n"
        "BEQ     _PostLogicalEventToUI\n"
        "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF86DB14_my() { //#fs  
        asm volatile (
        "STMFD   SP!, {R4,LR}\n"
        "BL      sub_FF84F174_my\n"  // continue to SDHC-hook here
        "LDR     R4, =0x57D0\n"
        "LDR     R0, [R4,#4]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF86DB44\n"
        "BL      sub_FF881C08\n"
        "BL      sub_FF9055FC\n"
        "BL      sub_FF881C08\n"
        "BL      sub_FF84CB64\n"
        "BL      sub_FF881C18\n"
        "BL      sub_FF9056C8\n"

"loc_FF86DB44:\n" //                            ; CODE XREF: sub_FF86DB14+14j
        "MOV     R0, #1\n"
        "STR     R0, [R4]\n"
        "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF84F174_my() { //#fs  
        asm volatile (
        "STMFD   SP!, {R4-R6,LR}\n"
        "MOV     R6, #0\n"
        "MOV     R0, R6\n"
        "BL      sub_FF84EC34\n"
        "LDR     R4, =0x11890\n"
        "MOV     R5, #0\n"
        "LDR     R0, [R4,#0x38]\n"
        "BL      sub_FF84F668\n"
        "CMP     R0, #0\n"
        "LDREQ   R0, =0x29D4\n"
        "STREQ   R5, [R0,#0x10]\n"
        "STREQ   R5, [R0,#0x14]\n"
        "STREQ   R5, [R0,#0x18]\n"
        "MOV     R0, R6\n"
        "BL      sub_FF84EC74\n" //uMounter (u=unknown, just to prevent misunderstandings)
        "MOV     R0, R6\n"
        "BL      sub_FF84EFB0_my\n" // continue to SDHC-hook here!
        "MOV     R5, R0\n"
        "MOV     R0, R6\n"
        "BL      sub_FF84F01C\n"
        "LDR     R1, [R4,#0x3C]\n"
        "AND     R2, R5, R0\n"
        "CMP     R1, #0\n"
        "MOV     R0, #0\n"
        "MOVEQ   R0, #0x80000001\n"
        "BEQ     loc_FF84F208\n"
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

"loc_FF84F208:\n" //                            ; CODE XREF: sub_FF84F174+64j
        "STR     R0, [R4,#0x40]\n"
        "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FF84EFB0_my() { //#fs  
        asm volatile (
        "STMFD   SP!, {R4-R6,LR}\n"
        "LDR     R5, =0x29D4\n"
        "MOV     R6, R0\n"
        "LDR     R0, [R5,#0x14]\n"
        "CMP     R0, #0\n"
        "MOVNE   R0, #1\n"
        "LDMNEFD SP!, {R4-R6,PC}\n"
        "MOV     R0, #0x17\n"
        "MUL     R1, R0, R6\n"
        "LDR     R0, =0x11890\n"
        "ADD     R4, R0, R1,LSL#2\n"
        "LDR     R0, [R4,#0x38]\n"
        "MOV     R1, R6\n"
        "BL      sub_FF84ED40_my\n" //continue to SDHC-hook here
        "CMP     R0, #0\n"
        "LDMEQFD SP!, {R4-R6,PC}\n"
        "LDR     R0, [R4,#0x38]\n"
        "MOV     R1, R6\n"
        "BL      sub_FF84EEA8\n"
        "CMP     R0, #0\n"
        "LDMEQFD SP!, {R4-R6,PC}\n"
        "MOV     R0, R6\n"
        "BL      sub_FF84E83C\n"
        "CMP     R0, #0\n"
        "MOVNE   R1, #1\n"
        "STRNE   R1, [R5,#0x14]\n"
        "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe



void __attribute__((naked,noinline)) sub_FF84ED40_my() { //#fs  ; Partition t
        asm volatile (
        "STMFD   SP!, {R4-R8,LR}\n"
        "MOV     R8, R0\n"
        "MOV     R0, #0x17\n"
        "MUL     R1, R0, R1\n"
        "LDR     R0, =0x11890\n"
        "MOV     R6, #0\n"
        "ADD     R7, R0, R1,LSL#2\n"
        "LDR     R0, [R7,#0x3C]\n"
        "MOV     R5, #0\n"
        "CMP     R0, #6\n"
        "ADDLS   PC, PC, R0,LSL#2\n"
        "B       loc_FF84EE8C\n"
 

"loc_FF84ED70:\n" //                            ; CODE XREF: sub_FF84ED40+28j
        "B       loc_FF84EDA4\n"
 

"loc_FF84ED74:\n" //                            ; CODE XREF: sub_FF84ED40+28j
        "B       loc_FF84ED8C\n"
 

"loc_FF84ED78:\n" //                            ; CODE XREF: sub_FF84ED40+28j
        "B       loc_FF84ED8C\n"
 

"loc_FF84ED7C:\n" //                            ; CODE XREF: sub_FF84ED40+28j
        "B       loc_FF84ED8C\n"
 

"loc_FF84ED80:\n" //                            ; CODE XREF: sub_FF84ED40+28j
        "B       loc_FF84ED8C\n"
 

"loc_FF84ED84:\n" //                            ; CODE XREF: sub_FF84ED40+28j
        "B       loc_FF84EE84\n"
 

"loc_FF84ED88:\n" //                            ; CODE XREF: sub_FF84ED40+28j
        "B       loc_FF84ED8C\n"

"loc_FF84ED8C:\n" //                            ; CODE XREF: sub_FF84ED40+28j


        "MOV     R2, #0\n"
        "MOV     R1, #0x200\n"
        "MOV     R0, #3\n"
        "BL      sub_FF867C94\n"
        "MOVS    R4, R0\n"
        "BNE     loc_FF84EDAC\n"

"loc_FF84EDA4:\n" //                            ; CODE XREF: sub_FF84ED40+28j


        "MOV     R0, #0\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
 

"loc_FF84EDAC:\n" //                            ; CODE XREF: sub_FF84ED40+60j
        "LDR     R12, [R7,#0x4C]\n"
        "MOV     R3, R4\n"
        "MOV     R2, #1\n"
        "MOV     R1, #0\n"
        "MOV     R0, R8\n"
        //"BLX     R12 //\n"
        "MOV     LR, PC\n"
        "MOV     PC, R12\n"
        "CMP     R0, #1\n"
        "BNE     loc_FF84EDD8\n"
        "MOV     R0, #3\n"
        "BL      sub_FF867DD4\n"
        "B       loc_FF84EDA4\n"
 

"loc_FF84EDD8:\n" //                            ; CODE XREF: sub_FF84ED40+88j
        "MOV     R0, R8\n"
        "BL      sub_FF922E24\n"
        
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
        "LDRB    R1, [R4,#0x1C9]\n"
        "LDRB    R3, [R4,#0x1C8]\n"
        "LDRB    R12, [R4,#0x1CC]\n"
        "MOV     R1, R1,LSL#24\n"
        "ORR     R1, R1, R3,LSL#16\n"
        "LDRB    R3, [R4,#0x1C7]\n"
        "LDRB    R2, [R4,#0x1BE]\n"
        //"LDRB    LR, [R4,#0x1FF]\n"
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
        //"LDRB    R12, [R4,#0x1FE]\n"

	"LDRB    R12, [LR,#0x1FE]\n"
	"LDRB    LR, [LR,#0x1FF]\n"

        "MOV     R4, #0\n"
        "BNE     loc_FF84EE60\n"
        "CMP     R0, R1\n"
        "BCC     loc_FF84EE60\n"
        "ADD     R2, R1, R3\n"
        "CMP     R2, R0\n"
        "CMPLS   R12, #0x55\n"
        "CMPEQ   LR, #0xAA\n"
        "MOVEQ   R6, R1\n"
        "MOVEQ   R5, R3\n"
        "MOVEQ   R4, #1\n"

"loc_FF84EE60:\n" //                            ; CODE XREF: sub_FF84ED40+F8j

        "MOV     R0, #3\n"
        "BL      sub_FF867DD4\n"
        "CMP     R4, #0\n"
        "BNE     loc_FF84EE98\n"
        "MOV     R6, #0\n"
        "MOV     R0, R8\n"
        "BL      sub_FF922E24\n"
        "MOV     R5, R0\n"
        "B       loc_FF84EE98\n"
 

"loc_FF84EE84:\n" //                            ; CODE XREF: sub_FF84ED40+28j


        "MOV     R5, #0x40\n"
        "B       loc_FF84EE98\n"
 

"loc_FF84EE8C:\n" //                            ; CODE XREF: sub_FF84ED40+28j


        "MOV     R1, #0x374\n"
        "LDR     R0, =0xFF84ED34\n" // aMounter_c  ; "Mounter.c"\n"
        "BL      _DebugAssert\n"

"loc_FF84EE98:\n" //                            ; CODE XREF: sub_FF84ED40+12Cj

        "STR     R6, [R7,#0x44]!\n"
        "MOV     R0, #1\n"
        "STR     R5, [R7,#4]\n"
        "LDMFD   SP!, {R4-R8,PC}\n"

	);
}; //#fe

// Extracted method: sub_FF842A44 + 240
// Extracted method: sub_FF842C84
void __attribute__((naked,noinline)) jogdial_task_my()
{
	asm volatile (
		"STMFD   SP!, {R3-R11,LR}\n"
		"BL      sub_FF842e34\n" // LOCATION: JogDial.c:14
		"LDR     R11, =0x80000B01\n"
		"LDR     R8, =0xffab07cc\n"		// HL
		"LDR     R7, =0xC0240000\n"		// HL
		"LDR     R6, =0x22A0\n"				// HL
		"MOV     R9, #1\n"
		"MOV     R10, #0\n"

		"loc_FF842CA4:\n"
		"LDR     R3, =0x1A1\n"			// HL
		"LDR     R0, [R6,#0xC]\n"
		"LDR     R2, =0xFF842EDC\n" // HL?, "JogDial.c"
		"MOV     R1, #0\n"
		"BL      sub_FF81BBD8\n"			// HL
		//"MOV     R0, #40\n"
		"MOV     R0, #40\n" // +
		"BL      _SleepTask\n" // LOCATION: KerSys.c:0

		//------------------  added code ---------------------
		"labelA:\n"
		"LDR     R0, =jogdial_stopped\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #1\n"
		"BNE     labelB\n"
		"MOV     R0, #40\n"
		"BL      _SleepTask\n"
		"B       labelA\n"
		"labelB:\n"
		//------------------  original code ------------------

		"LDR     R0, [R7,#0x104]\n"
		"MOV     R0, R0,ASR#16\n"
		"STRH    R0, [R6]\n"
		"LDRSH   R2, [R6,#2]\n"
		"SUB     R1, R0, R2\n"
		"CMP     R1, #0\n"
		"BEQ     loc_FF842D68\n"
		"MOV     R5, R1\n"
		"RSBLT   R5, R5, #0\n"
		"MOVLE   R4, #0\n"
		"MOVGT   R4, #1\n"
		"CMP     R5, #0xFF\n"
		"BLS     loc_FF842D1C\n"
		"CMP     R1, #0\n"
		"RSBLE   R1, R2, #0xFF\n"
		"ADDLE   R1, R1, #0x7F00\n"
		"ADDLE   R0, R1, R0\n"
		"RSBGT   R0, R0, #0xFF\n"
		"ADDGT   R0, R0, #0x7F00\n"
		"ADDGT   R0, R0, R2\n"
		"ADD     R5, R0, #0x8000\n"
		"ADD     R5, R5, #1\n"
		"EOR     R4, R4, #1\n"

		"loc_FF842D1C:\n"
		"LDR     R0, [R6,#0x14]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF842D60\n"
		"LDR     R0, [R6,#0x1C]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF842D48\n"
		"LDR     R1, [R8,R4,LSL#2]\n"
		"CMP     R1, R0\n"
		"BEQ     loc_FF842D50\n"
		"LDR     R0, =0xB01\n"
		"BL      sub_FF875370\n"

		"loc_FF842D48:\n"
		"MOV     R0, R11\n"
		"BL      sub_FF875370\n"

		"loc_FF842D50:\n"
		"LDR     R0, [R8,R4,LSL#2]\n"
		"MOV     R1, R5\n"
		"STR     R0, [R6,#0x1C]\n"
		"BL      sub_FF8752b8\n"

		"loc_FF842D60:\n"
		"LDRH    R0, [R6]\n"
		"STRH    R0, [R6,#2]\n"

		"loc_FF842D68:\n"
		"STR     R10, [R7,#0x100]\n"
		"STR     R9, [R7,#0x108]\n"
		"LDR     R0, [R6,#0x10]\n"
		"CMP     R0, #0\n"
		"BLNE    _SleepTask\n" // LOCATION: KerSys.c:0
		"B       loc_FF842CA4\n"
		);
}
