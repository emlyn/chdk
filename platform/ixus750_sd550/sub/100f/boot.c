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
    long *canon_data_src = (void*)0xFFAEAEF0;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xEA00;
    long *canon_bss_start = (void*)0x10300; // just after data
    long canon_bss_len = 0x9f5B0 - 0x10300;
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
	"STR	LR, [SP,#-4]!\n"
	"BL	sub_FF811A40\n"
	"MOV	R0, #2\n"
	"MOV	R1, R0\n"
	"BL	sub_FFACEB54\n"
	"BL	sub_FFABB22C\n"
	"BL	sub_FF811298\n"
	"BL	sub_FF811800\n"
	"LDR	LR, [SP],#4\n"
	"B	h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()
{
    asm volatile (
        "STMFD   SP!, {R4,LR}\n"
        "SUB     SP, SP, #8\n"
        "BL      sub_FFACF054\n" //classlibinit
        "BL      sub_FFAE4340\n" //tasklibinit
        "LDR     R3, =0xf294\n"
        "LDR     R2, =0x9b6a0\n"
        "LDR     R1, [R3]\n"
        "LDR     R0, =0x9ef70\n"
        "MOV     R3, #0x100\n"
        "BL      sub_FFADD190\n" //qinit
        "LDR     R3, =0xf254\n"
        "LDR     R0, =0xfb1c\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFADD190\n" //qinit
        "LDR     R3, =0xf310\n"
        "LDR     R0, =0x9ef44\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFADD190\n" //qinit
        "BL      sub_FFAE8EC0\n" //workqinit
        "BL      sub_FF811384\n"
        "MOV     R4, #0\n"
        "MOV     R3, R0\n"
        "MOV     R12, #0x800\n"
        "LDR     R0, =h_usrRoot\n"
        "MOV     R1, #0x4000\n"
    );
//        "LDR     R2, =0xAC2B0\n"	// 0x7C2B0 + 0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
        "STR     R12, [SP]\n"
        "STR     R4, [SP,#4]\n"
        "BL      sub_FFAE1580\n" //kernelinit
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
        "BL      sub_FF811AA8\n"
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFAD51D0\n" //meminit
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFAD5C48\n" //mempartlibinit
        "BL      sub_FF8118C0\n"
        "BL      sub_FF8117DC\n"
        "MOV     R0, #0x32\n"
        "BL      sub_FFAD7BEC\n" //selectinit
        "BL      sub_FF811AEC\n"
        "BL      sub_FF811ACC\n"
        "BL      sub_FF811B18\n"
        "BL      sub_FFAD74AC\n" //seltaskdeletehookadd
        "BL      sub_FF811A9C\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    asm volatile (
        "LDMFD   SP!, {R4,R5,LR}\n"
        "B       sub_FF811444\n"
    );
}
