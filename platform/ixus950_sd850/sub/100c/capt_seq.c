#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0xED44;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FFB0D8E4_my(long p)
{
    asm volatile (
"		STMFD   SP!, {R4,LR}\n"
"		BL      sub_FFB0D420\n"
"		LDR     R3, =0xAAB80\n"
"		LDR     R2, [R3,#0x24]\n"
"		CMP     R2, #0\n"
"		MOV     R4, R0\n"
"		MOV     R0, #0xC\n"
"		BEQ     loc_FFB0D92C\n"
"		BL      sub_FFB17EE8\n"
"		TST     R0, #1\n"
"		BEQ     loc_FFB0D92C\n"
"		LDR     R3, [R4,#8]\n"
"		LDR     R2, =0xED30\n"
"		ORR     R3, R3, #0x40000000\n"
"		MOV     R1, #1\n"
"		STR     R1, [R2]\n"
"		STR     R3, [R4,#8]\n"
"		LDMFD   SP!, {R4,PC}\n"
"loc_FFB0D92C:\n"
"		BL      sub_FF826284\n"
"		BL      sub_FF81BE94\n"
"		STR     R0, [R4,#0x14]\n"
"		MOV     R0, R4\n"
	"BL  sub_FFB10B64_my\n"	//---> escape to My!
	"BL  capt_seq_hook_raw_here\n"  // + <----- RAW hook
"		TST     R0, #1\n"
"		LDRNE   R3, =0xED30\n"
"		MOVNE   R2, #1\n"
"		STRNE   R2, [R3]\n"
"		LDMFD   SP!, {R4,PC}\n"
    );
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
            "BL      wait_until_remote_button_is_released\n"
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
"                BL      sub_FFB0D8E4_my\n"   //<---- extra RAW hook inside
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







/*
ROM:FF976A78     var_38          = -0x38
ROM:FF976A78     var_34          = -0x34
ROM:FF976A78     var_30          = -0x30
ROM:FF976A78     var_24          = -0x24
ROM:FF976A78     var_20          = -0x20
ROM:FF976A78     var_1E          = -0x1E
ROM:FF976A78     var_1C          = -0x1C
*/
//void __attribute__((naked,noinline)) _task_ExpDrvTask() {
void __attribute__((naked,noinline)) exp_drv_task() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n" // @ Store Block to Memory
                 "SUB     SP, SP, #0x20\n" //   @ Rd = Op1 - Op2
                 "ADD     R7, SP, #0x4\n" //  @ Rd = Op1 + Op2
                 "B       loc_FF976F88\n" //    @ Branch


     "loc_FF976A88:\n" //                           @ CODE XREF: task_ExpDrvTask+530
                 "CMP     R2, #0x22\n" // @ '"' @ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976AA0\n"    //@ Branch

                 "LDR     R0, [R12,#0x8C]\n" //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R12,#0x88]\n" //@ Indirect Jump
                 "B       loc_FF976B04\n"    //@ Branch



     "loc_FF976AA0:\n"                           //@ CODE XREF: task_ExpDrvTask+14
                 "CMP     R2, #0x1D\n"       //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976AB4\n"    //@ Branch

                 "MOV     R0, R12\n"         //@ Rd = Op2
                 "BL      sub_FF976948\n"    //@ Branch with Link

                 "B       loc_FF976AF4\n"    //@ Branch



     "loc_FF976AB4:\n"                           //@ CODE XREF: task_ExpDrvTask+2C
                 "CMP     R2, #0x1E\n"       //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976AC8\n"    //@ Branch

                 "MOV     R0, R12\n"         //@ Rd = Op2
                 "BL      sub_FF9769A4\n"    //@ Branch with Link

                 "B       loc_FF976AF4\n"    //@ Branch



     "loc_FF976AC8:\n"                           //@ CODE XREF: task_ExpDrvTask+40
                 "SUB     R3, R2, #0x1F\n"   //@ Rd = Op1 - Op2
                 "CMP     R3, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BHI     loc_FF976AE0\n"    //@ Branch

                 "MOV     R0, R12\n"         //@ Rd = Op2
                 "BL      sub_FF976A00\n"    //@ Branch with Link

                 "B       loc_FF976AF4\n"    //@ Branch



     "loc_FF976AE0:\n"                           //@ CODE XREF: task_ExpDrvTask+58
                 "CMP     R2, #0x21\n"           // @ '!' Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976B10\n"    //@ Branch

                 "BL      sub_FF93C0BC\n"    //@ Branch with Link

                 "BL      sub_FF93F1F4\n"    //@ Branch with Link

                 "BL      sub_FF93E42C\n"    //@ Branch with Link


     "loc_FF976AF4:\n"                           //@ CODE XREF: task_ExpDrvTask+38
                 "LDR     R3, [SP,#4]\n"     //@ Load from Memory
                 "LDR     R0, [R3,#0x8C]\n"  //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R3,#0x88]\n"  //@ Indirect Jump

     "loc_FF976B04:\n"                           //@ CODE XREF: task_ExpDrvTask+24
                 "LDR     R0, [SP,#0x4]\n" //@ Load from Memory
                 "BL      sub_FF9722A8\n"    //@ Branch with Link

                 "B       loc_FF976F88\n"    //@ Branch


     "loc_FF976B10:\n"                           //@ CODE XREF: task_ExpDrvTask+6C
                 "CMP     R2, #0xD\n"        //@ Set cond. codes on Op1 - Op2
                 "MOV     R8, #1\n"          //@ Rd = Op2
                 "BNE     loc_FF976B80\n"    //@ Branch

                 "LDR     R1, [R12,#0x7C]\n" //@ Load from Memory
                 "ADD     R1, R1, R1,LSL#1\n" //@ Rd = Op1 + Op2
                 "ADD     R1, R12, R1,LSL#2\n" //@ Rd = Op1 + Op2
                 "ADD     R6, SP, #0x14\n"   //@ Rd = Op1 + Op2
                 "SUB     R1, R1, #8\n"      //@ Rd = Op1 - Op2
                 "MOV     R2, #0xC\n"        //@ Rd = Op2
                 "MOV     R0, R6\n"          //@ Rd = Op2
                 "BL      _memcpy\n"          //@ Branch with Link

                 "LDR     R0, [SP,#4]\n" //@ Load from Memory
                 "BL      sub_FF974F0C\n"    //@ Branch with Link

                 "LDR     R3, [SP,#04]\n" //@ Load from Memory
                 "LDR     R1, [R3,#0x7C]\n"  //@ Load from Memory
                 "LDR     R2, [R3,#0x8C]\n"  //@ Load from Memory
                 "ADD     R0, R3, #4\n"      //@ Rd = Op1 + Op2
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R3,#0x88]\n"  //@ Indirect Jump
                 "LDR     R0, [SP,#4]\n" //@ Load from Memory
                 "BL      sub_FF9751D8\n"    //@ Branch with Link

                 "LDR     R3, [SP,#04]\n" //@ Load from Memory
                 "ADD     R0, R3, #4\n"      //@ Rd = Op1 + Op2
                 "LDR     R1, [R3,#0x7C]\n"  //@ Load from Memory
                 "LDR     R2, [R3,#0x94]\n"  //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R3,#0x90]\n"  //@ Indirect Jump
                 "B       loc_FF976ED0\n"    //@ Branch



     "loc_FF976B80:\n"                           //@ CODE XREF: task_ExpDrvTask+A0
                 "SUB     R3, R2, #0xE\n"    //@ Rd = Op1 - Op2
                 "CMP     R3, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BHI     loc_FF976C3C\n"    //@ Branch

                 "ADD     R6, SP, #0x14\n" //@ Rd = Op1 + Op2
                 "ADD     R5, SP, #0x8\n" //@ Rd = Op1 + Op2
                 "MOV     R0, R12\n"         //@ Rd = Op2
                 "MOV     R1, R6\n"          //@ Rd = Op2
                 "MOV     R2, R5\n"          //@ Rd = Op2
                 "BL      sub_FF9752C8\n"    //@ Branch with Link

                 "MOV     R4, R0\n"          //@ Rd = Op2
                 "CMP     R4, #5\n"          //@ Set cond. codes on Op1 - Op2
                 "CMPNE   R4, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976BD4\n"    //@ Branch

                 "LDR     R12, [SP,#0x4]\n" //@ Load from Memory
                 "MOV     R0, R5\n"          //@ Rd = Op2
                 "LDR     R1, [R12,#0x7C]\n" //@ Load from Memory
                 "MOV     R2, R4\n"          //@ Rd = Op2
                 "LDR     R3, [R12,#0x8C]\n" //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R12,#0x88]\n" //@ Indirect Jump
                 "B       loc_FF976C0C\n"    //@ Branch



     "loc_FF976BD4:\n"                           //@ CODE XREF: task_ExpDrvTask+138
                 "CMP     R4, #6\n"          //@ Set cond. codes on Op1 - Op2
                 "CMPNE   R4, #2\n"          //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976C1C\n"    //@ Branch

                 "LDR     R12, [SP,#0x4]\n" //@ Load from Memory
                 "MOV     R0, R5\n"          //@ Rd = Op2
                 "MOV     R1, R8\n"          //@ Rd = Op2
                 "MOV     R2, R4\n"          //@ Rd = Op2
                 "LDR     R3, [R12,#0x8C]\n" //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R12,#0x88]\n" //@ Indirect Jump
                 "MOV     R1, R6\n"          //@ Rd = Op2
                 "LDR     R0, [SP,#0x4]\n" //@ Load from Memory
                 "MOV     R2, R5\n"          //@ Rd = Op2
                 "BL      sub_FF976578\n"    //@ Branch with Link


     "loc_FF976C0C:\n"                           //@ CODE XREF: task_ExpDrvTask+158
                 "MOV     R1, R4\n"          //@ Rd = Op2
                 "LDR     R0, [SP,#04]\n" //@ Load from Memory
                 "BL      sub_FF9768DC\n"    //@ Branch with Link

                 "B       loc_FF976ED0\n"    //@ Branch


     "loc_FF976C1C:\n"                           //@ CODE XREF: task_ExpDrvTask+164
                 "LDR     R12, [SP,#0x4]\n" //@ Load from Memory
                 "MOV     R2, R4\n"          //@ Rd = Op2
                 "ADD     R0, R12, #4\n"     //@ Rd = Op1 + Op2
                 "LDR     R1, [R12,#0x7C]\n" //@ Load from Memory
                 "LDR     R3, [R12,#0x8C]\n" //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R12,#0x88]\n" //@ Indirect Jump
                 "B       loc_FF976ED0\n"    //@ Branch



     "loc_FF976C3C:\n"                           //@ CODE XREF: task_ExpDrvTask+110
                 "SUB     R3, R2, #0x19\n"   //@ Rd = Op1 - Op2
                 "CMP     R3, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BHI     loc_FF976C94\n"    //@ Branch

                 "LDR     R1, [R12,#0x7C]\n" //@ Load from Memory
                 "ADD     R1, R1, R1,LSL#1\n" //@ Rd = Op1 + Op2
                 "ADD     R1, R12, R1,LSL#2\n" //@ Rd = Op1 + Op2
                 "ADD     R6, SP, #0x14\n" //@ Rd = Op1 + Op2
                 "SUB     R1, R1, #8\n"      //@ Rd = Op1 - Op2
                 "MOV     R2, #0xC\n"        //@ Rd = Op2
                 "MOV     R0, R6\n"          //@ Rd = Op2
                 "BL      _memcpy\n"          //@ Branch with Link

                 "LDR     R0, [SP,#0x4]\n" //@ Load from Memory
                 "BL      sub_FF97430C\n"    //@ Branch with Link

                 "LDR     R3, [SP,#0x4]\n" //@ Load from Memory
                 "ADD     R0, R3, #4\n"      //@ Rd = Op1 + Op2
                 "LDR     R1, [R3,#0x7C]\n"  //@ Load from Memory
                 "LDR     R2, [R3,#0x8C]\n"  //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R3,#0x88]\n"  //@ Indirect Jump
                 "LDR     R0, [SP,#0x4]\n" //@ Load from Memory
                 "BL      sub_FF97462C\n"    //@ Branch with Link

                 "B       loc_FF976ED0\n"    //@ Branch



     "loc_FF976C94:\n"                           //@ CODE XREF: task_ExpDrvTask+1CC
                 "ADD     R6, SP, #0x14\n" //@ Rd = Op1 + Op2
                 "ADD     R1, R12, #4\n"     //@ Rd = Op1 + Op2
                 "MOV     R2, #0xC\n"        //@ Rd = Op2
                 "MOV     R0, R6\n"          //@ Rd = Op2
                 "BL      _memcpy\n"          //@ Branch with Link

                 "LDR     R12, [SP,#0x4]\n" //@ Load from Memory
                 "LDR     R3, [R12]\n"       //@ Load from Memory
                 "MOV     R2, R12\n"         //@ Rd = Op2
                 "CMP     R3, #0x1C\n"       //@ Set cond. codes on Op1 - Op2
                 "LDRLS   PC, [PC,R3,LSL#2]\n" //@ Indirect Jump

                 "B       loc_FF976EBC\n"    //@ Branch


                 ".long loc_FF976D34\n"
                 ".long loc_FF976D40\n"
                 ".long loc_FF976D4C\n"
                 ".long loc_FF976D4C\n"
                 ".long loc_FF976D34\n"
                 ".long loc_FF976D40\n"
                 ".long loc_FF976D4C\n"
                 ".long loc_FF976D4C\n"
                 ".long loc_FF976D70\n"
                 ".long loc_FF976D70\n"
                 ".long loc_FF976E90\n"
                 ".long loc_FF976E9C\n"
                 ".long loc_FF976EAC\n"
                 ".long loc_FF976EBC\n"
                 ".long loc_FF976EBC\n"
                 ".long loc_FF976EBC\n"
                 ".long loc_FF976D58\n"
                 ".long loc_FF976D64\n"
                 ".long loc_FF976D80\n"
                 ".long loc_FF976D8C\n"
                 ".long loc_FF976DC4\n"
                 ".long loc_FF976DFC\n"
                 ".long loc_FF976E34\n"
                 ".long loc_FF976E6C\n"
                 ".long loc_FF976E6C\n"
                 ".long loc_FF976EBC\n"
                 ".long loc_FF976EBC\n"
                 ".long loc_FF976E78\n"
                 ".long loc_FF976E84\n"


     "loc_FF976D34:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF972C08\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976D40:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF972EAC\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976D4C:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF973120\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976D58:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF97341C\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976D64:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF973684\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976D70:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
//                 "BL      sub_FF973980\n"    //@ Branch with Link
                 "BL      sub_FF973980_my\n"    //@ Branch with Link this is the place where the function lies where ewvar also creates its own version of, so we just do the same here

                 "MOV     R8, #0\n"          //@ Rd = Op2
                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976D80:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF973AE0\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch


     "loc_FF976D8C:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "LDRH    R1, [R2,#4]\n"     //@ Load from Memory
//                 "LDR     R3, =0x2E4A8\n"  //@ Load from Memory
                 "LDR     R3, =0x2E4A8\n"  //@ Load from Memory
                 "STRH    R1, [SP,#0x14]\n" //@ Store to Memory
                 "LDRH    R1, [R3,#6]\n"     //@ Load from Memory
                 "STRH    R1, [SP,#0x1A]\n" //@ Store to Memory
                 "LDRH    R1, [R3,#2]\n"     //@ Load from Memory
                 "STRH    R1, [SP,#0x16]\n" //@ Store to Memory
                 "LDRH    R3, [R3,#4]\n"     //@ Load from Memory
                 "STRH    R3, [SP,#0x18]\n" //@ Store to Memory
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "LDRH    R2, [R2,#0xC]\n"   //@ Load from Memory
                 "STRH    R2, [SP,#0x1C]\n" //@ Store to Memory
                 "BL      sub_FF973DDC\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch


     "loc_FF976DC4:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "LDRH    R2, [R2,#4]\n"     //@ Load from Memory
                 "LDR     R3, =0x2E4A8\n"  //@ Load from Memory
                 "STRH    R2, [SP,#0x14]\n" //@ Store to Memory
                 "LDRH    R2, [R3,#8]\n"     //@ Load from Memory
                 "STRH    R2, [SP,#0x1C]\n" //@ Store to Memory
                 "LDRH    R1, [R3,#2]\n"     //@ Load from Memory
                 "STRH    R1, [SP,#0x16]\n" //@ Store to Memory
                 "LDRH    R2, [R3,#4]\n"     //@ Load from Memory
                 "STRH    R2, [SP,#0x18]\n" //@ Store to Memory
                 "LDRH    R3, [R3,#6]\n"     //@ Load from Memory
                 "STRH    R3, [SP,#0x1A]\n" //@ Store to Memory
                 "BL      sub_FF973F04\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch


     "loc_FF976DFC:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "LDR     R3, =0x2E4A8\n"  //@ Load from Memory
                 "LDRH    R1, [R3]\n"        //@ Load from Memory
                 "STRH    R1, [SP,#0x14]\n" //@ Store to Memory
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "LDRH    R2, [R2,#6]\n"     //@ Load from Memory
                 "STRH    R2, [SP,#0x16]\n" //@ Store to Memory
                 "LDRH    R2, [R3,#8]\n"     //@ Load from Memory
                 "STRH    R2, [SP,#0x1C]\n" //@ Store to Memory
                 "LDRH    R1, [R3,#4]\n"     //@ Load from Memory
                 "STRH    R1, [SP,#0x18]\n" //@ Store to Memory
                 "LDRH    R3, [R3,#6]\n"     //@ Load from Memory
                 "STRH    R3, [SP,#0x1A]\n" //@ Store to Memory
                 "BL      sub_FF973FC8\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch


     "loc_FF976E34:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "LDR     R3, =0x2E4A8\n"  //@ Load from Memory
                 "LDRH    R1, [R3,#6]\n"     //@ Load from Memory
                 "STRH    R1, [SP,#0x1A]\n" //@ Store to Memory
                 "LDRH    R1, [R3]\n"        //@ Load from Memory
                 "STRH    R1, [SP,#0x14]\n" //@ Store to Memory
                 "LDRH    R1, [R3,#2]\n"     //@ Load from Memory
                 "STRH    R1, [SP,#0x16]\n" //@ Store to Memory
                 "LDRH    R3, [R3,#4]\n"     //@ Load from Memory
                 "STRH    R3, [SP,#0x18]\n" //@ Store to Memory
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "LDRH    R2, [R2,#0xC]\n"   //@ Load from Memory
                 "STRH    R2, [SP,#0x1C]\n" //@ Store to Memory
                 "BL      sub_FF974080\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976E6C:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF974130\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976E78:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF974778\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976E84:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF974A24\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976E90:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "BL      sub_FF974BE0\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976E9C:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "MOV     R1, #0\n"          //@ Rd = Op2
                 "BL      sub_FF974DC8\n"    //@ Branch with Link

                 "B       loc_FF976EB8\n"    //@ Branch

     "loc_FF976EAC:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "MOV     R0, R2\n"          //@ Rd = Op2
                 "MOV     R1, #1\n"          //@ Rd = Op2
                 "BL      sub_FF974DC8\n"    //@ Branch with Link


     "loc_FF976EB8:\n"                           //@ CODE XREF: task_ExpDrvTask+2C4
                 "LDR     R12, [SP,#0x4]\n" //@ Load from Memory

     "loc_FF976EBC:\n"                           //@ CODE XREF: task_ExpDrvTask+240
                 "ADD     R0, R12, #4\n"     //@ Rd = Op1 + Op2
                 "LDR     R1, [R12,#0x7C]\n" //@ Load from Memory
                 "LDR     R2, [R12,#0x8C]\n" //@ Load from Memory
                 "MOV     LR, PC\n"          //@ Rd = Op2
                 "LDR     PC, [R12,#0x88]\n" //@ Indirect Jump

     "loc_FF976ED0:\n"                           //@ CODE XREF: task_ExpDrvTask+104
                 "CMP     R8, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976EF8\n"    //@ Branch

                 "LDR     R1, [SP,#0x4]\n" //@ Load from Memory
                 "LDR     R3, [R1,#0x7C]\n"  //@ Load from Memory
                 "ADD     R3, R3, R3,LSL#1\n" //@ Rd = Op1 + Op2
                 "ADD     R1, R1, R3,LSL#2\n" //@ Rd = Op1 + Op2
                 "MOV     R0, R6\n"          //@ Rd = Op2
                 "SUB     R1, R1, #8\n"      //@ Rd = Op1 - Op2
                 "BL      sub_FF9728C0\n"    //@ Branch with Link

                 "B       loc_FF976F74\n"    //@ Branch


     "loc_FF976EF8:\n"                           //@ CODE XREF: task_ExpDrvTask+45C
                 "LDR     R3, [SP,#0x4]\n" //@ Load from Memory
                 "LDR     R2, [R3]\n"        //@ Load from Memory
                 "CMP     R2, #9\n"          //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976F40\n"    //@ Branch

                 "MOV     R4, #0\n"          //@ Rd = Op2
                 "MOV     R1, #1\n"          //@ Rd = Op2
                 "MOV     R2, R1\n"          //@ Rd = Op2
                 "MOV     R3, R1\n"          //@ Rd = Op2
                 "MOV     R0, R4\n"          //@ Rd = Op2
                 "STR     R4, [SP]\n" //@ Store to Memory
                 "BL      sub_FF972804\n"    //@ Branch with Link

                 "MOV     R1, #1\n"          //@ Rd = Op2
                 "MOV     R0, R4\n"          //@ Rd = Op2
                 "MOV     R2, R1\n"          //@ Rd = Op2
                 "MOV     R3, R1\n"          //@ Rd = Op2
                 "STR     R4, [SP]\n" //@ Store to Memory
                 "BL      sub_FF972A5C\n"    //@ Branch with Link

                 "B       loc_FF976F74\n"    //@ Branch


     "loc_FF976F40:\n"                           //@ CODE XREF: task_ExpDrvTask+48C
                 "MOV     R4, #1\n"          //@ Rd = Op2
                 "MOV     R0, R4\n"          //@ Rd = Op2
                 "MOV     R1, R4\n"          //@ Rd = Op2
                 "MOV     R2, R4\n"          //@ Rd = Op2
                 "MOV     R3, R4\n"          //@ Rd = Op2
                 "STR     R4, [SP]\n" //@ Store to Memory
                 "BL      sub_FF972804\n"    //@ Branch with Link

                 "MOV     R0, R4\n"          //@ Rd = Op2
                 "MOV     R1, R0\n"          //@ Rd = Op2
                 "MOV     R2, R0\n"          //@ Rd = Op2
                 "MOV     R3, R0\n"          //@ Rd = Op2
                 "STR     R4, [SP]\n" //@ Store to Memory
                 "BL      sub_FF972A5C\n"    //@ Branch with Link


     "loc_FF976F74:\n"                           //@ CODE XREF: task_ExpDrvTask+47C
                 "LDR     R2, =0x2E4F4\n"  //@ Load from Memory
                 "MOV     R3, #0\n"          //@ Rd = Op2
                 "LDR     R0, [SP,#0x4]\n" //@ Load from Memory
                 "STR     R3, [R2]\n"        //@ Store to Memory
                 "BL      sub_FF9722A8\n"    //@ Branch with Link


     "loc_FF976F88:\n"                           //@ CODE XREF: task_ExpDrvTask+C
                 "LDR     R3, =0x2E49C\n"  //@ Load from Memory
                 "MOV     R2, #0\n"          //@ Rd = Op2
                 "LDR     R0, [R3]\n"        //@ Load from Memory
                 "MOV     R1, R7\n"          //@ Rd = Op2
//                 "BL      ReceiveMessageQueue\n" //@ Branch with Link
                 "BL      sub_FFB223A8\n" //@ Branch with Link

                 "LDR     R12, [SP,#0x4]\n" //@ Load from Memory
                 "LDR     R2, [R12]\n"       //@ Load from Memory
                 "CMP     R2, #0x23\n" //  @ '#'  Set cond. codes on Op1 - Op2
                 "BNE     loc_FF976A88\n"    //@ Branch

                 "MOV     R0, R12\n"         //@ Rd = Op2
                 "BL      sub_FF9722A8\n"    //@ Branch with Link

                 "LDR     R3, =0x2E498\n"  //@ Load from Memory
                 "MOV     R1, #1\n"          //@ Rd = Op2
                 "LDR     R0, [R3]\n"        //@ Load from Memory
//                 "BL      SetEventFlag\n"    //@ Branch with Link
                 "BL      sub_FFB21C90\n"    //@ Branch with Link

                 "BL      _ExitTask\n"       //@ Branch with Link

                 "ADD     SP, SP, #0x20\n"   //@ Rd = Op1 + Op2
                 "LDMFD   SP!, {R4-R8,PC}\n" //@ Load Block from Memory

//		 "RET\n"                     //@ Return from Subroutine
		 );
}

void __attribute__((naked,noinline)) sub_FF973980_my() {
    asm volatile(

     "sub_FF973980:\n"                           //@ CODE XREF: task_ExpDrvTask+2FC
                 "STMFD   SP!, {R4-R6,LR}\n" //@ Store Block to Memory
                 "LDR     R3, =0x2E498\n"  //@ Load from Memory
                 "MOV     R4, R0\n"          //@ Rd = Op2
                 "MOV     R1, #0x3E\n"   // @ '>' Rd = Op2
                 "LDR     R0, [R3]\n"        //@ Load from Memory
//                 "BL      ClearEventFlag\n"  //@ Branch with Link
                 "BL      sub_FFB21E2C\n"  //@ Branch with Link

                 "MOV     R1, #0\n"          //@ Rd = Op2
                 "LDRSH   R0, [R4,#4]\n"     //@ Load from Memory
                 "BL      sub_FF9723DC\n"    //@ Branch with Link

                 "MOV     R6, R0\n"          //@ Rd = Op2
                 "LDRSH   R0, [R4,#6]\n"     //@ Load from Memory
                 "BL      sub_FF972544\n"    //@ Branch with Link

                 "LDRSH   R0, [R4,#8]\n"     //@ Load from Memory
                 "BL      sub_FF9725E0\n"    //@ Branch with Link

                 "LDRSH   R0, [R4,#0xA]\n"   //@ Load from Memory
                 "BL      sub_FF97267C\n"    //@ Branch with Link

                 "LDRSH   R0, [R4,#0xC]\n"   //@ Load from Memory
                 "BL      sub_FF972718\n"    //@ Branch with Link

                 "LDR     R3, [R4]\n"        //@ Load from Memory
                 "CMP     R3, #9\n"          //@ Set cond. codes on Op1 - Op2
                 "MOV     R5, R0\n"          //@ Rd = Op2
                 "MOVEQ   R5, #0\n"          //@ Rd = Op2
                 "MOVEQ   R6, R5\n"          //@ Rd = Op2
                 "CMP     R6, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF973A04\n"    //@ Branch

                 "MOV     R2, #2\n"          //@ Rd = Op2
                 "LDRSH   R0, [R4,#4]\n"     //@ Load from Memory
//                 "LDR     R1, =loc_FF9722FC\n" //@ Load from Memory
                 "LDR     R1, =0xFF9722FC\n" //@ Load from Memory
                 "BL      sub_FFAE28F8\n"    //@ Branch with Link

                 "LDR     R2, =0x2E4E8\n"  //@ Load from Memory
                 "MOV     R3, #0\n"          //@ Rd = Op2
                 "STR     R3, [R2]\n"        //@ Store to Memory
                 "B       loc_FF973A08\n"    //@ Branch


     "loc_FF973A04:\n"                           //@ CODE XREF: sub_FF973980+60
                 "BL      sub_FF9727B4\n"    //@ Branch with Link


     "loc_FF973A08:\n"                           //@ CODE XREF: sub_FF973980+80
                 "STRH    R0, [R4,#4]\n"     //@ Store to Memory
                 "CMP     R5, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF973A28\n"    //@ Branch

                 "LDRSH   R0, [R4,#0xC]\n"   //@ Load from Memory
//                 "LDR     R1, =loc_FF9723C0\n" //@ Load from Memory
                 "LDR     R1, =0xFF9723C0\n" //@ Load from Memory
                 "MOV     R2, #0x20\n" //  @ ' ' @ Rd = Op2
                 "BL      sub_FF972BA8\n"    //@ Branch with Link

                 "B       loc_FF973A2C\n"    //@ Branch

     "loc_FF973A28:\n"                           //@ CODE XREF: sub_FF973980+90
                 "BL      sub_FF9727F4\n"    //@ Branch with Link

     "loc_FF973A2C:\n"                           //@ CODE XREF: sub_FF973980+A4
                 "STRH    R0, [R4,#0xC]\n"   //@ Store to Memory
                 "LDRSH   R0, [R4,#6]\n"     //@ Load from Memory
                 "BL      sub_FF93BD38_my\n"    //@ Branch with Link // again an ewvar copy of a function which we also are going to replace

                 "LDRSH   R0, [R4,#8]\n"     //@ Load from Memory
                 "MOV     R1, #1\n"          //@ Rd = Op2
                 "BL      sub_FF93DFEC\n"    //@ Branch with Link

                 "ADD     R0, R4, #8\n"      //@ Rd = Op1 + Op2
                 "MOV     R1, #0\n"          //@ Rd = Op2
                 "BL      sub_FF93E0AC\n"    //@ Branch with Link

                 "LDRSH   R0, [R4,#0xE]\n"   //@ Load from Memory
                 "BL      sub_FF9605D0\n"    //@ Branch with Link

                 "CMP     R6, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "BNE     loc_FF973A90\n"    //@ Branch

                 "LDR     R3, =0x2E498\n"  //@ Load from Memory
                 "MOV     R2, #0xBB0\n"      //@ Rd = Op2
                 "LDR     R0, [R3]\n"        //@ Load from Memory
                 "MOV     R1, #2\n"          //@ Rd = Op2
                 "ADD     R2, R2, #8\n"      //@ Rd = Op1 + Op2
//                 "BL      unknown_libname_854\n" //@ "Canon A-Series Firmware"
                 "BL      sub_FFB21C80\n" //@ "Canon A-Series Firmware"

                 "TST     R0, #1\n"          //@ Set cond. codes on Op1 & Op2
                 "BEQ     loc_FF973A90\n"    //@ Branch

                 "MOV     R1, #0x500\n"      //@ Rd = Op2
//                 "LDR     R0, =aExpdrv_c\n"  //@ Load from Memory
                 "LDR     R0, =0xFF972254\n"  //@ Load from Memory => string "ExpDrv.c"
                 "ADD     R1, R1, #8\n"      //@ Rd = Op1 + Op2
//                 "BL      DebugAssert\n"     //@ Branch with Link
                 "BL      sub_FFB2F4F0\n"     //@ Branch with Link


     "loc_FF973A90:\n"                           //@ CODE XREF: sub_FF973980+DC
                 "CMP     R5, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "LDMNEFD SP!, {R4-R6,PC}\n" //@ Load Block from Memory
                 "LDR     R3, =0x2E498\n"  //@ Load from Memory
                 "MOV     R2, #0xBB0\n"      //@ Rd = Op2
                 "LDR     R0, [R3]\n"        //@ Load from Memory
                 "MOV     R1, #0x20\n"       // @ ' '\n" //@ Rd = Op2
                 "ADD     R2, R2, #8\n"      //@ Rd = Op1 + Op2
//                 "BL      unknown_libname_854\n" //@ "Canon A-Series Firmware"
                 "BL      sub_FFB21C80\n" //@ "Canon A-Series Firmware"

                 "TST     R0, #1\n"          //@ Set cond. codes on Op1 & Op2
                 "LDMEQFD SP!, {R4-R6,PC}\n" //@ Load Block from Memory
                 "MOV     R1, #0x500\n"      //@ Rd = Op2
//                 "LDR     R0, =aExpdrv_c\n"  //@ Load from Memory
                 "LDR     R0, =0xFF972254\n"  //@ Load from Memory
                 "ADD     R1, R1, #0xD\n"    //@ Rd = Op1 + Op2
                 "LDMFD   SP!, {R4-R6,LR}\n" //@ Load Block from Memory
//                 "B       DebugAssert\n"     //@ Branch
                 "B       sub_FFB2F4F0\n"     //@ Branch with Link

	    );
}

void __attribute__((naked,noinline)) sub_FF93BD38_my(){
asm volatile(


     "sub_FF93BD38:\n"                           //@ CODE XREF: sub_FF93D684+Cp
                 "STMFD   SP!, {R4,LR}\n"    //@ Store Block to Memory
//                 "LDR     R3, =unk_6544\n"   //@ Load from Memory
                 "LDR     R3, =0x6544\n"   //@ Load from Memory
                 "LDR     R2, [R3]\n"        //@ Load from Memory
                 "MOV     R1, #0x168\n"      //@ Rd = Op2
                 "MOV     R3, R0,LSL#16\n"   //@ Rd = Op2
                 "CMP     R2, #1\n"          //@ Set cond. codes on Op1 - Op2
                 "ADD     R1, R1, #3\n"      //@ Rd = Op1 + Op2
//                 "LDR     R0, =aShutter_c\n" //@ Load from Memory => string "Shutter.c"
                 "LDR     R0, =0xFF93B554\n" //@ Load from Memory
                 "MOV     R4, R3,ASR#16\n"   //@ Rd = Op2
                 "BEQ     loc_FF93BD64\n"    //@ Branch

  //               "BL      DebugAssert\n"     //@ Branch with Link
                 "BL      sub_FFB2F4F0\n"     //@ Branch with Link


     "loc_FF93BD64:\n"                           //@ CODE XREF: sub_FF93BD38+24j
                 "MOV     R1, #0x170\n"      //@ Rd = Op2
                 "CMN     R4, #0xC00\n"      //@ Set cond. codes on Op1 + Op2
//                 "LDR     R3, =unk_15036\n"  //@ Load from Memory
                 "LDR     R3, =0x15036\n"  //@ Load from Memory
  //               "LDR     R0, =aShutter_c\n" //@ Load from Memory
                 "LDR     R0, =0xFF93B554\n" //@ Load from Memory
                 "ADD     R1, R1, #1\n"      //@ Rd = Op1 + Op2
                 "LDREQSH R4, [R3]\n"        //@ Load from Memory
                 "LDRNE   R3, =0x15036\n"  //@ Load from Memory
                 "CMN     R4, #0xC00\n"      //@ Set cond. codes on Op1 + Op2
                 "STRH    R4, [R3]\n"        //@ Store to Memory
                 "BNE     loc_FF93BD90\n"    //@ Branch

//                 "BL      DebugAssert\n"     //@ Branch with Link
                 "BL      sub_FFB2F4F0\n"     //@ Branch with Link


     "loc_FF93BD90:\n"                           //@ CODE XREF: sub_FF93BD38+50j
                 "MOV     R0, R4\n"          //@ Rd = Op2
//                 "BL      sub_FF93CE88\n"    //@ Branch with Link
                 "BL      apex2us\n"    //@ Branch with Link => yet another function we need to make our way through to get to our own version

                 "MOV     R4, R0\n"          //@ Rd = Op2
//                 "BL      nullsub_118\n"     //@ Branch with Link
                 "BL      sub_FF9C2BB0\n"     //@ Branch with Link

                 "MOV     R0, R4\n"          //@ Rd = Op2
                 "BL      sub_FF9DE41C\n"    //@ Branch with Link

                 "MOV     R1, #0x174\n"      //@ Rd = Op2
                 "TST     R0, #1\n"          //@ Set cond. codes on Op1 & Op2
                 "ADD     R1, R1, #2\n"      //@ Rd = Op1 + Op2
//                 "LDR     R0, =aShutter_c\n" //@ Load from Memory
                 "LDR     R0, =0xFF93B554\n" //@ Load from Memory
                 "LDMEQFD SP!, {R4,PC}\n"    //@ Load Block from Memory
                 "LDMFD   SP!, {R4,LR}\n"    //@ Load Block from Memory
    //             "B       DebugAssert\n"     //@ Branch
                 "B       sub_FFB2F4F0\n"     //@ Branch with Link
	);
}
