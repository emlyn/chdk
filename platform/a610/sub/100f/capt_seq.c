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
    long *nrflag = (long*)0x6CE0;

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


void __attribute__((naked,noinline)) sub_FFD399A8_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0x73D34\n"
                "LDR     R5, =0x6CDC\n"
                "SUB     SP, SP, #4\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC0FA60\n"
                "BL      sub_FFD3F7C0\n"
                "LDR     R0, [R0,#0x7C]\n"
                "BL      sub_FFD3991C\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x6CE4\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC8C410\n"

                "B	sub_FFD399E4\n"
    );
}

void __attribute__((naked,noinline)) sub_FFD36838_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FFD3F564\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFD36850\n"
                "BL      sub_FFD3F570\n"

"loc_FFD36850:\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD387B4\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FFD36870\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD34D90\n"

"loc_FFD36870:\n"
                "BL      sub_FFD7480C\n"
                "BL      sub_FFD3417C\n"
                "MOV     R4, R0\n"
                "BL      sub_FFC143A4\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD3A1C0\n"
                "BL      sub_FFD38CF8\n"
                "BL      sub_FFD38C98\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD399A8_my\n"
		"BL      capt_seq_hook_raw_here\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FFD34D90\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD39BA8\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFD36D90\n"

"loc_FFD36C3C:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFD36D68\n"
                ".long loc_FFD36CAC\n"
                ".long loc_FFD36CB8\n"
                ".long loc_FFD36CC0\n"
                ".long loc_FFD36CD0\n"
                ".long loc_FFD36CC8\n"
                ".long loc_FFD36CD8\n"
                ".long loc_FFD36CE0\n"
                ".long loc_FFD36CEC\n"
                ".long loc_FFD36CF4\n"
                ".long loc_FFD36D00\n"
                ".long loc_FFD36D08\n"
                ".long loc_FFD36D10\n"
                ".long loc_FFD36D18\n"
                ".long loc_FFD36D20\n"
                ".long loc_FFD36D28\n"
                ".long loc_FFD36D34\n"
                ".long loc_FFD36D3C\n"
                ".long loc_FFD36D44\n"
                ".long loc_FFD36D4C\n"
                ".long loc_FFD36D58\n"
                ".long loc_FFD36D60\n"
                ".long loc_FFD36D78\n"

"loc_FFD36CAC:\n"
                "BL      sub_FFD38410\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFD348E8\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CB8:\n"
                "BL      sub_FFD36838_my\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CC0:\n"
                "BL      sub_FFD387A4\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CC8:\n"
                "BL      sub_FFD376CC\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CD0:\n"
                "BL      sub_FFD37728\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CD8:\n"
                "BL      sub_FFD37918\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CE0:\n"
                "BL      sub_FFD38504\n"
                "BL      sub_FFD348E8\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CEC:\n"
                "BL      sub_FFD36920\n"
                "B       loc_FFD36D74\n"

"loc_FFD36CF4:\n"
                "BL      sub_FFD3856C\n"
                "BL      sub_FFD348E8\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D00:\n"
                "BL      sub_FFD37728\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D08:\n"
                "BL      sub_FFD38E30\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D10:\n"
                "BL      sub_FFD390B8\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D18:\n"
                "BL      sub_FFD39144\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D20:\n"
                "BL      sub_FFD391FC\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D28:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFD392AC\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D34:\n"
                "BL      sub_FFD393FC\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D3C:\n"
                "BL      sub_FFD39470\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D44:\n"
                "BL      sub_FFD39528\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D4C:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD392AC\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D58:\n"
                "BL      sub_FFD39628\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D60:\n"
                "BL      sub_FFD39654\n"
                "B       loc_FFD36D74\n"

"loc_FFD36D68:\n"
                "LDR     R0, =0xFFD365BC\n"
                "MOV     R1, #0x2DC\n"
                "BL      sub_FFC03AD0\n"

"loc_FFD36D74:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"

"loc_FFD36D78:\n"
                "LDR     R3, =0x73CBC\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC0F8C4\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFD36638\n"

"loc_FFD36D90:\n"
                "LDR     R3, =0x73CC0\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC10074\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD36C3C\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xFFD365BC\n"
                "ADD     R1, R1, #1\n"
                "BL      sub_FFC03AD0\n"
                "BL      sub_FFC11610\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"

    );
}



