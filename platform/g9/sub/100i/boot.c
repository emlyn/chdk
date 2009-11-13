#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "stdlib.h"


const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void taskCreateHook(int *p) { 
 p-=16;
 if (p[0]==0xFF861210)  p[0]=(int)capt_seq_task;
 if (p[0]==0xFF85D4C0)  p[0]=(int)movie_record_task;
 if (p[0]==0xFF877284)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFF8B8B90)  p[0]=(int)exp_drv_task;
}

void taskCreateHook2(int *p) { 
 p-=16;
 if (p[0]==0xFF877284)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFF8B8B90)  p[0]=(int)exp_drv_task;
}

void boot() { 

    long *canon_data_src = (void*)0xFFB2E41C; // OK	//canon_data_src!!!  @FF810130
    long *canon_data_dst = (void*)0x1900;	// OK  //MEMBASEADDR   @FF810134
    long canon_data_len = 0x140E4- 0x1900; // data_end - data_start     
    long *canon_bss_start = (void*)0x140e4; // just after data 	// OK	//@FF810138
    long canon_bss_len = 0xb0b68 - 0x140e4; //  MEMISOSTART - 

    long i;

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

    *(int*)(0x261C+8)= (*(int*)0xC02200C0)&1 ? 1: 2;  // replacement of sub_FF822E10

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
  
	asm volatile ("B      sub_FF8101a4_my\n");  //---------->
	
}; 


void __attribute__((naked,noinline)) sub_FF8101a4_my() {
		asm volatile (	
                "LDR     R0, =0xFF81021C\n"
                "MOV     R1, #0\n"
                "LDR     R3, =0xFF810254\n"
"loc_FF8101B0:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FF8101B0\n"
                "LDR     R0, =0xFF810254\n"
                "MOV     R1, #0x4B0\n"
                "LDR     R3, =0xFF810468\n"
"loc_FF8101CC:\n"
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
                "LDR     R0, =0x6C4\n"
                "LDR     R2, =0xEEEEEEEE\n"
                "MOV     R3, #0x1000\n"
"loc_FF810200:\n"
                "CMP     R0, R3\n"
                "STRCC   R2, [R0],#4\n"
                "BCC     loc_FF810200\n"
                "BL      sub_FF810FB8_my\n" //----------->
      );
				
}; //#fe


//OK
void __attribute__((naked,noinline)) sub_FF810FB8_my() { 
        asm volatile ( 
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFABD420\n"
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
          //       "LDR     R0, =0xB0B68\n"     // -
                 "LDR     R0, =new_sa\n"        // +
                 "LDR     R0, [R0]\n"           // +
                 "LDR     R2, =0x2ABC00\n"
                 "LDR     R1, =0x2A4968\n"
                 "STR     R0, [SP,#8]\n"
                 "SUB     R0, R1, R0\n"
                 "ADD     R3, SP, #0xC\n"
                 "STR     R2, [SP]\n"
                 "STMIA   R3, {R0-R2}\n"
                 "MOV     R0, #0x22\n"
                 "STR     R0, [SP,#0x18]\n"
                 "MOV     R0, #0x68\n"
                 "STR     R0, [SP,#0x1C]\n"
                 "LDR     R0, =0x19B\n"
                 "MOV     R1, #0x64\n"
                 "STRD    R0, [SP,#0x20]\n"
                 "MOV     R0, #0x78\n"
                 "STRD    R0, [SP,#0x28]\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [SP,#0x30]\n"
                 "STR     R0, [SP,#0x34]\n"
                 "MOV     R0, #0x10\n"
                 "STR     R0, [SP,#0x5C]\n"
                 "MOV     R0, #0x800\n"
                 "STR     R0, [SP,#0x60]\n"
                 "MOV     R0, #0xA0\n"
                 "STR     R0, [SP,#0x64]\n"
                 "MOV     R0, #0x280\n"
                 "STR     R0, [SP,#0x68]\n"
                 "LDR     R1, =sub_FF814DBC_my\n"       //---------->
                 "MOV     R0, SP\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF812D70\n"
                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"
	);
}; 


void __attribute__((naked,noinline)) sub_FF814DBC_my() {
	asm volatile (		
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF81095C\n"
                 "BL      sub_FF819948\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814ED0\n"
                 "BLLT    sub_FF814EB0\n"
                 "BL      sub_FF8149E0\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814ED8\n"
                 "BLLT    sub_FF814EB0\n"
                 "LDR     R0, =0xFF814EE8\n"
                 "BL      sub_FF814ACC\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814EF0\n"
                 "BLLT    sub_FF814EB0\n"
                 "LDR     R0, =0xFF814EE8\n"
                 "BL      sub_FF81357C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814F04\n"
                 "BLLT    sub_FF814EB0\n"
                 "BL      sub_FF8194D0\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814F10\n"
                 "BLLT    sub_FF814EB0\n"
                 "BL      sub_FF8114D0\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814F1C\n"
                 "BLLT    sub_FF814EB0\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       taskcreate_Startup_my\n" //---------->
        );
}; 


void __attribute__((naked,noinline)) taskcreate_Startup_my() { 
	asm volatile (		
	
                 "STMFD   SP!, {R3,LR}\n"
          //     "BL      nullsub_3\n"
                 "BL      sub_FF82C8FC\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF81DC4C\n"
                 "BL      sub_FF824568\n"
                 "CMP     R0, #0\n"
                 "LDREQ   R2, =0xC0220000\n"
                 "LDREQ   R0, [R2,#0xC0]\n"
                 "LDREQ   R1, [R2,#0xC4]\n"
                 "ORREQ   R0, R0, R1\n"
                 "TSTEQ   R0, #1\n"
                 "BNE     loc_FF81DC4C\n"
                 "MOV     R0, #0x44\n"
                 "STR     R0, [R2,#0x4C]\n"
 "loc_FF81DC48:\n"
                 "B       loc_FF81DC48\n"
 "loc_FF81DC4C:\n"
            //   "BL      sub_FF822E10\n"  // removed, see boot() function
            //   "BL      nullsub_4\n"
                 "BL      sub_FF82A488\n"
                 "MOV     R1, #0x300000\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF82A6D0\n"
                 "BL      sub_FF82A67C\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =task_Startup_my\n"  //----------->
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x19\n"
                 "LDR     R0, =0xFF81DC90\n"
                 "BL      sub_FF81BAF0\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R12,PC}\n"
 );
}; 


void __attribute__((naked,noinline)) task_Startup_my() { 
       	asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF81517C\n"
                 "BL      sub_FF823FA0\n"
                 "BL      sub_FF820E60\n"
          //     "BL      j_nullsub_134\n"
                 "BL      sub_FF82CADC\n"
          //     "BL      sub_FF82C9C4\n"  // Skip starting diskboot.bin again
		);
        CreateTask_spytask();  // +
        asm volatile (
                 "BL      sub_FF82CCA4\n"
                 "BL      sub_FF82CB2C\n"
                 "BL      sub_FF8299CC\n"
                 "BL      sub_FF82CCA8\n"
         //      "BL      taskcreate_PhySw\n" //-
        );
         CreateTask_PhySw(); // +
        asm volatile (
                 "BL      sub_FF82629C\n"
                 "BL      sub_FF82CCC0\n"
         //      "BL      nullsub_2\n"
                 "BL      sub_FF822130\n"
                 "BL      sub_FF82C6A8\n"
                 "BL      sub_FF8228D4\n"
                 "BL      sub_FF82203C\n"
                 "BL      sub_FF82D720\n"
                 "BL      sub_FF821FF8\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF815088\n"
 );
}; 


void CreateTask_spytask() { 
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; 

void CreateTask_PhySw() { 
        _CreateTask("PhySw", 0x17, 0x800, mykbd_task, 0);
        asm volatile ( "BL      sub_FF84962C\n");	//taskcreate_JogDial
};


void __attribute__((naked,noinline)) init_file_modules_task() { 
  asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FF86FFF8\n"
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FF8711D8\n"
                "BL      sub_FF870024_my\n"             //----------->
                "BL      core_spytask_can_start\n"      // +
                "CMP     R4, #0\n"
                "MOVEQ   R0, R5\n"
                "LDMEQFD SP!, {R4-R6,LR}\n"
                "MOVEQ   R1, #0\n"
                "BEQ     sub_FF8711D8\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
 );
}; 


void __attribute__((naked,noinline)) sub_FF870024_my() { 
 asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FF85235C_my\n"   //----------->
                "LDR     R4, =0x5AC4\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF870054\n"
                "BL      sub_FF87FD60\n"
                "BL      sub_FF90B9B4\n"
                "BL      sub_FF87FD60\n"
                "BL      sub_FF918508\n"
                "BL      sub_FF87FD70\n"
                "BL      sub_FF90BA5C\n"
"loc_FF870054:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4]\n"
                "LDMFD   SP!, {R4,PC}\n"
 );
}; 


void __attribute__((naked,noinline)) sub_FF85235C_my() {
 asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOV     R6, #0\n"
                "MOV     R0, R6\n"
                "BL      sub_FF851F2C\n"
                "LDR     R4, =0x168D0\n"
                "MOV     R5, #0\n"
                "LDR     R0, [R4,#0x38]\n"
                "BL      sub_FF8528F4\n"
                "CMP     R0, #0\n"
                "LDREQ   R0, =0x2D34\n"
                "STREQ   R5, [R0,#0xC]\n"
                "STREQ   R5, [R0,#0x10]\n"
                "STREQ   R5, [R0,#0x14]\n"
                "MOV     R0, R6\n"
                "BL      sub_FF851F6C\n"
                "MOV     R0, R6\n"
                "BL      sub_FF852198_my\n"  //-------------->
                "MOV     R5, R0\n"
                "MOV     R0, R6\n"
                "BL      sub_FF852204\n"
                "LDR     R1, [R4,#0x3C]\n"
                "AND     R2, R5, R0\n"
                "CMP     R1, #0\n"
                "MOV     R0, #0\n"
                "MOVEQ   R0, #0x80000001\n"
                "BEQ     loc_FF8523F0\n"
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
"loc_FF8523F0:\n"
                "STR     R0, [R4,#0x40]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
 );
}; 


void __attribute__((naked,noinline)) sub_FF852198_my() {
 asm volatile (
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "LDR     R5, =0x2D34\n"
                 "MOV     R6, R0\n"
                 "LDR     R0, [R5,#0x10]\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R0, #1\n"
                 "LDMNEFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, #0x17\n"
                 "MUL     R1, R0, R6\n"
                 "LDR     R0, =0x168D0\n"
                 "ADD     R4, R0, R1,LSL#2\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R6\n"
                 "BL      sub_FF852030_my\n"  //-------------->
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R6\n"
                 "BL      sub_FF852A0C\n"
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FF851B4C\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R1, #1\n"
                 "STRNE   R1, [R5,#0x10]\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
};


void __attribute__((naked,noinline)) sub_FF852030_my() {
 asm volatile (	
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R0\n"
                 "MOV     R0, #0x17\n"
                 "MUL     R1, R0, R1\n"
                 "LDR     R0, =0x168D0\n"
                 "MOV     R6, #0\n"
                 "ADD     R7, R0, R1,LSL#2\n"
                 "LDR     R0, [R7,#0x3C]\n"
                 "MOV     R5, #0\n"
                 "CMP     R0, #6\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FF85217C\n"
 "loc_FF852060:\n"
                 "B       loc_FF852094\n"
 "loc_FF852064:\n"
                 "B       loc_FF85207C\n"
 "loc_FF852068:\n"
                 "B       loc_FF85207C\n"
 "loc_FF85206C:\n"
                 "B       loc_FF85207C\n"
 "loc_FF852070:\n"
                 "B       loc_FF85207C\n"
 "loc_FF852074:\n"
                 "B       loc_FF852174\n"
 "loc_FF852078:\n"
                 "B       loc_FF85207C\n"
 "loc_FF85207C:\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x200\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF86C4D0\n"
                 "MOVS    R4, R0\n"
                 "BNE     loc_FF85209C\n"
 "loc_FF852094:\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FF85209C:\n"
                 "LDR     R12, [R7,#0x4C]\n"
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF8520C8\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF86C610\n"
                 "B       loc_FF852094\n"
 "loc_FF8520C8:\n"
                 "MOV     R0, R8\n"
                 "BL      sub_FF9290BC\n"

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
           //    "LDRB    LR, [R4,#0x1FF]\n"          // replaced, see below
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
               //"LDRB    R12, [R4,#0x1FE]\n"     // replaced, see below

                 "LDRB    R12, [LR,#0x1FE]\n"        // New! First MBR signature byte (0x55)
                 "LDRB    LR, [LR,#0x1FF]\n"         //      Last MBR signature byte (0xAA)				

                 "MOV     R4, #0\n"
                 "BNE     loc_FF852150\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FF852150\n"
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R6, R1\n"
                 "MOVEQ   R5, R3\n"
                 "MOVEQ   R4, #1\n"
 "loc_FF852150:\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF86C610\n"
                 "CMP     R4, #0\n"
                 "BNE     loc_FF852188\n"
                 "MOV     R6, #0\n"
                 "MOV     R0, R8\n"
                 "BL      sub_FF9290BC\n"
                 "MOV     R5, R0\n"
                 "B       loc_FF852188\n"
 "loc_FF852174:\n"
                 "MOV     R5, #0x40\n"
                 "B       loc_FF852188\n"
 "loc_FF85217C:\n"
                 "LDR     R1, =0x365\n"
                 "LDR     R0, =0xFF852024\n"
                 "BL      sub_FF81BFC8\n"
 "loc_FF852188:\n"
                 "STR     R6, [R7,#0x44]!\n"
                 "MOV     R0, #1\n"
                 "STR     R5, [R7,#4]\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}; 


// I could not manually find this function in the S5IS firmware, possibly signatures
// might find it. Until that moment, I hooked it here (copied from another camera)
unsigned long __attribute__((naked,noinline)) _time(unsigned long *timer) {
     asm volatile (
          "STMFD   SP!, {R3-R5,LR}\n"
          "MOV     R4, R0\n"
          "MVN     R0, #0\n"
          "STR     R0, [SP,#0x10-0x10]\n"
          "MOV     R0, SP\n"
          "BL      sub_FF86BAEC\n" // _GetTimeOfSystem\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC55F38\n"
          "CMP     R4, #0\n"
          "LDRNE   R0, [SP,#0x10-0x10]\n"
          "STRNE   R0, [R4]\n"

     "loc_FFC55F38:\n"
          "LDR     R0, [SP,#0x10-0x10]\n"
          "LDMFD   SP!, {R3-R5,PC}\n"
     );
   return 0;  // shut up the compiler
}

