#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"


//VERIFY_SD780 ALL stuff below...

static long *nrflag = (long*)0x5B30; // see below

#include "../../../generic/capt_seq.c"

// SD780  [ Original 0xFF91F5BC ]
// SD1200 [ Original 0xFFCFC540 ]
void __attribute__((naked,noinline)) sub_FFCFC540_my() {
	asm volatile (
"                 STMFD   SP!, {R0-R8,LR}\n"
"                 MOV     R4, R0\n"
"                 BL      sub_FFCFD00C\n" // SsShootEvent.c:60\n"
"                 MVN     R1, #0\n"
"                 BL      sub_FFC52500\n"
"                 LDR     R5, =0x5B30\n"
"                 LDR     R0, [R5, #0xC]\n"
"                 CMP     R0, #0\n"
"                 BNE     loc_FFCFC590\n"
"                 MOV     R1, #1\n"
"                 MOV     R0, #0\n"
"                 BL      sub_FFC17000\n"
"                 STR     R0, [R5, #0xC]\n"
"                 MOV     R3, #0\n"
"                 STR     R3, [SP]\n"
"                 LDR     R3, =0xFFCFC048\n"
//"                 LDR     R0, =0xFF91F83C\n"  // "ShutterSoundTask"  Yossar: commented, added proper address
"                 LDR     R0, =0xFFCFC798\n"  // "ShutterSoundTask" //from firmware
"                 MOV     R2, #0x400\n"
"                 MOV     R1, #0x17\n"
"                 BL      sub_FFC16FCC\n"
"loc_FFCFC590:\n"
"                 MOV     R2, #4\n"
"                 ADD     R1, SP, #8\n"
"                 MOV     R0, #0x8A\n"
"                 BL      sub_FFC5A2E8\n" // PT_GetPropertyCaseString_0 ; LOCATION: PropertyCase.c:0\n"
"                 TST     R0, #1\n"
"                 LDRNE   R1, =0x3A7\n" // was 0x3AE, corrected
"                 LDRNE   R0, =0xFFCFC2B4\n" // "SsCaptureSeq.c"
"                 BLNE    sub_FFC0B284\n" // DebugAssert\n"
"                 LDR     R7, =0x12034\n"
"                 LDR     R8, =0x11F70\n"
"                 LDRSH   R1, [R7,#0xE]\n"
"                 LDR     R0, [R8,#0x8C]\n"
"                 BL      sub_FFCC3CD0\n"
"                 BL      sub_FFC33858\n" // GetCCDTemperature ; LOCATION: Thermometer.c:250\n"
"                 LDR     R3, =0x5B38\n"
"                 STRH    R0, [R4,#0x9C]\n"
"                 SUB     R2, R3, #4\n"
"                 STRD     R2, [SP]\n"  //???
"                 MOV     R1, R0\n"
"                 LDRH    R0, [R8,#0x5C]\n"
"                 LDRSH   R2, [R7,#0xC]\n"
"                 SUB     R3, R3, #8\n"
"                 BL      sub_FFCFD5F8\n" // NRTable.c:219\n"
//VERIFY_SD780"                 BL      wait_until_remote_button_is_released\n"		// this func needs to be tested and added
"                 BL      capt_seq_hook_set_nr\n"
"                 B       sub_FFCFC5EC\n" // -> continue function in firmware
    );
}

// SD780  [ Original 0xFF85DB34 ]
// SD1200 [ Original 0xFFC4A3B8 ]
// task_CaptSeqTask+160
void __attribute__((naked,noinline)) sub_FFC4A3B8_my() {
	asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                LDR     R4, [R0,#0xC]\n"
"                LDR     R6, =0x11F70\n"
"                LDR     R0, [R4,#8]\n"
"                MOV     R5, #0\n"
"                ORR     R0, R0, #1\n"
"                STR     R0, [R4,#8]\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                MOVEQ   R0, #2\n"
"                BLEQ    sub_FFC45BD0\n"	
"                BL      sub_FFC4A8A8\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC4A454\n"	
"                MOV     R0, R4\n"
"                BL      sub_FFC4ABD8\n"
"                MOV     R0, R4\n"
"                BL      sub_FFCFB294\n"	
"                CMP     R0, #0\n"
"                MOV     R0, R4\n"
"                BEQ     loc_FFC4A42C\n"	
"                BL      sub_FFCFB320\n" // SsPrePreSeq.c:0
"                TST     R0, #1\n"
"                MOVNE   R2, R4\n"
"                LDMNEFD SP!, {R4-R6,LR}\n"
"                MOVNE   R1, #1\n"
"                BNE     sub_FFC483E8\n" // SsShootCtrl.c:0
"                B       loc_FFC4A430\n"
"loc_FFC4A42C:\n"
"                BL      sub_FFCFB2E4\n"
"loc_FFC4A430:\n"
"                MOV     R0, R4\n"
"                BL      sub_FFC49B14\n"
"                MOV     R0, R4\n"
"                BL      sub_FFCFC478\n" // SsCaptureSeq.c:1
"                BL      sub_FFCFCEA0\n" // SsShootLib.c:32768 
"                MOV     R0, R4\n"
"                BL      sub_FFCFC540_my\n" // SsCaptureSeq.c:0 nr setup 
//"                BL      sub_FFCFC540\n" // SsCaptureSeq.c:0 nr setup		// this was original call
"                BL      capt_seq_hook_raw_here\n" 	
"                MOV     R5, R0\n"
"                B       loc_FFC4A464\n"
"loc_FFC4A454:\n"
"                LDR     R0, =0x2850\n"
"                LDR     R0, [R0,#0x10]\n"
"                CMP     R0, #0\n"
"                MOVNE   R5, #0x1D\n"
"loc_FFC4A464:\n"
"                BL      sub_FFC4CCF4\n"
"                BL      sub_FFC4CD3C\n"
"                BL      sub_FFC4CD7C\n"
"                MOV     R2, R4\n"
"                MOV     R1, #1\n"
"                MOV     R0, R5\n"
"                BL      sub_FFC483E8\n" // SsShootCtrl.c:0
"                BL      sub_FFCFC7C8\n"
"                CMP     R0, #0\n"
"                LDRNE   R0, [R4,#8]\n"
"                ORRNE   R0, R0, #0x2000\n"
"                STRNE   R0, [R4,#8]\n"
"                LDMFD   SP!, {R4-R6,PC}\n"
    );
}

//VERIFY_SD780 - Below this is good ASM but needs work still...
//SD1200 - Original 0xFFC49FE0
void __attribute__((naked,noinline)) task_CaptSeqTask_my() {
	asm volatile (
"                STMFD   SP!, {R3-R9,LR}\n"
"                LDR     R6, =0x2850\n"
"                LDR     R4, =0x11F70\n"
"                MOV     R9, #1\n"
"                MOV     R7, #0\n"
"loc_FFC49FF4:\n"
"                LDR     R0, [R6,#0x4]\n"
"                MOV     R2, #0\n"
"                MOV     R1, SP\n"
"                BL      sub_FFC167B8\n" //  KerQueue.c
"                TST     R0, #1\n"
"                BEQ     loc_FFC4A020\n"
"                LDR     R1, =0x588\n"
"                LDR     R0, =0xFFC49B94\n" // "SsShootTask.c"
"                BL      sub_FFC0B284\n" // DebugAssert
"                BL      sub_FFC0B23C\n" // ExitTask
"                LDMFD   SP!, {R3-R9,PC}\n"
"loc_FFC4A020:\n"
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #0x1D\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       jumptable_entry_default\n"
"loc_FFC4A034:\n"
"                B       jumptable_entry_0\n"
"loc_FFC4A038:\n"
"                B       jumptable_entry_1\n"
"loc_FFC4A03C:\n"
"                B       jumptable_entry_2\n"
"loc_FFC4A040:\n"
"                B       jumptable_entry_3\n"
"loc_FFC4A044:\n"
"                B       jumptable_entry_4\n"
"loc_FFC4A048:\n"
"                B       jumptable_entry_5\n"
"loc_FFC4A04C:\n"
"                B       jumptable_entry_6\n"
"loc_FFC4A050:\n"
"                B       jumptable_entry_7\n"
"loc_FFC4A054:\n"
"                B       jumptable_entry_8\n"
"loc_FFC4A058:\n"
"                B       jumptable_entry_9\n"
"loc_FFC4A05C:\n"
"                B       jumptable_entry_10\n"
"loc_FFC4A060:\n"
"                B       jumptable_entry_11\n"
"loc_FFC4A064:\n"
"                B       jumptable_entry_12\n"
"loc_FFC4A068:\n"
"                B       jumptable_entry_13\n"
"loc_FFC4A06C:\n"
"                B       jumptable_entry_14\n"
"loc_FFC4A070:\n"
"                B       jumptable_entry_15\n"
"loc_FFC4A074:\n"
"                B       jumptable_entry_16\n"
"loc_FFC4A078:\n"
"                B       jumptable_entry_17\n"
"loc_FFC4A07C:\n"
"                B       jumptable_entry_18\n"
"loc_FFC4A080:\n"
"                B       jumptable_entry_19\n"
"loc_FFC4A084:\n"
"                B       jumptable_entry_20\n"
"loc_FFC4A088:\n"
"                B       jumptable_entry_21\n"
"loc_FFC4A08C:\n"
"                B       jumptable_entry_22\n"
"loc_FFC4A090:\n"
"                B       jumptable_entry_23\n"
"loc_FFC4A094:\n"
"                B       jumptable_entry_24\n"
"loc_FFC4A098:\n"
"                B       jumptable_entry_25\n"
"loc_FFC4A09C:\n"
"                B       jumptable_entry_26\n"
"loc_FFC4A0A0:\n"
"                B       jumptable_entry_27\n"
"loc_FFC4A0A4:\n"
"                B       jumptable_entry_28\n"
"loc_FFC4A0A8:\n"
"                B       jumptable_entry_29\n"


// START OF PASTE
"jumptable_entry_0:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 0               // LOCATION: SsPrepareSeq.c:0
"                BL      sub_FFC4A8B8\n"
"                BL      sub_FFC47F08\n"
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BEQ     jumptable_entry_29\n"
"                BL      sub_FFC49870\n"
"                MOV     R5, R0\n"
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FFC4A0F4\n"
"                MOV     R0, #0xC\n"
"                BL      sub_FFC4E41C\n"
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#0x10]\n"
"                LDRNE   R0, [R5,#8]\n"
"                ORRNE   R0, R0, #0x40000000\n"
"                STRNE   R0, [R5,#8]\n"
"                BNE     jumptable_entry_29\n"
"loc_FFC4A0F4:\n"                      // CODE XREF: task_CaptSeqTask+F0j
"                MOV     R0, R5\n"
"                BL      sub_FFC49B14\n" // nr setup, hook here too ?
"                MOV     R0, R5\n"
"                BL      sub_FFCFC540\n"    // LOCATION: SsCaptureSeq.c:0
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#0x10]\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_1:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 1
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FFC4A13C\n"
"                MOV     R0, #0xC\n"
"                BL      sub_FFC4E41C\n"
"                TST     R0, #1\n"
"                LDRNE   R0, [SP]\n"
"                MOVNE   R1, #1\n"
"                LDRNE   R2, [R0,#0xC]\n"
"                MOVNE   R0, #1\n"
"                BNE     loc_FFC4A1C8\n"
"loc_FFC4A13C:\n"                      // CODE XREF: task_CaptSeqTask+138j
"                LDR     R0, [SP]\n"
"                BL      sub_FFC4A3B8_my\n"
"loc_FFC4A144:\n"                      // CODE XREF: task_CaptSeqTask+17Cj
"                STR     R7, [R4,#0x24]\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_2:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 2
"                MOV     R0, #1\n"
"                BL      sub_FFC4AAC4\n"    // LOCATION: SsPrepareSeq.c:0
"                B       jumptable_entry_29\n"
"jumptable_entry_4:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 4
// called in shooting, "after first call to 32" (mean entry 29?)
"                BL      sub_FFC4A528\n"
"                B       loc_FFC4A144\n"
"jumptable_entry_3:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 3
// last call after shot, also called switching from play->shoot
"                BL      sub_FFC4A898\n"
"                B       loc_FFC4A144\n"    // middle of jumptable_entry_4
"jumptable_entry_5:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 5
"                BL      sub_FFC4A8A0\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_6:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 6            ; LOCATION: SsPrepareSeq.c:960
"                BL      sub_FFC4A9E4\n"
"                B       loc_FFC4A1D4\n"    // middle of jumptable_entry_8
"jumptable_entry_7:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 7
"                LDR     R5, [R0,#0xC]\n"
"                BL      sub_FFC4A8A8\n"
"                MOV     R0, R5\n"
"                BL      sub_FFCFB5EC\n"    // LOCATION: SsPrePreSeq.c:2097152
"                TST     R0, #1\n"
"                MOV     R8, R0\n"
"                BNE     loc_FFC4A1B8\n"
"                BL      sub_FFC5A478\n"    // LOCATION: PropertyCase.c:0
"                STR     R0, [R5,#0x18]\n"
"                MOV     R0, R5\n"
"                BL      sub_FFCFC478\n"    // LOCATION: SsCaptureSeq.c:1
"                MOV     R0, R5\n"
"                BL      sub_FFCFC824\n"    // LOCATION: SsCaptureSeq.c:4
"                MOV     R8, R0\n"
"                LDR     R0, [R5,#0x18]\n"
"                BL      sub_FFC5A68C\n"    // LOCATION: PropertyCase.c:0
"loc_FFC4A1B8:\n"                      // CODE XREF: task_CaptSeqTask+1B0j
"                BL      sub_FFC4A898\n"
"                MOV     R2, R5\n"
"                MOV     R1, #9\n"
"                MOV     R0, R8\n"
"loc_FFC4A1C8:\n"                      // CODE XREF: task_CaptSeqTask+158j
"                BL      sub_FFC483E8\n"    // LOCATION: SsShootCtrl.c:0
"                B       jumptable_entry_29\n"
"jumptable_entry_8:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 8            ; LOCATION: SsPrepareSeq.c:0
// movie mode half press ?
"                BL      sub_FFC4AA44\n"
"loc_FFC4A1D4:\n"                      // CODE XREF: task_CaptSeqTask+194j
"                BL      sub_FFC47F08\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_10:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 10
"                LDR     R0, [R4,#0x54]\n"
"                BL      sub_FFC4AE20\n"    // LOCATION: SsMovieRec.c:184
"                B       jumptable_entry_29\n"
"jumptable_entry_11:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 11           ; LOCATION: SsMovieRec.c:2
"                BL      sub_FFC4B0C8\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_12:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 12           ; LOCATION: SsMovieRec.c:43
"                BL      sub_FFC4B15C\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_9:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 9
"                BL      sub_FFC4A898\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_13:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 13
"                BL      sub_FFCFB7FC\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_14:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 14
"                BL      sub_FFCFB9DC\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_15:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 15           ; LOCATION: SsExpCompSeq.c:105
"                BL      sub_FFCFBA6C\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_16:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 16
"                BL      sub_FFCFBB14\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_17:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 17
"                MOV     R0, #0\n"
"                BL      sub_FFCFBCD0\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_18:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 18
"                BL      sub_FFCFBE08\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_19:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 19           ; LOCATION: SsMFSeq.c:110
"                BL      sub_FFCFBE98\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_20:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 20           ; LOCATION: SsMFSeq.c:177
"                BL      sub_FFCFBF58\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_21:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 21
// focus mode to mf
"                BL      sub_FFC4AC24\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_22:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 22
// halfpress to shoot, focus mode change except MF
"                BL      sub_FFC4ACB0\n"
"                BL      sub_FFC1498C\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_23:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 23
"                BL      sub_FFCFBBD0\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_24:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 24           ; LOCATION: SsChgExpSeq.c:0
"                BL      sub_FFCFBC14\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_25:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 25
"                BL      sub_FFC4CC98\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_26:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 26
"                BL      sub_FFC4CCF4\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_27:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 27
// iso change
"                BL      sub_FFC4CD50\n"
"                BL      sub_FFC4CD10\n"
"                B       jumptable_entry_29\n"
"jumptable_entry_28:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 28
"                LDRH    R0, [R4,#0x98]\n"
"                CMP     R0, #4\n"
"                BLNE    sub_FFC4CFBC\n"    // LOCATION: SsLiveFunc.c:780
"                B       jumptable_entry_29\n"
"jumptable_entry_default:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C default entry
"                LDR     R1, =0x6C9\n"
"                LDR     R0, =0xFFC49B94\n"  // "SsShootTask.c
"                BL      sub_FFC0B284\n"     // DebugAssert
"jumptable_entry_29:\n"                      // CODE XREF: task_CaptSeqTask+4Cj
// jumptable FFC4A02C entry 29: Most continue here
// also called explicitly in shoot after 1 and 30, and on pb -> shoot 2x
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0,#4]\n"
"                LDR     R0, [R6]\n"
"                BL      sub_FFC524CC\n"
"                LDR     R5, [SP]\n"
"                LDR     R0, [R5,#8]\n"
"                CMP     R0, #0\n"
"                LDREQ   R1, =0x12B\n"
"                LDREQ   R0, =0xFFC49B94\n"  // "SsShootTask.c
"                BLEQ    sub_FFC0B284\n"     // DebugAssert
"                STR     R7, [R5,#8]\n"
"                B       loc_FFC49FF4\n"    // main loop
// End of function task_CaptSeqTask
    );
}

