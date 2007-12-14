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


void __attribute__((naked,noinline)) sub_FFD39620_my(long p)
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
	    	"BL      sub_FFD3F438\n"
	    	"LDR     R0, [R0,#0x7C]\n"
	    	"BL      sub_FFD39594\n" // nr

	    	"BL      capt_seq_hook_set_nr\n"

	    	"LDR     R3, =0x6CE4\n"
		"LDR     R0, [R3]\n"
	    	"BL      sub_FFC8C088\n"

		"B	 sub_FFD3965C\n" // continue orig. func
    );
}

void __attribute__((naked,noinline)) sub_FFD364B0_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#0xC]\n"
                "BL      sub_FFD3F1DC\n"
                "CMP     R0, #0\n"
                "BNE     1f\n"
                "BL      sub_FFD3F1E8\n"

"1:\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD3842C\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     2f\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD34A08\n"

"2:\n"
                "BL      sub_FFD74484\n"
                "BL      sub_FFD33DF4\n"
                "MOV     R4, R0\n"
                "BL      sub_FFC143A4\n"
                "ADD     R3, R5, R5,LSL#1\n"
                "ADD     R4, R4, R3,LSL#5\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFD39E38\n" // ??
                "BL      sub_FFD38970\n" // tv related
                "BL      sub_FFD38910\n" // ??
                "MOV     R0, R5\n"
                "BL      sub_FFD39620_my\n" // make photo

		"BL      capt_seq_hook_raw_here\n"

                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FFD34A08\n" // save file ?
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFD39820\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FFD36A08\n"
// ---------------------------------------------------------------------------

"loc_FFD368B4:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFD369E0\n"
// ---------------------------------------------------------------------------
                ".long loc_FFD36924\n"
                ".long loc_FFD36930\n"
                ".long loc_FFD36938\n"
                ".long loc_FFD36948\n"
                ".long loc_FFD36940\n"
                ".long loc_FFD36950\n"
                ".long loc_FFD36958\n"
                ".long loc_FFD36964\n"
                ".long loc_FFD3696C\n"
                ".long loc_FFD36978\n"
                ".long loc_FFD36980\n"
                ".long loc_FFD36988\n"
                ".long loc_FFD36990\n"
                ".long loc_FFD36998\n"
                ".long loc_FFD369A0\n"
                ".long loc_FFD369AC\n"
                ".long loc_FFD369B4\n"
                ".long loc_FFD369BC\n"
                ".long loc_FFD369C4\n"
                ".long loc_FFD369D0\n"
                ".long loc_FFD369D8\n"
                ".long loc_FFD369F0\n"
// ---------------------------------------------------------------------------

"loc_FFD36924:\n"
                "BL      sub_FFD38088\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFD34560\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36930:\n"
                "BL      sub_FFD364B0_my\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36938:\n"
                "BL      sub_FFD3841C\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36940:\n"
                "BL      sub_FFD37344\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36948:\n"
                "BL      sub_FFD373A0\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36950:\n"
                "BL      sub_FFD37590\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36958:\n"
                "BL      sub_FFD3817C\n"
                "BL      sub_FFD34560\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36964:\n"
                "BL      sub_FFD36598\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD3696C:\n"
                "BL      sub_FFD381E4\n"
                "BL      sub_FFD34560\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36978:\n"
                "BL      sub_FFD373A0\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36980:\n"
                "BL      sub_FFD38AA8\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36988:\n"
                "BL      sub_FFD38D30\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36990:\n"
                "BL      sub_FFD38DBC\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD36998:\n"
                "BL      sub_FFD38E74\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369A0:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFD38F24\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369AC:"
                "BL      sub_FFD39074\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369B4:\n"
                "BL      sub_FFD390E8\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369BC:\n"
                "BL      sub_FFD391A0\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369C4:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD38F24\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369D0:\n"
                "BL      sub_FFD392A0\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369D8:\n"
                "BL      sub_FFD392CC\n"
                "B       loc_FFD369EC\n"
// ---------------------------------------------------------------------------

"loc_FFD369E0:\n"
                "LDR     R0, =0xFFD36234\n"
                "MOV     R1, #0x2DC\n"
                "BL      sub_FFC03AD0\n"

"loc_FFD369EC:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"

"loc_FFD369F0:\n"
                "LDR     R3, =0x73CBC\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFC0F8C4\n"
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFD362B0\n"

"loc_FFD36A08:\n"
                "LDR     R3, =0x73CC0\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFC10074\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFD368B4\n"
                "MOV     R1, #0x24C\n"
                "LDR     R0, =0xFFD36234\n"
                "ADD     R1, R1, #1\n"
                "BL      sub_FFC03AD0\n"
                "BL      sub_FFC11610\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"

    );
}
