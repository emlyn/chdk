#include "lolevel.h"
#include "platform.h"
#include "core.h"

// @ FF93DBA8
static long *nrflag = (long*)0x91A4;

#include "../../../generic/capt_seq.c"

// Extracted method: task_CaptSeqTask (FF85E03C)
void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
		"STMFD   SP!, {R3-R9,LR}\n"
		"LDR     R6, =0x19EBC\n"
		"LDR     R5, =0x54E0\n"
		"MOV     R9, #1\n"
		"MOV     R7, #0\n"

		"loc_FF85E050:\n"
		"LDR     R0, [R5,#0xC]\n"
		"MOV     R2, #0\n"
		"MOV     R1, SP\n"
		"BL      sub_FF827D90\n" // LOCATION: KerQueue.c:0
		"TST     R0, #1\n"
		"BEQ     loc_FF85E07C\n"
		"LDR     R1, =0x48E\n"
		"LDR     R0, =0xFF85DD14\n" // "SsShootTask.c"
		"BL      _DebugAssert\n"
		"BL      sub_FF81BAA8\n" // ExitTask\n"
		"LDMFD   SP!, {R3-R9,PC}\n"

		"loc_FF85E07C:\n"
		"LDR     R0, [SP,#0x20-0x20]\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x1B\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF85E29C\n"

		"loc_FF85E090:\n"
		"B       loc_FF85E100\n"

		"loc_FF85E094:\n"
		"B       loc_FF85E168\n"

		"loc_FF85E098:\n"
		"B       loc_FF85E170\n"

		"loc_FF85E09C:\n"
		"B       loc_FF85E188\n"

		"loc_FF85E0A0:\n"
		"B       loc_FF85E17C\n"

		"loc_FF85E0A4:\n"
		"B       loc_FF85E190\n"

		"loc_FF85E0A8:\n"
		"B       loc_FF85E198\n"

		"loc_FF85E0AC:\n"
		"B       loc_FF85E1A0\n"

		"loc_FF85E0B0:\n"
		"B       loc_FF85E1F8\n"

		"loc_FF85E0B4:\n"
		"B       loc_FF85E204\n"

		"loc_FF85E0B8:\n"
		"B       loc_FF85E20C\n"

		"loc_FF85E0BC:\n"
		"B       loc_FF85E214\n"

		"loc_FF85E0C0:\n"
		"B       loc_FF85E21C\n"

		"loc_FF85E0C4:\n"
		"B       loc_FF85E224\n"

		"loc_FF85E0C8:\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E0CC:\n"
		"B       loc_FF85E234\n"

		"loc_FF85E0D0:\n"
		"B       loc_FF85E23C\n"

		"loc_FF85E0D4:\n"
		"B       loc_FF85E248\n"

		"loc_FF85E0D8:\n"
		"B       loc_FF85E250\n"

		"loc_FF85E0DC:\n"
		"B       loc_FF85E258\n"

		"loc_FF85E0E0:\n"
		"B       loc_FF85E260\n"

		"loc_FF85E0E4:\n"
		"B       loc_FF85E26C\n"

		"loc_FF85E0E8:\n"
		"B       loc_FF85E274\n"

		"loc_FF85E0EC:\n"
		"B       loc_FF85E27C\n"

		"loc_FF85E0F0:\n"
		"B       loc_FF85E284\n"

		"loc_FF85E0F4:\n"
		"B       loc_FF85E28C\n"

		"loc_FF85E0F8:\n"
		"B       loc_FF85E294\n"

		"loc_FF85E0FC:\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E100:\n"
		// jumptable FF85E088 entry 0
		"BL      sub_FF93C448\n" // LOCATION: SsPrepareSeq.c:0
		"BL      shooting_expo_param_override\n" // +
		"BL      sub_FF85C1C4\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF85E2A8\n"
		"BL      sub_FF85D9E4\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF85E148\n"
		"MOV     R0, #0xC\n"
		"BL      sub_FF8610AC\n"
		"TST     R0, #1\n"
		"STRNE   R9, [R5,#4]\n"
		"LDRNE   R0, [R4,#8]\n"
		"ORRNE   R0, R0, #0x40000000\n"
		"STRNE   R0, [R4,#8]\n"
		"BNE     loc_FF85E2A8\n"

		"loc_FF85E148:\n"
		"BL      sub_FF95DE08\n"
		"BL      sub_FF86D198\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		//"BL      sub_FF93DB30\n" // LOCATION: SsCaptureSeq.c:536
		"BL      sub_FF93DB30_my\n" // +
		"BL      capt_seq_hook_raw_here\n" // +
		"TST     R0, #1\n"
		"STRNE   R9, [R5,#4]\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E168:\n"
		// jumptable FF85E088 entry 1
		//"BL      sub_FF85E3C0\n"
		"BL      sub_FF85E3C0_my\n" // +
		"B       loc_FF85E180\n"

		"loc_FF85E170:\n"
		// jumptable FF85E088 entry 2
		"MOV     R0, #1\n"
		"BL      sub_FF93C5F0\n" // LOCATION: SsPrepareSeq.c:0
		"B       loc_FF85E2A8\n"

		"loc_FF85E17C:\n"
		// jumptable FF85E088 entry 4
		"BL      sub_FF93C0E0\n"

		"loc_FF85E180:\n"
		"STR     R7, [R6,#0x24]\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E188:\n"
		// jumptable FF85E088 entry 3
		"BL      sub_FF93C414\n"
		"B       loc_FF85E180\n"

		"loc_FF85E190:\n"
		// jumptable FF85E088 entry 5
		"BL      sub_FF93C41C\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E198:\n"
		// jumptable FF85E088 entry 6
		"BL      sub_FF93C510\n" // LOCATION: SsPrepareSeq.c:0
		"B       loc_FF85E1FC\n"

		"loc_FF85E1A0:\n"
		// jumptable FF85E088 entry 7
		"LDR     R4, [R0,#0xC]\n"
		"BL      sub_FF93C424\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93CC38\n" // LOCATION: SsPrePreSeq.c:2097152
		"TST     R0, #1\n"
		"MOV     R8, R0\n"
		"BNE     loc_FF85E1E0\n"
		"BL      sub_FF86D198\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93DA48\n" // LOCATION: SsCaptureSeq.c:1
		"MOV     R0, R4\n"
		"BL      sub_FF93DF9C\n" // LOCATION: SsCaptureSeq.c:4
		"MOV     R8, R0\n"
		"LDR     R0, [R4,#0x14]\n"
		"BL      sub_FF86D3A4\n" // LOCATION: PropertyCase.c:0

		"loc_FF85E1E0:\n"
		"BL      sub_FF93C414\n"
		"MOV     R2, R4\n"
		"MOV     R1, #9\n"
		"MOV     R0, R8\n"
		"BL      sub_FF85C718\n" // LOCATION: SsShootCtrl.c:0
		"B       loc_FF85E2A8\n"

		"loc_FF85E1F8:\n"
		// jumptable FF85E088 entry 8
		"BL      sub_FF93C570\n" // LOCATION: SsPrepareSeq.c:960

		"loc_FF85E1FC:\n"
		"BL      sub_FF85C1C4\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E204:\n"
		// jumptable FF85E088 entry 9
		"BL      sub_FF93C414\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E20C:\n"
		// jumptable FF85E088 entry 10
		"BL      sub_FF93CEA4\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E214:\n"
		// jumptable FF85E088 entry 11
		"BL      sub_FF93D08C\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E21C:\n"
		// jumptable FF85E088 entry 12
		"BL      sub_FF93D11C\n" // LOCATION: SsExpCompSeq.c:94
		"B       loc_FF85E2A8\n"

		"loc_FF85E224:\n"
		// jumptable FF85E088 entry 13
		"BL      sub_FF93D1D0\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E22C:\n"
		// jumptable FF85E088 entry 14
		"BL      sub_FF93D3C8\n" // LOCATION: SsChgExpSeq.c:32
		"B       loc_FF85E2A8\n"

		"loc_FF85E234:\n"
		// jumptable FF85E088 entry 15
		"BL      sub_FF93D418\n" // LOCATION: SsChgExpSeq.c:32
		"B       loc_FF85E2A8\n"

		"loc_FF85E23C:\n"
		// jumptable FF85E088 entry 16
		"MOV     R0, #0\n"
		"BL      sub_FF93D49C\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E248:\n"
		// jumptable FF85E088 entry 17
		"BL      sub_FF93D5EC\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E250:\n"
		// jumptable FF85E088 entry 18
		"BL      sub_FF93D680\n" // LOCATION: SsMFSeq.c:109
		"B       loc_FF85E2A8\n"

		"loc_FF85E258:\n"
		// jumptable FF85E088 entry 19
		"BL      sub_FF93D748\n" // LOCATION: SsMFSeq.c:181
		"B       loc_FF85E2A8\n"

		"loc_FF85E260:\n"
		// jumptable FF85E088 entry 20
		"BL      sub_FF93C714\n"
		"BL      sub_FF824C38\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E26C:\n"
		// jumptable FF85E088 entry 21
		"BL      sub_FF93D28C\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E274:\n"
		// jumptable FF85E088 entry 22
		"BL      sub_FF93D2F8\n" // LOCATION: SsChgExpSeq.c:0
		"B       loc_FF85E2A8\n"

		"loc_FF85E27C:\n"
		// jumptable FF85E088 entry 23
		"BL      sub_FF93F558\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E284:\n"
		// jumptable FF85E088 entry 24
		"BL      sub_FF93F574\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E28C:\n"
		// jumptable FF85E088 entry 25
		"BL      sub_FF93F584\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E294:\n"
		// jumptable FF85E088 entry 26
		"BL      sub_FF93F5B0\n"
		"B       loc_FF85E2A8\n"

		"loc_FF85E29C:\n"
		// jumptable FF85E088 default entry
		"LDR     R1, =0x58E\n"
		"LDR     R0, =0xFF85DD14\n" // aSsshoottask_c
		"BL      _DebugAssert\n"

		"loc_FF85E2A8:\n"
		// jumptable FF85E088 entry 27
		"LDR     R0, [SP,#0x20-0x20]\n"
		"LDR     R1, [R0,#4]\n"
		"LDR     R0, [R5,#8]\n"
		"BL      sub_FF827B0C\n"
		"LDR     R4, [SP,#0x20-0x20]\n"
		"LDR     R0, [R4,#8]\n"
		"CMP     R0, #0\n"
		"LDREQ   R1, =0x10D\n"
		"LDREQ   R0, =0xFF85DD14\n" // aSsshoottask_c
		"BLEQ    _DebugAssert\n"
		"STR     R7, [R4,#8]\n"
		"B       loc_FF85E050\n"
		);
}

void __attribute__((naked,noinline)) sub_FF85E3C0_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"LDR     R4, [R0,#0xC]\n"
		"LDR     R6, =0x19EBC\n"
		"LDR     R0, [R4,#8]\n"
		"MOV     R5, #0\n"
		"ORR     R0, R0, #1\n"
		"STR     R0, [R4,#8]\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"MOVEQ   R0, #2\n"
		"BLEQ    sub_FF858330\n"
		"BL      sub_FF93C424\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BNE     loc_FF85E440\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93C8B8\n" // LOCATION: SsPrePreSeq.c:242
		"TST     R0, #1\n"
		"MOVNE   R2, R4\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE   R1, #1\n"
		"BNE     sub_FF85C718\n" // LOCATION: SsShootCtrl.c:0
		"BL      sub_FF95DE08\n"
		"BL      sub_FF86D198\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93DA48\n" // LOCATION: SsCaptureSeq.c:1
		"BL      sub_FF93E520\n" // LOCATION: SsShootLib.c:32768
		"MOV     R0, R4\n"
		//"BL      sub_FF93DB30\n" // LOCATION: SsCaptureSeq.c:536
		"BL      sub_FF93DB30_my\n" // +
		"MOV     R5, R0\n"
		"BL      capt_seq_hook_raw_here\n" // +
		"B       loc_FF85E450\n"

		"loc_FF85E440:\n"
		"LDR     R0, =0x54E0\n"
		"LDR     R0, [R0,#4]\n"
		"CMP     R0, #0\n"
		"MOVNE   R5, #0x1D\n"

		"loc_FF85E450:\n"
		"BL      sub_FF93F574\n"
		"BL      sub_FF93F5B0\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"MOV     R0, R5\n"
		"BL      sub_FF85C718\n" // LOCATION: SsShootCtrl.c:0
		"BL      sub_FF93DF3C\n"
		"CMP     R0, #0\n"
		"LDRNE   R0, [R4,#8]\n"
		"ORRNE   R0, R0, #0x2000\n"
		"STRNE   R0, [R4,#8]\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
		);
}

void __attribute__((naked,noinline)) sub_FF93DB30_my()
{
	asm volatile (
		"STMFD   SP!, {R0-R10,LR}\n"
		"MOV     R6, #0\n"
		"MOV     R4, R0\n"
		"BL      sub_FF93E698\n" // LOCATION: SsShootEvent.c:60
		"MVN     R1, #0\n"
		"BL      sub_FF827B40\n"
		"MOV     R2, #4\n"
		"ADD     R1, SP, #0x30-0x28\n"
		"MOV     R0, #0x8A\n"
		"BL      sub_FF86D008\n" // PT_GetPropertyCaseString_0
		"TST     R0, #1\n"
		"MOVNE   R1, #0x218\n"
		"LDRNE   R0, =0xFF93DD04\n" // "SsCaptureSeq.c"
		"BLNE    _DebugAssert\n"
		"LDR     R8, =0x19F70\n"
		"LDR     R5, =0x19EBC\n"
		"LDRSH   R1, [R8,#0xE]\n"
		"LDR     R0, [R5,#0x7C]\n"
		"BL      sub_FF8F3B40\n"
		"BL      sub_FF845330\n" // GetCCDTemperature
		"LDR     R2, =0x91A8\n"
		"ADD     R3, R4, #0x8C\n"
		"STRH    R0, [R4,#0x88]\n"
		"STRD    R2, [SP,#0x30-0x30]\n"
		"MOV     R1, R0\n"
		"LDRH    R0, [R5,#0x54]\n"
		"LDRSH   R2, [R8,#0xC]\n"
		"LDR     R3, =0x91A4\n"
		"BL      sub_FF93EB8C\n" // LOCATION: NRTable.c:202
		"BL      wait_until_remote_button_is_released\n" // +
		"BL      capt_seq_hook_set_nr\n" // +
		"BL      sub_FF93DBA4\n" // Continue in the original FW
		);
}

// Extracted method: task_ExpDrvTask (FF8B6864)
void __attribute__((naked,noinline)) exp_drv_task()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"SUB     SP, SP, #0x20\n"
		"LDR     R8, =0xBB8\n"
		"LDR     R7, =0x6E30\n"
		"LDR     R5, =0x3E198\n"
		"MOV     R0, #0\n"
		"ADD     R6, SP, #0x38-0x28\n"
		"STR     R0, [SP,#0x38-0x2C]\n"

		"loc_FF8B6884:\n"
		"LDR     R0, [R7,#0x20]\n"
		"MOV     R2, #0\n"
		"ADD     R1, SP, #0x38-0x1C\n"
		"BL      sub_FF827D90\n" // LOCATION: KerQueue.c:0
		"LDR     R0, [SP,#0x38-0x2C]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FF8B68CC\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0x13\n"
		"CMPNE   R0, #0x14\n"
		"CMPNE   R0, #0x15\n"
		"BEQ     loc_FF8B69E8\n"
		"CMP     R0, #0x27\n"
		"BEQ     loc_FF8B69C0\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B6814\n" // LOCATION: ExpDrv.c:512

		"loc_FF8B68CC:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x2C\n"
		"BNE     loc_FF8B68FC\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7AD0\n" // LOCATION: ExpDrv.c:268
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF827B0C\n"
		"BL      sub_FF81BAA8\n" // eventproc_export_ExitTask
		"ADD     SP, SP, #0x20\n"
		"LDMFD   SP!, {R4-R8,PC}\n"

		"loc_FF8B68FC:\n"
		"CMP     R1, #0x2B\n"
		"BNE     loc_FF8B6918\n"
		"LDR     R2, [R0,#0x88]!\n"
		"LDR     R1, [R0,#4]\n"
		"MOV     R0, R1\n"
		"BLX     R2\n"
		"B       loc_FF8B6E50\n"

		"loc_FF8B6918:\n"
		"CMP     R1, #0x25\n"
		"BNE     loc_FF8B6968\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827B40\n"
		"LDR     R0, =0xFF8B329C\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF92F844\n" // LOCATION: IrisController.c:74
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827A44\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0xD1B\n"
		"BNE     loc_FF8B69AC\n"

		"loc_FF8B6954:\n"
		"LDR     R1, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R1,#0x8C]\n"
		"LDR     R1, [R1,#0x88]\n"
		"BLX     R1\n"
		"B       loc_FF8B6E50\n"

		"loc_FF8B6968:\n"
		"CMP     R1, #0x26\n"
		"BNE     loc_FF8B69B8\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B6814\n" // LOCATION: ExpDrv.c:512
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827B40\n"
		"LDR     R0, =0xFF8B32AC\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF92FACC\n" // LOCATION: IrisController.c:160
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827A44\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"BEQ     loc_FF8B6954\n"
		"LDR     R1, =0xD25\n"

		"loc_FF8B69AC:\n"
		"LDR     R0, =0xFF8B399C\n" // "ExpDrv.c"
		"BL      _DebugAssert\n"
		"B       loc_FF8B6954\n"

		"loc_FF8B69B8:\n"
		"CMP     R1, #0x27\n"
		"BNE     loc_FF8B69D0\n"

		"loc_FF8B69C0:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B6814\n" // LOCATION: ExpDrv.c:512
		"B       loc_FF8B6954\n"

		"loc_FF8B69D0:\n"
		"CMP     R1, #0x2A\n"
		"BNE     loc_FF8B69E8\n"
		"BL      sub_FF895C1C\n" // LOCATION: Shutter.c:2
		"BL      sub_FF8969E8\n" // LOCATION: ImgPixel.c:0
		"BL      sub_FF89646C\n" // LOCATION: ImgGain.c:0
		"B       loc_FF8B6954\n"

		"loc_FF8B69E8:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R4, #1\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x11\n"
		"CMPNE   R1, #0x12\n"
		"BNE     loc_FF8B6A58\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B5328\n" // LOCATION: ExpDrv.c:2
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7EA4\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x90]\n"
		"LDR     R2, [R0,#0x94]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"B       loc_FF8B6D90\n"

		"loc_FF8B6A58:\n"
		"CMP     R1, #0x13\n"
		"CMPNE   R1, #0x14\n"
		"CMPNE   R1, #0x15\n"
		"BNE     loc_FF8B6B0C\n"
		"ADD     R3, SP, #0x38-0x2C\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B5570\n" // LOCATION: ExpDrv.c:0
		"CMP     R0, #1\n"
		"MOV     R4, R0\n"
		"CMPNE   R4, #5\n"
		"BNE     loc_FF8B6AA8\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, R4\n"
		"LDR     R1, [R0,#0x7C]!\n"
		"LDR     R12, [R0,#0xC]!\n"
		"LDR     R3, [R0,#4]\n"
		"MOV     R0, SP\n"
		"BLX     R12\n"
		"B       loc_FF8B6AE0\n"

		"loc_FF8B6AA8:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"CMP     R4, #2\n"
		"LDR     R3, [R0,#0x8C]\n"
		"CMPNE   R4, #6\n"
		"BNE     loc_FF8B6AF4\n"
		"LDR     R12, [R0,#0x88]\n"
		"MOV     R0, SP\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"BLX     R12\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B6528\n" // LOCATION: ExpDrv.c:0

		"loc_FF8B6AE0:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R2, [SP,#0x38-0x2C]\n"
		"MOV     R1, R4\n"
		"BL      sub_FF8B67B4\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6D90\n"

		"loc_FF8B6AF4:\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R12, [R0,#0x88]\n"
		"ADD     R0, R0, #4\n"
		"MOV     R2, R4\n"
		"BLX     R12\n"
		"B       loc_FF8B6D90\n"

		"loc_FF8B6B0C:\n"
		"CMP     R1, #0x21\n"
		"CMPNE   R1, #0x22\n"
		"BNE     loc_FF8B6B58\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B48B4\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B4BA4\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6D90\n"

		"loc_FF8B6B58:\n"
		"ADD     R1, R0, #4\n"
		"LDMIA   R1, {R2,R3,R12}\n"
		"STMIA   R6, {R2,R3,R12}\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x24\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6B74:\n"
		"B       loc_FF8B6C08\n"

		"loc_FF8B6B78:\n"
		"B       loc_FF8B6C08\n"

		"loc_FF8B6B7C:\n"
		"B       loc_FF8B6C58\n"

		"loc_FF8B6B80:\n"
		"B       loc_FF8B6C60\n"

		"loc_FF8B6B84:\n"
		"B       loc_FF8B6C60\n"

		"loc_FF8B6B88:\n"
		"B       loc_FF8B6C60\n"

		"loc_FF8B6B8C:\n"
		"B       loc_FF8B6C08\n"

		"loc_FF8B6B90:\n"
		"B       loc_FF8B6C58\n"

		"loc_FF8B6B94:\n"
		"B       loc_FF8B6C60\n"

		"loc_FF8B6B98:\n"
		"B       loc_FF8B6C60\n"

		"loc_FF8B6B9C:\n"
		"B       loc_FF8B6C78\n"

		"loc_FF8B6BA0:\n"
		"B       loc_FF8B6C78\n"

		"loc_FF8B6BA4:\n"
		"B       loc_FF8B6D64\n"

		"loc_FF8B6BA8:\n"
		"B       loc_FF8B6D6C\n"

		"loc_FF8B6BAC:\n"
		"B       loc_FF8B6D6C\n"

		"loc_FF8B6BB0:\n"
		"B       loc_FF8B6D6C\n"

		"loc_FF8B6BB4:\n"
		"B       loc_FF8B6D6C\n"

		"loc_FF8B6BB8:\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6BBC:\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6BC0:\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6BC4:\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6BC8:\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6BCC:\n"
		"B       loc_FF8B6C68\n"

		"loc_FF8B6BD0:\n"
		"B       loc_FF8B6C70\n"

		"loc_FF8B6BD4:\n"
		"B       loc_FF8B6C70\n"

		"loc_FF8B6BD8:\n"
		"B       loc_FF8B6C84\n"

		"loc_FF8B6BDC:\n"
		"B       loc_FF8B6C84\n"

		"loc_FF8B6BE0:\n"
		"B       loc_FF8B6C8C\n"

		"loc_FF8B6BE4:\n"
		"B       loc_FF8B6CBC\n"

		"loc_FF8B6BE8:\n"
		"B       loc_FF8B6CEC\n"

		"loc_FF8B6BEC:\n"
		"B       loc_FF8B6D1C\n"

		"loc_FF8B6BF0:\n"
		"B       loc_FF8B6D4C\n"

		"loc_FF8B6BF4:\n"
		"B       loc_FF8B6D4C\n"

		"loc_FF8B6BF8:\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6BFC:\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C00:\n"
		"B       loc_FF8B6D54\n"

		"loc_FF8B6C04:\n"
		"B       loc_FF8B6D5C\n"

		"loc_FF8B6C08:\n"
		// jumptable FF8B6B6C entries 0,1,6
		"BL      sub_FF8B3784\n" // LOCATION: ExpDrv.c:800
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C58:\n"
		// jumptable FF8B6B6C entries 2,7
		"BL      sub_FF8B3A14\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C60:\n"
		// jumptable FF8B6B6C entries 3-5,8,9
		"BL      sub_FF8B3C18\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C68:\n"
		// jumptable FF8B6B6C entry 22
		"BL      sub_FF8B3E80\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C70:\n"
		// jumptable FF8B6B6C entries 23,24
		"BL      sub_FF8B4074\n" // LOCATION: ExpDrv.c:11
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C78:\n"
		// jumptable FF8B6B6C entries 10,11
		//"BL      sub_FF8B42DC\n" // LOCATION: ExpDrv.c:2
		"BL      sub_FF8B42DC_my\n" //------------>
		"MOV     R4, #0\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C84:\n"
		// jumptable FF8B6B6C entries 25,26
		"BL      sub_FF8B4418\n"
		"B       loc_FF8B6D70\n"

		"loc_FF8B6C8C:\n"
		// jumptable FF8B6B6C entry 27
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
		"BL      sub_FF8B7B44\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6D70\n"

		"loc_FF8B6CBC:\n"
		// jumptable FF8B6B6C entry 28
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
		"BL      sub_FF8B7CC0\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6D70\n"

		"loc_FF8B6CEC:\n"
		// jumptable FF8B6B6C entry 29
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
		"BL      sub_FF8B7D6C\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6D70\n"

		"loc_FF8B6D1C:\n"
		// jumptable FF8B6B6C entry 30
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
		"BL      sub_FF8B7E0C\n" // LOCATION: ExpDrv.c:32
		"B       loc_FF8B6D70\n"

		"loc_FF8B6D4C:\n"
		// jumptable FF8B6B6C entries 31,32
		"BL      sub_FF8B468C\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6D70\n"

		"loc_FF8B6D54:\n"
		// jumptable FF8B6B6C entry 35
		"BL      sub_FF8B4CA8\n" // LOCATION: ExpDrv.c:10
		"B       loc_FF8B6D70\n"

		"loc_FF8B6D5C:\n"
		// jumptable FF8B6B6C entry 36
		"BL      sub_FF8B4EE0\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6D70\n"

		"loc_FF8B6D64:\n"
		// jumptable FF8B6B6C entry 12
		"BL      sub_FF8B5058\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6D70\n"

		"loc_FF8B6D6C:\n"
		// jumptable FF8B6B6C entries 13-16
		"BL      sub_FF8B51F0\n" // LOCATION: ExpDrv.c:128

		"loc_FF8B6D70:\n"
		// jumptable FF8B6B6C default entry
		// jumptable FF8B6B6C entries 17-21,33,34
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"CMP     R4, #1\n"
		"BNE     loc_FF8B6DD8\n"

		"loc_FF8B6D90:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, #0xC\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R0, R0, R1,LSL#2\n"
		"SUB     R4, R0, #8\n"
		"LDR     R0, =0x3E198\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAAD774\n"
		"LDR     R0, =0x3E1A4\n"
		"MOV     R2, #0xC\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAAD774\n"
		"LDR     R0, =0x3E1B0\n"
		"MOV     R2, #0xC\n"
		"MOV     R1, R4\n"
		"BL      sub_FFAAD774\n"
		"B       loc_FF8B6E50\n"

		"loc_FF8B6DD8:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0xB\n"
		"BNE     loc_FF8B6E20\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B358C\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"B       loc_FF8B6E4C\n"

		"loc_FF8B6E20:\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"BL      sub_FF8B358C\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"

		"loc_FF8B6E4C:\n"
		"BL      sub_FF8B36CC\n"

		"loc_FF8B6E50:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7AD0\n" // LOCATION: ExpDrv.c:268
		"B       loc_FF8B6884\n"
		);
}

void __attribute__((naked,noinline)) sub_FF8B42DC_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"LDR     R7, =0x6E30\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x3E\n"
		"BL      sub_FF827B40\n"
		"LDRSH   R0, [R4,#4]\n"
		"MOV     R2, #0\n"
		"MOV     R1, #0\n"
		"BL      sub_FF8B3320\n"
		"MOV     R6, R0\n"
		"LDRSH   R0, [R4,#6]\n"
		"BL      sub_FF8B342C\n"
		"LDRSH   R0, [R4,#8]\n"
		"BL      sub_FF8B3484\n"
		"LDRSH   R0, [R4,#0xA]\n"
		"BL      sub_FF8B34DC\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"BL      sub_FF8B3534\n"
		"MOV     R5, R0\n"
		"LDR     R0, [R4]\n"
		"LDR     R8, =0x3E1B0\n"
		"CMP     R0, #0xB\n"
		"MOVEQ   R6, #0\n"
		"MOVEQ   R5, #0\n"
		"BEQ     loc_FF8B436C\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B436C\n"
		"LDRSH   R0, [R4,#4]\n"
		"LDR     R1, =0xFF8B328C\n"
		"MOV     R2, #2\n"
		"BL      sub_FF92F998\n" // LOCATION: IrisController.c:117
		"STRH    R0, [R4,#4]\n"
		"MOV     R0, #0\n"
		"STR     R0, [R7,#0x28]\n"
		"B       loc_FF8B4374\n"

		"loc_FF8B436C:\n"
		"LDRH    R0, [R8]\n"
		"STRH    R0, [R4,#4]\n"

		"loc_FF8B4374:\n"
		"CMP     R5, #1\n"
		"LDRNEH  R0, [R8,#8]\n"
		"BNE     loc_FF8B4390\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"MOV     R2, #0x20\n"
		"LDR     R1, =0xFF8B3310\n"
		"BL      sub_FF8B7B00\n"

		"loc_FF8B4390:\n"
		"STRH    R0, [R4,#0xC]\n"
		"LDRSH   R0, [R4,#6]\n"
		//"BL      sub_FF895968\n" // LOCATION: Shutter.c:0
		"BL      sub_FF895968_my\n" //------------>
		"LDRSH   R0, [R4,#8]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF896164\n" // LOCATION: ImgGain.c:0
		"MOV     R1, #0\n"
		"ADD     R0, R4, #8\n"
		"BL      sub_FF8961EC\n" // LOCATION: ImgGain.c:0
		"LDRSH   R0, [R4,#0xE]\n"
		"BL      sub_FF8AA25C\n" // LOCATION: BrtCrct.c:552
		"LDR     R4, =0xBB8\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B43E8\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #2\n"
		"BL      sub_FF827A44\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x532\n"
		"LDRNE   R0, =0xFF8B399C\n" // "ExpDrv.c"
		"BLNE    _DebugAssert\n"

		"loc_FF8B43E8:\n"
		"CMP     R5, #1\n"
		"LDMNEFD SP!, {R4-R8,PC}\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #0x20\n"
		"BL      sub_FF827A44\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x537\n"
		"LDRNE   R0, =0xFF8B399C\n" // "ExpDrv.c"
		"LDMNEFD SP!, {R4-R8,LR}\n"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R8,PC}\n"
		);
}

void __attribute__((naked,noinline)) sub_FF895968_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"LDR     R5, =0x68EC\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R5,#4]\n"
		"CMP     R0, #1\n"
		"LDRNE   R1, =0x16D\n"
		"LDRNE   R0, =0xFF895700\n" // "Shutter.c"
		"BLNE    _DebugAssert\n"
		"CMN     R4, #0xC00\n"
		"LDREQSH R4, [R5,#2]\n"
		"CMN     R4, #0xC00\n"
		"LDREQ   R1, =0x173\n"
		"LDREQ   R0, =0xFF895700\n" // "Shutter.c"
		"STRH    R4, [R5,#2]\n"
		"BLEQ    _DebugAssert\n"
		"MOV     R0, R4\n"
		//"BL      sub_FF9B2824\n"
		"BL      apex2us\n" // +
		"MOV     R4, R0\n"
		"BL      sub_FF8C53CC\n" // nullsub_67
		"MOV     R0, R4\n"
		"BL      sub_FF8C98BC\n"
		"TST     R0, #1\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE   R1, #0x178\n"
		"LDRNE   R0, =0xFF895700\n" // "Shutter.c"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
		);
}
