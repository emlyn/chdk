#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Our stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_blinker();
void CreateTask_PhySw();
void CreateTask_spytask();

void boot();
void __attribute__((naked,noinline)) task_blinker();
void dump_chdk();

void taskCreateHook(int *p) { 
 p-=16;
 if (p[0]==0xFF862E48)  p[0]=(int)movie_record_task;
}

////////////////////////////////////////////////////////////////////////////////
// Note to developers:
// The code below is just somewhat annotated in an attempt to figure out what
// the camera does. I left it in, it might be of some use to someone someday.
// Occasionally, I added the .ltorg directive, because the compiler/assembler
// isn't smart enough to place it somewhere sensible. Remember to bypass
// (B new_location) that directive if you really *MUST* place it in the middle
// of your code.
////////////////////////////////////////////////////////////////////////////////


#define DEBUG_LED 0xC02200D4 // Red led (lower-right corner) normally indicating SD read/write

void boot() {

    asm volatile ("B      sub_FF81000C_my\n");

};


void __attribute__((naked,noinline)) sub_FF81000C_my() {
     asm volatile (
          "LDR     R1, =0xC0400004\n"
          "LDR     R2, [R1]\n"
          "ORR     R2, R2, #2\n"
          "STR     R2, [R1]\n"
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
          "LDR     R0, =0x10000033\n"
          "MCR     p15, 0, R0,c6,c3\n"
          "MOV     R0, #0x40000017\n"
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
          "MOV     R1, #0x40000006\n"
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
          "LDR     R0, =0xFFB07EB8\n"
          "LDR     R1, =0x1900\n"
          "LDR     R3, =0x1056C\n"

     "loc_FF81014C:\n"
          "CMP     R1, R3\n"                     // Copy code from 0xFFB07EB8(inc) onwards to 0x1900(inc) .. 0x1056C (ex)
          "LDRCC   R2, [R0],#4\n"
          "STRCC   R2, [R1],#4\n"
          "BCC     loc_FF81014C\n"               // loop
          "LDR     R1, =0x9B610\n"
          "MOV     R2, #0\n"

     "loc_FF810164:\n"
          "CMP     R3, R1\n"                     // Zerofill from 0x1056C(inc) .. 0x9B610(exc)
          "STRCC   R2, [R3],#4\n"
          "BCC     loc_FF810164\n"               // loop
//          "B       sub_FF8101B8\n"
          "B       sub_FF8101B8_my\n"            // +---------------------> Hook
     ".ltorg\n"
     );
}


void __attribute__((naked,noinline)) sub_FF8101B8_my() {
     *(int*)0x1930=(int)taskCreateHook;
     asm volatile (
     "loc_FF8101B8:\n"
          "LDR     R0, =0xFF810230\n"
          "MOV     R1, #0\n"
          "LDR     R3, =0xFF810268\n"

     "loc_FF8101C4:\n"
          "CMP     R0, R3\n"                     // Copy code from 0xFF810230(inc) .. 0xFF810268(exc) to 0x0 .. 0x38
          "LDRCC   R2, [R0],#4\n"
          "STRCC   R2, [R1],#4\n"
          "BCC     loc_FF8101C4\n"               // loop
          "LDR     R0, =0xFF810268\n"
          "MOV     R1, #0x4B0\n"
          "LDR     R3, =0xFF81047C\n"

     "loc_FF8101E0:\n"
          "CMP     R0, R3\n"                     // Copy code from 0xFF810268(inc) .. 0xFF81047C(exc) to 0x4B0 .. 0x6C4
          "LDRCC   R2, [R0],#4\n"
          "STRCC   R2, [R1],#4\n"
          "BCC     loc_FF8101E0\n"               // loop
          "MOV     R0, #0xD2\n"
          "MSR     CPSR_cxsf, R0\n"
          "MOV     SP, #0x1000\n"
          "MOV     R0, #0xD3\n"
          "MSR     CPSR_cxsf, R0\n"
          "MOV     SP, #0x1000\n"
          "LDR     R0, =0x6C4\n"
          "LDR     R2, =0xEEEEEEEE\n"
          "MOV     R3, #0x1000\n"

     "loc_FF810214:\n"
          "CMP     R0, R3\n"                     // Fill 0x6C4 .. 0x1000 with 0xEEEEEEEE
          "STRCC   R2, [R0],#4\n"
          "BCC     loc_FF810214\n"               // loop
//          "BL      sub_FF810FCC\n"
          "BL      sub_FF810FCC_my\n"            // +---------------------> Hook
     ".ltorg\n"
     );
}

void __attribute__((naked,noinline)) sub_FF810FCC_my() {
     asm volatile (
          "STR     LR, [SP,#-0x4]!\n"
          "SUB     SP, SP, #0x74\n"
          "MOV     R0, SP\n"
          "MOV     R1, #0x74\n"
          "BL      sub_FFA92C10\n"
          "MOV     R0, #0x53000\n"
          "STR     R0, [SP,#0x74-0x70]\n"
//          "LDR     R0, =0x9B610\n"
          );    
//          "LDR     R0, =0xDB610\n"			// 0x9B610 + 0x40000 (memsize) = 0xDB610
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
//          "STRD    R0, [SP,#0x74-0x54]\n"  // WORKSFORME, configure gcc WITHOUT --with-cpu=arm9
          "STR    R0, [SP,#0x74-0x54]\n"     // Though use the old, 2-line version
          "STR    R1, [SP,#0x74-0x50]\n"     // for the final until everyone uses 'new' gcc
          "MOV     R0, #0x78\n"
//          "STRD    R0, [SP,#0x74-0x4C]\n"  // Idem
          "STR    R0, [SP,#0x74-0x4C]\n"     // Idem
          "STR    R1, [SP,#0x74-0x48]\n"     // Idem
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
//          "LDR     R1, =sub_FF814E0C\n"
          "LDR     R1, =sub_FF814E0C_my\n"       // +---------------------> Hook
          "MOV     R0, SP\n"
          "MOV     R2, #0\n"
          "BL      sub_FF812D84\n"
          "ADD     SP, SP, #0x74\n"
          "LDR     PC, [SP],#4\n"
     ".ltorg\n"
     );
}


void __attribute__((naked,noinline)) sub_FF814E0C_my() {
        asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FF810970\n"
              "BL      sub_FF8197D0\n"           // dmSetup
              "CMP     R0, #0\n"
//              "ADRLT   R0, aDmsetup\n"
              "LDRLT   R0, =0xFF814F20\n"
              "BLLT    sub_FF814F00\n"           // err_init_task
              "BL      sub_FF814A30\n"           // termDriverInit
              "CMP     R0, #0\n"
//              "ADRLT   R0, aTermdriverinit\n" 
              "LDRLT   R0, =0xFF814F28\n"
              "BLLT    sub_FF814F00\n"           // err_init_task
//              "ADR     R0, a_term\n"
              "LDR     R0, =0xFF814F38\n"
              "BL      sub_FF814B1C\n"           // termDeviceCreate
              "CMP     R0, #0\n"
//              "ADRLT   R0, aTermdevicecrea\n"
              "LDRLT   R0, =0xFF814F40\n"
              "BLLT    sub_FF814F00\n"           // err_init_task
//              "ADR     R0, a_term\n"
              "LDR     R0, =0xFF814F38\n"
              "BL      sub_FF813594\n"           // stdioSetup
              "CMP     R0, #0\n"
//              "ADRLT   R0, aStdiosetup\n"
              "LDRLT   R0, =0xFF814F54\n"
              "BLLT    sub_FF814F00\n"           // err_init_task
              "BL      sub_FF8194B8\n"           // stdlibSetup
              "CMP     R0, #0\n"
//              "ADRLT   R0, aStdlibsetup\n"
              "LDRLT   R0, =0xFF814F60\n"
              "BLLT    sub_FF814F00\n"           // err_init_task
              "BL      sub_FF8114E4\n"           // armlib_setup
              "CMP     R0, #0\n"
//              "ADRLT   R0, aArmlib_setup\n"
              "LDRLT   R0, =0xFF814F6C\n"
              "BLLT    sub_FF814F00\n"           // err_init_task
              "LDMFD   SP!, {R4,LR}\n"
              //"B       sub_FF81D9F0\n"         // CreateTaskStartup
              "B       sub_FF81D9F0_my\n"        // +---------------------> Hook
     ".ltorg\n"
        );
};


void __attribute__((naked,noinline)) sub_FF81D9F0_my() {
     asm volatile (
          "STMFD   SP!, {R3,LR}\n"
          "BL      sub_FF82CE28\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF81DA2C\n"
          "BL      sub_FF824D04\n"
          "CMP     R0, #0\n"
          "LDREQ   R2, =0xC0220000\n"
          "LDREQ   R0, [R2,#0x10C]\n"
          "LDREQ   R1, [R2,#0x108]\n"
          "ORREQ   R0, R0, R1\n"
          "TSTEQ   R0, #1\n"
          "BNE     loc_FF81DA2C\n"
          "MOV     R0, #0x44\n"
          "STR     R0, [R2,#0x4C]\n"

     "loc_FF81DA28:\n"
          "B       loc_FF81DA28\n"


     "loc_FF81DA2C:\n"
          "BL      sub_FF823630\n"
          "BL      sub_FF82A9D0\n"
          "MOV     R1, #0x300000\n"
          "MOV     R0, #0\n"
          "BL      sub_FF82AC18\n"
          "BL      sub_FF82ABC4\n"
          "MOV     R3, #0\n"
          "STR     R3, [SP,#8-8]\n"
//          "LDR     R3, sub_FF81D950\n"         // Startup, 0xFF81D950
          "LDR     R3, =sub_FF81D950_my\n"       // +---------------------> Hook
          "MOV     R2, #0\n"
          "MOV     R1, #0x19\n"
//          "ADR     R0, aStartup\n"
          "LDR     R0, =0xFF81DA7C\n"
          "BL      sub_FF81B8FC\n"               // CreateTask
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R12,PC}\n"
     ".ltorg\n"
     );
}

void __attribute__((naked,noinline)) sub_FF81D950_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FF8151CC\n"
          "BL      sub_FF824778\n"
          "BL      sub_FF820D4C\n"
          //"BL      j_nullsub_163\n"            
          "BL      sub_FF82D018\n"
//          "BL      sub_FF82CF00\n"            // Apparently responsible for
                                                // diskboot. Bypassing it does
                                                // not seem to affect the camera
                                                // negatively.
     );
     
     CreateTask_spytask();
     
     asm volatile (
          "LDR     R4, =0x66A8\n"
          "B       loc_FF81D97C\n"

     "loc_FF81D974:\n"
          "SUBS    R4, R4, #1\n"
          "BEQ     loc_FF81D98C\n"

     "loc_FF81D97C:\n"
          "MOV     R0, #5\n"
          "BL      sub_FF820E54\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF81D974\n"

     "loc_FF81D98C:\n"
          "MOV     R0, #5\n"
          "BL      sub_FF82124C\n"
          "SUBS    R12, R0, #0x300\n"
          "SUBGES  R12, R12, #0xF6\n"
          "BLE     loc_FF81D9B0\n"
          "BL      sub_FF829F0C\n"
          "MOV     R1, #0xB5\n"
//          "ADR     R0, aStartup_c\n"
          "LDR     R0, =0xFF81DA6C\n"
          "BL      sub_FF81BCCC\n"               // Assert, 0xFF81BCCC

     "loc_FF81D9B0:\n"
          "BL      sub_FF82DABC\n"
          "BL      sub_FF82D068\n"
          "BL      sub_FF829F0C\n"
          "BL      sub_FF82DACC\n"
          //"BL      sub_FF8235D4\n"             // PhySw, bypass and create own
     );

     CreateTask_PhySw();

     asm volatile (
//          "BL      sub_FF826988\n"             // CaptSeqTask and lots of other stuff
          "BL      sub_FF826988_my\n"            // +---------------------> Hook (in capt_seq.c)
          "BL      sub_FF82DAEC\n"
          //"BL      nullsub_2\n"
          "BL      sub_FF822998\n"
          "BL      sub_FF82CBF4\n"
          "BL      sub_FF8230C0\n"
          "BL      sub_FF8228A4\n"
          //"BL      sub_FF82E570\n"
          "BL      sub_FF82E570_my\n"            // +---> MAJOR HOOK (SDHC boot)
          "BL      sub_FF822728\n"
          "LDMFD   SP!, {R4,LR}\n"
          "B       sub_FF8150D8\n"
     ".ltorg\n"
     );
}


/////////////////////////////////////////////////////////////////////////////////////
// Major SDHC boot fix hook starts here
//
// Paths that certainly do not (by itself) get the SDHC booting going:
// sub_FF82E570 -> sub_FF824D18 -> sub_FF824A60 -> sub_FF87BF78 (entire 'right subtree')
// sub_FF82E570 -> sub_FF82E120 -> sub_FF87AC88 -> sub_FF87A340 -> sub_FF87BF78 (shortest path (subroutine-count-wise) through 'left subtree')
// sub_FF82E570 -> sub_FF82E120 -> sub_FF87AC88 -> sub_FF87A80C -> sub_FF87A340 -> sub_FF87BF78 (sub_FF87A80C does not appear to be called)
// 
// Unexplored:
// sub_FF82E570 -> sub_FF82E120 -> sub_FF87BD48 -> sub_FF87BB94 -> sub_FF87AC88 ->              -> sub_FF87A340 -> sub_FF87BF78
//                                                                              -> sub_FF87A80C ->
//
// Final, working path:
// sub_FF82E570 -> sub_FF82E120 -> sub_FF87BD48 -> sub_FF87BB94 -> sub_FF87AC88 -> sub_FF87A340 -> sub_FF87BF78
//
// That's the 'tree'-part, the rest of the subroutines are just straight on down, no junctions.
// -> sub_FF87BF28 -> sub_FF874FDC -> sub_FF856910 -> sub_FF85674C -> sub_FF8565E4
/////////////////////////////////////////////////////////////////////////////////////

void __attribute__((naked,noinline)) sub_FF82E570_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FF878D88\n"
          "BL      sub_FF824CD8\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF82E590\n"
          "BL      sub_FF87C08C\n"
          "LDMFD   SP!, {R4,LR}\n"
          "B       sub_FF824D18\n"

     "loc_FF82E590:\n"
          "BL      sub_FF87AF30\n"
          "LDR     R4, =0x1E80\n"
          "LDR     R0, [R4,#4]\n"
          "CMP     R0, #0\n"
          "LDMNEFD SP!, {R4,PC}\n"
          "MOV     R1, #0\n"
          //"LDR     R0, =0xFF82E120\n"
          "LDR     R0, =sub_FF82E120_my\n"       // +----> Hook for SDHC booting
          "BL      sub_FF875938\n"
          "STR     R0, [R4,#4]\n"
          "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF82E120_my() {
     asm volatile (
          "STMFD   SP!, {R3-R11,LR}\n"
          "LDR     R6, =0x1E80\n"
          "MOV     R5, R1\n"
          "LDR     R0, [R6,#0x14]\n"
          "MOV     R4, R3\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF82E144\n"
          "BL      sub_FF8795E0\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E144:\n"
          "LDR     R12, =0x1162\n"
          "LDR     R10, =0x1005\n"
          "CMP     R5, R12\n"
          "MOV     R7, #0\n"
          "MOV     R8, #1\n"
          "BEQ     loc_FF82E4C4\n"
          "BGT     loc_FF82E28C\n"
          "LDR     R12, =0x1062\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FF82E54C\n"
          "BGT     loc_FF82E1F8\n"
          "CMP     R5, R10\n"
          "BEQ     loc_FF82E248\n"
          "BGT     loc_FF82E1D0\n"
          "SUB     R12, R5, #0x800\n"
          "SUBS    R12, R12, #3\n"
          "BEQ     loc_FF82E3CC\n"
          "SUB     R12, R5, #0x800\n"
          "SUBS    R12, R12, #0x158\n"
          "BEQ     loc_FF82E554\n"
          "LDR     R4, =0x9A3\n"
          "CMP     R5, R4\n"
          "ADD     R7, R4, #2\n"
          "CMPNE   R5, R7\n"
          "BNE     loc_FF82E4B4\n"
          "LDR     R0, [R6,#0xC]\n"
          "SUB     R12, R0, #0x8000\n"
          "SUBS    R12, R12, #2\n"
          "BEQ     loc_FF82E1C8\n"
          "LDR     R0, =0x10A5\n"
          "BL      sub_FF877A7C\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF82E4A0\n"

     "loc_FF82E1C8:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E1D0:\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0x56\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x5B\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x5E\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x61\n"
          "BNE     loc_FF82E4B4\n"
          "B       loc_FF82E54C\n"

     "loc_FF82E1F8:\n"
          "LDR     R12, =0x10AD\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FF82E4EC\n"
          "BGT     loc_FF82E250\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0x63\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x65\n"
          "BEQ     loc_FF82E54C\n"
          "SUB     R12, R5, #0x1000\n"
          "LDR     R0, =0x10A3\n"
          "SUBS    R12, R12, #0xA9\n"
          "BEQ     loc_FF82E4E0\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xAA\n"
          "BNE     loc_FF82E4B4\n"
          "BL      sub_FF877A7C\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF82E1C8\n"

     "loc_FF82E244:\n"
          "BL      sub_FF82EB04\n"

     "loc_FF82E248:\n"
          "MOV     R1, R4\n"
          "B       loc_FF82E4B8\n"

     "loc_FF82E250:\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xAE\n"
          "BEQ     loc_FF82E244\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xAF\n"
          "BEQ     loc_FF82E4EC\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xB0\n"
          "BEQ     loc_FF82E244\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xB2\n"
          "BNE     loc_FF82E4B4\n"
          "LDR     R0, =0x1008\n"
          "MOV     R1, R4\n"
          "B       loc_FF82E4BC\n"

     "loc_FF82E28C:\n"
          "LDR     R11, =0x201B\n"
          "LDR     R0, =0x1E80\n"
          "CMP     R5, R11\n"
          "LDR     R2, [R0,#0x10]!\n"
          "LDR     R1, [R0,#0x10]\n"
          "SUB     R9, R11, #0x17\n"
          "BEQ     loc_FF82E480\n"
          "BGT     loc_FF82E354\n"
          "LDR     R11, =0x116A\n"
          "CMP     R5, R11\n"
          "BEQ     loc_FF82E46C\n"
          "BGT     loc_FF82E308\n"
          "SUB     R12, R5, #0x1100\n"
          "SUBS    R12, R12, #0x63\n"
          "MOVEQ   R1, #0\n"
          "MOVEQ   R0, #0x82\n"
          "BEQ     loc_FF82E498\n"
          "SUB     R12, R5, #0x1100\n"
          "SUBS    R12, R12, #0x65\n"
          "BEQ     loc_FF82E490\n"
          "LDR     R4, =0x1168\n"
          "SUB     R12, R5, #0x1100\n"
          "SUBS    R12, R12, #0x67\n"
          "CMPNE   R5, R4\n"
          "BNE     loc_FF82E4B4\n"
          "STR     R8, [R6,#0x10]\n"
          "LDR     R6, =0x4508\n"
          "CMP     R1, #0\n"
          "BEQ     loc_FF82E45C\n"
          "BL      sub_FF879614\n"
          "B       loc_FF82E460\n"

     "loc_FF82E308:\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #2\n"
          "BEQ     loc_FF82E518\n"
          "CMP     R5, R9\n"
          "MOV     R0, R9\n"
          "BEQ     loc_FF82E524\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #5\n"
          "BEQ     loc_FF82E518\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #0x19\n"
          "BNE     loc_FF82E4B4\n"
          "CMP     R1, #0\n"
          "BEQ     loc_FF82E1C8\n"
          "CMP     R2, #0\n"
          "BNE     loc_FF82E1C8\n"

     "loc_FF82E348:\n"
          "MOV     R1, #0\n"

     "loc_FF82E34C:\n"
          "BL      sub_FF87AC88\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E354:\n"
          "LDR     R12, =0x3110\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FF82E248\n"
          "BGT     loc_FF82E39C\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #0x1D\n"
          "BEQ     loc_FF82E518\n"
          "LDR     R0, =0x2027\n"
          "CMP     R5, R0\n"
          "BEQ     loc_FF82E4F8\n"
          "SUB     R12, R5, #0x3000\n"
          "SUBS    R12, R12, #6\n"
          "BEQ     loc_FF82E248\n"
          "SUB     R12, R5, #0x3000\n"
          "SUBS    R12, R12, #0x10\n"
          "BNE     loc_FF82E4B4\n"
          "BL      sub_FF89A628\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E39C:\n"
          "SUB     R12, R5, #0x3100\n"
          "SUBS    R12, R12, #0x11\n"
          "BEQ     loc_FF82E248\n"
          "CMP     R5, #0x3140\n"
          "BEQ     loc_FF82E540\n"
          "SUB     R12, R5, #0x3200\n"
          "SUBS    R12, R12, #1\n"
          "BEQ     loc_FF82E4B4\n"
          "SUB     R12, R5, #0x3200\n"
          "SUBS    R12, R12, #2\n"
          "BEQ     loc_FF82E248\n"
          "B       loc_FF82E4B4\n"

     "loc_FF82E3CC:\n"
          "MOV     R4, #1\n"
          "MOV     R0, #2\n"
          "BL      sub_FF878E1C\n"
          "CMP     R0, #1\n"
          "MOVEQ   R4, #2\n"
          "MOV     R0, R4\n"
          "BL      sub_FF822CC4\n"
          "CMP     R0, #0\n"
          "STRNE   R8, [R6,#0x14]\n"
          "BNE     loc_FF82E428\n"
          "BL      sub_FF87F814\n"
          "BL      sub_FF87CD38\n"
          "BL      sub_FF87DBD8\n"
          "BL      sub_FF87E0E8\n"
          "BL      sub_FF87C310\n"
          "BL      sub_FF87E4E4\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF82E430\n"
          "BL      sub_FF82DE8C\n"
          "BL      sub_FF87E4D8\n"
          "MOV     R1, R0\n"
          "LDR     R0, =0x1167\n"
          "BL      sub_FF876100\n"

     "loc_FF82E428:\n"
          "MOV     R0, R7\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E430:\n"
          "BL      sub_FF826FA0\n"
          "CMP     R0, #1\n"
          "LDRNE   R0, =0x310B\n"
          "LDREQ   R0, =0x310C\n"
          "MOV     R1, #0\n"
          "BL      sub_FF876100\n"
          //"BL      sub_FF87BD48\n"
          "BL      sub_FF87BD48_my\n"            // +----> Hook for SDHC booting
          "B       loc_FF82E428\n"

     "loc_FF82E450:\n"
          "MOV     R0, R6\n"
          "BL      sub_FF8641A8\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E45C:\n"
          "BL      sub_FF826C98\n"

     "loc_FF82E460:\n"
          "CMP     R5, R4\n"
          "BNE     loc_FF82E1C8\n"
          "B       loc_FF82E450\n"

     "loc_FF82E46C:\n"
          "MOV     R0, #1\n"
          "BL      sub_FF87972C\n"
          "MOV     R1, R11\n"
          "MOV     R0, R10\n"
          "B       loc_FF82E4BC\n"

     "loc_FF82E480:\n"
          "CMP     R2, #1\n"
          "BNE     loc_FF82E248\n"
          "BL      sub_FF879614\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E490:\n"
          "MOV     R1, #0\n"
          "MOV     R0, #0x83\n"

     "loc_FF82E498:\n"
          "BL      sub_FF87E1BC\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E4A0:\n"
          "CMP     R5, R4\n"
          "STREQ   R8, [R6,#0x34]\n"
          "BEQ     loc_FF82E4B4\n"
          "CMP     R5, R7\n"
          "STREQ   R8, [R6,#0x30]\n"

     "loc_FF82E4B4:\n"
          "MOV     R1, #0\n"

     "loc_FF82E4B8:\n"
          "MOV     R0, R5\n"

     "loc_FF82E4BC:\n"
          "BL      sub_FF87AC88\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E4C4:\n"
          "BL      sub_FF882260\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF82E248\n"
          "BL      sub_FF882B70\n"
          "CMP     R0, #0\n"
          "BLEQ    sub_FF880F94\n"
          "B       loc_FF82E248\n"

     "loc_FF82E4E0:\n"
          "BL      sub_FF877A7C\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF82E1C8\n"

     "loc_FF82E4EC:\n"
          "MOV     R0, R5\n"
          "BL      sub_FF82DFAC\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E4F8:\n"
          "MOV     R1, #0\n"
          "BL      sub_FF87AC88\n"
          "MOV     R1, #0\n"
          "MOV     R0, R11\n"
          "BL      sub_FF87AC88\n"
          "MOV     R1, #0\n"
          "MOV     R0, R9\n"
          "B       loc_FF82E34C\n"

     "loc_FF82E518:\n"
          "STR     R7, [R6,#0x20]\n"
          "BL      sub_FF82E7A4\n"
          "B       loc_FF82E248\n"

     "loc_FF82E524:\n"
          "STR     R7, [R6,#0x20]\n"
          "BL      sub_FF82E7A4\n"
          "LDR     R0, [R6,#0x10]\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF82E248\n"
          "BL      sub_FF879640\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E540:\n"
          "CMP     R1, #0\n"
          "BLEQ    sub_FF82E7A4\n"
          "B       loc_FF82E1C8\n"

     "loc_FF82E54C:\n"
          "MVN     R0, #0\n"
          "B       loc_FF82E348\n"

     "loc_FF82E554:\n"
          "TST     R4, #0x80000000\n"
          "MOVNE   R0, #1\n"
          "LDMNEFD SP!, {R3-R11,PC}\n"
          "BL      sub_FF883D08\n"
          "CMP     R0, #0\n"
          "BLEQ    sub_FF829CD8\n"
          "B       loc_FF82E1C8\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87BD48_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FF82E770\n"
          "MOV     R4, R0\n"
          "BL      sub_FF87BE64\n"
          "MOV     R0, R4\n"
          "BL      sub_FF87BBF8\n"
          "BL      sub_FF82E770\n"
          "MOV     R4, R0\n"
          "LDR     R0, =0x6374\n"
          "LDR     R0, [R0]\n"
          "TST     R0, #1\n"
          "BEQ     loc_FF87BD84\n"

     "loc_FF87BD78:\n"
          "MOV     R1, R4\n"
          "MOV     R0, #2\n"
          "B       loc_FF87BDEC\n"

     "loc_FF87BD84:\n"
          "TST     R0, #0x2000\n"
          "BEQ     loc_FF87BDA0\n"
          "TST     R0, #0x200\n"
          "LDREQ   R1, =0x4004\n"
          "LDRNE   R1, =0x8002\n"
          "MOV     R0, #3\n"
          "B       loc_FF87BDEC\n"

     "loc_FF87BDA0:\n"
          "TST     R0, #0x10\n"
          "BNE     loc_FF87BD78\n"
          "TST     R0, #0x40\n"
          "BEQ     loc_FF87BDBC\n"

     "loc_FF87BDB0:\n"
          "MOV     R1, R4\n"
          "MOV     R0, #1\n"
          "B       loc_FF87BDEC\n"

     "loc_FF87BDBC:\n"
          "TST     R0, #0x20\n"
          "BEQ     loc_FF87BDD8\n"
          "TST     R0, #0x4000\n"
          "BNE     loc_FF87BDD8\n"

     "loc_FF87BDCC:\n"
          "MOV     R1, R4\n"
          "MOV     R0, #0\n"
          "B       loc_FF87BDEC\n"

     "loc_FF87BDD8:\n"
          "LDR     R1, =0x102\n"
          "BICS    R1, R1, R0\n"
          "BNE     loc_FF87BDF4\n"
          "MOV     R1, R4\n"
          "MOV     R0, #6\n"

     "loc_FF87BDEC:\n"
          "LDMFD   SP!, {R4,LR}\n"
          //"B       sub_FF87BB94\n"
          "B       sub_FF87BB94_my\n"            // +----> Hook for SDHC booting

     "loc_FF87BDF4:\n"
          "TST     R0, #0x100\n"
          "BNE     loc_FF87BD78\n"
          "TST     R0, #0x4000\n"
          "TSTEQ   R0, #0x400\n"
          "BNE     loc_FF87BDB0\n"
          "TST     R0, #0x200\n"
          "TSTEQ   R0, #2\n"
          "BNE     loc_FF87BDCC\n"
          "TST     R0, #0x40000\n"
          "BEQ     loc_FF87BD78\n"
          "TST     R0, #0x200000\n"
          "MOVEQ   R1, R4\n"
          "MOVEQ   R0, #1\n"
          //"BLEQ    sub_FF87BB94\n"
          "BLEQ    sub_FF87BB94_my\n"            // +----> Hook for SDHC booting
          "B       loc_FF87BD78\n"
     );
}


void __attribute__((naked,noinline)) sub_FF87BB94_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "MOVS    R4, R0\n"
          "MOV     R0, #1\n"
          "MOV     R5, R1\n"
          "BNE     loc_FF87BBD4\n"
          "MOV     R1, #0\n"
          "MOV     R0, #0\n"
          "BL      sub_FF878DAC\n"
          "BL      sub_FF82E770\n"
          "SUB     R12, R0, #0x1000\n"
          "SUBS    R12, R12, #0x5B\n"
          "BNE     loc_FF87BBCC\n"

     "loc_FF87BBC4:\n"
          "BL      sub_FF87BADC\n"
          "B       loc_FF87BBDC\n"

     "loc_FF87BBCC:\n"
          "BL      sub_FF87BB1C\n"
          "B       loc_FF87BBDC\n"

     "loc_FF87BBD4:\n"
          "CMP     R4, #5\n"
          "BEQ     loc_FF87BBC4\n"

     "loc_FF87BBDC:\n"
          "CMP     R0, #0\n"
          "LDREQ   R5, =0x1162\n"
          "MOVEQ   R4, #2\n"
          "MOV     R0, R4\n"
          "MOV     R1, R5\n"
          "LDMFD   SP!, {R4-R6,LR}\n"
          //"B       sub_FF87AC88\n"
          "B       sub_FF87AC88_my\n"            // +----> Hook for SDHC booting
     );
}

void __attribute__((naked,noinline)) sub_FF87AC88_my() {
     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "MOV     R8, R1\n"
          "MOV     R4, R0\n"
          "BL      sub_FF879928\n"
          "LDR     R5, =0x62AC\n"
          "MOV     R7, #1\n"
          "LDR     R0, [R5,#0x10]\n"
          "MOV     R6, #0\n"
          "CMP     R0, #0x15\n"
          "ADDLS   PC, PC, R0,LSL#2\n"
          "B       loc_FF87AF28\n"

     "loc_FF87ACB4:\n"
          "B       loc_FF87AD0C\n"

     "loc_FF87ACB8:\n"
          "B       loc_FF87AD34\n"

     "loc_FF87ACBC:\n"
          "B       loc_FF87AD78\n"

     "loc_FF87ACC0:\n"
          "B       loc_FF87ADEC\n"

     "loc_FF87ACC4:\n"
          "B       loc_FF87ADFC\n"

     "loc_FF87ACC8:\n"
          "B       loc_FF87AE08\n"

     "loc_FF87ACCC:\n"
          "B       loc_FF87AE78\n"

     "loc_FF87ACD0:\n"
          "B       loc_FF87AE88\n"

     "loc_FF87ACD4:\n"
          "B       loc_FF87AD1C\n"

     "loc_FF87ACD8:\n"
          "B       loc_FF87AD28\n"

     "loc_FF87ACDC:\n"
          "B       loc_FF87AE88\n"

     "loc_FF87ACE0:\n"
          "B       loc_FF87AD6C\n"

     "loc_FF87ACE4:\n"
          "B       loc_FF87AF28\n"

     "loc_FF87ACE8:\n"
          "B       loc_FF87AF28\n"

     "loc_FF87ACEC:\n"
          "B       loc_FF87AD84\n"

     "loc_FF87ACF0:\n"
          "B       loc_FF87AD90\n"

     "loc_FF87ACF4:\n"
          "B       loc_FF87ADC4\n"

     "loc_FF87ACF8:\n"
          "B       loc_FF87AD40\n"

     "loc_FF87ACFC:\n"
          "B       loc_FF87AF10\n"

     "loc_FF87AD00:\n"
          "B       loc_FF87AE94\n"

     "loc_FF87AD04:\n"
          "B       loc_FF87AEC4\n"

     "loc_FF87AD08:\n"
          "B       loc_FF87AEC4\n"

     "loc_FF87AD0C:\n"
          "MOV     R1, R8\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          //"B       sub_FF87A340\n"
          "B       sub_FF87A340_my\n"            // +----> Hook for SDHC booting

     "loc_FF87AD1C:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B658\n"

     "loc_FF87AD28:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87A80C\n"

     "loc_FF87AD34:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF879F08\n"

     "loc_FF87AD40:\n"
          "SUB     R12, R4, #0x1000\n"
          "SUBS    R12, R12, #0xA5\n"
          "STREQ   R7, [R5,#0x84]\n"
          "BEQ     loc_FF87AF20\n"
          "SUB     R12, R4, #0x3000\n"
          "SUBS    R12, R12, #6\n"
          "BNE     loc_FF87AF28\n"
          "MOV     R0, #0\n"
          "BL      sub_FF82DCE4\n"
          "BL      sub_FF87B57C\n"
          "B       loc_FF87AF20\n"

     "loc_FF87AD6C:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B5B8\n"

     "loc_FF87AD78:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87A104\n"

     "loc_FF87AD84:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87A9B8\n"

     "loc_FF87AD90:\n"
          "SUB     R12, R4, #0x3200\n"
          "SUBS    R12, R12, #2\n"
          "BNE     loc_FF87AF28\n"
          "MOV     R0, #3\n"
          "BL      sub_FF87980C\n"
          "MOV     R0, #8\n"
          "BL      sub_FF82DC50\n"
          "MOV     R0, #6\n"
          "BL      sub_FF84239C\n"
          "BL      sub_FF87D148\n"
          "BL      sub_FF87CFA4\n"
          "BL      sub_FF87C380\n"
          "B       loc_FF87AF20\n"

     "loc_FF87ADC4:\n"
          "SUB     R12, R4, #0x3300\n"
          "SUBS    R12, R12, #1\n"
          "BNE     loc_FF87AF28\n"
          "LDR     R0, =0x4010\n"
          "BL      sub_FF82DC50\n"
          "BL      sub_FF89EF88\n"
          "BL      sub_FF87C380\n"
          "MOV     R0, #4\n"
          "BL      sub_FF87980C\n"
          "B       loc_FF87AF20\n"

     "loc_FF87ADEC:\n"
          "MOV     R1, R8\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87AB20\n"

     "loc_FF87ADFC:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B788\n"

     "loc_FF87AE08:\n"
          "LDR     R8, =0x1182\n"
          "CMP     R4, R8\n"
          "STREQ   R7, [R5,#0xB0]\n"
          "BEQ     loc_FF87AF20\n"
          "SUB     R12, R4, #0x1100\n"
          "SUBS    R12, R12, #0x86\n"
          "BEQ     loc_FF87AE60\n"
          "SUB     R12, R4, #0x3200\n"
          "SUBS    R12, R12, #0x16\n"
          "BNE     loc_FF87AF28\n"
          "MOV     R0, #8\n"
          "BL      sub_FF82DC50\n"
          "MOV     R0, #3\n"
          "BL      sub_FF87980C\n"
          "STR     R6, [R5,#0xB4]\n"
          "LDR     R0, [R5,#0xB0]\n"
          "CMP     R0, #0\n"
          "MOVNE   R1, #0\n"
          "MOVNE   R0, R8\n"
          "STRNE   R6, [R5,#0xB0]\n"
          "BLNE    sub_FF87AB20\n"
          "B       loc_FF87AF20\n"

     "loc_FF87AE60:\n"
          "LDR     R0, [R5,#0xB4]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87AF20\n"
          "BL      sub_FF89C658\n"
          "STR     R7, [R5,#0xB4]\n"
          "B       loc_FF87AF20\n"

     "loc_FF87AE78:\n"
          "MOV     R1, R8\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B868\n"

     "loc_FF87AE88:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87A704\n"

     "loc_FF87AE94:\n"
          "LDR     R12, =0x10B0\n"
          "CMP     R4, R12\n"
          "BEQ     loc_FF87AEC0\n"
          "BGT     loc_FF87AECC\n"
          "CMP     R4, #4\n"
          "BEQ     loc_FF87AEF4\n"
          "SUB     R12, R4, #0x1000\n"
          "SUBS    R12, R12, #0xAA\n"
          "SUBNE   R12, R4, #0x1000\n"
          "SUBNES  R12, R12, #0xAE\n"
          "BNE     loc_FF87AF28\n"

     "loc_FF87AEC0:\n"
          "BL      sub_FF879508\n"

     "loc_FF87AEC4:\n"
          "MOV     R0, R6\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF87AECC:\n"
          "SUB     R12, R4, #0x2000\n"
          "SUBS    R12, R12, #4\n"
          "BEQ     loc_FF87AF08\n"
          "SUB     R12, R4, #0x5000\n"
          "SUBS    R12, R12, #1\n"
          "SUBNE   R12, R4, #0x5000\n"
          "SUBNES  R12, R12, #6\n"
          "BNE     loc_FF87AF28\n"
          "BL      sub_FF879EA8\n"
          "B       loc_FF87AF20\n"

     "loc_FF87AEF4:\n"
          "LDR     R0, [R5,#0x2C]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87AF08\n"
          "BL      sub_FF826C50\n"
          "B       loc_FF87AF20\n"

     "loc_FF87AF08:\n"
          "BL      sub_FF879540\n"
          "B       loc_FF87AF20\n"

     "loc_FF87AF10:\n"
          "SUB     R12, R4, #0x3000\n"
          "SUBS    R12, R12, #0x130\n"
          "BNE     loc_FF87AF28\n"
          "BL      sub_FF8795E0\n"

     "loc_FF87AF20:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF87AF28:\n"
          "MOV     R0, #1\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87A340_my() {
     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "LDR     R7, =0x8002\n"
          "LDR     R4, =0x62AC\n"
          "CMP     R0, #3\n"
          "MOV     R6, R1\n"
          "MOV     R5, #1\n"
          "BEQ     loc_FF87A4B4\n"
          "BGT     loc_FF87A37C\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF87A3C0\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF87A444\n"
          "CMP     R0, #2\n"
          "BNE     loc_FF87A53C\n"
          "B       loc_FF87A394\n"

     "loc_FF87A37C:\n"
          "CMP     R0, #6\n"
          "STREQ   R5, [R4,#0x28]\n"
          "BEQ     loc_FF87A4AC\n"
          "SUB     R12, R0, #0x2000\n"
          "SUBS    R12, R12, #4\n"
          "BNE     loc_FF87A53C\n"

     "loc_FF87A394:\n"
          "SUB     R12, R6, #0x1100\n"
          "SUBS    R12, R12, #0x62\n"
          "BNE     loc_FF87A3B0\n"
          "MOV     R1, R7\n"
          "MOV     R0, #0\n"
          "BL      sub_FF87E1BC\n"
          "STR     R5, [R4,#0x60]\n"

     "loc_FF87A3B0:\n"
          "BL      sub_FF87D148\n"
          "BL      sub_FF87CFA4\n"
          "BL      sub_FF879E48\n"
          "B       loc_FF87A534\n"

     "loc_FF87A3C0:\n"
          "MOV     R0, #7\n"
          "BL      sub_FF87980C\n"
          "MOV     R0, R7\n"
          "BL      sub_FF82DC50\n"
          "BL      sub_FF87BFB4\n"
          "BL      sub_FF87CE1C\n"
          "MOV     R1, R7\n"
          "MOV     R0, #0\n"
          "BL      sub_FF87E1BC\n"
          //"ADR     R1, aAcBootrec\n"             // \"AC:BootRec\"
          "LDR     R1, =0xFF87A574\n"             // \"AC:BootRec\"
          "MOV     R0, #0x20\n"
          "STR     R6, [R4,#0x18]\n"
          "BL      sub_FF872A58\n"
          //"ADR     R1, aAcInitlens\n"            // \"AC:InitLens\"
          "LDR     R1, =0xFF87A580\n"            // \"AC:InitLens\"
          "MOV     R0, #0x20\n"
          "BL      sub_FF872A58\n"
          "STR     R5, [R4,#0x28]\n"
          "BL      sub_FF82DDF8\n"
          "BL      sub_FF82DD3C\n"
          "LDR     R0, [R4,#0x1C]\n"
          "LDR     R1, [R4,#0x20]\n"
          "ORRS    R0, R0, R1\n"
          "BLNE    sub_FF87B0E4\n"
          "LDR     R0, [R4,#0x68]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87A430\n"
          "BL      sub_FF82DE68\n"
          "B       loc_FF87A438\n"

     "loc_FF87A430:\n"
          "BL      sub_FF8269E8\n"
          "BL      sub_FF82E700\n"

     "loc_FF87A438:\n"
          //"BL      sub_FF87BF78\n"
          "BL      sub_FF87BF78_my\n"            // +----> Hook for SDHC booting
          "BL      sub_FF87BFF0\n"
          "B       loc_FF87A534\n"

     "loc_FF87A444:\n"
          "MOV     R0, #8\n"
          "BL      sub_FF87980C\n"
          "BL      sub_FF87BFB4\n"
          "BL      sub_FF87CE1C\n"
          "LDR     R5, =0x4004\n"
          "MOV     R0, #0\n"
          "MOV     R1, R5\n"
          "BL      sub_FF87E1BC\n"
          //"ADR     R1, aAcBootpb\n"              // \"AC:BootPB\"
          "LDR     R1, =0xFF87A590\n"              // \"AC:BootPB\"
          "MOV     R0, #0x20\n"
          "BL      sub_FF872A58\n"
          //"BL      sub_FF87BF78\n"
          "BL      sub_FF87BF78_my\n"            // +----> Hook for SDHC booting
          "BL      sub_FF87C08C\n"
          "BL      sub_FF82E690\n"
          "MOV     R0, R5\n"
          "BL      sub_FF82DC50\n"
          "LDR     R0, [R4,#0x68]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87A498\n"
          "BL      sub_FF82DE68\n"
          "B       loc_FF87A49C\n"

     "loc_FF87A498:\n"
          "BL      sub_FF8269E8\n"

     "loc_FF87A49C:\n"
          "BL      sub_FF87C020\n"
          "LDR     R0, [R4,#0x30]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF87A534\n"

     "loc_FF87A4AC:\n"
          "BL      sub_FF87B108\n"
          "B       loc_FF87A534\n"

     "loc_FF87A4B4:\n"
          "MOV     R1, R6\n"
          "MOV     R0, #0\n"
          "BL      sub_FF87E1BC\n"
          //"ADR     R1, aAcBootclock\n"           // \"AC:BootClock\"
          "LDR     R1, =0xFF87A59C\n"           // \"AC:BootClock\"
          "MOV     R0, #0x20\n"
          "BL      sub_FF872A58\n"
          "STR     R5, [R4,#0x68]\n"
          "BL      sub_FF87C08C\n"
          "BL      sub_FF82E690\n"
          "BL      sub_FF87B0B4\n"
          "BL      sub_FF82E764\n"
          "CMP     R0, #0\n"
          "LDRNE   R0, =0x8045\n"
          "MOVNE   R1, #0\n"
          "BLNE    sub_FF8789D4\n"
          "BL      sub_FF87DFD0\n"
          "MOV     R0, #0x80\n"
          "BL      sub_FF82DC50\n"
          "BL      sub_FF87D2D8\n"
          "BL      sub_FF8B0EB4\n"
          "BL      sub_FF973218\n"
          "BL      sub_FF8AF708\n"
          "BL      sub_FF87C9E4\n"
          "BL      sub_FF87D180\n"
          "MOV     R0, #9\n"
          "BL      sub_FF87980C\n"
          "LDR     R0, =0x300E\n"
          "MOV     R1, R6\n"
          "BL      sub_FF876100\n"
          "MOV     R1, #0\n"
          "MOV     R0, #1\n"
          "BL      sub_FF87E1BC\n"

     "loc_FF87A534:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF87A53C:\n"
          "MOV     R0, #1\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87BF78_my() {
     asm volatile (

          "LDR     R0, =0x6380\n"
          "STMFD   SP!, {R3,LR}\n"
          "LDR     R1, [R0,#0x10]\n"
          "CMP     R1, #1\n"
          "BEQ     locret_FF87BFB0\n"
          "MOV     R1, #1\n"
          "STR     R1, [R0,#0x10]\n"
          "MOV     R3, #0\n"
          "STR     R3, [SP,#8-8]\n"
          //"LDR     R3, =sub_FF87BF28\n"
          "LDR     R3, =sub_FF87BF28_my\n"       // +----> Hook for SDHC booting
          "MOV     R1, #0x19\n"
          //"LDR     R0, =aInitfilemodule\n"        // \"InitFileModules\"
          "LDR     R0, =0xFF87C0F8\n"
          "MOV     R2, #0x1000\n"
          "BL      sub_FF81B8FC\n"

     "locret_FF87BFB0:\n"
          "LDMFD   SP!, {R12,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87BF28_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "BL      sub_FF874FB0\n"
          "LDR     R5, =0x5006\n"
          "MOVS    R4, R0\n"
          "MOVNE   R1, #0\n"
          "MOVNE   R0, R5\n"
          "BLNE    sub_FF876100\n"
          //"BL      sub_FF874FDC\n"
          "BL      sub_FF874FDC_my\n"            // +----> Hook for SDHC booting

          "BL      core_spytask_can_start\n"     // +----> CHDK: Set "it's-safe-to-start"-Flag for spytask

          "CMP     R4, #0\n"
          "MOVEQ   R0, R5\n"
          "LDMEQFD SP!, {R4-R6,LR}\n"
          "MOVEQ   R1, #0\n"
          "BEQ     sub_FF876100\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF874FDC_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          //"BL      sub_FF856910\n"
          "BL      sub_FF856910_my\n"            // +----> Hook for SDHC booting
          "LDR     R4, =0x5C88\n"
          "LDR     R0, [R4,#4]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87500C\n"
          "BL      sub_FF888178\n"
          "BL      sub_FF9274EC\n"
          "BL      sub_FF888178\n"
          "BL      sub_FF933CC0\n"
          "BL      sub_FF888188\n"
          "BL      sub_FF927594\n"

     "loc_FF87500C:\n"
          "MOV     R0, #1\n"
          "STR     R0, [R4]\n"
          "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF856910_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "MOV     R6, #0\n"
          "MOV     R0, R6\n"
          "BL      sub_FF8564E0\n"
          "LDR     R4, =0x131E4\n"
          "MOV     R5, #0\n"
          "LDR     R0, [R4,#0x38]\n"
          "BL      sub_FF856EA8\n"
          "CMP     R0, #0\n"
          "LDREQ   R0, =0x2EB4\n"
          "STREQ   R5, [R0,#0xC]\n"
          "STREQ   R5, [R0,#0x10]\n"
          "STREQ   R5, [R0,#0x14]\n"
          "MOV     R0, R6\n"
          "BL      sub_FF856520\n"
          "MOV     R0, R6\n"
          //"BL      sub_FF85674C\n"
          "BL      sub_FF85674C_my\n"            // +----> Hook for SDHC booting
          "MOV     R5, R0\n"
          "MOV     R0, R6\n"
          "BL      sub_FF8567B8\n" 
          "LDR     R1, [R4,#0x3C]\n"
          "AND     R2, R5, R0\n"
          "CMP     R1, #0\n"
          "MOV     R0, #0\n"
          "MOVEQ   R0, #0x80000001\n"
          "BEQ     loc_FF8569A4\n"
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

     "loc_FF8569A4:\n"
          "STR     R0, [R4,#0x40]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF85674C_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "LDR     R5, =0x2EB4\n"
          "MOV     R6, R0\n"
          "LDR     R0, [R5,#0x10]\n"
          "CMP     R0, #0\n"
          "MOVNE   R0, #1\n"
          "LDMNEFD SP!, {R4-R6,PC}\n"
          "MOV     R0, #0x17\n"
          "MUL     R1, R0, R6\n"
          "LDR     R0, =0x131E4\n"
          "ADD     R4, R0, R1,LSL#2\n"
          "LDR     R0, [R4,#0x38]\n"
          "MOV     R1, R6\n"
          //"BL      sub_FF8565E4\n"
          "BL      sub_FF8565E4_my\n"            // +----> Hook for SDHC booting
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "LDR     R0, [R4,#0x38]\n"
          "MOV     R1, R6\n"
          "BL      sub_FF856FC0\n"
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "MOV     R0, R6\n"
          "BL      sub_FF856100\n"
          "CMP     R0, #0\n"
          "MOVNE   R1, #1\n"
          "STRNE   R1, [R5,#0x10]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF8565E4_my() {
     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "MOV     R8, R0\n"
          "MOV     R0, #0x17\n"
          "MUL     R1, R0, R1\n"
          "LDR     R0, =0x131E4\n"
          "MOV     R6, #0\n"
          "ADD     R7, R0, R1,LSL#2\n"
          "LDR     R0, [R7,#0x3C]\n"
          "MOV     R5, #0\n"
          "CMP     R0, #6\n"
          "ADDLS   PC, PC, R0,LSL#2\n"
          "B       loc_FF856730\n"

     "loc_FF856614:\n"
          "B       loc_FF856648\n"

     "loc_FF856618:\n"
          "B       loc_FF856630\n"

     "loc_FF85661C:\n"
          "B       loc_FF856630\n"

     "loc_FF856620:\n"
          "B       loc_FF856630\n"

     "loc_FF856624:\n"
          "B       loc_FF856630\n"

     "loc_FF856628:\n"
          "B       loc_FF856728\n"

     "loc_FF85662C:\n"
          "B       loc_FF856630\n"

     "loc_FF856630:\n"
          "MOV     R2, #0\n"
          "MOV     R1, #0x200\n"
          "MOV     R0, #3\n"
          "BL      sub_FF8716C4\n"
          "MOVS    R4, R0\n"
          "BNE     loc_FF856650\n"

     "loc_FF856648:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF856650:\n"
          "LDR     R12, [R7,#0x4C]\n"
          "MOV     R3, R4\n"
          "MOV     R2, #1\n"
          "MOV     R1, #0\n"
          "MOV     R0, R8\n"
          //"BLX     R12\n"      // WORKSFORME, configure gcc WITHOUT --with-cpu=arm9
          "MOV     LR, PC\n"     // 2-op workaround for 'normal' compiler
          "MOV     PC, R12\n"    // Does the same thing, effectively, because PC is always 8 bytes ahead.
          "CMP     R0, #1\n"
          "BNE     loc_FF85667C\n"
          "MOV     R0, #3\n"
          "BL      sub_FF871544\n"
          "B       loc_FF856648\n"

///////
// Offsets are fixed from here on, everything +0x10 for the second entry
///////

     "loc_FF85667C:\n"
          "MOV     R0, R8\n"
          "BL      sub_FF94450C\n"

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
//          "LDRB    LR, [R4,#0x1FF]\n"            // Last MBR signature byte (0xAA)
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
//          "LDRB    R12, [R4,#0x1FE]\n"           // First MBR signature byte (0x55)
          "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
          "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.
          "MOV     R4, #0\n"                     // This value previously held a pointer to the partition table :(
          "BNE     loc_FF856704\n"               // Jump out if the partition is malformed (partition status \'other\')
          "CMP     R0, R1\n"
          "BCC     loc_FF856704\n"               // Jump out if R0 < R1 (probably checking for a valid LBA addr)
          "ADD     R2, R1, R3\n"                 // R2 = partition start address + length = partition end address
          "CMP     R2, R0\n"                     // Guess: CMPLS is used to check for an overflow, the partition end address cannot be negative.
          "CMPLS   R12, #0x55\n"                 // Check MBR signature with original offset
          "CMPEQ   LR, #0xAA\n"                  // Check MBR signature with original offset
          "MOVEQ   R6, R1\n"
          "MOVEQ   R5, R3\n"
          "MOVEQ   R4, #1\n"

     "loc_FF856704:\n"
          "MOV     R0, #3\n"
          "BL      sub_FF871544\n"
          "CMP     R4, #0\n"
          "BNE     loc_FF85673C\n"
          "MOV     R6, #0\n"
          "MOV     R0, R8\n"
          "BL      sub_FF94450C\n"
          "MOV     R5, R0\n"
          "B       loc_FF85673C\n"

     "loc_FF856728:\n"
          "MOV     R5, #0x40\n"
          "B       loc_FF85673C\n"

     "loc_FF856730:\n"
          "LDR     R1, =0x365\n"
          //"ADR     R0, aMounter_c\n"             // \"Mounter.c\"
          "LDR     R0, =0xFF8565D8\n"
          //"BL      Assert\n"
          "BL      sub_FF81BCCC\n"

     "loc_FF85673C:\n"
          "STR     R6, [R7,#0x44]!\n"
          "MOV     R0, #1\n"
          "STR     R5, [R7,#4]\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

////////////////////////////////////////////////////////////////////////////////
// SDHC HOOK ENDS HERE
////////////////////////////////////////////////////////////////////////////////


// I could not manually find this function in the S5IS firmware, possibly signatures
// might find it. Until that moment, I hooked it here (copied from another camera)
unsigned long __attribute__((naked,noinline)) _time(unsigned long *timer) {
     asm volatile (
          "STMFD   SP!, {R3-R5,LR}\n"
          "MOV     R4, R0\n"
          "MVN     R0, #0\n"
          "STR     R0, [SP,#0x10-0x10]\n"
          "MOV     R0, SP\n"
          "BL      sub_FF870BB8\n" // _GetTimeOfSystem\n"
          "CMP     R0, #0\n"
          "BNE     loc_FFC55F38\n"
          "CMP     R4, #0\n"
          "LDRNE   R0, [SP,#0x10-0x10]\n"
          "STRNE   R0, [R4]\n"

     "loc_FFC55F38:\n"
          "LDR     R0, [SP,#0x10-0x10]\n"
          "LDMFD   SP!, {R3-R5,PC}\n"
     );
}



void CreateTask_blinker() {
        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};


void __attribute__((naked,noinline)) task_blinker() {
        int ledstate;

        int counter = 0;

        long *led = (void*) 0xC02200E0;   // AF led

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
                        //gui_init();
                        //_ExecuteEventProcedure("UIFS_WriteFirmInfoToFile");
                        //_UIFS_WriteFirmInfoToFile(0);
                }

                if (counter == 10) {
                        //draw_txt_string(2, 2, "test");
                }

                msleep(500);
        }
};


void CreateTask_spytask() {
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


void CreateTask_PhySw() {
        _CreateTask("PhySw", 0x17, 0x800, mykbd_task, 0);
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
        
    volatile long *led = (void*) 0xC02200D0;   // yellow led

    *led = 0x46; //on 

  //  _qDump("A/qdump", 0, (void*) 0x01900, 0xb0000);
    //_qDump("A/firmdump", 0, (void*) 0xffc00000, 0x00400000);
    //_qDump("A/firmlower", 0, (void*) 0xff800000, 0x00400000); // identical to 0xfc000000

    //started();

	//dirnum = get_target_dir_num();
	//sprintf(fn, FN_RAWDIR, dirnum);
	//mkdir(fn);

	//sprintf(fn, FN_RAWDIR "/" "DMP_%04d.JPG", dirnum, ++ramdump_num);

	//fd = _Fopen_Fut("A/dump", "w");
	//if (fd >= 0) {
	    //write(fd, (void*)0, 0x1900);
	    //write(fd, (void*)0x1900, 32*1024*1024-0x1900);
            //_Fwrite_Fut((void*)0x9D000, 0x20000, 0x20000, fd);
	    //_Fclose_Fut(fd);
	//}
    *led = 0x44; //off
    //finished();
} //#fe
