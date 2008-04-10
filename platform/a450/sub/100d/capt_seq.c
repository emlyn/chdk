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



void __attribute__((naked,noinline)) sub_FFE71CDC_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFE72704\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "BL      sub_FFE81DD0\n"       //ClearEventFlag
                "MOV     R0, #0x8A\n"
                "ADD     R1, SP, #0x14-0x10\n"
                "MOV     R2, #4\n"
                "BL      sub_FFC0B79C\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFE71D1C\n"
                "MOV     R1, #0x1D0\n"
                "LDR     R0, =0xFFE71B60\n"    //aSscaptureseq_c
                "ADD     R1, R1, #2\n"
                "BL      sub_FFE8F45C\n"       //DebugAssert
"loc_FFE71D1C:\n"
                "LDR     R3, =0x94240\n"
                "LDR     R2, =0x94300\n"
                "LDR     R0, [R3,#0x74]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FFDCBF04\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE71AE4\n"
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0xCF78\n"
                "LDR     R0, [R3]\n"
                "B       sub_FFE71D40\n"
    );
}

void __attribute__((naked,noinline)) sub_FFE6ED68_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R3, [R4,#8]\n"
                "ORR     R3, R3, #1\n"
                "STR     R3, [R4,#8]\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFE78BA4\n"
                "TST     R0, #1\n"
                "MOV     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, R0\n"
                "BEQ     loc_FFE6EDAC\n"
                "LDR     R3, [R4,#8]\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFE6D604\n"
"loc_FFE6EDAC:\n"
                "BL      sub_FFE6F800\n"   //Set_CMD25Write_48
                "MOV     R0, R4\n"
                "BL      sub_FFE70834\n"
                "TST     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FFE6EDD0\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFE6D604\n"
"loc_FFE6EDD0:\n"
                "BL      sub_FFC0B998\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE71BC4\n"
                "BL      sub_FFE72570\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE71CDC_my\n"   //---------------->
                "BL      capt_seq_hook_raw_here\n"
                "MOV     R1, #1\n"
                "MOV     R2, R4\n"
                "BL      sub_FFE6D604\n"
                "BL      sub_FFE72010\n"
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
                "B       loc_FFE6F2D4\n"
"loc_FFE6F178:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFE6F2A8\n"

                ".long loc_FFE6F1E8\n"
                ".long loc_FFE6F1F4\n"
                ".long loc_FFE6F1FC\n"
                ".long loc_FFE6F210\n"
                ".long loc_FFE6F208\n"
                ".long loc_FFE6F218\n"
                ".long loc_FFE6F220\n"
                ".long loc_FFE6F22C\n"
                ".long loc_FFE6F234\n"
                ".long loc_FFE6F240\n"
                ".long loc_FFE6F248\n"
                ".long loc_FFE6F250\n"
                ".long loc_FFE6F258\n"
                ".long loc_FFE6F260\n"
                ".long loc_FFE6F268\n"
                ".long loc_FFE6F274\n"
                ".long loc_FFE6F27C\n"
                ".long loc_FFE6F284\n"
                ".long loc_FFE6F28C\n"
                ".long loc_FFE6F298\n"
                ".long loc_FFE6F2A0\n"
                ".long loc_FFE6F2BC\n"
"loc_FFE6F1E8:\n"
                "BL      sub_FFE6F814\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FFE6D0F4\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F1F4:\n"
                "BL      sub_FFE6ED68_my\n"  //---------------->
                "B       loc_FFE6F2B8\n"
"loc_FFE6F1FC:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFE6F9E8\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F208:\n"
                "BL      sub_FFE6F3B8\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F210:\n"
                "BL      sub_FFE6F7E0\n"   //BackLightDrv_LcdBackLightOff_13
                "B       loc_FFE6F2B8\n"
"loc_FFE6F218:\n"
                "BL      sub_FFE6F7F0\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F220:\n"
                "BL      sub_FFE6F8F8\n"
                "BL      sub_FFE6D0F4\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F22C:\n"
                "BL      sub_FFE6EE74\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F234:\n"
                "BL      sub_FFE6F95C\n"
                "BL      sub_FFE6D0F4\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F240:\n"
                "BL      sub_FFE6F7E0\n"   //BackLightDrv_LcdBackLightOff_13
                "B       loc_FFE6F2B8\n"
"loc_FFE6F248:\n"
                "BL      sub_FFE70F48\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F250:\n"
                "BL      sub_FFE71114\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F258:\n"
                "BL      sub_FFE711A8\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F260:\n"
                "BL      sub_FFE712A4\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F268:\n"
                "MOV     R0, #0\n"
                "BL      sub_FFE71510\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F274:\n"
                "BL      sub_FFE716C8\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F27C:\n"
                "BL      sub_FFE7175C\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F284:\n"
                "BL      sub_FFE71818\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F28C:\n"
                "BL      sub_FFE6FB3C\n"
                "BL      sub_FFE6EC8C\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F298:\n"
                "BL      sub_FFE713E4\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F2A0:\n"
                "BL      sub_FFE71440\n"
                "B       loc_FFE6F2B8\n"
"loc_FFE6F2A8:\n"
                "MOV     R1, #0x4C0\n"
                "LDR     R0, =0xFFE6EAE8\n"   //aSsshoottask_c
                "ADD     R1, R1, #0xE\n"
                "BL      sub_FFE8F45C\n"      //DebugAssert
"loc_FFE6F2B8:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
"loc_FFE6F2BC:\n"
                "LDR     R3, =0x6E2B8\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFE81C34\n"      //SetEventFlag
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FFE6EB68\n"
"loc_FFE6F2D4:\n"
                "LDR     R3, =0x6E2BC\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFE8234C\n"     //ReceiveMessageQueue
                "TST     R0, #1\n"
                "BEQ     loc_FFE6F178\n"
                "LDR     R0, =0xFFE6EAE8\n"  //aSsshoottask_c
                "MOV     R1, #0x400\n"
                "BL      sub_FFE8F45C\n"     //DebugAssert
                "BL      sub_FFE83910\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

