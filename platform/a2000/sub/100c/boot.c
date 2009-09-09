#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define DP (void*)0xC02200C4					// direct-print (blue)
#define LED_PR	0xc02200C4
#define LED_RED 0xc02200C8
#define LED_GRN	0xc02200CC
#define LED_PWR	0xc02200D0

const char * const new_sa = &_end;

void CreateTask_blinker();
void __attribute__((naked,noinline)) task_blinker();

// Task override registration
void taskCreateHook(int *p) { 
 p-=17;
 if (p[0]==0xFFC4AE84)  p[0]=(int)capt_seq_task;	
 if (p[0]==0xFFC11060)  p[0]=(int)mykbd_task;
 if (p[0]==0xFFC60268)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFFC47BB4)  p[0]=(int)movie_record_task;	 
}
void taskCreateHook2(int *p) { 
 p-=17;
 if (p[0]==0xFFC60268)  p[0]=(int)init_file_modules_task;
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

void boot();

void boot() {

    long *canon_data_src = (void*)0xFFEDAC70;   // value taken at ROM:FFC00188
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xDF84 - 0x1900; // data_end - data_start 0xDF7C taken at ROM:FFC00138
    long *canon_bss_start = (void*)0xDF84; // just after data 
    long canon_bss_len = 0xD4F38 - 0xDF84; // d4ec8 taken at ROM:FFC00FB4

    long i;

    // enable caches and write buffer...
    // this is a carryover from old dryos ports, may not be useful
    asm volatile (
			"MRC     p15, 0, R0,c1,c0\n"
			"ORR     R0, R0, #0x1000\n"
			"ORR     R0, R0, #4\n"
			"ORR     R0, R0, #1\n"
			"MCR     p15, 0, R0,c1,c0\n"
	    :::"r0"
	  );

    for(i=0;i<canon_data_len/4;i++)
			canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
			canon_bss_start[i]=0;

    asm volatile ("B      sub_FFC001A4_my\n");
};

/* OK */
void __attribute__((naked,noinline)) sub_FFC001A4_my() {

	*(int*)0x1930=(int)taskCreateHook;
	*(int*)0x1934=(int)taskCreateHook2;

	// replacement of sub_FFC111A4	
	// from taskcreate_startup to sub_FFC111A4 
	// and there to sub_FFC35CC4
	// Found at: ROM:FFC30DF0
  *(int*)(0x228C+0x4) = (*(int*)0xC02200B8)&1 ? 0x100000: 0x200000; 
     
     asm volatile (
		     "LDR     R0, =0xFFC0021C\n"				// exception handler code
		     "MOV     R1, #0\n"
		     "LDR     R3, =0xFFC00254\n"
		     
		"loc_FFC001B0:\n"
		     "CMP     R0, R3\n"									// load exception vector
		     "LDRCC   R2, [R0],#4\n"
		     "STRCC   R2, [R1],#4\n"
		     "BCC     loc_FFC001B0\n"
		     "LDR     R0, =0xFFC00254\n"
		     "MOV     R1, #0x4B0\n"
		     "LDR     R3, =0xFFC00468\n"
		     
		"loc_FFC001CC:\n"
		     "CMP     R0, R3\n"									// copy IRQ handler to ITCM starting at 0x4b0, 532 bytes up to 0x6C4
		     "LDRCC   R2, [R0],#4\n"
		     "STRCC   R2, [R1],#4\n"
		     "BCC     loc_FFC001CC\n"
		     "MOV     R0, #0xD2\n"
		     "MSR     CPSR_cxsf, R0\n"					// set CPSR mode = IRQ, ints disabled
		     "MOV     SP, #0x1000\n"						// irq mode SP
		     "MOV     R0, #0xD3\n"
		     "MSR     CPSR_cxsf, R0\n"					// set CPSR mode = Super, ints disabled
		     "MOV     SP, #0x1000\n"						// super mode SP
		     "LDR     R0, =0xFFC00210\n"
		     "LDR     R2, =0xEEEEEEEE\n"
		     "MOV     R3, #0x1000\n"
		     
		"loc_FFC00200:\n"
		     "CMP     R0, R3\n"            // clear ITCM 0x6C4-end with EEEEEEEE
		     "STRCC   R2, [R0],#4\n"
		     "BCC     loc_FFC00200\n"
		     "BL      sub_FFC00F98_my\n"     // --> Hook

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

/* OK */
void __attribute__((naked,noinline)) sub_FFC00F98_my() {
 
	asm volatile (

		     "STR     LR, [SP,#-0x4]!\n"
		     "SUB     SP, SP, #0x74\n"
		     "MOV     R0, SP\n"
		     "MOV     R1, #0x74\n"
		     "BL      sub_FFE723D0\n"
		     "MOV     R0, #0x53000\n"
		     "STR     R0, [SP,#0x74-0x70]\n"

				 // Original code...
   	     //"LDR     R0, =0xD4F38\n"

				 // Replacement
 		     "LDR     R0, =new_sa\n"
   	     "LDR     R0, [R0]\n"

		     "LDR     R2, =0x279C00\n"
		     "LDR     R1, =0x2724A8\n"
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

		     "LDR     R1, =sub_FFC04D90_my\n"  // -> Hook

		     "STR     R0, [SP,#0x74-0x54]\n"
		     "MOV     R0, #0x96\n"
		     "STR     R0, [SP,#0x74-0x50]\n"
		     "MOV     R0, #0x78\n"
		     "STR     R0, [SP,#0x74-0x4C]\n"
		     "MOV     R0, #0x64\n"
		     "STR     R0, [SP,#0x74-0x48]\n"
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
		     "MOV     R0, SP\n"
		     "MOV     R2, #0\n"

		     "BL      sub_FFC02D3C\n"

		     "ADD     SP, SP, #0x74\n"
		     "LDR     PC, [SP],#4\n"
     );
}


/* OK */
void __attribute__((naked,noinline)) sub_FFC04D90_my() {

        asm volatile (

              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FFC00944\n"
              "BL      sub_FFC09708\n"           // _dmSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EA4\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "BL      sub_FFC049B8\n"           // termDriverInit
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EAC\n"
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "LDR     R0, =0xFFC04EBC\n"				 // /_term
              "BL      sub_FFC04AA0\n"           // termDeviceCreate
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EC4\n"				 // termDeviceCreate
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "LDR     R0, =0xFFC04EBC\n"
              "BL      sub_FFC0354C\n"           // stdioSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04ED8\n"				 // stdioSetup
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "BL      sub_FFC09290\n"           // stdlibSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EE4\n"				 // stdlibSetup
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "BL      sub_FFC0147C\n"           // armlib_setup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EF0\n"				 // armlib_setup
              "BLLT    sub_FFC04E84\n"           // err_init_task
              "LDMFD   SP!, {R4,LR}\n"
							"B 	taskcreate_Startup_my\n"		// <--------------- changed, 0xFFC0CD6C in fw
        );
};

/* OK */
void __attribute__((naked,noinline)) taskcreate_Startup_my() {

     asm volatile (

          "STMFD   SP!, {R3,LR}\n"
				  "BL	     sub_FFC11198\n"				// j_nullsub_234
          "BL      sub_FFC18AE0\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC0CDA0\n"
          "BL      sub_FFC11194\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC0CDA0\n"
	  			"LDR	   R1, =0xC0022000\n"
          "MOV     R0, #0x44\n"
          "STR     R0, [R1,#0xA4]\n"
          "STR     R0, [R1,#0xA0]\n"
     "loc_FFC0CD9C:\n"									// CODE XREF: taskcreate_Startup:loc_FFC0CD9C
          "B       loc_FFC0CD9C\n"
     "loc_FFC0CDA0:\n"									// CODE XREF: taskcreate_Startup+10
          //"BL      sub_FFC111A0\n"		// removed for correct power-on on "on/off" button.
				  "BL	     sub_FFC1119C\n"			// j_nullsub_235
          "BL      sub_FFC16E70\n"
          "LDR     R1, =0x2CE000\n"
          "MOV     R0, #0\n"
          "BL      sub_FFC170B8\n"
          "BL      sub_FFC17064\n"			// _sub_FFC17064__KerSys_c__548 ; LOCATION: KerSys.c:548
          "MOV     R3, #0\n"
          "STR     R3, [SP]\n"
					"LDR 	R3, =task_Startup_my\n"		// <----------- changed, 0x:FFC0CD10 in fw
          "MOV     R2, #0\n"
          "MOV     R1, #0x19\n"
          "LDR     R0, =0xFFC0CDE8\n"							// "Startup"
          "BL      sub_FFC0B8C0\n"               // eventproc_export_CreateTask ; LOCATION: KerTask.c:163
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R12,PC}\n"
     			".ltorg\n"
     );
}

/* OK */
void __attribute__((naked,noinline)) task_Startup_my() {

     asm volatile (

          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FFC0515C\n"			// taskcreate_ClockSave
          "BL      sub_FFC12304\n"
          "BL      sub_FFC10BE0\n"
	  			"BL	     sub_FFC18B20\n"			// j_nullsub_238
          "BL      sub_FFC18CE8\n"
          //"BL      sub_FFC18BA8\n"		// //start diskboot.bin, //StartDiskboot --> removed
          "BL      sub_FFC18EA0\n"
          "BL      sub_FFC18D38\n"
          "BL      sub_FFC16164\n"
	  			"BL	     sub_FFC18EA4\n"
          "BL 	CreateTask_spytask\n"    // <--- function added
				  "BL	     sub_FFC11094\n"      // taskcreate_PhySw
          "BL      sub_FFC141F0\n"		
          "BL      sub_FFC18EBC\n"
	  			"BL	     sub_FFC0FC08\n"			// nullsub_2
          "BL      sub_FFC10530\n"
          "BL      sub_FFC188C0\n"			// taskcreate_Bye
          "BL      sub_FFC10B90\n"
          "BL      sub_FFC1044C\n"			// _sub_FFC1044C__LowBat_c__2 ; LOCATION: LowBat.c:2
          "BL      sub_FFC19944\n"
          "BL      sub_FFC10424\n"
          "LDMFD   SP!, {R4,LR}\n"
          "B       sub_FFC0505C\n"			// _sub_FFC0505C__ClkEnabler_V_J_c__144 ; LOCATION: ClkEnabler_V_J.c:144
     ".ltorg\n"
     );
}

void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(


			"STMFD 	SP!, {R4-R6,LR}\n"
			"BL 	  sub_FFC5994C\n"
			"LDR 	  R5, =0x5006\n"
			"MOVS 	R4, R0\n"
			"MOVNE 	R1, #0\n"
			"MOVNE 	R0, R5\n"
			"BLNE 	sub_FFC5C03C\n"		//eventproc_export_PostLogicalEventToUI
			"BL 	  sub_FFC59978_my\n"			// <---------- changed
      "BL 	  core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask
			"CMP 	R4, #0\n"
			"MOVEQ 	R0, R5\n"
			"LDMEQFD 	SP!, {R4-R6,LR}\n"
			"MOVEQ 	R1, #0\n"
			"BEQ 	sub_FFC5C03C\n"		//eventproc_export_PostLogicalEventToUI
			"LDMFD 	SP!, {R4-R6,PC}\n"
 );
}

/* OK */
void __attribute__((naked,noinline)) sub_FFC59978_my() {

     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FFC3F894_my\n"       // +----> Hook for SDHC booting (ex sub_FFC3FC50_my) 
					"BL 		 sub_FFCE9BA4\n"					// nullsub_101
          "LDR     R4, =0x5454\n"
          "LDR     R0, [R4,#4]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC599AC\n"
          "BL      sub_FFC3ED5C\n"
          "BL      sub_FFCDF96C\n"
          "BL      sub_FFC3ED5C\n"
          "BL      sub_FFC3AC30\n"
          "BL      sub_FFC3EC5C\n"
          "BL      sub_FFCDFA38\n"
          
     "loc_FFC599AC:\n"
          "MOV     R0, #1\n"
          "STR     R0, [R4]\n"
          "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC3F894_my() {

     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "MOV     R6, #0\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3F354\n"
          "LDR     R4, =0x176C4\n"
          "MOV     R5, #0\n"
          "LDR     R0, [R4,#0x38]\n"
          "BL      sub_FFC3FDB4\n"
          "CMP     R0, #0\n"
          "LDREQ   R0, =0x26DC\n"
          "STREQ   R5, [R0,#0x10]\n"
          "STREQ   R5, [R0,#0x14]\n"
          "STREQ   R5, [R0,#0x18]\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3F394\n"				// _sub_FFC3F394__Mounter_c__824 ; LOCATION: Mounter.c:824
          "MOV     R0, R6\n"
          "BL      sub_FFC3F6D0_my\n"     // +----> Hook for SDHC booting (ex sub_FFC3FA8C_my)
          "MOV     R5, R0\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3F73C\n" 				// _sub_FFC3F73C__Mounter_c__8 ; LOCATION: Mounter.c:8
          "LDR     R1, [R4,#0x3C]\n"
          "AND     R2, R5, R0\n"
          "CMP     R1, #0\n"
          "MOV     R0, #0\n"
          "MOVEQ   R0, #0x80000001\n"
          "BEQ     loc_FFC3F928\n"
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

     "loc_FFC3F928:\n"
          "STR     R0, [R4,#0x40]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC3F6D0_my() {

     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "LDR     R5, =0x26DC\n"
          "MOV     R6, R0\n"
          "LDR     R0, [R5,#0x14]\n"
          "CMP     R0, #0\n"
          "MOVNE   R0, #1\n"
          "LDMNEFD SP!, {R4-R6,PC}\n"
          "MOV     R0, #0x17\n"
          "MUL     R1, R0, R6\n"
          "LDR     R0, =0x176C4\n"
          "ADD     R4, R0, R1,LSL#2\n"
          "LDR     R0, [R4,#0x38]\n"
          "MOV     R1, R6\n"
          "BL      sub_FFC3F460_my\n"     // +----> Hook for SDHC booting (ex sub_FFC3F81C_my) _sub_FFC3F460__Mounter_c__0 ; LOCATION: Mounter.c:0
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "LDR     R0, [R4,#0x38]\n"
          "MOV     R1, R6\n"
          "BL      sub_FFC3F5C8\n"				// _sub_FFC3F5C8__Mounter_c__0 ; LOCATION: Mounter.c:0
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "MOV     R0, R6\n"
          "BL      sub_FFC3EF5C\n"
          "CMP     R0, #0\n"
          "MOVNE   R1, #1\n"
          "STRNE   R1, [R5,#0x14]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FFC3F460_my() {

     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "MOV     R8, R0\n"
          "MOV     R0, #0x17\n"
          "MUL     R1, R0, R1\n"
          "LDR     R0, =0x176C4\n"
          "MOV     R6, #0\n"
          "ADD     R7, R0, R1,LSL#2\n"
          "LDR     R0, [R7,#0x3C]\n"
          "MOV     R5, #0\n"
          "CMP     R0, #6\n"
          "ADDLS   PC, PC, R0,LSL#2\n"
          "B       loc_FFC3F5AC\n"

		"loc_FFC3F490:\n"
	  		"B       loc_FFC3F4C4\n"
	
		"loc_FFC3F494:\n"
	  	"B       loc_FFC3F4AC\n"
	
		"loc_FFC3F498:\n"
		  "B       loc_FFC3F4AC\n"

		"loc_FFC3F49C:\n"
		  "B       loc_FFC3F4AC\n"

		"loc_FFC3F4A0:\n"
		  "B       loc_FFC3F4AC\n"

		"loc_FFC3F4A4:\n"
		  "B       loc_FFC3F5A4\n"

		"loc_FFC3F4A8:\n"
		  "B       loc_FFC3F4AC\n"

		"loc_FFC3F4AC:\n"
		  "MOV     R2, #0\n"
	  	"MOV     R1, #0x200\n"
	  	"MOV     R0, #2\n"
	  	"BL      sub_FFC53A1C\n"
	  	"MOVS    R4, R0\n"
	  	"BNE     loc_FFC3F4CC\n"
	
		"loc_FFC3F4C4:\n"
	  	"MOV     R0, #0\n"
	  	"LDMFD   SP!, {R4-R8,PC}\n"
	
		"loc_FFC3F4CC:\n"
	  	"LDR     R12, [R7,#0x4C]\n"
	  	"MOV     R3, R4\n"
	  	"MOV     R2, #1\n"
	  	"MOV     R1, #0\n"
	  	"MOV     R0, R8\n"

//		"BLX 	R12\n"			// !! Workaround !!
			"MOV 	LR, PC\n"			// gcc won't compile "BLX 	R12" nor "BL 	R12".
			"MOV 	PC, R12\n"			// workaround: make your own "BL" and hope we don't need the change to thumb-mode

	  	"CMP     R0, #1\n"
	  	"BNE     loc_FFC3F4F8\n"
	  	"MOV     R0, #2\n"
	  	"BL      sub_FFC53B68\n"		// _sub_FFC53B68__ExMemMan_c__0 ; LOCATION: ExMemMan.c:0
	  	"B       loc_FFC3F4C4\n"

     "loc_FFC3F4F8:\n"
          "MOV     R0, R8\n"
          "BL      sub_FFCF4E44\n"

					//insertion of new code for FAT32 autodetection
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
          "LDRB    R1, [R4,#0x1C9]\n"            // 4th byte of LBA
          "LDRB    R3, [R4,#0x1C8]\n"            // 3rd byte of LBA
          "LDRB    R12, [R4,#0x1CC]\n"           // 3rd byte of partition length
          "MOV     R1, R1,LSL#24\n"              // Shift and...
          "ORR     R1, R1, R3,LSL#16\n"          // combine LBA bytes (endianness fix)
          "LDRB    R3, [R4,#0x1C7]\n"            // 2nd byte of LBA
          "LDRB    R2, [R4,#0x1BE]\n"            // Partition status (0x00=nonboot, 0x80=boot, other=bad)
          //"LDRB    LR, [R4,#0x1FF]\n"            // Last MBR signature byte (0xAA)
          "ORR     R1, R1, R3,LSL#8\n"           // Combine more LBA bytes
          "LDRB    R3, [R4,#0x1C6]\n"            // 1st byte of LBA
          "CMP     R2, #0\n"                     // Check partition status
          "CMPNE   R2, #0x80\n"                  // and again
          "ORR     R1, R1, R3\n"                 // Combine LBA into final value
          "LDRB    R3, [R4,#0x1CD]\n"            // 4th byte of partition length
          "MOV     R3, R3,LSL#24\n"              // Shift and...
          "ORR     R3, R3, R12,LSL#16\n"         // combine partition length bytes
          "LDRB    R12, [R4,#0x1CB]\n"           // 2nd byte of partition length
          "ORR     R3, R3, R12,LSL#8\n"          // Combine partition length bytes
          "LDRB    R12, [R4,#0x1CA]\n"           // 1st byte of partition length
          "ORR     R3, R3, R12\n"                // Combine partition length bytes into final value
          //"LDRB    R12, [R4,#0x1FE]\n"           // First MBR signature byte (0x55)
          "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
          "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.
          "MOV     R4, #0\n"                     // This value previously held a pointer to the partition table :(
          "BNE     loc_FFC3F580\n"               // Jump out if the partition is malformed (partition status \'other\')
          "CMP     R0, R1\n"
          "BCC     loc_FFC3F580\n"               // Jump out if R0 < R1 (probably checking for a valid LBA addr)
          "ADD     R2, R1, R3\n"                 // R2 = partition start address + length = partition end address
          "CMP     R2, R0\n"                     // Guess: CMPLS is used to check for an overflow, the partition end address cannot be negative.
          "CMPLS   R12, #0x55\n"                 // Check MBR signature with original offset
          "CMPEQ   LR, #0xAA\n"                  // Check MBR signature with original offset
          "MOVEQ   R6, R1\n"
          "MOVEQ   R5, R3\n"
          "MOVEQ   R4, #1\n"

     "loc_FFC3F580:\n"
          //"MOV     R0, #3\n"
          "MOV     R0, #2\n"
          "BL      sub_FFC53B68\n"			// _sub_FFC53B68__ExMemMan_c__0 ; LOCATION: ExMemMan.c:0
          "CMP     R4, #0\n"
          "BNE     loc_FFC3F5B8\n"
          "MOV     R6, #0\n"
          "MOV     R0, R8\n"
          "BL      sub_FFCF4E44\n"
          "MOV     R5, R0\n"
          "B       loc_FFC3F5B8\n"

     "loc_FFC3F5A4:\n"
          "MOV     R5, #0x40\n"
          "B       loc_FFC3F5B8\n"

     "loc_FFC3F5AC:\n"
          "LDR     R1, =0x37A\n"
          "LDR     R0, =0xFFC3F454\n"			// "Mounter.c"
          "BL      sub_FFC0BD98\n"				// DebugAssert

     "loc_FFC3F5B8:\n"
          "STR     R6, [R7,#0x44]!\n"
          "MOV     R0, #1\n"
          "STR     R5, [R7,#4]\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

void __attribute__((naked,noinline)) task_blinker() {

		volatile long *p=(void*)0xC02200CC;
    
    int delay = 0x200000;
    int i;
    
		while(1){
			p[0]=0x46;
			for(i=0;i<delay;i++){
				asm ("nop\n");
				asm ("nop\n");
			}
			p[0]=0x44;
			for(i=0;i<delay;i++){
				asm ("nop\n");
				asm ("nop\n");
			}
	}
};

void CreateTask_blinker() {
        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};
