#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

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
    long *nrflag = (long*)0x53EC;

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


void tv_override(void){
 if (conf.tv_override) shooting_set_tv96_direct(-384-32*conf.tv_override);
}


void __attribute__((naked,noinline)) sub_FF955474_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R3, =0x53E4\n"
                "SUB     SP, SP, #4\n"
                "LDR     R2, [R3]\n"
                "LDR     R4, =0x53E8\n"
                "CMP     R2, #0\n"
                "STR     R0, [R4]\n"
                "MOV     R8, #0\n"
                "LDR     R6, =0xFF9553AC\n"
                "BNE     loc_FF9554A8\n"
                "LDR     R0, =0xFF955468\n"
                "MOV     R1, #0xDB\n"
                "BL      sub_FF813E68\n"
"loc_FF9554A8:\n"
                "LDR     R3, =0x6FCFC\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FF3C\n"
                "BL      sub_FF9553E4\n"
	    	"BL      capt_seq_hook_set_nr\n"

		"B       sub_FF9554BC\n"
    );
}

void __attribute__((naked,noinline)) sub_FF952384_my(long p)
{
    asm volatile (
                 "STMFD   SP!, {R4,R5,LR}\n"
                 "LDR     R5, [R0,#8]\n"
                 "BL      sub_FF95FA28\n"
                 "CMP     R0, #0\n"
                 "LDR     R0, =0xFF952360\n"
                 "BNE     loc_FF9523A4\n"
                 "BL      sub_FFAB7858\n"
                 "BL      sub_FF95FA34\n"
"loc_FF9523A4:\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF954244\n"
                 "TST     R0, #1\n"
                 "MOV     R2, R5\n"
                 "MOV     R1, #1\n"
                 "BEQ     loc_FF9523C4\n"
                 "LDMFD   SP!, {R4,R5,LR}\n"
                 "B       sub_FF951570\n"
"loc_FF9523C4:\n"
                 "BL      sub_FF98D144\n"
                 "BL      sub_FF950C10\n"
                 "MOV     R4, R0\n"
                 "BL      sub_FF825E98\n"
                 "ADD     R3, R5, R5,LSL#2\n"
                 "ADD     R3, R5, R3,LSL#1\n"
                 "ADD     R4, R4, R3,LSL#3\n"
                 "STR     R0, [R4,#4]\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF955D04\n"
                 "BL      sub_FF954828\n"
                 "BL      sub_FF954794\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF955474_my\n"
                 "BL      capt_seq_hook_raw_here\n"
                 "MOV     R2, R5\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF951570\n"
                 "LDMFD   SP!, {R4,R5,LR}\n"
                 "B       sub_FF9556BC\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "SUB     SP, SP, #4\n"
                 "MOV     R4, SP\n"
                 "B       loc_FF952DC0\n"

"loc_FF952C3C:\n"
                 "LDR     R0, [SP]\n"
                 "LDR     R3, [R0]\n"
                 "CMP     R3, #0xF\n"
                 "LDRLS   PC, [PC,R3,LSL#2]\n"
                 "B       loc_FF952DA8\n"

                 ".long loc_FF952C90\n"
                 ".long loc_FF952CA0\n"
                 ".long loc_FF952CB4\n"
                 ".long loc_FF952CC4\n"
                 ".long loc_FF952CD4\n"
                 ".long loc_FF952CE4\n"
                 ".long loc_FF952CF8\n"
                 ".long loc_FF952D08\n"
                 ".long loc_FF952D1C\n"
                 ".long loc_FF952D2C\n"
                 ".long loc_FF952D3C\n"
                 ".long loc_FF952D4C\n"
                 ".long loc_FF952D5C\n"
                 ".long loc_FF952D70\n"
                 ".long loc_FF952D80\n"
                 ".long loc_FF952D90\n"
"loc_FF952C90:\n"
                 "BL      sub_FF95341C\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #8\n"
                 "B       loc_FF952D9C\n"
"loc_FF952CA0:\n"
                 "BL      sub_FF953BAC\n"
                 "BL      tv_override\n"  // +
                 "BL      sub_FF9511A4\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x10\n"
                 "B       loc_FF952D9C\n"
"loc_FF952CB4:\n"
                 "BL      sub_FF952384_my\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #2\n"
                 "B       loc_FF952D9C\n"
"loc_FF952CC4:\n"
                 "BL      sub_FF9541A4\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #1\n"
                 "B       loc_FF952D9C\n"
"loc_FF952CD4:\n"
                 "BL      sub_FF953C4C\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x20\n"
                 "B       loc_FF952D9C\n"
"loc_FF952CE4:\n"
                 "BL      sub_FF953D3C\n"
                 "BL      sub_FF9511A4\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x40\n"
                 "B       loc_FF952D9C\n"
"loc_FF952CF8:\n"
                 "BL      sub_FF952538\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x80\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D08:\n"
                 "BL      sub_FF953EB8\n"
                 "BL      sub_FF9511A4\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x400\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D1C:\n"
                 "BL      sub_FF953C4C\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x800\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D2C:\n"
                 "BL      sub_FF95496C\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x8000\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D3C:\n"
                 "BL      sub_FF954D20\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x10000\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D4C:\n"
                 "BL      sub_FF954C3C\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x20000\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D5C:\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF954DD4\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x40000\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D70:\n"
                 "BL      sub_FF955038\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x80000\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D80:\n"
                 "BL      sub_FF9550B0\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x100000\n"
                 "B       loc_FF952D9C\n"
"loc_FF952D90:\n"
                 "BL      sub_FF9550FC\n"
                 "LDR     R3, =0x6FC94\n"
                 "MOV     R1, #0x200000\n"
"loc_FF952D9C:\n"
                 "LDR     R0, [R3]\n"
                 "BL      sub_FF81FDA0\n"
                 "B       loc_FF952DB8\n"
"loc_FF952DA8:\n"
                 "MOV     R1, #0x370\n"
                 "LDR     R0, =0xFF952034\n"
                 "ADD     R1, R1, #1\n"
                 "BL      sub_FF813E68\n"
"loc_FF952DB8:\n"
                 "LDR     R0, [SP]\n"
                 "BL      sub_FF9520B4\n"
"loc_FF952DC0:\n"
                 "LDR     R3, =0x6FC98\n"
                 "MOV     R1, R4\n"
                 "LDR     R0, [R3]\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF8205A8\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF952C3C\n"
                 "MOV     R1, #0x2E4\n"
                 "LDR     R0, =0xFF952034\n"
                 "ADD     R1, R1, #3\n"
                 "BL      sub_FF813E68\n"
                 "BL      sub_FF821DD0\n"
                 "ADD     SP, SP, #4\n"
                 "LDMFD   SP!, {R4,PC}\n"
	);
}

