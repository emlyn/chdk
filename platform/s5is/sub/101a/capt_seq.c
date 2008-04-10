#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (2)
#define NR_OFF (1)

static long raw_save_stage;

void capt_seq_hook_raw_here()
{
    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available();
    while (raw_save_stage != RAWDATA_SAVED){
	_SleepTask(10);
    }
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}


void capt_seq_hook_set_nr()
{
    long *nrflag = (long*)0xB704;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = 1;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = 2;
	break;
    };
}


///////////////////////////////////////////////
// Captseqtask bypass
// Functions are left intact, no jumps back to original firmware. Code is
// currently 40 kB (including comments, whitespace and such), about 11 kB 
// (including comments, whitespace and such) can be saved, so roughly 1/4.
// This is probably not worth it, as full functions might make debugging easier.
///////////////////////////////////////////////

void __attribute__((naked,noinline)) sub_FF826A50_my() { // called from init things
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "LDR     R4, =0x1D6C\n"
          "MOV     R0, #0\n"
          "MOV     R1, #4\n"
          "STR     R0, [R4,#8]\n"
          "BL      sub_FF81BCF4\n"
          "STR     R0, [R4]\n"
          "MOV     R0, #0\n"
          "MOV     R1, #1\n"
          "BL      sub_FF81BD18\n"
          "STR     R0, [R4,#4]\n"
          "BL      sub_FF869CD0\n"
          "BL      sub_FF868B08\n"
//          "BL      sub_FF865D68\n"               // Taskcreate_captseqtask called from this one
          "BL      sub_FF865D68_my\n"               // Taskcreate_captseqtask called from this one
          "BL      sub_FF869F98\n"
          "LDR     R0, [R4]\n"
          "LDMFD   SP!, {R4,LR}\n"
          "MOV     R1, #0x1000\n"
          "B       sub_FF82A33C\n"
     );
}

void __attribute__((naked,noinline)) sub_FF865D68_my() {
     asm volatile (

          "STMFD   SP!, {R3-R5,LR}\n"
          "LDR     R4, =0x59AC\n"
          "LDR     R0, [R4,#0x20]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF865E3C\n"
          //"BL      nullsub_20\n"
          "MOV     R1, #1\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BD18\n"
          "STR     R0, [R4,#0x38]\n"
          "MOV     R0, #0\n"
          "MOV     R1, #0\n"
          "BL      sub_FF81BCF4\n"
          "STR     R0, [R4,#0x3C]\n"
          "BL      sub_FF86614C\n"
          "MOV     R1, #0x14\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BCD0\n"
          "STR     R0, [R4,#0x2C]\n"
          "MOV     R0, #0\n"
          "MOV     R1, #1\n"
          "BL      sub_FF81BD18\n"
          "MOV     R1, #0\n"
          "STR     R0, [R4]\n"
          "BL      sub_FF81B860\n" // TakeSemaphore
          "LDR     R1, =0x1AA6C\n"
          "MOV     R0, #0\n"
          "MOV     R5, #0\n"

     "loc_FF865DD8:\n"                           // CODE XREF: sub_FF865D68+80j
          "ADD     R2, R1, R0,LSL#4\n"
          "ADD     R0, R0, #1\n"
          "CMP     R0, #6\n"
          "STR     R5, [R2,#0xC]\n"
          "BCC     loc_FF865DD8\n"
          "STR     R5, [R4,#0x30]\n"
          "LDR     R0, [R4]\n"
          "BL      sub_FF81B930\n" // GiveSemaphore
          "MOV     R3, #0\n"
          "STR     R3, [SP,#0x10-0x10]\n"
          //"ADR     R3, ShootSeqTask\n"
          "LDR     R3, =0xFF865CEC\n" // ShootSeqTask
          "MOV     R2, #0x1000\n"
          "MOV     R1, #0x17\n"
          //"ADR     R0, aShootseqtask\n"          // \"ShootSeqTask\"
          "LDR     R0, =0xFF866050\n" // aShootseqtask
          "BL      sub_FF81BC9C\n"
          "LDR     R0, =0x59EC\n"
          "MOV     R1, #0\n"
          "STR     R5, [R4,#0x34]\n"
          "STR     R1, [R0],#4\n"
          "STR     R1, [R0]\n"
          "BL      sub_FF866404\n"
          "BL      sub_FF86A128\n"
          "BL      sub_FF868504\n"
//          "BL      sub_FF867014\n" // taskcreate_CaptSeqTask
          "BL      sub_FF867014_my\n" // bypass taskcreate_CaptSeqTask
          "BL      sub_FF867E24\n"

     "loc_FF865E3C:\n"                           // CODE XREF: sub_FF865D68+10j
          "MOV     R0, #1\n"
          "STR     R0, [R4,#0x20]\n"
          "LDMFD   SP!, {R3-R5,PC}\n"

     );
}

void __attribute__((naked,noinline)) sub_FF867014_my() {
     asm volatile (
          "STMFD   SP!, {R3-R5,LR}\n"
          "LDR     R2, =0x1AC04\n"
          "MOV     R0, #0\n"
          "MOV     R1, #0\n"

     "loc_FF867024:\n"                           // CODE XREF: taskcreate_CaptSeqTask+20j
          "ADD     R3, R2, R0,LSL#4\n"
          "ADD     R0, R0, #1\n"
          "CMP     R0, #5\n"
          "STR     R1, [R3,#8]\n"
          "BCC     loc_FF867024\n"
          "LDR     R0, =0x1AC54\n"
          "STR     R1, [R0,#8]\n"
          "ADD     R0, R0, #0x10\n"
          "STR     R1, [R0,#8]\n"
          "BL      sub_FF95F6D4\n"
          "BL      sub_FF961960\n"
          "MOV     R1, #5\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BCD0\n"
          "LDR     R4, =0x5A14\n"
          "LDR     R1, =0x1001FF\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BCF4\n"
          "STR     R0, [R4,#0x10]\n"
          "MOV     R3, #0\n"
          "STR     R3, [SP,#0x10-0x10]\n"
          //"ADR     R3, CaptSeqTask\n"
          "ADR     R3, sub_FF866D48_my\n" // bypass CaptSeqTask
          //"ADR     R0, aCaptseqtask\n"           // \"CaptSeqTask\"
          "LDR     R0, =0xFF867228\n" // "CaptSeqTask"
          "MOV     R2, #0x1000\n"
          "MOV     R1, #0x17\n"
          "BL      sub_FF81BC9C\n"
          "LDMFD   SP!, {R3-R5,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF866D48_my() {
     asm volatile (
          "STMFD   SP!, {R3-R9,LR}\n"
          "LDR     R6, =0x1AC98\n"
          "LDR     R5, =0x5A14\n"
          "MOV     R9, #1\n"
          "MOV     R7, #0\n"

     "loc_FF866D5C:\n"                           // CODE XREF: CaptSeqTask+2C8j
          "LDR     R0, [R5,#0x14]\n"
          "MOV     R2, #0\n"
          "MOV     R1, SP\n"
          "BL      sub_FF82A5C0\n"
          "TST     R0, #1\n"
          "BEQ     loc_FF866D88\n"
          "LDR     R1, =0x415\n"
          "LDR     R0, =0xFF8667C8\n" //aSsshoottask_c\n"
          "BL      sub_FF81BD94\n" //assert\n"
          "BL      sub_FF81BC54\n" //ExitTask\n"
          "LDMFD   SP!, {R3-R9,PC}\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D88:\n"                           // CODE XREF: CaptSeqTask+28j
          "LDR     R0, [SP,#0x20-0x20]\n"
          "LDR     R1, [R0]\n"
          "CMP     R1, #0x1B\n"
          "ADDLS   PC, PC, R1,LSL#2\n"
          "B       loc_FF866FD8\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D9C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E0C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DA0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E7C\n"													// Entry 1: After shooting, while doing darkframesub (after shutter button?)
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DA4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E84\n"													// Entry 2: After shutter button release when already done shooting pic
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DA8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E9C\n"													// Entry 3: If shutter button not pressed
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DAC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E90\n"													// Entry 4: In timed image review
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DB0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EA4\n"													// Entry 5: In detailed image review
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DB4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EAC\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DB8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EB4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DBC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F0C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DC0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F18\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DC4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F20\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DC8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F28\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DCC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F30\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DD0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F38\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DD4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F40\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DD8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F48\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DDC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F50\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DE0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F58\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DE4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F60\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DE8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F68\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DEC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F70\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DF0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F7C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DF4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F88\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DF8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F90\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DFC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866FC0\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E00:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866FC8\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E04:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866FD0\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E08:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E0C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 0\n"
          "BL      sub_FF95F190\n"
          "BL      sub_FF864C5C\n"
          "LDR     R0, [R6,#0x24]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF866FE4\n"
          "BL      sub_FF8664A0\n"
          "MOV     R4, R0\n"
          "LDR     R0, [R6,#0x24]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF866E54\n"
          "MOV     R0, #0xC\n"
          "BL      sub_FF869C60\n"
          "TST     R0, #1\n"
          "STRNE   R9, [R5,#4]\n"
          "LDRNE   R0, [R4,#8]\n"
          "ORRNE   R0, R0, #0x40000000\n"
          "STRNE   R0, [R4,#8]\n"
          "BNE     loc_FF866FE4\n"

     "loc_FF866E54:\n"                           // CODE XREF: CaptSeqTask+E8j
          "MOV     R0, R4\n"
          "BL      sub_FF960B34\n"
          "BL      sub_FF9733B8\n"
          "BL      sub_FF8749E4\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, R4\n"
          "BL      sub_FF961054\n"
          "TST     R0, #1\n"
          "STRNE   R9, [R5,#4]\n"
          "B       loc_FF866FE4\n"

     "loc_FF866E7C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 1\n"       // According to the A720IS firmware, this is done after relasing the shutter (button?)
//          "BL      sub_FF866844\n"             // Bypass this and the camera will not properly shoot a picture, it will beep after a bit
          "BL      sub_FF866844_my\n"
          "B       loc_FF866E94\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E84:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 2\n"
          "MOV     R0, #1\n"
          "BL      sub_FF95F3D8\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E90:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 4\n"
          "BL      sub_FF95EF2C\n"

     "loc_FF866E94:\n"                           // CODE XREF: CaptSeqTask+138j
          "STR     R7, [R6,#0x24]\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E9C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 3\n"       // Points to prepareseq.c
          "BL      sub_FF95F15C\n"
          "B       loc_FF866E94\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EA4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 5\n"       // Points to prepareseq.c
          "BL      sub_FF95F164\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EAC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 6\n"
          "BL      sub_FF95F2C4\n"
          "B       loc_FF866F10\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EB4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 7\n"
          "LDR     R4, [R0,#0xC]\n"
          "BL      sub_FF95F16C\n" //UiEvnt_StartDisguiseCradleStatus_4\n"
          "MOV     R0, R4\n"
          "BL      sub_FF95FC9C\n"
          "TST     R0, #1\n"
          "MOV     R8, R0\n"
          "BNE     loc_FF866EF4\n"
          "BL      sub_FF8749E4\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, R4\n"
          "BL      sub_FF960F84\n"
          "MOV     R0, R4\n"
          "BL      sub_FF96143C\n"
          "MOV     R8, R0\n"
          "LDR     R0, [R4,#0x14]\n"
          "BL      sub_FF874BD8\n"

     "loc_FF866EF4:\n"                           // CODE XREF: CaptSeqTask+184j
          "BL      sub_FF95F15C\n"
          "MOV     R2, R4\n"
          "MOV     R1, #7\n"
          "MOV     R0, R8\n"
          "BL      sub_FF865098\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F0C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 8\n"
          "BL      sub_FF95F354\n"

     "loc_FF866F10:\n"                           // CODE XREF: CaptSeqTask+168j
          "BL      sub_FF864C5C\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F18:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 9\n"
          "BL      sub_FF95F15C\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F20:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 10\n"
          "BL      sub_FF95FEE8\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F28:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 11\n"
          "BL      sub_FF9600E4\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F30:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 12\n"
          "BL      sub_FF9601C8\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F38:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 13\n"
          "BL      sub_FF96027C\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F40:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 14\n"
          "BL      sub_FF9606E0\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F48:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 15\n"
          "BL      sub_FF960724\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F50:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 16\n"
          "MOV     R0, #0\n"
          "B       loc_FF866F74\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F58:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 17\n"
          "BL      sub_FF960898\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F60:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 18\n"
          "BL      sub_FF96092C\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F68:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 19\n"
          "BL      sub_FF9609E0\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F70:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 20\n"
          "MOV     R0, #1\n"

     "loc_FF866F74:\n"                           // CODE XREF: CaptSeqTask+20Cj
          "BL      sub_FF960778\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F7C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 21\n"
          "BL      sub_FF95F574\n"
          "BL      sub_FF8670FC\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F88:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 22\n"
          "BL      sub_FF9604F4\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F90:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 23\n"
          "MOV     R2, #2\n"
          "ADD     R1, R6, #0x58\n"
          "MOV     R0, #0x6F\n"
          "BL      sub_FF874864\n"
          "TST     R0, #1\n"
          "LDRNE   R0, =0xFF8667C8\n" //aSsshoottask_c\n"
          "MOVNE   R1, #0x4D0\n"
          "BLNE    sub_FF81BD94\n" //assert\n"
          "LDRH    R0, [R6,#0x58]\n"
          "CMP     R0, #1\n"
          "BLEQ    sub_FF9604E8\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866FC0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 24\n"
          "BL      sub_FF96062C\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866FC8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 25\n"
          "BL      sub_FF86672C\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866FD0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 26\n"
          "BL      sub_FF8269C4\n"
          "B       loc_FF866FE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866FD8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 default entry\n"
          "LDR     R1, =0x4F1\n"
          "LDR     R0, =0xFF8667C8\n" //aSsshoottask_c\n"
          "BL      sub_FF81BD94\n" //assert\n"

     "loc_FF866FE4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866D94 entry 27\n"
          "LDR     R0, [SP,#0x20-0x20]\n"
          "LDR     R1, [R0,#4]\n"
          "LDR     R0, [R5,#0x10]\n"
          "BL      sub_FF82A33C\n"
          "LDR     R4, [SP,#0x20-0x20]\n"
          "LDR     R0, [R4,#8]\n"
          "CMP     R0, #0\n"
          "LDREQ   R0, =0xFF8667C8\n" //aSsshoottask_c\n"
          "MOVEQ   R1, #0xF7\n"
          "BLEQ    sub_FF81BD94\n" //assert\n"
          "STR     R7, [R4,#8]\n"
          "B       loc_FF866D5C\n"
     ".ltorg\n"
     );
}


void __attribute((naked,noinline)) sub_FF866844_my() {
     asm volatile (
          "STMFD   SP!, {R4-R8,LR}\n"
          "LDR     R4, [R0,#0xC]\n"
          "LDR     R5, =0x1AC98\n"
          "LDR     R0, [R4,#8]\n"
          "LDR     R6, =0x820A\n"
          "ORR     R0, R0, #1\n"
          "STR     R0, [R4,#8]\n"
          "LDRH    R0, [R5]\n"
          "LDR     R8, =0x5A14\n"
          "MOV     R7, #0\n"
          "CMP     R0, R6\n"
          "BEQ     loc_FF8668E8\n"
          "LDRH    R0, [R5,#0x88]\n"
          "CMP     R0, #3\n"
          "BEQ     loc_FF86693C\n"
          "LDR     R0, [R4,#0xC]\n"
          "CMP     R0, #1\n"
          "BLS     loc_FF8668F4\n"
          "LDRH    R0, [R5,#0x86]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF86693C\n"
          "LDRH    R0, [R5,#0x82]\n"
          "CMP     R0, #2\n"
          "BNE     loc_FF866900\n"
          "BL      sub_FF95F628\n"
          "LDRH    R0, [R5]\n"
          "CMP     R0, R6\n"
          "BEQ     loc_FF8668E8\n"
          "LDRH    R0, [R5,#0x88]\n"
          "CMP     R0, #3\n"
          "BEQ     loc_FF86693C\n"
          "LDR     R0, [R4,#0xC]\n"
          "CMP     R0, #1\n"
          "BLS     loc_FF8668F4\n"
          "LDRH    R0, [R5,#0x86]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF86693C\n"
          "LDRH    R0, [R5,#0x82]\n"
          "CMP     R0, #2\n"
          "BEQ     loc_FF86692C\n"
          "B       loc_FF866900\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF8668E8:\n"                           // CODE XREF: sub_FF866844+2Cj
          " \n"                                  // sub_FF866844+6Cj
          "LDRH    R0, [R5,#0x88]\n"
          "CMP     R0, #3\n"
          "BEQ     loc_FF86693C\n"

     "loc_FF8668F4:\n"                           // CODE XREF: sub_FF866844+44j
          " \n"                                  // sub_FF866844+84j
          "LDRH    R0, [R5,#0x86]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF86693C\n"

     "loc_FF866900:\n"                           // CODE XREF: sub_FF866844+5Cj
          " \n"                                  // sub_FF866844+A0j
          "LDRH    R0, [R5,#0x82]\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF86693C\n"
          "LDRH    R0, [R5]\n"
          "CMP     R0, R6\n"
          "LDRNE   R0, [R4,#0xC]\n"
          "CMPNE   R0, #1\n"
          "BLS     loc_FF86693C\n"
          "LDR     R0, [R4,#0x10]\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF86693C\n"

     "loc_FF86692C:\n"                           // CODE XREF: sub_FF866844+9Cj
          "LDR     R2, =0xEA60\n"
          "LDR     R0, [R8,#0x10]\n"
          "MOV     R1, #0x40000000\n"
          "BL      sub_FF869FC0\n"

     "loc_FF86693C:\n"                           // CODE XREF: sub_FF866844+38j
          " \n"                                  // sub_FF866844+50j ...
          "BL      sub_FF86672C\n"
          "LDR     R0, [R5,#0x24]\n"
          "CMP     R0, #0\n"
          "MOVEQ   R0, #2\n"
          "BLEQ    sub_FF85FD44\n"
          "BL      sub_FF95F16C\n" // UiEvnt_StartDisguiseCradleStatus_4\n"
          "LDR     R0, [R4,#0x18]\n"
          "CMP     R0, #0\n"
          "BLNE    sub_FF861FF0\n"
          "LDR     R0, [R5,#0x24]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF8669B8\n"
          "MOV     R0, R4\n"
          "BL      sub_FF960B34\n"
          "MOV     R0, R4\n"
          "BL      sub_FF95F8B8\n"
          "TST     R0, #1\n"
          "MOVNE   R2, R4\n"
//          "LDMFDNE SP!, {R4-R8,LR}\n"
          "LDMNEFD SP!, {R4-R8,LR}\n"
          "MOVNE   R1, #1\n"
          "BNE     sub_FF865098\n"
          "BL      sub_FF9733B8\n"

          "BL      shooting_expo_param_override\n"  // +-----------> Override Canon stuff :)

          "BL      sub_FF8749E4\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, R4\n"
          "BL      sub_FF960F84\n"
          "BL      sub_FF961874\n"
          "MOV     R0, R4\n"
//          "BL      sub_FF961054\n" // This is where shooting AND darkframe sub is done
          "BL      sub_FF961054_my\n" // so hook it
          "MOV     R7, R0\n"

          "BL      capt_seq_hook_raw_here\n" // +-----------> Capture RAW, camera already did badpixel-sub (always) though some pixels are still there

          "B       loc_FF8669C4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF8669B8:\n"                           // CODE XREF: sub_FF866844+124j
          "LDR     R0, [R8,#4]\n"
          "CMP     R0, #0\n"
          "MOVNE   R7, #0x1D\n"

     "loc_FF8669C4:\n"                           // CODE XREF: sub_FF866844+170j
          "MOV     R2, R4\n"
          "MOV     R1, #1\n"
          "MOV     R0, R7\n"
          "BL      sub_FF865098\n"
          "BL      sub_FF9613DC\n"
          "CMP     R0, #0\n"
          "LDRNE   R0, [R4,#8]\n"
          "ORRNE   R0, R0, #0x2000\n"
          "STRNE   R0, [R4,#8]\n"
          "LDR     R0, [R4,#0x18]\n"
          "CMP     R0, #0\n"
          "BLNE    sub_FF862008\n"
          "LDRH    R0, [R5,#0x88]\n"
          "CMP     R0, #3\n"
//          "LDMFDEQ SP!, {R4-R8,PC}\n"
          "LDMEQFD SP!, {R4-R8,PC}\n"
          "LDRH    R0, [R5,#0x86]\n"
          "CMP     R0, #0\n"
//          "LDRHEQ  R0, [R5,#0x82]\n"
          "LDREQH  R0, [R5,#0x82]\n"
          "CMPEQ   R0, #2\n"
          "MOVEQ   R0, R4\n"
//          "LDMFDEQ SP!, {R4-R8,LR}\n"
          "LDMEQFD SP!, {R4-R8,LR}\n"
          "BEQ     sub_FF95F670\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
	".ltorg\n"
     );
}

void __attribute__((naked,noinline)) sub_FF961054_my() {
     asm volatile (
          "STMFD   SP!, {R0-R8,LR}\n"
          "MOV     R4, R0\n"
          "BL      sub_FF9619B0\n"
          "MVN     R1, #0\n"
          "BL      sub_FF82A370\n"
          "MOV     R2, #4\n"
          "ADD     R1, SP, #0x28-0x20\n"
          "MOV     R0, #0x8A\n"
          "BL      sub_FF874864\n"
          "TST     R0, #1\n"
          "LDRNE   R1, =0x1D2\n"
//          "ADRNE   R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDRNE   R0, =0xFF96126C\n"
          "BLNE    sub_FF81BD94\n" // assert\n"
          "LDR     R6, =0x1AD48\n"
          "LDR     R7, =0x1AC98\n"
          "LDRSH   R1, [R6,#0xE]\n"
          "LDR     R0, [R7,#0x7C]\n"
//          "BL      nullsub_70\n"
          "BL      sub_FF8505BC\n" //GetCCDTemperature\n"
          "LDR     R2, =0xB708\n"
          "ADD     R3, R4, #0x78\n"
          "STRH    R0, [R4,#0x74]\n"
//          "STRD    R2, [SP,#0x28-0x28]\n"  // WORKSFORME, configure gcc WITHOUT --with-cpu=arm9
          "STR    R2, [SP,#0x28-0x28]\n"     // Though use the old, 2-line version
          "STR    R3, [SP,#0x28-0x24]\n"     // for the final until everyone uses 'new' gcc
          "MOV     R1, R0\n"
          "LDRH    R0, [R7,#0x54]\n"
          "LDRSH   R2, [R6,#0xC]\n"
          "LDR     R3, =0xB704\n"

          "BL      sub_FFA40388\n" // 2 (NR) is set into 0xB704 in this sub! Still before shooting

          "BL      capt_seq_hook_set_nr\n" // +-----------> so immediately override NR

          "LDR     R0, [R4,#0x18]\n"
          "LDR     R1, =0xB704\n"
          "CMP     R0, #0\n"
          "MOV     R8, #1\n"
          "BEQ     loc_FF9610E4\n"
          "LDR     R0, [R1]\n"
          "CMP     R0, #2\n"
          "STREQ   R8, [R1]\n"

     "loc_FF9610E4:\n"                           // CODE XREF: sub_FF961054+80j
          "LDR     R0, [R1,#4]\n"
          "MOV     R5, R1\n"
          "BL      sub_FF850AD8\n"
          "LDR     R0, [R5]\n"
          "MOV     R1, #0\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF96115C\n"
          "STR     R1, [SP,#0x28-0x1C]\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R1, #0x33\n"
          "MOV     R3, #2\n"
          "ADD     R2, SP, #0x28-0x1C\n"
          "BL      sub_FF874CD0\n"
          "LDR     R0, [R4,#8]\n"
//          "ADR     R3, sub_FF960DE8\n"
          "LDR     R3, =0xFF960DE8\n"
          "ORR     R0, R0, #0x40\n"
          "STR     R0, [R4,#8]\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "STR     R4, [SP,#0x28-0x28]\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
          "MOV     R2, R4\n"
//          "ADR     R1, sub_FF960D68\n"
          "LDR     R1, =0xFF960D68\n"
          "BEQ     loc_FF96114C\n"
          "BL      sub_FF9D03DC\n"
          "B       loc_FF961150\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF96114C:\n"                           // CODE XREF: sub_FF961054+ECj
          "BL      sub_FF8BA418\n"

     "loc_FF961150:\n"                           // CODE XREF: sub_FF961054+F4j
          " \n"                                  // sub_FF961054+2ACj ...
          "TST     R0, #1\n"
          "BEQ     loc_FF961324\n"
          "B       loc_FF96130C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF96115C:\n"                           // CODE XREF: sub_FF961054+A8j
          "CMP     R0, #2\n"
          "BNE     loc_FF9612AC\n"
          "STR     R1, [SP,#0x28-0x28+4]\n" // start shooting with darkframe
          "STR     R8, [SP,#0x28-0x1C]\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R1, #0x33\n"
          "MOV     R3, #2\n"
          "ADD     R2, SP, #0x28-0x1C\n"
          "BL      sub_FF874CD0\n"
          "LDR     R0, [R4,#8]\n"
          "LDR     R1, =0xFF960D68\n"
          "ORR     R0, R0, #0x80\n"
          "STR     R0, [R4,#8]\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "STR     R4, [SP,#0x28-0x28]\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
//          "ADR     R3, locret_FF960E78\n"
          "LDR     R3, =0xFF960F40\n"
          "MOV     R2, R4\n"
          "BEQ     loc_FF9611B4\n"
          "BL      sub_FF9D03E4\n"
          "B       loc_FF9611B8\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF9611B4:\n"                           // CODE XREF: sub_FF961054+154j
          "BL      sub_FF8BA498\n"

     "loc_FF9611B8:\n"                           // CODE XREF: sub_FF961054+15Cj
          "TST     R0, #1\n"
          "BNE     loc_FF96130C\n"
          "MOV     R1, #0\n"
          "MOV     R0, #0x44\n"
          "BL      sub_FF886C08\n"
          "LDR     R0, [R4,#8]\n"
          "ORR     R0, R0, #0x100\n"
          "STR     R0, [R4,#8]\n"
          "BL      sub_FF8BA414\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "LDR     R1, =0xFF960DE8\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
          "MOV     R2, R4\n"
          "BEQ     loc_FF9611FC\n"
          "BL      sub_FF9D03F4\n"
          "B       loc_FF961200\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF9611FC:\n"                           // CODE XREF: sub_FF961054+19Cj
          "BL      sub_FF8BA5C4\n"

     "loc_FF961200:\n"                           // CODE XREF: sub_FF961054+1A4j
          "TST     R0, #1\n"
          "BNE     loc_FF96130C\n"
          "MOV     R2, #2\n"
          "ADD     R1, SP, #0x28-0x28+4\n"
          "MOV     R0, #0xD8\n"
          "BL      sub_FF874864\n"
          "TST     R0, #1\n"
          "LDRNE   R1, =0x24E\n"
//          "ADRNE   R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDRNE   R0, =0xFF96126C\n"
          "BLNE    sub_FF81BD94\n" // assert\n"
          "LDR     R0, [R4,#0x78]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF961324\n"
          "LDR     R0, [R6]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF96124C\n"
          "LDRH    R0, [SP,#0x28-0x28+4]\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF961324\n"

     "loc_FF96124C:\n"                           // CODE XREF: sub_FF961054+1E8j
          "MOV     R1, #0\n"
          "MOV     R0, #0x45\n"
          "BL      sub_FF886C08\n"
          "B       loc_FF961324\n"
          "@ ---------------------------------------------------------------------------\n"
          
          ".ltorg\n" // Shut up stupid compiler/assembler manually
          
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF9612AC:\n"                           // CODE XREF: sub_FF961054+10Cj
          "CMP     R0, #3\n"
          "BNE     loc_FF961318\n"
          "MOV     R0, #2\n"
          "STR     R0, [SP,#0x28-0x1C]\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R3, #2\n"
          "ADD     R2, SP, #0x28-0x1C\n"
          "MOV     R1, #0x33\n"
          "BL      sub_FF874CD0\n"
          "LDR     R0, [R4,#8]\n"
          "LDR     R3, =0xFF960DE8\n"
          "ORR     R0, R0, #0x200\n"
          "STR     R0, [R4,#8]\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "STR     R4, [SP,#0x28-0x28]\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
          "LDR     R1, =0xFF960D68\n"
          "MOV     R2, R4\n"
          "BEQ     loc_FF961304\n"
          "BL      sub_FF9D03EC\n"
          "B       loc_FF961150\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF961304:\n"                           // CODE XREF: sub_FF961054+2A4j
          "BL      sub_FF8BA544\n"
          "B       loc_FF961150\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF96130C:\n"                           // CODE XREF: sub_FF961054+104j
          " \n"                                  // sub_FF961054+168j ...
          "MOV     R0, #0x1D\n"

     "loc_FF961310:\n"                           // CODE XREF: sub_FF961054+384j
          "ADD     SP, SP, #0x10\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF961318:\n"                           // CODE XREF: sub_FF961054+25Cj
          "LDR     R1, =0x279\n"
//          "ADR     R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDR     R0, =0xFF96126C\n"
          "BL      sub_FF81BD94\n" //assert\n"

     "loc_FF961324:\n"                           // CODE XREF: sub_FF961054+100j
          " \n"                                  // sub_FF961054+1DCj ...
          "LDR     R2, =0xB708\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R3, #4\n"
          "MOV     R1, #0x45\n"
          "BL      sub_FF874CD0\n"
          "MOV     R0, #1\n"
          "BL      sub_FF91C114\n"
          "STR     R0, [R4,#0x98]\n"
          "BL      sub_FF868688\n"
          "LDRH    R0, [R7]\n"
          "LDR     R12, =0x820A\n"
          "CMP     R0, R12\n"
//          "LDRHNE  R0, [R7,#0x88]\n"
          "LDRNEH  R0, [R7,#0x88]\n"
          "MOVNE   R1, R7\n"
          "CMPNE   R0, #3\n"
          "LDRNE   R0, [R4,#0xC]\n"
          "CMPNE   R0, #1\n"
          "BLS     loc_FF9613B4\n"
          "LDRH    R2, [R1,#0x86]\n"
          "CMP     R2, #0\n"
          "BNE     loc_FF961398\n"
          "LDRH    R0, [R1,#0x82]\n"
          "CMP     R0, #1\n"
          "CMPNE   R0, #2\n"
          "BEQ     loc_FF961398\n"
          "CMP     R0, #3\n"
//          "LDRHEQ  R0, [R1,#0x8A]\n"
          "LDREQH  R0, [R1,#0x8A]\n"
          "CMPEQ   R0, #2\n"
          "BNE     loc_FF9613D4\n"

     "loc_FF961398:\n"                           // CODE XREF: sub_FF961054+320j
          " \n"                                  // sub_FF961054+330j
          "LDR     R0, [R4,#0x10]\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF9613B4\n"
          "CMP     R2, #0\n"
//          "LDRHEQ  R0, [R1,#0x82]\n"
          "LDREQH  R0, [R1,#0x82]\n"
          "CMPEQ   R0, #2\n"
          "BNE     loc_FF9613D4\n"

     "loc_FF9613B4:\n"                           // CODE XREF: sub_FF961054+314j
          " \n"                                  // sub_FF961054+34Cj
          "BL      sub_FF9619B0\n"
          "LDR     R2, =0x2710\n"
          "MOV     R1, #4\n"
          "BL      sub_FF869FC0\n"
          "CMP     R0, #0\n"
          "LDRNE   R1, =0x286\n"
//          "ADRNE   R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDRNE   R0, =0xFF96126C\n"
          "BLNE    sub_FF81BD94\n" // assert\n"

     "loc_FF9613D4:\n"                           // CODE XREF: sub_FF961054+340j
          " \n"                                  // sub_FF961054+35Cj
          "MOV     R0, #0\n"
          "B       loc_FF961310\n"
     ".ltorg\n"
     );
}
