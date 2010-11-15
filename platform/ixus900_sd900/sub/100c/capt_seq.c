#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "core.h"

//static long *nrflag = (long*)0x6ACC;   // SD800
static long *nrflag = (long*)0x6B78;   // ??? ROM:FF995AB8

#include "../../../generic/capt_seq.c"

// ROM:FF992B24 task_CaptSeqTask() (SD800: ROM:FF998E1C)
void __attribute__((naked,noinline)) capt_seq_task() {
    asm volatile(
        "STMFD   SP!, {R4,LR}\n"
        "SUB     SP, SP, #4\n"
        "MOV     R4, SP\n"
        "B       loc_FF992CA8\n"

        "loc_FF992B34:\n"
        "LDR     R2, [SP]\n"
        "LDR     R3, [R2]\n"
        "MOV     R0, R2\n"
        "CMP     R3, #0x17\n"   // switch 24 cases
        "LDRLS   PC, [PC,R3,LSL#2]\n"   // switch jump
        "B       loc_FF992C7C\n"   // switch default

        ".long loc_FF992BAC\n"
        ".long loc_FF992BB8\n"
        ".long loc_FF992BC0\n"
        ".long loc_FF992BD4\n"
        ".long loc_FF992BCC\n"
        ".long loc_FF992BDC\n"
        ".long loc_FF992BE4\n"
        ".long loc_FF992BF0\n"
        ".long loc_FF992BF8\n"
        ".long loc_FF992C04\n"
        ".long loc_FF992C0C\n"
        ".long loc_FF992C14\n"
        ".long loc_FF992C1C\n"
        ".long loc_FF992C24\n"
        ".long loc_FF992C2C\n"
        ".long loc_FF992C38\n"
        ".long loc_FF992C40\n"
        ".long loc_FF992C48\n"
        ".long loc_FF992C50\n"
        ".long loc_FF992C5C\n"
        ".long loc_FF992C64\n"
        ".long loc_FF992C6C\n"
        ".long loc_FF992C74\n"
        ".long loc_FF992C90\n"

        "loc_FF992BAC:\n"
        "BL      sub_FF9931C0\n"   // jumptable FF992B44 case 0
        "BL      shooting_expo_param_override\n"   // + from SD800
        "BL      sub_FF9906E0\n"
        "B       loc_FF992C8C\n"

        "loc_FF992BB8:\n"
        //"BL      sub_FF9925E4\n"   // jumptable FF992B44 case 1
        "BL       sub_FF9925E4_my\n"   // + like SD800
        "B       loc_FF992C8C\n"

        "loc_FF992BC0:\n"
        "MOV     R0, #1\n"         // jumptable FF992B44 case 2
        "BL      sub_FF993500\n"
        "B       loc_FF992C8C\n"

        "loc_FF992BCC:\n"
        "BL      sub_FF992D9C\n"   // jumptable FF992B44 case 4
        "B       loc_FF992C8C\n"

        "loc_FF992BD4:\n"
        "BL      sub_FF99318C\n"   // BackLightDrv_LcdBackLightOff_5() jumptable FF992B44 case 3
        "B       loc_FF992C8C\n"

        "loc_FF992BDC:\n"
        "BL      sub_FF99319C\n"   // jumptable FF992B44 case 5
        "B       loc_FF992C8C\n"

        "loc_FF992BE4:\n"
        "BL      sub_FF9933E0\n"   // jumptable FF992B44 case 6
        "BL      sub_FF9906E0\n"
        "B       loc_FF992C8C\n"

        "loc_FF992BF0:\n"
        "BL      sub_FF992834\n"   // jumptable FF992B44 case 7
        "B       loc_FF992C8C\n"

        "loc_FF992BF8:\n"
        "BL      sub_FF993454\n"   // jumptable FF992B44 case 8
        "BL      sub_FF9906E0\n"
        "B       loc_FF992C8C\n"

        "loc_FF992C04:\n"
        "BL      sub_FF99318C\n"   // BackLightDrv_LcdBackLightOff_5() jumptable FF992B44 case 9
        "B       loc_FF992C8C\n"

        "loc_FF992C0C:\n"
        "BL      sub_FF994C0C\n"   // jumptable FF992B44 case 10
        "B       loc_FF992C8C\n"

        "loc_FF992C14:\n"
        "BL      sub_FF994DE0\n"   // jumptable FF992B44 case 11
        "B       loc_FF992C8C\n"

        "loc_FF992C1C:\n"
        "BL      sub_FF994E74\n"   // jumptable FF992B44 case 12
        "B       loc_FF992C8C\n"

        "loc_FF992C24:\n"
        "BL      sub_FF994F10\n"   // jumptable FF992B44 case 13
        "B       loc_FF992C8C\n"

        "loc_FF992C2C:\n"
        "MOV     R0, #0\n"         // jumptable FF992B44 case 14
        "BL      sub_FF99517C\n"
        "B       loc_FF992C8C\n"

        "loc_FF992C38:\n"
        "BL      sub_FF995354\n"   // jumptable FF992B44 case 15
        "B       loc_FF992C8C\n"

        "loc_FF992C40:\n"
        "BL      sub_FF9953EC\n"   // jumptable FF992B44 case 16
        "B       loc_FF992C8C\n"

        "loc_FF992C48:\n"
        "BL      sub_FF9954A8\n"   // jumptable FF992B44 case 17
        "B       loc_FF992C8C\n"

        "loc_FF992C50:\n"
        "BL      sub_FF993670\n"   // jumptable FF992B44 case 18
        "BL      sub_FF9923A4\n"
        "B       loc_FF992C8C\n"

        "loc_FF992C5C:\n"
        "BL      sub_FF995050\n"   // jumptable FF992B44 case 19
        "B       loc_FF992C8C\n"

        "loc_FF992C64:\n"
        "BL      sub_FF9950A8\n"   // jumptable FF992B44 case 20
        "B       loc_FF992C8C\n"

        "loc_FF992C6C:\n"
        "BL      sub_FF9924C4\n"   // jumptable FF992B44 case 21
        "B       loc_FF992C8C\n"

        "loc_FF992C74:\n"
        "BL      sub_FF98F6F0\n"   // jumptable FF992B44 case 22
        "B       loc_FF992C8C\n"

        "loc_FF992C7C:\n"
        "MOV     R1, #0x4E0\n"     // switch default
        "LDR     R0, =0xFF9920E4\n"   // aShoottask_c
        "ADD     R1, R1, #7\n"
        "BL      sub_FF813D70\n"   // DebugAssert()

        "loc_FF992C8C:\n"
        "LDR     R2, [SP]\n"

        "loc_FF992C90:\n"
        "LDR     R3, =0x76CBC\n"   // jumptable FF992B44 case 23
        "LDR     R1, [R2,#4]\n"
        "LDR     R0, [R3]\n"
        "BL      sub_FF820CE0\n"   // SetEventFlag()
        "LDR     R0, [SP]\n"
        "BL      sub_FF9921D4\n"

        "loc_FF992CA8:\n"
        "LDR     R3, =0x76CC0\n"
        "MOV     R1, R4\n"
        "LDR     R0, [R3]\n"
        "MOV     R2, #0\n"
        "BL      sub_FF8213F8\n"   // ReceiveMessageQueue
        "TST     R0, #1\n"
        "BEQ     loc_FF992B34\n"
        "MOV     R1, #0x410\n"
        "LDR     R0, =0xFF9920E4\n"   // aShoottask_c
        "ADD     R1, R1, #9\n"
        "BL      sub_FF813D70\n"   // DebugAssert()
        "BL      sub_FF822954\n"   // ExitTask()
        "ADD     SP, SP, #4\n"
        "LDMFD   SP!, {R4,PC}\n"
    );
}

// ROM:FF9925E4
void __attribute__((naked,noinline)) sub_FF9925E4_my(long p) {
    asm volatile(
        "STMFD   SP!, {R4,LR}\n"
        "LDR     R4, [R0,#0xC]\n"
        "LDR     R3, [R4,#8]\n"
        "ORR     R3, R3, #1\n"
        "STR     R3, [R4,#8]\n"
        "MOV     R0, #0xC\n"
        "BL      sub_FF99CC0C\n"
        "TST     R0, #1\n"
        "BEQ     loc_FF992628\n"
        "LDR     R3, [R4,#8]\n"
        "MOV     R0, #1\n"
        "ORR     R3, R3, #0x40000000\n"
        "STR     R3, [R4,#8]\n"

        "loc_FF992618:\n"
        "MOV     R2, R4\n"
        "MOV     R1, #1\n"
        "LDMFD   SP!, {R4,LR}\n"
        "B       sub_FF990BD8\n"   // LOCATION: ShootCtrl.c:1888

        "loc_FF992628:\n"
        "LDR     R1, =0xA2400\n"
        "MOV     R3, #0x8200\n"
        "LDRH    R2, [R1]\n"
        "ADD     R3, R3, #0xA\n"
        "CMP     R2, R3\n"
        "BEQ     loc_FF992674\n"
        "LDRH    R3, [R1,#0x88]\n"
        "CMP     R3, #3\n"
        "BEQ     loc_FF992674\n"
        "LDR     R3, [R4,#0xC]\n"
        "CMP     R3, #1\n"
        "BLS     loc_FF992674\n"
        "LDRH    R3, [R1,#0x86]\n"
        "CMP     R3, #0\n"
        "BNE     loc_FF992674\n"
        "LDRH    R3, [R1,#0x82]\n"
        "CMP     R3, #2\n"
        "BNE     loc_FF992674\n"
        "BL      sub_FF9936E8\n"

        "loc_FF992674:\n"
        "LDR     R1, =0xA2400\n"
        "MOV     R3, #0x8200\n"
        "LDRH    R2, [R1]\n"
        "ADD     R3, R3, #0xA\n"
        "CMP     R2, R3\n"
        "BEQ     loc_FF9926BC\n"
        "LDRH    R3, [R1,#0x88]\n"
        "CMP     R3, #3\n"
        "BEQ     loc_FF9926BC\n"
        "LDR     R3, [R4,#0xC]\n"
        "CMP     R3, #1\n"
        "BLS     loc_FF9926BC\n"
        "LDRH    R3, [R1,#0x86]\n"
        "CMP     R3, #0\n"
        "BNE     loc_FF9926BC\n"
        "LDRH    R3, [R1,#0x82]\n"
        "CMP     R3, #2\n"
        "BEQ     loc_FF992724\n"

        "loc_FF9926BC:\n"
        "LDR     R2, =0xA2400\n"
        "LDRH    R3, [R2,#0x88]\n"
        "CMP     R3, #3\n"
        "BEQ     loc_FF99273C\n"
        "LDRH    R3, [R2,#0x86]\n"
        "CMP     R3, #0\n"
        "BNE     loc_FF99273C\n"
        "LDRH    R1, [R2,#0x82]\n"
        "CMP     R1, #1\n"
        "BNE     loc_FF99273C\n"
        "LDRH    R2, [R2]\n"
        "MOV     R3, #0x8200\n"
        "ADD     R3, R3, #0xA\n"
        "CMP     R2, R3\n"
        "BEQ     loc_FF99273C\n"
        "LDR     R3, [R4,#0xC]\n"
        "CMP     R3, #1\n"
        "BLS     loc_FF99273C\n"
        "ADD     R3, R1, #0xFF00\n"
        "ADD     R3, R3, #0xFF\n"
        "MOV     R3, R3,LSL#16\n"
        "CMP     R3, #0x10000\n"
        "BHI     loc_FF99273C\n"
        "LDR     R3, [R4,#0x10]\n"
        "CMP     R3, #1\n"
        "BNE     loc_FF99273C\n"

        "loc_FF992724:\n"
        "LDR     R3, =0x76CBC\n"
        "MOV     R2, #0xEA00\n"
        "LDR     R0, [R3]\n"
        "MOV     R1, #0x8000000\n"
        "ADD     R2, R2, #0x60\n"
        "BL      sub_FF99D090\n"   // LOCATION: ShootSeqCommon.c:452

        "loc_FF99273C:\n"
        "BL      sub_FF9924C4\n"
        "BL      sub_FF9931AC\n"   // Set_CMD25Write_27()
        "MOV     R0, R4\n"
        "BL      sub_FF9943AC\n"   // LOCATION: PrePreSeq.c:236
        "TST     R0, #1\n"
        "BNE     loc_FF992618\n"
        "BL      sub_FF9D5114\n"
        "BL      sub_FF825AC4\n"
        "STR     R0, [R4,#0x14]\n"
        "MOV     R0, R4\n"
        "BL      sub_FF995938\n"
        "BL      sub_FF9963A4\n"
        "MOV     R0, R4\n"
        //"BL      sub_FF995A50\n"   // original
        "BL      sub_FF995A50_my\n"   // + from SD800
        "BL      capt_seq_hook_raw_here\n"   // + from SD800
        "MOV     R1, #1\n"
        "MOV     R2, R4\n"
        "BL      sub_FF990BD8\n"
        "BL      sub_FF995E80\n"
        "CMP     R0, #0\n"
        "LDRNE   R3, [R4,#8]\n"
        "ORRNE   R3, R3, #0x2000\n"
        "STRNE   R3, [R4,#8]\n"
        "LDR     R2, =0xA2400\n"
        "LDRH    R3, [R2,#0x88]\n"
        "CMP     R3, #3\n"
        "LDMEQFD SP!, {R4,PC}\n"
        "LDRH    R3, [R2,#0x86]\n"
        "CMP     R3, #0\n"
        "LDMNEFD SP!, {R4,PC}\n"
        "LDRH    R3, [R2,#0x82]\n"
        "CMP     R3, #2\n"
        "LDMNEFD SP!, {R4,PC}\n"
        "MOV     R0, R4\n"
        "LDMFD   SP!, {R4,LR}\n"
        "B       sub_FF993740\n"
    );
}

// ROM:FF995A50
void __attribute__((naked,noinline)) sub_FF995A50_my(long p) {
    asm volatile(
        "STMFD   SP!, {R4,R5,LR}\n"
        "MOV     R4, R0\n"
        "SUB     SP, SP, #0xC\n"
        "BL      sub_FF996518\n"   // LOCATION: ShootEvent.c:60
        "MVN     R1, #0\n"
        "BL      sub_FF820E7C\n"   // ClearEventFlag()
        "MOV     R0, #0x120\n"
        "ADD     R0, R0, #2\n"
        "ADD     R1, SP, #4\n"
        "MOV     R2, #4\n"
        "BL      sub_FF8258C8\n"   // GetPropertyCase()
        "TST     R0, #1\n"
        "BEQ     loc_FF995A90\n"
        "LDR     R0, =0xFF9958CC\n"   // aCaptureseq_c
        "MOV     R1, #0x1DC\n"
        "BL      sub_FF813D70\n"   // DebugAssert()

        "loc_FF995A90:\n"
        "LDR     R3, =0xA2400\n"
        "LDR     R2, =0xA24C0\n"
        "LDR     R0, [R3,#0x7C]\n"
        "LDRSH   R1, [R2,#0xE]\n"
        "BL      sub_FF8B0C2C\n"   // nullsub_28()
        "MOV     R0, R4\n"
        "BL      sub_FF995850\n"
        "BL      wait_until_remote_button_is_released\n"   // + from SD800
        "BL      capt_seq_hook_set_nr\n"   // + from SD800
        "LDR     R3, =0x6B7C\n"
        "LDR     R0, [R3]\n"
        "B       sub_FF995AB4\n"   // branche to original function
    );
}
