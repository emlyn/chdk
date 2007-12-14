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
    long *nrflag = (long*)0x5724;

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


void __attribute__((naked,noinline)) sub_FF96F5D0_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R3, =0x571C\n"
                "SUB     SP, SP, #4\n"
                "LDR     R2, [R3]\n"
                "LDR     R4, =0x5720\n"
                "CMP     R2, #0\n"
                "STR     R0, [R4]\n"
                "MOV     R8, #0\n"
                "LDR     R6, =0xFF96F508\n"
                "BNE     loc_FF96F604\n"
                "LDR     R0, =0xFF96F5C4\n"
                "MOV     R1, #0xDB\n"
                "BL      sub_FF813D58\n"
"loc_FF96F604:\n"
                "LDR     R3, =0x5D164\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF8208C8\n"
                "BL      sub_FF96F540\n"
	    	"BL      capt_seq_hook_set_nr\n"

		"B       sub_FF96F618\n"
    );
}

void __attribute__((naked,noinline)) sub_FF96C05C_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R5, [R0,#8]\n"
                "BL      sub_FF97AE48\n"
                "CMP     R0, #0\n"
                "LDR     R0, =0xFF96C038\n"
                "BNE     loc_FF96C07C\n"
                "BL      sub_FFAF213C\n"
                "BL      sub_FF97AE54\n"
"loc_FF96C07C:\n"
                "BL      sub_FF96A0BC\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "RSB     R3, R5, R3,LSL#3\n"
                "MOV     R6, R3,LSL#2\n"
                "ADD     R0, R6, R0\n"
                "LDR     R3, [R0,#8]\n"
                "CMP     R3, #0\n"
                "BEQ     loc_FF96C0A0\n"
                "BL      sub_FF953B98\n"
"loc_FF96C0A0:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96E07C\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF96C0C0\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FF96AE1C\n"
"loc_FF96C0C0:\n"
                "BL      sub_FF96A0BC\n"
                "MOV     R4, R0\n"
                "BL      sub_FF825F00\n"
                "ADD     R4, R6, R4\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96FF14\n"
                "BL      sub_FF96E6D8\n"
                "BL      sub_FF96E644\n"
                "MOV     R0, R5\n"
                "BL      sub_FF96F5D0_my\n"
                "BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF96AE1C\n"
                "BL      sub_FF96F894\n"
                "BL      sub_FF96A0BC\n"
                "ADD     R0, R6, R0\n"
                "LDR     R3, [R0,#8]\n"
                "CMP     R3, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "LDMFD   SP!, {R4-R6,LR}\n"
                "B       sub_FF953BD4\n"

    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF96CBD8\n"
"loc_FF96CA28:\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "LDR     R3, [R0]\n"
                "CMP     R3, #0x11\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF96CBC0\n"
                ".long loc_FF96CA84\n"
                ".long loc_FF96CA94\n"
                ".long loc_FF96CAA8\n"
                ".long loc_FF96CAB8\n"
                ".long loc_FF96CAC8\n"
                ".long loc_FF96CAD8\n"
                ".long loc_FF96CAEC\n"
                ".long loc_FF96CAFC\n"
                ".long loc_FF96CB10\n"
                ".long loc_FF96CB20\n"
                ".long loc_FF96CB30\n"
                ".long loc_FF96CB40\n"
                ".long loc_FF96CB50\n"
                ".long loc_FF96CB64\n"
                ".long loc_FF96CB74\n"
                ".long loc_FF96CB84\n"
                ".long loc_FF96CB94\n"
                ".long loc_FF96CBA8\n"
"loc_FF96CA84:\n"
                "BL      sub_FF96D24C\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #8\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CA94:\n"
                "BL      sub_FF96D9D0\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF96A98C\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x10\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CAA8:\n"
                "BL      sub_FF96C05C_my\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #2\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CAB8:\n"
                "BL      sub_FF96DFE0\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #1\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CAC8:\n"
                "BL      sub_FF96DA80\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x20\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CAD8:\n"
                "BL      sub_FF96DB78\n"
                "BL      sub_FF96A98C\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x40\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CAEC:\n"
                "BL      sub_FF96C240\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x80\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CAFC:\n"
                "BL      sub_FF96DCF0\n"
                "BL      sub_FF96A98C\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x400\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB10:\n"
                "BL      sub_FF96DA80\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x800\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB20:\n"
                "BL      sub_FF96E81C\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x8000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB30:\n"
                "BL      sub_FF96EBF8\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x10000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB40:\n"
                "BL      sub_FF96EB14\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x20000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB50:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF96ECB0\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x40000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB64:\n"
                "BL      sub_FF96EFBC\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x80000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB74:\n"
                "BL      sub_FF96F034\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x100000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB84:\n"
                "BL      sub_FF96F080\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x200000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CB94:\n"
                "MOV     R0, #1\n"
                "BL      sub_FF96ECB0\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x400000\n"
                "B       loc_FF96CBB4\n"
"loc_FF96CBA8:\n"
                "BL      sub_FF96F0E8\n"
                "LDR     R3, =0x5D0FC\n"
                "MOV     R1, #0x800000\n"
"loc_FF96CBB4:\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF82072C\n"
                "B       loc_FF96CBD0\n"
"loc_FF96CBC0:\n"
                "MOV     R1, #0x374\n"
                "LDR     R0, =0xFF96BD0C\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FF813D58\n"
"loc_FF96CBD0:\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FF96BD8C\n"
"loc_FF96CBD8:\n"
                "LDR     R3, =0x5D100\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820F34\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF96CA28\n"
                "LDR     R0, =0xFF96BD0C\n"
                "MOV     R1, #0x2EC\n"
                "BL      sub_FF813D58\n"
                "BL      sub_FF82275C\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

