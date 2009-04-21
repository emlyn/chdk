
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

//JS
//found at 0xFFD1B5D0
static long *nrflag = (long*)0x8C64;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) capt_seq_task() {
 asm volatile (
			"STMFD 	SP!, {R3-R7,LR}\n"
			"LDR 	R6, =0x5368\n"
				
		"loc_FFC503B8:\n"		
			"LDR 	R0, [R6,#0x10]\n"
			"MOV 	R2, #0\n"
			"MOV 	R1, SP\n"
			"BL 	sub_FFC16FF0\n"
			"TST 	R0, #1\n"
			"BEQ 	loc_FFC503E4\n"
			"LDR 	R1, =0x539\n"
			"LDR 	R0, =0xFFC4FC88\n"
			"BL 	sub_FFC0BD98\n"			//DebugAssert
			"BL 	sub_ffc0bb50 \n"		//eventproc_export_ExitTask
			"LDMFD 	SP!, {R3-R7,PC}\n"
				
		"loc_FFC503E4:\n"		
			"LDR 	R0, [SP,#0x18-0x18]\n"
			"LDR 	R1, [R0]\n"
			"CMP 	R1, #0x22\n"
			"ADDLS 	PC, PC, R1,LSL#2\n"
			"B 	loc_FFC505EC\n"
				
		"loc_FFC503F8:\n"		
			"B 	loc_FFC50484\n"
				
		"loc_FFC503FC:\n"		
			"B 	loc_FFC5048C\n"
				
		"loc_FFC50400:\n"		
			"B 	loc_FFC50494\n"
				
		"loc_FFC50404:\n"		
			"B 	loc_FFC504A8\n"
				
		"loc_FFC50408:\n"		
			"B 	loc_FFC504A0\n"
				
		"loc_FFC5040C:\n"		
			"B 	loc_FFC504B0\n"
				
		"loc_FFC50410:\n"		
			"B 	loc_FFC504B8\n"
				
		"loc_FFC50414:\n"		
			"B 	loc_FFC504C4\n"
				
		"loc_FFC50418:\n"		
			"B 	loc_FFC5051C\n"
				
		"loc_FFC5041C:\n"		
			"B 	loc_FFC504A8\n"
				
		"loc_FFC50420:\n"		
			"B 	loc_FFC50524\n"
				
		"loc_FFC50424:\n"		
			"B 	loc_FFC50534\n"
				
		"loc_FFC50428:\n"		
			"B 	loc_FFC5053C\n"
				
		"loc_FFC5042C:\n"		
			"B 	loc_FFC50544\n"
				
		"loc_FFC50430:\n"		
			"B 	loc_FFC5054C\n"
				
		"loc_FFC50434:\n"		
			"B 	loc_FFC50554\n"
				
		"loc_FFC50438:\n"		
			"B 	loc_FFC5055C\n"
				
		"loc_FFC5043C:\n"		
			"B 	loc_FFC50564\n"
				
		"loc_FFC50440:\n"		
			"B 	loc_FFC5056C\n"
				
		"loc_FFC50444:\n"		
			"B 	loc_FFC50574\n"
				
		"loc_FFC50448:\n"		
			"B 	loc_FFC5057C\n"
				
		"loc_FFC5044C:\n"		
			"B 	loc_FFC50584\n"
				
		"loc_FFC50450:\n"		
			"B 	loc_FFC5058C\n"
				
		"loc_FFC50454:\n"		
			"B 	loc_FFC50594\n"
				
		"loc_FFC50458:\n"		
			"B 	loc_FFC505A0\n"
				
		"loc_FFC5045C:\n"		
			"B 	loc_FFC505A8\n"
				
		"loc_FFC50460:\n"		
			"B 	loc_FFC505B4\n"
				
		"loc_FFC50464:\n"		
			"B 	loc_FFC505BC\n"
				
		"loc_FFC50468:\n"		
			"B 	loc_FFC505C4\n"
				
		"loc_FFC5046C:\n"		
			"B 	loc_FFC505CC\n"
				
		"loc_FFC50470:\n"		
			"B 	loc_FFC505D4\n"
				
		"loc_FFC50474:\n"		
			"B 	loc_FFC505DC\n"
				
		"loc_FFC50478:\n"		
			"B 	loc_FFC505E4\n"
				
		"loc_FFC5047C:\n"		
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50480:\n"		
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50484:\n"		
				
			"BL 	sub_FFC50C44\n"
			"B 	loc_FFC504BC\n"
				
		"loc_FFC5048C:\n"		
				
			"BL 	sub_FFC4FD38_my\n"		//-------> changed
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50494:\n"		
				
			"MOV 	R0, #1\n"
			"BL 	sub_FFC50DE0\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC504A0:\n"		
				
			"BL 	sub_FFC50928\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC504A8:\n"		
				
			"BL 	sub_FFC50C24\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC504B0:\n"		
				
			"BL 	sub_FFC50C2C\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC504B8:\n"		
				
			"BL 	sub_FFC50D00\n"
				
		"loc_FFC504BC:\n"		
				
			"BL 	sub_FFC4E33C\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC504C4:\n"		
				
			"LDR 	R4, [R0,#0xC]\n"
			"BL 	sub_FFC50C34\n"
			"MOV 	R0, R4\n"
			"BL 	sub_FFD1A490\n"
			"TST 	R0, #1\n"
			"MOV 	R5, R0\n"
			"BNE 	loc_FFC50504\n"
			"BL 	sub_FFC5F430\n"
			"STR 	R0, [R4,#0x18]\n"
			"MOV 	R0, R4\n"
			"BL 	sub_FFD1B498\n"
			"MOV 	R0, R4\n"
			"BL 	sub_FFD1BA7C\n"
			"MOV 	R5, R0\n"
			"LDR 	R0, [R4,#0x18]\n"
			"BL 	sub_FFC5F644\n"
				
		"loc_FFC50504:\n"		
			"BL 	sub_FFC50C24\n"
			"MOV 	R2, R4\n"
			"MOV 	R1, #9\n"
			"MOV 	R0, R5\n"
			"BL 	sub_FFC4E718\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC5051C:\n"		
				
			"BL 	sub_FFC50D60\n"
			"B 	loc_FFC504BC\n"
				
		"loc_FFC50524:\n"		
				
			"LDR 	R0, =0x1940C\n"
			"LDR 	R0, [R0,#0x4C]\n"
			"BL 	sub_FFC5130C\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50534:\n"		
				
			"BL 	sub_FFC515B4\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC5053C:\n"		
				
			"BL 	sub_FFC51640\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50544:\n"		
				
			"BL 	sub_FFD1A6B4\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC5054C:\n"		
				
			"BL 	sub_FFD1A89C\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50554:\n"		
				
			"BL 	sub_FFD1A92C\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC5055C:\n"		
				
			"BL 	sub_FFD1A9D4\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50564:\n"		
				
			"BL 	sub_FFD1ABF4\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC5056C:\n"		
				
			"BL 	sub_FFD1AC44\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50574:\n"		
				
			"MOV 	R0, #0\n"
			"B 	loc_FFC50598\n"
				
		"loc_FFC5057C:\n"		
				
			"BL 	sub_FFD1AE00\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50584:\n"		
				
			"BL 	sub_FFD1AE94\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC5058C:\n"		
				
			"BL 	sub_FFD1AF58\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC50594:\n"		
				
			"MOV 	R0, #1\n"
				
		"loc_FFC50598:\n"		
			"BL 	sub_FFD1ACC0\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505A0:\n"		
				
			"BL 	sub_FFC50FA8\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505A8:\n"		
				
			"BL 	sub_FFC50FD4\n"
			"BL 	sub_FFC50724\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505B4:\n"		
				
			"BL 	sub_FFD1AAF0\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505BC:\n"		
				
			"BL 	sub_FFD1AB84\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505C4:\n"		
				
			"BL 	sub_FFC4FC18\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505CC:\n"		
				
			"BL 	sub_FFC141F0\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505D4:\n"		
				
			"BL 	sub_FFC52C80\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505DC:\n"		
				
			"BL 	sub_FFC52C9C\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505E4:\n"		
				
			"BL 	sub_FFC52CAC\n"
			"B 	loc_FFC505F8\n"
				
		"loc_FFC505EC:\n"		
				
			"LDR 	R1, =0x65E\n"
			"LDR 	R0, =0xFFC4FC88 \n"
			"BL 	sub_FFC0BD98\n"			//DebugAssert
				
		"loc_FFC505F8:\n"		
				
			"LDR 	R0, [SP,#0x18-0x18]\n"
			"LDR 	R1, [R0,#4]\n"
			"LDR 	R0, [R6,#0xC]\n"
			"BL 	sub_FFC16D60\n"
			"LDR 	R4, [SP,#0x18-0x18]\n"
			"LDR 	R0, [R4,#8]\n"
			"CMP 	R0, #0\n"
			"LDREQ 	R1, =0x11D\n"
			"LDREQ 	R0, =0xFFC4FC88\n"
			"BLEQ 	sub_FFC0BD98\n"			//DebugAssert
			"MOV 	R0, #0\n"
			"STR 	R0, [R4,#8]\n"
			"B 	loc_FFC503B8\n"
 );
} 
//JSE


void __attribute__((naked,noinline)) sub_FFC4FD38_my(){ // 
 asm volatile(
 			"STMFD 	SP!, {R3-R7,LR}\n"
			"LDR 	R4, [R0,#0xC]\n"
			"LDR 	R5, =0x1940C\n"
			"LDR 	R0, [R4,#8]\n"
			"ORR 	R0, R0, #1\n"
			"STR 	R0, [R4,#8]\n"
			"LDRH 	R0, [R5,#0x8A]\n"
			"CMP 	R0, #3\n"
			"BEQ 	loc_FFC4FE08\n"
			"LDR 	R0, [R4,#0xC]\n"
			"CMP 	R0, #1\n"
			"BLS 	loc_FFC4FDB8\n"
			"LDRH 	R0, [R5,#0x88]\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFC4FE08\n"
			"LDRH 	R0, [R5,#0x84]\n"
			"CMP 	R0, #2\n"
			"BNE 	loc_FFC4FDC4\n"
			"BL 	sub_FFC51094\n"
			"LDRH 	R0, [R5,#0x8A]\n"
			"CMP 	R0, #3\n"
			"BEQ 	loc_FFC4FE08\n"
			"LDR 	R0, [R4,#0xC]\n"
			"CMP 	R0, #1\n"
			"BLS 	loc_FFC4FDB8\n"
			"LDRH 	R0, [R5,#0x88]\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFC4FE08\n"
			"LDRH 	R0, [R5,#0x84]\n"
			"CMP 	R0, #2\n"
			"BEQ 	loc_FFC4FDE8\n"
			"B 	loc_FFC4FDC4\n"
				
		"loc_FFC4FDB8:\n"		
				
			"LDRH 	R0, [R5,#0x88]\n"
			"CMP 	R0, #0\n"
			"BNE 	loc_FFC4FE08\n"
				
		"loc_FFC4FDC4:\n"		
				
			"LDRH 	R0, [R5,#0x84]\n"
			"CMP 	R0, #1\n"
			"BNE 	loc_FFC4FE08\n"
			"LDR 	R0, [R4,#0xC]\n"
			"CMP 	R0, #1\n"
			"BLS 	loc_FFC4FE08\n"
			"LDR 	R0, [R4,#0x10]\n"
			"CMP 	R0, #1\n"
			"BNE 	loc_FFC4FE08\n"
				
		"loc_FFC4FDE8:\n"		
			"LDR 	R3, =0x24D\n"
			"LDR 	R0, =0x5368\n"
			"STR 	R3, [SP,#0x18-0x18]\n"
			"LDR 	R0, [R0,#0xC]\n"
			"LDR 	R2, =0xEA60\n"
			"LDR 	R3, =0xFFC4FC88 \n"
			"MOV 	R1, #0x40000000\n"
			"BL 	sub_FFC5454C\n"
				
		"loc_FFC4FE08:\n"		
				
			"BL 	sub_FFC4FC18\n"
			"MOV 	R0, #2\n"
			"BL 	sub_FFC4B0D8\n"
			"BL 	sub_FFC50C34\n"
			"MOV 	R0, R4\n"
			"BL 	sub_FFC50F1C\n"
			"MOV 	R0, R4\n"
			"BL 	sub_FFD1A098\n"
			"CMP 	R0, #0\n"
			"MOV 	R0, R4\n"
			"BEQ 	loc_FFC4FE50\n"
			"BL 	sub_FFD1A1B0\n"
			"TST 	R0, #1\n"
			"MOVNE 	R2, R4\n"
			"LDMNEFD 	SP!, {R3-R7,LR}\n"
			"MOVNE 	R1, #1\n"
			"BNE 	sub_FFC4E718\n"
			"B 	loc_FFC4FE54\n"
				
		"loc_FFC4FE50:\n"		
			"BL 	sub_FFD1A120\n"
				
		"loc_FFC4FE54:\n"		
			"MOV 	R0, #0\n"
			"STR 	R0, [SP,#0x18-0x18]\n"
			"LDRH 	R0, [R5,#0x8A]\n"
			"MOV 	R2, #2\n"
			"MOV 	R1, SP\n"
			"CMP 	R0, #3\n"
			"LDRNE 	R0, [R4,#0xC]\n"
			"CMPNE 	R0, #1\n"
			"MOVHI 	R0, #1\n"
			"STRHI 	R0, [SP,#0x18-0x18]\n"
			"LDR 	R0, =0x123\n"
			"BL 	sub_FFC5F198  \n"		//PT_GetPropertyCaseString
			"BL 	sub_FFD38E3C\n"
			"BL 	sub_FFC5F430\n"
			"STR 	R0, [R4,#0x18]\n"
			"MOV 	R0, R4\n"
			"BL 	sub_FFD1B498\n"
			"BL 	sub_FFD1C114\n"
			"MOV 	R0, R4\n"
			"BL 	sub_FFD1B560_my\n"	//---------------> changed
			"BL		capt_seq_hook_raw_here\n"  //	----------> added
			"MOV 	R6, R0\n"
			"BL 	sub_FFC52C9C\n"
			"BL 	sub_FFC52CD8\n"
			"MOV 	R2, R4\n"
			"MOV 	R1, #1\n"
			"MOV 	R0, R6\n"
			"BL 	sub_FFC4E718\n"
			"BL 	sub_FFD1BA0C\n"
			"CMP 	R0, #0\n"
			"LDRNE 	R0, [R4,#8]\n"
			"ORRNE 	R0, R0, #0x2000\n"
			"STRNE 	R0, [R4,#8]\n"
			"LDRH 	R0, [R5,#0x8A]\n"
			"CMP 	R0, #3\n"
			"BEQ 	locret_FFC4FEFC\n"
			"LDRH 	R0, [R5,#0x88]\n"
			"CMP 	R0, #0\n"
			"LDREQH 	R0, [R5,#0x84]\n"
			"CMPEQ 	R0, #2\n"
			"MOVEQ 	R0, R4\n"
			"LDMEQFD 	SP!, {R3-R7,LR}\n"
			"BEQ 	sub_FFC510E8\n"
				
		"locret_FFC4FEFC:\n"		
			"LDMFD 	SP!, {R3-R7,PC}\n"
 );
}



void __attribute__((naked,noinline)) sub_FFD1B560_my(){ // 
 asm volatile(
		"STMFD 	SP!, {R1-R9,LR}\n"
		"MOV 	R4, R0\n"
		"BL 	sub_FFD1C274\n"
		"MOV 	R1, #0xFFFFFFFF\n"
		"BL 	sub_FFC16D94\n"
		"MOV 	R2, #4\n"
		"ADD 	R1, SP, #0x28-0x24\n"
		"MOV 	R0, #0x8A\n"
		"BL 	sub_FFC5F2A0 \n"			//PT_GetPropertyCaseString_0
		"TST 	R0, #1\n"
		"MOVNE 	R1, #0x360\n"
		"LDRNE 	R0, =0xFFD1B71C\n"
		"BLNE 	sub_FFC0BD98\n"		//DebugAssert
		"LDR 	R7, =0x194C4\n"
		"LDR 	R6, =0x1940C\n"
		"LDRSH 	R1, [R7,#0xE]\n"
		"LDR 	R0, [R6,#0x80]\n"
		"BL 	sub_FFCE495C\n"
		"BL 	sub_FFC387EC\n"			//GetCCDTemperature
		"LDR 	R3, =0x8C68\n"
		"STRH 	R0, [R4,#0x94]\n"
		"STR 	R3, [SP,#0x28-0x28]\n"
		"MOV 	R1, R0\n"
		"LDRH 	R0, [R6,#0x54]\n"
		"LDRSH 	R2, [R7,#0xC]\n"
		"SUB 	R3, R3, #4\n"
		"BL 	sub_FFD1C86C\n"
		"BL 	wait_until_remote_button_is_released\n"	//---------> changed
		"BL 	capt_seq_hook_set_nr\n"                     // -------> inserted
		"B 		sub_FFD1B5CC\n"                             // continue function in firmware
 );
}
