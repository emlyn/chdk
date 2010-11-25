#ifndef INCLUDED_LED_H
#define INCLUDED_LED_H

extern long * LED_GREEN, * LED_RED, * LED_AF;

#ifndef DEFAULT_DELAY
#define DEFAULT_DELAY 5000000
#endif

typedef unsigned long ulong;

void busy_wait(ulong n);
void led_on(long * led);
void led_off(long * led);
void led_flashx(long * led, ulong times, ulong delay);
void led_binx(long val, ulong delay);
void led_dumpx(long * mem, ulong len, ulong delay);

void __attribute__((naked,noinline)) led_flash2();

/*
static inline void led_flash(long * led, ulong times) {
  led_flashx(led, times, DEFAULT_DELAY);
}

static inline void led_bin(long val) {
  led_binx(val, DEFAULT_DELAY);
}

static inline void led_dump(long * mem, ulong len) {
  led_dumpx(mem, len, DEFAULT_DELAY);
}
*/
#define led_flash(led, times) led_flashx(led, times, DEFAULT_DELAY)
#define led_bin(val) led_binx(val, DEFAULT_DELAY)
#define led_dump(mem, len) led_dumpx(mem, len, DEFAULT_DELAY)

#define BUSY_WAIT(delay) do { unsigned long i = (delay); while (--i) asm volatile("nop\n"); } while (0)

#define LED_ON(led) do { *(long*)(led) = 0x46; } while(0)

#define LED_OFF(led) do { *(long*)(led) = 0x44; } while(0)

#define LED_FLASHX(led, times, delay) \
  do { \
    long i = (times);     \
    while (i--) {         \
      LED_ON((led));      \
      BUSY_WAIT((delay)); \
      LED_OFF((led));     \
      BUSY_WAIT((delay)); \
    }                     \
  } while (0)

#define LED_FLASH(led, times) LED_FLASHX((led), (times), DEFAULT_DELAY)

#endif // INCLUDED_LED_H
