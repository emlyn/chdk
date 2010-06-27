#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

// TODO FAKE
static long *nrflag = (long*)(0xDEAD); 

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF861320_my() {
	asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                LDR     R4, [R0,#0xC]\n"
"                LDR     R6, =0x14358\n"
"                LDR     R0, [R4,#8]\n"
"                MOV     R5, #0\n"
"                ORR     R0, R0, #1\n"
"                STR     R0, [R4,#8]\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                MOVEQ   R0, #2\n"
"                BLEQ    sub_FF85C65C\n"
"                BL      sub_FF861854\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF8613D0\n"
"                MOV     R0, #0\n"
"                BL      sub_FF935130\n"
"                MOV     R0, R4\n"
"                BL      sub_FF861BA4\n"
"                MOV     R0, R4\n"
"                BL      sub_FF933130\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF8613A0\n"
"                BL      sub_FF935170\n"
"                MOV     R0, R4\n"
"                BL      sub_FF933214\n" // SsPrePreSeq.c 0
"                TST     R0, #1\n"
"                MOVNE   R2, R4\n"
"                LDMNEFD SP!, {R4-R6,LR}\n"
"                MOVNE   R1, #1\n"
"                BNE     sub_FF85F284\n" // SsShootCtrl.c 0
"                B       loc_FF8613AC\n"
"loc_FF8613A0:\n"
"                MOV     R0, R4\n"
"                BL      sub_FF9331B0\n"
"                BL      sub_FF935170\n"
"loc_FF8613AC:\n"
"                MOV     R0, R4\n"
"                BL      sub_FF860A18\n"
"                MOV     R0, R4\n"
"                BL      sub_FF934460\n" // SsCaptureSeq.c 1
"                BL      sub_FF934FC0\n" // SsShootLib.c 488
"                MOV     R0, R4\n"
"                BL      sub_FF934548\n" // SsCaptureSeq.c 0 nr setup ?
"                BL      capt_seq_hook_raw_here\n"  // note preserves R0
"                MOV     R5, R0\n"
"                B       loc_FF8613E0\n"
"loc_FF8613D0:\n"
"                LDR     R0, =0x2AA0\n"
"                LDR     R0, [R0,#0x10]\n"
"                CMP     R0, #0\n"
"                MOVNE   R5, #0x1D\n"
"loc_FF8613E0:\n"
"                BL      sub_FF8640F4\n"
"                BL      sub_FF86413C\n"
"                BL      sub_FF86417C\n"
"                MOV     R2, R4\n"
"                MOV     R1, #1\n"
"                MOV     R0, R5\n"
"                BL      sub_FF85F284\n" // SsShootCtrl.c 0
"                BL      sub_FF9347F4\n"
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
"                LDR     R6, =0x2AA0\n"
"                LDR     R4, =0x14358\n"
"                MOV     R9, #1\n"
"                MOV     R7, #0\n"
"loc_FF860F48:\n"
"                LDR     R0, [R6,#4]\n"
"                MOV     R2, #0\n"
"                MOV     R1, SP\n"
"                BL      sub_FF826C30\n" // KerQueue.c 0
"                TST     R0, #1\n"
"                BEQ     loc_FF860F74\n"
"                LDR     R1, =0x588\n"
"                LDR     R0, =0xFF860A98\n" // aSsshoottask_c
"                BL      sub_FF81B284\n" // DebugAssert
"                BL      sub_FF81B23C\n" // eventproc_export_ExitTask
"                LDMFD   SP!, {R3-R9,PC}\n"
"loc_FF860F74:\n"
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #0x1E\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       loc_FF8611FC\n"
"                B       loc_FF861004\n"
"                B       loc_FF861068\n"
"                B       loc_FF8610A4\n"
"                B       loc_FF8610B8\n"
"                B       loc_FF8610B0\n"
"                B       loc_FF8610C0\n"
"                B       loc_FF8610C8\n"
"                B       loc_FF8610D0\n"
"                B       loc_FF861128\n"
"                B       loc_FF861150\n"
"                B       loc_FF861134\n"
"                B       loc_FF861140\n"
"                B       loc_FF861148\n"
"                B       loc_FF861158\n"
"                B       loc_FF861160\n"
"                B       loc_FF861168\n"
"                B       loc_FF861170\n"
"                B       loc_FF861178\n"
"                B       loc_FF861180\n"
"                B       loc_FF861188\n"
"                B       loc_FF861190\n"
"                B       loc_FF861198\n"
"                B       loc_FF8611A4\n"
"                B       loc_FF8611AC\n"
"                B       loc_FF8611B8\n"
"                B       loc_FF8611C0\n"
"                B       loc_FF8611C8\n"
"                B       loc_FF8611D0\n"
"                B       loc_FF8611D8\n"
"                B       loc_FF8611E4\n"
"                B       loc_FF861208\n"
"loc_FF861004:\n"
// jumptable FF860F80 entry 0
"                BL      sub_FF861864\n" // SsPrepareSeq.c 0
// TODO do we need the short press hack ?
"                BL      shooting_expo_param_override\n"  // +
"                BL      sub_FF85ED58\n"
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF861208\n"
"                BL      sub_FF860774\n"
"                MOV     R5, R0\n"
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF86104C\n"
"                MOV     R0, #0xC\n"
"                BL      sub_FF8659A4\n"
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#0x10]\n"
"                LDRNE   R0, [R5,#8]\n"
"                ORRNE   R0, R0, #0x40000000\n"
"                STRNE   R0, [R5,#8]\n"
"                BNE     loc_FF861208\n"
"loc_FF86104C:\n"
"                MOV     R0, R5\n"
"                BL      sub_FF860A18\n"
"                MOV     R0, R5\n"
"                BL      sub_FF934548\n" // SsCaptureSeq.c 0
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#0x10]\n"
"                B       loc_FF861208\n"
"loc_FF861068:\n"
// jumptable FF860F80 entry 1
// TODO this doesn't look like entry 1 on sd990
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF861094\n"
"                MOV     R0, #0xC\n"
"                BL      sub_FF8659A4\n"
"                TST     R0, #1\n"
"                LDRNE   R0, [SP]\n"
"                MOVNE   R1, #1\n"
"                LDRNE   R2, [R0,#0xC]\n"
"                MOVNE   R0, #1\n"
"                BNE     loc_FF861120\n"
"loc_FF861094:\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FF861320_my\n" // looks equivalent to sd990 sub_FF8662E0
"loc_FF86109C:\n"
"                STR     R7, [R4,#0x24]\n"
"                B       loc_FF861208\n"
"loc_FF8610A4:\n"
// jumptable FF860F80 entry 2
"                MOV     R0, #1\n"
"                BL      sub_FF861A7C\n" // SsPrepareSeq.c 0
"                B       loc_FF861208\n"
"loc_FF8610B0:\n"
// jumptable FF860F80 entry 4
"                BL      sub_FF8614AC\n"
"                B       loc_FF86109C\n"
"loc_FF8610B8:\n"
// jumptable FF860F80 entry 3
"                BL      sub_FF861844\n" // SsPrepareSeq.c 4
"                B       loc_FF86109C\n"
"loc_FF8610C0:\n"
// jumptable FF860F80 entry 5
"                BL      sub_FF86184C\n"
"                B       loc_FF861208\n"
"loc_FF8610C8:\n"
// jumptable FF860F80 entry 6
"                BL      sub_FF86199C\n" // SsPrepareSeq.c 960
"                B       loc_FF86112C\n"
"loc_FF8610D0:\n"
// jumptable FF860F80 entry 7
"                LDR     R5, [R0,#0xC]\n"
"                BL      sub_FF861854\n"
"                MOV     R0, R5\n"
"                BL      sub_FF93351C\n" // SsPrePreSeq.c 505
"                TST     R0, #1\n"
"                MOV     R8, R0\n"
"                BNE     loc_FF861110\n"
"                BL      sub_FF871E5C\n" // PropertyCase.c 0
"                STR     R0, [R5,#0x18]\n"
"                MOV     R0, R5\n"
"                BL      sub_FF934460\n" // SsCaptureSeq.c 1
"                MOV     R0, R5\n"
"                BL      sub_FF934850\n" // SsCaptureSeq.c 4
"                MOV     R8, R0\n"
"                LDR     R0, [R5,#0x18]\n"
"                BL      sub_FF872070\n" // PropertyCase.c 0
"loc_FF861110:\n"
"                BL      sub_FF861844\n" // SsPrepareSeq.c 4
"                MOV     R2, R5\n"
"                MOV     R1, #9\n"
"                MOV     R0, R8\n"
"loc_FF861120:\n"
"                BL      sub_FF85F284\n" // SsShootCtrl.c 0
"                B       loc_FF861208\n"
"loc_FF861128:\n"
// jumptable FF860F80 entry 8
"                BL      sub_FF8619FC\n" // SsPrepareSeq.c 0
"loc_FF86112C:\n"
"                BL      sub_FF85ED58\n"
"                B       loc_FF861208\n"
"loc_FF861134:\n"
// jumptable FF860F80 entry 10
"                LDR     R0, [R4,#0x54]\n"
"                BL      sub_FF861E10\n" // SsMovieRec.c 184
"                B       loc_FF861208\n"
"loc_FF861140:\n"
// jumptable FF860F80 entry 11
"                BL      sub_FF8620B8\n" // SsMovieRec.c 2
"                B       loc_FF861208\n"
"loc_FF861148:\n"
// jumptable FF860F80 entry 12
"                BL      sub_FF86214C\n" // SsMovieRec.c 43
"                B       loc_FF861208\n"
"loc_FF861150:\n"
// jumptable FF860F80 entry 9
"                BL      sub_FF861844\n" // SsPrepareSeq.c 4
"                B       loc_FF861208\n"
"loc_FF861158:\n"
// jumptable FF860F80 entry 13
"                BL      sub_FF93373C\n"
"                B       loc_FF861208\n"
"loc_FF861160:\n"
// jumptable FF860F80 entry 14
"                BL      sub_FF933924\n"
"                B       loc_FF861208\n"
"loc_FF861168:\n"
// jumptable FF860F80 entry 15
"                BL      sub_FF9339B4\n" // SsExpCompSeq.c 105
"                B       loc_FF861208\n"
"loc_FF861170:\n"
// jumptable FF860F80 entry 16
"                BL      sub_FF933A68\n"
"                B       loc_FF861208\n"
"loc_FF861178:\n"
// jumptable FF860F80 entry 17
"                MOV     R0, #0\n"
"                B       loc_FF86119C\n"
"loc_FF861180:\n"
// jumptable FF860F80 entry 18
"                BL      sub_FF933DC4\n"
"                B       loc_FF861208\n"
"loc_FF861188:\n"
// jumptable FF860F80 entry 19
"                BL      sub_FF933E54\n" // SsMFSeq.c 110
"                B       loc_FF861208\n"
"loc_FF861190:\n"
// jumptable FF860F80 entry 20
"                BL      sub_FF933F14\n" // SsMFSeq.c 177
"                B       loc_FF861208\n"
"loc_FF861198:\n"
// jumptable FF860F80 entry 21
"                MOV     R0, #1\n"
"loc_FF86119C:\n"
"                BL      sub_FF933C8C\n"
"                B       loc_FF861208\n"
"loc_FF8611A4:\n"
// jumptable FF860F80 entry 22
"                BL      sub_FF861BFC\n"
"                B       loc_FF861208\n"
"loc_FF8611AC:\n"
// jumptable FF860F80 entry 23
"                BL      sub_FF861C9C\n"
"                BL      sub_FF824A48\n"
"                B       loc_FF861208\n"
"loc_FF8611B8:\n"
// jumptable FF860F80 entry 24
"                BL      sub_FF933B24\n"
"                B       loc_FF861208\n"
"loc_FF8611C0:\n"
// jumptable FF860F80 entry 25
"                BL      sub_FF933B90\n" // SsChgExpSeq.c 0
"                B       loc_FF861208\n"
"loc_FF8611C8:\n"
// jumptable FF860F80 entry 26
"                BL      sub_FF86408C\n"
"                B       loc_FF861208\n"
"loc_FF8611D0:\n"
// jumptable FF860F80 entry 27
"                BL      sub_FF8640F4\n"
"                B       loc_FF861208\n"
"loc_FF8611D8:\n"
// jumptable FF860F80 entry 28
"                BL      sub_FF864150\n"
"                BL      sub_FF864110\n"
"                B       loc_FF861208\n"
"loc_FF8611E4:\n"
// jumptable FF860F80 entry 29
"                MOV     R0, #1\n"
"                BL      sub_FF935130\n"
"                LDRH    R0, [R4,#0x98]\n"
"                CMP     R0, #4\n"
"                BLNE    sub_FF8643BC\n" // SsLiveFunc.c 780
"                B       loc_FF861208\n"
"loc_FF8611FC:\n"
// jumptable FF860F80 default entry
"                LDR     R1, =0x6C9\n"
"                LDR     R0, =0xFF860A98\n" // aSsshoottask_c
"                BL      sub_FF81B284\n" // DebugAssert
"loc_FF861208:\n"
// jumptable FF860F80 entry 30
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0,#4]\n"
"                LDR     R0, [R6]\n"
"                BL      sub_FF869BC0\n"
"                LDR     R5, [SP]\n"
"                LDR     R0, [R5,#8]\n"
"                CMP     R0, #0\n"
"                LDREQ   R1, =0x12B\n"
"                LDREQ   R0, =0xFF860A98\n" // aSsshoottask_c
"                BLEQ    sub_FF81B284\n" // DebugAssert
"                STR     R7, [R5,#8]\n"
"                B       loc_FF860F48\n"
    );
}
