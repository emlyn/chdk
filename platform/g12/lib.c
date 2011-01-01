#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
	extern int full_screen_refresh;
	extern void _LockAndRefresh();
	extern void _ScreenUnlock();

	full_screen_refresh |= 3;
	_LockAndRefresh();
	_ScreenUnlock();
}


void shutdown()
{
	volatile long *p = (void*)0xC022001C;    
	
	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");
	
	*p = 0x44;  // power off.
	
	while(1);
}

#define LED_PR 0xC0220138	// Lower Indicator

void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

// G12 has 7 led values
// 0/0 - Upper indicator Green
// 1/1 - Upper indicator Orange
// 2/2 - Lower indicator Yellow
// 3/3 - Power LED Green
// 4/9 - AF Assist Lamp
// 5/14 - ISO LED
// 6/15 - EV LED
void camera_set_led(int led, int state, int bright) {
 static char led_table[7]={0,1,2,3,9,14,15};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 0x9a;	// found in GetParameterData
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x86E, 1);  // RotateJogDialRight (table @ FFC0BE90)
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x86F, 1);  // RotateJogDialLeft (table @ FFC0BE90)
}
