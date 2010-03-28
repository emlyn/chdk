#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

void taskHook(context_t **context) { 

 task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

 if(!_strcmp(tcb->name, "PhySw"))           tcb->entry = (void*)mykbd_task; 
 if(!_strcmp(tcb->name, "CaptSeqTask"))     tcb->entry = (void*)capt_seq_task; 
 if(!_strcmp(tcb->name, "InitFileModules")) tcb->entry = (void*)init_file_modules_task;
 if(!_strcmp(tcb->name, "MovieRecord"))     tcb->entry = (void*)movie_record_task;
 if(!_strcmp(tcb->name, "ExpDrvTask"))      tcb->entry = (void*)exp_drv_task;
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
 "loc_FFC00028:\n"
                 "MCR     p15, 0, R1,c7,c5\n"
                 "MCR     p15, 0, R1,c7,c6\n"
                 "MOV     R0, #0x3D\n"
                 "MCR     p15, 0, R0,c6,c0\n"
                 "MOV     R0, #0xC000002F\n"
                 "MCR     p15, 0, R0,c6,c1\n"
                 "MOV     R0, #0x31\n"
                 "MCR     p15, 0, R0,c6,c2\n"
                 "LDR     R0, =0x10000031\n"
                 "MCR     p15, 0, R0,c6,c3\n"
                 "MOV     R0, #0x40000017\n"
                 "MCR     p15, 0, R0,c6,c4\n"
                 "LDR     R0, =0xFFC0002B\n"
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
                 "MOV     R1, #0x40000006\n"
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
                 "LDR     R0, =0xFFE88E20\n"
                 "LDR     R1, =0x1900\n"
                 "LDR     R3, =0xBA68\n"
 "loc_FFC0013C:\n"
                 "CMP     R1, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC0013C\n"
                 "LDR     R1, =0x102438\n"
                 "MOV     R2, #0\n"
 "loc_FFC00154:\n"
                 "CMP     R3, R1\n"
                 "STRCC   R2, [R3],#4\n"
                 "BCC     loc_FFC00154\n"
                 "B       sub_FFC001A4_my\n"  //--------->
    );
};


void __attribute__((naked,noinline)) sub_FFC001A4_my() {
   *(int*)0x1934=(int)taskHook;
   *(int*)0x1938=(int)taskHook;
   *(int*)(0x2164)= (*(int*)0xC022005C)&1 ? 0x400000 : 0x200000; // replacement of sub_FFC2C2FC for correct power-on.
   asm volatile (
                 "LDR     R0, =0xFFC0021C\n"
                 "MOV     R1, #0\n"
                 "LDR     R3, =0xFFC00254\n"
 "loc_FFC001B0:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC001B0\n"
                 "LDR     R0, =0xFFC00254\n"
                 "MOV     R1, #0x4B0\n"
                 "LDR     R3, =0xFFC00468\n"
 "loc_FFC001CC:\n"
                 "CMP     R0, R3\n"
                 "LDRCC   R2, [R0],#4\n"
                 "STRCC   R2, [R1],#4\n"
                 "BCC     loc_FFC001CC\n"
                 "MOV     R0, #0xD2\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "MOV     R0, #0xD3\n"
                 "MSR     CPSR_cxsf, R0\n"
                 "MOV     SP, #0x1000\n"
                 "LDR     R0, =0x6C4\n"
                 "LDR     R2, =0xEEEEEEEE\n"
                 "MOV     R3, #0x1000\n"
 "loc_FFC00200:\n"
                 "CMP     R0, R3\n"
                 "STRCC   R2, [R0],#4\n"
                 "BCC     loc_FFC00200\n"
                 "BL      sub_FFC00FC8_my\n" //-------->
     );
}

void __attribute__((naked,noinline)) sub_FFC00FC8_my() {
     asm volatile (
                 "STR     LR, [SP,#-4]!\n"
                 "SUB     SP, SP, #0x74\n"
                 "MOV     R0, SP\n"
                 "MOV     R1, #0x74\n"
                 "BL      sub_FFE315E8\n"
                 "MOV     R0, #0x53000\n"
                 "STR     R0, [SP,#4]\n"
           //    "LDR     R0, =0x102438\n"      // -
                 "LDR     R0, =new_sa\n"        // +
                 "LDR     R0, [R0]\n"           // +
                 "LDR     R2, =0x279C00\n"
                 "LDR     R1, =0x2724A8\n"
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
                 "LDR     R1, =sub_FFC04D3C_my\n"  //--------->
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
                 "BL      sub_FFC02D6C\n"
                 "ADD     SP, SP, #0x74\n"
                 "LDR     PC, [SP],#4\n"
     );
}


void __attribute__((naked,noinline)) sub_FFC04D3C_my() {
        asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FFC00958\n"
                 "BL      sub_FFC097EC\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04E50\n"
                 "BLLT    sub_FFC04E30\n"
                 "BL      sub_FFC04978\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04E58\n"
                 "BLLT    sub_FFC04E30\n"
                 "LDR     R0, =0xFFC04E68\n"
                 "BL      sub_FFC04A60\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04E70\n"
                 "BLLT    sub_FFC04E30\n"
                 "LDR     R0, =0xFFC04E68\n"
                 "BL      sub_FFC0357C\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04E84\n"
                 "BLLT    sub_FFC04E30\n"
                 "BL      sub_FFC09304\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04E90\n"
                 "BLLT    sub_FFC04E30\n"
                 "BL      sub_FFC014AC\n"
                 "CMP     R0, #0\n"
                 "LDRLT   R0, =0xFFC04E9C\n"
                 "BLLT    sub_FFC04E30\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       taskcreate_Startup_my\n" //-------->
        );
};


void __attribute__((naked,noinline)) taskcreate_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R3,LR}\n"
             //  "BL      j_nullsub_55\n"
                 "BL      sub_FFC17F38\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC0CEA0\n"
                 "BL      sub_FFC11104\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC0CEA0\n"
                 "LDR     R1, =0xC0220000\n"
                 "MOV     R0, #0x44\n"
                 "STR     R0, [R1,#0x20]\n"
 "loc_FFC0CE9C:\n"
                 "B       loc_FFC0CE9C\n"
 "loc_FFC0CEA0:\n"
             //  "BL      sub_FFC11110\n"      // removed for correct power-on on 'on/off' button.
             //  "BL      j_nullsub_56\n"
                 "BL      sub_FFC163F0\n"
                 "LDR     R1, =0x2CE000\n"
                 "MOV     R0, #0\n"
                 "BL      sub_FFC16638\n"
                 "BL      sub_FFC165E4\n"
                 "MOV     R3, #0\n"
                 "STR     R3, [SP]\n"
                 "LDR     R3, =task_Startup_my\n"  //-------->
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x19\n"
                 "LDR     R0, =0xFFC0CEE8\n"
                 "BL      sub_FFC0B9C4\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R12,PC}\n"

     );
}

void __attribute__((naked,noinline)) task_Startup_my() {
     asm volatile (
                 "STMFD   SP!, {R4,LR}\n"
                 "BL      sub_FFC05158\n"
                 "BL      sub_FFC121EC\n"
                 "BL      sub_FFC10AA4\n"
             //  "BL      j_nullsub_58\n"
                 "BL      sub_FFC1815C\n"
             //  "BL      sub_FFC1800C\n"    // - start diskboot.bin
                 "BL      sub_FFC182F8\n"
                 "BL      sub_FFC1818C\n"
                 "BL      sub_FFC156E4\n"
                 "BL      sub_FFC182FC\n"
                 "BL      CreateTask_spytask\n"    // +
                 "BL      sub_FFC11004\n"
                 "BL      sub_FFC13FEC\n"
                 "BL      sub_FFC18314\n"
             //  "BL      nullsub_2\n"
                 "BL      sub_FFC1042C\n"
                 "BL      sub_FFC17D14\n"
                 "BL      sub_FFC10A54\n"
                 "BL      sub_FFC10350\n"
                 "BL      sub_FFC18D38\n"
                 "BL      sub_FFC10328\n"
                 "LDMFD   SP!, {R4,LR}\n"
                 "B       sub_FFC05008\n"
     );
}

/*******************************************************************/

void __attribute__((naked,noinline)) init_file_modules_task() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "BL      sub_FFC521E4\n"
                 "LDR     R5, =0x5006\n"
                 "MOVS    R4, R0\n"
                 "MOVNE   R1, #0\n"
                 "MOVNE   R0, R5\n"
                 "BLNE    sub_FFC54884\n"
                 "BL      sub_FFC52210_my\n"             //------------->
                 "BL      core_spytask_can_start\n"      // + set "it's safe to start" flag for spytask
                 "CMP     R4, #0\n"
                 "MOVEQ   R0, R5\n"
                 "LDMEQFD SP!, {R4-R6,LR}\n"
                 "MOVEQ   R1, #0\n"
                 "BEQ     sub_FFC54884\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"

 );
}

void __attribute__((naked,noinline)) sub_FFC52210_my() {
 asm volatile(
                 "STMFD   SP!, {R4,LR}\n"
                 "MOV     R0, #3\n"
                 "BL      sub_FFC3A55C_my\n"    //---------->
           //    "BL      nullsub_97\n"
                 "LDR     R4, =0x29F4\n"
                 "LDR     R0, [R4,#4]\n"
                 "CMP     R0, #0\n"
                 "BNE     loc_FFC52248\n"
                 "BL      sub_FFC39920\n"
                 "BL      sub_FFCC07DC\n"
                 "BL      sub_FFC39920\n"
                 "BL      sub_FFC35D84\n"
                 "BL      sub_FFC39820\n"
                 "BL      sub_FFCC08A0\n"
 "loc_FFC52248:\n"
                 "MOV     R0, #1\n"
                 "STR     R0, [R4]\n"
                 "LDMFD   SP!, {R4,PC}\n"
 );
}


void __attribute__((naked,noinline)) sub_FFC3A55C_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R6, R0\n"
                 "BL      sub_FFC3A4C4\n"
                 "LDR     R1, =0xEEA4\n"
                 "MOV     R5, R0\n"
                 "ADD     R4, R1, R0,LSL#7\n"
                 "LDR     R0, [R4,#0x70]\n"
                 "CMP     R0, #4\n"
                 "LDREQ   R1, =0x6D8\n"
                 "LDREQ   R0, =0xFFC39FE8\n"
                 "BLEQ    sub_FFC0BE9C\n"
                 "MOV     R1, R6\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC39F30\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "BL      sub_FFC3AA88\n"
                 "CMP     R0, #0\n"
                 "STREQ   R0, [R4,#0x70]\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC3A008\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC3A2FC_my\n"  //--------->
                 "MOV     R7, R0\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC3A360\n"
                 "LDR     R1, [R4,#0x3C]\n"
                 "AND     R2, R7, R0\n"
                 "CMP     R1, #0\n"
                 "MOV     R0, #0\n"
                 "MOVEQ   R0, #0x80000001\n"
                 "BEQ     loc_FFC3A604\n"
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
 "loc_FFC3A604:\n"
                 "CMP     R6, #7\n"
                 "STR     R0, [R4,#0x40]\n"
                 "LDMNEFD SP!, {R4-R8,PC}\n"
                 "MOV     R0, R6\n"
                 "BL      sub_FFC3A514\n"
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R8,LR}\n"
                 "LDREQ   R0, =0xFFC3A800\n"
                 "BEQ     sub_FFC015AC\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC3A2FC_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "MOV     R5, R0\n"
                 "LDR     R0, =0xEEA4\n"
                 "ADD     R4, R0, R5,LSL#7\n"
                 "LDR     R0, [R4,#0x70]\n"
                 "TST     R0, #2\n"
                 "MOVNE   R0, #1\n"
                 "LDMNEFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R5\n"
                 "BL      sub_FFC3A08C_my\n"  //--------->
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "LDR     R0, [R4,#0x38]\n"
                 "MOV     R1, R5\n"
                 "BL      sub_FFC3A1F8\n"
                 "CMP     R0, #0\n"
                 "LDMEQFD SP!, {R4-R6,PC}\n"
                 "MOV     R0, R5\n"
                 "BL      sub_FFC39B18\n"
                 "CMP     R0, #0\n"
                 "LDRNE   R1, [R4,#0x70]\n"
                 "ORRNE   R1, R1, #2\n"
                 "STRNE   R1, [R4,#0x70]\n"
                 "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC3A08C_my() {
 asm volatile(
                 "STMFD   SP!, {R4-R8,LR}\n"
                 "MOV     R8, R0\n"
                 "LDR     R0, =0xEEA4\n"
                 "MOV     R7, #0\n"
                 "ADD     R5, R0, R1,LSL#7\n"
                 "LDR     R0, [R5,#0x3C]\n"
                 "MOV     R6, #0\n"
                 "CMP     R0, #7\n"
                 "ADDLS   PC, PC, R0,LSL#2\n"
                 "B       loc_FFC3A1DC\n"
 "loc_FFC3A0B4:\n"
                 "B       loc_FFC3A0EC\n"
 "loc_FFC3A0B8:\n"
                 "B       loc_FFC3A0D4\n"
 "loc_FFC3A0BC:\n"
                 "B       loc_FFC3A0D4\n"
 "loc_FFC3A0C0:\n"
                 "B       loc_FFC3A0D4\n"
 "loc_FFC3A0C4:\n"
                 "B       loc_FFC3A0D4\n"
 "loc_FFC3A0C8:\n"
                 "B       loc_FFC3A1D4\n"
 "loc_FFC3A0CC:\n"
                 "B       loc_FFC3A0D4\n"
 "loc_FFC3A0D0:\n"
                 "B       loc_FFC3A0D4\n"
 "loc_FFC3A0D4:\n"
                 "MOV     R2, #0\n"
                 "MOV     R1, #0x200\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC4C3DC\n"
                 "MOVS    R4, R0\n"
                 "BNE     loc_FFC3A0F4\n"
 "loc_FFC3A0EC:\n"
                 "MOV     R0, #0\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 "loc_FFC3A0F4:\n"
                 "LDR     R12, [R5,#0x4C]\n"
                 "MOV     R3, R4\n"
                 "MOV     R2, #1\n"
                 "MOV     R1, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R12\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FFC3A120\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC4C528\n"
                 "B       loc_FFC3A0EC\n"
 "loc_FFC3A120:\n"
                 "LDR     R1, [R5,#0x68]\n"
                 "MOV     R0, R8\n"
                 "BLX     R1\n"

		 "MOV   R1, R4\n"           // + pointer to MBR in R1
		 "BL    mbr_read_dryos\n"   // + total sectors count in R0 before and after call

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
            //   "LDRB    LR, [R4,#0x1FF]\n"     // -
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
            //   "LDRB    R12, [R4,#0x1FE]\n"     // -
                 "LDRB    R12, [LR,#0x1FE]\n"           // + First MBR signature byte (0x55), LR is original offset.
                 "LDRB    LR, [LR,#0x1FF]\n"            // + Last MBR signature byte (0xAA), LR is original offset.
                 "MOV     R4, #0\n"
                 "BNE     loc_FFC3A1AC\n"
                 "CMP     R0, R1\n"
                 "BCC     loc_FFC3A1AC\n"
                 "ADD     R2, R1, R3\n"
                 "CMP     R2, R0\n"
                 "CMPLS   R12, #0x55\n"
                 "CMPEQ   LR, #0xAA\n"
                 "MOVEQ   R7, R1\n"
                 "MOVEQ   R6, R3\n"
                 "MOVEQ   R4, #1\n"
 "loc_FFC3A1AC:\n"
                 "MOV     R0, #2\n"
                 "BL      sub_FFC4C528\n"
                 "CMP     R4, #0\n"
                 "BNE     loc_FFC3A1E8\n"
                 "LDR     R1, [R5,#0x68]\n"
                 "MOV     R7, #0\n"
                 "MOV     R0, R8\n"
                 "BLX     R1\n"
                 "MOV     R6, R0\n"
                 "B       loc_FFC3A1E8\n"
 "loc_FFC3A1D4:\n"
                 "MOV     R6, #0x40\n"
                 "B       loc_FFC3A1E8\n"
 "loc_FFC3A1DC:\n"
                 "LDR     R1, =0x5C9\n"
                 "LDR     R0, =0xFFC39FE8\n"
                 "BL      sub_FFC0BE9C\n"
 "loc_FFC3A1E8:\n"
                 "STR     R7, [R5,#0x44]!\n"
                 "MOV     R0, #1\n"
                 "STR     R6, [R5,#4]\n"
                 "LDMFD   SP!, {R4-R8,PC}\n"
 );
}



