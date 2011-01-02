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

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

long vid_get_bitmap_screen_width() { return 320; }
long vid_get_bitmap_screen_height() { return 240; }
long vid_get_bitmap_buffer_width() { return 960; }
long vid_get_bitmap_buffer_height() { return 270; }

int vid_get_viewport_buffer_width() { return 720; }	// G12 - buffer is twice as wide as viewport

int vid_get_viewport_width()
{
	// viewport width table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	static long vp_w[5] = { 360, 360, 360, 272, 216 };
	return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

int vid_get_viewport_xoffset()
{
	// viewport width offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	static long vp_w[5] = { 0, 0, 0, 44, 72 };				// should all be even values for edge overlay
	return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

long vid_get_viewport_height()
{
	// viewport height table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	static long vp_h[5] = { 240, 180, 214, 240, 240 };
	return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}

int vid_get_viewport_yoffset()
{
	// viewport height offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	static long vp_h[5] = { 0, 30, 13, 0, 0 };
	return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
}
