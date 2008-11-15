/*
 * led adresses and blinker code
 *
 * this file is part of the chdk project
 * (c) 2008 chr
 * GPL v3+
 *
 * creates for each LED 3 functions (e.g. green):
 *
 * 1. blink_LED_GREEN()
 * 2. LED_GREEN_ON()
 *    LED_GREEN_OFF()
 *
 * can also used from asm: BL LED_GREEN_ON
 *
 * to 1.
 * saves and restores registers on stack.
 * Be careful when using from Supervisor mode,
 * (that means while booting!)
 * it may crash while interrupts are active
 *
 * to 2.
 * register r2 and r3 are clobbered !
 */


// from ff8e8f10
#define LED_PWR    0xc02200d0
#define LED_PR     0xc02200d4
#define LED_ORANGE 0xc0220130
#define LED_GREEN  0xc0220134
#define LED_YELLOW 0xc0220138
#define LED_AF     0xC0223030

#define DELAY 3000000

void blink_it(volatile long *p);

#define blink_(LED) \
void __attribute__((noinline)) blink_##LED(); \
void __attribute__((noinline)) LED##_ON(); \
void __attribute__((noinline)) LED##_OFF();


//#undef blink_(led)
//#define blink_(LED) blink_##LED() = 0;
blink_(LED_PWR)
blink_(LED_GREEN)
blink_(LED_YELLOW)
blink_(LED_ORANGE)
blink_(LED_AF)
blink_(LED_PR)
#undef blink_

