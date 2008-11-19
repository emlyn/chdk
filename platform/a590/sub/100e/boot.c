#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void boot();

#define LED_BASE 0xC02200C0
#define DP (void*)0xC02200C4	// direct-print (blue)
#define DELAY 2500000

void boot() { //#fs
    long *canon_data_src = (void*)0xFFED0D74;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xDC48 - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xDC48; // just after data 
    long canon_bss_len = 0xA5304 - 0xDC48; 

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
    asm volatile ("B      sub_FFC001a4_my\n");
}; //#fe


// init
void __attribute__((naked,noinline)) sub_FFC001a4_my() { //#fs 

        asm volatile (
                "LDR     R0, =0xFFC0021C\n"
                "MOV     R1, #0\n"
                "LDR     R3, =0xFFC00254\n"

        "loc_FFC001B0:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001B0\n"

                "LDR     R0, =0xFFC00254\n"
                "MOV     R1, #0x4B0\n"
                "LDR     R3, =0xFFC00468\n"

        "loc_FFC001CC:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001CC\n"
                "MOV     R0, #0xD2\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "MOV     R0, #0xD3\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "LDR     R0, =0x6C4\n"
                "LDR     R2, =0xEEEEEEEE\n"
                "MOV     R3, #0x1000\n"

        "loc_FFC00200:\n"
                "CMP     R0, R3\n"
                "STRCC   R2, [R0],#4\n"
                "BCC     loc_FFC00200\n"
                "BL      sub_FFC00FA0_my\n"
				);
} //#fe

void __attribute__((naked,noinline)) sub_FFC00FA0_my() { //#fs 
        asm volatile (
              //"STR     LR, [SP,#0xFFFFFFFC]!\n"
              "STR     LR, [SP,#-4]!\n"         // inspired by original CHDK-code
              "SUB     SP, SP, #0x74\n"
              "MOV     R0, SP\n"
              "MOV     R1, #0x74\n"
              "BL      sub_FFE66B20\n"
			  
              "MOV     R0, #0x53000\n"
              "STR     R0, [SP,#0x74-0x70]\n"
        );
//              "LDR     R0, =0xE5304\n"          // 0xa5304 + 0x40000, note: 0x20000 *should* have been enough, but our code was overwritten...
                                                // ...thus we push the memory pool a little more up (0x30000 = 192k)
        asm volatile (
              "LDR     R0, =new_sa\n"
              "LDR     R0, [R0]\n"
        );
        asm volatile (
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
              //"STRD     R0, [SP,#0x74-0x54]\n"        // "strd not supported by cpu" claims gcc
              "STR      R0, [SP,#0x74-0x54]\n"          // split in two single-word STRs
              "STR      R1, [SP,#0x74-0x50]\n"

              "MOV     R0, #0x78\n"
              //"STRD     R0, [SP,#0x74-0x4C]\n"        // "strd not supported by cpu" claims gcc
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
              "STR     R0, [SP,#0x74-0x0C]\n"

              //"LDR     R1, =0xFFC04DBC\n"         // uHwSetup = 0xFFC04DBC
              "LDR     R1, =uHwSetup_my\n"         // followup to own function
              "MOV     R0, SP\n"
              "MOV     R2, #0\n"
              "BL      sub_FFC02D58\n"
              "ADD     SP, SP, #0x74\n"
              "LDR     PC, [SP],#4\n"
			  ".pool \n"
        );
}; //#fe

void __attribute__((naked,noinline)) uHwSetup_my() { //#fs 
        asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FFC0094C\n"
              "BL      sub_FFC0972C\n"          // _dmSetup 
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xffc04EB8\n"       // FFC04ED0 aDmsetup
              "BLLT    sub_FFC04E98\n"          // FFC04EB0  _err_init_task
              "BL      sub_FFC049C8\n"          // _termDriverInit
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EC0\n"       // aTermdriverinit
              "BLLT    sub_FFC04E98\n"          // FFC04EB0  _err_init_task
              "LDR     R0, =0xFFc04ED0\n"       // a_term
              "BL      sub_FFC04AB4\n"          // _termDeviceCreate
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04ED8\n"       // aTermdevicecrea
              "BLLT    sub_FFC04E98\n"          // FFC04EB0  _err_init_task
              "LDR     R0, =0xFFc04ED0\n"       // a_term
              "BL      sub_FFC03564\n"          // _stdioSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EEC\n"       // aStdiosetup
              "BLLT    sub_FFC04E98\n"          // FFC04EB0  _err_init_task
              "BL      sub_FFC092B4\n"          // _stdlibSetup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EF8\n"       // aStdlibsetup
              "BLLT    sub_FFC04E98\n"          // FFC04EB0  _err_init_task
              "BL      sub_FFC014B8\n"          // _armlib_setup
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04F04\n"       // aArmlib_setup
              "BLLT    sub_FFC04E98\n"          // FFC04EB0  _err_init_task
              "LDMFD   SP!, {R4,LR}\n"
			  //"B       _CreateTaskStartup\n"   // FFC0CD84
			  "B       CreateTask_Startup_my\n"
			  

        );
}; //#fe

void __attribute__((naked,noinline)) CreateTask_Startup_my() { //#fs 

        asm volatile (
				 "STMFD   SP!, {R3,LR}\n"
                 //"BL      j_nullsub_155\n"
				 "BL      sub_FFC19C58\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC0CDB4\n"
                 "BL      sub_FFC119E4\n"
				 "CMP     R0, #0\n"
                 "BNE     loc_FFC0CDB4\n"
                 "LDR     R1, =0xC0220000\n"
                 "MOV     R0, #0x44\n"
                 "STR     R0, [R1,#0x4C]\n"
		"loc_FFC0CDB0:\n"
                "B       loc_FFC0CDB0\n"
		"loc_FFC0CDB4:\n"
                "BL       sub_FFC119F0\n"
                "BL       sub_FFC119EC\n"
                "BL      sub_FFC17FE0\n"
                "LDR     R1, =0x2CE000\n"
                "MOV     R0, #0\n"
				
                "BL      sub_FFC18228\n"
                "BL      sub_FFC181D4\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP,#8-8]\n"
				//"STR     R3, [SP]\n"
                //"LDR     R3, =0xFFC0CD84\n" // task_Startup
				"LDR     R3, =task_Startup_my\n"
                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFFC0CDFC\n" //astartup
				"BL      sub_FFC0B8E0\n"	//createtask
				"MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
				".pool \n"
        );
}; //#fe



void __attribute__((naked,noinline)) task_Startup_my() { //#fs 
        
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC051BC\n"  // uRegClockSave
                "BL      sub_FFC12B48\n"
                "BL      sub_FFC0FE20\n"
                "BL      sub_FFC19C98\n"
                "BL      sub_FFC19E60\n"	//ADCScan
                //"BL      sub_FFC1BA84\n"  // StartDiskboot
    );
        CreateTask_spytask();
		
        asm volatile (
                "BL      sub_FFC1A014\n"
                "BL      sub_FFC19EB0\n"        
                "BL      sub_FFC17520\n"
                "BL      sub_FFC1A018\n"
				"BL      sub_FFC118FC_my\n"  // CreateTask_PhySw - checks buttons and acts accordingly
                "BL      sub_FFC14AB4_my\n"        //divert to intercept task_ShootSeqTask
				"BL      sub_FFC1A030\n"			
				//"BL      nullsub_2\n"
                "BL      sub_FFC10DD0\n"	
                "BL      sub_FFC19A20\n"
                "BL      sub_FFC1142C\n"
                "BL      sub_FFC10CD0\n"
				"BL      sub_FFC1A97C_my\n"     // divert for SDHC-bootdisk-suppor
                "BL      sub_FFC10C8C\n"
                "LDMFD   SP!, {R4,PC}\n"        // restore stack to PC instead of LR to return to caller				
				//"BL       sub_FFC05070\n"
				);
				
}; //#fe

void CreateTask_spytask() { //#fs 
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

//taskcreate_PhySw
void __attribute__((naked,noinline)) sub_FFC118FC_my() { //#fs 
asm volatile (
		"stmfd	sp!, {r3, r4, r5, lr} \n"
		"ldr	r4,  =0x1be4 \n"
		"ldr	r0, [r4, #0x10] \n"
		"cmp	r0, #0	\n" // ; 0x0
		"BNE	loc_FFC11930 \n" //
		"mov	r3, #0	\n" // ; 0x0
		"str	r3, [sp] \n"
		"ldr	r3, =mykbd_task \n" //
		"mov	r2, #0x800	\n" // ; 0x800
		"mov	r1, #0x17	\n" // ; 0x17
		"ldr	r0, =0xFFC11B24 \n" // ; (53796850)  *"PhySw"
		"BL		sub_FFC0BBB8 \n" // <KernelCreateTask -24636>
		"str	r0, [r4, #0x10] \n"
	"loc_FFC11930:\n"
		"BL	sub_FFC5BFC8 \n" // <OpLog.Create>
		"ldr	r1,  =0x0000f128 \n"
		"ldmfd	sp!, {r3, r4, r5, lr} \n"
		"mov	r0, #0	\n" // ; 0x0
		"B	sub_FFC5BE98 \n" // <OpLog.Start +300376>
	);

}; //#fe

void __attribute__((naked,noinline)) sub_FFC14AB4_my() { //#fs 
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x1C04\n"
                "MOV     R0, #0\n"
                "MOV     R1, #4\n"
                "STR     R0, [R4,#0xC]\n"
                "BL      sub_FFC0BC10\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #1\n"
                "BL      sub_FFC0BC34\n"
                "STR     R0, [R4,#8]\n"
                "BL      sub_FFC520BC\n"
                "BL      sub_FFC53334\n"
				"BL      sub_FFC510C0\n"
				"BL      sub_FFC4E03C_my\n"     // divert this for ShootSeqTask
				"BL      sub_FFC5237C\n"
	            "LDR     R0, [R4, #4]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "MOV     R1, #0x1000\n"
				"B       sub_FFC17884\n"
				);
					
}; //#fe

void __attribute__((naked,noinline)) sub_FFC4E03C_my() { //#fs 
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x5488\n"			
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC4E0A8\n"
                "MOV     R1, #1\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BC34\n"			
                "STR     R0, [R4,#0xC]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC0BC10\n"
				"STR     R0, [R4,#0x10]\n"
                "BL      sub_FFC4E33C\n"
				"BL      sub_FFC4E88C\n"   // continue here for task_ShootSeqTask (this is nonsense. We just need CaptSeqTask)
				"MOV     R0, #0\n"
                "STR     R0, [R4,#0x8]\n"
                "ADD     R0, R4, #0x14\n"
                "MOV     R1, #0\n"
                "STR     R1, [R0],#4\n"
                "STR     R1, [R0]\n"
                "BL      sub_FFC4EA2C\n"
                "BL      sub_FFC52528\n"
                "BL      sub_FFC50A6C\n"
                "BL      sub_FFC4F394_my\n"     // continue here for task_CaptSeqTask
				"BL      sub_FFC505AC\n"
				"loc_FFC4E0A8:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC4F394_my() { //#fs  // CreateTask_CaptSeqTask

      		asm volatile(
                "STMFD   SP!, {R3-R5,LR}\n"
                "LDR     R2, =0x18860\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
			"loc_FFC4F3A4:\n"
                "ADD     R3, R2, R0,LSL#4\n"
                "ADD     R0, R0, #1\n"
                "CMP     R0, #5\n"
                "STR     R1, [R3,#8]\n"
                "BCC     loc_FFC4F3A4\n"
                "BL      sub_FFD174EC\n"
                "BL      sub_FFD190C4\n"
                "MOV     R1, #5\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BBEC\n"
                "LDR     R4, =0x54C0\n"
				"LDR     R1, =0x1001FF\n"
                "STR     R0, [R4,#8]\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BC10\n"
				"STR     R0, [R4,#4]\n"
				"MOV	 R0, #0\n"
				"MOV	 R1, #1\n"
				"BL 	 sub_FFC0BC34\n"   

				"STR	 R0, [R4, #0xC]\n"
				"MOV	 R3,  #0\n"
                //"STR     R3, [SP,#0x10+var_10]\n"
                "STR     R3, [SP]\n"
                "LDR     R3, =task_CaptSeqTask_my\n"            // task_CaptSeqTask
                "LDR     R0, =0xFFC4F4CC\n"             // aCaptseqtask ; "CaptSeqTask"
                "MOV     R2, #0x1000\n"
                "MOV     R1, #0x17\n"
				"BL      sub_FFC0BBB8\n"                // uKernelMiscCreateTask o. CreateTaskStrict
				"LDMFD   SP!, {R3-R5,PC}\n"
        ".ltorg\n"
        );
}; //#fe


// -----------------
// SDHC-Boot-Support
// -----------------
// Required subs:

// uAC_Boot:                  
// CreateTask_InitFileModules: 
// task_InitFileModules:       


void __attribute__((naked,noinline)) sub_FFC1A97C_my() { //#fs  
        asm volatile (
		        "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC62B68\n"
                "BL      sub_FFC38838\n"
                "CMP     R0, #1\n"
                "BNE     loc_FFC1A99C\n"
                "BL      sub_FFC65910\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFC388C4\n"
"loc_FFC1A99C:\n"
                "BL      sub_FFC64950\n"
                "LDR     R4, =0x1D18\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "LDMNEFD SP!, {R4,PC}\n"
                "MOV     R1, #0\n"
                "LDR     R0, =sub_FFC1A54C_my\n"
                "BL      sub_FFC60FD0\n"
                "STR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC1A54C_my() { //#fs  
asm volatile (        
                "STMFD   SP!, {R3-R11,LR}\n"
                "LDR     R6, =0x1D18\n"
"                MOV     R5, R3\n"
                "LDR     R0, [R6,#0x14]\n"
"                MOV     R4, R1\n"
                "CMP     R0, #1\n"			//is the switch in shoot mode?
"                BNE     loc_FFC1A570\n"
                "BL      sub_FFC63384\n"
"                B       loc_FFC1A600\n"
"loc_FFC1A570:\n"							//we are in review mode
                "LDR     R11, =0x1167\n"
"                MOV     R7, #0\n"
                "SUB     R12, R11, #5\n"
"                CMP     R4, R12\n"
                "MOV     R9, #1\n"
"                BEQ     loc_FFC1A8A4\n"
                "BGT     loc_FFC1A6A0\n"
"                LDR     R0, =0x1061\n"
                "ORR     R12, R0, R0,ASR#11\n"
"                CMP     R4, R12\n"
                "ADD     R1, R0, #4\n"
"                BEQ     loc_FFC1A93C\n"
                "BGT     loc_FFC1A62C\n"
"                LDR     R12, =0x1056\n"
                "CMP     R4, R12\n"
"                BEQ     loc_FFC1A93C\n"
                "BGT     loc_FFC1A608\n"
"                SUB     R12, R4, #0x800\n"
                "SUBS    R12, R12, #3\n"
"                BEQ     loc_FFC1A7C0\n"
                "SUB     R12, R4, #0x800\n"
"                SUBS    R12, R12, #0x158\n"
                "BEQ     loc_FFC1A958\n"
"                SUB     R12, R4, #0x900\n"
                "SUBS    R12, R12, #0xA3\n"
"                SUBNE   R12, R4, #0x900\n"
                "SUBNES  R12, R12, #0xA5\n"
"                BNE     loc_FFC1A974\n"
                "LDR     R0, [R6,#0xC]\n"
"                SUB     R12, R0, #0x8000\n"
                "SUBS    R12, R12, #2\n"
"                BEQ     loc_FFC1A600\n"
                "LDR     R0, =0x10A5\n"
"                BL      sub_FFC61E48\n"
                "CMP     R0, #0\n"
"                BEQ     loc_FFC1A974\n"
"loc_FFC1A600:\n"						//shoot mode, return
                "MOV     R0, #0\n"
"                LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A608:\n"
                "SUB     R12, R4, #0x1000\n"
"                SUBS    R12, R12, #0x5B\n"
                "SUBNE   R12, R4, #0x1000\n"
"                SUBNES  R12, R12, #0x5E\n"
                "CMPNE   R4, R0\n"
"                SUBNE   R12, R4, #0x1000\n"
                "SUBNES  R12, R12, #0x62\n"
"                BNE     loc_FFC1A974\n"
                "B       loc_FFC1A93C\n"
"loc_FFC1A62C:\n"
                "LDR     R12, =0x10AE\n"
"                CMP     R4, R12\n"
                "BEQ     loc_FFC1A8D8\n"
"                BGT     loc_FFC1A670\n"
                "CMP     R4, R1\n"
"                BEQ     loc_FFC1A93C\n"
                "SUB     R12, R4, #0x1000\n"
"                LDR     R0, =0x10A3\n"
                "SUBS    R12, R12, #0xA9\n"
"                BEQ     loc_FFC1A8B4\n"
                "SUB     R12, R4, #0x1000\n"
"                SUBS    R12, R12, #0xAA\n"
                "BEQ     loc_FFC1A8CC\n"
"                SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0xAD\n"
"                BNE     loc_FFC1A974\n"
                "B       loc_FFC1A8C0\n"
"loc_FFC1A670:\n"
                "SUB     R12, R4, #0x1000\n"
"                SUBS    R12, R12, #0xAF\n"
                "BEQ     loc_FFC1A8C0\n"
"                SUB     R12, R4, #0x1000\n"
                "SUBS    R12, R12, #0xB0\n"
"                BEQ     loc_FFC1A8D8\n"
                "SUB     R12, R4, #0x1000\n"
"                SUBS    R12, R12, #0xB2\n"
                "BNE     loc_FFC1A974\n"
"                LDR     R0, =0x1008\n"
                "MOV     R1, R5\n"
"                B       loc_FFC1A89C\n"
"loc_FFC1A6A0:\n"
                "LDR     R10, =0x201B\n"
"                LDR     R0, =0x1D18\n"
                "CMP     R4, R10\n"
"                LDR     R2, [R0,#0x10]!\n"
                "LDR     R1, [R0,#0x10]\n"
"                SUB     R8, R10, #0x17\n"
                "BEQ     loc_FFC1A878\n"
"                BGT     loc_FFC1A75C\n"
                "LDR     R10, =0x116A\n"
"                CMP     R4, R10\n"
                "BEQ     loc_FFC1A864\n"
"                BGT     loc_FFC1A718\n"
                "SUB     R12, R4, #0x1100\n"
"                SUBS    R12, R12, #0x63\n"
                "MOVEQ   R1, #0\n"
"                MOVEQ   R0, #0x82\n"
                "BEQ     loc_FFC1A890\n"
"                SUB     R12, R4, #0x1100\n"
                "SUBS    R12, R12, #0x65\n"
"                BEQ     loc_FFC1A888\n"
                "LDR     R5, =0x1168\n"
"                CMP     R4, R11\n"
                "CMPNE   R4, R5\n"
"                BNE     loc_FFC1A974\n"
                "STR     R9, [R6,#0x10]\n"
"                LDR     R6, =0x4508\n"
                "CMP     R1, #0\n"
"                BEQ     loc_FFC1A84C\n"
                "BL      sub_FFC633B8\n"
"                B       loc_FFC1A858\n"
"loc_FFC1A718:\n"
                "SUB     R12, R4, #0x2000\n"
"                SUBS    R12, R12, #2\n"
                "BEQ     loc_FFC1A908\n"
"                CMP     R4, R8\n"
                "MOV     R0, R8\n"
"                BEQ     loc_FFC1A914\n"
                "SUB     R12, R4, #0x2000\n"
"                SUBS    R12, R12, #5\n"
                "BEQ     loc_FFC1A908\n"
"                SUB     R12, R4, #0x2000\n"
                "SUBS    R12, R12, #0x19\n"
"                BNE     loc_FFC1A974\n"
                "CMP     R1, #0\n"
"                BEQ     loc_FFC1A600\n"
                "CMP     R2, #0\n"
"                BNE     loc_FFC1A600\n"
                "B       loc_FFC1A950\n"
"loc_FFC1A75C:\n"
                "LDR     R12, =0x3111\n"
"                CMP     R4, R12\n"
                "BEQ     loc_FFC1A8DC\n"
"                BGT     loc_FFC1A79C\n"
                "SUB     R12, R4, #0x2000\n"
"                SUBS    R12, R12, #0x1D\n"
                "BEQ     loc_FFC1A908\n"
"                LDR     R0, =0x2027\n"
                "CMP     R4, R0\n"
"                BEQ     loc_FFC1A8E4\n"
                "SUB     R12, R4, #0x3000\n"
"                SUBS    R12, R12, #6\n"
                "SUBNE   R12, R4, #0x3000\n"
"                SUBNES  R12, R12, #0x110\n"
                "BNE     loc_FFC1A974\n"
"                B       loc_FFC1A8DC\n"
"loc_FFC1A79C:\n"
                "CMP     R4, #0x3140\n"
"                BEQ     loc_FFC1A930\n"
                "SUB     R12, R4, #0x3200\n"
"                SUBS    R12, R12, #1\n"
                "BEQ     loc_FFC1A974\n"
"                SUB     R12, R4, #0x3200\n"
                "SUBS    R12, R12, #2\n"
"                BNE     loc_FFC1A974\n"
                "B       loc_FFC1A8DC\n"
"loc_FFC1A7C0:\n"
                "MOV     R4, #1\n"
"                MOV     R0, #2\n"
                "BL      sub_FFC62BFC\n"
"                CMP     R0, #1\n"
                "MOVEQ   R4, #2\n"
"                MOV     R0, R4\n"
                "BL      sub_FFC11054\n"
"                CMP     R0, #0\n"
                "STRNE   R9, [R6,#0x14]\n"
"                BNE     loc_FFC1A818\n"
                "BL      sub_FFC681A0\n"
"                BL      sub_FFC6622C\n"
                "BL      sub_FFC66D30\n"
"                BL      sub_FFC65B80\n"
                "BL      sub_FFC67378\n"
"                CMP     R0, #0\n"
                "BEQ     loc_FFC1A820\n"
"                BL      sub_FFC1A270\n"
                "BL      sub_FFC672DC\n"
"                MOV     R1, R0\n"
                "MOV     R0, R11\n"
"                BL      sub_FFC617D8\n"
"loc_FFC1A818:\n"
                "MOV     R0, R7\n"
"                LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A820:\n"
                "BL      sub_FFC15114\n"
"                CMP     R0, #1\n"
                "LDRNE   R0, =0x310B\n"
"                LDREQ   R0, =0x310C\n"
                "MOV     R1, #0\n"
"                BL      sub_FFC617D8\n"
                "BL      sub_FFC654D8_my\n" //this first branch works       // Continue here (possibility 1) for SDHC-boot
"                B       loc_FFC1A818\n"
"loc_FFC1A840:\n"
                "MOV     R0, R6\n"
"                BL      sub_FFC4C8E4\n"
                "B       loc_FFC1A600\n"
"loc_FFC1A84C:\n"
                "BL      sub_FFC664A4\n"
"                BL      sub_FFC66408\n"
                "BL      sub_FFC14DC0\n"
"loc_FFC1A858:\n"
                "CMP     R4, R5\n"
"                BNE     loc_FFC1A600\n"
                "B       loc_FFC1A840\n"
"loc_FFC1A864:\n"
                "MOV     R0, #1\n"
"                BL      sub_FFC634E4\n"
                "LDR     R0, =0x1005\n"
"                MOV     R1, R10\n"
                "B       loc_FFC1A89C\n"
"loc_FFC1A878:\n"
                "CMP     R2, #1\n"
"                BNE     loc_FFC1A8DC\n"
                "BL      sub_FFC633B8\n"
"                B       loc_FFC1A600\n"
"loc_FFC1A888:\n"
                "MOV     R1, #0\n"
"                MOV     R0, #0x83\n"
"loc_FFC1A890:\n"
                "BL      sub_FFC66E08\n"
"                B       loc_FFC1A600\n"
"loc_FFC1A898:\n"
				"MOV     R0, R4\n"
"loc_FFC1A89C:\n"
                //"BL      sub_FFC64678_my\n"
				"BL      sub_FFC64678\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A8A4:\n"
                "BL      sub_FFC6A108\n"
"                CMP     R0, #0\n"
                "BLNE    sub_FFC68FF4\n"
"                B       loc_FFC1A8DC\n"
"loc_FFC1A8B4:\n"
                "BL      sub_FFC61E48\n"
"                CMP     R0, #0\n"
                "BNE     loc_FFC1A600\n"
"loc_FFC1A8C0:\n"
             "\n"
                "MOV     R0, R4\n"
"                BL      sub_FFC1A33C\n"
                "LDMFD   SP!, {R3-R11,PC}\n"
"loc_FFC1A8CC:\n"
                "BL      sub_FFC61E48\n"
"                CMP     R0, #0\n"
                "BNE     loc_FFC1A600\n"
"loc_FFC1A8D8:\n"
				"BL      sub_FFC1AD78\n"
"loc_FFC1A8DC:\n"
                "MOV     R1, R5\n"
"                B       loc_FFC1A898\n"
"loc_FFC1A8E4:\n"
                "MOV     R1, #0\n"
               "BL      sub_FFC64678_my\n"
//"                BL      sub_FFC64678\n"
                "MOV     R1, #0\n"
"                MOV     R0, R10\n"
                "BL      sub_FFC64678_my\n"
//"                BL      sub_FFC64678\n"
"                MOV     R1, #0\n"
                "MOV     R0, R8\n"
"loc_FFC1A900:\n"
               "BL      sub_FFC64678_my\n"
//"                BL      sub_FFC64678\n"
"                B       loc_FFC1A600\n"
"loc_FFC1A908:\n"
                "STR     R7, [R6,#0x20]\n"
"                BL      sub_FFC1AB40\n"
                "B       loc_FFC1A8DC\n"
"loc_FFC1A914:\n"
                "STR     R7, [R6,#0x20]\n"
"                BL      sub_FFC1AB40\n"
                "LDR     R0, [R6,#0x10]\n"
"                CMP     R0, #1\n"
                "BNE     loc_FFC1A8DC\n"
"                BL      sub_FFC633FC\n"
                "B       loc_FFC1A600\n"
"loc_FFC1A930:\n"
                "CMP     R1, #0\n"
"                BLEQ    sub_FFC1AB40\n"
                "B       loc_FFC1A600\n"
"loc_FFC1A93C:\n"
                "CMP     R4, R0\n"
"                BEQ     loc_FFC1A950\n"
                "CMP     R4, R1\n"
"                MVNNE  R0, #0\n"
                "MOVEQ   R0, R1\n"
"loc_FFC1A950:\n"
                "MOV     R1, #0\n"
"                B       loc_FFC1A900\n"
"loc_FFC1A958:\n"
                "TST     R5, #0x80000000\n"
"                MOVNE   R0, #1\n"
                "LDMNEFD SP!, {R3-R11,PC}\n"
"                BL      sub_FFC6B408\n"
                "CMP     R0, #0\n"
"                BLEQ    sub_FFC173F4\n"
                "B       loc_FFC1A600\n"
"loc_FFC1A974:\n" 
   "MOV     R1, #0\n"
                "B       loc_FFC1A898\n"
				);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC654D8_my() { //#fs  
        asm volatile (
		 "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC1AAF4\n"
"                CMP     R0, #0\n"
                "LDRNE   R0, =0x1061\n"
"                BNE     loc_FFC65500\n"
                "BL      sub_FFC1AADC\n"
"                CMP     R0, #0\n"
                "LDRNE   R0, =0x105B\n"
"                BNE     loc_FFC65500\n"
                "BL      sub_FFC1AB0C\n"
"loc_FFC65500:\n"
				"MOV     R4, R0\n"
"                BL      sub_FFC65668\n"
                "MOV     R0, R4\n"
"                BL      sub_FFC65708\n"
                "BL      sub_FFC1AB0C\n"
"                MOV     R4, R0\n"
                "LDR     R0, =0x5A14\n"
"                LDR     R0, [R0]\n"
                "TST     R0, #1\n"
"                TSTEQ   R0, #0x10\n"
                "BEQ     loc_FFC65538\n"
"loc_FFC6552C:\n"
   "MOV     R1, R4\n"
                "MOV     R0, #2\n"
"                B       loc_FFC6557C\n"
"loc_FFC65538:\n"
                "TST     R0, #0x40\n"
"                BEQ     loc_FFC6554C\n"
"loc_FFC65540:\n"
                "MOV     R1, R4\n"
"                MOV     R0, #1\n"
                "B       loc_FFC6557C\n"
"loc_FFC6554C:\n"
                "TST     R0, #0x20\n"
"                BEQ     loc_FFC65568\n"
                "TST     R0, #0x4000\n"
"                BNE     loc_FFC65568\n"
"loc_FFC6555C:\n"
                "MOV     R1, R4\n"
"                MOV     R0, #0\n"
                "B       loc_FFC6557C\n"
"loc_FFC65568:\n"
                "LDR     R1, =0x102\n"
"                BICS    R1, R1, R0\n"
                "BNE     loc_FFC65584\n"
"                MOV     R1, R4\n"
                "MOV     R0, #6\n"
"loc_FFC6557C:\n"
"				LDMFD   SP!, {R4,LR}\n"
"                B       sub_FFC65474_my\n"
"loc_FFC65584:\n"
"                TST     R0, #0x100\n"
"                BNE     loc_FFC6552C\n"
"                TST     R0, #0x400\n"
"                BNE     loc_FFC65540\n"
"                TST     R0, #0x200\n"
"                TSTEQ   R0, #2\n"
"                BNE     loc_FFC6555C\n"
"                TST     R0, #0x40000\n"
"                BEQ     loc_FFC6552C\n"
"                TST     R0, #0x200000\n"
"                MOVEQ   R1, R4\n"
"                MOVEQ   R0, #1\n"
"                BLEQ    sub_FFC65474_my\n"
"                B       loc_FFC6552C\n"
		);
};
void __attribute__((naked,noinline)) sub_FFC65474_my() { //#fs  
        asm volatile (
		 "STMFD   SP!, {R4-R6,LR}\n"
                "MOVS    R4, R0\n"
"                MOV     R0, #1\n"
                "MOV     R5, R1\n"
"                BNE     loc_FFC654B4\n"
                "MOV     R1, #0\n"
"                MOV     R0, #0\n"
                "BL      sub_FFC62B8C\n"
"                BL      sub_FFC1AB0C\n"
                "SUB     R12, R0, #0x1000\n"
"                SUBS    R12, R12, #0x5B\n"
                "BNE     loc_FFC654AC\n"
"loc_FFC654A4:\n"
                "BL      sub_FFC653A8\n"
"                B       loc_FFC654BC\n"
"loc_FFC654AC:\n"
                "BL      sub_FFC65408\n"
"                B       loc_FFC654BC\n"
"loc_FFC654B4:\n"
                "CMP     R4, #5\n"
"                BEQ     loc_FFC654A4\n"
"loc_FFC654BC:\n"
                "CMP     R0, #0\n"
"                LDREQ   R5, =0x1162\n"
                "MOVEQ   R4, #2\n"
"                MOV     R0, R4\n"
                "MOV     R1, R5\n"
"                LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FFC64678_my\n"
			);
};//#fe

void __attribute__((naked,noinline)) sub_FFC64678_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R7, R1\n"
"                MOV     R6, R0\n"
                "BL      sub_FFC67378\n"
"                CMP     R0, #0\n"
                "BNE     loc_FFC64948\n"
"                MOV     R1, R7\n"
                "MOV     R0, R6\n"
"                BL      sub_FFC636BC\n"
                "LDR     R4, =0x5958\n"
"                MOV     R5, #0\n"
                "LDR     R0, [R4,#0x10]\n"
"                CMP     R0, #0x16\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
"                B       loc_FFC64948\n"
"loc_FFC646B4:\n"
                "B       loc_FFC64710\n"
"loc_FFC646B8:\n"
                "B       loc_FFC6472C\n"
"loc_FFC646BC:\n"
                "B       loc_FFC64760\n"
"loc_FFC646C0:\n"
                "B       loc_FFC64810\n"
"loc_FFC646C4:\n"
                "B       loc_FFC64820\n"
"loc_FFC646C8:\n"
                "B       loc_FFC64948\n"
"loc_FFC646CC:\n"
                "B       loc_FFC64948\n"
"loc_FFC646D0:\n"
                "B       loc_FFC648A4\n"
"loc_FFC646D4:\n"
                "B       loc_FFC64720\n"
"loc_FFC646D8:\n"
                "B       loc_FFC64948\n"
"loc_FFC646DC:\n"
                "B       loc_FFC648A4\n"
"loc_FFC646E0:\n"
                "B       loc_FFC64754\n"
"loc_FFC646E4:\n"
                "B       loc_FFC64948\n"
"loc_FFC646E8:\n"
                "B       loc_FFC64948\n"
"loc_FFC646EC:\n"
                "B       loc_FFC6476C\n"
"loc_FFC646F0:\n"
                "B       loc_FFC64778\n"
"loc_FFC646F4:\n"
                "B       loc_FFC647E8\n"
"loc_FFC646F8:\n"
                "B       loc_FFC64738\n"
"loc_FFC646FC:\n"
                "B       loc_FFC64930\n"
"loc_FFC64700:\n"
                "B       loc_FFC648B0\n"
"loc_FFC64704:\n"
                "B       loc_FFC648E0\n"
"loc_FFC64708:\n"
                "B       loc_FFC648E0\n"
"loc_FFC6470C:\n"
                "B       loc_FFC6482C\n"
"loc_FFC64710:\n"
                "MOV     R1, R7\n"
"                MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
"                B       sub_FFC64040_my\n" 	//----------------->
"loc_FFC64720:\n"
                "MOV     R0, R6\n"
"                LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC65074\n"
"loc_FFC6472C:\n"
                "MOV     R0, R6\n"
"                LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC63CE0\n"
"loc_FFC64738:\n"
                "SUB     R12, R6, #0x3000\n"
"                SUBS    R12, R12, #6\n"
                "BNE     loc_FFC64948\n"
"                MOV     R0, #0\n"
                "BL      sub_FFC1A108\n"
"                BL      sub_FFC64F70\n"
                "B       loc_FFC64940\n"
"loc_FFC64754:\n"
                "MOV     R0, R6\n"
"                LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC64FA8\n"
"loc_FFC64760:\n"
                "MOV     R0, R6\n"
"                LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC63E70\n"
"loc_FFC6476C:\n"
                "MOV     R0, R6\n"
"                LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC64418\n"
"loc_FFC64778:\n"
                "SUB     R12, R6, #0x3200\n"
"                SUBS    R12, R12, #2\n"
                "BNE     loc_FFC64948\n"
"                MOV     R0, #3\n"
                "BL      sub_FFC635C8\n"
"                MOV     R0, #8\n"
                "BL      sub_FFC1A068\n"
"                MOV     R1, #0\n"
                "MOV     R0, #0x19\n"
"                BL      sub_FFC2B7A0\n"
                "BL      sub_FFC664A4\n"
"                BL      sub_FFC6673C\n"
                "BL      sub_FFC65BF0\n"
"                B       loc_FFC64940\n"
"loc_FFC647E8:\n"
                "SUB     R12, R6, #0x3300\n"
"                SUBS    R12, R12, #1\n"
                "BNE     loc_FFC64948\n"
"                LDR     R0, =0x4010\n"
                "BL      sub_FFC1A068\n"
"                BL      sub_FFD6E344\n"
                "BL      sub_FFC65BF0\n"
"                MOV     R0, #4\n"
                "BL      sub_FFC635C8\n"
"                B       loc_FFC64940\n"
"loc_FFC64810:\n"
                "MOV     R1, R7\n"
"                MOV     R0, R6\n"
                "LDMFD   SP!, {R4-R8,LR}\n"
"                B       sub_FFC64574\n"
"loc_FFC64820:\n"
                "MOV     R0, R6\n"
"                LDMFD   SP!, {R4-R8,LR}\n"
                "B       sub_FFC651B8\n"
"loc_FFC6482C:\n"
                "LDR     R7, =0x1182\n"
"                MOV     R0, R6\n"
                "CMP     R0, R7\n"
"                MOV     R6, #1\n"
                "STREQ   R6, [R4,#0xA8]\n"
"                BEQ     loc_FFC64940\n"
                "SUB     R12, R0, #0x1000\n"
"                SUBS    R12, R12, #0x1AC\n"
                "BEQ     loc_FFC6488C\n"
"                SUB     R12, R0, #0x3000\n"
                "SUBS    R12, R12, #0x224\n"
"                BNE     loc_FFC64948\n"
                "MOV     R0, #8\n"
"                BL      sub_FFC1A068\n"
                "MOV     R0, #3\n"
"                BL      sub_FFC635C8\n"
                "STR     R5, [R4,#0xAC]\n"
"                LDR     R0, [R4,#0xA8]\n"
                "CMP     R0, #0\n"
"                MOVNE   R1, #0\n"
                "MOVNE   R0, R7\n"
"                STRNE   R5, [R4,#0xA8]\n"
                "BLNE    sub_FFC64574\n"
"                B       loc_FFC64940\n"
"loc_FFC6488C:\n"
                "LDR     R0, [R4,#0xAC]\n"
"                CMP     R0, #0\n"
                "BNE     loc_FFC64940\n"
"                BL      sub_FFD6C260\n"
                "STR     R6, [R4,#0xAC]\n"
"                B       loc_FFC64940\n"
"loc_FFC648A4:\n"
                "MOV     R0, R6\n"
"                LDMFD   SP!, {R4-R8,LR}\n"
				"BL      sub_FFC64338\n"  // branch for movie support
"loc_FFC648B0:\n"
                "LDR     R12, =0x10B0\n"
"                CMP     R6, R12\n"
                "BEQ     loc_FFC648DC\n"
"                BGT     loc_FFC648E8\n"
                "CMP     R6, #4\n"
"                BEQ     loc_FFC64910\n"
                "SUB     R12, R6, #0x1000\n"
"                SUBS    R12, R12, #0xAA\n"
                "SUBNE   R12, R6, #0x1000\n"
"                SUBNES  R12, R12, #0xAE\n"
                "BNE     loc_FFC64948\n"
"loc_FFC648DC:\n"
                "BL      sub_FFC632A0\n"
"loc_FFC648E0:\n"
                "MOV     R0, R5\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC648E8:\n"
                "SUB     R12, R6, #0x2000\n"
"                SUBS    R12, R12, #4\n"
                "BEQ     loc_FFC64928\n"
"                SUB     R12, R6, #0x5000\n"
                "SUBS    R12, R12, #1\n"
"                SUBNE   R12, R6, #0x5000\n"
                "SUBNES  R12, R12, #6\n"
"                BNE     loc_FFC64948\n"
                "BL      sub_FFC63C4C\n"
"                B       loc_FFC64940\n"
"loc_FFC64910:\n"
                "LDR     R0, [R4,#0x2C]\n"
"                CMP     R0, #0\n"
                "BNE     loc_FFC64928\n"
"                BL      sub_FFC64B04\n"
                "BL      sub_FFC14D78\n"
"                B       loc_FFC64940\n"
"loc_FFC64928:\n"
                "BL      sub_FFC632DC\n"
"                B       loc_FFC64940\n"
"loc_FFC64930:\n"
                "SUB     R12, R6, #0x3000\n"
"                SUBS    R12, R12, #0x130\n"
                "BNE     loc_FFC64948\n"
"                BL      sub_FFC63384\n"
"loc_FFC64940:\n"
                "MOV     R0, #0\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC64948:\n"
                "MOV     R0, #1\n"
"                LDMFD   SP!, {R4-R8,PC}\n"

        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC64040_my() { //#fs  uAC_Boot
        asm volatile (

		        "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R7, =0x8002\n"
"                LDR     R4, =0x5958\n"
"                CMP     R0, #2\n"
"                MOV     R6, R1\n"
"                MOV     R5, #1\n"
"                BEQ     loc_FFC640CC\n"
"                BGT     loc_FFC640B4\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FFC640F8\n"
"                CMP     R0, #1\n"
"                BNE     loc_FFC64190\n"
"                MOV     R0, #8\n"
"                BL      sub_FFC635C8\n"
"                BL      sub_FFC65840\n"
"                BL      sub_FFC6630C\n"
"                LDR     R1, =0xFFC642F0\n"
"                MOV     R0, #0x20\n"
"                BL      sub_FFC5AE84\n"
"                BL      sub_FFC65804_my\n"   //  ---------> taskcreate_initfilemodules
"                BL      sub_FFC65910\n"
"                BL      sub_FFC1AA6C\n"
"                LDR     R0, =0x4004\n"
"                BL      sub_FFC1A068\n"
"                LDR     R0, [R4,#0x68]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC64170\n"
"                BL      sub_FFC1A24C\n"
"                B       loc_FFC64174\n"
"loc_FFC640B4:\n"
"                CMP     R0, #6\n"
"                STREQ   R5, [R4,#0x28]\n"
"                BEQ     loc_FFC64184\n"
"                SUB     R12, R0, #0x2000\n"
"                SUBS    R12, R12, #4\n"
"                BNE     loc_FFC64190\n"
"loc_FFC640CC:\n"
"                SUB     R12, R6, #0x1100\n"
"                SUBS    R12, R12, #0x62\n"
"                BNE     loc_FFC640E8\n"
"                MOV     R1, R7\n"
"                MOV     R0, #0\n"
"                BL      sub_FFC66E08\n"
"                STR     R5, [R4,#0x60]\n"
"loc_FFC640E8:\n"
"                BL      sub_FFC664A4\n"
"                BL      sub_FFC6673C\n"
"                BL      sub_FFC63BEC\n"
"                B       loc_FFC64188\n"
"loc_FFC640F8:\n"
"                MOV     R0, #7\n"
"                BL      sub_FFC635C8\n"
"                MOV     R0, R7\n"
"                BL      sub_FFC1A068\n"
"                BL      sub_FFC65844\n" //common drivers
"                BL      sub_FFC6630C\n"
"                LDR     R1, =0xFFC64300\n"
"                MOV     R0, #0x20\n"
"                STR     R6, [R4,#0x18]\n"
"                BL      sub_FFC5AE84\n"
"                LDR     R1, =0xFFC6430C\n"
"                MOV     R0, #0x20\n"
"                BL      sub_FFC5AE84\n"
"                STR     R5, [R4,#0x28]\n"
"                BL      sub_FFC1A1DC\n"
"                BL      sub_FFC1A130\n"
"                LDR     R0, [R4,#0x1C]\n"
"                LDR     R1, [R4,#0x20]\n"
"                ORRS    R0, R0, R1\n"
"                BLNE    sub_FFC64AE0\n"
"                LDR     R0, [R4,#0x68]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC6415C\n"
"                BL      sub_FFC1A24C\n" //taskcreate_startupimage
"                B       loc_FFC64164\n"
"loc_FFC6415C:\n"
"                BL      sub_FFC14B18\n"
"                BL      sub_FFC1AAA4\n"
"loc_FFC64164:\n"
"               BL      sub_FFC65804_my\n" //taskcreate_initfilemodules
"                BL      sub_FFC6587C\n"
"                B       loc_FFC64188\n"
"loc_FFC64170:\n"
"                BL      sub_FFC14B18\n"
"loc_FFC64174:\n"
"                BL      sub_FFC658AC\n"
"                LDR     R0, [R4,#0x30]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FFC64188\n"
"loc_FFC64184:\n"
"                BL      sub_FFC64B28\n"
"loc_FFC64188:\n"
"                MOV     R0, #0\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC64190:\n"
"                MOV     R0, #1\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
	);
};//#fe
		

void __attribute__((naked,noinline)) sub_FFC65804_my() { //#fs  CreateTask_InitFileModules
        asm volatile (
                "LDR     R0, =0x5A20\n"
                "STMFD   SP!, {R3,LR}\n"
                "LDR     R1, [R0,#4]\n"
                "CMP     R1, #0\n"
                "BNE     locret_FFC6583C\n"
                "MOV     R1, #1\n"
                "STR     R1, [R0,#4]\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
                "LDR     R3, =task_InitFileModules_my\n"        // continue for SDHC-boot (orig: FFC5F754)
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFFC65968\n"     // aInitfilemodule ; "InitFileModules"
                "MOV     R2, #0x1000\n"
                "BL      sub_FFC0B8E0\n"         // CreateTask, 0xFFC0BBC0
        "locret_FFC6583C:\n"
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FFC5E340\n"
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FFC617D8\n"    
				"BL      sub_FFC5E36C_my\n"    // continue to SDHC-hook here!
                "BL      core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask
                "CMP     R4, #0\n"
                "MOVEQ   R0, R5\n"
                "LDMEQFD SP!, {R4-R6,LR}\n"
                "MOVEQ   R1, #0\n"
                "BEQ     sub_FFC617D8\n"        // cameralog "LogicalEvent...", it's save to run this after spytask has started
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5E36C_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"    
				"BL      sub_FFC412FC_my\n"    // continue to SDHC-hook here!
                "LDR     R4, =0x57A0\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC5E39C\n"
                "BL      sub_FFC6C348\n"
                "BL      sub_FFCE4D14\n"
                "BL      sub_FFC6C348\n"
                "BL      sub_FFC3ECEC\n"
                "BL      sub_FFC6C358\n"
                "BL      sub_FFCE4DE0\n"
"loc_FFC5E39C:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC412FC_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOV     R6, #0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC40DBC\n"
                "LDR     R4, =0x103AC\n"
                "MOV     R5, #0\n"
                "LDR     R0, [R4,#0x38]\n"
                "BL      sub_FFC417F0\n"
                "CMP     R0, #0\n"
                "LDREQ   R0, =0x29E4\n"
                "STREQ   R5, [R0,#0x10]\n"
                "STREQ   R5, [R0,#0x14]\n"
                "STREQ   R5, [R0,#0x18]\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC40DFC\n"        // uMounter (u=unknown, just to prevent misunderstandings)
                "MOV     R0, R6\n"
                "BL      sub_FFC41138_my\n"    // continue to SDHC-hook here!
                "MOV     R5, R0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC411A4\n"
                "LDR     R1, [R4,#0x3C]\n"
                "AND     R2, R5, R0\n"
                "CMP     R1, #0\n"
                "MOV     R0, #0\n"
                "MOVEQ   R0, #0x80000001\n"
                "BEQ     loc_FFC41390\n"
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
        "loc_FFC41390:\n"
                "STR     R0, [R4,#0x40]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC41138_my() { //#fs  
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R5, =0x29E4\n"
                "MOV     R6, R0\n"
                "LDR     R0, [R5,#0x14]\n"
                "CMP     R0, #0\n"
                "MOVNE   R0, #1\n"
                "LDMNEFD SP!, {R4-R6,PC}\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R6\n"
                "LDR     R0, =0x103AC\n"
                "ADD     R4, R0, R1,LSL#2\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC40EC8_my\n"        //    continue to SDHC-hook here!
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC41030\n"
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC409C4\n"
                "CMP     R0, #0\n"
                "MOVNE   R1, #1\n"
                "STRNE   R1, [R5,#0x14]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC40EC8_my() { //#fs  ; Partition table parse takes place here. => SDHC-boot
        asm volatile (
                "STMFD   SP!, {R4-R8,LR} \n"
                "MOV     R8, R0\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R1\n"
                "LDR     R0, =0x103AC\n"
                "MOV     R6, #0\n"
                "ADD     R7, R0, R1,LSL#2\n"
                "LDR     R0, [R7,#0x3C]\n"
                "MOV     R5, #0\n"
                "CMP     R0, #6\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
				"B       loc_FFC41014\n"
"loc_FFC40EF8:\n"
                "B       loc_FFC40F2C\n"
"loc_FFC40EFC:\n"
                "B       loc_FFC40F14\n"
"loc_FFC40F00:\n"
                "B       loc_FFC40F14\n"
"loc_FFC40F04:\n"
                "B       loc_FFC40F14\n"
"loc_FFC40F08:\n"
                "B       loc_FFC40F14\n"
"loc_FFC40F0C:\n"
                "B       loc_FFC4100C\n"
"loc_FFC40F10:\n"
                "B       loc_FFC40F14\n"
"loc_FFC40F14:\n"
                "MOV     R2, #0\n"
                "MOV     R1, #0x200\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC584EC\n"
                "MOVS    R4, R0\n"
                "BNE     loc_FFC40F34\n"
"loc_FFC40F2C:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC40F34:\n"
                "LDR     R12, [R7,#0x4C]\n"
                "MOV     R3, R4\n"
                "MOV     R2, #1\n"
                "MOV     R1, #0\n"
                "MOV     R0, R8\n"
				"MOV     LR, PC\n"      // gcc won't compile "BLX R12" nor "BL R12".
                "MOV     PC, R12\n"     // workaround: make your own "BL" and hope we don't need the change to thumb-mode
                "CMP     R0, #1\n"
                "BNE     loc_FFC40F60\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC5862C\n"
                "B       loc_FFC40F2C\n"
"loc_FFC40F60:\n"
                "MOV     R0, R8\n"
                "BL      sub_FFD018E4\n" //Dataghost code follows
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
				
                "LDRB    R12, [LR,#0x1FE]\n"            // New! First MBR signature byte (0x55)
                "LDRB    LR, [LR,#0x1FF]\n"             //      Last MBR signature byte (0xAA)

                "MOV     R4, #0\n"
                "BNE     loc_FFC40FE8\n"
                "CMP     R0, R1\n"
                "BCC     loc_FFC40FE8\n"
                "ADD     R2, R1, R3\n"
                "CMP     R2, R0\n"
                "CMPLS   R12, #0x55\n"
                "CMPEQ   LR, #0xAA\n"
                "MOVEQ   R6, R1\n"
                "MOVEQ   R5, R3\n"
                "MOVEQ   R4, #1\n"
"loc_FFC40FE8:\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC5862C\n"
                "CMP     R4, #0\n"
                "BNE     loc_FFC41020\n"
                "MOV     R6, #0\n"
                "MOV     R0, R8\n"
                "BL      sub_FFD018E4\n"
                "MOV     R5, R0\n"
                "B       loc_FFC41020\n"
"loc_FFC4100C:\n"
                "MOV     R5, #0x40\n"
                "B       loc_FFC41020\n"
"loc_FFC41014:\n"
                "MOV     R1, #0x374\n"
                "LDR     R0, =0xFFC40EBC\n"
                "BL      sub_FFC0BDB8\n"
"loc_FFC41020:\n"				
                "STR     R6, [R7,#0x44]!\n"
                "MOV     R0, #1\n"
                "STR     R5, [R7,#4]\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
	);
} //#fe

