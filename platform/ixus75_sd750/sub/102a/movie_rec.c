#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table1[9]={0x2000,0x38D,0x788,0x5800,0x9C5,0x14B8,0x10000,0x1C6A,0x3C45};
long def_table2[9]={0x1CCD,-0x2E1,-0x579,0x4F33,-0x7EB,-0xF0C,0xE666,-0x170A,-0x2BC6};

long table1[9], table2[9];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<9;i++) {table1[i]=(def_table1[i]*a)/b; table2[i]=(def_table2[i]*a)/b;}
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};

// Modified for the 102a
void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(                
								"STMFD   SP!, {R4,R5,LR}\n"
								"SUB     SP, SP, #4\n"
								"MOV     R5, SP\n"
								"MOV     R4, #0\n"
"loc_FFB8EA28:\n"
								"LDR     R3, =0xBBB10\n"
								"MOV     R2, #0\n"
								"LDR     R0, [R3]\n"
								"MOV     R1, R5\n"
								"BL      sub_FFB1F0A8\n"		// ReceiveMessageQueue
								"LDR     R3, =0xBBC30\n"
								"LDR     R2, [R3]\n"
								"CMP     R2, #0\n"
								"BNE     loc_FFB8EAD4\n"
								"LDR     R1, [SP]\n"		// ,#0x10+var_10
								"LDR     R3, [R1]\n"
								"SUB     R3, R3, #2\n"
								"MOV     R0, R1\n"
								"CMP     R3, #9\n"         
								"LDRLS   PC, [PC,R3,LSL#2]\n"
								"B       loc_FFB8EAD8\n"
								".long loc_FFB8EA98\n"
								".long loc_FFB8EAB0\n"
								".long loc_FFB8EAB8\n"
								".long loc_FFB8EAC0\n"
								".long loc_FFB8EAA0\n"
								".long loc_FFB8EAC8\n"
								".long loc_FFB8EAA8\n"
								".long loc_FFB8EAD8\n"
								".long loc_FFB8EAD0\n"
								".long loc_FFB8EA90\n"
"loc_FFB8EA90:\n"
								"BL      sub_FFB8EB44\n"
								"B       loc_FFB8EAD4\n"
"loc_FFB8EA98:\n"
                "BL      unlock_optical_zoom\n"
								"BL      sub_FFB8ED4C\n"
								"B       loc_FFB8EAD4\n"
"loc_FFB8EAA0:\n"
								"BL      sub_FFB8F12C_my\n"   //----------->
								"B       loc_FFB8EAD4\n"
"loc_FFB8EAA8:\n"
								"BL      sub_FFB8F9BC\n"
								"B       loc_FFB8EAD4\n"
"loc_FFB8EAB0:\n"
								"BL      sub_FFB8F470\n"
								"B       loc_FFB8EAD4\n"
"loc_FFB8EAB8:\n"
								"BL      sub_FFB8FB58\n"
								"B       loc_FFB8EAD4\n"
"loc_FFB8EAC0:\n"
								"BL      sub_FFB8FD38\n"
								"B       loc_FFB8EAD4\n"
"loc_FFB8EAC8:\n"
								"BL      sub_FFB8FA44\n"
								"B       loc_FFB8EAD4\n"
"loc_FFB8EAD0:\n"
								"BL      sub_FFB8F4C0\n"
"loc_FFB8EAD4:\n"
								"LDR     R1, [SP]\n"		// ,#0x10+var_10
"loc_FFB8EAD8:\n"
								"LDR     R3, =0xBBB14\n"
								"STR     R4, [R1]\n"
								"LDR     R0, [R3]\n"
								"MOV     R2, R4\n"
								"BL      sub_FFB1F4C0\n"		// PostMessageQueue
								"B       loc_FFB8EA28\n"
	);
}

void __attribute__((naked,noinline)) sub_FFB8F12C_my(){
 asm volatile(
								"STMFD   SP!, {R4-R11,LR}\n"
								"LDR     R7, =0xBBC48\n"
								"SUB     SP, SP, #0x3C\n"
								"LDR     R3, [R7]\n"
								"MOV     R5, #0\n"
								"CMP     R3, #3\n"
								"MOV     R4, R0\n"
								"STR     R5, [SP,#0x34]\n"		//	#0x60+var_2C
								"STR     R5, [SP,#0x2C]\n"		// #0x60+var_34
								"MOV     R6, #1\n"
								"MOVEQ   R3, #4\n"
								"STREQ   R3, [R7]\n"
								"LDR     R3, =0xBBCF4\n"
								"MOV     LR, PC\n"
								"LDR     PC, [R3]\n"
								"LDR     R2, [R7]\n"
								"CMP     R2, #4\n"
								"BNE     loc_FFB8F388\n"
								"LDR     R3, =0xBBD36\n"
								"LDRH    R2, [R3]\n"
								"CMP     R2, #1\n"
								"BNE     loc_FFB8F1BC\n"
								"LDR     R2, =0xBBC58\n"
								"LDR     R1, =0xBBD38\n"
								"LDR     R0, [R2]\n"
								"LDRH    R3, [R1]\n"
								"MUL     R12, R3, R0\n"
								"LDR     R2, =0x10624DD3\n"
								"UMULL   R3, R1, R2, R12\n"
								"LDR     R3, =0xBBC74\n"
								"MOV     R1, R1,LSR#6\n"
								"LDR     R0, [R3]\n"
								"BL      sub_FF91EA44\n"		//	__umodsi3
								"CMP     R0, #0\n"
								"MOVNE   R6, #0\n"
								"MOVEQ   R6, #1\n"
"loc_FFB8F1BC:\n"
								"CMP     R6, #1\n"
								"BNE     loc_FFB8F1DC\n"
								"ADD     R0, SP, #0x38\n"		// #0x60+var_28
								"ADD     R1, SP, #0x34\n"		// #0x60+var_2C
								"ADD     R2, SP, #0x30\n"		// #0x60+var_30
								"ADD     R3, SP, #0x2C\n"		// #0x60+var_34
								"BL      sub_FFB908F4\n"
								"MOV     R5, R0\n"
"loc_FFB8F1DC:\n"
								"CMP     R5, #0\n"
								"BNE     loc_FFB8F20C\n"
								"LDR     R3, =0xBBC38\n"
								"LDR     R2, [R3]\n"
								"CMP     R2, #1\n"
								"BNE     loc_FFB8F220\n"
								"LDR     R2, =0xBBC74\n"
								"LDR     R1, =0xBBC4C\n"
								"LDR     R0, [R2]\n"
								"LDR     R3, [R1]\n"
								"CMP     R0, R3\n"
								"BCC     loc_FFB8F220\n"
"loc_FFB8F20C:\n"
								"MOV     R0, R5\n"
								"BL      sub_FFB8F3E8\n"
								"BL      sub_FFB8F97C\n"
								"MOV     R3, #5\n"
								"B       loc_FFB8F384\n"
"loc_FFB8F220:\n"
								"LDR     R9, [SP,#0x34]\n"		// #0x60+var_2C
								"CMP     R9, #0\n"
								"BEQ     loc_FFB8F308\n"
								"LDR     R7, =0xBBC90\n"
								"LDR     R12, =0xBBC7C\n"
								"LDMIB   R4, {R0-R2}\n"
								"LDR     R10, [R4,#0x18]\n"
								"LDR     R6, [R7]\n"
								"LDR     R7, [R4,#0x14]\n"
								"LDR     R4, =0xBBC3C\n"
								"LDR     R8, [R12]\n"
								"ADD     R5, SP, #0x2C\n"			// #0x60+var_34
								"LDMIA   R5, {R5,LR}\n"
								"MOV     R11, #1\n"
								"LDR     R3, [SP,#0x38]\n"		// #0x60+var_28
								"ADD     R12, SP, #0x28\n"		// #0x60+var_38
								"STR     R11, [R4]\n"
								"ADD     R4, SP, #0x24\n"			// #0x60+var_3C
								"STMEA   SP, {R9,LR}\n"
								"STR     R5, [SP,#0x8]\n"			// #0x60+var_58
								"STR     R12, [SP,#0xC]\n"		// #0x60+var_54
								"STR     R8, [SP,#0x10]\n"		// #0x60+var_50
								"STR     R6, [SP,#0x14]\n"		// #0x60+var_4C
								"STR     R7, [SP,#0x18]\n"		// #0x60+var_48
								"STR     R10, [SP,#0x1C]\n"		// #0x60+var_44
								"STR     R4, [SP,#0x20]\n"		// #0x60+var_40
								"BL      sub_FFB939A0\n"
								"LDR     R3, =0xBBB08\n"
								"MOV     R1, #0x3E8\n"
								"LDR     R0, [R3]\n"
								"BL      sub_FFB1FC70\n"
								"CMP     R0, #9\n"
								"BNE     loc_FFB8F2B4\n"
								"BL      sub_FFB91184\n"
								"LDR     R3, =0xBBC48\n"
								"LDR     R0, =0xFFB8F114\n"		//	aJpegtimeout_5
								"B       loc_FFB8F2CC\n"
"loc_FFB8F2B4:\n"
								"LDR     R4, [SP,#0x24]\n"		// #0x60+var_3C
								"CMP     R4, #0\n"
								"BEQ     loc_FFB8F2D8\n"
								"BL      sub_FFB91184\n"
								"LDR     R3, =0xBBC48\n"
								"LDR     R0, =0xFFB8F120\n"		// aJpegicerror_5
"loc_FFB8F2CC:\n"
								"STR     R11, [R3]\n"
								"BL      sub_FFB42C38\n"		// HardwareDefect
								"B       loc_FFB8F388\n"
"loc_FFB8F2D8:\n"
								"BL      sub_FFB93B1C\n"
								"LDR     R0, [SP,#0x38]\n"		// #0x60+var_28
								"LDR     R1, [SP,#0x28]\n"		// #0x60+var_38
								"BL      sub_FFB90DDC\n"
								"LDR     R12, =0xBBC70\n"
								"LDR     R3, [R12]\n"
								"ADD     R3, R3, #1\n"
								"LDR     R0, [SP,#0x28]\n"		// #0x60+var_38
								"LDR     R1, =0xBBC90\n"
								"MOV     R2, R4\n"
								"STR     R3, [R12]\n"
								"BL      sub_FFAFE62C_my\n"  //-------------->
"loc_FFB8F308:\n"
								"LDR     R4, =0xBBC74\n"
								"LDR     R2, =0xBBC9C\n"
								"LDR     R3, [R4]\n"
								"LDR     R1, [R2]\n"
								"LDR     R12, =0xBBC98\n"
								"ADD     R3, R3, #1\n"
								"MUL     R0, R1, R3\n"
								"LDR     R1, [R12]\n"
								"STR     R3, [R4]\n"
								"BL      sub_FF91E9AC\n"		// __udivis3
								"LDR     R6, =0xBBC94\n"
								"MOV     R4, R0\n"
								"BL      sub_FFB911C0\n"
								"LDR     R3, [R6]\n"
								"CMP     R3, R4\n"
								"BNE     loc_FFB8F35C\n"
								"LDR     R5, =0xBBC40\n"
								"LDR     R3, [R5]\n"
								"CMP     R3, #1\n"
								"BNE     loc_FFB8F37C\n"
								"B       loc_FFB8F360\n"
"loc_FFB8F35C:\n"
								"LDR     R5, =0xBBC40\n"
"loc_FFB8F360:\n"
								"LDR     R2, =0xBBCD8\n"
								"MOV     R0, R4\n"
								"MOV     LR, PC\n"
								"LDR     PC, [R2]\n"
								"MOV     R3, #0\n"
								"STR     R3, [R5]\n"
								"STR     R4, [R6]\n"
"loc_FFB8F37C:\n"
								"LDR     R7, =0xBBC3C\n"
								"MOV     R3, #0\n"
"loc_FFB8F384:\n"
								"STR     R3, [R7]\n"
"loc_FFB8F388:\n"
								"ADD     SP, SP, #0x3C\n"
								"LDMFD   SP!, {R4-R11,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFAFE62C_my(){
 asm volatile(
								"STMFD   SP!, {R4-R8,LR}\n"
								"LDR     R12, =0x975B4\n"
								"LDR     R4, [R12]\n"
								"LDR     R3, =0x975BC\n"
								"CMP     R4, #0\n"
								"MOV     R8, R1\n"
								"MOV     R7, R0\n"
								"LDR     R1, [R3]\n"
								"BEQ     loc_FFAFE664\n"
								"LDR     R2, =0x975C0\n"
								"LDR     R3, [R2]\n"
								"CMP     R3, #1\n"
								"BNE     loc_FFAFE678\n"
								"B       loc_FFAFE668\n"
"loc_FFAFE664:\n"
								"LDR     R2, =0x975C0\n"
"loc_FFAFE668:\n"
								"MOV     R3, #0\n"
								"STR     R3, [R2]\n"
								"STR     R7, [R12]\n"
								"B       loc_FFAFE730\n"
"loc_FFAFE678:\n"
								"LDR     R2, =0x975B8\n"
								"LDR     R3, [R2]\n"
								"LDR     R6, =table1\n"		// unk_FFAFE530
								"ADD     R3, R3, R3,LSL#1\n"
								"MOV     LR, R3,LSL#2\n"
								"LDR     R2, [R6,LR]\n"
								"LDR     R5, =table2\n"		// unk_FFAFE554
								"RSB     R12, R2, R4\n"
								"LDR     R3, [R5,LR]\n"
								"CMP     R12, #0\n"
								"RSB     R0, R3, R4\n"
								"BLE     loc_FFAFE6DC\n"
								"ADD     R3, R6, #4\n"
								"LDR     R2, [R3,LR]\n"
								"CMP     R2, R12\n"
								"ADDGE   R1, R1, #1\n"
								"BGE     loc_FFAFE6D0\n"
								"ADD     R3, R6, #8\n"
								"LDR     R2, [R3,LR]\n"
								"CMP     R2, R12\n"
								"ADDGE   R1, R1, #2\n"
								"ADDLT   R1, R1, #3\n"
"loc_FFAFE6D0:\n"
						 // "CMP     R1, #0x16\n"
						 // "MOVGE   R1, #0x16\n"
                "CMP     R1, #0x1A\n"     // + 
                "MOVGE   R1, #0x1A\n"     // + 
                
								"B       loc_FFAFE714\n"
"loc_FFAFE6DC:\n"
								"CMP     R0, #0\n"
								"BGE     loc_FFAFE714\n"
								"ADD     R3, R5, #4\n"
								"LDR     R2, [R3,LR]\n"
								"CMP     R2, R0\n"
								"SUBLE   R1, R1, #1\n"
								"BLE     loc_FFAFE70C\n"
								"ADD     R3, R5, #8\n"
								"LDR     R2, [R3,LR]\n"
								"CMP     R2, R0\n"
								"SUBLE   R1, R1, #2\n"
								"SUBGT   R1, R1, #3\n"
"loc_FFAFE70C:\n"
								"CMP     R1, #0\n"
								"MOVLT   R1, #0\n"
"loc_FFAFE714:\n"
								"LDR     R0, =0x975BC\n"
								"LDR     R3, [R0]\n"
								"CMP     R1, R3\n"
								"LDRNE   R2, =0x975C0\n"
								"MOVNE   R3, #1\n"
								"STRNE   R1, [R0]\n"
								"STRNE   R3, [R2]\n"
"loc_FFAFE730:\n"
								"LDR     R3, =0x975BC\n"
								"LDR     R2, =CompressionRateTable\n"		// unk_FFAFE4D4
								"LDR     R1, [R3]\n"
								"LDR     R0, =0x975B4\n"
								"LDR     R3, [R2,R1,LSL#2]\n"
								
								"LDR     R1, =video_mode\n"      // +
                "LDR     R1, [R1]\n"             // +
                "LDR     R1, [R1]\n"             // +
                "CMP     R1, #1\n"               // +
                "LDREQ   R1, =video_quality\n"   // +     
                "LDREQ   R1, [R1]\n"             // +     
                "LDREQ   R3, [R1]\n"             // +
								
								"STR     R7, [R0]\n"
								"STR     R3, [R8]\n"
								"LDMFD   SP!, {R4-R8,PC}\n"
 );
}
