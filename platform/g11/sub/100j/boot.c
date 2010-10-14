#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "stdlib.h"


const char * const new_sa = &_end;


// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

void taskCreateHook(int *p) { 
p-=17;
if (p[0]==0xFF87B13C)  p[0]=(int)capt_seq_task;
if (p[0]==0xFF962AF4)  p[0]=(int)movie_record_task;
if (p[0]==0xFF898F88)  p[0]=(int)init_file_modules_task; 
if (p[0]==0xFF8BFBA8)  p[0]=(int)exp_drv_task;
if (p[0]==0xFF860554)  p[0]=(int)JogDial_task_my;
}

void taskCreateHook2(int *p) { 
p-=17;
if (p[0]==0xFF898F88)  p[0]=(int)init_file_modules_task;
if (p[0]==0xFF8BFBA8)  p[0]=(int)exp_drv_task; 
}

void __attribute__((naked,noinline)) boot() {
    asm volatile (
                    "LDR     R1, =0xC0410000\n"
                    "MOV     R0, #0\n"
                    "STR     R0, [R1]\n"
                    "MOV     R1, #0x78\n"
                    "MCR     p15, 0, R1,c1,c0\n"
                    "MOV     R1, #0\n"
                    "MCR     p15, 0, R1,c7,c10, 4\n"
                    "MCR     p15, 0, R1,c7,c5\n"
                    "MCR     p15, 0, R1,c7,c6\n"
                    "MOV     R0, #0x3D\n"
                    "MCR     p15, 0, R0,c6,c0\n"
                    "MOV     R0, #0xC000002F\n"
                    "MCR     p15, 0, R0,c6,c1\n"
                    "MOV     R0, #0x33\n"
                    "MCR     p15, 0, R0,c6,c2\n"
                    "MOV     R0, #0x40000033\n"
                    "MCR     p15, 0, R0,c6,c3\n"
                    "MOV     R0, #0x80000017\n"
                    "MCR     p15, 0, R0,c6,c4\n"
                    "LDR     R0, =0xFF80002D\n"
                    "MCR     p15, 0, R0,c6,c5\n"
                    "MOV     R0, #0x34\n"
                    "MCR     p15, 0, R0,c2,c0\n"
                    "MOV     R0, #0x34\n"
                    "MCR     p15, 0, R0,c2,c0, 1\n"
                    "MOV     R0, #0x34\n"
                    "MCR     p15, 0, R0,c3,c0\n"
                    "LDR     R0, =0x3333330\n"
                    "MCR     p15, 0, R0,c5,c0, 2\n"
                    "LDR     R0, =0x3333330\n"
                    "MCR     p15, 0, R0,c5,c0, 3\n"
                    "MRC     p15, 0, R0,c1,c0\n"
                    "ORR     R0, R0, #0x1000\n"
                    "ORR     R0, R0, #4\n"
                    "ORR     R0, R0, #1\n"
                    "MCR     p15, 0, R0,c1,c0\n"
                    "MOV     R1, #0x80000006\n"
                    "MCR     p15, 0, R1,c9,c1\n"
                    "MOV     R1, #6\n"
                    "MCR     p15, 0, R1,c9,c1, 1\n"
                    "MRC     p15, 0, R1,c1,c0\n"
                    "ORR     R1, R1, #0x50000\n"
                    "MCR     p15, 0, R1,c1,c0\n"
                    "LDR     R2, =0xC0200000\n"
                    "MOV     R1, #1\n"
                    "STR     R1, [R2,#0x10C]\n"
                    "MOV     R1, #0xFF\n"
                    "STR     R1, [R2,#0xC]\n"
                    "STR     R1, [R2,#0x1C]\n"
                    "STR     R1, [R2,#0x2C]\n"
                    "STR     R1, [R2,#0x3C]\n"
                    "STR     R1, [R2,#0x4C]\n"
                    "STR     R1, [R2,#0x5C]\n"
                    "STR     R1, [R2,#0x6C]\n"
                    "STR     R1, [R2,#0x7C]\n"
                    "STR     R1, [R2,#0x8C]\n"
                    "STR     R1, [R2,#0x9C]\n"
                    "STR     R1, [R2,#0xAC]\n"
                    "STR     R1, [R2,#0xBC]\n"
                    "STR     R1, [R2,#0xCC]\n"
                    "STR     R1, [R2,#0xDC]\n"
                    "STR     R1, [R2,#0xEC]\n"
                    "STR     R1, [R2,#0xFC]\n"
                    "LDR     R1, =0xC0400008\n"
                    "LDR     R2, =0x430005\n"
                    "STR     R2, [R1]\n"
                    "MOV     R1, #1\n"
                    "LDR     R2, =0xC0243100\n"
                    "STR     R2, [R1]\n"
                    "LDR     R2, =0xC0242010\n"
                    "LDR     R1, [R2]\n"
                    "ORR     R1, R1, #1\n"
                    "STR     R1, [R2]\n"
                    "LDR     R0, =0xFFC0C238\n"
                    "LDR     R1, =0x1900\n" // MEMBASEADDR=0x1900
                    "LDR     R3, =0xE90C\n"

"loc_FF81013C:\n"
                     "CMP     R1, R3\n"
                     "LDRCC   R2, [R0],#4\n"
                     "STRCC   R2, [R1],#4\n"
                     "BCC     loc_FF81013C\n"
                     "LDR     R1, =0x1411E8\n" // MEMISOSTART=0x1411E8
                     "MOV     R2, #0\n"
"loc_FF810154:\n"
                     "CMP     R3, R1\n"
                     "STRCC   R2, [R3],#4\n"
                     "BCC     loc_FF810154\n"
		             "B      sub_FF810354_my\n"
    );
};

void __attribute__((naked,noinline)) sub_FF810354_my() {

    *(int*)0x1930=(int)taskCreateHook; 
    *(int*)0x1934=(int)taskCreateHook2; 
    *(int*)0x1938=(int)taskCreateHook; 		

    /* Power ON/OFF detection */
	*(int*)(0x25C8)= (*(int*)0xC0220108)&1 ? 0x1000000 : 0x2000000; // replacement  for correct power-on.

		asm volatile (	
 		"LDR     R0, =0xFF8103CC\n"
		"MOV     R1, #0\n"
		"LDR     R3, =0xFF810404\n"
"loc_FF810360:\n"
		"CMP     R0, R3\n"
		"LDRCC   R2, [R0],#4\n"
		"STRCC   R2, [R1],#4\n"
		"BCC     loc_FF810360\n"
		"LDR     R0, =0xFF810404\n"
		"MOV     R1, #0x4B0\n"
		"LDR     R3, =0xFF810618\n"
"loc_FF81037C:\n"
		"CMP     R0, R3\n"
		"LDRCC   R2, [R0],#4\n"
		"STRCC   R2, [R1],#4\n"
		"BCC     loc_FF81037C\n"
		"MOV     R0, #0xD2\n"
		"MSR     CPSR_cxsf, R0\n"
		"MOV     SP, #0x1000\n"
		"MOV     R0, #0xD3\n"
		"MSR    CPSR_cxsf, R0\n"
		"MOV     SP, #0x1000\n"
		"LDR     R0, =0x6C4\n" // @0xFF8103C0
		"LDR     R2, =0xEEEEEEEE\n"
		"MOV     R3, #0x1000\n"
"loc_FF8103B0:\n"
		"CMP     R0, R3\n"
		"STRCC   R2, [R0],#4\n"
		"BCC     loc_FF8103B0\n"
		"BL      sub_FF811178_my\n" // ----->

"loc_FF8103C0:\n"
                "ANDEQ   R0, R0, R4,ASR#13\n"

"loc_FF8103C4:\n"
                "ANDEQ   R0, R0, R0,ROR R6\n"

"loc_FF8103C8:\n"
                "ANDEQ   R0, R0, R4,ROR R6\n"

"loc_FF8103CC:\n"
                "NOP\n"
                "LDR     PC, =0xFF810618\n"
  );				
};

void __attribute__((naked,noinline)) sub_FF811178_my() { 
        asm volatile ( 
	"STR     LR, [SP,#-4]!\n"
	"SUB     SP, SP, #0x74\n"
	"MOV     R0, SP\n"
	"MOV     R1, #0x74\n"
	"BL      sub_FFB3CA80\n"
	"MOV     R0, #0x53000\n"
	"STR     R0, [SP,#4]\n"
//	"LDR     R0, =0x1411E8\n"		// -
    "LDR     R0, =new_sa\n"        // +
    "LDR     R0, [R0]\n"           // +
	"LDR     R2, =0x379C00\n"
	"LDR     R1, =0x3724A8\n"
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
//	"LDR     R1, =0xFF815E34\n" // -
	"LDR     R1, =sub_FF815E34_my\n" //+ ---------->
	"STR     R0, [SP,#0x20]\n"
	"MOV     R0, #0x96\n"
	"STR     R0, [SP,#0x24]\n"
	"MOV     R0, #0x78\n"
	"STR     R0, [SP,#0x28]\n"
	"MOV     R0, #0x64\n"
	"STR     R0, [SP,#0x2C]\n"
	"MOV     R0, #0\n"
	"STR     R0, [SP,#0x30]\n"
	"STR     R0, [SP,#0x34]\n"
	"MOV     R0, #0x10\n"
	"STR     R0, [SP,#0x5C]\n"
	"MOV     R0, #0x800\n"
	"STR     R0, [SP,#0x74-0x14]\n"
	"MOV     R0, #0xA0\n"
	"STR     R0, [SP,#0x60]\n"
	"MOV     R0, #0x280\n"
	"STR     R0, [SP,#0x68]\n"
	"MOV     R0, SP\n"
	"MOV     R2, #0\n"
	"BL      sub_FF8133E4\n"
	"ADD     SP, SP, #0x74\n"
	"LDR     PC, [SP],#4\n"
        );
}; 

void __attribute__((naked,noinline)) sub_FF815E34_my() {
	asm volatile (	
        "STMFD   SP!, {R4,LR}\n"
        "BL      sub_FF810B08\n"
	

        "BL      sub_FF81A148\n" // dmSetup
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF815F48\n" // aDmSetup
        "BLLT    sub_FF815F28\n" // err_init_task
        "BL      sub_FF815A70\n"

        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF815F50\n" //termDriverInit
        "BLLT    sub_FF815F28\n" 	// err_init_task
        "LDR     R0, =0xFF815F60\n" //_term
		"BL      sub_FF815B58\n" 	// termDeviceCreate
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF815F68\n" //termDeviceCreate
        "BLLT    sub_FF815F28\n" 	// err_init_task
        "LDR     R0, =0xFF815F60\n" // _term
		"BL      sub_FF813BE0\n" 	// stdioSetup 
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF815F7C\n" // stdioSetup 
        "BLLT    sub_FF815F28\n"	// err_init_task
		"BL      sub_FF819B5C\n"
        "CMP     R0, #0\n"
        "LDRLT   R0, =0xFF815F88\n" //stdlibSetup
        "BLLT    sub_FF815F28\n"	// err_init_task
        "BL      sub_FF81165C\n"
		"CMP     R0, #0\n"
        "LDRLT   R0, =0xFF815F94\n" // armlib_setup
        "BLLT    sub_FF815F28\n"

        "LDMFD   SP!, {R4,LR}\n"
        "B       taskcreate_Startup_my\n" //---------->
        );
}; 



void __attribute__((naked,noinline)) taskcreate_Startup_my() { 

	asm volatile (	
                "STMFD   SP!, {R3,LR}\n"
                "BL		 sub_FF83332C\n"
                "BL      sub_FF83AC68\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF81F8AC\n"
                "BL      sub_FF834A98\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF81F8AC\n"
                "BL      sub_FF833328\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF81F8AC\n"
                "BL      sub_FF832A04\n"
                "LDR     R1, =0xC0220000\n"
                "MOV     R0, #0x44\n"
                "STR     R0, [R1,#0x1C]\n"
                "BL      sub_FF832BF4\n"
"loc_FF81F8A8:\n"
				"B       loc_FF81F8A8\n"
"loc_FF81F8AC:\n"
//                "BL      0xFF833334\n"// removed, see boot() function
                "BL      sub_FF85FA68\n"
                "BL		 sub_FF838F18\n"
                "MOV     R0, #0x46\n"
                "BL      sub_FF8390A0\n"
                "LDR     R1, =0x3CE000\n"
                "MOV     R0, #0\n"
                "BL      sub_FF839360\n"
                "BL      sub_FF83910C\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
		//		"ADR     R3, 0xFF81F804\n" // -
				"LDR     R3, =task_Startup_my\n" //+ -----------> 
                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFF81F8FC\n"
                "BL      sub_FF81E5B4\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
 );
}; 

void __attribute__((naked,noinline)) task_Startup_my() { 

       	asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FF816490\n"
			  "BL      sub_FF83441C\n"
              "BL      sub_FF832674\n"
              "BL      sub_FF83ACA8\n"
              "BL      sub_FF83AE8C\n"
              //"BL      sub_FF83AD3C\n" // Skip starting diskboot.bin again
	          "BL      sub_FF83B030\n"
              "BL      sub_FF831370\n"
              "BL      sub_FF83AEBC\n"
              "BL      sub_FF8386BC\n"
              "BL      sub_FF83B034\n"
			//"BL      sub_FF833224\n" //taskcreate_PhySw		
	);
	CreateTask_spytask();  // +
    CreateTask_PhySw(); // +

    asm volatile (	
  	          "BL      sub_FF836618\n"
              "BL      sub_FF83B04C\n"
              "BL      sub_FF8306A8\n"
              "BL      sub_FF831FCC\n"
              "BL      sub_FF83AA40\n"
	          "BL      sub_FF832628\n"
              "BL      sub_FF831ED8\n" 
              "BL      sub_FF8313A4\n"
              "BL      sub_FF83BC60\n"
              "BL      sub_FF831EB0\n"
              "LDMFD   SP!, {R4,LR}\n"
              "B       sub_FF8165B0\n"
	);
}; 

void CreateTask_spytask() { 
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

void __attribute__((naked,noinline)) CreateTask_PhySw() {
       	asm volatile ( 
		"STMFD   SP!, {R3-R5,LR}\n"
		"LDR     R4, =0x1C38\n"
		"LDR     R0, [R4,#0x10]\n"
		"CMP     R0, #0\n"
		"BNE     loc_FF833258\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0]\n"
		"LDR     R3, =mykbd_task\n"  // task_phySw
//		"LDR     R3, =0xFF8331F0\n"  // task_phySw

//		"MOV     R2, #0x800\n"
		"MOV     R2, #0x2000\n"		// greater Stacksize

		"MOV     R1, #0x17\n"
		"LDR     R0, =0xFF833430\n"	//phySw
		"BL      sub_FF839160\n" 	//KernelCreateTask
		"STR     R0, [R4,#0x10]\n"
"loc_FF833258:\n"
		"BL      sub_FF8608A8\n"
		"BL      sub_FF88BB08\n"
		"BL      sub_FF834A3C\n"
		"CMP     R0, #0\n"
		"LDREQ   R1, =0x32584\n"
		"LDMEQFD SP!, {R3-R5,LR}\n"
		"BEQ     sub_FF88BA90\n"
		"LDMFD   SP!, {R3-R5,PC}\n"
        "NOP\n"
	);
}; 

void __attribute__((naked,noinline)) init_file_modules_task() { 
  asm volatile (
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FF88DF50\n"
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    sub_FF8931BC\n"
			  /* "BL      sub_FF88DF7C\n" */ // -
				 "BL      sub_FF88DF7C_my\n"    //----------->
		 		 "BL      core_spytask_can_start\n"      // +
                 "CMP     R4, #0\n"
                 "MOVEQ   R0, R5\n"
                 "LDMEQFD SP!, {R4-R6,LR}\n"
                 "MOVEQ   R1, #0\n"
                 "BEQ     sub_FF8931BC\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}; 

void __attribute__((naked,noinline)) sub_FF88DF7C_my() { 
 asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "MOV     R0, #3\n"
               //"BL     sub_FF86F8AC\n" //-	
				 "BL     sub_FF86F8AC_my\n" // ---------->
				 "BL     sub_FF9487F0\n"
                 "LDR     R4, =0x3030\n"
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF88DFB4\n"
				 "BL      sub_FF86EBB8\n"
				 "BL      sub_FF93C834\n"
                 "BL      sub_FF86EBB8\n"
				 "BL      sub_FF86AEB4\n"
                 "BL      sub_FF86EAB8\n"
                 "BL      sub_FF93C8FC\n"
"loc_FF88DFB4:\n"
				 "MOV     R0, #1\n"
                 "STR     R0, [R4]\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}; 


void __attribute__((naked,noinline)) sub_FF86F8AC_my() {
 asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R8, R0\n"
                "BL      sub_FF86F82C\n"
				"LDR     R1, =0x375F0\n"
                "MOV     R6, R0\n"
                "ADD     R4, R1, R0,LSL#7\n"
                "LDR     R0, [R4,#0x6C]\n"
                "CMP     R0, #4\n"
                "LDREQ   R1, =0x804\n"
                "LDREQ   R0, =0xFF86F378\n"
				"BLEQ    sub_FF81E88C\n"
                "MOV     R1, R8\n"
                "MOV     R0, R6\n"
                "BL      sub_FF86F0CC\n"
				"LDR     R0, [R4,#0x38]\n"
                "BL      sub_FF86FEC8\n"
                "CMP     R0, #0\n"
                "STREQ   R0, [R4,#0x6C]\n"
                "MOV     R0, R6\n"
                "BL      sub_FF86F15C\n"
                "MOV     R0, R6\n"
//                "BL      sub_FF86F4E0\n" //-
                "BL       sub_FF86F4E0_my\n" //----------->
		        "MOV     R5, R0\n"
                "MOV     R0, R6\n"
		        "BL      sub_FF86F708\n" 
		        "LDR     R6, [R4,#0x3C]\n"
                "AND     R7, R5, R0\n"
                "CMP     R6, #0\n"
                "LDR     R1, [R4,#0x38]\n"
                "MOVEQ   R0, #0x80000001\n"
                "MOV     R5, #0\n"
                "BEQ     loc_FF86F95C\n"
                "MOV     R0, R1\n"
                "BL      sub_FF86ED20\n"
                "CMP     R0, #0\n"
                "MOVNE   R5, #4\n"
                "CMP     R6, #5\n"
                "ORRNE   R0, R5, #1\n"
                "BICEQ   R0, R5, #1\n"
                "CMP     R7, #0\n"
                "BICEQ   R0, R0, #2\n"
                "ORREQ   R0, R0, #0x80000000\n"
                "BICNE   R0, R0, #0x80000000\n"
                "ORRNE   R0, R0, #2\n"

"loc_FF86F95C:\n"
				"CMP     R8, #7\n"
               "STR     R0, [R4,#0x40]\n"
               "LDMNEFD SP!, {R4-R8,PC}\n"
               "MOV     R0, R8\n"
               "BL      sub_FF86F87C\n"
               "CMP     R0, #0\n"
               "LDMEQFD SP!, {R4-R8,LR}\n"
               "LDREQ   R0, =0xFF86F9A8\n"
			   "BEQ     =0xFF81175C\n" //qPrintf
               "LDMFD   SP!, {R4-R8,PC}\n"
 );
}; 

void __attribute__((naked,noinline)) sub_FF86F4E0_my() {

 asm volatile (
               "STMFD   SP!, {R4-R6,LR}\n"
               "MOV     R5, R0\n"
               "LDR     R0, =0x375F0\n"
               "ADD     R4, R0, R5,LSL#7\n"
               "LDR     R0, [R4,#0x6C]\n"
               "TST     R0, #2\n"
               "MOVNE   R0, #1\n"
               "LDMNEFD SP!, {R4-R6,PC}\n"
               "LDR     R0, [R4,#0x38]\n"
               "MOV     R1, R5\n"
//              "BL      sub_FF86F1DC\n" // -
               "BL    sub_FF86F1DC_my\n" // --------->
			   "CMP     R0, #0\n"
               "LDRNE   R0, [R4,#0x38]\n"
               "MOVNE   R1, R5\n"
               "BLNE    sub_FF86F39C\n"
			   "LDR     R2, =0x37670\n"
               "ADD     R1, R5, R5,LSL#4\n"
               "LDR     R1, [R2,R1,LSL#2]\n"
               "CMP     R1, #4\n"
               "BEQ     loc_FF86F540\n"
               "CMP     R0, #0\n"
               "LDMEQFD SP!, {R4-R6,PC}\n"
               "MOV     R0, R5\n"
               "BL      sub_FF86EDB0\n"

"loc_FF86F540:\n"
                "CMP     R0, #0\n"
                "LDRNE   R1, [R4,#0x6C]\n"
                "ORRNE   R1, R1, #2\n"
                "STRNE   R1, [R4,#0x6C]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
 );
};


void __attribute__((naked,noinline)) sub_FF86F1DC_my() {
 asm volatile (	
                "STMFD   SP!, {R4-R10,LR}\n"
                "MOV     R9, R0\n"
                "LDR     R0, =0x375F0\n"
                "MOV     R8, #0\n"
                "ADD     R5, R0, R1,LSL#7\n"
                "LDR     R0, [R5,#0x3C]\n"
                "MOV     R7, #0\n"
                "CMP     R0, #7\n"
                "MOV     R6, #0\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
                "B       loc_FF86F334\n"
"loc_FF86F208:\n"
				"B       loc_FF86F240\n"
"loc_FF86F20C:\n"
                "B       loc_FF86F228\n"
 "loc_FF86F210:\n"
				"B       loc_FF86F228\n"
"loc_FF86F214:\n"
                "B  	 loc_FF86F228\n"
 "loc_FF86F218:\n"
                 "B      loc_FF86F228\n"
"loc_FF86F21C:\n"
                 "B      loc_FF86F32C\n"
"loc_FF86F220:\n"
                 "B      loc_FF86F228\n"
"loc_FF86F224:\n"
                 "B      loc_FF86F228\n"
"loc_FF86F228:\n"
                "MOV     R2, #0\n"
                "MOV     R1, #0x200\n"
                "MOV     R0, #2\n"
                "BL      sub_FF887F8C\n"
                "MOVS    R4, R0\n"
                "BNE     loc_FF86F248\n"

 "loc_FF86F240:\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R10,PC}\n"
"loc_FF86F248:\n"
                 "LDR     R12, [R5,#0x50]\n"
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R9\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF86F274\n"
                 "MOV     R0, #2\n"
 				 "BL      sub_FF8880D8\n"
                 "B       loc_FF86F240\n"
"loc_FF86F274:\n"
                 "LDR     R1, [R5,#0x64]\n"
                 "MOV     R0, R9\n"
                 "BLX     R1\n"



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
                 //"LDRB    LR, [R4,#0x1FF]\n" // replaced, see below
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
                 //"LDRB    R12, [R4,#0x1FE]\n" // replaced, see below
		 
                 "LDRB    R12, [LR,#0x1FE]\n"        // New! First MBR signature byte (0x55)
                 "LDRB    LR, [LR,#0x1FF]\n"         //      Last MBR signature byte (0xAA)	

                 "BNE     loc_FF86F300\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FF86F300\n"
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R7, R1\n"
                 "MOVEQ   R6, R3\n"
                 "MOVEQ   R4, #1\n"
                 "BEQ     loc_FF86F304\n"
"loc_FF86F300:\n"
                 "MOV     R4, R8\n"
"loc_FF86F304:\n"
                 "MOV     R0, #2\n"
				 "BL      sub_FF8880D8\n"
                 "CMP     R4, #0\n"
                 "BNE     loc_FF86F340\n"
                 "LDR     R1, [R5,#0x64]\n"
                 "MOV     R7, #0\n"
                 "MOV     R0, R9\n"
                 "BLX     R1\n"
                 "MOV     R6, R0\n"
                 "B       loc_FF86F340\n"
"loc_FF86F32C:\n"
                 "MOV     R6, #0x40\n"
                 "B       loc_FF86F340\n"
"loc_FF86F334:\n"
                 "LDR     R1, =0x568\n"
                 "LDR     R0, =0xFF86F378\n"
                 
				 "BL   	  =0xFF81E88C\n"

"loc_FF86F340:\n"
                 "STR     R7, [R5,#0x44]!\n"
                 "STMIB   R5, {R6,R8}\n"
                 "MOV     R0, #1\n"
		 
                 "LDMFD   SP!, {R4-R10,PC}\n"
 );
}; 

void __attribute__((naked,noinline)) sub_FF8604E0_my() {
 asm volatile (
				"LDR     R0, =0x25D0\n"
				"LDR     R0, [R0,#8]\n"
				"B       sub_FF838B50\n"
				);
};

void __attribute__((naked,noinline)) JogDial_task_my() {
 asm volatile (	
               "STMFD   SP!, {R4-R11,LR}\n"
               "SUB     SP, SP, #0x2C\n"
               "BL      sub_FF8608FC\n"
               "LDR     R1, =0x25D0\n"
               "LDR     R8, =0xFFB4775C\n" // Oder sub?
               "MOV     R0, #0\n"
               "ADD     R2, SP, #0x14\n"
               "ADD     R3, SP, #0x18\n"
               "ADD     R10, SP, #0xC\n"
               "ADD     R9, SP, #0x10\n"
               "MOV     R7, #0\n"
"loc_FF860580:\n"
               "ADD     R3, SP, #0x18\n"
               "ADD     R12, R3, R0,LSL#1\n"
               "ADD     R2, SP, #0x14\n"
               "STRH    R7, [R12]\n"
               "ADD     R12, R2, R0,LSL#1\n"
               "STRH    R7, [R12]\n"
               "STR     R7, [R9,R0,LSL#2]\n"
               "STR     R7, [R10,R0,LSL#2]\n"
               "ADD     R0, R0, #1\n"
               "CMP     R0, #1\n"
               "BLT     loc_FF860580\n"
"loc_FF8605AC:\n"
               "LDR     R0, =0x25D0\n"
               "MOV     R2, #0\n"
               "LDR     R0, [R0,#8]\n"
               "ADD     R1, SP, #0x4\n"
               "BL      sub_FF83894C\n"
               "TST     R0, #1\n"
               "LDRNE   R1, =0x226\n"
               "LDRNE   R0, =0xFF860830\n" // "JogDial.c"
               "BLNE    sub_FF81E88C\n" // DebugAssert


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

               "LDR     R0, [SP,#0x4]\n"
               "AND     R4, R0, #0xFF\n"
               "AND     R0, R0, #0xFF00\n"
               "CMP     R0, #0x100\n"
               "BEQ     loc_FF860630\n"
               "CMP     R0, #0x200\n"
               "BEQ     loc_FF860668\n"
               "CMP     R0, #0x300\n"
               "BEQ     loc_FF86087C\n"
               "CMP     R0, #0x400\n"
               "BNE     loc_FF8605AC\n"
               "CMP     R4, #0\n"
               "LDRNE   R1, =0x2CA\n"
               "LDRNE   R0, =0xFF860830\n" // "JogDial.c"
               "BLNE    sub_FF81E88C\n" // DebugAssert
               "LDR     R2, =0xFFB47748\n"
               "ADD     R0, R4, R4,LSL#2\n"
               "LDR     R1, [R2,R0,LSL#2]\n"
               "STR     R7, [R1]\n"
               "MOV     R1, #1\n"
               "ADD     R0, R2, R0,LSL#2\n"
"loc_FF860624:\n"
               "LDR     R0, [R0,#8]\n"
               "STR     R1, [R0]\n"
               "B       loc_FF8605AC\n"
"loc_FF860630:\n"
               "LDR     R5, =0x25E0\n"
               "LDR     R0, [R5,R4,LSL#2]\n"
               "BL      sub_FF8398E4\n"
               "ADRL     R2, sub_FF8604E0_my\n"
//               "LDR     R2, sub_FF8604E0\n"
               "ADD     R1, R2, #0\n"
               "ORR     R3, R4, #0x200\n"
               "MOV     R0, #0x28\n"
               "BL      sub_FF839800\n"
               "TST     R0, #1\n"
               "CMPNE   R0, #0x15\n"
               "STR     R0, [R10,R4,LSL#2]\n"
               "BEQ     loc_FF8605AC\n"
               "LDR     R1, =0x23B\n"
               "B       loc_FF860820\n"
"loc_FF860668:\n"
               "LDR     R1, =0xFFB47748\n"
               "ADD     R0, R4, R4,LSL#2\n"
               "STR     R0, [SP,#0x28]\n"
               "ADD     R0, R1, R0,LSL#2\n"
               "STR     R0, [SP,#0x24]\n"
               "LDR     R0, [R0,#4]\n"
               "LDR     R0, [R0]\n"
               "MOV     R2, R0,ASR#16\n"
               "ADD     R0, SP, #0x18\n"
               "ADD     R0, R0, R4,LSL#1\n"
               "STR     R0, [SP,#0x20]\n"
               "STRH    R2, [R0]\n"
               "ADD     R0, SP, #0x14\n"
               "ADD     R0, R0, R4,LSL#1\n"
               "STR     R0, [SP,#0x1c]\n"
               "LDRSH   R3, [R0]\n"
               "SUB     R0, R2, R3\n"
               "CMP     R0, #0\n"
               "BEQ     loc_FF8607D8\n"
               "MOV     R1, R0\n"
               "RSBLT   R0, R0, #0\n"
               "MOVLE   R5, #0\n"
               "MOVGT   R5, #1\n"
               "CMP     R0, #0xFF\n"
               "BLS     loc_FF8606F4\n"
               "CMP     R1, #0\n"
               "RSBLE   R0, R3, #0xFF\n"
               "ADDLE   R0, R0, #0x7F00\n"
               "ADDLE   R0, R0, R2\n"
               "RSBGT   R0, R2, #0xFF\n"
               "ADDGT   R0, R0, #0x7F00\n"
               "ADDGT   R0, R0, R3\n"
               "ADD     R0, R0, #0x8000\n"
               "ADD     R0, R0, #1\n"
               "EOR     R5, R5, #1\n"
"loc_FF8606F4:\n"
               "STR     R0, [SP,#0x8]\n"
               "LDR     R0, [R9,R4,LSL#2]\n"
               "CMP     R0, #0\n"
               "BEQ     loc_FF860744\n"
               "LDR     R1, =0xFFB47740\n"
               "ADD     R1, R1, R4,LSL#3\n"
               "LDR     R1, [R1,R5,LSL#2]\n"
               "CMP     R1, R0\n"
               "BEQ     loc_FF860760\n"
               "ADD     R11, R4, R4,LSL#1\n"
               "ADD     R6, R8, R11,LSL#2\n"
               "LDRB    R0, [R6,#9]\n"
               "CMP     R0, #1\n"
               "LDREQ   R0, [R6,#4]\n"
               "BLEQ    sub_FF89501C\n"
               "LDRB    R0, [R6,#8]\n"
               "CMP     R0, #1\n"
               "BNE     loc_FF860760\n"
               "LDR     R0, [R8,R11,LSL#2]\n"
               "B       loc_FF86075C\n"
"loc_FF860744:\n"
               "ADD     R0, R4, R4,LSL#1\n"
               "ADD     R1, R8, R0,LSL#2\n"
               "LDRB    R1, [R1,#8]\n"
               "CMP     R1, #1\n"
               "BNE     loc_FF860760\n"
               "LDR     R0, [R8,R0,LSL#2]\n"
"loc_FF86075C:\n"
               "BL      sub_FF89501C\n"
"loc_FF860760:\n"
               "LDR     R0, =0xFFB47740\n"
               "LDR     R1, [SP,#0x8]\n"
               "ADD     R6, R0, R4,LSL#3\n"
               "LDR     R0, [R6,R5,LSL#2]\n"
               "BL      sub_FF894F4C\n"
               "LDR     R0, [R6,R5,LSL#2]\n"
               "STR     R0, [R9,R4,LSL#2]\n"
               "LDR     R0, [SP,#0x20]\n"
               "LDR     R1, [SP,#0x1C]\n"
               "LDRH    R0, [R0]\n"
               "STRH    R0, [R1]\n"
               "ADD     R0, R4, R4,LSL#1\n"
               "ADD     R0, R8, R0,LSL#2\n"
               "LDRB    R0, [R0,#9]\n"
               "CMP     R0, #1\n"
               "BNE     loc_FF8607D8\n"
               "LDR     R5, =0x25E0\n"
               "LDR     R0, [R5,R4,LSL#2]\n"
               "BL      sub_FF8398E4\n"
//               "ADR     R2, sub_FF8604EC\n"
               "LDR     R2, =0xFF8604EC\n"
               "ADD     R1, R2, #0\n"
               "ORR     R3, R4, #0x300\n"
               "MOV     R0, #0x1F4\n"
               "BL      sub_FF839800\n"
               "TST     R0, #1\n"
               "CMPNE   R0, #0x15\n"
               "STR     R0, [R5,R4,LSL#2]\n"
               "LDRNE   R0, =0xFF860830\n" //"JogDial.c"
               "MOVNE   R1, #0x2A4\n"
               "BLNE    sub_FF81E88C\n" //DebugAssert
"loc_FF8607D8:\n"
               "ADD     R0, R4, R4,LSL#1\n"
               "ADD     R0, R8, R0,LSL#2\n"
               "LDRB    R0, [R0,#0xA]\n"
               "CMP     R0, #1\n"
               "BNE     loc_FF860860\n"
               "LDR     R0, =0x25D0\n"
               "LDR     R0, [R0,#0xC]\n"
               "CMP     R0, #0\n"
               "BEQ     loc_FF860860\n"
//               "ADR     R2, loc_FF8604E0\n"
               "ADRL     R2,sub_FF8604E0_my\n"
               "ADD     R1, R2, #0\n"
               "ORR     R3, R4, #0x400\n"
               "BL      sub_FF839800\n"
               "TST     R0, #1\n"
               "CMPNE   R0, #0x15\n"
               "STR     R0, [R10,R4,LSL#2]\n"
               "BEQ     loc_FF8605AC\n"
               "LDR     R1, =0x2AF\n"
"loc_FF860820:\n"
               "LDR     R0, =0xFF860830\n" // "JogDial.c"
               "BL      sub_FF81E88C\n" // DebugAssert
               "B       loc_FF8605AC\n"

			   "NOP\n"

"loc_FF860860:\n"
               "LDR     R1, =0xFFB47748\n"
               "LDR     R0, [SP,#0x28]\n"
               "LDR     R0, [R1,R0,LSL#2]\n"
               "STR     R7, [R0]\n"
               "LDR     R0, [SP,#0x24]\n"
               "MOV     R1, #1\n"
               "B       loc_FF860624\n"
"loc_FF86087C:\n"
               "LDR     R0, [R9,R4,LSL#2]\n"
               "CMP     R0, #0\n"
               "MOVEQ   R1, #0x2BC\n"
               "LDREQ   R0, =0xFF860830\n" //aJogdial_c
               "BLEQ    sub_FF81E88C\n" //DebugAssert
               "ADD     R0, R4, R4,LSL#1\n"
               "ADD     R0, R8, R0,LSL#2\n"
               "LDR     R0, [R0,#4]\n"
               "BL      sub_FF89501C\n"
               "STR     R7, [R9,R4,LSL#2]\n"
               "B       loc_FF8605AC\n"
 );
}; 
