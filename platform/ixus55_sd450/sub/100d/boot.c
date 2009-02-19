#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);


void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit(); // Orig. starts at FF811990
void __attribute__((naked,noinline)) h_usrKernelInit(); // Orig. starts at FF811748
void __attribute__((naked,noinline)) h_usrRoot(); // Orig. starts at FF811A70



void boot()
{
    // offset of "start of data" string in primary.bin - 4
    // All the asm code below is from: 0xFF8100E0

    long *canon_data_src = (void*)0xFFAEB6A0;
    long *canon_data_dst = (void*)0x1900;
    // up to the end of flash
    long canon_data_len = 0xEA00;
    // just after ROM data
    long *canon_bss_start = (void*)(0x1900+0xEA00);
    // BSS end offset (from FF810134 disasm) minus BSS start
    long canon_bss_len = 0xA87D0 - (long)canon_bss_start;
    long i;


    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

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


void h_usrInit() // Orig. starts at FF811990
{
    asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FF81196C\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFACF300\n" // unknown_libname_838
	"BL      sub_FFABB9D8\n" // excVecInit
	"BL      sub_FF8111C4\n"
	"BL      sub_FF81172C\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}

void  h_usrKernelInit() // Orig. starts at FF811748
{
    asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFACF800\n" // classLibInit
	"BL      sub_FFAE4AEC\n" // taskLibInit
	"LDR     R3, =0xF294\n"
	"LDR     R2, =0xA5400\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xA8190\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFADD93C\n" // qInit
	"LDR     R3, =0xF254\n"
	"LDR     R0, =0xFB1C\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFADD93C\n" // qInit
	"LDR     R3, =0xF310\n"
	"LDR     R0, =0xA8164\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFADD93C\n" // qInit
	"BL      sub_FFAE966C\n" // workQInit
	"BL      sub_FF8112B0\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"  // !!!
	"MOV     R1, #0x4000\n"
    );    
//        "LDR     R2, =0xD87D0\n"	// !!! 0xA87D0 + 0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFAE1D2C\n" // kernelInit
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
    );
};


void  h_usrRoot() // Orig. starts at FF811A70
{
    asm volatile (
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FF8119D4\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFAD597C\n" // memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFAD63F4\n" // memPartLibInit
	"BL      sub_FF811708\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFAD8398\n" // selectInit
	"BL      sub_FF811A18\n"
	"BL      sub_FF8119F8\n"
	"BL      sub_FF811A44\n"
	"BL      sub_FFAD7C58\n" // selTaskDeleteHookAdd
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

