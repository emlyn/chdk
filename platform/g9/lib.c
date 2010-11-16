#include "platform.h"

void shutdown()
{
    volatile long *p = (void*)0xc022006C;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


#define LED_PR 0xC022006C //used iso blue, was 0xc02200C4  //a650- 0xc02200C4


void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

#define LED_BASE 0xc0220080
#define LED_AF 0xC0220094//was 0xc0220080 //a650- 0xc0220080//from g7

void camera_set_led1(int led, int state, int bright)//?
{
  int leds[] = {12,16,4,8,4,0,4};
  if(led < 4 || led > 10 || led == 6) return;
  volatile long *p=(void*)LED_BASE + leds[led-4];
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}


int get_flash_params_count(void){
 return 114;	//++  FF956AEC
}

int Get_JogDial(void){
 return (*(int*)0xC0220304)>>16;
}
