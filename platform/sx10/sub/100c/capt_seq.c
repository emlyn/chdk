#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x9B40;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) capt_seq_task() {
 asm volatile (
                 "STMFD   SP!, {R3-R9,LR}\n"
                 "LDR     R6, =0x5584\n"
                 "LDR     R4, =0x1BE24\n"
                 "MOV     R9, #1\n"
                 "MOV     R7, #0\n"
 "loc_FF868BA4:\n" //done
                 "LDR     R0, [R6,#0x14]\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, SP\n"
                 "BL      sub_FF8274FC\n" //checked
                 "TST     R0, #1\n"
                 "BEQ     loc_FF868BD0\n" //done
                 "LDR     R1, =0x539\n"
                 "LDR     R0, =0xFF868334\n" //done
                 "BL      sub_FF81B1CC\n"
                 "BL      sub_FF81B184\n"
                 "LDMFD   SP!, {R3-R9,PC}\n"
 "loc_FF868BD0:\n" //done
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x24\n"
                 "ADDLS   PC, PC, R1,LSL#2\n"
                 "B       loc_FF868EAC\n" //done
 

"loc_FF868BE4:\n"
		"B	loc_FF868C78\n"
"loc_FF868BE8:\n"
		"B	loc_FF868CE4\n"
"loc_FF868BEC:\n"
		"B	loc_FF868CEC\n"
"loc_FF868BF0:\n"
		"B	loc_FF868D10\n"
"loc_FF868BF4:\n"
		"B	loc_FF868D04\n"
"loc_FF868BF8:\n"
		"B	loc_FF868D18\n"
"loc_FF868BFC:\n"
		"B	loc_FF868D20\n"
"loc_FF868C00:\n"
		"B	loc_FF868D28\n"
"loc_FF868C04:\n"
		"B	loc_FF868D80\n"
"loc_FF868C08:\n"
		"B	loc_FF868DA8\n"
"loc_FF868C0C:\n"
		"B	loc_FF868D8C\n"
"loc_FF868C10:\n"
		"B	loc_FF868D98\n"
"loc_FF868C14:\n"
		"B	loc_FF868DA0\n"
"loc_FF868C18:\n"
		"B	loc_FF868DB0\n"
"loc_FF868C1C:\n"
		"B	loc_FF868DB8\n"
"loc_FF868C20:\n"
		"B	loc_FF868DC0\n"
"loc_FF868C24:\n"
		"B	loc_FF868DC8\n"
"loc_FF868C28:\n"
		"B	loc_FF868DD0\n"
"loc_FF868C2C:\n"
		"B	loc_FF868DD8\n"
"loc_FF868C30:\n"
		"B	loc_FF868DE0\n"
"loc_FF868C34:\n"
		"B	loc_FF868DE8\n"
"loc_FF868C38:\n"
		"B	loc_FF868DF0\n"
"loc_FF868C3C:\n"
		"B	loc_FF868DF8\n"
"loc_FF868C40:\n"
		"B	loc_FF868E00\n"
"loc_FF868C44:\n"
		"B	loc_FF868E08\n"
"loc_FF868C48:\n"
		"B	loc_FF868E14\n"
"loc_FF868C4C:\n"
		"B	loc_FF868E1C\n"
"loc_FF868C50:\n"
		"B	loc_FF868E28\n"
"loc_FF868C54:\n"
		"B	loc_FF868E30\n"
"loc_FF868C58:\n"
		"B	loc_FF868E60\n"
"loc_FF868C5C:\n"
		"B	loc_FF868E68\n"
"loc_FF868C60:\n"
		"B	loc_FF868E70\n"
"loc_FF868C64:\n"
		"B	loc_FF868E78\n"
"loc_FF868C68:\n"
		"B	loc_FF868E80\n"
"loc_FF868C6C:\n"
		"B	loc_FF868E88\n"
"loc_FF868C70:\n"
		"B	loc_FF868E94\n"
"loc_FF868C74:\n"
		"B	loc_FF868EB8\n"
  "loc_FF868C78:\n" //done
                 "BL      sub_FF8694B8\n" //done
                 "BL      shooting_expo_param_override\n"  // +
                 "BL      sub_FF866548\n" //done

 //  this code added to avoid some incorrect behavior if overrides are used.
 //  but it can cause some unexpected side effects. In this case, remove this code!

                 "MOV     R0, #0\n"
                 "STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press
 	
 //  end of my code

                 "LDR     R0, [R4,#0x24]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF868EB8\n" //done
                 "BL      sub_FF868004\n"  //done
                 "MOV     R5, R0\n"
                 "LDR     R0, [R4,#0x24]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF868CC0\n" //done
                 "MOV     R0, #0xC\n"
                 "BL      sub_FF86D148\n" //done
                 "TST     R0, #1\n"
                 "STRNE   R9, [R6,#4]\n"
                 "LDRNE   R0, [R5,#8]\n"
                 "ORRNE   R0, R0, #0x40000000\n"
                 "STRNE   R0, [R5,#8]\n"
                 "BNE     loc_FF868EB8\n" //done
 "loc_FF868CC0:\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF94C27C\n" //done -0x10
                 "MOV     R0, R5\n"
                 "BL      sub_FF8683E4\n" //done
                 "MOV     R0, R5\n"
                 "BL      sub_FF94C954_my\n"             // -----------> 
                 "BL      capt_seq_hook_raw_here\n"      // +
                 "TST     R0, #1\n"
                 "STRNE   R9, [R6,#4]\n"
                 "B       loc_FF868EB8\n" //done
 "loc_FF868CE4:\n" //done
                 "BL      sub_FF86845C_my\n"             // -----------> 
                 "B       loc_FF868D08\n" //done
 "loc_FF868CEC:\n" //done
                 "MOV     R0, #1\n"
                 "BL      sub_FF86972C\n" //done
                 "LDR     R0, [R4,#0xC]\n"
                 "CMP     R0, #0\n"
                 "BLNE    sub_FF86A230\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868D04:\n" //done
                 "BL      sub_FF869184\n" //done
 "loc_FF868D08:\n" //done
                 "STR     R7, [R4,#0x24]\n"
                 "B       loc_FF868EB8\n" //done
 "loc_FF868D10:\n" //done
                 "BL      sub_FF869498\n" //done
                 "B       loc_FF868D08\n" //done
 "loc_FF868D18:\n" //done
                 "BL      sub_FF8694A0\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868D20:\n" //done
                 "BL      sub_FF86961C\n" //done
                 "B       loc_FF868D84\n" //done
 "loc_FF868D28:\n" //done
                 "LDR     R5, [R0,#0xC]\n"
                 "BL      sub_FF8694A8\n" //done
                 "MOV     R0, R5\n"
                 "BL      sub_FF94B260\n" //done
                 "TST     R0, #1\n"
                 "MOV     R8, R0\n"
                 "BNE     loc_FF868D68\n" //done
                 "BL      sub_FF879860\n" //done
                 "STR     R0, [R5,#0x18]\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF94C810\n" //done
                 "MOV     R0, R5\n"
                 "BL      sub_FF94CC1C\n" //done
                 "MOV     R8, R0\n"
                 "LDR     R0, [R5,#0x18]\n"
                 "BL      sub_FF879A74\n" //done
 "loc_FF868D68:\n" //done
                 "BL      sub_FF869498\n" //done
                 "MOV     R2, R5\n"
                 "MOV     R1, #9\n"
                 "MOV     R0, R8\n"
                 "BL      sub_FF866AD4\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868D80:\n" //done
                 "BL      sub_FF8696AC\n" //done
 "loc_FF868D84:\n" //done
                 "BL      sub_FF866548\n" //done
                 "B       loc_FF868EB8\n"  //done
 "loc_FF868D8C:\n" //done
                 "LDR     R0, [R4,#0x54]\n"
                 "BL      sub_FF869D44\n" //done
                 "B       loc_FF868EB8\n"  //done
 "loc_FF868D98:\n" //done
                 "BL      sub_FF869FF0\n"  //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DA0:\n" //done
                 "BL      sub_FF86A080\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DA8:\n"
                 "BL      sub_FF869498\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DB0:\n" //done
                 "BL      sub_FF94B4A0\n" //done -0X10
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DB8:\n" //done
                 "BL      sub_FF94B6CC\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DC0:\n" //done
                 "BL      sub_FF94B760\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DC8:\n" //done
                 "BL      sub_FF94B888\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DD0:\n"	 //done
                 "BL      sub_FF94B93C\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DD8:\n" //done
                 "BL      sub_FF94BDCC\n"  //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DE0:\n" //done
                 "BL      sub_FF94BE24\n"  //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DE8:\n"  //done
                 "MOV     R0, #0\n"
                 "B       loc_FF868E0C\n"  //done
 "loc_FF868DF0:\n" //done
                 "BL      sub_FF94BFC0\n"  //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868DF8:\n"  //done
                 "BL      sub_FF94C050\n"  //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E00:\n" //done
                 "BL      sub_FF94C110\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E08:\n" //done
                 "MOV     R0, #1\n"
 "loc_FF868E0C:\n" //done
                 "BL      sub_FF94BE98\n"  //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E14:\n" //done
                 "BL      sub_FF869964\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E1C:\n" //done
                 "BL      sub_FF869A04\n" //done
                 "BL      sub_FF868FE0\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E28:\n" //done
                 "BL      sub_FF94BBF4\n"  //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E30:\n" //done
                 "MOV     R2, #2\n"
                 "ADD     R1, R4, #0x74\n"
                 "MOV     R0, #0x6F\n"
                 "BL      sub_FF8796D0\n"  //done
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x61C\n"
                 "LDRNE   R0, =0xFF868334\n" //done
                 "BLNE    sub_FF81B1CC\n"
                 "LDRH    R0, [R4,#0x74]\n"
                 "CMP     R0, #1\n"
                 "BLEQ    sub_FF94BBE8\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E60:\n" //done
                 "BL      sub_FF94BD20\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E68:\n" //done
                 "BL      sub_FF8682C4\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E70:\n" //done
                 "BL      sub_FF824960\n"
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E78:\n" //done
                 "BL      sub_FF86B888\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E80:\n" //done
                 "BL      sub_FF86B8F0\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E88:\n" //done
                 "BL      sub_FF86B94C\n" //done
                 "BL      sub_FF86B90C\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868E94:\n" //done
                 "MOV     R0, #1\n"
                 "BL      sub_FF94D420\n" //done
                 "LDRH    R0, [R4,#0xA0]\n"
                 "CMP     R0, #3\n"
                 "BLNE    sub_FF86BB08\n" //done
                 "B       loc_FF868EB8\n" //done
 "loc_FF868EAC:\n" //done
                 "LDR     R1, =0x65E\n"
                 "LDR     R0, =0xFF868334\n" //done
                 "BL      sub_FF81B1CC\n"
 "loc_FF868EB8:\n" //done
                 "LDR     R0, [SP]\n"
                 "LDR     R1, [R0,#4]\n"
                 "LDR     R0, [R6,#0x10]\n"
                 "BL      sub_FF8713FC\n" //done
                 "LDR     R5, [SP]\n"
                 "LDR     R0, [R5,#8]\n"
                 "CMP     R0, #0\n"
                 "LDREQ   R1, =0x11D\n"
                 "LDREQ   R0, =0xFF868334\n" //done
                 "BLEQ    sub_FF81B1CC\n"
                 "STR     R7, [R5,#8]\n"
                 "B       loc_FF868BA4\n" //done
 );
} 



void __attribute__((naked,noinline)) sub_FF86845C_my(){ // 
 asm volatile(
                 "STMFD   SP!, {R3-R9,LR}\n"
                 "LDR     R4, [R0,#0xC]\n"
                 "LDR     R5, =0x1BE24\n"
                 "LDR     R0, [R4,#8]\n"
                 "LDR     R6, =0x820A\n"
                 "ORR     R0, R0, #1\n"
                 "STR     R0, [R4,#8]\n"
                 "LDRH    R0, [R5]\n"
                 "LDR     R8, =0x5584\n"
                 "MOV     R7, #0\n"
                 "CMP     R0, R6\n"
                 "BEQ     loc_FF868500\n" //done
                 "LDRH    R0, [R5,#0xA6]\n"
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF868560\n" //done
                 "LDR     R0, [R4,#0xC]\n"
                 "CMP     R0, #1\n"
                 "BLS     loc_FF86850C\n" //done
                 "LDRH    R0, [R5,#0xA4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF868560\n"  //done
                 "LDRH    R0, [R5,#0xA0]\n"
                 "CMP     R0, #2\n"
                 "BNE     loc_FF868518\n" //done
                 "BL      sub_FF869AB4\n" //done
                 "LDRH    R0, [R5]\n"
                 "CMP     R0, R6\n"
                 "BEQ     loc_FF868500\n" //done
                 "LDRH    R0, [R5,#0xA6]\n"
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF868560\n" //done
                 "LDR     R0, [R4,#0xC]\n"
                 "CMP     R0, #1\n"
                 "BLS     loc_FF86850C\n" //done
                 "LDRH    R0, [R5,#0xA4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF868560\n" //done
                 "LDRH    R0, [R5,#0xA0]\n"
                 "CMP     R0, #2\n"
                 "BEQ     loc_FF868544\n" //done
                 "B       loc_FF868518\n" //done
 "loc_FF868500:\n" //done
                 "LDRH    R0, [R5,#0xA6]\n"
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF868560\n" //done
 "loc_FF86850C:\n" //done
                 "LDRH    R0, [R5,#0xA4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF868560\n" //done
 "loc_FF868518:\n" //done
                 "LDRH    R0, [R5,#0xA0]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF868560\n" //done
                 "LDRH    R0, [R5]\n"
                 "CMP     R0, R6\n"
                 "LDRNE   R0, [R4,#0xC]\n"
                 "CMPNE   R0, #1\n"
                 "BLS     loc_FF868560\n" //done
                 "LDR     R0, [R4,#0x10]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF868560\n" //done
 "loc_FF868544:\n" //done
                 "LDR     R3, =0x24D\n"
                 "LDR     R2, =0xEA60\n"
                 "STR     R3, [SP]\n"
                 "LDR     R0, [R8,#0x10]\n"
                 "LDR     R3, =0xFF868334\n" //done
                 "MOV     R1, #0x40000000\n"
                 "BL      sub_FF86D4CC\n" //done
 "loc_FF868560:\n"//done
                 "BL      sub_FF8682C4\n"//done
                 "LDR     R0, [R5,#0x24]\n"
                 "CMP     R0, #0\n"
                 "MOVEQ   R0, #2\n"
                 "BLEQ    sub_FF861AD4\n" //done
                 "BL      sub_FF8694A8\n" //done
                 "LDR     R0, [R5,#0x24]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF868618\n" //done
                 "MOV     R0, #0\n"
                 "BL      sub_FF94D420\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF94C27C\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF8698CC\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF94AE04\n" //done
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF8685D0\n" //done
                 "BL      sub_FF94D460\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF94AFC8\n" //done
                 "TST     R0, #1\n"
                 "MOVNE   R2, R4\n"
                 "LDMNEFD SP!, {R3-R9,LR}\n"
                 "MOVNE   R1, #1\n"
                 "BNE     sub_FF866AD4\n" //done
                 "B       loc_FF8685F4\n" //done
 "loc_FF8685D0:\n" //done
                 "LDR     R0, [R5,#0xC]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF8685E8\n" //done
                 "BL      sub_FF86A1B8\n" //done
                 "BL      sub_FF900290\n" //done
                 "BL      sub_FF86324C\n" //done
 "loc_FF8685E8:\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF94AEFC\n" //done
                 "BL      sub_FF94D460\n" //done
 "loc_FF8685F4:\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF8683E4\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF94C810\n" //done
                 "BL      sub_FF94D2B0\n" //done
                 "MOV     R0, R4\n"
                 "BL      sub_FF94C954_my\n" //done             //-----------> 
                 "MOV     R7, R0\n"
                 "BL      capt_seq_hook_raw_here\n"      // +
                 "B       loc_FF868624\n" //done
 "loc_FF868618:\n" //done
                 "LDR     R0, [R8,#4]\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R7, #0x1D\n"
 "loc_FF868624:\n" //done
                 "BL      sub_FF86B8F0\n" //done
                 "BL      sub_FF86B938\n" //done
                 "BL      sub_FF86B978\n" //done
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, R7\n"
                 "BL      sub_FF866AD4\n" //done
                 "BL      sub_FF94CBAC\n" //done
                 "CMP     R0, #0\n"
                 "LDRNE   R0, [R4,#8]\n"
                 "ORRNE   R0, R0, #0x2000\n"
                 "STRNE   R0, [R4,#8]\n"
                 "LDR     R0, [R4,#0x1C]\n"
                 "CMP     R0, #0\n"
                 "BLNE    sub_FF863264\n" //done
                 "LDRH    R0, [R5,#0xA6]\n"
                 "CMP     R0, #3\n"
                 "BEQ     loc_FF868688\n" //done
                 "LDRH    R0, [R5,#0xA4]\n"
                 "CMP     R0, #0\n"
                 "LDREQH  R0, [R5,#0xA0]\n"
                 "CMPEQ   R0, #2\n"
                 "MOVEQ   R0, R4\n"
                 "LDMEQFD SP!, {R3-R9,LR}\n"
                 "BEQ     sub_FF869B08\n" //done
 "loc_FF868688:\n" //done
                 "LDMFD   SP!, {R3-R9,PC}\n"
 );
}



void __attribute__((naked,noinline)) sub_FF94C954_my(){ // done
 asm volatile(
                 "STMFD   SP!, {R1-R7,LR}\n"
                 "MOV     R4, R0\n"
                 "BL      sub_FF94D590\n" //done
                 "MVN     R1, #0\n"
                 "BL      sub_FF871430\n" //done
                 "MOV     R2, #4\n"
                 "ADD     R1, SP, #4\n"
                 "MOV     R0, #0x8A\n"
                 "BL      sub_FF8796D0\n" //done
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x373\n"
                 "LDRNE   R0, =0xFF94C920\n" //done was 930 
                 "BLNE    sub_FF81B1CC\n"
                 "LDR     R7, =0x1BEF8\n"
                 "LDR     R6, =0x1BE24\n"
                 "LDRSH   R1, [R7,#0xE]\n"
                 "LDR     R0, [R6,#0x9C]\n"
                 "BL      sub_FF90B004\n" //done
                 "BL      sub_FF84E5E8\n" //done
                 "LDR     R3, =0x9B44\n"
                 "STRH    R0, [R4,#0x94]\n"
                 "STR     R3, [SP]\n"
                 "MOV     R1, R0\n"
                 "LDRH    R0, [R6,#0x70]\n"
                 "LDRSH   R2, [R7,#0xC]\n"
                 "SUB     R3, R3, #4\n"
                 "BL      sub_FF94DBB4\n" //done
                 "BL      wait_until_remote_button_is_released\n"
                 "BL      capt_seq_hook_set_nr\n"                     // +
                 "B       sub_FF94C9C0\n" //done                            // continue function in firmware
 );
}


/*************************************************************/
void __attribute__((naked,noinline)) exp_drv_task(){
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "SUB     SP, SP, #0x20\n"
                 "LDR     R8, =0xBB8\n"
                 "LDR     R7, =0x6EE4\n"
                 "LDR     R5, =0x210F0\n"
                 "MOV     R0, #0\n"
                 "ADD     R6, SP, #0x10\n"
                 "STR     R0, [SP,#0xC]\n"
 "loc_FF8AD7E4:\n" //done
                 "LDR     R0, [R7,#0x20]\n"
                 "MOV     R2, #0\n"
                 "ADD     R1, SP, #0x1C\n"
                 "BL      sub_FF8274FC\n"
                 "LDR     R0, [SP,#0xC]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF8AD82C\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R0, [R0]\n"
                 "CMP     R0, #0x13\n"
                 "CMPNE   R0, #0x14\n"
                 "CMPNE   R0, #0x15\n"
                 "BEQ     loc_FF8AD948\n" //done
                 "CMP     R0, #0x27\n"
                 "BEQ     loc_FF8AD920\n" //done
                 "ADD     R1, SP, #0xC\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF8AD738\n" //done
 "loc_FF8AD82C:\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x2C\n"
                 "BNE     loc_FF8AD85C\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "BL      sub_FF8AEA14\n" //done
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF8713FC\n" //done
                 "BL      sub_FF81B184\n"
                 "ADD     SP, SP, #0x20\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FF8AD85C:\n" //done
                 "CMP     R1, #0x2B\n"
                 "BNE     loc_FF8AD878\n" //done
                 "LDR     R2, [R0,#0x88]!\n"
                 "LDR     R1, [R0,#4]\n"
                 "MOV     R0, R1\n"
                 "BLX     R2\n"
                 "B       loc_FF8ADD68\n" //done
 "loc_FF8AD878:\n" //done
                 "CMP     R1, #0x25\n"
                 "BNE     loc_FF8AD8C8\n" //done
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R1, #0x80\n"
                 "BL      sub_FF871430\n" //done
                 "LDR     R0, =0xFF8AA1FC\n" //done
                 "MOV     R1, #0x80\n"
                 "BL      sub_FF93B050\n" //done
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R8\n"
                 "MOV     R1, #0x80\n"
                 "BL      sub_FF87133C\n" //done
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0xD36\n"
                 "BNE     loc_FF8AD90C\n" //done
 "loc_FF8AD8B4:\n" //done
                 "LDR     R1, [SP,#0x1C]\n"
                 "LDR     R0, [R1,#0x8C]\n"
                 "LDR     R1, [R1,#0x88]\n"
                 "BLX     R1\n"
                 "B       loc_FF8ADD68\n" //done
 "loc_FF8AD8C8:\n" //done
                 "CMP     R1, #0x26\n"
                 "BNE     loc_FF8AD918\n" //done
                 "ADD     R1, SP, #0xC\n"
                 "BL      sub_FF8AD738\n" //done
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R1, #0x100\n"
                 "BL      sub_FF871430\n" //done
                 "LDR     R0, =0xFF8AA20C\n" //done
                 "MOV     R1, #0x100\n"
                 "BL      sub_FF93B9DC\n" //done
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R8\n"
                 "MOV     R1, #0x100\n"
                 "BL      sub_FF87133C\n" //done
                 "TST     R0, #1\n"
                 "BEQ     loc_FF8AD8B4\n" //done
                 "MOV     R1, #0xD40\n"
 "loc_FF8AD90C:\n" //done
                 "LDR     R0, =0xFF8AA904\n" //done
                 "BL      sub_FF81B1CC\n"
                 "B       loc_FF8AD8B4\n" //done
 "loc_FF8AD918:\n" //done
                 "CMP     R1, #0x27\n"
                 "BNE     loc_FF8AD930\n" //done
 "loc_FF8AD920:\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "ADD     R1, SP, #0xC\n"
                 "BL      sub_FF8AD738\n" //done
                 "B       loc_FF8AD8B4\n" //done
 "loc_FF8AD930:\n" //done
                 "CMP     R1, #0x2A\n"
                 "BNE     loc_FF8AD948\n" //done
                 "BL      sub_FF89D334\n" //done
                 "BL      sub_FF89DFC0\n" //done
                 "BL      sub_FF89DAF8\n" //done
                 "B       loc_FF8AD8B4\n" //done
 "loc_FF8AD948:\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "MOV     R4, #1\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x11\n"
                 "CMPNE   R1, #0x12\n"
                 "BNE     loc_FF8AD9B8\n" //done
                 "LDR     R1, [R0,#0x7C]\n"
                 "ADD     R1, R1, R1,LSL#1\n"
                 "ADD     R1, R0, R1,LSL#2\n"
                 "SUB     R1, R1, #8\n"
                 "LDMIA   R1, {R2-R4}\n"
                 "STMIA   R6, {R2-R4}\n"
                 "BL      sub_FF8AC2AC\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R3, [R0,#0x88]\n"
                 "LDR     R2, [R0,#0x8C]\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R3\n"
                 "LDR     R0, [SP,#0x1C]\n"
                 "BL      sub_FF8AEDC8\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R3, [R0,#0x90]\n"
                 "LDR     R2, [R0,#0x94]\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R3\n"
                 "B       loc_FF8ADCA8\n" //done
 "loc_FF8AD9B8:\n" //done
                 "CMP     R1, #0x13\n"
                 "CMPNE   R1, #0x14\n"
                 "CMPNE   R1, #0x15\n"
                 "BNE     loc_FF8ADA6C\n" //done
                 "ADD     R3, SP, #0xC\n"
                 "MOV     R2, SP\n"
                 "ADD     R1, SP, #0x10\n"
                 "BL      sub_FF8AC4F4\n" //done
                 "CMP     R0, #1\n"
                 "MOV     R4, R0\n"
                 "CMPNE   R4, #5\n"
                 "BNE     loc_FF8ADA08\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "MOV     R2, R4\n"
                 "LDR     R1, [R0,#0x7C]!\n"
                 "LDR     R12, [R0,#0xC]!\n"
                 "LDR     R3, [R0,#4]\n"
                 "MOV     R0, SP\n"
                 "BLX     R12\n"
                 "B       loc_FF8ADA40\n" //done
 "loc_FF8ADA08:\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "CMP     R4, #2\n"
                 "LDR     R3, [R0,#0x8C]\n"
                 "CMPNE   R4, #6\n"
                 "BNE     loc_FF8ADA54\n" //done
                 "LDR     R12, [R0,#0x88]\n"
                 "MOV     R0, SP\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #1\n"
                 "BLX     R12\n"
                 "LDR     R0, [SP,#0x1C]\n"
                 "MOV     R2, SP\n"
                 "ADD     R1, SP, #0x10\n"
                 "BL      sub_FF8AD484\n" //done
 "loc_FF8ADA40:\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R2, [SP,#0xC]\n"
                 "MOV     R1, R4\n"
                 "BL      sub_FF8AD6D8\n" //done
                 "B       loc_FF8ADCA8\n" //done
 "loc_FF8ADA54:\n"	 //done
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R12, [R0,#0x88]\n"
                 "ADD     R0, R0, #4\n"
                 "MOV     R2, R4\n"
                 "BLX     R12\n"
                 "B       loc_FF8ADCA8\n" //done
 "loc_FF8ADA6C:\n" //done
                 "CMP     R1, #0x21\n"
                 "CMPNE   R1, #0x22\n"
                 "BNE     loc_FF8ADAB8\n" //done
                 "LDR     R1, [R0,#0x7C]\n"
                 "ADD     R1, R1, R1,LSL#1\n"
                 "ADD     R1, R0, R1,LSL#2\n"
                 "SUB     R1, R1, #8\n"
                 "LDMIA   R1, {R2-R4}\n"
                 "STMIA   R6, {R2-R4}\n"
                 "BL      sub_FF8AB82C\n" //done
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R3, [R0,#0x88]\n"
                 "LDR     R2, [R0,#0x8C]\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R3\n"
                 "LDR     R0, [SP,#0x1C]\n"
                 "BL      sub_FF8ABB28\n" //done
                 "B       loc_FF8ADCA8\n" //done
 "loc_FF8ADAB8:\n" //done
                 "ADD     R1, R0, #4\n"
                 "LDMIA   R1, {R2,R3,R12}\n"
                 "STMIA   R6, {R2,R3,R12}\n"
                 "LDR     R1, [R0]\n"
                 "CMP     R1, #0x24\n"
                 "ADDLS   PC, PC, R1,LSL#2\n"
                 "B       loc_FF8ADC88\n" //done
 "loc_FF8ADAD4:\n" //done
                 "B       loc_FF8ADB68\n" //done

"loc_FF8ADAD8:\n"
		"B	loc_FF8ADB68\n"
"loc_FF8ADADC:\n"
		"B	loc_FF8ADB70\n"
"loc_FF8ADAE0:\n"
		"B	loc_FF8ADB78\n"
"loc_FF8ADAE4:\n"
		"B	loc_FF8ADB78\n"
"loc_FF8ADAE8:\n"
		"B	loc_FF8ADB78\n"
"loc_FF8ADAEC:\n"
		"B	loc_FF8ADB68\n"
"loc_FF8ADAF0:\n"
		"B	loc_FF8ADB70\n"
"loc_FF8ADAF4:\n"
		"B	loc_FF8ADB78\n"
"loc_FF8ADAF8:\n"
		"B	loc_FF8ADB78\n"
"loc_FF8ADAFC:\n"
		"B	loc_FF8ADB90\n"
"loc_FF8ADB00:\n"
		"B	loc_FF8ADB90\n"
"loc_FF8ADB04:\n"
		"B	loc_FF8ADC7C\n"
"loc_FF8ADB08:\n"
		"B	loc_FF8ADC84\n"
"loc_FF8ADB0C:\n"
		"B	loc_FF8ADC84\n"
"loc_FF8ADB10:\n"
		"B	loc_FF8ADC84\n"
"loc_FF8ADB14:\n"
		"B	loc_FF8ADC84\n"
"loc_FF8ADB18:\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB1C:\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB20:\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB24:\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB28:\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB2C:\n"
		"B	loc_FF8ADB80\n"
"loc_FF8ADB30:\n"
		"B	loc_FF8ADB88\n"
"loc_FF8ADB34:\n"
		"B	loc_FF8ADB88\n"
"loc_FF8ADB38:\n"
		"B	loc_FF8ADB9C\n"
"loc_FF8ADB3C:\n"
		"B	loc_FF8ADB9C\n"
"loc_FF8ADB40:\n"
		"B	loc_FF8ADBA4\n"
"loc_FF8ADB44:\n"
		"B	loc_FF8ADBD4\n"
"loc_FF8ADB48:\n"
		"B	loc_FF8ADC04\n"
"loc_FF8ADB4C:\n"
		"B	loc_FF8ADC34\n"
"loc_FF8ADB50:\n"
		"B	loc_FF8ADC64\n"
"loc_FF8ADB54:\n"
		"B	loc_FF8ADC64\n"
"loc_FF8ADB58:\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB5C:\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB60:\n"
		"B	loc_FF8ADC6C\n"
"loc_FF8ADB64:\n"
		"B	loc_FF8ADC74\n"
"loc_FF8ADB68:\n"
		"BL	sub_FF8AA6F0\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB70:\n" 
		"BL	sub_FF8AA978\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB78:\n"
		"BL	sub_FF8AAB7C\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB80:\n"
		"BL	sub_FF8AADE4\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB88:\n"
		"BL	sub_FF8AAFD8\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB90:\n"
		"BL	sub_FF8AB240_my\n" //new code
		"MOV	R4, #0\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADB9C:\n"
		"BL	sub_FF8AB37C\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADBA4:\n"
                 "LDRH    R1, [R0,#4]\n"
                 "STRH    R1, [SP,#0x10]\n"
                 "LDRH    R1, [R5,#2]\n"
                 "STRH    R1, [SP,#0x12]\n"
                 "LDRH    R1, [R5,#4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R5,#6]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R0,#0xC]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "BL      sub_FF8AEA88\n" //done
                 "B       loc_FF8ADC88\n" //done
"loc_FF8ADBD4:\n"
                 "LDRH    R1, [R0,#4]\n"
                 "STRH    R1, [SP,#0x10]\n"
                 "LDRH    R1, [R5,#2]\n"
                 "STRH    R1, [SP,#0x12]\n"
                 "LDRH    R1, [R5,#4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R5,#6]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R5,#8]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "BL      sub_FF8AEBE4\n"
                 "B       loc_FF8ADC88\n" //done
"loc_FF8ADC04:\n"
                "LDRH    R1, [R5]\n"
                 "STRH    R1, [SP,#0x10]\n"
                 "LDRH    R1, [R0,#6]\n"
                 "STRH    R1, [SP,#0x12]\n"
                 "LDRH    R1, [R5,#4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R5,#6]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R5,#8]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "BL      sub_FF8AEC90\n" //done
                 "B       loc_FF8ADC88\n" //done
"loc_FF8ADC34:\n"
                 "LDRH    R1, [R5]\n"
                 "STRH    R1, [SP,#0x10]\n"
                 "LDRH    R1, [R5,#2]\n"
                 "STRH    R1, [SP,#0x12]\n"
                 "LDRH    R1, [R5,#4]\n"
                 "STRH    R1, [SP,#0x14]\n"
                 "LDRH    R1, [R5,#6]\n"
                 "STRH    R1, [SP,#0x16]\n"
                 "LDRH    R1, [R0,#0xC]\n"
                 "STRH    R1, [SP,#0x18]\n"
                 "BL      sub_FF8AED30\n"
                 "B       loc_FF8ADC88\n" //done
"loc_FF8ADC64:\n"
		"BL	sub_FF8AB5F0\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADC6C:\n"
		"BL	sub_FF8ABC2C\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADC74:\n"
		"BL	sub_FF8ABE64\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADC7C:\n"
		"BL	sub_FF8ABFDC\n"
		"B	loc_FF8ADC88\n"
"loc_FF8ADC84:\n"
		"BL	sub_FF8AC174\n"

"loc_FF8ADC88:\n"
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "LDR     R3, [R0,#0x88]\n"
                 "LDR     R2, [R0,#0x8C]\n"
                 "ADD     R0, R0, #4\n"
                 "BLX     R3\n"
                 "CMP     R4, #1\n"
                 "BNE     loc_FF8ADCF0\n"

"loc_FF8ADCA8:\n"
                 "LDR     R0, [SP,#0x1C]\n"
                 "MOV     R2, #0xC\n"
                 "LDR     R1, [R0,#0x7C]\n"
                 "ADD     R1, R1, R1,LSL#1\n"
                 "ADD     R0, R0, R1,LSL#2\n"
                 "SUB     R4, R0, #8\n"
                 "LDR     R0, =0x210F0\n"
                 "ADD     R1, SP, #0x10\n"
                 "BL      sub_FFAFFFF4\n"
                 "LDR     R0, =0x210FC\n"
                 "MOV     R2, #0xC\n"
                 "ADD     R1, SP, #0x10\n"
                 "BL      sub_FFAFFFF4\n"
                 "LDR     R0, =0x21108\n"
                 "MOV     R2, #0xC\n"
                 "MOV     R1, R4\n"
                 "BL      sub_FFAFFFF4\n"
                 "B       loc_FF8ADD68\n"

"loc_FF8ADCF0:\n"
                 "LDR     R0, [SP,#0x1C]\n"
                 "LDR     R0, [R0]\n"
                 "CMP     R0, #0xB\n"
                 "BNE     loc_FF8ADD38\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "MOV     R3, #1\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF8AA4F8\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "MOV     R3, #1\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, #0\n"
                 "B       loc_FF8ADD64\n"

"loc_FF8ADD38:\n"
                 "MOV     R3, #1\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, #1\n"
                 "STR     R3, [SP]\n"
                 "BL      sub_FF8AA4F8\n"
                 "MOV     R3, #1\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #1\n"
                 "MOV     R0, #1\n"
                 "STR     R3, [SP]\n"

"loc_FF8ADD64:\n"
		"BL	sub_FF8AA638\n"

"loc_FF8ADD68:\n"
	         "LDR   R0, [SP,#0x1C]\n" //LDR	R0, [SP,#0x38+var_1C]
			 "BL	sub_FF8AEA14\n"
			 "B		loc_FF8AD7E4\n" 
	 );
}

void __attribute__((naked,noinline)) sub_FF8AB240_my(){ // 
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "LDR     R7, =0x6EE4\n"
                 "MOV     R4, R0\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R1, #0x3E\n"
                 "BL      sub_FF871430\n" //done
                 "LDRSH   R0, [R4,#4]\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF8AA280\n" //done
                 "MOV     R6, R0\n"
                 "LDRSH   R0, [R4,#6]\n"
                 "BL      sub_FF8AA398\n" //done
                 "LDRSH   R0, [R4,#8]\n"
                 "BL      sub_FF8AA3F0\n" //done
                 "LDRSH   R0, [R4,#0xA]\n"
                 "BL      sub_FF8AA448\n" //done
                 "LDRSH   R0, [R4,#0xC]\n"
                 "BL      sub_FF8AA4A0\n" //done
                 "MOV     R5, R0\n"
                 "LDR     R0, [R4]\n"
                 "LDR     R8, =0x21108\n"
                 "CMP     R0, #0xB\n"
                 "MOVEQ   R6, #0\n"
                 "MOVEQ   R5, #0\n"
                 "BEQ     loc_FF8AB2D0\n" //done
                 "CMP     R6, #1\n"
                 "BNE     loc_FF8AB2D0\n" //done
                 "LDRSH   R0, [R4,#4]\n"
                 "LDR     R1, =0xFF8AA1EC\n" //done
                 "MOV     R2, #2\n"
                 "BL      sub_FF93B398\n" //done
                 "STRH    R0, [R4,#4]\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R7,#0x28]\n"
                 "B       loc_FF8AB2D8\n" //done
 "loc_FF8AB2D0:\n" //done
                 "LDRH    R0, [R8]\n"
                 "STRH    R0, [R4,#4]\n"
 "loc_FF8AB2D8:\n" //done
                 "CMP     R5, #1\n"
                 "LDRNEH  R0, [R8,#8]\n"
                 "BNE     loc_FF8AB2F4\n" //done
                 "LDRSH   R0, [R4,#0xC]\n"
                 "LDR     R1, =0xFF8AA270\n" //done
                 "MOV     R2, #0x20\n"
                 "BL      sub_FF8AEA44\n" //done
 "loc_FF8AB2F4:\n" //done
                 "STRH    R0, [R4,#0xC]\n"
                 "LDRSH   R0, [R4,#6]\n"
                 "BL      sub_FF89D0A4_my\n"//done   //------------>
                 "LDRSH   R0, [R4,#8]\n"
                 "MOV     R1, #1\n"
                 "BL      sub_FF89D7F0\n" //done
                 "MOV     R1, #0\n"
                 "ADD     R0, R4, #8\n"
                 "BL      sub_FF89D878\n" //done
                 "LDRSH   R0, [R4,#0xE]\n"
                 "BL      sub_FF8A5F0C\n" //done
                 "LDR     R4, =0xBB8\n"
                 "CMP     R6, #1\n"
                 "BNE     loc_FF8AB34C\n" //done
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #2\n"
                 "BL      sub_FF87133C\n" //done	
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x54D\n"
                 "LDRNE   R0, =0xFF8AA904\n" //done
                 "BLNE    sub_FF81B1CC\n"
 "loc_FF8AB34C:\n" //done
                 "CMP     R5, #1\n"
                 "LDMNEFD SP!, {R4-R8,PC}\n"
                 "LDR     R0, [R7,#0x1C]\n"
                 "MOV     R2, R4\n"
                 "MOV     R1, #0x20\n"
                 "BL      sub_FF87133C\n" //done
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x552\n"
                 "LDRNE   R0, =0xFF8AA904\n" //done
                 "LDMNEFD SP!, {R4-R8,LR}\n"
                 "BNE     sub_FF81B1CC\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF89D0A4_my(){ // 
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "LDR     R5, =0x6C14\n"
                 "MOV     R4, R0\n"
                 "LDR     R0, [R5,#4]\n"
                 "CMP     R0, #1\n"
                 "MOVNE   R1, #0x140\n"
                 "LDRNE   R0, =0xFF89CEA8\n" //checked
                 "BLNE    sub_FF81B1CC\n" //checked
                 "CMN     R4, #0xC00\n"
                 "LDREQSH R4, [R5,#2]\n"
                 "CMN     R4, #0xC00\n"
                 "LDREQ   R1, =0x146\n"
                 "LDREQ   R0, =0xFF89CEA8\n" //checked
                 "STRH    R4, [R5,#2]\n"
                 "BLEQ    sub_FF81B1CC\n" //checked
                 "MOV     R0, R4\n"
           //    "BL      sub_FF9E0118\n"  // -
                 "BL      apex2us\n"  // +
                 "MOV     R4, R0\n"
           //    "BL      nullsub_228\n"
                 "MOV     R0, R4\n"
                 "BL      sub_FF8D6278\n" //checked
                 "TST     R0, #1\n"
                 "LDRNE   R1, =0x14B\n"
                 "LDMNEFD SP!, {R4-R6,LR}\n"
                 "LDRNE   R0, =0xFF89CEA8\n"
                 "BNE     sub_FF81B1CC\n" //checked
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}
