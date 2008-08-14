#include "lolevel.h"
#include "platform.h"
#include "core.h"

/* These functions need to be taken from the original firmware and addresses need to be modifyed */

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);
const long new_sa = MEMISOSTART + MEMISOSIZE;

void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();

extern void mykbd_task_proceed_2();

void boot()
{
    long *canon_data_src = (void*)0xFFAD7700; // This is the address of the "Startofdata" string on the firmware
    long *canon_data_dst = (void*)0x1900; // This is where the boot data is copiedduring firmware update
    long canon_data_len = 0xEB60; // This is the length of data from "Startofdata" to the end of the firmware dump
    long *canon_bss_start = (void*)0x10460; //  = 0xEB60 + 0x1900,  just after data
    long canon_bss_len = 0x72DC0 - 0x10460; // The original address of h_usrKernelInit - bss start
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
	"BL      sub_FF811B20\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFABDC68\n"
	"BL      sub_FFAAA238\n"
	"BL      sub_FF81125C\n"
	"BL      sub_FF811838\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
	);

}

void  h_usrKernelInit()
{
	asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFABE168\n"
	"BL      sub_FFAD0C28\n"
	"LDR     R3, =0xF894\n"
	"LDR     R2, =0x704A0\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0x7278C\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFACC464\n"
	"LDR     R3, =0xF854\n"
	"LDR     R0, =0xFC74\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFACC464\n"
	"LDR     R3, =0xF910\n"
	"LDR     R0, =0x72760\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFACC464\n"
	"BL      sub_FFAD57A8\n"
	"BL      sub_FF811348\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"
	"MOV     R1, #0x4000\n"
	);

	//"LDR     R2, =0xB2DC0\n" // 0x72DC0 + 0x40000
	asm volatile (
	"LDR     R2, =new_sa\n"
	"LDR     R2, [R2]\n"
	);

	asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFACDE68\n"
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
	volatile long *p;
	
	asm volatile (
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FF811BA0\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFAC4450\n" // memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFAC4EC8\n" // mmPartLibInit <----- OK up to here!!
	
	//"BL      sub_FF811928\n" // Here something BAD happens! It initializes the MMU, but SD500 has this replaced by a NULLSUB call...

	"BL      sub_FF811814\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFAC6938\n" // selectInit
	"BL      sub_FF811BE4\n"
	"BL      sub_FF811BC4\n"
	"BL      sub_FF811C10\n"
	"BL      sub_FFAC61F8\n" //selTaskDeleteHookAdd
	"BL      sub_FF811B94\n"
	);
	
    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

	asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FF811408\n"
	);

}

#if CAM_CONSOLE_LOG_ENABLED
typedef struct { 
 	 	    long dev_hdr[4]; 
 	 	    long opened; 
 	 	 
 	 	    long fill[64]; 
 	 	} MY_DEV; 
 	 	 
 	 	#define CONS_W (45) 
 	 	#define CONS_H (128) 
 	 	 
 	 	char console_buf[CONS_H][CONS_W]; 
 	 	long console_buf_line = 0; 
 	 	long console_buf_line_ptr = 0; 
 	 	 
 	 	char cmd[100] = "ShowCameraLog\n\0"; 
 	 	int cons_cmd_ptr = -1; 
 	 	 
 	 	void mytty_putc(char c); 
 	 	 
 	 	int ttyRead(MY_DEV* tty,  char* buffer, int nBytes) 
 	 	{ 
 	 	    int r = 1; 
 	 	 
 	 	    if (cons_cmd_ptr == -1){ 
 	 	        msleep(2000); 
 	 	        cons_cmd_ptr = 0; 
 	 	    } 
 	 	 
 	 	    mytty_putc('r'); 
 	 	     
 	 	    if (cmd[cons_cmd_ptr] != 0){ 
 	 	        *buffer = cmd[cons_cmd_ptr]; 
 	 	        cons_cmd_ptr++; 
 	 	    } else { 
 	 	        while (cons_cmd_ptr != 0){ 
 	 	            msleep(10); 
 	 	        } 
 	 	        *buffer = cmd[cons_cmd_ptr]; 
 	 	        cons_cmd_ptr++; 
 	 	    } 
 	 	 
 	 	    return r; 
 	 	} 
 	 	 
 	 	void mytty_nextline() 
 	 	{ 
 	 	    int i; 
 	 	 
 	 	    console_buf_line_ptr=0; 
 	 	    console_buf_line++; 
 	 	    if (console_buf_line>=CONS_H){ 
 	 	        console_buf_line = 0; 
 	 	    } 
 	 	    for (i=0;i<15;i++){ 
 	 	        int l=i+console_buf_line; 
 	 	        if (l>=CONS_H) 
 	 	            l-=CONS_H; 
 	 	        console_buf[l][0] = 0; 
 	 	    } 
 	 	} 
 	 	 
 	 	void mytty_putc(char c) 
 	 	{ 
 	 	    if (c == 0xa){ 
 	 	        mytty_nextline(); 
 	 	    } else { 
 	 	        if (console_buf_line_ptr>=(CONS_W-1)){ 
 	 	            mytty_nextline(); 
 	 	        } 
 	 	 
 	 	        console_buf[console_buf_line][console_buf_line_ptr++] = c; 
 	 	        console_buf[console_buf_line][console_buf_line_ptr] = 0; 
 	 	    } 
 	 	} 
 	 	 
 	 	int tyWrite = 0xFFACA1E4; //FFB19FF8; 
 	 	
    //ttyWrite seems to work, Read might be broken 
 	 	int ttyWrite(MY_DEV* tty,  char* buffer, int nBytes) 
 	 	{ 
 	 	    int i; 
 	 	 
 	 	    for (i=0;i<nBytes;i++){ 
 	 	        mytty_putc(buffer[i]); 
 	 	    } 
 	 	 
 	 	    return ((int(*)(void *p, void *p2, int l))tyWrite)(tty, buffer, nBytes); 
 	 	//    return nBytes; 
 	 	} 
 	 	 
 	 	 
 	 	/* 
 	 	  Referenced from ttyDrv_init as 
 	 	     LDR     R11, =TTY_DRV_NUM 
 	 	  and ttyDevCreate as 
 	 	     LDR     R9, =TTY_DRV_NUM 
 	 	*/ 
 	 	int *TTY_DRV_NUM = (int*)0x0006F578; 
 	 	 
 	 	static void replaceConsoleDriver() 
 	 	{ 
 	 	    // These function addresses are from ttyDrv_init function call 
 	 	    int f0 = 0xFFAC9274; //0xFFB19088; 
 	 	    int f1 = 0; 
 	 	    int f2 = 0xFFAC9274; //0xFFB19088; 
 	 	    int f3 = 0xFFAC92B4; //0xFFB190C8; 
 	 	    int f6 = 0xFFAC92F8; //0xFFB1910C; 
 	 	    int fRead = (int)&ttyRead; 
 	 	    int fWrite = (int)&ttyWrite; 
 	 	    int newdriver_id = _iosDrvInstall((void*)f0, (void*)f1, (void*)f2, (void*)f3, (void*)fRead, (void*)fWrite, (void*)f6); 
 	 	 
 	 	    *TTY_DRV_NUM = newdriver_id; 
 	 	} 
 	 	 
 	 	void h_ios_tty_Init() 
 	 	{ 
 	 	/* 
 	 	  asm volatile 
 	 	  ( 
 	 	      "MOV     R0, #0x1000" 
 	 	      "BL      sub_FF811478" 
 	 	 
 	 	      "MOV     R1, #0x32"                  
 	 	      "LDR     R2, =aNull" 
 	 	      "MOV     R0, #0x14"                        
 	 	      "BL      iosInit" 
 	 	  ); 
 	 	*/   
 	 	  _iosInit(0x14, 0x32, "/null"); 
 	 	  replaceConsoleDriver(); 
 	   
	 	/*  asm volatile 
	 	  ( 
	 	      "BL      sub_FF811878" 
	 	  ); 
	 	*/ 
	 	} 
#endif
    
