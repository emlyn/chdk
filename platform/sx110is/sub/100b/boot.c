//sx110.100b

#include "lolevel.h"
#include "platform.h"
#include "core.h"


#define DP (void*)0xC02200C4					// direct-print (blue)
#define LED_PR	0xc02200C4
#define LED_RED 0xc02200C8
#define LED_GRN	0xc02200CC
#define LED_PWR	0xc02200D0

#define DELAY 800000

void debug_my_blink()
{
	volatile long *p = (void*)DP;       		// turned off later, so assumed to be power
	volatile long *p2 = (void*)LED_RED;       		// turned off later, so assumed to be power
	int counter;

	// DEBUG: blink led
	//led on
	counter = DELAY; 
	*p = 0x46; 
	while (counter--) { asm("nop\n nop\n"); };
	*p2 = 0x46;
	//led off
	counter = DELAY; 
	*p = 0x44; 
	while (counter--) { asm("nop\n nop\n"); };
	*p2= 0x44;
}

//js
const char * const new_sa = &_end;

void JogDial_task_my(void);

void taskCreateHook(int *p) { 
 p-=17;
 if (p[0]==0xFFC503B0)  p[0]=(int)capt_seq_task;	
 if (p[0]==0xFFC11060)  p[0]=(int)mykbd_task;
 if (p[0]==0xFFC67A68)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFFC36528)  p[0]=(int)JogDial_task_my;	
 if (p[0]==0xFFC4CC8C)  p[0]=(int)movie_record_task;	 
}

void taskCreateHook2(int *p) { 
 p-=17;
 if (p[0]==0xFFC67A68)  p[0]=(int)init_file_modules_task;
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

//jse

//JS
/* Boot method is still the old detour of original camera boot code as used since the first DryOS-ports...
For some unknown reasons SX110 will not boot if CHDK starts with the original sequence at FFC0000C.
If someone wants to check it: look at 
"loc_FFC00154:\n"
		"CMP 	R3, R1\n"
		"STRCC 	R2, [R3],#4\n"
		"BCC 	loc_FFC00154\n"

		"B 	loc_FFC001A4_my\n"		// <------------------------------- changed
*/
void boot();

void boot() { //#fs
		long *canon_data_src = (void*)0xFFEFF5F8; 
		long *canon_data_dst = (void*)0x1900;
		long canon_data_len = 0xE6B4 - 0x1900;		// data_end - data_start
		long *canon_bss_start = (void*)0xE6B4;		// just after data
		long canon_bss_len = 0xA2728 - 0xE6B4;

    long i;

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

// done below
//    *(int*)(0x2478+0x4) = (*(int*)0xC02200B8)&1 ? 0x100000: 0x200000; // replacement of sub_FFC111A4	//from taskcreate_startup to sub_FFC111A4 and there to sub_FFC35CC4
	
    // jump to init-sequence that follows the data-copy-routine
    asm volatile ("B 	loc_FFC001A4_my\n");	// <---------------
}; //#fe
//JSE

//JS
void __attribute__((naked,noinline)) loc_FFC001A4_my() {
	*(int*)0x1930=(int)taskCreateHook;
	*(int*)0x1934=(int)taskCreateHook2;
    *(int*)(0x2478+0x4) = (*(int*)0xC02200B8)&1 ? 0x100000: 0x200000; // replacement of sub_FFC111A4	//from taskcreate_startup to sub_FFC111A4 and there to sub_FFC35CC4
	asm volatile (
		"loc_FFC001A4:\n"		
			"LDR 	R0, =0xFFC0021C\n"
			"MOV 	R1, #0\n"
			"LDR 	R3, =0xFFC00254\n"
		"loc_FFC001B0:\n"		
			"CMP 	R0, R3\n"
			"LDRCC 	R2, [R0],#4\n"
			"STRCC 	R2, [R1],#4\n"
			"BCC 	loc_FFC001B0\n"
			"LDR 	R0, =0xFFC00254\n"
			"MOV 	R1, #0x4B0\n"
			"LDR 	R3, =0xFFC00468\n"
		"loc_FFC001CC:\n"		
			"CMP 	R0, R3\n"
			"LDRCC 	R2, [R0],#4\n"
			"STRCC 	R2, [R1],#4\n"
			"BCC 	loc_FFC001CC\n"
			"MOV 	R0, #0xD2\n"
			"MSR 	CPSR_cxsf, R0\n"
			"MOV 	SP, #0x1000\n"
			"MOV 	R0, #0xD3\n"
			"MSR 	CPSR_cxsf, R0\n"
			"MOV 	SP, #0x1000\n"
			"LDR 	R0, =loc_FFC00210\n"
			"LDR 	R2, =0xEEEEEEEE\n"
			"MOV 	R3, #0x1000\n"
				
		"loc_FFC00200:\n"		
			"CMP 	R0, R3\n"
			"STRCC 	R2, [R0],#4\n"
			"BCC 	loc_FFC00200\n"
			"BL 	sub_FFC00F98_my\n"	// <---------- changed
				
		"loc_FFC00210:\n"		
			"ANDEQ 	R0, R0, R4,ASR#13\n"
				
		"loc_FFC00214:\n"		
				
			"ANDEQ 	R0, R0, R0,ROR R6\n"
				
		"loc_FFC00218:\n"		
			"ANDEQ 	R0, R0, R4,ROR R6\n"
				
		"loc_FFC0021C:\n"		
			"NOP\n"	
			"LDR 	PC, =0xFFC00468\n"
	);
}
//JSE

//JS

void __attribute__((naked,noinline)) sub_FFC00F98_my() {

      asm volatile (
			"STR 	LR, [SP,#-4]!\n"	//ROM:FFC00F98                 STR     LR, [SP,#unk_FFFFFFFC]!
			"SUB 	SP, SP, #0x74\n"
			"MOV 	R0, SP\n"
			"MOV 	R1, #0x74\n"
			"BL 	sub_FFE8F154\n"
			"MOV 	R0, #0x53000\n"
			"STR 	R0, [SP,#0x4]\n"
//			"LDR 	R0, =0xA2728\n"		// <--- removed

			"LDR     R0, =new_sa\n"        	// <--- added
			"LDR     R0, [R0]\n"           // <--- added

			"LDR 	R2, =0x279C00\n"
			"LDR 	R1, =0x2724A8\n"
			"STR 	R0, [SP,#0x8]\n"
			"SUB 	R0, R1, R0\n"
			"ADD 	R3, SP, #0xC\n"
			"STR 	R2, [SP,#0x0]\n"
			"STMIA 	R3, {R0-R2}\n"
			"MOV 	R0, #0x22\n"
			"STR 	R0, [SP,#0x18]\n"
			"MOV 	R0, #0x68\n"
			"STR 	R0, [SP,#0x1C]\n"
			"LDR 	R0, =0x19B\n"
			"LDR 	R1, =sub_FFC04D90_my\n"	// <-------------- changed
			"STR 	R0, [SP,#0x20]\n"
			"MOV 	R0, #0x96\n"
			"STR 	R0, [SP,#0x24]\n"
			"MOV 	R0, #0x78\n"
			"STR 	R0, [SP,#0x28]\n"
			"MOV 	R0, #0x64\n"
			"STR 	R0, [SP,#0x2C]\n"
			"MOV 	R0, #0\n"
			"STR 	R0, [SP,#0x30]\n"
			"STR 	R0, [SP,#0x34]\n"
			"MOV 	R0, #0x10\n"
			"STR 	R0, [SP,#0x5C]\n"
			"MOV 	R0, #0x800\n"
			"STR 	R0, [SP,#0x60]\n"
			"MOV 	R0, #0xA0\n"
			"STR 	R0, [SP,#0x64]\n"
			"MOV 	R0, #0x280\n"
			"STR 	R0, [SP,#0x68]\n"
			"MOV 	R0, SP\n"
			"MOV 	R2, #0\n"
			"BL 	sub_FFC02D3C\n"
			"ADD 	SP, SP, #0x74\n"
			"LDR 	PC, [SP],#4\n"
			
	);
}
//JSE

void __attribute__((naked,noinline)) sub_FFC04D90_my() {
asm volatile (
			"STMFD 	SP!, {R4,LR}\n"
			"BL 	sub_FFC00944\n"
			"BL 	sub_FFC09708\n"	//dmsetup
			"CMP 	R0, #0\n"
			"LDRLT 	R0, =0xFFC04EA4\n"
			"BLLT 	sub_FFC04E84\n"
			"BL 	sub_FFC049B8\n"
			"CMP 	R0, #0\n"
			"LDRLT 	R0, =0xFFC04EAC\n"
			"BLLT 	sub_FFC04E84\n"
			"LDR 	R0, =0xFFC04EBC\n"
			"BL 	sub_FFC04AA0\n"		//termDeviceCreate
			"CMP 	R0, #0\n"
			"LDRLT 	R0, =0xFFC04EC4\n"
			"BLLT 	sub_FFC04E84\n"
			"LDR 	R0, =0xFFC04EBC\n"
			"BL 	sub_FFC0354C\n"	//stdioSetup
			"CMP 	R0, #0\n"
			"LDRLT 	R0, =0xFFC04ED8\n"
			"BLLT 	sub_FFC04E84\n"
			"BL 	sub_FFC09290	\n"		//stdlibSetup
			"CMP 	R0, #0\n"
			"LDRLT 	R0, =0xFFC04EE4\n"
			"BLLT 	sub_FFC04E84\n"
			"BL 	sub_FFC0147C\n"
			"CMP 	R0, #0\n"
			"LDRLT 	R0, =0xFFC04EF0\n"
			"BLLT 	sub_FFC04E84\n"
			"LDMFD 	SP!, {R4,LR}\n"
			"B 	taskcreate_Startup_my\n"		// <--------------- changed, 0xFFC0CD6C in fw
        );
};
//JSE

//JS
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
			 asm volatile (
			"STMFD 	SP!, {R3,LR}\n"
			"BL 	sub_FFC1119C\n"		//j_null0x245
			"BL 	sub_FFC19194\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFC0CDA0\n"
			"BL 	sub_FFC11198\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFC0CDA0\n"
			"LDR 	R1, =0xC0220000\n"
			"MOV 	R0, #0x44\n"
			"STR 	R0, [R1,#0x54]\n"
			"STR 	R0, [R1,#0x4C]\n"
		"loc_FFC0CD9C:\n"		
			"B 	loc_FFC0CD9C\n"
		"loc_FFC0CDA0:\n"
//			"BL 	sub_FFC111A4\n"		// removed for correct power-on on "on/off" button.
			"BL 	sub_FFC111A0\n" 			//j_null0x246
			"BL 	sub_FFC17524\n"
			"LDR 	R1, =0x2CE000\n"
			"MOV 	R0, #0\n"
			"BL 	sub_FFC1776C\n"
			"BL 	sub_FFC17718\n"
			"MOV 	R3, #0\n"
			"STR 	R3, [SP]\n"
			"LDR 	R3, =task_Startup_my\n"		// <----------- changed, 0x:FFC0CD10 in fw
			"MOV 	R2, #0\n"
			"MOV 	R1, #0x19\n"
			"LDR 	R0, =0xFFC0CDE8\n"
			"BL 	sub_FFC0B8C0\n"
			"MOV 	R0, #0\n"
			"LDMFD 	SP!, {R12,PC}\n"
     );
}
//JSE
//JS
void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (
			"STMFD 	SP!, {R4,LR}\n"
			"BL 	sub_FFC0515C\n"		//taskcreate_ClockSave
			"BL 	sub_FFC12308\n"
			"BL 	sub_FFC10BE0\n"
			"BL 	sub_FFC191D4\n"				//j_null0x249
			"BL 	sub_FFC1939C\n"
//			"BL 	sub_FFC1925C\n"	//start diskboot.bin, //StartDiskboot --> removed
			"BL 	sub_FFC19554\n"
			"BL 	sub_FFC193EC\n"
			"BL 	sub_FFC16818\n"
			"BL 	sub_FFC19558\n"
            "BL 	CreateTask_spytask\n"    // <--- function added
			"BL 	sub_FFC11094\n"		//taskcreate_PhySw
			"BL 	sub_FFC14270\n"
			"BL 	sub_FFC19570\n"
			"BL 	sub_FFC0FC08\n"		//null0x2
			"BL 	sub_FFC10530\n"
			"BL 	sub_FFC18F74\n"		//taskcreate_Bye
			"BL 	sub_FFC10B90\n"
			"BL 	sub_FFC1044C\n"
			"BL 	sub_FFC1A008\n"
			"BL 	sub_FFC10424\n"
			"LDMFD 	SP!, {R4,LR}\n"
			"B 	sub_FFC0505C\n"
     );
}
//JSE

//JS

void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
			"STMFD 	SP!, {R4-R6,LR}\n"
			"BL 	sub_FFC5FB40\n"
			"LDR 	R5, =0x5006\n"
			"MOVS 	R4, R0\n"
			"MOVNE 	R1, #0\n"
			"MOVNE 	R0, R5\n"
			"BLNE 	sub_FFC61C00\n"		//eventproc_export_PostLogicalEventToUI
			"BL 	sub_FFC5FB6C_my\n"			// <---------- changed
            "BL 	core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask
			"CMP 	R4, #0\n"
			"MOVEQ 	R0, R5\n"
			"LDMEQFD 	SP!, {R4-R6,LR}\n"
			"MOVEQ 	R1, #0\n"
			"BEQ 	sub_FFC61C00\n"		//eventproc_export_PostLogicalEventToUI
			"LDMFD 	SP!, {R4-R6,PC}\n"
 );
}
// JSE

//JS
void __attribute__((naked,noinline)) sub_FFC5FB6C_my() {
 asm volatile(
			"STMFD 	SP!, {R4,LR}\n"
			"BL 	sub_FFC44A3C_my\n"		// <--------- changed
			"BL 	sub_FFCF7C2C\n"			//null0x106
			"LDR 	R4, =0x5678\n"
			"LDR 	R0, [R4,#4]\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFC5FBA0\n"
			"BL 	sub_FFC43F04\n"
			"BL 	sub_FFCEDA20\n"
			"BL 	sub_FFC43F04\n"
			"BL 	sub_FFC3FDD8\n"
			"BL 	sub_FFC43E04\n"
			"BL 	sub_FFCEDAEC\n"
		"loc_FFC5FBA0:\n"		
			"MOV 	R0, #1\n"
			"STR 	R0, [R4]\n"
			"LDMFD 	SP!, {R4,PC}\n"
 );
}
//JSE

//JS
void __attribute__((naked,noinline)) sub_FFC44A3C_my() {
 asm volatile(
			"STMFD 	SP!, {R4-R6,LR}\n"
			"MOV 	R6, #0\n"
			"MOV 	R0, R6\n"
			"BL 	sub_FFC444FC\n"
			"LDR 	R4, =0x17E00\n"
			"MOV 	R5, #0\n"
			"LDR 	R0, [R4,#0x38]\n"
			"BL 	sub_FFC44F5C\n"
			"CMP 	R0, #0\n"
			"LDREQ 	R0, =0x28D0\n"
			"STREQ 	R5, [R0,#0x10]\n"
			"STREQ 	R5, [R0,#0x14]\n"
			"STREQ 	R5, [R0,#0x18]\n"
			"MOV 	R0, R6\n"
			"BL 	sub_FFC4453C\n"
			"MOV 	R0, R6\n"
			"BL 	sub_FFC44878_my\n"		// <--------- changed
			"MOV 	R5, R0\n"
			"MOV 	R0, R6\n"
			"BL 	sub_FFC448E4\n"
			"LDR 	R1, [R4,#0x3C]\n"
			"AND 	R2, R5, R0\n"
			"CMP 	R1, #0\n"
			"MOV 	R0, #0\n"
			"MOVEQ 	R0, #0x80000001\n"
			"BEQ 	loc_FFC44AD0\n"
			"LDR 	R3, [R4,#0x2C]\n"
			"CMP 	R3, #2\n"
			"MOVEQ 	R0, #4\n"
			"CMP 	R1, #5\n"
			"ORRNE 	R0, R0, #1\n"
			"BICEQ 	R0, R0, #1\n"
			"CMP 	R2, #0\n"
			"BICEQ 	R0, R0, #2\n"
			"ORREQ 	R0, R0, #0x80000000\n"
			"BICNE 	R0, R0, #0x80000000\n"
			"ORRNE 	R0, R0, #2\n"
				
		"loc_FFC44AD0:\n"		
			"STR 	R0, [R4,#0x40]\n"
			"LDMFD 	SP!, {R4-R6,PC}\n"
 );
}
//JSE

//JS
void __attribute__((naked,noinline)) sub_FFC44878_my() {
 asm volatile(
			"STMFD 	SP!, {R4-R6,LR}\n"
			"LDR 	R5, =0x28D0\n"
			"MOV 	R6, R0\n"
			"LDR 	R0, [R5,#0x14]\n"
			"CMP 	R0, #0\n"
			"MOVNE 	R0, #1\n"
			"LDMNEFD 	SP!, {R4-R6,PC}\n"
			"MOV 	R0, #0x17\n"
			"MUL 	R1, R0, R6\n"
			"LDR 	R0, =0x17E00\n"
			"ADD 	R4, R0, R1,LSL#2\n"
			"LDR 	R0, [R4,#0x38]\n"
			"MOV 	R1, R6\n"
			"BL 	sub_FFC44608_my\n"		// <---- changed
			"CMP 	R0, #0\n"
			"LDMEQFD 	SP!, {R4-R6,PC}\n"
			"LDR 	R0, [R4,#0x38]\n"
			"MOV 	R1, R6\n"
			"BL 	sub_FFC44770\n"
			"CMP 	R0, #0\n"
			"LDMEQFD 	SP!, {R4-R6,PC}\n"
			"MOV 	R0, R6\n"
			"BL 	sub_FFC44104\n"
			"CMP 	R0, #0\n"
			"MOVNE 	R1, #1\n"
			"STRNE 	R1, [R5,#0x14]\n"
			"LDMFD 	SP!, {R4-R6,PC}\n"
 );
}
//JSE

//JS
void __attribute__((naked,noinline)) sub_FFC44608_my() {

 asm volatile(
			"STMFD 	SP!, {R4-R8,LR}\n"
			"MOV 	R8, R0\n"
			"MOV 	R0, #0x17\n"
			"MUL 	R1, R0, R1\n"
			"LDR 	R0, =0x17E00\n"
			"MOV 	R6, #0\n"
			"ADD 	R7, R0, R1,LSL#2\n"
			"LDR 	R0, [R7,#0x3C]\n"
			"MOV 	R5, #0\n"
			"CMP 	R0, #6\n"
			"ADDLS 	PC, PC, R0,LSL#2\n"
			"B 	loc_FFC44754\n"
				
		"loc_FFC44638:\n"		
			"B 	loc_FFC4466C\n"
				
		"loc_FFC4463C:\n"		
			"B 	loc_FFC44654\n"
				
		"loc_FFC44640:\n"		
			"B 	loc_FFC44654\n"
				
		"loc_FFC44644:\n"		
			"B 	loc_FFC44654\n"
				
		"loc_FFC44648:\n"		
			"B 	loc_FFC44654\n"
				
		"loc_FFC4464C:\n"		
			"B 	loc_FFC4474C\n"
				
		"loc_FFC44650:\n"		
			"B 	loc_FFC44654\n"
				
		"loc_FFC44654:\n"		
				
			"MOV 	R2, #0\n"
			"MOV 	R1, #0x200\n"
			"MOV 	R0, #2\n"
			"BL 	sub_FFC59C10\n"
			"MOVS 	R4, R0\n"
			"BNE 	loc_FFC44674\n"
				
		"loc_FFC4466C:\n"		
				
			"MOV 	R0, #0\n"
			"LDMFD 	SP!, {R4-R8,PC}\n"
				
		"loc_FFC44674:\n"		
			"LDR 	R12, [R7,#0x4C]\n"
			"MOV 	R3, R4\n"
			"MOV 	R2, #1\n"
			"MOV 	R1, #0\n"
			"MOV 	R0, R8\n"
//			"BLX 	R12\n"			// !! Workaround !!
		"MOV 	LR, PC\n"			// gcc won't compile "BLX 	R12" nor "BL 	R12".
		"MOV 	PC, R12\n"			// workaround: make your own "BL" and hope we don't need the change to thumb-mode
			
			"CMP 	R0, #1\n"
			"BNE 	loc_FFC446A0\n"
			"MOV 	R0, #2\n"
			"BL 	sub_FFC59D5C\n"
			"B 	loc_FFC4466C\n"
				
		"loc_FFC446A0:\n"		
			"MOV 	R0, R8\n"
			"BL 	sub_FFD02ECC\n"
			
			//insertion of new code for FAT32 autodetection
		 "MOV   R1, R4\n"           //  pointer to MBR in R1
		 "BL 	mbr_read_dryos\n"   //  total sectors count in R0 before and after call

          // Start of DataGhost's FAT32 autodetection code
          // Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
          // According to the code below, we can use R1, R2, R3 and R12.
          // LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
          // that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
          "MOV     R12, R4\n"                    // Copy the MBR start address so we have something to work with
          "MOV     LR, R4\n"                     // Save old offset for MBR signature
          "MOV     R1, #1\n"                     // Note the current partition number
          "B 	dg_sd_fat32_enter\n"          // We actually need to check the first partition as well, no increments yet!
     "dg_sd_fat32:\n"
          "CMP 	R1, #4\n"                     // Did we already see the 4th partition?
          "BEQ 	dg_sd_fat32_end\n"            // Yes, break. We didn't find anything, so don't change anything.
          "ADD 	R12, R12, #0x10\n"            // Second partition
          "ADD 	R1, R1, #1\n"                 // Second partition for the loop
     "dg_sd_fat32_enter:\n"
          "LDRB 	R2, [R12, #0x1BE]\n"          // Partition status
          "LDRB 	R3, [R12, #0x1C2]\n"          // Partition type (FAT32 = 0xB)
          "CMP 	R3, #0xB\n"                   // Is this a FAT32 partition?
          "CMPNE 	R3, #0xC\n"                   // Not 0xB, is it 0xC (FAT32 LBA) then?
          "BNE 	dg_sd_fat32\n"                // No, it isn't. Loop again.
          "CMP 	R2, #0x00\n"                  // It is, check the validity of the partition type
          "CMPNE 	R2, #0x80\n"
          "BNE 	dg_sd_fat32\n"                // Invalid, go to next partition
                                                 // This partition is valid, it's the first one, bingo!
          "MOV 	R4, R12\n"                    // Move the new MBR offset for the partition detection.
          
     "dg_sd_fat32_end:\n"
          // End of DataGhost's FAT32 autodetection code
			//end insertion

			"LDRB 	R1, [R4,#0x1C9]\n"
			"LDRB 	R3, [R4,#0x1C8]\n"
			"LDRB 	R12, [R4,#0x1CC]\n"
			"MOV 	R1, R1,LSL#24\n"
			"ORR 	R1, R1, R3,LSL#16\n"
			"LDRB 	R3, [R4,#0x1C7]\n"
			"LDRB 	R2, [R4,#0x1BE]\n"
//			"LDRB 	LR, [R4,#0x1FF]\n"		// removed
			"ORR 	R1, R1, R3,LSL#8\n"
			"LDRB 	R3, [R4,#0x1C6]\n"
			"CMP 	R2, #0\n"
			"CMPNE 	R2, #0x80\n"
			"ORR 	R1, R1, R3\n"
			"LDRB 	R3, [R4,#0x1CD]\n"
			"MOV 	R3, R3,LSL#24\n"
			"ORR 	R3, R3, R12,LSL#16\n"
			"LDRB 	R12, [R4,#0x1CB]\n"
			"ORR 	R3, R3, R12,LSL#8\n"
			"LDRB 	R12, [R4,#0x1CA]\n"
			"ORR 	R3, R3, R12\n"
//			"LDRB 	R12, [R4,#0x1FE]\n"			// removed
			 "LDRB    R12, [LR,#0x1FE]\n"           // added, First MBR signature byte (0x55), LR is original offset.
			 "LDRB    LR, [LR,#0x1FF]\n"            // added, Last MBR signature byte (0xAA), LR is original offset.
			"MOV 	R4, #0\n"
			"BNE 	loc_FFC44728\n"
			"CMP 	R0, R1\n"
			"BCC 	loc_FFC44728\n"
			"ADD 	R2, R1, R3\n"
			"CMP 	R2, R0\n"
			"CMPLS 	R12, #0x55\n"
			"CMPEQ 	LR, #0xAA\n"
			"MOVEQ 	R6, R1\n"
			"MOVEQ 	R5, R3\n"
			"MOVEQ 	R4, #1\n"
				
		"loc_FFC44728:\n"		

			"MOV 	R0, #2\n"
			"BL 	sub_FFC59D5C\n"
			"CMP 	R4, #0\n"
			"BNE 	loc_FFC44760\n"
			"MOV 	R6, #0\n"
			"MOV 	R0, R8\n"
			"BL 	sub_FFD02ECC\n"
			"MOV 	R5, R0\n"
			"B 	loc_FFC44760\n"
				
		"loc_FFC4474C:\n"		
				
			"MOV 	R5, #0x40\n"
			"B 	loc_FFC44760\n"
				
		"loc_FFC44754:\n"		
				
			"LDR 	R1, =0x37A\n"
			"LDR 	R0, =0xFFC445FC \n"
			"BL 	sub_FFC0BD98\n"			//DebugAssert
				
		"loc_FFC44760:\n"		
				
			"STR 	R6, [R7,#0x44]!\n"
			"MOV 	R0, #1\n"
			"STR 	R5, [R7,#4]\n"
			"LDMFD 	SP!, {R4-R8,PC}\n"
 );
}
//JSE

//JS
void __attribute__((naked,noinline)) JogDial_task_my() { 
 asm volatile(
			"STMFD 	SP!, {R3-R11,LR}\n"
			"BL 	sub_FFC36774\n"
			"LDR 	R11, =0x80000B01\n"
			"LDR 	R8, =0xFFE97FE0\n"
			"LDR 	R7, =0xC0240000\n"
			"LDR 	R6, =0x2494\n"
			"MOV 	R9, #1\n"
			"MOV 	R10, #0\n"
				
		"loc_FFC36548:\n"		
			"LDR 	R3, =0x1AE\n"
			"LDR 	R0, [R6,#0x10]\n"
			"LDR 	R2, =0xFFC36754\n"
			"MOV 	R1, #0\n"
			"BL 	sub_FFC0BC80\n"
			"MOV 	R0, #0x28\n"
			"BL 	sub_ffc176ac\n"		//eventproc_export_SleepTask
//------------------  inserted code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE 	labelB\n"
                "MOV     R0, #40\n"
                "BL 	sub_ffc176ac\n"		//eventproc_export_SleepTask
                "B 	labelA\n"
"labelB:\n"
// end insertion
			"LDR 	R0, [R7,#0x104]\n"
			"MOV 	R0, R0,ASR#16\n"
			"STRH 	R0, [R6]\n"
			"LDRSH 	R2, [R6,#2]\n"
			"SUB 	R1, R0, R2\n"
			"CMP 	R1, #0\n"
			"BEQ 	loc_FFC3660C\n"
			"MOV 	R5, R1\n"
			"RSBLT 	R5, R5, #0\n"
			"MOVLE 	R4, #0\n"
			"MOVGT 	R4, #1\n"
			"CMP 	R5, #0xFF\n"
			"BLS 	loc_FFC365C0\n"
			"CMP 	R1, #0\n"
			"RSBLE 	R1, R2, #0xFF\n"
			"ADDLE 	R1, R1, #0x7F00\n"
			"ADDLE 	R0, R1, R0\n"
			"RSBGT 	R0, R0, #0xFF\n"
			"ADDGT 	R0, R0, #0x7F00\n"
			"ADDGT 	R0, R0, R2\n"
			"ADD 	R5, R0, #0x8000\n"
			"ADD 	R5, R5, #1\n"
			"EOR 	R4, R4, #1\n"
				
		"loc_FFC365C0:\n"		
			"LDR 	R0, [R6,#0x18]\n"
			"CMP 	R0, #0\n"
			"BEQ 	loc_FFC36604\n"
			"LDR 	R0, [R6,#0x20]\n"
			"CMP 	R0, #0\n"
			"BEQ 	loc_FFC365EC\n"
			"LDR 	R1, [R8,R4,LSL#2]\n"
			"CMP 	R1, R0\n"
			"BEQ 	loc_FFC365F4\n"
			"LDR 	R0, =0xB01\n"
			"BL 	sub_FFC63A78\n"
				
		"loc_FFC365EC:\n"		
			"MOV 	R0, R11\n"
			"BL 	sub_FFC63A78\n"
				
		"loc_FFC365F4:\n"		
			"LDR 	R0, [R8,R4,LSL#2]\n"
			"MOV 	R1, R5\n"
			"STR 	R0, [R6,#0x20]\n"
			"BL 	sub_FFC639C0\n"
				
		"loc_FFC36604:\n"		
			"LDRH 	R0, [R6]\n"
			"STRH 	R0, [R6,#2]\n"
				
		"loc_FFC3660C:\n"		
			"STR 	R10, [R7,#0x100]\n"
			"STR 	R9, [R7,#0x108]\n"
			"LDR 	R0, [R6,#0x14]\n"
			"CMP 	R0, #0\n"
			"BLNE 	sub_ffc176ac\n"				//eventproc_export_SleepTask
			"B 	loc_FFC36548\n"
 );
}
//JSE

