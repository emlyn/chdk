#include "lolevel.h"
#include "platform.h"
#include "core.h"
//#include "stdlib.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);


void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();



void boot()
{
    // offset of "start of data" string in primary.bin - 4
    // All the asm code below is from: 0xFF8100F8

    long *canon_data_src = (void*)0xFFB29580;
    long *canon_data_dst = (void*)0x1900;
    // up to the end of flash
    long canon_data_len = 0xBDE0;
    // just after ROM data
    long *canon_bss_start = (void*)(0x1900+0xBDE0);
    // BSS end offset (from FF810134 disasm) minus BSS start
    long canon_bss_len = 0x9C6B0 - (long)canon_bss_start;
    long i;

    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
/*
	int * data = (int*)0x170000;
	for (i = 0; i < 30*1024*1024/4; i++) {
	  data[i] = 0xCAFEDEAD;
	}
*/

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;


    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"BIC     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
    h_usrInit();
}


void h_usrInit()
{
    asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FF81196C\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFB0EED8\n"
	"BL      sub_FFB01B4C\n"
	"BL      sub_FF8111C4\n"
	"BL      sub_FF81172C\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()
{
    asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFB0F3D8\n"
	"BL      sub_FFB22BE0\n"
	"LDR     R3, =0xC6F0\n"
	"LDR     R2, =0x99340\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0x9C070\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFB1BCF0\n"
	"LDR     R3, =0xC6B0\n"
	"LDR     R0, =0xCEF8\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB1BCF0\n"
	"LDR     R3, =0xC76C\n"
	"LDR     R0, =0x9C044\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB1BCF0\n"
	"BL      sub_FFB27760\n"
	"BL      sub_FF8112B0\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"  // !!!
	"MOV     R1, #0x4000\n"
    );    
//	"LDR     R2, =0xCC6B0\n"	// !!! 0x9C6B0 + 0x30000    MEMISOSIZE!!!
//	"LDR     R2, =0x18A6B0\n"   // !!! Increased size !!! 0x9C6B0+0x1ae000= 0x24A6B0-0x18A6B0=786432
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"                    
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFB1FE20\n"
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
    );
}


void  h_usrRoot()
{
    asm volatile
    (
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FF8119D4\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB1406C\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB14AE4\n"
	"BL      sub_FF811708\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFB16A88\n"  // selectInit
    );

    asm volatile
    (	
	"BL      sub_FF811A14\n" //ios_tty_Init
	"BL      sub_FF8119F8\n"
	"BL      sub_FF811A40\n"
	"BL      sub_FFB16348\n"
	"BL      sub_FF8119C8\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FF811370\n"
    );
}

