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
    long *nrflag = (long*)0xBF94;

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


void __attribute__((naked,noinline)) sub_FFE96FA8_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFE97A18\n"
                "MVN     R1, #0\n"
                "BL      sub_FFEA7FA8\n"
                "MOV     R0, #0x8A\n"
                "ADD     R1, SP, #4\n"
                "MOV     R2, #4\n"
                "BL      sub_FFC0BCB8\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFE96FE8\n"
                "MOV     R1, #0x1D0\n"
                "LDR     R0, =0xFFE96E2C\n"
                "ADD     R1, R1, #2\n"
                "BL      sub_FFEB5664\n"
"loc_FFE96FE8:\n"                           
                "LDR     R3, =0xA4BA0\n"
                "LDR     R2, =0xA4C60\n"
                "LDR     R0, [R3,#0x74]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FFDE52F8\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE96DB0\n"
                "BL      capt_seq_hook_set_nr\n" // +
                "LDR     R3, =0xBF98\n"
                "LDR     R0, [R3]\n"

                "B       sub_FFE9700C\n"  // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FFE93F70_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R3, [R4,#8]\n"
                "ORR     R3, R3, #1\n"
                "STR     R3, [R4,#8]\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFE9E130\n"
                "TST     R0, #1\n"
                "MOV     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, R0\n"
                "BEQ     loc_FFE93FB4\n"
                "LDR     R3, [R4,#8]\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R4,#8]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFE927E4\n"
"loc_FFE93FB4:\n"                           
                "BL      sub_FFE94A48\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE95AAC\n"
                "TST     R0, #1\n"
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BEQ     loc_FFE93FD8\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FFE927E4\n"
"loc_FFE93FD8:\n"                           
                "BL      sub_FFC15FF0\n"
                "BL      sub_FFC0BEB4\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE96E90\n"
                "BL      sub_FFE97884\n"
                "MOV     R0, R4\n"
                "BL      sub_FFE96FA8_my\n"  //---------->
                "BL      capt_seq_hook_raw_here\n"  // +
                "MOV     R1, #1\n"
                "MOV     R2, R4\n"
                "BL      sub_FFE927E4\n"
                "BL      sub_FFE97324\n"
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
                "B       loc_FFE944E0\n"
"loc_FFE94384:\n"                           
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFE944B4\n"
                ".long loc_FFE943F4\n"
                ".long loc_FFE94400\n"
                ".long loc_FFE94408\n"
                ".long loc_FFE9441C\n"
                ".long loc_FFE94414\n"
                ".long loc_FFE94424\n"
                ".long loc_FFE9442C\n"
                ".long loc_FFE94438\n"
                ".long loc_FFE94440\n"
                ".long loc_FFE9444C\n"
                ".long loc_FFE94454\n"
                ".long loc_FFE9445C\n"
                ".long loc_FFE94464\n"
                ".long loc_FFE9446C\n"
                ".long loc_FFE94474\n"
                ".long loc_FFE94480\n"
                ".long loc_FFE94488\n"
                ".long loc_FFE94490\n"
                ".long loc_FFE94498\n"
                ".long loc_FFE944A4\n"
                ".long loc_FFE944AC\n"
                ".long loc_FFE944C8\n"
"loc_FFE943F4:\n"                           
                                        
                "BL      sub_FFE94A5C\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FFE922D8\n"
                "B       loc_FFE944C4\n"
"loc_FFE94400:\n"                           
                                        
                "BL      sub_FFE93F70_my\n"  //--------->
                "B       loc_FFE944C4\n"
"loc_FFE94408:\n"                           
                                        
                "MOV     R0, #1\n"
                "BL      sub_FFE94C58\n"
                "B       loc_FFE944C4\n"
"loc_FFE94414:\n"                           
                                        
                "BL      sub_FFE945C4\n"
                "B       loc_FFE944C4\n"
"loc_FFE9441C:\n"                           
                                        
                "BL      sub_FFE94A28\n"
                "B       loc_FFE944C4\n"
"loc_FFE94424:\n"                           
                                        
                "BL      sub_FFE94A38\n"
                "B       loc_FFE944C4\n"
"loc_FFE9442C:\n"                           
                                        
                "BL      sub_FFE94B50\n"
                "BL      sub_FFE922D8\n"
                "B       loc_FFE944C4\n"
"loc_FFE94438:\n"                           
                                        
                "BL      sub_FFE94080\n"
                "B       loc_FFE944C4\n"
"loc_FFE94440:\n"                           
                                        
                "BL      sub_FFE94BC0\n"
                "BL      sub_FFE922D8\n"
                "B       loc_FFE944C4\n"
"loc_FFE9444C:\n"                           
                                        
                "BL      sub_FFE94A28\n"
                "B       loc_FFE944C4\n"
"loc_FFE94454:\n"                           
                                        
                "BL      sub_FFE961E0\n"
                "B       loc_FFE944C4\n"
"loc_FFE9445C:\n"                           
                                        
                "BL      sub_FFE963B4\n"
                "B       loc_FFE944C4\n"
"loc_FFE94464:\n"                           
                                        
                "BL      sub_FFE96448\n"
                "B       loc_FFE944C4\n"
"loc_FFE9446C:\n"                           
                                        
                "BL      sub_FFE96544\n"
                "B       loc_FFE944C4\n"
"loc_FFE94474:\n"                           
                                        
                "MOV     R0, #0\n"
                "BL      sub_FFE967B0\n"
                "B       loc_FFE944C4\n"
"loc_FFE94480:\n"                           
                                        
                "BL      sub_FFE96984\n"
                "B       loc_FFE944C4\n"
"loc_FFE94488:\n"                           
                                        
                "BL      sub_FFE96A20\n"
                "B       loc_FFE944C4\n"
"loc_FFE94490:\n"                           
                                        
                "BL      sub_FFE96AE0\n"
                "B       loc_FFE944C4\n"
"loc_FFE94498:\n"                           
                                        
                "BL      sub_FFE94DB4\n"
                "BL      sub_FFE93E94\n"
                "B       loc_FFE944C4\n"
"loc_FFE944A4:\n"                           
                                        
                "BL      sub_FFE96684\n"
                "B       loc_FFE944C4\n"
"loc_FFE944AC:\n"                           
                                        
                "BL      sub_FFE966E0\n"
                "B       loc_FFE944C4\n"
"loc_FFE944B4:\n"                           
                "MOV     R1, #0x4C0\n"
                "LDR     R0, =0xFFE93CF0\n"
                "ADD     R1, R1, #0xE\n"
                "BL      sub_FFEB5664\n"
"loc_FFE944C4:\n"                           
                                        
                "LDR     R2, [SP]\n"
"loc_FFE944C8:\n"                           
                                        
                "LDR     R3, =0x7E568\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFEA7E0C\n"
                "LDR     R0, [SP]\n"
                "BL      sub_FFE93D70\n"
"loc_FFE944E0:\n"                           
                "LDR     R3, =0x7E56C\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFEA8524\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFE94384\n"
                "LDR     R0, =0xFFE93CF0\n"
                "MOV     R1, #0x400\n"
                "BL      sub_FFEB5664\n"
                "BL      sub_FFEA9AE8\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

