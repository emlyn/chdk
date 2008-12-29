#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0xAAFC;

#include "../../../generic/capt_seq.c"

void __attribute__((naked,noinline)) sub_FF931550_my(){ 
 asm volatile(
        	"STMFD	SP!, {R0-R10,LR}	\n"
		"MOV	R6, #0			\n"
		"MOV	R4, R0			\n"
		"BL	sub_FF932038		\n"
		"MVN    R1, #0                  \n"  //"MOVL	R1, 0xFFFFFFFF          \n"
		"BL	sub_FF828EE0		\n"
		"MOV	R2, #4			\n"
		"ADD	R1, SP,	#8       	\n"
		"MOV	R0, #0x8A		\n"
		"BL	sub_FF869470            \n"
		"TST	R0, #1			\n"
		"LDRNE	R1, =0x20A		\n"
		"LDRNE	R0, =0xFF931724        	\n"  //aSscaptureseq_c  ; "SsCaptureSeq.c"
		"BLNE	sub_FF81C090		\n"
		"LDR	R8, =0x1A140		\n"
		"LDR	R5, =0x1A08C		\n"
		"LDRSH	R1, [R8,#0xE]		\n"
		"LDR	R0, [R5,#0x7C]		\n"
		"BL	sub_FF8EF628		\n"
		"BL	sub_FF846AC0      	\n"
		"LDR	R2, =0xAB00		\n"
		"ADD	R3, R4,	#0x8C		\n"
		"STRH	R0, [R4,#0x88]		\n"
		//"STRD	R2, [SP]        	\n"
                "STR    R2, [SP]                \n"
                "STR    R3, [SP,#4]             \n"
		"MOV	R1, R0			\n"
		"LDRH	R0, [R5,#0x54]		\n"
		"LDRSH	R2, [R8,#0xC]		\n"
		"LDR	R3, =0xAAFC		\n"
		"BL	sub_FF932524		\n"
            "BL      wait_until_remote_button_is_released\n"
                 "BL     capt_seq_hook_set_nr    \n"
                "B      sub_FF9315C4            \n"
 );
}

void __attribute__((naked,noinline)) sub_FF85C054_my() //#fs
{
	asm volatile (
        	"STMFD	SP!, {R4-R6,LR}	\n"
		"LDR	R4, [R0,#0xC]	\n"
		"LDR	R6, =0x1A08C	\n"
		"LDR	R0, [R4,#8]	\n"
		"MOV	R5, #0		\n"
		"ORR	R0, R0,	#1	\n"
		"STR	R0, [R4,#8]	\n"
		"LDR	R0, [R6,#0x24]	\n"
		"CMP	R0, #0		\n"
		"MOVEQ	R0, #2		\n"
		"BLEQ	sub_FF856814	\n"
		"BL	sub_FF92FED4	\n"
		"LDR	R0, [R6,#0x24]	\n"
		"CMP	R0, #0		\n"
		"BNE	loc_FF85C0D4	\n"
		"MOV	R0, R4		\n"
		"BL	sub_FF930368	\n"
		"TST	R0, #1		\n"
		"MOVNE	R2, R4		\n"
		"LDMNEFD SP!, {R4-R6,LR}\n"
		"MOVNE	R1, #1		\n"
		"BNE	sub_FF85A544	\n"
		"BL	sub_FF9449BC	\n"
		"BL	sub_FF869600	\n"
		"STR	R0, [R4,#0x14]	\n"
		"MOV	R0, R4		\n"
		"BL	sub_FF931468	\n"
		"BL	sub_FF931ECC	\n"
		"MOV	R0, R4		\n"
		"BL	sub_FF931550_my	\n"        //-------------->
                "BL     capt_seq_hook_raw_here\n"  //-------------->
		"MOV	R5, R0		\n"
		"B	loc_FF85C0E4	\n"

        "loc_FF85C0D4:			\n"
		"LDR	R0, =0x5640	\n"
		"LDR	R0, [R0,#4]	\n"
		"CMP	R0, #0		\n"
		"MOVNE	R5, #0x1D	\n"

        "loc_FF85C0E4:			\n"
		"MOV	R2, R4		\n"
		"MOV	R1, #1		\n"
		"MOV	R0, R5		\n"
		"BL	sub_FF85A544	\n"
		"BL	sub_FF93191C	\n"
		"CMP	R0, #0		\n"
		"LDRNE	R0, [R4,#8]	\n"
		"ORRNE	R0, R0,	#0x2000	\n"
		"STRNE	R0, [R4,#8]	\n"
		"LDMFD	SP!, {R4-R6,PC}	\n"
 );
}

void __attribute__((naked,noinline)) task_CaptSeqTask_my() //#fs
{
	asm volatile (
        	"STMFD	SP!, {R3-R9,LR}		\n"
		"LDR	R6, =0x1A08C		\n"
		"LDR	R5, =0x5640		\n"
		"MOV	R9, #1			\n"
		"MOV	R7, #0			\n"

        "loc_FF85BD24:				\n"
		"LDR	R0, [R5,#0xC]		\n"
		"MOV	R2, #0			\n"
		"MOV	R1, SP			\n"
		"BL	sub_FF829130		\n"
		"TST	R0, #1			\n"
		"BEQ	loc_FF85BD50		\n"
		"LDR	R1, =0x43F		\n"
		"LDR	R0, =0xFF85BAA8	        \n"    // aSsshoottask_c ; SsShootTask.c
		"BL	sub_FF81C090		\n"    // Assert                        
		"BL	sub_FF81BE48		\n"    // ExitTask                      
		"LDMFD	SP!, {R3-R9,PC}		\n"

        "loc_FF85BD50:				\n"
		//"LDR	R0, [SP,#0x20+var_20]	\n"
        	"LDR	R0, [SP]          	\n"
		"LDR	R1, [R0]		\n"
		"CMP	R1, #0x17		\n"
		"ADDLS	PC, PC,	R1,LSL#2	\n"
		"B	loc_FF85BF40		\n"    // default: error handler (invalid jump offset) (also when shutter half-pressed?)
                                                                                                                                  
	        "B	loc_FF85BDC4		\n"    // 0: immediately after shutter release, !modify this one!                 
		"B	loc_FF85BE2C		\n"                                                                               
		"B	loc_FF85BE34		\n"
		"B	loc_FF85BE4C		\n"
		"B	loc_FF85BE40		\n"
		"B	loc_FF85BE54		\n"
		"B	loc_FF85BE5C		\n"
		"B	loc_FF85BE64		\n"
		"B	loc_FF85BEBC		\n"
		"B	loc_FF85BEC8		\n"
		"B	loc_FF85BED0		\n"
		"B	loc_FF85BED8		\n"
		"B	loc_FF85BEE0		\n"
		"B	loc_FF85BEE8		\n"
		"B	loc_FF85BEF0		\n"
		"B	loc_FF85BEF8		\n"
		"B	loc_FF85BF00		\n"
		"B	loc_FF85BF0C		\n"
		"B	loc_FF85BF14		\n"
		"B	loc_FF85BF1C		\n"
		"B	loc_FF85BF24		\n"
		"B	loc_FF85BF30		\n"
		"B	loc_FF85BF38		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BDC4:				\n"
        // jumptable FF85BD5C entry 0			
		"BL	sub_FF92FEF8             \n"
                "BL     shooting_expo_param_override\n"  // +
		"BL	sub_FF859FE8		\n"
		"LDR	R0, [R6,#0x24]		\n"
		"CMP	R0, #0			\n"
		"BEQ	loc_FF85BF4C		\n"
		"BL	sub_FF85B774		\n"
		"MOV	R4, R0			\n"
		"LDR	R0, [R6,#0x24]		\n"
		"CMP	R0, #0			\n"
		"BEQ	loc_FF85BE0C		\n"
		"MOV	R0, #0xC		\n"
		"BL	sub_FF85EE0C		\n"
		"TST	R0, #1			\n"
		"STRNE	R9, [R5,#4]		\n"
		"LDRNE	R0, [R4,#8]		\n"
		"ORRNE	R0, R0,	#0x40000000	\n"
		"STRNE	R0, [R4,#8]		\n"
		"BNE	loc_FF85BF4C		\n"

        "loc_FF85BE0C:				\n"
		"BL	sub_FF9449BC		\n"
		"BL	sub_FF869600		\n"
		"STR	R0, [R4,#0x14]		\n"
		"MOV	R0, R4			\n"
		"BL	sub_FF931550		\n"
		"TST	R0, #1			\n"
		"STRNE	R9, [R5,#4]		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BE2C:				\n"
        //; jumptable FF85BD5C entry 1			
		"BL	sub_FF85C054_my         \n"   // *
		"B	loc_FF85BE44		\n"

        "loc_FF85BE34:				\n"
        //; jumptable FF85BD5C entry 2			
		"MOV	R0, #1\n"
		"BL	sub_FF93009C		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BE40:				\n"
        //; jumptable FF85BD5C entry 4			
		"BL	sub_FF92FB94\n"

        "loc_FF85BE44:				\n"
		"STR	R7, [R6,#0x24]		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BE4C:				\n"
        //; jumptable FF85BD5C entry 3			
		"BL	sub_FF92FEC4\n"
		"B	loc_FF85BE44		\n"

        "loc_FF85BE54:				\n"
        //; jumptable FF85BD5C entry 5			
		"BL	sub_FF92FECC\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BE5C:				\n"
        //; jumptable FF85BD5C entry 6			
		"BL	sub_FF92FFBC\n"
		"B	loc_FF85BEC0		\n"

        "loc_FF85BE64:				\n"
        //; jumptable FF85BD5C entry 7			
		"LDR	R4, [R0,#0xC]\n"
		"BL	sub_FF92FED4		\n"
		"MOV	R0, R4			\n"
		"BL	sub_FF9306E8		\n"
		"TST	R0, #1			\n"
		"MOV	R8, R0			\n"
		"BNE	loc_FF85BEA4		\n"
		"BL	sub_FF869600		\n"
		"STR	R0, [R4,#0x14]		\n"
		"MOV	R0, R4			\n"
		"BL	sub_FF931468		\n"
		"MOV	R0, R4			\n"
		"BL	sub_FF93197C		\n"
		"MOV	R8, R0			\n"
		"LDR	R0, [R4,#0x14]		\n"
		"BL	sub_FF869814		\n"

        "loc_FF85BEA4:				\n"
		"BL	sub_FF92FEC4		\n"
		"MOV	R2, R4			\n"
		"MOV	R1, #8			\n"
		"MOV	R0, R8			\n"
		"BL	sub_FF85A544		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BEBC:				\n"
        //; jumptable FF85BD5C entry 8			
		"BL	sub_FF930018\n"

        "loc_FF85BEC0:				\n"
		"BL	sub_FF859FE8		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BEC8:				\n"
        //; jumptable FF85BD5C entry 9			
		"BL	sub_FF92FEC4\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BED0:				\n"
        //; jumptable FF85BD5C entry 10			
		"BL	sub_FF930954\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BED8:				\n"
        //; jumptable FF85BD5C entry 11			
		"BL	sub_FF930B0C\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BEE0:				\n"
        //; jumptable FF85BD5C entry 12			
		"BL	sub_FF930B9C\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BEE8:				\n"
        //; jumptable FF85BD5C entry 13			
		"BL	sub_FF930C50\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BEF0:				\n"
        //; jumptable FF85BD5C entry 14			
		"BL	sub_FF930E38\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BEF8:				\n"
        //; jumptable FF85BD5C entry 15			
		"BL	sub_FF930E88\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF00:				\n"
        //; jumptable FF85BD5C entry 16			
		"MOV	R0, #0\n"
		"BL	sub_FF930F0C		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF0C:				\n"
        //; jumptable FF85BD5C entry 17			
		"BL	sub_FF93104C\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF14:				\n"
        //; jumptable FF85BD5C entry 18			
		"BL	sub_FF9310E0\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF1C:				\n"
        //; jumptable FF85BD5C entry 19			
		"BL	sub_FF9311A0\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF24:				\n"
        //; jumptable FF85BD5C entry 20			
		"BL	sub_FF9301C0\n"
		"BL	sub_FF825BA8		\n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF30:				\n"
        //; jumptable FF85BD5C entry 21			
		"BL	sub_FF930D0C             \n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF38:				\n"
        //; jumptable FF85BD5C entry 22			
		"BL	sub_FF930D78            \n"
		"B	loc_FF85BF4C		\n"

        "loc_FF85BF40:				\n"
        //; jumptable FF85BD5C default entry		
		"LDR	R1, =0x523              \n"
		"LDR	R0, =0xFF85BAA8	        \n"   // aSsshoottask_c ; SsShootTask.c
		"BL	sub_FF81C090		\n"   // Assert                        

        "loc_FF85BF4C:				\n"
        //; jumptable FF85BD5C entry 23			
		//"LDR	R0, [SP,#0x20+var_20]   \n"
        	"LDR	R0, [SP]                \n"
		"LDR	R1, [R0,#4]		\n"
		"LDR	R0, [R5,#8]		\n"
		"BL	sub_FF828EAC		\n"
		//"LDR	R4, [SP,#0x20+var_20]	\n"
        	"LDR	R4, [SP]                \n"
		"LDR	R0, [R4,#8]		\n"
		"CMP	R0, #0			\n"
		"LDREQ	R0, =0xFF85BAA8	        \n"   // aSsshoottask_c ; SsShootTask.c
		"MOVEQ	R1, #0xFC		\n"   
		"BLEQ	sub_FF81C090		\n"   // Assert
		"STR	R7, [R4,#8]		\n"
		"B	loc_FF85BD24		\n"
    );
} //#fe
