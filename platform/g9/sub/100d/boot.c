#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "stdlib.h"

//extern void draw_txt_string(int col, int row, const char *str, color cl); 

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void taskCreateHook(int *p) { 
 p-=16;
// TODO can save some memory by hooking other tasks this way
// if (p[0]==0x)  p[0]=(int)capt_seq_task;
// if (p[0]==0x)  p[0]=(int)movie_record_task;
// if (p[0]==0x)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFF8B8B90)  p[0]=(int)exp_drv_task;
}

void taskCreateHook2(int *p) { 
 p-=16;
// if (p[0]==0x)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFF8B8B90)  p[0]=(int)exp_drv_task;
}

/*
void CreateTask_blinker(); 
void task_blinker();
void dump_chdk();


void boot();


#define DPs (void*)0xC022006C					// direct-print (blue)
#define LED_AF (void*)0xC0220094	//LED_AF
#define LED_ISO (void*)0xC02200B0	//LED_ISO   
#define LED_PWR (void*)0xC0220068	//LED_PWR   
#define LED_BLUE (void*)0xC022006C	//LED_BLUE
#define DELAYs 3000000

void debug_my_blink_green()
{
	volatile long *p = (void*)LED_AF;       		// turned off later, so assumed to be power
	int counter;

	// DEBUG: blink led
	counter = DELAYs; *p = 0x46;
	while (counter--) { asm("nop\n nop\n"); };
	counter = DELAYs; *p = 0x44;
	while (counter--) { asm("nop\n nop\n"); };
}

void debug_my_pause()
{
	int counter;

	// DEBUG: blink led
	counter = DELAYs; 
	while (counter--) { asm("nop\n nop\n"); };
	counter = DELAYs; 
	while (counter--) { asm("nop\n nop\n"); };
}

void debug_my_blink_blue()
{
	volatile long *p = (void*)LED_BLUE;       		// turned off later, so assumed to be power
	int counter;

	// DEBUG: blink led
	counter = DELAYs; *p = 0x46;
	while (counter--) { asm("nop\n nop\n"); };
	counter = DELAYs; *p = 0x44;
	while (counter--) { asm("nop\n nop\n"); };
}




#define DP (void*)0xC0220068	// led_pwr DEBUG

#define DEBUG_LED 0xC022006C //ok //used iso blue, was 0xc02200C4  +++


#define DELAY 5000000			// DEBUG

*/

void boot() { //#fs


    long *canon_data_src = (void*)0xFFB2E384; // OK	//canon_data_src!!!  @FF810130
    long *canon_data_dst = (void*)0x1900;	// OK  //MEMBASEADDR   @FF810134
    long canon_data_len = 0x140E4- 0x1900; // data_end - data_start     
    long *canon_bss_start = (void*)0x140e4; // just after data 	// OK	//@FF810138
    long canon_bss_len = 0xb0b68 - 0x140e4; //  MEMISOSTART - 

    long i;


    // Code taken from VxWorks CHDK. turns caches on
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

    *(int*)(0x261C+8)= (*(int*)0xC02200C0)&1 ? 1 : 2;  // replacement of sub_FF822E10

/*
    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"BIC     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
*/

    *(int*)0x1930=(int)taskCreateHook; 
    *(int*)0x1934=(int)taskCreateHook2; 

    // jump to init-sequence that follows the data-copy-routine 

  
	asm volatile ("B      sub_FF8101a4_my\n");
	//asm volatile ("B      sub_FF8101a4\n");
	
}; //#fe


// init //OK
void __attribute__((naked,noinline)) sub_FF8101a4_my() { //#fs  OK

				
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
                "BL      sub_FF810FB8_my\n"
      );
				
}; //#fe


//OK
void __attribute__((naked,noinline)) sub_FF810FB8_my() { //#fs  OK  h_usrKernelInit


        asm volatile ( 
                "STR     LR, [SP,#-4]!\n"
                "SUB     SP, SP, #0x74\n"
                "MOV     R0, SP\n"
                "MOV     R1, #0x74\n"
                "BL      sub_FFABD388\n"
                "MOV     R0, #0x53000\n"
                "STR     R0, [SP,#0x74-0x70]\n"
				
	);
				//"LDR     R0, =0xB0B68"
        asm volatile (
              "LDR     R0, =new_sa\n"
              "LDR     R0, [R0]\n"
        );
        asm volatile (				
                "LDR     R2, =0x2ABC00\n"
                "LDR     R1, =0x2A4968\n"
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
                //"STRD    R0, [SP,#0x74-0x54]\n"		  // "strd not supported by cpu" claims gcc
				"STR      R0, [SP,#0x74-0x54]\n"          // split in two single-word STRs
				"STR      R1, [SP,#0x74-0x50]\n"
                "MOV     R0, #0x78\n"
                //"STRD    R0, [SP,#0x74-0x4C]\n"		  // "strd not supported by cpu" claims gcc
				"STR      R0, [SP,#0x74-0x4C]\n"          // split in two single-word STRs
				"STR      R1, [SP,#0x74-0x48]\n"
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
				//"LDR     R1, =0xFF814DBC\n"         
                "LDR     R1, =uHwSetup_my\n"	//<---------------------------------------chdk
                "MOV     R0, SP\n"
                "MOV     R2, #0\n"
                "BL      sub_FF812D70\n"
                "ADD     SP, SP, #0x74\n"
                "LDR     PC, [SP],#4\n"
			);
	
}; //#fe


//OK
void __attribute__((naked,noinline)) uHwSetup_my() { //#fs FF814DBC

	asm volatile (		
			//debug ok
		
              "STMFD   SP!, {R4,LR}\n"
			  "BL      sub_FF81095C\n"
			  "BL      sub_FF819948\n"          
			  "CMP     R0, #0\n"
			  "LDRLT   R0, =0xFF814ED0\n"       
              "BLLT    sub_FF814EB0\n"          
		      "BL      sub_FF8149E0\n"          // _termDriverInit
			  "CMP     R0, #0\n"
			  "LDRLT   R0, =0xFF814ED8\n"       // aTermdriverinit
	          "BLLT    sub_FF814EB0\n"          
			  "LDR     R0, =0xFF814EE8\n"       // a_term
			  			  
              "BL      sub_FF814ACC\n"          // _termDeviceCreate
			  "CMP     R0, #0\n"
              "LDRLT   R0, =0xFF814EF0\n"       // aTermdevicecrea
              "BLLT    sub_FF814EB0\n"          
              "LDR     R0, =0xFF814EE8\n"       // a_term
              "BL      sub_FF81357C\n"          // _stdioSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFF814F04\n"       // aStdiosetup
              "BLLT    sub_FF814EB0\n"          
              "BL      sub_FF8194D0\n"          // _stdlibSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFF814F10\n"       // aStdlibsetup
              "BLLT    sub_FF814EB0\n"          
              "BL      sub_FF8114D0\n"          // _armlib_setup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFF814F1C\n"       // aArmlib_setup
              "BLLT    sub_FF814EB0\n"          //   _err_init_task
              "LDMFD   SP!, {R4,LR}\n"
              "B       CreateTask_Startup_my\n" //<---------------------------------------chdk

        );
}; //#fe


//OK 
void __attribute__((naked,noinline)) CreateTask_Startup_my() { //#fs FF81DC0C	

		asm volatile (		
        "STMFD   SP!, {R3,LR}\n"
                //"BL      nullsub_3\n"
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
                //"BL      nullsub_4\n"
                "BL      sub_FF82A488\n"
                "MOV     R1, #0x300000\n"
                "MOV     R0, #0\n"
                "BL      sub_FF82A6D0\n"
                "BL      sub_FF82A67C\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP,#8-0x08]\n"
                "LDR     R3, =task_Startup_my\n"		// originally FF81DBB0 <---------------------------------------chdk
                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFF81DC90\n"			//"Startup"
                "BL      sub_FF81BAF0\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
				);
		
 //OK
}; //#fe



			

//OK
void __attribute__((naked,noinline)) task_Startup_my() { //#fs originally FF81DBB0
       
       	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
				"BL      sub_FF81517C\n"  
				"BL      sub_FF823FA0\n"
                "BL      sub_FF820E60\n"
                //"BL      j_nullsub_177\n"
				"BL      sub_FF82CADC\n"
				//"BL      sub_FF82C9C4\n"	// skip diskboot 
		);
        CreateTask_spytask();  // <------------
        asm volatile (
			   "BL      sub_FF82CCA4\n"
               "BL      sub_FF82CB2C\n"		
               "BL      sub_FF8299CC\n"
               "BL      sub_FF82CCA8\n"
        );
         CreateTask_PhySw(); //<---------------
        asm volatile (
				//"BL      sub_FF822DA8\n"  // (taskcreate_PhySw) 
				//"BL      sub_FF82629C\n"
				"BL      sub_FF82629C_my\n"		// divert to intercept task_ShootSeqTask------------------------------>
				"BL      sub_FF82CCC0\n"
                //"BL      nullsub_2\n"
                "BL      sub_FF822130\n"
                "BL      sub_FF82C6A8\n"  // taskcreate_Bye\n"
                "BL      sub_FF8228D4\n"
                "BL      sub_FF82203C\n"  // taskcreate_TempCheck\n"
				//"BL      sub_FF82D720\n"
				"BL      sub_FF82D720_my\n" 		// divert for SDHC-bootdisk-support<--------------------------------- 
				"BL      sub_FF821FF8\n"
                "LDMFD   SP!, {R4,LR}\n" 
                "B       sub_FF815088\n"
             );

}; //#fe


void CreateTask_spytask() { //#fs 
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

void CreateTask_PhySw() { //#fs 
        _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
        asm volatile (
				"BL      sub_FF84962C\n"	//taskcreate_JogDial
        ); 
}; //#fe


//OK
void __attribute__((naked,noinline)) sub_FF82629C_my() { //#fs  

		 asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x1D38\n" 
                "MOV     R0, #0\n"
                "MOV     R1, #4\n"
                "STR     R0, [R4,#0xC]\n" 
                "BL      sub_FF81BE20\n" 
                "STR     R0, [R4,#4]\n"	
                "MOV     R0, #0\n"
                "MOV     R1, #1\n"
                "BL      sub_FF81BE44\n" 
                "STR     R0, [R4,#8]\n" 
                "BL      sub_FF864A14\n"
                "BL      sub_FF86383C\n"				
				"BL      sub_FF8601A0_my\n"     // divert this for ShootSeqTask 	<------------------
				"BL      sub_FF864CFC\n" 
                "LDR     R0, [R4,#4]\n" 
                "LDMFD   SP!, {R4,LR}\n"
                "MOV     R1, #0x1000\n"
                "B       sub_FF829D2C\n"
        );
}; //#fe
//OK
void __attribute__((naked,noinline)) sub_FF8601A0_my() { //#fs 

	      asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x57EC\n" 
                "LDR     R0, [R4,#8]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF86020C\n" 
                //"BL      nullsub_30\n"
                "MOV     R1, #1\n"
                "MOV     R0, #0\n"
                "BL      sub_FF81BE44\n" 
                "STR     R0, [R4,#0x20]\n" 
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
                "BL      sub_FF81BE20\n" 
                "STR     R0,[R4,#0x24]\n"
                "BL      sub_FF860584\n" 
                "BL      sub_FF860370\n"   
                "MOV     R0, #0\n"
                "STR     R0, [R4,#0x1C]\n" 
                "ADD     R0, R4, #0x28\n" 
                "MOV     R1, #0\n"
                "STR     R1, [R0],#4\n"
                "STR     R1, [R0]\n"
                "BL      sub_FF86089C\n" 
                "BL      sub_FF864EA8\n" 
                "BL      sub_FF8631AC\n"		
                "BL      sub_FF8614E8_my\n"     // continue here for task_CaptSeqTask  <----------------------------
				
                "BL      sub_FF862CA8\n"		
        "loc_FF86020C:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4,#8]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

//OK ****
void __attribute__((naked,noinline)) sub_FF8614E8_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R3-R5,LR}\n"
                "LDR     R2, =0x1E3C0\n" 
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
        "loc_FF8614F8:\n"
                "ADD     R3, R2, R0,LSL#4\n"
                "ADD     R0, R0, #1\n"
                "CMP     R0, #5\n"
                "STR     R1, [R3,#8]\n"
                "BCC     loc_FF8614F8\n" 
				"LDR     R0, =0x1E410\n" 
				"STR     R1, [R0,#8]\n" 
				"ADD     R0, R0, #0x10\n" 
				"STR     R1, [R0,#8]\n" 
                "BL      sub_FF942928\n" 
                "BL      sub_FF944F7C\n" 
                "MOV     R1, #5\n"
                "MOV     R0, #0\n"
                "BL      sub_FF81BDFC\n"
                "LDR     R4, =0x583C\n" 
                "LDR     R1, =0x1001FF\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, #0\n"
                "BL      sub_FF81BE20\n" 
				"STR     R0, [R4,#0x10]\n" 
                "MOV     R3, #0\n"				
                // "STR     R3, [SP,#0x10+var_10]\n"
				"STR     R3, [SP]\n"
//                "LDR     R3, =0xFF861210\n" 
				"LDR     R3, =task_CaptSeqTask_my\n" //  task_CaptSeqTask  <-------------------------
				"LDR     R0, =0xFF861710\n"             // aCaptseqtask ; "CaptSeqTask" 
                "MOV     R2, #0x1000\n"
                "MOV     R1, #0x17\n"
                "BL      sub_FF81BDC8\n"                
                "LDMFD   SP!, {R3-R5,PC}\n"
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

//OK
void __attribute__((naked,noinline)) sub_FF82D720_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FF873F90\n"   
                "BL      sub_FF824504\n"    // IsFactoryMode"  
                "CMP     R0, #1\n"
                "BNE     loc_FF82D740\n"  
                "BL      sub_FF8773E0\n" 
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FF82457C\n"    // StartFactoryModeController" 
         "loc_FF82D740:\n" 
                "BL      sub_FF876264\n" 
                "LDR     R4, =0x1E50\n" 
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "LDMNEFD SP!, {R4,PC}\n"
                "MOV     R1, #0\n"
                //"LDR     R0, =0xFF82D250\n"        
                "LDR     R0, =sub_FF82D250_my\n"        // continue here for SDHC-boot-support   <------------------
                "BL      sub_FF8709DC\n"    
                "STR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

//OK
void __attribute__((naked,noinline)) sub_FF82D250_my() { //#fs    
        asm volatile (
                
                 "STMFD   SP!, {R3-R11,LR}\n"
                 "LDR     R6, =0x1E50\n"
                 "MOV     R5, R1\n"
                 "LDR     R0, [R6,#0x14]\n"
                 "MOV     R4, R3\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF82D274\n"
                 "BL      sub_FF87486C\n"
                 "B       loc_FF82D65C\n"
        "loc_FF82D274:\n" 
                "LDR     R12, =0x1162\n" 
                "LDR     R10, =0x1005\n"  
                "CMP     R5, R12\n"  
                "MOV     R7, #0\n"  
                "MOV     R8, #1\n"  
                "BEQ     loc_FF82D67C\n"  
                "BGT     loc_FF82D3C8\n"  
                "LDR     R12, =0x1062\n"  
                "CMP     R5, R12\n"  
                "BEQ     loc_FF82D718\n"  
                "BGT     loc_FF82D33C\n"  
                "CMP     R5, R10\n"  
                "BEQ     loc_FF82D6A8\n" 
                "BGT     loc_FF82D314\n"  
                "LDR     R9, =0x9A3\n"  
                "CMP     R5, R9\n"  
                "BEQ     loc_FF82D63C\n"
				"BGT     loc_FF82D2F0\n"  
                "SUB     R12, R5, #0x800\n"  
                "SUBS    R12, R12, #3\n" 
                "BEQ     loc_FF82D4D8\n" 
                "SUB     R12, R5, #0x800\n"  
                "SUBS    R12, R12, #0x158\n"  
                "BNE     loc_FF82D66C\n"  
                "TST     R4, #0x80000000\n"  
                "MOVNE   R0, #1\n"  
                "BNE     locret_FF82D534\n"  
                "BL      sub_FF87DA3C\n" 
				"CMP     R0, #0\n"
                "BLEQ    sub_FF829828\n"  
				"B       loc_FF82D65C\n"  
"loc_FF82D2F0:\n"       
				"SUB     R12, R5, #0x900\n"
				"SUBS    R12, R12, #0xA5\n"
				"BEQ     loc_FF82D63C\n"
				"SUB     R12, R5, #0x1000\n"
				"SUBS    R12, R12, #3\n"
				"BNE     loc_FF82D66C\n"
				"BL      sub_FF82D1B4\n"
				"MOV     R1, R4\n"
				"B       loc_FF82D674\n"
"loc_FF82D314:\n"       
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0x56\n"
                "SUBNE   R12, R5, #0x1000\n"
                "SUBNES  R12, R12, #0x5B\n"
                "SUBNE   R12, R5, #0x1000\n"
                "SUBNES  R12, R12, #0x5E\n"
                "SUBNE   R12, R5, #0x1000\n"
                "SUBNES  R12, R12, #0x61\n"
                "BNE     loc_FF82D66C\n"
                "B       loc_FF82D718\n"
"loc_FF82D33C:\n"       
                "LDR     R12, =0x10AD\n"
                "CMP     R5, R12\n"
                "BEQ     loc_FF82D698\n"
                "BGT     loc_FF82D38C\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0x63\n"
                "SUBNE   R12, R5, #0x1000\n"
                "SUBNES  R12, R12, #0x65\n"
                "BEQ     loc_FF82D718\n"
                "SUB     R12, R5, #0x1000\n"
                "LDR     R0, =0x10A3\n"
                "SUBS    R12, R12, #0xA9\n"
                "BEQ     loc_FF82D68C\n"
                "SUB     R12, R5, #0x1000\n"
                "SUBS    R12, R12, #0xAA\n"
                "BNE     loc_FF82D66C\n"
                "BL      sub_FF872EB8\n" 
                "CMP     R0, #0\n"
                "BEQ     loc_FF82D6A4\n"
                "B       loc_FF82D65C\n"
"loc_FF82D38C:\n"  
                "SUB     R12, R5, #0x1000\n"  
                "SUBS    R12, R12, #0xAE\n"  
                "BEQ     loc_FF82D6A4\n"  
                "SUB     R12, R5, #0x1000\n"  
                "SUBS    R12, R12, #0xAF\n" 
                "BEQ     loc_FF82D698\n"  
                "SUB     R12, R5, #0x1000\n"  
                "SUBS    R12, R12, #0xB0\n"  
                "BEQ     loc_FF82D6A4\n"  
                "SUB     R12, R5, #0x1000\n"  
                "SUBS    R12, R12, #0xB2\n"  
                "BNE     loc_FF82D66C\n"  
				"LDR     R0, =0x1008\n"  
				"MOV     R1, R4\n"  
				"B       loc_FF82D674\n"  
"loc_FF82D3C8:\n"
                 "LDR     R11, =0x201B\n"
                 "LDR     R0, =0x1E50\n"
                 "CMP     R5, R11\n"
                 "LDR     R2, [R0,#0x10]!\n"
                 "LDR     R1, [R0,#0x10]\n"
                 "SUB     R9, R11, #0x17\n"
                 "BEQ     loc_FF82D610\n"
                 "BGT     loc_FF82D460\n"
                 "LDR     R11, =0x116A\n"
                 "CMP     R5, R11\n"
                 "BEQ     loc_FF82D5FC\n"
                 "BGT     loc_FF82D424\n"
                 "SUB     R0, R5, #0x1100\n"
                 "SUB     R0, R0, #0x63\n"
                 "CMP     R0, #5\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FF82D66C\n"
"loc_FF82D40C:\n"      
                 "B       loc_FF82D634\n"
"loc_FF82D410:\n"      
                "B       loc_FF82D628\n"
"loc_FF82D414:\n"      
                "B       loc_FF82D620\n"
"loc_FF82D418:\n"      
                "B       loc_FF82D66C\n"
"loc_FF82D41C:\n"   
                 "B       loc_FF82D5BC\n"
"loc_FF82D420:\n"      
                "B       loc_FF82D5BC\n"
"loc_FF82D424:\n"       
                "SUB     R12, R5, #0x2000\n"
                "SUBS    R12, R12, #2\n"
                 "BEQ     loc_FF82D6E4\n"
                "CMP     R5, R9\n"
                "MOV     R0, R9\n"
                "BEQ     loc_FF82D6F0\n"
                 "SUB     R12, R5, #0x2000\n"
                "SUBS    R12, R12, #5\n"
                "BEQ     loc_FF82D6E4\n"
                "SUB     R12, R5, #0x2000\n"
                 "SUBS    R12, R12, #0x19\n"
                "BNE     loc_FF82D66C\n"
                "CMP     R1, #0\n"
                "BNE     loc_FF82D6D0\n"
                 "B       loc_FF82D65C\n"
"loc_FF82D460:\n"      
                "LDR     R12, =0x3110\n"
                "CMP     R5, R12\n"
                "BEQ     loc_FF82D6A8\n"
                 "BGT     loc_FF82D4A8\n"
                "SUB     R12, R5, #0x2000\n"
                "SUBS    R12, R12, #0x1D\n"
                "BEQ     loc_FF82D6E4\n"
                 "LDR     R0, =0x2027\n"
                "CMP     R5, R0\n"
                "BEQ     loc_FF82D6B0\n"
                "SUB     R12, R5, #0x3000\n"
                 "SUBS    R12, R12, #6\n"
                "BEQ     loc_FF82D6A8\n"
                "SUB     R12, R5, #0x3000\n"
                "SUBS    R12, R12, #0x10\n"
                 "BNE     loc_FF82D66C\n"
                 "BL      sub_FF893354\n"
                 "B       loc_FF82D65C\n"
"loc_FF82D4A8:\n"      
                 "SUB     R12, R5, #0x3100\n"
                 "SUBS    R12, R12, #0x11\n"
                 "BEQ     loc_FF82D6A8\n"
                 "CMP     R5, #0x3140\n"
                 "BEQ     loc_FF82D70C\n"
                 "SUB     R12, R5, #0x3200\n"
                 "SUBS    R12, R12, #1\n"
                 "BEQ     loc_FF82D66C\n"
                 "SUB     R12, R5, #0x3200\n"
                 "SUBS    R12, R12, #2\n"
                 "BNE     loc_FF82D66C\n"
                 "B       loc_FF82D6A8\n"
"loc_FF82D4D8:\n"       
                 "MOV     R4, #1\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FF874024\n"
                 "CMP     R0, #1\n"
                 "MOVEQ   R4, #2\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF8224B0\n" 
                 "CMP     R0, #0\n"
                 "STRNE   R8, [R6,#0x14]\n"
                 "BNE     loc_FF82D530\n"
                "BL      sub_FF879F0C\n"
                "BL      sub_FF877D84\n"
                "BL      sub_FF8789D8\n"
				"BL      sub_FF877670\n"	
                 "BL      sub_FF878F88\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FF82D59C\n"
                 "BL      sub_FF82CF20\n"
                "BL      sub_FF878EEC\n"
                "MOV     R1, R0\n"
                "LDR     R0, =0x1167\n"
                 "BL      sub_FF8711D8\n"
"loc_FF82D530:\n"       
                "MOV     R0, R7\n"

"locret_FF82D534:\n"   
                "LDMFD   SP!, {R3-R11,PC}\n"
"loc_FF82D59C:\n"       
                 "BL      sub_FF8268E8\n"
                 "CMP     R0, #1\n"
                 "LDRNE   R0, =0x310B\n"
                 "LDREQ   R0, =0x310C\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF8711D8\n" 
                 "BL      sub_FF8770A8_my\n"  // Continue here (possibility 1) for SDHC-boot  //<------------------------------------------
                 "B       loc_FF82D530\n"
 "loc_FF82D5BC:\n"      
                 "STR     R8, [R6,#0x10]\n"
                 "LDR     R6, =0x4508\n"
                 "LDR     R4, =0x1168\n"
                 "CMP     R1, #0\n"
                 "BEQ     loc_FF82D5E4\n"
                 "BL      sub_FF8748A0\n"
                 "B       loc_FF82D5F0\n"
 "loc_FF82D5D8:\n"      
                 "MOV     R0, R6\n"
                 "BL      sub_FF85E5B0\n"
                 "B       loc_FF82D65C\n"
 
 "loc_FF82D5E4:\n"      
                 "BL      sub_FF8781CC\n"
                 "BL      sub_FF877F94\n"
                 "BL      sub_FF826590\n"
 "loc_FF82D5F0:\n"      
                 "CMP     R5, R4\n"
                 "BEQ     loc_FF82D5D8\n"
                 "B       loc_FF82D65C\n"
 "loc_FF82D5FC:\n"       
                 "MOV     R0, #1\n"
                "BL      sub_FF8749CC\n"
                "MOV     R1, R11\n"
                "MOV     R0, R10\n"
                 "B       loc_FF82D674\n"
"loc_FF82D610:\n"   
                "CMP     R2, #1\n"
                "BNE     loc_FF82D6A8\n"
                "BL      sub_FF8748A0\n"
                 "B       loc_FF82D65C\n"
"loc_FF82D620:\n"       
                "MOV     R0, #2\n"
                "B       loc_FF82D62C\n"
 "loc_FF82D628:\n"     
                "MOV     R0, #1\n"
 "loc_FF82D62C:\n"      
                 "BL      sub_FF82DC30\n"
                "B       loc_FF82D65C\n"
"loc_FF82D634:\n"       
                "MOV     R0, #0\n"
                "B       loc_FF82D62C\n"  
 "loc_FF82D63C:\n"                       
                 "LDR     R0, [R6,#0xC]\n"
                "SUB     R12, R0, #0x8000\n"
                "SUBS    R12, R12, #2\n"
                "BEQ     loc_FF82D65C\n"
                 "LDR     R0, =0x10A5\n"
                "BL      sub_FF872EB8\n" // eventproc_export_IsControlEventActive     

                "CMP     R0, #0\n"
                "BEQ     loc_FF82D664\n"
 "loc_FF82D65C:\n"      
                 "MOV     R0, #0\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
 "loc_FF82D664:\n"       
                "CMP     R5, R9\n"
                "STREQ   R8, [R6,#0x30]\n"

 "loc_FF82D66C:\n"       
                 "MOV     R1, #0\n"
"loc_FF82D670:\n"       
                "MOV     R0, R5\n"

"loc_FF82D674:\n"       
                "BL      sub_FF875F98_My\n" // Continue here (possibility 2) for SDHC-boot //<-----------------------------

                "LDMFD   SP!, {R3-R11,PC}\n"
 "loc_FF82D67C:\n"       
                 "BL      sub_FF87C4A0\n"
                "CMP     R0, #0\n"
                "BLNE    sub_FF87B1FC\n"
                "B       loc_FF82D6A8\n"
 "loc_FF82D68C:\n"       
                 "BL      sub_FF872EB8\n" //eventproc_export_IsControlEventActive
                "CMP     R0, #0\n"
                "BNE     loc_FF82D65C\n"

"loc_FF82D698:\n"      
                "MOV     R0, R5\n"
                 "BL      sub_FF82D040\n"
                 "LDMFD   SP!, {R3-R11,PC}\n"
 "loc_FF82D6A4:\n"     
                 "BL      sub_FF82DC00\n"
 "loc_FF82D6A8:\n"      
                 "MOV     R1, R4\n"
                 "B       loc_FF82D670\n"
 "loc_FF82D6B0:\n"       
                 "MOV     R1, #0\n"
                 "BL      sub_FF875F98_My\n"  //Continue here (possibility 2) for SDHC-boot // <-------------------------------- 
                "MOV     R1, #0\n"
                "MOV     R0, R11\n"
                "BL      sub_FF875F98_My\n"  // Continue here (possibility 2) for SDHC-boot // <----------------------------------
                "MOV     R1, #0\n"
                "MOV     R0, R9\n"
                "B       loc_FF82D6DC\n"
 "loc_FF82D6D0:\n"       
                 "CMP     R2, #0\n"
                 "BNE     loc_FF82D65C\n"
 "loc_FF82D6D8:\n"      
                 "MOV     R1, #0\n"	
"loc_FF82D6DC:\n"     
                 "BL      sub_FF875F98_My\n"  //Continue here (possibility 2) for SDHC-boot  // <------------------------------------
                 "B       loc_FF82D65C\n"
 "loc_FF82D6E4:\n"      
                 "STR     R7, [R6,#0x20]\n"
                 "BL      sub_FF82D900\n"
                 "B       loc_FF82D6A8\n"
 "loc_FF82D6F0:\n"       
                 "STR     R7, [R6,#0x20]\n"
                 "BL      sub_FF82D900\n"
                 "LDR     R0, [R6,#0x10]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF82D6A8\n"
                 "BL      sub_FF8748E4\n"
                 "B       loc_FF82D65C\n"
"loc_FF82D70C:\n"       
                 "CMP     R1, #0\n"
                "BLEQ    sub_FF82D900\n"
                "B       loc_FF82D65C\n"
"loc_FF82D718:\n"      
                "LDR   R0, =0xFFFFFFFF\n" // was MOVL tryed MVN provare pure LDR
                 "B       loc_FF82D6D8\n"				 
	);
}; //#fe


// Continue here (possibility 1) for SDHC-boot  //OK
void __attribute__((naked,noinline)) sub_FF8770A8_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"				
				"BL      sub_FF82D8CC\n" 
                "MOV     R4, R0\n" 
                "BL      sub_FF8771C4\n" 
                "MOV     R0, R4\n" 
                "BL      sub_FF876F5C\n" 
                "BL      sub_FF82D8CC\n" 
                "MOV     R4, R0\n" 
                "LDR     R0, =0x60D8\n" 
				"LDR     R0, [R0]\n" 
				"TST     R0, #1\n" 
				"BEQ     loc_FF8770E4\n" 
        "loc_FF8770D8:\n" 
                "MOV     R1, R4\n" 
                "MOV     R0, #2\n" 
                "B       loc_FF87714C\n" 
         "loc_FF8770E4:\n" 
                "TST     R0, #0x2000\n" 
                "BEQ     loc_FF877100\n" 
                "TST     R0, #0x200\n" 
				"LDREQ   R1, =0x4004\n" 
				"LDRNE   R1, =0x8002\n" 
				"MOV     R0, #3\n"
				"B       loc_FF87714C\n" 
        "loc_FF877100:\n" 
                "TST     R0, #0x10\n" 
                "BNE     loc_FF8770D8\n" 
				"TST     R0, #0x40\n" 
				"BEQ     loc_FF87711C\n" 
        "loc_FF877110:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #1\n"
                "B       loc_FF87714C\n" 
        "loc_FF87711C:\n" 
                "TST     R0, #0x20\n"
                "BEQ     loc_FF877138\n" 
                "TST     R0, #0x4000\n"
                "BNE     loc_FF877138\n"
        "loc_FF87712C:\n"
                "MOV     R1, R4\n"
                "MOV     R0, #0\n"
                "B       loc_FF87714C\n" 
        "loc_FF877138:\n" 
                "LDR     R1, =0x102\n"
                "BICS    R1, R1, R0\n"
                "BNE     loc_FF877154\n" 
                "MOV     R1, R4\n"
                "MOV     R0, #6\n"
        "loc_FF87714C:\n" 
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FF876EF8_my\n"        // cont. for SDHC-boot <------------------------------------
        "loc_FF877154:\n" 
                "TST     R0, #0x100\n"
                "BNE     loc_FF8770D8\n" 
                "TST     R0, #0x4000\n" 
                "TSTEQ   R0, #0x400\n" 
				"BNE     loc_FF877110\n" 
                "TST     R0, #0x200\n"
                "TSTEQ   R0, #2\n"
                "BNE     loc_FF87712C\n" 
                "TST     R0, #0x40000\n"
                "BEQ     loc_FF8770D8\n" 
                "TST     R0, #0x200000\n"
                "MOVEQ   R1, R4\n"
                "MOVEQ   R0, #1\n"
                "BLEQ    sub_FF876EF8_my\n"        // cont. for SDHC-boot <------------------------------------
                "B       loc_FF8770D8\n" 
        );
}; //#fe
//OK
void __attribute__((naked,noinline)) sub_FF876EF8_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOVS    R4, R0\n"
                "MOV     R0, #1\n"
                "MOV     R5, R1\n"
                "BNE     loc_FF876F38\n" 
                "MOV     R1, #0\n"
                "MOV     R0, #0\n"
                "BL      sub_FF873FB4\n" 
                "BL      sub_FF82D8CC\n" 
                "SUB     R12, R0, #0x1000\n"
                "SUBS    R12, R12, #0x5B\n"
                "BNE     loc_FF876F30\n" 
        "loc_FF876F28:\n" 
                "BL      sub_FF876E4C\n" 
                "B       loc_FF876F40\n" 
        "loc_FF876F30:\n" 
                "BL      sub_FF876E8C\n" 
                "B       loc_FF876F40\n" 
        "loc_FF876F38:\n" 
                "CMP     R4, #5\n"
                "BEQ     loc_FF876F28\n" 
        "loc_FF876F40:\n" 
                "CMP     R0, #0\n"
                "LDREQ   R5, =0x1162\n"
                "MOVEQ   R4, #2\n"
                "MOV     R0, R4\n"
                "MOV     R1, R5\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FF875F98_My\n" //  Continue here (possibility 2) for SDHC-boot   <-------------------------
        );
}; //#fe


//NEW  OK
void __attribute__((naked,noinline)) sub_FF875F98_My() { //#fs 
        asm volatile (
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R1\n"
                 "MOV     R4, R0\n"
                 "BL      sub_FF878F88\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF87625C\n"
                 "MOV     R1, R8\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF874B90\n"
                 "LDR     R5, =0x6008\n"
                 "MOV     R7, #1\n"
                 "LDR     R0, [R5,#0x10]\n"
                 "MOV     R6, #0\n"
                 "CMP     R0, #0x16\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FF87625C\n"
 "loc_FF875FD8:\n"
                 "B       loc_FF876034\n"
 "loc_FF875FDC:\n"
                 "B       loc_FF87605C\n"
 "loc_FF875FE0:\n"
                 "B       loc_FF8760A0\n"
 "loc_FF875FE4:\n"  
                 "B       loc_FF87611C\n"
 "loc_FF875FE8:\n"  
                 "B       loc_FF87612C\n"
 "loc_FF875FEC:\n"  
                 "B       loc_FF87625C\n"
 "loc_FF875FF0:\n"  
                 "B       loc_FF8761A8\n"
 "loc_FF875FF4:\n"  
                 "B       loc_FF8761B8\n"
 "loc_FF875FF8:\n"  
                 "B       loc_FF876044\n"
 "loc_FF875FFC:\n"  
                 "B       loc_FF876050\n"
 "loc_FF876000:\n"
                 "B       loc_FF8761B8\n"
 "loc_FF876004:\n"  
                 "B       loc_FF876094\n"
 "loc_FF876008:\n"  
                 "B       loc_FF87625C\n"
 "loc_FF87600C:\n"
                 "B       loc_FF87625C\n"
 "loc_FF876010:\n"  
                 "B       loc_FF8760AC\n"
 "loc_FF876014:\n"  
                 "B       loc_FF8760B8\n"
 "loc_FF876018:\n"  
                 "B       loc_FF8760F0\n"
 "loc_FF87601C:\n"  
                 "B       loc_FF876068\n"
 "loc_FF876020:\n"  
                 "B       loc_FF876244\n"
 "loc_FF876024:\n"  
                 "B       loc_FF8761C4\n"
 "loc_FF876028:\n"  
                 "B       loc_FF8761F4\n"
 "loc_FF87602C:\n"  
                 "B       loc_FF8761F4\n"
 "loc_FF876030:\n"
                 "B       loc_FF876138\n"
 "loc_FF876034:\n"  
                 "MOV     R1, R8\n"
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF875648_my\n"		// uAC_Boot // divert for   <-------------------------
 "loc_FF876044:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF8769B0\n"
 "loc_FF876050:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF875B14\n"
 "loc_FF87605C:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF87522C\n"
 "loc_FF876068:\n"  
                 "SUB     R12, R4, #0x1000\n"
                 "SUBS    R12, R12, #0xA5\n"
                 "STREQ   R7, [R5,#0x88]\n"
                 "BEQ     loc_FF876254\n"
                 "SUB     R12, R4, #0x3000\n"
                 "SUBS    R12, R12, #6\n"
                 "BNE     loc_FF87625C\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF82CDA8\n"
                 "BL      sub_FF876890\n"		// uAC_InitPB
                 "B       loc_FF876254\n"
 "loc_FF876094:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF8768C8\n"
 "loc_FF8760A0:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF875404\n"
 "loc_FF8760AC:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF875CC0\n"
 "loc_FF8760B8:\n"  
                 "SUB     R12, R4, #0x3200\n"
                 "SUBS    R12, R12, #2\n"
                 "BNE     loc_FF87625C\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF874A74\n"		// uCameraConState
                 "MOV     R0, #8\n"
                 "BL      sub_FF82CD04\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, #0x19\n"
                 "BL      sub_FF83EEE0\n"
                 "BL      sub_FF8781CC\n"
                 "BL      sub_FF878018\n"
                 "BL      sub_FF8776E0\n"
                 "B       loc_FF876254\n"
 "loc_FF8760F0:\n"  
                 "SUB     R12, R4, #0x3300\n"
                 "SUBS    R12, R12, #1\n"
                 "BNE     loc_FF87625C\n"
                 "LDR     R0, =0x4010\n"
                 "STR     R6, [R5,#0x80]\n"
                 "BL      sub_FF82CD04\n"
                 "BL      sub_FF9A90CC\n"
                 "BL      sub_FF8776E0\n"
                 "MOV     R0, #4\n"
                 "BL      sub_FF874A74\n"		// uCameraConState
                 "B       loc_FF876254\n"
 "loc_FF87611C:\n"  
                 "MOV     R1, R8\n"
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF875E1C\n"
 "loc_FF87612C:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF876AF8\n"
 "loc_FF876138:\n"  
                 "LDR     R8, =0x1182\n"
                 "CMP     R4, R8\n"
                 "STREQ   R7, [R5,#0xB8]\n"
                 "BEQ     loc_FF876254\n"
                 "SUB     R12, R4, #0x1000\n"
                 "SUBS    R12, R12, #0x1AC\n"
                 "BEQ     loc_FF876190\n"
                 "SUB     R12, R4, #0x3000\n"
                 "SUBS    R12, R12, #0x224\n"
                 "BNE     loc_FF87625C\n"
                 "MOV     R0, #8\n"
                 "BL      sub_FF82CD04\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF874A74\n"		// uCameraConState
                 "STR     R6, [R5,#0xBC]\n"
                 "LDR     R0, [R5,#0xB8]\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R8\n"
                 "STRNE   R6, [R5,#0xB8]\n"
                 "BLNE    sub_FF875E1C\n"
                 "B       loc_FF876254\n"
 "loc_FF876190:\n"  
                 "LDR     R0, [R5,#0xBC]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF876254\n"
                 "BL      sub_FF9A71E4\n"
                 "STR     R7, [R5,#0xBC]\n"
                 "B       loc_FF876254\n"
 "loc_FF8761A8:\n"  
                 "MOV     R1, R8\n"
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 "B       sub_FF876BD8\n"
 "loc_FF8761B8:\n"  
                 "MOV     R0, R4\n"
                 "LDMFD   SP!, {R4-R8,LR}\n"
                 //"B       sub_FF875A0C\n"		
                 "B       sub_FF875A0C_my\n"		//---------->   movies_rec.c
 "loc_FF8761C4:\n"  
                 "LDR     R12, =0x10B0\n"
                 "CMP     R4, R12\n"
                 "BEQ     loc_FF8761F0\n"
                 "BGT     loc_FF8761FC\n"
                 "CMP     R4, #4\n"
                 "BEQ     loc_FF876224\n"
                 "SUB     R12, R4, #0x1000\n"
                 "SUBS    R12, R12, #0xAA\n"
                 "SUBNE   R12, R4, #0x1000\n"
                 "SUBNES  R12, R12, #0xAE\n"
                 "BNE     loc_FF87625C\n"
 "loc_FF8761F0:\n"  
                 "BL      sub_FF874770\n"
 "loc_FF8761F4:\n"  
                 "MOV     R0, R6\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FF8761FC:  \n"
                 "SUB     R12, R4, #0x2000\n"
                 "SUBS    R12, R12, #4\n"
                 "BEQ     loc_FF87623C\n"
                 "SUB     R12, R4, #0x5000\n"
                 "SUBS    R12, R12, #1\n"
                 "SUBNE   R12, R4, #0x5000\n"
                 "SUBNES  R12, R12, #6\n"
                 "BNE     loc_FF87625C\n"
                 "BL      sub_FF8751CC\n"
                 "B       loc_FF876254\n"
 "loc_FF876224:\n"  
                 "LDR     R0, [R5,#0x2C]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF87623C\n"
                 "BL      sub_FF87643C\n"
                 "BL      sub_FF826548\n"
                 "B       loc_FF876254\n"
 "loc_FF87623C:\n"
                 "BL      sub_FF8747AC\n"
                 "B       loc_FF876254\n"
 "loc_FF876244:\n"  
                 "SUB     R12, R4, #0x3000\n"
                 "SUBS    R12, R12, #0x130\n"
                 "BNE     loc_FF87625C\n"
                 "BL      sub_FF87486C\n"
 "loc_FF876254:\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FF87625C:\n"
                 "MOV     R0, #1\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe


//OK 
void __attribute__((naked,noinline)) sub_FF875648_my() { //#fs  uAC_Boot  
    asm volatile (
			"STMFD   SP!, {R4-R8,LR}\n"
            "LDR     R7, =0x8002\n"
            "LDR     R4, =0x6008\n"
            "CMP     R0, #3\n"
            "MOV     R6, R1\n"
            "MOV     R5, #1\n"
            "BEQ     loc_FF8757BC\n"
            "BGT     loc_FF875684\n"
            "CMP     R0, #0\n"
            "BEQ     loc_FF8756C8\n"
            "CMP     R0, #1\n"
            "BEQ     loc_FF87574C\n"
            "CMP     R0, #2\n"
            "BNE     loc_FF875844\n"
            "B       loc_FF87569C\n"
"loc_FF875684:\n"  
               "CMP     R0, #6\n" 
               "STREQ   R5, [R4,#0x28]\n" 
               "BEQ     loc_FF8757B4\n" 
               "SUB     R12, R0, #0x2000\n" 
               "SUBS    R12, R12, #4\n" 
               "BNE     loc_FF875844\n" 

"loc_FF87569C:\n"  
                "SUB     R12, R6, #0x1100\n" 
                "SUBS    R12, R12, #0x62\n" 
                "BNE     loc_FF8756B8\n" 
                "MOV     R1, R7\n" 
                "MOV     R0, #0\n" 
                "BL      sub_FF878AB0\n" 
                "STR     R5, [R4,#0x60]\n" 

"loc_FF8756B8:\n"  
                "BL      sub_FF8781CC\n" 
                "BL      sub_FF878018\n" 
                "BL      sub_FF875130\n" 
                "B       loc_FF87583C\n" 
"loc_FF8756C8:\n"  
                 "MOV     R0, #7\n"  
                 "BL      sub_FF874A74\n"  
                 "MOV     R0, R7\n"  
                 "BL      sub_FF82CD04\n"  
                 "BL      sub_FF877310\n"  // taskcreate_CommonDrivers
                 "BL      sub_FF877E68\n"  
                 "MOV     R1, R7\n"  
                 "MOV     R0, #0\n"  
                 "BL      sub_FF878AB0\n"  
                 "LDR     R1, =0xFF87587C\n"  
                 "MOV     R0, #0x20\n"  
                 "STR     R6, [R4,#0x18]\n"  
                 "BL      sub_FF86DA00\n"  
                 "LDR     R1, =0xFF875888\n" 
                 "MOV     R0, #0x20\n"  
                 "BL      sub_FF86DA00\n" 
                 "STR     R5, [R4,#0x28]\n"  
                 "BL      sub_FF82CE8C\n"  
                 "BL      sub_FF82CDD0\n"  
                 "LDR     R0, [R4,#0x1C]\n"  
                 "LDR     R1, [R4,#0x20]\n"  
                 "ORRS    R0, R0, R1\n"  
                 "BLNE    sub_FF876418\n"  
                 "LDR     R0, [R4,#0x68]\n"  
                 "CMP     R0, #0\n"  
                 "BNE     loc_FF875738\n"  
                 "BL      sub_FF82CEFC\n"  // taskcreate_StartupImage
                 "B       loc_FF875740\n"  
"loc_FF875738:\n"  
                "BL      sub_FF8262FC\n"
                "BL      sub_FF82D864\n"

"loc_FF875740:\n"  
                "BL      sub_FF8772D4_my\n" // taskcreate_InitFileModules<----------------------
                "BL      sub_FF87734C\n"
                "B       loc_FF87583C\n"
"loc_FF87574C:\n"  
                "MOV     R0, #8\n"
                "BL      sub_FF874A74\n" 
                "BL      sub_FF877310\n" 
                "BL      sub_FF877E68\n"
                "LDR     R5, =0x4004\n"
                "MOV     R0, #0\n"
                "MOV     R1, R5\n"
                "BL      sub_FF878AB0\n"
                "LDR     R1, =0xFF875898\n" 
                "MOV     R0, #0x20\n"
                "BL      sub_FF86DA00\n" 
				
                "BL      sub_FF8772D4_my\n" // taskcreate_InitFileModules  ----------------------------->
				
                "BL      sub_FF8773E0\n"
                "BL      sub_FF82D828\n"
                "MOV     R0, R5\n"
                "BL      sub_FF82CD04\n"
                "LDR     R0, [R4,#0x68]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF8757A0\n"
                "BL      sub_FF82CEFC\n" // taskcreate_StartupImage
                "B       loc_FF8757A4\n"
"loc_FF8757A0:\n"  
                "BL      sub_FF8262FC\n"

"loc_FF8757A4:\n"  
                 "BL      sub_FF87737C\n"
                 "LDR     R0, [R4,#0x30]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF87583C\n"

"loc_FF8757B4:\n"  
                "BL      sub_FF876460\n"
                "B       loc_FF87583C\n"
"loc_FF8757BC:\n"  
                 "MOV     R1, R6\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF878AB0\n"
                 "LDR     R1, =0xFF8758A4\n" 
                 "MOV     R0, #0x20\n"
                 "BL      sub_FF86DA00\n" 
                 "STR     R5, [R4,#0x68]\n"
                 "BL      sub_FF8773E0\n"
                 "BL      sub_FF82D828\n"
                 "BL      sub_FF8763F4\n"
                 "BL      sub_FF82D8C0\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R0, =0x804B\n"
                 "MOVNE   R1, #0\n"
                 "BLNE    sub_FF873C90\n" // eventproc_export_PTM_SetCurrentItem
                 "BL      sub_FF8788CC\n"
                 "MOV     R0, #0x80\n"
                 "BL      sub_FF82CD04\n"
                 "BL      sub_FF878310\n"
                 "BL      sub_FF895AD0\n" // eventproc_export_StartGUISystem
                 "BL      sub_FF957B60\n"
                 "BL      sub_FF9ABF4C\n"
                 "BL      sub_FF877B4C\n"
                 "BL      sub_FF878204\n"
                 "MOV     R0, #9\n"
                 "BL      sub_FF874A74\n" 
                 "LDR     R0, =0x300E\n"
                 "MOV     R1, R6\n"
                 "BL      sub_FF8711D8\n" 
                 "MOV     R1, #0\n"
                 "MOV     R0, #1\n"
                 "BL      sub_FF878AB0\n"

"loc_FF87583C:\n" 
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF875844:\n"  
               "MOV     R0, #1\n"
               "LDMFD   SP!, {R4-R8,PC}\n"
    );
}; //#fe

//OK
void __attribute__((naked,noinline)) sub_FF8772D4_my() { //#fs  CreateTask_InitFileModules 
        asm volatile (
                "LDR     R0, =0x60E4\n" 
                "STMFD   SP!, {R3,LR}\n"
                "LDR     R1, [R0,#4]\n"
                "CMP     R1, #0\n"
                "BNE     locret_FF87730C\n" 
                "MOV     R1, #1\n"
				"STR     R1, [R0,#4]\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
				
                "LDR     R3, =task_InitFileModules_my\n" // continue for SDHC-boot (orig: FFC5F754)-g9 = FF877284  "LDR     R3, =task_InitFileModules_my\n"
                
				"MOV     R1, #0x19\n"
                "LDR     R0, =0xFF877438\n"     // aInitfilemodule 
                "MOV     R2, #0x1000\n"
                "BL      sub_FF81BAF0\n"         // CreateTask
        "locret_FF87730C:\n" 
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

//OK
void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs   task_InitFileModules_my
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FF86FFF8\n" 
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FF8711D8\n" 
                "BL      sub_FF870024_my\n"    // continue to SDHC-hook here! was FFC5A4E8
				
                "BL      core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask
				
                "CMP     R4, #0\n"
                "MOVEQ   R0, R5\n"
                "LDMEQFD SP!, {R4-R6,LR}\n"
                "MOVEQ   R1, #0\n"
                "BEQ     sub_FF8711D8\n"        
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

//OK
void __attribute__((naked,noinline)) sub_FF870024_my() { //#fs  

	        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                
				"BL      sub_FF85235C_my\n"    // continue to SDHC-hook here! was FFC3F0CC --------------------------------------->
                
				"LDR     R4, =0x5AC4\n"	
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF870054\n" 
                "BL      sub_FF87FD60\n" 
                "BL      sub_FF90B938\n" 
                "BL      sub_FF87FD60\n" 
                "BL      sub_FF91848C\n" 
                "BL      sub_FF87FD70\n" 
                "BL      sub_FF90B9E0\n" 
        "loc_FF870054:\n" 
                "MOV     R0, #1\n"
                "STR     R0, [R4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe
//OK
void __attribute__((naked,noinline)) sub_FF85235C_my() { //#fs  

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
                "BL      sub_FF851F6C\n"        // uMounter (u=unknown, just to prevent misunderstandings)
                "MOV     R0, R6\n"
				
				"BL      sub_FF852198_my\n"    // continue to SDHC-hook here! <---------------------
                
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
}; //#fe
//OK
void __attribute__((naked,noinline)) sub_FF852198_my() { //#fs  
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
									
				"BL      sub_FF852030_my\n"        //    continue to SDHC-hook here! --------------------------------------------------->
               
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
}; //#fe

//OK
void __attribute__((naked,noinline)) sub_FF852030_my() { //#fs  ; Partition table parse takes place here. => SDHC-boot 
       asm volatile (	
	   
                "STMFD   SP!, {R4-R8,LR} \n"
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
				
                //"BLX     R12\n"       // !! Workaround !! attenzione
                //".long   0xE12FFF3C\n" 				
                "MOV     LR, PC\n"      // gcc won't compile "BLX R12" nor "BL R12".
                "MOV     PC, R12\n"     // workaround: make your own "BL" and hope we don't need the change to thumb-mode
				
                "CMP     R0, #1\n"
                "BNE     loc_FF8520C8\n"
                "MOV     R0, #3\n"
                "BL      sub_FF86C610\n"
                "B       loc_FF852094\n"
"loc_FF8520C8:\n"
                "MOV     R0, R8\n"
                "BL      sub_FF929040\n" // Add FAT32 autodetect-code after this line\n"

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
                "LDRB    R1, [R4,#0x1C9]\n"			// Continue with firmware
                "LDRB    R3, [R4,#0x1C8]\n"
                "LDRB    R12, [R4,#0x1CC]\n"
                "MOV     R1, R1,LSL#24\n"
                "ORR     R1, R1, R3,LSL#16\n"
                "LDRB    R3, [R4,#0x1C7]\n"
                "LDRB    R2, [R4,#0x1BE]\n"
                  //"LDRB    LR, [R4,#0x1FF]\n"		// replaced, see below
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
                  //"LDRB    R12, [R4,#0x1FE]\n"		// replaced, see below
				
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
                "BL      sub_FF929040\n"
                "MOV     R5, R0\n"
                "B       loc_FF852188\n"
"loc_FF852174:\n"
                "MOV     R5, #0x40\n"
                "B       loc_FF852188\n"
"loc_FF85217C:\n"
                "LDR     R1, =0x365\n"
                "LDR     R0, =0XFF852024\n"		//aMounter_c  ; "Mounter.c"
                "BL      sub_FF81BFC8\n"			//DebugAssert
"loc_FF852188:\n"
                "STR     R6, [R7,#0x44]!\n"
                "MOV     R0, #1\n"
                "STR     R5, [R7,#4]\n"
                "LDMFD   SP!, {R4-R8,PC}\n"  
        );
}; //#fe


//*********************************************

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
          "BNE     loc_FFC55EC8\n"
          "CMP     R4, #0\n"
          "LDRNE   R0, [SP,#0x10-0x10]\n"
          "STRNE   R0, [R4]\n"

     "loc_FFC55EC8:\n"
          "LDR     R0, [SP,#0x10-0x10]\n"
          "LDMFD   SP!, {R3-R5,PC}\n"
     );
   return 0;  // shut up the compiler
}

/*
 


void CreateTask_blinker() {
        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};


void __attribute__((naked,noinline)) task_blinker() {
        int ledstate;

        int counter = 0;

        long *led = (void*) 0xC022006C;   // AF led

        long *anypointer;       // multi-purpose pointer to poke around in memory
        long v1, v2, v3, v4;    // multi-purpose vars

        ledstate = 0;   // init: led off
        *led = 0x46;      // led on

        while (1) {
                counter++;

                if (ledstate == 1) {    // toggle LED
                        ledstate = 0;
                        *led = 0x44;      // LED off
                        //core_test(1);
                } else {
                        ledstate = 1;
                        *led = 0x46;      // LED on
                        //core_test(0);
                }

                if (counter == 2) {
                        //dump_chdk();
				//                      gui_init();
                        //_ExecuteEventProcedure("UIFS_WriteFirmInfoToFile");
                        //_UIFS_WriteFirmInfoToFile(0);
                }

                if (counter == 10) {
//                        draw_txt_string(2, 2, "test");
                }

                msleep(500);
        }
};
 

 //extern long _Fopen_Fut(const char *filename, const char *mode);
//extern void _Fclose_Fut(long file);
//extern long _Fwrite_Fut(const void *buf, long elsize, long count, long f);
//extern long Fread_Fut(void *buf, long elsize, long count, long f);
//extern long Fseek_Fut(long file, long offset, long whence);
//extern long _qDump(char* filename, long unused, long write_p2, long write_p3);

void dump_chdk() { //#fs
    int fd;
    long dirnum;
        
    volatile long *led = (void*) 0xC0220094;   // yellow led
    volatile long *led_blue = (void*) 0xC022006c;   // yellow led

    *led = 0x46; //on 

  //  _qDump("A/qdump", 0, (void*) 0x01900, 0xb0000);
    //_qDump("A/firmdump", 0, (void*) 0xFFC00000, 0x00400000);
    //_qDump("A/firmlower", 0, (void*) 0xff800000, 0x00400000); // identical to 0xfc000000

    //started();

	//dirnum = get_target_dir_num();
	//sprintf(fn, FN_RAWDIR, dirnum);
	//mkdir(fn);

	//sprintf(fn, FN_RAWDIR "/" "DMP_%04d.JPG", dirnum, ++ramdump_num);

    *led_blue = 0x46; //on 
    *led_blue = 0x44; //off
                msleep(500);
    *led_blue = 0x46; //on 
	fd = _Fopen_Fut("A/dump", "w");
    *led_blue = 0x44; //off
	if (fd >= 0) {
    *led_blue = 0x46; //on 
	    write(fd, (void*)0, 0x1900);
    *led_blue = 0x44; //off
	    //write(fd, (void*)0x1900, 32*1024*1024-0x1900);
            //_Fwrite_Fut((void*)0x9D000, 0x20000, 0x20000, fd);
    *led_blue = 0x46; //on 
	    _Fclose_Fut(fd);
    *led_blue = 0x44; //off
	}
    *led = 0x44; //off
    //finished();
} //#fe 

*/

//*********************************************
 
