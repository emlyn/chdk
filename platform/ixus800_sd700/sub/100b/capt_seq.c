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
    long *nrflag = (long*)0x61B0;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = NR_OFF;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = NR_ON;
	break;
    };
}


void __attribute__((naked,noinline)) sub_FF961D20_my(long p)
{                                        
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R3, =0x6F2EC\n"
                "LDR     R5, =0x61AC\n"
                "SUB     SP, SP, #4\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FF04\n" //ClearEventFlag
                "LDR     R3, =0x99F00\n"
                "LDR     R0, [R3,#0x7C]\n"
                "BL      sub_FF89E028\n" //IsEmptyWriteCache_42
                "BL      sub_FF961C74\n"
	    	"BL      capt_seq_hook_set_nr\n"

		"B       sub_FF961D50\n"
    );
}

void __attribute__((naked,noinline)) sub_FF95E860_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "BL      sub_FF967028\n"
                "CMP     R0, #0\n"
                "BNE     loc_FF95E878\n"
                "BL      sub_FF967034\n"
"loc_FF95E878:\n"
                "LDR     R3, =0x99F00\n"
                "LDR     R2, [R3,#0x24]\n"
                "CMP     R2, #0\n"
                "BNE     loc_FF95E8AC\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FF967048\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF95E8AC\n"
                "MOV     R0, #1\n"
"loc_FF95E89C:\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF95CF48\n"
"loc_FF95E8AC:\n"
                "LDR     R5, =0x99F00\n"
                "LDR     R3, [R5,#0x24]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF95E8C8\n"
                "MOV     R0, #2\n"
                "BL      sub_FFAB8A90\n"
                "LDR     R3, [R5,#0x24]\n"
"loc_FF95E8C8:\n"
                "CMP     R3, #0\n"
                "BNE     loc_FF95E910\n"
                "MOV     R0, R4\n"
                "BL      sub_FF960ADC\n"
                "TST     R0, #1\n"
                "BNE     loc_FF95E89C\n"
                "BL      sub_FF99FE38\n"
                "BL      sub_FF824ADC\n"
                "LDR     R2, =0x99E44\n"
                "ADD     R3, R4, R4,LSL#1\n"
                "STR     R0, [R2,R3,LSL#5]\n"
                "MOV     R0, R4\n"
                "BL      sub_FF96248C\n"
                "BL      sub_FF960FE0\n"
                "BL      sub_FF960F7C\n"
                "MOV     R0, R4\n"
                "BL      sub_FF961D20_my\n"          //------------>
                "BL      capt_seq_hook_raw_here\n"   // +
                "B       loc_FF95E924\n"         
"loc_FF95E910:\n"
                "LDR     R3, =0x619C\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
"loc_FF95E924:\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BL      sub_FF95CF48\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF961F18\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF95EE60\n"
"loc_FF95ECF8:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x14\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF95EE34\n"
                ".long loc_FF95ED64\n"
                ".long loc_FF95ED84\n"
                ".long loc_FF95ED98\n"
                ".long loc_FF95EDA8\n"
                ".long loc_FF95EDA0\n"
                ".long loc_FF95EDB0\n"
                ".long loc_FF95EDB8\n"
                ".long loc_FF95EDC4\n"
                ".long loc_FF95EDCC\n"
                ".long loc_FF95EDD8\n"
                ".long loc_FF95EDE0\n"
                ".long loc_FF95EDE8\n"
                ".long loc_FF95EDF0\n"
                ".long loc_FF95EDF8\n"
                ".long loc_FF95EE00\n"
                ".long loc_FF95EE0C\n"
                ".long loc_FF95EE14\n"
                ".long loc_FF95EE1C\n"
                ".long loc_FF95EE24\n"
                ".long loc_FF95EE2C\n"
                ".long loc_FF95EE48\n"
"loc_FF95ED64:\n"
                "BL      sub_FF96073C\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF95CA68\n"
                "LDR     R3, =0x99F00\n"
                "LDR     R2, [R3,#0x24]\n"
                "CMP     R2, #0\n"
                "BEQ     loc_FF95EE44\n"
                "BL      sub_FF95E944\n"
                "B       loc_FF95EE44\n"
"loc_FF95ED84:\n"
                "BL      sub_FF95E860_my\n"   //--------------->
"loc_FF95ED88:\n"
                "LDR     R2, =0x99F00\n"
                "MOV     R3, #0\n"
                "STR     R3, [R2,#0x24]\n"
                "B       loc_FF95EE44\n"
"loc_FF95ED98:\n"
                "BL      sub_FF960ACC\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDA0:\n"
                "BL      sub_FF95F934\n"
                "B       loc_FF95ED88\n"
"loc_FF95EDA8:\n"
                "BL      sub_FF95FCD0\n"
                "B       loc_FF95ED88\n"
"loc_FF95EDB0:\n"
                "BL      sub_FF95FCE0\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDB8:\n"
                "BL      sub_FF960820\n"
                "BL      sub_FF95CA68\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDC4:\n"
                "BL      sub_FF95EA18\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDCC:\n"
                "BL      sub_FF960888\n"
                "BL      sub_FF95CA68\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDD8:\n"
                "BL      sub_FF95FCD0\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDE0:\n"
                "BL      sub_FF961020\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDE8:\n"
                "BL      sub_FF961364\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDF0:\n"
                "BL      sub_FF9613E8\n"
                "B       loc_FF95EE44\n"
"loc_FF95EDF8:\n"
                "BL      sub_FF9614D8\n"
                "B       loc_FF95EE44\n"
"loc_FF95EE00:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF9615A0\n"
                "B       loc_FF95EE44\n"
"loc_FF95EE0C:\n"
                "BL      sub_FF96170C\n"
                "B       loc_FF95EE44\n"
"loc_FF95EE14:\n"
                "BL      sub_FF9617A0\n"
                "B       loc_FF95EE44\n"
"loc_FF95EE1C:\n"
                "BL      sub_FF96185C\n"
                "B       loc_FF95EE44\n"
"loc_FF95EE24:\n"
                "BL      sub_FF961948\n"
                "B       loc_FF95EE44\n"
"loc_FF95EE2C:\n"
                "BL      sub_FF96199C\n"
                "B       loc_FF95EE44\n"
"loc_FF95EE34:\n"
                "MOV     R1, #0x36C\n"
                "LDR     R0, =0xFF95E5EC\n"
                "ADD     R1, R1, #1\n"
                "BL      sub_FF813B80\n"
"loc_FF95EE44:\n"
                "LDR     R2, [SP]\n"
"loc_FF95EE48:\n"
                "LDR     R3, =0x6F274\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FD68\n"
                "LDR     R0, [SP]\n" 	
                "BL      sub_FF95E668\n"
"loc_FF95EE60:\n"
                "LDR     R3, =0x6F278\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820480\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF95ECF8\n"
                "MOV     R1, #0x2A4\n"
                "LDR     R0, =0xFF95E5EC\n"
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813B80\n"
                "BL      sub_FF8219DC\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

