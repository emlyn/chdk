#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

void JogDial_task_my(void);

void taskCreateHook(int *p) { 
 p-=17;
 if (p[0]==0xFF868B90)  p[0]=(int)capt_seq_task; //done
 if (p[0]==0xFF821784)  p[0]=(int)mykbd_task; //done
 if (p[0]==0xFF884A4C)  p[0]=(int)init_file_modules_task; //done
 if (p[0]==0xFF84B8D8)  p[0]=(int)JogDial_task_my; //done
 if (p[0]==0xFF864354)  p[0]=(int)movie_record_task; //done
 if (p[0]==0xFF8AD7C4)  p[0]=(int)exp_drv_task; //done
}

void taskCreateHook2(int *p) { 
 p-=17;
 if (p[0]==0xFF884A4C)  p[0]=(int)init_file_modules_task; //done
 if (p[0]==0xFF8AD7C4)  p[0]=(int)exp_drv_task; //done
}

void CreateTask_spytask() {

         _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

};


void __attribute__((naked,noinline)) boot() {

    asm volatile (
                 "LDR     R1, =0xC0410000\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [R1]\n"
                 "MOV     R1, #0x78\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "MOV     R1, #0\n"
                 "MCR     p15, 0, R1,c7,c10, 4\n"
                 "MCR     p15, 0, R1,c7,c5\n"
                 "MCR     p15, 0, R1,c7,c6\n"
                 "MOV     R0, #0x3D\n"
                 "MCR     p15, 0, R0,c6,c0\n"
                 "MOV     R0, #0xC000002F\n"
                 "MCR     p15, 0, R0,c6,c1\n"
                 "MOV     R0, #0x33\n"
                 "MCR     p15, 0, R0,c6,c2\n"
                 "MOV     R0, #0x40000033\n"
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x80000017\n"
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFF80002D\n"
                 "MCR     p15, 0, R0,c6,c5\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c2,c0, 1\n"
                 "MOV     R0, #0x34\n"
                 "MCR     p15, 0, R0,c3,c0\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 2\n"
                 "LDR     R0, =0x3333330\n"
                 "MCR     p15, 0, R0,c5,c0, 3\n"
                 "MRC     p15, 0, R0,c1,c0\n"
                 "ORR     R0, R0, #0x1000\n"
                 "ORR     R0, R0, #4\n"
                 "ORR     R0, R0, #1\n"
                 "MCR     p15, 0, R0,c1,c0\n"
                 "MOV     R1, #0x80000006\n"
                 "MCR     p15, 0, R1,c9,c1\n"
                 "MOV     R1, #6\n"
                 "MCR     p15, 0, R1,c9,c1, 1\n"
                 "MRC     p15, 0, R1,c1,c0\n"
                 "ORR     R1, R1, #0x50000\n"
                 "MCR     p15, 0, R1,c1,c0\n"
                 "LDR     R2, =0xC0200000\n"
                 "MOV     R1, #1\n"
                 "STR     R1, [R2,#0x10C]\n"
                 "MOV     R1, #0xFF\n"
                 "STR     R1, [R2,#0xC]\n"
                 "STR     R1, [R2,#0x1C]\n"
                 "STR     R1, [R2,#0x2C]\n"
                 "STR     R1, [R2,#0x3C]\n"
                 "STR     R1, [R2,#0x4C]\n"
                 "STR     R1, [R2,#0x5C]\n"
                 "STR     R1, [R2,#0x6C]\n"
                 "STR     R1, [R2,#0x7C]\n"
                 "STR     R1, [R2,#0x8C]\n"
                 "STR     R1, [R2,#0x9C]\n"
                 "STR     R1, [R2,#0xAC]\n"
                 "STR     R1, [R2,#0xBC]\n"
                 "STR     R1, [R2,#0xCC]\n"
                 "STR     R1, [R2,#0xDC]\n"
                 "STR     R1, [R2,#0xEC]\n"
                 "STR     R1, [R2,#0xFC]\n"
                 "LDR     R1, =0xC0400008\n"
                 "LDR     R2, =0x430005\n"
                 "STR     R2, [R1]\n"
                 "MOV     R1, #1\n"
                 "LDR     R2, =0xC0243100\n"
                 "STR     R2, [R1]\n"
                 "LDR     R2, =0xC0242010\n"
                 "LDR     R1, [R2]\n"
                 "ORR     R1, R1, #1\n"
                 "STR     R1, [R2]\n"
                 "LDR     R0, =0xFFB9B26C\n" //done
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0x10A50\n"
 "loc_FF81013C:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF81013C\n" //checked
                 "LDR     R1, =0xACB74\n"
                 "MOV     R2, #0\n"
 "loc_FF810154:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FF810154\n" //checked
                 "B       sub_FF8101A0_my\n"   //checked //---------->
    );	
};


void __attribute__((naked,noinline)) sub_FF8101A0_my() {
   *(int*)0x1930=(int)taskCreateHook;
   *(int*)0x1934=(int)taskCreateHook2;
   *(int*)(0x25BC+4)= (*(int*)0xC0220134)&1 ? 0x2000000 : 0x1000000; // replacement of sub_FF8218C8 for correct power-on.
  asm volatile (
                 "LDR     R0, =0xFF810218\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFF810250\n"
 "loc_FF8101AC:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF8101AC\n"
                 "LDR     R0, =0xFF810250\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFF810464\n"
 "loc_FF8101C8:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FF8101C8\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
 "loc_FF8101FC:\n"
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FF8101FC\n"
                 "BL      sub_FF810F94_my\n"  //------------>
     );
}

void __attribute__((naked,noinline)) sub_FF810F94_my() {
     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFB00250\n" //done
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
            //   "LDR     R0, =0xACB74\n"
                 "LDR     R0, =new_sa\n"        // +
                 "LDR     R0, [R0]\n"           // +
                 "LDR     R2, =0x2B9C00\n"
                 "LDR     R1, =0x2B24A8\n"
                 "STR     R0, [SP,#8]\n"
                 "SUB     R0, R1, R0\n"
                 "ADD     R3, SP, #0xC\n"
                 "STR     R2, [SP]\n"
                 "STMIA   R3, {R0-R2}\n"
                 "MOV     R0, #0x22\n"
                 "STR     R0, [SP,#0x18]\n"
                 "MOV     R0, #0x68\n"
                 "STR     R0, [SP,#0x1C]\n"
                 "LDR     R0, =0x19B\n"
                 "LDR     R1, =sub_FF814D8C_my\n"  //------------>
                 "STR     R0, [SP,#0x20]\n"
                 "MOV     R0, #0x96\n"
                 "STR     R0, [SP,#0x24]\n"
                 "MOV     R0, #0x78\n"
                 "STR     R0, [SP,#0x28]\n"
                 "MOV     R0, #0x64\n"
                 "STR     R0, [SP,#0x2C]\n"
                 "MOV     R0, #0\n"
                 "STR     R0, [SP,#0x30]\n"
                 "STR     R0, [SP,#0x34]\n"
                 "MOV     R0, #0x10\n"
                 "STR     R0, [SP,#0x5C]\n"
                 "MOV     R0, #0x800\n"
                 "STR     R0, [SP,#0x60]\n"
                 "MOV     R0, #0xA0\n"
                 "STR     R0, [SP,#0x64]\n"
                 "MOV     R0, #0x280\n"
                 "STR     R0, [SP,#0x68]\n"
                 "MOV     R0, SP\n"
                 "MOV     R2, #0\n"
                 "BL      sub_FF812D38\n"
                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"
     );
}

void __attribute__((naked,noinline)) sub_FF814D8C_my() {
        asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF810940\n"
                 "BL      sub_FF81901C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814EA0\n"
                 "BLLT    sub_FF814E80\n"
                 "BL      sub_FF8149B4\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814EA8\n"
                 "BLLT    sub_FF814E80\n"
                 "LDR     R0, =0xFF814EB8\n"
                 "BL      sub_FF814A9C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814EC0\n"
                 "BLLT    sub_FF814E80\n"
                 "LDR     R0, =0xFF814EB8\n"
                 "BL      sub_FF813548\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814ED4\n"
                 "BLLT    sub_FF814E80\n"
                 "BL      sub_FF818BA4\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814EE0\n"
                 "BLLT    sub_FF814E80\n"
                 "BL      sub_FF811478\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFF814EEC\n"
                 "BLLT    sub_FF814E80\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       taskcreate_Startup_my\n" //---------->
        );
};

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R3,LR}\n"
        //       "BL      j_nullsub_174\n"
                 "BL      sub_FF829940\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF81C1E0\n"
                 "BL      sub_FF8218BC\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF81C1E0\n"
                 "BL      sub_FF821050\n"
                 "LDR     R1, =0xC0220000\n"
                 "MOV     R0, #0x44\n"
                 "STR     R0, [R1,#0x1C]\n"
                 "BL      sub_FF82123C\n"
 "loc_FF81C1DC:\n"
                 "B       loc_FF81C1DC\n"
 "loc_FF81C1E0:\n"
        //       "BL      sub_FF8218C8\n"   // removed for correct power-on on 'on/off' button.
        //       "BL      j_nullsub_175\n"
                 "BL      sub_FF827AC8\n"
                 "LDR     R1, =0x30E000\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FF827F10\n"
                 "BL      sub_FF827CBC\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =task_Startup_my\n"   //------------>
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x19\n"
                 "LDR     R0, =0xFF81C228\n"
                 "BL      sub_FF81AEF4\n"
	 
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R12,PC}\n"
				 
     );
}

void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF8153CC\n"
                 "BL      sub_FF822A24\n"
                 "BL      sub_FF820CE8\n"
      //         "BL      j_nullsub_178\n"
                 "BL      sub_FF829B48\n"
      //         "BL      sub_FF829A08\n"    // start diskboot.bin
                 "BL      sub_FF829D00\n"
                 "BL      sub_FF81FAA0\n"
                 "BL      sub_FF829B98\n"
                 "BL      sub_FF8270C8\n"
                 "BL      sub_FF829D04\n"
                 "BL      CreateTask_spytask\n"    // +
                 "BL      sub_FF8217B8\n"
                 "BL      sub_FF8249EC\n"
                 "BL      sub_FF829D1C\n"
      //         "BL      nullsub_2\n"
                 "BL      sub_FF82062C\n"
                 "BL      sub_FF829718\n"
                 "BL      sub_FF820C98\n"
                 "BL      sub_FF820548\n"
                 "BL      sub_FF81FAD4\n"
                 "BL      sub_FF82A854\n"
                 "BL      sub_FF820520\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FF815490\n"
     );
}


void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FF879F70\n" //done
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    sub_FF87ECE0\n" //done
                 "BL      sub_FF879F9C_my\n"   //done        //---------->
                 "BL      core_spytask_can_start\n"      // CHDK: Set "it's-save-to-start"-Flag for spytask
                 "CMP     R4, #0\n"
                 "MOVEQ   R0, R5\n"
                 "LDMEQFD SP!, {R4-R6,LR}\n"
                 "MOVEQ   R1, #0\n"
                 "BEQ     sub_FF87ECE0\n" //done
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF879F9C_my() {
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FF85AB00_my\n"    //----------->
           //    "BL      nullsub_66\n"
                 "LDR     R4, =0x58CC\n"
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FF879FD0\n" //done - these all seen to be about 8 bytes less that the 101 build
                 "BL      sub_FF859FC8\n" //done
                 "BL      sub_FF913790\n" //done
                 "BL      sub_FF859FC8\n" //done
                 "BL      sub_FF855E9C\n" //done was FF855EA4
                 "BL      sub_FF859EC8\n" //done was FF859ED0
                 "BL      sub_FF91385C\n" //done was FF913864
 "loc_FF879FD0:\n" //done was FF879FD8
                 "MOV     R0, #1\n"
                 "STR     R0, [R4]\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF85AB00_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "MOV     R6, #0\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FF85A5C0\n" //done
                 "LDR     R4, =0x1A784\n"
                 "MOV     R5, #0\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "BL      sub_FF85B020\n" //done
                 "CMP     R0, #0\n"
                 "LDREQ   R0, =0x2A70\n"
                 "STREQ   R5, [R0,#0x10]\n"
                 "STREQ   R5, [R0,#0x14]\n"
                 "STREQ   R5, [R0,#0x18]\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FF85A600\n" //done
                 "MOV     R0, R6\n"
                 "BL      sub_FF85A93C_my\n"     //--------->  done
                 "MOV     R5, R0\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FF85A9A8\n" //done
                 "LDR     R1, [R4,#0x3C]\n"
                 "AND     R2, R5, R0\n"
                 "CMP     R1, #0\n"
                 "MOV     R0, #0\n"
                 "MOVEQ   R0, #0x80000001\n"
                 "BEQ     loc_FF85AB94\n" //done
                 "LDR     R3, [R4,#0x2C]\n"
                 "CMP     R3, #2\n"
                 "MOVEQ   R0, #4\n"
                 "CMP     R1, #5\n"
                 "ORRNE   R0, R0, #1\n"
                 "BICEQ   R0, R0, #1\n"
                 "CMP     R2, #0\n"
                 "BICEQ   R0, R0, #2\n"
                 "ORREQ   R0, R0, #0x80000000\n"
                 "BICNE   R0, R0, #0x80000000\n"
                 "ORRNE   R0, R0, #2\n"
 "loc_FF85AB94:\n" //done
                 "STR     R0, [R4,#0x40]\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF85A93C_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "LDR     R5, =0x2A70\n"
                 "MOV     R6, R0\n"
                 "LDR     R0, [R5,#0x14]\n"
                 "CMP     R0, #0\n"
                 "MOVNE   R0, #1\n"
                 "LDMNEFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, #0x17\n"
                 "MUL     R1, R0, R6\n"
                 "LDR     R0, =0x1A784\n"
                 "ADD     R4, R0, R1,LSL#2\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R6\n"
                 "BL      sub_FF85A6CC_my\n"  //--------------> done
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R6\n"
                 "BL      sub_FF85A834\n" //done
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FF85A1C8\n" //done
                 "CMP     R0, #0\n"
                 "MOVNE   R1, #1\n"
                 "STRNE   R1, [R5,#0x14]\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF85A6CC_my() {

 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R0\n"
                 "MOV     R0, #0x17\n"
                 "MUL     R1, R0, R1\n"
                 "LDR     R0, =0x1A784\n"
                 "MOV     R6, #0\n"
                 "ADD     R7, R0, R1,LSL#2\n"
                 "LDR     R0, [R7,#0x3C]\n"
                 "MOV     R5, #0\n"
                 "CMP     R0, #6\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FF85A818\n" //done
 "loc_FF85A6FC:\n" //done
                 "B       loc_FF85A730\n" //done
 "loc_FF85A700:\n" //done
                 "B       loc_FF85A718\n" //done
 "loc_FF85A704:\n" //done
                 "B       loc_FF85A718\n" //done
 "loc_FF85A708:\n" //done
                 "B       loc_FF85A718\n" //done
 "loc_FF85A70C:\n" //done
                 "B       loc_FF85A718\n" //done
 "loc_FF85A710:\n" //done
                 "B       loc_FF85A810\n" //done
 "loc_FF85A714:\n" //done
                 "B       loc_FF85A718\n" //done
 "loc_FF85A718:\n" //done
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x200\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FF873F18\n" //done was FF873F20
                 "MOVS    R4, R0\n"
                 "BNE     loc_FF85A738\n" //done
 "loc_FF85A730:\n" //done
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FF85A738:\n" //done
                 "LDR     R12, [R7,#0x4C]\n"
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF85A764\n" //done
                 "MOV     R0, #2\n"
                 "BL      sub_FF874064\n" //done was FF87406C
                 "B       loc_FF85A730\n" //done
 "loc_FF85A764:\n" //done
                 "MOV     R0, R8\n"
                 "BL      sub_FF92ADE0\n"  //done

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
          "MOV     R4, R12\n"                    // Move the new MBR offset for the partition detection.
          
     "dg_sd_fat32_end:\n"
          // End of DataGhost's FAT32 autodetection code

                 "LDRB    R1, [R4,#0x1C9]\n"
                 "LDRB    R3, [R4,#0x1C8]\n"
                 "LDRB    R12, [R4,#0x1CC]\n"
                 "MOV     R1, R1,LSL#24\n"
                 "ORR     R1, R1, R3,LSL#16\n"
                 "LDRB    R3, [R4,#0x1C7]\n"
                 "LDRB    R2, [R4,#0x1BE]\n"
             //  "LDRB    LR, [R4,#0x1FF]\n"           // -
                 "ORR     R1, R1, R3,LSL#8\n"
                 "LDRB    R3, [R4,#0x1C6]\n"
                 "CMP     R2, #0\n"
                 "CMPNE   R2, #0x80\n"
                 "ORR     R1, R1, R3\n"
                 "LDRB    R3, [R4,#0x1CD]\n"
                 "MOV     R3, R3,LSL#24\n"
                 "ORR     R3, R3, R12,LSL#16\n"
                 "LDRB    R12, [R4,#0x1CB]\n"
                 "ORR     R3, R3, R12,LSL#8\n"
                 "LDRB    R12, [R4,#0x1CA]\n"
                 "ORR     R3, R3, R12\n"
             //  "LDRB    R12, [R4,#0x1FE]\n"           // -
                 "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
                 "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.
                 "MOV     R4, #0\n"
                 "BNE     loc_FF85A7EC\n" //done
                 "CMP     R0, R1\n"
                 "BCC     loc_FF85A7EC\n" //done
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R6, R1\n"
                 "MOVEQ   R5, R3\n"
                 "MOVEQ   R4, #1\n"
 "loc_FF85A7EC:\n" //done
                 "MOV     R0, #2\n"
                 "BL      sub_FF874064\n" //done was FF87406C
                 "CMP     R4, #0\n"
                 "BNE     loc_FF85A824\n" //done
                 "MOV     R6, #0\n"
                 "MOV     R0, R8\n"
                 "BL      sub_FF92ADE0\n" //done was FF92ADE8
                 "MOV     R5, R0\n"
                 "B       loc_FF85A824\n" //done
 "loc_FF85A810:\n" //done
                 "MOV     R5, #0x40\n"
                 "B       loc_FF85A824\n" //done
 "loc_FF85A818:\n" //done
                 "LDR     R1, =0x37A\n"
                 "LDR     R0, =0xFF85A6C0\n" //done
                 "BL      sub_FF81B1CC\n" //done
 "loc_FF85A824:\n" //done
                 "STR     R6, [R7,#0x44]!\n"
                 "MOV     R0, #1\n"
                 "STR     R5, [R7,#4]\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}


void __attribute__((naked,noinline)) JogDial_task_my() { 
 asm volatile(
                 "STMFD   SP!, {R3-R11,LR}\n"
                 "BL      sub_FF84BA88\n"
                 "LDR     R11, =0x80000B01\n"
                 "LDR     R8, =0xFFB0AE28\n" //done was FFB0AE38
                 "LDR     R7, =0xC0240000\n"
                 "LDR     R6, =0x25D8\n"
                 "MOV     R9, #1\n"
                 "MOV     R10, #0\n"
 "loc_FF84B8F8:\n"
                 "LDR     R3, =0x1AE\n"
                 "LDR     R0, [R6,#0xC]\n"
                 "LDR     R2, =0xFF84BB30\n"
                 "MOV     R1, #0\n"
                 "BL      sub_FF827DF8\n"
                 "MOV     R0, #40\n"
                 "BL      _SleepTask\n"

//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n"
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------



                 "LDR     R0, [R7,#0x104]\n"
                 "MOV     R0, R0,ASR#16\n"
                 "STRH    R0, [R6]\n"
                 "LDRSH   R2, [R6,#2]\n"
                 "SUB     R1, R0, R2\n"
                 "CMP     R1, #0\n"
                 "BEQ     loc_FF84B9BC\n"
                 "MOV     R5, R1\n"
                 "RSBLT   R5, R5, #0\n"
                 "MOVLE   R4, #0\n"
                 "MOVGT   R4, #1\n"
                 "CMP     R5, #0xFF\n"
                 "BLS     loc_FF84B970\n"
                 "CMP     R1, #0\n"
                 "RSBLE   R1, R2, #0xFF\n"
                 "ADDLE   R1, R1, #0x7F00\n"
                 "ADDLE   R0, R1, R0\n"
                 "RSBGT   R0, R0, #0xFF\n"
                 "ADDGT   R0, R0, #0x7F00\n"
                 "ADDGT   R0, R0, R2\n"
                 "ADD     R5, R0, #0x8000\n"
                 "ADD     R5, R5, #1\n"
                 "EOR     R4, R4, #1\n"
 "loc_FF84B970:\n"
                 "LDR     R0, [R6,#0x14]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF84B9B4\n"
                 "LDR     R0, [R6,#0x1C]\n"
                 "CMP     R0, #0\n"
                 "BEQ     loc_FF84B99C\n"
                 "LDR     R1, [R8,R4,LSL#2]\n"
                 "CMP     R1, R0\n"
                 "BEQ     loc_FF84B9A4\n"
                 "LDR     R0, =0xB01\n"
                 "BL      sub_FF880BB0\n" //done was FF880BB8
 "loc_FF84B99C:\n"
                 "MOV     R0, R11\n"
                 "BL      sub_FF880BB0\n" //done was FF880BB8
 "loc_FF84B9A4:\n"
                 "LDR     R0, [R8,R4,LSL#2]\n"
                 "MOV     R1, R5\n"
                 "STR     R0, [R6,#0x1C]\n"
                 "BL      sub_FF880AD8\n" //done was FF880AE0
 "loc_FF84B9B4:\n"
                 "LDRH    R0, [R6]\n"
                 "STRH    R0, [R6,#2]\n"
 "loc_FF84B9BC:\n"
                 "STR     R10, [R7,#0x100]\n"
                 "STR     R9, [R7,#0x108]\n"
                 "LDR     R0, [R6,#0x10]\n"
                 "CMP     R0, #0\n"
                 "BLNE    _SleepTask\n"
                 "B       loc_FF84B8F8\n"
 );
}
