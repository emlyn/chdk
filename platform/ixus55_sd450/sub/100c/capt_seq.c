#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6D6C; 

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF950464_my(long p)
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
                "BL      sub_FF955EBC\n"
                "LDR     R0, [R0,#0x7C]\n"
                "BL      sub_FF89DAD0\n" // IsEmptyWriteCache_44
                "BL      sub_FF9503D8\n"
                "BL      wait_until_remote_button_is_released\n"
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6D70\n"
                "LDR     R0, [R3]\n"

                "B       sub_FF95049C\n" // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FF94D4F0_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FF955C60\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF94D508\n"
                "BL      sub_FF955C6C\n"

"loc_FF94D508:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94F2A0\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF94D528\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF94BAF0\n"

"loc_FF94D528:\n"
                "BL      sub_FF9891A0\n"
                "BL      sub_FF94AF28\n"
                "MOV     R4, R0\n"
                "BL      sub_FF824678\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF950C7C\n"
                "BL      sub_FF94F7E4\n"
                "BL      sub_FF94F784\n"
                "MOV     R0, R5\n"
                "BL      sub_FF950464_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF94BAF0\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF950664\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task() 
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF94D87C\n"

"loc_FF94D734:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x14\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF94D850\n"

                ".long loc_FF94D7A0\n"     
                ".long loc_FF94D7AC\n"
                ".long loc_FF94D7B4\n"
                ".long loc_FF94D7C4\n"
                ".long loc_FF94D7BC\n"
                ".long loc_FF94D7CC\n"
                ".long loc_FF94D7D4\n"
                ".long loc_FF94D7E0\n"
                ".long loc_FF94D7E8\n"
                ".long loc_FF94D7F4\n"
                ".long loc_FF94D7FC\n"
                ".long loc_FF94D804\n"
                ".long loc_FF94D80C\n"
                ".long loc_FF94D814\n"
                ".long loc_FF94D81C\n"
                ".long loc_FF94D828\n"
                ".long loc_FF94D830\n"
                ".long loc_FF94D838\n"
                ".long loc_FF94D840\n"
                ".long loc_FF94D848\n"
                ".long loc_FF94D864\n"


"loc_FF94D7A0:\n"
                "BL      sub_FF94EEFC\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FF94B64C\n"
                "B       loc_FF94D860\n"

"loc_FF94D7AC:\n"
                "BL      sub_FF94D4F0_my\n"
                "B       loc_FF94D860\n"

"loc_FF94D7B4:\n"
                "BL      sub_FF94F290\n"
                "B       loc_FF94D860\n"

"loc_FF94D7BC:\n"
                "BL      sub_FF94E1B8\n"
                "B       loc_FF94D860\n"

"loc_FF94D7C4:\n"
                "BL      sub_FF94E214\n"
                "B       loc_FF94D860\n"

"loc_FF94D7CC:\n"
                "BL      sub_FF94E404\n"
                "B       loc_FF94D860\n"

"loc_FF94D7D4:\n"
                "BL      sub_FF94EFF0\n"
                "BL      sub_FF94B64C\n"
                "B       loc_FF94D860\n"

"loc_FF94D7E0:\n"
                "BL      sub_FF94D5A4\n"
                "B       loc_FF94D860\n"

"loc_FF94D7E8:\n"
                "BL      sub_FF94F058\n"
                "BL      sub_FF94B64C\n"
                "B       loc_FF94D860\n"

"loc_FF94D7F4:\n"
                "BL      sub_FF94E214\n"
                "B       loc_FF94D860\n"

"loc_FF94D7FC:\n"
                "BL      sub_FF94F91C\n"
                "B       loc_FF94D860\n"

"loc_FF94D804:\n"
                "BL      sub_FF94FBA4\n"
                "B       loc_FF94D860\n"

"loc_FF94D80C:\n"
                "BL      sub_FF94FC30\n"
                "B       loc_FF94D860\n"

"loc_FF94D814:\n"
                "BL      sub_FF94FCE8\n"
                "B       loc_FF94D860\n"

"loc_FF94D81C:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF94FD98\n"
                "B       loc_FF94D860\n"

"loc_FF94D828:\n"
                "BL      sub_FF94FEE8\n"
                "B       loc_FF94D860\n"

"loc_FF94D830:\n"
                "BL      sub_FF94FF5C\n"
                "B       loc_FF94D860\n"

"loc_FF94D838:\n"
                "BL      sub_FF950014\n"
                "B       loc_FF94D860\n"

"loc_FF94D840:\n"
                "BL      sub_FF9500E4\n"
                "B       loc_FF94D860\n"

"loc_FF94D848:\n"
                "BL      sub_FF950110\n"
                "B       loc_FF94D860\n"

"loc_FF94D850:\n"
                "MOV     R1, #0x2DC\n"
                "LDR     R0, =0xFF94D29C\n" // aShoottask_c
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813A80\n" // DebugAssert

"loc_FF94D860:\n"
                "LDR     R2, [SP]\n"

"loc_FF94D864:\n"
                "LDR     R3, =0x7D444\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FB7C\n"  //  SetEventFlag
                "LDR     R0, [SP]\n"
                "BL      sub_FF94D318\n"

"loc_FF94D87C:\n"
                "LDR     R3, =0x7D448\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF82032C\n" //  ReceiveMessageQueue
                "TST     R0, #1\n"
                "BEQ     loc_FF94D734\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xFF94D29C\n" // aShoottask_c
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813A80\n" // DebugAssert
                "BL      sub_FF8218C8\n" //  ExitTask

                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

