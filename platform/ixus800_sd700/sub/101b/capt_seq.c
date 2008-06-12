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
    long *nrflag = (long*)0x61B0;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = NR_OFF;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = NR_ON;
	break;
    };
}


void __attribute__((naked,noinline)) sub_FF961D24_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R3, =0x6F2EC\n"
                "LDR     R5, =0x61AC\n"
                "SUB     SP, SP, #4\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FF08\n" //ClearEventFlag
                "BL      wait_until_remote_button_is_released\n"
                "LDR     R3, =0x99F00\n"
                "LDR     R0, [R3,#0x7C]\n"
                "BL      sub_FF89E02C\n" //IsEmptyWriteCache_42
                "BL      sub_FF961C78\n"
                "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"

		"B       sub_FF961D54\n"
    );
}

void __attribute__((naked,noinline)) sub_FF95E864_my(long p)
{
    asm volatile (
	
"                 STMFD   SP!, {R4,R5,LR}\n"
"                 LDR     R4, [R0,#0xC]\n"
"                 BL      sub_FF96702C\n"
"                 CMP     R0, #0\n"
"                 BNE     loc_FF95E87C\n"
"                 BL      sub_FF967038\n"
" loc_FF95E87C:\n"  
"                 LDR     R3, =0x99F00\n"
"                 LDR     R2, [R3,#0x24]\n"
"                 CMP     R2, #0\n"
"                 BNE     loc_FF95E8B0\n"
"                 MOV     R0, #0xC\n"
"                 BL      sub_FF96704C\n"
"                 TST     R0, #1\n"
"                 BEQ     loc_FF95E8B0\n"
"                 MOV     R0, #1\n"
" loc_FF95E8A0:\n"
"                 MOV     R2, R4\n"
"                 MOV     R1, #1\n"
"                 LDMFD   SP!, {R4,R5,LR}\n"
"                 B       sub_FF95CF4C\n"
" loc_FF95E8B0:\n"
"                 LDR     R5, =0x99F00\n"
"                 LDR     R3, [R5,#0x24]\n"
"                 CMP     R3, #0\n"
"                 BNE     loc_FF95E8CC\n"
"                 MOV     R0, #2\n"
"                 BL      sub_FFAB8A88\n"
"                 LDR     R3, [R5,#0x24]\n"
" loc_FF95E8CC:\n"
"                 CMP     R3, #0\n"
"                 BNE     loc_FF95E914\n"
"                 MOV     R0, R4\n"
"                 BL      sub_FF960AE0\n"
"                 TST     R0, #1\n"
"                 BNE     loc_FF95E8A0\n"
"                 BL      sub_FF99FE3C\n"
"                 BL      sub_FF824AE0\n"
"                 LDR     R2, =0x99E44\n"
"                 ADD     R3, R4, R4,LSL#1\n"
"                 STR     R0, [R2,R3,LSL#5]\n"
"                 MOV     R0, R4\n"
"                 BL      sub_FF962490\n"
"                 BL      sub_FF960FE4\n"
"                 BL      sub_FF960F80\n"
"                 MOV     R0, R4\n"
"		  BL      sub_FF961D24_my\n"
"		  BL      capt_seq_hook_raw_here\n"
"                 B       loc_FF95E928\n"
" loc_FF95E914:\n"
"                 LDR     R3, =0x619C\n"
"                 LDR     R2, [R3]\n"
"                 CMP     R2, #0\n"
"                 MOVNE   R0, #0x1D\n"
"                 MOVEQ   R0, #0\n"
" loc_FF95E928:\n"
"                 MOV     R2, R4\n"
"                 MOV     R1, #1\n"
"                 BL      sub_FF95CF4C\n"
"                 LDMFD   SP!, {R4,R5,LR}\n"
"                 B       sub_FF961F1C\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "SUB     SP, SP, #4\n"
                "MOV     R4, SP\n"
                "B       loc_FF95EE64\n"
"loc_FF95ECFC:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x14\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FF95EE38\n"
		".long loc_FF95ED68\n"
                ".long loc_FF95ED88\n"
                ".long loc_FF95ED9C\n"
                ".long loc_FF95EDAC\n"
                ".long loc_FF95EDA4\n"
                ".long loc_FF95EDB4\n"
                ".long loc_FF95EDBC\n"
                ".long loc_FF95EDC8\n"
                ".long loc_FF95EDD0\n"
                ".long loc_FF95EDDC\n"
                ".long loc_FF95EDE4\n"
                ".long loc_FF95EDEC\n"
                ".long loc_FF95EDF4\n"
                ".long loc_FF95EDFC\n"
                ".long loc_FF95EE04\n"
                ".long loc_FF95EE10\n"
                ".long loc_FF95EE18\n"
                ".long loc_FF95EE20\n"
                ".long loc_FF95EE28\n"
                ".long loc_FF95EE30\n"
                ".long loc_FF95EE4C\n"

		
"loc_FF95ED68:\n"
                "BL      sub_FF960740\n"
                "BL      shooting_expo_param_override\n"  // +
                "BL      sub_FF95CA6C\n"
		"LDR     R3, =0x99F00\n"
		"LDR     R2, [R3,#0x24]\n"
		"CMP     R2, #0\n"
		"BEQ     loc_FF95EE48\n"
		"BL      sub_FF95E948\n"
                "B       loc_FF95EE48\n"
"loc_FF95ED88:\n"
                "BL      sub_FF95E864_my\n" //Our only real change
"loc_FF95ED8C:\n"
		"LDR     R2, =0x99F00\n"
		"MOV     R3, #0\n"
		"STR     R3, [R2,#0x24]\n"
		"B       loc_FF95EE48\n"
"loc_FF95ED9C:\n"
                "BL      sub_FF960AD0\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDA4:\n"
                "BL	  sub_FF95F938\n"
                "B       loc_FF95ED8C\n"
" loc_FF95EDAC:\n"
                "BL      sub_FF95FCD4\n" //BackLightDrv_LcdBackLightOff_3
                "B       loc_FF95ED8C\n"
"loc_FF95EDB4:\n"
                "BL      sub_FF95FCE4\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDBC:\n"
                "BL      sub_FF960824\n"
                "BL      sub_FF95CA6C\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDC8:\n"
                "BL      sub_FF95EA1C\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDD0:\n"
                "BL      sub_FF96088C\n"
                "BL      sub_FF95CA6C\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDDC:\n"
                "BL      sub_FF95FCD4\n" //BackLightDrv_LcdBackLightOff_3
                "B       loc_FF95EE48\n"
"loc_FF95EDE4:\n"
                "BL      sub_FF961024\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDEC:\n"
                "BL      sub_FF961368\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDF4:\n"
                "BL      sub_FF9613EC\n"
                "B       loc_FF95EE48\n"
"loc_FF95EDFC:\n"
                "BL      sub_FF9614DC\n"
                "B       loc_FF95EE48\n"
"loc_FF95EE04:\n"
                "MOV     R0, #0\n"
                "BL      sub_FF9615A4\n"
                "B       loc_FF95EE48\n"
"loc_FF95EE10:\n"
                "BL      sub_FF961710\n"
                "B       loc_FF95EE48\n"
"loc_FF95EE18:\n"
                "BL      sub_FF9617A4\n"
                "B       loc_FF95EE48\n"
"loc_FF95EE20:\n"
                "BL      sub_FF961860\n"
                "B       loc_FF95EE48\n"
"loc_FF95EE28:\n"
                "BL      sub_FF96194C\n"
                "B       loc_FF95EE48\n"
"loc_FF95EE30:\n"
                "BL      sub_FF9619A0\n"
                "B       loc_FF95EE48\n"
"loc_FF95EE38:\n"
                "MOV     R1, #0x36C\n"
                "LDR     R0, =0xFF95E5F0\n" //=aShoottask_c
                "ADD     R1, R1, #1\n"
                "BL      sub_FF813B80\n" //DebugAssert
"loc_FF95EE48:\n"
                "LDR     R2, [SP,#0xC-0xC]\n"
"loc_FF95EE4C:\n"
                "LDR     R3, =0x6F274\n"
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FD6C\n" //SetEventFlag
                "LDR     R0, [SP,#0xC-0xC]\n"
                "BL      sub_FF95E66C\n"
"loc_FF95EE64:\n"
                "LDR     R3, =0x6F278\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FF820484\n" //ReceiveMessageQueue
                "TST     R0, #1\n"
                "BEQ     loc_FF95ECFC\n"
                "MOV     R1, #0x2A4\n"
                "LDR     R0, =0xFF95E5F0\n" //=aShoottask_c
                "ADD     R1, R1, #3\n"
                "BL      sub_FF813B80\n" //DebugAssert
                "BL      sub_FF8219E0\n" //ExitTask
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

