#include "conf.h"

void change_video_tables(int a, int b){
}


void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}


void __attribute__((naked,noinline)) movie_record_task(){ 
 asm volatile(
                 "STMFD   SP!, {R2-R8,LR}\n"
                 "LDR     R8, =0x3F5\n"
                 "LDR     R7, =0x2710\n"
                 "LDR     R4, =0x53F8\n"
                 "MOV     R6, #0\n"
                 "MOV     R5, #1\n"
 "loc_FF86459C:\n" //done
                 "LDR     R0, [R4,#0x18]\n"
                 "MOV     R2, #0\n"
                 "ADD     R1, SP, #4\n"
                 "BL      sub_FF8274FC\n" //done
                 "LDR     R2, =0xFF862E34\n" //done
                 "LDR     R0, [R4,#0xB0]\n"
                 "MOV     R3, R8\n"
                 "MOV     R1, R7\n"
                 "BL      sub_FF827DF8\n" //checked
                 "LDR     R0, [R4,#0x20]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF86469C\n" //done
                 "LDR     R0, [SP,#4]\n"
                 "LDR     R1, [R0]\n"
                 "SUB     R1, R1, #2\n"
                 "CMP     R1, #0xB\n"
                 "ADDLS   PC, PC, R1,LSL#2\n"
                 "B       loc_FF86469C\n"
 "loc_FF8645E4:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF864644\n"

"loc_FF8645E8:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF86465C\n"

"loc_FF8645EC:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF86466C\n"

"loc_FF8645F0:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF864674\n"

"loc_FF8645F4:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF86464C\n"

"loc_FF8645F8:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF86467C\n"

"loc_FF8645FC:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF864654\n"

"loc_FF864600:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF86469C\n"

"loc_FF864604:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF86468C\n"

"loc_FF864608:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF864694\n"

"loc_FF86460C:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF864684\n"

"loc_FF864610:\n" //				; CODE XREF: sub_FF864584+58j
		"B	loc_FF864614\n"

"loc_FF864614:\n" //				; CODE XREF: sub_FF864584+58j
/*
; jumptable FF8645DC entry 11
		ADR	R0, nullsub_265
		STR	R6, [R4,#0x34]
		STR	R0, [R4,#0x9C]
		LDR	R0, =nullsub_264
		LDR	R2, =sub_FF86334C
		STR	R0, [R4,#0xA0]
		LDR	R0, =sub_FF86345C
		LDR	R1, =0x1BA0C
		STR	R6, [R4,#0x24]
		BL	sub_FF83C1F4
		STR	R5, [R4,#0x38]
		B	loc_FF86469C
*/
                 "LDR     R0, =0xFF86422C\n" //done
                 "STR     R6, [R4,#0x34]\n"
                 "STR     R0, [R4,#0x9C]\n"
                 "LDR     R0, =0xFF863348\n" //done
                 "LDR     R2, =0xFF86334C\n"
                 "STR     R0, [R4,#0xA0]\n"
                 "LDR     R0, =0xFF86345C\n" //done
                 "LDR     R1, =0x1BA0C\n"
                 "STR     R6, [R4,#0x24]\n"
                 "BL      sub_FF83C1F4\n" //checked
                 "STR     R5, [R4,#0x38]\n"
                 "B       loc_FF86469C\n" //done

		
"loc_FF864644:\n" //				; CODE XREF: sub_FF864584+58j
//					; sub_FF864584:loc_FF8645E4j
//;jumptable FF8645DC entry 0		; LOCATION: MovieRecorder.c:0
		"BL	sub_FF864354\n"
		"B	loc_FF86469C\n"

"loc_FF86464C:\n" //				; CODE XREF: sub_FF864584+58"j\n"
//					; sub_FF864584:loc_FF8645F4j
//; jumptable FF8645DC entry 4
		"BL	sub_FF863E84_my\n" //--->
		"B	loc_FF86469C\n"

"loc_FF864654:\n" //				; CODE XREF: sub_FF864584+58j
//					; sub_FF864584:loc_FF8645FCj
//; jumptable FF8645DC entry 6
		"BL	sub_FF864A18\n"
		"B	loc_FF86469C\n"

"loc_FF86465C:\n" //				; CODE XREF: sub_FF864584+58j
//					; sub_FF864584:loc_FF8645E8j
//; jumptable FF8645DC entry 1
		"LDR	R0, [R4,#0x38]\n"
		"CMP	R0, #5\n"
		"STRNE	R5, [R4,#0x28]\n"
		"B	loc_FF86469C\n"

"loc_FF86466C:\n" //				; CODE XREF: sub_FF864584+58j
//					; sub_FF864584:loc_FF8645ECj
//; jumptable FF8645DC entry 2		; LOCATION: MovieRecorder.c:0
		"BL	sub_FF863BCC\n"
		"B	loc_FF86469C\n"

"loc_FF864674:\n" //				; CODE XREF: sub_FF864584+58j
//					; sub_FF864584:loc_FF8645F0j
//; jumptable FF8645DC entry 3		; LOCATION: MovieRecorder.c:0
		"BL	sub_FF8638C0\n" //__MovieRecorder.c__0
		"B	loc_FF86469C\n"

"loc_FF86467C:\n" //				; CODE XREF: sub_FF864584+58j
					//; sub_FF864584:loc_FF8645F8j
//; jumptable FF8645DC entry 5		; LOCATION: MovieRecorder.c:100
		"BL	sub_FF8632D4\n" //__MovieRecorder.c__100
		"B	loc_FF86469C\n"

"loc_FF864684:\n" //				; CODE XREF: sub_FF864584+58j
//					; sub_FF864584:loc_FF86460Cj
//; jumptable FF8645DC entry 10		; LOCATION: MovieRecorder.c:100
		"BL	sub_FF864980\n" //__MovieRecorder.c__100
		"B	loc_FF86469C\n"

"loc_FF86468C:\n" //				; CODE XREF: sub_FF864584+58j
//					; sub_FF864584:loc_FF864604j
//; jumptable FF8645DC entry 8		; LOCATION: MovieRecorder.c:0
		"BL	sub_FF864834\n" //__MovieRecorder.c__0
		"B	loc_FF86469C\n" 

"loc_FF864694:\n" //				; CODE XREF: sub_FF864584+58j
					//; sub_FF864584:loc_FF864608j
//; jumptable FF8645DC entry 9		; LOCATION: MovieRecorder.c:0
		"BL	sub_FF8637B0\n" //__MovieRecorder.c__0
		"STR	R5, [R4,#0xD8]\n"

"loc_FF86469C:\n" //				; CODE XREF: sub_FF864584+44j
//					; sub_FF864584+58j ...
//; jumptable FF8645DC default entry
//; jumptable FF8645DC entry 7
		         "LDR     R1, [SP,#4]\n"
                 "MOV     R3, #0x430\n"
                 "STR     R6, [R1]\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =0xFF862E34\n" //done
                 "MOV     R2, R7\n"
                 "LDR     R0, [R4,#0x1C]\n"
                 "BL      sub_FF827E50\n" //checked
                 "LDR     R0, [R4,#0xB0]\n"
                 "BL      sub_FF8279E8\n"
                 "B       loc_FF86459C\n"
/*		LDR	R1, [SP,#0x20+var_1C]
		MOV	R3, #0x430
		STR	R6, [R1]
		STR	R3, [SP,#0x20+var_20]
		ADR	R3, aMovierecorder_ ; "MovieRecorder.c"
		MOV	R2, R7
		LDR	R0, [R4,#0x1C]
		BL	sub_FF827E50
		LDR	R0, [R4,#0xB0]
		BL	eventproc_export_GiveSemaphore ; LOCATION: KerSem.c:0
		B	loc_FF86459C
; End of function sub_FF864584
*/

 /*
 "loc_FF8645E4:\n" //done
                 "B       loc_FF864644\n"
 "loc_FF8645E8:\n" //done
                 "B       loc_FF86465C\n"
 "loc_FF8645EC:\n" //done
                 "B       loc_FF86466C\n"
 "loc_FF8645F0:\n" //done
                 "B       loc_FF864674\n"
 "loc_FF8645F4:\n" //done
                 "B       loc_FF86464C\n"
 "loc_FF8645FC:\n" //done
                 "B       loc_FF86467C\n"
 "loc_FF864600:\n" //done
                 "B       loc_FF864654\n"
 "loc_FF864604:\n" //done
                 "B       loc_FF86469C\n"
 "loc_FF864608:\n" //done
                 "B       loc_FF864694\n"
 "loc_FF86460C:\n" //done
                 "B       loc_FF86469C\n"
 "loc_FF864610:\n" //done
                 "B       loc_FF86468C\n"
 "loc_FF864614:\n" //done
                 "B       loc_FF86461C\n"
 "loc_FF864618:\n" //done
                 "LDR     R0, =0xFF864234\n"
                 "STR     R6, [R4,#0x34]\n"
                 "STR     R0, [R4,#0x9C]\n"
                 "LDR     R0, =0xFF863350\n"
                 "LDR     R2, =0xFF863354\n"
                 "STR     R0, [R4,#0xA0]\n"
                 "LDR     R0, =0xFF863464\n"
                 "LDR     R1, =0x1BA0C\n"
                 "STR     R6, [R4,#0x24]\n"
                 "BL      sub_FF83C1F4\n"
                 "STR     R5, [R4,#0x38]\n"
                 "B       loc_FF8646A4\n"
 "loc_FF86464C:\n"
                 "BL      sub_FF86435C\n"
                 "B       loc_FF8646A4\n"
 "loc_FF864654:\n"
                 "BL      sub_FF863E8C_my\n"  //--------------->
                 "B       loc_FF8646A4\n"
 "loc_FF86465C:\n"
                 "BL      sub_FF864A20\n"
                 "B       loc_FF8646A4\n"
 "loc_FF864664:\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "CMP     R0, #5\n"
                 "STRNE   R5, [R4,#0x28]\n"
                 "B       loc_FF8646A4\n"
 "loc_FF864674:\n"
                 "BL      sub_FF863BD4\n"
                 "B       loc_FF8646A4\n"
 "loc_FF86467C:\n"
                 "BL      sub_FF8638C8\n"
                 "B       loc_FF8646A4\n"
 "loc_FF864684:\n"
                 "BL      sub_FF8632DC\n"
                 "B       loc_FF8646A4\n"
 "loc_FF86468C:\n"
                 "BL      sub_FF864988\n"
                 "B       loc_FF8646A4\n"
 "loc_FF864694:\n"
                 "BL      sub_FF86483C\n"
                 "B       loc_FF8646A4\n"
 "loc_FF86469C:\n"
                 "BL      sub_FF8637B8\n"
                 "STR     R5, [R4,#0xD8]\n"
 "loc_FF8646A4:\n"
                 "LDR     R1, [SP,#4]\n"
                 "MOV     R3, #0x430\n"
                 "STR     R6, [R1]\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =0xFF862E3C\n"
                 "MOV     R2, R7\n"
                 "LDR     R0, [R4,#0x1C]\n"
                 "BL      sub_FF827E50\n"
                 "LDR     R0, [R4,#0xB0]\n"
                 "BL      sub_FF8279E8\n"
                 "B       loc_FF8645A4\n"
				 */
 );
}


void __attribute__((naked,noinline)) sub_FF863E84_my(){ 
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "SUB     SP, SP, #0x48\n"
                 "MOV     R7, #0\n"
                 "LDR     R6, =0x53F8\n"
                 "MOV     R4, R0\n"
                 "STR     R7, [SP,#0x38]\n"
                 "STR     R7, [SP,#0x30]\n"
                 "LDR     R0, [R6,#0x38]\n"
                 "CMP     R0, #3\n"
                 "MOVEQ   R0, #4\n"
                 "STREQ   R0, [R6,#0x38]\n"
                 "LDR     R0, [R6,#0x9C]\n"
                 "BLX     R0\n"
                 "LDR     R0, [R6,#0x38]\n"
                 "CMP     R0, #4\n"
                 "BNE     loc_FF863F88\n" //done
                 "ADD     R3, SP, #0x30\n"
                 "ADD     R2, SP, #0x34\n"
                 "ADD     R1, SP, #0x38\n"
                 "ADD     R0, SP, #0x3C\n"
                 "BL      sub_FF9462B4\n" //done
                 "CMP     R0, #0\n"
                 "MOV     R5, #1\n"
                 "BNE     loc_FF863F00\n" //done
                 "LDR     R1, [R6,#0x28]\n"
                 "CMP     R1, #1\n"
                 "BNE     loc_FF863F9C\n" //done
                 "LDR     R1, [R6,#0x4C]\n"
                 "LDR     R2, [R6,#0x3C]\n"
                 "CMP     R1, R2\n"
                 "BCC     loc_FF863F9C\n" //done
 "loc_FF863F00:\n"
                 "BL      sub_FF86349C\n" //done
                 "BL      sub_FF864820\n" //done
                 "LDR     R0, [R4,#0x14]\n"
                 "LDR     R1, [R4,#0x18]\n"
                 "ADD     R3, SP, #0x40\n"
                 "MVN     R2, #1\n"
                 "ADD     R7, SP, #0x18\n"
                 "STMIA   R7, {R0-R3}\n"
                 "LDR     R2, [R6,#0x64]\n"
                 "LDR     R3, [R6,#0x68]\n"
                 "MOV     R0, #0\n"
                 "ADD     R1, SP, #0x44\n"
                 "ADD     R7, SP, #8\n"
                 "STMIA   R7, {R0-R3}\n"
                 "MOV     R3, #0\n"
                 "MOV     R2, #0x40\n"
                 "STRD    R2, [SP]\n"
                 "LDMIB   R4, {R0,R1}\n"
                 "LDR     R3, =0x1BA98\n"
                 "MOV     R2, R8\n"
                 "BL      sub_FF8FF5B0\n" //done
                 "LDR     R0, [R6,#0x10]\n"
                 "MOV     R1, #0x3E8\n"
                 "BL      sub_FF827918\n" //checked
                 "CMP     R0, #9\n"
                 "BEQ     loc_FF864020\n" //done
                 "LDR     R0, [SP,#0x40]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF86403C\n" //done
                 "MOV     R0, #1\n"
                 "BL      sub_FF8FF658\n" //done
                 "BL      sub_FF8FF694\n" //done
                 "MOV     R0, #5\n"
                 "STR     R0, [R6,#0x38]\n"
 "loc_FF863F88:\n" //done
                 "ADD     SP, SP, #0x48\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FF863F90:\n" //done
                 "BL      sub_FF881204\n" //done
                 "MOV     R0, #1\n"
                 "B       loc_FF8640EC\n" //done
 "loc_FF863F9C:\n" //done
                 "LDR     R12, [SP,#0x38]\n"
                 "CMP     R12, #0\n"
                 "BEQ     loc_FF8641D4\n" //done
                 "STR     R5, [R6,#0x2C]\n"
                 "LDR     R0, [R6,#0x4C]\n"
                 "LDR     R8, [R4,#0xC]\n"
                 "CMP     R0, #0\n"
                 "LDRNE   LR, [SP,#0x3C]\n"
                 "BNE     loc_FF864068\n" //done
                 "LDR     R0, [R4,#0x14]\n"
                 "LDR     R1, [R4,#0x18]\n"
                 "ADD     R3, SP, #0x40\n"
                 "MVN     R2, #0\n"
                 "ADD     LR, SP, #0x18\n"
                 "STMIA   LR, {R0-R3}\n"
                 "LDR     R0, [SP,#0x30]\n"
                 "LDR     R2, [R6,#0x64]\n"
                 "LDR     R3, [R6,#0x68]\n"
                 "ADD     R1, SP, #0x44\n"
                 "ADD     LR, SP, #8\n"
                 "STMIA   LR, {R0-R3}\n"
                 "LDR     R3, [SP,#0x34]\n"
                 "STR     R12, [SP]\n"
                 "STR     R3, [SP,#4]\n"
                 "LDMIB   R4, {R0,R1}\n"
                 "LDR     R3, [SP,#0x3C]\n"
                 "MOV     R2, R8\n"
                 "BL      sub_FF8FF5B0\n" //done
                 "LDR     R0, [R6,#0x10]\n"
                 "MOV     R1, #0x3E8\n"
                 "BL      sub_FF827918\n" //checked
                 "CMP     R0, #9\n"
                 "BNE     loc_FF864030\n" //done
 "loc_FF864020:\n" //done
                 "BL      sub_FF946780\n" //done
                 "MOV     R0, #0x90000\n"
                 "STR     R5, [R6,#0x38]\n"
                 "B       loc_FF863F90\n" //done
 "loc_FF864030:\n" //done
                 "LDR     R0, [SP,#0x40]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF86404C\n" //done
 "loc_FF86403C:\n" //done
                 "BL      sub_FF946780\n" //done
                 "MOV     R0, #0xA0000\n"
                 "STR     R5, [R6,#0x38]\n"
                 "B       loc_FF863F90\n" //done
 "loc_FF86404C:\n" //done
                 "MOV     R0, #1\n"
                 "BL      sub_FF8FF658\n" //done
                 "LDR     R0, [SP,#0x44]\n"
                 "LDR     R1, [SP,#0x3C]\n"
                 "ADD     LR, R1, R0\n"
                 "LDR     R1, [SP,#0x38]\n"
                 "SUB     R12, R1, R0\n"
 "loc_FF864068:\n" //done
                 "LDR     R2, [R6,#0x48]\n"
                 "LDR     R0, [R4,#0x14]\n"
                 "LDR     R1, [R4,#0x18]\n"
                 "ADD     R3, SP, #0x40\n"
                 "STR     R1, [SP,#0x1C]\n"
                 "STR     R0, [SP,#0x18]\n"
                 "STR     R3, [SP,#0x24]\n"
                 "STR     R2, [SP,#0x20]\n"
                 "LDR     R2, [R6,#0x64]\n"
                 "LDR     R3, [R6,#0x68]\n"
                 "ADD     R1, SP, #0x44\n"
                 "STR     R1, [SP,#0xC]\n"
                 "STR     R3, [SP,#0x14]\n"
                 "LDR     R3, [SP,#0x34]\n"
                 "LDR     R0, [SP,#0x30]\n"
                 "STR     R2, [SP,#0x10]\n"
                 "STR     R3, [SP,#4]\n"
                 "STR     R12, [SP]\n"
                 "STR     R0, [SP,#8]\n"
                 "LDMIB   R4, {R0,R1}\n"
                 "MOV     R3, LR\n"
                 "MOV     R2, R8\n"
                 "BL      sub_FF8FF5B0\n" //done
                 "LDR     R0, [R6,#0x10]\n"
                 "MOV     R1, #0x3E8\n"
                 "BL      sub_FF827918\n" //checked
                 "CMP     R0, #9\n"
                 "BNE     loc_FF8640F4\n" //done
                 "BL      sub_FF946780\n" //done
                 "MOV     R0, #0x90000\n"
                 "STR     R5, [R6,#0x38]\n"
                 "BL      sub_FF881204\n" //done
                 "MOV     R0, #0\n"
 "loc_FF8640EC:\n" //done
                 "BL      sub_FF8FF658\n" //done
                 "B       loc_FF863F88\n" //done
 "loc_FF8640F4:\n" //done
                 "LDR     R0, [SP,#0x40]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF864114\n" //done
                 "BL      sub_FF946780\n" //done
                 "MOV     R0, #0xA0000\n"
                 "STR     R5, [R6,#0x38]\n"
                 "BL      sub_FF881204\n" //done
                 "B       loc_FF863F88\n" //done
 "loc_FF864114:\n" //done
                 "MOV     R0, #0\n"
                 "BL      sub_FF8FF658\n" //done
                 "LDR     R0, [R6,#0xD8]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF8641A4\n" //done
                 "LDR     R0, [R6,#0x48]\n"
                 "MOV     R1, #0xF\n"
                 "BL      sub_FFB02514\n" //done
                 "MOVS    R4, R1\n"
                 "STREQ   R7, [R6,#0xD8]\n"
                 "BEQ     loc_FF8641A4\n" //done
                 "LDR     R5, [SP,#0x3C]\n"
                 "MOV     R2, #4\n"
                 "ADD     R0, SP, #0x2C\n"
                 "ADD     R1, R5, #4\n"
                 "BL      sub_FFAFFFF4\n" //done was FFB00004
                 "LDR     R0, [SP,#0x2C]\n"
                 "MOV     R1, R0,LSR#24\n"
                 "AND     R2, R0, #0xFF0000\n"
                 "ORR     R1, R1, R2,LSR#8\n"
                 "AND     R2, R0, #0xFF00\n"
                 "ORR     R1, R1, R2,LSL#8\n"
                 "ORR     R0, R1, R0,LSL#24\n"
                 "BIC     R0, R0, #0x1E000\n"
                 "ORR     R0, R0, R4,LSL#13\n"
                 "MOV     R1, R0,LSR#24\n"
                 "AND     R2, R0, #0xFF0000\n"
                 "ORR     R1, R1, R2,LSR#8\n"
                 "AND     R2, R0, #0xFF00\n"
                 "ORR     R1, R1, R2,LSL#8\n"
                 "ORR     R0, R1, R0,LSL#24\n"
                 "STR     R0, [SP,#0x2C]\n"
                 "ADD     R0, R5, #4\n"
                 "ADD     R1, SP, #0x2C\n"
                 "MOV     R2, #4\n"
                 "BL      sub_FFAFFFF4\n" //done was FFB00004
 "loc_FF8641A4:\n" //done
                 "LDR     R0, [SP,#0x3C]\n"
                 "LDR     R1, [SP,#0x44]\n"
                 "BL      sub_FF9464DC\n" //done
                 "LDR     R0, [R6,#0x48]\n"
                 "LDR     R3, =0x5460\n"    // ->----
                 "ADD     R1, R0, #1\n"     //       |
                 "STR     R1, [R6,#0x48]\n" //       |
                 "STR     R3, [SP]\n"       //       |
                 "LDR     R0, [SP,#0x44]\n" //       |
                 "SUB     R3, R3, #4\n"     // ->----|
                 "MOV     R2, #0xF\n"       //       |
                 "BL      sub_FF9446D8\n"   //       |  //done (0x10 off)
                                            //       |
                 "LDR     R0, =0x5460-4\n"  // -<----     // +
                 "BL      set_quality\n"                  // +


 "loc_FF8641D4:\n" //done
                 "LDR     R0, [R6,#0x4C]\n"
                 "ADD     R0, R0, #1\n"
                 "STR     R0, [R6,#0x4C]\n"
                 "LDR     R1, [R6,#0x74]\n"
                 "MUL     R0, R1, R0\n"
                 "LDR     R1, [R6,#0x70]\n"
                 "BL      sub_FFB02514\n" //done 0x10
                 "MOV     R4, R0\n"
                 "BL      sub_FF9467B8\n" //done 0x10
                 "LDR     R1, [R6,#0x6C]\n"
                 "CMP     R1, R4\n"
                 "BNE     loc_FF864210\n" //done
                 "LDR     R0, [R6,#0x30]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF864224\n" //done
 "loc_FF864210:\n" //done
                 "LDR     R1, [R6,#0x80]\n"
                 "MOV     R0, R4\n"
                 "BLX     R1\n"
                 "STR     R4, [R6,#0x6C]\n"
                 "STR     R7, [R6,#0x30]\n"
 "loc_FF864224:\n" //done
                 "STR     R7, [R6,#0x2C]\n"
                 "B       loc_FF863F88\n" //done

 );
}

