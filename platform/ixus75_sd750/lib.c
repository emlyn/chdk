#include "platform.h"

//define LED_AF    0xc02200C0 // found in "taskcreate_LEDCon"
//define LED_BLUE  0xc02200C4
//define LED_RED   0xc02200C8
//define LED_GRN   0xc02200CC
//define LED_YLW   0xc02200D0
//define LED_PWR   0xc02200D4

void shutdown()
{
    volatile long *p = (void*)0xC02200A0;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


#define LED_PR 0xc02200C4

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}


int get_flash_params_count(void){
 return 111;
}

#define LED_BASE 0xC02200C0

void camera_set_led(int led, int state, int bright)

{
  int leds[] = {12,16,4,8,4,0,4};
  if(led < 4 || led > 10 || led == 6) return;
  volatile long *p=(void*)LED_BASE + leds[led-4];
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

