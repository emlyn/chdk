#include "lolevel.h"
#include "platform.h"
#include "core.h"

// @ FF93D898
static long *nrflag = (long*)0x91AC;

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
        "STRD    R2, [SP,#0x30-0x30]\n"
        "MOV     R1, R0\n"
        "LDRH    R0, [R5,#0x54]\n"
        "LDRSH   R2, [R8,#0xC]\n"
        "LDR     R3, =0x91AC\n"
        "BL      sub_FF93E880\n"
        "BL      wait_until_remote_button_is_released\n" // +
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


// Extracted method: task_ExpDrvTask (FF8B6A80) 
void __attribute__((naked,noinline)) exp_drv_task()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"SUB     SP, SP, #0x20\n"
		"LDR     R8, =0xBB8\n"
		"LDR     R7, =0x6E30\n"
		"LDR     R5, =0x3E12C\n"
		"MOV     R0, #0\n"
		"ADD     R6, SP, #0x38-0x28\n"
		"STR     R0, [SP,#0x38-0x2C]\n"

		"loc_FF8B6AA0:\n"
		"LDR     R0, [R7,#0x20]\n"
		"MOV     R2, #0\n"
		"ADD     R1, SP, #0x38-0x1C\n"
		"BL      sub_FF827DA0\n" // LOCATION: KerQueue.c:0
		"LDR     R0, [SP,#0x38-0x2C]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FF8B6AE8\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0x13\n"
		"CMPNE   R0, #0x14\n"
		"CMPNE   R0, #0x15\n"
		"BEQ     loc_FF8B6C04\n"
		"CMP     R0, #0x27\n"
		"BEQ     loc_FF8B6BDC\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B6A30\n" // LOCATION: ExpDrv.c:512

		"loc_FF8B6AE8:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x2C\n"
		"BNE     loc_FF8B6B18\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7CEC\n" // LOCATION: ExpDrv.c:268
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF827B1C\n"
		"BL      sub_FF81BAA8\n" // eventproc_export_ExitTask
		"ADD     SP, SP, #0x20\n"
		"LDMFD   SP!, {R4-R8,PC}\n"

		"loc_FF8B6B18:\n"
		"CMP     R1, #0x2B\n"
		"BNE     loc_FF8B6B34\n"
		"LDR     R2, [R0,#0x88]!\n"
		"LDR     R1, [R0,#4]\n"
		"MOV     R0, R1\n"
		"BLX     R2\n"
		"B       loc_FF8B706C\n"

		"loc_FF8B6B34:\n"
		"CMP     R1, #0x25\n"
		"BNE     loc_FF8B6B84\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827B50\n"
		"LDR     R0, =0xFF8B34B8\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF92FACC\n" // LOCATION: IrisController.c:74
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827A54\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0xD1B\n"
		"BNE     loc_FF8B6BC8\n"

		"loc_FF8B6B70:\n"
		"LDR     R1, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R1,#0x8C]\n"
		"LDR     R1, [R1,#0x88]\n"
		"BLX     R1\n"
		"B       loc_FF8B706C\n"

		"loc_FF8B6B84:\n"
		"CMP     R1, #0x26\n"
		"BNE     loc_FF8B6BD4\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B6A30\n" // LOCATION: ExpDrv.c:512
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827B50\n"
		"LDR     R0, =0xFF8B34C8\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF92FD54\n" // LOCATION: IrisController.c:160
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827A54\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"BEQ     loc_FF8B6B70\n"
		"LDR     R1, =0xD25\n"

		"loc_FF8B6BC8:\n"
		"LDR     R0, =0xFF8B3BB8\n" // "ExpDrv.c"
		"BL      _DebugAssert\n"
		"B       loc_FF8B6B70\n"

		"loc_FF8B6BD4:\n"
		"CMP     R1, #0x27\n"
		"BNE     loc_FF8B6BEC\n"

		"loc_FF8B6BDC:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B6A30\n" // LOCATION: ExpDrv.c:512
		"B       loc_FF8B6B70\n"

		"loc_FF8B6BEC:\n"
		"CMP     R1, #0x2A\n"
		"BNE     loc_FF8B6C04\n"
		"BL      sub_FF895DFC\n" // LOCATION: Shutter.c:2
		"BL      sub_FF896BC8\n" // LOCATION: ImgPixel.c:0
		"BL      sub_FF89664C\n" // LOCATION: ImgGain.c:0
		"B       loc_FF8B6B70\n"

		"loc_FF8B6C04:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R4, #1\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x11\n"
		"CMPNE   R1, #0x12\n"
		"BNE     loc_FF8B6C74\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B5544\n" // LOCATION: ExpDrv.c:2
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B80C0\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x90]\n"
		"LDR     R2, [R0,#0x94]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"B       loc_FF8B6FAC\n"

		"loc_FF8B6C74:\n"
		"CMP     R1, #0x13\n"
		"CMPNE   R1, #0x14\n"
		"CMPNE   R1, #0x15\n"
		"BNE     loc_FF8B6D28\n"
		"ADD     R3, SP, #0x38-0x2C\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B578C\n" // LOCATION: ExpDrv.c:0
		"CMP     R0, #1\n"
		"MOV     R4, R0\n"
		"CMPNE   R4, #5\n"
		"BNE     loc_FF8B6CC4\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, R4\n"
		"LDR     R1, [R0,#0x7C]!\n"
		"LDR     R12, [R0,#0xC]!\n"
		"LDR     R3, [R0,#4]\n"
		"MOV     R0, SP\n"
		"BLX     R12\n"
		"B       loc_FF8B6CFC\n"

		"loc_FF8B6CC4:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"CMP     R4, #2\n"
		"LDR     R3, [R0,#0x8C]\n"
		"CMPNE   R4, #6\n"
		"BNE     loc_FF8B6D10\n"
		"LDR     R12, [R0,#0x88]\n"
		"MOV     R0, SP\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"BLX     R12\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B6744\n" // LOCATION: ExpDrv.c:0

		"loc_FF8B6CFC:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R2, [SP,#0x38-0x2C]\n"
		"MOV     R1, R4\n"
		"BL      sub_FF8B69D0\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6FAC\n"

		"loc_FF8B6D10:\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R12, [R0,#0x88]\n"
		"ADD     R0, R0, #4\n"
		"MOV     R2, R4\n"
		"BLX     R12\n"
		"B       loc_FF8B6FAC\n"

		"loc_FF8B6D28:\n"
		"CMP     R1, #0x21\n"
		"CMPNE   R1, #0x22\n"
		"BNE     loc_FF8B6D74\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B4AD0\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B4DC0\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6FAC\n"

		"loc_FF8B6D74:\n"
		"ADD     R1, R0, #4\n"
		"LDMIA   R1, {R2,R3,R12}\n"
		"STMIA   R6, {R2,R3,R12}\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x24\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6D90:\n"
		"B       loc_FF8B6E24\n"

		"loc_FF8B6D94:\n"
		"B       loc_FF8B6E24\n"

		"loc_FF8B6D98:\n"
		"B       loc_FF8B6E74\n"

		"loc_FF8B6D9C:\n"
		"B       loc_FF8B6E7C\n"

		"loc_FF8B6DA0:\n"
		"B       loc_FF8B6E7C\n"

		"loc_FF8B6DA4:\n"
		"B       loc_FF8B6E7C\n"

		"loc_FF8B6DA8:\n"
		"B       loc_FF8B6E24\n"

		"loc_FF8B6DAC:\n"
		"B       loc_FF8B6E74\n"

		"loc_FF8B6DB0:\n"
		"B       loc_FF8B6E7C\n"

		"loc_FF8B6DB4:\n"
		"B       loc_FF8B6E7C\n"

		"loc_FF8B6DB8:\n"
		"B       loc_FF8B6E94\n"

		"loc_FF8B6DBC:\n"
		"B       loc_FF8B6E94\n"

		"loc_FF8B6DC0:\n"
		"B       loc_FF8B6F80\n"

		"loc_FF8B6DC4:\n"
		"B       loc_FF8B6F88\n"

		"loc_FF8B6DC8:\n"
		"B       loc_FF8B6F88\n"

		"loc_FF8B6DCC:\n"
		"B       loc_FF8B6F88\n"

		"loc_FF8B6DD0:\n"
		"B       loc_FF8B6F88\n"

		"loc_FF8B6DD4:\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6DD8:\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6DDC:\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6DE0:\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6DE4:\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6DE8:\n"
		"B       loc_FF8B6E84\n"

		"loc_FF8B6DEC:\n"
		"B       loc_FF8B6E8C\n"

		"loc_FF8B6DF0:\n"
		"B       loc_FF8B6E8C\n"

		"loc_FF8B6DF4:\n"
		"B       loc_FF8B6EA0\n"

		"loc_FF8B6DF8:\n"
		"B       loc_FF8B6EA0\n"

		"loc_FF8B6DFC:\n"
		"B       loc_FF8B6EA8\n"

		"loc_FF8B6E00:\n"
		"B       loc_FF8B6ED8\n"

		"loc_FF8B6E04:\n"
		"B       loc_FF8B6F08\n"

		"loc_FF8B6E08:\n"
		"B       loc_FF8B6F38\n"

		"loc_FF8B6E0C:\n"
		"B       loc_FF8B6F68\n"

		"loc_FF8B6E10:\n"
		"B       loc_FF8B6F68\n"

		"loc_FF8B6E14:\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6E18:\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6E1C:\n"
		"B       loc_FF8B6F70\n"

		"loc_FF8B6E20:\n"
		"B       loc_FF8B6F78\n"

		"loc_FF8B6E24:\n"
		// jumptable FF8B6D88 entries 0,1,6
		"BL      sub_FF8B39A0\n" // LOCATION: ExpDrv.c:800
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6E74:\n"
		// jumptable FF8B6D88 entries 2,7
		"BL      sub_FF8B3C30\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6E7C:\n"
		// jumptable FF8B6D88 entries 3-5,8,9
		"BL      sub_FF8B3E34\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6E84:\n"
		// jumptable FF8B6D88 entry 22
		"BL      sub_FF8B409C\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6E8C:\n"
		// jumptable FF8B6D88 entries 23,24
		"BL      sub_FF8B4290\n" // LOCATION: ExpDrv.c:11
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6E94:\n"
		// jumptable FF8B6D88 entries 10,11
		//"BL      sub_FF8B44F8\n" // LOCATION: ExpDrv.c:2
		"BL      sub_FF8B44F8_my\n" //------------>
		"MOV     R4, #0\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6EA0:\n"
		// jumptable FF8B6D88 entries 25,26
		"BL      sub_FF8B4634\n"
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6EA8:\n"
		// jumptable FF8B6D88 entry 27
		"LDRH    R1, [R0,#4]\n"
		"STRH    R1, [SP,#0x38-0x28]\n"
		"LDRH    R1, [R5,#2]\n"
		"STRH    R1, [SP,#0x38-0x26]\n"
		"LDRH    R1, [R5,#4]\n"
		"STRH    R1, [SP,#0x38-0x24]\n"
		"LDRH    R1, [R5,#6]\n"
		"STRH    R1, [SP,#0x38-0x22]\n"
		"LDRH    R1, [R0,#0xC]\n"
		"STRH    R1, [SP,#0x38-0x20]\n"
		"BL      sub_FF8B7D60\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6ED8:\n"
		// jumptable FF8B6D88 entry 28
		"LDRH    R1, [R0,#4]\n"
		"STRH    R1, [SP,#0x38-0x28]\n"
		"LDRH    R1, [R5,#2]\n"
		"STRH    R1, [SP,#0x38-0x26]\n"
		"LDRH    R1, [R5,#4]\n"
		"STRH    R1, [SP,#0x38-0x24]\n"
		"LDRH    R1, [R5,#6]\n"
		"STRH    R1, [SP,#0x38-0x22]\n"
		"LDRH    R1, [R5,#8]\n"
		"STRH    R1, [SP,#0x38-0x20]\n"
		"BL      sub_FF8B7EDC\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6F08:\n"
		// jumptable FF8B6D88 entry 29
		"LDRH    R1, [R5]\n"
		"STRH    R1, [SP,#0x38-0x28]\n"
		"LDRH    R1, [R0,#6]\n"
		"STRH    R1, [SP,#0x38-0x26]\n"
		"LDRH    R1, [R5,#4]\n"
		"STRH    R1, [SP,#0x38-0x24]\n"
		"LDRH    R1, [R5,#6]\n"
		"STRH    R1, [SP,#0x38-0x22]\n"
		"LDRH    R1, [R5,#8]\n"
		"STRH    R1, [SP,#0x38-0x20]\n"
		"BL      sub_FF8B7F88\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6F38:\n"
		// jumptable FF8B6D88 entry 30
		"LDRH    R1, [R5]\n"
		"STRH    R1, [SP,#0x38-0x28]\n"
		"LDRH    R1, [R5,#2]\n"
		"STRH    R1, [SP,#0x38-0x26]\n"
		"LDRH    R1, [R5,#4]\n"
		"STRH    R1, [SP,#0x38-0x24]\n"
		"LDRH    R1, [R5,#6]\n"
		"STRH    R1, [SP,#0x38-0x22]\n"
		"LDRH    R1, [R0,#0xC]\n"
		"STRH    R1, [SP,#0x38-0x20]\n"
		"BL      sub_FF8B8028\n" // LOCATION: ExpDrv.c:32
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6F68:\n"
		// jumptable FF8B6D88 entries 31,32
		"BL      sub_FF8B48A8\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6F70:\n"
		// jumptable FF8B6D88 entry 35
		"BL      sub_FF8B4EC4\n" // LOCATION: ExpDrv.c:10
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6F78:\n"
		// jumptable FF8B6D88 entry 36
		"BL      sub_FF8B50FC\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6F80:\n"
		// jumptable FF8B6D88 entry 12
		"BL      sub_FF8B5274\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6F8C\n"

		"loc_FF8B6F88:\n"
		// jumptable FF8B6D88 entries 13-16
		"BL      sub_FF8B540C\n" // LOCATION: ExpDrv.c:128

		"loc_FF8B6F8C:\n"
		// jumptable FF8B6D88 default entry
		// jumptable FF8B6D88 entries 17-21,33,34
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"CMP     R4, #1\n"
		"BNE     loc_FF8B6FF4\n"

		"loc_FF8B6FAC:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, #0xC\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R0, R0, R1,LSL#2\n"
		"SUB     R4, R0, #8\n"
		"LDR     R0, =0x3E12C\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAAC800\n"
		"LDR     R0, =0x3E138\n"
		"MOV     R2, #0xC\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAAC800\n"
		"LDR     R0, =0x3E144\n"
		"MOV     R2, #0xC\n"
		"MOV     R1, R4\n"
		"BL      sub_FFAAC800\n"
		"B       loc_FF8B706C\n"

		"loc_FF8B6FF4:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0xB\n"
		"BNE     loc_FF8B703C\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B37A8\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"B       loc_FF8B7068\n"

		"loc_FF8B703C:\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"BL      sub_FF8B37A8\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"

		"loc_FF8B7068:\n"
		"BL      sub_FF8B38E8\n"

		"loc_FF8B706C:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7CEC\n" // LOCATION: ExpDrv.c:268
		"B       loc_FF8B6AA0\n"
		);
}

void __attribute__((naked,noinline)) sub_FF8B44F8_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"LDR     R7, =0x6E30\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x3E\n"
		"BL      sub_FF827B50\n"
		"LDRSH   R0, [R4,#4]\n"
		"MOV     R2, #0\n"
		"MOV     R1, #0\n"
		"BL      sub_FF8B353C\n"
		"MOV     R6, R0\n"
		"LDRSH   R0, [R4,#6]\n"
		"BL      sub_FF8B3648\n"
		"LDRSH   R0, [R4,#8]\n"
		"BL      sub_FF8B36A0\n"
		"LDRSH   R0, [R4,#0xA]\n"
		"BL      sub_FF8B36F8\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"BL      sub_FF8B3750\n"
		"MOV     R5, R0\n"
		"LDR     R0, [R4]\n"
		"LDR     R8, =0x3E144\n"
		"CMP     R0, #0xB\n"
		"MOVEQ   R6, #0\n"
		"MOVEQ   R5, #0\n"
		"BEQ     loc_FF8B4588\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B4588\n"
		"LDRSH   R0, [R4,#4]\n"
		"LDR     R1, =0xFF8B34A8\n"
		"MOV     R2, #2\n"
		"BL      sub_FF92FC20\n" // LOCATION: IrisController.c:117
		"STRH    R0, [R4,#4]\n"
		"MOV     R0, #0\n"
		"STR     R0, [R7,#0x28]\n"
		"B       loc_FF8B4590\n"

		"loc_FF8B4588:\n"
		"LDRH    R0, [R8]\n"
		"STRH    R0, [R4,#4]\n"

		"loc_FF8B4590:\n"
		"CMP     R5, #1\n"
		"LDRNEH  R0, [R8,#8]\n"
		"BNE     loc_FF8B45AC\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"MOV     R2, #0x20\n"
		"LDR     R1, =0xFF8B352C\n"
		"BL      sub_FF8B7D1C\n"

		"loc_FF8B45AC:\n"
		"STRH    R0, [R4,#0xC]\n"
		"LDRSH   R0, [R4,#6]\n"
		//"BL      sub_FF895B48\n" // LOCATION: Shutter.c:0
		"BL      sub_FF895B48_my\n" //------------>
		"LDRSH   R0, [R4,#8]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF896344\n" // LOCATION: ImgGain.c:0
		"MOV     R1, #0\n"
		"ADD     R0, R4, #8\n"
		"BL      sub_FF8963CC\n" // LOCATION: ImgGain.c:0
		"LDRSH   R0, [R4,#0xE]\n"
		"BL      sub_FF8AA464\n" // LOCATION: BrtCrct.c:552
		"LDR     R4, =0xBB8\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B4604\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #2\n"
		"BL      sub_FF827A54\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x532\n"
		"LDRNE   R0, =0xFF8B3BB8\n" // "ExpDrv.c"
		"BLNE    _DebugAssert\n"

		"loc_FF8B4604:\n"
		"CMP     R5, #1\n"
		"LDMNEFD SP!, {R4-R8,PC}\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #0x20\n"
		"BL      sub_FF827A54\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x537\n"
		"LDRNE   R0, =0xFF8B3BB8\n" // "ExpDrv.c"
		"LDMNEFD SP!, {R4-R8,LR}\n"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R8,PC}\n"
		);
}

// FF895B48
void __attribute__((naked,noinline)) sub_FF895B48_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"LDR     R5, =0x68EC\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R5,#4]\n"
		"CMP     R0, #1\n"
		"LDRNE   R1, =0x16D\n"
		"LDRNE   R0, =0xFF8958E0\n" // "Shutter.c"
		"BLNE    _DebugAssert\n"
		"CMN     R4, #0xC00\n"
		"LDREQSH R4, [R5,#2]\n"
		"CMN     R4, #0xC00\n"
		"LDREQ   R1, =0x173\n"
		"LDREQ   R0, =0xFF8958E0\n" // "Shutter.c"
		"STRH    R4, [R5,#2]\n"
		"BLEQ    _DebugAssert\n"
		"MOV     R0, R4\n"
		//"BL      sub_FF9B19C0\n"
		"BL      apex2us\n" // +
		"MOV     R4, R0\n"
		"BL      sub_FF8C5920\n" // nullsub_67
		"MOV     R0, R4\n"
		"BL      sub_FF8C9E10\n"
		"TST     R0, #1\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE   R1, #0x178\n"
		"LDRNE   R0, =0xFF8958E0\n" // "Shutter.c"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
		);
}
