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
    long *nrflag = (long*)0xED44;

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


void __attribute__((naked,noinline)) sub_FFB10B64_my(long p)
{
    asm volatile (
"		STMFD	SP!, {R4,LR}\n"
"		MOV	R4, R0\n"
"		SUB	SP, SP,	#0xC\n"
"		BL	sub_FFB115D4\n"

//"		MOVL	R1, 0xFFFFFFFF\n"	// asm doesn't like this. Thus:
	       "MVN     R1, #0\n"

"		BL	sub_FFB21E2C\n" //ClearEventFlag
"		MOV	R0, #0x8A\n"
"		ADD	R1, SP,	#4\n"
"		MOV	R2, #4\n"
"		BL	sub_FF81BC98\n"
"		TST	R0, #1\n"
"		BEQ	loc_FFB10BA4\n"

"		MOV	R1, #0x1D0\n"
// means: "	MOV	R1, #0x1D,28\n"

"		LDR	R0, =0xFFB109E8\n" //"SsCaptureSeq.c"
"		ADD	R1, R1,	#2\n"
"		BL	sub_FFB2F4F0\n" //DebugAssert
"loc_FFB10BA4:\n"
"		LDR	R3, =0xAAB80\n"
"		LDR	R2, =0xAAC40\n"
"		LDR	R0, [R3,#0x7C]\n"
"		LDRSH	R1, [R2,#0xE]\n"
"		BL	sub_FFA4226C\n"
"		MOV	R0, R4\n"
"		BL	sub_FFB1096C\n"
               "BL      capt_seq_hook_set_nr\n"  // + <- ADDED !!!!!
"		LDR	R3, =0xED48\n"
"		LDR	R0, [R3]\n"
	       "B       sub_FFB10BC8\n"  // ---> jump to the original code in ROM, see below
//FFB10BC8	BL	sub_FFA42780
    );
}

// orig. is sub_FFB0D80C
void __attribute__((naked,noinline)) sub_FFB0D80C_my(long p)
{
    asm volatile (
	
"                STMFD   SP!, {R4,R5,LR}\n"
"                LDR     R5, =0xAAB80\n"
"                LDR     R4, [R0,#0xC]\n"
"                LDR     R2, [R5,#0x24]\n"
"                LDR     R3, [R4,#8]\n"
"                CMP     R2, #0\n"
"                ORR     R3, R3, #1\n"
"                STR     R3, [R4,#8]\n"
"                BNE     loc_FFB0D838\n"
"                MOV     R0, #2\n"
"                BL      sub_FFAF1CA4\n"
"loc_FFB0D838:\n"
"                BL      sub_FFB0E394\n" //Set_CMD25Write_62
"                LDR     R3, [R5,#0x24]\n"
"                CMP     R3, #0\n"
"                BNE     loc_FFB0D8A4\n"
"                MOV     R0, R4\n"
"                BL      sub_FFB0F59C\n"
"                TST     R0, #1\n"
"                BEQ     loc_FFB0D868\n"
"                MOV     R2, R4\n"
"                MOV     R1, #1\n"
"                LDMFD   SP!, {R4,R5,LR}\n"
"                B       sub_FFB0BF7C\n"
"loc_FFB0D868:\n"
"                BL      sub_FF826284\n"
"                BL      sub_FF81BE94\n"
"                LDRH    R2, [R5]\n"
//"                MOVL    R3, 0x420F\n"	// asm doesn't understand this. Thus:
		"MOV	R3, #0x4200\n"
// means:	"MOV	R3, #0x42,24\n"
		"ADD	R3, R3, #0xF\n"

"                CMP     R2, R3\n"
"                STR     R0, [R4,#0x14]\n"
"                BNE     loc_FFB0D88C\n"
"                BL      sub_FFAF185C\n"
"loc_FFB0D88C:\n"
"                MOV     R0, R4\n"
"                BL      sub_FFB10A4C\n"
"                BL      sub_FFB11440\n"
"                MOV     R0, R4\n"
//"                BL      sub_FFB10B64\n"
                "BL      sub_FFB10B64_my\n"  //---------> ESCAPE to My !!!!!
                "BL      capt_seq_hook_raw_here\n"  // + <- ADDED !!!!!
"                B       loc_FFB0D8B8\n"
"loc_FFB0D8A4:\n"
"                LDR     R3, =0xED30\n"
"                LDR     R2, [R3]\n"
"                CMP     R2, #0\n"
"                MOVNE   R0, #0x1D\n"
"                MOVEQ   R0, #0\n"
"loc_FFB0D8B8:\n"
"                MOV     R1, #1\n"
"                MOV     R2, R4\n"
"                BL      sub_FFB0BF7C\n"
"                BL      sub_FFB10EE0\n"
"                CMP     R0, #0\n"
"                LDRNE   R3, [R4,#8]\n"
"                ORRNE   R3, R3, #0x2000\n"
"                STRNE   R3, [R4,#8]\n"
"                LDMFD   SP!, {R4,R5,PC}\n"
    );
}

// orig. at FFB0DD10
void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                SUB     SP, SP, #4\n"
"                MOV     R4, SP\n"
"                B       loc_FFB0DEB4\n"
"loc_FFB0DD20:\n"
"                LDR     R2, [SP]\n"
"                LDR     R3, [R2]\n"
"                MOV     R0, R2\n"
"                CMP     R3, #0x17\n"
"                LDRLS   PC, [PC,R3,LSL#2]\n"
"                B       loc_FFB0DE88\n"
"                .long loc_FFB0DD98\n"
"                .long loc_FFB0DDB8\n"
"                .long loc_FFB0DDCC\n"
"                .long loc_FFB0DDE0\n"
"                .long loc_FFB0DDD8\n"
"                .long loc_FFB0DDE8\n"
"                .long loc_FFB0DDF0\n"
"                .long loc_FFB0DDFC\n"
"                .long loc_FFB0DE04\n"
"                .long loc_FFB0DE10\n"
"                .long loc_FFB0DE18\n"
"                .long loc_FFB0DE20\n"
"                .long loc_FFB0DE28\n"
"                .long loc_FFB0DE30\n"
"                .long loc_FFB0DE38\n"
"                .long loc_FFB0DE40\n"
"                .long loc_FFB0DE48\n"
"                .long loc_FFB0DE54\n"
"                .long loc_FFB0DE5C\n"
"                .long loc_FFB0DE64\n"
"                .long loc_FFB0DE6C\n"
"                .long loc_FFB0DE78\n"
"                .long loc_FFB0DE80\n"
"                .long loc_FFB0DE9C\n"
"loc_FFB0DD98:\n"
"                BL      sub_FFB0E3BC\n"
                "BL      shooting_expo_param_override\n"   // + <- ADDED !!!!!
"                BL      sub_FFB0BA04\n"
"                LDR     R3, =0xAAB80\n"
"                LDR     R2, [R3,#0x24]\n"
"                CMP     R2, #0\n"
"                BEQ     loc_FFB0DE98\n"
"                BL      sub_FFB0D8E4\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DDB8:\n"
//"                BL      sub_FFB0D80C\n"
"                BL      sub_FFB0D80C_my\n"  //---------> ESCAPE to My !!!!!
"loc_FFB0DDBC:\n"
"                LDR     R2, =0xAAB80\n"
"                MOV     R3, #0\n"
"                STR     R3, [R2,#0x24]\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DDCC:\n"
"                MOV     R0, #1\n"
"                BL      sub_FFB0E5E8\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DDD8:\n"
"                BL      sub_FFB0DFA0\n"
"                B       loc_FFB0DDBC\n"
"loc_FFB0DDE0:\n"
"                BL      sub_FFB0E374\n" //BackLightDrv_LcdBackLightOff_16
"                B       loc_FFB0DDBC\n"
"loc_FFB0DDE8:\n"
"                BL      sub_FFB0E384\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DDF0:\n"
"                BL      sub_FFB0E4D8\n"
"                BL      sub_FFB0BA04\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DDFC:\n"
"                BL      sub_FFB0D9BC\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE04:\n"
"                BL      sub_FFB0E54C\n"
"                BL      sub_FFB0BA04\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE10:\n"
"                BL      sub_FFB0E374\n" //BackLightDrv_LcdBackLightOff_16
"                B       loc_FFB0DE98\n"
"loc_FFB0DE18:\n"
"                BL      sub_FFB0FCD0\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE20:\n"
"                BL      sub_FFB0FEA4\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE28:\n"
"                BL      sub_FFB0FF38\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE30:\n"
"                BL      sub_FFB10034\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE38:\n"
"                BL      sub_FFB102BC\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE40:\n"
"                BL      sub_FFB1030C\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE48:\n"
"                MOV     R0, #0\n"
"                BL      sub_FFB10360\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE54:\n"
"                BL      sub_FFB10534\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE5C:\n"
"                BL      sub_FFB105D0\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE64:\n"
"                BL      sub_FFB1069C\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE6C:\n"
"                BL      sub_FFB0E73C\n"
"                BL      sub_FFB0D730\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE78:\n"
"                BL      sub_FFB10174\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE80:\n"
"                BL      sub_FFB101D0\n"
"                B       loc_FFB0DE98\n"
"loc_FFB0DE88:\n"
"                MOV     R1, #0x4F0\n"
"                LDR     R0, =0xFFB0D58C\n" //=aSsshoottask_c
"                ADD     R1, R1, #1\n"
"                BL      sub_FFB2F4F0\n" //DebugAssert
"loc_FFB0DE98:\n"
"                LDR     R2, [SP]\n"
"loc_FFB0DE9C:\n"
"                LDR     R3, =0x84428\n"
"                LDR     R1, [R2,#4]\n"
"                LDR     R0, [R3]\n"
"                BL      sub_FFB21C90\n" //SetEventFlag
"                LDR     R0, [SP]\n"
"                BL      sub_FFB0D60C\n"
"loc_FFB0DEB4:\n"
"                LDR     R3, =0x8442C\n"
"                MOV     R1, R4\n"
"                LDR     R0, [R3]\n"
"                MOV     R2, #0\n"
"                BL      sub_FFB223A8\n" //ReceiveMessageQueue
"                TST     R0, #1\n"
"                BEQ     loc_FFB0DD20\n"
"                MOV     R1, #0x410\n"
"                LDR     R0, =0xFFB0D58C\n" //=aSsshoottask_c
"                ADD     R1, R1, #5\n"
"                BL      sub_FFB2F4F0\n" //DebugAssert
"                BL      sub_FFB2396C\n"
"                ADD     SP, SP, #4\n"
"                LDMFD   SP!, {R4,PC}\n"
	);
}

