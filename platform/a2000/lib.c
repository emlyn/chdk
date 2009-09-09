
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


int get_flash_params_count(void){
 return 120; 
}

void ubasic_set_led(int led, int state, int bright) { 
        struct led_control led_c; 
        char convert_table[11]={0,1,2,3,0,2,3,1,8,10,10};  // s3 to a710 (and a720) convert table

        //char convert_table[6]={0,1,2,3,8,10};  // Test a720, values 0-5 are valid

        // 0 gr  
        // 1 red 
        // 2 yel 
        // 3 pw  
        // 8 dp  
        // 9 af  

        led_c.led_num=convert_table[led%11]; 
        led_c.action=state<=1 ? !state : state; 
        led_c.brightness=bright; 
        led_c.blink_count=255; 
        _PostLEDMessage(&led_c); 
} 


/*


void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}
*/



