#include "platform.h"
#include "lolevel.h"

void vid_bitmap_refresh()
{
	extern int enabled_refresh_physical_screen;
	extern int full_screen_refresh;

	// i've tried refreshphysical screen (screen unlock) and that caused the canon and
	// function menu to not display at all. This seems to work and is called in a similar
	// way in other places where original OSD should be refreshed.
	extern void _LockAndRefresh(); // wrapper function for screen lock
	extern void _UnlockAndRefresh(); // wrapper function for screen unlock

	_LockAndRefresh();

	//enabled_refresh_physical_screen=1;
	full_screen_refresh |= 3; //found in ScreenUnlock underneath a CameraLog.c call sub_FFA02598

	_UnlockAndRefresh();
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

#define LED_PR 0xC0220134	// Power LED

// TODO = this uses power LED, need to disable later (so power LED doesn't flicker)
void debug_led(int state)
{
 //*(int*)LED_PR=state ? 0x46 : 0x44;
}

// SX30 has two 'lights' - Power LED, and AF assist lamp
// Power Led = first entry in table (led 0)
// AF Assist Lamp = second entry in table (led 1)
void camera_set_led(int led, int state, int bright) {
 static char led_table[2]={3,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 0x9a;	// found in GetParameterData ??? 
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x86E, 1);  // RotateJogDialRight (in table @ FFC0E88C, fw 1.00h)
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x86F, 1);  // RotateJogDialLeft (in table @ FFC0E88C, fw 1.00h)
}

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

long vid_get_bitmap_screen_width() { return 320; }
long vid_get_bitmap_screen_height() { return 240; }
long vid_get_bitmap_buffer_width() { return 960; }
long vid_get_bitmap_buffer_height() { return 270; }

int vid_get_viewport_width() { return 360; }

long vid_get_viewport_height()
{
	if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1)	// Wide screen top & bottom 30 pixels not used in viewport
		return 180;
	return 240;
}

int vid_get_viewport_yoffset()
{
	if (shooting_get_prop(PROPCASE_ASPECT_RATIO) == 1)	// Wide screen top & bottom 30 pixels not used in viewport
		return 30;
	return 0;
}

// viewport image offset - used when image size != viewport size (zebra, histogram, motion detect & edge overlay)
// returns the byte offset into the viewport buffer where the image pixels start (to skip any black borders)
int vid_get_viewport_image_offset() {
	return (vid_get_viewport_yoffset() * vid_get_viewport_buffer_width()) * 3;
}
