#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define NR_ON (1)
#define NR_OFF (0)

static long *nrflag = (long*)0x5760; // value above aMaincapt_c

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF95F450_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R3, =0x5758\n"
                "SUB     SP, SP, #4\n"
                "LDR     R2, [R3]\n"
                "LDR     R4, =0x575C\n"
                "CMP     R2, #0\n"
                "STR     R0, [R4]\n"
                "MOV     R8, #0\n"
                "LDR     R6, =0xFF95F388\n" // locret_FF95F388
                "BNE     loc_FF95F484\n"
                "LDR     R0, =0xFF95F444\n" // aMaincapt_c
                "MOV     R1, #0xDB\n"
                "BL      sub_FF813BE8\n" // DebugAssert
"loc_FF95F484:\n"
                "LDR     R3, =0x6FFDC\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF820720\n" // ClearEventFlag
                "BL      sub_FF95F3C0\n"
	    	"BL      capt_seq_hook_set_nr\n" // +

		"B       sub_FF95F498\n"
    );
}

void __attribute__((naked,noinline)) sub_FF95C3EC_my(long p)
{
    asm volatile (
                 "STMFD   SP!, {R4,R5,LR}\n"
                 "LDR     R5, [R0,#8]\n"
                 "BL      sub_FF969BE4\n"
                 "CMP     R0, #0\n"
                 "LDR     R0, =0xFF95C3C8\n" // aStrbctrlCharge
                 "BNE     loc_FF95C40C\n"
                 "BL      sub_FFAB981C\n" // printf
                 "BL      sub_FF969BF0\n"
"loc_FF95C40C:\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF95E21C\n"
                 "TST     R0, #1\n"
                 "MOV     R2, R5\n"
                 "MOV     R1, #1\n"
                 "BEQ     loc_FF95C42C\n"
                 "LDMFD   SP!, {R4,R5,LR}\n"
                 "B       sub_FF95B59C\n"
"loc_FF95C42C:\n"
                 "BL      sub_FF95AC38\n"
				 "MOV     R4, R0\n"
                 "BL      sub_FF825CA0\n"
                 "ADD     R3, R5, R5,LSL#1\n"
                 "RSB     R3, R5, R3,LSL#3\n"
                 "ADD     R4, R4, R3,LSL#2\n"
                 "STR     R0, [R4,#4]\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF95FCFC\n"
                 "BL      sub_FF95E7FC\n"
                 "BL      sub_FF95E76C\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF95F450_my\n" // S  
                 "BL      capt_seq_hook_raw_here\n" // +
                 "MOV     R2, R5\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF95B59C\n"
                 "LDMFD   SP!, {R4,R5,LR}\n"
                 "B       sub_FF95F698\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "SUB     SP, SP, #4\n"
                 "MOV     R4, SP\n"
                 "B       loc_FF95CDA0\n"

"loc_FF95CC1C:\n"
                 "LDR     R0, [SP]\n"
                 "LDR     R3, [R0]\n"
                 "CMP     R3, #0xF\n"
                 "LDRLS   PC, [PC,R3,LSL#2]\n"
                 "B       loc_FF95CD88\n"

                 ".long loc_FF95CC70\n"
                 ".long loc_FF95CC80\n"
                 ".long loc_FF95CC94\n"
                 ".long loc_FF95CCA4\n"
                 ".long loc_FF95CCB4\n"
                 ".long loc_FF95CCC4\n"
                 ".long loc_FF95CCD8\n"
                 ".long loc_FF95CCE8\n"
                 ".long loc_FF95CCFC\n"
                 ".long loc_FF95CD0C\n"
                 ".long loc_FF95CD1C\n"
                 ".long loc_FF95CD2C\n"
                 ".long loc_FF95CD3C\n"
                 ".long loc_FF95CD50\n"
                 ".long loc_FF95CD60\n"
                 ".long loc_FF95CD70\n"
"loc_FF95CC70:\n"
                 "BL      sub_FF95D3FC\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #8\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CC80:\n"
                 "BL      sub_FF95DB80\n"
                 "BL      shooting_expo_param_override\n"  // +
                 "BL      sub_FF95B1D0\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x10\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CC94:\n"
                 "BL      sub_FF95C3EC_my\n" // S 
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #2\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CCA4:\n"
                 "BL      sub_FF95E17C\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #1\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CCB4:\n"
                 "BL      sub_FF95DC1C\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x20\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CCC4:\n"
                 "BL      sub_FF95DD14\n"
                 "BL      sub_FF95B1D0\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x40\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CCD8:\n"
                 "BL      sub_FF95C59C\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x80\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CCE8:\n"
                 "BL      sub_FF95DE90\n"
                 "BL      sub_FF95B1D0\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x400\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CCFC:\n"
                 "BL      sub_FF95DC1C\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x800\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CD0C:\n"
                 "BL      sub_FF95E940\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x8000\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CD1C:\n"
                 "BL      sub_FF95ECF0\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x10000\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CD2C:\n"
                 "BL      sub_FF95EC10\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x20000\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CD3C:\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF95EDA8\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x40000\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CD50:\n"
                 "BL      sub_FF95F014\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x80000\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CD60:\n"
                 "BL      sub_FF95F08C\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x100000\n"
                 "B       loc_FF95CD7C\n"
"loc_FF95CD70:\n"
                 "BL      sub_FF95F0D8\n"
                 "LDR     R3, =0x6FF74\n"
                 "MOV     R1, #0x200000\n"
"loc_FF95CD7C:\n"
                 "LDR     R0, [R3]\n"
                 "BL      sub_FF820584\n" // SetEventFlag
                 "B       loc_FF95CD98\n"
"loc_FF95CD88:\n"
                 "MOV     R1, #0x374\n"
                 "LDR     R0, =0xFF95C09C\n" // aCaptseq_c
                 "ADD     R1, R1, #2\n"
                 "BL      sub_FF813BE8\n" // DebugAssert
"loc_FF95CD98:\n"
                 "LDR     R0, [SP]\n"
                 "BL      sub_FF95C11C\n"
"loc_FF95CDA0:\n"
                 "LDR     R3, =0x6FF78\n"
                 "MOV     R1, R4\n"
                 "LDR     R0, [R3]\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF820D8C\n" // ReceiveMessageQueue
                 "TST     R0, #1\n"
                 "BEQ     loc_FF95CC1C\n"
                 "LDR     R0, =0xFF95C09C\n" // aCaptseq_c
				 "MOV     R1, #0x2EC\n"
                 "BL      sub_FF813BE8\n" // DebugAssert
                 "BL      sub_FF8225B4\n" // ExitTask
                 "ADD     SP, SP, #4\n"
                 "LDMFD   SP!, {R4,PC}\n"
	);
}

