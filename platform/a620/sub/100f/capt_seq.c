#include "lolevel.h"
#include "platform.h"
#include "core.h"


static long *nrflag = (long*)0x6D44;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FFD3A354_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0x741C4\n"
                "LDR     R5, =0x6D40\n"
                "SUB     SP, SP, #4\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC0FA40\n"
                "BL      sub_FFD40324\n"
                "BL      wait_until_remote_button_is_released\n"
                "LDR     R0, [R0,#0x7C]\n"
                "BL      sub_FFD3A2C8\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6D48\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC8C830\n"

		"B	 sub_FFD3A390\n"
    );
}

void __attribute__((naked,noinline)) sub_FFD371E4_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FFD400C8\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFD371FC\n"
                "BL      sub_FFD400D4\n"

"loc_FFD371FC:\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD39160\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FFD3721C\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD35710\n"

"loc_FFD3721C:\n"
                "BL      sub_FFD75760\n"
                "BL      sub_FFD34A68\n"
                "MOV     R4, R0\n"
                "BL      sub_FFC14384\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD3AB6C\n"
                "BL      sub_FFD396A4\n"
                "BL      sub_FFD39644\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD3A354_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FFD35710\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD3A554\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFD3773C\n"

"loc_FFD375E8:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFD37714\n"
                ".long loc_FFD37658\n"
                ".long loc_FFD37664\n"
                ".long loc_FFD3766C\n"
                ".long loc_FFD3767C\n"
                ".long loc_FFD37674\n"
                ".long loc_FFD37684\n"
                ".long loc_FFD3768C\n"
                ".long loc_FFD37698\n"
                ".long loc_FFD376A0\n"
                ".long loc_FFD376AC\n"
                ".long loc_FFD376B4\n"
                ".long loc_FFD376BC\n"
                ".long loc_FFD376C4\n"
                ".long loc_FFD376CC\n"
                ".long loc_FFD376D4\n"
                ".long loc_FFD376E0\n"
                ".long loc_FFD376E8\n"
                ".long loc_FFD376F0\n"
                ".long loc_FFD376F8\n"
                ".long loc_FFD37704\n"
                ".long loc_FFD3770C\n"
                ".long loc_FFD37724\n"

"loc_FFD37658:\n"
                "BL      sub_FFD38DBC\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFD35274\n"
                "B       loc_FFD37720\n"

"loc_FFD37664:\n"
                "BL      sub_FFD371E4_my\n"
                "B       loc_FFD37720\n"

"loc_FFD3766C:\n"
                "BL      sub_FFD39150\n"
                "B       loc_FFD37720\n"

"loc_FFD37674:\n"
                "BL      sub_FFD38078\n"
                "B       loc_FFD37720\n"

"loc_FFD3767C:\n"
                "BL      sub_FFD380D4\n"
                "B       loc_FFD37720\n"

"loc_FFD37684:\n"
                "BL      sub_FFD382C4\n"
                "B       loc_FFD37720\n"

"loc_FFD3768C:\n"
                "BL      sub_FFD38EB0\n"
                "BL      sub_FFD35274\n"
                "B       loc_FFD37720\n"

"loc_FFD37698:\n"
                "BL      sub_FFD372CC\n"
                "B       loc_FFD37720\n"

"loc_FFD376A0:\n"
                "BL      sub_FFD38F18\n"
                "BL      sub_FFD35274\n"
                "B       loc_FFD37720\n"

"loc_FFD376AC:\n"
                "BL      sub_FFD380D4\n"
                "B       loc_FFD37720\n"

"loc_FFD376B4:\n"
                "BL      sub_FFD397DC\n"
                "B       loc_FFD37720\n"

"loc_FFD376BC:\n"
                "BL      sub_FFD39A64\n"
                "B       loc_FFD37720\n"

"loc_FFD376C4:\n"
                "BL      sub_FFD39AF0\n"
                "B       loc_FFD37720\n"

"loc_FFD376CC:\n"
                "BL      sub_FFD39BA8\n"
                "B       loc_FFD37720\n"

"loc_FFD376D4:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFD39C58\n"
                "B       loc_FFD37720\n"

"loc_FFD376E0:\n"
                "BL      sub_FFD39DA8\n"
                "B       loc_FFD37720\n"

"loc_FFD376E8:\n"
                "BL      sub_FFD39E1C\n"
                "B       loc_FFD37720\n"

"loc_FFD376F0:\n"
                "BL      sub_FFD39ED4\n"
                "B       loc_FFD37720\n"

"loc_FFD376F8:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD39C58\n"
                "B       loc_FFD37720\n"

"loc_FFD37704:\n"
                "BL      sub_FFD39FD4\n"
                "B       loc_FFD37720\n"

"loc_FFD3770C:\n"
                "BL      sub_FFD3A000\n"
                "B       loc_FFD37720\n"

"loc_FFD37714:\n"
                "LDR     R0, =0xFFD36F68\n"
                "MOV     R1, #0x2DC\n"
                "BL      sub_FFC03AD0\n"

"loc_FFD37720:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"

"loc_FFD37724:\n"
                "LDR     R3, =0x7414C\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC0F8A4\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFD36FE4\n"

"loc_FFD3773C:\n"
                "LDR     R3, =0x74150\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC10054\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD375E8\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xFFD36F68\n"
                "ADD     R1, R1, #1\n"
                "BL      sub_FFC03AD0\n"
                "BL      sub_FFC115F0\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}





