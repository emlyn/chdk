#define LED_IO_R 0xC0220130
#define LED_IO_G 0xC0220134
#define LED_IO_Y 0xC0220138
#define LED_AF   0xC0223030

#define DELAY_1S     { int i; for (i = 0; i < 0x200000; i++) { asm volatile ("nop\n" ); } }

#define LED_ON(x) { volatile long *p = (void *)x; *p = 0x46; }
#define LED_OFF(x) { volatile long *p = (void *)x; *p = 0x44; }

#define LED_ON_1S(x) { volatile long *p = (void *)x; *p = 0x46; \
                    int i; for (i = 0; i < 0x200000; i++) { asm volatile ("nop\n" ); }  }
#define LED_OFF_1S(x) { volatile long *p = (void *)x; *p = 0x44; \
                    int i; for (i = 0; i < 0x200000; i++) { asm volatile ("nop\n" ); }  }

