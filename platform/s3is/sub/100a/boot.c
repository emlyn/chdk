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
    long *canon_data_src = (void*)0xFFB6B240;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xC890;
    long *canon_bss_start = (void*)0xe190; // just after data
    long canon_bss_len = 0x96410 - 0xe190;
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
	"BL      sub_FF81196C\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFB50BA0\n"
	"BL      sub_FFB43814\n"
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
	"BL      sub_FFB510A0\n"
	"BL      sub_FFB648A8\n"
	"LDR     R3, =0xD1A8\n"
	"LDR     R2, =0x92240\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0x95DD0\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFB5D9B8\n"
	"LDR     R3, =0xD168\n"
	"LDR     R0, =0xD9B0\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB5D9B8\n"
	"LDR     R3, =0xD224\n"
	"LDR     R0, =0x95DA4\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB5D9B8\n"
	"BL      sub_FFB69428\n"
	"BL      sub_FF8112B0\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
    );    
//	"LDR     R2, =0xD6410\n"	// 0x96410 + 0x40000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFB61AE8\n"
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
	"BL      sub_FF8119D4\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB55D34\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB567AC\n"
	"BL      sub_FF811708\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFB58750\n"
	"BL      sub_FF811A14\n"
	"BL      sub_FF8119F8\n"
	"BL      sub_FF811A40\n"
	"BL      sub_FFB58010\n"
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

