#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x9F90;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF93D820_my(){ 
 asm volatile(
        "STMFD   SP!, {R0-R10,LR}\n"
        "MOV     R6, #0\n"
        "MOV     R4, R0\n"
        "BL      sub_FF93E38C\n"
        "MVN     R1, #0\n" //0xFFFFFFFF\n"
        "BL      sub_FF827B50\n"
        "MOV     R2, #4\n"
		"ADD     R1, SP, #0x30-0x28\n"
        "MOV     R0, #0x8A\n"
        "BL      sub_FF86D25C\n"
        "TST     R0, #1\n"
        "MOVNE   R1, #0x218\n"
        "LDRNE   R0, =0xFF86D14C\n" // aSscaptureseq_c ; "SsCaptureSeq.c"\n"
        "BLNE    _DebugAssert\n"
        "LDR     R8, =0x19F40\n"
        "LDR     R5, =0x19E8C\n"
        "LDRSH   R1, [R8,#0xE]\n"
        "LDR     R0, [R5,#0x7C]\n"
        "BL      sub_FF8F3DC8\n"
        "BL      sub_FF845570\n" // GetCCDTemperature\n"
        "LDR     R2, =0x91B0\n"
        "ADD     R3, R4, #0x8C\n"
        "STRH    R0, [R4,#0x88]\n"
        // "STRD    R2, [SP,#0x30-0x30]\n"
        "STR     R2, [SP]\n"  //+
        "STR     R3, [SP,#4]\n"  //+
        "MOV     R1, R0\n"
        "LDRH    R0, [R5,#0x54]\n"
        "LDRSH   R2, [R8,#0xC]\n"
        "LDR     R3, =0x91AC\n"
        "BL      sub_FF93E880\n"
        "BL      capt_seq_hook_set_nr\n"
        "BL       sub_FF93D894\n"
 );
}

void __attribute__((naked,noinline)) sub_FF85E634_my() //#fs
{
	asm volatile (
        "STMFD   SP!, {R4-R6,LR}\n"
        "LDR     R4, [R0,#0xC]\n"
        "LDR     R6, =0x19E8C\n"
        "LDR     R0, [R4,#8]\n"
        "MOV     R5, #0\n"
        "ORR     R0, R0, #1\n"
        "STR     R0, [R4,#8]\n"
        "LDR     R0, [R6,#0x24]\n"
        "CMP     R0, #0\n"
        "MOVEQ   R0, #2\n"
        "BLEQ    sub_FF858610\n"
        "BL      sub_FF93C144\n"
        "LDR     R0, [R6,#0x24]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF85E6B4\n"
        "MOV     R0, R4\n"
        "BL      sub_FF93C5D8\n"
        "TST     R0, #1\n"
        "MOVNE   R2, R4\n"
        "LDMNEFD SP!, {R4-R6,LR}\n"
        "MOVNE   R1, #1\n"
        "BNE     sub_FF85C98C\n"
        "BL      sub_FF95DAFC\n"
        "BL      sub_FF86D3EC\n"
        "STR     R0, [R4,#0x14]\n"
        "MOV     R0, R4\n"
        "BL      sub_FF93D738\n"
        "BL      sub_FF93E214\n"
        "MOV     R0, R4\n"
        //"BL      sub_FF93D820\n"
        "BL      sub_FF93D820_my\n"
		"BL      capt_seq_hook_raw_here\n" // +
        "MOV     R5, R0\n"
        "B       loc_FF85E6C4\n"


"loc_FF85E6B4:\n" //                               ; CODE XREF: sub_FF85E634+38j
        "LDR     R0, =0x54E0\n"
        "LDR     R0, [R0,#4]\n"
        "CMP     R0, #0\n"
        "MOVNE   R5, #0x1D\n"

"loc_FF85E6C4:\n" //                               ; CODE XREF: sub_FF85E634+7Cj
        "BL      sub_FF93F268\n"
        "BL      sub_FF93F2A4\n"
        "MOV     R2, R4\n"
        "MOV     R1, #1\n"
        "MOV     R0, R5\n"
        "BL      sub_FF85C98C\n"
        "BL      sub_FF93DC28\n"
        "CMP     R0, #0\n"
        "LDRNE   R0, [R4,#8]\n"
        "ORRNE   R0, R0, #0x2000\n"
        "STRNE   R0, [R4,#8]\n"
        "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

//FF85E2B0
void __attribute__((naked,noinline)) capt_seq_task() //#fs
{
	asm volatile (
        "STMFD   SP!, {R3-R9,LR}\n"
        "LDR     R6, =0x19E8C\n"
        "LDR     R5, =0x54E0\n"
        "MOV     R9, #1\n"
        "MOV     R7, #0\n"

"loc_FF85E2C4:\n" //                               ; CODE XREF: task_CaptSeqTask+298j
        "LDR     R0, [R5,#0xC]\n"
        "MOV     R2, #0\n"
        "MOV     R1, SP\n"
        "BL      sub_FF827DA0\n"
        "TST     R0, #1\n"
        "BEQ     loc_FF85E2F0\n"
        "LDR     R1, =0x48E\n"
        "LDR     R0, =0xFF85DF88\n" // ; "SsShootTask.c"\n"
        "BL      _DebugAssert\n"
        "BL      sub_FF81BAA8\n" // ExitTask\n"
        "LDMFD   SP!, {R3-R9,PC}\n"


"loc_FF85E2F0:\n" //                               ; CODE XREF: task_CaptSeqTask+28j
        "LDR     R0, [SP,#0x20-0x20]\n"
        "LDR     R1, [R0]\n"
        "CMP     R1, #0x1B\n"
        "ADDLS   PC, PC, R1,LSL#2\n"
        "B       loc_FF85E510\n"


"loc_FF85E304:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E374\n"


"loc_FF85E308:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E3DC\n"


"loc_FF85E30C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E3E4\n"


"loc_FF85E310:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E3FC\n"


"loc_FF85E314:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E3F0\n"


"loc_FF85E318:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E404\n"


"loc_FF85E31C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E40C\n"


"loc_FF85E320:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E414\n"


"loc_FF85E324:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E46C\n"


"loc_FF85E328:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E478\n"


"loc_FF85E32C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E480\n"


"loc_FF85E330:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E488\n"


"loc_FF85E334:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E490\n"


"loc_FF85E338:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E498\n"


"loc_FF85E33C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4A0\n"


"loc_FF85E340:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4A8\n"


"loc_FF85E344:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4B0\n"


"loc_FF85E348:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4BC\n"


"loc_FF85E34C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4C4\n"


"loc_FF85E350:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4CC\n"


"loc_FF85E354:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4D4\n"


"loc_FF85E358:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4E0\n"


"loc_FF85E35C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4E8\n"


"loc_FF85E360:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4F0\n"


"loc_FF85E364:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E4F8\n"


"loc_FF85E368:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E500\n"


"loc_FF85E36C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E508\n"


"loc_FF85E370:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "B       loc_FF85E51C\n"


"loc_FF85E374:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj
        "BL      sub_FF93C168\n"
        "BL      shooting_expo_param_override\n" // +
        "BL      sub_FF85C438\n"
        "LDR     R0, [R6,#0x24]\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FF85E51C\n"
        "BL      sub_FF85DC58\n"
        "MOV     R4, R0\n"
        "LDR     R0, [R6,#0x24]\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FF85E3BC\n"
        "MOV     R0, #0xC\n"
        "BL      sub_FF861300\n"
        "TST     R0, #1\n"
        "STRNE   R9, [R5,#4]\n"
        "LDRNE   R0, [R4,#8]\n"
        "ORRNE   R0, R0, #0x40000000\n"
        "STRNE   R0, [R4,#8]\n"
        "BNE     loc_FF85E51C\n"

"loc_FF85E3BC:\n" //                               ; CODE XREF: task_CaptSeqTask+E8j
        "BL      sub_FF95DAFC\n"
        "BL      sub_FF86D3EC\n"
        "STR     R0, [R4,#0x14]\n"
        "MOV     R0, R4\n"
        "BL      sub_FF93D820_my\n" // changed
		"BL      capt_seq_hook_raw_here\n" // +
        "TST     R0, #1\n"
        "STRNE   R9, [R5,#4]\n"
        "B       loc_FF85E51C\n"


"loc_FF85E3DC:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj

		//"BL      sub_FF85E634\n"
        "BL      sub_FF85E634_my\n" //_my
        "B       loc_FF85E3F4\n"


"loc_FF85E3E4:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "MOV     R0, #1\n"
        "BL      sub_FF93C310\n"
        "B       loc_FF85E51C\n"


"loc_FF85E3F0:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93BE00\n"

"loc_FF85E3F4:\n" //                               ; CODE XREF: task_CaptSeqTask+130j

        "STR     R7, [R6,#0x24]\n"
        "B       loc_FF85E51C\n"


"loc_FF85E3FC:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93C134\n"
        "B       loc_FF85E3F4\n"


"loc_FF85E404:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93C13C\n"
        "B       loc_FF85E51C\n"


"loc_FF85E40C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93C230\n"
        "B       loc_FF85E470\n"


"loc_FF85E414:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "LDR     R4, [R0,#0xC]\n"
        "BL      sub_FF93C144\n"
        "MOV     R0, R4\n"
        "BL      sub_FF93C958\n"
        "TST     R0, #1\n"
        "MOV     R8, R0\n"
        "BNE     loc_FF85E454\n"
        "BL      sub_FF86D3EC\n"
        "STR     R0, [R4,#0x14]\n"
        "MOV     R0, R4\n"
        "BL      sub_FF93D738\n"
        "MOV     R0, R4\n"
        "BL      sub_FF93DC88\n"
        "MOV     R8, R0\n"
        "LDR     R0, [R4,#0x14]\n"
        "BL      sub_FF86D5F8\n"

"loc_FF85E454:\n" //                               ; CODE XREF: task_CaptSeqTask+17Cj
        "BL      sub_FF93C134\n"
        "MOV     R2, R4\n"
        "MOV     R1, #9\n"
        "MOV     R0, R8\n"
        "BL      sub_FF85C98C\n"
        "B       loc_FF85E51C\n"


"loc_FF85E46C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93C290\n"

"loc_FF85E470:\n" //                               ; CODE XREF: task_CaptSeqTask+160j
        "BL      sub_FF85C438\n"
        "B       loc_FF85E51C\n"


"loc_FF85E478:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93C134\n"
        "B       loc_FF85E51C\n"


"loc_FF85E480:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93CBC4\n"
        "B       loc_FF85E51C\n"


"loc_FF85E488:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93CDAC\n"
        "B       loc_FF85E51C\n"


"loc_FF85E490:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93CE3C\n"
        "B       loc_FF85E51C\n"


"loc_FF85E498:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93CEF0\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4A0:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93D0E8\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4A8:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93D138\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4B0:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "MOV     R0, #0\n"
        "BL      sub_FF93D1BC\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4BC:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93D30C\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4C4:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93D3A0\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4CC:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93D468\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4D4:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93C434\n"
        "BL      sub_FF824C48\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4E0:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93CFAC\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4E8:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93D018\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4F0:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93F24C\n"
        "B       loc_FF85E51C\n"


"loc_FF85E4F8:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93F268\n"
        "B       loc_FF85E51C\n"


"loc_FF85E500:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93F278\n"
        "B       loc_FF85E51C\n"


"loc_FF85E508:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "BL      sub_FF93F2A4\n"
        "B       loc_FF85E51C\n"


"loc_FF85E510:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "LDR     R1, =0x58E\n"
        "LDR     R0, =0xFF85DF88\n"
        "BL      _DebugAssert\n"

"loc_FF85E51C:\n" //                               ; CODE XREF: task_CaptSeqTask+4Cj


        "LDR     R0, [SP,#0x20-0x20]\n"
        "LDR     R1, [R0,#4]\n"
        "LDR     R0, [R5,#8]\n"
        "BL      sub_FF827B1C\n"
        "LDR     R4, [SP,#0x20-0x20]\n"
        "LDR     R0, [R4,#8]\n"
        "CMP     R0, #0\n"
        "LDREQ   R1, =0x10D\n"
        "LDREQ   R0, =0xFF85DF88\n"
        "BLEQ    _DebugAssert\n"
        "STR     R7, [R4,#8]\n"
        "B       loc_FF85E2C4\n"
    );
} //#fe
