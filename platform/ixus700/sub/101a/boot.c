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

extern void mykbd_task_proceed_2();

void __attribute__((naked,noinline)) h_kbd_p2_f()
{
    asm volatile (
                 "LDR     R4, =0xFB10\n"
                 "LDR     R2, [R4,#0x38]\n"
                 "TST     R2, #0x8000\n"
                 "BEQ     loc_FF828F1C\n"
                 "MOV     R2, #0x8000\n"
                 "MOV     R0, #0x2F\n"
                 "MOV     R1, #2\n"
                 "BL      sub_FF8294CC\n"
                 "LDR     R3, [R4,#0x38]\n"
                 "BIC     R3, R3, #0x8000\n"
                 "STR     R3, [R4,#0x38]\n"
                 "MOV     R2, R3\n"
 "loc_FF828F1C:\n"
                 "TST     R2, #2\n"
                 "BEQ     loc_FF828F44\n"
                 "MOV     R1, #2\n"
                 "MOV     R2, R1\n"
                 "MOV     R0, #0x21\n"
                 "BL      sub_FF8294CC\n"
                 "LDR     R3, [R4,#0x38]\n"
                 "BIC     R3, R3, #2\n"
                 "STR     R3, [R4,#0x38]\n"
                 "MOV     R2, R3\n"
 "loc_FF828F44:\n"
                 "TST     R2, #4\n"
                 "BEQ     loc_FF828F6C\n"
                 "MOV     R2, #4\n"
                 "MOV     R0, #0x22\n"
                 "MOV     R1, #2\n"
                 "BL      sub_FF8294CC\n"
                 "LDR     R3, [R4,#0x38]\n"
                 "BIC     R3, R3, #4\n"
                 "STR     R3, [R4,#0x38]\n"
                 "MOV     R2, R3\n"
 "loc_FF828F6C:\n"
                 "ADD     R1, R4, #0x30\n"
                 "LDMIA   R1, {R1,R3}\n"
                 "ADD     R3, R1, R3\n"
                 "CMN     R3, R2\n"
                 "BEQ     loc_FF828F84\n"
                 "BL      sub_FF82952C\n"
 "loc_FF828F84:\n"
                 "LDR     R3, =0x1FCC\n"
                 "LDR     R1, [R3]\n"
                 "CMP     R1, #1\n"
                 "BNE     loc_FF828FA0\n"
                 "MOV     R0, #0\n"
                 "MOV     R2, R1\n"
                 "BL      sub_FF8294CC\n"
 "loc_FF828FA0:\n"
                 "BL      sub_FF829C08\n"
                 "B       mykbd_task_proceed_2\n"
    );
}



void boot()
{
    long *canon_data_src = (void*)0xFFACE9C0;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xD340;
    long *canon_bss_start = (void*)0xEC40; // just after data
    long canon_bss_len = 0x7C2B0 - 0xEC40;
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
	"BL	sub_FFAB50FC\n"
	"BL	sub_FFAA17D4\n"
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
        "BL      sub_FFAB55FC\n"
        "BL      sub_FFAC7E08\n"
        "LDR     R3, =0xE07C\n"
        "LDR     R2, =0x78500\n"
        "LDR     R1, [R3]\n"
        "LDR     R0, =0x7BC70\n"
        "MOV     R3, #0x100\n"
        "BL      sub_FFAC3738\n"
        "LDR     R3, =0xE03C\n"
        "LDR     R0, =0xE45C\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFAC3738\n"
        "LDR     R3, =0xE0F8\n"
        "LDR     R0, =0x7BC44\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFAC3738\n"
        "BL      sub_FFACC988\n"
        "BL      sub_FF811384\n"
        "MOV     R4, #0\n"
        "MOV     R3, R0\n"
        "MOV     R12, #0x800\n"
        "LDR     R0, =h_usrRoot\n"
        "MOV     R1, #0x4000\n"
        "LDR     R2, =0xAC2B0\n"	// 0x7C2B0 + 0x30000
        "STR     R12, [SP]\n"
        "STR     R4, [SP,#4]\n"
        "BL      sub_FFAC5048\n"
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
        "BL      sub_FF811AA8\n"
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFABB778\n"
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFABC1F0\n"
        "BL      sub_FF8118C0\n"
        "BL      sub_FF8117DC\n"
        "MOV     R0, #0x32\n"
        "BL      sub_FFABE194\n"
        "BL      sub_FF811AEC\n"
        "BL      sub_FF811ACC\n"
        "BL      sub_FF811B18\n"
        "BL      sub_FFABDA54\n"
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

