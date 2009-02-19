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
//    long *canon_data_src = (void*)0xFFF2D320;
    long *canon_data_dst = (void*)0x1900;
//    long canon_data_len = 0xBF70;
//    long *canon_bss_start = (void*)0xD870; // just after data
//    long canon_bss_len = 0xA6C30 - 0xD870;
    long i;
    
    long *canon_data_src = (void*)0xFFF182E0;
    long canon_data_len = 0xBC40;
    long *canon_bss_start = (void*)0xD540;
    long canon_bss_len = 0xA6090 - 0xD540;

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
    /*asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FFC01964\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFCD371C\n"
	"BL      sub_FFCC86B0\n"
	"BL      sub_FFC011C4\n"
	"BL      sub_FFC01724\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );*/
    
    asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FFC01964\n"
	"MOV  R0, #2\n"
	"MOV R1, R0\n"
	"BL sub_FFCCB29C\n"
	"BL sub_FFCC0230\n"
	"BL sub_FFC011C4\n"
	"BL sub_FFC01724\n"
	"LDR LR, [SP],#4\n"
	"B h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()
{
    /*asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFCD3C1C\n"
	"BL      sub_FFCE3D48\n"
	"LDR     R3, =0x4FD8\n"
	"LDR     R2, =0xA3B40\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xA4690\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFCDF938\n"
	"LDR     R3, =0x4F98\n"
	"LDR     R0, =0x5338\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFCDF938\n"
	"LDR     R3, =0x5054\n"
	"LDR     R0, =0xA4664\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFCDF938\n"
	"BL      sub_FFCE8104\n"
	"BL      sub_FFC012AC\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
	"LDR     R2, =0xD6C30\n"	// 0xA6C30 + 0x30000
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFCE0F88\n"
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
    );*/
    
    asm volatile (
	"STMFD 	SP!, {R4,LR}\n"
	"SUB 	SP, SP, #8\n"
	"BL 	sub_FFCCB79C\n" //classLibInit
	"BL 	sub_FFCDB8C8\n" //taskLibInit
	"LDR 	R3, =0x4F28\n"
	"LDR 	R2, =0xA3200\n"
	"LDR 	R1, [R3]\n"
	"LDR 	R0, =0xA3D50\n"
	"MOV 	R3, #0x100\n"
	"BL 	sub_FFCD74B8\n" //qInit
	"LDR 	R3, =0x4EE8\n"
	"LDR 	R0, =0x5288\n"
	"LDR 	R1, [R3]\n"
	"BL 	sub_FFCD74B8\n" //qInit
	"LDR 	R3, =0x4FA4\n"
	"LDR 	R0, =0xA3D24\n"
	"LDR 	R1, [R3]\n"
	"BL 	sub_FFCD74B8\n" //QInit
	"BL 	sub_FFCDFC84\n" //workQInit
	"BL 	sub_FFC012AC\n"
	"MOV 	R4, #0\n"
	"MOV 	R3, R0\n"
	"MOV 	R12, #0x800\n"
	"LDR 	R0, =h_usrRoot\n" //sub_FFC01A5C
	"MOV 	R1, #0x4000\n"
    );    
//	"LDR 	R2, =0xD6090\n" //0xA6090+0x30000
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR 	R12, [SP]\n"
	"STR 	R4, [SP,#4]\n"
	"BL 	sub_FFCD8B08\n" //kernelInit
	"ADD 	SP, SP, #8\n"
	"LDMFD 	SP!, {R4,PC}\n"
    );
}


void  h_usrRoot()
{
    /*asm volatile (
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FFC019CC\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFCD86D4\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFCD914C\n"
//	"BL      sub_FFC017E4\n"
	"BL      sub_FFC01700\n"
	"BL      sub_FFC01A08\n"
	"BL      sub_FFC019EC\n"
	"BL      sub_FFC01A34\n"
	"BL      sub_FFC019C0\n"
    );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FFC01368\n"
    );*/
    
    asm volatile (
    	"STMFD 	SP!, {R4,R5,LR}\n"
	"MOV 	R5, R0\n"
	"MOV 	R4, R1\n"
	"BL 	sub_FFC019CC\n"
	"MOV 	R1, R4\n"
	"MOV 	R0, R5\n"
	"BL 	sub_FFCD0254\n" //memInit
	"MOV 	R1, R4\n"
	"MOV 	R0, R5\n"
	"BL 	sub_FFCD0CCC\n" //memPartLibInit
	// "BL nullsub_2\n" // this is empty function, can be removed
	"BL 	sub_FFC01700\n"
	"BL 	sub_FFC01A08\n"
	"BL 	sub_FFC019EC\n"
	"BL 	sub_FFC01A34\n"
	"BL 	sub_FFC019C0\n"
    );
    
    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);
    
    drv_self_hide();

    asm volatile (
	"LDMFD 	SP!, {R4,R5,LR}\n"
	"B 	sub_FFC01368\n\n"
    );
}





