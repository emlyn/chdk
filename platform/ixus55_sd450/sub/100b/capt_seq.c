#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6D6C; 

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF950538_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0x7D4BC\n"
                "LDR     R5, =0x6D68\n"
                "SUB     SP, SP, #4\n"
		"LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FDEC\n" // ClearEventFlag
                "BL      sub_FF955F90\n"
                "LDR     R0, [R0,#0x7C]\n"
                "BL      sub_FF89DBA4\n" // IsEmptyWriteCache_44
                "BL      sub_FF9504AC\n"
                "BL      wait_until_remote_button_is_released\n"
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6D70\n"
                "LDR     R0, [R3]\n"

                "B       sub_FF950570\n" // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FF94D5C4_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FF955D34\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF94D5DC\n"
                "BL      sub_FF955D40\n"

"loc_FF94D5DC:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94F374\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF94D5FC\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF94BBC4\n"

"loc_FF94D5FC:\n"
                "BL      sub_FF989274\n"
                "BL      sub_FF94AFFC\n"
                "MOV     R4, R0\n"
                "BL      sub_FF82474C\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF950D50\n"
                "BL      sub_FF94F8B8\n"
                "BL      sub_FF94F858\n"
                "MOV     R0, R5\n"
                "BL      sub_FF950538_my\n"
//                "BL      sub_FF950538\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF94BBC4\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF950738\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF94D950\n"

"loc_FF94D808:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x14\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF94D924\n"

                ".long loc_FF94D874\n"
                ".long loc_FF94D880\n"
                ".long loc_FF94D888\n"
                ".long loc_FF94D898\n"
                ".long loc_FF94D890\n"
                ".long loc_FF94D8A0\n"
                ".long loc_FF94D8A8\n"
                ".long loc_FF94D8B4\n"
                ".long loc_FF94D8BC\n"
                ".long loc_FF94D8C8\n"
                ".long loc_FF94D8D0\n"
                ".long loc_FF94D8D8\n"
                ".long loc_FF94D8E0\n"
                ".long loc_FF94D8E8\n"
                ".long loc_FF94D8F0\n"
                ".long loc_FF94D8FC\n"
                ".long loc_FF94D904\n"
                ".long loc_FF94D90C\n"
                ".long loc_FF94D914\n"
                ".long loc_FF94D91C\n"
                ".long loc_FF94D938\n"

"loc_FF94D874:\n"
                "BL      sub_FF94EFD0\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FF94B720\n"
                "B       loc_FF94D934\n"

"loc_FF94D880:\n"
                "BL      sub_FF94D5C4_my\n"
                "B       loc_FF94D934\n"

"loc_FF94D888:\n"
                "BL      sub_FF94F364\n"
                "B       loc_FF94D934\n"

"loc_FF94D890:\n"
                "BL      sub_FF94E28C\n"
                "B       loc_FF94D934\n"

"loc_FF94D898:\n"
                "BL      sub_FF94E2E8\n"
                "B       loc_FF94D934\n"

"loc_FF94D8A0:\n"
                "BL      sub_FF94E4D8\n"
                "B       loc_FF94D934\n"

"loc_FF94D8A8:\n"
                "BL      sub_FF94F0C4\n"
                "BL      sub_FF94B720\n"
                "B       loc_FF94D934\n"

"loc_FF94D8B4:\n" 
                "BL      sub_FF94D678\n"
                "B       loc_FF94D934\n"

"loc_FF94D8BC:\n"
                "BL      sub_FF94F12C\n"
                "BL      sub_FF94B720\n"
                "B       loc_FF94D934\n"

"loc_FF94D8C8:\n"
                "BL      sub_FF94E2E8\n"
                "B       loc_FF94D934\n"

"loc_FF94D8D0:\n" 
                "BL      sub_FF94F9F0\n"
                "B       loc_FF94D934\n"

"loc_FF94D8D8:\n" 
                "BL      sub_FF94FC78\n"
                "B       loc_FF94D934\n"

"loc_FF94D8E0:\n"
                "BL      sub_FF94FD04\n"
                "B       loc_FF94D934\n"
"loc_FF94D8E8:\n"
                "BL      sub_FF94FDBC\n"
                "B       loc_FF94D934\n"

"loc_FF94D8F0:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF94FE6C\n"
                "B       loc_FF94D934\n"

"loc_FF94D8FC:\n"
                "BL      sub_FF94FFBC\n"
                "B       loc_FF94D934\n"

"loc_FF94D904:\n"
                "BL      sub_FF950030\n"
                "B       loc_FF94D934\n"

"loc_FF94D90C:\n"
                "BL      sub_FF9500E8\n"
                "B       loc_FF94D934\n"

"loc_FF94D914:\n"
                "BL      sub_FF9501B8\n"
                "B       loc_FF94D934\n"

"loc_FF94D91C:\n"
                "BL      sub_FF9501E4\n"
                "B       loc_FF94D934\n"
"loc_FF94D924:\n"
                "MOV     R1, #0x2DC\n"
                "LDR     R0, =0xFF94D370\n" //  aShoottask_c
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813B54\n" // DebugAssert

"loc_FF94D934:\n"
                "LDR     R2, [SP]\n"

"loc_FF94D938:\n"
                "LDR     R3, =0x7D444\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FC50\n" // SetEventFlag
                "LDR     R0, [SP]\n"
                "BL      sub_FF94D3EC\n"

"loc_FF94D950:\n"
                "LDR     R3, =0x7D448\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820400\n" // ReceiveMessageQueue
                "TST     R0, #1\n"
                "BEQ     loc_FF94D808\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xFF94D370\n" // aShoottask_c
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813B54\n" // DebugAssert
                "BL      sub_FF82199C\n" // ExitTask

                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

