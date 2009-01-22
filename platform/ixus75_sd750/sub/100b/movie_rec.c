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

void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
								"STMFD   SP!, {R4,R5,LR}\n"
								"SUB     SP, SP, #4\n"
								"MOV     R5, SP\n"
								"MOV     R4, #0\n"
"loc_FFB8E934:\n"
								"LDR     R3, =0xBBB10\n"
								"MOV     R2, #0\n"
								"LDR     R0, [R3]\n"
								"MOV     R1, R5\n"
								"BL      sub_FFB1EFB4\n"		// ReceiveMessageQueue
								"LDR     R3, =0xBBC30\n"
								"LDR     R2, [R3]\n"
								"CMP     R2, #0\n"
								"BNE     loc_FFB8E9E0\n"
								"LDR     R1, [SP]\n"		// ,#0x10+var_10
								"LDR     R3, [R1]\n"
								"SUB     R3, R3, #2\n"
								"MOV     R0, R1\n"
								"CMP     R3, #9\n"
								"LDRLS   PC, [PC,R3,LSL#2]\n"
								"B       loc_FFB8E9E4\n"
								".long loc_FFB8E9A4\n"
								".long loc_FFB8E9BC\n"
								".long loc_FFB8E9C4\n"
								".long loc_FFB8E9CC\n"
								".long loc_FFB8E9AC\n"
								".long loc_FFB8E9D4\n"
								".long loc_FFB8E9B4\n"
								".long loc_FFB8E9E4\n"
								".long loc_FFB8E9DC\n"
								".long loc_FFB8E99C\n"
"loc_FFB8E99C:\n"
								"BL      sub_FFB8EA50\n"
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9A4:\n"
                "BL      unlock_optical_zoom\n"
								"BL      sub_FFB8EC58\n"
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9AC:\n"
								"BL      sub_FFB8F038_my\n"  //----------->
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9B4:\n"
								"BL      sub_FFB8F8C8\n"
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9BC:\n"
								"BL      sub_FFB8F37C\n"
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9C4:\n"
								"BL      sub_FFB8FA64\n"
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9CC:\n"
								"BL      sub_FFB8FC44\n"
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9D4:\n"
								"BL      sub_FFB8F950\n"
								"B       loc_FFB8E9E0\n"
"loc_FFB8E9DC:\n"
								"BL      sub_FFB8F3CC\n"
"loc_FFB8E9E0:\n"
								"LDR     R1, [SP]\n"		// ,#0x10+var_10
"loc_FFB8E9E4:\n"
								"LDR     R3, =0xBBB14\n"
								"STR     R4, [R1]\n"
								"LDR     R0, [R3]\n"
								"MOV     R2, R4\n"
								"BL      sub_FFB1F3CC\n"		// PostMessageQueue
								"B       loc_FFB8E934\n"
	);
}

void __attribute__((naked,noinline)) sub_FFB8F038_my(){
 asm volatile(
 								"STMFD   SP!, {R4-R11,LR}\n"
 								"LDR     R7, =0xBBC48\n"
                "SUB     SP, SP, #0x3C\n"
                "LDR     R3, [R7]\n"
                "MOV     R5, #0\n"
                "CMP     R3, #3\n"
                "MOV     R4, R0\n"
								"STR     R5, [SP,#0x34]\n"		// #0x60+var_2C
								"STR     R5, [SP,#0x2C]\n"		// #0x60+var_34
                "MOV     R6, #1\n"
                "MOVEQ   R3, #4\n"
                "STREQ   R3, [R7]\n"
                "LDR     R3, =0xBBCF4\n"
                "MOV     LR, PC\n"
                "LDR     PC, [R3]\n"
                "LDR     R2, [R7]\n"
                "CMP     R2, #4\n"
                "BNE     loc_FFB8F294\n"
                "LDR     R3, =0xBBD36\n"
                "LDRH    R2, [R3]\n"
                "CMP     R2, #1\n"
                "BNE     loc_FFB8F0C8\n"
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
                "BL      sub_FF91EA44\n"		// __umodsi3
                "CMP     R0, #0\n"
                "MOVNE   R6, #0\n"
                "MOVEQ   R6, #1\n"
"loc_FFB8F0C8:\n"
                "CMP     R6, #1\n"
                "BNE     loc_FFB8F0E8\n"
								"ADD     R0, SP, #0x38\n"		// #0x60+var_28
								"ADD     R1, SP, #0x34\n"		// #0x60+var_2C
								"ADD     R2, SP, #0x30\n"		// #0x60+var_30
								"ADD     R3, SP, #0x2C\n"		// #0x60+var_34
                "BL      sub_FFB90800\n"
                "MOV     R5, R0\n"
"loc_FFB8F0E8:\n"
                "CMP     R5, #0\n"
                "BNE     loc_FFB8F118\n"
                "LDR     R3, =0xBBC38\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #1\n"
                "BNE     loc_FFB8F12C\n"
                "LDR     R2, =0xBBC74\n"
                "LDR     R1, =0xBBC4C\n"
                "LDR     R0, [R2]\n"
                "LDR     R3, [R1]\n"
                "CMP     R0, R3\n"
                "BCC     loc_FFB8F12C\n"
"loc_FFB8F118:\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB8F2F4\n"
                "BL      sub_FFB8F888\n"
                "MOV     R3, #5\n"
                "B       loc_FFB8F290\n"
"loc_FFB8F12C:\n"
								"LDR     R9, [SP,#0x34]\n"		// #0x60+var_2C
                "CMP     R9, #0\n"
                "BEQ     loc_FFB8F214\n"
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
                "BL      sub_FFB938AC\n"
                "LDR     R3, =0xBBB08\n"
                "MOV     R1, #0x3E8\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFB1FB7C\n"
                "CMP     R0, #9\n"
                "BNE     loc_FFB8F1C0\n"
                "BL      sub_FFB91090\n"
                "LDR     R3, =0xBBC48\n"
                "LDR     R0, =0xFFB8F020\n"		// aJpegtimeout_5
                "B       loc_FFB8F1D8\n"
"loc_FFB8F1C0:\n"
								"LDR     R4, [SP,#0x24]\n"		// #0x60+var_3C
                "CMP     R4, #0\n"
                "BEQ     loc_FFB8F1E4\n"
                "BL      sub_FFB91090\n"
                "LDR     R3, =0xBBC48\n"
                "LDR     R0, =0xFFB8F02C\n"		// aJpegicerror_5
"loc_FFB8F1D8:\n"
                "STR     R11, [R3]\n"
                "BL      sub_FFB42B44\n"		// HardwareDefect
                "B       loc_FFB8F294\n"
"loc_FFB8F1E4:\n"
                "BL      sub_FFB93A28\n"
								"LDR     R0, [SP,#0x38]\n"		// #0x60+var_28
								"LDR     R1, [SP,#0x28]\n"		// #0x60+var_38
                "BL      sub_FFB90CE8\n"
                "LDR     R12, =0xBBC70\n"
                "LDR     R3, [R12]\n"
                "ADD     R3, R3, #1\n"
								"LDR     R0, [SP,#0x28]\n"		// #0x60+var_38
                "LDR     R1, =0xBBC90\n"
                "MOV     R2, R4\n"
                "STR     R3, [R12]\n"
                "BL      sub_FFAFE538_my\n"  //-------------->
"loc_FFB8F214:\n"
                "LDR     R4, =0xBBC74\n"
                "LDR     R2, =0xBBC9C\n"
                "LDR     R3, [R4]\n"
                "LDR     R1, [R2]\n"
                "LDR     R12, =0xBBC98\n"
                "ADD     R3, R3, #1\n"
                "MUL     R0, R1, R3\n"
                "LDR     R1, [R12]\n"
                "STR     R3, [R4]\n"
                "BL      sub_FF91E9AC\n"		// __udivsi3
                "LDR     R6, =0xBBC94\n"
                "MOV     R4, R0\n"
                "BL      sub_FFB910CC\n"
                "LDR     R3, [R6]\n"
                "CMP     R3, R4\n"
                "BNE     loc_FFB8F268\n"
                "LDR     R5, =0xBBC40\n"
                "LDR     R3, [R5]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FFB8F288\n"
                "B       loc_FFB8F26C\n"
"loc_FFB8F268:\n"
                "LDR     R5, =0xBBC40\n"
"loc_FFB8F26C:\n"
                "LDR     R2, =0xBBCD8\n"
                "MOV     R0, R4\n"
                "MOV     LR, PC\n"
                "LDR     PC, [R2]\n"
                "MOV     R3, #0\n"
                "STR     R3, [R5]\n"
                "STR     R4, [R6]\n"
"loc_FFB8F288:\n"
                "LDR     R7, =0xBBC3C\n"
                "MOV     R3, #0\n"
"loc_FFB8F290:\n"
                "STR     R3, [R7]\n"
"loc_FFB8F294:\n"
                "ADD     SP, SP, #0x3C\n"
                "LDMFD   SP!, {R4-R11,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFAFE538_my(){
 asm volatile(
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R12, =0x975B4\n"
                "LDR     R4, [R12]\n"
                "LDR     R3, =0x975BC\n"
                "CMP     R4, #0\n"
                "MOV     R8, R1\n"
                "MOV     R7, R0\n"
                "LDR     R1, [R3]\n"
                "BEQ     loc_FFAFE570\n"
                "LDR     R2, =0x975C0\n"
                "LDR     R3, [R2]\n"
                "CMP     R3, #1\n"
                "BNE     loc_FFAFE584\n"
                "B       loc_FFAFE574\n"
"loc_FFAFE570:\n"
                "LDR     R2, =0x975C0\n"
"loc_FFAFE574:\n"
                "MOV     R3, #0\n"
                "STR     R3, [R2]\n"
                "STR     R7, [R12]\n"
                "B       loc_FFAFE63C\n"
"loc_FFAFE584:\n"
                "LDR     R2, =0x975B8\n"
                "LDR     R3, [R2]\n"
                "LDR     R6, =table1\n"		// unk_FFAFE43C
                "ADD     R3, R3, R3,LSL#1\n"
                "MOV     LR, R3,LSL#2\n"
                "LDR     R2, [R6,LR]\n"
                "LDR     R5, =table2\n"		// unk_FFAFE460
                "RSB     R12, R2, R4\n"
                "LDR     R3, [R5,LR]\n"
                "CMP     R12, #0\n"
                "RSB     R0, R3, R4\n"
                "BLE     loc_FFAFE5E8\n"
                "ADD     R3, R6, #4\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R12\n"
                "ADDGE   R1, R1, #1\n"
                "BGE     loc_FFAFE5DC\n"
                "ADD     R3, R6, #8\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R12\n"
                "ADDGE   R1, R1, #2\n"
                "ADDLT   R1, R1, #3\n"
"loc_FFAFE5DC:\n"
             //	"CMP     R1, #0x16\n"
             // "MOVGE   R1, #0x16\n"
                "CMP     R1, #0x1A\n"     // + 
                "MOVGE   R1, #0x1A\n"     // +                 
                
                "B       loc_FFAFE620\n"
"loc_FFAFE5E8:\n"
                "CMP     R0, #0\n"
                "BGE     loc_FFAFE620\n"
                "ADD     R3, R5, #4\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R0\n"
                "SUBLE   R1, R1, #1\n"
                "BLE     loc_FFAFE618\n"
                "ADD     R3, R5, #8\n"
                "LDR     R2, [R3,LR]\n"
                "CMP     R2, R0\n"
                "SUBLE   R1, R1, #2\n"
                "SUBGT   R1, R1, #3\n"
"loc_FFAFE618:\n"
                "CMP     R1, #0\n"
                "MOVLT   R1, #0\n"
"loc_FFAFE620:\n"
                "LDR     R0, =0x975BC\n"
                "LDR     R3, [R0]\n"
                "CMP     R1, R3\n"
                "LDRNE   R2, =0x975C0\n"
                "MOVNE   R3, #1\n"
                "STRNE   R1, [R0]\n"
                "STRNE   R3, [R2]\n"
"loc_FFAFE63C:\n"
                "LDR     R3, =0x975BC\n"
                "LDR     R2, =CompressionRateTable\n"		// unk_FFAFE3E0
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
