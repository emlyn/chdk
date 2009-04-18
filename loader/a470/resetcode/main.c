
/*
 * Operating system has died. Known functions will be killed
 * after memmove.
 *
 * Make sure stack is not used.
 */

#define DP (void*)0xC0220084	// direct-print (blue)
#define AF (void*)0xC0220080
#define DELAY 5000000
/*
void debug(){
	volatile long *p = (void*)AF;
	*p = 0x46;
	while(1);
}*/

void __attribute__((noreturn)) copy_and_restart(void *dst_void, const void *src_void, long length) {

        volatile long *p = (void*)AF;       // turned off later, so assumed to be power

        int counter;

        // DEBUG: blink led
        //counter = DELAY; *p = 0x46;  while (counter--) { asm("nop\n nop\n"); };
        //counter = DELAY; *p = 0x44;  while (counter--) { asm("nop\n nop\n"); };
		
		//src_void = debug;
		//length = 100;
		
        {
                char *dst = dst_void;
                const char *src = src_void;

                if (src < dst && dst < src + length)
                {
                        /* Have to copy backwards */
                        src += length;
                        dst += length;
                        while (length--)
                        {
                                *--dst = *--src;
                        }
                }
                else
                {
                        while (length--)
                        {
                                *dst++ = *src++;
                        }
                }
        }
	
        //DEBUG: blink again
        //counter = DELAY; *p = 0x46;  while (counter--) { asm("nop\n nop\n"); };
        //counter = DELAY; *p = 0x44;  while (counter--) { asm("nop\n nop\n"); };

        // DEBUG: jump to regular firmware-boot (causing a boot loop)
        //dst_void = (void*) 0xFFC00000;

        // resetcode here:
        asm volatile (
                        "MRS     R0, CPSR\n"
                        "BIC     R0, R0, #0x3F\n"
                        "ORR     R0, R0, #0xD3\n"
                        "MSR     CPSR, R0\n"
                        "LDR     R1, =0xC0200000\n"
                        "MOV     R0, #0xFFFFFFFF\n"
                        "STR     R0, [R1,#0x10C]\n"
                        "STR     R0, [R1,#0xC]\n"
                        "STR     R0, [R1,#0x1C]\n"
                        "STR     R0, [R1,#0x2C]\n"
                        "STR     R0, [R1,#0x3C]\n"
                        "STR     R0, [R1,#0x4C]\n"
                        "STR     R0, [R1,#0x5C]\n"
                        "STR     R0, [R1,#0x6C]\n"
                        "STR     R0, [R1,#0x7C]\n"
                        "STR     R0, [R1,#0x8C]\n"
                        "STR     R0, [R1,#0x9C]\n"
                        "STR     R0, [R1,#0xAC]\n"
                        "STR     R0, [R1,#0xBC]\n"
                        "STR     R0, [R1,#0xCC]\n"
                        "STR     R0, [R1,#0xDC]\n"
                        "STR     R0, [R1,#0xEC]\n"
                        "CMP     R4, #7\n"
                        "STR     R0, [R1,#0xFC]\n"
                        "LDMEQFD SP!, {R4,PC}\n"
                        "MOV     R0, #0x78\n"
                        "MCR     p15, 0, R0,c1,c0\n"
                        "MOV     R0, #0\n"
                        "MCR     p15, 0, R0,c7,c10, 4\n"
                        "MCR     p15, 0, R0,c7,c5\n"
                        "MCR     p15, 0, R0,c7,c6\n"
                        "MOV     R0, #0x40000006\n"
                        "MCR     p15, 0, R0,c9,c1\n"
                        "MCR     p15, 0, R0,c9,c1, 1\n"
                        "MRC     p15, 0, R0,c1,c0\n"
                        "ORR     R0, R0, #0x50000\n"
                        "MCR     p15, 0, R0,c1,c0\n"				
                        "LDR     R0, =0x12345678\n"
                        "MOV     R1, #0x40000000\n"
                        "STR     R0, [R1,#0xFFC]\n"
                        //"LDR     R0, =0xFFC00000\n"   // original jump-vector
                        "MOV     R0, %0\n"              // new jump-vector
                        "LDMFD   SP!, {R4,LR}\n"
                        //"BX        %0\n"
                        "BX      R0\n"
                        : : "r"(dst_void) : "memory","r0","r1","r2","r3","r4");
        //);

        while(1);
}
