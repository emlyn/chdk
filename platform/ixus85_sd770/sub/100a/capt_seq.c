#include "lolevel.h"
#include "platform.h"
#include "core.h"

// @ FF93B264
static long *nrflag = (long*)0x8DCC;

#include "../../../generic/capt_seq.c"

// Extracted method: task_CaptSeqTask (FF85DE30)
void __attribute__((naked,noinline)) capt_seq_task() // OK
{
	asm volatile (
		"STMFD   SP!, {R3-R9,LR}\n"
		"LDR     R6, =0x19D4C\n"
		"LDR     R5, =0x54B8\n"
		"MOV     R9, #1\n"
		"MOV     R7, #0\n"

		"loc_FF85DE44:\n"
		"LDR     R0, [R5,#0xC]\n"
		"MOV     R2, #0\n"
		"MOV     R1, SP\n"
		"BL      sub_FF827D8C\n" // LOCATION: KerQueue.c:0
		"TST     R0, #1\n"
		"BEQ     loc_FF85DE70\n"
		"LDR     R1, =0x48E\n"
		"LDR     R0, =0xFF85DB08\n" // "SsShootTask.c"
		"BL      _DebugAssert\n"
		"BL      sub_FF81BAA8\n" // ExitTask\n"
		"LDMFD   SP!, {R3-R9,PC}\n"

		"loc_FF85DE70:\n"
		"LDR     R0, [SP,#0x20-0x20]\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x1B\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF85E090\n"

		"loc_FF85DE84:\n"
		"B       loc_FF85DEF4\n"

		"loc_FF85DE88:\n"
		"B       loc_FF85DF5C\n"

		"loc_FF85DE8C:\n"
		"B       loc_FF85DF64\n"

		"loc_FF85DE90:\n"
		"B       loc_FF85DF7C\n"

		"loc_FF85DE94:\n"
		"B       loc_FF85DF70\n"

		"loc_FF85DE98:\n"
		"B       loc_FF85DF84\n"

		"loc_FF85DE9C:\n"
		"B       loc_FF85DF8C\n"

		"loc_FF85DEA0:\n"
		"B       loc_FF85DF94\n"

		"loc_FF85DEA4:\n"
		"B       loc_FF85DFEC\n"

		"loc_FF85DEA8:\n"
		"B       loc_FF85DFF8\n"

		"loc_FF85DEAC:\n"
		"B       loc_FF85E000\n"

		"loc_FF85DEB0:\n"
		"B       loc_FF85E008\n"

		"loc_FF85DEB4:\n"
		"B       loc_FF85E010\n"

		"loc_FF85DEB8:\n"
		"B       loc_FF85E018\n"

		"loc_FF85DEBC:\n"
		"B       loc_FF85E020\n"

		"loc_FF85DEC0:\n"
		"B       loc_FF85E028\n"

		"loc_FF85DEC4:\n"
		"B       loc_FF85E030\n"

		"loc_FF85DEC8:\n"
		"B       loc_FF85E03C\n"

		"loc_FF85DECC:\n"
		"B       loc_FF85E044\n"

		"loc_FF85DED0:\n"
		"B       loc_FF85E04C\n"

		"loc_FF85DED4:\n"
		"B       loc_FF85E054\n"

		"loc_FF85DED8:\n"
		"B       loc_FF85E060\n"

		"loc_FF85DEDC:\n"
		"B       loc_FF85E068\n"

		"loc_FF85DEE0:\n"
		"B       loc_FF85E070\n"

		"loc_FF85DEE4:\n"
		"B       loc_FF85E078\n"

		"loc_FF85DEE8:\n"
		"B       loc_FF85E080\n"

		"loc_FF85DEEC:\n"
		"B       loc_FF85E088\n"

		"loc_FF85DEF0:\n"
		"B       loc_FF85E09C\n"

		"loc_FF85DEF4:\n"
		// jumptable FF85DE7C entry 0
		"BL      sub_FF939B34\n" // LOCATION: SsPrepareSeq.c:0
		"BL      shooting_expo_param_override\n" // +
		"BL      sub_FF85BFB8\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF85E09C\n"
		"BL      sub_FF85D7D8\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF85DF3C\n"
		"MOV     R0, #0xC\n"
		"BL      sub_FF860E80\n"
		"TST     R0, #1\n"
		"STRNE   R9, [R5,#4]\n"
		"LDRNE   R0, [R4,#8]\n"
		"ORRNE   R0, R0, #0x40000000\n"
		"STRNE   R0, [R4,#8]\n"
		"BNE     loc_FF85E09C\n"

		"loc_FF85DF3C:\n"
		"BL      sub_FF95CD34\n"
		"BL      sub_FF86CF6C\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		//"BL      sub_FF93B1EC\n" // LOCATION: SsCaptureSeq.c:536
		"BL      sub_FF93B1EC_my\n" // + 
		"BL      capt_seq_hook_raw_here\n" // +
		"TST     R0, #1\n"
		"STRNE   R9, [R5,#4]\n"
		"B       loc_FF85E09C\n"

		"loc_FF85DF5C:\n" 
		// jumptable FF85DE7C entry 1
		//"BL      sub_FF85E1B4\n"
		"BL      sub_FF85E1B4_my\n" // +
		"B       loc_FF85DF74\n"

		"loc_FF85DF64:\n"
		// jumptable FF85DE7C entry 2
		"MOV     R0, #1\n"
		"BL      sub_FF939CDC\n" // LOCATION: SsPrepareSeq.c:0
		"B       loc_FF85E09C\n"

		"loc_FF85DF70:\n"
		// jumptable FF85DE7C entry 4
		"BL      sub_FF9397CC\n"

		"loc_FF85DF74:\n"
		"STR     R7, [R6,#0x24]\n"
		"B       loc_FF85E09C\n"

		"loc_FF85DF7C:\n"
		// jumptable FF85DE7C entry 3
		"BL      sub_FF939B00\n"
		"B       loc_FF85DF74\n"

		"loc_FF85DF84:\n"
		// jumptable FF85DE7C entry 5
		"BL      sub_FF939B08\n"
		"B       loc_FF85E09C\n"

		"loc_FF85DF8C:\n"
		// jumptable FF85DE7C entry 6
		"BL      sub_FF939BFC\n" // LOCATION: SsPrepareSeq.c:0
		"B       loc_FF85DFF0\n"

		"loc_FF85DF94:\n"
		// jumptable FF85DE7C entry 7
		"LDR     R4, [R0,#0xC]\n"
		"BL      sub_FF939B10\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93A324\n" // LOCATION: SsPrePreSeq.c:2097152
		"TST     R0, #1\n"
		"MOV     R8, R0\n"
		"BNE     loc_FF85DFD4\n"
		"BL      sub_FF86CF6C\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93B104\n" // LOCATION: SsCaptureSeq.c:1
		"MOV     R0, R4\n"
		"BL      sub_FF93B654\n" // LOCATION: SsCaptureSeq.c:4
		"MOV     R8, R0\n"
		"LDR     R0, [R4,#0x14]\n"
		"BL      sub_FF86D178\n" // LOCATION: PropertyCase.c:0

		"loc_FF85DFD4:\n"
		"BL      sub_FF939B00\n"
		"MOV     R2, R4\n"
		"MOV     R1, #9\n"
		"MOV     R0, R8\n"
		"BL      sub_FF85C50C\n" // LOCATION: SsShootCtrl.c:0
		"B       loc_FF85E09C\n" // Corrigido aqui!

		"loc_FF85DFEC:\n"
		// jumptable FF85DE7C entry 8
		"BL      sub_FF939C5C\n" // LOCATION: SsPrepareSeq.c:960

		"loc_FF85DFF0:\n"
		"BL      sub_FF85BFB8\n"
		"B       loc_FF85E09C\n"

		"loc_FF85DFF8:\n"
		// jumptable FF85DE7C entry 9
		"BL      sub_FF939B00\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E000:\n"
		// jumptable FF85DE7C entry 10
		"BL      sub_FF93A590\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E008:\n"
		// jumptable FF85DE7C entry 11
		"BL      sub_FF93A778\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E010:\n"
		// jumptable FF85DE7C entry 12
		"BL      sub_FF93A808\n" // LOCATION: SsExpCompSeq.c:94
		"B       loc_FF85E09C\n"

		"loc_FF85E018:\n"
		// jumptable FF85DE7C entry 13
		"BL      sub_FF93A8BC\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E020:\n"
		// jumptable FF85DE7C entry 14
		"BL      sub_FF93AAB4\n" // LOCATION: SsChgExpSeq.c:32
		"B       loc_FF85E09C\n"

		"loc_FF85E028:\n"
		// jumptable FF85DE7C entry 15
		"BL      sub_FF93AB04\n" // LOCATION: SsChgExpSeq.c:32
		"B       loc_FF85E09C\n"

		"loc_FF85E030:\n"
		// jumptable FF85DE7C entry 16
		"MOV     R0, #0\n"
		"BL      sub_FF93AB88\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E03C:\n"
		// jumptable FF85DE7C entry 17
		"BL      sub_FF93ACD8\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E044:\n"
		// jumptable FF85DE7C entry 18
		"BL      sub_FF93AD6C\n" // LOCATION: SsMFSeq.c:109
		"B       loc_FF85E09C\n"

		"loc_FF85E04C:\n"
		// jumptable FF85DE7C entry 19
		"BL      sub_FF93AE34\n" // LOCATION: SsMFSeq.c:181
		"B       loc_FF85E09C\n"

		"loc_FF85E054:\n"
		// jumptable FF85DE7C entry 20
		"BL      sub_FF939E00\n"
		"BL      sub_FF824C34\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E060:\n"
		// jumptable FF85DE7C entry 21
		"BL      sub_FF93A978\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E068:\n"
		// jumptable FF85DE7C entry 22
		"BL      sub_FF93A9E4\n" // LOCATION: SsChgExpSeq.c:0
		"B       loc_FF85E09C\n"

		"loc_FF85E070:\n"
		// jumptable FF85DE7C entry 23
		"BL      sub_FF93CC18\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E078:\n"
		// jumptable FF85DE7C entry 24
		"BL      sub_FF93CC34\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E080:\n"
		// jumptable FF85DE7C entry 25
		"BL      sub_FF93CC44\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E088:\n"
		// jumptable FF85DE7C entry 26
		"BL      sub_FF93CC70\n"
		"B       loc_FF85E09C\n"

		"loc_FF85E090:\n"
		// jumptable FF85DE7C default entry
		"LDR     R1, =0x58E\n"
		"LDR     R0, =0xFF85DB08\n" // aSsshoottask_c
		"BL      _DebugAssert\n"

		"loc_FF85E09C:\n"
		// jumptable FF85DE7C entry 27
		"LDR     R0, [SP,#0x20-0x20]\n"
		"LDR     R1, [R0,#4]\n"
		"LDR     R0, [R5,#8]\n"
		"BL      sub_FF827B08\n"
		"LDR     R4, [SP,#0x20-0x20]\n"
		"LDR     R0, [R4,#8]\n"
		"CMP     R0, #0\n"
		"LDREQ   R1, =0x10D\n"
		"LDREQ   R0, =0xFF85DB08\n" // aSsshoottask_c
		"BLEQ    _DebugAssert\n"
		"STR     R7, [R4,#8]\n"
		"B       loc_FF85DE44\n"
		);
}

void __attribute__((naked,noinline)) sub_FF85E1B4_my() // OK
{
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"LDR     R4, [R0,#0xC]\n"
		"LDR     R6, =0x19D4C\n"
		"LDR     R0, [R4,#8]\n"
		"MOV     R5, #0\n"
		"ORR     R0, R0, #1\n"
		"STR     R0, [R4,#8]\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"MOVEQ   R0, #2\n"
		"BLEQ    sub_FF858190\n"
		"BL      sub_FF939B10\n"
		"LDR     R0, [R6,#0x24]\n"
		"CMP     R0, #0\n"
		"BNE     loc_FF85E234\n"
		"MOV     R0, R4\n"
		"BL      sub_FF939FA4\n" // LOCATION: SsPrePreSeq.c:242
		"TST     R0, #1\n"
		"MOVNE   R2, R4\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE   R1, #1\n"
		"BNE     sub_FF85C50C\n" // LOCATION: SsShootCtrl.c:0
		"BL      sub_FF95CD34\n"
		"BL      sub_FF86CF6C\n" // LOCATION: PropertyCase.c:0
		"STR     R0, [R4,#0x14]\n"
		"MOV     R0, R4\n"
		"BL      sub_FF93B104\n" // LOCATION: SsCaptureSeq.c:1
		"BL      sub_FF93BBE0\n" // LOCATION: SsShootLib.c:32768
		"MOV     R0, R4\n"
		//"BL      sub_FF93B1EC\n" // LOCATION: SsCaptureSeq.c:536
		"BL      sub_FF93B1EC_my\n" // +
		"MOV     R5, R0\n"
		"BL      capt_seq_hook_raw_here\n" // +
		"B       loc_FF85E244\n"

		"loc_FF85E234:\n"
		"LDR     R0, =0x54B8\n"
		"LDR     R0, [R0,#4]\n"
		"CMP     R0, #0\n"
		"MOVNE   R5, #0x1D\n"

		"loc_FF85E244:\n"
		"BL      sub_FF93CC34\n"
		"BL      sub_FF93CC70\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"MOV     R0, R5\n"
		"BL      sub_FF85C50C\n" // LOCATION: SsShootCtrl.c:0
		"BL      sub_FF93B5F4\n"
		"CMP     R0, #0\n"
		"LDRNE   R0, [R4,#8]\n"
		"ORRNE   R0, R0, #0x2000\n"
		"STRNE   R0, [R4,#8]\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
		);
}

void __attribute__((naked,noinline)) sub_FF93B1EC_my() // OK
{
	asm volatile (
		"STMFD   SP!, {R0-R10,LR}\n"
		"MOV     R6, #0\n"
		"MOV     R4, R0\n"
		"BL      sub_FF93BD58\n" // LOCATION: SsShootEvent.c:60
		"MVN     R1, #0\n"
		"BL      sub_FF827B3C\n"
		"MOV     R2, #4\n"
		"ADD     R1, SP, #0x30-0x28\n"
		"MOV     R0, #0x8A\n"
		"BL      sub_FF86CDDC\n" // PT_GetPropertyCaseString_0
		"TST     R0, #1\n"
		"MOVNE   R1, #0x218\n"
		"LDRNE   R0, =0xFF93B3BC\n" // "SsCaptureSeq.c"
		"BLNE    _DebugAssert\n"
		"LDR     R8, =0x19E00\n"
		"LDR     R5, =0x19D4C\n"
		"LDRSH   R1, [R8,#0xE]\n"
		"LDR     R0, [R5,#0x7C]\n"
		"BL      sub_FF8F17B8\n"
		"BL      sub_FF8450F0\n" // GetCCDTemperature
		"LDR     R2, =0x8DD0\n"
		"ADD     R3, R4, #0x8C\n"
		"STRH    R0, [R4,#0x88]\n"
		"STRD    R2, [SP,#0x30-0x30]\n"
		"MOV     R1, R0\n"
		"LDRH    R0, [R5,#0x54]\n"
		"LDRSH   R2, [R8,#0xC]\n"
		"LDR     R3, =0x8DCC\n"
		"BL      sub_FF93C24C\n" // LOCATION: NRTable.c:202
//PPL NO in 1100		"BL      wait_until_remote_button_is_released\n" // +
		"BL      wait_until_remote_button_is_released\n" // +





		"BL      capt_seq_hook_set_nr\n" // + 
		"BL      sub_FF93B260\n" // Continue in the original FW
		);
}

// Extracted method: task_ExpDrvTask (FF8B478C)
void __attribute__((naked,noinline)) exp_drv_task()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"SUB     SP, SP, #0x20\n"
		"LDR     R8, =0xBB8\n"
		"LDR     R7, =0x6A50\n"
		"LDR     R5, =0x3DEE0\n"
		"MOV     R0, #0\n"
		"ADD     R6, SP, #0x38-0x28\n"
		"STR     R0, [SP,#0x38-0x2C]\n"

		"loc_FF8B47AC:\n"
		"LDR     R0, [R7,#0x20]\n"
		"MOV     R2, #0\n"
		"ADD     R1, SP, #0x38-0x1C\n"
		"BL      sub_FF827D8C\n" // LOCATION: KerQueue.c:0
		"LDR     R0, [SP,#0x38-0x2C]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FF8B47F4\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0x13\n"
		"CMPNE   R0, #0x14\n"
		"CMPNE   R0, #0x15\n"
		"BEQ     loc_FF8B4910\n"
		"CMP     R0, #0x27\n"
		"BEQ     loc_FF8B48E8\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B473C\n" // LOCATION: ExpDrv.c:512

		"loc_FF8B47F4:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x2C\n"
		"BNE     loc_FF8B4824\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B59F8\n" // LOCATION: ExpDrv.c:268
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF827B08\n"
		"BL      sub_FF81BAA8\n" // eventproc_export_ExitTask
		"ADD     SP, SP, #0x20\n"
		"LDMFD   SP!, {R4-R8,PC}\n"

		"loc_FF8B4824:\n"
		"CMP     R1, #0x2B\n"
		"BNE     loc_FF8B4840\n"
		"LDR     R2, [R0,#0x88]!\n"
		"LDR     R1, [R0,#4]\n"
		"MOV     R0, R1\n"
		"BLX     R2\n"
		"B       loc_FF8B4D78\n"

		"loc_FF8B4840:\n"
		"CMP     R1, #0x25\n"
		"BNE     loc_FF8B4890\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827B3C\n"
		"LDR     R0, =0xFF8B11C4\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF92D4BC\n" // LOCATION: IrisController.c:74
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x80\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0xD1B\n"
		"BNE     loc_FF8B48D4\n"

		"loc_FF8B487C:\n"
		"LDR     R1, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R1,#0x8C]\n"
		"LDR     R1, [R1,#0x88]\n"
		"BLX     R1\n"
		"B       loc_FF8B4D78\n"

		"loc_FF8B4890:\n"
		"CMP     R1, #0x26\n"
		"BNE     loc_FF8B48E0\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B473C\n" // LOCATION: ExpDrv.c:512
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827B3C\n"
		"LDR     R0, =0xFF8B11D4\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF92D744\n" // LOCATION: IrisController.c:160
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R8\n"
		"MOV     R1, #0x100\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"BEQ     loc_FF8B487C\n"
		"LDR     R1, =0xD25\n"

		"loc_FF8B48D4:\n"
		"LDR     R0, =0xFF8B18C4\n" // "ExpDrv.c"
		"BL      _DebugAssert\n"
		"B       loc_FF8B487C\n"

		"loc_FF8B48E0:\n"
		"CMP     R1, #0x27\n"
		"BNE     loc_FF8B48F8\n"

		"loc_FF8B48E8:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"ADD     R1, SP, #0x38-0x2C\n"
		"BL      sub_FF8B473C\n" // LOCATION: ExpDrv.c:512
		"B       loc_FF8B487C\n"

		"loc_FF8B48F8:\n"
		"CMP     R1, #0x2A\n"
		"BNE     loc_FF8B4910\n"
		"BL      sub_FF893B08\n" // LOCATION: Shutter.c:2
		"BL      sub_FF8948D4\n" // LOCATION: ImgPixel.c:0
		"BL      sub_FF894358\n" // LOCATION: ImgGain.c:0
		"B       loc_FF8B487C\n"

		"loc_FF8B4910:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R4, #1\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x11\n"
		"CMPNE   R1, #0x12\n"
		"BNE     loc_FF8B4980\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B3250\n" // LOCATION: ExpDrv.c:2
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B5DCC\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x90]\n"
		"LDR     R2, [R0,#0x94]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"B       loc_FF8B4CB8\n"

		"loc_FF8B4980:\n"
		"CMP     R1, #0x13\n"
		"CMPNE   R1, #0x14\n"
		"CMPNE   R1, #0x15\n"
		"BNE     loc_FF8B4A34\n"
		"ADD     R3, SP, #0x38-0x2C\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B3498\n" // LOCATION: ExpDrv.c:0
		"CMP     R0, #1\n"
		"MOV     R4, R0\n"
		"CMPNE   R4, #5\n"
		"BNE     loc_FF8B49D0\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, R4\n"
		"LDR     R1, [R0,#0x7C]!\n"
		"LDR     R12, [R0,#0xC]!\n"
		"LDR     R3, [R0,#4]\n"
		"MOV     R0, SP\n"
		"BLX     R12\n"
		"B       loc_FF8B4A08\n"

		"loc_FF8B49D0:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"CMP     R4, #2\n"
		"LDR     R3, [R0,#0x8C]\n"
		"CMPNE   R4, #6\n"
		"BNE     loc_FF8B4A1C\n"
		"LDR     R12, [R0,#0x88]\n"
		"MOV     R0, SP\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"BLX     R12\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, SP\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FF8B4450\n" // LOCATION: ExpDrv.c:0

		"loc_FF8B4A08:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R2, [SP,#0x38-0x2C]\n"
		"MOV     R1, R4\n"
		"BL      sub_FF8B46DC\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B4CB8\n"

		"loc_FF8B4A1C:\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R12, [R0,#0x88]\n"
		"ADD     R0, R0, #4\n"
		"MOV     R2, R4\n"
		"BLX     R12\n"
		"B       loc_FF8B4CB8\n"

		"loc_FF8B4A34:\n"
		"CMP     R1, #0x21\n"
		"CMPNE   R1, #0x22\n"
		"BNE     loc_FF8B4A80\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R1, R0, R1,LSL#2\n"
		"SUB     R1, R1, #8\n"
		"LDMIA   R1, {R2-R4}\n"
		"STMIA   R6, {R2-R4}\n"
		"BL      sub_FF8B27DC\n" // LOCATION: ExpDrv.c:0
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B2ACC\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B4CB8\n"

		"loc_FF8B4A80:\n"
		"ADD     R1, R0, #4\n"
		"LDMIA   R1, {R2,R3,R12}\n"
		"STMIA   R6, {R2,R3,R12}\n"
		"LDR     R1, [R0]\n"
		"CMP     R1, #0x24\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4A9C:\n"
		"B       loc_FF8B4B30\n"

		"loc_FF8B4AA0:\n"
		"B       loc_FF8B4B30\n"

		"loc_FF8B4AA4:\n"
		"B       loc_FF8B4B80\n"

		"loc_FF8B4AA8:\n"
		"B       loc_FF8B4B88\n"

		"loc_FF8B4AAC:\n"
		"B       loc_FF8B4B88\n"

		"loc_FF8B4AB0:\n"
		"B       loc_FF8B4B88\n"

		"loc_FF8B4AB4:\n"
		"B       loc_FF8B4B30\n"

		"loc_FF8B4AB8:\n"
		"B       loc_FF8B4B80\n"

		"loc_FF8B4ABC:\n"
		"B       loc_FF8B4B88\n"

		"loc_FF8B4AC0:\n"
		"B       loc_FF8B4B88\n"

		"loc_FF8B4AC4:\n"
		"B       loc_FF8B4BA0\n"

		"loc_FF8B4AC8:\n"
		"B       loc_FF8B4BA0\n"

		"loc_FF8B4ACC:\n"
		"B       loc_FF8B4C8C\n"

		"loc_FF8B4AD0:\n"
		"B       loc_FF8B4C94\n"

		"loc_FF8B4AD4:\n"
		"B       loc_FF8B4C94\n"

		"loc_FF8B4AD8:\n"
		"B       loc_FF8B4C94\n"

		"loc_FF8B4ADC:\n"
		"B       loc_FF8B4C94\n"

		"loc_FF8B4AE0:\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4AE4:\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4AE8:\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4AEC:\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4AF0:\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4AF4:\n"
		"B       loc_FF8B4B90\n"

		"loc_FF8B4AF8:\n"
		"B       loc_FF8B4B98\n"

		"loc_FF8B4AFC:\n"
		"B       loc_FF8B4B98\n"

		"loc_FF8B4B00:\n"
		"B       loc_FF8B4BAC\n"

		"loc_FF8B4B04:\n"
		"B       loc_FF8B4BAC\n"

		"loc_FF8B4B08:\n"
		"B       loc_FF8B4BB4\n"

		"loc_FF8B4B0C:\n"
		"B       loc_FF8B4BE4\n"

		"loc_FF8B4B10:\n"
		"B       loc_FF8B4C14\n"

		"loc_FF8B4B14:\n"
		"B       loc_FF8B4C44\n"

		"loc_FF8B4B18:\n"
		"B       loc_FF8B4C74\n"

		"loc_FF8B4B1C:\n"
		"B       loc_FF8B4C74\n"

		"loc_FF8B4B20:\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4B24:\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4B28:\n"
		"B       loc_FF8B4C7C\n"

		"loc_FF8B4B2C:\n"
		"B       loc_FF8B4C84\n"

		"loc_FF8B4B30:\n"
		// jumptable FF8B4A94 entries 0,1,6
		"BL      sub_FF8B16AC\n" // LOCATION: ExpDrv.c:800
		"B       loc_FF8B4C98\n"

		"loc_FF8B4B80:\n"
		// jumptable FF8B4A94 entries 2,7
		"BL      sub_FF8B193C\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B4C98\n"

		"loc_FF8B4B88:\n"
		// jumptable FF8B4A94 entries 3-5,8,9
		"BL      sub_FF8B1B40\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B4C98\n"

		"loc_FF8B4B90:\n"
		// jumptable FF8B4A94 entry 22
		"BL      sub_FF8B1DA8\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B4C98\n"

		"loc_FF8B4B98:\n"
		// jumptable FF8B4A94 entries 23,24
		"BL      sub_FF8B1F9C\n" // LOCATION: ExpDrv.c:11
		"B       loc_FF8B4C98\n"

		"loc_FF8B4BA0:\n"
		// jumptable FF8B4A94 entries 10,11
		//"BL      sub_FF8B2204\n" // LOCATION: ExpDrv.c:2
		"BL      sub_FF8B2204_my\n" //------------>
		"MOV     R4, #0\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4BAC:\n"
		// jumptable FF8B4A94 entries 25,26
		"BL      sub_FF8B2340\n"
		"B       loc_FF8B4C98\n"

		"loc_FF8B4BB4:\n"
		// jumptable FF8B4A94 entry 27
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
		"BL      sub_FF8B5A6C\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B4C98\n"

		"loc_FF8B4BE4:\n"
		// jumptable FF8B4A94 entry 28
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
		"BL      sub_FF8B5BE8\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B4C98\n"

		"loc_FF8B4C14:\n"
		// jumptable FF8B4A94 entry 29
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
		"BL      sub_FF8B5C94\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B4C98\n"

		"loc_FF8B4C44:\n"
		// jumptable FF8B4A94 entry 30
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
		"BL      sub_FF8B5D34\n" // LOCATION: ExpDrv.c:32
		"B       loc_FF8B4C98\n"

		"loc_FF8B4C74:\n"
		// jumptable FF8B4A94 entries 31,32
		"BL      sub_FF8B25B4\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B4C98\n"

		"loc_FF8B4C7C:\n"
		// jumptable FF8B4A94 entry 35
		"BL      sub_FF8B2BD0\n" // LOCATION: ExpDrv.c:10
		"B       loc_FF8B4C98\n"

		"loc_FF8B4C84:\n"
		// jumptable FF8B4A94 entry 36
		"BL      sub_FF8B2E08\n" // LOCATION: ExpDrv.c:0
		"B       loc_FF8B4C98\n"

		"loc_FF8B4C8C:\n"
		// jumptable FF8B4A94 entry 12
		"BL      sub_FF8B2F80\n" // LOCATION: ExpDrv.c:2
		"B       loc_FF8B4C98\n"

		"loc_FF8B4C94:\n"
		// jumptable FF8B4A94 entries 13-16
		"BL      sub_FF8B3118\n" // LOCATION: ExpDrv.c:128

		"loc_FF8B4C98:\n"
		// jumptable FF8B4A94 default entry
		// jumptable FF8B4A94 entries 17-21,33,34
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R1, [R0,#0x7C]\n"
		"LDR     R3, [R0,#0x88]\n"
		"LDR     R2, [R0,#0x8C]\n"
		"ADD     R0, R0, #4\n"
		"BLX     R3\n"
		"CMP     R4, #1\n"
		"BNE     loc_FF8B4D00\n"

		"loc_FF8B4CB8:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"MOV     R2, #0xC\n"
		"LDR     R1, [R0,#0x7C]\n"
		"ADD     R1, R1, R1,LSL#1\n"
		"ADD     R0, R0, R1,LSL#2\n"
		"SUB     R4, R0, #8\n"
		"LDR     R0, =0x3DEE0\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAA6D50\n"
		"LDR     R0, =0x3DEEC\n"
		"MOV     R2, #0xC\n"
		"ADD     R1, SP, #0x38-0x28\n"
		"BL      sub_FFAA6D50\n"
		"LDR     R0, =0x3DEF8\n"
		"MOV     R2, #0xC\n"
		"MOV     R1, R4\n"
		"BL      sub_FFAA6D50\n"
		"B       loc_FF8B4D78\n"

		"loc_FF8B4D00:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"LDR     R0, [R0]\n"
		"CMP     R0, #0xB\n"
		"BNE     loc_FF8B4D48\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"BL      sub_FF8B14B4\n"
		"MOV     R3, #0\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #0\n"
		"B       loc_FF8B4D74\n"

		"loc_FF8B4D48:\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"
		"BL      sub_FF8B14B4\n"
		"MOV     R3, #1\n"
		"MOV     R2, #1\n"
		"MOV     R1, #1\n"
		"MOV     R0, #1\n"
		"STR     R3, [SP,#0x38-0x38]\n"

		"loc_FF8B4D74:\n"
		"BL      sub_FF8B15F4\n"

		"loc_FF8B4D78:\n"
		"LDR     R0, [SP,#0x38-0x1C]\n"
		"BL      sub_FF8B59F8\n" // LOCATION: ExpDrv.c:268
		"B       loc_FF8B47AC\n"
		);
}

void __attribute__((naked,noinline)) sub_FF8B2204_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"LDR     R7, =0x6A50\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R1, #0x3E\n"
		"BL      sub_FF827B3C\n"
		"LDRSH   R0, [R4,#4]\n"
		"MOV     R2, #0\n"
		"MOV     R1, #0\n"
		"BL      sub_FF8B1248\n"
		"MOV     R6, R0\n"
		"LDRSH   R0, [R4,#6]\n"
		"BL      sub_FF8B1354\n"
		"LDRSH   R0, [R4,#8]\n"
		"BL      sub_FF8B13AC\n"
		"LDRSH   R0, [R4,#0xA]\n"
		"BL      sub_FF8B1404\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"BL      sub_FF8B145C\n"
		"MOV     R5, R0\n"
		"LDR     R0, [R4]\n"
		"LDR     R8, =0x3DEF8\n"
		"CMP     R0, #0xB\n"
		"MOVEQ   R6, #0\n"
		"MOVEQ   R5, #0\n"
		"BEQ     loc_FF8B2294\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B2294\n"
		"LDRSH   R0, [R4,#4]\n"
		"LDR     R1, =0xFF8B11B4\n"
		"MOV     R2, #2\n"
		"BL      sub_FF92D610\n" // LOCATION: IrisController.c:117
		"STRH    R0, [R4,#4]\n"
		"MOV     R0, #0\n"
		"STR     R0, [R7,#0x28]\n"
		"B       loc_FF8B229C\n"

		"loc_FF8B2294:\n"
		"LDRH    R0, [R8]\n"
		"STRH    R0, [R4,#4]\n"

		"loc_FF8B229C:\n"
		"CMP     R5, #1\n"
		"LDRNEH  R0, [R8,#8]\n"
		"BNE     loc_FF8B22B8\n"
		"LDRSH   R0, [R4,#0xC]\n"
		"MOV     R2, #0x20\n"
		"LDR     R1, =0xFF8B1238\n"
		"BL      sub_FF8B5A28\n"

		"loc_FF8B22B8:\n"
		"STRH    R0, [R4,#0xC]\n"
		"LDRSH   R0, [R4,#6]\n"
		//"BL      sub_FF893854\n" // LOCATION: Shutter.c:0
		"BL      sub_FF893854_my\n" //------------>
		"LDRSH   R0, [R4,#8]\n"
		"MOV     R1, #1\n"
		"BL      sub_FF894050\n" // LOCATION: ImgGain.c:0
		"MOV     R1, #0\n"
		"ADD     R0, R4, #8\n"
		"BL      sub_FF8940D8\n" // LOCATION: ImgGain.c:0
		"LDRSH   R0, [R4,#0xE]\n"
		"BL      sub_FF8A8170\n" // LOCATION: BrtCrct.c:552
		"LDR     R4, =0xBB8\n"
		"CMP     R6, #1\n"
		"BNE     loc_FF8B2310\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #2\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x532\n"
		"LDRNE   R0, =0xFF8B18C4\n" // "ExpDrv.c"
		"BLNE    _DebugAssert\n"

		"loc_FF8B2310:\n"
		"CMP     R5, #1\n"
		"LDMNEFD SP!, {R4-R8,PC}\n"
		"LDR     R0, [R7,#0x1C]\n"
		"MOV     R2, R4\n"
		"MOV     R1, #0x20\n"
		"BL      sub_FF827A40\n" // LOCATION: KerFlag.c:0
		"TST     R0, #1\n"
		"LDRNE   R1, =0x537\n"
		"LDRNE   R0, =0xFF8B18C4\n" // "ExpDrv.c"
		"LDMNEFD SP!, {R4-R8,LR}\n"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R8,PC}\n"
		);
}

void __attribute__((naked,noinline)) sub_FF893854_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"LDR     R5, =0x650C\n"
		"MOV     R4, R0\n"
		"LDR     R0, [R5,#4]\n"
		"CMP     R0, #1\n"
		"LDRNE   R1, =0x16D\n"
		"LDRNE   R0, =0xFF8935EC\n" // "Shutter.c"
		"BLNE    _DebugAssert\n"
		"CMN     R4, #0xC00\n"
		"LDREQSH R4, [R5,#2]\n"
		"CMN     R4, #0xC00\n"
		"LDREQ   R1, =0x173\n"
		"LDREQ   R0, =0xFF8935EC\n" // "Shutter.c"
		"STRH    R4, [R5,#2]\n"
		"BLEQ    _DebugAssert\n"
		"MOV     R0, R4\n"
		//"BL      sub_FF9AD5A8\n"
		"BL      apex2us\n" // +
		"MOV     R4, R0\n"
		"BL      sub_FF8C32F4\n" // nullsub_67
		"MOV     R0, R4\n"
		"BL      sub_FF8C77E4\n"
		"TST     R0, #1\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE   R1, #0x178\n"
		"LDRNE   R0, =0xFF8935EC\n" // "Shutter.c"
		"BNE     _DebugAssert\n"
		"LDMFD   SP!, {R4-R6,PC}\n"
		);
}


/* exemplo debug
        "STMFD SP!, {R0-R11,LR}\n"
        );
    debug_led(1);
    int c = 500000;
    while (c--) {asm("nop\n nop\n");};
    debug_led(0);
    asm volatile (
        "LDMFD SP!, {R0-R11,LR}\n"
*/

