#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0xCDA0;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FFB01DBC_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFB0282C\n"
//              "MOVL    R1, 0xFFFFFFFF\n"
                "MVN     R1, #0\n"
                "BL      sub_FFB12F9C\n" //ClearEventFlag
                "MOV     R0, #0x8A\n"
                "ADD     R1, SP, #4\n"
                "MOV     R2, #4\n"
                "BL      sub_FF81BC98\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFB01DFC\n"
                "MOV     R1, #0x1D0\n"
                "LDR     R0, =0xFFB01C40\n" //aSscaptureseq_c
                "ADD     R1, R1, #2\n"
                "BL      sub_FFB20628\n" //DebugAssert
"loc_FFB01DFC:\n"                           
                "LDR     R3, =0xBDA80\n"
                "LDR     R2, =0xBDB40\n"
                "LDR     R0, [R3,#0x7C]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FFA3957C\n"
                "MOV     R0, R4\n"
                "BL      sub_FFB01BC4\n"
                "BL      wait_until_remote_button_is_released\n"
                "BL      capt_seq_hook_set_nr\n" // +
                "LDR     R3, =0xCDA4\n"
                "LDR     R0, [R3]\n"

                "B       sub_FFB01E20\n"  // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FFAFEBE4_my(long p)
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
                "BNE     loc_FFAFEC38\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFB09134\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFAFEC38\n"
                "LDR     R3, [R5,#8]\n"
                "MOV     R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R5,#8]\n"
"loc_FFAFEC28:\n"                           
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFAFD38C\n"
 "loc_FFAFEC38:\n"                           
                "LDR     R4, =0xBDA80\n"
                "BL      sub_FFAFF6DC\n" //Set_CMD25Write_61
                "LDR     R3, [R4,#0x24]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FFAFEC80\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB008C0\n"
                "TST     R0, #1\n"
                "BNE     loc_FFAFEC28\n"
                "BL      sub_FF8261B8\n"
                "BL      sub_FF81BE94\n"
                "STR     R0, [R5,#0x14]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB01CA4\n"
                "BL      sub_FFB02698\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB01DBC_my\n"  //---------->
                "BL      capt_seq_hook_raw_here\n"  // +
                "B       loc_FFAFEC94\n"
"loc_FFAFEC80:\n"
                "LDR     R3, =0xCD8C\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
"loc_FFAFEC94:\n"
                "MOV     R1, #1\n"
                "MOV     R2, R5\n"
                "BL      sub_FFAFD38C\n"
                "BL      sub_FFB02138\n"
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
                "B       loc_FFAFF21C\n"
"loc_FFAFF0A0:\n"                           
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFAFF1F0\n"
                ".long loc_FFAFF110\n"
                ".long loc_FFAFF130\n"
                ".long loc_FFAFF144\n"
                ".long loc_FFAFF158\n"
                ".long loc_FFAFF150\n"
                ".long loc_FFAFF160\n"
                ".long loc_FFAFF168\n"
                ".long loc_FFAFF174\n"
                ".long loc_FFAFF17C\n"
                ".long loc_FFAFF188\n"
                ".long loc_FFAFF190\n"
                ".long loc_FFAFF198\n"
                ".long loc_FFAFF1A0\n"
                ".long loc_FFAFF1A8\n"
                ".long loc_FFAFF1B0\n"
                ".long loc_FFAFF1BC\n"
                ".long loc_FFAFF1C4\n"
                ".long loc_FFAFF1CC\n"
                ".long loc_FFAFF1D4\n"
                ".long loc_FFAFF1E0\n"
                ".long loc_FFAFF1E8\n"
                ".long loc_FFAFF204\n"
"loc_FFAFF110:\n"                           
                                        
                "BL      sub_FFAFF704\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FFAFCE14\n"
                "LDR     R3, =0xBDA80\n"
                "LDR     R2, [R3,#0x24]\n"
                "CMP     R2, #0\n"
                "BEQ     loc_FFAFF200\n"
                "BL      sub_FFAFECC0\n"
                "B       loc_FFAFF200\n"
"loc_FFAFF130:\n"                           
                                        
                "BL      sub_FFAFEBE4_my\n"  //--------->

"loc_FFAFF134:\n"                           
                "LDR     R2, =0xBDA80\n"                       
                "MOV     R3, #0\n"
                "STR     R3, [R2,#0x24]\n"
                "B       loc_FFAFF200\n"
"loc_FFAFF144:\n"                           
                "MOV     R0, #1\n"                        
                "BL      sub_FFAFF924\n" //jumptable case 2
                "B       loc_FFAFF200\n"
"loc_FFAFF150:\n"                           
                "BL      sub_FFAFF304\n" //jumptable case 4
                "B       loc_FFAFF134\n"
"loc_FFAFF158:\n"                           
                "BL      sub_FFAFF6BC\n" //BackLightDrv_LcdBackLightOff_15
                "B       loc_FFAFF134\n"
"loc_FFAFF160:\n"                           
                "BL      sub_FFAFF6CC\n" //jumptable case 5
                "B       loc_FFAFF200\n"
"loc_FFAFF168:\n"                           
                "BL      sub_FFAFF81C\n" //jumptable case 6                        
                "BL      sub_FFAFCE14\n"
                "B       loc_FFAFF200\n"
"loc_FFAFF174:\n"                           
                "BL      sub_FFAFED9C\n" //jumptable case 7
                "B       loc_FFAFF200\n"
"loc_FFAFF17C:\n"                           
                "BL      sub_FFAFF88C\n" //jumptable case 8                        
                "BL      sub_FFAFCE14\n"
                "B       loc_FFAFF200\n"
"loc_FFAFF188:\n"                           
                "BL      sub_FFAFF6BC\n" //BackLightDrv_LcdBackLightOff_15
                "B       loc_FFAFF200\n"
"loc_FFAFF190:\n"                           
                "BL      sub_FFB00FF4\n" //jumptable case 10
                "B       loc_FFAFF200\n"
"loc_FFAFF198:\n"                           
                "BL      sub_FFB011C8\n" //jumptable case 11
                "B       loc_FFAFF200\n"
"loc_FFAFF1A0:\n"                           
                "BL      sub_FFB0125C\n" //jumptable case 12
                "B       loc_FFAFF200\n"
"loc_FFAFF1A8:\n"                           
                "BL      sub_FFB01358\n" //jumptable case 13
                "B       loc_FFAFF200\n"
"loc_FFAFF1B0:\n"                           
                "MOV     R0, #0\n"                        
                "BL      sub_FFB015C4\n" //jumptable case 14
                "B       loc_FFAFF200\n"
"loc_FFAFF1BC:\n"                           
                "BL      sub_FFB01798\n" //jumptable case 15
                "B       loc_FFAFF200\n"
"loc_FFAFF1C4:\n"                           
                "BL      sub_FFB01834\n" //jumptable case 16
                "B       loc_FFAFF200\n"
"loc_FFAFF1CC:\n"                           
                "BL      sub_FFB018F4\n" //jumptable case 17
                "B       loc_FFAFF200\n"
"loc_FFAFF1D4:\n"                           
                "BL      sub_FFAFFA78\n" //jumptable case 18                        
                "BL      sub_FFAFEB08\n"
                "B       loc_FFAFF200\n"
"loc_FFAFF1E0:\n"                           
                "BL      sub_FFB01498\n" //jumptable case 19
                "B       loc_FFAFF200\n"
"loc_FFAFF1E8:\n" 
                "BL      sub_FFB014F4\n" //jumptable case 20
                "B       loc_FFAFF200\n"
"loc_FFAFF1F0:\n"                         
                "MOV     R1, #0x4C0\n"
                "LDR     R0, =0xFFAFE964\n" //aSsshoottask_c
                "ADD     R1, R1, #0xE\n"
                "BL      sub_FFB20628\n" //DebugAssert
"loc_FFAFF200:\n"                           
                "LDR     R2, [SP]\n"
"loc_FFAFF204:\n"                           
                "LDR     R3, =0x97348\n" //jumptable case 21
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFB12E00\n" //SetEventFlag
                "LDR     R0, [SP]\n"
                "BL      sub_FFAFE9E4\n"
"loc_FFAFF21C:\n"                           
                "LDR     R3, =0x9734C\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFB13518\n" //ReceiveMessageQueue
                "TST     R0, #1\n"
                "BEQ     loc_FFAFF0A0\n"
                "LDR     R0, =0xFFAFE964\n" //aSsshoottask_c
                "MOV     R1, #0x400\n"
                "BL      sub_FFB20628\n" //DebugAssert
                "BL      sub_FFB14ADC\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

