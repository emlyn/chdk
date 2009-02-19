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
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();



void boot()
{
    long *canon_data_src = (void*)0xFFB74640;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xCBB0;
    long *canon_bss_start = (void*)0xE4B0; // 1900+data_len=E4B0
    long canon_bss_len = 0xBA7B0 - 0xE4B0;
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


void h_usrInit()
{
    asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FF811968\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFB5B17C\n"
	"BL      sub_FFB4D9A4\n" //excVecInit
	"BL      sub_FF8111C4\n" // sysInitStack
	"BL      sub_FF811728\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n" // !! has to be here
    );
}

void  h_usrKernelInit()
{
    asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFB5B67C\n" //classLibInit
	"BL      sub_FFB6E464\n" //taskLibInit
	"LDR     R3, =0xD4C8\n"
	"LDR     R2, =0xB7200\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xBA170\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFB67574\n" //qInit
	"LDR     R3, =0xD488\n"
	"LDR     R0, =0xDCD0\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB67574\n" //qInit
	"LDR     R3, =0xD544\n"
	"LDR     R0, =0xBA144\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB67574\n" //qInit
	"BL      sub_FFB72820\n" //workQInit
	"BL      sub_FF8112AC\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n" // R0, =sub_FF811A60 (h_usrRoot))
	"MOV     R1, #0x4000\n"
    );    
//        "LDR     R2, =0xEA7B0\n"	// 0xBA7B0 + 0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFB6B6A4\n" //kernelInit
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
    );
}



void  h_usrRoot()
{
    asm volatile (
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FF8119D0\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB60310\n" //memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB60D88\n" //memPartLibInit
//	"BL      sub_FF8117E8\n" // nullsub 3
	"BL      sub_FF811704\n"
	"BL      sub_FF811A0C\n"
	"BL      sub_FF8119F0\n"
	"BL      sub_FF811A38\n"
	"BL      sub_FF8119C4\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FF81136C\n" //IsEmptyWriteCache_2
    );
}

