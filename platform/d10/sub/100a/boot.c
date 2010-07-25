#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_spytask();
void boot();
void task_CaptSeqTask_my();

void taskCreateHook(int *p) { 
 p-=17;
 if (p[0]==0xFF87B84C)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFF860F34)  p[0]=(int)task_CaptSeqTask_my;
 /*
 if (p[0]==0x)  p[0]=(int)movie_record_task;
 */
}

/*
void taskCreateHook2(int *p) {
 p-=17;
}
*/


#define DEBUG_LED ((unsigned volatile *)0xC0220130) // RED
#define GREEN_LED ((unsigned volatile *)0xC0220134) // GREEN
void boot() {
    long *canon_data_src = (void*)0xFFB4EFA4;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xCDA0 - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xCDA0; // just after data 
    long canon_bss_len = 0x146A2C - 0xCDA0; 

    long i;

	*DEBUG_LED = 0x44;
	*GREEN_LED = 0x46;

    // enable caches and write buffer... this is a carryover from old dryos ports, may not be useful
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

// see http://chdk.setepontos.com/index.php/topic,2972.msg30712.html#msg30712
// this works for init_file_modules task in both play and rec mode
    *(int*)0x1934=(int)taskCreateHook;
// this does not start init_file_modules task ever
//    *(int*)0x1938=(int)taskCreateHook2;

	// Search on 0x12345678 finds function called by sub_FF849EB0, values found there OK
    *(int*)(0x2444)= (*(int*)0xC02200F8)&1 ? 0x200000 : 0x100000; 

    // jump to init-sequence that follows the data-copy-routine 
    asm volatile ("B      sub_FF8101A0_my\n");
}

void __attribute__((naked,noinline)) sub_FF8101A0_my() {
        asm volatile (
"                LDR     R0, =0xFF810218\n" // exception handler code
"                MOV     R1, #0\n"
"                LDR     R3, =0xFF810250\n"
"loc_FF8101AC:\n"
"                CMP     R0, R3\n"          // load exception vector
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FF8101AC\n"
"                LDR     R0, =0xFF810250\n"
"                MOV     R1, #0x4B0\n"
"                LDR     R3, =0xFF810464\n"
"loc_FF8101C8:\n"
"                CMP     R0, R3\n"          // copy IRQ handler to ITCM starting at 0x4b0, 532 bytes up to 0x6C4
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FF8101C8\n"
"                MOV     R0, #0xD2\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = IRQ, ints disabled
"                MOV     SP, #0x1000\n"     // irq mode SP
"                MOV     R0, #0xD3\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = Super, ints disabled
"                MOV     SP, #0x1000\n"     // super mode SP
"                LDR     R0, =0x6C4\n"
"                LDR     R2, =0xEEEEEEEE\n"
"                MOV     R3, #0x1000\n"
"loc_FF8101FC:\n"
"                CMP     R0, R3\n"          // clear ITCM 0x6C4-end with EEEEEEEE
"                STRCC   R2, [R0],#4\n"
"                BCC     loc_FF8101FC\n"
"                BL      sub_FF810FC4_my\n" //->
        );
}

void __attribute__((naked,noinline)) sub_FF810FC4_my() {
	asm volatile (
"                STR     LR, [SP,#-4]!\n"
"                SUB     SP, SP, #0x74\n"
"                MOV     R0, SP\n"
"                MOV     R1, #0x74\n"
"                BL      sub_FFACBFBC\n"
"                MOV     R0, #0x53000\n"
"                STR     R0, [SP,#4]\n"
//"                LDR     R0, =0x146A2C\n"
              "LDR     R0, =new_sa\n"
              "LDR     R0, [R0]\n"
"                LDR     R2, =0x2F9C00\n"
"                LDR     R1, =0x2F24A8\n"
"                STR     R0, [SP,#8]\n"
"                SUB     R0, R1, R0\n"
"                ADD     R3, SP, #0xC\n"
"                STR     R2, [SP]\n"
"                STMIA   R3, {R0-R2}\n"
"                MOV     R0, #0x22\n"
"                STR     R0, [SP,#0x18]\n"
"                MOV     R0, #0x68\n"
"                STR     R0, [SP,#0x1C]\n"
"                LDR     R0, =0x19B\n"
"                LDR     R1, =sub_FF814D38_my\n"
"                STR     R0, [SP,#0x20]\n"
"                MOV     R0, #0x96\n"
"                STR     R0, [SP,#0x24]\n"
"                MOV     R0, #0x78\n"
"                STR     R0, [SP,#0x28]\n"
"                MOV     R0, #0x64\n"
"                STR     R0, [SP,#0x2C]\n"
"                MOV     R0, #0\n"
"                STR     R0, [SP,#0x30]\n"
"                STR     R0, [SP,#0x34]\n"
"                MOV     R0, #0x10\n"
"                STR     R0, [SP,#0x5C]\n"
"                MOV     R0, #0x800\n"
"                STR     R0, [SP,#0x60]\n"
"                MOV     R0, #0xA0\n"
"                STR     R0, [SP,#0x64]\n"
"                MOV     R0, #0x280\n"
"                STR     R0, [SP,#0x68]\n"
"                MOV     R0, SP\n"
"                MOV     R2, #0\n"
"                BL      sub_FF812D68\n"
"                ADD     SP, SP, #0x74\n"
"                LDR     PC, [SP],#4\n"
	);
}
void __attribute__((naked,noinline)) sub_FF814D38_my() {
	asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                BL      sub_FF810954\n"
"                BL      sub_FF8190B4\n" // dmSetup
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E4C\n"    // "dmSetup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                BL      sub_FF814974\n"
"                CMP     R0, #0\n"
"                LDRLT   R0,=0xFF814E54\n" // "termDriverInit"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                LDR     R0, =0xFF814E64\n"      // "/_term"
"                BL      sub_FF814A5C\n" // termDeviceCreate
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E6C\n" // "termDeviceCreate"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                LDR     R0, =0xFF814E64\n"      // "/_term"
"                BL      sub_FF813578\n" // stdioSetup
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E80\n" // "stdioSetup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                BL      sub_FF818BCC\n"
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E8C\n" // "stdlibSetup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                BL      sub_FF8114A8\n"
"                CMP     R0, #0\n"
"                LDRLT   R0, =0xFF814E98\n" // "armlib_setup"
"                BLLT    sub_FF814E2C\n" // err_init_task
"                LDMFD   SP!, {R4,LR}\n"
"                B       taskcreate_Startup_my\n"
	);
}

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
	asm volatile (
"                STMFD   SP!, {R3,LR}\n"
//"                BL      j_nullsub_173\n"
"                BL      sub_FF828F44\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF81C29C\n"
"                BL      sub_FF821B88\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF81C29C\n"
"                BL      sub_FF821254\n"
"                LDR     R1, =0xC0220000\n"
"                MOV     R0, #0x44\n"
"                STR     R0, [R1,#0x14]\n"
"                STR     R0, [R1,#0x1C]\n"
"                BL      sub_FF821440\n"
"loc_FF81C298:\n"
"                B       loc_FF81C298\n"
"loc_FF81C29C:\n"
//"                BL      sub_FF821B94\n" // remove for correct power on (hold pwr button for rec)
//"                BL      j_nullsub_174\n"
"                BL      sub_FF8271FC\n"
"                LDR     R1, =0x34E000\n"
"                MOV     R0, #0\n"
"                BL      sub_FF827644\n"
"                BL      sub_FF8273F0\n" // KerSys.c 548
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =task_Startup_my\n"
"                MOV     R2, #0\n"
"                MOV     R1, #0x19\n"
"                LDR     R0, =0xFF81C2E0\n" // aStartup
"                BL      sub_FF81AFAC\n" // eventproc_export_CreateTask
"                MOV     R0, #0\n"
"                LDMFD   SP!, {R12,PC}\n"
	);
}

void CreateTask_blinker();

void __attribute__((naked,noinline)) task_Startup_my() {
	asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                BL      sub_FF815394\n" // taskcreate_ClockSave
"                BL      sub_FF822C70\n"
"                BL      sub_FF820F38\n"
//"                BL      j_nullsub_175\n"
"                BL      sub_FF829168\n"
//"                BL      sub_FF829018\n" // diskboot
"                BL      CreateTask_spytask\n"
"                BL      sub_FF829304\n"
"                BL      sub_FF81FB94\n"
"                BL      sub_FF829198\n"
"                BL      sub_FF8267FC\n"
"                BL      sub_FF829308\n"
"                BL      taskcreatePhySw_my\n"  // we do this here rather than hook so we don't waste the original stack
//"                BL      sub_FF821A88\n" // taskcreate_PhySw
"                BL      sub_FF824ADC\n"
"                BL      sub_FF829320\n"
//"                BL      nullsub_2\n"
"                BL      sub_FF820854\n"
"                BL      sub_FF828D24\n" // taskcreate_Bye
"                BL      sub_FF820EE8\n"
"                BL      sub_FF820760\n" // taskcreate_TempCheck LOCATION: LowBat.c:2
"                BL      sub_FF81FBC8\n"
"                BL      sub_FF829DE8\n"
"                BL      sub_FF820738\n"
"                LDMFD   SP!, {R4,LR}\n"
"                B       sub_FF8154B4\n" // LOCATION: MLHClock.c:0
	);
}

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R4, =0x1C2C\n"
"                LDR     R0, [R4,#0x10]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF821ABC\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =mykbd_task\n" // task_PhySw
//"                MOV     R2, #0x800\n"
"                MOV     R2, #0x2000\n" // stack size for new task_PhySw so we don't have to do stack switch
"                MOV     R1, #0x17\n"
"                LDR     R0, =0xFF821C90\n"      // "PhySw"
"                BL      sub_FF827444\n" // KernelCreateTask LOCATION: KernelMisc.c:19
"                STR     R0, [R4,#0x10]\n"
"loc_FF821ABC:\n"
"                BL      sub_FF87015C\n"
"                BL      sub_FF849F90\n" // IsFactoryMode
"                CMP     R0, #0\n"
"                LDREQ   R1, =0xE244\n"
"                LDMEQFD SP!, {R3-R5,LR}\n"
"                BEQ     sub_FF8700E4\n" // eventproc_export_OpLog_Start
"                LDMFD   SP!, {R3-R5,PC}\n"
	);
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

void __attribute__((naked,noinline)) init_file_modules_task() { 
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 BL      sub_FF87256C\n"
"                 LDR     R5, =0x5006\n"
"                 MOVS    R4, R0\n"
"                 MOVNE   R1, #0\n"
"                 MOVNE   R0, R5\n"
"                 BLNE    sub_FF8773D4\n" // PostLogicalEventToUI
"                 BL      sub_FF872598_my\n" // -> TODO
"                 BL      core_spytask_can_start\n" // + safe to start spytask
"                 CMP     R4, #0\n"
"                 MOVEQ   R0, R5\n"
"                 LDMEQFD SP!, {R4-R6,LR}\n"
"                 MOVEQ   R1, #0\n"
"                 BEQ     sub_FF8773D4\n" // PostLogicalEventToUI
"                 LDMFD   SP!, {R4-R6,PC}\n"
 );
} 

void __attribute__((naked,noinline)) sub_FF872598_my() { 
  asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                MOV     R0, #3\n"
"                BL      sub_FF855974_my\n" // -> (Mounter.c)
//"                BL      nullsub_64\n"
"                LDR     R4, =0x2E20\n"
"                LDR     R0, [R4,#4]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF8725D0\n"
"                BL      sub_FF854D38\n"
"                BL      sub_FF902984\n"
"                BL      sub_FF854D38\n"
"                BL      sub_FF850D8C\n"
"                BL      sub_FF854C38\n"
"                BL      sub_FF902A50\n"
"loc_FF8725D0:\n"
"                MOV     R0, #1\n"
"                STR     R0, [R4]\n"
"                LDMFD   SP!, {R4,PC}\n"

 );
} 

void __attribute__((naked,noinline)) sub_FF855974_my() { 
  asm volatile (
"                STMFD   SP!, {R4-R8,LR}\n"
"                MOV     R6, R0\n"
"                BL      sub_FF8558DC\n" // Mounter.c 0
"                LDR     R1, =0x10770\n"
"                MOV     R5, R0\n"
"                ADD     R4, R1, R0,LSL#7\n"
"                LDR     R0, [R4,#0x70]\n"
"                CMP     R0, #4\n"
"                LDREQ   R1, =0x6D8\n"
"                LDREQ   R0, =0xFF855400\n" // "Mounter.c"
"                BLEQ    sub_FF81B284\n" // DebugAssert
"                MOV     R1, R6\n"
"                MOV     R0, R5\n"
"                BL      sub_FF855348\n" // Mounter.c 0
"                LDR     R0, [R4,#0x38]\n"
"                BL      sub_FF855EA0\n"
"                CMP     R0, #0\n"
"                STREQ   R0, [R4,#0x70]\n"
"                MOV     R0, R5\n"
"                BL      sub_FF855420\n"
"                MOV     R0, R5\n"
"                BL      sub_FF855714_my\n" // ->
"                MOV     R7, R0\n"
"                MOV     R0, R5\n"
"                BL      sub_FF855778\n" // Mounter.c 7
"                LDR     R1, [R4,#0x3C]\n"
"                AND     R2, R7, R0\n"
"                CMP     R1, #0\n"
"                MOV     R0, #0\n"
"                MOVEQ   R0, #0x80000001\n"
"                BEQ     loc_FF855A1C\n"
"                LDR     R3, [R4,#0x2C]\n"
"                CMP     R3, #2\n"
"                MOVEQ   R0, #4\n"
"                CMP     R1, #5\n"
"                ORRNE   R0, R0, #1\n"
"                BICEQ   R0, R0, #1\n"
"                CMP     R2, #0\n"
"                BICEQ   R0, R0, #2\n"
"                ORREQ   R0, R0, #0x80000000\n"
"                BICNE   R0, R0, #0x80000000\n"
"                ORRNE   R0, R0, #2\n"
"loc_FF855A1C:\n"
"                CMP     R6, #7\n"
"                STR     R0, [R4,#0x40]\n"
"                LDMNEFD SP!, {R4-R8,PC}\n"
"                MOV     R0, R6\n"
"                BL      sub_FF85592C\n"
"                CMP     R0, #0\n"
"                LDMEQFD SP!, {R4-R8,LR}\n"
"                LDREQ   R0, =0xFF855C18\n" // "EmemMountError"
"                BEQ     sub_FF8115A8\n" // qPrintf
"                LDMFD   SP!, {R4-R8,PC}\n"

 );
} 

void __attribute__((naked,noinline)) sub_FF855714_my() { 
  asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                MOV     R5, R0\n"
"                LDR     R0, =0x10770\n"
"                ADD     R4, R0, R5,LSL#7\n"
"                LDR     R0, [R4,#0x70]\n"
"                TST     R0, #2\n"
"                MOVNE   R0, #1\n"
"                LDMNEFD SP!, {R4-R6,PC}\n"
"                LDR     R0, [R4,#0x38]\n"
"                MOV     R1, R5\n"
"                BL      sub_FF8554A4_my\n" // -> (Mounter.c)
"                CMP     R0, #0\n"
"                LDMEQFD SP!, {R4-R6,PC}\n"
"                LDR     R0, [R4,#0x38]\n"
"                MOV     R1, R5\n"
"                BL      sub_FF855610\n" // Mounter.c
"                CMP     R0, #0\n"
"                LDMEQFD SP!, {R4-R6,PC}\n"
"                MOV     R0, R5\n"
"                BL      sub_FF854F30\n"
"                CMP     R0, #0\n"
"                LDRNE   R1, [R4,#0x70]\n"
"                ORRNE   R1, R1, #2\n"
"                STRNE   R1, [R4,#0x70]\n"
"                LDMFD   SP!, {R4-R6,PC}\n"
 );
} 
void __attribute__((naked,noinline)) sub_FF8554A4_my() { 
  asm volatile (
"                STMFD   SP!, {R4-R8,LR}\n"
"                MOV     R8, R0\n"
"                LDR     R0, =0x10770\n"
"                MOV     R7, #0\n"
"                ADD     R5, R0, R1,LSL#7\n"
"                LDR     R0, [R5,#0x3C]\n"
"                MOV     R6, #0\n"
"                CMP     R0, #7\n"
"                ADDLS   PC, PC, R0,LSL#2\n"
"                B       loc_FF8555F4\n"
"                B       loc_FF855504\n"
"                B       loc_FF8554EC\n"
"                B       loc_FF8554EC\n"
"                B       loc_FF8554EC\n"
"                B       loc_FF8554EC\n"
"                B       loc_FF8555EC\n"
"                B       loc_FF8554EC\n"
"                B       loc_FF8554EC\n"
"loc_FF8554EC:\n"
// jumptable FF8554C4 entries 1-4,6,7
"                MOV     R2, #0\n"
"                MOV     R1, #0x200\n"
"                MOV     R0, #2\n"
"                BL      sub_FF86C664\n"
"                MOVS    R4, R0\n"
"                BNE     loc_FF85550C\n"
"loc_FF855504:\n"
// jumptable FF8554C4 entry 0
"                MOV     R0, #0\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF85550C:\n"
"                LDR     R12, [R5,#0x4C]\n"
"                MOV     R3, R4\n"
"                MOV     R2, #1\n"
"                MOV     R1, #0\n"
"                MOV     R0, R8\n"
"                BLX     R12\n"
"                CMP     R0, #1\n"
"                BNE     loc_FF855538\n"
"                MOV     R0, #2\n"
"                BL      sub_FF86C7B0\n" // ExMemMan.c 0
"                B       loc_FF855504\n"
"loc_FF855538:\n"

"                LDR     R1, [R5,#0x68]\n"
"                MOV     R0, R8\n"
"                BLX     R1\n"
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
"                LDRB    R1, [R4,#0x1C9]\n"
"                LDRB    R3, [R4,#0x1C8]\n"
"                LDRB    R12, [R4,#0x1CC]\n"
"                MOV     R1, R1,LSL#24\n"
"                ORR     R1, R1, R3,LSL#16\n"
"                LDRB    R3, [R4,#0x1C7]\n"
"                LDRB    R2, [R4,#0x1BE]\n"
//"                LDRB    LR, [R4,#0x1FF]\n"
"                ORR     R1, R1, R3,LSL#8\n"
"                LDRB    R3, [R4,#0x1C6]\n"
"                CMP     R2, #0\n"
"                CMPNE   R2, #0x80\n"
"                ORR     R1, R1, R3\n"
"                LDRB    R3, [R4,#0x1CD]\n"
"                MOV     R3, R3,LSL#24\n"
"                ORR     R3, R3, R12,LSL#16\n"
"                LDRB    R12, [R4,#0x1CB]\n"
"                ORR     R3, R3, R12,LSL#8\n"
"                LDRB    R12, [R4,#0x1CA]\n"
"                ORR     R3, R3, R12\n"
//"                LDRB    R12, [R4,#0x1FE]\n"
"                LDRB    R12, [LR,#0x1FE]\n" // +
"                LDRB    LR, [LR,#0x1FF]\n" // +
"                MOV     R4, #0\n"
"                BNE     loc_FF8555C4\n"
"                CMP     R0, R1\n"
"                BCC     loc_FF8555C4\n"
"                ADD     R2, R1, R3\n"
"                CMP     R2, R0\n"
"                CMPLS   R12, #0x55\n"
"                CMPEQ   LR, #0xAA\n"
"                MOVEQ   R7, R1\n"
"                MOVEQ   R6, R3\n"
"                MOVEQ   R4, #1\n"
"loc_FF8555C4:\n"
"                MOV     R0, #2\n"
"                BL      sub_FF86C7B0\n" // ExMemMan.c 0
"                CMP     R4, #0\n"
"                BNE     loc_FF855600\n"
"                LDR     R1, [R5,#0x68]\n"
"                MOV     R7, #0\n"
"                MOV     R0, R8\n"
"                BLX     R1\n"
"                MOV     R6, R0\n"
"                B       loc_FF855600\n"
"loc_FF8555EC:\n"
// jumptable FF8554C4 entry 5
"                MOV     R6, #0x40\n"
"                B       loc_FF855600\n"
"loc_FF8555F4:\n"
// jumptable FF8554C4 default entry
"                LDR     R1, =0x5C9\n"
"                LDR     R0, =0xFF855400\n"  // "Mounter.c"
"                BL      sub_FF81B1CC\n" // DebugAssert
"loc_FF855600:\n"
"                STR     R7, [R5,#0x44]!\n"
"                MOV     R0, #1\n"
"                STR     R6, [R5,#4]\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
 );
} 

#if 0
const unsigned ledlist[]={
	0xC0220134, // green
	0xC0220130, // red
};
// shamelessly stolen from s5 for debugging
extern void msleep(int x);
void __attribute__((noinline)) task_blinker() {
        int ledstate;

        int counter = 0;

        int *led = (void*) ledlist[0];
		int i_led = 0;

        int *anypointer;       // multi-purpose pointer to poke around in memory
        int v1, v2, v3, v4;    // multi-purpose vars

        ledstate = 0;   // init: led off
        *led = 0x46;      // led on

        while (1) {

                if (ledstate == 1) {    // toggle LED
                        ledstate = 0;
                        *led = 0x44;      // LED off
						led=(void *)ledlist[(++i_led)%2];
                        //core_test(1);
                } else {
                        ledstate = 1;
                        *led = 0x46;      // LED on
                        //core_test(0);
                }

                if (counter == 2) {
                        //dump_chdk();
                        //gui_init();
                        //_ExecuteEventProcedure("UIFS_WriteFirmInfoToFile");
                        //_UIFS_WriteFirmInfoToFile(0);
                }

                if (counter == 10) {
                        //draw_txt_string(2, 2, "test");
                }

                msleep(500);
                counter++;
        }
};

void CreateTask_blinker() {
        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};
#endif

