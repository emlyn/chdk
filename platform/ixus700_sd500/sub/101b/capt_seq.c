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


void __attribute__((naked,noinline)) sub_FF9554C4_my(long p)
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
                "LDR     R6, =0xFF9553FC\n"
                "BNE     loc_FF9554F8\n"
                "LDR     R0, =0xFF9554B8\n"
                "MOV     R1, #0xDB\n"
                "BL      sub_FF813E68\n"
"loc_FF9554F8:\n"
                "LDR     R3, =0x6FCFC\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FF3C\n"
                "BL      sub_FF955434\n"
	    	"BL      capt_seq_hook_set_nr\n" // +

		"B       sub_FF95550C\n"
    );
}

void __attribute__((naked,noinline)) sub_FF9523D4_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R5, [R0,#8]\n"
                "BL      sub_FF95FA78\n"
                "CMP     R0, #0\n"
                "LDR     R0, =0xFF9523B0\n"
                "BNE     loc_FF9523F4\n"
                "BL      sub_FFAB78A8\n"
                "BL      sub_FF95FA84\n"
"loc_FF9523F4:\n"
                "MOV     R0, R5\n"
                "BL      sub_FF954294\n"
                "TST     R0, #1\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FF952414\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF9515C0\n"
"loc_FF952414:\n"
                "BL      sub_FF98D194\n"
                "BL      sub_FF950C60\n"
                "MOV     R4, R0\n"
                "BL      sub_FF825E98\n"
                "ADD     R3, R5, R5,LSL#2\n"
                "ADD     R3, R5, R3,LSL#1\n"
                "ADD     R4, R4, R3,LSL#3\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, R5\n"
                "BL      sub_FF955D54\n"
                "BL      sub_FF954878\n"
                "BL      sub_FF9547E4\n"
                "MOV     R0, R5\n"
                "BL      sub_FF9554C4_my\n"  //------------->
                "BL      capt_seq_hook_raw_here\n" // +
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "BL      sub_FF9515C0\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FF95570C\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
 asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF952E10\n"
"loc_FF952C8C:\n"
                "LDR     R0, [SP]\n"
                "LDR     R3, [R0]\n"
                "CMP     R3, #0xF\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF952DF8\n"
                ".long loc_FF952CE0\n"
                ".long loc_FF952CF0\n"
                ".long loc_FF952D04\n"
                ".long loc_FF952D14\n"
                ".long loc_FF952D24\n"
                ".long loc_FF952D34\n"
                ".long loc_FF952D48\n"
                ".long loc_FF952D58\n"
                ".long loc_FF952D6C\n"
                ".long loc_FF952D7C\n"
                ".long loc_FF952D8C\n"
                ".long loc_FF952D9C\n"
                ".long loc_FF952DAC\n"
                ".long loc_FF952DC0\n"
                ".long loc_FF952DD0\n"
                ".long loc_FF952DE0\n"
"loc_FF952CE0:\n"
                "BL      sub_FF95346C\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #8\n"
                "B       loc_FF952DEC\n"
"loc_FF952CF0:\n"
                "BL      sub_FF953BFC\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF9511F4\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x10\n"
                "B       loc_FF952DEC\n"
"loc_FF952D04:\n"
                "BL      sub_FF9523D4_my\n"  //--------------->
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #2\n"
                "B       loc_FF952DEC\n"
"loc_FF952D14:\n"
                "BL      sub_FF9541F4\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #1\n"
                "B       loc_FF952DEC\n"
"loc_FF952D24:\n"
                "BL      sub_FF953C9C\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x20\n"
                "B       loc_FF952DEC\n"
"loc_FF952D34:\n"
                "BL      sub_FF953D8C\n"
                "BL      sub_FF9511F4\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x40\n"
                "B       loc_FF952DEC\n"
"loc_FF952D48:\n"
                "BL      sub_FF952588\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x80\n"
                "B       loc_FF952DEC\n"
"loc_FF952D58:\n"
                "BL      sub_FF953F08\n"
                "BL      sub_FF9511F4\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x400\n"
                "B       loc_FF952DEC\n"
"loc_FF952D6C:\n"
                "BL      sub_FF953C9C\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x800\n"
                "B       loc_FF952DEC\n"
"loc_FF952D7C:\n"
                "BL      sub_FF9549BC\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x8000\n"
                "B       loc_FF952DEC\n"
"loc_FF952D8C:\n"
                "BL      sub_FF954D70\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x10000\n"
                "B       loc_FF952DEC\n"
"loc_FF952D9C:\n"
                "BL      sub_FF954C8C\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x20000\n"
                "B       loc_FF952DEC\n"
"loc_FF952DAC:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF954E24\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x40000\n"
                "B       loc_FF952DEC\n"
"loc_FF952DC0:\n"
                "BL      sub_FF955088\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x80000\n"
                "B       loc_FF952DEC\n"
"loc_FF952DD0:\n"
                "BL      sub_FF955100\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x100000\n"
                "B       loc_FF952DEC\n"
"loc_FF952DE0:\n"
                "BL      sub_FF95514C\n"
                "LDR     R3, =0x6FC94\n"
                "MOV     R1, #0x200000\n"
"loc_FF952DEC:\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FDA0\n"
                "B       loc_FF952E08\n"
"loc_FF952DF8:\n"
                "MOV     R1, #0x370\n	"
                "LDR     R0, =0xFF952084\n"
                "ADD     R1, R1, #1\n"
                "BL      sub_FF813E68\n"
"loc_FF952E08:\n"
                "LDR     R0, [SP]\n"
                "BL      sub_FF952104\n"
"loc_FF952E10:\n"
                "LDR     R3, =0x6FC98\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF8205A8\n"
                "TST     R0, #1\n"
                "BEQ     loc_FF952C8C\n"
                "MOV     R1, #0x2E4\n"
                "LDR     R0, =0xFF952084\n"
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813E68\n"
                "BL      sub_FF821DD0\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

