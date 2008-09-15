#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (2)
#define NR_OFF (1)

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
    long *nrflag = (long*)0xCF74;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = 1;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = 2;
	break;
    };
}



void __attribute__((naked,noinline)) sub_FFE71CC4_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFE726EC\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "BL      sub_FFE81DB8\n"
                "MOV     R0, #0x8A\n"
                "ADD     R1, SP, #0x14-0x10\n"
                "MOV     R2, #4\n"
                "BL      sub_FFC0B79C\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFE71D04\n"
                "MOV     R1, #0x1D0\n"
                "LDR     R0, =0xFFE71B48\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FFE8F444\n"
"loc_FFE71D04:\n"
                "LDR     R3, =0x94240\n"
                "LDR     R2, =0x94300\n"
                "LDR     R0, [R3,#0x74]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FFDCBEF4\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE71ACC\n"
                "BL      wait_until_remote_button_is_released\n"
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0xCF78\n"
                "LDR     R0, [R3]\n"
                "B       sub_FFE71D28\n"
    );
}

void __attribute__((naked,noinline)) sub_FFE6ED50_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R3, [R4,#8]\n"
                "ORR     R3, R3, #1\n"
                "STR     R3, [R4,#8]\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFE78B8C\n"
                "TST     R0, #1\n"
                "MOV     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, R0\n"
                "BEQ     loc_FFE6ED94\n"
                "LDR     R3, [R4,#8]\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFE6D5EC\n"
"loc_FFE6ED94:\n"
                "BL      sub_FFE6F7E8\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE7081C\n"
                "TST     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FFE6EDB8\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFE6D5EC\n"
"loc_FFE6EDB8:\n"
                "BL      sub_FFC0B998\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE71BAC\n"
                "BL      sub_FFE72558\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE71CC4_my\n"
                "BL      capt_seq_hook_raw_here\n"
                "MOV     R1, #1\n"
                "MOV     R2, R4\n"
                "BL      sub_FFE6D5EC\n"
                "BL      sub_FFE71FF8\n"
                "CMP     R0, #0\n"
                "LDRNE   R3, [R4,#8]\n"
                "ORRNE   R3, R3, #0x2000\n"
                "STRNE   R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,PC}\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()    //IDA task_CaptSeqTask
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFE6F2BC\n"
"loc_FFE6F160:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFE6F290\n"

                ".long loc_FFE6F1D0\n"
                ".long loc_FFE6F1DC\n"
                ".long loc_FFE6F1E4\n"
                ".long loc_FFE6F1F8\n"
                ".long loc_FFE6F1F0\n"
                ".long loc_FFE6F200\n"
                ".long loc_FFE6F208\n"
                ".long loc_FFE6F214\n"
                ".long loc_FFE6F21C\n"
                ".long loc_FFE6F228\n"
                ".long loc_FFE6F230\n"
                ".long loc_FFE6F238\n"
                ".long loc_FFE6F240\n"
                ".long loc_FFE6F248\n"
                ".long loc_FFE6F250\n"
                ".long loc_FFE6F25C\n"
                ".long loc_FFE6F264\n"
                ".long loc_FFE6F26C\n"
                ".long loc_FFE6F274\n"
                ".long loc_FFE6F280\n"
                ".long loc_FFE6F288\n"
                ".long loc_FFE6F2A4\n"
"loc_FFE6F1D0:\n"
                "BL      sub_FFE6F7FC\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFE6D0DC\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F1DC:\n"
                "BL      sub_FFE6ED50_my\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F1E4:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFE6F9D0\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F1F0:\n"
                "BL      sub_FFE6F3A0\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F1F8:\n"
                "BL      sub_FFE6F7C8\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F200:\n"
                "BL      sub_FFE6F7D8\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F208:\n"
                "BL      sub_FFE6F8E0\n"
                "BL      sub_FFE6D0DC\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F214:\n"
                "BL      sub_FFE6EE5C\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F21C:\n"
                "BL      sub_FFE6F944\n"
                "BL      sub_FFE6D0DC\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F228:\n"
                "BL      sub_FFE6F7C8\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F230:\n"
                "BL      sub_FFE70F30\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F238:\n"
                "BL      sub_FFE710FC\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F240:\n"
                "BL      sub_FFE71190\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F248:\n"
                "BL      sub_FFE7128C\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F250:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFE714F8\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F25C:\n"
                "BL      sub_FFE716B0\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F264:\n"
                "BL      sub_FFE71744\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F26C:\n"
                "BL      sub_FFE71800\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F274:\n"
                "BL      sub_FFE6FB24\n"
                "BL      sub_FFE6EC74\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F280:\n"
                "BL      sub_FFE713CC\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F288:\n"
                "BL      sub_FFE71428\n"
                "B       loc_FFE6F2A0\n"
"loc_FFE6F290:\n"
                "MOV     R1, #0x4C0\n"
                "LDR     R0, =0xFFE6EAD0\n"
                "ADD     R1, R1, #0xE\n"
                "BL      sub_FFE8F444\n"
"loc_FFE6F2A0:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
"loc_FFE6F2A4:\n"
                "LDR     R3, =0x6E2B8\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFE81C1C\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFE6EB50\n"
"loc_FFE6F2BC:\n"
                "LDR     R3, =0x6E2BC\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFE82334\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFE6F160\n"
                "LDR     R0, =0xFFE6EAD0\n"
                "MOV     R1, #0x400\n"
                "BL      sub_FFE8F444\n"
                "BL      sub_FFE838F8\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

