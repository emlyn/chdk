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
    long *nrflag = (long*)0x6208;

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



void __attribute__((naked,noinline)) sub_FFD56070_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFD56A2C\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "BL      sub_FFC103A4\n"
                "LDR     R0, =0x122\n"
                "ADD     R1, SP, #0x14-0x10\n"
                "MOV     R2, #4\n"
                "BL      sub_FFC14DE4\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD560B0\n"
                "LDR     R0, =0xFFD55EEC\n"
                "MOV     R1, #0x1BC\n"
                "BL      sub_FFC03CF8\n"
"loc_FFD560B0:\n"
                "LDR     R3, =0x91AA0\n"
                "LDR     R2, =0x91B60\n"
                "LDR     R0, [R3,#0x80]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                //"BL      nullsub_49\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD55E70\n"
            "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x620C\n"
                "LDR     R0, [R3]\n"

		"B       sub_FFD560D4\n"
    );
}

void __attribute__((naked,noinline)) sub_FFD5307C_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0x91AA0\n"
                "LDR     R5, [R0,#0xC]\n"
                "LDR     R1, [R3,#0x24]\n"
                "LDR     R2, [R5,#8]\n"
                "CMP     R1, #0\n"
                "ORR     R2, R2, #1\n"
                "STR     R2, [R5,#8]\n"
                "BNE     loc_FFD530D0\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFD5CA00\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD530D0\n"
                "LDR     R3, [R5,#8]\n"
                "MOV     R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R5,#8]\n"
"loc_FFD530C0:\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD518C4\n"
"loc_FFD530D0:\n"
                "LDR     R4, =0x91AA0\n"
                "BL      sub_FFD53B6C\n"
                "LDR     R3, [R4,#0x24]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FFD53118\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD54C10\n"
                "TST     R0, #1\n"
                "BNE     loc_FFD530C0\n"
                "BL      sub_FFD9385C\n"
                "BL      sub_FFC14FE0\n"
                "STR     R0, [R5,#0x14]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD55F58\n"
                "BL      sub_FFD568B8\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD56070_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "B       loc_FFD5312C\n"
"loc_FFD53118:\n"
                "LDR     R3, =0x61EC\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
"loc_FFD5312C:\n"
                "MOV     R1, #1\n"
                "MOV     R2, R5\n"
                "BL      sub_FFD518C4\n"
                "BL      sub_FFD563A4\n"
                "CMP     R0, #0\n"
                "LDRNE   R3, [R5,#8]\n"
                "ORRNE   R3, R3, #0x2000\n"
                "STRNE   R3, [R5,#8]\n"
                "LDMFD   SP!, {R4,R5,PC}\n"


    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFD536F0\n"
"loc_FFD53564:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x16\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFD536C4\n"
                ".long loc_FFD535D8\n"
                ".long loc_FFD535F8\n"
                ".long loc_FFD5360C\n"
                ".long loc_FFD53620\n"
                ".long loc_FFD53618\n"
                ".long loc_FFD53628\n"
                ".long loc_FFD53630\n"
                ".long loc_FFD5363C\n"
                ".long loc_FFD53644\n"
                ".long loc_FFD53650\n"
                ".long loc_FFD53658\n"
                ".long loc_FFD53660\n"
                ".long loc_FFD53668\n"
                ".long loc_FFD53670\n"
                ".long loc_FFD53678\n"
                ".long loc_FFD53684\n"
                ".long loc_FFD5368C\n"
                ".long loc_FFD53694\n"
                ".long loc_FFD5369C\n"
                ".long loc_FFD536A8\n"
                ".long loc_FFD536B4\n"
                ".long loc_FFD536BC\n"
                ".long loc_FFD536D8\n"
"loc_FFD535D8:\n"
                "BL      sub_FFD53B94\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFD51358\n"
                "LDR     R3, =0x91AA0\n"
                "LDR     R2, [R3,#0x24]\n"
                "CMP     R2, #0\n"
                "BEQ     loc_FFD536D4\n"
                "BL      sub_FFD53158\n"
                "B       loc_FFD536D4\n"
"loc_FFD535F8:\n"
                "BL      sub_FFD5307C_my\n"
"loc_FFD535FC:\n"
                "LDR     R2, =0x91AA0\n"
                "MOV     R3, #0\n"
                "STR     R3, [R2,#0x24]\n"
                "B       loc_FFD536D4\n"
"loc_FFD5360C:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD53D84\n"
                "B       loc_FFD536D4\n"
"loc_FFD53618:\n"
                "BL      sub_FFD537E8\n"
                "B       loc_FFD535FC\n"
"loc_FFD53620:\n"
                "BL      sub_FFD53B4C\n"
                "B       loc_FFD535FC\n"
"loc_FFD53628:\n"
                "BL      sub_FFD53B5C\n"
                "B       loc_FFD536D4\n"
"loc_FFD53630:\n"
                "BL      sub_FFD53C7C\n"
                "BL      sub_FFD51358\n"
                "B       loc_FFD536D4\n"
"loc_FFD5363C:\n"
                "BL      sub_FFD53230\n"
                "B       loc_FFD536D4\n"
"loc_FFD53644:\n"
                "BL      sub_FFD53CE4\n"
                "BL      sub_FFD51358\n"
                "B       loc_FFD536D4\n"
"loc_FFD53650:\n"
                "BL      sub_FFD53B4C\n"
                "B       loc_FFD536D4\n"
"loc_FFD53658:\n"
                "BL      sub_FFD5533C\n"
                "B       loc_FFD536D4\n"
"loc_FFD53660:\n"
                "BL      sub_FFD55508\n"
                "B       loc_FFD536D4\n"
"loc_FFD53668:\n"
                "BL      sub_FFD5559C\n"
                "B       loc_FFD536D4\n"
"loc_FFD53670:\n"
                "BL      sub_FFD55638\n"
                "B       loc_FFD536D4\n"
"loc_FFD53678:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFD558A4\n"
                "B       loc_FFD536D4\n"
"loc_FFD53684:\n"
                "BL      sub_FFD55A5C\n"
                "B       loc_FFD536D4\n"
"loc_FFD5368C:\n"
                "BL      sub_FFD55AEC\n"
                "B       loc_FFD536D4\n"
"loc_FFD53694:\n"
                "BL      sub_FFD55BA4\n"
                "B       loc_FFD536D4\n"
"loc_FFD5369C:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD558A4\n"
                "B       loc_FFD536D4\n"
"loc_FFD536A8:\n"
                "BL      sub_FFD53EA0\n"
                "BL      sub_FFD52FA4\n"
                "B       loc_FFD536D4\n"
"loc_FFD536B4:\n"
                "BL      sub_FFD55778\n"
                "B       loc_FFD536D4\n"
"loc_FFD536BC:\n"
                "BL      sub_FFD557D0\n"
                "B       loc_FFD536D4\n"
"loc_FFD536C4:\n"
                "MOV     R1, #0x4E0\n"
                "LDR     R0, =0xFFD52E00\n"
                "ADD     R1, R1, #9\n"
                "BL      sub_FFC03CF8\n"
"loc_FFD536D4:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
"loc_FFD536D8:\n"
                "LDR     R3, =0x66DA4\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC10208\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFD52E7C\n"
"loc_FFD536F0:\n"
                "LDR     R3, =0x66DA8\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC10920\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD53564\n"
                "MOV     R1, #0x410\n"
                "LDR     R0, =0xFFD52E00\n"
                "ADD     R1, R1, #0xB\n"
                "BL      sub_FFC03CF8\n"
                "BL      sub_FFC11E7C\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}



