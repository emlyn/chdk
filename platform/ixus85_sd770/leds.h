#ifndef LEDS_H
#define LEDS_H

#define LED_PWR    0xc02200D0
#define LED_PR     0xc02200D4
#define LED_ORANGE 0xc0220130
#define LED_GREEN  0xc0220134
#define LED_YELLOW 0xc0220138
#define LED_AF     0xC0223030

#define DELAY 5000000

void led_blink(volatile long *p);

#endif
