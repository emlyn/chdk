static void __attribute__((noreturn)) shutdown();
static void __attribute__((noreturn)) panic(int cnt);

static long spycode[] = {
#include "reboot_core.h"
};

static long cp_n_res[] = {
#include "copy_and_reset.h"
};

#define LED_PR 0xc0220084

#define SPYCODEBASE ((void*)MEMISOSTART)
//#define RESETCODEBASE ((void*)0x1900)
#define RESETCODEBASE ((void*)RESTARTSTART)


void __attribute__((noreturn)) my_restart() 
{
    void __attribute__((noreturn)) (*copy_and_restart)(char *dst, char *src, long length);
    int i;

    for (i=0;i<(sizeof(cp_n_res)/sizeof(long));i++){
	((long*)(RESETCODEBASE))[i] = cp_n_res[i];
    }

    copy_and_restart = RESETCODEBASE;
    
    copy_and_restart(SPYCODEBASE, (char*)spycode, sizeof(spycode));
}

static void __attribute__((noreturn)) shutdown()
{
    volatile long *p = (void*)0xc02200a0;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


static void __attribute__((noreturn)) panic(int cnt)
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
	shutdown();
}
