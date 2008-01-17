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
    long *nrflag = (long*)0x9F90;

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

void __attribute__((naked,noinline)) sub_FFD0A3CC_my(){ 
 asm volatile(
                 "STMFD   SP!, {R0-R10,LR}\n"
                 "MOV     R6, #0\n"
                 "MOV     R4, R0\n"
                 "BL      sub_FFD0AEB4\n"
                 "MVN     R1, #0\n"
                 "BL      sub_FFC18E20\n"
                 "MOV     R2, #4\n"
                 "ADD     R1, SP, #8\n"
                 "MOV     R0, #0x8A\n"
                 "BL      sub_FFC59C2C\n"
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x20A\n"
                 "LDRNE   R0, =0xFFD0A5A0\n"
                 "BLNE    sub_FFC0C098\n"
                 "LDR     R8, =0x1933C\n"
                 "LDR     R5, =0x19290\n"
                 "LDRSH   R1, [R8,#0xE]\n"
                 "LDR     R0, [R5,#0x74]\n"
                 "BL      sub_FFCD0C9C\n"
                 "BL      sub_FFC39108\n"
                 "LDR     R2, =0x9F94\n"
                 "ADD     R3, R4, #0x8C\n"
                 "STRH    R0, [R4,#0x88]\n"
                 "STR     R2, [SP]\n"
                 "STR     R3, [SP,#4]\n"
                 "MOV     R1, R0\n"
                 "LDRH    R0, [R5,#0x4C]\n"
                 "LDRSH   R2, [R8,#0xC]\n"
                 "LDR     R3, =0x9F90\n"
		 "BL      sub_FFD0B3A0\n"
                 "BL      capt_seq_hook_set_nr\n"
                 "B       sub_FFD0A440\n"
 );
}


void __attribute__((naked,noinline)) task_CaptSeqTask_my() //#fs
{
	asm volatile (
                "STMFD   SP!, {R3-R7,LR}\n"
                "LDR     R6, =0x5680\n"

"loc_FFC4CB6C:\n"
                "LDR     R0, [R6,#8]\n"
                "MOV     R2, #0\n"
                "MOV     R1, SP\n"
                "BL      sub_FFC19070\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFC4CB98\n"
                "LDR     R1, =0x43F\n"
                "LDR     R0, =0xFFC4C924\n" // aSsshoottask_c ; SsShootTask.c
                "BL      sub_FFC0C098\n"    // Assert
                "BL      sub_FFC0BE50\n"    // ExitTask
                "LDMFD   SP!, {R3-R7,PC}\n"

"loc_FFC4CB98:\n"
                //LDR     R0, [SP,#0x18+var_18]
                "LDR     R0, [SP]\n"
                "LDR     R1, [R0]\n"

                "LDR     R2, =0x1850\n"         // DEBUG: Save jumptable-target ...
                "STR     R1, [R2]\n"            // ...to some unused space. Read and displayed in GUI in core/gui.c

                "CMP     R1, #0x16\n"
                "ADDLS   PC, PC, R1,LSL#2\n"
                "B       loc_FFC4CD80\n"        // 0: error handler (invalid jump offset) (also when shutter half-pressed?)

                "B       loc_FFC4CC08\n"        // 1: immediately after shutter release, !modify this one!
                "B       loc_FFC4CC10\n"
                "B       loc_FFC4CC88\n"        // 3: default if shutter not pressed
                "B       loc_FFC4CC9C\n"        // 4: after shutter release, when timed image preview active
                "B       loc_FFC4CC94\n"        // 5: after shutter release, in detailed image review
                "B       loc_FFC4CCA4\n"
                "B       loc_FFC4CCAC\n"
                "B       loc_FFC4CCB8\n"
                "B       loc_FFC4CD10\n"        // 9: also ends with continuation of #1
                "B       loc_FFC4CC9C\n"        // 10:
                "B       loc_FFC4CD18\n"        // 11:
                "B       loc_FFC4CD20\n"        // 12:
                "B       loc_FFC4CD28\n"        // 13:
                "B       loc_FFC4CD30\n"        // 14:
                "B       loc_FFC4CD38\n"        // 15: in image-viewer
                "B       loc_FFC4CD40\n"
                "B       loc_FFC4CD48\n"
                "B       loc_FFC4CD50\n"
                "B       loc_FFC4CD58\n"
                "B       loc_FFC4CD64\n"
                "B       loc_FFC4CD70\n"
                "B       loc_FFC4CD78\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CC08:\n"                               // #1
                "BL      sub_FFD08E6C\n"        
                "BL      shooting_expo_param_override\n"  // +
                "B       loc_FFC4CCB0\n"
"loc_FFC4CC10:\n"                               // #2
                "LDR     R4, [R0,#0xC]\n"
                "LDR     R0, [R4,#8]\n"
                "ORR     R0, R0, #1\n"
                "STR     R0, [R4,#8]\n"
                "MOV     R0, #2\n"
                "BL      sub_FFC48200\n"
                "BL      sub_FFD08E5C\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD092AC\n"
                "TST     R0, #1\n"
                "MOVNE   R2, R4\n"
                "MOVNE   R1, #1\n"
                "BNE     loc_FFC4CD08\n"
                "BL      sub_FFD1D7E0\n"
                "BL      sub_FFC59DBC\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD0A2E4\n"
                "BL      sub_FFD0AD48\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD0A3CC_my\n"         //--------------> 
                "BL      capt_seq_hook_raw_here\n"  //-------------->
                "MOV     R2, R4\n"
                "MOV     R1, #1\n"
                "BL      sub_FFC4B2F8\n"
                "BL      sub_FFD0A798\n"
                "CMP     R0, #0\n"
                "LDRNE   R0, [R4,#8]\n"
                "ORRNE   R0, R0, #0x2000\n"
                "STRNE   R0, [R4,#8]\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CC88:\n"
                "MOV     R0, #1\n"
                "BL      sub_FFD08FFC\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CC94:\n"
                "BL      sub_FFD08A88\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CC9C:\n"
                "BL      sub_FFD08E4C\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CCA4:\n"
                "BL      sub_FFD08E54\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CCAC:\n"
                "BL      sub_FFD08F1C\n"
"loc_FFC4CCB0:\n"
                "BL      sub_FFC4AF60\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CCB8:\n"
                "LDR     R4, [R0,#0xC]\n"
                "BL      sub_FFD08E5C\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD0962C\n"
                "TST     R0, #1\n"
                "MOV     R5, R0\n"
                "BNE     loc_FFC4CCF8\n"
                "BL      sub_FFC59DBC\n"
                "STR     R0, [R4,#0x14]\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD0A2E4\n"
                "MOV     R0, R4\n"
                "BL      sub_FFD0A7F8\n"
                "MOV     R5, R0\n"
                "LDR     R0, [R4,#0x14]\n"
                "BL      sub_FFC59FD0\n"
"loc_FFC4CCF8:\n"
                "BL      sub_FFD08E4C\n"
                "MOV     R2, R4\n"
                "MOV     R1, #8\n"
                "MOV     R0, R5\n"
"loc_FFC4CD08:\n"
                "BL      sub_FFC4B2F8\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD10:\n"
                "BL      sub_FFD08F78\n"
                "B       loc_FFC4CCB0\n"
"loc_FFC4CD18:\n"
                "BL      sub_FFD09898\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD20:\n"
                "BL      sub_FFD09A50\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD28:\n"
                "BL      sub_FFD09AE0\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD30:\n"
                "BL      sub_FFD09B94\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD38:\n"
                "MOV     R0, #0\n"
                "B       loc_FFC4CD5C\n"
"loc_FFC4CD40:\n"
                "BL      sub_FFD09EC8\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD48:\n"
                "BL      sub_FFD09F5C\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD50:\n"
                "BL      sub_FFD0A01C\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD58:\n"
                "MOV     R0, #1\n"
"loc_FFC4CD5C:\n"
                "BL      sub_FFD09D88\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD64:\n"
                "BL      sub_FFD09128\n"
                "BL      sub_FFC15B44\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD70:\n"
                "BL      sub_FFD09C50\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD78:\n"
                "BL      sub_FFD09CBC\n"
                "B       loc_FFC4CD8C\n"
"loc_FFC4CD80:\n"
                "LDR     R1, =0x523\n"
                "LDR     R0, =0xFFC4C924\n" // aSsshoottask_c ; SsShootTask.c
                "BL      sub_FFC0C098\n"    // Assert
"loc_FFC4CD8C:\n"
                //"LDR     R0, [SP,#0x18+var_18]\n"
                "LDR     R0, [SP]\n"
                "LDR     R1, [R0,#4]\n"
                "LDR     R0, [R6,#4]\n"
                "BL      sub_FFC18DEC\n"
                //"LDR     R4, [SP,#0x18+var_18]\n"
                "LDR     R4, [SP]\n"
                "LDR     R0, [R4,#8]\n"
                "CMP     R0, #0\n"
                "MOVEQ   R1, #0xFC\n"
                "LDREQ   R0, =0xFFC4C924\n" // aSsshoottask_c ; SsShootTask.c
                "BLEQ    sub_FFC0C098\n"    // Assert
                "MOV     R0, #0\n"
                "STR     R0, [R4,#8]\n"
                "B       loc_FFC4CB6C\n"
    );
} //#fe
