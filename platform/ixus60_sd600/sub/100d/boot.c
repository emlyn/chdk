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

    long *canon_data_src = (void*)0xFFB204A0;
    long *canon_data_dst = (void*)0x1900;
    // up to the end of flash
    long canon_data_len = 0xBC80;
    // just after ROM data
    long *canon_bss_start = (void*)(0x1900+0xBC80);
    // BSS end offset (from FF810134 disasm) minus BSS start
    long canon_bss_len = 0x9C4B0 - (long)canon_bss_start;
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


void h_usrInit()        // 0xFF811990
{
    asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FF81196C\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFB05DF4\n"    // unknown_libname_805
	"BL      sub_FFAF90DC\n"    // excVecInit
	"BL      sub_FF8111C4\n"
	"BL      sub_FF81172C\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()     // 0xFF811748
{
    asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFB062F4\n"
	"BL      sub_FFB19AFC\n"
	"LDR     R3, =0xC590\n"
	"LDR     R2, =0x99140\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0x9BE70\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFB12C0C\n"
	"LDR     R3, =0xC550\n"
	"LDR     R0, =0xCD98\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB12C0C\n"
	"LDR     R3, =0xC60C\n"
	"LDR     R0, =0x9BE44\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB12C0C\n"
	"BL      sub_FFB1E67C\n"
	"BL      sub_FF8112B0\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"  // !!!
	"MOV     R1, #0x4000\n"
    );    

    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"                    
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFB16D3C\n"
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
	"BL      sub_FFB0AF88\n"    // memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB0BA00\n"    // memPartLibInit
	//"BL      sub_FF8117EC\n"    // nullsub
    "BL      sub_FF811708\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFB0D9A4\n"  // selectInit
    );

    asm volatile
    (	
	"BL      sub_FF811A14\n"
	"BL      sub_FF8119F8\n"
	"BL      sub_FF811A40\n"
	"BL      sub_FFB0D264\n" // selTaskDeleteHookAdd
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

