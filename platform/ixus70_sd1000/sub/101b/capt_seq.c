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
    long *nrflag = (long*)0xCDA0;

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


void __attribute__((naked,noinline)) sub_FFB01E30_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFB028A0\n"
                "MVN     R1, #0\n"
                "BL      sub_FFB13010\n"
                "MOV     R0, #0x8A\n"
                "ADD     R1, SP, #4\n"
                "MOV     R2, #4\n"
                "BL      sub_FF81BC98\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFB01E70\n"
                "MOV     R1, #0x1D0\n"
                "LDR     R0, =0xFFB01CB4\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FFB2069C\n"
"loc_FFB01E70:\n"
                "LDR     R3, =0xBDA80\n"
                "LDR     R2, =0xBDB40\n"
                "LDR     R0, [R3,#0x7C]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FFA395F0\n"
                "MOV     R0, R4\n"
                "BL      sub_FFB01C38\n"
                "BL      capt_seq_hook_set_nr\n"  // +
                "LDR     R3, =0xCDA4\n"
                "LDR     R0, [R3]\n"
                "B       sub_FFB01E94\n"
    );
}

void __attribute__((naked,noinline)) sub_FFAFEC58_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,R5,LR}\n"
                "LDR     R3, =0xBDA80\n"
                "LDR     R5, [R0,#0xC]\n"
                "LDR     R1, [R3,#0x24]\n"
                "LDR     R2, [R5,#8]\n"
                "CMP     R1, #0\n"
                "ORR     R2, R2, #1\n"
                "STR     R2, [R5,#8]\n"
                "BNE     loc_FFAFECAC\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFB091A8\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFAFECAC\n"
                "LDR     R3, [R5,#8]\n"
                "MOV     R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R5,#8]\n"
"loc_FFAFEC9C:\n"
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFAFD400\n"
"loc_FFAFECAC:\n"
                "LDR     R4, =0xBDA80\n"
                "BL      sub_FFAFF750\n"
                "LDR     R3, [R4,#0x24]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FFAFECF4\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB00934\n"
                "TST     R0, #1\n"
                "BNE     loc_FFAFEC9C\n"
                "BL      sub_FF8261B8\n"
                "BL      sub_FF81BE94\n"
                "STR     R0, [R5,#0x14]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB01D18\n"
                "BL      sub_FFB0270C\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB01E30_my\n"         //------------->
                "BL      capt_seq_hook_raw_here\n"  // +
                "B       loc_FFAFED08\n"
"loc_FFAFECF4:\n"
                "LDR     R3, =0xCD8C\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
"loc_FFAFED08:\n"
                "MOV     R1, #1\n"
                "MOV     R2, R5\n"
                "BL      sub_FFAFD400\n"
                "BL      sub_FFB021AC\n"
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
                "B       loc_FFAFF290\n"
"loc_FFAFF114:\n"
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFAFF264\n"
                ".long loc_FFAFF184\n"
                ".long loc_FFAFF1A4\n"
                ".long loc_FFAFF1B8\n"
                ".long loc_FFAFF1CC\n"
                ".long loc_FFAFF1C4\n"
                ".long loc_FFAFF1D4\n"
                ".long loc_FFAFF1DC\n"
                ".long loc_FFAFF1E8\n"
                ".long loc_FFAFF1F0\n"
                ".long loc_FFAFF1FC\n"
                ".long loc_FFAFF204\n"
                ".long loc_FFAFF20C\n"
                ".long loc_FFAFF214\n"
                ".long loc_FFAFF21C\n"
                ".long loc_FFAFF224\n"
                ".long loc_FFAFF230\n"
                ".long loc_FFAFF238\n"
                ".long loc_FFAFF240\n"
                ".long loc_FFAFF248\n"
                ".long loc_FFAFF254\n"
                ".long loc_FFAFF25C\n"
                ".long loc_FFAFF278\n"
"loc_FFAFF184:\n"
                "BL      sub_FFAFF778\n"

                "BL      shooting_expo_param_override\n" // +

                "BL      sub_FFAFCE88\n"
                "LDR     R3, =0xBDA80\n"
                "LDR     R2, [R3,#0x24]\n"
                "CMP     R2, #0\n"
                "BEQ     loc_FFAFF274\n"
                "BL      sub_FFAFED34\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF1A4:\n"
                "BL      sub_FFAFEC58_my\n"  //------------>
"loc_FFAFF1A8:\n"
                "LDR     R2, =0xBDA80\n"
                "MOV     R3, #0\n"
                "STR     R3, [R2,#0x24]\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF1B8:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFAFF998\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF1C4:\n"
                "BL      sub_FFAFF378\n"
                "B       loc_FFAFF1A8\n"
"loc_FFAFF1CC:\n"
                "BL      sub_FFAFF730\n"
                "B       loc_FFAFF1A8\n"
"loc_FFAFF1D4:\n"
                "BL      sub_FFAFF740\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF1DC:\n"
                "BL      sub_FFAFF890\n"
                "BL      sub_FFAFCE88\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF1E8:\n"
                "BL      sub_FFAFEE10\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF1F0:\n"
                "BL      sub_FFAFF900\n"
                "BL      sub_FFAFCE88\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF1FC:\n"
                "BL      sub_FFAFF730\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF204:\n"
                "BL      sub_FFB01068\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF20C:\n"
                "BL      sub_FFB0123C\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF214:\n"
                "BL      sub_FFB012D0\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF21C:\n"
                "BL      sub_FFB013CC\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF224:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFB01638\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF230:\n"
                "BL      sub_FFB0180C\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF238:\n"
                "BL      sub_FFB018A8\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF240:\n"
                "BL      sub_FFB01968\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF248:\n"
                "BL      sub_FFAFFAEC\n"
                "BL      sub_FFAFEB7C\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF254:\n"
                "BL      sub_FFB0150C\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF25C:\n"
                "BL      sub_FFB01568\n"
                "B       loc_FFAFF274\n"
"loc_FFAFF264:\n"
                "MOV     R1, #0x4C0\n"
                "LDR     R0, =0xFFAFE9D8\n"
                "ADD     R1, R1, #0xE\n"
                "BL      sub_FFB2069C\n"
"loc_FFAFF274:\n"
                "LDR     R2, [SP]\n"
"loc_FFAFF278:\n"
                "LDR     R3, =0x97348\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFB12E74\n"
                "LDR     R0, [SP]\n"
                "BL      sub_FFAFEA58\n"
"loc_FFAFF290:\n"
                "LDR     R3, =0x9734C\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFB1358C\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFAFF114\n"
                "LDR     R0, =0xFFAFE9D8\n"
                "MOV     R1, #0x400\n"
                "BL      sub_FFB2069C\n"
                "BL      sub_FFB14B50\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

