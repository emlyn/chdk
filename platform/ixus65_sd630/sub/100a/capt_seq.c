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
    long *nrflag = (long*)0x61F4;

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

void __attribute__((naked,noinline)) sub_FF963344_my(long p)
{
#if 1
    asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R3, =0x6F3BC\n"
                "LDR     R5, =0x61F0\n"
                "SUB     SP, SP, #4\n"
                "MVN     R1, #0\n"
                "STR     R0, [R5]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FF04\n"
                "LDR     R3, =0x99EC0\n"
                "LDR     R0, [R3,#0x7C]\n"
                "BL      sub_FF89EFF0\n"
                "BL      sub_FF963298\n"
          //    "BL      wait_until_remote_button_is_released\n"
	    	"BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0x61F8\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF89F4B0\n"

		"B	 sub_FF963380\n"
    );
#endif
}

void __attribute__((naked,noinline)) sub_FF95FEA0_my(long p)
{
    asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "LDR     R4, [R0,#0xC]\n"
                 "BL      sub_FF968658\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF95FEB8\n"
                 "BL      sub_FF968664\n"
 "loc_FF95FEB8:\n"
                 "LDR     R3, =0x99EC0\n"
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BNE     loc_FF95FEEC\n"
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF968678\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF95FEEC\n"
                 "MOV     R0, #1\n"
 "loc_FF95FEDC:\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF95E574\n"
 "loc_FF95FEEC:\n"
                 "LDR     R3, =0x99EC0\n"
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BNE     loc_FF95FF3C\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF962100\n"
                 "TST     R0, #1\n"
                 "BNE     loc_FF95FEDC\n"
                 "BL      sub_FF9A15A8\n"
                 "BL      sub_FF824ADC\n"
                 "LDR     R2, =0x99E04\n"
                 "ADD     R3, R4, R4,LSL#1\n"
                 "STR     R0, [R2,R3,LSL#5]\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF963AB0\n"
                 "BL      sub_FF962604\n"
                 "BL      sub_FF9625A0\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF963344_my\n"  //------------->

                 "BL      capt_seq_hook_raw_here\n"

                 "B       loc_FF95FF50\n"
 "loc_FF95FF3C:\n"
                 "LDR     R3, =0x61E0\n"
                 "LDR     R2, [R3]\n"
                 "CMP     R2, #0\n"
                 "MOVNE   R0, #0x1D\n"
                 "MOVEQ   R0, #0\n"
 "loc_FF95FF50:\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF95E574\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF96353C\n"
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "SUB     SP, SP, #4\n"
                 "MOV     R4, SP\n"
                 "B       loc_FF96048C\n"
 "loc_FF960324:\n"
                 "LDR     R2, [SP]\n"
                 "LDR     R3, [R2]\n"
                 "MOV     R0, R2\n"
                 "CMP     R3, #0x14\n"
                 "LDRLS   PC, [PC,R3,LSL#2]\n"
                 "B       loc_FF960460\n"
                 ".long loc_FF960390\n"
                 ".long loc_FF9603B0\n"
                 ".long loc_FF9603C4\n"
                 ".long loc_FF9603D4\n"
                 ".long loc_FF9603CC\n"
                 ".long loc_FF9603DC\n"
                 ".long loc_FF9603E4\n"
                 ".long loc_FF9603F0\n"
                 ".long loc_FF9603F8\n"
                 ".long loc_FF960404\n"
                 ".long loc_FF96040C\n"
                 ".long loc_FF960414\n"
                 ".long loc_FF96041C\n"
                 ".long loc_FF960424\n"
                 ".long loc_FF96042C\n"
                 ".long loc_FF960438\n"
                 ".long loc_FF960440\n"
                 ".long loc_FF960448\n"
                 ".long loc_FF960450\n"
                 ".long loc_FF960458\n"
                 ".long loc_FF960474\n"
 "loc_FF960390:\n"
                 "BL      sub_FF961D60\n"
                 "BL      shooting_expo_param_override\n"   // +
                 "BL      sub_FF95E090\n"
                 "LDR     R3, =0x99EC0\n"
                 "LDR     R2, [R3,#0x24]\n"
                 "CMP     R2, #0\n"
                 "BEQ     loc_FF960470\n"
                 "BL      sub_FF95FF70\n"
                 "B       loc_FF960470\n"
 "loc_FF9603B0:\n"
                 "BL      sub_FF95FEA0_my\n" //------------->
 "loc_FF9603B4:\n"
                 "LDR     R2, =0x99EC0\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [R2,#0x24]\n"
                 "B       loc_FF960470\n"
 "loc_FF9603C4:\n"
                 "BL      sub_FF9620F0\n"
                 "B       loc_FF960470\n"
 "loc_FF9603CC:\n"
                 "BL      sub_FF960F60\n"
                 "B       loc_FF9603B4\n"
 "loc_FF9603D4:\n"
                 "BL      sub_FF9612FC\n"
                 "B       loc_FF9603B4\n"
 "loc_FF9603DC:\n"
                 "BL      sub_FF96130C\n"
                 "B       loc_FF960470\n"
 "loc_FF9603E4:\n"
                 "BL      sub_FF961E44\n"
                 "BL      sub_FF95E090\n"
                 "B       loc_FF960470\n"
 "loc_FF9603F0:\n"
                 "BL      sub_FF960044\n"
                 "B       loc_FF960470\n"
 "loc_FF9603F8:\n"
                 "BL      sub_FF961EAC\n"
                 "BL      sub_FF95E090\n"
                 "B       loc_FF960470\n"
 "loc_FF960404:\n"
                 "BL      sub_FF9612FC\n"
                 "B       loc_FF960470\n"
 "loc_FF96040C:\n"
                 "BL      sub_FF962644\n"
                 "B       loc_FF960470\n"
 "loc_FF960414:\n"
                 "BL      sub_FF962988\n"
                 "B       loc_FF960470\n"
 "loc_FF96041C:\n"
                 "BL      sub_FF962A0C\n"
                 "B       loc_FF960470\n"
 "loc_FF960424:\n"
                 "BL      sub_FF962AFC\n"
                 "B       loc_FF960470\n"
 "loc_FF96042C:\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF962BC4\n"
                 "B       loc_FF960470\n"
 "loc_FF960438:\n"
                 "BL      sub_FF962D30\n"
                 "B       loc_FF960470\n"
 "loc_FF960440:\n"
                 "BL      sub_FF962DC4\n"
                 "B       loc_FF960470\n"
 "loc_FF960448:\n"
                 "BL      sub_FF962E80\n"
                 "B       loc_FF960470\n"
 "loc_FF960450:\n"
                 "BL      sub_FF962F6C\n"
                 "B       loc_FF960470\n"
 "loc_FF960458:\n"
                 "BL      sub_FF962FC0\n"
                 "B       loc_FF960470\n"
 "loc_FF960460:\n"
                 "MOV     R1, #0x36C\n"
                 "LDR     R0, =0xFF95FC2C\n"
                 "ADD     R1, R1, #1\n"
                 "BL      sub_FF813B80\n"
 "loc_FF960470:\n"
                 "LDR     R2, [SP]\n"
 "loc_FF960474:\n"
                 "LDR     R3, =0x6F344\n"
                 "LDR     R1, [R2,#4]\n"
                 "LDR     R0, [R3]\n"
                 "BL      sub_FF81FD68\n"
                 "LDR     R0, [SP]\n"
                 "BL      sub_FF95FCA8\n"
 "loc_FF96048C:\n"
                 "LDR     R3, =0x6F348\n"
                 "MOV     R1, R4\n"
                 "LDR     R0, [R3]\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF820480\n"
                 "TST     R0, #1\n"
                 "BEQ     loc_FF960324\n"
                 "MOV     R1, #0x2A4\n"
                 "LDR     R0, =0xFF95FC2C\n"
                 "ADD     R1, R1, #3\n"
                 "BL      sub_FF813B80\n"
                 "BL      sub_FF8219DC\n"
                 "ADD     SP, SP, #4\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}





