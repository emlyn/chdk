#include "conf.h"

// from sx10
void change_video_tables(int a, int b){
}

// from sx10, TODO untested, not hooked up yet
void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

void __attribute__((naked,noinline)) movie_record_task(){ 
 asm volatile(
"                STMFD   SP!, {R2-R8,LR}\n"
"                LDR     R7, =0x2710\n"
"                LDR     R4, =0x53A0\n"
"                MOV     R6, #0\n"
"                MOV     R5, #1\n"
"loc_FF86215C:\n" // main loop
"                LDR     R0, [R4,#0x1C]\n"
"                MOV     R2, #0\n"
"                ADD     R1, SP, #4\n"
"                BL      sub_FF82746C\n" // LOCATION: KerQueue.c:0
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF86222C\n"
"                LDR     R0, [SP,#4]\n"
"                LDR     R1, [R0]\n"
"                SUB     R1, R1, #2\n"
"                CMP     R1, #9\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       loc_FF86222C\n"
"                B       loc_FF8621E0\n"
"                B       loc_FF862200\n"
"                B       loc_FF862210\n"
"                B       loc_FF862218\n"
"                B       loc_FF8621E8\n"
"                B       loc_FF862220\n"
"                B       loc_FF8621F0\n"
"                B       loc_FF86222C\n"
"                B       loc_FF862228\n"
"                B       loc_FF8621B8\n"
"loc_FF8621B8:\n"
// jumptable FF862188 entry 9
"                LDR     R0, =0xFF861E30\n" // loc_ret
"                STR     R6, [R4,#0x38]\n"
"                STR     R0, [R4,#0xA0]\n"
"                LDR     R2, =0xFF8613B0\n" // sub_FF8613B0
"                LDR     R1, =0x1AE50\n"
"                LDR     R0, =0xFF861494\n" //loc_FF861494
"                STR     R6, [R4,#0x28]\n"
"                BL      sub_FF83BBFC\n"
"                STR     R5, [R4,#0x3C]\n"
"                B       loc_FF86222C\n" // -> jt 7, loop
"loc_FF8621E0:\n"
// jumptable FF862188 entry 0
"                BL      unlock_optical_zoom\n" //  +
"                BL      sub_FF861F28\n" // __MovieRecorder_c__0
"                B       loc_FF86222C\n"
"loc_FF8621E8:\n"
// jumptable FF862188 entry 4
"                BL      sub_FF861AA8\n" // -> _my for quality ?
"                B       loc_FF86222C\n"
"loc_FF8621F0:\n"
// jumptable FF862188 entry 6
"                LDR     R1, [R0,#0x10]\n"
"                LDR     R0, [R0,#4]\n"
"                BL      sub_FF937EF8\n" // LOCATION: MovWriter.c:0
"                B       loc_FF86222C\n" // -> jt 7, loop
"loc_FF862200:\n"
// jumptable FF862188 entry 1
"                LDR     R0, [R4,#0x3C]\n"
"                CMP     R0, #5\n"
"                STRNE   R5, [R4,#0x2C]\n"
"                B       loc_FF86222C\n" // -> jt 7, loop
"loc_FF862210:\n"
// jumptable FF862188 entry 2
"                BL      sub_FF8617F0\n" // __MovieRecorder_c__0
"                B       loc_FF86222C\n" // -> jt 7, loop
"loc_FF862218:\n"
// jumptable FF862188 entry 3
"                BL      sub_FF8614E0\n" // __MovieRecorder_c__0
"                B       loc_FF86222C\n" // -> jt 7, loop
"loc_FF862220:\n"
// jumptable FF862188 entry 5
"                BL      sub_FF86133C\n" //__MovieRecorder_c__100
"                B       loc_FF86222C\n" // -> jt 7, loop
"loc_FF862228:\n"
// jumptable FF862188 entry 8
"                BL      sub_FF862398\n" /// __MovieRecorder_c__100
"loc_FF86222C:\n"
// jumptable FF862188 default entry
// jumptable FF862188 entry 7
"                LDR     R1, [SP,#4]\n"
"                MOV     R3, #0x430\n"
"                STR     R6, [R1]\n"
"                STR     R3, [SP]\n"
"                LDR     R0, [R4,#0x20]\n"
"                LDR     R3, =0xFF86113C\n"// =aMovierecorder_
"                MOV     R2, R7\n"
"                BL      sub_FF827DC0\n"
"                B       loc_FF86215C\n" // -> main loop
 );
}

