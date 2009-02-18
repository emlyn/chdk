#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6ACC;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF99BA84_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FF99C48C\n"
//                "MOVL    R1, 0xFFFFFFFF\n"
				"MVN     R1, #0\n"
                "BL      sub_FF820FC8\n" // ClearEventFlag
                "MOV     R0, #0x120\n" // MOV R0, #0x122 --> MOV #0x120 + ADD #0x2
                "ADD     R0, R0, #0x2\n"
                "ADD     R1, SP, #4\n"
                "MOV     R2, #4\n"
                "BL      sub_FF825A14\n" // GetPropertyCase
                "TST     R0, #1\n"
                "BEQ     loc_FF99BAC4\n"
                "MOV     R1, #0x1D0\n"
                "LDR     R0, =0xFF99B900\n" // aCaptureseq_c
                "BL      sub_FF813E84\n" // DebugAssert
 "loc_FF99BAC4:\n"
                "LDR     R3, =0xB7CA0\n"
                "LDR     R2, =0xB7D60\n"
                "LDR     R0, [R3,#0x84]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FF8B0144\n"
                "MOV     R0, R4\n"
                "BL      sub_FF99B884\n"
                "BL      wait_until_remote_button_is_released\n"
				"BL      capt_seq_hook_set_nr\n" // +
                "LDR     R3, =0x6AD0\n"
                "LDR     R0, [R3]\n"

                "B       sub_FF99BAE8\n"  // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FF998960_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0xB7CA0\n"
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R1, [R3,#0x28]\n"
                "LDR     R2, [R4,#8]\n"
                "CMP     R1, #0\n"
                "ORR     R2, R2, #1\n"
                "STR     R2, [R4,#8]\n"
                "BNE     loc_FF9989B4\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FF9A2710\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF9989B4\n"
                "LDR     R3, [R4,#8]\n"
                "MOV     R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R4,#8]\n"
 "loc_FF9989A4:\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF9971EC\n"
 "loc_FF9989B4:\n"
                "LDR     R5, =0xB7CA0\n"
                "LDR     R3, [R5,#0x28]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF9989CC\n"
                "MOV     R0, #2\n"
                "BL      sub_FFB0628C\n"
 "loc_FF9989CC:\n"
                "BL      sub_FF999480\n" // Set_CMD25Write_26
                "LDR     R3, [R5,#0x28]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF998A10\n"
                "MOV     R0, R4\n"
                "BL      sub_FF99A608\n"
                "TST     R0, #1\n"
                "BNE     loc_FF9989A4\n"
                "BL      sub_FF9DA8C8\n"
                "BL      sub_FF825C10\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FF99B96C\n"
                "BL      sub_FF99C318\n"
                "MOV     R0, R4\n"
                "BL      sub_FF99BA84_my\n"  //---------->
                "BL      capt_seq_hook_raw_here\n"  // +
                "B       loc_FF998A24\n"
 "loc_FF998A10:\n"
                "LDR     R3, =0x6AB0\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
 "loc_FF998A24:\n"
                "MOV     R1, #1\n"
                "MOV     R2, R4\n"
                "BL      sub_FF9971EC\n"
                "BL      sub_FF99BE04\n"
                "CMP     R0, #0\n"
                "LDRNE   R3, [R4,#8]\n"
                "ORRNE   R3, R3, #0x2000\n"
                "STRNE   R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,R5,PC}\n"
    );
}


void __attribute__((naked,noinline)) sub_FF998A50_my(){
    asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF9985E8\n"
                 "LDR     R3, =0xB7CA0\n"
                 "LDR     R2, [R3,#0x28]\n"
                 "CMP     R2, #0\n"
                 "MOV     R4, R0\n"
                 "MOV     R0, #0xC\n"
                 "BEQ     loc_FF998A98\n"
                 "BL      sub_FF9A2710\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF998A98\n"
                 "LDR     R3, [R4,#8]\n"
                 "LDR     R2, =0x6AB0\n"
                 "ORR     R3, R3, #0x40000000\n"
                 "MOV     R1, #1\n"
                 "STR     R1, [R2]\n"
                 "STR     R3, [R4,#8]\n"
                 "LDMFD   SP!, {R4,PC}\n"
 "loc_FF998A98:\n"
                 "BL      sub_FF9DA8C8\n"
                 "BL      sub_FF825C10\n"
                 "STR     R0, [R4,#0x14]\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF99BA84_my\n"  //--------->
                 "BL      capt_seq_hook_raw_here\n"  // +
                 "TST     R0, #1\n"
                 "LDRNE   R3, =0x6AB0\n"
                 "MOVNE   R2, #1\n"
                 "STRNE   R2, [R3]\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}


void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF998FA8\n"
 "loc_FF998E2C:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF998F7C\n"
                ".long loc_FF998E9C\n"
                ".long loc_FF998EBC\n"
                ".long loc_FF998ED0\n"
                ".long loc_FF998EE4\n"
                ".long loc_FF998EDC\n"
                ".long loc_FF998EEC\n"
                ".long loc_FF998EF4\n"
                ".long loc_FF998F00\n"
                ".long loc_FF998F08\n"
                ".long loc_FF998F14\n"
                ".long loc_FF998F1C\n"
                ".long loc_FF998F24\n"
                ".long loc_FF998F2C\n"
                ".long loc_FF998F34\n"
                ".long loc_FF998F3C\n"
                ".long loc_FF998F48\n"
                ".long loc_FF998F50\n"
                ".long loc_FF998F58\n"
                ".long loc_FF998F60\n"
                ".long loc_FF998F6C\n"
                ".long loc_FF998F74\n"
                ".long loc_FF998F90\n"
 "loc_FF998E9C:\n"
				"BL      sub_FF9994A8\n" // ; jumptable FF998E3C case 0
				"BL      shooting_expo_param_override\n"   // +
				"BL      sub_FF996C88\n"
				"LDR     R3, =0xB7CA0\n"
				"LDR     R2, [R3,#0x28]\n"
                "CMP     R2, #0\n"
				"BEQ     loc_FF998F8C\n"
				"BL      sub_FF998A50_my\n"  //--------->
				"B       loc_FF998F8C\n"
 "loc_FF998EBC:\n"
                                        
				"BL      sub_FF998960_my\n" //----------> ; jumptable FF998E3C case 1

 "loc_FF998EC0:\n"
				"LDR     R2, =0xB7CA0\n"
                "MOV     R3, #0\n"
				"STR     R3, [R2,#0x28]\n"
				"B       loc_FF998F8C\n"
 "loc_FF998ED0:\n"
				"MOV     R0, #1\n"       // ; jumptable FF998E3C case 2
				"BL      sub_FF9996E8\n"
				"B       loc_FF998F8C\n"
 "loc_FF998EDC:\n"
				"BL      sub_FF9990A0\n" //; jumptable FF998E3C case 4
				"B       loc_FF998EC0\n"
 "loc_FF998EE4:\n"
				"BL      sub_FF999460\n" // BackLightDrv_LcdBackLightOff_4 ; jumptable FF998E3C case 3
				"B       loc_FF998EC0\n"
 "loc_FF998EEC:\n"
				"BL      sub_FF999470\n" // ; jumptable FF998E3C case 5
				"B       loc_FF998F8C\n"
 "loc_FF998EF4:\n"
				"BL      sub_FF9995C8\n" //; jumptable FF998E3C case 6
				"BL      sub_FF996C88\n"
				"B       loc_FF998F8C\n"
 "loc_FF998F00:\n"
				"BL      sub_FF998B2C\n" //; jumptable FF998E3C case 7
				"B       loc_FF998F8C\n"
 "loc_FF998F08:\n"
				"BL      sub_FF99963C\n" // ; jumptable FF998E3C case 8
				"BL      sub_FF996C88\n"
				"B       loc_FF998F8C\n"
 "loc_FF998F14:\n"
				"BL      sub_FF999460\n" // BackLightDrv_LcdBackLightOff_4 ; jumptable FF998E3C case 9
				"B       loc_FF998F8C\n"
 "loc_FF998F1C:\n"
				"BL      sub_FF99AD1C\n" //; jumptable FF998E3C case 10
				"B       loc_FF998F8C\n"
 "loc_FF998F24:\n"
				"BL      sub_FF99AEF0\n" // ; jumptable FF998E3C case 11
				"B       loc_FF998F8C\n"
 "loc_FF998F2C:\n"
				"BL      sub_FF99AF84\n" // ; jumptable FF998E3C case 12
				"B       loc_FF998F8C\n"
 "loc_FF998F34:\n"
				"BL      sub_FF99B020\n" //  ; jumptable FF998E3C case 13
				"B       loc_FF998F8C\n"
 "loc_FF998F3C:\n"
				"MOV     R0, #0\n"       // ; jumptable FF998E3C case 14
				"BL      sub_FF99B28C\n"
				"B       loc_FF998F8C\n"
 "loc_FF998F48:\n"
				"BL      sub_FF99B460\n" // ; jumptable FF998E3C case 15
				"B       loc_FF998F8C\n"
 "loc_FF998F50:\n"
				"BL      sub_FF99B4F8\n" // ; jumptable FF998E3C case 16
				"B       loc_FF998F8C\n"
 "loc_FF998F58:\n"
				"BL      sub_FF99B5B4\n" // ; jumptable FF998E3C case 17
				"B       loc_FF998F8C\n"
 "loc_FF998F60:\n"
				"BL      sub_FF999830\n" // ; jumptable FF998E3C case 18
				"BL      sub_FF998884\n"
				"B       loc_FF998F8C\n"
 "loc_FF998F6C:\n"
				"BL      sub_FF99B160\n" // ; jumptable FF998E3C case 19
				"B       loc_FF998F8C\n"
 "loc_FF998F74:\n"
				"BL      sub_FF99B1B8\n" // ; jumptable FF998E3C case 20
				"B       loc_FF998F8C\n"
 "loc_FF998F7C:\n"
				"MOV     R1, #0x4E0\n" // ; default
				"LDR     R0, =0xFF9986E0\n" // aShoottask_c
				"ADD     R1, R1, #7\n"
				"BL      sub_FF813E84\n" // DebugAssert
 "loc_FF998F8C:\n"
				"LDR     R2, [SP]\n"
 "loc_FF998F90:\n"
				"LDR     R3, =0x8C424\n" // ; jumptable FF998E3C case 21
				"LDR     R1, [R2,#4]\n"
				"LDR     R0, [R3]\n"
				"BL      sub_FF820E2C\n" // SetEventFlag
				"LDR     R0, [SP]\n"
				"BL      sub_FF99875C\n"
 "loc_FF998FA8:\n"
				"LDR     R3, =0x8C428\n"
				"MOV     R1, R4\n"
				"LDR     R0, [R3]\n"
				"MOV     R2, #0\n"
				"BL      sub_FF821544\n" // ReceiveMessageQueue
				"TST     R0, #1\n"
				"BEQ     loc_FF998E2C\n"
				"LDR     R0, =0xFF9986E0\n" // aShoottask_c
				"MOV     R1, #0x410\n"
				"ADD     R1, R1, #9\n"
				"BL      sub_FF813E84\n" // DebugAssert
				"BL      sub_FF822AA0\n" // ExitTask
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

