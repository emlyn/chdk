#include "platform.h"
#include "lolevel.h"
#include "sd1400_debug.h"

void vid_bitmap_refresh()
{
    _ScreenLock();
    _RefreshPhysicalScreen(1);
}

void shutdown()
{
    volatile long *p = (void*)0xc022001C; // from task_by (not really complete)

    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");

    *p = 0x44;

    while(1);
}

int get_flash_params_count(void){
 return 120; // ? _sub_FF962AB8__PropertyTableManagerCore_c__6, similar to s5is
             // VERIFY_SD1200. Dunno where the above is from (Not SD780)
}

// based on SX10, values found by experiment
void ubasic_set_led(int led, int state, int bright) {
    return; /* doesn't seem to work */
 static char led_table[]={0, // green
                          1, // orange, right
                          2, // yellow, left
                          3, // power
                          // 4,5,6,7,
                          8, // blue
                          9 // af
                          };
 if((unsigned)led < sizeof(led_table))
  _LEDDrive(led_table[led], state<=1 ? !state : state);
// _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

#define DEBUG_LED LED_IO_Y
void debug_led(int state)
{
    * (int *) DEBUG_LED = state ? 0x46 : 0x44;
}

// from sx10
void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}


