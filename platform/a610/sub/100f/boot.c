#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);


void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();



void boot()
{
    long *canon_data_src = (void*)0xFFED3AA0;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xe910;
    long *canon_bss_start = (void*)0x10210; // just after data
    long canon_bss_len = 0xA0B70 - 0x10210;
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
	"BL      sub_FFC019BC\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFEB7704\n"
	"BL      sub_FFEA3DDC\n"
	"BL      sub_FFC01218\n"
	"BL      sub_FFC0177C\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()
{
    asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFEB7C04\n"
	"BL      sub_FFECCEF0\n"
	"LDR     R3, =0xF1A4\n"
	"LDR     R2, =0x9D200\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xA0530\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFEC5D40\n"
	"LDR     R3, =0xF164\n"
	"LDR     R0, =0xFA2C\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFEC5D40\n"
	"LDR     R3, =0xF220\n"
	"LDR     R0, =0xA0504\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFEC5D40\n"
	"BL      sub_FFED1A70\n"
	"BL      sub_FFC01304\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
    );    
//	"LDR     R2, =0xD0B70\n"	// 0xA0B70 + 0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP,#0x10-0x10]\n"
	"STR     R4, [SP,#0x10-0xC]\n"
	"BL      sub_FFECA130\n"
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
	"BL      sub_FFC01A24\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFEBDD80\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFEBE7F8\n"
	"BL      sub_FFC01758\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFEC079C\n"
	"BL      sub_FFC01A68\n"
	"BL      sub_FFC01A48\n"
	"BL      sub_FFC01A94\n"
	"BL      sub_FFEC005C\n"
	"BL      sub_FFC01A18\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FFC013C0\n"
    );
}

