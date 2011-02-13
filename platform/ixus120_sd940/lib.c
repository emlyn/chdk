#include "platform.h"
#include "lolevel.h"

#define LED_GREEN  0xC0220130
#define LED_ORANGE 0xC0220134
#define LED_AF     0xC0223030

extern int enabled_refresh_physical_screen;

extern unsigned int screen_width, screen_height, screen_size;
extern void draw_filled_rect( int, int, int, int, int );

void vid_bitmap_refresh()
{
	// this erase should not be needed but it is
	draw_filled_rect(0, 0, screen_width, screen_height, 0x00) ;
/*
	_ScreenLock();
	enabled_refresh_physical_screen=1;
	_RefreshPhysicalScreen(1);
*/
}


void shutdown()
{
	volatile long *p = (void*)LED_AF;

	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");

	*p = 0x44;  // power off.

	while(1);
}


void debug_led(int state)
{
 *(int*)LED_ORANGE=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[5]={4,5,7,8,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 120;
}

void vid_turn_off_updates()
{
  _ScreenLock();
}

void vid_turn_on_updates()
{
  _RefreshPhysicalScreen(1);
}


