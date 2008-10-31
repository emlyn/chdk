#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6D6C; 

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF9507EC_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0x7D4BC\n"
                "LDR     R5, =0x6D68\n"
                "SUB     SP, SP, #4\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FD18\n" // ClearEventFlag
                "BL      sub_FF956244\n"
                "LDR     R0, [R0,#0x7C]\n"
                "BL      sub_FF89DE58\n" // IsEmptyWriteCache_44
                "BL      sub_FF950760\n"
                "BL      wait_until_remote_button_is_released\n"
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6D70\n"
                "LDR     R0, [R3]\n"

                "B       sub_FF950824\n" // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FF94D878_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FF955FE8\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF94D890\n"
                "BL      sub_FF955FF4\n"

"loc_FF94D890:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94F628\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF94D8B0\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF94BE78\n"

"loc_FF94D8B0:\n"
                "BL      sub_FF989528\n"
                "BL      sub_FF94B2B0\n"
                "MOV     R4, R0\n"
                "BL      sub_FF824678\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF951004\n"
                "BL      sub_FF94FB6C\n"
                "BL      sub_FF94FB0C\n"
                "MOV     R0, R5\n"
                "BL      sub_FF9507EC_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF94BE78\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF9509EC\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task() 
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF94DC04\n"

"loc_FF94DABC:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x14\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF94DBD8\n"

                ".long loc_FF94DB28\n"     
                ".long loc_FF94DB34\n"
                ".long loc_FF94DB3C\n"
                ".long loc_FF94DB4C\n"
                ".long loc_FF94DB44\n"
                ".long loc_FF94DB54\n"
                ".long loc_FF94DB5C\n"
                ".long loc_FF94DB68\n"
                ".long loc_FF94DB70\n"
                ".long loc_FF94DB7C\n"
                ".long loc_FF94DB84\n"
                ".long loc_FF94DB8C\n"
                ".long loc_FF94DB94\n"
                ".long loc_FF94DB9C\n"
                ".long loc_FF94DBA4\n"
                ".long loc_FF94DBB0\n"
                ".long loc_FF94DBB8\n"
                ".long loc_FF94DBC0\n"
                ".long loc_FF94DBC8\n"
                ".long loc_FF94DBD0\n"
                ".long loc_FF94DBEC\n"


"loc_FF94DB28:\n"
                "BL      sub_FF94F284\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FF94B9D4\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB34:\n"
                "BL      sub_FF94D878_my\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB3C:\n"
                "BL      sub_FF94F618\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB44:\n"
                "BL      sub_FF94E540\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB4C:\n"
                "BL      sub_FF94E59C\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB54:\n"
                "BL      sub_FF94E78C\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB5C:\n"
                "BL      sub_FF94F389\n"
                "BL      sub_FF94B9D4\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB68:\n"
                "BL      sub_FF94D92C\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB70:\n"
                "BL      sub_FF94F3E0\n"
                "BL      sub_FF94B9D4\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB7C:\n"
                "BL      sub_FF94E59C\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB84:\n"
                "BL      sub_FF94FCA4\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB8C:\n"
                "BL      sub_FF94FF2C\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB94:\n"
                "BL      sub_FF94FFB8\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DB9C:\n"
                "BL      sub_FF950070\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DBA4:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF950120\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DBB0:\n"
                "BL      sub_FF950270\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DBB8:\n"
                "BL      sub_FF9502E4\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DBC0:\n"
                "BL      sub_FF95039C\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DBC8:\n"
                "BL      sub_FF95046C\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DBD0:\n"
                "BL      sub_FF950498\n"
                "B       loc_FF94DBE8\n"

"loc_FF94DBD8:\n"
                "MOV     R1, #0x2DC\n"
                "LDR     R0, =0xFF94D624\n" // aShoottask_c
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813A80\n" // DebugAssert

"loc_FF94DBE8:\n"
                "LDR     R2, [SP]\n"

"loc_FF94DBEC:\n"
                "LDR     R3, =0x7D444\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FB7C\n"  //  SetEventFlag
                "LDR     R0, [SP]\n"
                "BL      sub_FF94D6A0\n"

"loc_FF94DC04:\n"
                "LDR     R3, =0x7D448\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF82032C\n" //  ReceiveMessageQueue
                "TST     R0, #1\n"
                "BEQ     loc_FF94DABC\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xFF94D624\n" // aShoottask_c
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813A80\n" // DebugAssert
                "BL      sub_FF8218C8\n" //  ExitTask

                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

