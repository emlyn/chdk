static void __attribute__((noreturn)) shutdown();
static void __attribute__((noreturn)) panic(int cnt);

extern long *blob_chdk_core;
extern long *blob_copy_and_reset;
extern long blob_chdk_core_size;
extern long blob_copy_and_reset_size;

/* @brief Makes a copy of CHDK core in instruction memory and restarts FW.
 *
 * Starts by copying existing copy_and_restart procedure to 0x50000 and then using 
 * copied start_and_restart procedure to copy CHDK core to 0x9C890.  Absolute HEX 
 * addresses come from makefile.inc definitions.
 *
 * @note This is required because camera starts in standard FW (i.e. canon).  To switch between
 * canon and CHDK FW a reset is required.  If start of CHDK FW was a reset then new FW would 
 * continually restart.  As a result CHDK FW on first pass must copy CHDK core (i.e. removing reset
 * code) to instruction memory and then restarting FW so CHDK core executes.
 *
 * @return Does not return.
 */
void __attribute__((noreturn)) my_restart() 
{
    void __attribute__((noreturn)) (*copy_and_restart)(char *dst, char *src, long length);
    int i;

    // Make a copy of the procedure copy_and_reset in another memory space.
	for (i = 0 ; i < (blob_copy_and_reset_size / sizeof(long)) ; i++ ) 
	{
		((long*)(RESTARTSTART))[i] = blob_copy_and_reset[i];
    }

	// Execute duplicated code in non-instruction memory space.
    copy_and_restart = (void*)RESTARTSTART;
    copy_and_restart((void*)MEMISOSTART, (char*)blob_chdk_core, blob_chdk_core_size);
}

#define LED_PR 0xc0220084

static void __attribute__((noreturn)) shutdown()
{
    volatile long *p = (void*)0xc02200a0;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


static void __attribute__((noreturn)) panic(int cnt)
{
	volatile long *p=(void*)LED_PR;
	int i;

	for(;cnt>0;cnt--){
		p[0]=0x46;

		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
		p[0]=0x44;
		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
	}
	shutdown();
}
