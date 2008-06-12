#include "lolevel.h"
#include "platform.h"
#include "core.h"

const long new_sa = MEMISOSTART + MEMISOSIZE;

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
          "LDR     R0, =0xFFB07FA8\n"
          "LDR     R1, =0x1900\n"
          "LDR     R3, =0x1056C\n"

     "loc_FF81014C:\n"
          "CMP     R1, R3\n"                     // Copy code from 0xFFB07FA8(inc) onwards to 0x1900(inc) .. 0x1056C (ex)
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
          "BL      sub_FFA92D04\n"
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
              "BL      sub_FF819898\n"           // dmSetup
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
              "BL      sub_FF819580\n"           // stdlibSetup
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
              //"B       sub_FF81DAB8\n"         // CreateTaskStartup
              "B       sub_FF81DAB8_my\n"        // +---------------------> Hook
     ".ltorg\n"
        );
};


void __attribute__((naked,noinline)) sub_FF81DAB8_my() {
     asm volatile (
          "STMFD   SP!, {R3,LR}\n"
          "BL      sub_FF82CEF0\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF81DAF4\n"
          "BL      sub_FF824DCC\n"
          "CMP     R0, #0\n"
          "LDREQ   R2, =0xC0220000\n"
          "LDREQ   R0, [R2,#0x10C]\n"
          "LDREQ   R1, [R2,#0x108]\n"
          "ORREQ   R0, R0, R1\n"
          "TSTEQ   R0, #1\n"
          "BNE     loc_FF81DAF4\n"
          "MOV     R0, #0x44\n"
          "STR     R0, [R2,#0x4C]\n"

     "loc_FF81DAF0:\n"
          "B       loc_FF81DAF0\n"


     "loc_FF81DAF4:\n"
          "BL      sub_FF8236F8\n"
          "BL      sub_FF82AA98\n"
          "MOV     R1, #0x300000\n"
          "MOV     R0, #0\n"
          "BL      sub_FF82ACE0\n"
          "BL      sub_FF82AC8C\n"
          "MOV     R3, #0\n"
          "STR     R3, [SP,#8-8]\n"
//          "LDR     R3, sub_FF81DA18\n"         // Startup, 0xFF81DA18
          "LDR     R3, =sub_FF81DA18_my\n"       // +---------------------> Hook
          "MOV     R2, #0\n"
          "MOV     R1, #0x19\n"
//          "ADR     R0, aStartup\n"
          "LDR     R0, =0xFF81DB44\n"
          "BL      sub_FF81B9C4\n"               // CreateTask
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R12,PC}\n"
     ".ltorg\n"
     );
}

void __attribute__((naked,noinline)) sub_FF81DA18_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FF81521C\n"
          "BL      sub_FF824840\n"
          "BL      sub_FF820E14\n"
          //"BL      j_nullsub_163\n"            
          "BL      sub_FF82D0E0\n"
//          "BL      sub_FF82CFC8\n"            // Apparently responsible for
                                                // diskboot. Bypassing it does
                                                // not seem to affect the camera
                                                // negatively.
     );
     
     CreateTask_spytask();
     
     asm volatile (
          "LDR     R4, =0x66A8\n"
          "B       loc_FF81DA44\n"

     "loc_FF81DA3C:\n"
          "SUBS    R4, R4, #1\n"
          "BEQ     loc_FF81DA54\n"

     "loc_FF81DA44:\n"
          "MOV     R0, #5\n"
          "BL      sub_FF820F1C\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF81DA3C\n"

     "loc_FF81DA54:\n"
          "MOV     R0, #5\n"
          "BL      sub_FF821314\n"
          "SUBS    R12, R0, #0x300\n"
          "SUBGES  R12, R12, #0xF6\n"
          "BLE     loc_FF81DA78\n"
          "BL      sub_FF829FD4\n"
          "MOV     R1, #0xB5\n"
//          "ADR     R0, aStartup_c\n"
          "LDR     R0, =0xFF81DB34\n"
          "BL      sub_FF81BD94\n"               // Assert, 0xFF81BD94

     "loc_FF81DA78:\n"
          "BL      sub_FF82DB84\n"
          "BL      sub_FF82D130\n"
          "BL      sub_FF829FD4\n"
          "BL      sub_FF82DB94\n"
          //"BL      sub_FF82369C\n"             // PhySw, bypass and create own
     );

     CreateTask_PhySw();

     asm volatile (
//          "BL      sub_FF826A50\n"             // CaptSeqTask and lots of other stuff
          "BL      sub_FF826A50_my\n"            // +---------------------> Hook (in capt_seq.c)
          "BL      sub_FF82DBB4\n"
          //"BL      nullsub_2\n"
          "BL      sub_FF822A60\n"
          "BL      sub_FF82CCBC\n"
          "BL      sub_FF823188\n"
          "BL      sub_FF82296C\n"
          //"BL      sub_FF82E638\n"
          "BL      sub_FF82E638_my\n"            // +---> MAJOR HOOK (SDHC boot)
          "BL      sub_FF8227F0\n"
          "LDMFD   SP!, {R4,LR}\n"
          "B       sub_FF8150D8\n"
     ".ltorg\n"
     );
}


/////////////////////////////////////////////////////////////////////////////////////
// Major SDHC boot fix hook starts here
//
// Paths that certainly do not (by itself) get the SDHC booting going:
// sub_FF82E638 -> sub_FF824DE0 -> sub_FF824B28 -> sub_FF87C040 (entire 'right subtree')
// sub_FF82E638 -> sub_FF82E1E8 -> sub_FF87AD50 -> sub_FF87A408 -> sub_FF87C040 (shortest path (subroutine-count-wise) through 'left subtree')
// sub_FF82E638 -> sub_FF82E1E8 -> sub_FF87AD50 -> sub_FF87A8D4 -> sub_FF87A408 -> sub_FF87C040 (sub_FF87A8D4 does not appear to be called)
// 
// Unexplored:
// sub_FF82E638 -> sub_FF82E1E8 -> sub_FF87BE10 -> sub_FF87BC5C -> sub_FF87AD50 ->              -> sub_FF87A408 -> sub_FF87C040
//                                                                              -> sub_FF87A8D4 ->
//
// Final, working path:
// sub_FF82E638 -> sub_FF82E1E8 -> sub_FF87BE10 -> sub_FF87BC5C -> sub_FF87AD50 -> sub_FF87A408 -> sub_FF87C040
//
// That's the 'tree'-part, the rest of the subroutines are just straight on down, no junctions.
// -> sub_FF87BFF0 -> sub_FF8750A4 -> sub_FF8569D8 -> sub_FF856814 -> sub_FF8566AC
/////////////////////////////////////////////////////////////////////////////////////

void __attribute__((naked,noinline)) sub_FF82E638_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FF878E50\n"
          "BL      sub_FF824DA0\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF82E658\n"
          "BL      sub_FF87C154\n"
          "LDMFD   SP!, {R4,LR}\n"
          "B       sub_FF824DE0\n"

     "loc_FF82E658:\n"
          "BL      sub_FF87AFF8\n"
          "LDR     R4, =0x1E80\n"
          "LDR     R0, [R4,#4]\n"
          "CMP     R0, #0\n"
          "LDMNEFD SP!, {R4,PC}\n"
          "MOV     R1, #0\n"
          //"LDR     R0, =0xFF82E1E8\n"
          "LDR     R0, =sub_FF82E1E8_my\n"       // +----> Hook for SDHC booting
          "BL      sub_FF875A00\n"
          "STR     R0, [R4,#4]\n"
          "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF82E1E8_my() {
     asm volatile (
          "STMFD   SP!, {R3-R11,LR}\n"
          "LDR     R6, =0x1E80\n"
          "MOV     R5, R1\n"
          "LDR     R0, [R6,#0x14]\n"
          "MOV     R4, R3\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF82E20C\n"
          "BL      sub_FF8796A8\n"
          "B       loc_FF82E290\n"

     "loc_FF82E20C:\n"
          "LDR     R12, =0x1162\n"
          "LDR     R10, =0x1005\n"
          "CMP     R5, R12\n"
          "MOV     R7, #0\n"
          "MOV     R8, #1\n"
          "BEQ     loc_FF82E58C\n"
          "BGT     loc_FF82E354\n"
          "LDR     R12, =0x1062\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FF82E614\n"
          "BGT     loc_FF82E2C0\n"
          "CMP     R5, R10\n"
          "BEQ     loc_FF82E310\n"
          "BGT     loc_FF82E298\n"
          "SUB     R12, R5, #0x800\n"
          "SUBS    R12, R12, #3\n"
          "BEQ     loc_FF82E494\n"
          "SUB     R12, R5, #0x800\n"
          "SUBS    R12, R12, #0x158\n"
          "BEQ     loc_FF82E61C\n"
          "LDR     R4, =0x9A3\n"
          "CMP     R5, R4\n"
          "ADD     R7, R4, #2\n"
          "CMPNE   R5, R7\n"
          "BNE     loc_FF82E57C\n"
          "LDR     R0, [R6,#0xC]\n"
          "SUB     R12, R0, #0x8000\n"
          "SUBS    R12, R12, #2\n"
          "BEQ     loc_FF82E290\n"
          "LDR     R0, =0x10A5\n"
          "BL      sub_FF877B44\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF82E568\n"

     "loc_FF82E290:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E298:\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0x56\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x5B\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x5E\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x61\n"
          "BNE     loc_FF82E57C\n"
          "B       loc_FF82E614\n"

     "loc_FF82E2C0:\n"
          "LDR     R12, =0x10AD\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FF82E5B4\n"
          "BGT     loc_FF82E318\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0x63\n"
          "SUBNE   R12, R5, #0x1000\n"
          "SUBNES  R12, R12, #0x65\n"
          "BEQ     loc_FF82E614\n"
          "SUB     R12, R5, #0x1000\n"
          "LDR     R0, =0x10A3\n"
          "SUBS    R12, R12, #0xA9\n"
          "BEQ     loc_FF82E5A8\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xAA\n"
          "BNE     loc_FF82E57C\n"
          "BL      sub_FF877B44\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF82E290\n"

     "loc_FF82E30C:\n"
          "BL      sub_FF82EBCC\n"

     "loc_FF82E310:\n"
          "MOV     R1, R4\n"
          "B       loc_FF82E580\n"

     "loc_FF82E318:\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xAE\n"
          "BEQ     loc_FF82E30C\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xAF\n"
          "BEQ     loc_FF82E5B4\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xB0\n"
          "BEQ     loc_FF82E30C\n"
          "SUB     R12, R5, #0x1000\n"
          "SUBS    R12, R12, #0xB2\n"
          "BNE     loc_FF82E57C\n"
          "LDR     R0, =0x1008\n"
          "MOV     R1, R4\n"
          "B       loc_FF82E584\n"

     "loc_FF82E354:\n"
          "LDR     R11, =0x201B\n"
          "LDR     R0, =0x1E80\n"
          "CMP     R5, R11\n"
          "LDR     R2, [R0,#0x10]!\n"
          "LDR     R1, [R0,#0x10]\n"
          "SUB     R9, R11, #0x17\n"
          "BEQ     loc_FF82E548\n"
          "BGT     loc_FF82E41C\n"
          "LDR     R11, =0x116A\n"
          "CMP     R5, R11\n"
          "BEQ     loc_FF82E534\n"
          "BGT     loc_FF82E3D0\n"
          "SUB     R12, R5, #0x1100\n"
          "SUBS    R12, R12, #0x63\n"
          "MOVEQ   R1, #0\n"
          "MOVEQ   R0, #0x82\n"
          "BEQ     loc_FF82E560\n"
          "SUB     R12, R5, #0x1100\n"
          "SUBS    R12, R12, #0x65\n"
          "BEQ     loc_FF82E558\n"
          "LDR     R4, =0x1168\n"
          "SUB     R12, R5, #0x1100\n"
          "SUBS    R12, R12, #0x67\n"
          "CMPNE   R5, R4\n"
          "BNE     loc_FF82E57C\n"
          "STR     R8, [R6,#0x10]\n"
          "LDR     R6, =0x4508\n"
          "CMP     R1, #0\n"
          "BEQ     loc_FF82E524\n"
          "BL      sub_FF8796DC\n"
          "B       loc_FF82E528\n"

     "loc_FF82E3D0:\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #2\n"
          "BEQ     loc_FF82E5E0\n"
          "CMP     R5, R9\n"
          "MOV     R0, R9\n"
          "BEQ     loc_FF82E5EC\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #5\n"
          "BEQ     loc_FF82E5E0\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #0x19\n"
          "BNE     loc_FF82E57C\n"
          "CMP     R1, #0\n"
          "BEQ     loc_FF82E290\n"
          "CMP     R2, #0\n"
          "BNE     loc_FF82E290\n"

     "loc_FF82E410:\n"
          "MOV     R1, #0\n"

     "loc_FF82E414:\n"
          "BL      sub_FF87AD50\n"
          "B       loc_FF82E290\n"

     "loc_FF82E41C:\n"
          "LDR     R12, =0x3110\n"
          "CMP     R5, R12\n"
          "BEQ     loc_FF82E310\n"
          "BGT     loc_FF82E464\n"
          "SUB     R12, R5, #0x2000\n"
          "SUBS    R12, R12, #0x1D\n"
          "BEQ     loc_FF82E5E0\n"
          "LDR     R0, =0x2027\n"
          "CMP     R5, R0\n"
          "BEQ     loc_FF82E5C0\n"
          "SUB     R12, R5, #0x3000\n"
          "SUBS    R12, R12, #6\n"
          "BEQ     loc_FF82E310\n"
          "SUB     R12, R5, #0x3000\n"
          "SUBS    R12, R12, #0x10\n"
          "BNE     loc_FF82E57C\n"
          "BL      sub_FF89A6F0\n"
          "B       loc_FF82E290\n"

     "loc_FF82E464:\n"
          "SUB     R12, R5, #0x3100\n"
          "SUBS    R12, R12, #0x11\n"
          "BEQ     loc_FF82E310\n"
          "CMP     R5, #0x3140\n"
          "BEQ     loc_FF82E608\n"
          "SUB     R12, R5, #0x3200\n"
          "SUBS    R12, R12, #1\n"
          "BEQ     loc_FF82E57C\n"
          "SUB     R12, R5, #0x3200\n"
          "SUBS    R12, R12, #2\n"
          "BEQ     loc_FF82E310\n"
          "B       loc_FF82E57C\n"

     "loc_FF82E494:\n"
          "MOV     R4, #1\n"
          "MOV     R0, #2\n"
          "BL      sub_FF878EE4\n"
          "CMP     R0, #1\n"
          "MOVEQ   R4, #2\n"
          "MOV     R0, R4\n"
          "BL      sub_FF822D8C\n"
          "CMP     R0, #0\n"
          "STRNE   R8, [R6,#0x14]\n"
          "BNE     loc_FF82E4F0\n"
          "BL      sub_FF87F8DC\n"
          "BL      sub_FF87CE00\n"
          "BL      sub_FF87DCA0\n"
          "BL      sub_FF87E1B0\n"
          "BL      sub_FF87C3D8\n"
          "BL      sub_FF87E5AC\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF82E4F8\n"
          "BL      sub_FF82DF54\n"
          "BL      sub_FF87E5A0\n"
          "MOV     R1, R0\n"
          "LDR     R0, =0x1167\n"
          "BL      sub_FF8761C8\n"

     "loc_FF82E4F0:\n"
          "MOV     R0, R7\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E4F8:\n"
          "BL      sub_FF827068\n"
          "CMP     R0, #1\n"
          "LDRNE   R0, =0x310B\n"
          "LDREQ   R0, =0x310C\n"
          "MOV     R1, #0\n"
          "BL      sub_FF8761C8\n"
          //"BL      sub_FF87BE10\n"
          "BL      sub_FF87BE10_my\n"            // +----> Hook for SDHC booting
          "B       loc_FF82E4F0\n"

     "loc_FF82E518:\n"
          "MOV     R0, R6\n"
          "BL      sub_FF864270\n"
          "B       loc_FF82E290\n"

     "loc_FF82E524:\n"
          "BL      sub_FF826D60\n"

     "loc_FF82E528:\n"
          "CMP     R5, R4\n"
          "BNE     loc_FF82E290\n"
          "B       loc_FF82E518\n"

     "loc_FF82E534:\n"
          "MOV     R0, #1\n"
          "BL      sub_FF8797F4\n"
          "MOV     R1, R11\n"
          "MOV     R0, R10\n"
          "B       loc_FF82E584\n"

     "loc_FF82E548:\n"
          "CMP     R2, #1\n"
          "BNE     loc_FF82E310\n"
          "BL      sub_FF8796DC\n"
          "B       loc_FF82E290\n"

     "loc_FF82E558:\n"
          "MOV     R1, #0\n"
          "MOV     R0, #0x83\n"

     "loc_FF82E560:\n"
          "BL      sub_FF87E284\n"
          "B       loc_FF82E290\n"

     "loc_FF82E568:\n"
          "CMP     R5, R4\n"
          "STREQ   R8, [R6,#0x34]\n"
          "BEQ     loc_FF82E57C\n"
          "CMP     R5, R7\n"
          "STREQ   R8, [R6,#0x30]\n"

     "loc_FF82E57C:\n"
          "MOV     R1, #0\n"

     "loc_FF82E580:\n"
          "MOV     R0, R5\n"

     "loc_FF82E584:\n"
          "BL      sub_FF87AD50\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E58C:\n"
          "BL      sub_FF882328\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF82E310\n"
          "BL      sub_FF882C38\n"
          "CMP     R0, #0\n"
          "BLEQ    sub_FF88105C\n"
          "B       loc_FF82E310\n"

     "loc_FF82E5A8:\n"
          "BL      sub_FF877B44\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF82E290\n"

     "loc_FF82E5B4:\n"
          "MOV     R0, R5\n"
          "BL      sub_FF82E074\n"
          "LDMFD   SP!, {R3-R11,PC}\n"

     "loc_FF82E5C0:\n"
          "MOV     R1, #0\n"
          "BL      sub_FF87AD50\n"
          "MOV     R1, #0\n"
          "MOV     R0, R11\n"
          "BL      sub_FF87AD50\n"
          "MOV     R1, #0\n"
          "MOV     R0, R9\n"
          "B       loc_FF82E414\n"

     "loc_FF82E5E0:\n"
          "STR     R7, [R6,#0x20]\n"
          "BL      sub_FF82E86C\n"
          "B       loc_FF82E310\n"

     "loc_FF82E5EC:\n"
          "STR     R7, [R6,#0x20]\n"
          "BL      sub_FF82E86C\n"
          "LDR     R0, [R6,#0x10]\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF82E310\n"
          "BL      sub_FF879708\n"
          "B       loc_FF82E290\n"

     "loc_FF82E608:\n"
          "CMP     R1, #0\n"
          "BLEQ    sub_FF82E86C\n"
          "B       loc_FF82E290\n"

     "loc_FF82E614:\n"
          "MVN     R0, #0\n"
          "B       loc_FF82E410\n"

     "loc_FF82E61C:\n"
          "TST     R4, #0x80000000\n"
          "MOVNE   R0, #1\n"
          "LDMNEFD SP!, {R3-R11,PC}\n"
          "BL      sub_FF883DD0\n"
          "CMP     R0, #0\n"
          "BLEQ    sub_FF829DA0\n"
          "B       loc_FF82E290\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87BE10_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "BL      sub_FF82E838\n"
          "MOV     R4, R0\n"
          "BL      sub_FF87BF2C\n"
          "MOV     R0, R4\n"
          "BL      sub_FF87BCC0\n"
          "BL      sub_FF82E838\n"
          "MOV     R4, R0\n"
          "LDR     R0, =0x6374\n"
          "LDR     R0, [R0]\n"
          "TST     R0, #1\n"
          "BEQ     loc_FF87BE4C\n"

     "loc_FF87BE40:\n"
          "MOV     R1, R4\n"
          "MOV     R0, #2\n"
          "B       loc_FF87BEB4\n"

     "loc_FF87BE4C:\n"
          "TST     R0, #0x2000\n"
          "BEQ     loc_FF87BE68\n"
          "TST     R0, #0x200\n"
          "LDREQ   R1, =0x4004\n"
          "LDRNE   R1, =0x8002\n"
          "MOV     R0, #3\n"
          "B       loc_FF87BEB4\n"

     "loc_FF87BE68:\n"
          "TST     R0, #0x10\n"
          "BNE     loc_FF87BE40\n"
          "TST     R0, #0x40\n"
          "BEQ     loc_FF87BE84\n"

     "loc_FF87BE78:\n"
          "MOV     R1, R4\n"
          "MOV     R0, #1\n"
          "B       loc_FF87BEB4\n"

     "loc_FF87BE84:\n"
          "TST     R0, #0x20\n"
          "BEQ     loc_FF87BEA0\n"
          "TST     R0, #0x4000\n"
          "BNE     loc_FF87BEA0\n"

     "loc_FF87BE94:\n"
          "MOV     R1, R4\n"
          "MOV     R0, #0\n"
          "B       loc_FF87BEB4\n"

     "loc_FF87BEA0:\n"
          "LDR     R1, =0x102\n"
          "BICS    R1, R1, R0\n"
          "BNE     loc_FF87BEBC\n"
          "MOV     R1, R4\n"
          "MOV     R0, #6\n"

     "loc_FF87BEB4:\n"
          "LDMFD   SP!, {R4,LR}\n"
          //"B       sub_FF87BC5C\n"
          "B       sub_FF87BC5C_my\n"            // +----> Hook for SDHC booting

     "loc_FF87BEBC:\n"
          "TST     R0, #0x100\n"
          "BNE     loc_FF87BE40\n"
          "TST     R0, #0x4000\n"
          "TSTEQ   R0, #0x400\n"
          "BNE     loc_FF87BE78\n"
          "TST     R0, #0x200\n"
          "TSTEQ   R0, #2\n"
          "BNE     loc_FF87BE94\n"
          "TST     R0, #0x40000\n"
          "BEQ     loc_FF87BE40\n"
          "TST     R0, #0x200000\n"
          "MOVEQ   R1, R4\n"
          "MOVEQ   R0, #1\n"
          //"BLEQ    sub_FF87BC5C\n"
          "BLEQ    sub_FF87BC5C_my\n"            // +----> Hook for SDHC booting
          "B       loc_FF87BE40\n"
     );
}


void __attribute__((naked,noinline)) sub_FF87BC5C_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "MOVS    R4, R0\n"
          "MOV     R0, #1\n"
          "MOV     R5, R1\n"
          "BNE     loc_FF87BC9C\n"
          "MOV     R1, #0\n"
          "MOV     R0, #0\n"
          "BL      sub_FF878E74\n"
          "BL      sub_FF82E838\n"
          "SUB     R12, R0, #0x1000\n"
          "SUBS    R12, R12, #0x5B\n"
          "BNE     loc_FF87BC94\n"

     "loc_FF87BC8C:\n"
          "BL      sub_FF87BBA4\n"
          "B       loc_FF87BCA4\n"

     "loc_FF87BC94:\n"
          "BL      sub_FF87BBE4\n"
          "B       loc_FF87BCA4\n"

     "loc_FF87BC9C:\n"
          "CMP     R4, #5\n"
          "BEQ     loc_FF87BC8C\n"

     "loc_FF87BCA4:\n"
          "CMP     R0, #0\n"
          "LDREQ   R5, =0x1162\n"
          "MOVEQ   R4, #2\n"
          "MOV     R0, R4\n"
          "MOV     R1, R5\n"
          "LDMFD   SP!, {R4-R6,LR}\n"
          //"B       sub_FF87AD50\n"
          "B       sub_FF87AD50_my\n"            // +----> Hook for SDHC booting
     );
}

void __attribute__((naked,noinline)) sub_FF87AD50_my() {
     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "MOV     R8, R1\n"
          "MOV     R4, R0\n"
          "BL      sub_FF8799F0\n"
          "LDR     R5, =0x62AC\n"
          "MOV     R7, #1\n"
          "LDR     R0, [R5,#0x10]\n"
          "MOV     R6, #0\n"
          "CMP     R0, #0x15\n"
          "ADDLS   PC, PC, R0,LSL#2\n"
          "B       loc_FF87AFF0\n"

     "loc_FF87AD7C:\n"
          "B       loc_FF87ADD4\n"

     "loc_FF87AD80:\n"
          "B       loc_FF87ADFC\n"

     "loc_FF87AD84:\n"
          "B       loc_FF87AE40\n"

     "loc_FF87AD88:\n"
          "B       loc_FF87AEB4\n"

     "loc_FF87AD8C:\n"
          "B       loc_FF87AEC4\n"

     "loc_FF87AD90:\n"
          "B       loc_FF87AED0\n"

     "loc_FF87AD94:\n"
          "B       loc_FF87AF40\n"

     "loc_FF87AD98:\n"
          "B       loc_FF87AF50\n"

     "loc_FF87AD9C:\n"
          "B       loc_FF87ADE4\n"

     "loc_FF87ADA0:\n"
          "B       loc_FF87ADF0\n"

     "loc_FF87ADA4:\n"
          "B       loc_FF87AF50\n"

     "loc_FF87ADA8:\n"
          "B       loc_FF87AE34\n"

     "loc_FF87ADAC:\n"
          "B       loc_FF87AFF0\n"

     "loc_FF87ADB0:\n"
          "B       loc_FF87AFF0\n"

     "loc_FF87ADB4:\n"
          "B       loc_FF87AE4C\n"

     "loc_FF87ADB8:\n"
          "B       loc_FF87AE58\n"

     "loc_FF87ADBC:\n"
          "B       loc_FF87AE8C\n"

     "loc_FF87ADC0:\n"
          "B       loc_FF87AE08\n"

     "loc_FF87ADC4:\n"
          "B       loc_FF87AFD8\n"

     "loc_FF87ADC8:\n"
          "B       loc_FF87AF5C\n"

     "loc_FF87ADCC:\n"
          "B       loc_FF87AF8C\n"

     "loc_FF87ADD0:\n"
          "B       loc_FF87AF8C\n"

     "loc_FF87ADD4:\n"
          "MOV     R1, R8\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          //"B       sub_FF87A408\n"
          "B       sub_FF87A408_my\n"            // +----> Hook for SDHC booting

     "loc_FF87ADE4:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B720\n"

     "loc_FF87ADF0:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87A8D4\n"

     "loc_FF87ADFC:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF879FD0\n"

     "loc_FF87AE08:\n"
          "SUB     R12, R4, #0x1000\n"
          "SUBS    R12, R12, #0xA5\n"
          "STREQ   R7, [R5,#0x84]\n"
          "BEQ     loc_FF87AFE8\n"
          "SUB     R12, R4, #0x3000\n"
          "SUBS    R12, R12, #6\n"
          "BNE     loc_FF87AFF0\n"
          "MOV     R0, #0\n"
          "BL      sub_FF82DDAC\n"
          "BL      sub_FF87B644\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AE34:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B680\n"

     "loc_FF87AE40:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87A1CC\n"

     "loc_FF87AE4C:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87AA80\n"

     "loc_FF87AE58:\n"
          "SUB     R12, R4, #0x3200\n"
          "SUBS    R12, R12, #2\n"
          "BNE     loc_FF87AFF0\n"
          "MOV     R0, #3\n"
          "BL      sub_FF8798D4\n"
          "MOV     R0, #8\n"
          "BL      sub_FF82DD18\n"
          "MOV     R0, #6\n"
          "BL      sub_FF842464\n"
          "BL      sub_FF87D210\n"
          "BL      sub_FF87D06C\n"
          "BL      sub_FF87C448\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AE8C:\n"
          "SUB     R12, R4, #0x3300\n"
          "SUBS    R12, R12, #1\n"
          "BNE     loc_FF87AFF0\n"
          "LDR     R0, =0x4010\n"
          "BL      sub_FF82DD18\n"
          "BL      sub_FF89F050\n"
          "BL      sub_FF87C448\n"
          "MOV     R0, #4\n"
          "BL      sub_FF8798D4\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AEB4:\n"
          "MOV     R1, R8\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87ABE8\n"

     "loc_FF87AEC4:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B850\n"

     "loc_FF87AED0:\n"
          "LDR     R8, =0x1182\n"
          "CMP     R4, R8\n"
          "STREQ   R7, [R5,#0xB0]\n"
          "BEQ     loc_FF87AFE8\n"
          "SUB     R12, R4, #0x1100\n"
          "SUBS    R12, R12, #0x86\n"
          "BEQ     loc_FF87AF28\n"
          "SUB     R12, R4, #0x3200\n"
          "SUBS    R12, R12, #0x16\n"
          "BNE     loc_FF87AFF0\n"
          "MOV     R0, #8\n"
          "BL      sub_FF82DD18\n"
          "MOV     R0, #3\n"
          "BL      sub_FF8798D4\n"
          "STR     R6, [R5,#0xB4]\n"
          "LDR     R0, [R5,#0xB0]\n"
          "CMP     R0, #0\n"
          "MOVNE   R1, #0\n"
          "MOVNE   R0, R8\n"
          "STRNE   R6, [R5,#0xB0]\n"
          "BLNE    sub_FF87ABE8\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AF28:\n"
          "LDR     R0, [R5,#0xB4]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87AFE8\n"
          "BL      sub_FF89C720\n"
          "STR     R7, [R5,#0xB4]\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AF40:\n"
          "MOV     R1, R8\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87B930\n"

     "loc_FF87AF50:\n"
          "MOV     R0, R4\n"
          "LDMFD   SP!, {R4-R8,LR}\n"
          "B       sub_FF87A7CC\n"

     "loc_FF87AF5C:\n"
          "LDR     R12, =0x10B0\n"
          "CMP     R4, R12\n"
          "BEQ     loc_FF87AF88\n"
          "BGT     loc_FF87AF94\n"
          "CMP     R4, #4\n"
          "BEQ     loc_FF87AFBC\n"
          "SUB     R12, R4, #0x1000\n"
          "SUBS    R12, R12, #0xAA\n"
          "SUBNE   R12, R4, #0x1000\n"
          "SUBNES  R12, R12, #0xAE\n"
          "BNE     loc_FF87AFF0\n"

     "loc_FF87AF88:\n"
          "BL      sub_FF8795D0\n"

     "loc_FF87AF8C:\n"
          "MOV     R0, R6\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF87AF94:\n"
          "SUB     R12, R4, #0x2000\n"
          "SUBS    R12, R12, #4\n"
          "BEQ     loc_FF87AFD0\n"
          "SUB     R12, R4, #0x5000\n"
          "SUBS    R12, R12, #1\n"
          "SUBNE   R12, R4, #0x5000\n"
          "SUBNES  R12, R12, #6\n"
          "BNE     loc_FF87AFF0\n"
          "BL      sub_FF879F70\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AFBC:\n"
          "LDR     R0, [R5,#0x2C]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87AFD0\n"
          "BL      sub_FF826D18\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AFD0:\n"
          "BL      sub_FF879608\n"
          "B       loc_FF87AFE8\n"

     "loc_FF87AFD8:\n"
          "SUB     R12, R4, #0x3000\n"
          "SUBS    R12, R12, #0x130\n"
          "BNE     loc_FF87AFF0\n"
          "BL      sub_FF8796A8\n"

     "loc_FF87AFE8:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF87AFF0:\n"
          "MOV     R0, #1\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87A408_my() {
     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "LDR     R7, =0x8002\n"
          "LDR     R4, =0x62AC\n"
          "CMP     R0, #3\n"
          "MOV     R6, R1\n"
          "MOV     R5, #1\n"
          "BEQ     loc_FF87A57C\n"
          "BGT     loc_FF87A444\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF87A488\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF87A50C\n"
          "CMP     R0, #2\n"
          "BNE     loc_FF87A604\n"
          "B       loc_FF87A45C\n"

     "loc_FF87A444:\n"
          "CMP     R0, #6\n"
          "STREQ   R5, [R4,#0x28]\n"
          "BEQ     loc_FF87A574\n"
          "SUB     R12, R0, #0x2000\n"
          "SUBS    R12, R12, #4\n"
          "BNE     loc_FF87A604\n"

     "loc_FF87A45C:\n"
          "SUB     R12, R6, #0x1100\n"
          "SUBS    R12, R12, #0x62\n"
          "BNE     loc_FF87A478\n"
          "MOV     R1, R7\n"
          "MOV     R0, #0\n"
          "BL      sub_FF87E284\n"
          "STR     R5, [R4,#0x60]\n"

     "loc_FF87A478:\n"
          "BL      sub_FF87D210\n"
          "BL      sub_FF87D06C\n"
          "BL      sub_FF879F10\n"
          "B       loc_FF87A5FC\n"

     "loc_FF87A488:\n"
          "MOV     R0, #7\n"
          "BL      sub_FF8798D4\n"
          "MOV     R0, R7\n"
          "BL      sub_FF82DD18\n"
          "BL      sub_FF87C07C\n"
          "BL      sub_FF87CEE4\n"
          "MOV     R1, R7\n"
          "MOV     R0, #0\n"
          "BL      sub_FF87E284\n"
          //"ADR     R1, aAcBootrec\n"             // \"AC:BootRec\"
          "LDR     R1, =0xFF87A63C\n"             // \"AC:BootRec\"
          "MOV     R0, #0x20\n"
          "STR     R6, [R4,#0x18]\n"
          "BL      sub_FF872B20\n"
          //"ADR     R1, aAcInitlens\n"            // \"AC:InitLens\"
          "LDR     R1, =0xFF87A648\n"            // \"AC:InitLens\"
          "MOV     R0, #0x20\n"
          "BL      sub_FF872B20\n"
          "STR     R5, [R4,#0x28]\n"
          "BL      sub_FF82DEC0\n"
          "BL      sub_FF82DE04\n"
          "LDR     R0, [R4,#0x1C]\n"
          "LDR     R1, [R4,#0x20]\n"
          "ORRS    R0, R0, R1\n"
          "BLNE    sub_FF87B1AC\n"
          "LDR     R0, [R4,#0x68]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87A4F8\n"
          "BL      sub_FF82DF30\n"
          "B       loc_FF87A500\n"

     "loc_FF87A4F8:\n"
          "BL      sub_FF826AB0\n"
          "BL      sub_FF82E7C8\n"

     "loc_FF87A500:\n"
          //"BL      sub_FF87C040\n"
          "BL      sub_FF87C040_my\n"            // +----> Hook for SDHC booting
          "BL      sub_FF87C0B8\n"
          "B       loc_FF87A5FC\n"

     "loc_FF87A50C:\n"
          "MOV     R0, #8\n"
          "BL      sub_FF8798D4\n"
          "BL      sub_FF87C07C\n"
          "BL      sub_FF87CEE4\n"
          "LDR     R5, =0x4004\n"
          "MOV     R0, #0\n"
          "MOV     R1, R5\n"
          "BL      sub_FF87E284\n"
          //"ADR     R1, aAcBootpb\n"              // \"AC:BootPB\"
          "LDR     R1, =0xFF87A658\n"              // \"AC:BootPB\"
          "MOV     R0, #0x20\n"
          "BL      sub_FF872B20\n"
          //"BL      sub_FF87C040\n"
          "BL      sub_FF87C040_my\n"            // +----> Hook for SDHC booting
          "BL      sub_FF87C154\n"
          "BL      sub_FF82E758\n"
          "MOV     R0, R5\n"
          "BL      sub_FF82DD18\n"
          "LDR     R0, [R4,#0x68]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF87A560\n"
          "BL      sub_FF82DF30\n"
          "B       loc_FF87A564\n"

     "loc_FF87A560:\n"
          "BL      sub_FF826AB0\n"

     "loc_FF87A564:\n"
          "BL      sub_FF87C0E8\n"
          "LDR     R0, [R4,#0x30]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF87A5FC\n"

     "loc_FF87A574:\n"
          "BL      sub_FF87B1D0\n"
          "B       loc_FF87A5FC\n"

     "loc_FF87A57C:\n"
          "MOV     R1, R6\n"
          "MOV     R0, #0\n"
          "BL      sub_FF87E284\n"
          //"ADR     R1, aAcBootclock\n"           // \"AC:BootClock\"
          "LDR     R1, =0xFF87A664\n"           // \"AC:BootClock\"
          "MOV     R0, #0x20\n"
          "BL      sub_FF872B20\n"
          "STR     R5, [R4,#0x68]\n"
          "BL      sub_FF87C154\n"
          "BL      sub_FF82E758\n"
          "BL      sub_FF87B17C\n"
          "BL      sub_FF82E82C\n"
          "CMP     R0, #0\n"
          "LDRNE   R0, =0x8045\n"
          "MOVNE   R1, #0\n"
          "BLNE    sub_FF878A9C\n"
          "BL      sub_FF87E098\n"
          "MOV     R0, #0x80\n"
          "BL      sub_FF82DD18\n"
          "BL      sub_FF87D3A0\n"
          "BL      sub_FF8B0F7C\n"
          "BL      sub_FF9732E0\n"
          "BL      sub_FF8AF7D0\n"
          "BL      sub_FF87CAAC\n"
          "BL      sub_FF87D248\n"
          "MOV     R0, #9\n"
          "BL      sub_FF8798D4\n"
          "LDR     R0, =0x300E\n"
          "MOV     R1, R6\n"
          "BL      sub_FF8761C8\n"
          "MOV     R1, #0\n"
          "MOV     R0, #1\n"
          "BL      sub_FF87E284\n"

     "loc_FF87A5FC:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF87A604:\n"
          "MOV     R0, #1\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87C040_my() {
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
          //"LDR     R3, =sub_FF87BFF0\n"
          "LDR     R3, =sub_FF87BFF0_my\n"       // +----> Hook for SDHC booting
          "MOV     R1, #0x19\n"
          //"LDR     R0, =aInitfilemodule\n"        // \"InitFileModules\"
          "LDR     R0, =0xFF87C1C0\n"
          "MOV     R2, #0x1000\n"
          "BL      sub_FF81B9C4\n"

     "locret_FF87BFB0:\n"
          "LDMFD   SP!, {R12,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF87BFF0_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "BL      sub_FF875078\n"
          "LDR     R5, =0x5006\n"
          "MOVS    R4, R0\n"
          "MOVNE   R1, #0\n"
          "MOVNE   R0, R5\n"
          "BLNE    sub_FF8761C8\n"
          //"BL      sub_FF8750A4\n"
          "BL      sub_FF8750A4_my\n"            // +----> Hook for SDHC booting

          "BL      core_spytask_can_start\n"     // +----> CHDK: Set "it's-safe-to-start"-Flag for spytask

          "CMP     R4, #0\n"
          "MOVEQ   R0, R5\n"
          "LDMEQFD SP!, {R4-R6,LR}\n"
          "MOVEQ   R1, #0\n"
          "BEQ     sub_FF8761C8\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF8750A4_my() {
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          //"BL      sub_FF8569D8\n"
          "BL      sub_FF8569D8_my\n"            // +----> Hook for SDHC booting
          "LDR     R4, =0x5C88\n"
          "LDR     R0, [R4,#4]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF8750D4\n"
          "BL      sub_FF888240\n"
          "BL      sub_FF9275B4\n"
          "BL      sub_FF888240\n"
          "BL      sub_FF933D88\n"
          "BL      sub_FF888250\n"
          "BL      sub_FF92765C\n"

     "loc_FF8750D4:\n"
          "MOV     R0, #1\n"
          "STR     R0, [R4]\n"
          "LDMFD   SP!, {R4,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF8569D8_my() {
     asm volatile (
          "STMFD   SP!, {R4-R6,LR}\n"
          "MOV     R6, #0\n"
          "MOV     R0, R6\n"
          "BL      sub_FF8565A8\n"
          "LDR     R4, =0x131E4\n"
          "MOV     R5, #0\n"
          "LDR     R0, [R4,#0x38]\n"
          "BL      sub_FF856F70\n"
          "CMP     R0, #0\n"
          "LDREQ   R0, =0x2EB4\n"
          "STREQ   R5, [R0,#0xC]\n"
          "STREQ   R5, [R0,#0x10]\n"
          "STREQ   R5, [R0,#0x14]\n"
          "MOV     R0, R6\n"
          "BL      sub_FF8565E8\n"
          "MOV     R0, R6\n"
          //"BL      sub_FF856814\n"
          "BL      sub_FF856814_my\n"            // +----> Hook for SDHC booting
          "MOV     R5, R0\n"
          "MOV     R0, R6\n"
          "BL      sub_FF856880\n" 
          "LDR     R1, [R4,#0x3C]\n"
          "AND     R2, R5, R0\n"
          "CMP     R1, #0\n"
          "MOV     R0, #0\n"
          "MOVEQ   R0, #0x80000001\n"
          "BEQ     loc_FF856A6C\n"
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

     "loc_FF856A6C:\n"
          "STR     R0, [R4,#0x40]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF856814_my() {
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
          //"BL      sub_FF8566AC\n"
          "BL      sub_FF8566AC_my\n"            // +----> Hook for SDHC booting
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "LDR     R0, [R4,#0x38]\n"
          "MOV     R1, R6\n"
          "BL      sub_FF857088\n"
          "CMP     R0, #0\n"
          "LDMEQFD SP!, {R4-R6,PC}\n"
          "MOV     R0, R6\n"
          "BL      sub_FF8561C8\n"
          "CMP     R0, #0\n"
          "MOVNE   R1, #1\n"
          "STRNE   R1, [R5,#0x10]\n"
          "LDMFD   SP!, {R4-R6,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF8566AC_my() {
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
          "B       loc_FF8567F8\n"

     "loc_FF8566DC:\n"
          "B       loc_FF856710\n"

     "loc_FF8566E0:\n"
          "B       loc_FF8566F8\n"

     "loc_FF8566E4:\n"
          "B       loc_FF8566F8\n"

     "loc_FF8566E8:\n"
          "B       loc_FF8566F8\n"

     "loc_FF8566EC:\n"
          "B       loc_FF8566F8\n"

     "loc_FF8566F0:\n"
          "B       loc_FF8567F0\n"

     "loc_FF8566F4:\n"
          "B       loc_FF8566F8\n"

     "loc_FF8566F8:\n"
          "MOV     R2, #0\n"
          "MOV     R1, #0x200\n"
          "MOV     R0, #3\n"
          "BL      sub_FF87178C\n"
          "MOVS    R4, R0\n"
          "BNE     loc_FF856718\n"

     "loc_FF856710:\n"
          "MOV     R0, #0\n"
          "LDMFD   SP!, {R4-R8,PC}\n"

     "loc_FF856718:\n"
          "LDR     R12, [R7,#0x4C]\n"
          "MOV     R3, R4\n"
          "MOV     R2, #1\n"
          "MOV     R1, #0\n"
          "MOV     R0, R8\n"
          //"BLX     R12\n"      // WORKSFORME, configure gcc WITHOUT --with-cpu=arm9
          "MOV     LR, PC\n"     // 2-op workaround for 'normal' compiler
          "MOV     PC, R12\n"    // Does the same thing, effectively, because PC is always 8 bytes ahead.
          "CMP     R0, #1\n"
          "BNE     loc_FF856744\n"
          "MOV     R0, #3\n"
          "BL      sub_FF87160C\n"
          "B       loc_FF856710\n"

///////
// Offsets are fixed from here on, everything +0x10 for the second entry
///////

     "loc_FF856744:\n"
          "MOV     R0, R8\n"
          "BL      sub_FF9445D4\n"

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
          "BNE     loc_FF8567CC\n"               // Jump out if the partition is malformed (partition status \'other\')
          "CMP     R0, R1\n"
          "BCC     loc_FF8567CC\n"               // Jump out if R0 < R1 (probably checking for a valid LBA addr)
          "ADD     R2, R1, R3\n"                 // R2 = partition start address + length = partition end address
          "CMP     R2, R0\n"                     // Guess: CMPLS is used to check for an overflow, the partition end address cannot be negative.
          "CMPLS   R12, #0x55\n"                 // Check MBR signature with original offset
          "CMPEQ   LR, #0xAA\n"                  // Check MBR signature with original offset
          "MOVEQ   R6, R1\n"
          "MOVEQ   R5, R3\n"
          "MOVEQ   R4, #1\n"

     "loc_FF8567CC:\n"
          "MOV     R0, #3\n"
          "BL      sub_FF87160C\n"
          "CMP     R4, #0\n"
          "BNE     loc_FF856804\n"
          "MOV     R6, #0\n"
          "MOV     R0, R8\n"
          "BL      sub_FF9445D4\n"
          "MOV     R5, R0\n"
          "B       loc_FF856804\n"

     "loc_FF8567F0:\n"
          "MOV     R5, #0x40\n"
          "B       loc_FF856804\n"

     "loc_FF8567F8:\n"
          "LDR     R1, =0x365\n"
          //"ADR     R0, aMounter_c\n"             // \"Mounter.c\"
          "LDR     R0, =0xFF8566A0\n"
          //"BL      Assert\n"
          "BL      sub_FF81BD94\n"

     "loc_FF856804:\n"
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
          "BL      sub_FF870C80\n" // _GetTimeOfSystem\n"
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
    //_qDump("A/firmdump", 0, (void*) 0xFFC00000, 0x00400000);
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
