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

void __attribute__((naked,noinline)) _platformsub_kbd_fetch_data_my(){
 asm volatile (
                 "STMFD   SP!, {R4-R11,LR}\n"
                 "MOV     LR, #0x220000\n"
                 "ORR     R3, LR, #0x204\n"
                 "LDR     R1, =0xFBE4\n"
                 "ORR     R3, R3, #0xC0000000\n"
            //   "LDR     R9, [R3]\n"                // -

            //my code here
                 "MOV     R2, R0\n"
                 "LDR     R0, [R3]\n" 
                 "STMFD   SP!, {R1-R11}\n"  
                 "BL      usb_power_status_override\n"
                 "LDMFD   SP!, {R1-R11}\n"
                 "MOV     R9, R0\n"
                 "MOV     R0, R2\n"
                 "MOV     LR, #0x220000\n"
            //original code


                 "LDR     R6, [R1]\n"
                 "LDR     R4, =0xFB78\n"
                 "LDR     R1, [R0,#0x1C]\n"
                 "MOV     R10, R6,LSL#2\n"
                 "AND     R1, R9, R1\n"
                 "ADD     R12, R4, #0x20\n"
                 "SUB     R8, R6, #1\n"
                 "SUB     R7, R6, #2\n"
                 "STR     R1, [R12,R10]\n"
                 "AND     R8, R8, #7\n"
                 "AND     R7, R7, #7\n"
                 "MOV     R8, R8,LSL#2\n"
                 "MOV     R7, R7,LSL#2\n"
                 "LDR     R2, =0xFBD8\n"
                 "LDR     R5, [R12,R7]\n"
                 "LDR     R12, [R12,R8]\n"
                 "LDR     R3, [R2,#4]\n"
                 "EOR     R11, R1, R12\n"
                 "EOR     R12, R1, R5\n"
                 "ORR     R12, R11, R12\n"
                 "EOR     R2, R3, R1\n"
                 "STR     R1, [R0,#0x10]\n"
                 "BIC     R2, R2, R12\n"
                 "LDR     R1, =0xFBD8\n"
                 "EOR     R3, R3, R2\n"
                 "STR     R3, [R1,#4]\n"
                 "STR     R2, [R0,#0x34]\n"
                 "STR     R9, [R0,#0x58]\n"
                 "ORR     R3, LR, #0x208\n"
                 "ORR     R3, R3, #0xC0000000\n"
                 "LDR     R1, [R3]\n"
            //my code here
                 "MOV     R2, R0\n"
                 "MOV     R0, R1\n"
                 "STMFD   SP!, {R1-R11}\n"  
                 "BL      my_kbd_read_keys\n"
                 "LDMFD   SP!, {R1-R11}\n"
                 "MOV     R1,R0\n"
                 "MOV     R0,R2\n"
                 "MOV     LR, #0x220000\n"
            //original code
                 "MOV     R2, #0xFF00\n"
                 "ADD     R2, R2, #0xFF\n"
                 "ADD     R4, R4, #0x40\n"
                 "AND     R2, R1, R2\n"
                 "STR     R2, [R4,R10]\n"
                 "ADD     LR, LR, #0x3000\n"
                 "STR     R1, [R0,#0x5C]\n"
                 "ADD     R1, LR, #0xC000001C\n"
                 "LDR     R3, [R1]\n"
                 "AND     R3, R3, #1\n"    
                 "ORR     R2, R2, R3,LSL#16\n"
                 "STR     R2, [R4,R10]\n"
                 "ADD     LR, LR, #0xC0000024\n"
                 "LDR     R3, [LR]\n"
                 "LDR     R1, [R0,#0x20]\n"

              // "AND     R3, R3, #1\n"
                 "AND     R3, R3, #0\n"    // - clear SD card R/O flag

                 "ORR     R2, R2, R3,LSL#17\n"
                 "AND     R2, R2, R1\n"
                 "STR     R2, [R4,R10]\n"
                 "LDR     R3, [R4,R8]\n"
                 "LDR     LR, [R4,R7]\n"
                 "LDR     R4, =0xFBD8\n"
                 "LDR     R1, [R4,#8]\n"
                 "EOR     R11, R2, R3\n"
                 "EOR     R12, R2, LR\n"
                 "EOR     R3, R1, R2\n"
                 "ORR     R12, R11, R12\n"
                 "BIC     R3, R3, R12\n"
                 "EOR     R1, R1, R3\n"
                 "ADD     R6, R6, #1\n"
                 "STR     R2, [R0,#0x14]\n"
                 "STR     R1, [R4,#8]\n"
                 "LDR     R1, =0xFBE4\n"
                 "AND     R6, R6, #7\n"
                 "STR     R6, [R1]\n"
                 "STR     R3, [R0,#0x38]\n"
                 "LDMFD   SP!, {R4-R11,PC}\n"
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
    );
//        "LDR     R2, =0xAC2B0\n"	// 0x7C2B0 + 0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
        "STR     R12, [SP]\n"
        "STR     R4, [SP,#4]\n"
        "BL      sub_FFAC5048\n"
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

