#include "camera.h"
#include "conf.h"

void debug_led(int state);

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table[24]={0x2000, 0x38D,0x788,0x5800,0x9C5,0x14B8,0x10000,0x1C6A,0x3C45,0x8000,0xE35,0x1E23,0x1CCD,-0x2E1,-0x579,0x4F33,-0x7EB,-0xF0C,0xE666,-0x170A,-0x2BC6,0x7333,-0xB85,-0x15E3}; // @ 0xFFAA8CCC 
 
long table[24]; 

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<24;i++) table[i]=(def_table[i]*a)/b; 
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};




// Extracted method: taskcreate_MovieRecord (FF858324-FF858408)
// Overridden calls:
//     task_MovieRecord
void __attribute__((naked,noinline)) taskcreate_MovieRecord_my() {
    asm volatile (

    "var_20         = -0x20\n"

        "     STMFD   SP!, {R3-R9,LR}\n"
        "     LDR     R5, =0x54E0\n"
        "     MOV     R6, #0\n"
        "     STR     R6, [R5,#0x24]\n"
        "     LDR     R0, [R5,#8]\n"
        "     LDR     R8, =0x2710\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF8583DC\n"
        "     MOV     R0, #1\n"
        "     STR     R0, [R5,#8]\n"
        "     MOV     R0, #0\n"
        "     MOV     R1, #0\n"
        "     BL         sub_FF81BF0C\n"
        "     STR     R0, [R5,#0x14]\n"
        "     MOV     R0, #0\n"
        "     MOV     R1, #0\n"
        "     BL         sub_FF81BF0C\n"
        "     STR     R0, [R5,#0x18]\n"
        "     MOV     R0, #0\n"
        "     MOV     R1, #0xA\n"
        "     BL         sub_FF81BEC4\n"
        "     STR     R0, [R5,#0x1C]\n"
        "     MOV     R0, #0\n"
        "     MOV     R1, #0xA\n"
        "     BL         sub_FF81BEC4\n"
        "     LDR     R7, =0x19C5C\n"
        "     MOV     R4, #9\n"
        "     ADD     R9, R4, #0x2D4\n"
        "     STR     R0, [R5,#0x20]\n"

    "loc_FF858398:\n"    // CODE XREF: taskcreate_MovieRecord+98j
        "     RSB     R0, R4, R4,LSL#3\n"
        "     STR     R6, [R7,R0,LSL#2]\n"
        "     ADD     R1, R7, R0,LSL#2\n"
        "     STR     R9, [SP,#0x20+var_20]\n"
        "     LDR     R0, [R5,#0x20]\n"
        "     LDR     R3, =0xFF8575B0\n"    // aMovierecorder_
        "     MOV     R2, R8\n"
        "     BL         sub_FF81BFD0\n"
        "     SUBS    R4, R4, #1\n"
        "     BPL     loc_FF858398\n"
        "     MOV     R3, #0\n"
        "     STR     R3, [SP,#0x20+var_20]\n"
        "     ADR     R3, task_MovieRecord_my\n"    //   --------------->
        "     MOV     R2, #0x1000\n"
        "     MOV     R1, #0x14\n"
        "     LDR     R0, =0xFF858528\n"    // aMovierecord = "MovieRecord"
        "     BL         _KernelCreateTask\n"

    "loc_FF8583DC:\n"    // CODE XREF: taskcreate_MovieRecord+1Cj
        "     BL         _taskcreate_AviWrite\n"
        "     BL         sub_FF858440\n"
        "     MOV     R1, R0\n"
        "     MOV     R0, #0xB\n"
        "     ADD     R3, R0, #0x2DC\n"
        "     STR     R0, [R1]\n"
        "     STR     R3, [SP,#0x20+var_20]\n"
        "     LDR     R3, =0xFF8575B0\n"    // aMovierecorder_ = "MovieRecorder.c"
        "     MOV     R2, R8\n"
        "     LDR     R0, [R5,#0x1C]\n"
        "     BL         sub_FF81BFD0\n"
        "     LDMFD   SP!, {R3-R9,PC}\n"
    );
}

// Extracted method: task_MovieRecord (FF85821C-FF858320)
// Overridden calls:
//     sub_FF857CB4
void __attribute__((naked,noinline)) task_MovieRecord_my() {
	asm volatile (

    "var_20         = -0x20\n"
    "var_1C         = -0x1C\n"

        "     STMFD   SP!, {R2-R8,LR}\n"
        "     LDR     R8, =0x32B\n"
        "     LDR     R7, =0x2710\n"
        "     LDR     R4, =0x54E0\n"
        "     MOV     R6, #0\n"
        "     MOV     R5, #1\n"

    "loc_FF858234:\n"    // CODE XREF: task_MovieRecord+104j
	    "     LDR     R0, [R4,#0x1C]\n"
        "     MOV     R2, #0\n"
        "     ADD     R1, SP, #0x20+var_1C\n"
        "     BL         sub_FF829130\n"
        "     LDR     R0, [R4,#0x24]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF858304\n"
        "     LDR     R0, [SP,#0x20+var_1C]\n"
        "     LDR     R1, [R0]\n"
        "     SUB     R1, R1, #2\n"
        "     CMP     R1, #9\n"
        "     ADDLS   PC, PC, R1,LSL#2\n"
        "     B         loc_FF858304\n"


    "loc_FF858268:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF8582B8\n"


    "loc_FF85826C:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF8582D8\n"


    "loc_FF858270:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF8582E8\n"


    "loc_FF858274:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF8582F0\n"


    "loc_FF858278:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF8582C0\n"


    "loc_FF85827C:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF8582F8\n"


    "loc_FF858280:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF8582C8\n"


    "loc_FF858284:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF858304\n"


    "loc_FF858288:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF858300\n"


    "loc_FF85828C:\n"    // CODE XREF: task_MovieRecord+44j
        "     B         loc_FF858290\n"

    "loc_FF858290:\n"    // CODE XREF: task_MovieRecord+44j

        "     STR     R6, [R4,#0x38]\n"
        "     LDR     R0, =0xFF857EF0\n"    // nullsub_206
        "     LDR     R2, =0xFF857820\n"    // sub_FF857820
        "     LDR     R1, =0x19D84\n"
        "     STR     R0, [R4,#0xA4]\n"
        "     LDR     R0, =0xFF857904\n"    // sub_FF857904
        "     STR     R6, [R4,#0x28]\n"
        "     BL         sub_FF8C0804\n"
        "     STR     R5, [R4,#0x3C]\n"
        "     B         loc_FF858304\n"


    "loc_FF8582B8:\n"    // CODE XREF: task_MovieRecord+44j


        "     BL      unlock_optical_zoom\n"     //  +
        "     BL         sub_FF857FE8\n"
        "     B         loc_FF858304\n"


    "loc_FF8582C0:\n"    // CODE XREF: task_MovieRecord+44j


        "     BL         sub_FF857CB4_my\n"    //   --------------->
        "     B         loc_FF858304\n"


    "loc_FF8582C8:\n"    // CODE XREF: task_MovieRecord+44j


        "     LDR     R1, [R0,#0x10]\n"
        "     LDR     R0, [R0,#4]\n"
        "     BL         sub_FF92E71C\n"
        "     B         loc_FF858304\n"


    "loc_FF8582D8:\n"    // CODE XREF: task_MovieRecord+44j


        "     LDR     R0, [R4,#0x3C]\n"
        "     CMP     R0, #5\n"
        "     STRNE   R5, [R4,#0x2C]\n"
        "     B         loc_FF858304\n"


    "loc_FF8582E8:\n"    // CODE XREF: task_MovieRecord+44j


        "     BL         sub_FF857AB8\n"
        "     B         loc_FF858304\n"


    "loc_FF8582F0:\n"    // CODE XREF: task_MovieRecord+44j


        "     BL         sub_FF857950\n"
        "     B         loc_FF858304\n"


    "loc_FF8582F8:\n"    // CODE XREF: task_MovieRecord+44j


        "     BL         sub_FF8577AC\n"
        "     B         loc_FF858304\n"


    "loc_FF858300:\n"    // CODE XREF: task_MovieRecord+44j


        "     BL         sub_FF85846C\n"

    "loc_FF858304:\n"    // CODE XREF: task_MovieRecord+30j



        "     LDR     R1, [SP,#0x20+var_1C]\n"
        "     LDR     R3, =0xFF8575B0\n"    // aMovierecorder_
        "     STR     R6, [R1]\n"
        "     STR     R8, [SP,#0x20+var_20]\n"
        "     LDR     R0, [R4,#0x20]\n"
        "     MOV     R2, R7\n"
        "     BL         sub_FF81BFD0\n"
        "     B         loc_FF858234\n"
    );
}

// Extracted method: sub_FF857CB4 (FF857CB4-FF857EEC)
// Overridden calls:
//     sub_FF92CAB4
void __attribute__((naked,noinline)) sub_FF857CB4_my() {
    asm volatile (

    "var_58         = -0x58\n"
    "var_54         = -0x54\n"
    "var_50         = -0x50\n"
    "var_44         = -0x44\n"
    "var_34         = -0x34\n"
    "var_30         = -0x30\n"
    "var_2C         = -0x2C\n"
    "var_28         = -0x28\n"
    "var_24         = -0x24\n"
    "var_20         = -0x20\n"

        "     STMFD   SP!, {R4-R9,LR}\n"
        "     SUB     SP, SP, #0x3C\n"
        "     MOV     R7, #0\n"
        "     LDR     R5, =0x54E0\n"
        "     MOV     R4, R0\n"
        "     STR     R7, [SP,#0x58+var_2C]\n"
        "     STR     R7, [SP,#0x58+var_34]\n"
        "     LDR     R0, [R5,#0x3C]\n"
        "     MOV     R8, #4\n"
        "     CMP     R0, #3\n"
        "     STREQ   R8, [R5,#0x3C]\n"
        "     LDR     R0, [R5,#0xA4]\n"
        "     MOV     R6, #0\n"
    ".long   0xE12FFF30\n"    // 	     BLX     R0
        "     LDR     R0, [R5,#0x3C]\n"
        "     CMP     R0, #4\n"
        "     BNE     loc_FF857DC4\n"
        "     LDRH    R0, [R5,#2]\n"
        "     MOV     R9, #1\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF857D30\n"
        "     LDRH    R1, [R5,#4]\n"
        "     LDR     R0, [R5,#0x4C]\n"
        "     MUL     R0, R1, R0\n"
        "     MOV     R1, #0x3E8\n"
        "     BL         sub_FFA8D90C\n"
        "     MOV     R1, R0\n"
        "     LDR     R0, [R5,#0x54]\n"
        "     BL         sub_FFA8D90C\n"
        "     CMP     R1, #0\n"
        "     BNE     loc_FF857D4C\n"

    "loc_FF857D30:\n"    // CODE XREF: sub_FF857CB4+50j
        "     ADD     R3, SP, #0x58+var_34\n"
        "     ADD     R2, SP, #0x58+var_30\n"
        "     ADD     R1, SP, #0x58+var_2C\n"
        "     ADD     R0, SP, #0x58+var_28\n"
        "     BL         sub_FF92E8B0\n"
        "     MOVS    R6, R0\n"
        "     BNE     loc_FF857D68\n"

    "loc_FF857D4C:\n"    // CODE XREF: sub_FF857CB4+78j
        "     LDR     R0, [R5,#0x2C]\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF857DCC\n"
        "     LDR     R0, [R5,#0x54]\n"
        "     LDR     R1, [R5,#0x40]\n"
        "     CMP     R0, R1\n"
        "     BCC     loc_FF857DCC\n"

    "loc_FF857D68:\n"    // CODE XREF: sub_FF857CB4+94j
        "     CMP     R6, #0x80000001\n"
        "     STREQ   R8, [R5,#0x58]\n"
        "     BEQ     loc_FF857DA0\n"
        "     CMP     R6, #0x80000003\n"
        "     STREQ   R9, [R5,#0x58]\n"
        "     BEQ     loc_FF857DA0\n"
        "     CMP     R6, #0x80000005\n"
        "     MOVEQ   R0, #2\n"
        "     BEQ     loc_FF857D9C\n"
        "     CMP     R6, #0x80000007\n"
        "     STRNE   R7, [R5,#0x58]\n"
        "     BNE     loc_FF857DA0\n"
        "     MOV     R0, #3\n"

    "loc_FF857D9C:\n"    // CODE XREF: sub_FF857CB4+D4j
        "     STR     R0, [R5,#0x58]\n"

    "loc_FF857DA0:\n"    // CODE XREF: sub_FF857CB4+BCj

        "     LDR     R0, =0x19DB4\n"
        "     LDR     R0, [R0,#8]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF857DB8\n"
        "     BL         sub_FF8459F8\n"
        "     B         loc_FF857DBC\n"


    "loc_FF857DB8:\n"    // CODE XREF: sub_FF857CB4+F8j
        "     BL         sub_FF8577AC\n"

    "loc_FF857DBC:\n"    // CODE XREF: sub_FF857CB4+100j
        "     MOV     R0, #5\n"
        "     STR     R0, [R5,#0x3C]\n"

    "loc_FF857DC4:\n"    // CODE XREF: sub_FF857CB4+40j

        "     ADD     SP, SP, #0x3C\n"
        "     LDMFD   SP!, {R4-R9,PC}\n"


    "loc_FF857DCC:\n"    // CODE XREF: sub_FF857CB4+A0j

        "     LDR     R12, [SP,#0x58+var_2C]\n"
        "     CMP     R12, #0\n"
        "     BEQ     loc_FF857E98\n"
        "     STR     R9, [R5,#0x30]\n"
        "     LDR     R0, [R5,#0x70]\n"
        "     LDR     R1, [R4,#0x14]\n"
        "     LDR     R2, [R4,#0x18]\n"
        "     LDR     LR, [R4,#0xC]\n"
        "     ADD     R3, SP, #0x58+var_24\n"
        "     ADD     R6, SP, #0x58+var_44\n"
        "     STMIA   R6, {R0-R3}\n"
        "     LDR     R0, [SP,#0x58+var_34]\n"
        "     LDR     R3, [R5,#0x5C]\n"
        "     LDR     R1, [SP,#0x58+var_30]\n"
        "     ADD     R2, SP, #0x58+var_20\n"
        "     ADD     R6, SP, #0x58+var_50\n"
        "     STMIA   R6, {R0,R2,R3}\n"
        "     STR     R1, [SP,#0x58+var_54]\n"
        "     STR     R12, [SP,#0x58+var_58]\n"
        "     LDMIB   R4, {R0,R1}\n"
        "     LDR     R3, [SP,#0x58+var_28]\n"
        "     MOV     R2, LR\n"
        "     BL         sub_FF8EBADC\n"
        "     LDR     R0, [R5,#0x14]\n"
        "     MOV     R1, #0x3E8\n"
        "     BL         _TakeSemaphore\n"
        "     CMP     R0, #9\n"
        "     BNE     loc_FF857E4C\n"
        "     BL         sub_FF92EE8C\n"
        "     MOV     R0, #0x90000\n"
        "     STR     R9, [R5,#0x3C]\n"
        "     B         loc_FF857E64\n"


    "loc_FF857E4C:\n"    // CODE XREF: sub_FF857CB4+184j
        "     LDR     R0, [SP,#0x58+var_24]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF857E6C\n"
        "     BL         sub_FF92EE8C\n"
        "     MOV     R0, #0xA0000\n"
        "     STR     R9, [R5,#0x3C]\n"

    "loc_FF857E64:\n"    // CODE XREF: sub_FF857CB4+194j
        "     BL         _HardwareDefect\n"
        "     B         loc_FF857DC4\n"


    "loc_FF857E6C:\n"    // CODE XREF: sub_FF857CB4+1A0j
        "     BL         sub_FF8EBBA0\n"
        "     LDR     R0, [SP,#0x58+var_28]\n"
        "     LDR     R1, [SP,#0x58+var_20]\n"
        "     BL         sub_FF92EC34\n"
        "     LDR     R0, [R5,#0x50]\n"
        "     LDR     R1, =0x5550\n"
        "     ADD     R0, R0, #1\n"
        "     STR     R0, [R5,#0x50]\n"
        "     LDR     R0, [SP,#0x58+var_20]\n"
        "     MOV     R2, #0\n"
        "     BL         sub_FF92CAB4_my\n"    //   --------------->

    "loc_FF857E98:\n"    // CODE XREF: sub_FF857CB4+120j
        "     LDR     R0, [R5,#0x54]\n"
        "     ADD     R0, R0, #1\n"
        "     STR     R0, [R5,#0x54]\n"
        "     LDR     R1, [R5,#0x7C]\n"
        "     MUL     R0, R1, R0\n"
        "     LDR     R1, [R5,#0x78]\n"
        "     BL         sub_FFA8D90C\n"
        "     MOV     R4, R0\n"
        "     BL         sub_FF92EEC4\n"
        "     LDR     R1, [R5,#0x74]\n"
        "     CMP     R1, R4\n"
        "     BNE     loc_FF857ED4\n"
        "     LDR     R0, [R5,#0x34]\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF857EE8\n"

    "loc_FF857ED4:\n"    // CODE XREF: sub_FF857CB4+210j
        "     LDR     R1, [R5,#0x88]\n"
        "     MOV     R0, R4\n"
    ".long   0xE12FFF31\n"    // 	     BLX     R1
        "     STR     R4, [R5,#0x74]\n"
        "     STR     R7, [R5,#0x34]\n"

    "loc_FF857EE8:\n"    // CODE XREF: sub_FF857CB4+21Cj
        "     STR     R7, [R5,#0x30]\n"
        "     B         loc_FF857DC4\n"
    );
}

// Extracted method: sub_FF92CAB4 (FF92CAB4-FF92CB94)
// Overridden calls:
void __attribute__((naked,noinline)) sub_FF92CAB4_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R8,LR}\n"
        "     LDR     R4, =0xA8EC\n"
        "     LDR     LR, [R4]\n"
        "     LDR     R2, [R4,#8]\n"
        "     CMP     LR, #0\n"
        "     LDRNE   R3, [R4,#0xC]\n"
        "     MOV     R5, R2\n"
        "     CMPNE   R3, #1\n"
        "     MOVEQ   R2, #0\n"
        "     STREQ   R0, [R4]\n"
        "     STREQ   R2, [R4,#0xC]\n"
        "     BEQ     loc_FF92CB80\n"
        "     LDR     R3, [R4,#4]\n"

        "     LDR     R7, =table\n"  // +
		//"     LDR     R7, =0xFFAA8CCC\n"    // unk_FFAA8CCC

        "     ADD     R12, R3, R3,LSL#1\n"
        "     LDR     R3, [R7,R12,LSL#2]\n"
        "     ADD     R6, R7, #0x30\n"
        "     LDR     R8, [R6,R12,LSL#2]\n"
        "     SUB     R3, LR, R3\n"
        "     CMP     R3, #0\n"
        "     SUB     LR, LR, R8\n"
        "     BLE     loc_FF92CB3C\n"
        "     ADD     R12, R7, R12,LSL#2\n"
        "     LDR     LR, [R12,#4]\n"
        "     CMP     LR, R3\n"
        "     ADDGE   R2, R2, #1\n"
        "     BGE     loc_FF92CB30\n"
        "     LDR     R12, [R12,#8]\n"
        "     CMP     R12, R3\n"
        "     ADDLT   R2, R2, #3\n"
        "     ADDGE   R2, R2, #2\n"

    "loc_FF92CB30:\n"    // CODE XREF: sub_FF92CAB4+68j
        //"     CMP     R2, #0x17\n"
        //"     MOVGE   R2, #0x16\n"
        "     CMP     R2, #0x1A\n"   // +
        "     MOVGE   R2, #0x19\n"   // +
        "     B         loc_FF92CB70\n"


    "loc_FF92CB3C:\n"    // CODE XREF: sub_FF92CAB4+54j
        "     CMP     LR, #0\n"
        "     BGE     loc_FF92CB70\n"
        "     ADD     R3, R6, R12,LSL#2\n"
        "     LDR     R12, [R3,#4]\n"
        "     CMP     R12, LR\n"
        "     SUBLE   R2, R2, #1\n"
        "     BLE     loc_FF92CB68\n"
        "     LDR     R3, [R3,#8]\n"
        "     CMP     R3, LR\n"
        "     SUBGT   R2, R2, #3\n"
        "     SUBLE   R2, R2, #2\n"

    "loc_FF92CB68:\n"    // CODE XREF: sub_FF92CAB4+A0j
        "     CMP     R2, #0\n"
        "     MOVLT   R2, #0\n"

    "loc_FF92CB70:\n"    // CODE XREF: sub_FF92CAB4+84j

        "     CMP     R2, R5\n"
        "     STRNE   R2, [R4,#8]\n"
        "     MOVNE   R2, #1\n"
        "     STRNE   R2, [R4,#0xC]\n"

    "loc_FF92CB80:\n"    // CODE XREF: sub_FF92CAB4+2Cj
        //"     LDR     R2, =0xFFAA8C70\n"    // unk_FFAA8C70
        "     LDR     R2, =CompressionRateTable\n"   // +

        "     LDR     R3, [R4,#8]\n"
        "     LDR     R2, [R2,R3,LSL#2]\n"
        
        "     LDR     R3, =video_mode\n"      // +
        "     LDR     R3, [R3]\n"             // +
        "     LDR     R3, [R3]\n"             // +
        "     CMP     R3, #1\n"               // +
        "     LDREQ   R3, =video_quality\n"   // +     
        "     LDREQ   R3, [R3]\n"             // +     
        "     LDREQ   R2, [R3]\n"             // +   

		"     STR     R2, [R1]\n"
        "     STR     R0, [R4]\n"
#if CAM_CAN_MUTE_MICROPHONE
		//"     BL      mute_on_zoom\n"     // +   //  -- TurnOnMic/TurnOffMic don't seem to have any effect
#endif
        "     LDMFD   SP!, {R4-R8,PC}\n"
    );
}

// Extracted method: sub_FF85CDD4 (FF85CDD4-FF85D044)
// Overridden calls:
//     taskcreate_MovieRecord
void __attribute__((naked,noinline)) sub_FF85CDD4_my() {
    asm volatile (

    "var_50         = -0x50\n"
    "var_44         = -0x44\n"
    "var_28         = -0x28\n"
    "var_24         = -0x24\n"
    "var_20         = -0x20\n"
    "var_1C         = -0x1C\n"

        "     STMFD   SP!, {R4-R8,LR}\n"
        "     MOV     R8, R0\n"
        "     MOV     R0, #0x41\n"
        "     SUB     SP, SP, #0x38\n"
        "     MOV     R5, #0\n"
        "     STR     R0, [SP,#0x50+var_1C]\n"
        "     BL         sub_FF85CDA4\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R1, =0x13B\n"
        "     BNE     loc_FF85CF80\n"
        "     LDR     R4, =0x567C\n"
        "     MOV     R1, #0x1E\n"
        "     LDR     R0, [R4,#0xC]\n"
        "     BL         sub_FF828EE0\n"
        "     BL         sub_FF869600\n"
        "     STR     R0, [R4,#4]\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF865744\n"
        "     STR     R0, [SP,#0x50+var_28]\n"
        "     ADD     R0, SP, #0x50+var_28\n"
        "     MOV     R1, SP\n"
        "     BL         sub_FF865240\n"
        "     MOV     R0, SP\n"
        "     BL         sub_FF865128\n"
        "     STR     R0, [SP,#0x50+var_24]\n"
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R3, #4\n"
        "     ADD     R2, SP, #0x50+var_24\n"
        "     MOV     R1, #0x34\n"
        "     BL         sub_FF869920\n"
        "     LDR     R7, [SP,#0x50+var_24]\n"
        "     BL         sub_FF85D2FC\n"
        "     MOV     R6, #0\n"
        "     ADD     R1, SP, #0x50+var_28\n"
        "     ADD     R0, SP, #0x50+var_24\n"
        "     STR     R6, [SP,#0x50+var_24]\n"
        "     STR     R6, [SP,#0x50+var_28]\n"
        "     BL         sub_FF831E08\n"
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R3, #2\n"
        "     ADD     R2, SP, #0x50+var_24\n"
        "     MOV     R1, #0x2F\n"
        "     BL         sub_FF869920\n"
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R3, #2\n"
        "     ADD     R2, SP, #0x50+var_28\n"
        "     MOV     R1, #0x2D\n"
        "     BL         sub_FF869920\n"
        "     ADD     R1, SP, #0x50+var_28\n"
        "     ADD     R0, SP, #0x50+var_24\n"
        "     BL         sub_FF835568\n"
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R3, #2\n"
        "     ADD     R2, SP, #0x50+var_24\n"
        "     MOV     R1, #0x30\n"
        "     BL         sub_FF869920\n"
        "     ADD     R1, SP, #0x50+var_28\n"
        "     ADD     R0, SP, #0x50+var_24\n"
        "     BL         sub_FF8325CC\n"
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R3, #2\n"
        "     ADD     R2, SP, #0x50+var_28\n"
        "     MOV     R1, #0x2E\n"
        "     BL         sub_FF869920\n"
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R3, #2\n"
        "     ADD     R2, SP, #0x50+var_24\n"
        "     MOV     R1, #0xB8\n"
        "     BL         sub_FF8699CC\n"
        "     TST     R0, #1\n"
        "     LDRNE   R1, =0x11D\n"
        "     LDRNE   R0, =0xFF85D1F8\n"    // aSsmovierec_c = "SsMovieRec.c"
        "     BLNE    _DebugAssert\n"
        "     LDRH    R0, [SP,#0x50+var_24]\n"
        "     MOV     R3, #4\n"
        "     ADD     R2, SP, #0x50+var_28\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R0, #1\n"
        "     STR     R0, [SP,#0x50+var_28]\n"
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R1, #0x92\n"
        "     BL         sub_FF869920\n"
        "     MOV     R2, #1\n"
        "     ADD     R1, SP, #0x50+var_1C\n"
        "     MOV     R0, #0xFA\n"
        "     BL         _PT_GetPropertyCaseString\n"
        "     TST     R0, #1\n"
        "     LDRNE   R1, =0x152\n"
        "     LDRNE   R0, =0xFF85D1F8\n"    // aSsmovierec_c = "SsMovieRec.c"
        "     BLNE    _DebugAssert\n"
        "     LDRB    R0, [SP,#0x50+var_1C]\n"
        "     MOV     R3, R8\n"
        "     MOV     R2, #0x14\n"
        "     AND     R1, R0, #0xFF\n"
        "     ADD     R0, SP, #0x50+var_20\n"
        "     STR     R7, [SP,#0x50+var_50]\n"
        "     BL         sub_FF90835C\n"
        "     TST     R0, #1\n"
        "     LDRNE   R1, =0x156\n"
        "     BNE     loc_FF85CF80\n"
        "     LDR     R0, =0x1A068\n"
        "     LDR     R1, [SP,#0x50+var_20]\n"
        "     MOV     R2, #0x10\n"
        "     BL         sub_FF8FB780\n"
        "     TST     R0, #1\n"
        "     BEQ     loc_FF85CF90\n"
        "     LDR     R1, =0x15E\n"

    "loc_FF85CF80:\n"    // CODE XREF: sub_FF85CDD4+24j

        "     LDR     R0, =0xFF85D1F8\n"    // aSsmovierec_c = "SsMovieRec.c"
        "     BL         _DebugAssert\n"

    "loc_FF85CF88:\n"    // CODE XREF: sub_FF85CDD4+270j
        "     ADD     SP, SP, #0x38\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"


    "loc_FF85CF90:\n"    // CODE XREF: sub_FF85CDD4+1A4j
        "     LDR     R0, [R4,#4]\n"
        "     MOV     R3, #4\n"
        "     ADD     R2, SP, #0x50+var_20\n"
        "     MOV     R1, #0x2B\n"
        "     BL         sub_FF869920\n"
        "     BL         sub_FF879F30\n"
        "     LDRSB   R1, [SP,#0x50+var_1C]\n"
        "     CMP     R0, R1\n"
        "     MOVEQ   R7, #0\n"
        "     BEQ     loc_FF85CFE4\n"
        "     LDR     R5, =0x1A068\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF87A0AC\n"
        "     MOV     R8, R0\n"
        "     BL         sub_FF8B319C\n"
        "     CMP     R8, R0\n"
        "     MOV     R7, R0\n"
        "     LDRLS   R1, =0x16B\n"
        "     LDRLS   R0, =0xFF85D1F8\n"    // aSsmovierec_c = "SsMovieRec.c"
        "     BLLS    _DebugAssert\n"
        "     SUB     R7, R8, R7\n"

    "loc_FF85CFE4:\n"    // CODE XREF: sub_FF85CDD4+1E0j
        "     BL         taskcreate_MovieRecord_my\n"    //   --------------->
        "     LDR     R0, =0x1A08C\n"
        "     LDRH    R3, [R0,#0x4E]\n"
        "     LDRH    R2, [R0,#0x4C]\n"
        "     LDR     R1, [R0,#0x48]\n"
        "     LDR     R0, [R0,#0x44]\n"
        "     BL         sub_FF8572B4\n"
        "     MOV     R3, #0\n"
        "     LDR     R2, =0xFF85CD6C\n"    // unk_FF85CD6C
        "     MOV     R1, #0\n"
        "     LDR     R0, =0xFF85CD80\n"    // unk_FF85CD80
        "     ADD     R8, SP, #0x50+var_44\n"
        "     STMIA   R8, {R0-R3}\n"
        "     LDR     R2, =0xFF85CD90\n"    // unk_FF85CD90
        "     LDR     R1, =0xFF85CD7C\n"    // unk_FF85CD7C
        "     STMEA   SP, {R1-R3}\n"
        "     LDR     R1, [R4,#4]\n"
        "     MOV     R3, R6\n"
        "     MOV     R2, R7\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF857610\n"
        "     LDR     R0, [R4,#0xC]\n"
        "     MOV     R1, #0x20\n"
        "     BL         sub_FF828EAC\n"
        "     B         loc_FF85CF88\n"
        ".LTORG\n" // make literal pool
    );
}

// Extracted method: sub_FF828534 (FF828534-FF828568)
// Overridden calls:
//     sub_FF85CDD4
//     sub_FF85CDD4
void __attribute__((naked,noinline)) sub_FF828534_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     MOV     R4, R0\n"
        "     MOV     R0, #0x20\n"
        "     LDR     R1, =0xFF828754\n"    // aSsapiRecordmov = "SSAPI::RecordMovie"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF828AB0\n"
        "     CMP     R0, #0\n"
        "     LDMNEFD SP!, {R4,PC}\n"
        "     MOV     R0, #4\n"
        "     BL         sub_FF856814\n"
        "     BL         sub_FF85AD20\n"
        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF85CDD4_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF87821C (FF87821C-FF8782A8)
// Overridden calls:
//     sub_FF828534
void __attribute__((naked,noinline)) sub_FF87821C_my() {
    asm volatile (
        "     STMFD   SP!, {R3-R5,LR}\n"
        "     LDR     R4, =0x61D8\n"
        "     LDR     R0, [R4,#0x44]\n"
        "     CMP     R0, #1\n"
        "     BEQ     loc_FF878264\n"
        "     BL         _j_PTM_GetWorkingCaptureMode\n"
        "     SUB     R12, R0, #0xA00\n"
        "     SUBS    R12, R12, #0x29\n"
        "     MOV     R5, #1\n"
        "     BNE     loc_FF87825C\n"
        "     LDR     R0, =0x804F\n"
        "     MOV     R2, #1\n"
        "     MOV     R1, #1\n"
        "     BL         _j_PTM_SetCurrentItem_0\n"
        "     STR     R5, [R4,#0x44]\n"
        "     B         loc_FF878264\n"


    "loc_FF87825C:\n"    // CODE XREF: sub_FF87821C+24j
        "     STR     R5, [R4,#0x44]\n"
        "     BL         _LockMainPower\n"

    "loc_FF878264:\n"    // CODE XREF: sub_FF87821C+10j

        "     MOV     R1, #0\n"
        "     MOV     R0, #0x80\n"
        "     BL         sub_FF878F68\n"
        "     MOV     R2, #2\n"
        "     MOV     R1, SP\n"
        "     MOV     R0, #0x6B\n"
        "     BL         _PT_GetPropertyCaseString\n"
        "     MOV     R2, #2\n"
        "     MOV     R1, SP\n"
        "     MOV     R0, #0xA3\n"
        "     BL         _PT_SetPropertyCaseString\n"
        "     BL         sub_FF859634\n"
        "     BL         sub_FF877244\n"
        "     BL         sub_FF828534_my\n"    //   --------------->
        "     BL         sub_FF86A470\n"
        "     STR     R0, [R4,#0x4C]\n"
        "     BL         sub_FF8779C0\n"
        "     LDMFD   SP!, {R3-R5,PC}\n"
    );
}

// Extracted method: sub_FF878B58 (FF878B58-FF878B80)
// Overridden calls:
//     sub_FF87821C
//     sub_FF87821C
void __attribute__((naked,noinline)) sub_FF878B58_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF878D2C\n"    // a_entryaction_1 = "_EntryActionOnMoving"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     LDR     R1, =0x6228\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R1,#0xC]\n"
        "     MOV     R0, #4\n"
        "     BL         sub_FF878A9C\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF87821C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF8785AC (FF8785AC-FF878600)
// Overridden calls:
//     sub_FF878B58
void __attribute__((naked,noinline)) sub_FF8785AC_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF878888\n"    // a_entryactionon = "_EntryActionOnPreMoving"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     LDR     R4, =0x6228\n"
        "     LDR     R0, [R4,#0x10]\n"
        "     CMP     R0, #0\n"
        "     LDMEQFD SP!, {R4,LR}\n"
        "     BEQ     sub_FF878B58_my\n"    //   --------------->
        "     LDR     R1, =0xFF8788A4\n"    // a_entryaction_0 = "_EntryActionOnSelfTimer"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF94A468\n"
        "     LDR     R0, [R4,#0x18]\n"
        "     CMP     R0, #1\n"
        "     MOVNE   R0, #1\n"
        "     STRNE   R0, [R4,#0x18]\n"
        "     BLNE    _LockMainPower\n"
        "     MOV     R0, #9\n"
        "     BL         sub_FF878A9C\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF9492D0\n"
    );
}

// Extracted method: sub_FF878688 (FF878688-FF8789F4)
// Overridden calls:
//     sub_FF8785AC
//     sub_FF878B58
//     sub_FF878C50
//     sub_FF878C50
void __attribute__((naked,noinline)) sub_FF878688_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R8,LR}\n"
        "     MOV     R7, R1\n"
        "     MOV     R4, R0\n"
        "     BL         sub_FF878AB4\n"
        "     LDR     R5, =0x6228\n"
        "     LDR     R3, =0x201F\n"
        "     LDR     R12, [R5]\n"
        "     LDR     R2, =0x4008\n"
        "     LDR     R6, =0x9A3\n"
        "     LDR     R0, =0x3007\n"
        "     LDR     R1, =0x1051\n"
        "     CMP     R12, #9\n"
        "     SUB     LR, R3, #0x15\n"
        "     ADDLS   PC, PC, R12,LSL#2\n"
        "     B         loc_FF8789F0\n"


    "loc_FF8786C4:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF8786EC\n"


    "loc_FF8786C8:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF8786FC\n"


    "loc_FF8786CC:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF87870C\n"


    "loc_FF8786D0:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF878780\n"


    "loc_FF8786D4:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF8787C0\n"


    "loc_FF8786D8:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF878850\n"


    "loc_FF8786DC:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF8788EC\n"


    "loc_FF8786E0:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF878938\n"


    "loc_FF8786E4:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF8788FC\n"


    "loc_FF8786E8:\n"    // CODE XREF: sub_FF878688+34j
        "     B         loc_FF878960\n"


    "loc_FF8786EC:\n"    // CODE XREF: sub_FF878688+34j


        "     MOV     R1, R7\n"
        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF878608\n"


    "loc_FF8786FC:\n"    // CODE XREF: sub_FF878688+34j


        "     MOV     R1, R7\n"
        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R8,LR}\n"
        "     B         sub_FF878C50_my\n"    //   --------------->


    "loc_FF87870C:\n"    // CODE XREF: sub_FF878688+34j


        "     CMP     R4, R1\n"
        "     BEQ     loc_FF878770\n"
        "     SUB     R12, R4, #0x2000\n"
        "     SUBS    R12, R12, #6\n"
        "     BEQ     loc_FF878734\n"
        "     CMP     R4, R0\n"
        "     BEQ     loc_FF878778\n"
        "     SUB     R12, R4, #0x3100\n"
        "     SUBS    R12, R12, #0x4B\n"
        "     BNE     loc_FF8789F0\n"

    "loc_FF878734:\n"    // CODE XREF: sub_FF878688+94j
        "     BL         sub_FF877A08\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF878A9C\n"
        "     LDR     R0, [R5,#8]\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R1, #0\n"
        "     MOVNE   R0, R6\n"
        "     BNE     loc_FF878768\n"
        "     LDR     R0, [R5,#4]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF8789A0\n"
        "     LDR     R0, =0x9A1\n"
        "     MOV     R1, #0\n"

    "loc_FF878768:\n"    // CODE XREF: sub_FF878688+C8j
        "     BL         sub_FF878608\n"
        "     B         loc_FF8789A0\n"


    "loc_FF878770:\n"    // CODE XREF: sub_FF878688+88j

        "     BL         sub_FF878BA4\n"
        "     B         loc_FF8789A0\n"


    "loc_FF878778:\n"    // CODE XREF: sub_FF878688+9Cj

        "     BL         sub_FF878BDC\n"
        "     B         loc_FF8789A0\n"


    "loc_FF878780:\n"    // CODE XREF: sub_FF878688+34j


        "     SUB     R12, R4, #0x900\n"
        "     SUBS    R12, R12, #0xA2\n"
        "     BEQ     loc_FF8787B0\n"
        "     CMP     R4, R6\n"
        "     BEQ     loc_FF8787A8\n"
        "     CMP     R4, R1\n"
        "     BEQ     loc_FF8787B8\n"
        "     CMP     R4, R0\n"
        "     BLEQ    sub_FF878BDC\n"
        "     B         loc_FF8789F0\n"


    "loc_FF8787A8:\n"    // CODE XREF: sub_FF878688+108j
        "     BL         sub_FF8785AC_my\n"    //   --------------->
        "     B         loc_FF8789F0\n"


    "loc_FF8787B0:\n"    // CODE XREF: sub_FF878688+100j
        "     BL         sub_FF878B84\n"
        "     B         loc_FF8789F0\n"


    "loc_FF8787B8:\n"    // CODE XREF: sub_FF878688+110j
        "     BL         sub_FF878BA4\n"
        "     B         loc_FF8789F0\n"


    "loc_FF8787C0:\n"    // CODE XREF: sub_FF878688+34j


        "     CMP     R4, LR\n"
        "     BEQ     loc_FF878830\n"
        "     BGT     loc_FF8787F0\n"
        "     CMP     R4, R6\n"
        "     SUBNE   R12, R4, #0x900\n"
        "     SUBNES  R12, R12, #0xA5\n"
        "     BEQ     loc_FF87880C\n"
        "     CMP     R4, R1\n"
        "     BNE     loc_FF8789F0\n"
        "     BL         sub_FF82856C\n"
        "     BL         sub_FF878C2C\n"
        "     B         loc_FF8788F4\n"


    "loc_FF8787F0:\n"    // CODE XREF: sub_FF878688+140j
        "     CMP     R4, R3\n"
        "     BEQ     loc_FF878824\n"
        "     CMP     R4, R0\n"
        "     BEQ     loc_FF87883C\n"

    "loc_FF878800:\n"    // CODE XREF: sub_FF878688+1ECj
        "     CMP     R4, R2\n"
        "     BNE     loc_FF8789F0\n"
        "     B         loc_FF878830\n"


    "loc_FF87880C:\n"    // CODE XREF: sub_FF878688+150j
        "     BL         sub_FF82856C\n"
        "     MOV     R0, #5\n"
        "     BL         sub_FF878A9C\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R5,#0xC]\n"
        "     B         loc_FF8789A0\n"


    "loc_FF878824:\n"    // CODE XREF: sub_FF878688+16Cj
        "     MOV     R0, #5\n"
        "     BL         sub_FF878A9C\n"
        "     B         loc_FF87887C\n"


    "loc_FF878830:\n"    // CODE XREF: sub_FF878688+13Cj

        "     BL         sub_FF878C2C\n"
        "     BL         sub_FF878B84\n"
        "     B         loc_FF8789A0\n"


    "loc_FF87883C:\n"    // CODE XREF: sub_FF878688+174j
        "     BL         sub_FF82856C\n"
        "     BL         sub_FF878C2C\n"
        "     B         loc_FF878930\n"


    "loc_FF878848:\n"    // CODE XREF: sub_FF878688+270j

        "     BL         sub_FF878A9C\n"
        "     B         loc_FF8789A0\n"


    "loc_FF878850:\n"    // CODE XREF: sub_FF878688+34j


        "     CMP     R4, R3\n"
        "     BEQ     loc_FF87887C\n"
        "     BGT     loc_FF878870\n"
        "     CMP     R4, R1\n"
        "     BEQ     loc_FF8788F4\n"
        "     CMP     R4, LR\n"
        "     BEQ     loc_FF878830\n"
        "     B         loc_FF8789F0\n"


    "loc_FF878870:\n"    // CODE XREF: sub_FF878688+1D0j
        "     CMP     R4, R0\n"
        "     BNE     loc_FF878800\n"
        "     B         loc_FF878930\n"


    "loc_FF87887C:\n"    // CODE XREF: sub_FF878688+1A4j

        "     MOV     R0, R7\n"
        "     BL         sub_FF878BF8\n"
        "     B         loc_FF8789A0\n"




    "loc_FF8788EC:\n"    // CODE XREF: sub_FF878688+34j


        "     CMP     R4, R1\n"
        "     BNE     loc_FF8789F0\n"

    "loc_FF8788F4:\n"    // CODE XREF: sub_FF878688+164j

        "     MOV     R0, #8\n"
        "     B         loc_FF878848\n"


    "loc_FF8788FC:\n"    // CODE XREF: sub_FF878688+34j


        "     CMP     R4, R0\n"
        "     BEQ     loc_FF878930\n"
        "     BGT     loc_FF87891C\n"
        "     CMP     R4, LR\n"
        "     BEQ     loc_FF878770\n"
        "     CMP     R4, R3\n"
        "     BEQ     loc_FF87887C\n"
        "     B         loc_FF8789F0\n"


    "loc_FF87891C:\n"    // CODE XREF: sub_FF878688+27Cj
        "     CMP     R4, R2\n"
        "     SUBNE   R12, R4, #0x4000\n"
        "     SUBNES  R12, R12, #0xE\n"
        "     BEQ     loc_FF878770\n"
        "     B         loc_FF8789F0\n"


    "loc_FF878930:\n"    // CODE XREF: sub_FF878688+1BCj

        "     MOV     R0, #7\n"
        "     B         loc_FF878848\n"


    "loc_FF878938:\n"    // CODE XREF: sub_FF878688+34j


        "     CMP     R4, LR\n"
        "     BEQ     loc_FF878950\n"
        "     CMP     R4, R3\n"
        "     BEQ     loc_FF87887C\n"
        "     CMP     R4, R2\n"
        "     BNE     loc_FF8789F0\n"

    "loc_FF878950:\n"    // CODE XREF: sub_FF878688+2B4j
        "     BL         sub_FF878B84\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF877BD0\n"
        "     B         loc_FF8789A0\n"


    "loc_FF878960:\n"    // CODE XREF: sub_FF878688+34j


        "     SUB     R12, R4, #0x800\n"
        "     SUBS    R12, R12, #0x4A\n"
        "     BEQ     loc_FF8789A8\n"
        "     CMP     R4, R1\n"
        "     BEQ     loc_FF8789E0\n"
        "     CMP     R4, R0\n"
        "     BEQ     loc_FF8789D0\n"
        "     SUB     R12, R4, #0x3100\n"
        "     SUBS    R12, R12, #0x2A\n"
        "     BNE     loc_FF8789F0\n"
        "     BL         sub_FF878B3C\n"
        "     LDR     R0, [R5,#0x14]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF8789A0\n"
        "     BL         sub_FF878B58_my\n"    //   --------------->
        "     BL         sub_FF94A43C\n"

    "loc_FF8789A0:\n"    // CODE XREF: sub_FF878688+D4j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"


    "loc_FF8789A8:\n"    // CODE XREF: sub_FF878688+2E0j
        "     BL         sub_FF878B3C\n"
        "     LDR     R0, =0x8007\n"
        "     MOV     R1, #0\n"
        "     BL         _j_PTM_SetCurrentItem\n"
        "     BL         sub_FF949414\n"
        "     BL         sub_FF878B84\n"
        "     BL         sub_FF94A43C\n"
        "     BL         sub_FF877A08\n"
        "     MOV     R0, #0\n"
        "     B         loc_FF878848\n"


    "loc_FF8789D0:\n"    // CODE XREF: sub_FF878688+2F0j
        "     BL         sub_FF878B3C\n"
        "     BL         sub_FF949414\n"
        "     BL         sub_FF94A43C\n"
        "     B         loc_FF878778\n"


    "loc_FF8789E0:\n"    // CODE XREF: sub_FF878688+2E8j
        "     BL         sub_FF878B3C\n"
        "     BL         sub_FF949414\n"
        "     BL         sub_FF94A43C\n"
        "     B         loc_FF878770\n"


    "loc_FF8789F0:\n"    // CODE XREF: sub_FF878688+34j


        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"
    );
}

// Extracted method: sub_FF878C50 (FF878C50-FF878D10)
// Overridden calls:
//     sub_FF8785AC
void __attribute__((naked,noinline)) sub_FF878C50_my() {
    asm volatile (
        "     LDR     R3, =0x6228\n"
        "     LDR     R12, =0x2006\n"
        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, [R3,#0xC]\n"
        "     LDR     R2, [R3,#0x14]\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF878CC4\n"
        "     BGT     loc_FF878C90\n"
        "     SUB     R12, R0, #0x900\n"
        "     SUBS    R12, R12, #0xA2\n"
        "     BEQ     loc_FF878CE8\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x51\n"
        "     BNE     loc_FF878D0C\n"
        "     BL         sub_FF878BA4\n"
        "     B         loc_FF878D04\n"


    "loc_FF878C90:\n"    // CODE XREF: sub_FF878C50+1Cj
        "     SUB     R12, R0, #0x3000\n"
        "     SUBS    R12, R12, #7\n"
        "     BEQ     loc_FF878D00\n"
        "     SUB     R12, R0, #0x3100\n"
        "     SUBS    R12, R12, #0x4B\n"
        "     BNE     loc_FF878D0C\n"
        "     CMP     R2, #0\n"
        "     BNE     loc_FF878D04\n"
        "     LDR     R0, [R3,#8]\n"
        "     ORRS    R0, R0, R1\n"
        "     BEQ     loc_FF878CD0\n"
        "     BL         sub_FF8785AC_my\n"    //   --------------->
        "     B         loc_FF878D04\n"


    "loc_FF878CC4:\n"    // CODE XREF: sub_FF878C50+18j
        "     CMP     R2, #0\n"
        "     BLEQ    sub_FF877068\n"
        "     B         loc_FF878D04\n"


    "loc_FF878CD0:\n"    // CODE XREF: sub_FF878C50+68j
        "     LDR     R0, [R3,#4]\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R0, #3\n"
        "     BNE     loc_FF878CF8\n"
        "     BL         sub_FF878B84\n"
        "     B         loc_FF878D04\n"


    "loc_FF878CE8:\n"    // CODE XREF: sub_FF878C50+28j
        "     CMP     R1, #0\n"
        "     BNE     loc_FF878D04\n"
        "     BL         sub_FF828094\n"
        "     MOV     R0, #2\n"

    "loc_FF878CF8:\n"    // CODE XREF: sub_FF878C50+8Cj
        "     BL         sub_FF878A9C\n"
        "     B         loc_FF878D04\n"


    "loc_FF878D00:\n"    // CODE XREF: sub_FF878C50+48j
        "     BL         sub_FF878BDC\n"

    "loc_FF878D04:\n"    // CODE XREF: sub_FF878C50+3Cj

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4,PC}\n"


    "loc_FF878D0C:\n"    // CODE XREF: sub_FF878C50+34j

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}

// Extracted method: sub_FF877C0C (FF877C0C-FF878100)
// Overridden calls:
//     sub_FF877AA4
//     sub_FF878688
void __attribute__((naked,noinline)) sub_FF877C0C_my() {
    asm volatile (
        "     STMFD   SP!, {R3-R11,LR}\n"
        "     LDR     R5, =0x61D8\n"
        "     MOV     R4, R1\n"
        "     LDR     R1, [R5,#0x2C]\n"
        "     ADD     R0, R5, #0\n"
        "     LDR     R0, [R0,#0x14]\n"
        "     LDR     R11, =0x3007\n"
        "     LDR     R10, =0x9A5\n"
        "     CMP     R1, #0\n"
        "     MOV     R9, R3\n"
        "     MOV    R8, #0xFFFFFFFF\n"
        "     BEQ     loc_FF877CB0\n"
        "     CMP     R4, R11\n"
        "     BEQ     loc_FF877F40\n"
        "     CMP     R4, #0x800\n"
        "     LDREQ   R1, [R5,#0x3C]\n"
        "     MOVEQ   R4, R5\n"
        "     CMPEQ   R9, R1\n"
        "     BNE     loc_FF878090\n"
        "     MOV     R1, #0\n"
        "     STR     R1, [R4,#0x2C]\n"
        "     CMP     R0, #0\n"
        "     STR     R8, [R4,#0x3C]\n"
        "     BNE     loc_FF877C88\n"
        "     BL         sub_FF82C964\n"
        "     CMP     R0, #1\n"
        "     BEQ     loc_FF877C84\n"
        "     BL         sub_FF82C96C\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF877C88\n"

    "loc_FF877C84:\n"    // CODE XREF: sub_FF877C0C+68j
        "     BL         sub_FF877A34\n"

    "loc_FF877C88:\n"    // CODE XREF: sub_FF877C0C+5Cj

        "     LDR     R0, [R4,#0x48]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF877CA0\n"
        "     BL         sub_FF82C974\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF877FF4\n"

    "loc_FF877CA0:\n"    // CODE XREF: sub_FF877C0C+84j
        "     BL         sub_FF877A34\n"
        "     MOV     R1, #1\n"
        "     MOV     R0, R10\n"
        "     B         loc_FF87802C\n"


    "loc_FF877CB0:\n"    // CODE XREF: sub_FF877C0C+2Cj
        "     CMP     R0, #1\n"
        "     SUBEQ   R12, R4, #0x2000\n"
        "     SUBEQS  R12, R12, #0x1C\n"
        "     BNE     loc_FF877CCC\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF87847C\n"
        "     B         loc_FF877FF4\n"


    "loc_FF877CCC:\n"    // CODE XREF: sub_FF877C0C+B0j
        "     BL         sub_FF88E760\n"
        "     LDR     R6, =0x9A1\n"
        "     CMP     R0, #1\n"
        "     ADD     R7, R6, #2\n"
        "     BNE     loc_FF877CFC\n"
        "     CMP     R4, R10\n"
        "     CMPNE   R4, R6\n"
        "     CMPNE   R4, R7\n"
        "     BNE     loc_FF877CFC\n"
        "     BL         sub_FF88D8A4\n"
        "     STR     R4, [R5,#0x40]\n"
        "     B         loc_FF878090\n"


    "loc_FF877CFC:\n"    // CODE XREF: sub_FF877C0C+D0j

        "     BL         _GetAEIntegralServiceMode_7\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF877D1C\n"
        "     MOV     R0, R4\n"
        "     BL         sub_FF86AC20\n"
        "     CMP     R0, #1\n"
        "     CMPNE   R4, R10\n"
        "     BEQ     loc_FF878090\n"

    "loc_FF877D1C:\n"    // CODE XREF: sub_FF877C0C+F8j
        "     BL         sub_FF82CA7C\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF877D34\n"
        "     CMP     R4, R6\n"
        "     CMPNE   R4, R7\n"
        "     BEQ     loc_FF877FF4\n"

    "loc_FF877D34:\n"    // CODE XREF: sub_FF877C0C+118j
        "     BL         sub_FF8747A4\n"
        "     LDR     R1, =0x9A2\n"
        "     CMP     R0, #1\n"
        "     ADD     R2, R1, #2\n"
        "     BNE     loc_FF877D5C\n"
        "     CMP     R4, R6\n"
        "     CMPNE   R4, R1\n"
        "     CMPNE   R4, R7\n"
        "     CMPNE   R4, R2\n"
        "     BEQ     loc_FF877FF4\n"

    "loc_FF877D5C:\n"    // CODE XREF: sub_FF877C0C+138j
        "     SUB     R12, R4, #0x800\n"
        "     SUBS    R12, R12, #0x57\n"
        "     BNE     loc_FF877D84\n"
        "     LDR     R0, [R5,#0x10]\n"
        "     LDR     R1, [R5,#0x14]\n"
        "     ORR     R0, R0, R1\n"
        "     LDR     R1, [R5,#0x1C]\n"
        "     ORRS    R0, R0, R1\n"
        "     BLEQ    sub_FF98ECC8\n"
        "     B         loc_FF877FF4\n"


    "loc_FF877D84:\n"    // CODE XREF: sub_FF877C0C+158j
        "     LDR     R12, =0x9A5\n"
        "     MOV     R10, #1\n"
        "     CMP     R4, R12\n"
        "     BEQ     loc_FF878014\n"
        "     BGT     loc_FF877E3C\n"
        "     LDR     R12, =0x907\n"
        "     CMP     R4, R12\n"
        "     MOVEQ   R1, #2\n"
        "     BEQ     loc_FF87800C\n"
        "     BGT     loc_FF877E18\n"
        "     LDR     R12, =0x829\n"
        "     LDR     R6, =0x2003\n"
        "     CMP     R4, R12\n"
        "     BEQ     loc_FF877F80\n"
        "     BGT     loc_FF877DEC\n"
        "     CMP     R4, #0x800\n"
        "     BEQ     loc_FF877F10\n"
        "     SUB     R12, R4, #0x800\n"
        "     SUBS    R12, R12, #0x26\n"
        "     BNE     loc_FF8780A8\n"
        "     BL         sub_FF8747A4\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF877F54\n"
        "     MOV     R0, R4\n"
        "     BL         sub_FF874D74\n"
        "     B         loc_FF877FF4\n"


    "loc_FF877DEC:\n"    // CODE XREF: sub_FF877C0C+1B0j
        "     CMP     R4, #0x860\n"
        "     BEQ     loc_FF877FD0\n"
        "     SUB     R12, R4, #0x800\n"
        "     SUBS    R12, R12, #0x61\n"
        "     BNE     loc_FF8780A8\n"
        "     BL         sub_FF878590\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF878090\n"
        "     LDR     R0, =0x9A6\n"
        "     MOV     R1, R9\n"
        "     B         loc_FF87804C\n"


    "loc_FF877E18:\n"    // CODE XREF: sub_FF877C0C+19Cj
        "     CMP     R4, R6\n"
        "     BEQ     loc_FF878024\n"
        "     CMP     R4, R1\n"
        "     BEQ     loc_FF8780F4\n"
        "     CMP     R4, R7\n"
        "     BEQ     loc_FF878024\n"
        "     CMP     R4, R2\n"
        "     BEQ     loc_FF8780F4\n"
        "     B         loc_FF8780A8\n"


    "loc_FF877E3C:\n"    // CODE XREF: sub_FF877C0C+188j
        "     LDR     R12, =0x3149\n"
        "     CMP     R4, R12\n"
        "     MOVEQ   R1, #0\n"
        "     MOVEQ   R0, #0x84\n"
        "     BEQ     loc_FF8780A0\n"
        "     BGT     loc_FF877EA8\n"
        "     CMP     R4, R11\n"
        "     BEQ     loc_FF877F30\n"
        "     BGT     loc_FF877E84\n"
        "     SUB     R12, R4, #0x2000\n"
        "     SUBS    R12, R12, #0xA\n"
        "     BEQ     loc_FF8780F4\n"
        "     SUB     R12, R4, #0x2000\n"
        "     SUBS    R12, R12, #0x20\n"
        "     BNE     loc_FF8780A8\n"
        "     MOV     R1, R9\n"
        "     MOV     R0, #0x83\n"
        "     B         loc_FF8780A0\n"


    "loc_FF877E84:\n"    // CODE XREF: sub_FF877C0C+250j
        "     SUB     R12, R4, #0x3100\n"
        "     SUBS    R12, R12, #0x35\n"
        "     BEQ     loc_FF877EE4\n"
        "     SUB     R12, R4, #0x3000\n"
        "     SUBS    R12, R12, #0x148\n"
        "     BNE     loc_FF8780A8\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #0x86\n"
        "     B         loc_FF8780A0\n"


    "loc_FF877EA8:\n"    // CODE XREF: sub_FF877C0C+244j
        "     SUB     R12, R4, #0x3100\n"
        "     SUBS    R12, R12, #0x4A\n"
        "     BEQ     loc_FF878098\n"
        "     SUB     R12, R4, #0x4000\n"
        "     SUBS    R12, R12, #3\n"
        "     BEQ     loc_FF878054\n"
        "     SUB     R12, R4, #0x4000\n"
        "     SUBS    R12, R12, #8\n"
        "     BEQ     loc_FF878034\n"
        "     SUB     R12, R4, #0x4000\n"
        "     SUBS    R12, R12, #0xF\n"
        "     BNE     loc_FF8780A8\n"
        "     MOV     R0, #0x82\n"
        "     BL         sub_FF878FA8\n"
        "     B         loc_FF877FF4\n"


    "loc_FF877EE4:\n"    // CODE XREF: sub_FF877C0C+280j
        "     BL         _GetVRAMHPixelsSize_1\n"
        "     CMP     R0, #4\n"
        "     BEQ     loc_FF8780F4\n"
        "     LDR     R0, [R5,#0x1C]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF877FF4\n"
        "     LDR     R0, [R5,#0x48]\n"
        "     CMP     R0, #0\n"
        "     BLNE    sub_FF877A08\n"
        "     BL         sub_FF87795C\n"
        "     B         loc_FF877FF4\n"


    "loc_FF877F10:\n"    // CODE XREF: sub_FF877C0C+1B8j
        "     LDR     R0, [R5,#0x4C]\n"
        "     CMP     R9, R0\n"
        "     BNE     loc_FF878090\n"
        "     LDR     R1, =0xFF878124\n"    // aMvicon_clrevt = "MviCon_ClrEvt"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     STR     R8, [R5,#0x4C]\n"
        "     B         loc_FF878090\n"


    "loc_FF877F30:\n"    // CODE XREF: sub_FF877C0C+24Cj
        "     STR     R10, [R5,#0x1C]\n"
        "     LDR     R0, [R5,#0x18]\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF877F48\n"

    "loc_FF877F40:\n"    // CODE XREF: sub_FF877C0C+34j
        "     BL         sub_FF87795C\n"
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF877F48:\n"    // CODE XREF: sub_FF877C0C+330j
        "     MOV     R0, R4\n"
        "     BL         sub_FF877BD0\n"
        "     B         loc_FF877FF4\n"


    "loc_FF877F54:\n"    // CODE XREF: sub_FF877C0C+1D0j
        "     LDR     R0, [R5,#0x10]\n"
        "     LDR     R1, [R5,#0x14]\n"
        "     ORR     R0, R0, R1\n"
        "     LDR     R1, [R5,#0x1C]\n"
        "     ORRS    R0, R0, R1\n"
        "     BNE     loc_FF877FF4\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, R6\n"
        "     BL         sub_FF859588\n"
        "     BL         sub_FF980908\n"    // StartRecModeMenu
        "     B         loc_FF877FF4\n"


    "loc_FF877F80:\n"    // CODE XREF: sub_FF877C0C+1ACj
        "     LDR     R0, [R5,#0x10]\n"
        "     LDR     R1, [R5,#0x14]\n"
        "     ORRS    R0, R0, R1\n"
        "     BNE     loc_FF877FF4\n"
        "     BL         sub_FF874D80\n"
        "     CMP     R0, #0\n"
        "     LDREQ   R0, [R5,#0x1C]\n"
        "     CMPEQ   R0, #0\n"
        "     BNE     loc_FF877FF4\n"
        "     BL         sub_FF8747A4\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF877FF4\n"
        "     BL         _j_IsEvfDriveMode_16\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF877FF4\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, R6\n"
        "     BL         sub_FF859588\n"
        "     BL         sub_FF93F224\n"
        "     B         loc_FF877FF4\n"


    "loc_FF877FD0:\n"    // CODE XREF: sub_FF877C0C+1E4j
        "     BL         sub_FF878590\n"
        "     CMP     R0, #2\n"
        "     BEQ     loc_FF878090\n"
        "     BL         sub_FF878590\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF878090\n"
        "     LDR     R0, [R5,#0x4C]\n"
        "     CMN     R0, #1\n"
        "     BEQ     loc_FF877FFC\n"

    "loc_FF877FF4:\n"    // CODE XREF: sub_FF877C0C+90j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF877FFC:\n"    // CODE XREF: sub_FF877C0C+3E4j
        "     LDR     R0, [R5,#0x34]\n"
        "     CMP     R0, #0\n"
        "     STREQ   R10, [R5,#0x38]\n"

    "loc_FF878008:\n"    // CODE XREF: sub_FF877C0C+410j
        "     MOV     R1, #1\n"

    "loc_FF87800C:\n"    // CODE XREF: sub_FF877C0C+198j
        "     LDR     R0, =0x9A5\n"
        "     B         loc_FF87802C\n"


    "loc_FF878014:\n"    // CODE XREF: sub_FF877C0C+184j
        "     LDR     R0, [R5,#0x4C]\n"
        "     CMN     R0, #1\n"
        "     BEQ     loc_FF878008\n"
        "     B         loc_FF877FF4\n"


    "loc_FF878024:\n"    // CODE XREF: sub_FF877C0C+210j

        "     MOV     R1, #1\n"
        "     MOV     R0, R4\n"

    "loc_FF87802C:\n"    // CODE XREF: sub_FF877C0C+A0j

        "     BL         sub_FF877AA4_my\n"    //   --------------->
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF878034:\n"    // CODE XREF: sub_FF877C0C+2BCj
        "     MOV     R0, R9\n"
        "     BL         sub_FF8723D0\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF878090\n"
        "     MOV     R1, R9\n"
        "     MOV     R0, R4\n"

    "loc_FF87804C:\n"    // CODE XREF: sub_FF877C0C+208j
        "     BL         sub_FF878688_my\n"    //   --------------->
        "     B         loc_FF878090\n"


    "loc_FF878054:\n"    // CODE XREF: sub_FF877C0C+2B0j
        "     LDR     R0, [R5,#0x40]\n"
        "     CMN     R0, #1\n"
        "     BEQ     loc_FF878090\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF88A398\n"
        "     LDR     R0, [R5,#0x40]\n"
        "     CMP     R0, R6\n"
        "     BNE     loc_FF878080\n"
        "     BL         sub_FF82C964\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF87808C\n"

    "loc_FF878080:\n"    // CODE XREF: sub_FF877C0C+464j
        "     LDR     R0, [R5,#0x40]\n"
        "     MOV     R1, #0\n"
        "     BL         _PostLogicalEventForNotPowerType\n"

    "loc_FF87808C:\n"    // CODE XREF: sub_FF877C0C+470j
        "     STR     R8, [R5,#0x40]\n"

    "loc_FF878090:\n"    // CODE XREF: sub_FF877C0C+48j

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R3-R11,PC}\n"


    "loc_FF878098:\n"    // CODE XREF: sub_FF877C0C+2A4j
        "     MOV     R1, #0\n"
        "     MOV     R0, #0x85\n"

    "loc_FF8780A0:\n"    // CODE XREF: sub_FF877C0C+240j

        "     BL         sub_FF878F68\n"
        "     B         loc_FF877FF4\n"


    "loc_FF8780A8:\n"    // CODE XREF: sub_FF877C0C+1C4j

        "     LDR     R12, =0x855\n"
        "     CMP     R4, R12\n"
        "     BEQ     loc_FF8780E4\n"
        "     BGT     loc_FF8780D0\n"
        "     SUB     R12, R4, #0x800\n"
        "     SUBS    R12, R12, #0x38\n"
        "     SUBNE   R12, R4, #0x800\n"
        "     SUBNES  R12, R12, #0x39\n"
        "     BNE     loc_FF8780F4\n"
        "     B         loc_FF8780E4\n"


    "loc_FF8780D0:\n"    // CODE XREF: sub_FF877C0C+4A8j
        "     SUB     R12, R4, #0x800\n"
        "     SUBS    R12, R12, #0x56\n"
        "     SUBNE   R12, R4, #0x800\n"
        "     SUBNES  R12, R12, #0x5D\n"
        "     BNE     loc_FF8780F4\n"

    "loc_FF8780E4:\n"    // CODE XREF: sub_FF877C0C+4A4j

        "     LDR     R0, [R5,#0x10]\n"
        "     LDR     R1, [R5,#0x14]\n"
        "     ORRS    R0, R0, R1\n"
        "     BNE     loc_FF877FF4\n"

    "loc_FF8780F4:\n"    // CODE XREF: sub_FF877C0C+218j

        "     MOV     R1, R9\n"
        "     MOV     R0, R4\n"
        "     BL         sub_FF878688_my\n"    //   --------------->
        "     LDMFD   SP!, {R3-R11,PC}\n"
        ".LTORG\n" // make literal pool
    );
}

// Extracted method: sub_FF877AA4 (FF877AA4-FF877B6C)
// Overridden calls:
//     sub_FF878688
void __attribute__((naked,noinline)) sub_FF877AA4_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R6,LR}\n"
        "     MOV     R4, R0\n"
        "     LDR     R0, =0x61D8\n"
        "     MOV     R5, R1\n"
        "     LDR     R0, [R0,#0x1C]\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R1, =0xFF877BAC\n"    // aMvicon_fshtdwn = "MviCon_fShtDwn"
        "     BNE     loc_FF877B58\n"
        "     BL         sub_FF878A38\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF877AE0\n"

    "loc_FF877AD0:\n"    // CODE XREF: sub_FF877AA4+C8j
        "     MOV     R0, R4\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     MOV     R1, #0\n"
        "     B         sub_FF878688_my\n"    //   --------------->


    "loc_FF877AE0:\n"    // CODE XREF: sub_FF877AA4+28j
        "     CMP     R5, #2\n"
        "     BNE     loc_FF877AF8\n"
        "     BL         sub_FF878468\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF877B48\n"
        "     B         loc_FF877B14\n"


    "loc_FF877AF8:\n"    // CODE XREF: sub_FF877AA4+40j
        "     CMP     R5, #1\n"
        "     BNE     loc_FF877B48\n"
        "     LDR     R0, =0xA22\n"
        "     BL         sub_FF877388\n"
        "     BL         sub_FF877048\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF877B48\n"

    "loc_FF877B14:\n"    // CODE XREF: sub_FF877AA4+50j
        "     MOV     R0, #0\n"
        "     BL         sub_FF88A398\n"
        "     SUB     R12, R4, #0x900\n"
        "     SUBS    R12, R12, #0xA1\n"
        "     SUBNE   R12, R4, #0x900\n"
        "     SUBNES  R12, R12, #0xA3\n"
        "     SUBNE   R12, R4, #0x900\n"
        "     SUBNES  R12, R12, #0xA5\n"
        "     LDREQ   R0, =0xC507\n"
        "     MOVEQ   R1, #0\n"
        "     BLEQ    sub_FF859588\n"

    "loc_FF877B40:\n"    // CODE XREF: sub_FF877AA4+BCj
        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"


    "loc_FF877B48:\n"    // CODE XREF: sub_FF877AA4+4Cj

        "     BL         sub_FF877A34\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF877B64\n"
        "     LDR     R1, =0xFF877BBC\n"    // aMvicon_initchk = "MviCon_InitChkBuf"

    "loc_FF877B58:\n"    // CODE XREF: sub_FF877AA4+1Cj
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     B         loc_FF877B40\n"


    "loc_FF877B64:\n"    // CODE XREF: sub_FF877AA4+ACj
        "     MOV     R0, R5\n"
        "     BL         sub_FF949460\n"
        "     B         loc_FF877AD0\n"
    );
}

// Extracted method: sub_FF878138 (FF878138-FF8781AC)
// Overridden calls:
//     sub_FF877C0C
void __attribute__((naked,noinline)) sub_FF878138_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R4, =0x61D8\n"
        "     MOV     R1, #0\n"
        "     CMP     R0, #0\n"
        "     STR     R1, [R4,#0x30]\n"
        "     BEQ     loc_FF878160\n"
        "     BL         sub_FF871908\n"
        "     BL         sub_FF87841C\n"
        "     MOV     R0, #1\n"
        "     STR     R0, [R4,#0x48]\n"

    "loc_FF878160:\n"    // CODE XREF: sub_FF878138+14j
        "     LDR     R0, [R4,#8]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF87817C\n"
        "     LDR     R0, =sub_FF877C0C_my\n"    //   --------------->
        "     MOV     R1, #0\n"
        "     BL         _CreateController\n"
        "     STR     R0, [R4,#8]\n"

    "loc_FF87817C:\n"    // CODE XREF: sub_FF878138+30j
        "     LDR     R0, [R4,#0xC]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF878198\n"
        "     LDR     R0, =0xFF877860\n"    // sub_FF877860
        "     MOV     R1, #0\n"
        "     BL         sub_FF874B8C\n"
        "     STR     R0, [R4,#0xC]\n"

    "loc_FF878198:\n"    // CODE XREF: sub_FF878138+4Cj
        "     BL         sub_FF8789F8\n"
        "     BL         sub_FF8778C4\n"
        "     BL         sub_FF95352C\n"
        "     BL         sub_FF956D3C\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF94B4BC\n"
    );
}

// Extracted method: sub_FF875018 (FF875018-FF875040)
// Overridden calls:
//     sub_FF878138
//     sub_FF878138
void __attribute__((naked,noinline)) sub_FF875018_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF87517C\n"    // a_startmovie = "_StartMovie"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     LDR     R4, =0x6018\n"
        "     LDR     R0, [R4,#0x28]\n"
        "     CMP     R0, #0\n"
        "     BLNE    sub_FF875AB8\n"
        "     LDR     R0, [R4,#0x4C]\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF878138_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF8734F4 (FF8734F4-FF8736B0)
// Overridden calls:
//     sub_FF875018
void __attribute__((naked,noinline)) sub_FF8734F4_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R6,LR}\n"
        "     MOV     R5, R0\n"
        "     MOV     R4, R1\n"
        "     LDR     R1, =0xFF873710\n"    // a_decidecapture = "_DecideCaptureMode"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     LDR     R6, =0x6018\n"
        "     LDR     R0, [R6,#0x10]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF8736AC\n"
        "     LDR     R0, [R6,#0x18]\n"
        "     LDR     R1, =0x820A\n"
        "     LDR     R2, =0xFFFE0000\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF873574\n"
        "     CMP     R4, #1\n"
        "     LDMEQFD SP!, {R4-R6,PC}\n"
        "     CMP     R4, #0\n"
        "     BNE     loc_FF873574\n"
        "     CMP     R5, R1\n"
        "     BNE     loc_FF873554\n"
        "     BL         sub_FF875290\n"
        "     BL         sub_FF874F70\n"
        "     B         loc_FF8736AC\n"


    "loc_FF873554:\n"    // CODE XREF: sub_FF8734F4+50j
        "     CMP     R2, R5,LSL#17\n"
        "     TSTNE   R5, #0xC00\n"
        "     BEQ     loc_FF873568\n"
        "     BL         sub_FF875018_my\n"    //   --------------->
        "     B         loc_FF87356C\n"


    "loc_FF873568:\n"    // CODE XREF: sub_FF8734F4+68j
        "     BL         sub_FF874FCC\n"

    "loc_FF87356C:\n"    // CODE XREF: sub_FF8734F4+70j
        "     BL         sub_FF875290\n"
        "     B         loc_FF8736AC\n"


    "loc_FF873574:\n"    // CODE XREF: sub_FF8734F4+38j

        "     CMP     R5, R1\n"
        "     BNE     loc_FF8735C8\n"
        "     LDRH    R0, [R6,#2]\n"
        "     CMP     R0, R1\n"
        "     BEQ     loc_FF8736A4\n"
        "     CMP     R2, R0,LSL#17\n"
        "     TSTNE   R0, #0xC00\n"
        "     BEQ     loc_FF8735AC\n"
        "     LDR     R1, =0xFF873730\n"    // a_movietostitch = "_MovieToStitch"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BEQ     loc_FF87367C\n"
        "     B         loc_FF8735C0\n"


    "loc_FF8735AC:\n"    // CODE XREF: sub_FF8734F4+9Cj
        "     LDR     R1, =0xFF873740\n"    // a_stilltostitch = "_StillToStitch"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BEQ     loc_FF873698\n"

    "loc_FF8735C0:\n"    // CODE XREF: sub_FF8734F4+B4j
        "     BL         sub_FF874F70\n"
        "     B         loc_FF8736A4\n"


    "loc_FF8735C8:\n"    // CODE XREF: sub_FF8734F4+84j
        "     CMP     R2, R5,LSL#17\n"
        "     LDRH    R0, [R6,#2]\n"
        "     TSTNE   R5, #0xC00\n"
        "     BEQ     loc_FF873638\n"
        "     CMP     R0, R1\n"
        "     BNE     loc_FF8735F8\n"
        "     LDR     R1, =0xFF873750\n"    // a_stitchtomovie = "_StitchToMovie"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BEQ     loc_FF873654\n"
        "     B         loc_FF873630\n"


    "loc_FF8735F8:\n"    // CODE XREF: sub_FF8734F4+E8j
        "     CMP     R2, R0,LSL#17\n"
        "     TSTNE   R0, #0xC00\n"
        "     BEQ     loc_FF87361C\n"
        "     LDR     R1, =0xFF873760\n"    // a_movietomovie = "_MovieToMovie"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BEQ     loc_FF87367C\n"
        "     B         loc_FF873630\n"


    "loc_FF87361C:\n"    // CODE XREF: sub_FF8734F4+10Cj
        "     LDR     R1, =0xFF873770\n"    // a_stilltomovie = "_StillToMovie"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BEQ     loc_FF873698\n"

    "loc_FF873630:\n"    // CODE XREF: sub_FF8734F4+100j

        "     BL         sub_FF875018_my\n"    //   --------------->
        "     B         loc_FF8736A4\n"


    "loc_FF873638:\n"    // CODE XREF: sub_FF8734F4+E0j
        "     CMP     R0, R1\n"
        "     BNE     loc_FF87365C\n"
        "     LDR     R1, =0xFF873780\n"    // a_stitchtostill = "_StitchToStill"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BNE     loc_FF8736A0\n"

    "loc_FF873654:\n"    // CODE XREF: sub_FF8734F4+FCj
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF874FA0\n"


    "loc_FF87365C:\n"    // CODE XREF: sub_FF8734F4+148j
        "     CMP     R2, R0,LSL#17\n"
        "     TSTNE   R0, #0xC00\n"
        "     BEQ     loc_FF873684\n"
        "     LDR     R1, =0xFF873790\n"    // a_movietostill = "_MovieToStill"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BNE     loc_FF8736A0\n"

    "loc_FF87367C:\n"    // CODE XREF: sub_FF8734F4+B0j

        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF875044\n"


    "loc_FF873684:\n"    // CODE XREF: sub_FF8734F4+170j
        "     LDR     R1, =0xFF8737A0\n"    // a_stilltostill = "_StillToStill"
        "     MOV     R0, #0x60\n"
        "     BL         sub_FF867708\n"
        "     CMP     R4, #1\n"
        "     BNE     loc_FF8736A0\n"

    "loc_FF873698:\n"    // CODE XREF: sub_FF8734F4+C8j

        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF874FF4\n"


    "loc_FF8736A0:\n"    // CODE XREF: sub_FF8734F4+15Cj

        "     BL         sub_FF874FCC\n"

    "loc_FF8736A4:\n"    // CODE XREF: sub_FF8734F4+90j

        "     CMP     R4, #0\n"
        "     LDMNEFD SP!, {R4-R6,PC}\n"

    "loc_FF8736AC:\n"    // CODE XREF: sub_FF8734F4+24j

        "     STRH    R5, [R6,#2]\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"
    );
}

// Extracted method: sub_FF874884 (FF874884-FF8749BC)
// Overridden calls:
//     sub_FF8734F4
void __attribute__((naked,noinline)) sub_FF874884_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R6,LR}\n"
        "     LDR     R5, =0x6018\n"
        "     MOV     R4, #0\n"
        "     LDRH    R0, [R5,#4]\n"
        "     BL         sub_FF94BDD4\n"
        "     BL         sub_FF94A5E8\n"
        "     BL         sub_FF94CBAC\n"
        "     BL         sub_FF952C54\n"
        "     BL         _nullsub_96\n"
        "     BL         sub_FF94C2C4\n"
        "     LDR     R0, [R5,#0x4C]\n"
        "     MOV     R1, #3\n"
        "     CMP     R0, #0\n"
        "     STRNE   R1, [R5,#0x70]\n"
        "     LDR     R2, [R5,#0x60]\n"
        "     SUB     R12, R2, #0x1000\n"
        "     SUBS    R12, R12, #0x5B\n"
        "     CMPNE   R0, #0\n"
        "     LDR     R0, [R5,#0x58]\n"
        "     MOVNE   R4, #2\n"
        "     CMP     R2, R0\n"
        "     BNE     loc_FF8748EC\n"
        "     LDR     R0, [R5,#0x50]\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R4, #3\n"
        "     STRNE   R1, [R5,#0x70]\n"

    "loc_FF8748EC:\n"    // CODE XREF: sub_FF874884+54j
        "     MOV     R6, #0\n"
        "     STR     R6, [R5,#0x24]\n"
        "     BL         sub_FF875100\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R0, R4\n"
        "     BLNE    sub_FF826844\n"
        "     BL         sub_FF940CAC\n"
        "     STR     R6, [R5,#0x3C]\n"
        "     LDRH    R0, [R5,#4]\n"
        "     MOV     R1, #0\n"
        "     BL         sub_FF8734F4_my\n"    //   --------------->
        "     BL         sub_FF877030\n"
        "     LDR     R0, [R5,#0x74]\n"
        "     CMP     R0, #0\n"
        "     STRNE   R6, [R5,#0x74]\n"
        "     BLNE    sub_FF874F2C\n"
        "     LDR     R1, [R5,#0x70]\n"
        "     MOV     R0, #0x41\n"
        "     BL         sub_FF878F68\n"
        "     BL         sub_FF874F2C\n"
        "     BL         sub_FF94A5D8\n"
        "     BL         sub_FF9452C0\n"
        "     CMP     R0, #0\n"
        "     BLEQ    sub_FF94A5EC\n"
        "     BL         sub_FF94BD3C\n"
        "     BL         sub_FF93E3F0\n"
        "     BL         sub_FF86A470\n"
        "     STR     R0, [R5,#0x6C]\n"
        "     STR     R6, [R5,#0x2C]\n"
        "     LDR     R0, [R5,#0x50]\n"
        "     MOV     R4, R5\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF874988\n"
        "     LDR     R0, [R4,#0x10]\n"
        "     MOV     R1, R4\n"
        "     CMP     R0, #0\n"
        "     MOVEQ  R0, #0xFFFFFFFF\n"
        "     STREQ   R0, [R1,#0x58]\n"
        "     STREQ   R0, [R1,#0x60]\n"

    "loc_FF874988:\n"    // CODE XREF: sub_FF874884+E8j
        "     LDR     R0, =0x8003\n"
        "     STR     R6, [R4,#0x50]\n"
        "     BL         _PTM_GetCurrentItem\n"
        "     STRH    R0, [R4]\n"
        "     LDR     R0, =0x313D\n"
        "     MOV     R1, #0\n"
        "     BL         _PostLogicalEventToUI\n"    // "DryOS Canon Firmware; A720-based"
        "     BL         sub_FF87520C\n"
        "     LDR     R0, [R4,#0x30]\n"
        "     CMP     R0, #1\n"
        "     STREQ   R6, [R4,#0x30]\n"
        "     LDMEQFD SP!, {R4-R6,LR}\n"
        "     BEQ     sub_FF87400C\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"
    );
}

// Extracted method: sub_FF875074 (FF875074-FF8750FC)
// Overridden calls:
//     sub_FF8734F4
void __attribute__((naked,noinline)) sub_FF875074_my() {
    asm volatile (

    "var_10         = -0x10\n"
    "var_E         = -0xE\n"

        "     STMFD   SP!, {R3-R5,LR}\n"
        "     LDR     R4, =0x6018\n"
        "     LDR     R0, [R4,#0x4C]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF8750A4\n"
        "     LDR     R0, [R4,#0x60]\n"
        "     LDR     R1, [R4,#0x58]\n"
        "     CMP     R0, R1\n"
        "     BNE     loc_FF8750AC\n"
        "     LDR     R0, [R4,#0x50]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF8750AC\n"

    "loc_FF8750A4:\n"    // CODE XREF: sub_FF875074+10j
        "     MOV     R0, #3\n"
        "     STR     R0, [R4,#0x70]\n"

    "loc_FF8750AC:\n"    // CODE XREF: sub_FF875074+20j

        "     LDRH    R0, [R4,#4]\n"
        "     MOV     R1, SP\n"
        "     STRH    R0, [SP,#0x10+var_10]\n"
        "     LDR     R0, [R4,#0x70]\n"
        "     STRH    R0, [SP,#0x10+var_E]\n"
        "     MOV     R0, #0x40\n"
        "     BL         sub_FF878F68\n"
        "     LDR     R0, [R4,#0x4C]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF8750E0\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF945CA4\n"
        "     B         loc_FF8750F0\n"


    "loc_FF8750E0:\n"    // CODE XREF: sub_FF875074+5Cj
        "     LDR     R0, [R4,#0x1C]\n"
        "     CMP     R0, #0\n"
        "     LDREQH  R0, [R4,#4]\n"
        "     BLEQ    _PTM_SetCurrentCaptureMode\n"

    "loc_FF8750F0:\n"    // CODE XREF: sub_FF875074+68j
        "     LDRH    R0, [R4,#4]\n"
        "     MOV     R1, #1\n"
        "     BL         sub_FF8734F4_my\n"    //   --------------->
        "     LDMFD   SP!, {R3-R5,PC}\n"
    );
}

// Extracted method: sub_FF8749E8 (FF8749E8-FF874A04)
// Overridden calls:
//     sub_FF8747B0
//     sub_FF874884
void __attribute__((naked,noinline)) sub_FF8749E8_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R0, =0x60A4\n"
        "     ADR     R1, sub_FF8747B0_my\n"    //   --------------->
        "     BL         sub_FF87A61C\n"
        "     LDR     R1, =0x6018\n"
        "     ADR     R0, sub_FF874884_my\n"    //   --------------->
        "     STR     R0, [R1,#0x80]\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}

// Extracted method: sub_FF8747B0 (FF8747B0-FF874880)
// Overridden calls:
//     sub_FF875074
void __attribute__((naked,noinline)) sub_FF8747B0_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R6,LR}\n"
        "     LDR     R5, =0x6018\n"
        "     MOV     R4, #0\n"
        "     LDR     R0, [R5,#0x60]\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x5B\n"
        "     LDRNE   R1, [R5,#0x4C]\n"
        "     CMPNE   R1, #0\n"
        "     LDR     R1, [R5,#0x58]\n"
        "     MOVNE   R4, #2\n"
        "     CMP     R0, R1\n"
        "     BNE     loc_FF8747EC\n"
        "     LDR     R0, [R5,#0x50]\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R4, #3\n"

    "loc_FF8747EC:\n"    // CODE XREF: sub_FF8747B0+2Cj
        "     BL         sub_FF875100\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF874810\n"
        "     CMP     R4, #0\n"
        "     BNE     loc_FF874810\n"
        "     LDR     R0, [R5,#0x3C]\n"
        "     CMP     R0, #0\n"
        "     BLEQ    sub_FF93E580\n"
        "     BL         sub_FF9560A0\n"

    "loc_FF874810:\n"    // CODE XREF: sub_FF8747B0+44j

        "     LDR     R0, [R5,#0x30]\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF87483C\n"
        "     LDR     R1, =0xFF874A0C\n"    // a__preparecaptu = "__PrepareCaptureModeChange__"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R5,#0x30]\n"
        "     STR     R0, [R5,#0x2C]\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF87400C\n"


    "loc_FF87483C:\n"    // CODE XREF: sub_FF8747B0+68j
        "     BL         sub_FF875100\n"
        "     CMP     R0, #0\n"
        "     BLNE    sub_FF82675C\n"
        "     LDR     R0, [R5,#0x50]\n"
        "     CMP     R0, #0\n"
        "     MOVNE   R0, #1\n"
        "     BLNE    sub_FF945CA4\n"
        "     BL         sub_FF875074_my\n"    //   --------------->
        "     BL         sub_FF875100\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, [R5,#0x7C]\n"
        "     BLNE    sub_FF875354\n"
        "     MOV     R0, #3\n"
        "     STR     R0, [R5,#0x7C]\n"
        "     LDR     R1, [R5,#0x80]\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     MOV     R0, #0\n"
        "     BX         R1\n"
    );
}

// Extracted method: sub_FF874A48 (FF874A48-FF874A68)
// Overridden calls:
//     sub_FF8749E8
//     sub_FF8749E8
void __attribute__((naked,noinline)) sub_FF874A48_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF874C7C\n"    // a_aftercbrforpl = "_AfterCBRForPlay"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF86A470\n"
        "     LDR     R1, =0x6018\n"
        "     STR     R0, [R1,#0x6C]\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF8749E8_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF875294 (FF875294-FF8752E0)
// Overridden calls:
//     sub_FF8749E8
void __attribute__((naked,noinline)) sub_FF875294_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R0, =0x855\n"
        "     BL         sub_FF86C590\n"
        "     BL         sub_FF82BE70\n"
        "     BL         sub_FF8749E8_my\n"    //   --------------->
        "     BL         sub_FF944944\n"
        "     BL         sub_FF93F8DC\n"
        "     BL         sub_FF94C554\n"
        "     BL         sub_FF94C93C\n"
        "     BL         sub_FF952B88\n"
        "     BL         sub_FF9563E4\n"
        "     BL         sub_FF94CB2C\n"
        "     BL         sub_FF94C73C\n"
        "     BL         sub_FF954AFC\n"
        "     BL         sub_FF94C184\n"
        "     BL         sub_FF9527FC\n"
        "     BL         sub_FF9546C8\n"
        "     BL         _taskcreate_DSITask\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         _taskcreate_FaceFrame\n"
    );
}

// Extracted method: sub_FF874AFC (FF874AFC-FF874B40)
// Overridden calls:
//     sub_FF874A48
void __attribute__((naked,noinline)) sub_FF874AFC_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R4, =0x6018\n"
        "     LDRH    R0, [R4,#4]\n"
        "     BL         _PTM_SetCurrentCaptureMode\n"
        "     BL         _GetAEIntegralServiceMode_0\n"
        "     SUB     R12, R0, #0x4000\n"
        "     SUBS    R12, R12, #4\n"
        "     LDMNEFD SP!, {R4,PC}\n"
        "     LDR     R0, =0x60A4\n"
        "     LDR     R1, =0xFF8749C0\n"    // sub_FF8749C0
        "     BL         sub_FF87A61C\n"
        "     ADR     R0, sub_FF874A48_my\n"    //   --------------->
        "     STR     R0, [R4,#0x80]\n"
        "     BL         _nullsub_37\n"
        "     LDR     R1, =0x60B0\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     SUB     R0, R1, #0xC\n"
        "     B         sub_FF87A5C8\n"
    );
}

// Extracted method: sub_FF874C1C (FF874C1C-FF874C78)
// Overridden calls:
//     sub_FF875294
void __attribute__((naked,noinline)) sub_FF874C1C_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R6,LR}\n"
        "     LDR     R1, =0xFF874CD0\n"    // aStartrecmode = "StartRecMode"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     LDR     R4, =0x6018\n"
        "     MOV     R0, #6\n"
        "     MOV     R5, #1\n"
        "     STR     R0, [R4,#0x70]\n"
        "     STR     R5, [R4,#0x10]\n"
        "     BL         sub_FF94514C\n"
        "     BL         sub_FF94BB7C\n"
        "     BL         sub_FF94A428\n"
        "     BL         sub_FF875294_my\n"    //   --------------->
        "     BL         sub_FF954EDC\n"
        "     BL         sub_FF952F94\n"
        "     MOV     R0, #1\n"
        "     STR     R5, [R4,#0x18]\n"
        "     BL         sub_FF875354\n"
        "     MOV     R0, #3\n"
        "     STR     R0, [R4,#0x7C]\n"
        "     LDR     R1, [R4,#0x80]\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     MOV     R0, #0\n"
        "     BX         R1\n"
    );
}

// Extracted method: sub_FF82BE84 (FF82BE84-FF82BF24)
// Overridden calls:
//     sub_FF874AFC
void __attribute__((naked,noinline)) sub_FF82BE84_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R6,LR}\n"
        "     MOV     R4, R0\n"
        "     LDR     R0, =0x1DD0\n"
        "     MOV     R5, R4,LSL#16\n"
        "     MOV     R5, R5,LSR#16\n"
        "     STR     R4, [R0,#0xC]\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF86D4F8\n"
        "     CMP     R4, #0x80\n"
        "     MOVNE   R1, R4\n"
        "     MOVNE   R0, #0\n"
        "     BLNE    sub_FF872404\n"
        "     LDR     R12, =0x4010\n"
        "     CMP     R4, R12\n"
        "     BEQ     loc_FF82BF08\n"
        "     BGT     loc_FF82BEE0\n"
        "     CMP     R4, #8\n"
        "     BEQ     loc_FF82BEFC\n"
        "     CMP     R4, #0x80\n"
        "     SUBNE   R12, R4, #0x4000\n"
        "     SUBNES  R12, R12, #4\n"
        "     BEQ     loc_FF82BF08\n"
        "     B         loc_FF82BF00\n"


    "loc_FF82BEE0:\n"    // CODE XREF: sub_FF82BE84+3Cj
        "     SUB     R12, R4, #0x4000\n"
        "     SUBS    R12, R12, #0x40\n"
        "     CMPNE   R4, #0x4100\n"
        "     BEQ     loc_FF82BF08\n"
        "     SUB     R12, R4, #0x8000\n"
        "     SUBS    R12, R12, #0x20\n"
        "     BNE     loc_FF82BF00\n"

    "loc_FF82BEFC:\n"    // CODE XREF: sub_FF82BE84+44j
        "     BL         sub_FF874AFC_my\n"    //   --------------->

    "loc_FF82BF00:\n"    // CODE XREF: sub_FF82BE84+58j

        "     MOV     R0, #2\n"
        "     B         loc_FF82BF10\n"


    "loc_FF82BF08:\n"    // CODE XREF: sub_FF82BE84+38j

        "     BL         sub_FF874AFC_my\n"    //   --------------->
        "     MOV     R0, #0\n"

    "loc_FF82BF10:\n"    // CODE XREF: sub_FF82BE84+80j
        "     BL         sub_FF821F08\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF88F300\n"
        "     BL         _taskcreate_TempCheck\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF872190\n"
        ".LTORG\n" // make literal pool
    );
}

// Extracted method: sub_FF870400 (FF870400-FF87042C)
// Overridden calls:
//     sub_FF86EE0C
//     sub_FF874C1C
//     sub_FF86EE0C
void __attribute__((naked,noinline)) sub_FF870400_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF87063C\n"    // aAcEntryrecboot = "AC:EntryRecBoot"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF82C090\n"
        "     BL         sub_FF86FF90\n"
        "     BL         sub_FF874C1C_my\n"    //   --------------->
        "     MOV     R0, #1\n"
        "     BL         sub_FF86E64C\n"
        "     BL         sub_FF86EB38\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF86EE0C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF86F89C (FF86F89C-FF86F9F4)
// Overridden calls:
//     sub_FF82BE84
//     sub_FF870378
//     sub_FF870400
//     sub_FF870378
void __attribute__((naked,noinline)) sub_FF86F89C_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R6,LR}\n"
        "     SUB     R12, R0, #0x2000\n"
        "     LDR     R5, =0x5D50\n"
        "     SUBS    R12, R12, #4\n"
        "     MOV     R4, #1\n"
        "     BEQ     loc_FF86F8C8\n"
        "     SUB     R12, R0, #0x3200\n"
        "     SUBS    R12, R12, #2\n"
        "     MOVNE   R0, #1\n"
        "     LDMNEFD SP!, {R4-R6,PC}\n"
        "     STR     R4, [R5,#0xA4]\n"

    "loc_FF86F8C8:\n"    // CODE XREF: sub_FF86F89C+14j
        "     LDR     R0, [R5,#0x2C]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F9F0\n"
        "     LDR     R0, [R5,#0xA4]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86F9F0\n"
        "     BL         sub_FF86ECF0\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86F930\n"
        "     LDR     R0, [R5,#0xA8]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F930\n"
        "     LDR     R0, [R5,#0x1C]\n"
        "     LDR     R1, [R5,#0x20]\n"
        "     ORRS    R0, R0, R1\n"
        "     BEQ     loc_FF86F910\n"
        "     BL         sub_FF86EBB4\n"
        "     B         loc_FF86F914\n"


    "loc_FF86F910:\n"    // CODE XREF: sub_FF86F89C+68j
        "     BL         sub_FF86E2D0\n"

    "loc_FF86F914:\n"    // CODE XREF: sub_FF86F89C+70j
        "     LDR     R0, [R5,#0x34]\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, [R5,#0x30]\n"
        "     CMPNE   R0, #0\n"
        "     STREQ   R4, [R5,#0xA8]\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF870378_my\n"    //   --------------->


    "loc_FF86F930:\n"    // CODE XREF: sub_FF86F89C+4Cj

        "     LDR     R1, [R5,#0x24]\n"
        "     MOV     R6, R5\n"
        "     MOV     R0, #0\n"
        "     LDR     R5, =0x8002\n"
        "     CMP     R1, #0\n"
        "     STR     R0, [R6,#0xA4]\n"
        "     BEQ     loc_FF86F984\n"
        "     LDR     R1, =0xFF86FC24\n"    // a_entrytorec = "_EntryToRec"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     BL         _unknown_libname_80\n"    // "DryOS Canon Firmware; A720-based"
        "     BL         sub_FF870178\n"
        "     BL         sub_FF8261C4\n"
        "     BL         sub_FF877030\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #0x48\n"
        "     BL         sub_FF878F68\n"
        "     BL         sub_FF870400_my\n"    //   --------------->
        "     B         loc_FF86F9F0\n"


    "loc_FF86F984:\n"    // CODE XREF: sub_FF86F89C+ACj
        "     LDR     R1, =0xFF86FC30\n"    // a_entrytoprepar = "_EntryToPrepareLens"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     MOV     R0, #0xA\n"
        "     BL         sub_FF86E64C\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     BL         _unknown_libname_80\n"    // "DryOS Canon Firmware; A720-based"
        "     LDR     R1, =0xFF86FC44\n"    // aAcPreparelens = "AC:PrepareLens"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF870178\n"
        "     BL         sub_FF870BF4\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F9C8\n"
        "     BL         sub_FF8701C8\n"
        "     B         loc_FF86F9F0\n"


    "loc_FF86F9C8:\n"    // CODE XREF: sub_FF86F89C+120j
        "     BL         sub_FF8261C4\n"
        "     BL         sub_FF82BFFC\n"
        "     MOV     R0, #0\n"
        "     STR     R4, [R6,#0x28]\n"
        "     BL         sub_FF825CD0\n"
        "     BL         sub_FF825ED4\n"
        "     BL         sub_FF82CA3C\n"
        "     MOV     R0, R5\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     BL         sub_FF870DB0\n"

    "loc_FF86F9F0:\n"    // CODE XREF: sub_FF86F89C+34j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"
    );
}

// Extracted method: sub_FF86F9F8 (FF86F9F8-FF86FAFC)
// Overridden calls:
//     sub_FF82BE84
//     sub_FF86EDAC
//     sub_FF870430
void __attribute__((naked,noinline)) sub_FF86F9F8_my() {
    asm volatile (

        "     LDR     R12, =0x1162\n"
        "     STMFD   SP!, {R4,LR}\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86FAF0\n"
        "     BGT     loc_FF86FA54\n"
        "     LDR     R12, =0x10A9\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86FA48\n"
        "     BGT     loc_FF86FA34\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #5\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #8\n"
        "     BNE     loc_FF86FA98\n"
        "     B         loc_FF86FA4C\n"


    "loc_FF86FA34:\n"    // CODE XREF: sub_FF86F9F8+20j
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0xAD\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #0xAF\n"
        "     BNE     loc_FF86FA98\n"

    "loc_FF86FA48:\n"    // CODE XREF: sub_FF86F9F8+1Cj
        "     BL         sub_FF86EBB4\n"

    "loc_FF86FA4C:\n"    // CODE XREF: sub_FF86F9F8+38j

        "     BL         sub_FF86EDAC_my\n"    //   --------------->
        "     B         loc_FF86FAF8\n"


    "loc_FF86FA54:\n"    // CODE XREF: sub_FF86F9F8+10j
        "     LDR     R12, =0x119B\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86FAC8\n"
        "     BGT     loc_FF86FA80\n"
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x82\n"
        "     BEQ     loc_FF86FAC8\n"
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x85\n"
        "     BNE     loc_FF86FA98\n"
        "     B         loc_FF86FAA0\n"


    "loc_FF86FA80:\n"    // CODE XREF: sub_FF86F9F8+68j
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0xAB\n"
        "     BEQ     loc_FF86FAA0\n"
        "     SUB     R12, R0, #0x1200\n"
        "     SUBS    R12, R12, #3\n"
        "     BEQ     loc_FF86FAF8\n"

    "loc_FF86FA98:\n"    // CODE XREF: sub_FF86F9F8+34j

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4,PC}\n"


    "loc_FF86FAA0:\n"    // CODE XREF: sub_FF86F9F8+84j

        "     BL         sub_FF871A10\n"
        "     BL         sub_FF871A44\n"
        "     MOV     R0, #0x4100\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     BL         sub_FF989F3C\n"
        "     MOV     R0, #0x16\n"
        "     BL         sub_FF86E64C\n"
        "     MOV     R0, #1\n"
        "     BL         sub_FF872CA8\n"
        "     B         loc_FF86FAF8\n"


    "loc_FF86FAC8:\n"    // CODE XREF: sub_FF86F9F8+64j

        "     LDR     R0, =0x5D50\n"
        "     LDR     R0, [R0,#0x58]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86FAE0\n"
        "     BL         _nullsub_35\n"
        "     B         loc_FF86FA4C\n"


    "loc_FF86FAE0:\n"    // CODE XREF: sub_FF86F9F8+DCj
        "     BL         sub_FF871A10\n"
        "     BL         sub_FF871A44\n"
        "     BL         sub_FF870430_my\n"    //   --------------->
        "     B         loc_FF86FAF8\n"


    "loc_FF86FAF0:\n"    // CODE XREF: sub_FF86F9F8+Cj
        "     BL         _nullsub_35\n"
        "     BL         sub_FF86E44C\n"

    "loc_FF86FAF8:\n"    // CODE XREF: sub_FF86F9F8+58j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}


// Extracted method: sub_FF870430 (FF870430-FF870464)
// Overridden calls:
//     sub_FF82BE84
void __attribute__((naked,noinline)) sub_FF870430_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF87064C\n"    // aAcInitpb = "AC:InitPB"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF870DE0\n"
        "     LDR     R0, =0x4004\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     MOV     R0, #0xB\n"
        "     BL         sub_FF86E64C\n"
        "     BL         _unknown_libname_80\n"    // "DryOS Canon Firmware; A720-based"
        "     BL         sub_FF8261F8\n"
        "     BL         sub_FF870774\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF82BFBC\n"
    );
}

// Extracted method: sub_FF870694 (FF870694-FF870770)
// Overridden calls:
//     sub_FF82BE84
//     sub_FF82C130
void __attribute__((naked,noinline)) sub_FF870694_my() {
    asm volatile (
        "     SUB     R12, R0, #0x1000\n"
        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R4, =0x5D50\n"
        "     SUBS    R12, R12, #3\n"
        "     BEQ     loc_FF870760\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x184\n"
        "     BEQ     loc_FF870704\n"
        "     SUB     R12, R0, #0x3300\n"
        "     SUBS    R12, R12, #2\n"
        "     MOVNE   R0, #1\n"
        "     LDMNEFD SP!, {R4,PC}\n"
        "     BL         sub_FF98BF5C\n"
        "     LDR     R0, =0x4004\n"
        "     BL         sub_FF82BE84_my\n"    //   --------------->
        "     MOV     R0, #2\n"
        "     BL         sub_FF86E64C\n"
        "     LDR     R1, =0xFF87079C\n"    // aAcChecktermcom = "AC:CheckTermCom2PB"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF86ECF0\n"
        "     CMP     R0, #0\n"
        "     LDR     R0, [R4,#0x24]\n"
        "     BNE     loc_FF870710\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF870718\n"
        "     BL         sub_FF8710FC\n"
        "     B         loc_FF87076C\n"


    "loc_FF870704:\n"    // CODE XREF: sub_FF870694+1Cj
        "     MOV     R0, #1\n"
        "     BL         sub_FF8E2418\n"
        "     B         loc_FF87076C\n"


    "loc_FF870710:\n"    // CODE XREF: sub_FF870694+5Cj
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF87073C\n"

    "loc_FF870718:\n"    // CODE XREF: sub_FF870694+64j
        "     BL         sub_FF86ECF0\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF87073C\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R4,#0x50]\n"
        "     MOV     R0, #1\n"
        "     STR     R0, [R4,#0x54]\n"
        "     BL         sub_FF870204\n"
        "     B         loc_FF87076C\n"


    "loc_FF87073C:\n"    // CODE XREF: sub_FF870694+80j

        "     LDR     R0, [R4,#0x1C]\n"
        "     LDR     R1, [R4,#0x20]\n"
        "     ORRS    R0, R0, R1\n"
        "     BEQ     loc_FF870754\n"
        "     BL         sub_FF86EBB4\n"
        "     B         loc_FF870758\n"


    "loc_FF870754:\n"    // CODE XREF: sub_FF870694+B4j
        "     BL         sub_FF86E2D0\n"

    "loc_FF870758:\n"    // CODE XREF: sub_FF870694+BCj
        "     BL         sub_FF870244\n"
        "     B         loc_FF87076C\n"


    "loc_FF870760:\n"    // CODE XREF: sub_FF870694+10j
        "     LDR     R0, [R4,#0x24]\n"
        "     CMP     R0, #0\n"
        "     BLNE    sub_FF82C130_my\n"    //   --------------->

    "loc_FF87076C:\n"    // CODE XREF: sub_FF870694+6Cj

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}

// Extracted method: sub_FF86F498 (FF86F498-FF86F5E4)
// Overridden calls:
//     sub_FF86EDAC
//     sub_FF870400
void __attribute__((naked,noinline)) sub_FF86F498_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R6,LR}\n"
        "     BL         sub_FF8702AC\n"
        "     CMP     R0, #1\n"
        "     BLEQ    sub_FF8703BC\n"
        "     LDR     R4, =0x5D50\n"
        "     MOV     R5, #1\n"
        "     LDR     R0, [R4,#0x24]\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, [R4,#0x4C]\n"
        "     CMPNE   R0, #0\n"
        "     BEQ     loc_FF86F504\n"
        "     BL         sub_FF8702AC\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF86F504\n"
        "     BL         sub_FF8703BC\n"
        "     LDR     R0, [R4,#0x78]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F504\n"
        "     LDR     R1, =0xFF86F6C8\n"    // aAcStartupshowi = "AC:StartupShowInfo"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF99E698\n"
        "     BL         sub_FF99E624\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #0x51\n"
        "     BL         sub_FF878F68\n"
        "     STR     R5, [R4,#0x78]\n"

    "loc_FF86F504:\n"    // CODE XREF: sub_FF86F498+28j

        "     BL         sub_FF8702AC\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF86F550\n"
        "     LDR     R0, [R4,#0x44]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86F550\n"
        "     LDR     R0, [R4,#0x74]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F550\n"
        "     LDR     R1, =0xFF86F6DC\n"    // aAcDispshot = "AC:DispShot"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #0x8C\n"
        "     BL         sub_FF878F68\n"
        "     BL         sub_FF877030\n"
        "     MOV     R0, #0x21\n"
        "     BL         sub_FF878FA8\n"
        "     STR     R5, [R4,#0x74]\n"

    "loc_FF86F550:\n"    // CODE XREF: sub_FF86F498+74j

        "     LDR     R0, [R4,#0x38]\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, [R4,#0x3C]\n"
        "     CMPNE   R0, #0\n"
        "     LDRNE   R0, [R4,#0x44]\n"
        "     CMPNE   R0, #0\n"
        "     LDRNE   R0, [R4,#0x48]\n"
        "     CMPNE   R0, #0\n"
        "     LDRNE   R0, [R4,#0x1C]\n"
        "     LDRNE   R1, [R4,#0x20]\n"
        "     ORRNES  R0, R0, R1\n"
        "     BEQ     loc_FF86F58C\n"
        "     BL         sub_FF86EBB4\n"
        "     BL         sub_FF86EDAC_my\n"    //   --------------->
        "     B         loc_FF86F5B0\n"


    "loc_FF86F58C:\n"    // CODE XREF: sub_FF86F498+E4j
        "     LDR     R0, [R4,#0x58]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86F5B8\n"
        "     BL         sub_FF86EC58\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF86F5B8\n"
        "     BL         sub_FF871AB0\n"
        "     BL         sub_FF871A6C\n"
        "     BL         sub_FF870198\n"

    "loc_FF86F5B0:\n"    // CODE XREF: sub_FF86F498+F0j
        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"


    "loc_FF86F5B8:\n"    // CODE XREF: sub_FF86F498+FCj

        "     BL         sub_FF86EC58\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF86F5E0\n"
        "     LDR     R0, [R4,#0x7C]\n"
        "     CMP     R0, #0\n"
        "     BLEQ    sub_FF870400_my\n"    //   --------------->
        "     MOV     R0, #0\n"
        "     STR     R0, [R4,#0x70]\n"
        "     STR     R0, [R4,#0x74]\n"
        "     STR     R0, [R4,#0x78]\n"

    "loc_FF86F5E0:\n"    // CODE XREF: sub_FF86F498+128j
        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"
    );
}

// Extracted method: sub_FF86F6F0 (FF86F6F0-FF86F898)
// Overridden calls:
//     sub_FF86F224
void __attribute__((naked,noinline)) sub_FF86F6F0_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R8,LR}\n"
        "     LDR     R6, =0x1003\n"
        "     LDR     R7, =0x9A5\n"
        "     ADD     R12, R6, #0x5F\n"
        "     LDR     R4, =0x5D50\n"
        "     CMP     R0, R12\n"
        "     SUB     R8, R7, #4\n"
        "     BEQ     loc_FF86F82C\n"
        "     BGT     loc_FF86F764\n"
        "     LDR     R12, =0x1005\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F874\n"
        "     BGT     loc_FF86F740\n"
        "     CMP     R0, R8\n"
        "     CMPNE   R0, R7\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #1\n"
        "     CMPNE   R0, R6\n"
        "     BNE     loc_FF86F894\n"
        "     B         loc_FF86F82C\n"


    "loc_FF86F740:\n"    // CODE XREF: sub_FF86F6F0+30j
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #8\n"
        "     BEQ     loc_FF86F874\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x5B\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #0x61\n"
        "     BNE     loc_FF86F894\n"
        "     B         loc_FF86F82C\n"


    "loc_FF86F764:\n"    // CODE XREF: sub_FF86F6F0+20j
        "     LDR     R5, =0x10A5\n"
        "     ORR     R12, R5, R5,ASR#9\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F870\n"
        "     BGT     loc_FF86F798\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x65\n"
        "     CMPNE   R0, R5\n"
        "     BEQ     loc_FF86F82C\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0xA9\n"
        "     BNE     loc_FF86F894\n"
        "     B         loc_FF86F870\n"


    "loc_FF86F798:\n"    // CODE XREF: sub_FF86F6F0+84j
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0xAF\n"
        "     BEQ     loc_FF86F870\n"
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x62\n"
        "     BEQ     loc_FF86F874\n"
        "     SUB     R12, R0, #0x3000\n"
        "     SUBS    R12, R12, #0xC\n"
        "     BNE     loc_FF86F894\n"
        "     LDR     R0, [R4,#0x98]\n"
        "     CMP     R0, #1\n"
        "     MOVEQ   R1, #0\n"
        "     MOVEQ   R0, #2\n"
        "     BEQ     loc_FF86F838\n"
        "     BL         sub_FF82CAA0\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F820\n"
        "     LDR     R1, [R4,#0x9C]\n"
        "     MOV     R0, R5\n"
        "     CMP     R1, R5\n"
        "     BEQ     loc_FF86F820\n"
        "     BL         _IsControlEventActive\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F820\n"
        "     LDR     R0, [R4,#0x9C]\n"
        "     CMP     R0, R8\n"
        "     CMPNE   R0, R7\n"
        "     BEQ     loc_FF86F840\n"
        "     CMP     R0, R6\n"
        "     BEQ     loc_FF86F820\n"
        "     BL         sub_FF94234C\n"
        "     LDR     R1, =0x80000C00\n"
        "     CMP     R0, R1\n"
        "     BNE     loc_FF86F840\n"

    "loc_FF86F820:\n"    // CODE XREF: sub_FF86F6F0+E8j

        "     MOV     R1, #0\n"
        "     MOV     R0, #1\n"
        "     B         loc_FF86F838\n"


    "loc_FF86F82C:\n"    // CODE XREF: sub_FF86F6F0+1Cj

        "     STR     R0, [R4,#0x9C]\n"
        "     BL         sub_FF8701E8\n"
        "     B         loc_FF86F88C\n"


    "loc_FF86F838:\n"    // CODE XREF: sub_FF86F6F0+DCj

        "     BL         sub_FF86F224_my\n"    //   --------------->
        "     B         loc_FF86F88C\n"


    "loc_FF86F840:\n"    // CODE XREF: sub_FF86F6F0+114j

        "     BL         sub_FF870BF4\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F854\n"
        "     BL         sub_FF8701C8\n"
        "     B         loc_FF86F88C\n"


    "loc_FF86F854:\n"    // CODE XREF: sub_FF86F6F0+158j
        "     BL         sub_FF82CAA8\n"
        "     STR     R0, [R4,#0x18]\n"
        "     BL         sub_FF87015C\n"
        "     BL         sub_FF82BE70\n"
        "     LDR     R1, [R4,#0x18]\n"
        "     MOV     R0, #0\n"
        "     B         loc_FF86F838\n"


    "loc_FF86F870:\n"    // CODE XREF: sub_FF86F6F0+80j

        "     BL         sub_FF86EBB4\n"

    "loc_FF86F874:\n"    // CODE XREF: sub_FF86F6F0+2Cj

        "     LDR     R0, [R4,#0x98]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F88C\n"
        "     BL         sub_FF8701E8\n"
        "     MOV     R0, #1\n"
        "     STR     R0, [R4,#0x98]\n"

    "loc_FF86F88C:\n"    // CODE XREF: sub_FF86F6F0+144j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"


    "loc_FF86F894:\n"    // CODE XREF: sub_FF86F6F0+48j

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4-R8,PC}\n"
    );
}

// Extracted method: sub_FF82CD9C (FF82CD9C-FF82CDC4)
// Overridden calls:
//     sub_FF86FB00
void __attribute__((naked,noinline)) sub_FF82CD9C_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R4, =0x1DD0\n"
        "     LDR     R0, [R4]\n"
        "     CMP     R0, #0x1F\n"
        "     LDMNEFD SP!, {R4,PC}\n"
        "     MOV     R1, #0\n"
        "     LDR     R0, =0x313E\n"
        "     BL         sub_FF86FB00_my\n"    //   --------------->
        "     MOV     R0, #0\n"
        "     STR     R0, [R4]\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}


// Extracted method: sub_FF82C1B0 (FF82C1B0-FF82C288)
// Overridden calls:
//     sub_FF86FB00
void __attribute__((naked,noinline)) sub_FF82C1B0_my() {
    asm volatile (
        "     STMFD   SP!, {R4-R6,LR}\n"
        "     LDR     R4, =0x1DD0\n"
        "     MOV     R5, #1\n"
        "     MOV     R6, R0\n"
        "     STR     R5, [R4,#0x28]\n"
        "     LDR     R0, [R4,#8]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF82C1EC\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF82CDC8\n"    // sub_FF82CDC8
        "     LDR     R0, [R4,#8]\n"
        "     BL         sub_FF86A26C\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R4,#8]\n"

    "loc_FF82C1EC:\n"    // CODE XREF: sub_FF82C1B0+1Cj
        "     MOV     R0, #0\n"
        "     BL         sub_FF87E548\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF82C218\n"
        "     LDR     R1, =0xFF82C29C\n"    // aMycamfunc_play = "MyCamFunc_PlaySound_MYCAM_COVER_OPEN"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     LDR     R0, =0x400D\n"
        "     MOV     R1, #0\n"
        "     BL         sub_FF859588\n"
        "     B         loc_FF82C27C\n"


    "loc_FF82C218:\n"    // CODE XREF: sub_FF82C1B0+48j
        "     BL         sub_FF82CAF8\n"
        "     CMP     R0, #1\n"
        "     STREQ   R5, [R4,#0x18]\n"
        "     LDR     R0, [R4,#0xC]\n"
        "     SUB     R12, R0, #0x4000\n"
        "     SUBS    R12, R12, #4\n"
        "     SUBNE   R12, R0, #0x4000\n"
        "     SUBNES  R12, R12, #0x10\n"
        "     BEQ     loc_FF82C278\n"
        "     BL         sub_FF878A64\n"
        "     CMP     R0, #1\n"
        "     BEQ     loc_FF82C278\n"
        "     BL         _GetVRAMHPixelsSize_1\n"
        "     CMP     R0, #7\n"
        "     BEQ     loc_FF82C278\n"
        "     BL         _GetVRAMHPixelsSize_1\n"
        "     CMP     R0, #8\n"
        "     BEQ     loc_FF82C278\n"
        "     BL         _GetVRAMHPixelsSize_1\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF82C278\n"
        "     BL         sub_FF8772D8\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF82C27C\n"

    "loc_FF82C278:\n"    // CODE XREF: sub_FF82C1B0+88j

        "     BL         sub_FF82C01C\n"

    "loc_FF82C27C:\n"    // CODE XREF: sub_FF82C1B0+64j

        "     MOV     R0, R6\n"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     MOV     R1, #0\n"
        "     B         sub_FF86FB00_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF86E320 (FF86E320-FF86E34C)
// Overridden calls:
//     sub_FF86FB00
void __attribute__((naked,noinline)) sub_FF86E320_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF86E54C\n"    // aAcOpcovertimeo = "AC:OpCoverTimeout"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     LDR     R1, =0x5D40\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R1,#4]\n"
        "     STR     R0, [R1]\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #4\n"
        "     B         sub_FF86FB00_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF86F5E8 (FF86F5E8-FF86F6C4)
// Overridden calls:
//     sub_FF86EDAC
//     sub_FF86F498
//     sub_FF86F498
void __attribute__((naked,noinline)) sub_FF86F5E8_my() {
    asm volatile (
        "     LDR     R12, =0x201E\n"
        "     STMFD   SP!, {R4,LR}\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F6A8\n"
        "     BGT     loc_FF86F644\n"
        "     LDR     R12, =0x2004\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F6B0\n"
        "     BGT     loc_FF86F62C\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0xA9\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #0xAD\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #0xAF\n"
        "     BNE     loc_FF86F6C0\n"
        "     B         loc_FF86F6A8\n"


    "loc_FF86F62C:\n"    // CODE XREF: sub_FF86F5E8+20j
        "     SUB     R12, R0, #0x2000\n"
        "     SUBS    R12, R12, #5\n"
        "     SUBNE   R12, R0, #0x2000\n"
        "     SUBNES  R12, R12, #0x1D\n"
        "     BNE     loc_FF86F6C0\n"
        "     B         loc_FF86F6A8\n"


    "loc_FF86F644:\n"    // CODE XREF: sub_FF86F5E8+10j
        "     LDR     R12, =0x5004\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F6A8\n"
        "     BGT     loc_FF86F670\n"
        "     SUB     R12, R0, #0x3000\n"
        "     SUBS    R12, R12, #0xA\n"
        "     BEQ     loc_FF86F6A4\n"
        "     SUB     R12, R0, #0x5000\n"
        "     SUBS    R12, R12, #1\n"
        "     BNE     loc_FF86F6C0\n"
        "     B         loc_FF86F6A8\n"


    "loc_FF86F670:\n"    // CODE XREF: sub_FF86F5E8+68j
        "     SUB     R12, R0, #0x5000\n"
        "     SUBS    R12, R12, #6\n"
        "     BEQ     loc_FF86F6A8\n"
        "     SUB     R12, R0, #0x5000\n"
        "     SUBS    R12, R12, #7\n"
        "     BNE     loc_FF86F6C0\n"
        "     BL         sub_FF82CA40\n"
        "     LDR     R1, =0x5D50\n"
        "     LDR     R0, [R1,#0x10]\n"
        "     CMP     R0, #7\n"
        "     LDREQ   R0, [R1,#0x18]\n"
        "     BLEQ    sub_FF87015C\n"
        "     B         loc_FF86F6B8\n"


    "loc_FF86F6A4:\n"    // CODE XREF: sub_FF86F5E8+74j
        "     BL         sub_FF82BE70\n"

    "loc_FF86F6A8:\n"    // CODE XREF: sub_FF86F5E8+Cj

        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF86F498_my\n"    //   --------------->


    "loc_FF86F6B0:\n"    // CODE XREF: sub_FF86F5E8+1Cj
        "     BL         sub_FF86E2D0\n"
        "     BL         sub_FF86EDAC_my\n"    //   --------------->

    "loc_FF86F6B8:\n"    // CODE XREF: sub_FF86F5E8+B8j
        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4,PC}\n"


    "loc_FF86F6C0:\n"    // CODE XREF: sub_FF86F5E8+3Cj

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}

// Extracted method: sub_FF82C11C (FF82C11C-FF82C12C)
// Overridden calls:
//     sub_FF82CD9C
void __attribute__((naked,noinline)) sub_FF82C11C_my() {
    asm volatile (
        "     LDR     R0, =0x1DD0\n"
        "     LDR     R1, [R0]\n"
        "     ORR     R1, R1, #4\n"
        "     STR     R1, [R0]\n"
        "     B         sub_FF82CD9C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF82C0E0 (FF82C0E0-FF82C0F0)
// Overridden calls:
//     sub_FF82CD9C
void __attribute__((naked,noinline)) sub_FF82C0E0_my() {
    asm volatile (
        "     LDR     R0, =0x1DD0\n"
        "     LDR     R1, [R0]\n"
        "     ORR     R1, R1, #2\n"
        "     STR     R1, [R0]\n"
        "     B         sub_FF82CD9C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF82C0CC (FF82C0CC-FF82C0DC)
// Overridden calls:
//     sub_FF82CD9C
void __attribute__((naked,noinline)) sub_FF82C0CC_my() {
    asm volatile (
        "     LDR     R0, =0x1DD0\n"
        "     LDR     R1, [R0]\n"
        "     ORR     R1, R1, #1\n"
        "     STR     R1, [R0]\n"
        "     B         sub_FF82CD9C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF82C108 (FF82C108-FF82C118)
// Overridden calls:
//     sub_FF82CD9C
void __attribute__((naked,noinline)) sub_FF82C108_my() {
    asm volatile (
        "     LDR     R0, =0x1DD0\n"
        "     LDR     R1, [R0]\n"
        "     ORR     R1, R1, #0x10\n"
        "     STR     R1, [R0]\n"
        "     B         sub_FF82CD9C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF82C0F4 (FF82C0F4-FF82C104)
// Overridden calls:
//     sub_FF82CD9C
void __attribute__((naked,noinline)) sub_FF82C0F4_my() {
    asm volatile (
        "     LDR     R0, =0x1DD0\n"
        "     LDR     R1, [R0]\n"
        "     ORR     R1, R1, #8\n"
        "     STR     R1, [R0]\n"
        "     B         sub_FF82CD9C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF86E38C (FF86E38C-FF86E424)
// Overridden calls:
//     sub_FF86E320
void __attribute__((naked,noinline)) sub_FF86E38C_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R4, =0x5D40\n"
        "     LDR     R0, [R4,#4]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86E3F8\n"
        "     LDR     R0, =0x10B0\n"
        "     BL         _IsControlEventActive\n"
        "     CMP     R0, #0\n"
        "     LDMNEFD SP!, {R4,LR}\n"
        "     BNE     sub_FF86E350\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF86DC48\n"
        "     BL         sub_FF86E5E4\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #3\n"
        "     BL         sub_FF86E5B8\n"
        "     LDR     R1, =0xFF86E568\n"    // aAcStartshuttim = "AC:StartShutTimer"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     ADR     R2, sub_FF86E320_my\n"    //   --------------->
        "     LDR     R0, =0x2BF20\n"
        "     ADD     R1, R2, #0\n"
        "     MOV     R3, #0\n"
        "     BL         sub_FF86A1BC\n"
        "     STR     R0, [R4]\n"
        "     LDMFD   SP!, {R4,PC}\n"


    "loc_FF86E3F8:\n"    // CODE XREF: sub_FF86E38C+10j
        "     MOV     R1, #0\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF86DC48\n"
        "     BL         sub_FF86E5E4\n"
        "     LDR     R0, [R4,#8]\n"
        "     CMP     R0, #1\n"
        "     LDMNEFD SP!, {R4,LR}\n"
        "     MOVNE   R1, #0\n"
        "     MOV     R0, #1\n"
        "     BNE     sub_FF86E5B8\n"
        "     LDMEQFD SP!, {R4,LR}\n"
        "     BEQ     _RestartDevice\n"
    );
}

// Extracted method: sub_FF82C130 (FF82C130-FF82C15C)
// Overridden calls:
//     sub_FF82C0CC
//     sub_FF82C0E0
//     sub_FF82C0F4
//     sub_FF82C108
//     sub_FF82C11C
void __attribute__((naked,noinline)) sub_FF82C130_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     ADR     R0, sub_FF82C0CC_my\n"    //   --------------->
        "     BL         sub_FF880EC0\n"
        "     ADR     R0, sub_FF82C0E0_my\n"    //   --------------->
        "     BL         sub_FF87E548\n"
        "     ADR     R0, sub_FF82C0F4_my\n"    //   --------------->
        "     BL         sub_FF87F454\n"
        "     ADR     R0, sub_FF82C108_my\n"    //   --------------->
        "     BL         sub_FF884864\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     ADR     R0, sub_FF82C11C_my\n"    //   --------------->
        "     B         sub_FF87BA34\n"
    );
}

// Extracted method: sub_FF86ED10 (FF86ED10-FF86ED6C)
// Overridden calls:
//     sub_FF86E38C
//     sub_FF86E38C
void __attribute__((naked,noinline)) sub_FF86ED10_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R4, =0x5D50\n"
        "     LDR     R0, [R4,#0x60]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86ED38\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #5\n"
        "     BL         sub_FF86DC48\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF8701C8\n"


    "loc_FF86ED38:\n"    // CODE XREF: sub_FF86ED10+10j
        "     LDR     R1, [R4,#0x8C]\n"
        "     MOV     R0, #5\n"
        "     BL         sub_FF86DC48\n"
        "     LDR     R0, [R4,#0x5C]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86ED60\n"
        "     MOV     R0, #0x14\n"
        "     BL         sub_FF86E64C\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF86E428\n"


    "loc_FF86ED60:\n"    // CODE XREF: sub_FF86ED10+3Cj
        "     MOV     R0, #0x13\n"
        "     BL         sub_FF86E64C\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF86E38C_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF86EB84 (FF86EB84-FF86EBB0)
// Overridden calls:
//     sub_FF82C130
void __attribute__((naked,noinline)) sub_FF86EB84_my() {
    asm volatile (
        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF86ED84\n"    // aAcTstorelenst = "AC:TStoreLensT"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     LDR     R1, =0x5D50\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R1,#0x90]\n"
        "     BL         sub_FF82622C\n"
        "     CMP     R0, #1\n"
        "     LDMEQFD SP!, {R4,LR}\n"
        "     BEQ     sub_FF82C130_my\n"    //   --------------->
        "     LDMFD   SP!, {R4,PC}\n"
    );
}

// Extracted method: sub_FF86EFE4 (FF86EFE4-FF86F220)
// Overridden calls:
//     sub_FF82C130
//     sub_FF86EDAC
//     sub_FF870378
void __attribute__((naked,noinline)) sub_FF86EFE4_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R6,LR}\n"
        "     LDR     R5, =0x5D50\n"
        "     LDR     LR, =0x3202\n"
        "     LDR     R1, [R5,#0xB0]\n"
        "     LDR     R6, =0x2004\n"
        "     CMP     R1, #0\n"
        "     CMPNE   R0, LR\n"
        "     CMPNE   R0, R6\n"
        "     BNE     loc_FF86F210\n"
        "     LDR     R1, =0x5D50\n"
        "     LDR     R12, =0x10A9\n"
        "     LDR     R1, [R1,#0x24]\n"
        "     CMP     R0, R12\n"
        "     MOV     R3, #1\n"
        "     MOV     R4, #0\n"
        "     BEQ     loc_FF86F120\n"
        "     BGT     loc_FF86F0EC\n"
        "     LDR     R12, =0x1005\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F218\n"
        "     BGT     loc_FF86F084\n"
        "     LDR     R12, =0x9A5\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F0DC\n"
        "     BGT     loc_FF86F060\n"
        "     SUB     R12, R0, #0x900\n"
        "     SUBS    R12, R12, #0xA1\n"
        "     SUBNE   R12, R0, #0x900\n"
        "     SUBNES  R12, R12, #0xA3\n"
        "     BNE     loc_FF86F17C\n"
        "     B         loc_FF86F0DC\n"


    "loc_FF86F060:\n"    // CODE XREF: sub_FF86EFE4+60j
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #1\n"
        "     BEQ     loc_FF86F0E4\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #3\n"
        "     BNE     loc_FF86F17C\n"
        "     CMP     R1, #0\n"
        "     BLNE    sub_FF82C130_my\n"    //   --------------->
        "     B         loc_FF86F210\n"


    "loc_FF86F084:\n"    // CODE XREF: sub_FF86EFE4+50j
        "     LDR     R12, =0x1062\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F0E4\n"
        "     BGT     loc_FF86F0B0\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #8\n"
        "     BEQ     loc_FF86F218\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x5B\n"
        "     BNE     loc_FF86F17C\n"
        "     B         loc_FF86F0E4\n"


    "loc_FF86F0B0:\n"    // CODE XREF: sub_FF86EFE4+ACj
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x65\n"
        "     BEQ     loc_FF86F0E4\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0xA6\n"
        "     BNE     loc_FF86F17C\n"
        "     CMP     R1, #0\n"
        "     BEQ     loc_FF86F210\n"
        "     BL         sub_FF86ECF0\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86F210\n"

    "loc_FF86F0DC:\n"    // CODE XREF: sub_FF86EFE4+5Cj

        "     STR     R4, [R5,#0x50]!\n"
        "     STR     R3, [R5,#4]\n"

    "loc_FF86F0E4:\n"    // CODE XREF: sub_FF86EFE4+84j

        "     BL         sub_FF870204\n"
        "     B         loc_FF86F210\n"


    "loc_FF86F0EC:\n"    // CODE XREF: sub_FF86EFE4+40j
        "     LDR     R2, =0x1183\n"
        "     CMP     R0, R2\n"
        "     BEQ     loc_FF86F184\n"
        "     BGT     loc_FF86F148\n"
        "     LDR     R12, =0x10B7\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF86F0DC\n"
        "     BGT     loc_FF86F12C\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0xAD\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #0xAF\n"
        "     BNE     loc_FF86F17C\n"

    "loc_FF86F120:\n"    // CODE XREF: sub_FF86EFE4+3Cj
        "     STR     R3, [R5,#0xB0]\n"
        "     BL         sub_FF86EBB4\n"
        "     B         loc_FF86F20C\n"


    "loc_FF86F12C:\n"    // CODE XREF: sub_FF86EFE4+124j
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x62\n"
        "     BEQ     loc_FF86F200\n"
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x81\n"
        "     BNE     loc_FF86F17C\n"
        "     B         loc_FF86F184\n"


    "loc_FF86F148:\n"    // CODE XREF: sub_FF86EFE4+114j
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x95\n"
        "     BEQ     loc_FF86F184\n"
        "     CMP     R0, R6\n"
        "     BEQ     loc_FF86F1E8\n"
        "     SUB     R12, R0, #0x3000\n"
        "     SUBS    R12, R12, #1\n"
        "     STREQ   R3, [R5,#0xB0]\n"
        "     BEQ     loc_FF86F20C\n"
        "     CMP     R0, LR\n"
        "     STREQ   R3, [R5,#0xB4]\n"
        "     LDMEQFD SP!, {R4-R6,LR}\n"
        "     BEQ     sub_FF870378_my\n"    //   --------------->

    "loc_FF86F17C:\n"    // CODE XREF: sub_FF86EFE4+74j

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"


    "loc_FF86F184:\n"    // CODE XREF: sub_FF86EFE4+110j

        "     STR     R0, [R5,#0xAC]\n"
        "     CMP     R0, R2\n"
        "     STR     R4, [R5,#0x88]\n"
        "     BNE     loc_FF86F1BC\n"
        "     CMP     R1, #0\n"
        "     BLNE    sub_FF86FFFC\n"
        "     BL         sub_FF871178\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86F210\n"
        "     MOV     R0, #0x10\n"
        "     BL         sub_FF86E64C\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF8E2418\n"
        "     B         loc_FF86F210\n"


    "loc_FF86F1BC:\n"    // CODE XREF: sub_FF86EFE4+1ACj
        "     LDR     R1, =0xFF86F448\n"    // aAcPb2pc = "AC:PB2PC"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     LDR     R0, [R5,#0x24]\n"
        "     CMP     R0, #0\n"
        "     BLNE    sub_FF86FFFC\n"
        "     MOV     R0, #0\n"
        "     BL         sub_FF870128\n"
        "     MOV     R0, #0xF\n"
        "     BL         sub_FF86E64C\n"
        "     B         loc_FF86F210\n"


    "loc_FF86F1E8:\n"    // CODE XREF: sub_FF86EFE4+174j
        "     LDR     R0, [R5,#0x34]\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, [R5,#0xB4]\n"
        "     CMPNE   R0, #0\n"
        "     BLNE    sub_FF86EDAC_my\n"    //   --------------->
        "     B         loc_FF86F210\n"


    "loc_FF86F200:\n"    // CODE XREF: sub_FF86EFE4+150j
        "     STR     R3, [R5,#0xB0]\n"
        "     BL         _unknown_libname_96\n"    // "DryOS Canon Firmware; A720-based"
        "     B         loc_FF86F21C\n"


    "loc_FF86F20C:\n"    // CODE XREF: sub_FF86EFE4+144j

        "     BL         sub_FF870244\n"

    "loc_FF86F210:\n"    // CODE XREF: sub_FF86EFE4+20j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"


    "loc_FF86F218:\n"    // CODE XREF: sub_FF86EFE4+4Cj

        "     STR     R3, [R5,#0xB0]\n"

    "loc_FF86F21C:\n"    // CODE XREF: sub_FF86EFE4+224j
        "     BL         sub_FF86E2D0\n"
        "     B         loc_FF86F20C\n"
        ".LTORG\n" // make literal pool
    );
}

// Extracted method: sub_FF86EDAC (FF86EDAC-FF86EE08)
// Overridden calls:
//     sub_FF86ED10
//     sub_FF86ED10
void __attribute__((naked,noinline)) sub_FF86EDAC_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     LDR     R1, =0xFF86EFB8\n"    // aAcEntrynshtdwn = "AC:EntryNShtDwn"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     LDR     R4, =0x5D50\n"
        "     LDR     R0, [R4,#0x38]\n"
        "     CMP     R0, #0\n"
        "     LDMEQFD SP!, {R4,PC}\n"
        "     BL         _j_unknown_libname_73\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF86EDE4\n"
        "     LDR     R0, [R4,#0x44]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86EDFC\n"

    "loc_FF86EDE4:\n"    // CODE XREF: sub_FF86EDAC+28j
        "     LDR     R0, [R4,#0x38]\n"
        "     CMP     R0, #0\n"
        "     LDMEQFD SP!, {R4,PC}\n"
        "     BL         _j_unknown_libname_73\n"
        "     CMP     R0, #0\n"
        "     LDMNEFD SP!, {R4,PC}\n"

    "loc_FF86EDFC:\n"    // CODE XREF: sub_FF86EDAC+34j
        "     BL         sub_FF871AB0\n"
        "     BL         sub_FF871D48\n"
        "     LDMFD   SP!, {R4,LR}\n"
        "     B         sub_FF86ED10_my\n"    //   --------------->
    );
}

// Extracted method: sub_FF870468 (FF870468-FF87054C)
// Overridden calls:
//     sub_FF86EFE4
//     sub_FF86EB84
void __attribute__((naked,noinline)) sub_FF870468_my() {
    asm volatile (

    "var_10         = -0x10\n"

        "     SUB     R12, R0, #0x3200\n"
        "     SUBS    R12, R12, #1\n"
        "     MOVNE   R0, #1\n"
        "     STMFD   SP!, {R3-R5,LR}\n"
        "     BNE     locret_FF87054C\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #1\n"
        "     BL         sub_FF872404\n"
        "     MOV     R0, #2\n"
        "     BL         sub_FF86E64C\n"
        "     LDR     R4, =0x5D50\n"
        "     LDR     R0, [R4,#0x30]\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF8704E0\n"
        "     LDR     R1, =0xFF870658\n"    // aAcSstorelenst = "AC:SStoreLensT"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF86FFD8\n"
        "     LDR     R0, =0x406C\n"
        "     MOV     R2, #4\n"
        "     MOV     R1, SP\n"
        "     BL         sub_FF86DBA8\n"
        "     LDR     R0, [SP,#0x10+var_10]\n"
        "     MOV     R1, #0x3E8\n"
        "     LDR     R2, =sub_FF86EB84_my\n"    //   --------------->
        "     MUL     R0, R1, R0\n"
        "     ADD     R1, R2, #0\n"
        "     MOV     R3, #0\n"
        "     BL         sub_FF86A1BC\n"
        "     STR     R0, [R4,#0x90]\n"

    "loc_FF8704E0:\n"    // CODE XREF: sub_FF870468+34j
        "     BL         sub_FF87C298\n"
        "     BL         sub_FF871944\n"
        "     BL         sub_FF99E698\n"
        "     BL         sub_FF99E624\n"
        "     BL         sub_FF871630\n"
        "     BL         sub_FF871AE8\n"
        "     BL         sub_FF82BF40\n"
        "     LDR     R1, =0xFF870670\n"    // aAcEntrypb = "AC:EntryPB"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF86EB38\n"
        "     CMN     R0, #1\n"
        "     BLEQ    sub_FF8710FC\n"
        "     BL         sub_FF86EB38\n"
        "     BL         sub_FF86EFE4_my\n"    //   --------------->
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF870548\n"
        "     LDR     R0, [R4,#0x88]\n"
        "     MOV     R5, #0\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF870544\n"
        "     LDR     R0, =0x10A5\n"
        "     BL         _IsControlEventActive\n"
        "     CMP     R0, #0\n"
        "     BLEQ    sub_FF870204\n"

    "loc_FF870544:\n"    // CODE XREF: sub_FF870468+C8j
        "     STR     R5, [R4,#0x88]\n"

    "loc_FF870548:\n"    // CODE XREF: sub_FF870468+B8j
        "     MOV     R0, #0\n"

    "locret_FF87054C:\n"    // CODE XREF: sub_FF870468+10j
        "     LDMFD   SP!, {R3-R5,PC}\n"
    );
}

// Extracted method: sub_FF86EE0C (FF86EE0C-FF86EFB4)
// Overridden calls:
//     sub_FF86EDAC
//     sub_FF870378
//     sub_FF870378
void __attribute__((naked,noinline)) sub_FF86EE0C_my() {
    asm volatile (

        "     STMFD   SP!, {R4-R6,LR}\n"
        "     LDR     R4, =0x5D50\n"
        "     LDR     R3, =0x201B\n"
        "     LDR     R2, [R4,#0xA0]\n"
        "     SUB     LR, R3, #0x17\n"
        "     CMP     R2, #0\n"
        "     CMPNE   R0, R3\n"
        "     CMPNE   R0, LR\n"
        "     SUBNE   R12, R0, #0x3000\n"
        "     SUBNES  R12, R12, #6\n"
        "     BNE     loc_FF86EFA8\n"
        "     LDR     R6, =0x10A5\n"
        "     MOV     R1, #1\n"
        "     ADD     R12, R6, #0x13\n"
        "     CMP     R0, R12\n"
        "     MOV     R5, #0\n"
        "     STREQ   R1, [R4,#0x34]\n"
        "     BEQ     loc_FF86EF60\n"
        "     BGT     loc_FF86EEC8\n"
        "     CMP     R0, R6\n"
        "     STREQ   R1, [R4,#0x88]\n"
        "     BEQ     loc_FF86EE94\n"
        "     BGT     loc_FF86EE9C\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #3\n"
        "     BEQ     loc_FF86EE94\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #5\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #8\n"
        "     BEQ     loc_FF86EF60\n"
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0x61\n"
        "     BNE     loc_FF86EFB0\n"

    "loc_FF86EE94:\n"    // CODE XREF: sub_FF86EE0C+54j

        "     STR     R5, [R4,#0x6C]\n"
        "     B         loc_FF86EF58\n"


    "loc_FF86EE9C:\n"    // CODE XREF: sub_FF86EE0C+58j
        "     SUB     R12, R0, #0x1000\n"
        "     SUBS    R12, R12, #0xA9\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #0xAD\n"
        "     SUBNE   R12, R0, #0x1000\n"
        "     SUBNES  R12, R12, #0xAF\n"
        "     BNE     loc_FF86EFB0\n"
        "     STR     R1, [R4,#0xA0]\n"
        "     BL         sub_FF86EBB4\n"

    "loc_FF86EEC0:\n"    // CODE XREF: sub_FF86EE0C+15Cj
        "     BL         sub_FF870284\n"
        "     B         loc_FF86EFA8\n"


    "loc_FF86EEC8:\n"    // CODE XREF: sub_FF86EE0C+48j
        "     CMP     R0, R3\n"
        "     BEQ     loc_FF86EF6C\n"
        "     BGT     loc_FF86EF04\n"
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x62\n"
        "     BEQ     loc_FF86EF60\n"
        "     SUB     R12, R0, #0x1100\n"
        "     SUBS    R12, R12, #0x85\n"
        "     SUBNE   R12, R0, #0x1100\n"
        "     SUBNES  R12, R12, #0x86\n"
        "     BEQ     loc_FF86EFA8\n"
        "     CMP     R0, LR\n"
        "     BNE     loc_FF86EFB0\n"
        "     BL         sub_FF86EDAC_my\n"    //   --------------->
        "     B         loc_FF86EFA8\n"


    "loc_FF86EF04:\n"    // CODE XREF: sub_FF86EE0C+C4j
        "     SUB     R12, R0, #0x3000\n"
        "     SUBS    R12, R12, #1\n"
        "     BEQ     loc_FF86EF60\n"
        "     SUB     R12, R0, #0x3000\n"
        "     SUBS    R12, R12, #0x110\n"
        "     SUBNE   R12, R0, #0x3100\n"
        "     SUBNES  R12, R12, #0x11\n"
        "     BNE     loc_FF86EFB0\n"
        "     LDR     R1, =0xFF86EFD0\n"    // a_entrystartrec = "_EntryStartRecMode"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     MOV     R1, #0\n"
        "     MOV     R0, #1\n"
        "     BL         sub_FF872404\n"
        "     LDR     R0, [R4,#0x50]\n"
        "     CMP     R0, #0\n"
        "     BNE     loc_FF86EF58\n"
        "     MOV     R0, R6\n"
        "     BL         _IsControlEventActive\n"
        "     CMP     R0, #0\n"
        "     BEQ     loc_FF86EF88\n"

    "loc_FF86EF58:\n"    // CODE XREF: sub_FF86EE0C+8Cj

        "     BL         sub_FF86EBFC\n"
        "     B         loc_FF86EFA8\n"


    "loc_FF86EF60:\n"    // CODE XREF: sub_FF86EE0C+44j

        "     STR     R1, [R4,#0xA0]\n"
        "     BL         sub_FF86E2D0\n"
        "     B         loc_FF86EEC0\n"


    "loc_FF86EF6C:\n"    // CODE XREF: sub_FF86EE0C+C0j
        "     CMP     R2, #0\n"
        "     BEQ     loc_FF86EFB0\n"
        "     LDR     R0, [R4,#0x60]\n"
        "     CMP     R0, #0\n"
        "     BLNE    _unknown_libname_96\n"    // "DryOS Canon Firmware; A720-based"
        "     LDMFD   SP!, {R4-R6,LR}\n"
        "     B         sub_FF870378_my\n"    //   --------------->


    "loc_FF86EF88:\n"    // CODE XREF: sub_FF86EE0C+148j
        "     LDR     R0, [R4,#0x68]\n"
        "     LDR     R1, [R4,#0x7C]\n"
        "     ORRS    R0, R0, R1\n"
        "     BLEQ    sub_FF874BB8\n"
        "     BL         sub_FF871944\n"
        "     BL         sub_FF871AE8\n"
        "     BL         sub_FF82BF40\n"
        "     STR     R5, [R4,#0x68]\n"

    "loc_FF86EFA8:\n"    // CODE XREF: sub_FF86EE0C+28j

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"


    "loc_FF86EFB0:\n"    // CODE XREF: sub_FF86EE0C+84j

        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4-R6,PC}\n"
    );
}

// Extracted method: sub_FF870378 (FF870378-FF8703B8)
// Overridden calls:
//     sub_FF86EDAC
void __attribute__((naked,noinline)) sub_FF870378_my() {
    asm volatile (

        "     STMFD   SP!, {R4,LR}\n"
        "     BL         _nullsub_35\n"
        "     LDR     R1, =0x5D50\n"
        "     LDR     R0, [R1,#0x34]\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, [R1,#0x30]\n"
        "     CMPNE   R0, #0\n"
        "     BEQ     loc_FF8703A8\n"
        "     BL         sub_FF86FFFC\n"
        "     BL         sub_FF871AE8\n"
        "     BL         sub_FF871D48\n"
        "     B         loc_FF8703B4\n"


    "loc_FF8703A8:\n"    // CODE XREF: sub_FF870378+1Cj
        "     BL         sub_FF871AE8\n"
        "     BL         sub_FF871D48\n"
        "     BL         sub_FF86EDAC_my\n"    //   --------------->

    "loc_FF8703B4:\n"    // CODE XREF: sub_FF870378+2Cj
        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}

// Extracted method: sub_FF870550 (FF870550-FF870628)
// Overridden calls:
//     sub_FF86EDAC
void __attribute__((naked,noinline)) sub_FF870550_my() {
    asm volatile (
        "     LDR     R12, =0x5001\n"
        "     STMFD   SP!, {R4,LR}\n"
        "     CMP     R0, R12\n"
        "     BEQ     loc_FF87058C\n"
        "     BGT     loc_FF8705C8\n"
        "     SUB     R12, R0, #0x2000\n"
        "     SUBS    R12, R12, #4\n"
        "     BEQ     loc_FF87058C\n"
        "     SUB     R12, R0, #0x3000\n"
        "     SUBS    R12, R12, #0xA\n"
        "     BNE     loc_FF8705DC\n"
        "     LDR     R1, =0xFF870680\n"    // aCreatepbcontro = "CreatePBController"
        "     MOV     R0, #0x20\n"
        "     BL         sub_FF867708\n"
        "     BL         sub_FF87B388\n"

    "loc_FF87058C:\n"    // CODE XREF: sub_FF870550+Cj

        "     LDR     R4, =0x5D50\n"
        "     LDR     R0, [R4,#0x38]\n"
        "     CMP     R0, #0\n"
        "     LDRNE   R0, [R4,#0x40]\n"
        "     CMPNE   R0, #0\n"
        "     LDRNE   R0, [R4,#0x44]\n"
        "     CMPNE   R0, #0\n"
        "     LDRNE   R0, [R4,#0x48]\n"
        "     CMPNE   R0, #0\n"
        "     LDRNE   R0, [R4,#0x1C]\n"
        "     LDRNE   R1, [R4,#0x20]\n"
        "     ORRNES  R0, R0, R1\n"
        "     BEQ     loc_FF8705E4\n"
        "     BL         sub_FF86EBB4\n"
        "     B         loc_FF8705FC\n"


    "loc_FF8705C8:\n"    // CODE XREF: sub_FF870550+10j
        "     SUB     R12, R0, #0x5000\n"
        "     SUBS    R12, R12, #3\n"
        "     SUBNE   R12, R0, #0x5000\n"
        "     SUBNES  R12, R12, #6\n"
        "     BEQ     loc_FF87058C\n"

    "loc_FF8705DC:\n"    // CODE XREF: sub_FF870550+28j
        "     MOV     R0, #1\n"
        "     LDMFD   SP!, {R4,PC}\n"


    "loc_FF8705E4:\n"    // CODE XREF: sub_FF870550+6Cj
        "     BL         sub_FF86ECAC\n"
        "     CMP     R0, #1\n"
        "     BNE     loc_FF870624\n"
        "     BL         sub_FF86EB38\n"
        "     CMN     R0, #1\n"
        "     BEQ     loc_FF870604\n"

    "loc_FF8705FC:\n"    // CODE XREF: sub_FF870550+74j
        "     BL         sub_FF86EDAC_my\n"    //   --------------->
        "     B         loc_FF870624\n"


    "loc_FF870604:\n"    // CODE XREF: sub_FF870550+A8j
        "     BL         sub_FF870774\n"
        "     LDR     R0, [R4,#0x68]\n"
        "     CMP     R0, #0\n"
        "     BLEQ    sub_FF82BFBC\n"
        "     MOV     R0, #0\n"
        "     STR     R0, [R4,#0x68]\n"
        "     MOV     R0, #0xB\n"
        "     BL         sub_FF86E64C\n"

    "loc_FF870624:\n"    // CODE XREF: sub_FF870550+9Cj

        "     MOV     R0, #0\n"
        "     LDMFD   SP!, {R4,PC}\n"
    );
}
