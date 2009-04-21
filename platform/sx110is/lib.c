
#include "platform.h"
#include "lolevel.h"

#define LED_PR	0xc02200C4
#define LED_RED 0xc02200C8
#define LED_GRN	0xc02200CC
#define LED_PWR	0xc02200D0

void vid_bitmap_refresh()
{
 extern int enabled_refresh_physical_screen;
 enabled_refresh_physical_screen=1;
 _RefreshPhysicalScreen(1);
}


void shutdown()
{

/*
ROM:FFC0CD8C                 LDR     R1, =0xC0220000
ROM:FFC0CD90                 MOV     R0, #0x44
ROM:FFC0CD94                 STR     R0, [R1,#0x54]
ROM:FFC0CD98                 STR     R0, [R1,#0x4C]


C0220000+54+4C=0xC02200A0

*/

	volatile long *p = (void*)0xC02200A0;    
	
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
 *(int*)LED_PR=state ? 0x46 : 0x44;
 *(int*)LED_GRN=state ? 0x46 : 0x44;
}

void ubasic_set_led(int led, int state, int bright) {
 static char led_table[5]={4,5,7,8,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 120; 
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}



