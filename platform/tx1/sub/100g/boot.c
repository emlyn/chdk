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
void __attribute__((naked,noinline)) h_usrInit(); // Orig. starts at FF81198C
void __attribute__((naked,noinline)) h_usrKernelInit(); // Orig. starts at FF811744
void __attribute__((naked,noinline)) h_usrRoot(); // Orig. starts at FF811A60



void boot()
{

    long *canon_data_src = (void*)0xFFBBE510;  // 0xFF810104
    long *canon_data_dst = (void*)0x1900;      // 0xFF810108
    long canon_data_len = 0xCEA0;              // 0xFF8100F8
    long *canon_bss_start = (void*)(0x1900+0xCEA0);
    long canon_bss_len = 0xB84D0 - (long)canon_bss_start; //0xFF810134
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
	"BL      sub_FF925020\n" 
	"BL      sub_FF918F9C\n" 
	"BL      sub_FF8111C4\n" 	
	"BL      sub_FF811728\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}

void  h_usrKernelInit() 
{
    asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "SUB     SP, SP, #8\n"
                 "BL      sub_FF925520\n" 
                 "BL      sub_FF93564C\n" 
                 "LDR     R3, =0x5720\n"
                 "LDR     R2, =0xB4A80\n"
                 "LDR     R1, [R3]\n"
                 "LDR     R0, =0xB56D0\n"
                 "MOV     R3, #0x100\n"
                 "BL      sub_FF93123C\n" 
                 "LDR     R3, =0x56E0\n"
                 "LDR     R0, =0x5A80\n"
                 "LDR     R1, [R3]\n"
                 "BL      sub_FF93123C\n" 
                 "LDR     R3, =0x579C\n"
                 "LDR     R0, =0xB56A4\n"
                 "LDR     R1, [R3]\n"
                 "BL      sub_FF93123C\n" 
                 "BL      sub_FF939A08\n" 
                 "BL      sub_FF8112AC\n"
                 "MOV     R4, #0\n"
                 "MOV     R3, R0\n"
                 "MOV     R12, #0x800\n"
                 "LDR     R0, =h_usrRoot\n" 
                 "MOV     R1, #0x4000\n"
                 "LDR     R2, =new_sa\n"
                 "LDR     R2, [R2]\n"                    
                 "STR     R12, [SP]\n"
                 "STR     R4, [SP,#4]\n"
                 "BL      sub_FF93288C\n" 
                 "ADD     SP, SP, #8\n"
                 "LDMFD   SP!, {R4,PC}\n"
    );
};



void  h_usrRoot() 
{
    asm volatile (
                 "STMFD   SP!, {R4,R5,LR}\n"
                 "MOV     R5, R0\n"
                 "MOV     R4, R1\n"
                 "BL      sub_FF8119D0\n"
                 "MOV     R1, R4\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF929FD8\n" 
                 "MOV     R1, R4\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FF92AA50\n" 
                 "BL      sub_FF8117E8\n" 
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
                 "B       sub_FF81136C\n" 
    );
}

