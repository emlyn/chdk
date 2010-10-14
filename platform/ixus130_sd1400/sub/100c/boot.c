#include "lolevel.h"
#include "platform.h"
#include "core.h"

#include "led.h"

const char * const new_sa = &_end;

// Our stuff
//extern long wrs_kernel_bss_start;
//extern long wrs_kernel_bss_end;
long aHookList[128];
long aHookNum=0;

// Forward declarations
//void CreateTask_spytask();
//void boot();

//void __attribute__((naked,noinline)) sub_STUB_my() {
//	asm volatile (
//	"nop\n"
//	);
//}

void taskCreateHook(int *p) {
  led_flash(LED_RED, 1);
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
  led_flash(LED_RED, 1);
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
	"ldr	r1, =0xc0410000\n" // was: "[pc, #336]	; ff810164" 
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r0, [r1]\n"
	"ldr	r1, =0x78\n" // was: "mov ..., #120"
	"mcr	15, 0, r1, cr1, cr0, 0\n"
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"mcr	15, 0, r1, cr7, cr10, 4\n"
	"mcr	15, 0, r1, cr7, cr5, 0\n"
	"mcr	15, 0, r1, cr7, cr6, 0\n"
	"ldr	r0, =0x3d\n" // was: "mov ..., #61"
	"mcr	15, 0, r0, cr6, cr0, 0\n"
	"ldr	r0, =0xc000002f\n" // was: "mov ..., #-1073741777"
	"mcr	15, 0, r0, cr6, cr1, 0\n"
	"ldr	r0, =0x33\n" // was: "mov ..., #51"
	"mcr	15, 0, r0, cr6, cr2, 0\n"
	"ldr	r0, =0x40000033\n" // was: "mov ..., #1073741875"
	"mcr	15, 0, r0, cr6, cr3, 0\n"
	"ldr	r0, =0x80000017\n" // was: "mov ..., #-2147483625"
	"mcr	15, 0, r0, cr6, cr4, 0\n"
	"ldr	r0, =0xff80002d\n" // was: "[pc, #264]	; ff810168" 
	"mcr	15, 0, r0, cr6, cr5, 0\n"
	"ldr	r0, =0x34\n" // was: "mov ..., #52"
	"mcr	15, 0, r0, cr2, cr0, 0\n"
	"ldr	r0, =0x34\n" // was: "mov ..., #52"
	"mcr	15, 0, r0, cr2, cr0, 1\n"
	"ldr	r0, =0x34\n" // was: "mov ..., #52"
	"mcr	15, 0, r0, cr3, cr0, 0\n"
	"ldr	r0, =0x03333330\n" // was: "[pc, #236]	; ff81016c" 
	"mcr	15, 0, r0, cr5, cr0, 2\n"
	"ldr	r0, =0x03333330\n" // was: "[pc, #228]	; ff81016c" 
	"mcr	15, 0, r0, cr5, cr0, 3\n"
	"mrc	15, 0, r0, cr1, cr0, 0\n"
	"orr	r0, r0, #4096\n"	// 0x1000
	"orr	r0, r0, #4\n"	// 0x4
	"orr	r0, r0, #1\n"	// 0x1
	"mcr	15, 0, r0, cr1, cr0, 0\n"
	"ldr	r1, =0x80000006\n" // was: "mov ..., #-2147483642"
	"mcr	15, 0, r1, cr9, cr1, 0\n"
	"ldr	r1, =0x6\n" // was: "mov ..., #6"
	"mcr	15, 0, r1, cr9, cr1, 1\n"
	"mrc	15, 0, r1, cr1, cr0, 0\n"
	"orr	r1, r1, #327680\n"	// 0x50000
	"mcr	15, 0, r1, cr1, cr0, 0\n"
	"ldr	r2, =0xc0200000\n" // was: "[pc, #176]	; ff810170" 
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"str	r1, [r2, #268]\n"
	"ldr	r1, =0xff\n" // was: "mov ..., #255"
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
	"ldr	r1, =0xc0400008\n" // was: "[pc, #100]	; ff810174" 
	"ldr	r2, =0x00430005\n" // was: "[pc, #100]	; ff810178" 
	"str	r2, [r1]\n"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r2, =0xc0243100\n" // was: "[pc, #92]	; ff81017c" 
	"str	r2, [r1]\n"
	"ldr	r2, =0xc0242010\n" // was: "[pc, #88]	; ff810180" 
	"ldr	r1, [r2]\n"
	"orr	r1, r1, #1\n"	// 0x1
	"str	r1, [r2]\n"
	"ldr	r0, =0xffbf8434\n" // was: "[pc, #76]	; ff810184" 
	"ldr	r1, =0x00001900\n" // was: "[pc, #76]	; ff810188" 
	"ldr	r3, =0x0000ebd0\n" // was: "[pc, #76]	; ff81018c" 
"loc_ff81013c:\n"
	"cmp	r1, r3\n"
	"ldrcc	r2, [r0], #4\n"
	"strcc	r2, [r1], #4\n"
	"bcc	loc_ff81013c\n"
	"ldr	r1, =0x0014fe20\n" // was: "[pc, #60]	; ff810190" 
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
"loc_ff810154:\n"
	"cmp	r3, r1\n"
	"strcc	r2, [r3], #4\n"
	"bcc	loc_ff810154\n"
    );
/*
ff85f3f0: 	e92d4010 	push	{r4, lr}
ff85f3f4: 	e59f46cc 	ldr	r4, [pc, #1740]	; ff85fac8: (00002480) 
ff85f3f8: 	e3a00000 	mov	r0, #0	; 0x0
ff85f3fc: 	e5840000 	str	r0, [r4]
ff85f400: 	ebff71a0 	bl	loc_ff83ba88
ff85f404: 	e3500000 	cmp	r0, #0	; 0x0
ff85f408: 	15940000 	ldrne	r0, [r4]
ff85f40c: 	13800502 	orrne	r0, r0, #8388608	; 0x800000
ff85f410: 	15840000 	strne	r0, [r4]
ff85f414: 	e59f06b0 	ldr	r0, [pc, #1712]	; ff85facc: (c0220128) 
ff85f418: 	eb0001c8 	bl	loc_ff85fb40
ff85f41c: 	e3500000 	cmp	r0, #0	; 0x0
ff85f420: 	05940000 	ldreq	r0, [r4]
ff85f424: 	03800602 	orreq	r0, r0, #2097152	; 0x200000
ff85f428: 	05840000 	streq	r0, [r4]
ff85f42c: 	e59f069c 	ldr	r0, [pc, #1692]	; ff85fad0: (c022012c) 
ff85f430: 	eb0001c2 	bl	loc_ff85fb40
ff85f434: 	e3500000 	cmp	r0, #0	; 0x0
ff85f438: 	05940000 	ldreq	r0, [r4]
ff85f43c: 	03800501 	orreq	r0, r0, #4194304	; 0x400000
ff85f440: 	05840000 	streq	r0, [r4]
ff85f444: 	e8bd8010 	pop	{r4, pc}
// Search on 0x12345678 finds function that is called from function with this code (SD780 0xFF842A90)
*/
  *(int*)0x2480 = (*(int*)0xC0220128) & 1 ? 0x400000 : 0x200000;

  *(int*)0x1934 = (int)taskCreateHook;
  *(int*)0x1938 = (int)taskCreateHook2;

  asm volatile (
	"b	sub_ff810354_my\n"
    );
}

void __attribute__((naked,noinline)) sub_ff810354_my() { //??? was FF8101A0
  asm volatile (
	"ldr	r0, =0xff8103cc\n" // was: "[pc, #1036]	; ff810768" 
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"ldr	r3, =0xff810404\n" // was: "[pc, #1032]	; ff81076c" 
"loc_ff810360:\n"
	"cmp	r0, r3\n"
	"ldrcc	r2, [r0], #4\n"
	"strcc	r2, [r1], #4\n"
	"bcc	loc_ff810360\n"
	"ldr	r0, =0xff810404\n" // was: "[pc, #1016]	; ff810770" 
	"ldr	r1, =0x4b0\n" // was: "mov ..., #1200"
	"ldr	r3, =0xff810618\n" // was: "[pc, #1012]	; ff810774" 
"loc_ff81037c:\n"
	"cmp	r0, r3\n"
	"ldrcc	r2, [r0], #4\n"
	"strcc	r2, [r1], #4\n"
	"bcc	loc_ff81037c\n"
	"ldr	r0, =0xd2\n" // was: "mov ..., #210"
	"msr	CPSR_fsxc, r0\n"
	"ldr	sp, =0x1000\n" // was: "mov ..., #4096"
	"ldr	r0, =0xd3\n" // was: "mov ..., #211"
	"msr	CPSR_fsxc, r0\n"
	"ldr	sp, =0x1000\n" // was: "mov ..., #4096"
	"ldr	r0, =0x000006c4\n" // was: "[pc, #20]	; ff8103c0" 
	"ldr	r2, =0xeeeeeeee\n" // was: "[pc, #968]	; ff810778" 
	"ldr	r3, =0x1000\n" // was: "mov ..., #4096"
"loc_ff8103b0:\n"
	"cmp	r0, r3\n"
	"strcc	r2, [r0], #4\n"
	"bcc	loc_ff8103b0\n"
	"bl	sub_ff811198_my\n"
        );
}

void __attribute__((naked,noinline)) sub_ff811198_my() {
  asm volatile (
	"push	{lr}\n"		// (str lr, [sp, #-4]!)
	"sub	sp, sp, #116\n"	// 0x74
	"mov	r0, sp\n"
	"ldr	r1, =0x74\n" // was: "mov ..., #116"
	"bl	sub_ffb399c4\n"
	"ldr	r0, =0x53000\n" // was: "mov ..., #339968"
	"str	r0, [sp, #4]\n"
	"ldr	r0, =new_sa\n" // Replaces original start location 0x14fe20
	"ldr	r2, =0x00339c00\n" // was: "[pc, #136]	; ff811248" 
	"ldr	r1, =0x003324a8\n" // was: "[pc, #140]	; ff811250" 
	"str	r0, [sp, #8]\n"
	"sub	r0, r1, r0\n"
	"add	r3, sp, #12\n"	// 0xc
	"str	r2, [sp]\n"
	"stm	r3, {r0, r1, r2}\n"
	"ldr	r0, =0x22\n" // was: "mov ..., #34"
	"str	r0, [sp, #24]\n"
	"ldr	r0, =0x68\n" // was: "mov ..., #104"
	"str	r0, [sp, #28]\n"
	"ldr	r0, =0x0000019b\n" // was: "[pc, #104]	; ff811254" 
	"ldr	r1, =sub_ff815e58_my\n" // was: "[pc, #104]	; ff811258"
	"str	r0, [sp, #32]\n"
	"ldr	r0, =0x96\n" // was: "mov ..., #150"
	"str	r0, [sp, #36]\n"
	"ldr	r0, =0x78\n" // was: "mov ..., #120"
	"str	r0, [sp, #40]\n"
	"ldr	r0, =0x64\n" // was: "mov ..., #100"
	"str	r0, [sp, #44]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r0, [sp, #48]\n"
	"str	r0, [sp, #52]\n"
	"ldr	r0, =0x10\n" // was: "mov ..., #16"
	"str	r0, [sp, #92]\n"
	"ldr	r0, =0x800\n" // was: "mov ..., #2048"
	"str	r0, [sp, #96]\n"
	"ldr	r0, =0xa0\n" // was: "mov ..., #160"
	"str	r0, [sp, #100]\n"
	"ldr	r0, =0x280\n" // was: "mov ..., #640"
	"str	r0, [sp, #104]\n"
	"mov	r0, sp\n"
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff813404\n"
	"add	sp, sp, #116\n"	// 0x74
	"pop	{pc}\n"		// (ldr pc, [sp], #4)
    );
}

void __attribute__((naked,noinline)) sub_ff815e58_my() {
  asm volatile (
	"push	{r4, lr}\n"
	"bl	sub_ff810b20\n"
	"bl	sub_ff81a244\n"
	"cmp	r0, #0\n"	// 0x0
	"addlt	r0, pc, #252\n"	// ff815f6c: (65536d64)  *"dmSetup"
	"bllt	sub_ff815f4c\n"
	"bl	sub_ff815a94\n"
	"cmp	r0, #0\n"	// 0x0
	"addlt	r0, pc, #244\n"	// ff815f74: (6d726574)  *"termDriverInit"
	"bllt	sub_ff815f4c\n"
	"add	r0, pc, #252\n"	// ff815f84: (65745f2f)  *"/_term"
	"bl	sub_ff815b7c\n"
	"cmp	r0, #0\n"	// 0x0
	"addlt	r0, pc, #248\n"	// ff815f8c: (6d726574)  *"termDeviceCreate"
	"bllt	sub_ff815f4c\n"
	"add	r0, pc, #232\n"	// ff815f84: (65745f2f)  *"/_term"
	"bl	sub_ff813bf0\n"
	"cmp	r0, #0\n"	// 0x0
	"addlt	r0, pc, #248\n"	// ff815fa0: (69647473)  *"stdioSetup"
	"bllt	sub_ff815f4c\n"
	"bl	sub_ff819c3c\n"
	"cmp	r0, #0\n"	// 0x0
	"addlt	r0, pc, #244\n"	// ff815fac: (6c647473)  *"stdlibSetup"
	"bllt	sub_ff815f4c\n"
	"bl	sub_ff81167c\n"
	"cmp	r0, #0\n"	// 0x0
	"addlt	r0, pc, #240\n"	// ff815fb8: (6c6d7261)  *"armlib_setup"
	"bllt	sub_ff815f4c\n"
	"pop	{r4, lr}\n"
	"b	taskcreate_Startup_my\n" // ff81faf0
    );
}

void __attribute__((naked,noinline)) taskcreate_Startup_my() { // 0xff81faf0
  asm volatile (
	"push	{r3, lr}\n"
	"bl	sub_ff834340\n"
	"bl	sub_ff83ba88\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff81fb34\n"
	"bl	sub_ff835b2c\n"
	"cmp	r0, #0\n"	// 0x0
	"beq	loc_ff81fb34\n"
	"bl	sub_ff83433c\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff81fb34\n"
	"bl	sub_ff8339dc\n"
	"ldr	r1, =0xc0220000\n" // was: "[pc, #76]	; ff81fb74" 
	"ldr	r0, =0x44\n" // was: "mov ..., #68"
	"str	r0, [r1, #28]\n"
	"bl	sub_ff833bc8\n"
"loc_ff81fb30:\n"
	"b	loc_ff81fb30\n"
"loc_ff81fb34:\n" // 3 refs
	"bl	sub_ff834348\n"
	"bl	sub_ff834344\n"
	"bl	sub_ff839cb0\n"
	"ldr	r1, =0x0038e000\n" // was: "[pc, #48]	; ff81fb78" 
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff83a0f8\n"
	"bl	sub_ff839ea4\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	"ldr    r3, =task_Startup_my\n" // was: "sub	r3, pc, #212\n"	// ff81fa8c: (e92d4010) 
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x19\n" // was: "mov ..., #25"
	"add	r0, pc, #16\n"	// ff81fb7c: (72617453)  *"Startup"
	"bl	sub_ff81e83c\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"pop	{ip, pc}\n"
    );
}

void __attribute__((naked,noinline)) task_Startup_my() { // ff81fa8c
  asm volatile (
	"push	{r4, lr}\n"
	"bl	sub_ff81650c\n" // taskcreate_ClockSave
	"bl	sub_ff83543c\n"
	"bl	sub_ff833638\n"
	"bl	sub_ff83bac8\n" // j_nullsub
	"bl	sub_ff83bcb4\n"
//SD780??? following was commented out:
	"bl	sub_ff83bb5c\n" // diskboot loop - VERIFY_SD780
    );

  //???CreateTask_spytask();
//       CreateTask_blinker();

  asm volatile (
	"bl	sub_ff83be58\n"
	"bl	sub_ff8322e4\n"
	"bl	sub_ff83bce4\n"
	"bl	sub_ff839454\n"
	"bl	sub_ff83be5c\n"
	"bl	sub_ff834230_my\n" // taskcreate_PhySw
	"bl	sub_ff8377a8_my\n" // taskcreate_SsTask -> for shoot seq stuff
	"bl	sub_ff83be74\n"
	"bl	sub_ff8316a8\n" // nullsub
	"bl	sub_ff833090\n"
	"bl	sub_ff83b860\n" // taskcreate_Bye
	"bl	sub_ff8335ec\n"
	"bl	sub_ff83302c\n" // taskcreate_TempCheck
	"bl	sub_ff832318\n"
	"bl	sub_ff83c8f4\n"
	"bl	sub_ff833004\n"
	"pop	{r4, lr}\n"
	"b	sub_ff81662c\n"
    );
}

void __attribute__((naked,noinline)) sub_ff8377a8_my() {
asm volatile (
	"push	{r4, lr}\n"
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f50\n"
	"ldr	r4, =0x00001c7c\n" // was: "[pc, #-492]	; ff8375d4" 
	"str	r0, [r4, #16]\n"
	"bl	sub_ff87f1ec\n" // SD708 was FF87F19C
	"bl	sub_ff880934\n" // SD780 was FF8808E4 -> taskcreate_SsTask
	"bl	sub_ff87e334\n" // SD780 was FF87E2E4
	"bl	sub_ff878d6c_my\n" // SD780 was FF878D1C_my
	"bl	sub_ff87f4d0\n" // SD780 was FF87F480
	"ldr	r0, [r4, #16]\n"
	"pop	{r4, lr}\n"
	"ldr	r1, =0x1000\n" // was: "mov ..., #4096"
	"b	sub_ff883f9c\n" // SD780 was FF883F4C
  );
}

void __attribute__((naked,noinline)) sub_ff878d6c_my() { // was FF878D1C_my
  asm volatile (
	"push	{r4, lr}\n"
	"ldr	r4, =0x00002b64\n" // was: "[pc, #-3512]	; ff877fc0" 
	"ldr	r0, [r4, #12]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff878dd8\n" // SD780 was FF878D88
	"bl	sub_ff87c898\n" // SD780 was FF87C848 nullsub
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f74\n" // SD780 was FF839F74 KernelMisc.c:55
	"str	r0, [r4, #4]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x8\n" // was: "mov ..., #8"
	"bl	sub_ff839f50\n" // SD780 was FF839F50 KernelMisc.c:43
	"str	r0, [r4, #8]\n"
	"bl	sub_ff87914c\n" // SD780 was FF8790FC
	"bl	sub_ff8798d4\n" // SD780 was FF879884
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r0, [r4]\n"
	"add	r0, r4, #16\n"	// 0x10
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"str	r1, [r0], #4\n"
	"str	r1, [r0]\n"
	"bl	sub_ff879ae4\n" // SD780 was FF879A94
	"bl	sub_ff87f6d0\n" // SD780 was FF87F680
	"bl	sub_ff87ccc4\n" // SD780 was FF87CC74
	"bl	sub_ff87a628_my\n" // SD780 was FF87A5D8_my -> taskcreate_CaptSeqTask
	"bl	sub_ff87b6d8\n" // SD780 was FF87B688
"loc_ff878dd8:\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"str	r0, [r4, #12]\n"
	"pop	{r4, pc}\n"
    );
}

void __attribute__((naked,noinline)) sub_ff87a628_my() { // was sub_FF87A5D8_my
  asm volatile (
	"push	{r3, r4, r5, lr}\n"
	"ldr	r2, =0x00039578\n" // was: "[pc, #-1920]	; ff879eb4" 
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
"loc_ff87a638:\n"
	"add	r3, r2, r0, lsl #4\n"
	"add	r0, r0, #1\n"	// 0x1
	"cmp	r0, #5\n"	// 0x5
	"str	r1, [r3, #8]\n"
	"bcc	loc_ff87a638\n"
	"bl	sub_ff87b214\n" // was FF87A5E8
	"bl	sub_ff95f458\n" // was FF95F3A0
	"bl	sub_ff960018\n" // was FF95FF60
	"ldr	r1, =0x5\n" // was: "mov ..., #5"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f2c\n" // was FF839F2C KernelMisc.c:31
	"ldr	r4, =0x00002b9c\n" // was: "[pc, #-2000]	; ff879e9c" 
	"ldr	r1, =0x00101dff\n" // was: "[pc, #-1968]	; ff879ec0" 
	"str	r0, [r4, #4]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f50\n" // was FF839F50 KernelMisc.c:43
	"str	r0, [r4]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff839f74\n" // was FF839F74 KernelMisc.c:55
	"str	r0, [r4, #8]\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	"ldr    r3, =0xff87a310\n" // was "sub	r3, pc, #908\n"	// ff87a310: (e92d43f8) 
	"ldr    r0, =0xff87a898\n" // was "add	r0, pc, #504\n"	// ff87a898: (74706143)  *"CaptSeqTask"
	"ldr	r2, =0x1000\n" // was: "mov ..., #4096"
	"ldr	r1, =0x17\n" // was: "mov ..., #23"
	"bl	sub_ff839ef8\n" // was FF839EF8 KernelCreateTask ; LOCATION: KernelMisc.c:19
	"pop	{r3, r4, r5, pc}\n"
    );
}

void __attribute__((naked,noinline)) sub_ff834230_my() {
  asm volatile (
	"push	{r3, r4, r5, lr}\n"
	"ldr	r4, =0x00001c20\n" // was: "[pc, #476]	; ff834418" 
	"ldr	r0, [r4, #16]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff834264\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	"ldr	r3, =0xff8341fc\n" // was: "sub	r3, pc, #88"  
        // Increate stack size from 0x800 to 0x2000 for new task_PhySw so we don't have to do stack switch
	"ldr	r2, =0x2000\n" // was: "mov ..., #2048"
	"ldr	r1, =0x17\n" // was: "mov ..., #23"
	"ldr	r0, =0xff834438\n" // was: "add	r0, pc, #472"   *"PhySw"
	"bl	sub_ff839ef8\n" // KernelCreateTask
	"str	r0, [r4, #16]\n"
"loc_ff834264:\n"
	"bl	sub_ff88a644\n" // was FF88A5F4
	"bl	sub_ff835aa4\n" // was FF835AA4 IsFactoryMode
	"cmp	r0, #0\n"	// 0x0
	"ldreq	r1, =0x0003280c\n" // was: "[pc, #428]	; ff834424" 
	"popeq	{r3, r4, r5, lr}\n"
	"beq	sub_ff88a5cc\n" // was FF88A57C eventproc_export_OpLog_Start
	"pop	{r3, r4, r5, pc}\n"
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
