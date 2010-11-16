#include "platform.h"

/* led addresses, look in function "taskcreate_LEDCon" ROM:FF82F958 (branch to ROM:FF82FEC8)
#define LED_AF    0xC02200C0   // AF Beam (red, frontside)
#define LED_BLUE  0xC02200C4   // led in print/share button (blue, backside)
#define LED_RED   0xC02200C8   // right state led red (bi-state with green, backside)
#define LED_GRN   0xC02200CC   // right state led green (bi-state with red, backside)
#define LED_YLW   0xC02200D0   // left state led (yellow, backside)
#define LED_PWR   0xC02200D8   // power led (green, on top)
*/

void shutdown() {
    volatile long *p = (void*)0xc02200a0;
    asm(
        "MRS     R1, CPSR\n"
        "AND     R0, R1, #0x80\n"
        "ORR     R1, R1, #0x80\n"
        "MSR     CPSR_cf, R1\n"
        :::"r1","r0"
    );
    *p = 0x44;
    while(1);
}

// ROM:FF9B0820 verified that there are 110 entries for FlashParamsTable
int get_flash_params_count(void) {
    return 110;
}

#define LED_PR    0xC02200C4   // (Direct Print Button, Blue Led)
//#define LED_PR    0xC02200D0   // left state led (yellow, backside)

void debug_led(int state) {
    volatile long *p=(void*)LED_PR;
    if(state)
        p[0]=0x46;
    else
        p[0]=0x44;
}

#define LED_BASE  0xC02200C0   // led base address

void camera_set_led(int led, int state, int bright) {
    int leds[] = {12,16,4,8,4,0,4};
    if(led < 4 || led > 10 || led == 6) return;
    volatile long *p=(void*)LED_BASE + leds[led-4];
    if(state)
        p[0]=0x46;
    else
        p[0]=0x44;
}

#ifdef CAM_CONSOLE_LOG_ENABLED
void save_rom_log() {
    asm volatile(
        "MOV R0, #0\n"
        "MOV R1, #1\n"
        "STMDB SP!, {R0, R1, LR}\n"
        "MOV R0, SP\n"
        "MOV LR, PC\n"   // ToDo: required ?
        "BL _GetLogToFile\n"
        "LDMIA SP!, {R0, R1, LR}\n"
    );
}
#endif
