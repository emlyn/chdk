#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x9B40;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) hangdebug() {
	debug_led(1);
	while(1);
}


void __attribute__((naked,noinline)) capt_seq_task() {
 asm volatile (
//capt_seq_task                           // DATA XREF: sub_FF868F90+78 o
                "STMFD   SP!, {R3-R9,LR}\n"
                "LDR     R6, =0x5584\n"
                "LDR     R4, =0x1BE24\n"
                "MOV     R9, #1\n"
                "MOV     R7, #0\n"
"loc_FF868C4C:\n"                            // CODE XREF: capt_seq_task+354 j
                "LDR     R0, [R6,#0x14]\n"
                "MOV     R2, #0\n"
                "MOV     R1, SP\n"
                "BL      sub_FF8274FC\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF868C78\n"
                "LDR     R1, =0x539\n"
                "LDR     R0, =0xFF8683DC\n"
                "BL      sub_FF81B1CC\n"
                "BL      sub_FF81B184\n"
                "LDMFD   SP!, {R3-R9,PC}\n"
// ---------------------------------------------------------------------------
"loc_FF868C78:\n"                            // CODE XREF: capt_seq_task+28 j
                "LDR     R0, [SP]\n"
                "LDR     R1, [R0]\n"
                "CMP     R1, #0x24\n"
                "ADDLS   PC, PC, R1,LSL#2\n"
                "B       loc_FF868F54\n"
"loc_FF868C8C:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868D20\n"
"loc_FF868C90:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868D8C\n"
"loc_FF868C94:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868D94\n"
"loc_FF868C98:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868DB8\n"
"loc_FF868C9C:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868DAC\n"
"loc_FF868CA0:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868DC0\n"
"loc_FF868CA4:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868DC8\n"
"loc_FF868CA8:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868DD0\n"
"loc_FF868CAC:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E28\n"
"loc_FF868CB0:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E50\n"
"loc_FF868CB4:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E34\n"
"loc_FF868CB8:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E40\n"
"loc_FF868CBC:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E48\n"
"loc_FF868CC0:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E58\n"
"loc_FF868CC4:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E60\n"
"loc_FF868CC8:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E68\n"
"loc_FF868CCC:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E70\n"
"loc_FF868CD0:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E78\n"
"loc_FF868CD4:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E80\n"
"loc_FF868CD8:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E88\n"
"loc_FF868CDC:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E90\n"
"loc_FF868CE0:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868E98\n"
"loc_FF868CE4:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868EA0\n"
"loc_FF868CE8:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868EA8\n"
"loc_FF868CEC:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868EB0\n"
"loc_FF868CF0:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868EBC\n"
"loc_FF868CF4:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868EC4\n"
"loc_FF868CF8:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868ED0\n"
"loc_FF868CFC:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868ED8\n"
"loc_FF868D00:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F08\n"
"loc_FF868D04:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F10\n"
"loc_FF868D08:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F18\n"
"loc_FF868D0C:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F20\n"
"loc_FF868D10:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F28\n"
"loc_FF868D14:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F30\n"
"loc_FF868D18:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F3C\n"
"loc_FF868D1C:\n"                            // CODE XREF: capt_seq_task+4C j
                "B       loc_FF868F60\n"
"loc_FF868D20:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868C8C j
// jumptable FF868C84 entry 0
                "BL      sub_FF869560\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF8665F0\n"

 //  this code added to avoid some incorrect behavior if overrides are used.
 //  but it can cause some unexpected side effects. In this case, remove this code!

                 "MOV     R0, #0\n"
                 "STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press
 	
 //  end of my code


                "LDR     R0, [R4,#0x24]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FF868F60\n"
                "BL      sub_FF8680AC\n"
                "MOV     R5, R0\n"
                "LDR     R0, [R4,#0x24]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FF868D68\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FF86D1F0\n"
                "TST     R0, #1\n"
                "STRNE   R9, [R6,#4]\n"
                "LDRNE   R0, [R5,#8]\n"
                "ORRNE   R0, R0, #0x40000000\n"
                "STRNE   R0, [R5,#8]\n"
                "BNE     loc_FF868F60\n"
"loc_FF868D68:\n"                            // CODE XREF: capt_seq_task+10C j
                "MOV     R0, R5\n"
                "BL      sub_FF94C32C\n"
                "MOV     R0, R5\n"
                "BL      sub_FF86848C\n"
                "MOV     R0, R5\n"

                "BL      sub_FF94CA04_my\n"		// ----------->
                "BL      capt_seq_hook_raw_here\n"      // +


                "TST     R0, #1\n"
                "STRNE   R9, [R6,#4]\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868D8C:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868C90 j
// jumptable FF868C84 entry 1
                "BL      sub_FF868504_my\n"		// ----------->
                "B       loc_FF868DB0\n"
// ---------------------------------------------------------------------------
"loc_FF868D94:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868C94 j
// jumptable FF868C84 entry 2
                "MOV     R0, #1\n"
                "BL      sub_FF8697D4\n"
                "LDR     R0, [R4,#0xC]\n"
                "CMP     R0, #0\n"
                "BLNE    sub_FF86A2D8\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868DAC:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868C9C j
// jumptable FF868C84 entry 4
                "BL      sub_FF86922C\n"
"loc_FF868DB0:\n"                            // CODE XREF: capt_seq_task+158 j
                                        // capt_seq_task+184 j
                "STR     R7, [R4,#0x24]\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868DB8:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868C98 j
// jumptable FF868C84 entry 3
                "BL      sub_FF869540\n"
                "B       loc_FF868DB0\n"
// ---------------------------------------------------------------------------
"loc_FF868DC0:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CA0 j
// jumptable FF868C84 entry 5
                "BL      sub_FF869548\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868DC8:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CA4 j
// jumptable FF868C84 entry 6
                "BL      sub_FF8696C4\n"
                "B       loc_FF868E2C\n"
// ---------------------------------------------------------------------------
"loc_FF868DD0:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CA8 j
// jumptable FF868C84 entry 7
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FF869550\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94B310\n"
                "TST     R0, #1\n"
                "MOV     R8, R0\n"
                "BNE     loc_FF868E10\n"
                "BL      sub_FF879908\n"
                "STR     R0, [R5,#0x18]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94C8C0\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94CCCC\n"
                "MOV     R8, R0\n"
                "LDR     R0, [R5,#0x18]\n"
                "BL      sub_FF879B1C\n"
"loc_FF868E10:\n"                            // CODE XREF: capt_seq_task+1B0 j
                "BL      sub_FF869540\n"
                "MOV     R2, R5\n"
                "MOV     R1, #9\n"
                "MOV     R0, R8\n"
                "BL      sub_FF866B7C\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E28:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CAC j
// jumptable FF868C84 entry 8
                "BL      sub_FF869754\n"
"loc_FF868E2C:\n"                            // CODE XREF: capt_seq_task+194 j
                "BL      sub_FF8665F0\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E34:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CB4 j
// jumptable FF868C84 entry 10
                "LDR     R0, [R4,#0x54]\n"
                "BL      sub_FF869DEC\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E40:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CB8 j
// jumptable FF868C84 entry 11
                "BL      sub_FF86A098\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E48:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CBC j
// jumptable FF868C84 entry 12
                "BL      sub_FF86A128\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E50:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CB0 j
// jumptable FF868C84 entry 9
                "BL      sub_FF869540\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E58:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CC0 j
// jumptable FF868C84 entry 13
                "BL      sub_FF94B550\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E60:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CC4 j
// jumptable FF868C84 entry 14
                "BL      sub_FF94B77C\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E68:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CC8 j
// jumptable FF868C84 entry 15
                "BL      sub_FF94B810\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E70:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CCC j
// jumptable FF868C84 entry 16
                "BL      sub_FF94B938\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E78:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CD0 j
// jumptable FF868C84 entry 17
                "BL      sub_FF94B9EC\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E80:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CD4 j
// jumptable FF868C84 entry 18
                "BL      sub_FF94BE7C\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E88:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CD8 j
// jumptable FF868C84 entry 19
                "BL      sub_FF94BED4\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868E90:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CDC j
// jumptable FF868C84 entry 20
                "MOV     R0, #0\n"
                "B       loc_FF868EB4\n"
// ---------------------------------------------------------------------------
"loc_FF868E98:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CE0 j
// jumptable FF868C84 entry 21
                "BL      sub_FF94C070\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868EA0:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CE4 j
// jumptable FF868C84 entry 22
                "BL      sub_FF94C100\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868EA8:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CE8 j
// jumptable FF868C84 entry 23
                "BL      sub_FF94C1C0\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868EB0:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CEC j
// jumptable FF868C84 entry 24
                "MOV     R0, #1\n"
"loc_FF868EB4:\n"                            // CODE XREF: capt_seq_task+25C j
                "BL      sub_FF94BF48\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868EBC:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CF0 j
// jumptable FF868C84 entry 25
                "BL      sub_FF869A0C\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868EC4:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CF4 j
// jumptable FF868C84 entry 26
                "BL      sub_FF869AAC\n"
                "BL      sub_FF869088\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868ED0:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CF8 j
// jumptable FF868C84 entry 27
                "BL      sub_FF94BCA4\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868ED8:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868CFC j
// jumptable FF868C84 entry 28
                "MOV     R2, #2\n"
                "ADD     R1, R4, #0x74\n"
                "MOV     R0, #0x6F\n"
                "BL      sub_FF879778\n"
                "TST     R0, #1\n"
                "LDRNE   R1, =0x61C\n"
                "LDRNE   R0, =0xFF8683DC\n"
                "BLNE    sub_FF81B1CC\n"
                "LDRH    R0, [R4,#0x74]\n"
                "CMP     R0, #1\n"
                "BLEQ    sub_FF94BC98\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F08:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D00 j
// jumptable FF868C84 entry 29
                "BL      sub_FF94BDD0\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F10:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D04 j
// jumptable FF868C84 entry 30
                "BL      sub_FF86836C\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F18:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D08 j
// jumptable FF868C84 entry 31
                "BL      sub_FF824960\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F20:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D0C j
// jumptable FF868C84 entry 32
                "BL      sub_FF86B930\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F28:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D10 j
// jumptable FF868C84 entry 33
                "BL      sub_FF86B998\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F30:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D14 j
// jumptable FF868C84 entry 34
                "BL      sub_FF86B9F4\n"
                "BL      sub_FF86B9B4\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F3C:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D18 j
// jumptable FF868C84 entry 35
                "MOV     R0, #1\n"
                "BL      sub_FF94D4D0\n"
                "LDRH    R0, [R4,#0xA0]\n"
                "CMP     R0, #3\n"
                "BLNE    sub_FF86BBB0\n"
                "B       loc_FF868F60\n"
// ---------------------------------------------------------------------------
"loc_FF868F54:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task+50 j
// jumptable FF868C84 default entry
                "LDR     R1, =0x65E\n"
                "LDR     R0, =0xFF8683DC\n"
                "BL      sub_FF81B1CC\n"
"loc_FF868F60:\n"                            // CODE XREF: capt_seq_task+4C j
                                        // capt_seq_task:loc_FF868D1C j ...
// jumptable FF868C84 entry 36
                "LDR     R0, [SP]\n"
                "LDR     R1, [R0,#4]\n"
                "LDR     R0, [R6,#0x10]\n"
                "BL      sub_FF8714A4\n"
                "LDR     R5, [SP]\n"
                "LDR     R0, [R5,#8]\n"
                "CMP     R0, #0\n"
                "LDREQ   R1, =0x11D\n"
                "LDREQ   R0, =0xFF8683DC\n"
                "BLEQ    sub_FF81B1CC\n"
                "STR     R7, [R5,#8]\n"
                "B       loc_FF868C4C\n"
// End of function capt_seq_task

);

} 





void __attribute__((naked,noinline)) sub_FF94CA04_my(){
 asm volatile(
		"STMFD	SP!, {R1-R7,LR}\n"
		"MOV	R4, R0\n"
		"BL	sub_FF94D640\n"
                "MVN    R1, #0\n"
		"BL	sub_FF8714D8\n"
		"MOV	R2, #4\n"
		"ADD	R1, SP,	#4\n"
		"MOV	R0, #0x8A\n"
		"BL	sub_FF879778\n"
		"TST	R0, #1\n"
		"LDRNE	R1, =0x373\n"
		"LDRNE	R0, =0xFF94C9D0\n"	// "SsCaptureSeq.c"\n"
		"BLNE	sub_FF81B1CC\n"
		"LDR	R7, =0x1BEF8\n"
		"LDR	R6, =0x1BE24\n"
		"LDRSH	R1, [R7,#0xE]\n"
		"LDR	R0, [R6,#0x9C]\n"
		"BL	sub_FF90B0AC\n"
		"BL	sub_FF84E5F0\n"
		"LDR	R3, =0x9B44\n"
		"STRH	R0, [R4,#0x94]\n"
		"STR	R3, [SP]\n"
		"MOV	R1, R0\n"
		"LDRH	R0, [R6,#0x70]\n"
		"LDRSH	R2, [R7,#0xC]\n"
		"SUB	R3, R3,	#4\n"
		"BL	sub_FF94DC64\n"
                "BL     wait_until_remote_button_is_released\n"
                "BL     capt_seq_hook_set_nr\n"                     // +
                "B      sub_FF94CA70\n"                             // continue function in firmware
 );
}







void __attribute__((naked,noinline)) sub_FF868504_my(){
 asm volatile(
		"STMFD	SP!, {R3-R9,LR}\n"
		"LDR	R4, [R0,#0xC]\n"
		"LDR	R5, =0x1BE24\n"
		"LDR	R0, [R4,#8]\n"
		"LDR	R6, =0x820A\n"
		"ORR	R0, R0,	#1\n"
		"STR	R0, [R4,#8]\n"
		"LDRH	R0, [R5]\n"
		"LDR	R8, =0x5584\n"
		"MOV	R7, #0\n"
		"CMP	R0, R6\n"
		"BEQ	loc_FF8685A8\n"
		"LDRH	R0, [R5,#0xA6]\n"
		"CMP	R0, #3\n"
		"BEQ	loc_FF868608\n"
		"LDR	R0, [R4,#0xC]\n"
		"CMP	R0, #1\n"
		"BLS	loc_FF8685B4\n"
		"LDRH	R0, [R5,#0xA4]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF868608\n"
		"LDRH	R0, [R5,#0xA0]\n"
		"CMP	R0, #2\n"
		"BNE	loc_FF8685C0\n"
		"BL	sub_FF869B5C\n"
		"LDRH	R0, [R5]\n"
		"CMP	R0, R6\n"
		"BEQ	loc_FF8685A8\n"
		"LDRH	R0, [R5,#0xA6]\n"
		"CMP	R0, #3\n"
		"BEQ	loc_FF868608\n"
		"LDR	R0, [R4,#0xC]\n"
		"CMP	R0, #1\n"
		"BLS	loc_FF8685B4\n"
		"LDRH	R0, [R5,#0xA4]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF868608\n"
		"LDRH	R0, [R5,#0xA0]\n"
		"CMP	R0, #2\n"
		"BEQ	loc_FF8685EC\n"
		"B	loc_FF8685C0\n"
// ---------------------------------------------------------------------------

"loc_FF8685A8:\n"				// CODE XREF: sub_FF868504+2Cj
//					// sub_FF868504+6Cj
		"LDRH	R0, [R5,#0xA6]\n"
		"CMP	R0, #3\n"
		"BEQ	loc_FF868608\n"

"loc_FF8685B4:\n"				// CODE XREF: sub_FF868504+44j
//					// sub_FF868504+84j
		"LDRH	R0, [R5,#0xA4]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF868608\n"

"loc_FF8685C0:\n"				// CODE XREF: sub_FF868504+5Cj
//					// sub_FF868504+A0j
		"LDRH	R0, [R5,#0xA0]\n"
		"CMP	R0, #1\n"
		"BNE	loc_FF868608\n"
		"LDRH	R0, [R5]\n"
		"CMP	R0, R6\n"
		"LDRNE	R0, [R4,#0xC]\n"
		"CMPNE	R0, #1\n"
		"BLS	loc_FF868608\n"
		"LDR	R0, [R4,#0x10]\n"
		"CMP	R0, #1\n"
		"BNE	loc_FF868608\n"

"loc_FF8685EC:\n"				// CODE XREF: sub_FF868504+9Cj
		"LDR	R3, =0x24D\n"
		"LDR	R2, =0xEA60\n"
		"STR	R3, [SP]\n"
		"LDR	R0, [R8,#0x10]\n"
		"LDR	R3, =0xFF8683DC\n"	// "SsShootTask.c"\n"
		"MOV	R1, #0x40000000\n"
		"BL	sub_FF86D574\n"

"loc_FF868608:\n"				// CODE XREF: sub_FF868504+38j
//					// sub_FF868504+50j ...
		"BL	sub_FF86836C\n"
		"LDR	R0, [R5,#0x24]\n"
		"CMP	R0, #0\n"
		"MOVEQ	R0, #2\n"
		"BLEQ	sub_FF861ADC\n"
		"BL	sub_FF869550\n"
		"LDR	R0, [R5,#0x24]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FF8686C0\n"
		"MOV	R0, #0\n"
		"BL	sub_FF94D4D0\n"
		"MOV	R0, R4\n"
		"BL	sub_FF94C32C\n"
		"MOV	R0, R4\n"
		"BL	sub_FF869974\n"
		"MOV	R0, R4\n"
		"BL	sub_FF94AEB4\n"
		"CMP	R0, #0\n"
		"BEQ	loc_FF868678\n"
		"BL	sub_FF94D510\n"
		"MOV	R0, R4\n"
		"BL	sub_FF94B078\n"
		"TST	R0, #1\n"
		"MOVNE	R2, R4\n"
		"LDMNEFD	SP!, {R3-R9,LR}\n"
		"MOVNE	R1, #1\n"
		"BNE	sub_FF866B7C\n"
		"B	loc_FF86869C\n"
// ---------------------------------------------------------------------------

"loc_FF868678:\n"				// CODE XREF: sub_FF868504+14Cj
		"LDR	R0, [R5,#0xC]\n"
		"CMP	R0, #0\n"
		"BEQ	loc_FF868690\n"
		"BL	sub_FF86A260\n"
		"BL	sub_FF900338\n"
		"BL	sub_FF863254\n"

"loc_FF868690:\n"				// CODE XREF: sub_FF868504+17Cj
		"MOV	R0, R4\n"
		"BL	sub_FF94AFAC\n"
		"BL	sub_FF94D510\n"

"loc_FF86869C:\n"				// CODE XREF: sub_FF868504+170j
		"MOV	R0, R4\n"
		"BL	sub_FF86848C\n"
		"MOV	R0, R4\n"
		"BL	sub_FF94C8C0\n"
		"BL	sub_FF94D360\n"
		"MOV	R0, R4\n"
                "BL     sub_FF94CA04_my\n"             //----------->
		"MOV	R7, R0\n"
                "BL     capt_seq_hook_raw_here\n"      // +
		"B	loc_FF8686CC\n"
// ---------------------------------------------------------------------------

"loc_FF8686C0:\n"				// CODE XREF: sub_FF868504+124j
		"LDR	R0, [R8,#4]\n"
		"CMP	R0, #0\n"
		"MOVNE	R7, #0x1D\n"

"loc_FF8686CC:\n"				// CODE XREF: sub_FF868504+1B8j
		"BL	sub_FF86B998\n"
		"BL	sub_FF86B9E0\n"
		"BL	sub_FF86BA20\n"
		"MOV	R2, R4\n"
		"MOV	R1, #1\n"
		"MOV	R0, R7\n"
		"BL	sub_FF866B7C\n"
		"BL	sub_FF94CC5C\n"
		"CMP	R0, #0\n"
		"LDRNE	R0, [R4,#8]\n"
		"ORRNE	R0, R0,	#0x2000\n"
		"STRNE	R0, [R4,#8]\n"
		"LDR	R0, [R4,#0x1C]\n"
		"CMP	R0, #0\n"
		"BLNE	sub_FF86326C\n"
		"LDRH	R0, [R5,#0xA6]\n"
		"CMP	R0, #3\n"
		"BEQ	loc_FF868730\n"
		"LDRH	R0, [R5,#0xA4]\n"
		"CMP	R0, #0\n"
		"LDREQH	R0, [R5,#0xA0]\n"
		"CMPEQ	R0, #2\n"
		"MOVEQ	R0, R4\n"
		"LDMEQFD	SP!, {R3-R9,LR}\n"
		"BEQ	sub_FF869BB0\n"

"loc_FF868730:\n"				// CODE XREF: sub_FF868504+20Cj
		"LDMFD	SP!, {R3-R9,PC}\n"
// End of function sub_FF868504
 );
}












/*************************************************************/
void __attribute__((naked,noinline)) exp_drv_task(){
 asm volatile(
		"STMFD   SP!, {R4-R8,LR}\n"
		"SUB     SP, SP, #0x20\n"
		"LDR	R8, =0xBB8\n"
		"LDR	R7, =0x6EE4\n"
		"LDR	R5, =0x210F0\n"
		"MOV	R0, #0\n"
		"ADD	R6, SP,	#0x10\n"
		"STR	R0, [SP,#0x0C]\n"

"loc_FF8AD88C:\n"				// CODE XREF: exp_drv_task+5ACj
		"LDR	R0, [R7,#0x20]\n"
		"MOV	R2, #0\n"
		"ADD	R1, SP,	#0x1C\n"
		"BL	sub_FF8274FC\n"
		"LDR	R0, [SP,#0x0C]\n"
		"CMP	R0, #1\n"
		"BNE	loc_FF8AD8D4\n"
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R0, [R0]\n"
		"CMP	R0, #0x13\n"
		"CMPNE	R0, #0x14\n"
		"CMPNE	R0, #0x15\n"
		"BEQ	loc_FF8AD9F0\n"
		"CMP	R0, #0x27\n"
		"BEQ	loc_FF8AD9C8\n"
		"ADD	R1, SP,	#0x0C\n"
		"MOV	R0, #0\n"
		"BL	sub_FF8AD7E0\n"

"loc_FF8AD8D4:\n"				// CODE XREF: exp_drv_task+38j
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R1, [R0]\n"
		"CMP	R1, #0x2C\n"
		"BNE	loc_FF8AD904\n"
		"LDR	R0, [SP,#0x1C]\n"
		"BL	sub_FF8AEABC\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R1, #1\n"
		"BL	sub_FF8714A4\n"
		"BL	sub_FF81B184\n"
		"ADD	SP, SP,	#0x20\n"
		"LDMFD	SP!, {R4-R8,PC}\n"
// ---------------------------------------------------------------------------

"loc_FF8AD904:\n"				// CODE XREF: exp_drv_task+74j
		"CMP	R1, #0x2B\n"
		"BNE	loc_FF8AD920\n"
		"LDR	R2, [R0,#0x88]!\n"
		"LDR	R1, [R0,#4]\n"
		"MOV	R0, R1\n"
		"BLX	R2\n"
		"B	loc_FF8ADE10\n"
// ---------------------------------------------------------------------------

"loc_FF8AD920:\n"				// CODE XREF: exp_drv_task+9Cj
		"CMP	R1, #0x25\n"
		"BNE	loc_FF8AD970\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R1, #0x80\n"
		"BL	sub_FF8714D8\n"
		"LDR	R0, =0xFF8AA2A4\n"
		"MOV	R1, #0x80\n"
		"BL	sub_FF93B0F8\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R2, R8\n"
		"MOV	R1, #0x80\n"
		"BL	sub_FF8713E4\n"
		"TST	R0, #1\n"
		"LDRNE	R1, =0xD36\n"
		"BNE	loc_FF8AD9B4\n"

"loc_FF8AD95C:\n"				// CODE XREF: exp_drv_task+140j
//					// exp_drv_task+150j ...
		"LDR	R1, [SP,#0x1C]\n"
		"LDR	R0, [R1,#0x8C]\n"
		"LDR	R1, [R1,#0x88]\n"
		"BLX	R1\n"
		"B	loc_FF8ADE10\n"
// ---------------------------------------------------------------------------

"loc_FF8AD970:\n"				// CODE XREF: exp_drv_task+B8j
		"CMP	R1, #0x26\n"
		"BNE	loc_FF8AD9C0\n"
		"ADD	R1, SP,	#0x0C\n"
		"BL	sub_FF8AD7E0\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R1, #0x100\n"
		"BL	sub_FF8714D8\n"
		"LDR	R0, =0xFF8AA2B4\n"
		"MOV	R1, #0x100\n"
		"BL	sub_FF93BA84\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R2, R8\n"
		"MOV	R1, #0x100\n"
		"BL	sub_FF8713E4\n"
		"TST	R0, #1\n"
		"BEQ	loc_FF8AD95C\n"
		"MOV	R1, #0xD40\n"

"loc_FF8AD9B4:\n"				// CODE XREF: exp_drv_task+ECj
		"LDR	R0, =0xFF8AA9AC\n"
		"BL	sub_FF81B1CC\n"
		"B	loc_FF8AD95C\n"
// ---------------------------------------------------------------------------

"loc_FF8AD9C0:\n"				// CODE XREF: exp_drv_task+108j
		"CMP	R1, #0x27\n"
		"BNE	loc_FF8AD9D8\n"

"loc_FF8AD9C8:\n"				// CODE XREF: exp_drv_task+58j
		"LDR	R0, [SP,#0x1C]\n"
		"ADD	R1, SP,	#0x0C\n"
		"BL	sub_FF8AD7E0\n"
		"B	loc_FF8AD95C\n"
// ---------------------------------------------------------------------------

"loc_FF8AD9D8:\n"				// CODE XREF: exp_drv_task+158j
		"CMP	R1, #0x2A\n"
		"BNE	loc_FF8AD9F0\n"
		"BL	sub_FF89D3DC\n"
		"BL	sub_FF89E068\n"
		"BL	sub_FF89DBA0\n"
		"B	loc_FF8AD95C\n"
// ---------------------------------------------------------------------------

"loc_FF8AD9F0:\n"				// CODE XREF: exp_drv_task+50j
//					// exp_drv_task+170j
		"LDR	R0, [SP,#0x1C]\n"
		"MOV	R4, #1\n"
		"LDR	R1, [R0]\n"
		"CMP	R1, #0x11\n"
		"CMPNE	R1, #0x12\n"
		"BNE	loc_FF8ADA60\n"
		"LDR	R1, [R0,#0x7C]\n"
		"ADD	R1, R1,	R1,LSL#1\n"
		"ADD	R1, R0,	R1,LSL#2\n"
		"SUB	R1, R1,	#8\n"
		"LDMIA	R1, {R2-R4}\n"
		"STMIA	R6, {R2-R4}\n"
		"BL	sub_FF8AC354\n"
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R1, [R0,#0x7C]\n"
		"LDR	R3, [R0,#0x88]\n"
		"LDR	R2, [R0,#0x8C]\n"
		"ADD	R0, R0,	#4\n"
		"BLX	R3\n"
		"LDR	R0, [SP,#0x1C]\n"
		"BL	sub_FF8AEE70\n"
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R1, [R0,#0x7C]\n"
		"LDR	R3, [R0,#0x90]\n"
		"LDR	R2, [R0,#0x94]\n"
		"ADD	R0, R0,	#4\n"
		"BLX	R3\n"
		"B	loc_FF8ADD50\n"
// ---------------------------------------------------------------------------

"loc_FF8ADA60:\n"				// CODE XREF: exp_drv_task+198j
		"CMP	R1, #0x13\n"
		"CMPNE	R1, #0x14\n"
		"CMPNE	R1, #0x15\n"
		"BNE	loc_FF8ADB14\n"
		"ADD	R3, SP,	#0x0C\n"
		"MOV	R2, SP\n"
		"ADD	R1, SP,	#0x10\n"
		"BL	sub_FF8AC59C\n"
		"CMP	R0, #1\n"
		"MOV	R4, R0\n"
		"CMPNE	R4, #5\n"
		"BNE	loc_FF8ADAB0\n"
		"LDR	R0, [SP,#0x1C]\n"
		"MOV	R2, R4\n"
		"LDR	R1, [R0,#0x7C]!\n"
		"LDR	R12, [R0,#0xC]!\n"
		"LDR	R3, [R0,#4]\n"
		"MOV	R0, SP\n"
		"BLX	R12\n"
		"B	loc_FF8ADAE8\n"
// ---------------------------------------------------------------------------

"loc_FF8ADAB0:\n"				// CODE XREF: exp_drv_task+220j
		"LDR	R0, [SP,#0x1C]\n"
		"CMP	R4, #2\n"
		"LDR	R3, [R0,#0x8C]\n"
		"CMPNE	R4, #6\n"
		"BNE	loc_FF8ADAFC\n"
		"LDR	R12, [R0,#0x88]\n"
		"MOV	R0, SP\n"
		"MOV	R2, R4\n"
		"MOV	R1, #1\n"
		"BLX	R12\n"
		"LDR	R0, [SP,#0x1C]\n"
		"MOV	R2, SP\n"
		"ADD	R1, SP,	#0x10\n"
		"BL	sub_FF8AD52C\n"

"loc_FF8ADAE8:\n"				// CODE XREF: exp_drv_task+240j
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R2, [SP,#0x0C]\n"
		"MOV	R1, R4\n"
		"BL	sub_FF8AD780\n"
		"B	loc_FF8ADD50\n"
// ---------------------------------------------------------------------------

"loc_FF8ADAFC:\n"				// CODE XREF: exp_drv_task+254j
		"LDR	R1, [R0,#0x7C]\n"
		"LDR	R12, [R0,#0x88]\n"
		"ADD	R0, R0,	#4\n"
		"MOV	R2, R4\n"
		"BLX	R12\n"
		"B	loc_FF8ADD50\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB14:\n"				// CODE XREF: exp_drv_task+200j
		"CMP	R1, #0x21\n"
		"CMPNE	R1, #0x22\n"
		"BNE	loc_FF8ADB60\n"
		"LDR	R1, [R0,#0x7C]\n"
		"ADD	R1, R1,	R1,LSL#1\n"
		"ADD	R1, R0,	R1,LSL#2\n"
		"SUB	R1, R1,	#8\n"
		"LDMIA	R1, {R2-R4}\n"
		"STMIA	R6, {R2-R4}\n"
		"BL	sub_FF8AB8D4\n"
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R1, [R0,#0x7C]\n"
		"LDR	R3, [R0,#0x88]\n"
		"LDR	R2, [R0,#0x8C]\n"
		"ADD	R0, R0,	#4\n"
		"BLX	R3\n"
		"LDR	R0, [SP,#0x1C]\n"
		"BL	sub_FF8ABBD0\n"
		"B	loc_FF8ADD50\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB60:\n"				// CODE XREF: exp_drv_task+2B0j
		"ADD	R1, R0,	#4\n"
		"LDMIA	R1, {R2,R3,R12}\n"
		"STMIA	R6, {R2,R3,R12}\n"
		"LDR	R1, [R0]\n"
		"CMP	R1, #0x24\n"
		"ADDLS	PC, PC,	R1,LSL#2\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB7C:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC10\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB80:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC10\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB84:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC18\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB88:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC20\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB8C:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC20\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB90:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC20\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB94:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC10\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB98:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC18\n"
// ---------------------------------------------------------------------------

"loc_FF8ADB9C:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC20\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBA0:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC20\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBA4:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC38\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBA8:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC38\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBAC:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD24\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBB0:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD2C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBB4:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD2C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBB8:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD2C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBBC:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD2C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBC0:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBC4:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBC8:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBCC:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBD0:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBD4:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC28\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBD8:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBDC:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBE0:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC44\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBE4:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC44\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBE8:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC4C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBEC:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADC7C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBF0:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADCAC\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBF4:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADCDC\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBF8:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD0C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADBFC:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD0C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC00:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC04:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC08:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD14\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC0C:\n"				// CODE XREF: exp_drv_task+308j
		"B	loc_FF8ADD1C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC10:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADB7Cj ...
// jumptable FF8ADB74 entries 0,1,6
		"BL	sub_FF8AA798\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC18:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADB84j ...
// jumptable FF8ADB74 entries 2,7
		"BL	sub_FF8AAA20\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC20:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADB88j ...
// jumptable FF8ADB74 entries 3-5,8,9
		"BL	sub_FF8AAC24\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC28:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBD4j
// jumptable FF8ADB74 entry 22
		"BL	sub_FF8AAE8C\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC30:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBD8j ...
// jumptable FF8ADB74 entries 23,24
		"BL	sub_FF8AB080\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC38:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBA4j ...
// jumptable FF8ADB74 entries 10,11
                "BL     sub_FF8AB2E8_my\n"  //------------>
		"MOV	R4, #0\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC44:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBE0j ...
// jumptable FF8ADB74 entries 25,26
		"BL	sub_FF8AB424\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC4C:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBE8j
// jumptable FF8ADB74 entry 27
		"LDRH	R1, [R0,#4]\n"
		"STRH	R1, [SP,#0x10]\n"
		"LDRH	R1, [R5,#2]\n"
		"STRH	R1, [SP,#0x12]\n"
		"LDRH	R1, [R5,#4]\n"
		"STRH	R1, [SP,#0x14]\n"
		"LDRH	R1, [R5,#6]\n"
		"STRH	R1, [SP,#0x16]\n"
		"LDRH	R1, [R0,#0xC]\n"
		"STRH	R1, [SP,#0x18]\n"
		"BL	sub_FF8AEB30\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADC7C:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBECj
// jumptable FF8ADB74 entry 28
		"LDRH	R1, [R0,#4]\n"
		"STRH	R1, [SP,#0x10]\n"
		"LDRH	R1, [R5,#2]\n"
		"STRH	R1, [SP,#0x12]\n"
		"LDRH	R1, [R5,#4]\n"
		"STRH	R1, [SP,#0x14]\n"
		"LDRH	R1, [R5,#6]\n"
		"STRH	R1, [SP,#0x16]\n"
		"LDRH	R1, [R5,#8]\n"
		"STRH	R1, [SP,#0x18]\n"
		"BL	sub_FF8AEC8C\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADCAC:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBF0j
// jumptable FF8ADB74 entry 29
		"LDRH	R1, [R5]\n"
		"STRH	R1, [SP,#0x10]\n"
		"LDRH	R1, [R0,#6]\n"
		"STRH	R1, [SP,#0x12]\n"
		"LDRH	R1, [R5,#4]\n"
		"STRH	R1, [SP,#0x14]\n"
		"LDRH	R1, [R5,#6]\n"
		"STRH	R1, [SP,#0x16]\n"
		"LDRH	R1, [R5,#8]\n"
		"STRH	R1, [SP,#0x18]\n"
		"BL	sub_FF8AED38\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADCDC:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBF4j
// jumptable FF8ADB74 entry 30
		"LDRH	R1, [R5]\n"
		"STRH	R1, [SP,#0x10]\n"
		"LDRH	R1, [R5,#2]\n"
		"STRH	R1, [SP,#0x12]\n"
		"LDRH	R1, [R5,#4]\n"
		"STRH	R1, [SP,#0x14]\n"
		"LDRH	R1, [R5,#6]\n"
		"STRH	R1, [SP,#0x16]\n"
		"LDRH	R1, [R0,#0xC]\n"
		"STRH	R1, [SP,#0x18]\n"
		"BL	sub_FF8AEDD8\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADD0C:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBF8j ...
// jumptable FF8ADB74 entries 31,32
		"BL	sub_FF8AB698\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADD14:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADC08j
// jumptable FF8ADB74 entry 35
		"BL	sub_FF8ABCD4\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADD1C:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADC0Cj
// jumptable FF8ADB74 entry 36
		"BL	sub_FF8ABF0C\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADD24:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBACj
// jumptable FF8ADB74 entry 12
		"BL	sub_FF8AC084\n"
		"B	loc_FF8ADD30\n"
// ---------------------------------------------------------------------------

"loc_FF8ADD2C:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task:loc_FF8ADBB0j ...
// jumptable FF8ADB74 entries 13-16
		"BL	sub_FF8AC21C\n"

"loc_FF8ADD30:\n"				// CODE XREF: exp_drv_task+308j
//					// exp_drv_task+30Cj ...
// jumptable FF8ADB74 default entry
// jumptable FF8ADB74 entries 17-21,33,34
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R1, [R0,#0x7C]\n"
		"LDR	R3, [R0,#0x88]\n"
		"LDR	R2, [R0,#0x8C]\n"
		"ADD	R0, R0,	#4\n"
		"BLX	R3\n"
		"CMP	R4, #1\n"
		"BNE	loc_FF8ADD98\n"

"loc_FF8ADD50:\n"				// CODE XREF: exp_drv_task+1F0j
//					// exp_drv_task+28Cj ...
		"LDR	R0, [SP,#0x1C]\n"
		"MOV	R2, #0xC\n"
		"LDR	R1, [R0,#0x7C]\n"
		"ADD	R1, R1,	R1,LSL#1\n"
		"ADD	R0, R0,	R1,LSL#2\n"
		"SUB	R4, R0,	#8\n"
		"LDR	R0, =0x210F0\n"
		"ADD	R1, SP,	#0x10\n"
		"BL	sub_FFB00130\n"
		"LDR	R0, =0x210FC\n"
		"MOV	R2, #0xC\n"
		"ADD	R1, SP,	#0x10\n"
		"BL	sub_FFB00130\n"
		"LDR	R0, =0x21108\n"
		"MOV	R2, #0xC\n"
		"MOV	R1, R4\n"
		"BL	sub_FFB00130\n"
		"B	loc_FF8ADE10\n"
// ---------------------------------------------------------------------------

"loc_FF8ADD98:\n"				// CODE XREF: exp_drv_task+4E0j
		"LDR	R0, [SP,#0x1C]\n"
		"LDR	R0, [R0]\n"
		"CMP	R0, #0xB\n"
		"BNE	loc_FF8ADDE0\n"
		"MOV	R3, #0\n"
		"STR	R3, [SP]\n"
		"MOV	R3, #1\n"
		"MOV	R2, #1\n"
		"MOV	R1, #1\n"
		"MOV	R0, #0\n"
		"BL	sub_FF8AA5A0\n"
		"MOV	R3, #0\n"
		"STR	R3, [SP]\n"
		"MOV	R3, #1\n"
		"MOV	R2, #1\n"
		"MOV	R1, #1\n"
		"MOV	R0, #0\n"
		"B	loc_FF8ADE0C\n"
// ---------------------------------------------------------------------------

"loc_FF8ADDE0:\n"				// CODE XREF: exp_drv_task+538j
		"MOV	R3, #1\n"
		"MOV	R2, #1\n"
		"MOV	R1, #1\n"
		"MOV	R0, #1\n"
		"STR	R3, [SP]\n"
		"BL	sub_FF8AA5A0\n"
		"MOV	R3, #1\n"
		"MOV	R2, #1\n"
		"MOV	R1, #1\n"
		"MOV	R0, #1\n"
		"STR	R3, [SP]\n"

"loc_FF8ADE0C:\n"				// CODE XREF: exp_drv_task+570j
		"BL	sub_FF8AA6E0\n"

"loc_FF8ADE10:\n"				// CODE XREF: exp_drv_task+B0j
//					// exp_drv_task+100j ...
		"LDR	R0, [SP,#0x1C]\n"
		"BL	sub_FF8AEABC\n"
		"B	loc_FF8AD88C\n"
// End of function exp_drv_task

 );
}







void __attribute__((naked,noinline)) sub_FF8AB2E8_my(){
 asm volatile(
		"STMFD	SP!, {R4-R8,LR}\n"
		"LDR	R7, =0x6EE4\n"
		"MOV	R4, R0\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R1, #0x3E\n"
		"BL	sub_FF8714D8\n"
		"LDRSH	R0, [R4,#4]\n"
		"MOV	R2, #0\n"
		"MOV	R1, #0\n"
		"BL	sub_FF8AA328\n"
		"MOV	R6, R0\n"
		"LDRSH	R0, [R4,#6]\n"
		"BL	sub_FF8AA440\n"
		"LDRSH	R0, [R4,#8]\n"
		"BL	sub_FF8AA498\n"
		"LDRSH	R0, [R4,#0xA]\n"
		"BL	sub_FF8AA4F0\n"
		"LDRSH	R0, [R4,#0xC]\n"
		"BL	sub_FF8AA548\n"
		"MOV	R5, R0\n"
		"LDR	R0, [R4]\n"
		"LDR	R8, =0x21108\n"
		"CMP	R0, #0xB\n"
		"MOVEQ	R6, #0\n"
		"MOVEQ	R5, #0\n"
		"BEQ	loc_FF8AB378\n"
		"CMP	R6, #1\n"
		"BNE	loc_FF8AB378\n"
		"LDRSH	R0, [R4,#4]\n"
		"LDR	R1, =0xFF8AA294\n"
		"MOV	R2, #2\n"
		"BL	sub_FF93B440\n"
		"STRH	R0, [R4,#4]\n"
		"MOV	R0, #0\n"
		"STR	R0, [R7,#0x28]\n"
		"B	loc_FF8AB380\n"
// ---------------------------------------------------------------------------

"loc_FF8AB378:\n"				// CODE XREF: sub_FF8AB2E8+64j
//					// sub_FF8AB2E8+6Cj
		"LDRH	R0, [R8]\n"
		"STRH	R0, [R4,#4]\n"

"loc_FF8AB380:\n"				// CODE XREF: sub_FF8AB2E8+8Cj
		"CMP	R5, #1\n"
		"LDRNEH	R0, [R8,#8]\n"
		"BNE	loc_FF8AB39C\n"
		"LDRSH	R0, [R4,#0xC]\n"
		"LDR	R1, =0xFF8AA318\n"
		"MOV	R2, #0x20\n"
		"BL	sub_FF8AEAEC\n"

"loc_FF8AB39C:\n"				// CODE XREF: sub_FF8AB2E8+A0j
		"STRH	R0, [R4,#0xC]\n"
		"LDRSH	R0, [R4,#6]\n"
                "BL     sub_FF89D14C_my\n"   //------------>
		"LDRSH	R0, [R4,#8]\n"
		"MOV	R1, #1\n"
		"BL	sub_FF89D898\n"
		"MOV	R1, #0\n"
		"ADD	R0, R4,	#8\n"
		"BL	sub_FF89D920\n"
		"LDRSH	R0, [R4,#0xE]\n"
		"BL	sub_FF8A5FB4\n"
		"LDR	R4, =0xBB8\n"
		"CMP	R6, #1\n"
		"BNE	loc_FF8AB3F4\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R2, R4\n"
		"MOV	R1, #2\n"
		"BL	sub_FF8713E4\n"
		"TST	R0, #1\n"
		"LDRNE	R1, =0x54D\n"
		"LDRNE	R0, =0xFF8AA9AC\n"
		"BLNE	sub_FF81B1CC\n"

"loc_FF8AB3F4:\n"				// CODE XREF: sub_FF8AB2E8+E8j
		"CMP	R5, #1\n"
		"LDMNEFD	SP!, {R4-R8,PC}\n"
		"LDR	R0, [R7,#0x1C]\n"
		"MOV	R2, R4\n"
		"MOV	R1, #0x20\n"
		"BL	sub_FF8713E4\n"
		"TST	R0, #1\n"
		"LDRNE	R1, =0x552\n"
		"LDRNE	R0, =0xFF8AA9AC\n"	// "ExpDrv.c"\n"
		"LDMNEFD	SP!, {R4-R8,LR}\n"
		"BNE	sub_FF81B1CC\n"
		"LDMFD	SP!, {R4-R8,PC}\n"
// End of function sub_FF8AB2E8
 );
}

void __attribute__((naked,noinline)) sub_FF89D14C_my(){
 asm volatile(
		"STMFD	SP!, {R4-R6,LR}\n"
		"LDR	R5, =0x6C14\n"
		"MOV	R4, R0\n"
		"LDR	R0, [R5,#4]\n"
		"CMP	R0, #1\n"
		"MOVNE	R1, #0x140\n"
		"LDRNE	R0, =0xFF89CF50\n"	// "Shutter.c"\n"
		"BLNE	sub_FF81B1CC\n"
		"CMN	R4, #0xC00\n"
		"LDREQSH	R4, [R5,#2]\n"
		"CMN	R4, #0xC00\n"
		"LDREQ	R1, =0x146\n"
		"LDREQ	R0, =0xFF89CF50\n"	// "Shutter.c"\n"
		"STRH	R4, [R5,#2]\n"
		"BLEQ	sub_FF81B1CC\n"
		"MOV	R0, R4\n"
		"BL	apex2us\n"		// ??????
		"MOV	R4, R0\n"
	//	"BL	nullsub_61\n"		// ?????
		"MOV	R0, R4\n"
		"BL	sub_FF8D6320\n"
		"TST	R0, #1\n"
		"LDRNE	R1, =0x14B\n"
		"LDMNEFD	SP!, {R4-R6,LR}\n"
		"LDRNE	R0, =0xFF89CF50\n"	// "Shutter.c"\n"
		"BNE	sub_FF81B1CC\n"
		"LDMFD	SP!, {R4-R6,PC}\n"
// End of function sub_FF89D14C
 );
}
