#include "lolevel.h"
#include "platform.h"
#include "core.h"

const long new_sa = MEMISOSTART + MEMISOSIZE;

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
	// address of "start of data" string in FW:
    long *canon_data_src = (void*)0xFFB99360;
    long *canon_data_dst = (void*)0x1900;
	// size from "start of data" to the end of FW at FFBA7D40, =E9E0:
    long canon_data_len = 0xE9E0;
    long *canon_bss_start = (void*)0x102E0; // 1900+data_len=102E0
	// R2 before original kernelInit (MEMISOSTART) minus bss_start
	// (kernelInit at FF932E10)
    long canon_bss_len = 0xAC070 - 0x102E0;
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
	"BL      sub_FF9255A4\n"
	"BL      sub_FF91969C\n" //excVecInit
	"BL      sub_FF8111C4\n"
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
	"BL      sub_FF925AA4\n" //classLibInit
	"BL      sub_FF935BD0\n" //taskLibInit
	"LDR     R3, =0x5B20\n"
	"LDR     R2, =0xA90C0\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xA9D10\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FF9317C0\n" //qInit
	"LDR     R3, =0x5AE0\n"
	"LDR     R0, =0x5E80\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FF9317C0\n" //qInit
	"LDR     R3, =0x5B9C\n"
	"LDR     R0, =0xA9CE4\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FF9317C0\n" //qInit
	"BL      sub_FF939F8C\n" //workQInit
	"BL      sub_FF8112AC\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"	// !! has to be here
	"MOV     R1, #0x4000\n"
    );    
//        "LDR     R2, =0xDC070\n"	// !! MEMISOSTART 0xAC070 + MEMISOSIZE 0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FF932E10\n" //kernelInit
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
	"BL      sub_FF8119D0\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FF92A55C\n" //memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FF92AFD4\n" //memPartLibInit
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

