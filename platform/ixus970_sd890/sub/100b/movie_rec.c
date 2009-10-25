#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table[68] = {
	0x2000,  0x38D,   0x788,   0xBE1,   0x10CB,  0x1642,  0x1C48,  0x22F9,  0x2A79,  0x32AA, 0x3C01, 0x4637,
	0x5190,  0x5E0E,  0x5800,  0x9C5,   0x14B8,  0x20C9,  0x2E31,  0x3D39,  0x4DC9,  0x6030, 0x74D1, 0x8B8D,
	0xA509,  0xC160,  0xE054,  0x102AF, 0x10000, 0x1C6A,  0x3C45,  0x5F60,  0x8661,  0xB21A, 0xE249, 0x117D2,
	0x153D5, 0x195F8, 0x1E01C, 0x2328E, 0x28C99, 0x2F08B, 0x8000,  0xE35,   0x1E23,  0x2FB0, 0x4331, 0x590D, 
	0x7125,  0x8BE9,  0xA9EB,  0xCAFC,  0xF00E,  0x11947, 0x1464D, 0x17846, 0x1CCD, -0x2E1,  -0x579, 0x4F33,
	-0x7EB, -0xF0C,   0xE666,  -0x170A, -0x2BC6, 0x7333,  -0xB85, -0x15E3};

long table[68];

void change_video_tables(int a, int b) {
	int i;

	for (i=0;i<68;i++) {
		table[i]=(def_table[i]*a)/b;
	}
}

long CompressionRateTable[] = {0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};

// Extracted method: sub_FF85A004
void __attribute__((naked,noinline)) movie_record_task()
{
	asm volatile (
		"STMFD   SP!, {R2-R8,LR}\n"
		"LDR     R8, =0x32B\n"
		"LDR     R7, =0x2710\n"
		"LDR     R4, =0x5390\n"
		"MOV     R6, #0\n"
		"MOV     R5, #1\n"

		"loc_FF85A01C:\n"
		"LDR     R0, [R4,#0x1C]\n"
		"MOV     R2, #0\n"
		"ADD     R1, SP, #0x20-0x1C\n"
		"BL      sub_FF827D90\n" // LOCATION: KerQueue.c:0
		"LDR     R0, [R4,#0x24]\n"
		"CMP     R0, #0\n"
		"BNE     loc_FF85A0EC\n"
		"LDR     R0, [SP,#0x20-0x1C]\n"
		"LDR     R1, [R0]\n"
		"SUB     R1, R1, #2\n"
		"CMP     R1, #9\n"
		"ADDLS   PC, PC, R1,LSL#2\n"
		"B       loc_FF85A0EC\n"

		"loc_FF85A050:\n"
		"B       loc_FF85A0A0\n"

		"loc_FF85A054:\n"
		"B       loc_FF85A0C0\n"

		"loc_FF85A058:\n"
		"B       loc_FF85A0D0\n"

		"loc_FF85A05C:\n"
		"B       loc_FF85A0D8\n"

		"loc_FF85A060:\n"
		"B       loc_FF85A0A8\n"

		"loc_FF85A064:\n"
		"B       loc_FF85A0E0\n"

		"loc_FF85A068:\n"
		"B       loc_FF85A0B0\n"

		"loc_FF85A06C:\n"
		"B       loc_FF85A0EC\n"

		"loc_FF85A070:\n"
		"B       loc_FF85A0E8\n"

		"loc_FF85A074:\n"
		"B       loc_FF85A078\n"

		"loc_FF85A078:\n"
		// jumptable FF85A048 entry 9
		"STR     R6, [R4,#0x38]\n"
		"LDR     R0, =0xFF859CD8\n" // nullsub_234
		"LDR     R2, =0xFF859608\n"
		"LDR     R1, =0x19B18\n"
		"STR     R0, [R4,#0xA4]\n"
		"LDR     R0, =0xFF8596EC\n"
		"STR     R6, [R4,#0x28]\n"
		"BL      sub_FF8C7F90\n"
		"STR     R5, [R4,#0x3C]\n"
		"B       loc_FF85A0EC\n"

		"loc_FF85A0A0:\n"
		// jumptable FF85A048 entry 0
		"BL      unlock_optical_zoom\n" //------------->
		"BL      sub_FF859DD0\n" // LOCATION: MovieRecorder.c:0
		"B       loc_FF85A0EC\n"

		"loc_FF85A0A8:\n"
		// jumptable FF85A048 entry 4
		"BL      sub_FF859A9C_my\n" //------------->
		"B       loc_FF85A0EC\n"

		"loc_FF85A0B0:\n"
		// jumptable FF85A048 entry 6
		"LDR     R1, [R0,#0x10]\n"
		"LDR     R0, [R0,#4]\n"
		"BL      sub_FF938D90\n" // LOCATION: AviWriter.c:0
		"B       loc_FF85A0EC\n"

		"loc_FF85A0C0:\n"
		// jumptable FF85A048 entry 1
		"LDR     R0, [R4,#0x3C]\n"
		"CMP     R0, #5\n"
		"STRNE   R5, [R4,#0x2C]\n"
		"B       loc_FF85A0EC\n"

		"loc_FF85A0D0:\n"
		// jumptable FF85A048 entry 2
		"BL      sub_FF8598A0\n" // LOCATION: MovieRecorder.c:1000
		"B       loc_FF85A0EC\n"

		"loc_FF85A0D8:\n"
		// jumptable FF85A048 entry 3
		"BL      sub_FF859738\n"
		"B       loc_FF85A0EC\n"

		"loc_FF85A0E0:\n"
		// jumptable FF85A048 entry 5
		"BL      sub_FF859594\n" // LOCATION: MovieRecorder.c:100
		"B       loc_FF85A0EC\n"

		"loc_FF85A0E8:\n"
		// jumptable FF85A048 entry 8
		"BL      sub_FF85A254\n" // LOCATION: MovieRecorder.c:100

		"loc_FF85A0EC:\n"
		// jumptable FF85A048 default entry
		// jumptable FF85A048 entry 7
		"LDR     R1, [SP,#0x20-0x1C]\n"
		"LDR     R3, =0xFF859398\n" // aMovierecorder_  ; "MovieRecorder.c"
		"STR     R6, [R1]\n"
		"STR     R8, [SP,#0x20-0x20]\n"
		"LDR     R0, [R4,#0x20]\n"
		"MOV     R2, R7\n"
		"BL      sub_FF81BC30\n"
		"B       loc_FF85A01C\n"
		);
}

void __attribute__((naked,noinline)) sub_FF859A9C_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R9,LR}\n"
		"SUB     SP, SP, #0x3C\n"
		"MOV     R7, #0\n"
		"LDR     R5, =0x5390\n"
		"MOV     R4, R0\n"
		"STR     R7, [SP,#0x58-0x2C]\n"
		"STR     R7, [SP,#0x58-0x34]\n"
		"LDR     R0, [R5,#0x3C]\n"
		"MOV     R8, #4\n"
		"CMP     R0, #3\n"
		"STREQ   R8, [R5,#0x3C]\n"
		"LDR     R0, [R5,#0xA4]\n"
		"MOV     R6, #0\n"
		"BLX     R0\n"
		"LDR     R0, [R5,#0x3C]\n"
		"CMP     R0, #4\n"
		"BNE     loc_FF859BAC\n"
		"LDRH    R0, [R5,#2]\n"
		"MOV     R9, #1\n"
		"CMP     R0, #1\n"
		"BNE     loc_FF859B18\n"
		"LDRH    R1, [R5,#4]\n"
		"LDR     R0, [R5,#0x4C]\n"
		"MUL     R0, R1, R0\n"
		"MOV     R1, #0x3E8\n"
		"BL      sub_FFAAF1AC\n"
		"MOV     R1, R0\n"
		"LDR     R0, [R5,#0x54]\n"
		"BL      sub_FFAAF1AC\n"
		"CMP     R1, #0\n"
		"BNE     loc_FF859B34\n"

		"loc_FF859B18:\n"
		"ADD     R3, SP, #0x58-0x34\n"
		"ADD     R2, SP, #0x58-0x30\n"
		"ADD     R1, SP, #0x58-0x2C\n"
		"ADD     R0, SP, #0x58-0x28\n"
		"BL      sub_FF938F24\n"
		"MOVS    R6, R0\n"
		"BNE     loc_FF859B50\n"

		"loc_FF859B34:\n"
		"LDR     R0, [R5,#0x2C]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FF859BB4\n"
		"LDR     R0, [R5,#0x54]\n"
		"LDR     R1, [R5,#0x40]\n"
		"CMP     R0, R1\n"
		"BCC     loc_FF859BB4\n"

		"loc_FF859B50:\n"
		"CMP     R6, #0x80000001\n"
		"STREQ   R8, [R5,#0x58]\n"
		"BEQ     loc_FF859B88\n"
		"CMP     R6, #0x80000003\n"
		"STREQ   R9, [R5,#0x58]\n"
		"BEQ     loc_FF859B88\n"
		"CMP     R6, #0x80000005\n"
		"MOVEQ   R0, #2\n"
		"BEQ     loc_FF859B84\n"
		"CMP     R6, #0x80000007\n"
		"STRNE   R7, [R5,#0x58]\n"
		"BNE     loc_FF859B88\n"
		"MOV     R0, #3\n"

		"loc_FF859B84:\n"
		"STR     R0, [R5,#0x58]\n"

		"loc_FF859B88:\n"
		"LDR     R0, =0x19B48\n"
		"LDR     R0, [R0,#8]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF859BA0\n"
		"BL      sub_FF84427C\n"
		"B       loc_FF859BA4\n"

		"loc_FF859BA0:\n"
		"BL      sub_FF859594\n" // LOCATION: MovieRecorder.c:100

		"loc_FF859BA4:\n"
		"MOV     R0, #5\n"
		"STR     R0, [R5,#0x3C]\n"

		"loc_FF859BAC:\n"
		"ADD     SP, SP, #0x3C\n"
		"LDMFD   SP!, {R4-R9,PC}\n"

		"loc_FF859BB4:\n"
		"LDR     R12, [SP,#0x58-0x2C]\n"
		"CMP     R12, #0\n"
		"BEQ     loc_FF859C80\n"
		"STR     R9, [R5,#0x30]\n"
		"LDR     R0, [R5,#0x70]\n"
		"LDR     R1, [R4,#0x14]\n"
		"LDR     R2, [R4,#0x18]\n"
		"LDR     LR, [R4,#0xC]\n"
		"ADD     R3, SP, #0x58-0x24\n"
		"ADD     R6, SP, #0x58-0x44\n"
		"STMIA   R6, {R0-R3}\n"
		"LDR     R0, [SP,#0x58-0x34]\n"
		"LDR     R3, [R5,#0x5C]\n"
		"LDR     R1, [SP,#0x58-0x30]\n"
		"ADD     R2, SP, #0x58-0x20\n"
		"ADD     R6, SP, #0x58-0x50\n"
		"STMIA   R6, {R0,R2,R3}\n"
		"STR     R1, [SP,#0x58-0x54]\n"
		"STR     R12, [SP,#0x58-0x58]\n"
		"LDMIB   R4, {R0,R1}\n"
		"LDR     R3, [SP,#0x58-0x28]\n"
		"MOV     R2, LR\n"
		"BL      sub_FF8EFE60\n"
		"LDR     R0, [R5,#0x14]\n"
		"MOV     R1, #0x3E8\n"
		"BL      sub_FF81B6AC\n" // eventproc_export_TakeSemaphore
		"CMP     R0, #9\n"
		"BNE     loc_FF859C34\n"
		"BL      sub_FF939500\n"
		"MOV     R0, #0x90000\n"
		"STR     R9, [R5,#0x3C]\n"
		"B       loc_FF859C4C\n"

		"loc_FF859C34:\n"
		"LDR     R0, [SP,#0x58-0x24]\n"
		"CMP     R0, #0\n"
		"BEQ     loc_FF859C54\n"
		"BL      sub_FF939500\n"
		"MOV     R0, #0xA0000\n"
		"STR     R9, [R5,#0x3C]\n"

		"loc_FF859C4C:\n"
		"BL      sub_FF875750\n" // eventproc_export_HardwareDefect
		"B       loc_FF859BAC\n"

		"loc_FF859C54:\n"
		"BL      sub_FF8EFF24\n"
		"LDR     R0, [SP,#0x58-0x28]\n"
		"LDR     R1, [SP,#0x58-0x20]\n"
		"BL      sub_FF9392A8\n" // LOCATION: AviWriter.c:0
		"LDR     R0, [R5,#0x50]\n"
		"LDR     R1, =0x5400\n"
		"ADD     R0, R0, #1\n"
		"STR     R0, [R5,#0x50]\n"
		"LDR     R0, [SP,#0x58-0x20]\n"
		"MOV     R2, #0\n"
		"BL      sub_FF937138_my\n" //------------->

		"loc_FF859C80:\n"
		"LDR     R0, [R5,#0x54]\n"
		"ADD     R0, R0, #1\n"
		"STR     R0, [R5,#0x54]\n"
		"LDR     R1, [R5,#0x7C]\n"
		"MUL     R0, R1, R0\n"
		"LDR     R1, [R5,#0x78]\n"
		"BL      sub_FFAAF1AC\n"
		"MOV     R4, R0\n"
		"BL      sub_FF939538\n"
		"LDR     R1, [R5,#0x74]\n"
		"CMP     R1, R4\n"
		"BNE     loc_FF859CBC\n"
		"LDR     R0, [R5,#0x34]\n"
		"CMP     R0, #1\n"
		"BNE     loc_FF859CD0\n"

		"loc_FF859CBC:\n"
		"LDR     R1, [R5,#0x88]\n"
		"MOV     R0, R4\n"
		"BLX     R1\n"
		"STR     R4, [R5,#0x74]\n"
		"STR     R7, [R5,#0x34]\n"

		"loc_FF859CD0:\n"
		"STR     R7, [R5,#0x30]\n"
		"B       loc_FF859BAC\n"
		);
}

void __attribute__((naked,noinline)) sub_FF937138_my()
{
	asm volatile (
		"STMFD   SP!, {R4-R8,LR}\n"
		"LDR     R4, =0x8C44\n"
		"LDR     LR, [R4]\n"
		"LDR     R2, [R4,#8]\n"
		"CMP     LR, #0\n"
		"LDRNE   R3, [R4,#0xC]\n"
		"MOV     R5, R2\n"
		"CMPNE   R3, #1\n"
		"MOVEQ   R2, #0\n"
		"STREQ   R0, [R4]\n"
		"STREQ   R2, [R4,#0xC]\n"
		"BEQ     loc_FF937204\n"
		"LDR     R3, [R4,#4]\n"
		//"LDR     R7, =0xFFACAD70\n"
		"LDR     R7, =table\n" // +
		"ADD     R12, R3, R3,LSL#1\n"
		"LDR     R3, [R7,R12,LSL#2]\n"
		"ADD     R6, R7, #0x30\n"
		"LDR     R8, [R6,R12,LSL#2]\n"
		"SUB     R3, LR, R3\n"
		"CMP     R3, #0\n"
		"SUB     LR, LR, R8\n"
		"BLE     loc_FF9371C0\n"
		"ADD     R12, R7, R12,LSL#2\n"
		"LDR     LR, [R12,#4]\n"
		"CMP     LR, R3\n"
		"ADDGE   R2, R2, #1\n"
		"BGE     loc_FF9371B4\n"
		"LDR     R12, [R12,#8]\n"
		"CMP     R12, R3\n"
		"ADDLT   R2, R2, #3\n"
		"ADDGE   R2, R2, #2\n"

		"loc_FF9371B4:\n"
		//"CMP     R2, #0x17\n"
		//"MOVGE   R2, #0x16\n"
		"CMP     R2, #0x1A\n" // +
		"MOVGE   R2, #0x19\n" // +
		"B       loc_FF9371F4\n"

		"loc_FF9371C0:\n"
		"CMP     LR, #0\n"
		"BGE     loc_FF9371F4\n"
		"ADD     R3, R6, R12,LSL#2\n"
		"LDR     R12, [R3,#4]\n"
		"CMP     R12, LR\n"
		"SUBLE   R2, R2, #1\n"
		"BLE     loc_FF9371EC\n"
		"LDR     R3, [R3,#8]\n"
		"CMP     R3, LR\n"
		"SUBGT   R2, R2, #3\n"
		"SUBLE   R2, R2, #2\n"

		"loc_FF9371EC:\n"
		"CMP     R2, #0\n"
		"MOVLT   R2, #0\n"

		"loc_FF9371F4:\n"
		"CMP     R2, R5\n"
		"STRNE   R2, [R4,#8]\n"
		"MOVNE   R2, #1\n"
		"STRNE   R2, [R4,#0xC]\n"

		"loc_FF937204:\n"
		//"LDR     R2, =0xFFACAD14\n"
		"LDR     R2, =CompressionRateTable\n" // +
		"LDR     R3, [R4,#8]\n"
		"LDR     R2, [R2,R3,LSL#2]\n"

		"LDR     R3, =video_mode\n" // +
		"LDR     R3, [R3]\n" // +
		"LDR     R3, [R3]\n" // +
		"CMP     R3, #1\n" // +
		"LDREQ   R3, =video_quality\n" // +
		"LDREQ   R3, [R3]\n" // +
		"LDREQ   R2, [R3]\n" // +

		"STR     R2, [R1]\n"
		"STR     R0, [R4]\n"
		"LDMFD   SP!, {R4-R8,PC}\n"
		);
}
