#include "platform.h"

void shutdown()
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


#define LED_PR 0xc02200e4  // found in sub_FF82D1A0

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}
#define LED_AF 0xc02200ec
#define LED_BASE 0xc02200dc

void ubasic_set_led(int led, int state, int bright)

{
  int leds[] = {12,16,4,8,4,0,4};
  if(led < 4 || led > 10 || led == 6) return;
  volatile long *p=(void*)LED_BASE+ leds[led-4];
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}


int get_flash_params_count(void){
 return 83;
}

