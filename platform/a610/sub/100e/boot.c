#include "lolevel.h"
#include "platform.h"
#include "core.h"

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
    long *canon_data_src = (void*)0xFFED3720;
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
	"BL      sub_FFEB737C\n"
	"BL      sub_FFEA3A54\n"
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
	"BL      sub_FFEB787C\n"
	"BL      sub_FFECCB68\n"
	"LDR     R3, =0xF1A4\n"
	"LDR     R2, =0x9D200\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xA0530\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFEC59B8\n"
	"LDR     R3, =0xF164\n"
	"LDR     R0, =0xFA2C\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFEC59B8\n"
	"LDR     R3, =0xF220\n"
	"LDR     R0, =0xA0504\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFEC59B8\n"
	"BL      sub_FFED16E8\n"
	"BL      sub_FFC01304\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
	"LDR     R2, =0xD0B70\n" // 0xA0B70 + 0x30000
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFEC9DA8\n"
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
    );
}

static long drv_struct[16];

static long dh_err()
{
    return -1;
}

static void drv_self_hide()
{
    long drvnum;
    
    drvnum = _iosDrvInstall(dh_err,dh_err,dh_err,dh_err,dh_err,dh_err,dh_err);
    if (drvnum >= 0)
	_iosDevAdd(drv_struct, "A/DISKBOOT.BIN", drvnum);
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
	"BL      sub_FFEBD9F8\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFEBE470\n"
	"BL      sub_FFC0183C\n"
	"BL      sub_FFC01758\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFEC0414\n"
	"BL      sub_FFC01A68\n"
	"BL      sub_FFC01A48\n"
	"BL      sub_FFC01A94\n"
	"BL      sub_FFEBFCD4\n"
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

