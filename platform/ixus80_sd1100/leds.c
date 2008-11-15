/*
 * this file is part of the chdk project
 * (c) 2008 chr
 * GPL v3+
 */

#include "platform.h"
#include "leds.h"


void blink_it(volatile long *p) {
    int counter;

	asm("stmdb	sp!, {r0, r1, r2, r3} \n"); \

    counter = DELAY; *p = 0x46;
    while (counter--) { asm("nop\n nop\n"); };
    counter = DELAY; *p = 0x44;
    while (counter--) { asm("nop\n nop\n"); };

	asm("ldmia	sp!, {r0, r1, r2, r3} \n"); \
}

#define blink_(LED) void blink_##LED() { \
	blink_it((long*)LED); \
} \
void __attribute__((noinline)) LED##_ON() { \
	*(long *)LED = 0x46; \
} \
void __attribute__((noinline)) LED##_OFF() { \
	*(long *)LED = 0x44; \
}
blink_(LED_PWR)
blink_(LED_GREEN)
blink_(LED_YELLOW)
blink_(LED_ORANGE)
blink_(LED_AF)
blink_(LED_PR)

#undef blink_

