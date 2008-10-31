/**
    this code completely copied from ../100k + adapted to the 100j firmware
    + very slight fixups
    + moved 'BL shooting_expo_param_override' up a bit so it does not interfere
        with the BEQ following it
        => shooting series works!
        
    Known bugs: setting the ISO < 58 results in whitescreen + poweroff
        (take care when setting autoiso parameters!)
*/
#include "lolevel.h"
#include "platform.h"
#include "core.h"

//#include "../../../generic/capt_seq.c"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (1)
#define NR_OFF (0)

static long raw_save_stage;

void __attribute__((naked,noinline)) capt_seq_hook_raw_here()
{
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");
	long save_count=0; 
	volatile long *p; p=(void*) 0xc02200E4; 
	 *p=0x46;
	 
	 
	raw_save_stage = RAWDATA_AVAILABLE;
	core_rawdata_available();
	while (raw_save_stage != RAWDATA_SAVED){
		_SleepTask(10);
		save_count++;
		if (save_count>20){
			*p=0x46;
			save_count=0;
		}else if(save_count>10){
			*p=0;
		}
	}
		
	 *p=0;
 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}


void capt_seq_hook_set_nr()
{
	return;
#if 0
    long *nrflag = (long*)0x53EC;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = 0;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = 1;
	break;
    };
#endif
}

// dk: ok
void __attribute__((naked,noinline)) sub_FF955474_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "LDR     R3, =0x53E4\n"
                "SUB     SP, SP, #4\n"
                "LDR     R2, [R3]\n"
                "LDR     R4, =0x53E8\n"
                "CMP     R2, #0\n"
                "STR     R0, [R4]\n"
                "MOV     R8, #0\n"
                "LDR     R6, =0xFF9553AC\n"
                "BNE     loc_FF9554A8\n"
                "LDR     R0, =0xFF955468\n"
                "MOV     R1, #0xDB\n"
                "BL      sub_FF813E68\n"
"loc_FF9554A8:\n"
                "LDR     R3, =0x6FCFC\n"
                "LDR     R1, =0xFFFFFFFF\n"
                "LDR     R0, [R3]\n"
                "BL      sub_FF81FF3C\n"
                "BL      sub_FF9553E4\n"
	    	"BL      capt_seq_hook_set_nr\n"

		"B       sub_FF9554BC\n"
    );
}


// dk: ok
void __attribute__((naked,noinline)) sub_ff9432b8_my()
{

asm volatile (

/*	
ff9432b8: 	e92d4070 	stmdb	sp!, {r4, r5, r6, lr}
ff9432bc: 	e59f31a8 	ldr	r3, [pc, #424]	; ff94346c: (00005b70) 
ff9432c0: 	e5932000 	ldr	r2, [r3]
ff9432c4: 	e3520000 	cmp	r2, #0	; 0x0
ff9432c8: 	0a00000b 	beq	ff9432fc <_binary_dump_bin_start+0x1332fc>
ff9432cc: 	e59f319c 	ldr	r3, [pc, #412]	; ff943470: (00005b90) 
ff9432d0: 	e5932000 	ldr	r2, [r3]
ff9432d4: 	e3520000 	cmp	r2, #0	; 0x0
ff9432d8: 	0a000007 	beq	ff9432fc <_binary_dump_bin_start+0x1332fc>
ff9432dc: 	e59f3190 	ldr	r3, [pc, #400]	; ff943474: (00005b74) 
ff9432e0: 	e5932000 	ldr	r2, [r3]
ff9432e4: 	e3520000 	cmp	r2, #0	; 0x0
ff9432e8: 	0a000003 	beq	ff9432fc <_binary_dump_bin_start+0x1332fc>
ff9432ec: 	e59f3184 	ldr	r3, [pc, #388]	; ff943478: (00005bb0) 
ff9432f0: 	e5932000 	ldr	r2, [r3]
ff9432f4: 	e3520000 	cmp	r2, #0	; 0x0
ff9432f8: 	1a000004 	bne	ff943310 <_binary_dump_bin_start+0x133310>
*/
	"STMFD   SP!, {R4,R5,R6,LR}\n"
	"LDR     R3, =0x5B70\n"
	"LDR     R2, [R3]\n"
	"CMP     R2, #0\n"
	"BEQ     loc_FF9432FC\n" //ok
	"LDR     R3, =0x5B90\n"
	"LDR     R2, [R3]\n"
	"CMP     R2, #0\n"
	"BEQ     loc_FF9432FC\n" //ok
	"LDR     R3, =0x5B74\n"
	"LDR     R2, [R3]\n"
	"CMP     R2, #0\n"
	"BEQ     loc_FF9432FC\n" //ok
	"LDR     R3, =0x5BB0\n"
	"LDR     R2, [R3]\n"
	"CMP     R2, #0\n"
	"BNE     loc_FF943310\n" //
		
"loc_FF9432FC:\n"
/*
ff9432fc: 	e3a02e52 	mov	r2, #1312	; 0x520
ff943300: 	e59f0174 	ldr	r0, [pc, #372]	; ff94347c: (ff9431dc)  **"m_pSettingForPrepare != 
ff943304: 	e59f1174 	ldr	r1, [pc, #372]	; ff943480: (ff941b94)  **"CaptSeq.c"
ff943308: 	e2822002 	add	r2, r2, #2	; 0x2
ff94330c: 	ebfb463f 	bl	ff814c10 <_binary_dump_bin_start+0x4c10>
*/
	"MOV     R2, #0x520\n"
	"LDR     R0, =0xff9431dc\n" //debug string loc
	"LDR     R1, =0xff941b94\n" //debug string loc
	"ADD     R2, R2, #2\n"
	"BL      sub_FF814C10\n" //debugAssert
//	"ldr pc, =0xff943310\n" // dk: huh? => commented out
		
		
"loc_FF943310:\n"
/*
ff943310: 	ebfff9bf 	bl	ff941a14 <_binary_dump_bin_start+0x131a14>
ff943314: 	e3500000 	cmp	r0, #0	; 0x0
ff943318: 	1a00000b 	bne	ff94334c <_binary_dump_bin_start+0x13334c>
ff94331c: 	e59f314c 	ldr	r3, [pc, #332]	; ff943470: (00005b90) 
ff943320: 	e5932000 	ldr	r2, [r3]
ff943324: 	e5921004 	ldr	r1, [r2, #4]
ff943328: 	e3510000 	cmp	r1, #0	; 0x0
ff94332c: 	0a000006 	beq	ff94334c <_binary_dump_bin_start+0x13334c>
ff943330: 	e59f014c 	ldr	r0, [pc, #332]	; ff943484: (ff943264) 
ff943334: 	eb05f418 	bl	ffac039c <_binary_dump_bin_start+0x2b039c>
ff943338: 	e59f0148 	ldr	r0, [pc, #328]	; ff943488: (ff943284) 
ff94333c: 	eb05f416 	bl	ffac039c <_binary_dump_bin_start+0x2b039c>
ff943340: 	ebfff9c0 	bl	ff941a48 <_binary_dump_bin_start+0x131a48>
*/
	"BL      sub_FF941A14\n"
	"CMP     R0, #0\n"
	"BNE     loc_FF94334C\n" //ok
	"LDR     R3, =0x5B90\n"
	"LDR     R2, [R3]\n"
	"LDR     R1, [R2,#4]\n"
	"CMP     R1, #0\n"
	"BEQ     loc_FF94334C\n" //ok
	"LDR     R0, =0xff943264\n" //debug string loc
	"BL      sub_ffac039c\n" //printf
	"LDR     R0, =0xff943284\n" //debug string loc
	"BL      sub_ffac039c\n" //printf
	
	//ok ?!	
	"BL      sub_FF941A48\n"
		
/*
ff943344: 	e59f0140 	ldr	r0, [pc, #320]	; ff94348c: (ff9432a8)  **"Completed!!"
ff943348: 	eb05f413 	bl	ffac039c <_binary_dump_bin_start+0x2b039c>
*/
		
	"LDR     R0, =0xff9432a8\n" //debug string lco
	"BL      sub_ffac039c\n" //printf
"loc_FF94334C:\n"

/*
ff94334c: 	e59f313c 	ldr	r3, [pc, #316]	; ff943490: (0006763c) 
ff943350: 	e3e04000 	mvn	r4, #0	; 0x0
ff943354: 	e5930000 	ldr	r0, [r3]
ff943358: 	e1a01004 	mov	r1, r4
ff94335c: 	ebfb7a54 	bl	ff821cb4 <_binary_dump_bin_start+0x11cb4>
*/
	"LDR     R3, =0x6763C\n"
	"MVN     R4, #0\n" //0xFFFFFFFF
	"LDR     R0, [R3]\n"
	"MOV     R1, R4\n"
	"BL      sub_ff821cb4\n" //ClearEventFlag ?! //####
	
/*
ff943360: 	e59f312c 	ldr	r3, [pc, #300]	; ff943494: (00067640) 
ff943364: 	e1a01004 	mov	r1, r4
ff943368: 	e5930000 	ldr	r0, [r3]
ff94336c: 	ebfb7a50 	bl	ff821cb4 <_binary_dump_bin_start+0x11cb4>
*/
	"LDR     R3, =0x67640\n"
	"MOV     R1, R4\n"
	"LDR     R0, [R3]\n"
	"BL      sub_ff821cb4\n" //ClearEventFlag ?! //####

/*
ff943370: 	e59f3120 	ldr	r3, [pc, #288]	; ff943498: (00005b80) 
ff943374: 	e5933000 	ldr	r3, [r3]
ff943378: 	e3530001 	cmp	r3, #1	; 0x1
ff94337c: 	13530003 	cmpne	r3, #3	; 0x3
*/

	//before take
  "BL      capt_seq_hook_set_nr\n" // + do noise reduction set
  "BL      shooting_expo_param_override\n"  // + seems to be working :)

	"LDR     R3, =0x5B80\n"
	"LDR     R3, [R3]\n"
	"CMP     R3, #1\n"
	"CMPNE   R3, #3\n"
		
/*
ff943380: 	0a00000e 	beq	ff9433c0 <_binary_dump_bin_start+0x1333c0>
ff943384: 	e3530004 	cmp	r3, #4	; 0x4
ff943388: 	0a00000c 	beq	ff9433c0 <_binary_dump_bin_start+0x1333c0>
ff94338c: 	e59f30e0 	ldr	r3, [pc, #224]	; ff943474: (00005b74) 
ff943390: 	e5932000 	ldr	r2, [r3]
ff943394: 	e1d210b2 	ldrh	r1, [r2, #2]
ff943398: 	e3510001 	cmp	r1, #1	; 0x1
ff94339c: 	1a000006 	bne	ff9433bc <_binary_dump_bin_start+0x1333bc>
ff9433a0: 	e59f30d0 	ldr	r3, [pc, #208]	; ff943478: (00005bb0) 
ff9433a4: 	e5932000 	ldr	r2, [r3]
ff9433a8: 	e5921008 	ldr	r1, [r2, #8]
ff9433ac: 	e3510001 	cmp	r1, #1	; 0x1
ff9433b0: 	9a000001 	bls	ff9433bc <_binary_dump_bin_start+0x1333bc>
*/
	"BEQ     loc_FF9433C0\n"
		
	"CMP     R3, #4\n"
	"BEQ     loc_FF9433C0\n"
	"LDR     R3, =0x5B74\n"
	"LDR     R2, [R3]\n"
	"LDRH    R1, [R2,#2]\n"
	"CMP     R1, #1\n"
	"BNE     loc_FF9433BC\n"
	"LDR     R3, =0x5BB0\n"
	"LDR     R2, [R3]\n"
	"LDR     R1, [R2,#8]\n"
	"CMP     R1, #1\n"
	"BLS     loc_FF9433BC\n"
	
/*
ff9433b4: 	ebfffbe6 	bl	ff942354 <_binary_dump_bin_start+0x132354>
ff9433b8: 	ea000000 	b	ff9433c0 <_binary_dump_bin_start+0x1333c0>
*/
	///???
	"BL      sub_FF942354\n"
		
	"B       loc_FF9433C0\n"
		
"loc_FF9433BC:\n"
//ff9433bc: 	ebfffd70 	bl	ff942984 <_binary_dump_bin_start+0x132984>
	"BL      sub_FF942984\n"
		
"loc_FF9433C0:\n"
/*
ff9433c0: 	ebfffe29 	bl	ff942c6c <_binary_dump_bin_start+0x132c6c>
ff9433c4: 	e1a04000 	mov	r4, r0
ff9433c8: 	e3140001 	tst	r4, #1	; 0x1
ff9433cc: 	0a00000c 	beq	ff943404 <_binary_dump_bin_start+0x133404>
ff9433d0: 	e59f60c4 	ldr	r6, [pc, #196]	; ff94349c: (00005bc4) 
ff9433d4: 	e5962000 	ldr	r2, [r6]
ff9433d8: 	e3520000 	cmp	r2, #0	; 0x0
ff9433dc: 	0a000003 	beq	ff9433f0 <_binary_dump_bin_start+0x1333f0>
ff9433e0: 	e59f30b8 	ldr	r3, [pc, #184]	; ff9434a0: (00005bc8) 
ff9433e4: 	e5931000 	ldr	r1, [r3]
ff9433e8: 	e1a0e00f 	mov	lr, pc
ff9433ec: 	e1a0f002 	mov	pc, r2
*/
	"BL      sub_FF942C6C\n"
	"MOV     R4, R0\n"
	"TST     R4, #1\n"
	"BEQ     loc_FF943404\n"
	"LDR     R6, =0x5BC4\n"
	"LDR     R2, [R6]\n"
	"CMP     R2, #0\n"
	"BEQ     loc_FF9433F0\n"
	"LDR     R3, =0x5BC8\n"
	"LDR     R1, [R3]\n"
	"MOV     LR, PC\n"
	"MOV     PC, R2\n"
		
"loc_FF9433F0:\n"
/*
ff9433f0: 	e59f50ac 	ldr	r5, [pc, #172]	; ff9434a4: (00067638) 
ff9433f4: 	e3a01002 	mov	r1, #2	; 0x2
ff9433f8: 	e5950000 	ldr	r0, [r5]
ff9433fc: 	ebfb79c7 	bl	ff821b20 <_binary_dump_bin_start+0x11b20>
ff943400: 	ea000001 	b	ff94340c <_binary_dump_bin_start+0x13340c>
*/
	"LDR     R5, =0x67638\n"
	"MOV     R1, #2\n"
	"LDR     R0, [R5]\n"
	"BL      sub_FF821B20\n" //SetEventFlag?
	"B       loc_FF94340C\n"

"loc_FF943404:\n"
//ff943404: 	e59f6090 	ldr	r6, [pc, #144]	; ff94349c: (00005bc4) 
//ff943408: 	e59f5094 	ldr	r5, [pc, #148]	; ff9434a4: (00067638) 

	"LDR     R6, =0x5BC4\n"
	"LDR     R5, =0x67638\n"
	
"loc_FF94340C:\n"
/*
ff94340c: 	ebfff9e3 	bl	ff941ba0 <_binary_dump_bin_start+0x131ba0>
ff943410: 	e59f3090 	ldr	r3, [pc, #144]	; ff9434a8: (00005bb4) 
ff943414: 	e5932000 	ldr	r2, [r3]
ff943418: 	e3520000 	cmp	r2, #0	; 0x0
ff94341c: 	0a000004 	beq	ff943434 <_binary_dump_bin_start+0x133434>
ff943420: 	e59f3084 	ldr	r3, [pc, #132]	; ff9434ac: (00005bb8) 
ff943424: 	e1a00004 	mov	r0, r4
ff943428: 	e5931000 	ldr	r1, [r3]
ff94342c: 	e1a0e00f 	mov	lr, pc
ff943430: 	e1a0f002 	mov	pc, r2
*/
	"BL      sub_FF941BA0\n"
	"LDR     R3, =0x5BB4\n"
	"LDR     R2, [R3]\n"
	"CMP     R2, #0\n"
	"BEQ     loc_FF943434\n"
	"LDR     R3, =0x5BB8\n"
	"MOV     R0, R4\n"
	"LDR     R1, [R3]\n"
	"MOV     LR, PC\n"
	"MOV     PC, R2\n"

"loc_FF943434:\n"
//ff943434: 	ebfffe8b 	bl	ff942e68 <_binary_dump_bin_start+0x132e68>
//ff943438: 	ebfffec5 	bl	ff942f54 <_binary_dump_bin_start+0x132f54>
//ff94343c: 	ebfffeee 	bl	ff942ffc <_binary_dump_bin_start+0x132ffc>

	//do pre flash ?
	"BL      sub_FF942E68\n"
	"BL      sub_FF942F54\n"
	//now do main flash
	"BL      sub_FF942FFC\n"
		
	// 	"STMFD   SP!, {R3, R5, ip, LR}\n"
	//"BL capt_seq_hook_raw_here\n"
// 	"LDMFD   SP!, {R3, R5, ip, LR}\n"

/*
ff943440: 	e5962000 	ldr	r2, [r6]
ff943444: 	e3520000 	cmp	r2, #0	; 0x0
ff943448: 	0a000003 	beq	ff94345c <_binary_dump_bin_start+0x13345c>
ff94344c: 	e59f304c 	ldr	r3, [pc, #76]	; ff9434a0: (00005bc8) 
ff943450: 	e5931000 	ldr	r1, [r3]
ff943454: 	e1a0e00f 	mov	lr, pc
ff943458: 	e1a0f002 	mov	pc, r2
*/		
	"LDR     R2, [R6]\n"
	"CMP     R2, #0\n"
	"BEQ     loc_FF94345C\n"
	"LDR     R3, =0x5BC8\n"
	"LDR     R1, [R3]\n"
	"MOV     LR, PC\n"
	"MOV     PC, R2\n"

"loc_FF94345C:\n"
	"BL capt_seq_hook_raw_here\n"
/*
ff94345c: 	e5950000 	ldr	r0, [r5]
ff943460: 	e3a01002 	mov	r1, #2	; 0x2
ff943464: 	e8bd4070 	ldmia	sp!, {r4, r5, r6, lr}
ff943468: 	eafb79ac 	b	ff821b20 <_binary_dump_bin_start+0x11b20>
*/	"LDR     R0, [R5]\n"
	"MOV     R1, #2\n"
	"LDMFD   SP!, {R4-R6,LR}\n"
	"B       sub_FF821B20\n" //SetEventFlag?
		
		
);
		
 

}

// dk: ok
void __attribute__((naked,noinline)) capt_seq_task()
{//THE CODE USES STRANGE JUMP TABLE!
//adresses are copied to ram locations from 0x5BCC on:
//this data is copied there and used as jumptable:
//
//ROM:ffadb9a0                  DCD loc_FF9427E8 //no idea
//ROM:FFADB9D4X                 DCD sub_FF9432B8 //takes the snapshot (OVERRIDE)
//ROM:FFADB9D8X                 DCD sub_FF942A40 //also called after releasing half_press
//ROM:FFADB9DCX                 DCD sub_FF9426DC //this is called after releasing shoot_half
//ROM:FFADB9E0X                 DCD sub_FF943848 
//ROM:FFADB9E4X                 DCD sub_FF943B90
//ROM:FFADB9E8X                 DCD sub_FF943E2C
//ROM:FFADB9ECX                 DCD sub_FF943FD0 //cancel movie capt seq
//ROM:FFADB9F0X                 DCD sub_FF944210 
//ROM:FFADB9F4X                 DCD sub_FF9443E0
//ROM:FFADB9F8X                 DCD sub_FF9444E0
//ROM:FFADB9FCX                 DCD sub_FF944564
//ROM:FFADBA00X                 DCD sub_FF9447CC
//ROM:FFADBA04X                 DCD sub_FF944880
//
	asm volatile (
//ff944b48: 	e92d4030 	stmdb	sp!, {r4, r5, lr}
//ff944b4c: 	e24dd004 	sub	sp, sp, #4	; 0x4
//ff944b50: 	e1a0500d 	mov	r5, sp
//ff944b54: 	ea000007 	b	ff944b78 <_binary_dump_bin_start+0x134b78>
		//save
		"STMFD   SP!, {R4, R5, LR}\n"
		//make room for local var on stack
		"SUB     SP, SP, #4\n"
			
		//manipulate jump table in ram:
    //change 0x5BD0 from FF9427E8 to sub_FF9427E8_my
    //no idea what this is. maybe some idle stuff ?
    ///"ldr r5, =0x5BD0\n"
 		///"ldr r4, =sub_ff9427e8_my\n"
 		///"str r4, [r5]\n"
		//change 0x5BD4 from 0xff9432b8 to sub_ff9432b8_my
		"ldr r5, =0x5BD4\n"
		"ldr r4, =sub_ff9432b8_my\n"
		"str r4, [r5]\n"
    //change 0x5BD8 from FF942A40 to sub_ff942A40_my
    ///"ldr r5, =0x5BD8\n"
 		///"ldr r4, =sub_ff942A40_my\n"
 		///"str r4, [r5]\n"
    //change 0x5BDC from ff9427e8 to sub_ff9426dc_my
    ///"ldr r5, =0x5BDC\n"
 		///"ldr r4, =sub_ff9426dc_my\n"
 		///"str r4, [r5]\n"
		
			
		//save SP on R5
		"MOV     R5, SP\n"
		//jump to ..78
		"B       loc_FF944B78\n"
		
//ff944b58: 	e59dc000 	ldr	ip, [sp]
//ff944b5c: 	e35c000d 	cmp	ip, #13	; 0xd
//ff944b60: 	9a000001 	bls	ff944b6c <_binary_dump_bin_start+0x134b6c>
//ff944b64: 	ebfb4029 	bl	ff814c10 <_binary_dump_bin_start+0x4c10>
//ff944b68: 	e59dc000 	ldr	ip, [sp]
	
	"loc_FF944B58:\n"
		//ip=memread(SP)
		"LDR     ip, [SP]\n"
		//compare against 13
		"CMP     ip, #13\n"
		//branch link if lower or same
		"BLS     loc_FF944B6C\n"
		//branch link anyway
		"BL      sub_FF814C10\n"
		"LDR     ip, [SP]\n"
//
	//original branch uses strange jump table in memory
	//i replaced it with a normal better to read one:
	//smaller than 13:

	"loc_FF944B6C:\n"
 		///"CMP     ip, #0\n"
    ///"BNE     loc_FF944B6C_orig\n"
    //hook my little test routine for getting the PROPCASE_SHOOTING workaround value:
    "STMFD   SP!, {R0}\n"
    ///"LDR R0, =1\n"
    "MOV R0, ip\n"
    "bl set_shooting_status\n" //set_shooting_status(1);
	  "LDMFD   SP!, {R0}\n"
          
  "loc_FF944B6C_orig:\n"
          
          
//ff944b6c: 	e59f304c 	ldr	r3, [pc, #76]	; ff944bc0: (00005bd0) 
//ff944b70: 	e1a0e00f 	mov	lr, pc
//ff944b74: 	e793f10c 	ldr	pc, [r3, ip, lsl #2]

// 		//save to stack
// 		"STMFD   SP!, {R5, ip}\n"
// 		"BLEQ capt_seq_hook_raw_here\n"
// 		"LDMFD   SP!, {R5, ip}\n"
		//R3=0x5BD0
		"LDR     R3, =0x5BD0\n"
		//save PC to link reg
		"MOV     LR, PC\n"
		//PC=mem(0x05BD0+4*ip) --> JUMP!
		"LDR     PC, [R3,ip,LSL #2]\n"
	//	"B loc_FF944B78\n"

//ff944b78: 	e59f3044 	ldr	r3, [pc, #68]	; ff944bc4: (00067644) 
//ff944b7c: 	e3a0c000 	mov	ip, #0	; 0x0
//ff944b80: 	e59f4040 	ldr	r4, [pc, #64]	; ff944bc8: (00005b7c) 
//ff944b84: 	e1a0200c 	mov	r2, ip
//ff944b88: 	e1a01005 	mov	r1, r5
//ff944b8c: 	e5930000 	ldr	r0, [r3]
//ff944b90: 	e584c000 	str	ip, [r4]
    				
	"loc_FF944B78:\n"
		//r3=0x67644
		"LDR     R3, =0x67644\n"
		//ip=0
		"MOV     ip, #0\n"
		//r4=0x5B7C
		"LDR     R4, =0x5B7C\n"
		//r2=0
		"MOV     R2, ip\n"
		//r1=r5=SP backup
		"MOV     R1, R5\n"
		//r0=mem(0x67644)
		"LDR     R0, [R3]\n"
		//write(0x5B7C, 0)
		"STR     ip, [R4]\n"
		
//ff944b94: 	ebfb75e1 	bl	ff822320 <_binary_dump_bin_start+0x12320>
//ff944b98: 	e3a02e7b 	mov	r2, #1968	; 0x7b0
//ff944b9c: 	e3100001 	tst	r0, #1	; 0x1
//ff944ba0: 	e59f1024 	ldr	r1, [pc, #36]	; ff944bcc: (ff941b94)  **"CaptSeq.c"
//ff944ba4: 	e2822005 	add	r2, r2, #5	; 0x5
//ff944ba8: 	e59f0020 	ldr	r0, [pc, #32]	; ff944bd0: (ff944b30)  **"ReqID < CAPTSEQ_REQ_MAX"

		//branch link ReceiveMessagequeue
		"BL      sub_FF822320\n" //ReceiveMessageQueue?
		//r2=0x7B0
		"MOV     R2, #1968\n"
		//test if r0 bit0 is set
		"TST     R0, #1\n"
		//load pointer to debug string
		"LDR     R1, =0xff941b94\n" //=>"CaptSeq.c"
		//r2=0x7B5
		"ADD     R2, R2, #5\n"
		//load pointer to debug string 2
		"LDR     R0, =0xff944b30\n" //=>"ReqID < CAPTSEQ_REQ_MAX"

//dk    "STMFD   SP!, {R0}\n"
//    "LDR R0, =0\n"
//    ///"bl set_shooting_status\n" //set_shooting_status(0);
//	   "LDMFD   SP!, {R0}\n"
          
//ff944bac: 	0affffe9 	beq	ff944b58 <_binary_dump_bin_start+0x134b58>
//ff944bb0: 	ebfb7be3 	bl	ff823b44 <_binary_dump_bin_start+0x13b44>
//ff944bb4: 	e28dd004 	add	sp, sp, #4	; 0x4
//ff944bb8: 	e8bd8030 	ldmia	sp!, {r4, r5, pc} // == LDMFD
		//if test successfule jump to loc_FF944B58 -> endless loop
		"BEQ     loc_FF944B58\n"
		//exit
		"BL      sub_FF823B44\n" //ExitTask?
		"ADD     SP, SP, #4\n"
		"LDMFD   SP!, {R4,R5,PC}"
);

}

