#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "../../sd1200_debug.h"
#include "stdlib.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
/*
long aHookList[128];
long aHookNum=0;
*/

// Forward declarations
void CreateTask_spytask();
//void CreateTask_blinker();
void boot();
//void DumpMemory(char *path, void *start_address, int length);

void taskCreateHook(int *p) {
	// reyalp - ???
	/*
	int i;
	int found=0;

	if (aHookNum < 126)
	{
		if (*(p-17) > 0xFFC00000)
		{
			found=0;
			for (i=0;i<aHookNum;i++)
			{
				if (aHookList[i]==(long)p)
				{
					found=1;
				}
			}
			if (found==0)
			{
				aHookList[aHookNum]=(long)p;
				aHookNum++;
			}
		}

	}
	*/

    p-=17;
    if (p[0] == 0xFFC61374) p[0] = (int) init_file_modules_task;
	//if (p[0]==0xFFC7EE88) p[0]=(int)exp_drv_task; // found for sd1200 but not yet tested
	//if (p[0]==0xFFCCF40C) p[0]=(int)movie_record_task;

//VERIFY_SD780 - MORE?
// if (p[1]==0x)  p[0]=(int)capt_seq_task;
// task_InitFileModules
//if (p[0]==0xFF85D754) p[0]=(int)capt_seq_task;
}

// ??? from sx10
void taskCreateHook2(int *p) {
 p-=17;
 if (p[0] == 0xFFC61374) p[0] = (int) init_file_modules_task;
 //VERIFY_SD780 - Does this need to be here at all anymore?
//Uncomment if (p[0]==0xFF881534)  p[0]=(int)init_file_modules_task;
}

void boot() { //#fs
    int *canon_data_src  = (int *)0xFFECD3E4;  	     //From end of first function
    int *canon_data_dst  = (int *)0x1900;            //From end of first function
    int canon_data_len   = (int *) 0xAEB8 - canon_data_dst;   // data_end - data_start

    int *canon_bss_start = (int *)0xCDAC;           // just after data
    int canon_bss_len    = (int *)0x12AD3C - canon_bss_start; //In loop at end of first function

    long i;
    
    // enable caches and write buffer. Makes things go faster.
    // SD1200 original 0xFFC00088
    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    // SD1200 had trouble with stdioLib so I continued the code from above. It
    // seems only the last chunk was needed.
    asm volatile (/*
"   MOV     R1, #0x80000006\n"
"    MCR     p15, 0, R1,c9,c1\n"
"    MOV     R1, #6\n"
"    MCR     p15, 0, R1,c9,c1, 1\n"
"    MRC     p15, 0, R1,c1,c0\n"
"    ORR     R1, R1, #0x50000\n"
"    MCR     p15, 0, R1,c1,c0\n"
"    LDR     R2, =0xC0200000\n"
"    MOV     R1, #1\n"
"    STR     R1, [R2,#0x10C]\n"
"    MOV     R1, #0xFF\n"
"    STR     R1, [R2,#0xC]\n"
"    STR     R1, [R2,#0x1C]\n"
"    STR     R1, [R2,#0x2C]\n"
"    STR     R1, [R2,#0x3C]\n"
"    STR     R1, [R2,#0x4C]\n"
"    STR     R1, [R2,#0x5C]\n"
"    STR     R1, [R2,#0x6C]\n"
"    STR     R1, [R2,#0x7C]\n"
"    STR     R1, [R2,#0x8C]\n"
"    STR     R1, [R2,#0x9C]\n"
"    STR     R1, [R2,#0xAC]\n"
"    STR     R1, [R2,#0xBC]\n"
"    STR     R1, [R2,#0xCC]\n"
"    STR     R1, [R2,#0xDC]\n"
"    STR     R1, [R2,#0xEC]\n"
"    STR     R1, [R2,#0xFC]\n"
"    LDR     R1, =0xC0400008\n"
"    LDR     R2, =0x430005\n"
"    STR     R2, [R1]\n"
"    MOV     R1, #1\n"
"    LDR     R2, =0xC0243100\n"
"    STR     R2, [R1]\n"
"    LDR     R2, =0xC0242010\n"
"    LDR     R1, [R2]\n"
"    ORR     R1, R1, #1\n"
"    STR     R1, [R2]\n" */ 

// reyalp - WTF ? either you need this OR the for loops, but not both...
// Without this chunk we get stuck in stdioSetup
"    LDR     R0, =0xFFECD3E4\n"
"    LDR     R1, =0x1900\n"
"    LDR     R3, =0xAEB8\n" 
"loc_FFC0013C:\n"
"    CMP     R1, R3\n"
"    LDRCC   R2, [R0],#4\n"
"    STRCC   R2, [R1],#4\n"
"    BCC     loc_FFC0013C\n"
"    LDR     R1, =0x12AD3C\n"
"    MOV     R2, #0\n"
"loc_FFC00154:\n"
"    CMP     R3, R1\n"
"    STRCC   R2, [R3],#4\n"
"    BCC     loc_FFC00154\n" 
    :::"r0","r1","r2","r3");


    for(i = 0; i < canon_data_len/4; i++)
        canon_data_dst[i]=canon_data_src[i];

    for(i = 0; i < canon_bss_len/4; i++)
        canon_bss_start[i]=0;

// see http://chdk.setepontos.com/index.php/topic,2972.msg30712.html#msg30712
    // Kept these from SD780 for SD1200 (I don't know what they mean)
    *(int*)0x1934=(int)taskCreateHook;
    *(int*)0x1938=(int)taskCreateHook2; //VERIFY_SD780 VERIFY_SD1200

	// Search on 0x12345678 finds function that is called from function with
    // this code (SD780 0xFF842A90, SD1200 0xFFC307C4).
    *(int*)(0x222C)= (*(int*)0xC02200F8)&1 ? 0x400000 : 0x200000;

    asm volatile ("B      sub_FFC001A0_my\n");
}

//SD780 - ASM matches but comments are unknown if correct....
//SD1200 - Changed offsets (Just s/FF81/FFC0/). Found code at 0xFFC001A0
void __attribute__((naked,noinline)) sub_FFC001A0_my() {
asm volatile (
"                LDR     R0, =0xFFC00218\n" // exception handler code
"                MOV     R1, #0\n"
"                LDR     R3, =0xFFC00250\n"
"loc_FFC001AC:\n"
"                CMP     R0, R3\n"          // load exception vector
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FFC001AC\n"
"                LDR     R0, =0xFFC00250\n"
"                MOV     R1, #0x4B0\n"
"                LDR     R3, =0xFFC00464\n"
"loc_FFC001C8:\n"
"                CMP     R0, R3\n"          // copy IRQ handler to ITCM starting at 0x4b0, 532 bytes up to 0x6C4
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FFC001C8\n"
"                MOV     R0, #0xD2\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = IRQ, ints disabled
"                MOV     SP, #0x1000\n"     // irq mode SP
"                MOV     R0, #0xD3\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = Super, ints disabled
"                MOV     SP, #0x1000\n"     // super mode SP
"                LDR     R0, =0x6C4\n"		// in orig firmware: LDR     R0, loc_FFC0020C
"                LDR     R2, =0xEEEEEEEE\n"
"                MOV     R3, #0x1000\n"
"loc_FFC001FC:\n"
"                CMP     R0, R3\n"          // clear ITCM 0x6C4-end with EEEEEEEE
"                STRCC   R2, [R0],#4\n"
"                BCC     loc_FFC001FC\n"
"                BL      sub_FFC00FC4_my\n" //->my
        );
}

//SD780 - ASM matches
//SD1200 - ASM Matches, adjusted offsets
void __attribute__((naked,noinline)) sub_FFC00FC4_my() {
	asm volatile (
"                 STR     LR, [SP,#-4]!\n"
"                 SUB     SP, SP, #0x74\n"
"                 MOV     R0, SP\n"
"                 MOV     R1, #0x74\n"
"                 BL      sub_FFE6083C\n"
"                 MOV     R0, #0x53000\n"
"                 STR     R0, [SP,#4]\n"

"                 LDR     R0, =new_sa\n"	//Replaces original start location 0x12AD3C
"                 LDR     R0, [R0]\n"		//

"                 LDR     R2, =0x2F9C00\n"
"                 LDR     R1, =0x2F24A8\n"
"                 STR     R0, [SP,#8]\n"
"                 SUB     R0, R1, R0\n"
"                 ADD     R3, SP, #0xC\n"
"                 STR     R2, [SP]\n"
"                 STMIA   R3, {R0-R2}\n"
"                 MOV     R0, #0x22\n"
"                 STR     R0, [SP,#0x18]\n"
"                 MOV     R0, #0x68\n"
"                 STR     R0, [SP,#0x1C]\n"
"                 LDR     R0, =0x19B\n"
"                 LDR     R1, =sub_FFC04D38_my\n"
"                 STR     R0, [SP,#0x20]\n"
"                 MOV     R0, #0x96\n"
"                 STR     R0, [SP,#0x24]\n"
"                 MOV     R0, #0x78\n"
"                 STR     R0, [SP,#0x28]\n"
"                 MOV     R0, #0x64\n"
"                 STR     R0, [SP,#0x2C]\n"
"                 MOV     R0, #0\n"
"                 STR     R0, [SP,#0x30]\n"
"                 STR     R0, [SP,#0x34]\n"
"                 MOV     R0, #0x10\n"
"                 STR     R0, [SP,#0x5C]\n"
"                 MOV     R0, #0x800\n"
"                 STR     R0, [SP,#0x60]\n"
"                 MOV     R0, #0xA0\n"
"                 STR     R0, [SP,#0x64]\n"
"                 MOV     R0, #0x280\n"
"                 STR     R0, [SP,#0x68]\n"
"                 MOV     R0, SP\n"
"                 MOV     R2, #0\n"
"                 BL      sub_FFC02D68\n"
"                 ADD     SP, SP, #0x74\n"
"                 LDR     PC, [SP],#4\n"
	);
} 

//SD780 - ASM matches
//SD1200 - Changed offsets (Just s/FF81/FFC0/).  [ Original 0xFFC04D38 ]
void __attribute__((naked,noinline)) sub_FFC04D38_my() {
	asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 BL      sub_FFC00954\n"
"                 BL      sub_FFC090B4\n" // dmSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFFC04E4C\n" // "dmSetup"
"                 BLLT    sub_FFC04E2C\n" // err_init_task
"                 BL      sub_FFC04974\n"
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFFC04E54\n" // "termDriverInit"
"                 BLLT    sub_FFC04E2C\n" // err_init_task
"                 LDR     R0, =0xFFC04E64\n" // "/_term"
"                 BL      sub_FFC04A5C\n" // termDeviceCreate
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFFC04E6C\n" // "termDeviceCreate"
"                 BLLT    sub_FFC04E2C\n" // err_init_task
"                 LDR     R0, =0xFFC04E64\n" // "/_term"
"                 BL      sub_FFC03578\n" // stdioSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFFC04E80\n" // "stdioSetup"
"                 BLLT    sub_FFC04E2C\n" // err_init_task
"                 BL      sub_FFC08BCC\n" // stdlibSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFFC04E8C\n" // "stdlibSetup"
"                 BLLT    sub_FFC04E2C\n" // err_init_task
"                 BL      sub_FFC014A8\n"
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFFC04E98\n" // "armlib_setup"
"                 BLLT    sub_FFC04E2C\n" // err_init_task
"                 LDMFD   SP!, {R4,LR}\n"
"                 B       taskcreate_Startup_my\n"
	);
} //Ivan:checked

//SD780 - ASM matches [ 0xFF81C260 ]
//SD1200 - Changed offsets [ 0xFFC0C260 ]. More than just s/81/C0/g
void __attribute__((naked,noinline)) taskcreate_Startup_my() { 
	asm volatile (
"                STMFD   SP!, {R3,LR}\n"
//"                BL      sub_FFC11B18\n" //nullsub
"                BL      sub_FFC18AC8\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC0C298\n"
"                BL      sub_FFC11B14\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC0C298\n"
"                BL      sub_FFC111F0\n"
"                LDR     R1, =0xC0220000\n"
"                MOV     R0, #0x44\n"
"                STR     R0, [R1,#0x1C]\n"
"                BL      sub_FFC113DC\n"
"loc_FFC0C294:\n"
"                B       loc_FFC0C294\n"
"loc_FFC0C298:\n"
"                BL      sub_FFC11B20\n"
//"                BL      sub_FFC11B1C\n"   //nullsub
"                BL      sub_FFC16D84\n"
"                LDR     R1, =0x34E000\n"
"                MOV     R0, #0\n"
"                BL      sub_FFC171CC\n"
"                BL      sub_FFC16F78\n" // LOCATION: KerSys.c:548
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =task_Startup_my\n" // ->
"                MOV     R2, #0\n"
"                MOV     R1, #0x19\n"
"                LDR     R0, =0xFFC0C2E0\n"  // "Startup"
"                BL      sub_FFC0AFAC\n" // eventproc_export_CreateTask ; LOCATION: KerTask.c:163\n"
"                MOV     R0, #0\n"
"                LDMFD   SP!, {R12,PC}\n"
	);
}


//SD780 - ASM matches - Original location 0xFF81C1FC
//SD1200 - Changed Offsets - Original location 0xFFC0C1FC (task_Startup)
void __attribute__((naked,noinline)) task_Startup_my() {
	asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 BL      sub_FFC05394\n" // taskcreate_ClockSave
"                 BL      sub_FFC12BFC\n"
"                 BL      sub_FFC10F04\n"
"                 BL      sub_FFC18B08\n" // j_nullsub
"                 BL      sub_FFC18CEC\n"
//"                 BL      sub_FFC18B9C\n" // diskboot
        );

       CreateTask_spytask();
       //CreateTask_blinker();

        asm volatile (
"                 BL      sub_FFC18E88\n"
"                 BL      sub_FFC0FB90\n"
"                 BL      sub_FFC18D1C\n"
"                 BL      sub_FFC16384\n"
"                 BL      sub_FFC18E8C\n"
"                 BL      taskcreate_PhySw_my\n" // taskcreate_PhySw
"                 BL      taskcreate_SsTask_my\n" // taskcreate_SsTask -> for shoot seq stuff
"                 BL      sub_FFC14A14\n"  // Yossar: this was missing
"                 BL      sub_FFC18EA4\n"
"                 BL      sub_FFC0EFB0\n" // nullsub
"                 BL      sub_FFC10808\n"
"                 BL      sub_FFC188A8\n" // taskcreate_Bye
"                 BL      sub_FFC10EB4\n"
"                 BL      sub_FFC10714\n" // taskcreate_TempCheck
"                 BL      sub_FFC0FBC4\n"
"                 BL      sub_FFC198E0\n"
"                 BL      sub_FFC106EC\n");

       asm volatile (
"                 LDMFD   SP!, {R4,LR}\n"
"                 B       sub_FFC054B4\n" // _sub_FFC054B4__MLHClock_c__0 ; LOCATION: MLHClock.c:0
	);
}

//SD780 - ASM matches
//SD1200 - Original location 0xFFC14A14
//         Changed offsets
//         Also order of instructions
//         Shouldn't matter, but matches original now.
void __attribute__((naked,noinline)) taskcreate_SsTask_my() {
asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 MOV     R1, #0\n"
"                 MOV     R0, #0\n"
"                 BL      sub_FFC17024\n" // KernelMisc.c:43
"                 LDR     R4, =0x1C48\n"
"                 STR     R0, [R4,#4]\n"
"                 BL      sub_FFC4E494\n"
"                 BL      sub_FFC4FB6C\n"
"                 BL      sub_FFC4D624\n"
"                 BL      sub_FFC48B54_my\n"
"                 BL      sub_FFC4E750\n"
"                 LDR     R0, [R4,#4]\n"
"                 LDMFD   SP!, {R4,LR}\n"
"                 MOV     R1, #0x1000\n"
"                 B       sub_FFC524CC\n"
	);
}

//SD780 - ASM matches [ Original Location 0xFF85C228 ]
//SD1200 - Changed offsets [ Original Location 0xFFC48B54 ]
//       - Changed some constants to match original
void __attribute__((naked,noinline)) sub_FFC48B54_my() {
	asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                LDR     R4, =0x2818\n"
"                LDR     R0, [R4,#0xC]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC48BC0\n"
"                BL      sub_FFC4BEB4\n" // nullsub
"                MOV     R1, #1\n"
"                MOV     R0, #0\n"
"                BL      sub_FFC17048\n" // KernelMisc.c:55
"                STR     R0, [R4,#4]\n"
"                MOV     R0, #0\n"
"                MOV     R1, #8\n"
"                BL      sub_FFC17024\n" // KernelMisc.c:43
"                STR     R0, [R4,#0x8]\n"
"                BL      sub_FFC48E5C\n"
"                BL      sub_FFC495CC\n"
"                MOV     R0, #0\n"
"                STR     R0, [R4]\n"
"                ADD     R0, R4, #0x10\n"
"                MOV     R1, #0\n"
"                STR     R1, [R0],#4\n"
"                STR     R1, [R0]\n"
"                BL      sub_FFC497D4\n"
"                BL      sub_FFC4E958\n"
"                BL      sub_FFC4C1C4\n"
"                BL      taskcreate_CaptSeqTask_my\n"
"                BL      sub_FFC4B200\n"

"loc_FFC48BC0:\n"
"                MOV     R0, #1\n"
"                STR     R0, [R4,#0xC]\n"
"                LDMFD   SP!, {R4,PC}\n"
	);
}

//SD780 - ASM matches [ Original 0xFF85DA4C ]
//SD1200 - Changed Offsets/Constants [ Original 0xFFC4A2D0 ]

//Note the name taskcreate_CaptSeqTask vs task_CaptSeqTask
void __attribute__((naked,noinline)) taskcreate_CaptSeqTask_my() {
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R2, =0x11EEC\n"
"                MOV     R0, #0\n"
"                MOV     R1, #0\n"

"loc_FFC4A2E0:\n"
"                ADD     R3, R2, R0,LSL#4\n"
"                ADD     R0, R0, #1\n"
"                CMP     R0, #5\n"
"                STR     R1, [R3,#8]\n"
"                BCC     loc_FFC4A2E0\n"
"                BL      sub_FFC4AD60\n"
"                BL      sub_FFCFCFBC\n"
"                MOV     R1, #5\n"
"                MOV     R0, #0\n"
"                BL      sub_FFC17000\n" // KernelMisc.c:31
"                LDR     R4, =0x2850\n"
"                LDR     R1, =0x101DFF\n"
"                STR     R0, [R4,#0x4]\n"
"                MOV     R0, #0\n"
"                BL      sub_FFC17024\n" // KernelMisc.c:43
"                STR     R0, [R4]\n"
"                MOV     R0, #0\n"
"                MOV     R1, #1\n"
"                BL      sub_FFC17048\n" // KernelMisc.c:55
"                STR     R0, [R4,#0x8]\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =task_CaptSeqTask_my\n" // SsShootTask.c:13
"                LDR     R0, =0xFFC4A504\n" // "CaptSeqTask"
"                MOV     R2, #0x1000\n"
"                MOV     R1, #0x17\n"
"                BL      sub_FFC16FCC\n"// KernelCreateTask ; LOCATION: KernelMisc.c:19
"                LDMFD   SP!, {R3-R5,PC}\n"
	);
}

//SD780 - ASM matches
//SD1200 - Changed offsets [ Original Location 0xFFC11A14 ]
void __attribute__((naked,noinline)) taskcreate_PhySw_my() {
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R4, =0x1C28\n"
"                LDR     R0, [R4,#0x10]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC11A48\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =mykbd_task\n" // task_PhySw
//"                LDR     R3, =0xFFC119E0\n" // task_PhySw
"                MOV     R2, #0x2000\n" 	// Increate stack size from 0x800 to 0x2000 for new task_PhySw so we don't have to do stack switch
"                MOV     R1, #0x17\n"
"                LDR     R0, =0xFFC11C1C\n" // "PhySw"
"                BL      sub_FFC16FCC\n" // KernelCreateTask
"                STR     R0, [R4,#0x10]\n"

"loc_FFC11A48:\n"
"                BL      sub_FFC587DC\n"
"                BL      sub_FFC33FCC\n" // IsFactoryMode
"                CMP     R0, #0\n"
"                LDREQ   R1, =0xC344\n"
"                LDMEQFD SP!, {R3-R5,LR}\n"
"                BEQ     sub_FFC5871C\n" // eventproc_export_OpLog_Start
"                LDMFD   SP!, {R3-R5,PC}\n"
	);
}

#if 0
const unsigned ledlist[]={
    0xC0220134, // green
    0xC0220130, // red
    0xC0220138, // yellow
    0xC0223030, // AF
};

void __attribute__((noinline)) task_blinker() {
    int ledstate;

    int counter = 0;

    int *led = (void *) ledlist[0];
    //int i_led = 0;
    int i_led = 1;

    int *anypointer;       // multi-purpose pointer to poke around in memory
    int v1, v2, v3, v4;    // multi-purpose vars

    ledstate = 0;   // init: led off
    *led = 0x46;      // led on

    while (1) {

            if (ledstate == 1) {    // toggle LED
                    ledstate = 0;
                    *led = 0x44;      // LED off
                    led=(void *)ledlist[(i_led)%4];
                    //led=(void *)ledlist[(++i_led)%4];
                    //ubasic_set_led(i_led % 6, ledstate, 0);
                    //core_test(1);
            } else {
                    ledstate = 1;
                    //ubasic_set_led(i_led % 6, ledstate, 0);
                    *led = 0x46;      // LED on
                    //core_test(0);
            }

            if (counter == 5) {
                    //LED_OFF(LED_IO_R); LED_OFF(LED_IO_G); LED_OFF(LED_IO_Y); LED_OFF(LED_AF);
                    //DumpMemory("A/firmware.bin", (void *) 0xFFC00000, 0x3FFFFF);
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


extern long Fopen_Fut(const char *filename, const char *mode);
extern long Fclose_Fut(long file);
extern long Fflush_Fut(long file);
extern long Fwrite_Fut(const void *buf, long elsize, long count, long f);

void DumpMemory(char *path, void *start_address, int length) {
    int fd;
    
    LED_OFF(LED_IO_G);
    LED_ON(LED_IO_Y);

    fd = Fopen_Fut(path, "w");
    if (fd >= 0) {
        LED_ON(LED_IO_R);
        Fwrite_Fut( (void *) start_address, 1, length, fd);
        LED_OFF(LED_IO_R);
        Fflush_Fut(fd);
        Fclose_Fut(fd);
        LED_OFF(LED_IO_Y);
        LED_ON(LED_IO_G);
    }

    while(1);
}

void CreateTask_blinker() {
       _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
}
#endif

void CreateTask_spytask() {
       _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

//SD780 - ASM Matches - Original location 0xFF877DD0
//SD1200 - Changed offsets [ Original Location 0xFFC61374 ]
void __attribute__((naked,noinline)) init_file_modules_task() {
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 BL      sub_FFC5AB88\n"
"                 LDR     R5, =0x5006\n"
"                 MOVS    R4, R0\n"
"                 MOVNE   R1, #0\n"
"                 MOVNE   R0, R5\n"
"                 BLNE    sub_FFC5D244\n"			// PostLogicalEventToUI
"                 BL      sub_FFC5ABB4_my\n" // ->
"                 BL      core_spytask_can_start\n" // + safe to start spytask
"                 CMP     R4, #0\n"
"                 MOVEQ   R0, R5\n"
"                 LDMEQFD SP!, {R4-R6,LR}\n"
"                 MOVEQ   R1, #0\n"
"                 BEQ     sub_FFC5D244\n" // PostLogicalEventToUI
"                 LDMFD   SP!, {R4-R6,PC}\n"
	);
}

//SD780 - ASM matches [ Original location 0xFF86EB50]
//SD1200 - ASM Matches/Offsets updated [ Original location 0xFFC5ABB4 ]
void __attribute__((naked,noinline)) sub_FFC5ABB4_my() {
  asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 MOV	  R0, #3\n"
"                 BL      sub_FFC3F454_my\n" // ->  //Mounter.c
"                 BL      sub_FFCD8B9c\n" // nullsub
"                 LDR     R4, =0x2BA4\n"
"                 LDR     R0, [R4,#4]\n"
"                 CMP     R0, #0\n"
"                 BNE     loc_FFC5ABEC\n"
"                 BL      sub_FFC3E818\n"
"                 BL      sub_FFCCF14C\n"
"                 BL      sub_FFC3E818\n"
"                 BL      sub_FFC3AC7C\n"
"                 BL      sub_FFC3E718\n"
"                 BL      sub_FFCCF210\n"
"loc_FFC5ABEC:\n"
"                 MOV     R0, #1\n"
"                 STR     R0, [R4]\n"
"                 LDMFD   SP!, {R4,PC}\n"
 );
}

//SD780 - ASM matches [ Original 0xFF852020 ]
//SD1200 - ASM Matches, updated offsets. [ Original 0xFFC3F454 ] 
void __attribute__((naked,noinline)) sub_FFC3F454_my() {
  asm volatile (

"                 STMFD   SP!, {R4-R8,LR}\n"
"                 MOV     R6, R0\n"
"                 BL      sub_FFC3F3BC\n" // Mounter.c:0
"                 LDR     R1, =0xE2FC\n"
"                 MOV     R5, R0\n"
"                 ADD     R4, R1, R0, LSL#7\n"
"                 LDR     R0, [R4,#0x70]\n"
"                 CMP     R0, #4\n"
"                 LDREQ   R1, =0x6D8\n"
"                 LDREQ   R0, =0xFFC3EEE0\n" // "Mounter.c"
"                 BLEQ    sub_FFC0B284\n" // DebugAssert
"                 MOV     R1, R6\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FFC3EE28\n" // LOCATION: Mounter.c:0
"                 LDR     R0, [R4,#0x38]\n"
"                 BL      sub_FFC3F980\n"
"				  CMP	  R0, #0\n"
"				  STREQ	  R0, [R4,#0x70]\n"
"				  MOV	  R0, R5\n"
"				  BL	  sub_FFC3EF00\n"
"				  MOV	  R0, R5\n"
"				  BL	  sub_FFC3F1F4_my\n"
"                 MOV     R7, R0\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FFC3F258\n" // LOCATION: Mounter.c:7
"                 LDR     R1, [R4,#0x3C]\n"
"                 AND     R2, R7, R0\n"
"                 CMP     R1, #0\n"
"                 MOV     R0, #0\n"
"                 MOVEQ   R0, #0x80000001\n"
"                 BEQ     loc_FFC3F4FC\n"
"                 LDR     R3, [R4,#0x2C]\n"
"                 CMP     R3, #2\n"
"                 MOVEQ   R0, #4\n"
"                 CMP     R1, #5\n"
"                 ORRNE   R0, R0, #1\n"
"                 BICEQ   R0, R0, #1\n"
"                 CMP     R2, #0\n"
"                 BICEQ   R0, R0, #2\n"
"                 ORREQ   R0, R0, #0x80000000\n"
"                 BICNE   R0, R0, #0x80000000\n"
"                 ORRNE   R0, R0, #2\n"
"loc_FFC3F4FC:\n"
"				  CMP	  R6, #7\n"
"                 STR     R0, [R4,#0x40]\n"
"				  LDMNEFD SP!, {R4-R8,PC}\n"
"				  MOV	  R0, R6\n"
"				  BL	  sub_FFC3F40C\n"
"				  CMP	  R0, #0\n"
"				  LDMEQFD SP!, {R4-R8,LR}\n"
"				  LDREQ   R0,=0xFFC3F6F8\n" // "EMEM MOUNT ERROR!!!\n"
"				  BEQ 	  sub_FFC015A8\n"  // qPrintf
"                 LDMFD   SP!, {R4-R8,PC}\n"		// Yossar: was R6, in firmware is R8
 );
}

//SD780 - ASM matches - Note support of FAT32 is OFF [ Original 0xFF851DC0 ]
//SD1200 - ASM Matches, updated offsets [ Original 0xFFC3F1F4]

// Mounter.c
void __attribute__((naked,noinline)) sub_FFC3F1F4_my() {
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 MOV     R5, R0\n"
"                 LDR     R0, =0xE2Fc\n"
"				  ADD 	  R4, R0, R5,LSL#7\n"
"                 LDR     R0, [R4,#0x70]\n"
"                 TST     R0, #2\n"
"                 MOVNE   R0, #1\n"
"                 LDMNEFD SP!, {R4-R6,PC}\n"
"				  LDR 	  R0, [R4,#0x38]\n"
"                 MOV     R1, R5\n"
//"                 BL      sub_FF851B50_my\n"  // -> FAT32 Support  //VERIFY_SD780
"                 BL      sub_FFC3EF84\n" 		// -> is Mounter.c
"                 CMP     R0, #0\n"
"                 LDMEQFD SP!, {R4-R6,PC}\n"
"                 LDR     R0, [R4,#0x38]\n"
"                 MOV     R1, R5\n"
"                 BL      sub_FFC3F0F0\n" // LOCATION: Mounter.c:0
"                 CMP     R0, #0\n"
"                 LDMEQFD SP!, {R4-R6,PC}\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FFC3EA10\n"
"                 CMP     R0, #0\n"
"				  LDRNE	  R1, [R4,#0x70]\n"
"				  ORRNE	  R1, R1, #2\n"
"                 STRNE   R1, [R4,#0x70]\n"
"                 LDMFD   SP!, {R4-R6,PC}\n"
  );
}


/*
//VERIFY_SD780 - FAT32 is OFF
void __attribute__((naked,noinline)) sub_FF851B50_my() {  //Need to fix
  asm volatile (
"                 STMFD   SP!, {R4-R8,LR}\n"
"                 MOV     R8, R0\n"
"                 MOV     R0, #0x17\n"
"                 MUL     R1, R0, R1\n"
"                 LDR     R0, =0x19BC8\n"
"                 MOV     R6, #0\n"
"                 ADD     R7, R0, R1,LSL#2\n"
"                 LDR     R0, [R7,#0x3C]\n"
"                 MOV     R5, #0\n"
"                 CMP     R0, #6\n"
"                 ADDLS   PC, PC, R0,LSL#2\n"
"                 B       loc_FF858FD0\n"
"                 B       loc_FF858EE8\n"
"                 B       loc_FF858ED0\n"
"                 B       loc_FF858ED0\n"
"                 B       loc_FF858ED0\n"
"                 B       loc_FF858ED0\n"
"                 B       loc_FF858FC8\n"
"                 B       loc_FF858ED0\n"
"loc_FF858ED0:\n"
// jumptable FF858EAC entries 1-4,6
"                 MOV     R2, #0\n"
"                 MOV     R1, #0x200\n"
"                 MOV     R0, #2\n"
"                 BL      sub_FF870BA0\n"
"                 MOVS    R4, R0\n"
"                 BNE     loc_FF858EF0\n"
"loc_FF858EE8:\n"
// jumptable FF858EAC entry 0
"                 MOV     R0, #0\n"
"                 LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF858EF0:\n"
"                 LDR     R12, [R7,#0x4C]\n"
"                 MOV     R3, R4\n"
"                 MOV     R2, #1\n"
"                 MOV     R1, #0\n"
"                 MOV     R0, R8\n"
///FIX this BLX not good"                 BLX     R12\n"
"                 CMP     R0, #1\n"
"                 BNE     loc_FF858F1C\n"
"                 MOV     R0, #2\n"
"                 BL      sub_FF870CEC\n" // LOCATION: ExMemMan.c:0
"                 B       loc_FF858EE8\n"
"loc_FF858F1C:\n"
"                 MOV     R0, R8\n"
"                 BL      sub_FF9214E8\n"
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
"                 LDRB    R1, [R4,#0x1C9]\n"
"                 LDRB    R3, [R4,#0x1C8]\n"
"                 LDRB    R12, [R4,#0x1CC]\n"
"                 MOV     R1, R1,LSL#24\n"
"                 ORR     R1, R1, R3,LSL#16\n"
"                 LDRB    R3, [R4,#0x1C7]\n"
"                 LDRB    R2, [R4,#0x1BE]\n"
//"                 LDRB    LR, [R4,#0x1FF]\n" // -
"                 ORR     R1, R1, R3,LSL#8\n"
"                 LDRB    R3, [R4,#0x1C6]\n"
"                 CMP     R2, #0\n"
"                 CMPNE   R2, #0x80\n"
"                 ORR     R1, R1, R3\n"
"                 LDRB    R3, [R4,#0x1CD]\n"
"                 MOV     R3, R3,LSL#24\n"
"                 ORR     R3, R3, R12,LSL#16\n"
"                 LDRB    R12, [R4,#0x1CB]\n"
"                 ORR     R3, R3, R12,LSL#8\n"
"                 LDRB    R12, [R4,#0x1CA]\n"
"                 ORR     R3, R3, R12\n"
//"                 LDRB    R12, [R4,#0x1FE]\n" // -
"                 LDRB    R12, [LR,#0x1FE]\n" // +
"                 LDRB    LR, [LR,#0x1FF]\n" // +
"                 MOV     R4, #0\n"
"                 BNE     loc_FF858FA4\n"
"                 CMP     R0, R1\n"
"                 BCC     loc_FF858FA4\n"
"                 ADD     R2, R1, R3\n"
"                 CMP     R2, R0\n"
"                 CMPLS   R12, #0x55\n"
"                 CMPEQ   LR, #0xAA\n"
"                 MOVEQ   R6, R1\n"
"                 MOVEQ   R5, R3\n"
"                 MOVEQ   R4, #1\n"
"loc_FF858FA4:\n"
"                 MOV     R0, #2\n"
"                 BL      sub_FF870CEC\n" // LOCATION: ExMemMan.c:0
"                 CMP     R4, #0\n"
"                 BNE     loc_FF858FDC\n"
"                 MOV     R6, #0\n"
"                 MOV     R0, R8\n"
"                 BL      sub_FF9214E8\n"
"                 MOV     R5, R0\n"
"                 B       loc_FF858FDC\n"
"loc_FF858FC8:\n"
// jumptable FF858EAC entry 5
"                 MOV     R5, #0x40\n"
"                 B       loc_FF858FDC\n"
"loc_FF858FD0:\n"
// jumptable FF858EAC default entry
"                 LDR     R1, =0x37A\n"
"                 LDR     R0, =0xFF858E78\n" // "Mounter.c"
"                 BL      sub_FF81B1CC\n" // DebugAssert
" loc_FF858FDC:\n"
"                 STR     R6, [R7,#0x44]!\n"
"                 MOV     R0, #1\n"
"                 STR     R5, [R7,#4]\n"
"                 LDMFD   SP!, {R4-R8,PC}\n"
  );
}
*/
