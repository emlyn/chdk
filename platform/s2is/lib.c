#include "platform.h"
#include "lolevel.h"

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

#define LED_BRIGHTNESS  200
#define LED_GREEN       4
#define LED_YELLOW      5
#define LED_ORANGE      7
#define LED_BLUE        8
#define LED_AF_BEAM     9
#define LED_TIMER       10
  
static void led_on(const int led, const int brightness)
{
    if (led < 4 || led > 10 || led == 6) return;
    static void* addr;
    addr = led_table + (led * 0x40);
    _UniqueLedOn(addr,brightness);
}
 
static void led_off(const int led)
{
    if (led < 4 || led > 10 || led == 6) return;
    static void* addr;
    addr = led_table + (led * 0x40);
    _UniqueLedOff(addr);
}

void debug_led(int state)
{
    if (state)
        led_on(LED_BLUE, LED_BRIGHTNESS);
    else
        led_off(LED_BLUE);
}

int get_flash_params_count(void){
 return 85;
}

void camera_set_led(int led, int state, int bright)
{
	if (state) {
		if (bright > LED_BRIGHTNESS) bright = LED_BRIGHTNESS;
		if (led == 6) {
	        led_on(4, bright);
		    led_on(5, bright);
		} else
			led_on(led, bright);
	}
    else
		if (led == 6) {
	        led_off(4);
		    led_off(5);
		} else
        led_off(led);
}
