#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0xB704;

#include "../../../generic/capt_seq.c"

///////////////////////////////////////////////
// Captseqtask bypass
// Functions are left intact, no jumps back to original firmware. Code is
// currently 40 kB (including comments, whitespace and such), about 11 kB 
// (including comments, whitespace and such) can be saved, so roughly 1/4.
// This is probably not worth it, as full functions might make debugging easier.
///////////////////////////////////////////////

void __attribute__((naked,noinline)) sub_FF826988_my() { // called from init things
     asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "LDR     R4, =0x1D6C\n"
          "MOV     R0, #0\n"
          "MOV     R1, #4\n"
          "STR     R0, [R4,#8]\n"
          "BL      sub_FF81BC2C\n"
          "STR     R0, [R4]\n"
          "MOV     R0, #0\n"
          "MOV     R1, #1\n"
          "BL      sub_FF81BC50\n"
          "STR     R0, [R4,#4]\n"
          "BL      sub_FF869C08\n"
          "BL      sub_FF868A40\n"
//          "BL      sub_FF865CA0\n"               // Taskcreate_captseqtask called from this one
          "BL      sub_FF865CA0_my\n"               // Taskcreate_captseqtask called from this one
          "BL      sub_FF869ED0\n"
          "LDR     R0, [R4]\n"
          "LDMFD   SP!, {R4,LR}\n"
          "MOV     R1, #0x1000\n"
          "B       sub_FF82A274\n"
     );
}

void __attribute__((naked,noinline)) sub_FF865CA0_my() {
     asm volatile (

          "STMFD   SP!, {R3-R5,LR}\n"
          "LDR     R4, =0x59AC\n"
          "LDR     R0, [R4,#0x20]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF865D74\n"
          //"BL      nullsub_20\n"
          "MOV     R1, #1\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BC50\n"
          "STR     R0, [R4,#0x38]\n"
          "MOV     R0, #0\n"
          "MOV     R1, #0\n"
          "BL      sub_FF81BC2C\n"
          "STR     R0, [R4,#0x3C]\n"
          "BL      sub_FF866084\n"
          "MOV     R1, #0x14\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BC08\n"
          "STR     R0, [R4,#0x2C]\n"
          "MOV     R0, #0\n"
          "MOV     R1, #1\n"
          "BL      sub_FF81BC50\n"
          "MOV     R1, #0\n"
          "STR     R0, [R4]\n"
          "BL      sub_FF81B798\n" // TakeSemaphore
          "LDR     R1, =0x1AA6C\n"
          "MOV     R0, #0\n"
          "MOV     R5, #0\n"

     "loc_FF865D10:\n"                           // CODE XREF: sub_FF865CA0+80j
          "ADD     R2, R1, R0,LSL#4\n"
          "ADD     R0, R0, #1\n"
          "CMP     R0, #6\n"
          "STR     R5, [R2,#0xC]\n"
          "BCC     loc_FF865D10\n"
          "STR     R5, [R4,#0x30]\n"
          "LDR     R0, [R4]\n"
          "BL      sub_FF81B868\n" // GiveSemaphore
          "MOV     R3, #0\n"
          "STR     R3, [SP,#0x10-0x10]\n"
          //"ADR     R3, ShootSeqTask\n"
          "LDR     R3, =0xFF865C24\n" // ShootSeqTask
          "MOV     R2, #0x1000\n"
          "MOV     R1, #0x17\n"
          //"ADR     R0, aShootseqtask\n"          // \"ShootSeqTask\"
          "LDR     R0, =0xFF865F88\n" // aShootseqtask
          "BL      sub_FF81BBD4\n"
          "LDR     R0, =0x59EC\n"
          "MOV     R1, #0\n"
          "STR     R5, [R4,#0x34]\n"
          "STR     R1, [R0],#4\n"
          "STR     R1, [R0]\n"
          "BL      sub_FF86633C\n"
          "BL      sub_FF86A060\n"
          "BL      sub_FF86843C\n"
//          "BL      sub_FF866F4C\n" // taskcreate_CaptSeqTask
          "BL      sub_FF866F4C_my\n" // bypass taskcreate_CaptSeqTask
          "BL      sub_FF867D5C\n"

     "loc_FF865D74:\n"                           // CODE XREF: sub_FF865CA0+10j
          "MOV     R0, #1\n"
          "STR     R0, [R4,#0x20]\n"
          "LDMFD   SP!, {R3-R5,PC}\n"

     );
}

void __attribute__((naked,noinline)) sub_FF866F4C_my() {
     asm volatile (
          "STMFD   SP!, {R3-R5,LR}\n"
          "LDR     R2, =0x1AC04\n"
          "MOV     R0, #0\n"
          "MOV     R1, #0\n"

     "loc_FF866F5C:\n"                           // CODE XREF: taskcreate_CaptSeqTask+20j
          "ADD     R3, R2, R0,LSL#4\n"
          "ADD     R0, R0, #1\n"
          "CMP     R0, #5\n"
          "STR     R1, [R3,#8]\n"
          "BCC     loc_FF866F5C\n"
          "LDR     R0, =0x1AC54\n"
          "STR     R1, [R0,#8]\n"
          "ADD     R0, R0, #0x10\n"
          "STR     R1, [R0,#8]\n"
          "BL      sub_FF95F60C\n"
          "BL      sub_FF961898\n"
          "MOV     R1, #5\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BC08\n"
          "LDR     R4, =0x5A14\n"
          "LDR     R1, =0x1001FF\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, #0\n"
          "BL      sub_FF81BC2C\n"
          "STR     R0, [R4,#0x10]\n"
          "MOV     R3, #0\n"
          "STR     R3, [SP,#0x10-0x10]\n"
          //"ADR     R3, CaptSeqTask\n"
          "ADR     R3, sub_FF866C80_my\n" // bypass CaptSeqTask
          //"ADR     R0, aCaptseqtask\n"           // \"CaptSeqTask\"
          "LDR     R0, =0xFF867160\n" // "CaptSeqTask"
          "MOV     R2, #0x1000\n"
          "MOV     R1, #0x17\n"
          "BL      sub_FF81BBD4\n"
          "LDMFD   SP!, {R3-R5,PC}\n"
     );
}

void __attribute__((naked,noinline)) sub_FF866C80_my() {
     asm volatile (
          "STMFD   SP!, {R3-R9,LR}\n"
          "LDR     R6, =0x1AC98\n"
          "LDR     R5, =0x5A14\n"
          "MOV     R9, #1\n"
          "MOV     R7, #0\n"

     "loc_FF866C94:\n"                           // CODE XREF: CaptSeqTask+2C8j
          "LDR     R0, [R5,#0x14]\n"
          "MOV     R2, #0\n"
          "MOV     R1, SP\n"
          "BL      sub_FF82A4F8\n"
          "TST     R0, #1\n"
          "BEQ     loc_FF866CC0\n"
          "LDR     R1, =0x415\n"
          "LDR     R0, =0xFF866700\n" //aSsshoottask_c\n"
          "BL      sub_FF81BCCC\n" //assert\n"
          "BL      sub_FF81BB8C\n" //ExitTask\n"
          "LDMFD   SP!, {R3-R9,PC}\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CC0:\n"                           // CODE XREF: CaptSeqTask+28j
          "LDR     R0, [SP,#0x20-0x20]\n"
          "LDR     R1, [R0]\n"
          "CMP     R1, #0x1B\n"
          "ADDLS   PC, PC, R1,LSL#2\n"
          "B       loc_FF866F10\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CD4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866D44\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CD8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866DB4\n"													// Entry 1: After shooting, while doing darkframesub (after shutter button?)
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CDC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866DBC\n"													// Entry 2: After shutter button release when already done shooting pic
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CE0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866DD4\n"													// Entry 3: If shutter button not pressed
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CE4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866DC8\n"													// Entry 4: In timed image review
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CE8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866DDC\n"													// Entry 5: In detailed image review
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CEC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866DE4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CF0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866DEC\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CF4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E44\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CF8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E50\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866CFC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E58\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D00:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E60\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D04:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E68\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D08:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E70\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D0C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E78\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D10:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E80\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D14:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E88\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D18:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E90\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D1C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866E98\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D20:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EA0\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D24:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EA8\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D28:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EB4\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D2C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EC0\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D30:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EC8\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D34:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866EF8\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D38:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F00\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D3C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F08\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D40:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866D44:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 0\n"
          "BL      sub_FF95F0C8\n"
          "BL      sub_FF864B94\n"
          "LDR     R0, [R6,#0x24]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF866F1C\n"
          "BL      sub_FF8663D8\n"
          "MOV     R4, R0\n"
          "LDR     R0, [R6,#0x24]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF866D8C\n"
          "MOV     R0, #0xC\n"
          "BL      sub_FF869B98\n"
          "TST     R0, #1\n"
          "STRNE   R9, [R5,#4]\n"
          "LDRNE   R0, [R4,#8]\n"
          "ORRNE   R0, R0, #0x40000000\n"
          "STRNE   R0, [R4,#8]\n"
          "BNE     loc_FF866F1C\n"

     "loc_FF866D8C:\n"                           // CODE XREF: CaptSeqTask+E8j
          "MOV     R0, R4\n"
          "BL      sub_FF960A6C\n"
          "BL      sub_FF9732F0\n"
          "BL      sub_FF87491C\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, R4\n"
          "BL      sub_FF960F8C\n"
          "TST     R0, #1\n"
          "STRNE   R9, [R5,#4]\n"
          "B       loc_FF866F1C\n"

     "loc_FF866DB4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 1\n"       // According to the A720IS firmware, this is done after relasing the shutter (button?)
//          "BL      sub_FF86677C\n"             // Bypass this and the camera will not properly shoot a picture, it will beep after a bit
          "BL      sub_FF86677C_my\n"
          "B       loc_FF866DCC\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DBC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 2\n"
          "MOV     R0, #1\n"
          "BL      sub_FF95F310\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DC8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 4\n"
          "BL      sub_FF95EE64\n"

     "loc_FF866DCC:\n"                           // CODE XREF: CaptSeqTask+138j
          "STR     R7, [R6,#0x24]\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DD4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 3\n"       // Points to prepareseq.c
          "BL      sub_FF95F094\n"
          "B       loc_FF866DCC\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DDC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 5\n"       // Points to prepareseq.c
          "BL      sub_FF95F09C\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DE4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 6\n"
          "BL      sub_FF95F1FC\n"
          "B       loc_FF866E48\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866DEC:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 7\n"
          "LDR     R4, [R0,#0xC]\n"
          "BL      sub_FF95F0A4\n" //UiEvnt_StartDisguiseCradleStatus_4\n"
          "MOV     R0, R4\n"
          "BL      sub_FF95FBD4\n"
          "TST     R0, #1\n"
          "MOV     R8, R0\n"
          "BNE     loc_FF866E2C\n"
          "BL      sub_FF87491C\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, R4\n"
          "BL      sub_FF960EBC\n"
          "MOV     R0, R4\n"
          "BL      sub_FF961374\n"
          "MOV     R8, R0\n"
          "LDR     R0, [R4,#0x14]\n"
          "BL      sub_FF874B10\n"

     "loc_FF866E2C:\n"                           // CODE XREF: CaptSeqTask+184j
          "BL      sub_FF95F094\n"
          "MOV     R2, R4\n"
          "MOV     R1, #7\n"
          "MOV     R0, R8\n"
          "BL      sub_FF864FD0\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E44:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 8\n"
          "BL      sub_FF95F28C\n"

     "loc_FF866E48:\n"                           // CODE XREF: CaptSeqTask+168j
          "BL      sub_FF864B94\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E50:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 9\n"
          "BL      sub_FF95F094\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E58:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 10\n"
          "BL      sub_FF95FE20\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E60:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 11\n"
          "BL      sub_FF96001C\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E68:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 12\n"
          "BL      sub_FF960100\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E70:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 13\n"
          "BL      sub_FF9601B4\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E78:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 14\n"
          "BL      sub_FF960618\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E80:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 15\n"
          "BL      sub_FF96065C\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E88:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 16\n"
          "MOV     R0, #0\n"
          "B       loc_FF866EAC\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E90:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 17\n"
          "BL      sub_FF9607D0\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866E98:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 18\n"
          "BL      sub_FF960864\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EA0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 19\n"
          "BL      sub_FF960918\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EA8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 20\n"
          "MOV     R0, #1\n"

     "loc_FF866EAC:\n"                           // CODE XREF: CaptSeqTask+20Cj
          "BL      sub_FF9606B0\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EB4:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 21\n"
          "BL      sub_FF95F4AC\n"
          "BL      sub_FF867034\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EC0:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 22\n"
          "BL      sub_FF96042C\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EC8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 23\n"
          "MOV     R2, #2\n"
          "ADD     R1, R6, #0x58\n"
          "MOV     R0, #0x6F\n"
          "BL      sub_FF87479C\n"
          "TST     R0, #1\n"
          "LDRNE   R0, =0xFF866700\n" //aSsshoottask_c\n"
          "MOVNE   R1, #0x4D0\n"
          "BLNE    sub_FF81BCCC\n" //assert\n"
          "LDRH    R0, [R6,#0x58]\n"
          "CMP     R0, #1\n"
          "BLEQ    sub_FF960420\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866EF8:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 24\n"
          "BL      sub_FF960564\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F00:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 25\n"
          "BL      sub_FF866664\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F08:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 26\n"
          "BL      sub_FF8268FC\n"
          "B       loc_FF866F1C\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866F10:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC default entry\n"
          "LDR     R1, =0x4F1\n"
          "LDR     R0, =0xFF866700\n" //aSsshoottask_c\n"
          "BL      sub_FF81BCCC\n" //assert\n"

     "loc_FF866F1C:\n"                           // CODE XREF: CaptSeqTask+4Cj
          "@ jumptable FF866CCC entry 27\n"
          "LDR     R0, [SP,#0x20-0x20]\n"
          "LDR     R1, [R0,#4]\n"
          "LDR     R0, [R5,#0x10]\n"
          "BL      sub_FF82A274\n"
          "LDR     R4, [SP,#0x20-0x20]\n"
          "LDR     R0, [R4,#8]\n"
          "CMP     R0, #0\n"
          "LDREQ   R0, =0xFF866700\n" //aSsshoottask_c\n"
          "MOVEQ   R1, #0xF7\n"
          "BLEQ    sub_FF81BCCC\n" //assert\n"
          "STR     R7, [R4,#8]\n"
          "B       loc_FF866C94\n"
     ".ltorg\n"
     );
}


void __attribute((naked,noinline)) sub_FF86677C_my() {
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
          "BEQ     loc_FF866820\n"
          "LDRH    R0, [R5,#0x88]\n"
          "CMP     R0, #3\n"
          "BEQ     loc_FF866874\n"
          "LDR     R0, [R4,#0xC]\n"
          "CMP     R0, #1\n"
          "BLS     loc_FF86682C\n"
          "LDRH    R0, [R5,#0x86]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF866874\n"
          "LDRH    R0, [R5,#0x82]\n"
          "CMP     R0, #2\n"
          "BNE     loc_FF866838\n"
          "BL      sub_FF95F560\n"
          "LDRH    R0, [R5]\n"
          "CMP     R0, R6\n"
          "BEQ     loc_FF866820\n"
          "LDRH    R0, [R5,#0x88]\n"
          "CMP     R0, #3\n"
          "BEQ     loc_FF866874\n"
          "LDR     R0, [R4,#0xC]\n"
          "CMP     R0, #1\n"
          "BLS     loc_FF86682C\n"
          "LDRH    R0, [R5,#0x86]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF866874\n"
          "LDRH    R0, [R5,#0x82]\n"
          "CMP     R0, #2\n"
          "BEQ     loc_FF866864\n"
          "B       loc_FF866838\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF866820:\n"                           // CODE XREF: sub_FF86677C+2Cj
          " \n"                                  // sub_FF86677C+6Cj
          "LDRH    R0, [R5,#0x88]\n"
          "CMP     R0, #3\n"
          "BEQ     loc_FF866874\n"

     "loc_FF86682C:\n"                           // CODE XREF: sub_FF86677C+44j
          " \n"                                  // sub_FF86677C+84j
          "LDRH    R0, [R5,#0x86]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF866874\n"

     "loc_FF866838:\n"                           // CODE XREF: sub_FF86677C+5Cj
          " \n"                                  // sub_FF86677C+A0j
          "LDRH    R0, [R5,#0x82]\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF866874\n"
          "LDRH    R0, [R5]\n"
          "CMP     R0, R6\n"
          "LDRNE   R0, [R4,#0xC]\n"
          "CMPNE   R0, #1\n"
          "BLS     loc_FF866874\n"
          "LDR     R0, [R4,#0x10]\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF866874\n"

     "loc_FF866864:\n"                           // CODE XREF: sub_FF86677C+9Cj
          "LDR     R2, =0xEA60\n"
          "LDR     R0, [R8,#0x10]\n"
          "MOV     R1, #0x40000000\n"
          "BL      sub_FF869EF8\n"

     "loc_FF866874:\n"                           // CODE XREF: sub_FF86677C+38j
          " \n"                                  // sub_FF86677C+50j ...
          "BL      sub_FF866664\n"
          "LDR     R0, [R5,#0x24]\n"
          "CMP     R0, #0\n"
          "MOVEQ   R0, #2\n"
          "BLEQ    sub_FF85FC7C\n"
          "BL      sub_FF95F0A4\n" // UiEvnt_StartDisguiseCradleStatus_4\n"
          "LDR     R0, [R4,#0x18]\n"
          "CMP     R0, #0\n"
          "BLNE    sub_FF861F28\n"
          "LDR     R0, [R5,#0x24]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF8668F0\n"
          "MOV     R0, R4\n"
          "BL      sub_FF960A6C\n"
          "MOV     R0, R4\n"
          "BL      sub_FF95F7F0\n"
          "TST     R0, #1\n"
          "MOVNE   R2, R4\n"
//          "LDMFDNE SP!, {R4-R8,LR}\n"
          "LDMNEFD SP!, {R4-R8,LR}\n"
          "MOVNE   R1, #1\n"
          "BNE     sub_FF864FD0\n"
          "BL      sub_FF9732F0\n"

          "BL      shooting_expo_param_override\n"  // +-----------> Override Canon stuff :)

          "BL      sub_FF87491C\n"
          "STR     R0, [R4,#0x14]\n"
          "MOV     R0, R4\n"
          "BL      sub_FF960EBC\n"
          "BL      sub_FF9617AC\n"
          "MOV     R0, R4\n"
//          "BL      sub_FF960F8C\n" // This is where shooting AND darkframe sub is done
          "BL      sub_FF960F8C_my\n" // so hook it
          "MOV     R7, R0\n"

          "BL      capt_seq_hook_raw_here\n" // +-----------> Capture RAW, camera already did badpixel-sub (always) though some pixels are still there

          "B       loc_FF8668FC\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF8668F0:\n"                           // CODE XREF: sub_FF86677C+124j
          "LDR     R0, [R8,#4]\n"
          "CMP     R0, #0\n"
          "MOVNE   R7, #0x1D\n"

     "loc_FF8668FC:\n"                           // CODE XREF: sub_FF86677C+170j
          "MOV     R2, R4\n"
          "MOV     R1, #1\n"
          "MOV     R0, R7\n"
          "BL      sub_FF864FD0\n"
          "BL      sub_FF961314\n"
          "CMP     R0, #0\n"
          "LDRNE   R0, [R4,#8]\n"
          "ORRNE   R0, R0, #0x2000\n"
          "STRNE   R0, [R4,#8]\n"
          "LDR     R0, [R4,#0x18]\n"
          "CMP     R0, #0\n"
          "BLNE    sub_FF861F40\n"
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
          "BEQ     sub_FF95F5A8\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
	".ltorg\n"
     );
}

void __attribute__((naked,noinline)) sub_FF960F8C_my() {
     asm volatile (
          "STMFD   SP!, {R0-R8,LR}\n"
          "MOV     R4, R0\n"
          "BL      sub_FF9618E8\n"
          "MVN     R1, #0\n"
          "BL      sub_FF82A2A8\n"
          "MOV     R2, #4\n"
          "ADD     R1, SP, #0x28-0x20\n"
          "MOV     R0, #0x8A\n"
          "BL      sub_FF87479C\n"
          "TST     R0, #1\n"
          "LDRNE   R1, =0x1D2\n"
//          "ADRNE   R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDRNE   R0, =0xFF9611A4\n"
          "BLNE    sub_FF81BCCC\n" // assert\n"
          "LDR     R6, =0x1AD48\n"
          "LDR     R7, =0x1AC98\n"
          "LDRSH   R1, [R6,#0xE]\n"
          "LDR     R0, [R7,#0x7C]\n"
//          "BL      nullsub_70\n"
          "BL      sub_FF8504F4\n" //GetCCDTemperature\n"
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

          "BL      sub_FFA402C0\n" // 2 (NR) is set into 0xB704 in this sub! Still before shooting

          "BL      wait_until_remote_button_is_released\n"
          "BL      capt_seq_hook_set_nr\n" // +-----------> so immediately override NR

          "LDR     R0, [R4,#0x18]\n"
          "LDR     R1, =0xB704\n"
          "CMP     R0, #0\n"
          "MOV     R8, #1\n"
          "BEQ     loc_FF96101C\n"
          "LDR     R0, [R1]\n"
          "CMP     R0, #2\n"
          "STREQ   R8, [R1]\n"

     "loc_FF96101C:\n"                           // CODE XREF: sub_FF960F8C+80j
          "LDR     R0, [R1,#4]\n"
          "MOV     R5, R1\n"
          "BL      sub_FF850A10\n"
          "LDR     R0, [R5]\n"
          "MOV     R1, #0\n"
          "CMP     R0, #1\n"
          "BNE     loc_FF961094\n"
          "STR     R1, [SP,#0x28-0x1C]\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R1, #0x33\n"
          "MOV     R3, #2\n"
          "ADD     R2, SP, #0x28-0x1C\n"
          "BL      sub_FF874C08\n"
          "LDR     R0, [R4,#8]\n"
//          "ADR     R3, sub_FF960D20\n"
          "LDR     R3, =0xFF960D20\n"
          "ORR     R0, R0, #0x40\n"
          "STR     R0, [R4,#8]\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "STR     R4, [SP,#0x28-0x28]\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
          "MOV     R2, R4\n"
//          "ADR     R1, sub_FF960CA0\n"
          "LDR     R1, =0xFF960CA0\n"
          "BEQ     loc_FF961084\n"
          "BL      sub_FF9D0314\n"
          "B       loc_FF961088\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF961084:\n"                           // CODE XREF: sub_FF960F8C+ECj
          "BL      sub_FF8BA350\n"

     "loc_FF961088:\n"                           // CODE XREF: sub_FF960F8C+F4j
          " \n"                                  // sub_FF960F8C+2ACj ...
          "TST     R0, #1\n"
          "BEQ     loc_FF96125C\n"
          "B       loc_FF961244\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF961094:\n"                           // CODE XREF: sub_FF960F8C+A8j
          "CMP     R0, #2\n"
          "BNE     loc_FF9611E4\n"
          "STR     R1, [SP,#0x28-0x28+4]\n" // start shooting with darkframe
          "STR     R8, [SP,#0x28-0x1C]\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R1, #0x33\n"
          "MOV     R3, #2\n"
          "ADD     R2, SP, #0x28-0x1C\n"
          "BL      sub_FF874C08\n"
          "LDR     R0, [R4,#8]\n"
          "LDR     R1, =0xFF960CA0\n"
          "ORR     R0, R0, #0x80\n"
          "STR     R0, [R4,#8]\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "STR     R4, [SP,#0x28-0x28]\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
//          "ADR     R3, locret_FF960E78\n"
          "LDR     R3, =0xFF960E78\n"
          "MOV     R2, R4\n"
          "BEQ     loc_FF9610EC\n"
          "BL      sub_FF9D031C\n"
          "B       loc_FF9610F0\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF9610EC:\n"                           // CODE XREF: sub_FF960F8C+154j
          "BL      sub_FF8BA3D0\n"

     "loc_FF9610F0:\n"                           // CODE XREF: sub_FF960F8C+15Cj
          "TST     R0, #1\n"
          "BNE     loc_FF961244\n"
          "MOV     R1, #0\n"
          "MOV     R0, #0x44\n"
          "BL      sub_FF886B40\n"
          "LDR     R0, [R4,#8]\n"
          "ORR     R0, R0, #0x100\n"
          "STR     R0, [R4,#8]\n"
          "BL      sub_FF8BA34C\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "LDR     R1, =0xFF960D20\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
          "MOV     R2, R4\n"
          "BEQ     loc_FF961134\n"
          "BL      sub_FF9D032C\n"
          "B       loc_FF961138\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF961134:\n"                           // CODE XREF: sub_FF960F8C+19Cj
          "BL      sub_FF8BA4FC\n"

     "loc_FF961138:\n"                           // CODE XREF: sub_FF960F8C+1A4j
          "TST     R0, #1\n"
          "BNE     loc_FF961244\n"
          "MOV     R2, #2\n"
          "ADD     R1, SP, #0x28-0x28+4\n"
          "MOV     R0, #0xD8\n"
          "BL      sub_FF87479C\n"
          "TST     R0, #1\n"
          "LDRNE   R1, =0x24E\n"
//          "ADRNE   R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDRNE   R0, =0xFF9611A4\n"
          "BLNE    sub_FF81BCCC\n" // assert\n"
          "LDR     R0, [R4,#0x78]\n"
          "CMP     R0, #0\n"
          "BNE     loc_FF96125C\n"
          "LDR     R0, [R6]\n"
          "CMP     R0, #0\n"
          "BEQ     loc_FF961184\n"
          "LDRH    R0, [SP,#0x28-0x28+4]\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF96125C\n"

     "loc_FF961184:\n"                           // CODE XREF: sub_FF960F8C+1E8j
          "MOV     R1, #0\n"
          "MOV     R0, #0x45\n"
          "BL      sub_FF886B40\n"
          "B       loc_FF96125C\n"
          "@ ---------------------------------------------------------------------------\n"
          
          ".ltorg\n" // Shut up stupid compiler/assembler manually
          
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF9611E4:\n"                           // CODE XREF: sub_FF960F8C+10Cj
          "CMP     R0, #3\n"
          "BNE     loc_FF961250\n"
          "MOV     R0, #2\n"
          "STR     R0, [SP,#0x28-0x1C]\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R3, #2\n"
          "ADD     R2, SP, #0x28-0x1C\n"
          "MOV     R1, #0x33\n"
          "BL      sub_FF874C08\n"
          "LDR     R0, [R4,#8]\n"
          "LDR     R3, =0xFF960D20\n"
          "ORR     R0, R0, #0x200\n"
          "STR     R0, [R4,#8]\n"
          "LDR     R0, [SP,#0x28-0x20]\n"
          "STR     R4, [SP,#0x28-0x28]\n"
          "CMP     R0, #0\n"
          "LDR     R0, [R4,#0x24]\n"
          "LDR     R1, =0xFF960CA0\n"
          "MOV     R2, R4\n"
          "BEQ     loc_FF96123C\n"
          "BL      sub_FF9D0324\n"
          "B       loc_FF961088\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF96123C:\n"                           // CODE XREF: sub_FF960F8C+2A4j
          "BL      sub_FF8BA47C\n"
          "B       loc_FF961088\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF961244:\n"                           // CODE XREF: sub_FF960F8C+104j
          " \n"                                  // sub_FF960F8C+168j ...
          "MOV     R0, #0x1D\n"

     "loc_FF961248:\n"                           // CODE XREF: sub_FF960F8C+384j
          "ADD     SP, SP, #0x10\n"
          "LDMFD   SP!, {R4-R8,PC}\n"
          "@ ---------------------------------------------------------------------------\n"

     "loc_FF961250:\n"                           // CODE XREF: sub_FF960F8C+25Cj
          "LDR     R1, =0x279\n"
//          "ADR     R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDR     R0, =0xFF9611A4\n"
          "BL      sub_FF81BCCC\n" //assert\n"

     "loc_FF96125C:\n"                           // CODE XREF: sub_FF960F8C+100j
          " \n"                                  // sub_FF960F8C+1DCj ...
          "LDR     R2, =0xB708\n"
          "LDR     R0, [R4,#0x14]\n"
          "MOV     R3, #4\n"
          "MOV     R1, #0x45\n"
          "BL      sub_FF874C08\n"
          "MOV     R0, #1\n"
          "BL      sub_FF91C04C\n"
          "STR     R0, [R4,#0x98]\n"
          "BL      sub_FF8685C0\n"
          "LDRH    R0, [R7]\n"
          "LDR     R12, =0x820A\n"
          "CMP     R0, R12\n"
//          "LDRHNE  R0, [R7,#0x88]\n"
          "LDRNEH  R0, [R7,#0x88]\n"
          "MOVNE   R1, R7\n"
          "CMPNE   R0, #3\n"
          "LDRNE   R0, [R4,#0xC]\n"
          "CMPNE   R0, #1\n"
          "BLS     loc_FF9612EC\n"
          "LDRH    R2, [R1,#0x86]\n"
          "CMP     R2, #0\n"
          "BNE     loc_FF9612D0\n"
          "LDRH    R0, [R1,#0x82]\n"
          "CMP     R0, #1\n"
          "CMPNE   R0, #2\n"
          "BEQ     loc_FF9612D0\n"
          "CMP     R0, #3\n"
//          "LDRHEQ  R0, [R1,#0x8A]\n"
          "LDREQH  R0, [R1,#0x8A]\n"
          "CMPEQ   R0, #2\n"
          "BNE     loc_FF96130C\n"

     "loc_FF9612D0:\n"                           // CODE XREF: sub_FF960F8C+320j
          " \n"                                  // sub_FF960F8C+330j
          "LDR     R0, [R4,#0x10]\n"
          "CMP     R0, #1\n"
          "BEQ     loc_FF9612EC\n"
          "CMP     R2, #0\n"
//          "LDRHEQ  R0, [R1,#0x82]\n"
          "LDREQH  R0, [R1,#0x82]\n"
          "CMPEQ   R0, #2\n"
          "BNE     loc_FF96130C\n"

     "loc_FF9612EC:\n"                           // CODE XREF: sub_FF960F8C+314j
          " \n"                                  // sub_FF960F8C+34Cj
          "BL      sub_FF9618E8\n"
          "LDR     R2, =0x2710\n"
          "MOV     R1, #4\n"
          "BL      sub_FF869EF8\n"
          "CMP     R0, #0\n"
          "LDRNE   R1, =0x286\n"
//          "ADRNE   R0, aSscaptureseq_c\n"        // \"SsCaptureSeq.c\"
          "LDRNE   R0, =0xFF9611A4\n"
          "BLNE    sub_FF81BCCC\n" // assert\n"

     "loc_FF96130C:\n"                           // CODE XREF: sub_FF960F8C+340j
          " \n"                                  // sub_FF960F8C+35Cj
          "MOV     R0, #0\n"
          "B       loc_FF961248\n"
     ".ltorg\n"
     );
}

