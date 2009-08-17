#include "lolevel.h"
#include "platform.h"
#include "core.h"

// @ FF93DB18
static long *nrflag = (long*)0x91A4;

#include "../../../generic/capt_seq.c"

// Extracted method: task_CaptSeqTask (FF85DFC0)
void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
		"STMFD   SP!, {R3-R9,LR}\n"
		"LDR     R6, =0x19EBC\n"
		"LDR     R5, =0x54E0\n"
		"MOV     R9, #1\n"
		"MOV     R7, #0\n"

		"loc_FF85DFD4:\n"
		"LDR     R0, [R5,#0xC]\n"
		"MOV     R2, #0\n"
		"MOV     R1, SP\n"
		"BL      sub_FF827D8C\n" // LOCATION: KerQueue.c:0
		"TST     R0, #1\n"
		"BEQ     loc_FF85E000\n"
		"LDR     R1, =0x48E\n"
		"LDR     R0, =0xFF85DC98\n" // "SsShootTask.c"
		"BL      _DebugAssert\n"
		"BL      sub_FF81BAA8\n" // ExitTask\n"
		"LDMFD   SP!, {R3-R9,PC}\n"

		"loc_FF85E000:\n"
		"LDR     R0, [SP,#0x20-0x20]\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x1B\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF85E220\n"

		"loc_FF85E014:\n"
		"B       loc_FF85E084\n"

		"loc_FF85E018:\n"
		"B       loc_FF85E0EC\n"

		"loc_FF85E01C:\n"
		"B       loc_FF85E0F4\n"

		"loc_FF85E020:\n"
		"B       loc_FF85E10C\n"

		"loc_FF85E024:\n"
		"B       loc_FF85E100\n"

		"loc_FF85E028:\n"
		"B       loc_FF85E114\n"

		"loc_FF85E02C:\n"
		"B       loc_FF85E11C\n"

		"loc_FF85E030:\n"
		"B       loc_FF85E124\n"

		"loc_FF85E034:\n"
		"B       loc_FF85E17C\n"

		"loc_FF85E038:\n"
		"B       loc_FF85E188\n"

		"loc_FF85E03C:\n"
		"B       loc_FF85E190\n"

		"loc_FF85E040:\n"
		"B       loc_FF85E198\n"

		"loc_FF85E044:\n"
		"B       loc_FF85E1A0\n"

		"loc_FF85E048:\n"
		"B       loc_FF85E1A8\n"

		"loc_FF85E04C:\n"
		"B       loc_FF85E1B0\n"

		"loc_FF85E050:\n"
		"B       loc_FF85E1B8\n"

		"loc_FF85E054:\n"
		"B       loc_FF85E1C0\n"

		"loc_FF85E058:\n"
		"B       loc_FF85E1CC\n"

		"loc_FF85E05C:\n"
		"B       loc_FF85E1D4\n"

		"loc_FF85E060:\n"
		"B       loc_FF85E1DC\n"

		"loc_FF85E064:\n"
		"B       loc_FF85E1E4\n"

		"loc_FF85E068:\n"
		"B       loc_FF85E1F0\n"

		"loc_FF85E06C:\n"
		"B       loc_FF85E1F8\n"

		"loc_FF85E070:\n"
		"B       loc_FF85E200\n"

		"loc_FF85E074:\n"
		"B       loc_FF85E208\n"

		"loc_FF85E078:\n"
		"B       loc_FF85E210\n"

		"loc_FF85E07C:\n"
		"B       loc_FF85E218\n"

		"loc_FF85E080:\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E084:\n"
		// jumptable FF85E00C entry 0
		"BL      sub_FF93C3B8\n" // LOCATION: SsPrepareSeq.c:0
		"BL      shooting_expo_param_override\n" // +
		"BL      sub_FF85C148\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF85E22C\n"
		"BL      sub_FF85D968\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF85E0CC\n"
		"MOV     R0, #0xC\n"
		"BL      sub_FF861030\n"
		"TST     R0, #1\n"
		"STRNE   R9, [R5,#4]\n"
		"LDRNE   R0, [R4,#8]\n"
		"ORRNE   R0, R0, #0x40000000\n"
		"STRNE   R0, [R4,#8]\n"
		"BNE     loc_FF85E22C\n"

		"loc_FF85E0CC:\n"
		"BL      sub_FF95DD78\n"
		"BL      sub_FF86D11C\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		//"BL      sub_FF93DAA0\n" // LOCATION: SsCaptureSeq.c:536
		"BL      sub_FF93DAA0_my\n" // +
		"BL      capt_seq_hook_raw_here\n" // +
		"TST     R0, #1\n"
		"STRNE   R9, [R5,#4]\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E0EC:\n"
		// jumptable FF85E00C entry 1
		//"BL      sub_FF85E344\n"
		"BL      sub_FF85E344_my\n" // +
		"B       loc_FF85E104\n"

		"loc_FF85E0F4:\n"
		// jumptable FF85E00C entry 2
		"MOV     R0, #1\n"
		"BL      sub_FF93C560\n" // LOCATION: SsPrepareSeq.c:0
		"B       loc_FF85E22C\n"

		"loc_FF85E100:\n"
		// jumptable FF85E00C entry 4
		"BL      sub_FF93C050\n"

		"loc_FF85E104:\n"
		"STR     R7, [R6,#0x24]\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E10C:\n"
		// jumptable FF85E00C entry 3
		"BL      sub_FF93C384\n"
		"B       loc_FF85E104\n"

		"loc_FF85E114:\n"
		// jumptable FF85E00C entry 5
		"BL      sub_FF93C38C\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E11C:\n"
		// jumptable FF85E00C entry 6
		"BL      sub_FF93C480\n" // LOCATION: SsPrepareSeq.c:0
		"B       loc_FF85E180\n"

		"loc_FF85E124:\n"
		// jumptable FF85E00C entry 7
		"LDR     R4, [R0,#0xC]\n"
		"BL      sub_FF93C394\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93CBA8\n" // LOCATION: SsPrePreSeq.c:2097152
		"TST     R0, #1\n"
		"MOV     R8, R0\n"
		"BNE     loc_FF85E164\n"
		"BL      sub_FF86D11C\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93D9B8\n" // LOCATION: SsCaptureSeq.c:1
		"MOV     R0, R4\n"
		"BL      sub_FF93DF0C\n" // LOCATION: SsCaptureSeq.c:4
		"MOV     R8, R0\n"
		"LDR     R0, [R4,#0x14]\n"
		"BL      sub_FF86D328\n" // LOCATION: PropertyCase.c:0

		"loc_FF85E164:\n"
		"BL      sub_FF93C384\n"
		"MOV     R2, R4\n"
		"MOV     R1, #9\n"
		"MOV     R0, R8\n"
		"BL      sub_FF85C69C\n" // LOCATION: SsShootCtrl.c:0
		"B       loc_FF85E22C\n"

		"loc_FF85E17C:\n"
		// jumptable FF85E00C entry 8
		"BL      sub_FF93C4E0\n" // LOCATION: SsPrepareSeq.c:960

		"loc_FF85E180:\n"
		"BL      sub_FF85C148\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E188:\n"
		// jumptable FF85E00C entry 9
		"BL      sub_FF93C384\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E190:\n"
		// jumptable FF85E00C entry 10
		"BL      sub_FF93CE14\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E198:\n"
		// jumptable FF85E00C entry 11
		"BL      sub_FF93CFFC\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E1A0:\n"
		// jumptable FF85E00C entry 12
		"BL      sub_FF93D08C\n" // LOCATION: SsExpCompSeq.c:94
		"B       loc_FF85E22C\n"

		"loc_FF85E1A8:\n"
		// jumptable FF85E00C entry 13
		"BL      sub_FF93D140\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E1B0:\n"
		// jumptable FF85E00C entry 14
		"BL      sub_FF93D338\n" // LOCATION: SsChgExpSeq.c:32
		"B       loc_FF85E22C\n"

		"loc_FF85E1B8:\n"
		// jumptable FF85E00C entry 15
		"BL      sub_FF93D388\n" // LOCATION: SsChgExpSeq.c:32
		"B       loc_FF85E22C\n"

		"loc_FF85E1C0:\n"
		// jumptable FF85E00C entry 16
		"MOV     R0, #0\n"
		"BL      sub_FF93D40C\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E1CC:\n"
		// jumptable FF85E00C entry 17
		"BL      sub_FF93D55C\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E1D4:\n"
		// jumptable FF85E00C entry 18
		"BL      sub_FF93D5F0\n" // LOCATION: SsMFSeq.c:109
		"B       loc_FF85E22C\n"

		"loc_FF85E1DC:\n"
		// jumptable FF85E00C entry 19
		"BL      sub_FF93D6B8\n" // LOCATION: SsMFSeq.c:181
		"B       loc_FF85E22C\n"

		"loc_FF85E1E4:\n"
		// jumptable FF85E00C entry 20
		"BL      sub_FF93C684\n"
		"BL      sub_FF824C38\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E1F0:\n"
		// jumptable FF85E00C entry 21
		"BL      sub_FF93D1FC\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E1F8:\n"
		// jumptable FF85E00C entry 22
		"BL      sub_FF93D268\n" // LOCATION: SsChgExpSeq.c:0
		"B       loc_FF85E22C\n"

		"loc_FF85E200:\n"
		// jumptable FF85E00C entry 23
		"BL      sub_FF93F4C8\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E208:\n"
		// jumptable FF85E00C entry 24
		"BL      sub_FF93F4E4\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E210:\n"
		// jumptable FF85E00C entry 25
		"BL      sub_FF93F4F4\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E218:\n"
		// jumptable FF85E00C entry 26
		"BL      sub_FF93F520\n"
		"B       loc_FF85E22C\n"

		"loc_FF85E220:\n"
		// jumptable FF85E00C default entry
		"LDR     R1, =0x58E\n"
		"LDR     R0, =0xFF85DC98\n" // aSsshoottask_c
		"BL      _DebugAssert\n"

		"loc_FF85E22C:\n"
		// jumptable FF85E00C entry 27
		"LDR     R0, [SP,#0x20-0x20]\n"
		"LDR     R1, [R0,#4]\n"
		"LDR     R0, [R5,#8]\n"
		"BL      sub_FF827B08\n"
		"LDR     R4, [SP,#0x20-0x20]\n"
		"LDR     R0, [R4,#8]\n"
		"CMP     R0, #0\n"
		"LDREQ   R1, =0x10D\n"
		"LDREQ   R0, =0xFF85DC98\n" // aSsshoottask_c
		"BLEQ    _DebugAssert\n"
		"STR     R7, [R4,#8]\n"
		"B       loc_FF85DFD4\n"
		);
}

void __attribute__((naked,noinline)) sub_FF85E344_my()
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
		"BLEQ    sub_FF8582B4\n"
		"BL      sub_FF93C394\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BNE     loc_FF85E3C4\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93C828\n" // LOCATION: SsPrePreSeq.c:242
		"TST     R0, #1\n"
		"MOVNE   R2, R4\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE   R1, #1\n"
		"BNE     sub_FF85C69C\n" // LOCATION: SsShootCtrl.c:0
		"BL      sub_FF95DD78\n"
		"BL      sub_FF86D11C\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93D9B8\n" // LOCATION: SsCaptureSeq.c:1
		"BL      sub_FF93E490\n" // LOCATION: SsShootLib.c:32768
		"MOV     R0, R4\n"
		//"BL      sub_FF93DAA0\n" // LOCATION: SsCaptureSeq.c:536
		"BL      sub_FF93DAA0_my\n" // +
		"MOV     R5, R0\n"
		"BL      capt_seq_hook_raw_here\n" // +
		"B       loc_FF85E3D4\n"

		"loc_FF85E3C4:\n"
		"LDR     R0, =0x54E0\n"
		"LDR     R0, [R0,#4]\n"
		"CMP     R0, #0\n"
		"MOVNE   R5, #0x1D\n"

		"loc_FF85E3D4:\n"
		"BL      sub_FF93F4E4\n"
		"BL      sub_FF93F520\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"MOV     R0, R5\n"
		"BL      sub_FF85C69C\n" // LOCATION: SsShootCtrl.c:0
		"BL      sub_FF93DEAC\n"
		"CMP     R0, #0\n"
		"LDRNE   R0, [R4,#8]\n"
		"ORRNE   R0, R0, #0x2000\n"
		"STRNE   R0, [R4,#8]\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
		);
}

void __attribute__((naked,noinline)) sub_FF93DAA0_my()
{
	asm volatile (
		"STMFD   SP!, {R0-R10,LR}\n"
		"MOV     R6, #0\n"
		"MOV     R4, R0\n"
		"BL      sub_FF93E608\n" // LOCATION: SsShootEvent.c:60
		"MVN     R1, #0\n"
		"BL      sub_FF827B3C\n"
		"MOV     R2, #4\n"
		"ADD     R1, SP, #0x30-0x28\n"
		"MOV     R0, #0x8A\n"
		"BL      sub_FF86CF8C\n" // PT_GetPropertyCaseString_0
		"TST     R0, #1\n"
		"MOVNE   R1, #0x218\n"
		"LDRNE   R0, =0xFF93DC74\n" // "SsCaptureSeq.c"
		"BLNE    _DebugAssert\n"
		"LDR     R8, =0x19F70\n"
		"LDR     R5, =0x19EBC\n"
		"LDRSH   R1, [R8,#0xE]\n"
		"LDR     R0, [R5,#0x7C]\n"
		"BL      sub_FF8F3AC4\n"
		"BL      sub_FF84532C\n" // GetCCDTemperature
		"LDR     R2, =0x91A8\n"
		"ADD     R3, R4, #0x8C\n"
		"STRH    R0, [R4,#0x88]\n"
		"STRD    R2, [SP,#0x30-0x30]\n"
		"MOV     R1, R0\n"
		"LDRH    R0, [R5,#0x54]\n"
		"LDRSH   R2, [R8,#0xC]\n"
		"LDR     R3, =0x91A4\n"
		"BL      sub_FF93EAFC\n" // LOCATION: NRTable.c:202
		"BL      wait_until_remote_button_is_released\n" // +
		"BL      capt_seq_hook_set_nr\n" // +
		"BL      sub_FF93DB14\n" // Continue in the original FW
		);
}

// Extracted method: task_ExpDrvTask (FF8B67E8)
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

		"loc_FF8B6808:\n"
		"LDR     R0, [R7,#0x20]\n"
		"MOV     R2, #0\n"
		"ADD     R1, SP, #0x38-0x1C\n"
		"BL      sub_FF827D8C\n" // LOCATION: KerQueue.c:0
		"LDR     R0, [SP,#0x38-0x2C]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FF8B6850\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0x13\n"
		"CMPNE   R0, #0x14\n"
		"CMPNE   R0, #0x15\n"
		"BEQ     loc_FF8B696C\n"
		"CMP     R0, #0x27\n"
		"BEQ     loc_FF8B6944\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B6798\n" // LOCATION: ExpDrv.c:512

		"loc_FF8B6850:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x2C\n"
		"BNE     loc_FF8B6880\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7A54\n" // LOCATION: ExpDrv.c:268
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF827B08\n"
		"BL      sub_FF81BAA8\n" // eventproc_export_ExitTask
		"ADD     SP, SP, #0x20\n"
		"LDMFD   SP!, {R4-R8,PC}\n"

		"loc_FF8B6880:\n"
		"CMP     R1, #0x2B\n"
		"BNE     loc_FF8B689C\n"
		"LDR     R2, [R0,#0x88]!\n"
		"LDR     R1, [R0,#4]\n"
		"MOV     R0, R1\n"
		"BLX     R2\n"
		"B       loc_FF8B6DD4\n"

		"loc_FF8B689C:\n"
		"CMP     R1, #0x25\n"
		"BNE     loc_FF8B68EC\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827B3C\n"
		"LDR     R0, =0xFF8B3220\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF92F7C8\n" // LOCATION: IrisController.c:74
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0xD1B\n"
		"BNE     loc_FF8B6930\n"

		"loc_FF8B68D8:\n"
		"LDR     R1, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R1,#0x8C]\n"
		"LDR     R1, [R1,#0x88]\n"
		"BLX     R1\n"
		"B       loc_FF8B6DD4\n"

		"loc_FF8B68EC:\n"
		"CMP     R1, #0x26\n"
		"BNE     loc_FF8B693C\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B6798\n" // LOCATION: ExpDrv.c:512
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827B3C\n"
		"LDR     R0, =0xFF8B3230\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF92FA50\n" // LOCATION: IrisController.c:160
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"BEQ     loc_FF8B68D8\n"
		"LDR     R1, =0xD25\n"

		"loc_FF8B6930:\n"
		"LDR     R0, =0xFF8B3920\n" // "ExpDrv.c"
		"BL      _DebugAssert\n"
		"B       loc_FF8B68D8\n"

		"loc_FF8B693C:\n"
		"CMP     R1, #0x27\n"
		"BNE     loc_FF8B6954\n"

		"loc_FF8B6944:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B6798\n" // LOCATION: ExpDrv.c:512
		"B       loc_FF8B68D8\n"

		"loc_FF8B6954:\n"
		"CMP     R1, #0x2A\n"
		"BNE     loc_FF8B696C\n"
		"BL      sub_FF895BA0\n" // LOCATION: Shutter.c:2
		"BL      sub_FF89696C\n" // LOCATION: ImgPixel.c:0
		"BL      sub_FF8963F0\n" // LOCATION: ImgGain.c:0
		"B       loc_FF8B68D8\n"

		"loc_FF8B696C:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R4, #1\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x11\n"
		"CMPNE   R1, #0x12\n"
		"BNE     loc_FF8B69DC\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B52AC\n" // LOCATION: ExpDrv.c:2
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7E28\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x90]\n"
		"LDR     R2, [R0,#0x94]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"B       loc_FF8B6D14\n"

		"loc_FF8B69DC:\n"
		"CMP     R1, #0x13\n"
		"CMPNE   R1, #0x14\n"
		"CMPNE   R1, #0x15\n"
		"BNE     loc_FF8B6A90\n"
		"ADD     R3, SP, #0x38-0x2C\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B54F4\n" // LOCATION: ExpDrv.c:0
		"CMP     R0, #1\n"
		"MOV     R4, R0\n"
		"CMPNE   R4, #5\n"
		"BNE     loc_FF8B6A2C\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, R4\n"
		"LDR     R1, [R0,#0x7C]!\n"
		"LDR     R12, [R0,#0xC]!\n"
		"LDR     R3, [R0,#4]\n"
		"MOV     R0, SP\n"
		"BLX     R12\n"
		"B       loc_FF8B6A64\n"

		"loc_FF8B6A2C:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"CMP     R4, #2\n"
		"LDR     R3, [R0,#0x8C]\n"
		"CMPNE   R4, #6\n"
		"BNE     loc_FF8B6A78\n"
		"LDR     R12, [R0,#0x88]\n"
		"MOV     R0, SP\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"BLX     R12\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B64AC\n" // LOCATION: ExpDrv.c:0

		"loc_FF8B6A64:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R2, [SP,#0x38-0x2C]\n"
		"MOV     R1, R4\n"
		"BL      sub_FF8B6738\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6D14\n"

		"loc_FF8B6A78:\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R12, [R0,#0x88]\n"
		"ADD     R0, R0, #4\n"
		"MOV     R2, R4\n"
		"BLX     R12\n"
		"B       loc_FF8B6D14\n"

		"loc_FF8B6A90:\n"
		"CMP     R1, #0x21\n"
		"CMPNE   R1, #0x22\n"
		"BNE     loc_FF8B6ADC\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B4838\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B4B28\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6D14\n"

		"loc_FF8B6ADC:\n"
		"ADD     R1, R0, #4\n"
		"LDMIA   R1, {R2,R3,R12}\n"
		"STMIA   R6, {R2,R3,R12}\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x24\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6AF8:\n"
		"B       loc_FF8B6B8C\n"

		"loc_FF8B6AFC:\n"
		"B       loc_FF8B6B8C\n"

		"loc_FF8B6B00:\n"
		"B       loc_FF8B6BDC\n"

		"loc_FF8B6B04:\n"
		"B       loc_FF8B6BE4\n"

		"loc_FF8B6B08:\n"
		"B       loc_FF8B6BE4\n"

		"loc_FF8B6B0C:\n"
		"B       loc_FF8B6BE4\n"

		"loc_FF8B6B10:\n"
		"B       loc_FF8B6B8C\n"

		"loc_FF8B6B14:\n"
		"B       loc_FF8B6BDC\n"

		"loc_FF8B6B18:\n"
		"B       loc_FF8B6BE4\n"

		"loc_FF8B6B1C:\n"
		"B       loc_FF8B6BE4\n"

		"loc_FF8B6B20:\n"
		"B       loc_FF8B6BFC\n"

		"loc_FF8B6B24:\n"
		"B       loc_FF8B6BFC\n"

		"loc_FF8B6B28:\n"
		"B       loc_FF8B6CE8\n"

		"loc_FF8B6B2C:\n"
		"B       loc_FF8B6CF0\n"

		"loc_FF8B6B30:\n"
		"B       loc_FF8B6CF0\n"

		"loc_FF8B6B34:\n"
		"B       loc_FF8B6CF0\n"

		"loc_FF8B6B38:\n"
		"B       loc_FF8B6CF0\n"

		"loc_FF8B6B3C:\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6B40:\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6B44:\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6B48:\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6B4C:\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6B50:\n"
		"B       loc_FF8B6BEC\n"

		"loc_FF8B6B54:\n"
		"B       loc_FF8B6BF4\n"

		"loc_FF8B6B58:\n"
		"B       loc_FF8B6BF4\n"

		"loc_FF8B6B5C:\n"
		"B       loc_FF8B6C08\n"

		"loc_FF8B6B60:\n"
		"B       loc_FF8B6C08\n"

		"loc_FF8B6B64:\n"
		"B       loc_FF8B6C10\n"

		"loc_FF8B6B68:\n"
		"B       loc_FF8B6C40\n"

		"loc_FF8B6B6C:\n"
		"B       loc_FF8B6C70\n"

		"loc_FF8B6B70:\n"
		"B       loc_FF8B6CA0\n"

		"loc_FF8B6B74:\n"
		"B       loc_FF8B6CD0\n"

		"loc_FF8B6B78:\n"
		"B       loc_FF8B6CD0\n"

		"loc_FF8B6B7C:\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6B80:\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6B84:\n"
		"B       loc_FF8B6CD8\n"

		"loc_FF8B6B88:\n"
		"B       loc_FF8B6CE0\n"

		"loc_FF8B6B8C:\n"
		// jumptable FF8B6AF0 entries 0,1,6
		"BL      sub_FF8B3708\n" // LOCATION: ExpDrv.c:800
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6BDC:\n"
		// jumptable FF8B6AF0 entries 2,7
		"BL      sub_FF8B3998\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6BE4:\n"
		// jumptable FF8B6AF0 entries 3-5,8,9
		"BL      sub_FF8B3B9C\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6BEC:\n"
		// jumptable FF8B6AF0 entry 22
		"BL      sub_FF8B3E04\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6BF4:\n"
		// jumptable FF8B6AF0 entries 23,24
		"BL      sub_FF8B3FF8\n" // LOCATION: ExpDrv.c:11
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6BFC:\n"
		// jumptable FF8B6AF0 entries 10,11
		//"BL      sub_FF8B4260\n" // LOCATION: ExpDrv.c:2
		"BL      sub_FF8B4260_my\n" //------------>
		"MOV     R4, #0\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6C08:\n"
		// jumptable FF8B6AF0 entries 25,26
		"BL      sub_FF8B439C\n"
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6C10:\n"
		// jumptable FF8B6AF0 entry 27
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
		"BL      sub_FF8B7AC8\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6C40:\n"
		// jumptable FF8B6AF0 entry 28
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
		"BL      sub_FF8B7C44\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6C70:\n"
		// jumptable FF8B6AF0 entry 29
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
		"BL      sub_FF8B7CF0\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6CA0:\n"
		// jumptable FF8B6AF0 entry 30
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
		"BL      sub_FF8B7D90\n" // LOCATION: ExpDrv.c:32
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6CD0:\n"
		// jumptable FF8B6AF0 entries 31,32
		"BL      sub_FF8B4610\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6CD8:\n"
		// jumptable FF8B6AF0 entry 35
		"BL      sub_FF8B4C2C\n" // LOCATION: ExpDrv.c:10
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6CE0:\n"
		// jumptable FF8B6AF0 entry 36
		"BL      sub_FF8B4E64\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6CE8:\n"
		// jumptable FF8B6AF0 entry 12
		"BL      sub_FF8B4FDC\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B6CF4\n"

		"loc_FF8B6CF0:\n"
		// jumptable FF8B6AF0 entries 13-16
		"BL      sub_FF8B5174\n" // LOCATION: ExpDrv.c:128

		"loc_FF8B6CF4:\n"
		// jumptable FF8B6AF0 default entry
		// jumptable FF8B6AF0 entries 17-21,33,34
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"CMP     R4, #1\n"
		"BNE     loc_FF8B6D5C\n"

		"loc_FF8B6D14:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, #0xC\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R0, R0, R1,LSL#2\n"
		"SUB     R4, R0, #8\n"
		"LDR     R0, =0x3E198\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAAD758\n"
		"LDR     R0, =0x3E1A4\n"
		"MOV     R2, #0xC\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAAD758\n"
		"LDR     R0, =0x3E1B0\n"
		"MOV     R2, #0xC\n"
		"MOV     R1, R4\n"
		"BL      sub_FFAAD758\n"
		"B       loc_FF8B6DD4\n"

		"loc_FF8B6D5C:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0xB\n"
		"BNE     loc_FF8B6DA4\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B3510\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"B       loc_FF8B6DD0\n"

		"loc_FF8B6DA4:\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"BL      sub_FF8B3510\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"

		"loc_FF8B6DD0:\n"
		"BL      sub_FF8B3650\n"

		"loc_FF8B6DD4:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B7A54\n" // LOCATION: ExpDrv.c:268
		"B       loc_FF8B6808\n"
		);
}

void __attribute__((naked,noinline)) sub_FF8B4260_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"LDR     R7, =0x6E30\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x3E\n"
		"BL      sub_FF827B3C\n"
		"LDRSH   R0, [R4,#4]\n"
		"MOV     R2, #0\n"
		"MOV     R1, #0\n"
		"BL      sub_FF8B32A4\n"
		"MOV     R6, R0\n"
		"LDRSH   R0, [R4,#6]\n"
		"BL      sub_FF8B33B0\n"
		"LDRSH   R0, [R4,#8]\n"
		"BL      sub_FF8B3408\n"
		"LDRSH   R0, [R4,#0xA]\n"
		"BL      sub_FF8B3460\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"BL      sub_FF8B34B8\n"
		"MOV     R5, R0\n"
		"LDR     R0, [R4]\n"
		"LDR     R8, =0x3E1B0\n"
		"CMP     R0, #0xB\n"
		"MOVEQ   R6, #0\n"
		"MOVEQ   R5, #0\n"
		"BEQ     loc_FF8B42F0\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B42F0\n"
		"LDRSH   R0, [R4,#4]\n"
		"LDR     R1, =0xFF8B3210\n"
		"MOV     R2, #2\n"
		"BL      sub_FF92F91C\n" // LOCATION: IrisController.c:117
		"STRH    R0, [R4,#4]\n"
		"MOV     R0, #0\n"
		"STR     R0, [R7,#0x28]\n"
		"B       loc_FF8B42F8\n"

		"loc_FF8B42F0:\n"
		"LDRH    R0, [R8]\n"
		"STRH    R0, [R4,#4]\n"

		"loc_FF8B42F8:\n"
		"CMP     R5, #1\n"
		"LDRNEH  R0, [R8,#8]\n"
		"BNE     loc_FF8B4314\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"MOV     R2, #0x20\n"
		"LDR     R1, =0xFF8B3294\n"
		"BL      sub_FF8B7A84\n"

		"loc_FF8B4314:\n"
		"STRH    R0, [R4,#0xC]\n"
		"LDRSH   R0, [R4,#6]\n"
		//"BL      sub_FF8958EC\n" // LOCATION: Shutter.c:0
		"BL      sub_FF8958EC_my\n" //------------>
		"LDRSH   R0, [R4,#8]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF8960E8\n" // LOCATION: ImgGain.c:0
		"MOV     R1, #0\n"
		"ADD     R0, R4, #8\n"
		"BL      sub_FF896170\n" // LOCATION: ImgGain.c:0
		"LDRSH   R0, [R4,#0xE]\n"
		"BL      sub_FF8AA1E0\n" // LOCATION: BrtCrct.c:552
		"LDR     R4, =0xBB8\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B436C\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #2\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x532\n"
		"LDRNE   R0, =0xFF8B3920\n" // "ExpDrv.c"
		"BLNE    _DebugAssert\n"

		"loc_FF8B436C:\n"
		"CMP     R5, #1\n"
		"LDMNEFD SP!, {R4-R8,PC}\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #0x20\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x537\n"
		"LDRNE   R0, =0xFF8B3920\n" // "ExpDrv.c"
		"LDMNEFD SP!, {R4-R8,LR}\n"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R8,PC}\n"
		);
}

void __attribute__((naked,noinline)) sub_FF8958EC_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"LDR     R5, =0x68EC\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R5,#4]\n"
		"CMP     R0, #1\n"
		"LDRNE   R1, =0x16D\n"
		"LDRNE   R0, =0xFF895684\n" // "Shutter.c"
		"BLNE    _DebugAssert\n"
		"CMN     R4, #0xC00\n"
		"LDREQSH R4, [R5,#2]\n"
		"CMN     R4, #0xC00\n"
		"LDREQ   R1, =0x173\n"
		"LDREQ   R0, =0xFF895684\n" // "Shutter.c"
		"STRH    R4, [R5,#2]\n"
		"BLEQ    _DebugAssert\n"
		"MOV     R0, R4\n"
		//"BL      sub_FF9B2794\n"
		"BL      apex2us\n" // +
		"MOV     R4, R0\n"
		"BL      sub_FF8C5350\n" // nullsub_67
		"MOV     R0, R4\n"
		"BL      sub_FF8C9840\n"
		"TST     R0, #1\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE   R1, #0x178\n"
		"LDRNE   R0, =0xFF895684\n" // "Shutter.c"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
		);
}