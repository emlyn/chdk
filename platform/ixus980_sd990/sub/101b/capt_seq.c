#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x93C8; // see below

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF93DDF4_my() {
	asm volatile (
"                 STMFD   SP!, {R1-R7,LR}\n"
"                 MOV     R4, R0\n"
"                 BL      sub_FF93EA40\n" // SsShootEvent.c:60\n"
"                 MVN     R1, #0\n"
"                 BL      sub_FF86E0B8\n"
"                 MOV     R2, #4\n"
"                 ADD     R1, SP, #4\n"
"                 MOV     R0, #0x8A\n"
"                 BL      sub_FF876358\n" // PT_GetPropertyCaseString_0 ; LOCATION: PropertyCase.c:0\n"
"                 TST     R0, #1\n"
"                 LDRNE   R1, =0x373\n"
"                 LDRNE   R0, =0xFF93DDC0\n" // "SsCaptureSeq.c"
"                 BLNE    sub_FF81B1CC\n" // DebugAssert\n"
"                 LDR     R7, =0x1B2C8\n"
"                 LDR     R6, =0x1B208\n"
"                 LDRSH   R1, [R7,#0xE]\n"
"                 LDR     R0, [R6,#0x88]\n"
"                 BL      sub_FF9016DC\n"
"                 BL      sub_FF84CDCC\n" // GetCCDTemperature ; LOCATION: Thermometer.c:250\n"
"                 LDR     R3, =0x93CC\n"
"                 STRH    R0, [R4,#0x94]\n"
"                 STR     R3, [SP]\n"
"                 MOV     R1, R0\n"
"                 LDRH    R0, [R6,#0x5C]\n"
"                 LDRSH   R2, [R7,#0xC]\n"
"                 SUB     R3, R3, #4\n"
"                 BL      sub_FF93F038\n" // NRTable.c:219\n"
"                 BL      wait_until_remote_button_is_released\n"
"                 BL      capt_seq_hook_set_nr\n"
"                 B       sub_FF93DE60\n" // -> continue function in firmware
    );
}

void __attribute__((naked,noinline)) sub_FF8662E0_my() {
	asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                LDR     R4, [R0,#0xC]\n"
"                LDR     R6, =0x1B208\n"
"                LDR     R0, [R4,#8]\n"
"                MOV     R5, #0\n"
"                ORR     R0, R0, #1\n"
"                STR     R0, [R4,#8]\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                MOVEQ   R0, #2\n"
"                BLEQ    sub_FF86004C\n"
"                BL      sub_FF866800\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF866390\n" // _<
"                MOV     R0, #0\n"
"                BL      sub_FF93E8DC\n"
"                MOV     R0, R4\n"
"                BL      sub_FF866B50\n"
"                MOV     R0, R4\n"
"                BL      sub_FF93C9A4\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF866360\n"
"                BL      sub_FF93E91C\n"
"                MOV     R0, R4\n"
"                BL      sub_FF93CA88\n" // SsPrePreSeq.c:0
"                TST     R0, #1\n"
"                MOVNE   R2, R4\n"
"                LDMNEFD SP!, {R4-R6,LR}\n"
"                MOVNE   R1, #1\n"
"                BNE     sub_FF8643C4\n" // SsShootCtrl.c:0
"                B       loc_FF86636C\n"
"loc_FF866360:\n"
"                MOV     R0, R4\n"
"                BL      sub_FF93CA24\n"
"                BL      sub_FF93E91C\n"
"loc_FF86636C:\n"
"                MOV     R0, R4\n"
"                BL      sub_FF8659AC\n"
"                MOV     R0, R4\n"
"                BL      sub_FF93DCB0\n" // SsCaptureSeq.c:1
"                BL      sub_FF93E76C\n" // SsShootLib.c:32768
"                MOV     R0, R4\n"
"                BL      sub_FF93DDF4_my\n" // SsCaptureSeq.c:0 nr setup
"                MOV     R5, R0\n"
"                B       loc_FF8663A0\n"
"loc_FF866390:\n"
"                LDR     R0, =0x54EC\n"
"                LDR     R0, [R0,#4]\n"
"                CMP     R0, #0\n"
"                MOVNE   R5, #0x1D\n"
"loc_FF8663A0:\n"
"                BL      capt_seq_hook_raw_here\n"  
"                BL      sub_FF8686F0\n"
"                BL      sub_FF868738\n"
"                BL      sub_FF868778\n"
"                MOV     R2, R4\n"
"                MOV     R1, #1\n"
"                MOV     R0, R5\n"
"                BL      sub_FF8643C4\n" // SsShootCtrl.c:0
"                BL      sub_FF93E04C\n"
"                CMP     R0, #0\n"
"                LDRNE   R0, [R4,#8]\n"
"                ORRNE   R0, R0, #0x2000\n"
"                STRNE   R0, [R4,#8]\n"
"                LDMFD   SP!, {R4-R6,PC}\n"
    );
}

void __attribute__((naked,noinline)) task_CaptSeqTask_my() {
	asm volatile (
"                STMFD   SP!, {R3-R9,LR}\n"
"                LDR     R6, =0x54EC\n"
"                LDR     R4, =0x1B208\n"
"                MOV     R9, #1\n"
"                MOV     R7, #0\n"
"loc_FF865F20:\n"
"                LDR     R0, [R6,#0xC]\n"
"                MOV     R2, #0\n"
"                MOV     R1, SP\n"
"                BL      sub_FF82746C\n" //  KerQueue.c
"                TST     R0, #1\n"
"                BEQ     loc_FF865F4C\n"
"                LDR     R1, =0x539\n"
"                LDR     R0, =0xFF865A28\n" // "SsShootTask.c"
"                BL      sub_FF81B1CC\n" // DebugAssert
"                BL      sub_FF81B184\n" // ExitTask
"                LDMFD   SP!, {R3-R9,PC}\n"
"loc_FF865F4C:\n"
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #0x20\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       loc_FF8661BC\n"
"                B       loc_FF865FE4\n"
"                B       loc_FF866048\n"
"                B       loc_FF866050\n"
"                B       loc_FF866068\n"
"                B       loc_FF86605C\n"
"                B       loc_FF866070\n"
"                B       loc_FF866078\n"
"                B       loc_FF866080\n"
"                B       loc_FF8660D8\n"
"                B       loc_FF866100\n"
"                B       loc_FF8660E4\n"
"                B       loc_FF8660F0\n"
"                B       loc_FF8660F8\n"
"                B       loc_FF866108\n"
"                B       loc_FF866110\n"
"                B       loc_FF866118\n"
"                B       loc_FF866120\n"
"                B       loc_FF866128\n"
"                B       loc_FF866130\n"
"                B       loc_FF866138\n"
"                B       loc_FF866140\n"
"                B       loc_FF866148\n"
"                B       loc_FF866150\n"
"                B       loc_FF866158\n"
"                B       loc_FF866164\n"
"                B       loc_FF86616C\n"
"                B       loc_FF866178\n"
"                B       loc_FF866180\n"
"                B       loc_FF866188\n"
"                B       loc_FF866190\n"
"                B       loc_FF866198\n"
"                B       loc_FF8661A4\n"
"                B       loc_FF8661C8\n"
"loc_FF865FE4:\n"
// jumptable FF865F58 entry 0: halfpress in shoot mode, or full press if quick
"                BL      sub_FF866810\n" // SsPrepareSeq_c
//"                BL      shooting_expo_param_override\n"  // +
"    STMFD   SP!, {R1-R12,LR}\n"
"    BL      captseq_hack_override_active\n" // returns 1 if tv or sv override in effect
"    LDMFD   SP!, {R1-R12,LR}\n"
"    STR     R0,[SP,#-4]!\n" // push return value
"    BL      shooting_expo_param_override\n" // saves all regs
"                BL      sub_FF863F08\n"
"    LDR     R0,[SP],#4\n" // pop override hack
"    CMP     R0, #1\n"
"    MOVEQ   R0, #0\n"
"    STREQ   R0, [R4,#0x24]\n"  // fixes overrides behavior at short shutter press
//"                BL      sub_FF863F08\n"
/*
 //  this code added to avoid some incorrect behavior if overrides are used.
 //  but it can cause some unexpected side effects. In this case, remove this code!

                 "LDR     R0, =ovr_disable\n"
                 "LDR     R0, [R0]\n"
                 "LDR     R0, [R0]\n"
                 "CMP     R0, #1\n"
                 "BEQ     locA\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press
//               "STR     R0, [R4,#0x1C]\n"  
                 "B       loc_FF8661C8\n"
"locA:\n"
 	
 //  end of my code
*/
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF8661C8\n" // -> jt 32, loop
"                BL      sub_FF865700\n"
"                MOV     R5, R0\n"
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF86602C\n"
"                MOV     R0, #0xC\n"
"                BL      sub_FF869DCC\n"
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#4]\n"
"                LDRNE   R0, [R5,#8]\n"
"                ORRNE   R0, R0, #0x40000000\n"
"                STRNE   R0, [R5,#8]\n"
"                BNE     loc_FF8661C8\n" // -> jt 32, loop
"loc_FF86602C:\n"
"                MOV     R0, R5\n"
"                BL      sub_FF8659AC\n"
"                MOV     R0, R5\n"
"                BL      sub_FF93DDF4\n" // nr setup, hook here too ?
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#4]\n"
"                B       loc_FF8661C8\n" // -> jt 32, loop
"loc_FF866048:\n"
// jumptable FF865F58 entry 1: called 1+ sec after entry 0, i.e. shooting near complete
"                BL      sub_FF8662E0_my\n"
"                B       loc_FF866060\n" // -> middle of jt 4
"loc_FF866050:\n"
// jumptable FF865F58 entry 2
"                MOV     R0, #1\n"
"                BL      sub_FF866A28\n"
"                B       loc_FF8661C8\n" // jt 32, loop
"loc_FF86605C:\n"
// jumptable FF865F58 entry 4 // called in shooting, after first call to 32
"                BL      sub_FF866474\n"
"loc_FF866060:\n"
"                STR     R7, [R4,#0x24]\n"
"                B       loc_FF8661C8\n" // jt 32, loop
"loc_FF866068:\n"
// jumptable FF865F58 entry 3: last call after shot, also called switching from play->shoot
"                BL      sub_FF8667F0\n"
"                B       loc_FF866060\n" // -> middle of jt 4
"loc_FF866070:\n"
// jumptable FF865F58 entry 5
"                BL      sub_FF8667F8\n"
"                B       loc_FF8661C8\n"
"loc_FF866078:\n"
// jumptable FF865F58 entry 6
"                BL      sub_FF866948\n"
"                B       loc_FF8660DC\n" // -> middle of jt 8
"loc_FF866080:\n"
// jumptable FF865F58 entry 7
"                LDR     R5, [R0,#0xC]\n"
"                BL      sub_FF866800\n"
"                MOV     R0, R5\n"
"                BL      sub_FF93CD94\n"
"                TST     R0, #1\n"
"                MOV     R8, R0\n"
"                BNE     loc_FF8660C0\n"
"                BL      sub_FF8764E8\n"
"                STR     R0, [R5,#0x18]\n"
"                MOV     R0, R5\n"
"                BL      sub_FF93DCB0\n"
"                MOV     R0, R5\n"
"                BL      sub_FF93E0BC\n"
"                MOV     R8, R0\n"
"                LDR     R0, [R5,#0x18]\n"
"                BL      sub_FF8766FC\n"
"loc_FF8660C0:\n"
"                BL      sub_FF8667F0\n"
"                MOV     R2, R5\n"
"                MOV     R1, #9\n"
"                MOV     R0, R8\n"
"                BL      sub_FF8643C4\n"
"                B       loc_FF8661C8\n"
"loc_FF8660D8:\n"
// jumptable FF865F58 entry 8: movie mode half press ?
"                BL      sub_FF8669A8\n"
"loc_FF8660DC:\n"
"                BL      sub_FF863F08\n"
"                B       loc_FF8661C8\n"
"loc_FF8660E4:\n"
// jumptable FF865F58 entry 10
"                LDR     R0, [R4,#0x54]\n"
"                BL      sub_FF866DBC\n"
"                B       loc_FF8661C8\n"
"loc_FF8660F0:\n"
// jumptable FF865F58 entry 11
"                BL      sub_FF86706C\n"
"                B       loc_FF8661C8\n"
"loc_FF8660F8:\n"
// jumptable FF865F58 entry 12
"                BL      sub_FF8670FC\n"
"                B       loc_FF8661C8\n"
"loc_FF866100:\n"
// jumptable FF865F58 entry 9
"                BL      sub_FF8667F0\n"
"                B       loc_FF8661C8\n"
"loc_FF866108:\n"
// jumptable FF865F58 entry 13
"                BL      sub_FF93CFC0\n"
"                B       loc_FF8661C8\n"
"loc_FF866110:\n"
// jumptable FF865F58 entry 14
"                BL      sub_FF93D1A8\n"
"                B       loc_FF8661C8\n"
"loc_FF866118:\n"
// jumptable FF865F58 entry 15
"                BL      sub_FF93D238\n"
"                B       loc_FF8661C8\n"
"loc_FF866120:\n"
// jumptable FF865F58 entry 16
"                BL      sub_FF93D2EC\n"
"                B       loc_FF8661C8\n"
"loc_FF866128:\n"
// jumptable FF865F58 entry 17
"                BL      sub_FF93D4EC\n"
"                B       loc_FF8661C8\n"
"loc_FF866130:\n"
// jumptable FF865F58 entry 18
"                BL      sub_FF93D544\n"
"                B       loc_FF8661C8\n"
"loc_FF866138:\n"
// jumptable FF865F58 entry 19
"                MOV     R0, #0\n"
"                B       loc_FF86615C\n"
"loc_FF866140:\n"
// jumptable FF865F58 entry 20
"                BL      sub_FF93D704\n"
"                B       loc_FF8661C8\n"
"loc_FF866148:\n"
// jumptable FF865F58 entry 21: focus mode to mf 
"                BL      sub_FF93D794\n"
"                B       loc_FF8661C8\n"
"loc_FF866150:\n"
// jumptable FF865F58 entry 22: halfpress to shoot, focus mode change except MF
"                BL      sub_FF93D854\n"
"                B       loc_FF8661C8\n"
"loc_FF866158:\n"
// jumptable FF865F58 entry 23
"                MOV     R0, #1\n"
"loc_FF86615C:\n"
"                BL      sub_FF93D5CC\n"
"                B       loc_FF8661C8\n"
"loc_FF866164:\n"
// jumptable FF865F58 entry 24
"                BL      sub_FF866BA8\n"
"                B       loc_FF8661C8\n"
"loc_FF86616C:\n"
// jumptable FF865F58 entry 25
"                BL      sub_FF866C48\n"
"                BL      sub_FF8249F4\n"
"                B       loc_FF8661C8\n"
"loc_FF866178:\n"
// jumptable FF865F58 entry 26
"                BL      sub_FF93D3A8\n"
"                B       loc_FF8661C8\n"
"loc_FF866180:\n"
// jumptable FF865F58 entry 27: iso change
"                BL      sub_FF93D414\n"
"                B       loc_FF8661C8\n"
"loc_FF866188:\n"
// jumptable FF865F58 entry 28
"                BL      sub_FF868688\n"
"                B       loc_FF8661C8\n"
"loc_FF866190:\n"
// jumptable FF865F58 entry 29
"                BL      sub_FF8686F0\n"
"                B       loc_FF8661C8\n"
"loc_FF866198:\n"
// jumptable FF865F58 entry 30: in shoot, after jt 4
"                BL      sub_FF86874C\n"
"                BL      sub_FF86870C\n"
"                B       loc_FF8661C8\n"
"loc_FF8661A4:\n"
// jumptable FF865F58 entry 31
"                MOV     R0, #1\n"
"                BL      sub_FF93E8DC\n"
"                LDRH    R0, [R4,#0x8C]\n"
"                CMP     R0, #3\n"
"                BLNE    sub_FF868948\n"
"                B       loc_FF8661C8\n"
"loc_FF8661BC:\n"
// jumptable FF865F58 default entry
"                LDR     R1, =0x65E\n"
"                LDR     R0, =0xFF865A28\n" // "SsShootTask.c"
"                BL      sub_FF81B1CC\n" // DebugAssert
"loc_FF8661C8:\n"
// jumptable FF865F58 entry 32: Most continue here
// also called explicitly in shoot after 1 and 30, and on pb -> shoot 2x
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0,#4]\n"
"                LDR     R0, [R6,#8]\n"
"                BL      sub_FF86E084\n"
"                LDR     R5, [SP]\n"
"                LDR     R0, [R5,#8]\n"
"                CMP     R0, #0\n"
"                LDREQ   R1, =0x11D\n"
"                LDREQ   R0, =0xFF865A28\n" // "SsShootTask.c"
"                BLEQ    sub_FF81B1CC\n" // DebugAssert
"                STR     R7, [R5,#8]\n"
"                B       loc_FF865F20\n" // -> main loop
    );
}

