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


#if 0
void blink_blue(int duration)
{
  int i;

  *((volatile long *) 0xc0220084) = 0x46; // Turn on LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }   
   
  *((volatile long *) 0xc0220084) = 0x44; // Turn off LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }
}

void blink_orange(int duration)
{
  int i;

  *((volatile long *) 0xc0220080) = 0x46; // Turn on LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }   
   
  *((volatile long *) 0xc0220080) = 0x44; // Turn off LED   
  for (i=0; i<duration; i++) // Wait a while   
  {   
    asm volatile ( "nop\n" );   
  }
}

void blink()
{
    blink_blue(10000000);
    blink_orange(10000000);
    blink_blue(10000000);
}
#endif

void boot()
{
    long *canon_data_src = (void*)0xFFEC54F0;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xEBC0 - 0x1900;
    long *canon_bss_start = (void*)0xEBC0; // just after data
    long canon_bss_len = 0x9F7D0 - 0xEBC0;
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
	"BL      sub_FFEAB86C\n"     //unknown_libname_773 ; "Canon A-Series Firmware"
	"BL      sub_FFE9CEDC\n"     //excVecInit
	"BL      sub_FFC011C4\n"
	"BL      sub_FFC01728\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()
{
//    blink();
    asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFEABD6C\n"    //classLibInit
	"BL      sub_FFEBEB54\n"    //taskLibInit
	"LDR     R3, =0xDBD8\n"
	"LDR     R2, =0x9C460\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0x9F190\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFEB7C64\n"   //qInit
	"LDR     R3, =0xDB98\n"
	"LDR     R0, =0xE3E0\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFEB7C64\n"   //qInit
	"LDR     R3, =0xDC54\n"
	"LDR     R0, =0x9F164\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFEB7C64\n"   //qInit
	"BL      sub_FFEC36D4\n"   //workQInit
	"BL      sub_FFC012B0\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
    );
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFEBBD94\n"  //kernelInit
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
	"BL      sub_FFEB0A00\n"     //memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFEB1478\n"     //memPartLibInit
	"BL      sub_FFC017E8\n"     //SetZoomActuatorSpeedPercent
	"BL      sub_FFC01704\n"
	"BL      sub_FFC01A10\n"
	"BL      sub_FFC019F4\n"
	"BL      sub_FFC01A3C\n"
	"BL      sub_FFC019C4\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();
//    blink(); //    "BL      blink\n"

    asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FFC0136C\n"
    );
}
