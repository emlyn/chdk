#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0xe7d8; // S95 100h: FFAF96D8

#include "../../../generic/capt_seq.c"


/*----------------------------------------------------------------------
	capt_seq_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
"		STMFD	SP!, {R3-R7,LR} \n"
"		LDR	R7, =0x2E6C \n"
"		LDR	R4, =0x3CFBC \n"
"		MOV	R6, #0 \n"
"loc_FF88323C: \n"
"		LDR	R0, [R7,#4] \n"
"		MOV	R2, #0 \n"
"		MOV	R1, SP \n"
"		BL	sub_FF83A2F8 \n"
"		TST	R0, #1 \n"
"		BEQ	loc_FF883268 \n"
"		LDR	R1, =0x43F \n"
"		LDR	R0, =0xFF882CF4 \n"					// aSsshoottask_c
"		BL	sub_FF81EB78 \n"					// DebugAssert
"		BL	sub_FF81EB30 \n"					// eventproc_export_ExitTask
"		LDMFD	SP!, {R3-R7,PC} \n"
"loc_FF883268: \n"
"		LDR	R0, [SP] \n"
"		LDR	R1, [R0] \n"
"		CMP	R1, #0x23 \n"
"		ADDLS	PC, PC,	R1,LSL#2 \n"
"		B	loc_FF8834A0 \n"
"loc_FF88327C: \n"
"		B	loc_FF88330C \n"
"loc_FF883280: \n"
"		B	loc_FF883324 \n"
"loc_FF883284: \n"
"		B	loc_FF883348 \n"
"loc_FF883288: \n"
"		B	loc_FF88335C \n"
"loc_FF88328C: \n"
"		B	loc_FF883354 \n"
"loc_FF883290: \n"
"		B	loc_FF883368 \n"
"loc_FF883294: \n"
"		B	loc_FF883370 \n"
"loc_FF883298: \n"
"		B	loc_FF883378 \n"
"loc_FF88329C: \n"
"		B	loc_FF883384 \n"
"loc_FF8832A0: \n"
"		B	loc_FF8833AC \n"
"loc_FF8832A4: \n"
"		B	loc_FF883390 \n"
"loc_FF8832A8: \n"
"		B	loc_FF88339C \n"
"loc_FF8832AC: \n"
"		B	loc_FF8833A4 \n"
"loc_FF8832B0: \n"
"		B	loc_FF8833B4 \n"
"loc_FF8832B4: \n"
"		B	loc_FF8833BC \n"
"loc_FF8832B8: \n"
"		B	loc_FF8833C4 \n"
"loc_FF8832BC: \n"
"		B	loc_FF8833CC \n"
"loc_FF8832C0: \n"
"		B	loc_FF8833D4 \n"
"loc_FF8832C4: \n"
"		B	loc_FF8833DC \n"
"loc_FF8832C8: \n"
"		B	loc_FF8833E4 \n"
"loc_FF8832CC: \n"
"		B	loc_FF8833EC \n"
"loc_FF8832D0: \n"
"		B	loc_FF8833F4 \n"
"loc_FF8832D4: \n"
"		B	loc_FF8833FC \n"
"loc_FF8832D8: \n"
"		B	loc_FF883408 \n"
"loc_FF8832DC: \n"
"		B	loc_FF883410 \n"
"loc_FF8832E0: \n"
"		B	loc_FF88341C \n"
"loc_FF8832E4: \n"
"		B	loc_FF883424 \n"
"loc_FF8832E8: \n"
"		B	loc_FF88342C \n"
"loc_FF8832EC: \n"
"		B	loc_FF883434 \n"
"loc_FF8832F0: \n"
"		B	loc_FF88343C \n"
"loc_FF8832F4: \n"
"		B	loc_FF883444 \n"
"loc_FF8832F8: \n"
"		B	loc_FF88344C \n"
"loc_FF8832FC: \n"
"		B	loc_FF883454 \n"
"loc_FF883300: \n"
"		B	loc_FF88345C \n"
"loc_FF883304: \n"
"		B	loc_FF883468 \n"
"loc_FF883308: \n"
"		B	loc_FF8834AC \n"

// jump table entry 0
"loc_FF88330C: \n"
"		BL	sub_FF8839D4 \n"

"		BL	shooting_expo_param_override\n"  		// added

"		BL	sub_FF880B34 \n"

// force call to next function
"		MOV     R0, #0\n"
"		STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press

"		LDR	R0, [R4,#0x24] \n"
"		CMP	R0, #0 \n"
"		BLNE	sub_FF98AEC0 \n"
"		B	loc_FF8834AC \n"

// jump table entry 1
"loc_FF883324: \n"
"		LDRH	R1, [R4] \n"
"		LDR	R0, [R0,#0xC] \n"
"		SUB	R12, R1, #0x4200 \n"
"		SUBS	R12, R12, #0x2E \n"
"		BNE	loc_FF883340 \n"
"		BL	sub_FF98BCA8 \n"
"		B	loc_FF8834AC \n"
"loc_FF883340: \n"

//"		BL	sub_FF98ACEC \n"
"		BL	sub_FF98ACEC_my \n"					// patched

"		B	loc_FF8834AC \n"

// jump table entry 2
"loc_FF883348: \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF883CB8 \n"
"		B	loc_FF8834AC \n"

"loc_FF883354: \n"
"		BL	sub_FF88366C \n"
"		B	loc_FF883360 \n"

"loc_FF88335C: \n"
"		BL	sub_FF8839B4 \n"
"loc_FF883360: \n"
"		STR	R6, [R4,#0x24] \n"
"		B	loc_FF8834AC \n"

"loc_FF883368: \n"
"		BL	sub_FF8839BC \n"
"		B	loc_FF8834AC \n"

"loc_FF883370: \n"
"		BL	sub_FF883BBC \n"
"		B	loc_FF883388 \n"

"loc_FF883378: \n"
"		LDR	R0, [R0,#0xC] \n"
"		BL	sub_FF98AF28 \n"
"		B	loc_FF8834AC \n"

"loc_FF883384: \n"
"		BL	sub_FF883C28 \n"
"loc_FF883388: \n"
"		BL	sub_FF880B34 \n"
"		B	loc_FF8834AC \n"

"loc_FF883390: \n"
"		LDR	R0, [R4,#0x54] \n"
"		BL	sub_FF884614 \n"
"		B	loc_FF8834AC \n"

"loc_FF88339C: \n"
"		BL	sub_FF884968 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833A4: \n"
"		BL	sub_FF8849CC \n"
"		B	loc_FF8834AC \n"

"loc_FF8833AC: \n"
"		BL	sub_FF8839B4 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833B4: \n"
"		BL	sub_FF989FFC \n"
"		B	loc_FF8834AC \n"

"loc_FF8833BC: \n"
"		BL	sub_FF98A208 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833C4: \n"
"		BL	sub_FF98A2A0 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833CC: \n"
"		BL	sub_FF98A38C \n"
"		B	loc_FF8834AC \n"

"loc_FF8833D4: \n"
"		BL	sub_FF98A484 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833DC: \n"
"		MOV	R0, #0 \n"
"		B	loc_FF883400 \n"

"loc_FF8833E4: \n"
"		BL	sub_FF98A6C0 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833EC: \n"
"		BL	sub_FF98A764 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833F4: \n"
"		BL	sub_FF98A844 \n"
"		B	loc_FF8834AC \n"

"loc_FF8833FC: \n"
"		MOV	R0, #1 \n"
"loc_FF883400: \n"
"		BL	sub_FF98A548 \n"
"		B	loc_FF8834AC \n"

"loc_FF883408: \n"
"		BL	sub_FF883EC4 \n"
"		B	loc_FF8834AC \n"

"loc_FF883410: \n"
"		BL	sub_FF883F6C \n"
"		BL	sub_FF98C1D0 \n"
"		B	loc_FF8834AC \n"

"loc_FF88341C: \n"
"		BL	sub_FF884350 \n"
"		B	loc_FF8834AC \n"

"loc_FF883424: \n"
"		BL	sub_FF884490 \n"
"		B	loc_FF8834AC \n"

"loc_FF88342C: \n"
"		BL	sub_FF98C2A0 \n"
"		B	loc_FF8834AC \n"

"loc_FF883434: \n"
"		BL	sub_FF837C6C \n"
"		B	loc_FF8834AC \n"

"loc_FF88343C: \n"
"		BL	sub_FF886FE4 \n"
"		B	loc_FF8834AC \n"

"loc_FF883444: \n"
"		BL	sub_FF887070 \n"
"		B	loc_FF8834AC \n"

"loc_FF88344C: \n"
"		BL	sub_FF98A97C \n"
"		B	loc_FF8834AC \n"

"loc_FF883454: \n"
"		BL	sub_FF98A9E0 \n"
"		B	loc_FF8834AC \n"

"loc_FF88345C: \n"
"		BL	sub_FF8870CC \n"
"		BL	sub_FF88708C \n"
"		B	loc_FF8834AC \n"

"loc_FF883468: \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF98B6D0 \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF98B800 \n"
"		LDRH	R0, [R4,#0x9C] \n"
"		CMP	R0, #4 \n"
"		LDRNEH	R0, [R4] \n"
"		SUBNE	R12, R0, #0x4200 \n"
"		SUBNES	R12, R12, #0x2A \n"
"		BNE	loc_FF8834AC \n"
"		BL	sub_FF887070 \n"
"		BL	sub_FF887670 \n"
"		BL	sub_FF8874EC \n"
"		B	loc_FF8834AC \n"

"loc_FF8834A0: \n"
"		LDR	R1, =0x591 \n"
"		LDR	R0, =0xFF882CF4 \n"				// "SsShootTask.c"
"		BL	sub_FF81EB78 \n"				// DebugAssert

"loc_FF8834AC: \n"
"		LDR	R0, [SP] \n"
"		LDR	R1, [R0,#4] \n"
"		LDR	R0, [R7] \n"
"		BL	sub_FF88E1E4 \n"
"		LDR	R5, [SP] \n"
"		LDR	R0, [R5,#8] \n"
"		CMP	R0, #0 \n"
"		LDREQ	R1, =0x115 \n"
"		LDREQ	R0, =0xFF882CF4 \n"			// "SsShootTask.c"
"		BLEQ	sub_FF81EB78 \n"			// DebugAssert
"		STR	R6, [R5,#8] \n"
"		B	loc_FF88323C \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF98ACEC_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF98ACEC_my()
{
	asm volatile (
"		STMFD	SP!, {R3-R7,LR} \n"
"		LDR	R5, =0x3CFBC \n"
"		MOV	R4, R0 \n"
"		LDR	R0, [R5,#0x24] \n"
"		MOV	R6, #0 \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF98AD28 \n"
"		MOV	R0, #0xC \n"
"		BL	sub_FF889040 \n"
"		TST	R0, #1 \n"
"		MOVNE	R2, R4 \n"
"		LDMNEFD	SP!, {R3-R7,LR} \n"
"		MOVNE	R1, #1 \n"
"		MOVNE	R0, #1 \n"
"		BNE	sub_FF8811F8 \n"
"loc_FF98AD28: \n"
"		LDR	R0, [R4,#8] \n"
"		LDR	R7, =0x420C \n"
"		ORR	R0, R0,	#1 \n"
"		STR	R0, [R4,#8] \n"
"		LDRH	R0, [R5] \n"
"		CMP	R0, R7 \n"
"		BEQ	loc_FF98ADB8 \n"
"		LDRH	R0, [R5,#0x9A] \n"
"		CMP	R0, #3 \n"
"		BEQ	loc_FF98AE00 \n"
"		LDR	R0, [R4,#0xC] \n"
"		CMP	R0, #1 \n"
"		BLS	loc_FF98ADC4 \n"
"		LDRH	R0, [R5,#0x98] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF98AE00 \n"
"		LDRH	R0, [R5,#0x94] \n"
"		CMP	R0, #2 \n"
"		BNE	loc_FF98ADD0 \n"
"		BL	sub_FF88402C \n"
"		LDRH	R0, [R5] \n"
"		CMP	R0, R7 \n"
"		BEQ	loc_FF98ADB8 \n"
"		LDRH	R0, [R5,#0x9A] \n"
"		CMP	R0, #3 \n"
"		BEQ	loc_FF98AE00 \n"
"		LDR	R0, [R4,#0xC] \n"
"		CMP	R0, #1 \n"
"		BLS	loc_FF98ADC4 \n"
"		LDRH	R0, [R5,#0x98] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF98AE00 \n"
"		LDRH	R0, [R5,#0x94] \n"
"		CMP	R0, #2 \n"
"		BEQ	loc_FF98ADFC \n"
"		B	loc_FF98ADD0 \n"
"loc_FF98ADB8: \n"
"		LDRH	R0, [R5,#0x9A] \n"
"		CMP	R0, #3 \n"
"		BEQ	loc_FF98AE00 \n"
"loc_FF98ADC4: \n"
"		LDRH	R0, [R5,#0x98] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF98AE00 \n"
"loc_FF98ADD0: \n"
"		LDRH	R0, [R5,#0x94] \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF98AE00 \n"
"		LDRH	R0, [R5] \n"
"		CMP	R0, R7 \n"
"		LDRNE	R0, [R4,#0xC] \n"
"		CMPNE	R0, #1 \n"
"		BLS	loc_FF98AE00 \n"
"		LDR	R0, [R4,#0x10] \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF98AE00 \n"
"loc_FF98ADFC: \n"
"		BL	sub_FF98C2D8 \n"
"loc_FF98AE00: \n"
"		BL	sub_FF98C2A0 \n"
"		BL	sub_FF8839C4 \n"
"		LDR	R0, [R5,#0x24] \n"
"		CMP	R0, #0 \n"
"		BNE	loc_FF98AE98 \n"
"		MOV	R0, R4 \n"
"		BL	sub_FFAF907C \n"
"		TST	R0, #1 \n"
"		BNE	locret_FF98AEBC \n"
"		MOV	R0, R4 \n"
"		BL	sub_FFAF949C \n"
"		BL	sub_FF98B498 \n"
"		MOV	R6, #1 \n"
"		MOV	R0, #2 \n"
"		BL	sub_FF87EFF8 \n"

"		BL      wait_until_remote_button_is_released \n"	// added
"		BL      capt_seq_hook_set_nr \n"					// added

"		LDRH	R0, [R5] \n"
"		SUB	R12, R0, #0x8200 \n"
"		SUBS	R12, R12, #0x2D \n"
"		BNE	loc_FF98AE88 \n"
"		MOV	R2, #2 \n"
"		ADD	R0, R2,	#0x15C \n"
"		MOV	R1, SP \n"
"		STR	R6, [SP] \n"
"		BL	sub_FF896414 \n"				// PT_GetPropertyCaseString
"		TST	R0, #1 \n"
"		MOVNE	R1, #0xC3 \n"
"		LDRNE	R0, =0xFF8962D0 \n"			// "SsCaptureSeq.c"
"		BLNE	sub_FF81EB78 \n"			// DebugAssert
"		LDRH	R0, [SP] \n"
"		CMP	R0, #1 \n"
"		STRHI	R6, [R4,#0xE4] \n"
"		BHI	loc_FF98AEA8 \n"
"		MOV	R0, #0 \n"
"		STR	R0, [R4,#0xE4] \n"
"loc_FF98AE88: \n"
"		MOV	R0, R4 \n"

// ** the following function captures the image **
"		BL	sub_FFAF9990 \n"

"		BL     capt_seq_hook_raw_here \n"		// added

"		MOV	R6, R0 \n"
"		B	loc_FF98AEAC \n"
"loc_FF98AE98: \n"
"		LDR	R0, =0x7514 \n"
"		LDR	R0, [R0] \n"
"		CMP	R0, #0 \n"
"		BEQ	loc_FF98AEAC \n"
"loc_FF98AEA8: \n"
"		MOV	R6, #0x1D \n"
"loc_FF98AEAC: \n"
"		MOV	R1, R6 \n"
"		MOV	R0, R4 \n"
"		LDMFD	SP!, {R3-R7,LR} \n"
"		B	sub_FFAF9188 \n"
"locret_FF98AEBC: \n"
"		LDMFD	SP!, {R3-R7,PC} \n"
	);
}


/*----------------------------------------------------------------------
	exp_drv_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) exp_drv_task()
{
	asm volatile(
"		STMFD	SP!, {R4-R8,LR} \n"
"		SUB	SP, SP,	#0x20 \n"
"		LDR	R8, =0xBB8 \n"
"		LDR	R7, =0x4888 \n"
"		LDR	R5, =0x59818 \n"
"		MOV	R0, #0 \n"
"		ADD	R6, SP,	#0x10 \n"
"		STR	R0, [SP,#0x0c] \n"

"loc_FF8CF1C8: \n"
"		LDR	R0, [R7,#0x20] \n"
"		MOV	R2, #0 \n"
"		ADD	R1, SP,	#0x1c \n"
"		BL	sub_FF83A2F8 \n"
"		LDR	R0, [SP,#0x0C] \n"
"		CMP	R0, #1 \n"
"		BNE	loc_FF8CF214 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		LDR	R0, [R0] \n"
"		CMP	R0, #0x14 \n"
"		CMPNE	R0, #0x15 \n"
"		CMPNE	R0, #0x16 \n"
"		CMPNE	R0, #0x17 \n"
"		BEQ	loc_FF8CF378 \n"
"		CMP	R0, #0x29 \n"
"		BEQ	loc_FF8CF300 \n"
"		ADD	R1, SP,	#0x0c \n"
"		MOV	R0, #0 \n"
"		BL	sub_FF8CF158 \n"

"loc_FF8CF214: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		LDR	R1, [R0] \n"
"		CMP	R1, #0x2F \n"
"		BNE	loc_FF8CF244 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		BL	sub_FF8D053C \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R1, #1 \n"
"		BL	sub_FF88E1E4 \n"
"		BL	sub_FF81EB30 \n"			// eventproc_export_ExitTask
"		ADD	SP, SP,	#0x20 \n"
"		LDMFD	SP!, {R4-R8,PC} \n"

"loc_FF8CF244: \n"
"		CMP	R1, #0x2E \n"
"		BNE	loc_FF8CF260 \n"
"		LDR	R2, [R0,#0x8C]! \n"
"		LDR	R1, [R0,#4] \n"
"		MOV	R0, R1 \n"
"		BLX	R2 \n"
"		B	loc_FF8CF824 \n"

"loc_FF8CF260: \n"
"		CMP	R1, #0x27 \n"
"		BNE	loc_FF8CF2B0 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R1, #0x80 \n"
"		BL	sub_FF88E218 \n"
"		LDR	R0, =0xFF8CAFB4 \n"
"		MOV	R1, #0x80 \n"
"		BL	sub_FF97D684 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R2, R8 \n"
"		MOV	R1, #0x80 \n"
"		BL	sub_FF88E124 \n"
"		TST	R0, #1 \n"
"		LDRNE	R1, =0x1096 \n"
"		BNE	loc_FF8CF36C \n"

"loc_FF8CF29C: \n"
"		LDR	R1, [SP,#0x1c] \n"
"		LDR	R0, [R1,#0x90] \n"
"		LDR	R1, [R1,#0x8C] \n"
"		BLX	R1 \n"
"		B	loc_FF8CF824 \n"

"loc_FF8CF2B0: \n"
"		CMP	R1, #0x28 \n"
"		BNE	loc_FF8CF2F8 \n"
"		ADD	R1, SP,	#0x0c \n"
"		BL	sub_FF8CF158 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R1, #0x100 \n"
"		BL	sub_FF88E218 \n"
"		LDR	R0, =0xFF8CAFC4 \n"
"		MOV	R1, #0x100 \n"
"		BL	sub_FF97E014 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R2, R8 \n"
"		MOV	R1, #0x100 \n"
"		BL	sub_FF88E124 \n"
"		TST	R0, #1 \n"
"		BEQ	loc_FF8CF29C \n"
"		LDR	R1, =0x10A0 \n"
"		B	loc_FF8CF36C \n"

"loc_FF8CF2F8: \n"
"		CMP	R1, #0x29 \n"
"		BNE	loc_FF8CF310 \n"

"loc_FF8CF300: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		ADD	R1, SP,	#0x0c \n"
"		BL	sub_FF8CF158 \n"
"		B	loc_FF8CF29C \n"

"loc_FF8CF310: \n"
"		CMP	R1, #0x2C \n"
"		BNE	loc_FF8CF328 \n"
"		BL	sub_FF8BD5E0 \n"
"		BL	sub_FF8BE1EC \n"
"		BL	sub_FF8BDD58 \n"
"		B	loc_FF8CF29C \n"

"loc_FF8CF328: \n"
"		CMP	R1, #0x2D \n"
"		BNE	loc_FF8CF378 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R1, #4 \n"
"		BL	sub_FF88E218 \n"
"		LDR	R1, =0xFF8CAFE4 \n"
"		LDR	R0, =0xFFFFF400 \n"
"		MOV	R2, #4 \n"
"		BL	sub_FF8BD05C \n"
"		BL	sub_FF8BD2E4 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R2, R8 \n"
"		MOV	R1, #4 \n"
"		BL	sub_FF88E040 \n"
"		TST	R0, #1 \n"
"		BEQ	loc_FF8CF29C \n"
"		LDR	R1, =0x10C8 \n"

"loc_FF8CF36C: \n"
"		LDR	R0, =0xFF8CB66C	 \n"			// "ExpDrv.c
"		BL	sub_FF81EB78 \n"				// DebugAssert
"		B	loc_FF8CF29C \n"

"loc_FF8CF378: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		MOV	R4, #1 \n"
"		LDR	R1, [R0] \n"
"		CMP	R1, #0x12 \n"
"		CMPNE	R1, #0x13 \n"
"		BNE	loc_FF8CF3E8 \n"
"		LDR	R1, [R0,#0x7C] \n"
"		ADD	R1, R1,	R1,LSL#1 \n"
"		ADD	R1, R0,	R1,LSL#2 \n"
"		SUB	R1, R1,	#8 \n"
"		LDMIA	R1, {R2-R4} \n"
"		STMIA	R6, {R2-R4} \n"
"		BL	sub_FF8CD8C0 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		LDR	R1, [R0,#0x7C] \n"
"		LDR	R3, [R0,#0x8C] \n"
"		LDR	R2, [R0,#0x90] \n"
"		ADD	R0, R0,	#4 \n"
"		BLX	R3 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		BL	sub_FF8D0950 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		LDR	R1, [R0,#0x7C] \n"
"		LDR	R3, [R0,#0x94] \n"
"		LDR	R2, [R0,#0x98] \n"
"		ADD	R0, R0,	#4 \n"
"		BLX	R3 \n"
"		B	loc_FF8CF760 \n"

"loc_FF8CF3E8: \n"
"		CMP	R1, #0x14 \n"
"		CMPNE	R1, #0x15 \n"
"		CMPNE	R1, #0x16 \n"
"		CMPNE	R1, #0x17 \n"
"		BNE	loc_FF8CF4A0 \n"
"		ADD	R3, SP,	#0x0c \n"
"		MOV	R2, SP \n"
"		ADD	R1, SP,	#0x10 \n"
"		BL	sub_FF8CDB2C \n"
"		CMP	R0, #1 \n"
"		MOV	R4, R0 \n"
"		CMPNE	R4, #5 \n"
"		BNE	loc_FF8CF43C \n"
"		LDR	R0, [SP,#0x1c] \n"
"		MOV	R2, R4 \n"
"		LDR	R1, [R0,#0x7C]! \n"
"		LDR	R12, [R0,#0x10]! \n"
"		LDR	R3, [R0,#4] \n"
"		MOV	R0, SP \n"
"		BLX	R12 \n"
"		B	loc_FF8CF474 \n"

"loc_FF8CF43C: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		CMP	R4, #2 \n"
"		LDR	R3, [R0,#0x90] \n"
"		CMPNE	R4, #6 \n"
"		BNE	loc_FF8CF488 \n"
"		LDR	R12, [R0,#0x8C] \n"
"		MOV	R0, SP \n"
"		MOV	R2, R4 \n"
"		MOV	R1, #1 \n"
"		BLX	R12 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		MOV	R2, SP \n"
"		ADD	R1, SP,	#0x10 \n"
"		BL	sub_FF8CEEA4 \n"

"loc_FF8CF474: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		LDR	R2, [SP,#0x0c] \n"
"		MOV	R1, R4 \n"
"		BL	sub_FF8CF0F8 \n"
"		B	loc_FF8CF760 \n"

"loc_FF8CF488: \n"
"		LDR	R1, [R0,#0x7C] \n"
"		LDR	R12, [R0,#0x8C] \n"
"		ADD	R0, R0,	#4 \n"
"		MOV	R2, R4 \n"
"		BLX	R12 \n"
"		B	loc_FF8CF760 \n"

"loc_FF8CF4A0: \n"
"		CMP	R1, #0x23 \n"
"		CMPNE	R1, #0x24 \n"
"		BNE	loc_FF8CF540 \n"
"		LDR	R1, [R0,#0x7C] \n"
"		ADD	R1, R1,	R1,LSL#1 \n"
"		ADD	R1, R0,	R1,LSL#2 \n"
"		SUB	R1, R1,	#8 \n"
"		LDMIA	R1, {R2-R4} \n"
"		STMIA	R6, {R2-R4} \n"
"		BL	sub_FF8CC948 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		LDR	R1, [R0,#0x7C] \n"
"		LDR	R3, [R0,#0x8C] \n"
"		LDR	R2, [R0,#0x90] \n"
"		ADD	R0, R0,	#4 \n"
"		BLX	R3 \n"
"		LDR	R0, [SP,#0x1c] \n"
"		BL	sub_FF8CCD94 \n"
"		B	loc_FF8CF760 \n"

"loc_FF8CF540: \n"
"		ADD	R1, R0,	#4 \n"
"		LDMIA	R1, {R2,R3,R12} \n"
"		STMIA	R6, {R2,R3,R12} \n"
"		LDR	R1, [R0] \n"
"		CMP	R1, #0x26 \n"
"		ADDLS	PC, PC,	R1,LSL#2 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF55C: \n"
"		B	loc_FF8CF5F8 \n"

"loc_FF8CF560: \n"
"		B	loc_FF8CF5F8 \n"

"loc_FF8CF564: \n"
"		B	loc_FF8CF600 \n"

"loc_FF8CF568: \n"
"		B	loc_FF8CF608 \n"

"loc_FF8CF56C: \n"
"		B	loc_FF8CF608 \n"

"loc_FF8CF570: \n"
"		B	loc_FF8CF608 \n"

"loc_FF8CF574: \n"
"		B	loc_FF8CF5F8 \n"

"loc_FF8CF578: \n"
"		B	loc_FF8CF600 \n"

"loc_FF8CF57C: \n"
"		B	loc_FF8CF608 \n"

"loc_FF8CF580: \n"
"		B	loc_FF8CF608 \n"

"loc_FF8CF584: \n"
"		B	loc_FF8CF620 \n"

"loc_FF8CF588: \n"
"		B	loc_FF8CF620 \n"

"loc_FF8CF58C: \n"
"		B	loc_FF8CF72C \n"

"loc_FF8CF590: \n"
"		B	loc_FF8CF734 \n"

"loc_FF8CF594: \n"
"		B	loc_FF8CF734 \n"

"loc_FF8CF598: \n"
"		B	loc_FF8CF734 \n"

"loc_FF8CF59C: \n"
"		B	loc_FF8CF734 \n"

"loc_FF8CF5A0: \n"
"		B	loc_FF8CF73C \n"

"loc_FF8CF5A4: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5A8: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5AC: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5B0: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5B4: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5B8: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5BC: \n"
"		B	loc_FF8CF610 \n"

"loc_FF8CF5C0: \n"
"		B	loc_FF8CF618 \n"

"loc_FF8CF5C4: \n"
"		B	loc_FF8CF618 \n"

"loc_FF8CF5C8: \n"
"		B	loc_FF8CF62C \n"

"loc_FF8CF5CC: \n"
"		B	loc_FF8CF62C \n"

"loc_FF8CF5D0: \n"
"		B	loc_FF8CF634 \n"

"loc_FF8CF5D4: \n"
"		B	loc_FF8CF66C \n"

"loc_FF8CF5D8: \n"
"		B	loc_FF8CF6A4 \n"

"loc_FF8CF5DC: \n"
"		B	loc_FF8CF6DC \n"

"loc_FF8CF5E0: \n"
"		B	loc_FF8CF714 \n"

"loc_FF8CF5E4: \n"
"		B	loc_FF8CF714 \n"

"loc_FF8CF5E8: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5EC: \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF5F0: \n"
"		B	loc_FF8CF71C \n"

"loc_FF8CF5F4: \n"
"		B	loc_FF8CF724 \n"

"loc_FF8CF5F8: \n"
// jumptable FF8CF554 entries 0,1,6
"		BL	sub_FF8CB4F4 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF600: \n"
// jumptable FF8CF554 entries 2,7
"		BL	sub_FF8CB790 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF608: \n"
// jumptable FF8CF554 entries 3-5,8,9
"		BL	sub_FF8CB9B8 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF610: \n"
// jumptable FF8CF554 entry 24
"		BL	sub_FF8CBC90 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF618: \n"
// jumptable FF8CF554 entries 25,26
"		BL	sub_FF8CBEA8 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF620: \n"
// jumptable FF8CF554 entries 10,11

//"		BL	sub_FF8CC1CC \n"
"		BL	sub_FF8CC1CC_my \n"				// patched

"		MOV	R4, #0 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF62C: \n"
// jumptable FF8CF554 entries 27,28
"		BL	sub_FF8CC314 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF634: \n"
// jumptable FF8CF554 entry 29
"		LDRH	R1, [R0,#4] \n"
"		STRH	R1, [SP,#0x10] \n"
"		LDRH	R1, [R5,#2] \n"
"		STRH	R1, [SP,#0x12] \n"
"		LDRH	R1, [R5,#4] \n"
"		STRH	R1, [SP,#0x14] \n"
"		LDRH	R1, [R5,#6] \n"
"		STRH	R1, [SP,#0x16] \n"
"		LDRH	R1, [R0,#0xC] \n"
"		STRH	R1, [SP,#0x18] \n"
"		LDRH	R1, [R5,#0xA] \n"
"		STRH	R1, [SP,#0x1a] \n"
"		BL	sub_FF8D0648 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF66C: \n"
// jumptable FF8CF554 entry 30
"		LDRH	R1, [R0,#4] \n"
"		STRH	R1, [SP,#0x10] \n"
"		LDRH	R1, [R5,#2] \n"
"		STRH	R1, [SP,#0x12] \n"
"		LDRH	R1, [R5,#4] \n"
"		STRH	R1, [SP,#0x14] \n"
"		LDRH	R1, [R5,#6] \n"
"		STRH	R1, [SP,#0x16] \n"
"		LDRH	R1, [R5,#8] \n"
"		STRH	R1, [SP,#0x18] \n"
"		LDRH	R1, [R5,#0xA] \n"
"		STRH	R1, [SP,#0x1a] \n"
"		BL	sub_FF8D0750 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF6A4: \n"
// jumptable FF8CF554 entry 31
"		LDRH	R1, [R5] \n"
"		STRH	R1, [SP,#0x10] \n"
"		LDRH	R1, [R0,#6] \n"
"		STRH	R1, [SP,#0x12] \n"
"		LDRH	R1, [R5,#4] \n"
"		STRH	R1, [SP,#0x14] \n"
"		LDRH	R1, [R5,#6] \n"
"		STRH	R1, [SP,#0x16] \n"
"		LDRH	R1, [R5,#8] \n"
"		STRH	R1, [SP,#0x18] \n"
"		LDRH	R1, [R5,#0xA] \n"
"		STRH	R1, [SP,#0x1a] \n"
"		BL	sub_FF8D0804 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF6DC: \n"
// jumptable FF8CF554 entry 32
"		LDRH	R1, [R5] \n"
"		STRH	R1, [SP,#0x10] \n"
"		LDRH	R1, [R5,#2] \n"
"		STRH	R1, [SP,#0x12] \n"
"		LDRH	R1, [R5,#4] \n"
"		STRH	R1, [SP,#0x14] \n"
"		LDRH	R1, [R5,#6] \n"
"		STRH	R1, [SP,#0x16] \n"
"		LDRH	R1, [R0,#0xC] \n"
"		STRH	R1, [SP,#0x18] \n"
"		LDRH	R1, [R5,#0xA] \n"
"		STRH	R1, [SP,#0x1a] \n"
"		BL	sub_FF8D08AC \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF714: \n"
// jumptable FF8CF554 entries 33,34
"		BL	sub_FF8CC720 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF71C: \n"
// jumptable FF8CF554 entry 37
"		BL	sub_FF8CCE98 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF724: \n"
// jumptable FF8CF554 entry 38
"		BL	sub_FF8CD134 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF72C: \n"
// jumptable FF8CF554 entry 12
"		BL	sub_FF8CD314 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF734: \n"
// jumptable FF8CF554 entries 13-16
"		BL	sub_FF8CD548 \n"
"		B	loc_FF8CF740 \n"

"loc_FF8CF73C: \n"
// jumptable FF8CF554 entry 17
"		BL	sub_FF8CD6B8 \n"

"loc_FF8CF740: \n"
// jumptable FF8CF554 default entry
// jumptable FF8CF554 entries 18-23,35,36
"		LDR	R0, [SP,#0x1c] \n"
"		LDR	R1, [R0,#0x7C] \n"
"		LDR	R3, [R0,#0x8C] \n"
"		LDR	R2, [R0,#0x90] \n"
"		ADD	R0, R0,	#4 \n"
"		BLX	R3 \n"
"		CMP	R4, #1 \n"
"		BNE	loc_FF8CF7A8 \n"

"loc_FF8CF760: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		MOV	R2, #0xC \n"
"		LDR	R1, [R0,#0x7C] \n"
"		ADD	R1, R1,	R1,LSL#1 \n"
"		ADD	R0, R0,	R1,LSL#2 \n"
"		SUB	R4, R0,	#8 \n"
"		LDR	R0, =0x59818 \n"
"		ADD	R1, SP,	#0x10 \n"
"		BL	sub_FFB9F0D4 \n"
"		LDR	R0, =0x59824 \n"
"		MOV	R2, #0xC \n"
"		ADD	R1, SP,	#0x10 \n"
"		BL	sub_FFB9F0D4 \n"
"		LDR	R0, =0x59830 \n"
"		MOV	R2, #0xC \n"
"		MOV	R1, R4 \n"
"		BL	sub_FFB9F0D4 \n"
"		B	loc_FF8CF824 \n"

"loc_FF8CF7A8: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		MOV	R3, #1 \n"
"		LDR	R0, [R0] \n"
"		CMP	R0, #0xB \n"
"		BNE	loc_FF8CF7F0 \n"
"		MOV	R2, #0 \n"
"		STRD	R2, [SP] \n"
"		MOV	R2, #1 \n"
"		MOV	R1, #1 \n"
"		MOV	R0, #0 \n"
"		BL	sub_FF8CB2D4 \n"
"		MOV	R3, #1 \n"
"		MOV	R2, #0 \n"
"		STRD	R2, [SP] \n"
"		MOV	R2, #1 \n"
"		MOV	R1, #1 \n"
"		MOV	R0, #0 \n"
"		B	loc_FF8CF820 \n"

"loc_FF8CF7F0: \n"
"		MOV	R2, #1 \n"
"		STRD	R2, [SP] \n"
"		MOV	R3, #1 \n"
"		MOV	R1, #1 \n"
"		MOV	R0, #1 \n"
"		BL	sub_FF8CB2D4 \n"
"		MOV	R3, #1 \n"
"		MOV	R2, #1 \n"
"		MOV	R1, #1 \n"
"		MOV	R0, #1 \n"
"		STR	R3, [SP] \n"
"		STR	R3, [SP,#0x04] \n"

"loc_FF8CF820: \n"
"		BL	sub_FF8CB43C \n"

"loc_FF8CF824: \n"
"		LDR	R0, [SP,#0x1c] \n"
"		BL	sub_FF8D053C \n"
"		B	loc_FF8CF1C8 \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF8CC1CC_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF8CC1CC_my()
{
	asm volatile (
"		STMFD	SP!, {R4-R8,LR} \n"
"		LDR	R7, =0x4888 \n"
"		MOV	R4, R0 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R1, #0x3E \n"
"		BL	sub_FF88E218 \n"
"		LDRSH	R0, [R4,#4] \n"
"		MOV	R2, #0 \n"
"		MOV	R1, #0 \n"
"		BL	sub_FF8CB038 \n"
"		MOV	R5, R0 \n"
"		LDRSH	R0, [R4,#6] \n"
"		BL	sub_FF8CB148 \n"
"		LDRSH	R0, [R4,#8] \n"
"		BL	sub_FF8CB1A0 \n"
"		LDRSH	R0, [R4,#0xA] \n"
"		BL	sub_FF8CB1F8 \n"
"		LDRSH	R0, [R4,#0xC] \n"
"		MOV	R1, #0 \n"
"		BL	sub_FF8CB250 \n"
"		MOV	R6, R0 \n"
"		LDRSH	R0, [R4,#0xE] \n"
"		BL	sub_FF8D05E8 \n"
"		LDR	R0, [R4] \n"
"		LDR	R8, =0x59830 \n"
"		CMP	R0, #0xB \n"
"		MOVEQ	R5, #0 \n"
"		MOVEQ	R6, #0 \n"
"		BEQ	loc_FF8CC268 \n"
"		CMP	R5, #1 \n"
"		BNE	loc_FF8CC268 \n"
"		LDRSH	R0, [R4,#4] \n"
"		LDR	R1, =0xFF8CAFA4 \n"
"		MOV	R2, #2 \n"
"		BL	sub_FF97D9D0 \n"
"		STRH	R0, [R4,#4] \n"
"		MOV	R0, #0 \n"
"		STR	R0, [R7,#0x28] \n"
"		B	loc_FF8CC270 \n"

"loc_FF8CC268: \n"
"		LDRH	R0, [R8] \n"
"		STRH	R0, [R4,#4] \n"

"loc_FF8CC270: \n"
"		CMP	R6, #1 \n"
"		LDRNEH	R0, [R8,#8] \n"
"		BNE	loc_FF8CC28C \n"
"		LDRSH	R0, [R4,#0xC] \n"
"		LDR	R1, =0xFF8CB028 \n"
"		MOV	R2, #0x20 \n"
"		BL	sub_FF8D0604 \n"

"loc_FF8CC28C: \n"
"		STRH	R0, [R4,#0xC] \n"
"		LDRSH	R0, [R4,#6] \n"

//"		BL	sub_FF8BD350 \n"
"		BL	sub_FF8BD350_my \n"				// patched

"		LDRSH	R0, [R4,#8] \n"
"		MOV	R1, #1 \n"
"		BL	sub_FF8BDAA0 \n"
"		MOV	R1, #0 \n"
"		ADD	R0, R4,	#8 \n"
"		BL	sub_FF8BDB28 \n"
"		LDRSH	R0, [R4,#0xE] \n"
"		BL	sub_FF8C5F98 \n"
"		LDR	R4, =0xBB8 \n"
"		CMP	R5, #1 \n"
"		BNE	loc_FF8CC2E4 \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R2, R4 \n"
"		MOV	R1, #2 \n"
"		BL	sub_FF88E124 \n"
"		TST	R0, #1 \n"
"		LDRNE	R1, =0x61E \n"
"		LDRNE	R0, =0xFF8CB66C \n"		// "ExpDrv.c"
"		BLNE	sub_FF81EB78 \n"		// DebugAssert

"loc_FF8CC2E4: \n"
"		CMP	R6, #1 \n"
"		LDMNEFD	SP!, {R4-R8,PC} \n"
"		LDR	R0, [R7,#0x1C] \n"
"		MOV	R2, R4 \n"
"		MOV	R1, #0x20 \n"
"		BL	sub_FF88E124 \n"
"		TST	R0, #1 \n"
"		LDRNE	R1, =0x623 \n"
"		LDRNE	R0, =0xFF8CB66C \n"		// "ExpDrv.c"
"		LDMNEFD	SP!, {R4-R8,LR} \n"
"		BNE	sub_FF81EB78 \n"			// DebugAssert
"		LDMFD	SP!, {R4-R8,PC} \n"
	);
}


/*----------------------------------------------------------------------
	sub_FF8BD350_my()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF8BD350_my() {
	asm volatile (
"		STMFD	SP!, {R4-R6,LR} \n"
"		LDR	R5, =0x456C \n"
"		MOV	R4, R0 \n"
"		LDR	R0, [R5,#4] \n"
"		CMP	R0, #1 \n"
"		LDRNE	R1, =0x146 \n"
"		LDRNE	R0, =0xFF8BD154 \n"		// "Shutter.c"
"		BLNE	sub_FF81EB78 \n"		// DebugAssert
"		CMN	R4, #0xC00 \n"
"		LDREQSH	R4, [R5,#2] \n"
"		CMN	R4, #0xC00 \n"
"		MOVEQ	R1, #0x14C \n"
"		LDREQ	R0, =0xFF8BD154 \n"		// "Shutter.c"
"		STRH	R4, [R5,#2] \n"
"		BLEQ	sub_FF81EB78 \n"		// DebugAssert
"		MOV	R0, R4 \n"

//"		BL	sub_FFA50D94 \n"
"		BL      apex2us \n"				// patched

"		MOV	R4, R0 \n"
"		BL	sub_FF90988C \n"			// nullsub_203
"		MOV	R0, R4 \n"
"		BL	sub_FF9162BC \n"
"		TST	R0, #1 \n"
"		LDRNE	R1, =0x151 \n"
"		LDMNEFD	SP!, {R4-R6,LR} \n"
"		LDRNE	R0, =0xFF8BD154 \n"		// "Shutter.c"
"		BNE	sub_FF81EB78 \n"			// DebugAssert
"		LDMFD	SP!, {R4-R6,PC} \n"
	);
}

