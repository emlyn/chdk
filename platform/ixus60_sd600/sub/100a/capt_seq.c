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
    long *nrflag = (long*)0x61AC;   // found at 0xFF962120 (CaptureSeq.c)

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

void __attribute__((naked,noinline)) sub_FF962138_my(long p)    // TODO
{
#if 1
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R3, =0x6F18C\n"
                "LDR     R5, =0x61A8\n"
                "SUB     SP, SP, #4\n"
                "MVN     R1, #0\n"          
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FE80\n"    // ClearEventFlag
                "LDR     R3, =0x99C40\n"
                "LDR     R0, [R3,#0x7C]\n"
                "BL      sub_FF89E17C\n"    // IsEmptyWriteCache_42
                "BL      sub_FF96208C\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x61B0\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF89E63C\n"

		"B	 sub_FF962174\n"    // ---> addr of next line (to finish function)
    );
#endif
}

void __attribute__((naked,noinline)) sub_FF95EC90_my(long p)    // TODO
{
    asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "LDR     R4, [R0,#0xC]\n"
                 "BL      sub_FF967434\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF95ECA8\n"
                 "BL      sub_FF967440\n"   
 "loc_FF95ECA8:\n"
                 "LDR     R3, =0x99C40\n"
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BNE     loc_FF95ECDC\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF967454\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF95ECDC\n"
                 "MOV     R0, #1\n"         
 "loc_FF95ECCC:\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF95D378\n"   
 "loc_FF95ECDC:\n"
                 "LDR     R3, =0x99C40\n"
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BNE     loc_FF95ED2C\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF960EF0\n"
                 "TST     R0, #1\n"
                 "BNE     loc_FF95ECCC\n"
                 "BL      sub_FF9A0088\n"
                 "BL      sub_FF824A78\n"
                 "LDR     R2, =0x99B84\n"
                 "ADD     R3, R4, R4,LSL#1\n"
                 "STR     R0, [R2,R3,LSL#5]\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF9628A4\n"
                 "BL      sub_FF9613F4\n"
                 "BL      sub_FF961390\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF962138_my\n"  //------------->

                 "BL      capt_seq_hook_raw_here\n"

                 "B       loc_FF95ED40\n"       
 "loc_FF95ED2C:\n"
                 "LDR     R3, =0x6198\n"
                 "LDR     R2, [R3]\n"
                 "CMP     R2, #0\n"
                 "MOVNE   R0, #0x1D\n"
                 "MOVEQ   R0, #0\n"
 "loc_FF95ED40:\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF95D378\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF962330\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()    // task_CaptSeqTask
{
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "SUB     SP, SP, #4\n"
                 "MOV     R4, SP\n"
                 "B       loc_FF95F27C\n"   
 "loc_FF95F114:\n"
                 "LDR     R2, [SP]\n"       
                 "LDR     R3, [R2]\n"
                 "MOV     R0, R2\n"
                 "CMP     R3, #0x14\n"
                 "LDRLS   PC, [PC,R3,LSL#2]\n"
                 "B       loc_FF95F250\n"   
                 ".long loc_FF95F180\n"
                 ".long loc_FF95F1A0\n"
                 ".long loc_FF95F1B4\n"
                 ".long loc_FF95F1C4\n"
                 ".long loc_FF95F1BC\n"
                 ".long loc_FF95F1CC\n"
                 ".long loc_FF95F1D4\n"
                 ".long loc_FF95F1E0\n"
                 ".long loc_FF95F1E8\n"
                 ".long loc_FF95F1F4\n"
                 ".long loc_FF95F1FC\n"
                 ".long loc_FF95F204\n"
                 ".long loc_FF95F20C\n"
                 ".long loc_FF95F214\n"
                 ".long loc_FF95F21C\n"
                 ".long loc_FF95F228\n"
                 ".long loc_FF95F230\n"
                 ".long loc_FF95F238\n"
                 ".long loc_FF95F240\n"
                 ".long loc_FF95F248\n"
                 ".long loc_FF95F264\n"     
 "loc_FF95F180:\n"
                 "BL      sub_FF960B50\n"
                 "BL      shooting_expo_param_override\n"   // +
                 "BL      sub_FF95CE98\n"   
                 "LDR     R3, =0x99C40\n"        
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BEQ     loc_FF95F260\n"
                 "BL      sub_FF95ED60\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1A0:\n"
                 "BL      sub_FF95EC90_my\n" //------------->
 "loc_FF95F1A4:\n"
                 "LDR     R2, =0x99C40\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [R2,#0x24]\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1B4:\n"
                 "BL      sub_FF960EE0\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1BC:\n"
                 "BL      sub_FF95FD50\n"
                 "B       loc_FF95F1A4\n"   
 "loc_FF95F1C4:\n"
                 "BL      sub_FF9600EC\n"   //BackLightDrv_LcdBackLightOff_3
                 "B       loc_FF95F1A4\n"   
 "loc_FF95F1CC:\n"
                 "BL      sub_FF9600FC\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1D4:\n"
                 "BL      sub_FF960C34\n"
                 "BL      sub_FF95CE98\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1E0:\n"
                 "BL      sub_FF95EE34\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1E8:\n"
                 "BL      sub_FF960C9C\n"
                 "BL      sub_FF95CE98\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1F4:\n"
                 "BL      sub_FF9600EC\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F1FC:\n"
                 "BL      sub_FF961434\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F204:\n"
                 "BL      sub_FF961780\n"   
                 "B       loc_FF95F260\n"   
 "loc_FF95F20C:\n"
                 "BL      sub_FF961804\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F214:\n"
                 "BL      sub_FF9618F0\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F21C:\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF9619B8\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F228:\n"
                 "BL      sub_FF961B24\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F230:\n"
                 "BL      sub_FF961BB8\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F238:\n"
                 "BL      sub_FF961C74\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F240:\n"
                 "BL      sub_FF961D60\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F248:\n"
                 "BL      sub_FF961DB4\n"
                 "B       loc_FF95F260\n"   
 "loc_FF95F250:\n"
                 "MOV     R1, #0x36C\n"
                 "LDR     R0, =0xFF95EA1C\n"    // aShoottask_c
                 "ADD     R1, R1, #1\n"
                 "BL      sub_FF813AFC\n"   // DebugAssert
 "loc_FF95F260:\n"
                 "LDR     R2, [SP]\n"
 "loc_FF95F264:\n"
                 "LDR     R3, =0x6F114\n"
                 "LDR     R1, [R2,#4]\n"
                 "LDR     R0, [R3]\n"
                 "BL      sub_FF81FCE4\n"   // SetEventFlag
                 "LDR     R0, [SP]\n"
                 "BL      sub_FF95EA98\n"
 "loc_FF95F27C:\n"
                 "LDR     R3, =0x6F118\n"
                 "MOV     R1, R4\n"
                 "LDR     R0, [R3]\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF8203FC\n"   // ReceiveMessageQueue
                 "TST     R0, #1\n"
                 "BEQ     loc_FF95F114\n" 
                 "MOV     R1, #0x2A4\n"
                 "LDR     R0, =0xFF95EA1C\n"
                 "ADD     R1, R1, #3\n"
                 "BL      sub_FF813AFC\n"   // DebugAssert
                 "BL      sub_FF821958\n"   // ExitTask
                 "ADD     SP, SP, #4\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}





