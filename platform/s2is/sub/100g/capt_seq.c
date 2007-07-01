#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (1)
#define NR_OFF (0)

static long raw_save_stage;

void capt_seq_hook_raw_here()
{
    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available();
    while (raw_save_stage != RAWDATA_SAVED){
	_SleepTask(10);
    }
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}


void capt_seq_hook_set_nr()
{
    long *nrflag = (long*)0x5754;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = 0;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = 1;
	break;
    };
}

void __attribute__((naked,noinline)) sub_FF96F334_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R3, =0x574C\n"
                "SUB     SP, SP, #4\n"
                "LDR     R2, [R3]\n"
                "LDR     R4, =0x5750\n"
                "CMP     R2, #0\n"
                "STR     R0, [R4]\n"
                "MOV     R8, #0\n"
                "LDR     R6, =0xFF96F26C\n"
                "BNE     loc_FF96F368\n"
                "LDR     R0, =0xFF96F328\n"
                "MOV     R1, #0xDB\n"
                "BL      sub_FF813D58\n"
"loc_FF96F368:\n"
                "LDR     R3, =0x5D184\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF8208C8\n"
                "BL      sub_FF96F2A4\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "B       sub_FF96F37C\n"
    );
}

void __attribute__((naked,noinline)) sub_FF96BDC0_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R5, [R0,#8]\n"
                "BL      sub_FF97ABAC\n"
                "CMP     R0, #0\n"
                "LDR     R0, =0xFF96BD9C\n"
                "BNE     loc_FF96BDE0\n"
                "BL      sub_FFAF1F48\n"
                "BL      sub_FF97ABB8\n"
"loc_FF96BDE0:\n"
                "BL      sub_FF969E20\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "RSB     R3, R5, R3,LSL#3\n"
                "MOV     R6, R3,LSL#2\n"
                "ADD     R0, R6, R0\n"
                "LDR     R3, [R0,#8]\n"
                "CMP     R3, #0\n"
                "BEQ     loc_FF96BE04\n"
                "BL      sub_FF9538FC\n"
"loc_FF96BE04:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96DDE0\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF96BE24\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FF96AB80\n"
"loc_FF96BE24:\n"
                "BL      sub_FF969E20\n"
                "MOV     R4, R0\n"
                "BL      sub_FF825F00\n"
                "ADD     R4, R6, R4\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96FC78\n"
                "BL      sub_FF96E43C\n"
                "BL      sub_FF96E3A8\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96F334_my\n"
                "BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF96AB80\n"
                "BL      sub_FF96F5F8\n"
                "BL      sub_FF969E20\n"
                "ADD     R0, R6, R0\n"
                "LDR     R3, [R0,#8]\n"
                "CMP     R3, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FF953938\n"

    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF96C93C\n"
"loc_FF96C78C:\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "LDR     R3, [R0]\n"
                "CMP     R3, #0x11\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF96C924\n"
                ".long loc_FF96C7E8\n"
                ".long loc_FF96C7F8\n"
                ".long loc_FF96C80C\n"
                ".long loc_FF96C81C\n"
                ".long loc_FF96C82C\n"
                ".long loc_FF96C83C\n"
                ".long loc_FF96C850\n"
                ".long loc_FF96C860\n"
                ".long loc_FF96C874\n"
                ".long loc_FF96C884\n"
                ".long loc_FF96C894\n"
                ".long loc_FF96C8A4\n"
                ".long loc_FF96C8B4\n"
                ".long loc_FF96C8C8\n"
                ".long loc_FF96C8D8\n"
                ".long loc_FF96C8E8\n"
                ".long loc_FF96C8F8\n"
                ".long loc_FF96C90C\n"
"loc_FF96C7E8:\n"
                "BL      sub_FF96CFB0\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #8\n"
                "B       loc_FF96C918\n"
"loc_FF96C7F8:\n"
                "BL      sub_FF96D734\n"
                "BL      sub_FF96A6F0\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x10\n"
                "B       loc_FF96C918\n"
"loc_FF96C80C:\n"
                "BL      sub_FF96BDC0_my\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #2\n"
                "B       loc_FF96C918\n"
"loc_FF96C81C:\n"
                "BL      sub_FF96DD44\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #1\n"
                "B       loc_FF96C918\n"
"loc_FF96C82C:\n"
                "BL      sub_FF96D7E4\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x20\n"
                "B       loc_FF96C918\n"
"loc_FF96C83C:\n"
                "BL      sub_FF96D8DC\n"
                "BL      sub_FF96A6F0\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x40\n"
                "B       loc_FF96C918\n"
"loc_FF96C850:\n"
                "BL      sub_FF96BFA4\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x80\n"
                "B       loc_FF96C918\n"
"loc_FF96C860:\n"
                "BL      sub_FF96DA54\n"
                "BL      sub_FF96A6F0\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x400\n"
                "B       loc_FF96C918\n"
"loc_FF96C874:\n"
                "BL      sub_FF96D7E4\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x800\n"
                "B       loc_FF96C918\n"
"loc_FF96C884:\n"
                "BL      sub_FF96E580\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x8000\n"
                "B       loc_FF96C918\n"
"loc_FF96C894:\n"
                "BL      sub_FF96E95C\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x10000\n"
                "B       loc_FF96C918\n"
"loc_FF96C8A4:\n"
                "BL      sub_FF96E878\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x20000\n"
                "B       loc_FF96C918\n"
"loc_FF96C8B4:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF96EA14\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x40000\n"
                "B       loc_FF96C918\n"
"loc_FF96C8C8:\n"
                "BL      sub_FF96ED20\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x80000\n"
                "B       loc_FF96C918\n"
"loc_FF96C8D8:\n"
                "BL      sub_FF96ED98\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x100000\n"
                "B       loc_FF96C918\n"
"loc_FF96C8E8:\n"
                "BL      sub_FF96EDE4\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x200000\n"
                "B       loc_FF96C918\n"
"loc_FF96C8F8:\n"
                "MOV     R0, #1\n"
                "BL      sub_FF96EA14\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x400000\n"
                "B       loc_FF96C918\n"
"loc_FF96C90C:\n"
                "BL      sub_FF96EE4C\n"
                "LDR     R3, =0x5D11C\n"
                "MOV     R1, #0x800000\n"
"loc_FF96C918:\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF82072C\n"
                "B       loc_FF96C934\n"
"loc_FF96C924:\n"
                "MOV     R1, #0x374\n"
                "LDR     R0, =0xFF96BA70\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813D58\n"
"loc_FF96C934:\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FF96BAF0\n"
"loc_FF96C93C:\n"
                "LDR     R3, =0x5D120\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820F34\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF96C78C\n"
                "LDR     R0, =0xFF96BA70\n"
                "MOV     R1, #0x2EC\n"
                "BL      sub_FF813D58\n"
                "BL      sub_FF82275C\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

