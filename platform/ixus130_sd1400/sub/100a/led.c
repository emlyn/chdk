#include "led.h"

long * LED_GREEN = (long*)0xC0220130,
     * LED_RED   = (long*)0xC0220134,
     * LED_AF    = (long*)0xC0223030;

void busy_wait(ulong time) {
  BUSY_WAIT(time);
}
#undef  BUSY_WAIT
#define BUSY_WAIT busy_wait

void led_on(long * led) {
  LED_ON(led);
}

void led_off(long * led) {
  LED_OFF(led);
}

void led_flash2_helper() {
#define d (1024*1024*3)
  BUSY_WAIT(d);
  LED_ON(LED_GREEN);
  BUSY_WAIT(d);
  LED_ON(LED_RED);
  BUSY_WAIT(2*d);
  LED_OFF(LED_GREEN);
  BUSY_WAIT(d);
  LED_OFF(LED_RED);
  BUSY_WAIT(d);
#undef d
}

void __attribute__((naked,noinline)) led_flash2() {
  asm volatile(
    "push {r0-r11,lr}\n"
    "bl   led_flash2_helper\n"
    "pop  {r0-r11,pc}\n"
    );
}

void led_flashx(long * led, ulong times, ulong delay) {
  LED_FLASHX(led, times, delay);
}

void led_binx(long val, ulong delay) {
  long i = 0;
  led_flashx(val & 0x80000000 ? LED_RED : LED_GREEN, 1, delay);
  for (i = 1; i < 32; ++i) {
    if (i%4 == 0) busy_wait(delay);
    if (i%8 == 0) busy_wait(delay);
    if (i%16 == 0) busy_wait(delay);
    val <<= 1;
    led_flashx(val & 0x80000000 ? LED_RED : LED_GREEN, 1, delay);
  }
  led_flashx(LED_AF, 1, 2*delay);
}

void led_dumpx(long * mem, ulong len, ulong delay) {
  long i = 0;
  led_flashx(LED_AF, 1, 2*delay);
  for (i = 0; i < len; ++i) {
    led_binx(mem[i], delay);
  }
}
