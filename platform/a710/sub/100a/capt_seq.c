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
    long *nrflag = (long*)0x621C;

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



void __attribute__((naked,noinline)) sub_FFD5F178_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFD5FB34\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "BL      sub_FFC103A4\n"
                "LDR     R0, =0x122\n"
                "ADD     R1, SP, #0x14-0x10\n"
                "MOV     R2, #4\n"
                "BL      sub_FFC14DEC\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD5F1B8\n"
                "LDR     R0, =0xFFD5EFF4\n"
                "MOV     R1, #0x1BC\n"
                "BL      sub_FFC03CF8\n"
"loc_FFD5F1B8:\n"
                "LDR     R3, =0x9CB20\n"
                "LDR     R2, =0x9CBE0\n"
                "LDR     R0, [R3,#0x78]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FFC90768\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD5EF78\n"
            "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6220\n"
                "LDR     R0, [R3]\n"

		"B       sub_FFD5F1DC\n"
    );
}

void __attribute__((naked,noinline)) sub_FFD5C2C4_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R3, [R4,#8]\n"
                "ORR     R3, R3, #1\n"
                "STR     R3, [R4,#8]\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFD6581C\n"
                "TST     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R0, #2\n"
                "BEQ     loc_FFD5C30C\n"
                "LDR     R3, [R4,#8]\n"
                "SUB     R0, R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "MOV     R1, R0\n"
                "STR     R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFD5AA1C\n"
"loc_FFD5C30C:\n"
                "BL      sub_FFEA6BEC\n"
                "BL      sub_FFD5CD8C\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD5DD50\n"
                "TST     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FFD5C334\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFD5AA1C\n"
"loc_FFD5C334:\n"
                "BL      sub_FFD9ADF8\n"
                "BL      sub_FFC14FE8\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD5F060\n"
                "BL      sub_FFD5F9C0\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD5F178_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R1, #1\n"
                "MOV     R2, R4\n"
                "BL      sub_FFD5AA1C\n"
                "BL      sub_FFD5F4AC\n"
                "CMP     R0, #0\n"
                "LDRNE   R3, [R4,#8]\n"
                "ORRNE   R3, R3, #0x2000\n"
                "STRNE   R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,PC}\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFD5C878\n"
"loc_FFD5C70C:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x16\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFD5C84C\n"
                ".long loc_FFD5C780\n"
                ".long loc_FFD5C78C\n"
                ".long loc_FFD5C794\n"
                ".long loc_FFD5C7A8\n"
                ".long loc_FFD5C7A0\n"
                ".long loc_FFD5C7B0\n"
                ".long loc_FFD5C7B8\n"
                ".long loc_FFD5C7C4\n"
                ".long loc_FFD5C7CC\n"
                ".long loc_FFD5C7D8\n"
                ".long loc_FFD5C7E0\n"
                ".long loc_FFD5C7E8\n"
                ".long loc_FFD5C7F0\n"
                ".long loc_FFD5C7F8\n"
                ".long loc_FFD5C800\n"
                ".long loc_FFD5C80C\n"
                ".long loc_FFD5C814\n"
                ".long loc_FFD5C81C\n"
                ".long loc_FFD5C824\n"
                ".long loc_FFD5C830\n"
                ".long loc_FFD5C83C\n"
                ".long loc_FFD5C844\n"
                ".long loc_FFD5C860\n"
"loc_FFD5C780:\n"
                "BL      sub_FFD5CDA0\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFD5A518\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C78C:\n"
                "BL      sub_FFD5C2C4_my\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C794:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD5CF94\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7A0:\n"
                "BL      sub_FFD5C96C\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7A8:\n"
                "BL      sub_FFD5CD6C\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7B0:\n"
                "BL      sub_FFD5CD7C\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7B8:\n"
                "BL      sub_FFD5CE8C\n"
                "BL      sub_FFD5A518\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7C4:\n"
                "BL      sub_FFD5C3D8\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7CC:\n"
                "BL      sub_FFD5CEF4\n"
                "BL      sub_FFD5A518\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7D8:\n"
                "BL      sub_FFD5CD6C\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7E0:\n"
                "BL      sub_FFD5E444\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7E8:\n"
                "BL      sub_FFD5E610\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7F0:\n"
                "BL      sub_FFD5E6A4\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C7F8:\n"
                "BL      sub_FFD5E740\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C800:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFD5E9AC\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C80C:\n"
                "BL      sub_FFD5EB64\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C814:\n"
                "BL      sub_FFD5EBF4\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C81C:\n"
                "BL      sub_FFD5ECAC\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C824:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD5E9AC\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C830:\n"
                "BL      sub_FFD5D0D0\n"
                "BL      sub_FFD5C1EC\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C83C:\n"
                "BL      sub_FFD5E880\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C844:\n"
                "BL      sub_FFD5E8D8\n"
                "B       loc_FFD5C85C\n"
"loc_FFD5C84C:\n"
                "MOV     R1, #0x4E0\n"
                "LDR     R0, =0xFFD5C048\n"
                "ADD     R1, R1, #9\n"
                "BL      sub_FFC03CF8\n"
"loc_FFD5C85C:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
"loc_FFD5C860:\n"
                "LDR     R3, =0x71C94\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC10208\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFD5C0C4\n"
"loc_FFD5C878:\n"
                "LDR     R3, =0x71C98\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC10920\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD5C70C\n"
                "MOV     R1, #0x410\n"
                "LDR     R0, =0xFFD5C048\n"
                "ADD     R1, R1, #0xB\n"
                "BL      sub_FFC03CF8\n"
                "BL      sub_FFC11E7C\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

