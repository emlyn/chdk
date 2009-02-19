#include "lolevel.h"
#include "platform.h"
#include "core.h"
extern void ShowCode(int code);
extern void ShowCodeR(int code);
/* These functions need to be taken from the original firmware and addresses need to be modifyed */

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);
const char * const new_sa = &_end;

void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();

void boot()		//done
{
    long *canon_data_src = (void*)0xFFAE7EE0; // This is the address of the "Startofdata"-4 string on the firmware
    long *canon_data_dst = (void*)MEMBASEADDR; // This is where the boot data is copiedduring firmware update
    long canon_data_len = 0xE7D0; // This is the length of data from "Startofdata" to the end of the firmware dump
    long *canon_bss_start = (void*) (canon_data_len + MEMBASEADDR); //  = 0xEB60 + 0x1900,  just after data
    long canon_bss_len = MEMISOSTART - (long) canon_bss_start; // The original address of h_usrKernelInit - bss start
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


void h_usrInit() //done	
{
	asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FF811A40\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFACBB40\n"
	"BL      sub_FFAB8218\n"
	"BL      sub_FF811298\n"
	"BL      sub_FF811800\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
	);
}


void  h_usrKernelInit() //done	 @ 0xFF81181C in dump
{
	asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFACC040\n"
	"BL      sub_FFAE132C\n"
	"LDR     R3, =0xF05C\n"
	"LDR     R2, =0xA4740\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xA7FB0\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFADA17C\n"
	"LDR     R3, =0xF01C\n"
	"LDR     R0, =0xF8E4\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFADA17C\n"
	"LDR     R3, =0xF0D8\n"
	"LDR     R0, =0xA7F84\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFADA17C\n"
	"BL      sub_FFAE5EAC\n"
	"BL      sub_FF811384\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"

	"LDR     R2, =new_sa\n"
	"LDR     R2, [R2]\n"

	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFADE56C\n"
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
	);
}


void  h_usrRoot() // 0xFF811B44 in dump  //done
{
	volatile long *p;
	asm volatile (
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FF811AA8\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFAD21BC\n" // memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFAD2C34\n" // mmPartLibInit <----- OK up to here!!
	//NULLSTUB
	"BL      sub_FF8117DC\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFAD4BD8\n" // selectInit
	"BL      sub_FF811AEC\n"
	"BL      sub_FF811ACC\n"
	"BL      sub_FF811B18\n"
	"BL      sub_FFAD4498\n" //selTaskDeleteHookAdd
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
