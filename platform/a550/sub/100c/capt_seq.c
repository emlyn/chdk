#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0xB918;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FFE72574_my(long p)
{
    asm volatile (
								"STMFD   SP!, {R4,LR}\n"
								"MOV     R4, R0\n"
								"SUB     SP, SP, #0xC\n"
								"BL      sub_FFE72F9C\n"
								"MVN     R1, #0\n"						//differnt from dump but synced wit a560
								"BL      sub_FFE82480\n"
								"MOV     R0, #0x8A\n"
								"ADD     R1, SP, #4\n"				//14-10
								"MOV     R2, #4\n"
								"BL      sub_FFC0B7C4\n"
								"TST     R0, #1\n"
								"BEQ     loc_FFE725B4\n"
								"MOV     R1, #0x1D0\n"
								"LDR     R0, =0xFFE723F8\n"
								"ADD     R1, R1, #2\n"
								"BL      sub_FFE8FB40\n"
	"loc_FFE725B4:\n"
								"LDR     R3, =0x9DDC0\n"
								"LDR     R2, =0x9DE80\n"
								"LDR     R0, [R3,#0x74]\n"
								"LDRSH   R1, [R2,#0xE]\n"
								"BL      sub_FFDD28E0\n"
								"MOV     R0, R4\n"
								"BL      sub_FFE7237C\n"
                                "BL      wait_until_remote_button_is_released\n"
								"BL      capt_seq_hook_set_nr\n" // +
								"LDR     R3, =0xB91C\n"
								"LDR     R0, [R3]\n"

                "B       sub_FFE725D8\n"  // ---> jump to end of function in ROM
    );
}

void __attribute__((naked,noinline)) sub_FFE6F5FC_my(long p)
{
    asm volatile (
								"STMFD   SP!, {R4,LR}\n"
								"LDR     R4, [R0,#0xC]\n"
								"LDR     R3, [R4,#8]\n"
								"ORR     R3, R3, #1\n"
								"STR     R3, [R4,#8]\n"
								"MOV     R0, #0xC\n"
								"BL      sub_FFE79254\n"
								"TST     R0, #1\n"
								"MOV     R0, #1\n"
								"MOV     R2, R4\n"
								"MOV     R1, R0\n"
								"BEQ     loc_FFE6F640\n"
								"LDR     R3, [R4,#8]\n"
								"ORR     R3, R3, #0x40000000\n"
								"STR     R3, [R4,#8]\n"
								"LDMFD   SP!, {R4,LR}\n"
								"B       sub_FFE6DEB0\n"
"loc_FFE6F640:\n"
								"BL      sub_FFE70098\n"
								"MOV     R0, R4\n"
								"BL      sub_FFE710CC\n"
								"TST     R0, #1\n"
								"MOV     R2, R4\n"
								"MOV     R1, #1\n"
								"BEQ     loc_FFE6F664\n"
								"LDMFD   SP!, {R4,LR}\n"
								"B       sub_FFE6DEB0\n"
"loc_FFE6F664:\n"
								"BL      sub_FFC15B10\n"
								"BL      sub_FFC0B9C0\n"
								"STR     R0, [R4,#0x14]\n"
								"MOV     R0, R4\n"
								"BL      sub_FFE7245C\n"
								"BL      sub_FFE72E08\n"
								"MOV     R0, R4\n"
								"BL      sub_FFE72574_my\n"			//------->
								"BL      capt_seq_hook_raw_here\n"  // +
								"MOV     R1, #1\n"
								"MOV     R2, R4\n"
								"BL      sub_FFE6DEB0\n"
								"BL      sub_FFE728A8\n"
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
								"B       loc_FFE6FB6C\n"
"loc_FFE6FA10:\n"
								"LDR     R2, [SP]\n"
								"LDR     R3, [R2]\n"
								"MOV     R0, R2\n"
								"CMP     R3, #0x15\n"
								"LDRLS   PC, [PC,R3,LSL#2]\n"
								"B       loc_FFE6FB40\n"
								".long loc_FFE6FA80\n"
								".long loc_FFE6FA8C\n"
								".long loc_FFE6FA94\n"
								".long loc_FFE6FAA8\n"
								".long loc_FFE6FAA0\n"
								".long loc_FFE6FAB0\n"
								".long loc_FFE6FAB8\n"
								".long loc_FFE6FAC4\n"
								".long loc_FFE6FACC\n"
								".long loc_FFE6FAD8\n"
								".long loc_FFE6FAE0\n"
								".long loc_FFE6FAE8\n"
								".long loc_FFE6FAF0\n"
								".long loc_FFE6FAF8\n"
								".long loc_FFE6FB00\n"
								".long loc_FFE6FB0C\n"
								".long loc_FFE6FB14\n"
								".long loc_FFE6FB1C\n"
								".long loc_FFE6FB24\n"
								".long loc_FFE6FB30\n"
								".long loc_FFE6FB38\n"
								".long loc_FFE6FB54\n"
"loc_FFE6FA80:\n"
								
								"BL      sub_FFE700AC\n"
								"BL      shooting_expo_param_override\n"   // +
								"BL      sub_FFE6D9A0\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FA8C:\n"
								
								"BL      sub_FFE6F5FC_my\n"  //--------->
								"B       loc_FFE6FB50\n"
"loc_FFE6FA94:\n"
								
								"MOV     R0, #1\n"
								"BL      sub_FFE70280\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FAA0:\n"                            
								
								"BL      sub_FFE6FC50\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FAA8:\n"
								
								"BL      sub_FFE70078\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FAB0:\n"
								
								"BL      sub_FFE70088\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FAB8:\n"
								
								"BL      sub_FFE70190\n"   
								"BL      sub_FFE6D9A0\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FAC4:\n"
								
								"BL      sub_FFE6F70C\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FACC:\n"
								
								"BL      sub_FFE701F4\n"   
								"BL      sub_FFE6D9A0\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FAD8:\n"
								
								"BL      sub_FFE70078\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FAE0:\n"
								
								"BL      sub_FFE717E0\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FAE8:\n"
								
								"BL      sub_FFE719AC\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FAF0:\n"
								
								"BL      sub_FFE71A40\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FAF8:\n"
								
								"BL      sub_FFE71B3C\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FB00:\n"
								
								"MOV     R0, #0\n"   
								"BL      sub_FFE71DA8\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FB0C:\n"
								
								"BL      sub_FFE71F60\n"  
								"B       loc_FFE6FB50\n"
"loc_FFE6FB14:\n"
								
								"BL      sub_FFE71FF4\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FB1C:\n"
								
								"BL      sub_FFE720B0\n"   
								"B       loc_FFE6FB50\n"
"loc_FFE6FB24:\n"

								"BL      sub_FFE703D4\n"   
								"BL      sub_FFE6F520\n"
								"B       loc_FFE6FB50\n"
"loc_FFE6FB30:\n"

								"BL      sub_FFE71C7C\n"  
								"B       loc_FFE6FB50\n"
"loc_FFE6FB38:\n"

								"BL      sub_FFE71CD8\n" 
								"B       loc_FFE6FB50\n"
"loc_FFE6FB40:\n"

								"MOV     R1, #0x4C0\n"   
								"LDR     R0, =0xFFE6F37C\n"
								"ADD     R1, R1, #0xE\n"
								"BL      sub_FFE8FB40\n"
"loc_FFE6FB50:\n"

								"LDR     R2, [SP]\n"
"loc_FFE6FB54:\n"

								"LDR     R3, =0x78070\n"
								"LDR     R1, [R2,#4]\n"
								"LDR     R0, [R3]\n"
								"BL      sub_FFE822E4\n"
								"LDR     R0, [SP]\n"
								"BL      sub_FFE6F3FC\n"
"loc_FFE6FB6C:\n"
								"LDR     R3, =0x78074\n"
								"MOV     R1, R4\n"
								"LDR     R0, [R3]\n"
								"MOV     R2, #0\n"
								"BL      sub_FFE829FC\n"
								"TST     R0, #1\n"
								"BEQ     loc_FFE6FA10\n"
								"LDR     R0, =0xFFE6F37C\n"
								"MOV     R1, #0x400\n"
								"BL      sub_FFE8FB40\n"
								"BL      sub_FFE83FC0\n"
								"ADD     SP, SP, #4\n"
								"LDMFD   SP!, {R4,PC}\n"

	);
}

