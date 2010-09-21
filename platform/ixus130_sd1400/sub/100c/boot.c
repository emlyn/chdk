#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define LED 0xC0220130 // IO, green
#define DELAY 5000000

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
long aHookList[128];
long aHookNum=0;


// Forward declarations
void CreateTask_spytask();
void boot();

//void __attribute__((naked,noinline)) sub_STUB_my() {
//	asm volatile (
//	"nop\n"
//	);
//}

void taskCreateHook(int *p) {

	int i;
	int found=0;

	if (aHookNum < 126)
	{
		if (*(p-17) > 0xff810000)
		{
			found=0;
			for (i=0;i<aHookNum;i++)
			{
                          if (aHookList[i]==(long)p)
				{
					found=1;
				}
			}
			if (found==0)
			{
                          aHookList[aHookNum]=(long)p;
			aHookNum++;
			}
		}

	}
	 p-=17;

//VERIFY_SD780 - MORE?
// if (p[0]==0x)  p[0]=(int)capt_seq_task;
//Corrected by JHARP - if (p[0]==0xFF91A6AC)  p[0]=(int)movie_record_task;
// task_InitFileModules
//if (p[0]==0xFF85D754) p[0]=(int)capt_seq_task;

//???if (p[0]==0xFF899CC4) p[0]=(int)exp_drv_task;
//???if (p[0]==0xFF91A6AC) p[0]=(int)movie_record_task;
//???if (p[0]==0xFF877DD0) p[0]=(int)init_file_modules_task;

//if (p[0]==0xFF877F84) p[0]=(int)init_file_modules_task;
/*
loc:  2f34f4 - data:ff8a6368 - *data:      AFTask
loc:  2f2d14 - data:ff845914 - *data:      ASIF
loc:  2f34a - data:ff8a57b8 - *data:       AfIntSrvTask
loc:  2f287c - data:ff843884 - *data:      AudioTsk
loc:  2f2d68 - data:ff8411cc - *data:      BeepTask
loc:  2f36ec - data:ff8944f - *data:       BrtMsrTask
loc:  2f2f6 - data:ff828c7c - *data:       Bye
loc:  2f2bc4 - data:ff916cc - *data:       CZ
loc:  2f2fc - data:ff85dc98 - *data:       CaptSeqTask
loc:  2f3adc - data:ff8a12f - *data:       ChaceFace
loc:  2f38 - data:ff877f94 - *data:        CommonDrivers
loc:  2f3c8 - data:ff81be8 - *data:        ConsoleSvr
loc:  2f2e1 - data:ff8733 - *data:         CtrlSrv
loc:  2f314 - data:ff8f449 - *data:        DPOFTask
loc:  2f3f2 - data:ff87fd1c - *data:       DSITask
loc:  2f3b84 - data:ff89f48 - *data:       DetectMoveTask
loc:  2f33a4 - data:ff9a473c - *data:      DetectVerticalWound
loc:  2f335 - data:ff8a32ac - *data:       DevelopModule
loc:  2f3b3 - data:ff8a12fc - *data:       DispFace
loc:  2f3bd8 - data:ff86de34 - *data:      EvShel
loc:  2f3698 - data:ff9ad1d8 - *data:      ExpDrvSubTask
loc:  2f3644 - data:ff89b12c - *data:      ExpDrvTask
loc:  2f3f74 - data:ff87fb4c - *data:      FaceFrame
loc:  2f32 - data:ff8e3848 - *data:        Fencing
loc:  2f2a74 - data:ff9115bc - *data:      FocusLens
loc:  2f389 - data:ff8ef34 - *data:        FolderCreateCheckTask
loc:  2f3b - data:ff84f6dc - *data:        FsIoNotifyTask
loc:  2f28d - data:ff8419fc - *data:       HdmiDriverTask
loc:  2f2c18 - data:ff917acc - *data:      ISComTask
loc:  2f3cd4 - data:ff858aac - *data:      ISMainTask
loc:  2f2924 - data:ff834e - *data:        ImageSensorTask
loc:  2f2cc - data:ff855d8 - *data:        ImgPlayDrv
loc:  2f35c - data:ff877f84 - *data:       InitFileModules
loc:  2f2c6c - data:ff8426d - *data:       LEDCon
loc:  2f32fc - data:ff9e365 - *data:       LiveImageTask
loc:  2f3c2c - data:ff81bdfc - *data:      LowConsole
loc:  2f3938 - data:ff8f1814 - *data:      MetaCtg
loc:  2f3254 - data:ff8cd67 - *data:       MotionVector
loc:  2f359c - data:ff89e178 - *data:      OBCtrlTask
loc:  2f2e64 - data:ff821c78 - *data:      PhySw
loc:  2f3a88 - data:ff8b24d8 - *data:      PrcssFil
loc:  2f272c - data:ff852fc - *data:       SD1stInit
loc:  2f32a8 - data:ff8cedd4 - *data:      SceneDetectTask
loc:  2f3d28 - data:ff85cbf - *data:       SsStartupTask
loc:  2f2eb8 - data:ff86391 - *data:       SsTask
loc:  2f3e24 - data:ff8ab714 - *data:      SsgMainTask
loc:  2f3e78 - data:ff8ab72 - *data:       SsgPeriodTask
loc:  2f35f - data:ff829574 - *data:       StartupImage
loc:  2f344c - data:ff8b2a1c - *data:      SyncPeriod
loc:  2f33f8 - data:ff8b2a1 - *data:       SynchTask
loc:  2f2fb4 - data:ff82984 - *data:       TempCheck
loc:  2f3dd - data:ff8af358 - *data:       TgTask
loc:  2f2978 - data:ff8462 - *data:        Thermometer
loc:  2f3a34 - data:ff89d334 - *data:      WBCtrl
loc:  2f3548 - data:ff88e4c - *data:       WBIntegTask
loc:  2f3ecc - data:ff9bde7 - *data:       WBLPFace
loc:  2f2828 - data:ff86d9 - *data:        WdtPrint
loc:  2f27d4 - data:ff86d84 - *data:       WdtReset
loc:  2f29cc - data:ff9168ac - *data:      ZoomLens
loc:  2f2dbc - data:ff8645b - *data:       errLogTask
 */

}

// ??? from sx10
void taskCreateHook2(int *p) {
 p-=17;
 //VERIFY_SD780 - Does this need to be here at all anymore?
//Uncomment if (p[0]==0xFF881534)  p[0]=(int)init_file_modules_task;
 //???if (p[0]==0xFF877DD0) p[0]=(int)init_file_modules_task;
}

#if 0
int dumpCF90_SD7802() {

#define START_ADDRESS     0xCF00
#define START_ADDRESS2     0x1900
#define FWSIZE            0x3FF
char j[32];
int jF;

	void* l;
	char filen[32];

	l=(void*)Fopen_Fut("A/0xCF90a.bin","ab");
	Fwrite_Fut(START_ADDRESS,1,FWSIZE,l);
	Fflush_Fut(l);
	Fclose_Fut(l);
	l=(void*)Fopen_Fut("A/0xCF90b.bin","ab");
	Fwrite_Fut(START_ADDRESS2,1,FWSIZE,l);
	Fflush_Fut(l);
	Fclose_Fut(l);

	//jF = open("/_term", O_RDONLY,0777);
	//getc()
	//sprintf(filen, "open(%8x)", jF);

	//draw_txt_string(20, 12, filen, conf.osd_color);

	//		int fd;

		//	script_console_add_line(buf);
		//	script_console_draw();

		//char filen=malloc(16);
		//int i;
		//for (i=0x4; i>0; i = i << 1) {
		//	sprintf(filen, "A/crash_%i_.log", i);
		//	fd = open("A/crash.log", O_WRONLY|O_CREAT|O_APPEND, 0777);
		//	write(fd, buf, len);
//			close(jF);



//	char *Tfilename = (char*) 0xFF814E64;


//	l=(void*)Fopen_Fut(Tfilename,"r");
//	Fread_Fut(j,1,31,l);
//	draw_txt_string(26, 14, j, conf.osd_color);
	//Fclose_Fut(l);
	//save_rom_log();
	return 0;
}


void __attribute__((naked,noinline)) task_blinker() {

int i;
_SleepTask(5000);
		while(1){
			draw_txt_string(27, 12, "Str_ShowAllTaskInfo", 200);
			dumpCF90_SD7802();
			_SleepTask(1000);
			draw_txt_string(27, 12, "End_ShowAllTaskInfo", 200);
		}
};

void CreateTask_blinker() {
        _CreateTask("Blinker", 0x1, 0x200, task_blinker, 0);
};
#endif

void boot() {
  asm volatile (
    "MRC     p15, 0, R0,c1,c0\n"
    "ORR     R0, R0, #0x1000\n"
    "ORR     R0, R0, #4\n"
    "ORR     R0, R0, #1\n"
    "MCR     p15, 0, R0,c1,c0\n"

    //"b       sub_FF810000\n"

    "ldr	r1, =0xc0410000\n"
    "mov	r0, #0\n"//	; 0x0
    "str	r0, [r1]\n"
    "mov	r1, #120\n"//	; 0x78
    "mcr	15, 0, r1, cr1, cr0, 0\n"
    "mov	r1, #0\n"//	; 0x0
    "mcr	15, 0, r1, cr7, cr10, 4\n"
    "mcr	15, 0, r1, cr7, cr5, 0\n"
    "mcr	15, 0, r1, cr7, cr6, 0\n"
    "mov	r0, #61\n"//	; 0x3d
    "mcr	15, 0, r0, cr6, cr0, 0\n"
    "mov	r0, #0xc000002f\n"
    "mcr	15, 0, r0, cr6, cr1, 0\n"
    "mov	r0, #51\n"//	; 0x33
    "mcr	15, 0, r0, cr6, cr2, 0\n"
    "mov	r0, #0x40000033\n"
    "mcr	15, 0, r0, cr6, cr3, 0\n"
    "mov	r0, #0x80000017\n"
    "mcr	15, 0, r0, cr6, cr4, 0\n"
    "ldr	r0, =0xff80002d\n" 
    "mcr	15, 0, r0, cr6, cr5, 0\n"
    "mov	r0, #52\n"//	; 0x34
    "mcr	15, 0, r0, cr2, cr0, 0\n"
    "mov	r0, #52\n"//	; 0x34
    "mcr	15, 0, r0, cr2, cr0, 1\n"
    "mov	r0, #52\n"//	; 0x34
    "mcr	15, 0, r0, cr3, cr0, 0\n"
    "ldr	r0, =0x03333330\n" 
    "mcr	15, 0, r0, cr5, cr0, 2\n"
    "ldr	r0, =0x03333330\n" 
    "mcr	15, 0, r0, cr5, cr0, 3\n"
    "mrc	15, 0, r0, cr1, cr0, 0\n"
    "orr	r0, r0, #4096\n"//	; 0x1000
    "orr	r0, r0, #4\n"//	; 0x4
    "orr	r0, r0, #1\n"//	; 0x1
    "mcr	15, 0, r0, cr1, cr0, 0\n"
    "mov	r1, #0x80000006\n"
    "mcr	15, 0, r1, cr9, cr1, 0\n"
    "mov	r1, #6\n"//	; 0x6
    "mcr	15, 0, r1, cr9, cr1, 1\n"
    "mrc	15, 0, r1, cr1, cr0, 0\n"
    "orr	r1, r1, #0x50000\n"
    "mcr	15, 0, r1, cr1, cr0, 0\n"
    "ldr	r2, =0xc0200000\n" 
    "mov	r1, #1\n"//	; 0x1
    "str	r1, [r2, #268]\n"
    "mov	r1, #255\n"//	; 0xff
    "str	r1, [r2, #12]\n"
    "str	r1, [r2, #28]\n"
    "str	r1, [r2, #44]\n"
    "str	r1, [r2, #60]\n"
    "str	r1, [r2, #76]\n"
    "str	r1, [r2, #92]\n"
    "str	r1, [r2, #108]\n"
    "str	r1, [r2, #124]\n"
    "str	r1, [r2, #140]\n"
    "str	r1, [r2, #156]\n"
    "str	r1, [r2, #172]\n"
    "str	r1, [r2, #188]\n"
    "str	r1, [r2, #204]\n"
    "str	r1, [r2, #220]\n"
    "str	r1, [r2, #236]\n"
    "str	r1, [r2, #252]\n"
    "ldr	r1, =0xc0400008\n" 
    "ldr	r2, =0x00430005\n" 
    "str	r2, [r1]\n"
    "mov	r1, #1\n"//	; 0x1
    "ldr	r2, =0xc0243100\n" 
    "str	r2, [r1]\n"
    "ldr	r2, =0xc0242010\n" 
    "ldr	r1, [r2]\n"
    "orr	r1, r1, #1\n"//	; 0x1
    "str	r1, [r2]\n"

    //"B          sub_ff810130\n" // works with this
    "ldr	r0, =0xffbf837c\n"
    "B          sub_ff810134\n" // fails with this

    "ldr	r1, =0x1900\n"
    "ldr	r3, =0xebd0\n"
"loc_FF81013C:\n"
    "cmp	r1, r3\n"
    "ldrcc	r2, [r0], #4\n"
    "strcc	r2, [r1], #4\n"
    "bcc	loc_FF81013C\n"
    "ldr	r1, =0x14fe20\n" 
    "mov	r2, #0\n"//	; 0x0
"loc_FF810154:\n"
    "cmp	r3, r1\n"
    "strcc	r2, [r3], #4\n"
    "bcc	loc_FF810154\n"
    "b  	sub_FF810354\n"
    );
}

void boot_old() { //#fs
    long *canon_data_src = (void*)0xFFBF837C;  	//From end of first function
    long *canon_data_dst = (void*)0x1900;		//From end of first function
    long canon_data_len = 0xEBD0 - 0x1900; 		// data_end - data_start
    long *canon_bss_start = (void*)0xEBD0; 		// just after data
    long canon_bss_len = 0x14FE20 - 0xEBD0;		//In loop at end of first function

    long i;

    volatile unsigned *p = (void*)LED;
    int counter;
    counter = DELAY/16; *p = 0x46; while (counter--) { asm("nop\n nop\n"); };
    counter = DELAY/16; *p = 0x44; while (counter--) { asm("nop\n nop\n"); };

    // enable caches and write buffer... this is a carryover from old dryos ports, may not be useful
    // SD780 still has this in first function VERIFY_SD780
    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
        "B       sub_ff810000\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
        canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
        canon_bss_start[i]=0;

// see http://chdk.setepontos.com/index.php/topic,2972.msg30712.html#msg30712

    //*(int*)0x1934=(int)taskCreateHook;
    //*(int*)0x1938=(int)taskCreateHook2; //VERIFY_SD780

    // IXUS130: Found at FF85F3F0
	/*
//	ROM:FF842A90 sub_FF842A90                            ; CODE XREF: sub_FF821B7Cj
//	ROM:FF842A90                 STMFD   SP!, {R4,LR}
//	ROM:FF842A94                 LDR     R4, =0x2480     // was 0x2278
//	ROM:FF842A98                 MOV     R0, #0
//	ROM:FF842A9C                 STR     R0, [R4]        // was [R4,#4]
//	ROM:FF842AA0                 BL      sub_FF83BA88    // was FF828C8C
//	ROM:FF842AA4                 CMP     R0, #0
//	ROM:FF842AA8                 LDRNE   R0, [R4]        // was [R4,#4]
//	ROM:FF842AAC                 ORRNE   R0, R0, #0x800000
//	ROM:FF842AB0                 STRNE   R0, [R4]        // was [R4,#4]
//	ROM:FF842AB4                 LDR     R0, =0xC0220128 // was 0xC02200C0
//	ROM:FF842AB8                 BL      sub_FF85FB40    // was FF84321C
//	ROM:FF842ABC                 CMP     R0, #0
//	ROM:FF842AC0                 LDREQ   R0, [R4]        // was [R4,#4]
//	ROM:FF842AC4                 ORREQ   R0, R0, #0x200000
//	ROM:FF842AC8                 STREQ   R0, [R4]        // was [R4,#4]
//	ROM:FF842ACC                 LDR     R0, =0xC022012C // was 0xC02200CC
//	ROM:FF842AD0                 BL      sub_FF85FB40    // was FF84321C
//	ROM:FF842AD4                 CMP     R0, #0
//	ROM:FF842AD8                 LDREQ   R0, [R4]        // was [R4,#4]
//	ROM:FF842ADC                 ORREQ   R0, R0, #0x400000
//	ROM:FF842AE0                 STREQ   R0, [R4]        // was [R4,#4]
//	ROM:FF842AE4                 LDMFD   SP!, {R4,PC}
//	ROM:FF842AE4 ; End of function sub_FF842A90
	*/

     // Search on 0x12345678 finds function that is called from function with this code (SD780 0xFF842A90)
    //*(int*)(0x2480)= (*(int*)0xC0220128)&1 ? 0x400000 : 0x200000; //VERIFY_SD780 replacement of sub_FF842A90/sub_FF821B7C for correct power-on.

    counter = DELAY; *p = 0x46; while (counter--) { asm("nop\n nop\n"); };
    counter = DELAY; *p = 0x44; while (counter--) { asm("nop\n nop\n"); };

    // jump to init-sequence that follows the data-copy-routine
    //asm volatile ("B      sub_FF810354_my\n");
    asm volatile ("B      sub_FF810354_my\n");
}

//??? Found at ff810354
//SD780 - ASM matches but comments are unknown if correct....
void __attribute__((naked,noinline)) sub_FF810354_my() { //??? was FF8101A0
        asm volatile (
"                LDR     R0, =0xFF8103CC\n" // exception handler code
"                MOV     R1, #0\n"
"                LDR     R3, =0xFF810404\n"
"loc_FF810360:\n"
"                CMP     R0, R3\n"          // load exception vector
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FF810360\n"
"                LDR     R0, =0xFF810404\n"
"                MOV     R1, #0x4B0\n"
"                LDR     R3, =0xFF810618\n"
"loc_FF81037C:\n"
"                CMP     R0, R3\n"          // copy IRQ handler to ITCM starting at 0x4b0, 532 bytes up to 0x6C4
"                LDRCC   R2, [R0],#4\n"
"                STRCC   R2, [R1],#4\n"
"                BCC     loc_FF81037C\n"
"                MOV     R0, #0xD2\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = IRQ, ints disabled
"                MOV     SP, #0x1000\n"     // irq mode SP
"                MOV     R0, #0xD3\n"
"                MSR     CPSR_cxsf, R0\n"   // set CPSR mode = Super, ints disabled
"                MOV     SP, #0x1000\n"     // super mode SP
"                LDR     R0, =0x6C4\n"
"                LDR     R2, =0xEEEEEEEE\n"
"                MOV     R3, #0x1000\n"
"loc_FF8103B0:\n"
"                CMP     R0, R3\n"          // clear ITCM 0x6C4-end with EEEEEEEE
"                STRCC   R2, [R0],#4\n"
"                BCC     loc_FF8103B0\n"
"                BL      sub_FF811198_my\n" //->my
        );
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF811198_my() { //??? was FF810FC4
	asm volatile (
"                 STR     LR, [SP,#-4]!\n"
"                 SUB     SP, SP, #0x74\n"
"                 MOV     R0, SP\n"
"                 MOV     R1, #0x74\n"
"                 BL      sub_FFB39910\n" // was sub_FFAC7EFC
"                 MOV     R0, #0x53000\n"
"                 STR     R0, [SP,#4]\n"

"                 LDR     R0, =new_sa\n" //Replaces original start location 0x14FE20 (was 0x146B8C)
"                 LDR     R0, [R0]\n"	 //

"                 LDR     R2, =0x339C00\n"
"                 LDR     R1, =0x3324A8\n"
"                 STR     R0, [SP,#8]\n"
"                 SUB     R0, R1, R0\n"
"                 ADD     R3, SP, #0xC\n"
"                 STR     R2, [SP]\n"
"                 STMIA   R3, {R0-R2}\n"
"                 MOV     R0, #0x22\n"
"                 STR     R0, [SP,#0x18]\n"
"                 MOV     R0, #0x68\n"
"                 STR     R0, [SP,#0x1C]\n"
"                 LDR     R0, =0x19B\n"
"                 LDR     R1, =0xFF815E58\n" // "LDR     R1, =sub_FF815E58"
"                 STR     R0, [SP,#0x20]\n"
"                 MOV     R0, #0x96\n"
"                 STR     R0, [SP,#0x24]\n"
"                 MOV     R0, #0x78\n"
"                 STR     R0, [SP,#0x28]\n"
"                 MOV     R0, #0x64\n"
"                 STR     R0, [SP,#0x2C]\n"
"                 MOV     R0, #0\n"
"                 STR     R0, [SP,#0x30]\n"
"                 STR     R0, [SP,#0x34]\n"
"                 MOV     R0, #0x10\n"
"                 STR     R0, [SP,#0x5C]\n"
"                 MOV     R0, #0x800\n"
"                 STR     R0, [SP,#0x60]\n"
"                 MOV     R0, #0xA0\n"
"                 STR     R0, [SP,#0x64]\n"
"                 MOV     R0, #0x280\n"
"                 STR     R0, [SP,#0x68]\n"

// DBG: OK
"                 LDR     R0, =0xC0220130\n"
"                 MOV     R2, #0x46\n"
"                 STR     R2, [r0, #0]\n"

"                 MOV     R0, SP\n"
"                 MOV     R2, #0\n"
"                 BL      sub_FF813404\n" // was FF812D68

// DBG: NO
"                 LDR     R0, =0xC0220134\n"
"                 MOV     R2, #0x46\n"
"                 STR     R2, [r0, #0]\n"
"tmp123:\n"
"                 B       tmp123\n"

"                 ADD     SP, SP, #0x74\n"
"                 LDR     PC, [SP],#4\n"
	);
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF815E58_my() { // was FF814D38
	asm volatile (
"                 STMFD   SP!, {R4,LR}\n"

"                 LDR     R0, =0xC0220134\n"
"                 MOV     R2, #0x46\n"
"                 STR     R2, [r0, #0]\n"
"tmp456:\n"
"                 B       tmp456\n"

"                 BL      sub_FF810B20\n" // was FF810954
"                 BL      sub_FF81A244\n" // was FF8190B4 dmSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF815F6C\n" // "dmSetup"
"                 BLLT    sub_FF815F4C\n" // was FF814E2C err_init_task
"                 BL      sub_FF815A94\n" // was FF814974
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF815F74\n" // "termDriverInit"
"                 BLLT    sub_FF815F4C\n" // was FF814E2C err_init_task
"                 LDR     R0, =0xFF815F84\n" // "/_term"
"                 BL      sub_FF815B7C\n" // was FF814A5C termDeviceCreate
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF815F8C\n" // "termDeviceCreate"
"                 BLLT    sub_FF815F4C\n" // was FF814E2C err_init_task
"                 LDR     R0, =0xFF815F84\n" // "/_term"
"                 BL      sub_FF813BF0\n" // was FF813578 stdioSetup  //VERIFY_SD780 testing
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF815FA0\n" // "stdioSetup"
"                 BLLT    sub_FF815F4C\n" // was FF814E2C err_init_task
"                 BL      sub_FF819C3C\n" // was ???????? stdlibSetup
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF815FAC\n" // "stdlibSetup"
"                 BLLT    sub_FF815F4C\n" // was FF814E2C err_init_task
"                 BL      sub_FF81167C\n" // was FF8114A8
"                 CMP     R0, #0\n"
"                 LDRLT   R0, =0xFF815FB8\n" // "armlib_setup"
"                 BLLT    sub_FF815F4C\n" // was FF814E2C err_init_task
"                 LDMFD   SP!, {R4,LR}\n"
"                 B       taskcreate_Startup_my\n" // FF81FAF0
	);
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) taskcreate_Startup_my() {  //0xFF81FAF0 (was 0xFF81C260)
	asm volatile (
"                STMFD   SP!, {R3,LR}\n"
"                BL      sub_FF834340\n" // was FF821B74 ??? nullsub
"                BL      sub_FF83BA88\n" // was FF828C8C
"                CMP     R0, #0\n"
"                BNE     loc_FF81FB34\n" // was FF81C298
"                BL      sub_FF835B2C\n" // was FF821B70

"                CMP     R0, #0\n" // new in IXUS130
"                BEQ     loc_FF81FB34\n"
"                BL      sub_FF83433C\n"

"                CMP     R0, #0\n"
"                BNE     loc_FF81FB34\n" // was FF81C298
"                BL      sub_FF8339DC\n" // was FF82123C
"                LDR     R1, =0xC0220000\n"
"                MOV     R0, #0x44\n"
"                STR     R0, [R1,#0x1C]\n"
"                BL      sub_FF833BC8\n" // was FF821428
"loc_FF81FB30:\n"
"                B       loc_FF81FB30\n"
"loc_FF81FB34:\n" // was FF81C298
//"                BL      sub_FF834348\n" // was FF821B7C VERIFY_SD780 is this true? - removed for correct power-on on 'on/off' button.  Hmm seems fine...
"                BL      sub_FF834344\n"   // was FF821B78 ??? nullsub
"                BL      sub_FF839CB0\n" // was FF826F44
"                LDR     R1, =0x38E000\n" // was 34E000
"                MOV     R0, #0\n"
"                BL      sub_FF83A0F8\n" // was FF82738C
"                BL      sub_FF839EA4\n" // was FF827138 LOCATION: KerSys.c:548
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =task_Startup_my\n" // FF81FA8C ->
"                MOV     R2, #0\n"
"                MOV     R1, #0x19\n"
"                LDR     R0, =0xFF81FB7C\n"  // "Startup"
"                BL      sub_FF81E83C\n" // was FF81AFAC eventproc_export_CreateTask ; LOCATION: KerTask.c:163\n"
"                MOV     R0, #0\n"
"                LDMFD   SP!, {R12,PC}\n"
	);
}


//SD780 - ASM matches - Original location 0xFF81C1FC, IXUS130 -> FF81FA8C
void __attribute__((naked,noinline)) task_Startup_my() {
	asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 BL      sub_FF81650C\n" // was FF815394 taskcreate_ClockSave
"                 BL      sub_FF83543C\n" // was FF822C58
"                 BL      sub_FF833638\n" // was FF820F04
"                 BL      sub_FF83BAC8\n" // was FF828CCC j_nullsub
"                 BL      sub_FF83BCB4\n" // was FF828EB0
//??? following was commented out
"                 BL      sub_FF83BB5C\n"  // was FF828D60 diskboot loop - VERIFY_SD780
        );

        //???CreateTask_spytask();
//       CreateTask_blinker();

        asm volatile (
"                 BL      sub_FF83BE58\n" // was FF829054
"                 BL      sub_FF8322E4\n" // was FF81FB90
"                 BL      sub_FF83BCE4\n" // was FF828EE0
"                 BL      sub_FF839454\n" // was FF826544
"                 BL      sub_FF83BE5C\n" // was FF829058
"                 BL      sub_FF834230_my\n" // was FF821A70 taskcreate_PhySw
"                 BL      sub_FF8377A8_my\n" // was FF824A98 taskcreate_SsTask -> for shoot seq stuff
"                 BL      sub_FF83BE74\n" // was FF829070
"                 BL      sub_FF8316A8\n" // was FF81EFB0 ??? nullsub
"                 BL      sub_FF833090\n" // was FF820808
"                 BL      sub_FF83B860\n" // was FF828A68 taskcreate_Bye
"                 BL      sub_FF8335EC\n" // was FF820EB4
"                 BL      sub_FF83302C\n" // was FF820714 taskcreate_TempCheck
"                 BL      sub_FF832318\n" // was FF81FBC4
"                 BL      sub_FF83C8F4\n" // was FF829AEC
"                 BL      sub_FF833004\n" // was FF8206EC
"                 LDMFD   SP!, {R4,LR}\n"
"                 B       sub_FF81662C\n" // was FF8154B4 _sub_FF8154B4__MLHClock_c__0 ; LOCATION: MLHClock.c:0
	);
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF8377A8_my() { // was FF824A98
asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 MOV     R0, #0\n"
"                 MOV     R1, #0\n"
"                 BL      sub_FF839F50\n" // was FF8271E4 KernelMisc.c:43
"                 LDR     R4, =0x1C7C\n" // was 0x1C48
"                 STR     R0, [R4,#16]\n" // was #4
"                 BL      sub_FF87F19C\n" // was FF862108
"                 BL      sub_FF8808E4\n" // was FF863818 -> taskcreate_SsTask
"                 BL      sub_FF87E2E4\n" // was FF861238
"                 BL      sub_FF878D1C_my\n" // was FF85C228
"                 BL      sub_FF87F480\n" // was FF8623EC
"                 LDR     R0, [R4,#16]\n" // was #4
"                 LDMFD   SP!, {R4,LR}\n"
"                 MOV     R1, #0x1000\n"
"                 B       sub_FF883F4C\n" // was FF866178
	);
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF878D1C_my() { // was FF85C228
	asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                LDR     R4, =0x2B64\n" // was 0x28E4
"                LDR     R0, [R4,#0xC]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF878D88\n" // was FF85C294
"                BL      sub_FF87C848\n" // was FF85FA38 ??? nullsub
"                MOV     R1, #1\n"
"                MOV     R0, #0\n"
"                BL      sub_FF839F74\n" // was FF827208 KernelMisc.c:55
"                STR     R0, [R4,#4]\n"
"                MOV     R0, #0\n"
"                MOV     R1, #8\n"
"                BL      sub_FF839F50\n" // was FF8271E4 KernelMisc.c:43
"                STR     R0, [R4,#0x8]\n"
"                BL      sub_FF8790FC\n" // was FF85C590
"                BL      sub_FF879884\n" // was FF85CD18
"                MOV     R0, #0\n"
"                STR     R0, [R4]\n"
"                ADD     R0, R4, #0x10\n"
"                MOV     R1, #0\n"
"                STR     R1, [R0],#4\n"
"                STR     R1, [R0]\n"
"                BL      sub_FF879A94\n" // was FF85CF20
"                BL      sub_FF87F680\n" // was FF8625F4
"                BL      sub_FF87CC74\n" // was FF85FD7C
"                BL      sub_FF87A5D8_my\n" // was FF85DA4C ->taskcreate_CaptSeqTask
"                BL      sub_FF87B688\n" // was FF85EA10

"loc_FF878D88:\n"
"                MOV     R0, #1\n"
"                STR     R0, [R4,#0xC]\n"
"                LDMFD   SP!, {R4,PC}\n"
	);
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF87A5D8_my() { // was FF85DA4C
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R2, =0x39578\n" // was 0x1446C
"                MOV     R0, #0\n"
"                MOV     R1, #0\n"

"loc_FF87A5E8:\n"
"                ADD     R3, R2, R0,LSL#4\n"
"                ADD     R0, R0, #1\n"
"                CMP     R0, #5\n"
"                STR     R1, [R3,#8]\n"
"                BCC     loc_FF87A5E8\n"
"                BL      sub_FF87B1C4\n" // was FF85E55C
"                BL      sub_FF95F3A0\n" // was FF9202C4

"                BL      sub_FF95FF60\n" // new in IXUS130

"                MOV     R1, #5\n"
"                MOV     R0, #0\n"
"                BL      sub_FF839F2C\n" // was FF8271C0 KernelMisc.c:31
"                LDR     R4, =0x2B9C\n" // was 0x291C
"                LDR     R1, =0x101DFF\n"
"                STR     R0, [R4,#0x4]\n"
"                MOV     R0, #0\n"
"                BL      sub_FF839F50\n" // was FF8271E4 KernelMisc.c:43
"                STR     R0, [R4]\n"
"                MOV     R0, #0\n"
"                MOV     R1, #1\n"
"                BL      sub_FF839F74\n" // was FF827208 KernelMisc.c:55
"                STR     R0, [R4,#0x8]\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
//"                LDR     R3, =task_CaptSeqTask_my\n" // 0xFF87A2C0
"                LDR     R3, =0xFF87A2C0\n" //???

"                LDR     R0, =0xFF87A848\n" // was 0xFF85DC98 "CaptSeqTask"
"                MOV     R2, #0x1000\n"
"                MOV     R1, #0x17\n"
"                BL      sub_FF839EF8\n"// was FF82718C KernelCreateTask ; LOCATION: KernelMisc.c:19
"                LDMFD   SP!, {R3-R5,PC}\n"
	);
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF834230_my() { // was FF821A70
	asm volatile (
"                STMFD   SP!, {R3-R5,LR}\n"
"                LDR     R4, =0x1C20\n" // was 0x1C28
"                LDR     R0, [R4,#0x10]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF834264\n" // was FF821AA4
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
//"                LDR     R3, =mykbd_task\n" // FF8341FC task_PhySw
"                LDR     R3, =0xFF8341FC\n" //???

"                MOV     R2, #0x2000\n" 	// Increate stack size from 0x800 to 0x2000 for new task_PhySw so we don't have to do stack switch
"                MOV     R1, #0x17\n"
"                LDR     R0, =0xFF834438\n" // "PhySw"
"                BL      sub_FF839EF8\n" // was FF82718C KernelCreateTask
"                STR     R0, [R4,#0x10]\n"

"loc_FF834264:\n"
"                BL      sub_FF88A5F4\n" // was FF86C714
"                BL      sub_FF835AA4\n" // was FF846654 IsFactoryMode
"                CMP     R0, #0\n"
"                LDREQ   R1, =0x3280C\n" // was 0xE244
"                LDMEQFD SP!, {R3-R5,LR}\n"
"                BEQ     sub_FF88A57C\n" // was FF86C69C eventproc_export_OpLog_Start
"                LDMFD   SP!, {R3-R5,PC}\n"
	);
}

#if 0
//VERIFY_SD780 - What does this do for us?
void CreateTask_spytask() {
  //???_CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}


//SD780 - ASM Matches - Original location 0xFF877DD0
void __attribute__((naked,noinline)) init_file_modules_task() {
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 BL      sub_FF86EB24\n"
"                 LDR     R5, =0x5006\n"
"                 MOVS    R4, R0\n"
"                 MOVNE   R1, #0\n"
"                 MOVNE   R0, R5\n"
"                 BLNE    sub_FF873978\n"			// PostLogicalEventToUI
"                 BL      sub_FF86EB50_my\n" // ->
"                 BL      core_spytask_can_start\n" // + safe to start spytask
"                 CMP     R4, #0\n"
"                 MOVEQ   R0, R5\n"
"                 LDMEQFD SP!, {R4-R6,LR}\n"
"                 MOVEQ   R1, #0\n"
"                 BEQ     sub_FF873978\n" // PostLogicalEventToUI
"                 LDMFD   SP!, {R4-R6,PC}\n"
	);
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF86EB50_my() {
  asm volatile (
"                 STMFD   SP!, {R4,LR}\n"
"                 MOV	  R0, #3\n"
"                 BL      sub_FF852020_my\n" // ->  //Mounter.c
//"                 BL      nullsub_95\n"
"                 LDR     R4, =0x2C94\n"
"                 LDR     R0, [R4,#4]\n"
"                 CMP     R0, #0\n"
"                 BNE     loc_FF86EB88\n"
"                 BL      sub_FF8513E4\n"
"                 BL      sub_FF8ED998\n"
"                 BL      sub_FF8513E4\n"
"                 BL      sub_FF84D438\n"
"                 BL      sub_FF8512E4\n"
"                 BL      sub_FF8EDA64\n"
"loc_FF86EB88:\n"
"                 MOV     R0, #1\n"
"                 STR     R0, [R4]\n"
"                 LDMFD   SP!, {R4,PC}\n"
 );
}

//SD780 - ASM matches
void __attribute__((naked,noinline)) sub_FF852020_my() {
  asm volatile (

"                 STMFD   SP!, {R4-R8,LR}\n"
"                 MOV     R6, R0\n"
"                 BL      sub_FF851F88\n"
"                 LDR     R1, =0x10938\n"
"                 MOV     R5, R0\n"
"                 ADD     R4, R1, R0, LSL#7\n"
"                 LDR     R0, [R4,#0x70]\n"
"                 CMP     R0, #4\n"
"                 LDREQ   R1, =0x6D8\n"
"                 LDREQ   R0, =0xFF851AAC\n"
"                 BLEQ    sub_FF81B284\n"
"                 MOV     R1, R6\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FF8519F4\n" // LOCATION: Mounter.c:824// Original
"                 LDR     R0, [R4,#0x38]\n"
"                 BL      sub_FF85254C\n"
"				  CMP	  R0, #0\n"
"				  STREQ	  R0, [R4,#0x70]\n"
"				  MOV	  R0, R5\n"
"				  BL	  sub_FF851ACC\n"
"				  MOV	  R0, R5\n"
"				  BL	  sub_FF851DC0_my\n"
"                 MOV     R7, R0\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FF851E24\n" // LOCATION: Mounter.c:8// Original
"                 LDR     R1, [R4,#0x3C]\n"
"                 AND     R2, R7, R0\n"
"                 CMP     R1, #0\n"
"                 MOV     R0, #0\n"
"                 MOVEQ   R0, #0x80000001\n"
"                 BEQ     loc_FF8520C8\n"
"                 LDR     R3, [R4,#0x2C]\n"
"                 CMP     R3, #2\n"
"                 MOVEQ   R0, #4\n"
"                 CMP     R1, #5\n"
"                 ORRNE   R0, R0, #1\n"
"                 BICEQ   R0, R0, #1\n"
"                 CMP     R2, #0\n"
"                 BICEQ   R0, R0, #2\n"
"                 ORREQ   R0, R0, #0x80000000\n"
"                 BICNE   R0, R0, #0x80000000\n"
"                 ORRNE   R0, R0, #2\n"
"loc_FF8520C8:\n"
"				  CMP	  R6, #7\n"
"                 STR     R0, [R4,#0x40]\n"
"				  LDMNEFD SP!, {R4-R8,PC}\n"
"				  MOV	  R0, R6\n"
"				  BL	  sub_FF851FD8\n"
"				  CMP	  R0, #0\n"
"				  LDMEQFD SP!, {R4-R8,LR}\n"
"				  LDREQ   R0,=0xFF8522C4\n"
"				  BEQ 	  sub_FF8115A8\n"
"                 LDMFD   SP!, {R4-R6,PC}\n"
 );
}

//SD780 - ASM matches - Note support of FAT32 is OFF
void __attribute__((naked,noinline)) sub_FF851DC0_my() {
  asm volatile (
"                 STMFD   SP!, {R4-R6,LR}\n"
"                 MOV     R5, R0\n"
"                 LDR     R0, =0x10938\n"
"				  ADD 	  R4, R0, R5,LSL#7\n"
"                 LDR     R0, [R4,#0x70]\n"
"                 TST     R0, #2\n"
"                 MOVNE   R0, #1\n"
"                 LDMNEFD SP!, {R4-R6,PC}\n"
"				  LDR 	  R0, [R4,#0x38]\n"
"                 MOV     R1, R5\n"
"                 BL      sub_FF851B50_my\n"  // -> FAT32 Support  //VERIFY_SD780
//"                 BL      sub_FF851B50\n" 		// -> is Mounter.c
"                 CMP     R0, #0\n"
"                 LDMEQFD SP!, {R4-R6,PC}\n"
"                 LDR     R0, [R4,#0x38]\n"
"                 MOV     R1, R5\n"
"                 BL      sub_FF851CBC\n" // LOCATION: Mounter.c:0
"                 CMP     R0, #0\n"
"                 LDMEQFD SP!, {R4-R6,PC}\n"
"                 MOV     R0, R5\n"
"                 BL      sub_FF8515DC\n"
"                 CMP     R0, #0\n"
"				  LDRNE	  R1, [R4,#0x70]\n"
"				  ORRNE	  R1, R1, #2\n"
"                 STRNE   R1, [R4,#0x70]\n"
"                 LDMFD   SP!, {R4-R6,PC}\n"
  );
}


//VERIFY_SD780 - FAT32 is OFF
void __attribute__((naked,noinline)) sub_FF851B50_my() {  //Need to fix
  asm volatile (
"                 STMFD   SP!, {R4-R8,LR}\n"
"                 MOV     R8, R0\n"
//"                 MOV     R0, #0x17\n"
//"                 MUL     R1, R0, R1\n"
"                 LDR     R0, =0x10938\n"
"                 MOV     R7, #0\n"
"                 ADD     R5, R0, R1,LSL#7\n"
"                 LDR     R0, [R5,#0x3C]\n"
"                 MOV     R6, #0\n"
"                 CMP     R0, #7\n"
"                 ADDLS   PC, PC, R0,LSL#2\n"
"                 B       loc_FF851CA0\n"
"                 B       loc_FF851BB0\n"
"                 B       loc_FF851B98\n"
"                 B       loc_FF851B98\n"
"                 B       loc_FF851B98\n"
"                 B       loc_FF851B98\n"
"                 B       loc_FF851C98\n"
"                 B       loc_FF851B98\n"
"                 B       loc_FF851B98\n"
"loc_FF851B98:\n"
// jumptable FF851B70 entries 1-4,6,7
"                 MOV     R2, #0\n"
"                 MOV     R1, #0x200\n"
"                 MOV     R0, #2\n"
"                 BL      sub_FF868C1C\n"
"                 MOVS    R4, R0\n"
"                 BNE     loc_FF851BB8\n"
"loc_FF851BB0:\n"
// jumptable FF851B70 entry 0
"                 MOV     R0, #0\n"
"                 LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF851BB8:\n"
"                 LDR     R12, [R5,#0x4C]\n"
"                 MOV     R3, R4\n"
"                 MOV     R2, #1\n"
"                 MOV     R1, #0\n"
"                 MOV     R0, R8\n"
//"               BLX 	  R12\n"			//-
"                 MOV 	  LR, PC\n"			//+
"                 MOV 	  PC, R12\n"		//+
"                 CMP     R0, #1\n"
"                 BNE     loc_FF851BE4\n"
"                 MOV     R0, #2\n"
"                 BL      sub_FF868D68\n" // LOCATION: ExMemMan.c:0
"                 B       loc_FF851BB0\n"
"loc_FF851BE4:\n"
"                 LDR     R1, [R5,#0x68]\n"
"                 MOV     R0, R8\n"
//"               BLX     R1\n"  //FF851BEC //-
"                 MOV     LR, PC\n" //+
"                 MOV     PC, R1\n" //+



 	 "MOV   R1, R4\n"           //  pointer to MBR in R1
 	 "BL    mbr_read_dryos\n"   //  total sectors count in R0 before and after call

        // Start of DataGhost's FAT32 autodetection code
        // Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
        // According to the code below, we can use R1, R2, R3 and R12.
        // LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
        // that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
        "MOV     R12, R4\n"                    // Copy the MBR start address so we have something to work with
        "MOV     LR, R4\n"                     // Save old offset for MBR signature
        "MOV     R1, #1\n"                     // Note the current partition number
        "B       dg_sd_fat32_enter\n"          // We actually need to check the first partition as well, no increments yet!
   "dg_sd_fat32:\n"
        "CMP     R1, #4\n"                     // Did we already see the 4th partition?
        "BEQ     dg_sd_fat32_end\n"            // Yes, break. We didn't find anything, so don't change anything.
        "ADD     R12, R12, #0x10\n"            // Second partition
        "ADD     R1, R1, #1\n"                 // Second partition for the loop
   "dg_sd_fat32_enter:\n"
        "LDRB    R2, [R12, #0x1BE]\n"          // Partition status
        "LDRB    R3, [R12, #0x1C2]\n"          // Partition type (FAT32 = 0xB)
        "CMP     R3, #0xB\n"                   // Is this a FAT32 partition?
        "CMPNE   R3, #0xC\n"                   // Not 0xB, is it 0xC (FAT32 LBA) then?
        "BNE     dg_sd_fat32\n"                // No, it isn't. Loop again.
        "CMP     R2, #0x00\n"                  // It is, check the validity of the partition type
        "CMPNE   R2, #0x80\n"
        "BNE     dg_sd_fat32\n"                // Invalid, go to next partition
                                               // This partition is valid, it's the first one, bingo!
		//	  		  "LDR R0, =0xC0223000\n"
		//	  		  "MOV R7, #0x46\n"
		//	  		  "STR R7, [R0, #0x30]\n"
        "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.

   "dg_sd_fat32_end:\n"
        // End of DataGhost's FAT32 autodetection code
		  //FF851BF0
"                 LDRB    R1, [R4,#0x1C9]\n"
"                 LDRB    R3, [R4,#0x1C8]\n"
"                 LDRB    R12, [R4,#0x1CC]\n"
"                 MOV     R1, R1,LSL#24\n"
"                 ORR     R1, R1, R3,LSL#16\n"
"                 LDRB    R3, [R4,#0x1C7]\n"
"                 LDRB    R2, [R4,#0x1BE]\n"
//"                 LDRB    LR, [R4,#0x1FF]\n" // -
"                 ORR     R1, R1, R3,LSL#8\n"
"                 LDRB    R3, [R4,#0x1C6]\n"
"                 CMP     R2, #0\n"
"                 CMPNE   R2, #0x80\n"
"                 ORR     R1, R1, R3\n"
"                 LDRB    R3, [R4,#0x1CD]\n"
"                 MOV     R3, R3,LSL#24\n"
"                 ORR     R3, R3, R12,LSL#16\n"
"                 LDRB    R12, [R4,#0x1CB]\n"
"                 ORR     R3, R3, R12,LSL#8\n"
"                 LDRB    R12, [R4,#0x1CA]\n"
"                 ORR     R3, R3, R12\n"

		  //fix below
//"                 LDRB    R12, [R4,#0x1FE]\n" // -
"                 LDRB    R12, [LR,#0x1FE]\n" // +
"                 LDRB    LR, [LR,#0x1FF]\n" // +
//At ff851c44
		  "                 MOV     R4, #0\n"
"                 BNE     loc_FF851C70\n"
"                 CMP     R0, R1\n"
"                 BCC     loc_FF851C70\n"
"                 ADD     R2, R1, R3\n"
"                 CMP     R2, R0\n"
"                 CMPLS   R12, #0x55\n"
"                 CMPEQ   LR, #0xAA\n"
"                 MOVEQ   R7, R1\n"
"                 MOVEQ   R6, R3\n"
"                 MOVEQ   R4, #1\n"
"loc_FF851C70:\n"
"                 MOV     R0, #2\n"
"                 BL      sub_FF868D68\n" // LOCATION: ExMemMan.c:0
"                 CMP     R4, #0\n"
"                 BNE     loc_FF851CAC\n"
//was a non-comment		  LDR R1, [R5,#0x68]
"                 LDR     R1, [R5,#0x68]\n"
"                 MOV     R7, #0\n"
"                 MOV     R0, R8\n"
//"                 BL      sub_FF9214E8\n"
//"               BLX     R1\n"  //-
"                 MOV     LR, PC\n" //+
"                 MOV     PC, R1\n" //+

"                 MOV     R6, R0\n"
"                 B       loc_FF851CAC\n"
"loc_FF851C98:\n"
// jumptable FF851B70 entry 5
"                 MOV     R6, #0x40\n"
"                 B       loc_FF851CAC\n"
"loc_FF851CA0:\n"
// jumptable FF851B70 default entry
"                 LDR     R1, =0x5C9\n"
"                 LDR     R0, =0xFF851AAC\n" // "Mounter.c"
"                 BL      sub_FF81B284\n" // DebugAssert
" loc_FF851CAC:\n"
"                 STR     R7, [R5,#0x44]!\n"
"                 MOV     R0, #1\n"
"                 STR     R6, [R5,#4]\n"
"                 LDMFD   SP!, {R4-R8,PC}\n"
  );
}

#endif
