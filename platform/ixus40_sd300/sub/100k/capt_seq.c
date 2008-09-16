#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (1)
#define NR_OFF (0)

static long raw_save_stage;

void capt_seq_hook_raw_here()
{
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
	 
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}


void capt_seq_hook_set_nr()
{
	return;
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
}

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



void __attribute__((naked,noinline)) sub_ff9432b8_my()
{

asm volatile (
	
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
	"MOV     R2, #0x520\n"
	"LDR     R0, =0xff94347c\n" //debug string loc
	"LDR     R1, =0xff943480\n" //debug string loc
	"ADD     R2, R2, #2\n"
	"BL      sub_FF814C10\n" //debugAssert
	"ldr pc, =0xff943310\n"
		
		
"loc_FF943310:\n"
	"BL      sub_FF941A14\n"
	"CMP     R0, #0\n"
	"BNE     loc_FF94334C\n" //ok
	"LDR     R3, =0x5B90\n"
	"LDR     R2, [R3]\n"
	"LDR     R1, [R2,#4]\n"
	"CMP     R1, #0\n"
	"BEQ     loc_FF94334C\n" //ok
	"LDR     R0, =0xff943484\n" //debug string loc
	"BL      sub_FFAC03C4\n" //printf
	"LDR     R0, =0xff943488\n" //debug string loc
	"BL      sub_FFAC03C4\n" //printf
	
	//ok ?!	
	"BL      sub_FF941A48\n"
		
		
	"LDR     R0, =0xff94348c\n" //debug string lco
	"BL      sub_FFAC03C4\n" //printf
"loc_FF94334C:\n"
	"LDR     R3, =0x6763C\n"
	"MVN     R4, #0\n" //0xFFFFFFFF
	"LDR     R0, [R3]\n"
	"MOV     R1, R4\n"
	"BL      sub_FFAC03C4\n" //ClearEventFlag ?!
	"LDR     R3, =0x67640\n"
	"MOV     R1, R4\n"
	"LDR     R0, [R3]\n"
	"BL      sub_FFAC03C4\n" //ClearEventFlag ?!
	
	"LDR     R3, =0x5B80\n"
	"LDR     R3, [R3]\n"
	"CMP     R3, #1\n"
	"CMPNE   R3, #3\n"
		
	//before take
  "BL      capt_seq_hook_set_nr\n" // + do noise reduction set
  "BL      shooting_expo_param_override\n"  // + seems to be working :)
        
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
	
	///???
	"BL      sub_FF942354\n"
		
	"B       loc_FF9433C0\n"
		
"loc_FF9433BC:\n"
	"BL      sub_FF942984\n"
		
"loc_FF9433C0:\n"
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
	"LDR     R5, =0x67638\n"
	"MOV     R1, #2\n"
	"LDR     R0, [R5]\n"
	"BL      sub_FF821B20\n" //SetEventFlag?
	"B       loc_FF94340C\n"

"loc_FF943404:\n"
	"LDR     R6, =0x5BC4\n"
	"LDR     R5, =0x67638\n"
	
"loc_FF94340C:\n"
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
	//do pre flash ?
	"BL      sub_FF942E68\n"
	"BL      sub_FF942F54\n"
	//now do main flash
	"BL      sub_FF942FFC\n"
		
	// 	"STMFD   SP!, {R3, R5, ip, LR}\n"
	//"BL capt_seq_hook_raw_here\n"
// 	"LDMFD   SP!, {R3, R5, ip, LR}\n"
		
	"LDR     R2, [R6]\n"
	"CMP     R2, #0\n"
	"BEQ     loc_FF94345C\n"
	"LDR     R3, =0x5BC8\n"
	"LDR     R1, [R3]\n"
	"MOV     LR, PC\n"
	"MOV     PC, R2\n"

"loc_FF94345C:\n"
	"BL capt_seq_hook_raw_here\n"
	"LDR     R0, [R5]\n"
	"MOV     R1, #2\n"
	"LDMFD   SP!, {R4-R6,LR}\n"
	"B       sub_FF821B20\n" //SetEventFlag?
		
		
);
		
 

}


void __attribute__((naked,noinline)) capt_seq_task()
{//THE CODE USES STRANGE JUMP TABLE!
//adresses are copied to ram locations from 0x5BCC on:
//this data is copied there and used as jumptable:
//
//ROM:FFADB9D0                 DCD loc_FF9427E8 //no idea
//ROM:FFADB9D4                 DCD sub_FF9432B8 //takes the snapshot
//ROM:FFADB9D8                 DCD sub_FF942A40 //also called after releasing half_press
//ROM:FFADB9DC                 DCD sub_FF9426DC //this is called after releasing shoot_half
//ROM:FFADB9E0                 DCD sub_FF943848 
//ROM:FFADB9E4                 DCD sub_FF943B90
//ROM:FFADB9E8                 DCD sub_FF943E2C
//ROM:FFADB9EC                 DCD sub_FF943FD0 //cancel movie capt seq
//ROM:FFADB9F0                 DCD sub_FF944210 
//ROM:FFADB9F4                 DCD sub_FF9443E0
//ROM:FFADB9F8                 DCD sub_FF9444E0
//ROM:FFADB9FC                 DCD sub_FF944564
//ROM:FFADBA00                 DCD sub_FF9447CC
//ROM:FFADBA04                 DCD sub_FF944880
//
	asm volatile (
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
          
    "STMFD   SP!, {R0}\n"
    "LDR R0, =0\n"
    ///"bl set_shooting_status\n" //set_shooting_status(0);
	   "LDMFD   SP!, {R0}\n"
          
		//if test successfule jump to loc_FF944B58 -> endless loop
		"BEQ     loc_FF944B58\n"
		//exit
		"BL      sub_FF823B44\n" //ExitTask?
		"ADD     SP, SP, #4\n"
		"LDMFD   SP!, {R4,R5,PC}"
);

}

