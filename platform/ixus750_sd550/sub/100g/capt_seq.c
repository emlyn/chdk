#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x6DB4; 

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF950D44_my(long p)
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
                "BL      sub_FF956780\n"
                "LDR     R0, [R0,#0x7C]\n"
                "BL      sub_FF89F644\n" // IsEmptyWriteCache_44
                "BL      sub_FF950CB8\n"
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6DB8\n"
                "LDR     R0, [R3]\n"

                "B       sub_FF950D7C\n" // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FF94DDF4_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FF956524\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF94DE0C\n"
                "BL      sub_FF956530\n"

"loc_FF94DE0C:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF94FBAC\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF94DE2C\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF94C3F4\n"

"loc_FF94DE2C:\n"
                "BL      sub_FF989BEC\n"
                "BL      sub_FF94B82C\n"
                "MOV     R4, R0\n"
                "BL      sub_FF82572C\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF951558\n"
                "BL      sub_FF9500F0\n"
                "BL      sub_FF950090\n"
                "MOV     R0, R5\n"
                "BL      sub_FF950D44_my\n" //top function up there
//                "BL      sub_FF950538\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF94C3F4\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF950F40\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF94E180\n"

"loc_FF94E038:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x14\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF94E154\n"

				".long loc_FF94E0A4\n" 
                ".long loc_FF94E0B0\n"
                ".long loc_FF94E0B8\n"
                ".long loc_FF94E0C8\n"
                ".long loc_FF94E0C0\n"
                ".long loc_FF94E0D0\n"
                ".long loc_FF94E0D8\n"
                ".long loc_FF94E0E4\n"
                ".long loc_FF94E0EC\n"
                ".long loc_FF94E0F8\n"
                ".long loc_FF94E100\n"
                ".long loc_FF94E108\n"
                ".long loc_FF94E110\n"
                ".long loc_FF94E118\n"
                ".long loc_FF94E120\n"
                ".long loc_FF94E12C\n"
                ".long loc_FF94E134\n"
                ".long loc_FF94E13C\n"
                ".long loc_FF94E144\n"
                ".long loc_FF94E14C\n"
                ".long loc_FF94E168\n"

"loc_FF94E0A4:\n"
                "BL      sub_FF94F808\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FF94BF50\n"
				"B       loc_FF94E164\n"

"loc_FF94E0B0:\n"
                "BL      sub_FF94DDF4_my\n"
//                "BL      sub_FF94DDF4\n"
                "B       loc_FF94E164\n"

"loc_FF94E0B8:\n"
                "BL      sub_FF94FB9C\n"
                "B       loc_FF94E164\n"

"loc_FF94E0C0:\n"
                "BL      sub_FF94EABC\n"
                "B       loc_FF94E164\n"

"loc_FF94E0C8:\n"
                "BL      sub_FF94EB18\n"
                "B       loc_FF94E164\n"

"loc_FF94E0D0:\n"
                "BL      sub_FF94ED0C\n"
                "B       loc_FF94E164\n"

"loc_FF94E0D8:\n"
                "BL      sub_FF94F8FC\n"
                "BL      sub_FF94BF50\n"
                "B       loc_FF94E164\n"

"loc_FF94E0E4:\n"
                "BL      sub_FF94DEA8\n"
                "B       loc_FF94E164\n"

"loc_FF94E0EC:\n"
                "BL      sub_FF94F964\n"
                "BL      sub_FF94BF50\n"
                "B       loc_FF94E164\n"

"loc_FF94E0F8:\n"
                "BL      sub_FF94EB18\n"
                "B       loc_FF94E164\n"

"loc_FF94E100:\n"
                "BL      sub_FF95022C\n"
                "B       loc_FF94E164\n"

"loc_FF94E108:\n"
                "BL      sub_FF9504B4\n"
                "B       loc_FF94E164\n"

"loc_FF94E110:\n"
                "BL      sub_FF950528\n"
                "B       loc_FF94E164\n"
"loc_FF94E118:\n"
                "BL      sub_FF9505E0\n"
                "B       loc_FF94E164\n"

"loc_FF94E120:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF950678\n"
                "B       loc_FF94E164\n"

"loc_FF94E12C:\n"
                "BL      sub_FF9507C8\n"
                "B       loc_FF94E164\n"

"loc_FF94E134:\n"
                "BL      sub_FF95083C\n"
                "B       loc_FF94E164\n"

"loc_FF94E13C:\n"
                "BL      sub_FF9508F4\n"
                "B       loc_FF94E164\n"

"loc_FF94E144:\n"
                "BL      sub_FF9509C4\n"
                "B       loc_FF94E164\n"

"loc_FF94E14C:\n"
                "BL      sub_FF9509F0\n"
                "B       loc_FF94E164\n"
"loc_FF94E154:\n"
                "MOV     R1, #0x2DC\n"
                "LDR     R0, =0xff94dba0\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813BFC\n"

"loc_FF94E164:\n"
                "LDR     R2, [SP]\n"

"loc_FF94E168:\n"
                "LDR     R3, =0x73EF4\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF8206E8\n"
                "LDR     R0, [SP]\n"
                "BL      sub_FF94DC1C\n"

"loc_FF94E180:\n"
                "LDR     R3, =0x73EF8\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820EA4\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF94E038\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xff94dba0\n"
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813BFC\n"
                "BL      sub_FF822634\n"

                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"

);
}
