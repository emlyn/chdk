#include "lolevel.h"
#include "platform.h"
#include "core.h"


#include "stdlib.h"


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
	long *nrflag = (long*)0x6164;

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


void __attribute__((naked,noinline)) capt_seq_task(){
	asm volatile (
		"STMFD   SP!, {R4,LR}\n"
		"SUB     SP, SP, #4\n"
		"MOV     R4, SP\n"
		"B       loc_FFD34C78\n"
	"loc_FFD34B20:\n"
		"LDR     R2, [SP,#0xC-0xC]\n"
		"LDR     R3, [R2]\n"
		"MOV     R0, R2\n"
		"CMP     R3, #0x15\n"
		"LDRLS   PC, [PC,R3,LSL#2]\n"
		"B       loc_FFD34C4C\n"
		".long loc_FFD34B90\n"
		".long loc_FFD34B9C\n"
		".long loc_FFD34BA4\n"
		".long loc_FFD34BB4\n"
		".long loc_FFD34BAC\n"
		".long loc_FFD34BBC\n"
		".long loc_FFD34BC4\n"
		".long loc_FFD34BD0\n"
		".long loc_FFD34BD8\n"
		".long loc_FFD34BE4\n"
		".long loc_FFD34BEC\n"
		".long loc_FFD34BF4\n"
		".long loc_FFD34BFC\n"
		".long loc_FFD34C04\n"
		".long loc_FFD34C0C\n"
		".long loc_FFD34C18\n"
		".long loc_FFD34C20\n"
		".long loc_FFD34C28\n"
		".long loc_FFD34C30\n"
		".long loc_FFD34C3C\n"
		".long loc_FFD34C44\n"
		".long loc_FFD34C60\n"
	"loc_FFD34B90:\n"
		"BL      sub_FFD3646C\n"
		"BL      shooting_expo_param_override\n"   // +
		"BL      sub_FFD3279C\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34B9C:\n"
         //       "BL      sub_FFD34704\n"
		"BL      sub_FFD34704_my\n"	//-------->
		"B       loc_FFD34C5C\n"
	"loc_FFD34BA4:\n"
		"BL      sub_FFD36804\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BAC:\n"
		"BL      sub_FFD356C0\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BB4:\n"
		"BL      sub_FFD35AF8\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BBC:\n"
		"BL      sub_FFD35B08\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BC4:\n"
		"BL      sub_FFD36550\n"
		"BL      sub_FFD3279C\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BD0:\n"
		"BL      sub_FFD34810\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BD8:\n"
		"BL      sub_FFD365B8\n"
		"BL      sub_FFD3279C\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BE4:\n"
		"BL      sub_FFD35AF8\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BEC:\n"
		"BL      sub_FFD36D94\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BF4:\n"
		"BL      sub_FFD370D8\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34BFC:\n"
		"BL      sub_FFD3715C\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C04:\n"
		"BL      sub_FFD3724C\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C0C:\n"
		"MOV     R0, #0\n"
		"BL      sub_FFD37314\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C18:\n"
		"BL      sub_FFD37480\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C20:\n"
		"BL      sub_FFD37514\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C28:\n"
		"BL      sub_FFD375D4\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C30:\n"
		"MOV     R0, #1\n"
		"BL      sub_FFD37314\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C3C:\n"
		"BL      sub_FFD376C0\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C44:\n"
		"BL      sub_FFD37714\n"
		"B       loc_FFD34C5C\n"
	"loc_FFD34C4C:\n"
		"MOV     R1, #0x36C\n"
		"LDR     R0, =0xFFD34490\n"
		"ADD     R1, R1, #1\n"
		"BL      sub_FFC03AE8\n"
	"loc_FFD34C5C:\n"
		"LDR     R2, [SP,#0xC-0xC]\n"
	"loc_FFD34C60:\n"
		"LDR     R3, =0x64CD4\n"
		"LDR     R1, [R2,#4]\n"
		"LDR     R0, [R3]\n"
		"BL      sub_FFC0F9A8\n"
		"LDR     R0, [SP,#0xC-0xC]\n"
		"BL      sub_FFD3450C\n"
	"loc_FFD34C78:\n"
		"LDR     R3, =0x64CD8\n"
		"MOV     R1, R4\n"
		"LDR     R0, [R3]\n"
		"MOV     R2, #0\n"
		"BL      sub_FFC100C0\n"
		"TST     R0, #1\n"
		"BEQ     loc_FFD34B20\n"
		"MOV     R1, #0x2A4\n"
		"LDR     R0, =0xFFD34490\n"
		"ADD     R1, R1, #3\n"
		"BL      sub_FFC03AE8\n"
		"BL      sub_FFC1161C\n"
		"ADD     SP, SP, #4\n"
		"LDMFD   SP!, {R4,PC}\n"
	);
}





void __attribute__((naked,noinline)) sub_FFD37A98_my(long p)
{
	asm volatile (
		"STMFD   SP!, {R4-R6,LR}\n"
		"LDR     R3, =0x64D4C\n"
		"LDR     R5, =0x6160\n"		// nrflag - 4
		"SUB     SP, SP, #4\n"
		//"LDR     R1, =0xFFFFFFFF\n"       //MOVL
                "MVN     R1, #0\n"                      //MOVL
		"STR     R0, [R5]\n"
		"LDR     R0, [R3]\n"
		"BL      sub_FFC0FB44\n"
		"LDR     R3, =0x8F360\n"
		"LDR     R0, [R3,#0x74]\n"
		"BL      sub_FFC8C01C\n"
		"BL      sub_FFD379EC\n"
        //    "BL      wait_until_remote_button_is_released\n"
		"BL      capt_seq_hook_set_nr\n" // +
		"LDR     R3, =0x6168\n"
		"LDR     R0, [R3]\n"

		"B       sub_FFD37AD0\n"
	);
}



void __attribute__((naked,noinline)) sub_FFD34704_my(long p)
{
	asm volatile (
		"STMFD   SP!, {R4,LR}\n"
		"LDR     R4, [R0,#0xC]\n"
		"BL      sub_FFD3CE2C\n"
		"CMP     R0, #0\n"
		"BNE     sub_FFD3471C\n"
		"BL      sub_FFD3CE38\n"
	"sub_FFD3471C:\n"
		"MOV     R0, #0xC\n"
		"BL      sub_FFD3CE4C\n"
		"TST     R0, #1\n"
		"MOV     R2, R4\n"
		"MOV     R0, R4\n"
		"BEQ     sub_FFD34744\n"
		"MOV     R0, #1\n"
		"MOV     R1, R0\n"
		"LDMFD   SP!, {R4,LR}\n"
		"B       sub_FFD32BF8\n"
	"sub_FFD34744:\n"
		"BL      sub_FFD36814\n"
		"TST     R0, #1\n"
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"BEQ     sub_FFD34760\n"
		"LDMFD   SP!, {R4,LR}\n"
		"B       sub_FFD32BF8\n"
	"sub_FFD34760:\n"
		"BL      sub_FFD74E34\n"
		"BL      sub_FFC146EC\n"
		"LDR     R2, =0x8F2A4\n"
		"ADD     R3, R4, R4,LSL#1\n"
		"STR     R0, [R2,R3,LSL#5]\n"
		"MOV     R0, R4\n"
		"BL      sub_FFD38204\n"
		"BL      sub_FFD36D54\n"
		"BL      sub_FFD36CDC\n"
		"MOV     R0, R4\n"
		"BL      sub_FFD37A98_my\n"  //---------->
        //        "BL      sub_FFD37A98\n"
                "BL      capt_seq_hook_raw_here\n"  // +
		"MOV     R2, R4\n"
		"MOV     R1, #1\n"
		"BL      sub_FFD32BF8\n"
		"LDMFD   SP!, {R4,LR}\n"
		"B       sub_FFD37C90\n"

	);
}
