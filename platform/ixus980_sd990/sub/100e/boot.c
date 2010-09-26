#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_spytask();
void JogDial_task_my(void);
void boot();

void taskCreateHook(int *p) { 
 p-=17;
// if (p[0]==0x)  p[0]=(int)capt_seq_task;
 if (p[0]==0xFF862148)  p[0]=(int)movie_record_task;
// task_InitFileModules
 if (p[0]==0xFF881534)  p[0]=(int)init_file_modules_task;
 if (p[0]==0xFF84A480)  p[0]=(int)JogDial_task_my;;
}
// ??? from sx10
void taskCreateHook2(int *p) {
 p-=17;
 if (p[0]==0xFF881534)  p[0]=(int)init_file_modules_task;
}


#define DEBUG_LED 0xC02200BC
void boot() { //#fs
    long *canon_data_src = (void*)0xFFB74B98;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xFE80 - 0x1900; // data_end - data_start
    long *canon_bss_start = (void*)0xFE80; // just after data 
    long canon_bss_len = 0xE8B40 - 0xFE80; 

    long i;


    // enable caches and write buffer, disabled earlier in loader 
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
    *(int*)0x1930=(int)taskCreateHook;
    *(int*)0x1934=(int)taskCreateHook2;

	// similar to SX10 (but no +4 and values are >> 8) via sub_FF849EB0. 
	// Search on 0x12345678 finds function called by this
    *(int*)(0x2588)= (*(int*)0xC02200F8)&1 ? 0x200000 : 0x100000; // replacement of sub_FF8219D8 for correct power-on.

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
"                BL      sub_FF810F94_my\n" //->
        );
}

void __attribute__((naked,noinline)) sub_FF810F94_my() {
	asm volatile (
"                 STR     LR, [SP,#-4]!\n"
"                 SUB     SP, SP, #0x74\n"
"                 MOV     R0, SP\n"
"                 MOV     R1, #0x74\n"
"                 BL      sub_FFADE438\n"
"                 MOV     R0, #0x53000\n"
"                 STR     R0, [SP,#4]\n"
//"                 LDR     R0, =0xE8B40\n"
              "LDR     R0, =new_sa\n"
              "LDR     R0, [R0]\n"
"                 LDR     R2, =0x379C00\n"
"                 LDR     R1, =0x3724A8\n"
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
//"                 LDR     R1, =sub_FF814D8C\n"
"                 LDR     R1, =sub_FF814D8C_my\n"
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
"                 BL      sub_FF812D38\n"
"                 ADD     SP, SP, #0x74\n"
"                 LDR     PC, [SP],#4\n"
	);
}

void __attribute__((naked,noinline)) sub_FF814D8C_my() {
	asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 BL      sub_FF810940\n"
"                 BL      sub_FF81901C\n" // dmSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF814EA0\n" // "dmSetup"
"                 BLLT    sub_FF814E80\n" // err_init_task
"                 BL      sub_FF8149B4\n"
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF814EA8\n" // "termDriverInit"
"                 BLLT    sub_FF814E80\n" // err_init_task
"                 LDR     R0, =0xFF814EB8\n" // "/_term"
"                 BL      sub_FF814A9C\n" // termDeviceCreate
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF814EC0\n" // "termDeviceCreate"
"                 BLLT    sub_FF814E80\n" // err_init_task
"                 LDR     R0, =0xFF814EB8\n" // "/_term"
"                 BL      sub_FF813548\n" // stdioSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF814ED4\n" // "stdioSetup"
"                 BLLT    sub_FF814E80\n" // err_init_task
"                 BL      sub_FF818BA4\n" // stdlibSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF814EE0\n" // "stdlibSetup"
"                 BLLT    sub_FF814E80\n" // err_init_task
"                 BL      sub_FF811478\n"
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF814EEC\n" // "armlib_setup"
"                 BLLT    sub_FF814E80\n" // err_init_task
"                 LDMFD   SP!, {R4,LR}\n"
"                 B       taskcreate_Startup_my\n" // ->
	);
}

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
	asm volatile (
"                STMFD   SP!, {R3,LR}\n"
"                BL      sub_FF8219D0\n"
"                BL      sub_FF8298A8\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF81C1E0\n"
"                BL      sub_FF8219CC\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF81C1E0\n"
"                BL      sub_FF821138\n"
"                LDR     R1, =0xC0220000\n"
"                MOV     R0, #0x44\n"
"                STR     R0, [R1,#0x1C]\n"
"                BL      sub_FF821328\n"
"loc_FF81C1DC:\n"
"                B       loc_FF81C1DC\n"
"loc_FF81C1E0:\n"
//"                BL      sub_FF8219D8\n" // removed for correct power-on on 'on/off' button.
"                BL      sub_FF8219D4\n"
"                BL      sub_FF827A38\n"
"                LDR     R1, =0x3CE000\n"
"                MOV     R0, #0\n"
"                BL      sub_FF827E80\n"
"                BL      sub_FF827C2C\n" // LOCATION: KerSys.c:548
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =task_Startup_my\n" // ->
"                MOV     R2, #0\n"
"                MOV     R1, #0x19\n"
"                LDR     R0, =0xFF81C228\n"  // "Startup"
"                BL      sub_FF81AEF4\n" // eventproc_export_CreateTask ; LOCATION: KerTask.c:163\n"
"                MOV     R0, #0\n"
"                LDMFD   SP!, {R12,PC}\n"
	);
}
void CreateTask_blinker();
void __attribute__((naked,noinline)) task_Startup_my() {
	asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 BL      sub_FF8153CC\n" // taskcreate_ClockSave
"                 BL      sub_FF822B34\n"
"                 BL      sub_FF820E0C\n" // j_nullsub
"                 BL      sub_FF8298E8\n"
"                 BL      sub_FF829AB0\n"
//"                 BL      sub_FF829970\n" // diskboot
        );

       CreateTask_spytask();
//       CreateTask_blinker();

        asm volatile (
"                 BL      sub_FF829C68\n"
"                 BL      sub_FF81FAA0\n"
"                 BL      sub_FF829B00\n"
"                 BL      sub_FF827038\n"
"                 BL      sub_FF829C6C\n"
        );

//        CreateTask_PhySw(); // not here, next call does this and jogdial

        asm volatile (
"                 BL      sub_FF8218C8_my\n"// taskcreate_PhySw ->
"                 BL      sub_FF824A80_my\n" // taskcreate_SsTask -> for shoot seq stuff
"                 BL      sub_FF829C84\n"
//"                 BL      sub_FF81EEF8\n" // nullsub
"                 BL      sub_FF820724\n"
"                 BL      sub_FF829684\n" // taskcreate_Bye
"                 BL      sub_FF820DBC\n"
"                 BL      sub_FF820630\n" // taskcreate_TempCheck
"                 BL      sub_FF81FAD4\n"
"                 BL      sub_FF82A7E0\n"
"                 BL      sub_FF820608\n"
"                 LDMFD   SP!, {R4,LR}\n"
"                 B       sub_FF815490\n" // _sub_FF815490__MLHClock_c__0 ; LOCATION: MLHClock.c:0
	);
}

void __attribute__((naked,noinline)) sub_FF824A80_my() {
asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 LDR     R4, =0x1C3C\n"
"                 MOV     R0, #0\n"
"                 MOV     R1, #4\n"
"                 STR     R0, [R4,#0xC]\n"
"                 BL      sub_FF827CD8\n" // KernelMisc.c:43
"                 STR     R0, [R4,#4]\n"
"                 MOV     R0, #0\n"
"                 MOV     R1, #1\n"
"                 BL      sub_FF827CFC\n" //  KernelMisc.c:55
"                 STR     R0, [R4,#8]\n"
"                 BL      sub_FF869E44\n"
"                 BL      sub_FF86B618\n" // -> taskcreate_SsTask
"                 BL      sub_FF868DC4\n"
"                 BL      sub_FF864BE8_my\n"
"                 BL      sub_FF86A124\n"
"                 LDR     R0, [R4,#4]\n"
"                 LDMFD   SP!, {R4,LR}\n"
"                 MOV     R1, #0x1000\n"
"                 B       sub_FF86E084\n"
	);
}

void __attribute__((naked,noinline)) sub_FF864BE8_my() {
	asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                LDR     R4, =0x54B8\n"
"                LDR     R0, [R4]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF864C54\n"
"                BL      sub_FF867F5C\n" // nullsub
"                MOV     R1, #1\n"
"                MOV     R0, #0\n"
"                BL      sub_FF827CFC\n" // KernelMisc.c:55
"                STR     R0, [R4,#0xC]\n"
"                MOV     R0, #0\n"
"                MOV     R1, #0\n"
"                BL      sub_FF827CD8\n" // KernelMisc.c:43
"                STR     R0, [R4,#0x10]\n"
"                BL      sub_FF864F98\n"
"                BL      sub_FF86545C\n"
"                MOV     R0, #0\n"
"                STR     R0, [R4,#8]\n"
"                ADD     R0, R4, #0x14\n"
"                MOV     R1, #0\n"
"                STR     R1, [R0],#4\n"
"                STR     R1, [R0]\n"
"                BL      sub_FF865664\n"
"                BL      sub_FF86A32C\n"
"                BL      sub_FF868348\n"
"                BL      sub_FF8661F8_my\n" // ->taskcreate_CaptSeqTask
"                BL      sub_FF8671D0\n"
"loc_FF864C54:\n"
"                MOV     R0, #1\n"
"                STR     R0, [R4]\n"
"                LDMFD   SP!, {R4,PC}\n"
	);
}
void __attribute__((naked,noinline)) sub_FF8661F8_my() {
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R2, =0x1B194\n"
"                MOV     R0, #0\n"
"                MOV     R1, #0\n"
"loc_FF866208:\n"
"                ADD     R3, R2, R0,LSL#4\n"
"                ADD     R0, R0, #1\n"
"                CMP     R0, #5\n"
"                STR     R1, [R3,#8]\n"
"                BCC     loc_FF866208\n"
"                BL      sub_FF866CF8\n"
"                BL      sub_FF93E9F0\n"
"                MOV     R1, #5\n"
"                MOV     R0, #0\n"
"                BL      sub_FF827CB4\n" // KernelMisc.c:31
"                LDR     R4, =0x54EC\n"
"                LDR     R1, =0x101DFF\n"
"                STR     R0, [R4,#0xC]\n"
"                MOV     R0, #0\n"
"                BL      sub_FF827CD8\n" // KernelMisc.c:43
"                STR     R0, [R4,#8]\n"
"                MOV     R0, #0\n"
"                MOV     R1, #1\n"
"                BL      sub_FF827CFC\n" // KernelMisc.c:55
"                STR     R0, [R4,#0x10]\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =task_CaptSeqTask_my\n"
"                LDR     R0, =0xFF866450\n" // "CaptSeqTask"
"                MOV     R2, #0x1000\n"
"                MOV     R1, #0x17\n"
"                BL      sub_FF827C80\n"// KernelCreateTask ; LOCATION: KernelMisc.c:19
"                LDMFD   SP!, {R3-R5,PC}\n"
	);
}

void __attribute__((naked,noinline)) sub_FF8218C8_my() {
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R4, =0x1C1C\n"
"                LDR     R0, [R4,#0x10]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF8218FC\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
//"                LDR     R3, =0xFF821894\n" // task_PhySw
"                LDR     R3, =mykbd_task\n" // task_PhySw
//"                MOV     R2, #0x800\n"
"                MOV     R2, #0x2000\n" // stack size for new task_PhySw so we don't have to do stack switch
"                MOV     R1, #0x17\n"
"                LDR     R0, =0xFF821AD0\n" // "PhySw"
"                BL      sub_FF827C80\n" // KernelCreateTask
"                STR     R0, [R4,#0x10]\n"
"loc_FF8218FC:\n"
"                BL      sub_FF84A57C\n"// taskcreate_JogDial
"                BL      sub_FF874848\n"
"                BL      sub_FF84DD9C\n" // IsFactoryMode
"                CMP     R0, #0\n"
"                LDREQ   R1, =0x11324\n"
"                LDMEQFD SP!, {R3-R5,LR}\n"
"                BEQ     sub_FF874788\n" // eventproc_export_OpLog_Start
"                LDMFD   SP!, {R3-R5,PC}\n"
	);
}

void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

void __attribute__((naked,noinline)) init_file_modules_task() { 
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 BL      sub_FF876BF8\n"
"                 LDR     R5, =0x5006\n"
"                 MOVS    R4, R0\n"
"                 MOVNE   R1, #0\n"
"                 MOVNE   R0, R5\n"
"                 BLNE    sub_FF87B8A4\n"// PostLogicalEventToUI
"                 BL      sub_FF876C24_my\n" // ->
"                 BL      core_spytask_can_start\n" // + safe to start spytask
"                 CMP     R4, #0\n"
"                 MOVEQ   R0, R5\n"
"                 LDMEQFD SP!, {R4-R6,LR}\n"
"                 MOVEQ   R1, #0\n"
"                 BEQ     sub_FF87B8A4\n" // PostLogicalEventToUI
"                 LDMFD   SP!, {R4-R6,PC}\n"
 );
} 

void __attribute__((naked,noinline)) sub_FF876C24_my() { 
  asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 BL      sub_FF8592B8_my\n" // ->
//"                 BL      nullsub_93\n"
"                 LDR     R4, =0x5824\n"
"                 LDR     R0, [R4,#4]\n"
"                 CMP     R0, #0\n"
"                 BNE     loc_FF876C58\n"
"                 BL      sub_FF858780\n"
"                 BL      sub_FF909EBC\n"
"                 BL      sub_FF858780\n"
"                 BL      sub_FF854654\n"
"                 BL      sub_FF858680\n"
"                 BL      sub_FF909F88\n"
"loc_FF876C58:\n"
"                 MOV     R0, #1\n"
"                 STR     R0, [R4]\n"
"                 LDMFD   SP!, {R4,PC}\n"
 );
} 

void __attribute__((naked,noinline)) sub_FF8592B8_my() { 
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 MOV     R6, #0\n"
"                 MOV     R0, R6\n"
"                 BL      sub_FF858D78\n"
"                 LDR     R4, =0x19BC8\n"
"                 MOV     R5, #0\n"
"                 LDR     R0, [R4,#0x38]\n"
"                 BL      sub_FF8597D8\n"
"                 CMP     R0, #0\n"
"                 LDREQ   R0, =0x2A20\n"
"                 STREQ   R5, [R0,#0x10]\n"
"                 STREQ   R5, [R0,#0x14]\n"
"                 STREQ   R5, [R0,#0x18]\n"
"                 MOV     R0, R6\n"
"                 BL      sub_FF858DB8\n" // LOCATION: Mounter.c:824
"                 MOV     R0, R6\n"
"                 BL      sub_FF8590F4_my\n" // ->
"                 MOV     R5, R0\n"
"                 MOV     R0, R6\n"
"                 BL      sub_FF859160\n" // LOCATION: Mounter.c:8
"                 LDR     R1, [R4,#0x3C]\n"
"                 AND     R2, R5, R0\n"
"                 CMP     R1, #0\n"
"                 MOV     R0, #0\n"
"                 MOVEQ   R0, #0x80000001\n"
"                 BEQ     loc_FF85934C\n"
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
"loc_FF85934C:\n"
"                 STR     R0, [R4,#0x40]\n"
"                 LDMFD   SP!, {R4-R6,PC}\n"
 );
} 

void __attribute__((naked,noinline)) sub_FF8590F4_my() { 
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 LDR     R5, =0x2A20\n"
"                 MOV     R6, R0\n"
"                 LDR     R0, [R5,#0x14]\n"
"                 CMP     R0, #0\n"
"                 MOVNE   R0, #1\n"
"                 LDMNEFD SP!, {R4-R6,PC}\n"
"                 MOV     R0, #0x17\n"
"                 MUL     R1, R0, R6\n"
"                 LDR     R0, =0x19BC8\n"
"                 ADD     R4, R0, R1,LSL#2\n"
"                 LDR     R0, [R4,#0x38]\n"
"                 MOV     R1, R6\n"
"                 BL      sub_FF858E84_my\n" // -> was Mounter.c
"                 CMP     R0, #0\n"
"                 LDMEQFD SP!, {R4-R6,PC}\n"
"                 LDR     R0, [R4,#0x38]\n"
"                 MOV     R1, R6\n"
"                 BL      sub_FF858FEC\n" // LOCATION: Mounter.c:0
"                 CMP     R0, #0\n"
"                 LDMEQFD SP!, {R4-R6,PC}\n"
"                 MOV     R0, R6\n"
"                 BL      sub_FF858980\n"
"                 CMP     R0, #0\n"
"                 MOVNE   R1, #1\n"
"                 STRNE   R1, [R5,#0x14]\n"
"                 LDMFD   SP!, {R4-R6,PC}\n"
  );
}

void __attribute__((naked,noinline)) sub_FF858E84_my() { 
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
"                 BLX     R12\n"
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

void __attribute__((naked,noinline)) JogDial_task_my() { 
  asm volatile (
"                STMFD   SP!, {R3-R11,LR}\n"
"                BL      sub_FF84A630\n" //__JogDial_c__14 ; LOCATION: JogDial.c:14
"                LDR     R11, =0x80000B01\n"
"                LDR     R8, =0xFFAE872C\n"
"                LDR     R7, =0xC0240000\n"
"                LDR     R6, =0x2594\n"
"                MOV     R9, #1\n"
"                MOV     R10, #0\n"
"loc_FF84A4A0:\n"
"                LDR     R3, =0x1AE\n"
"                LDR     R0, [R6,#0xC]\n"
"                LDR     R2, =0xFF84A6D8\n" // ; "JogDial.c"
"                MOV     R1, #0\n"
"                BL      sub_FF827D68\n"  //  ; take semaphore or assert
"                MOV     R0, #0x28\n"
"                BL      sub_FF827BC0\n" // eventproc_export_SleepTask ; LOCATION: KerSys.c:0
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

"                LDR     R0, [R7,#0x104]\n"
"                MOV     R0, R0,ASR#16\n"
"                STRH    R0, [R6]\n"
"                LDRSH   R2, [R6,#2]\n"
"                SUB     R1, R0, R2\n"
"                CMP     R1, #0\n"
"                BEQ     loc_FF84A564\n"
"                MOV     R5, R1\n"
"                RSBLT   R5, R5, #0\n"
"                MOVLE   R4, #0\n"
"                MOVGT   R4, #1\n"
"                CMP     R5, #0xFF\n"
"                BLS     loc_FF84A518\n"
"                CMP     R1, #0\n"
"                RSBLE   R1, R2, #0xFF\n"
"                ADDLE   R1, R1, #0x7F00\n"
"                ADDLE   R0, R1, R0\n"
"                RSBGT   R0, R0, #0xFF\n"
"                ADDGT   R0, R0, #0x7F00\n"
"                ADDGT   R0, R0, R2\n"
"                ADD     R5, R0, #0x8000\n"
"                ADD     R5, R5, #1\n"
"                EOR     R4, R4, #1\n"
"loc_FF84A518:\n"
"                LDR     R0, [R6,#0x14]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF84A55C\n"
"                LDR     R0, [R6,#0x1C]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF84A544\n"
"                LDR     R1, [R8,R4,LSL#2]\n"
"                CMP     R1, R0\n"
"                BEQ     loc_FF84A54C\n"
"                LDR     R0, =0xB01\n"
"                BL      sub_FF87D754\n"
"loc_FF84A544:\n"
"                MOV     R0, R11\n"
"                BL      sub_FF87D754\n"
"loc_FF84A54C:\n"
"                LDR     R0, [R8,R4,LSL#2]\n"
"                MOV     R1, R5\n"
"                STR     R0, [R6,#0x1C]\n"
"                BL      sub_FF87D69C\n"
"loc_FF84A55C:\n"
"                LDRH    R0, [R6]\n"
"                STRH    R0, [R6,#2]\n"
"loc_FF84A564:\n"
"                STR     R10, [R7,#0x100]\n"
"                STR     R9, [R7,#0x108]\n"
"                LDR     R0, [R6,#0x10]\n"
"                CMP     R0, #0\n"
"                BLNE    sub_FF827BC0\n" // eventproc_export_SleepTask ; LOCATION: KerSys.c:0
"                B       loc_FF84A4A0\n"
  );
}


#if 0
const unsigned ledlist[]={
	0xC0220134, // green
	0xC0220130, // orange (right)
	0xC0220138, // yellow (left)
	0xC02200B0, // power
	0xC02200BC, // dp
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
						led=(void *)ledlist[(++i_led)%5];
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

