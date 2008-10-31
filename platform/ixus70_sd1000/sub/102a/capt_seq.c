#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0xCDA0;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FFB01EB0_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "MOV     R4, R0\n"
                "SUB     SP, SP, #0xC\n"
                "BL      sub_FFB02920\n"
//              "MOVL    R1, 0xFFFFFFFF\n"
                "MVN     R1, #0\n"
                "BL      sub_FFB13090\n" //ClearEventFlag
                "MOV     R0, #0x8A\n"
                "ADD     R1, SP, #4\n"
                "MOV     R2, #4\n"
                "BL      sub_FF81BC98\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFB01EF0\n"
                "MOV     R1, #0x1D0\n"
                "LDR     R0, =0xFFB01D34\n" //aSscaptureseq_c
                "ADD     R1, R1, #2\n"
                "BL      sub_FFB2071C\n" //DebugAssert
"loc_FFB01EF0:\n"                           
                "LDR     R3, =0xBDA80\n"
                "LDR     R2, =0xBDB40\n"
                "LDR     R0, [R3,#0x7C]\n"
                "LDRSH   R1, [R2,#0xE]\n"
                "BL      sub_FFA395F0\n"
                "MOV     R0, R4\n"
                "BL      sub_FFB01CB8\n"
                "BL      wait_until_remote_button_is_released\n"
                "BL      capt_seq_hook_set_nr\n" // +
                "LDR     R3, =0xCDA4\n"
                "LDR     R0, [R3]\n"

                "B       sub_FFB01F14\n"  // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FFAFECD8_my(long p)
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
                "BNE     loc_FFAFED2C\n"
                "MOV     R0, #0xC\n"
                "BL      sub_FFB09228\n"
                "TST     R0, #1\n"
                "BEQ     loc_FFAFED2C\n"
                "LDR     R3, [R5,#8]\n"
                "MOV     R0, #1\n"
                "ORR     R3, R3, #0x40000000\n"
                "STR     R3, [R5,#8]\n"
"loc_FFAFED1C:\n"                           
                "MOV     R2, R5\n"
                "MOV     R1, #1\n"
                "LDMFD   SP!, {R4,R5,LR}\n"
                "B       sub_FFAFD480\n"
 "loc_FFAFED2C:\n"                           
                "LDR     R4, =0xBDA80\n"
                "BL      sub_FFAFF7D0\n" //Set_CMD25Write_61
                "LDR     R3, [R4,#0x24]\n"
                "CMP     R3, #0\n"
                "BNE     loc_FFAFED74\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB009B4\n"
                "TST     R0, #1\n"
                "BNE     loc_FFAFED1C\n"
                "BL      sub_FF8261B8\n"
                "BL      sub_FF81BE94\n"
                "STR     R0, [R5,#0x14]\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB01D98\n"
                "BL      sub_FFB0278C\n"
                "MOV     R0, R5\n"
                "BL      sub_FFB01EB0_my\n"  //---------->
                "BL      capt_seq_hook_raw_here\n"  // +
                "B       loc_FFAFED88\n"
"loc_FFAFED74:\n"
                "LDR     R3, =0xCD8C\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "MOVNE   R0, #0x1D\n"
                "MOVEQ   R0, #0\n"
"loc_FFAFED88:\n"
                "MOV     R1, #1\n"
                "MOV     R2, R5\n"
                "BL      sub_FFAFD480\n"
                "BL      sub_FFB0222C\n"
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
                "B       loc_FFAFF310\n"
"loc_FFAFF194:\n"                           
                "LDR     R2, [SP]\n"
                "LDR     R3, [R2]\n"
                "MOV     R0, R2\n"
                "CMP     R3, #0x15\n"
                "LDRLS   PC, [PC,R3,LSL#2]\n"
                "B       loc_FFAFF2E4\n"
                ".long loc_FFAFF204\n"
                ".long loc_FFAFF224\n"
                ".long loc_FFAFF238\n"
                ".long loc_FFAFF24C\n"
                ".long loc_FFAFF244\n"
                ".long loc_FFAFF254\n"
                ".long loc_FFAFF25C\n"
                ".long loc_FFAFF268\n"
                ".long loc_FFAFF270\n"
                ".long loc_FFAFF27C\n"
                ".long loc_FFAFF284\n"
                ".long loc_FFAFF28C\n"
                ".long loc_FFAFF294\n"
                ".long loc_FFAFF29C\n"
                ".long loc_FFAFF2A4\n"
                ".long loc_FFAFF2B0\n"
                ".long loc_FFAFF2B8\n"
                ".long loc_FFAFF2C0\n"
                ".long loc_FFAFF2C8\n"
                ".long loc_FFAFF2D4\n"
                ".long loc_FFAFF2DC\n"
                ".long loc_FFAFF2F8\n"
"loc_FFAFF204:\n"                           
                                        
                "BL      sub_FFAFF7F8\n"
                "BL      shooting_expo_param_override\n"   // +
                "BL      sub_FFAFCF08\n"
                "LDR     R3, =0xBDA80\n"
                "LDR     R2, [R3,#0x24]\n"
                "CMP     R2, #0\n"
                "BEQ     loc_FFAFF2F4\n"
                "BL      sub_FFAFEDB4\n"
                "B       loc_FFAFF2F4\n"
"loc_FFAFF224:\n"                           
                                        
                "BL      sub_FFAFECD8_my\n"  //--------->

"loc_FFAFF228:\n"                           
                "LDR     R2, =0xBDA80\n"                       
                "MOV     R3, #0\n"
                "STR     R3, [R2,#0x24]\n"
                "B       loc_FFAFF2F4\n"
"loc_FFAFF238:\n"                           
                "MOV     R0, #1\n"                        
                "BL      sub_FFAFFA18\n" //jumptable case 2
                "B       loc_FFAFF2F4\n"
"loc_FFAFF244:\n"                           
                "BL      sub_FFAFF3F8\n" //jumptable case 4
                "B       loc_FFAFF228\n"
"loc_FFAFF24C:\n"                           
                "BL      sub_FFAFF7B0\n" //BackLightDrv_LcdBackLightOff_15
                "B       loc_FFAFF228\n"
"loc_FFAFF254:\n"                           
                "BL      sub_FFAFF7C0\n" //jumptable case 5
                "B       loc_FFAFF2F4\n"
"loc_FFAFF25C:\n"                           
                "BL      sub_FFAFF910\n" //jumptable case 6                        
                "BL      sub_FFAFCF08\n"
                "B       loc_FFAFF2F4\n"
"loc_FFAFF268:\n"                           
                "BL      sub_FFAFEE90\n" //jumptable case 7
                "B       loc_FFAFF2F4\n"
"loc_FFAFF270:\n"                           
                "BL      sub_FFAFF980\n" //jumptable case 8                        
                "BL      sub_FFAFCF08\n"
                "B       loc_FFAFF2F4\n"
"loc_FFAFF27C:\n"                           
                "BL      sub_FFAFF7B0\n" //BackLightDrv_LcdBackLightOff_15
                "B       loc_FFAFF2F4\n"
"loc_FFAFF284:\n"                           
                "BL      sub_FFB010E8\n" //jumptable case 10
                "B       loc_FFAFF2F4\n"
"loc_FFAFF28C:\n"                           
                "BL      sub_FFB012BC\n" //jumptable case 11
                "B       loc_FFAFF2F4\n"
"loc_FFAFF294:\n"                           
                "BL      sub_FFB01350\n" //jumptable case 12
                "B       loc_FFAFF2F4\n"
"loc_FFAFF29C:\n"                           
                "BL      sub_FFB0144C\n" //jumptable case 13
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2A4:\n"                           
                "MOV     R0, #0\n"                        
                "BL      sub_FFB016B8\n" //jumptable case 14
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2B0:\n"                           
                "BL      sub_FFB0188C\n" //jumptable case 15
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2B8:\n"                           
                "BL      sub_FFB01928\n" //jumptable case 16
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2C0:\n"                           
                "BL      sub_FFB019E8\n" //jumptable case 17
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2C8:\n"                           
                "BL      sub_FFAFFB6C\n" //jumptable case 18                        
                "BL      sub_FFAFEBFC\n"
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2D4:\n"                           
                "BL      sub_FFB0158C\n" //jumptable case 19
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2DC:\n" 
                "BL      sub_FFB015E8\n" //jumptable case 20
                "B       loc_FFAFF2F4\n"
"loc_FFAFF2E4:\n"                         
                "MOV     R1, #0x4C0\n"
                "LDR     R0, =0xFFAFEA58\n" //aSsshoottask_c
                "ADD     R1, R1, #0xE\n"
                "BL      sub_FFB2071C\n" //DebugAssert
"loc_FFAFF2F4:\n"                           
                "LDR     R2, [SP]\n"
"loc_FFAFF2F8:\n"                           
                "LDR     R3, =0x97348\n" //jumptable case 21
                "LDR     R1, [R2,#4]\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FFB12EF4\n" //SetEventFlag
                "LDR     R0, [SP]\n"
                "BL      sub_FFAFEAD8\n"
"loc_FFAFF310:\n"                           
                "LDR     R3, =0x9734C\n"
                "MOV     R1, R4\n"
                "LDR     R0, [R3]\n"
                "MOV     R2, #0\n"
                "BL      sub_FFB1360C\n" //ReceiveMessageQueue
                "TST     R0, #1\n"
                "BEQ     loc_FFAFF194\n"
                "LDR     R0, =0xFFAFEA58\n" //aSsshoottask_c
                "MOV     R1, #0x400\n"
                "BL      sub_FFB2071C\n" //DebugAssert
                "BL      sub_FFB14BD0\n"
                "ADD     SP, SP, #4\n"
                "LDMFD   SP!, {R4,PC}\n"
	);
}

