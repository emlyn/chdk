#include "platform.h"

void shutdown()
{
    volatile long *p = (void*)0xc022002c;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x46;

    while(1);
}


#define LED_PR 0xc0220088

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}


long _GetFocusLensSubjectDistance()
{
    return -1;
}

void _kbd_pwr_on()
{

}

void _kbd_pwr_off()
{

}

void _Unmount_FileSystem()
{
}
void _Mount_FileSystem()
{
}
