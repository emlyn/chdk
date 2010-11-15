#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table1[9]= {0x2000,0x38D,0x788,0x5800,0x9C5,0x14B8,0x10000,0x1C6A,0x3C45};    // ???
long def_table2[9]= {0x1CCD,-0x2E1,-0x579,0x4F33,-0x7EB,-0xF0C,0xE666,-0x170A,-0x2BC6};    // ???

long table1[9], table2[9];

void change_video_tables(int a, int b) {
    int i;
    for(i=0; i<9; i++) {
        table1[i]=(def_table1[i]*a)/b;
        table2[i]=(def_table2[i]*a)/b;
    }
}

//long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};   // from SD800
long CompressionRateTable[]= {0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};  // ??? ROM:FF986318

// ROM:FF984E84 task_MovieRecord()
void __attribute__((naked,noinline)) movie_record_task() {
    asm volatile(
        "STMFD   SP!, {R4,R5,LR}\n"
        "SUB     SP, SP, #4\n"
        "MOV     R5, SP\n"
        "MOV     R4, #0\n"

        "loc_FF984E94:\n"
        "LDR     R3, =0x76324\n"
        "MOV     R2, #0\n"
        "LDR     R0, [R3]\n"
        "MOV     R1, R5\n"
        "BL      sub_FF8213F8\n"   // ReceiveMessageQueue()
        "LDR     R3, =0x763F8\n"
        "LDR     R2, [R3]\n"
        "CMP     R2, #0\n"
        "BNE     loc_FF984F40\n"
        "LDR     R1, [SP]\n"
        "LDR     R3, [R1]\n"
        "SUB     R3, R3, #2\n"
        "MOV     R0, R1\n"
        "CMP     R3, #9\n"   // switch 10 cases
        "LDRLS   PC, [PC,R3,LSL#2]\n"   // switch jump
        "B       loc_FF984F44\n"   // switch default

        ".long loc_FF984F04\n"   // jump table for switch statement
        ".long loc_FF984F1C\n"
        ".long loc_FF984F24\n"
        ".long loc_FF984F2C\n"
        ".long loc_FF984F0C\n"
        ".long loc_FF984F34\n"
        ".long loc_FF984F14\n"
        ".long loc_FF984F44\n"
        ".long loc_FF984F3C\n"
        ".long loc_FF984EFC\n"

        "loc_FF984EFC:\n"
        "BL      sub_FF984FB0\n"
        "B       loc_FF984F40\n"

        "loc_FF984F04:\n"
        "BL      unlock_optical_zoom\n"   // + like SD800
        "BL      sub_FF985194\n"
        "B       loc_FF984F40\n"

        "loc_FF984F0C:\n"
        //"BL      sub_FF98565C\n"   // original
        "BL      sub_FF98565C_my\n"   // + like SD800
        "B       loc_FF984F40\n"

        "loc_FF984F14:\n"
        "BL      sub_FF985D48\n"
        "B       loc_FF984F40\n"

        "loc_FF984F1C:\n"
        "BL      sub_FF98592C\n"
        "B       loc_FF984F40\n"

        "loc_FF984F24:\n"
        "BL      sub_FF985EE4\n"
        "B       loc_FF984F40\n"

        "loc_FF984F2C:\n"
        "BL      sub_FF986114\n"
        "B       loc_FF984F40\n"

        "loc_FF984F34:\n"
        "BL      sub_FF985DD0\n"
        "B       loc_FF984F40\n"

        "loc_FF984F3C:\n"
        "BL      sub_FF98597C\n"

        "loc_FF984F40:\n"
        "LDR     R1, [SP]\n"

        "loc_FF984F44:\n"
        "LDR     R3, =0x76328\n"
        "STR     R4, [R1]\n"
        "LDR     R0, [R3]\n"
        "MOV     R2, R4\n"
        "BL      sub_FF821810\n"   // PostMessageQueue()
        "B       loc_FF984E94\n"
    );
}

// ROM:FF98565C
void __attribute__((naked,noinline)) sub_FF98565C_my() {
    asm volatile(
        "STMFD   SP!, {R4-R11,LR}\n"
        "LDR     R5, =0x76410\n"
        "SUB     SP, SP, #0x34\n"
        "LDR     R3, [R5]\n"
        "MOV     R2, #0\n"
        "CMP     R3, #3\n"
        "STR     R2, [SP,#0x24]\n"
        "MOV     R4, R0\n"
        "STR     R2, [SP,#0x2C]\n"
        "MOVEQ   R3, #4\n"
        "STREQ   R3, [R5]\n"
        "LDR     R3, =0x764AC\n"
        "MOV     LR, PC\n"
        "LDR     PC, [R3]\n"
        "LDR     R2, [R5]\n"
        "CMP     R2, #4\n"
        "BNE     loc_FF985854\n"
        "ADD     R0, SP, #0x30\n"
        "ADD     R1, SP, #0x2C\n"
        "ADD     R2, SP, #0x28\n"
        "ADD     R3, SP, #0x24\n"
        "BL      sub_FF987180\n"
        "CMP     R0, #0\n"
        "BNE     loc_FF9856E4\n"
        "LDR     R3, =0x76400\n"
        "LDR     R2, [R3]\n"
        "CMP     R2, #1\n"
        "BNE     loc_FF9856F8\n"
        "LDR     R2, =0x7643C\n"
        "LDR     R1, =0x76414\n"
        "LDR     R12, [R2]\n"
        "LDR     R3, [R1]\n"
        "CMP     R12, R3\n"
        "BCC     loc_FF9856F8\n"

        "loc_FF9856E4:\n"
        "BL      sub_FF9858A4\n"
        "BL      sub_FF985D08\n"
        "MOV     R3, #5\n"
        "STR     R3, [R5]\n"
        "B       loc_FF985854\n"

        "loc_FF9856F8:\n"
        "LDR     R8, [SP,#0x2C]\n"
        "CMP     R8, #0\n"
        "BEQ     loc_FF9857D4\n"
        "LDR     R12, =0x76444\n"
        "LDR     R9, =0x76450\n"
        "LDR     R11, =0x76404\n"
        "LDR     R7, [R12]\n"
        "ADD     R5, SP, #0x24\n"
        "LDMIA   R5, {R5,LR}\n"
        "LDR     R6, [R9]\n"
        "MOV     R10, #1\n"
        "LDMIB   R4, {R0-R2}\n"
        "LDR     R3, [SP,#0x30]\n"
        "ADD     R12, SP, #0x20\n"
        "STR     R10, [R11]\n"
        "ADD     R4, SP, #0x1C\n"
        "STMEA   SP, {R8,LR}\n"
        "STR     R5, [SP,#0x8]\n"
        "STR     R12, [SP,#0xC]\n"
        "STR     R7, [SP,#0x10]\n"
        "STR     R6, [SP,#0x14]\n"
        "STR     R4, [SP,#0x18]\n"
        "BL      sub_FF8A7688\n"
        "LDR     R3, =0x7631C\n"
        "MOV     R1, #0x3E8\n"
        "LDR     R0, [R3]\n"
        "BL      sub_FF821FA4\n"   // TakeSemaphore()
        "CMP     R0, #9\n"
        "BNE     loc_FF98577C\n"
        "BL      sub_FF987A10\n"
        "LDR     R3, =0x76410\n"
        "LDR     R0, =0xFF985644\n"   // aJpegtimeout_4
        "B       loc_FF985794\n"

        "loc_FF98577C:\n"
        "LDR     R4, [SP,#0x1C]\n"
        "CMP     R4, #0\n"
        "BEQ     loc_FF9857A0\n"
        "BL      sub_FF987A10\n"
        "LDR     R3, =0x76410\n"
        "LDR     R0, =0xFF985650\n"   // aJpegicerror_5

        "loc_FF985794:\n"
        "STR     R10, [R3]\n"
        "BL      sub_FF99FA2C\n"   // eventproc_export_HardwareDefect()
        "B       loc_FF985854\n"

        "loc_FF9857A0:\n"
        "BL      sub_FF8A77E4\n"
        "LDR     R0, [SP,#0x30]\n"
        "LDR     R1, [SP,#0x20]\n"
        "BL      sub_FF987668\n"   // LOCATION: AviWriter.c:944
        "LDR     R12, =0x76438\n"
        "LDR     R3, [R12]\n"
        "ADD     R3, R3, #1\n"
        "LDR     R0, [SP,#0x20]\n"
        "MOV     R1, R9\n"
        "MOV     R2, R4\n"
        "STR     R3, [R12]\n"
        //"BL      sub_FF98650C\n"   // original
        "BL      sub_FF98650C_my\n"   // + like SD800
        "B       loc_FF9857D8\n"

        "loc_FF9857D4:\n"
        "LDR     R11, =0x76404\n"

        "loc_FF9857D8:\n"
        "LDR     R4, =0x7643C\n"
        "LDR     R2, =0x7645C\n"
        "LDR     R3, [R4]\n"
        "LDR     R1, [R2]\n"
        "LDR     R12, =0x76458\n"
        "ADD     R3, R3, #1\n"
        "MUL     R0, R1, R3\n"
        "LDR     R1, [R12]\n"
        "STR     R3, [R4]\n"
        "BL      sub_FFB4E7F0\n"   // __udivsi3()
        "LDR     R6, =0x76454\n"
        "MOV     R4, R0\n"
        "BL      sub_FF987A4C\n"
        "LDR     R3, [R6]\n"
        "CMP     R3, R4\n"
        "BNE     loc_FF98582C\n"
        "LDR     R5, =0x76408\n"
        "LDR     R3, [R5]\n"
        "CMP     R3, #1\n"
        "BNE     loc_FF98584C\n"
        "B       loc_FF985830\n"

        "loc_FF98582C:\n"
        "LDR     R5, =0x76408\n"

        "loc_FF985830:\n"
        "LDR     R2, =0x76490\n"
        "MOV     R0, R4\n"
        "MOV     LR, PC\n"
        "LDR     PC, [R2]\n"
        "MOV     R3, #0\n"
        "STR     R3, [R5]\n"
        "STR     R4, [R6]\n"

        "loc_FF98584C:\n"
        "MOV     R3, #0\n"
        "STR     R3, [R11]\n"

        "loc_FF985854:\n"
        "ADD     SP, SP, #0x34\n"
        "LDMFD   SP!, {R4-R11,PC}\n"
    );
}

void __attribute__((naked,noinline)) sub_FF98650C_my() {
    asm volatile(
        "CMP     R2, #1\n"
        "STMFD   SP!, {R4-R7,LR}\n"
        "MOV     R7, R0\n"
        "MOV     R6, R1\n"
        "MOVEQ   R3, #0x79\n"
        "STREQ   R3, [R6]\n"
        "LDMEQFD SP!, {R4-R7,PC}\n"
        "LDR     R12, =0x764F0\n"
        "LDR     R0, [R12]\n"
        "LDR     R3, =0x764F8\n"
        "CMP     R0, #0\n"
        "LDR     R1, [R3]\n"
        "BEQ     loc_FF986554\n"
        "LDR     R2, =0x764FC\n"
        "LDR     R3, [R2]\n"
        "CMP     R3, #1\n"
        "BNE     loc_FF986568\n"
        "B       loc_FF986558\n"

        "loc_FF986554:\n"
        "LDR     R2, =0x764FC\n"

        "loc_FF986558:\n"
        "MOV     R3, #0\n"
        "STR     R3, [R2]\n"
        "STR     R7, [R12]\n"
        "B       loc_FF986620\n"

        "loc_FF986568:\n"
        "LDR     R2, =0x764F4\n"
        "LDR     R3, [R2]\n"
        "LDR     R5, =table1\n"
        "ADD     R3, R3, R3,LSL#1\n"
        "MOV     LR, R3,LSL#2\n"
        "LDR     R2, [R5,LR]\n"
        "LDR     R4, =table2\n"
        "RSB     R12, R2, R0\n"
        "LDR     R3, [R4,LR]\n"
        "CMP     R12, #0\n"
        "RSB     R0, R3, R0\n"
        "BLE     loc_FF9865CC\n"
        "ADD     R3, R5, #4\n"
        "LDR     R2, [R3,LR]\n"
        "CMP     R2, R12\n"
        "ADDGE   R1, R1, #1\n"
        "BGE     loc_FF9865C0\n"
        "ADD     R3, R5, #8\n"
        "LDR     R2, [R3,LR]\n"
        "CMP     R2, R12\n"
        "ADDGE   R1, R1, #2\n"
        "ADDLT   R1, R1, #3\n"

        "loc_FF9865C0:\n"
        //"CMP     R1, #0xE\n"   // original
        "CMP     R1, #0x1A\n"   // + like SD800
        //"MOVGE   R1, #0xE\n"   // original
        "MOVGE   R1, #0x1A\n"   // + like SD800
        "B       loc_FF986604\n"

        "loc_FF9865CC:\n"
        "CMP     R0, #0\n"
        "BGE     loc_FF986604\n"
        "ADD     R3, R4, #4\n"
        "LDR     R2, [R3,LR]\n"
        "CMP     R2, R0\n"
        "SUBLE   R1, R1, #1\n"
        "BLE     loc_FF9865FC\n"
        "ADD     R3, R4, #8\n"
        "LDR     R2, [R3,LR]\n"
        "CMP     R2, R0\n"
        "SUBLE   R1, R1, #2\n"
        "SUBGT   R1, R1, #3\n"

        "loc_FF9865FC:\n"
        "CMP     R1, #0\n"
        "MOVLT   R1, #0\n"

        "loc_FF986604:\n"
        "LDR     R0, =0x764F8\n"
        "LDR     R3, [R0]\n"
        "CMP     R1, R3\n"
        "LDRNE   R2, =0x764FC\n"
        "MOVNE   R3, #1\n"
        "STRNE   R1, [R0]\n"
        "STRNE   R3, [R2]\n"

        "loc_FF986620:\n"
        "LDR     R3, =0x764F8\n"
        //"LDR     R1, =0x6AFC\n"   // original
        "LDR     R1, =video_mode\n"   // + like SD800
        "LDR     R0, [R3]\n"
        //"LDR     R2, =0xFF986318\n"   // original
        "LDR     R2, =CompressionRateTable\n"   // +
        "LDR     R12, [R1]\n"
        "LDR     R12, [R12]\n"   // from SD800
        "LDR     LR, [R2,R0,LSL#2]\n"
        "LDR     R3, =0x764F0\n"
        "CMP     R12, #1\n"
        "STR     R7, [R3]\n"
        "STR     LR, [R6]\n"
        //"MOVEQ   R3, #0xB\n"   // like SD800
        "LDREQ   R3, =video_quality\n"   // + like SD800
        "LDREQ   R3, [R3]\n"   // + like SD800
        "LDREQ   R3, [R3]\n"   // + like SD800
        "STREQ   R3, [R6]\n"
        "LDMFD   SP!, {R4-R7,PC}\n"
    );
}
