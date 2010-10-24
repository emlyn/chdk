// Operating system has died. Known functions will be killed after memmove. Make sure stack is not used.

void __attribute__((noreturn)) copy_and_restart(void *dst_void, const void *src_void, long length) {
    {
        char *dst = dst_void;
        const char *src = src_void;
        if (src < dst && dst < src + length) {
            // Have to copy backwards
            src += length;
            dst += length;
            while (length--) {
                *--dst = *--src;
            }
        } else {
            while (length--) {
                *dst++ = *src++;
            }
        }
    }

    // DEBUG: jump to rom base address of regular firmware (causing camera to restart in a loop, enable flash led to get feedback)
    //dst_void = (void*)0xFF810000;   // Canon A-series: 0xFFC00000 ; S-, SD-, and G- series: 0xFF810000

    // ROM:FF823AE4 resetcode here:
    // ToDo: copy real RestartDevice stuff from dissassemble
    // This is generic restartcode
    // search for "0xC0200000"
    asm volatile(
        "MRS     R1, CPSR\n"
        "BIC     R1, R1, #0x3F\n"
        "ORR     R1, R1, #0xD3\n"
        //"MSR     CPSR_cf, R1\n"   // orginal
        "MSR     CPSR, R1\n"
        "LDR     R2, =0xC0200000\n"
        "MOV     R1, #0xFFFFFFFF\n"
        "STR     R1, [R2,#0x10C]\n"
        "STR     R1, [R2,#0xC]\n"
        "STR     R1, [R2,#0x1C]\n"
        "STR     R1, [R2,#0x2C]\n"
        "STR     R1, [R2,#0x3C]\n"
        "STR     R1, [R2,#0x4C]\n"
        "STR     R1, [R2,#0x5C]\n"
        "STR     R1, [R2,#0x6C]\n"
        "STR     R1, [R2,#0x7C]\n"
        "STR     R1, [R2,#0x8C]\n"
        "STR     R1, [R2,#0x9C]\n"
        "STR     R1, [R2,#0xAC]\n"
        "STR     R1, [R2,#0xBC]\n"
        "STR     R1, [R2,#0xCC]\n"
        "STR     R1, [R2,#0xDC]\n"
        "STR     R1, [R2,#0xEC]\n"
        "STR     R1, [R2,#0xFC]\n"
        //"CMP     R4, #7\n"
        //"LDMEQFD SP!, {R4,PC}\n"
        "MOV     R1, #0x78\n"
        "MCR     p15, 0, R1,c1,c0\n"
        "MOV     R1, #0\n"
        "MCR     p15, 0, R1,c7,c10, 4\n"
        "MCR     p15, 0, R1,c7,c5\n"
        "MCR     p15, 0, R1,c7,c6\n"
        "MOV     R2, #0x40000000\n"
        "ORR     R1, R2, #6\n"
        "MCR     p15, 0, R1,c9,c1\n"
        "ORR     R1, R1, #6\n"
        "MCR     p15, 0, R1,c9,c1, 1\n"
        "MRC     p15, 0, R1,c1,c0\n"
        "ORR     R1, R1, #0x50000\n"
        "MCR     p15, 0, R1,c1,c0\n"
        "MOV     R3, #0xFF0\n"
        "LDR     R1, =0x12345678\n"
        //"MOV     R2, #0x81000000\n"
        "ADD     R3, R3, #0x4000000C\n"
        "STR     R1, [R3]\n"

        "MOV     SP, #0x1900\n"   // 0x2000000
        "MOV     LR, PC\n"
        "MOV     PC, %0\n"
        :: "r"(dst_void) : "memory","r1","r2","r3"
    );

    while(1);
}

// NEXT: core/entry.S -> platform/<camera>/main.c startup()
