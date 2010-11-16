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

//  fe50 10-Aug-2008:  LED adresses on SD870: 
#define LED_PR     0xC02200CC  //0
#define LED_YELLOW 0xc02200D8  //+12  (???)
#define LED_ORANGE 0xc0220133  //+103
#define LED_GREEN  0xc0220136  //+106
#define LED_AF     0xc0223030  //+12132

void debug_led(int state)
{
    volatile long *p=(void*)LED_PR;
    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

//  fe50 10-Aug-2008
void camera_set_led(int led, int state, int bright)
{
	// "brigth" not implemented
	// YELLOW not available
	// TIMER -> LED_AF
	int leds[] = {106,12,0,103,0,12132,12132};  //  green | yellow | not used | orange | blue | af beam | timer
	if(led < 4 || led > 10 || led == 6) return; //  return on invalid params;  no extra TIMER LED (is same as AF)
	volatile long *p=(void*)LED_PR + leds[led-4];
	if (state)
		p[0]=0x46;
	else
		p[0]=0x44;
}

int get_flash_params_count(void){
 return 114; //???
}
