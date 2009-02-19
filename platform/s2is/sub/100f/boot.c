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

extern void mykbd_task_proceed_2();


void __attribute__((naked,noinline)) h_kbd_p2_f()
{
    asm volatile (
                 "LDR     R4, =0x10390\n"
                 "LDR     R1, [R4,#0x30]\n"
                 "TST     R1, #0x8000\n"
                 "BEQ     loc_FF829394\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, #0xF\n"
                 "MOV     R2, #0x8000\n"
                 "BL      sub_FF829978\n"
                 "LDR     R3, [R4,#0x30]\n"
                 "BIC     R3, R3, #0x8000\n"
                 "STR     R3, [R4,#0x30]\n"
                 "MOV     R1, R3\n"
  "loc_FF829394:\n"
                 "TST     R1, #1\n"
                 "BEQ     loc_FF8293BC\n"
                 "MOV     R0, #0\n"
                 "MOV     R1, R0\n"
                 "MOV     R2, R5\n"
                 "BL      sub_FF829978\n"
                 "LDR     R3, [R4,#0x30]\n"
                 "BIC     R3, R3, #1\n"
                 "STR     R3, [R4,#0x30]\n"
                 "MOV     R1, R3\n"
  "loc_FF8293BC:\n"
                 "TST     R1, #2\n"
                 "BEQ     loc_FF8293E4\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R5\n"
                 "MOV     R2, #2\n"
                 "BL      sub_FF829978\n"
                 "LDR     R3, [R4,#0x30]\n"
                 "BIC     R3, R3, #2\n"
                 "STR     R3, [R4,#0x30]\n"
                 "MOV     R1, R3\n"
  "loc_FF8293E4:\n"
                 "LDR     R3, [R4,#0x34]\n"
                 "LDR     R2, [R4,#0x38]\n"
                 "ADD     R3, R1, R3\n"
                 "CMN     R3, R2\n"
                 "BEQ     loc_FF8293FC\n"
                 "BL      sub_FF8299D8\n"
  "loc_FF8293FC:\n"
                 "LDR     R3, =0x1FC0\n"
                 "LDR     R1, [R3]\n"
                 "CMP     R1, #1\n"
                 "BNE     loc_FF829418\n"
                 "MOV     R0, #0x28\n"
                 "MOV     R2, #0x100\n"
                 "BL      sub_FF829978\n"
  "loc_FF829418:\n"
                 "LDR     R3, =0x1038C\n"
                 "LDR     R0, [R3]\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF829440\n"
                 "MOV     R3, #0x30\n"
                 "STRH    R3, [SP,#2]\n"
                 "MOV     R1, R6\n"
                 "LDR     R3, =0x103F0\n"
                 "MOV     LR, PC\n"
                 "LDR     PC, [R3]\n"
  "loc_FF829440:\n"
                 "BL      sub_FF82A37C\n"
                 "B       mykbd_task_proceed_2\n"
    );
}


void boot()
{
    long *canon_data_src = (void*)0xFFB09320;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xDBB0;
    long *canon_bss_start = (void*)0xF4B0; // just after data
    long canon_bss_len = 0x6EF50 - 0xF4B0;
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
	"BL	sub_FFAEFA60\n"
	"BL	sub_FFADC138\n"
	"BL	sub_FF811298\n"
	"BL	sub_FF811800\n"
	"LDR	LR, [SP],#4\n"
	"B	h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()
{
    asm volatile (
	"STMFD	SP!, {R4,LR}\n"
	"SUB	SP, SP, #8\n"
	"BL	sub_FFAEFF60\n"
	"BL	sub_FFB0276C\n"
	"LDR	R3, =0xE8EC\n"
	"LDR	R2, =0x6A2C0\n"
	"LDR	R1, [R3]\n"
	"LDR	R0, =0x6E910\n"
	"MOV	R3, #0x100\n"
	"BL	sub_FFAFE09C\n"
	"LDR	R3, =0xE8AC\n"
	"LDR	R0, =0xECCC\n"
	"LDR	R1, [R3]\n"
	"BL	sub_FFAFE09C\n"
	"LDR	R3, =0xE968\n"
	"LDR	R0, =0x6E8E4\n"
	"LDR	R1, [R3]\n"
	"BL	sub_FFAFE09C\n"
	"BL	sub_FFB072EC\n"
	"BL	sub_FF811384\n"
	"MOV	R4, #0\n"
	"MOV	R3, R0\n"
	"MOV	R12, #0x800\n"
	"LDR	R0, =h_usrRoot\n"
	"MOV	R1, #0x4000\n"
    );    
//	"LDR	R2, =0x9EF50\n"	// 0x6EF50 + 0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR	R12, [SP]\n"
	"STR	R4, [SP,#4]\n"
	"BL	sub_FFAFF9AC\n"
	"ADD	SP, SP, #8\n"
	"LDMFD	SP!, {R4,PC}\n"
    );
}



void  h_usrRoot()
{
    asm volatile (
	"STMFD	SP!, {R4,R5,LR}\n"
	"MOV	R5, R0\n"
	"MOV	R4, R1\n"
	"BL	sub_FF811AA8\n"
	"MOV	R1, R4\n"
	"MOV	R0, R5\n"
	"BL	sub_FFAF60DC\n"
	"MOV	R1, R4\n"
	"MOV	R0, R5\n"
	"BL	sub_FFAF6B54\n"
	"BL	sub_FF8118C0\n"
	"BL	sub_FF8117DC\n"
	"MOV	R0, #0x32\n"
	"BL	sub_FFAF8AF8\n"
	"BL	sub_FF811AEC\n"
	"BL	sub_FF811ACC\n"
	"BL	sub_FF811B18\n"
	"BL	sub_FFAF83B8\n"
	"BL	sub_FF811A9C\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    asm volatile (
	"LDMFD	SP!, {R4,R5,LR}\n"
	"B	sub_FF811444\n"
    );
}

