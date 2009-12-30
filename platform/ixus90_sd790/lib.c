#include "platform.h"
#include "lolevel.h"
#include "leds.h"

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

void debug_led(int state)
{
	volatile long *p=(void*)LED_ORANGE;
	if (state)
	p[0]=0x46;
	else
	p[0]=0x44;
}

void debug_led_c(int color, int state)
{
    volatile long *p;
	if (color==0)
		p=(void*)LED_PR;
	else if (color==1)
		p=(void*)LED_GREEN;
	else if (color==2)
		p=(void*)LED_ORANGE;
	else
		p=(void*)LED_AF;

    if (state)
	p[0]=0x46;
    else
	p[0]=0x44;
}

//  fe50 10-Aug-2008
void ubasic_set_led(int led, int state, int bright)
{
/*	// "brigth" not implemented
	// YELLOW not available
	// TIMER -> LED_AF
	int leds[] = {0x134,0x138,0,0x130,0xd4,0x3030,0x3030};  //  green | yellow | not used | orange | blue | af beam | timer
	if(led < 4 || led > 10 || led == 6) return; //  return on invalid params;  no extra TIMER LED (is same as AF)
	volatile long *p=(void*)LED_PR + leds[led-4];
	if (state)
		p[0]=0x46;
	else
		p[0]=0x44;
*/
}

void JogDial_CW(void)
{
	_PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void)
{
	_PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}

// 0x73 @ FF95D668
int get_flash_params_count(void) { return 115; }

