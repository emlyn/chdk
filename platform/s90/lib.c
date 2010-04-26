#include "platform.h"
#include "lolevel.h"

void shutdown()
{
    volatile long *p = (void*)0xc022012C; // S90
    
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


#define LED_PR 0xc0220130 //DP LED

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

void ubasic_set_led(int led, int state, int bright) {
	static char led_table[4]={0,1,9,10};
    _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 130; // ERR99 ToDo: Is this the correct S90 value?
}

void vid_bitmap_refresh()
{
	 extern int enabled_refresh_physical_screen; // screen lock counter
	 extern void _ScreenUnlock();

	 _ScreenLock();
	  enabled_refresh_physical_screen = 1;
	 _ScreenUnlock();
}

