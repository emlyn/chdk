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
    long *canon_data_src = (void*)0xFFEDE3C0;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xB8D0;
    long *canon_bss_start = (void*)0xD1D0;
    long canon_bss_len = 0x91C70 - 0xD1D0;
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
		"BL      sub_FFC01968\n"
		"MOV     R0, #2\n"
		"MOV     R1, R0\n"
		"BL      sub_FFEC4EF8\n"
		"BL      sub_FFEB7BC0\n"
		"BL      sub_FFC011C4\n"
		"BL      sub_FFC01728\n"
		"LDR     LR, [SP],#4\n"
		//"B       loc_FFC01744\n"
		"B       h_usrKernelInit\n"
	);
}

void  h_usrKernelInit()
{
    asm volatile (
		"STMFD   SP!, {R4,LR}\n"
		"SUB     SP, SP, #8\n"
		"BL      sub_FFEC53F8\n"
		"BL      sub_FFED81E0\n"
		"LDR     R3, =0xC1E8\n"
		"LDR     R2, =0x8E7C0\n"
		"LDR     R1, [R3]\n"
		"LDR     R0, =0x91630\n"
		"MOV     R3, #0x100\n"
		"BL      sub_FFED12F0\n"
		"LDR     R3, =0xC1A8\n"
		"LDR     R0, =0xC9F0\n"
		"LDR     R1, [R3]\n"
		"BL      sub_FFED12F0\n"
		"LDR     R3, =0xC264\n"
		"LDR     R0, =0x91604\n"
		"LDR     R1, [R3]\n"
		"BL      sub_FFED12F0\n"
		"BL      sub_FFEDC59C\n"
		"BL      sub_FFC012B0\n"
		"MOV     R4, #0\n"
		"MOV     R3, R0\n"
		"MOV     R12, #0x800\n"
		"LDR     R0, =h_usrRoot\n"
		"MOV     R1, #0x4000\n"
        );    
//                "LDR     R2, =0xD1C70\n"	//0x91c70 + 0x40000
        asm volatile (
            "LDR     R2, =new_sa\n"
            "LDR     R2, [R2]\n"
        );
        asm volatile (
		"STR     R12, [SP]\n"
		"STR     R4, [SP,#4]\n"
		"BL      sub_FFED5420\n"
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
		"BL      sub_FFC019D0\n"
		"MOV     R1, R4\n"
		"MOV     R0, R5\n"
		"BL      sub_FFECA08C\n"
		"MOV     R1, R4\n"
		"MOV     R0, R5\n"
		"BL      sub_FFECAB04\n"
		//"BL      nullsub_1\n"
		"BL      sub_FFC01704\n"
		"BL      sub_FFC01A0C\n"
		"BL      sub_FFC019F0\n"
		"BL      sub_FFC01A38\n"
		"BL      sub_FFC019C4\n"
    );
    
    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);
    
    drv_self_hide();

    asm volatile (
		"LDMFD   SP!, {R4,R5,LR}\n"
		"B       sub_FFC0136C\n"
	);
}





