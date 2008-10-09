/*
 * Operating system has died. Known functions will be killed
 * after memmove.
 *
 * Make sure stack is not used.
 */

/* @brief Copy FW over existing FW and reset, new code is then being executed.
 *
 * Copy's FW load of length from start address at src_void to dst_void.  Following this 
 * there are some ASM statements to reset the device.
 * 
 * @param dst_void Pointer to destination 
 * @param src_void Pointer to source
 * @param long Length of compiled FW.
 * @return Does not return.
 */
void __attribute__((noreturn)) copy_and_restart(void *dst_void, const void *src_void, long length) {
{
      char *dst = dst_void;
      const char *src = src_void;
      
      if (src < dst && dst < src + length) {
         /* Have to copy backwards.
		  * otherwise destination data will begin to overwrite source data
		  * that has not been copied yet.*/
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

	/*
	 * The following asm volatile is used to:
	 *  - Change the processor mode to supervisor mode and disable interrupts
	 *  - Write all 1s from ___ base over offsets 0x00C to 0x10C
	 *  - Do some stuff with co-processor 15 (system control coprocessor)
	 *  - Some more stuff
	 *  - Adjust the SP, LR and PC.  PC points to passed argument dst_void, 
	 *    which is a pointer to a character.
	 */
    asm volatile(
	"MRS     R1, CPSR\n"		// Save 'current processor status registers' to R1
	"BIC     R1, R1, #0x3F\n"	// Change CPSR register to use ARM instruction set and ...
	"ORR     R1, R1, #0xD3\n"	// disable interrupts (fast and normal) and set supervisor mode (10011).
	"MSR     CPSR_cf, R1\n"		// Write new CPSR back into CPSR reg

	"LDR     R2, =0xC0200000\n" // Load register with word from memory - this is used as an address base.  Where is this?
	"MOV     R1, #0xFFFFFFFF\n"	// Load all 1s into R1 for memory writes that follow.
	"STR     R1, [R2,#0x10C]\n"	// This entire block of store commands writes all 1s from base address stored in R2
	"STR     R1, [R2,#0xC]\n"	// over the offsets 0x00C to 0x10C.  
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
	"STR     R1, [R2,#0xFC]\n"	// Done setting all 1s to memory block described above

	/*
	 * The following code makes use of co-processor 15 (system control coprocessor)
	 * CP15 c2-c6, c8, c10, c13 are allocated to memory protection system.
	 * CP15 c7, c9 are allocated to the control of caches and write buffers.
	 * CP15 c11 is allocated to level 1 memory DMA support.
	 * CP15 c12, c14 are reserved.
	 */
	// Register 1 is for cache and write buffer control bits
	"MOV     R1, #0x78\n"				// 0111 1000
	"MCR     p15, 0, R1,c1,c0\n"		// disable cache, enable write buffer, disable instruction cache
	"MOV     R1, #0\n"					
	// Register 7 writes are cache management functions
	"MCR     p15, 0, R1,c7,c10, 4\n"	// c10, 4 is data sync barrier (used to be drain write buffer) a memory barrier (blocks memory access?)
										// that completes when: memory access before this instruction are done, all cache ,branch predictor and 
										// translation lookaside buffer (TLB) maintenance operations preceding this instruction are done.
	"MCR     p15, 0, R1,c7,c5\n"		// c5, 0 invalidates entire instruction cache
	"MCR     p15, 0, R1,c7,c6\n"		// c6, 0 invalidates entire data cache
	// Register 9 is responsible for cache lockdown functions
	"MOV     R2, #0x40000000\n"			
	"ORR     R1, R2, #6\n"
	"MCR     p15, 0, R1,c9,c1\n"
	"ORR     R1, R1, #6\n"
	"MCR     p15, 0, R1,c9,c1, 1\n"
	// see above for register 1 functions
	"MRC     p15, 0, R1,c1,c0\n"		// following lines of code set bits 16 and 18 
	"ORR     R1, R1, #0x50000\n"
	"MCR     p15, 0, R1,c1,c0\n"

	"MOV     R3, #0xFF0\n"
	"LDR     R1, =0x12345678\n"
	"ADD     R3, R3, #0x4000000C\n"
	"STR     R1, [R3]\n"

	"MOV     SP, #0x1900\n"
	"MOV     LR, PC\n"
	"MOV     PC, %0\n"
    : : "r"(dst_void) : "memory","r1","r2","r3");

    while(1);
}
