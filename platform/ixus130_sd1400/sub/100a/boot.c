#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"
#include "led.h"

const char * const new_sa = &_end;

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

void __attribute__((naked,noinline)) init_file_modules_task() {    // FF89467C
  asm volatile (
        "push   {r4, r5, r6, lr}\n"
        "bl     sub_FF88CAC0\n" 
        "ldr    r5, =0x00005006\n" // was: "[pc, #408]  ; ff894874" 
        "movs   r4, r0\n"
        "ldrne  r1, =0x0\n" // was: "mov ..., #0"
        "movne  r0, r5\n"
        "blne   sub_FF8904CC\n" 
        "bl     sub_FF88CAEC\n" 
        //"bl     sub_ff88cb3c_my\n"
		"bl     core_spytask_can_start\n"
        "cmp    r4, #0\n"       // 0x0
        "moveq  r0, r5\n"
        "popeq  {r4, r5, r6, lr}\n"
        "ldreq  r1, =0x0\n" // was: "mov ..., #0"
        "beq    sub_FF8904CC\n" 
    );
  led_flash(LED_RED, 1);
  asm volatile (
        "pop    {r4, r5, r6, pc}\n"
    );
};

void taskHook(context_t **context) {
  task_t * tcb = (task_t*)((char*)context - offsetof(task_t, context));
  if (!_strcmp(tcb->name, "PhySw"))           tcb->entry = (void*)mykbd_task;
  if (!_strcmp(tcb->name, "CaptSeqTask"))     tcb->entry = (void*)capt_seq_task;
  if (!_strcmp(tcb->name, "InitFileModules")) tcb->entry = (void*)init_file_modules_task;
  if (!_strcmp(tcb->name, "MovieRecord"))     tcb->entry = (void*)movie_record_task;
  if (!_strcmp(tcb->name, "ExpDrvTask"))      tcb->entry = (void*)exp_drv_task;
  //if (!_strcmp(tcb->name, "RotarySw"))        tcb->entry = (void*)JogDial_task_my;
  //led_flash(LED_GREEN, 1);
}

void CreateTask_spytask() {
  _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

void __attribute__((naked,noinline)) boot() {
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
	"ldr	r0, =0xFFBF837C\n" // canon_data_src 
	"ldr	r1, =0x1900\n"     // MEMBASEADDR 
	"ldr	r3, =0xebd0\n"     // canon_bss_start
"loc_ff81013c:\n"
	"cmp	r1, r3\n"
	"ldrcc	r2, [r0], #4\n"
	"strcc	r2, [r1], #4\n"
	"bcc	loc_ff81013c\n"
	"ldr	r1, =0x0014fe20\n" // MEMISOSTART
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
"loc_ff810154:\n"
	"cmp	r3, r1\n"
	"strcc	r2, [r3], #4\n"
	"bcc	loc_ff810154\n"
	"b	sub_ff810354_my\n"
    );
}

void __attribute__((naked,noinline)) sub_ff810354_my() { //??? was FF8101A0
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
  // Power Button detection (short press = playback mode, long press = record mode)
  // replacement for sub_ff834348
  *(int*)0x2480 = (*(int*)0xC0220128) & 1 ? 0x400000 : 0x200000;
  // Long press on play to start in playback mode:
  //*(int*)0x2480 = (*(int*)0xc022012c) & 1 ? 0x200000 : 0x400000;
	
  //*(int*)0x1934 = (int)taskHook;
  *(int*)0x1938 = (int)taskHook;
	
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
	"bl	sub_FFB39910\n" 
	"ldr	r0, =0x53000\n" // was: "mov ..., #339968"
	"str	r0, [sp, #4]\n"

	"ldr	r0, =new_sa\n" // Replaces original start location 0x14fe20
        "ldr    r0, [r0]\n"

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
	"ldr	r1, =uHwSetup_my\n" // was: "[pc, #104]	; ff811258"
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

void __attribute__((naked,noinline)) uHwSetup_my() { // 0xff815e58
  asm volatile (
	"push	{r4, lr}\n"
	"bl	sub_ff810b20\n"
	"bl	sub_ff81a244\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrlt	r0, =0xff815f6c\n" // was: "addlt	r0, pc, #252"   *"dmSetup"
	"bllt	sub_ff815f4c\n"
	"bl	sub_ff815a94\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrlt	r0, =0xff815f74\n" // was: "addlt	r0, pc, #244"   *"termDriverInit"
	"bllt	sub_ff815f4c\n"
	"ldr	r0, =0xff815f84\n" // was: "add	r0, pc, #252"   *"/_term"
	"bl	sub_ff815b7c\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrlt	r0, =0xff815f8c\n" // was: "addlt	r0, pc, #248"   *"termDeviceCreate"
	"bllt	sub_ff815f4c\n"
	"ldr	r0, =0xff815f84\n" // was: "add	r0, pc, #232"   *"/_term"
	"bl	sub_ff813bf0\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrlt	r0, =0xff815fa0\n" // was: "addlt	r0, pc, #248"   *"stdioSetup"
	"bllt	sub_ff815f4c\n"
	"bl	sub_ff819c3c\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrlt	r0, =0xff815fac\n" // was: "addlt	r0, pc, #244"   *"stdlibSetup"
	"bllt	sub_ff815f4c\n"
	"bl	sub_ff81167c\n"
	"cmp	r0, #0\n"	// 0x0
	"ldrlt	r0, =0xff815fb8\n" // was: "addlt	r0, pc, #240"   *"armlib_setup"
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
	//"bl	sub_ff834348\n" // disabled for correct Power Button detection
	//"bl	sub_ff834344\n" // nullsub
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
	//"bl	sub_ff83bb5c\n" // original: StartSdInit() -> StartDiskboot()
    );

  CreateTask_spytask();
  //led_flash(LED_RED, 1);
   //CreateTask_blinker();

  asm volatile (
	"bl	sub_ff83be58\n"
	"bl	sub_ff8322e4\n"
	"bl	sub_ff83bce4\n"
	"bl	sub_ff839454\n"
	"bl	sub_ff83be5c\n"
	"bl	taskcreate_PhySw_my\n" // sub_ff834230
	//"bl	sub_ff834230\n"
	"bl	task_ShootSeqTask_my\n" // sub_ff8377a8 taskcreate_SsTask -> for shoot seq stuff
	//"bl	sub_ff8377a8\n" // sub_ff8377a8 taskcreate_SsTask -> for shoot seq stuff
	"bl	sub_ff83be74\n"
	//"bl	sub_ff8316a8\n" // nullsub
	"bl	sub_ff833090\n" // Battery.c:0
	"bl	sub_ff83b860\n" // taskcreate_Bye
	"bl	sub_ff8335ec\n"
	"bl	sub_ff83302c\n" // taskcreate_BatteryTask / taskcreate_TempCheck
	"bl	sub_ff832318\n"
	"bl	sub_ff83c8f4\n" // taskcreate_FactoryModeController
	"bl	sub_ff833004\n" // taskcreate_Ui
	"pop	{r4, lr}\n"
	"b	sub_ff81662c\n" // MLHClock.c:992
    );
}

void __attribute__((naked,noinline)) taskcreate_PhySw_my() { // 0xff834230
  asm volatile (
	"push	{r3, r4, r5, lr}\n"
	"ldr	r4, =0x00001c20\n" // was: "[pc, #476]	; ff834418" 
	"ldr	r0, [r4, #16]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_ff834264\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	//"ldr	r3, =0xff8341fc\n" //   
	"ldr	r3, =mykbd_task\n" // 0xff8341fc  
        // Increate stack size from 0x800 to 0x2000 for new task_PhySw so we don't have to do stack switch
	"ldr	r2, =0x2000\n"
	//"ldr	r2, =0x800\n" // was: "mov ..., #2048"
	"ldr	r1, =0x17\n" // was: "mov ..., #23"
	"ldr	r0, =0xff834438\n" // was: "add	r0, pc, #472"   *"PhySw"
	"bl	sub_ff839ef8\n" // KernelCreateTask
	"str	r0, [r4, #16]\n"
"loc_ff834264:\n"
	"bl	sub_FF88A5F4\n" 
	"bl	sub_ff835aa4\n" // IsFactoryMode
	"cmp	r0, #0\n"	// 0x0
	"ldreq	r1, =0x0003280c\n" // was: "[pc, #428]	; ff834424" 
	"popeq	{r3, r4, r5, lr}\n"
	"beq	sub_FF88A57C\n" // eventproc_export_OpLog_Start
	"pop	{r3, r4, r5, pc}\n"
    );
}

void __attribute__((naked,noinline)) task_ShootSeqTask_my() { //FF8377A8
asm volatile (
	"push	{r4, lr}\n"
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f50\n"
	"ldr	r4, =0x00001c7c\n" // was: "[pc, #-492]	; ff8375d4" 
	"str	r0, [r4, #16]\n"
	"bl	sub_FF87F19C\n" 
	"bl	sub_FF8808E4\n" // taskcreate_SsTask 
	"bl	sub_FF87E2E4\n" 
	"bl	sub_ff878d6c_my\n" 
	"bl	sub_FF87F480\n" 
	"ldr	r0, [r4, #16]\n"
	"pop	{r4, lr}\n"
	"ldr	r1, =0x1000\n" // was: "mov ..., #4096"
	"b	sub_FF883F4C\n" 
  );
}

void __attribute__((naked,noinline)) sub_ff878d6c_my() { // was FF878D1C_my FF878D1C 
  asm volatile (
	"push	{r4, lr}\n"
	"ldr	r4, =0x00002b64\n" // was: "[pc, #-3512]	; ff877fc0" 
	"ldr	r0, [r4, #12]\n"
	"cmp	r0, #0\n"	// 0x0
	"bne	loc_FF878D88\n"
	"bl	sub_FF87C848\n" // nullsub 
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f74\n" // KernelMisc.c:55
	"str	r0, [r4, #4]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x8\n" // was: "mov ..., #8"
	"bl	sub_ff839f50\n" // KernelMisc.c:43
	"str	r0, [r4, #8]\n"
	"bl	sub_FF8790FC\n" 
	"bl	sub_FF879884\n" 
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r0, [r4]\n"
	"add	r0, r4, #16\n"	// 0x10
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
	"str	r1, [r0], #4\n"
	"str	r1, [r0]\n"
	"bl	sub_FF879A94\n" 
	"bl	sub_FF87F680\n" 
	"bl	sub_FF87CC74\n" 
	"bl	sub_ff87a5d8_my\n" // taskcreate_CaptSeqTask
	"bl	sub_ff87b688\n" 
"loc_FF878D88:\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"str	r0, [r4, #12]\n"
	"pop	{r4, pc}\n"
    );
}

void __attribute__((naked,noinline)) sub_ff87a5d8_my() { // was sub_ff87a5d8_my
  asm volatile (  //FF87A5D8
	"push	{r3, r4, r5, lr}\n"
	"ldr	r2, =0x00039578\n" // was: "[pc, #-1920]	; ff879eb4" 
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x0\n" // was: "mov ..., #0"
"loc_FF87A5E8:\n"  //WAS loc_ff87a638
	"add	r3, r2, r0, lsl #4\n"
	"add	r0, r0, #1\n"	// 0x1
	"cmp	r0, #5\n"	// 0x5
	"str	r1, [r3, #8]\n"
	"bcc	loc_FF87A5E8\n" 
	"bl	sub_FF87B1C4\n" 
	"bl	sub_FF95F3A0\n" // nullsub 
	"bl	sub_FF95FF60\n" 
	"ldr	r1, =0x5\n" // was: "mov ..., #5"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f2c\n" // KernelMisc.c:31
	"ldr	r4, =0x00002b9c\n" // was: "[pc, #-2000]	; ff879e9c" 
	"ldr	r1, =0x00101dff\n" // was: "[pc, #-1968]	; ff879ec0" 
	"str	r0, [r4, #4]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bl	sub_ff839f50\n" // KernelMisc.c:43
	"str	r0, [r4]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x1\n" // was: "mov ..., #1"
	"bl	sub_ff839f74\n" // KernelMisc.c:55
	"str	r0, [r4, #8]\n"
	"ldr	r3, =0x0\n" // was: "mov ..., #0"
	"str	r3, [sp]\n"
	//"ldr    r3, =capt_seq_task\n"
	"ldr    r3, =0xFF87A2C0\n" // capt_seq_task 
	"ldr    r0, =0xFF87A848\n" // *"CaptSeqTask" 
	"ldr	r2, =0x1000\n" // was: "mov ..., #4096"
	"ldr	r1, =0x17\n" // was: "mov ..., #23"
	"bl	sub_ff839ef8\n" // was FF839EF8 KernelCreateTask ; LOCATION: KernelMisc.c:19
	"pop	{r3, r4, r5, pc}\n"
    );
}

//****************
/*
void __attribute__((naked,noinline)) sub_ff88cb3c_my() {    // sub_FF88FF58_my
  asm volatile (
        "push   {r4, lr}\n"
        "ldr    r0, =0x3\n" // was: "mov ..., #3"
        "bl     sub_ff86f084_my\n"
        "bl     sub_ff94002c\n"
        "ldr    r4, =0x00002f54\n" // was: "[pc, #112]  ; ff88cbc4" 
        "ldr    r0, [r4, #4]\n"
        "cmp    r0, #0\n"       // 0x0
        "bne    loc_ff88cb74\n"
        "bl     sub_ff86e2cc\n"
        "bl     sub_ff9344f0\n"
        "bl     sub_ff86e2cc\n"
        "bl     sub_ff86a6f0\n"
        "bl     sub_ff86e1cc\n"
        "bl     sub_ff93458c\n"
"loc_ff88cb74:\n"
        "ldr    r0, =0x1\n" // was: "mov ..., #1"
        "str    r0, [r4]\n"
        "pop    {r4, pc}\n"
    );
};

void __attribute__((naked,noinline)) sub_ff86f084_my() {    // sub_FF871A04_my
  asm volatile (
        "push   {r4, r5, r6, r7, r8, lr}\n"
        "mov    r8, r0\n"
        "bl     sub_ff86f004\n"
        "ldr    r1, =0x00038448\n" // was: "[pc, #-2052]        ; ff86e894" 
        "mov    r6, r0\n"
        "add    r4, r1, r0, lsl #7\n"
        "ldr    r0, [r4, #108]\n"
        "cmp    r0, #4\n"       // 0x4
        "ldreq  r1, =0x0000085a\n" // was: "[pc, #208]  ; ff86f17c" 
        "ldreq  r0, =0xff86eb44\n" // was: "[pc, #200]  ; ff86f178"  **"Mounter.c"
        "bleq   sub_ff81eb14\n"
        "mov    r1, r8\n"
        "mov    r0, r6\n"
        "bl     sub_ff86e8bc\n"
        "ldr    r0, [r4, #56]\n"
        "bl     sub_ff86f724\n"
        "cmp    r0, #0\n"       // 0x0
        "streq  r0, [r4, #108]\n"
        "mov    r0, r6\n"
        "bl     sub_ff86e94c\n"
        "mov    r0, r6\n"
        "bl     sub_ff86ecac\n"
        "mov    r5, r0\n"
        "mov    r0, r6\n"
        "bl     sub_ff86eedc_my\n"
        "ldr    r6, [r4, #60]\n"
        "and    r7, r5, r0\n"
        "cmp    r6, #0\n"       // 0x0
        "ldr    r1, [r4, #56]\n"
        "ldreq  r0, =0x80000001\n" // was: "mov ..., #-2147483647"
        "ldr    r5, =0x0\n" // was: "mov ..., #0"
        "beq    loc_ff86f134\n"
        "mov    r0, r1\n"
        "bl     sub_ff86e434\n"
        "cmp    r0, #0\n"       // 0x0
        "ldrne  r5, =0x4\n" // was: "mov ..., #4"
        "cmp    r6, #5\n"       // 0x5
        "orrne  r0, r5, #1\n"   // 0x1
        "biceq  r0, r5, #1\n"   // 0x1
        "cmp    r7, #0\n"       // 0x0
        "biceq  r0, r0, #2\n"   // 0x2
        "orreq  r0, r0, #0x80000000\n"
        "bicne  r0, r0, #0x80000000\n"
        "orrne  r0, r0, #2\n"   // 0x2
"loc_ff86f134:\n"
        "cmp    r8, #7\n"       // 0x7
        "str    r0, [r4, #64]\n"
        "popne  {r4, r5, r6, r7, r8, pc}\n"
        "mov    r0, r8\n"
        "bl     sub_ff86f054\n"
        "cmp    r0, #0\n"       // 0x0
        "popeq  {r4, r5, r6, r7, r8, lr}\n"
        "ldreq  r0, =0xff86f180\n" // was: "addeq       r0, pc, #40"   *"EMEM MOUNT ERROR!!!"
        "beq    sub_ff81177c\n"
        "pop    {r4, r5, r6, r7, r8, pc}\n"
    );
};

void __attribute__((naked,noinline)) sub_ff86eedc_my() {    // FF87185C
  asm volatile (
	"push	{r3, r4, r5, r6, r7, r8, r9, lr}\n"
	"mov	r5, r0\n"
	"ldr	r0, =0xff86f16c\n" // was: "add	r0, pc, #640"  
	"ldr	r0, [r0]\n"
	"ldr	r9, =0x00038448\n" // was: "[pc, #-1632]	; ff86e894" 
	"str	r0, [sp]\n"
	"add	r4, r9, r5, lsl #7\n"
	"ldr	r0, [r4, #108]\n"
	"tst	r0, #4\n"	// 0x4
	"ldrne	r0, =0x1\n" // was: "mov ..., #1"
	"bne	loc_ff86ef48\n"
	"ldr	r0, [r4, #60]\n"
	"ldr	r6, =0x00002968\n" // was: "[pc, #-1672]	; ff86e88c" 
	"cmp	r0, #6\n"	// 0x6
	"ldr	r8, =0x1\n" // was: "mov ..., #1"
	"ldr	r7, =0x0\n" // was: "mov ..., #0"
	"addls	pc, pc, r0, lsl #2\n"
	"b	loc_ff86efa8\n"
	"b	loc_ff86ef40\n"
	"b	loc_ff86ef4c\n"
	"b	loc_ff86ef4c\n"
	"b	loc_ff86ef4c\n"
	"b	loc_ff86ef4c\n"
	"b	loc_ff86ef64\n"
	"b	loc_ff86ef4c\n"
"loc_ff86ef40:\n" // jumptable entry 0
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r7, [r4, #108]\n"
"loc_ff86ef48:\n"
	"pop	{r3, r4, r5, r6, r7, r8, r9, pc}\n"
"loc_ff86ef4c:\n" // 5 refs, jumptable entries 1-4,6
	"ldr	r0, [r4, #56]\n"
	"bl	sub_ff86e434\n"
	"cmp	r0, #0\n"	// 0x0
	"streq	r7, [r6, #16]\n"
	"strne	r8, [r6, #16]\n"
	"b	loc_ff86efb4\n"
"loc_ff86ef64:\n" // jumptable entry 5
	"ldr	r2, =0x0\n" // was: "mov ..., #0"
	"ldr	r1, =0x8000\n" // was: "mov ..., #32768"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"str	r8, [r6, #16]\n"
	"bl	sub_ff886bc0\n"
	"mov	r6, r0\n"
	"mov	r2, r4\n"
	"ldr	r1, =0x8000\n" // was: "mov ..., #32768"
	"bl	sub_ff941dd8\n"
	"ldr	r0, [r9, r5, lsl #7]\n"
	"mov	r1, r6\n"
	"str	r0, [r4, #80]\n"
	"ldr	r0, [r4, #4]\n"
	"str	r0, [r4, #84]\n"
	"mov	r0, r5\n"
	"bl	sub_ff86e578\n"
	"b	loc_ff86efb4\n"
"loc_ff86efa8:\n" // jumptable default entry
	"ldr	r1, =0x000006c1\n" // was: "[pc, #448]	; ff86f170" 
	"ldr	r0, =0xff86eb44\n" // was: "sub	r0, pc, #1136"   *"Mounter.c"
	"bl	sub_ff81eb14\n"
"loc_ff86efb4:\n" // 2 refs
	"mov	r0, r5\n"
	"bl	sub_ff86e1d4\n"
	"strb	r0, [sp]\n"
	"mov	r0, r5\n"
	"mov	r1, sp\n"
	"bl	sub_ff86edac\n"
	"cmn	r0, #1\n"	// 0x1
	"bne	loc_ff86eff4\n"
	"ldr	r1, =0x000384c8\n" // was: "[pc, #-1860]	; ff86e898" 
	"add	r0, r5, r5, lsl #4\n"
	"str	r7, [r1, r0, lsl #2]\n"
	"ldr	r1, [r4, #108]\n"
	"ldr	r0, =0x0\n" // was: "mov ..., #0"
	"bic	r1, r1, #6\n"	// 0x6
"loc_ff86efec:\n"
	"str	r1, [r4, #108]\n"
	"pop	{r3, r4, r5, r6, r7, r8, r9, pc}\n"
"loc_ff86eff4:\n"
	"ldr	r1, [r4, #108]\n"
	"ldr	r0, =0x1\n" // was: "mov ..., #1"
	"orr	r1, r1, #4\n"	// 0x4
	"b	loc_ff86efec\n"
    );
};
*/
