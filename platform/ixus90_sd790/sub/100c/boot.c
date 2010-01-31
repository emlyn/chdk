#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

void __attribute__((naked,noinline)) jogdial_task_my();

// Forward declarations
//void CreateTask_PhySw();
void CreateTask_spytask();

void taskCreateHook(unsigned int *p)
{
	p-=16;
	if (p[0]==0xFF821ADC)  p[0]=(unsigned int)mykbd_task;
	if (p[0]==0xFF842C84)  p[0]=(unsigned int)jogdial_task_my; 
	if (p[0]==0xFF85A278)  p[0]=(unsigned int)movie_record_task;
	if (p[0]==0xFF85E2b0)  p[0]=(unsigned int)capt_seq_task;
	if (p[0]==0xFF8791D0)  p[0]=(unsigned int)init_file_modules_task;
	if (p[0]==0xFF8b6A80)  p[0]=(unsigned int)exp_drv_task;
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
        "BL      sub_FFAACA5C\n"
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
        "BL      sub_FF824CC8\n" // task_ShootSeqTask
        "BL      sub_FF82A2C8\n"
        //"BL      sub_FF81FB20\n" // nullsub_2
        "BL      sub_FF820FCC\n"
        "BL      sub_FF829CB8\n" // taskcreate_Bye
        "BL      sub_FF821640\n"
        "BL      sub_FF820EBC\n" // taskcreate_TempCheck\n"
        "BL      sub_FF82AD6C\n"
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


// -----------------
// SDHC-Boot-Support
// -----------------

// 0xFF8791d0
void __attribute__((naked,noinline)) init_file_modules_task() { //#fs  
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
		"LDR     R8, =0xffab07d0\n"		// HL
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
