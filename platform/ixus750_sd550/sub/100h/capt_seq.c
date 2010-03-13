#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6DB4; 

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF9510CC_my(long p)
//void __attribute__((naked,noinline)) sub_FF950D44_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0x73F6C\n"
                "LDR     R5, =0x6DB0\n"
                "SUB     SP, SP, #4\n"
		"LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF820884\n" // ClearEventFlag
                "BL      sub_FF956B08\n"
                "LDR     R0, [R0,#0x7C]\n"
                "BL      sub_FF89F9CC\n" // IsEmptyWriteCache_44
                "BL      sub_FF951040\n"
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6DB8\n"
                "LDR     R0, [R3]\n"

                "B       sub_FF951104\n" // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FF94E17C_my(long p)
//void __attribute__((naked,noinline)) sub_FF94DDF4_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FF9568AC\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF94E194\n"
                "BL      sub_FF9568B8\n"

"loc_FF94E194:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94FF34\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF94E1B4\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF94C77C\n"

"loc_FF94E1B4:\n"
                "BL      sub_FF989F74\n"
                "BL      sub_FF94BBB4\n"
                "MOV     R4, R0\n"
                "BL      sub_FF82572C\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF9518E0\n"
                "BL      sub_FF950478\n"
                "BL      sub_FF950418\n"
                "MOV     R0, R5\n"
                "BL      sub_FF9510CC_my\n" //top function up there
//                "BL      sub_FF950538\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF94C77C\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF9512C8\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF94E508\n"

"loc_FF94E3C0:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x14\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF94E4DC\n"

				".long loc_FF94E42C\n" 
                ".long loc_FF94E438\n"
                ".long loc_FF94E440\n"
                ".long loc_FF94E450\n"
                ".long loc_FF94E448\n"
                ".long loc_FF94E458\n"
                ".long loc_FF94E460\n"
                ".long loc_FF94E46C\n"
                ".long loc_FF94E474\n"
                ".long loc_FF94E480\n"
                ".long loc_FF94E488\n"
                ".long loc_FF94E490\n"
                ".long loc_FF94E498\n"
                ".long loc_FF94E4A0\n"
                ".long loc_FF94E4A8\n"
                ".long loc_FF94E4B4\n"
                ".long loc_FF94E4BC\n"
                ".long loc_FF94E4C4\n"
                ".long loc_FF94E4CC\n"
                ".long loc_FF94E4D4\n"
                ".long loc_FF94E4F0\n"

"loc_FF94E42C:\n"
                "BL      sub_FF94FB90\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FF94C2D8\n"
				"B       loc_FF94E4EC\n"

"loc_FF94E438:\n"
                "BL      sub_FF94E17C_my\n"
//                "BL      sub_FF94DDF4\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E440:\n"
                "BL      sub_FF94FF24\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E448:\n"
                "BL      sub_FF94EE44\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E450:\n"
                "BL      sub_FF94EEA0\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E458:\n"
                "BL      sub_FF94F094\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E460:\n"
                "BL      sub_FF94FC84\n"
                "BL      sub_FF94C2D8\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E46C:\n"
                "BL      sub_FF94E230\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E474:\n"
                "BL      sub_FF94FCEC\n"
                "BL      sub_FF94C2D8\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E480:\n"
                "BL      sub_FF94EEA0\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E488:\n"
                "BL      sub_FF9505B4\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E490:\n"
                "BL      sub_FF95083C\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E498:\n"
                "BL      sub_FF9508B0\n"
                "B       loc_FF94E4EC\n"
"loc_FF94E4A0:\n"
                "BL      sub_FF950968\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E4A8:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF950A00\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E4B4:\n"
                "BL      sub_FF950B50\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E4BC:\n"
                "BL      sub_FF950BC4\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E4C4:\n"
                "BL      sub_FF950C7C\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E4CC:\n"
                "BL      sub_FF950D4C\n"
                "B       loc_FF94E4EC\n"

"loc_FF94E4D4:\n"
                "BL      sub_FF950D78\n"
                "B       loc_FF94E4EC\n"
"loc_FF94E4DC:\n"
                "MOV     R1, #0x2DC\n"
                "LDR     R0, =0xff94dF28\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813BFC\n"

"loc_FF94E4EC:\n"
                "LDR     R2, [SP]\n"

"loc_FF94E4F0:\n"
                "LDR     R3, =0x73EF4\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF8206E8\n"
                "LDR     R0, [SP]\n"
                "BL      sub_FF94DFA4\n"

"loc_FF94E508:\n"
                "LDR     R3, =0x73EF8\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820EA4\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF94E3C0\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xff94df28\n"
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813BFC\n"
                "BL      sub_FF822634\n"

                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"

);
}
