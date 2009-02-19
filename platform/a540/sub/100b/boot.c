#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);


void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();

#define LED_PR 0xc0220084

static void blink(int cnt)
{
	volatile long *p=(void*)LED_PR;
	int i;

	for(;cnt>0;cnt--){
		p[0]=0x46;

		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
		p[0]=0x44;
		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
	}
}

static void __attribute__((noreturn)) panic(int cnt)
{
        blink(cnt);
	shutdown();
}

void boot()
{

  asm volatile (
//        "B       0xFFC00000\n"
        "MOV     R0, #2\n"
        "TEQ     R0, #2\n"
        "LDR     SP, =0x1900\n"
        "MOV     R11, #0\n"
        
        "MOV     R0, #0x3D\n"
        "MCR     p15, 0, R0,c6,c0\n"
        "MOV     R0, #0xC000002F\n"
        "MCR     p15, 0, R0,c6,c1\n"
        "MOV     R0, #0x31\n"
        "MCR     p15, 0, R0,c6,c2\n"
        "LDR     R0, =0x10000031\n"
        "MCR     p15, 0, R0,c6,c3\n"
        "MOV     R0, #0x40000017\n"
        "MCR     p15, 0, R0,c6,c4\n"
        "LDR     R0, =0xFF80002D\n"
        "MCR     p15, 0, R0,c6,c5\n"
        "MOV     R0, #0x34\n"
        "MCR     p15, 0, R0,c2,c0\n"
        "MOV     R0, #0x34\n"
        "MCR     p15, 0, R0,c2,c0, 1\n"
        "MOV     R0, #0x34\n"
        "MCR     p15, 0, R0,c3,c0\n"
        "LDR     R0, =0x3333330\n"
        "MCR     p15, 0, R0,c5,c0, 2\n"
        "LDR     R0, =0x3333330\n"
        "MCR     p15, 0, R0,c5,c0, 3\n"
        "MRC     p15, 0, R0,c1,c0\n"
        "ORR     R0, R0, #0x1000\n"
        "ORR     R0, R0, #1\n"
        "MCR     p15, 0, R0,c1,c0\n"
        
        "STR     LR, [SP,#-4]!\n"
        "MRC     p15, 0, R0,c1,c0\n"
        "ORR     R0, R0, #0x1000\n"
        "ORR     R0, R0, #4\n"
        "ORR     R0, R0, #1\n"
        "MCR     p15, 0, R0,c1,c0\n"
        "LDR     R3, =0xB910\n"
        "MOV     R12, #0\n"
        "CMP     R12, R3\n"
        "LDR     R2, =0xFFEF3DF0\n"
        "MOV     R1, #0x1900\n"
        "BCS     loc_FFC00130\n"
        "MOV     LR, R3\n"
  "loc_FFC00114:\n"
        "LDR     R3, [R2]\n"
        "ADD     R12, R12, #4\n"
        "CMP     R12, LR\n"
        "STR     R3, [R1]\n"
        "ADD     R2, R2, #4\n"
        "ADD     R1, R1, #4\n"
        "BCC     loc_FFC00114\n"
  "loc_FFC00130:\n"
        "LDR     R1, =0xD210\n"
        "LDR     R3, =0x922D0\n"
        "MOV     R12, #0\n"
        "RSB     R3, R1, R3\n"
        "CMP     R12, R3\n"
        "BCS     loc_FFC0015C\n"
        "MOV     R2, R12\n"
  "loc_FFC0014C:\n"
        "ADD     R2, R2, #4\n"
        "CMP     R2, R3\n"
        "STR     R12, [R1],#4\n"
        "BCC     loc_FFC0014C\n"
  "loc_FFC0015C:\n"
        "MRC     p15, 0, R0,c1,c0\n"
        "ORR     R0, R0, #0x1000\n"
        "BIC     R0, R0, #4\n"
        "ORR     R0, R0, #1\n"
        "MCR     p15, 0, R0,c1,c0\n"
        "LDR     LR, [SP],#4\n"
//        "B       sub_FFC0198C\n"
        "B       h_usrInit\n"
  );
//  blink(2);

}


void h_usrInit()
{
  asm volatile (
        "STR     LR, [SP,#-4]!\n"
        "BL      sub_FFC01968\n"
        "MOV     R0, #2\n"
        "MOV     R1, R0\n"
        "BL      sub_FFEDA92C\n"
        "BL      sub_FFECD5A8\n"
        "BL      sub_FFC011C4\n"
        "BL      sub_FFC01728\n"
        "LDR     LR, [SP],#4\n"
//        "B       sub_FFC01744\n"
        "B       h_usrKernelInit\n"
  );
}

void  h_usrKernelInit()
{

  asm volatile (
        "STMFD   SP!, {R4,LR}\n"
        "SUB     SP, SP, #8\n"
        "BL      sub_FFEDAE2C\n"
        "BL      sub_FFEEDC14\n"
        "LDR     R3, =0xC230\n"
        "LDR     R2, =0x8E900\n"
        "LDR     R1, [R3]\n"
        "LDR     R0, =0x91C90\n"
        "MOV     R3, #0x100\n"
        "BL      sub_FFEE6D24\n"
        "LDR     R3, =0xC1F0\n"
        "LDR     R0, =0xCA38\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFEE6D24\n"
        "LDR     R3, =0xC2AC\n"
        "LDR     R0, =0x91C64\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFEE6D24\n"
        "BL      sub_FFEF1FD0\n"
        "BL      sub_FFC012B0\n"
        "MOV     R4, #0\n"
        "MOV     R3, R0\n"
        "MOV     R12, #0x800\n"
        
//        "LDR     R0, =0xFFC01A60\n"
//        "MOV     R1, #0x4000\n"
//        "LDR     R2, =0x922D0\n"
        
        "LDR     R0, =h_usrRoot\n"
        "MOV     R1, #0x4000\n"
        );    
//        "LDR     R2, =0xD22D0\n" // 0x922D0 + MEMISOSIZE(0x40000)
        asm volatile (
            "LDR     R2, =new_sa\n"
            "LDR     R2, [R2]\n"
        );
        asm volatile (

        "STR     R12, [SP]\n"
        "STR     R4, [SP,#4]\n"
        "BL      sub_FFEEAE54\n"
        "ADD     SP, SP, #8\n"
        "LDMFD   SP!, {R4,PC}\n"
  );
}


void  h_usrRoot()
{
    asm volatile (
        "STMFD   SP!, {R4,R5,LR}\n"
        "MOV     R5, R0\n"
        "MOV     R4, R1\n"
        "BL      sub_FFC019D0\n"
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFEDFAC0\n"
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFEE0538\n"
        "BL      sub_FFC017E8\n"
        "BL      sub_FFC01704\n"
        "BL      sub_FFC01A0C\n"
        "BL      sub_FFC019F0\n"
        "BL      sub_FFC01A38\n"
        "BL      sub_FFC019C4\n"
    );

// patch begin
    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

   drv_self_hide();

// patch end

    asm volatile (
        "LDMFD   SP!, {R4,R5,LR}\n"
        "B       sub_FFC0136C\n"
    );
}
