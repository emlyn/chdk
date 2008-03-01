#include "lolevel.h"
#include "platform.h"
#include "core.h"

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
    long *canon_data_src = (void*)0xFFEDA440;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xea30;
    long *canon_bss_start = (void*)0x10330; // just after data
    long canon_bss_len = 0x9F990 - 0x10330;
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
	"BL      sub_FFEBE0A0\n"
	"BL      sub_FFEAA778\n"
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
	"BL      sub_FFEBE5A0\n"
	"BL      sub_FFED388C\n"
	"LDR     R3, =0xF2C4\n"
	"LDR     R2, =0x9C020\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0x9F350\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFECC6DC\n"
	"LDR     R3, =0xF284\n"
	"LDR     R0, =0xFB4C\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFECC6DC\n"
	"LDR     R3, =0xF340\n"
	"LDR     R0, =0x9F324\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFECC6DC\n"
	"BL      sub_FFED840C\n"
	"BL      sub_FFC01304\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
	"LDR     R2, =0xDF990\n"	// 0x9F990 + 0x40000
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFED0ACC\n"
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
	"BL      sub_FFEC471C\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFEC5194\n"
	"BL      sub_FFC01758\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFEC7138\n"
	"BL      sub_FFC01A68\n"
	"BL      sub_FFC01A48\n"
	"BL      sub_FFC01A94\n"
	"BL      sub_FFEC69F8\n"
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

