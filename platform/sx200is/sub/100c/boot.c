#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

void JogDial_task_my(void);

/*
// debug use only
void debug_blink() {
	int i;        
	*((volatile int *) 0xC0223030) = 0x46; // Turn on Print LED
	for (i=0; i<80000; i++) // Wait a while
		{
     		asm volatile ( "nop\n" );
		}
	*((volatile int *) 0xC0223030) = 0x44; // Turn off LED
	for (i=0; i<80000; i++) // Wait a while
		{ 
    		asm volatile ( "nop\n" );
		}
};
*/


void taskCreateHook(int *p) { 
 p-=17;
 if (p[0]==0xFF86327C)  p[0]=(int)capt_seq_task;
 if (p[0]==0xFF821A90)  p[0]=(int)mykbd_task;
 if (p[0]==0xFF87F81C)  p[0]=(int)init_file_modules_task; 
 if (p[0]==0xFF84856C)  p[0]=(int)JogDial_task_my;
 if (p[0]==0xFF8A2214)  p[0]=(int)exp_drv_task;
}

void taskCreateHook2(int *p) { 
 p-=17;
 if (p[0]==0xFF87F81C)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFF8A2214)  p[0]=(int)exp_drv_task;
}

void taskCreateHook3(int *p) { 
 p-=17;
 if (p[0]==0xFF9382B8)  p[0]=(int)movie_record_task;
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};

void __attribute__((naked,noinline)) boot() {
    asm volatile (
				 //"B		  sub_FF81000C\n"
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
                 "LDR     R0, =0xFFB91B18\n"
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0xDBCC\n"
    "loc_FF81013C:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF81013C\n"
                 "LDR     R1, =0x12351C\n"
                 "MOV     R2, #0\n"
    "loc_FF810154:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FF810154\n"
                 "B       sub_FF8101A0_my\n"   //---------->
    );
};


void __attribute__((naked,noinline)) sub_FF8101A0_my() {
   *(int*)0x1934=(int)taskCreateHook;
   *(int*)0x1938=(int)taskCreateHook2;
   *(int*)0x1930=(int)taskCreateHook3; //  don't know why but movie will only work with 1930 and card lock only with 1934 - 1938
   *(int*)(0x24C0+4)= (*(int*)0xC0220128)&1 ? 0x2000000 : 0x1000000; // replacement of sub_FF821BD4 for correct power-on.
   asm volatile (
                 "LDR     R0, =0xFF810218\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFF810250\n"
"loc_FF8101AC:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF8101AC\n"
                 "LDR     R0, =0xFF810250\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFF810464\n"
"loc_FF8101C8:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF8101C8\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
"loc_FF8101FC:\n"
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FF8101FC\n"
                 "BL      sub_FF810FC4_my\n" //------------>
"loc_FF81020C:\n"
                 "ANDEQ   R0, R0, R4,ASR#13\n"
"loc_FF810210:\n"
                 "ANDEQ   R0, R0, R0,ROR R6\n"
"loc_FF810214:\n"
                 "ANDEQ   R0, R0, R4,ROR R6\n"
"loc_FF810218:\n"
                 "NOP\n"
                 "LDR     PC, =0xFF810464\n"
     );
}

void __attribute__((naked,noinline)) sub_FF810FC4_my() {
     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFAF8D3C\n"
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
               //  "LDR     R0, =0x12351C\n"
                 "LDR     R0, =new_sa\n"        // +
                 "LDR     R0, [R0]\n"           // +
                 "LDR     R2, =0x2F9C00\n"
                 "LDR     R1, =0x2F24A8\n"
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
                 "LDR     R1, =sub_FF814D38_my\n" //------------>
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
                 "STR     R0, [SP,#0x60]\n"
                 "MOV     R0, #0xA0\n"
                 "STR     R0, [SP,#0x64]\n"
                 "MOV     R0, #0x280\n"
                 "STR     R0, [SP,#0x68]\n"
                 "MOV     R0, SP\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF812D68\n"
                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"
     );
}

void __attribute__((naked,noinline)) sub_FF814D38_my() {
     asm volatile ( 
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF810954\n"
                 "BL      sub_FF8190B4\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814E4C\n"    // "dmSetup"
                 "BLLT    sub_FF814E2C\n"
                 "BL      sub_FF814974\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814E54\n"   // "termDriverInit"
                 "BLLT    sub_FF814E2C\n"
                 "LDR     R0, =0xFF814E64\n"   // "/_term"
                 "BL      sub_FF814A5C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814E6C\n"   // "termDeviceCreate"
                 "BLLT    sub_FF814E2C\n"
                 "LDR     R0, =0xFF814E64\n"   // "/_term"
                 "BL      sub_FF813578\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814E80\n"    // "stdioSetup"
                 "BLLT    sub_FF814E2C\n"
                 "BL      sub_FF818BCC\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814E8C\n"    // "stdlibSetup"
                 "BLLT    sub_FF814E2C\n"
                 "BL      sub_FF8114A8\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814E98\n"    // "armlib_setup"
                 "BLLT    sub_FF814E2C\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       taskcreate_Startup_my\n" //---------->  at FF81C260

        );
};

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R3,LR}\n"
                 "BL      sub_FF821BCC\n"         //j_nullsub_239
                 "BL      sub_FF829050\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF81C298\n"
                 "BL      sub_FF821BC8\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF81C298\n"
                 "BL      sub_FF8212BC\n"
                 "LDR     R1, =0xC0220000\n"
                 "MOV     R0, #0x44\n"
                 "STR     R0, [R1,#0x1C]\n"
                 "BL      sub_FF8214A8\n"
"loc_FF81C294:\n"
                 "B       loc_FF81C294\n"
"loc_FF81C298:\n"
      //           "BL      sub_FF821BD4\n"       // -- replaced for power button startup
                 "BL      sub_FF821BD0\n"        // j_nullsub_240 
                 "BL      sub_FF827308\n"
                 "LDR     R1, =0x34E000\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF827750\n"
                 "BL      sub_FF8274FC\n"     // _sub_FF8274FC__KerSys.c__548
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =task_Startup_my\n"    //---------------->
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x19\n"
                 "LDR     R0, =0xFF81C2E0\n"   // "Startup"
                 "BL      sub_FF81AFAC\n"      // eventproc_export_CreateTask
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R12,PC}\n"
     );
}

void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF815394\n"    // taskcreate_ClockSave
                 "BL      sub_FF822CB0\n"
                 "BL      sub_FF820F70\n"
                 "BL      sub_FF829090\n"    // j_nullsub_243
                 "BL      sub_FF829274\n"
            //     "BL      sub_FF829124\n"    // start diskboot.bin
                 "BL      sub_FF829418\n"
                 "BL      sub_FF81FB90\n"
                 "BL      sub_FF8292A4\n"
                 "BL      sub_FF826908\n"
                 "BL      sub_FF82941C\n"
//"BL debug_blink\n"
                 "BL      CreateTask_spytask\n"    // +
//"BL debug_blink\n"
                 "BL      sub_FF821AC4\n"   // taskcreate_PhySw
                 "BL      sub_FF824B14\n"
                 "BL      sub_FF829434\n"
                 "BL      sub_FF81EFB0\n"   // nullsub_2
                 "BL      sub_FF82087C\n"
                 "BL      sub_FF828E2C\n"   // taskcreate_Bye
                 "BL      sub_FF820F20\n"
                 "BL      sub_FF820788\n"   // taskcreate_TempCheck
                 "BL      sub_FF81FBC4\n"
                 "BL      sub_FF829F18\n"
                 "BL      sub_FF820760\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF8154B4\n"   // _sub_FF8154B4__MLHCLOCK.c__0
     );
}


void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
 //"BL debug_blink\n"
               "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FF874B88\n"
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    sub_FF879A54\n"
                 "BL      sub_FF874BB4_my\n"           //---------->
                 "BL      core_spytask_can_start\n"      // CHDK: Set "it's-safe-to-start"-Flag for spytask
                 "CMP     R4, #0\n"
                 "MOVEQ   R0, R5\n"
                 "LDMEQFD SP!, {R4-R6,LR}\n"
                 "MOVEQ   R1, #0\n"
                 "BEQ     sub_FF879A54\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF874BB4_my() {
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FF857704_my\n"    //----------->
                 "BL      sub_FF91572C\n"       // nullsub_99
                 "LDR     R4, =0x2F04\n"
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF874BEC\n"
                 "BL      sub_FF856AC8\n"
                 "BL      sub_FF909DC4\n"
                 "BL      sub_FF856AC8\n"
                 "BL      sub_FF852B1C\n"
                 "BL      sub_FF8569C8\n"
                 "BL      sub_FF909E90\n"
 "loc_FF874BEC:\n"
                 "MOV     R0, #1\n"
                 "STR     R0, [R4]\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF857704_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R6, R0\n"
                 "BL      sub_FF85766C\n"              // _sub_FF85766C__Mounter.c__0 ; LOCATION: Mounter.c:0\n"
                 "LDR     R1, =0x11840\n"
                 "MOV     R5, R0\n"
                 "ADD     R4, R1, R0,LSL#7\n"
                 "LDR     R0, [R4,#0x70]\n"
                 "CMP     R0, #4\n"
                 "LDREQ   R1, =0x6D8\n"
                 "LDREQ   R0, =0xFF857190\n"    //  ; "Mounter.c"
                 "BLEQ    sub_FF81B284\n"      // DebugAssert
                 "MOV     R1, R6\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF8570D8\n"      //  _sub_FF8570D8__Mounter.c__0 ; LOCATION: Mounter.c:0
                 "LDR     R0, [R4,#0x38]\n"
                 "BL      sub_FF857C30\n"
                 "CMP     R0, #0\n"
                 "STREQ   R0, [R4,#0x70]\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF8571B0\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF8574A4_my\n"    // ------------------->
                 "MOV     R7, R0\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF857508\n"          //  _sub_FF857508__Mounter.c__7 ; LOCATION: Mounter.c:7
                 "LDR     R1, [R4,#0x3C]\n"
                 "AND     R2, R7, R0\n"
                 "CMP     R1, #0\n"
                 "MOV     R0, #0\n"
                 "MOVEQ   R0, #0x80000001\n"
                 "BEQ     loc_FF8577AC\n"
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
 "loc_FF8577AC:\n"
                 "CMP     R6, #7\n"
                 "STR     R0, [R4,#0x40]\n"
                 "LDMNEFD SP!, {R4-R8,PC}\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FF8576BC\n"
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R8,LR}\n"
                 "LDREQ   R0, =0xFF8579A8\n"       // ; "EMEM MOUNT ERROR!!!"
                 "BEQ     sub_FF8115A8\n"          // qPrintf
                 "LDMFD   SP!, {R4-R8,PC}\n"

 );
}


void __attribute__((naked,noinline)) sub_FF8574A4_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "MOV     R5, R0\n"
                 "LDR     R0, =0x11840\n"
                 "ADD     R4, R0, R5,LSL#7\n"
                 "LDR     R0, [R4,#0x70]\n"
                 "TST     R0, #2\n"
                 "MOVNE   R0, #1\n"
                 "LDMNEFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R5\n"
                 "BL      sub_FF857234_my\n"      // ------------------>
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R5\n"
                 "BL      sub_FF8573A0\n"     // __Mounter.c__0 ; LOCATION: Mounter.c:0
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF856CC0\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R1, [R4,#0x70]\n"
                 "ORRNE   R1, R1, #2\n"
                 "STRNE   R1, [R4,#0x70]\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF857234_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R0\n"
                 "LDR     R0, =0x11840\n"
                 "MOV     R7, #0\n"
                 "ADD     R5, R0, R1,LSL#7\n"
                 "LDR     R0, [R5,#0x3C]\n"
                 "MOV     R6, #0\n"
                 "CMP     R0, #7\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FF857384\n"
"loc_FF85725C:\n"
                 "B       loc_FF857294\n"
"loc_FF857260:\n"
                 "B       loc_FF85727C\n"
"loc_FF857264:\n"
                 "B       loc_FF85727C\n"
"loc_FF857268:\n"
                 "B       loc_FF85727C\n"
"loc_FF85726C:\n"
                 "B       loc_FF85727C\n"
"loc_FF857270:\n"
                 "B       loc_FF85737C\n"
"loc_FF857274:\n"
                 "B       loc_FF85727C\n"
"loc_FF857278:\n"
                 "B       loc_FF85727C\n"
"loc_FF85727C:\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x200\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FF86EC80\n"
                 "MOVS    R4, R0\n"
                 "BNE     loc_FF85729C\n"
"loc_FF857294:\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF85729C:\n"
                 "LDR     R12, [R5,#0x4C]\n"
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF8572C8\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FF86EDCC\n"       // __ExMemMan.c__0 ; LOCATION: ExMemMan.c:0
                 "B       loc_FF857294\n"
"loc_FF8572C8:\n"
                 "LDR     R1, [R5,#0x68]\n"
                 "MOV     R0, R8\n"
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
          "BNE     dg_sd_fat32\n"                // No, it isn't. Loop again.
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
            //     "LDRB    LR, [R4,#0x1FF]\n"
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
          //       "LDRB    R12, [R4,#0x1FE]\n"
                 "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
                 "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.

                 "MOV     R4, #0\n"
                 "BNE     loc_FF857354\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FF857354\n"
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R7, R1\n"
                 "MOVEQ   R6, R3\n"
                 "MOVEQ   R4, #1\n"
"loc_FF857354:\n"                            // CODE XREF: _sub_FF857234__Mounter.c__0+F8j
                 "MOV     R0, #2\n"
                 "BL      sub_FF86EDCC\n"    // __ExMemMan.c__0 ; LOCATION: ExMemMan.c
                 "CMP     R4, #0\n"
                 "BNE     loc_FF857390\n"
                 "LDR     R1, [R5,#0x68]\n"
                 "MOV     R7, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R1\n"
                 "MOV     R6, R0\n"
                 "B       loc_FF857390\n"
"loc_FF85737C:\n"                            // CODE XREF: _sub_FF857234__Mounter.c__0+20j
                 "MOV     R6, #0x40\n"
                 "B       loc_FF857390\n"
"loc_FF857384:\n"                            // CODE XREF: _sub_FF857234__Mounter.c__0+20j
                 "LDR     R1, =0x5C9\n"
                 "LDR     R0, =0xFF857190\n"     // "Mounter.c"
                 "BL      sub_FF81B284\n"        // DebugAssert
"loc_FF857390:\n"                                // CODE XREF: _sub_FF857234__Mounter.c__0+12Cj
                 "STR     R7, [R5,#0x44]!\n"
                 "MOV     R0, #1\n"
                 "STR     R6, [R5,#4]\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}


void __attribute__((naked,noinline)) JogDial_task_my() { 
 asm volatile(
                 "STMFD   SP!, {R3-R11,LR}\n"
                 "BL      sub_FF84871C\n"        // __JogDial.c__416 ; LOCATION: JogDial.c:416
                 "LDR     R11, =0x80000B01\n"
                 "LDR     R8, =0xFFAFE608\n"
                 "LDR     R7, =0xC0240000\n"
                 "LDR     R6, =0x24E4\n"
                 "MOV     R9, #1\n"
                 "MOV     R10, #0\n"
"loc_FF84858C:\n"
                 "LDR     R3, =0x1BB\n"
                 "LDR     R0, [R6,#0xC]\n"
                 "LDR     R2, =0xFF8487C4\n"     // "JogDial.c"
                 "MOV     R1, #0\n"
                 "BL      sub_FF827638\n"
                 "MOV     R0, #0x28\n"
                 "BL      sub_FF827490\n"        // eventproc_export_SleepTask ; LOCATION: KerSys.c:0
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
                 "BEQ     loc_FF848650\n"
                 "MOV     R5, R1\n"
                 "RSBLT   R5, R5, #0\n"
                 "MOVLE   R4, #0\n"
                 "MOVGT   R4, #1\n"
                 "CMP     R5, #0xFF\n"
                 "BLS     loc_FF848604\n"
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
"loc_FF848604:\n"
                 "LDR     R0, [R6,#0x14]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF848648\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF848630\n"
                 "LDR     R1, [R8,R4,LSL#2]\n"
                 "CMP     R1, R0\n"
                 "BEQ     loc_FF848638\n"
                 "LDR     R0, =0xB01\n"
                 "BL      sub_FF87B9B8\n"
"loc_FF848630:\n"
                 "MOV     R0, R11\n"
                 "BL      sub_FF87B9B8\n"
"loc_FF848638:\n"
                 "LDR     R0, [R8,R4,LSL#2]\n"
                 " MOV     R1, R5\n"
                 "STR     R0, [R6,#0x1C]\n"
                 "BL      sub_FF87B8E8\n"
"loc_FF848648:\n"
                 "LDRH    R0, [R6]\n"
                 "STRH    R0, [R6,#2]\n"
"loc_FF848650:\n"
                 "STR     R10, [R7,#0x100]\n"
                 "STR     R9, [R7,#0x108]\n"
                 "LDR     R0, [R6,#0x10]\n"
                 "CMP     R0, #0\n"
                 "BLNE    sub_FF827490\n"        // eventproc_export_SleepTask ; LOCATION: KerSys.c:0
                 "B       loc_FF84858C\n"
 );
}

