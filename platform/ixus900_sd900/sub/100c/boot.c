#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

// Ours stuff
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook(void *pNewTcb);
extern void deleteHook(void *pTcb);

void boot();

// "relocated" functions
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();

// setup .data and .bss
void boot() {
    // http://chdk.setepontos.com/index.php/topic,774.msg6347/topicseen.html#msg6347
    long *canon_data_src = (void*)0xFFB6DA40;   // ROM:FF810104
    long *canon_data_dst = (void*)0x1900;   // ROM:FF810108
    long canon_data_len = 0xCC00;   // ROM:FF8100F8
    long *canon_bss_start = (void*)0xE500;   // ROM:FF810130 (canon_data_dst + canon_data_len)
    long canon_bss_len = 0xA4D10 - 0xE500;   // ROM:FF810134 (MEMISOSTART - canon_bss_start)
    //long canon_bss_len = 0xA4D10 - (long)canon_bss_start;
    long i;

    // ROM:FF8100E4 , same as SD800, SD750 and other VxWorks
    asm volatile(
        "MRC     p15, 0, R0,c1,c0\n"
        "ORR     R0, R0, #0x1000\n"
        "ORR     R0, R0, #4\n"
        "ORR     R0, R0, #1\n"
        "MCR     p15, 0, R0,c1,c0\n"
        :::"r0"
    );

    for(i=0; i<canon_data_len/4; i++)
        canon_data_dst[i]=canon_data_src[i];

    for(i=0; i<canon_bss_len/4; i++)
        canon_bss_start[i]=0;

    // ROM:FF81015C , same as SD800, SD750 and other VxWorks
    asm volatile(
        "MRC     p15, 0, R0,c1,c0\n"
        "ORR     R0, R0, #0x1000\n"
        "BIC     R0, R0, #4\n"
        "ORR     R0, R0, #1\n"
        "MCR     p15, 0, R0,c1,c0\n"
        :::"r0"
    );

    h_usrInit();
}

// ROM:FF81198C
void h_usrInit() {
    asm volatile(
        "STR     LR, [SP,#-4]!\n"
        "BL      sub_FF811968\n"
        "MOV     R0, #2\n"
        "MOV     R1, R0\n"
        "BL      sub_FFB54584\n"
        "BL      sub_FFB46DF8\n"     // excVecInit()
        "BL      sub_FF8111C4\n"     // sysInitStack()
        "BL      sub_FF811728\n"
        "LDR     LR, [SP],#4\n"
        "B       h_usrKernelInit\n"
    );
}

// ROM:FF811744 #
void  h_usrKernelInit() {
    asm volatile(
        "STMFD   SP!, {R4,LR}\n"
        "SUB     SP, SP, #8\n"
        "BL      sub_FFB54A84\n"     // classLibInit()
        "BL      sub_FFB6786C\n"     // taskLibInit()
        "LDR     R3, =0xD520\n"
        "LDR     R2, =0xA1960\n"
        "LDR     R1, [R3]\n"
        "LDR     R0, =0xA46D0\n"
        "MOV     R3, #0x100\n"
        "BL      sub_FFB6097C\n"     // qInit()
        "LDR     R3, =0xD4E0\n"
        "LDR     R0, =0xDD28\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFB6097C\n"     // qInit()
        "LDR     R3, =0xD59C\n"
        "LDR     R0, =0xA46A4\n"
        "LDR     R1, [R3]\n"
        "BL      sub_FFB6097C\n"     // qInit()
        "BL      sub_FFB6BC28\n"     // workQInit()
        "BL      sub_FF8112AC\n"
        "MOV     R4, #0\n"
        "MOV     R3, R0\n"
        "MOV     R12, #0x800\n"
        "LDR     R0, =h_usrRoot\n"   // important !!
        "MOV     R1, #0x4000\n"
        "LDR     R2, =new_sa\n"      // skip some memory for later use with CHDK
        "LDR     R2, [R2]\n"         // helps "LDR     R2, =new_sa\n"
        "STR     R12, [SP]\n"
        "STR     R4, [SP,#4]\n"
        "BL      sub_FFB64AAC\n"     // kernelInit()
        "ADD     SP, SP, #8\n"
        "LDMFD   SP!, {R4,PC}\n"
    );
}

void  h_usrRoot() {
    // ROM:FF811A60
    asm volatile(
        "STMFD   SP!, {R4,R5,LR}\n"
        "MOV     R5, R0\n"
        "MOV     R4, R1\n"
        "BL      sub_FF8119D0\n"   // lib_Init()
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFB59718\n"   // memInit()
        "MOV     R1, R4\n"
        "MOV     R0, R5\n"
        "BL      sub_FFB5A190\n"   // memPartLibInit()
        //"BL      sub_FF8117E8\n"   // nullsub_1()
        "BL      sub_FF811704\n"
        "BL      sub_FF811A0C\n"   // tty_Init() (console log)
        //"BL      sub_FF811A0C_my\n"   // tty_Init() (console log)
        "BL      sub_FF8119F0\n"   // env_Init()
        "BL      sub_FF811A38\n"   // stdlog_Init() (logInit)
        "BL      sub_FF8119C4\n"   // show_Init()
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    // ROM:FF811AA0 , same as SD800, SD750
    asm volatile(
        "LDMFD   SP!, {R4,R5,LR}\n"
        "B       sub_FF81136C\n"   // startup_Init()
    );
}

/*
// VxWorks console
// tty_Init
void __attribute__((naked,noinline)) sub_FF811A0C_my(long p) {
    asm volatile (
        "MOV     R0, #0x1000\n"
        "STR     LR, [SP]\n"
        "BL      sub_FF811474\n"   // tty_StartMsg
        "MOV     R1, #0x32\n"
        //"LDR     R2, =aNull\n"   // original
        "LDR     R2, ='/tyCo/0'\n"   // +
        "MOV     R0, #0x14\n"
        "BL      _iosInit\n"
        "BL      sub_FFB5DBB0\n"   // ttyDrv
        "LDR     LR, [SP]\n"
        "B       sub_FF811874\n\n"
    );
*/
