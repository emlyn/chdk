#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (2)
#define NR_OFF (1)

static long raw_save_stage;

void capt_seq_hook_raw_here()
{
    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available();
    while (raw_save_stage != RAWDATA_SAVED){
        _SleepTask(10);
    }
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}

void capt_seq_hook_set_nr()
{
    long *nrflag = (long*)0x6134;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
        // leave it alone
        break;
    case NOISE_REDUCTION_OFF:
        *nrflag = 1;
        break;
    case NOISE_REDUCTION_ON:
        *nrflag = 2;
        break;
    };
}


/* void handle_is_off(void){
 if (conf.turn_off_is && (shooting_get_tv96()<0)) { // greater than 1 sec
  stop_IS();
 }
} */

/*void handle_is_on(void){
 if (conf.turn_off_is && (get_IS_mode()!=3)) start_IS();
} */

void __attribute__((naked,noinline)) sub_FFD483A4_my(long p)
{
  asm volatile (
              "STMFD   SP!, {R4-R6,LR}\n"
              "LDR     R3, =0x64DDC\n"
              "LDR     R5, =0x6130\n"
              "SUB     SP, SP, #4\n"
              "LDR     R1, =0xFFFFFFFF\n"
              "STR     R0, [R5]\n"
              "LDR     R0, [R3]\n"
              "BL      sub_FFC0FB44\n"
              "LDR     R3, =0x8F480\n"
              "LDR     R0, [R3,#0x74]\n"
              "BL      sub_FFC8BFB8\n"
              "BL      sub_FFD482F8\n"
             
              "LDR     R3, =0x6138\n"
              "LDR     R0, [R3]\n"
              "BL      sub_FFC8C454\n"
              "BL      capt_seq_hook_set_nr\n"
              "B       sub_FFD483E0\n"
  );
}

void __attribute__((naked,noinline)) sub_FFD45048_my(long p)
{
  asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "LDR     R4, [R0,#0xC]\n"
              "BL      sub_FFD4D73C\n"
              "CMP     R0, #0\n"
              "BNE     loc_FFD45060\n"
              "BL      sub_FFD4D748\n"
    "loc_FFD45060:\n"
              "MOV     R0, #0xC\n"
              "BL      sub_FFD4D75C\n"
              "TST     R0, #1\n"
              "MOV     R2, R4\n"
              "MOV     R0, R4\n"
              "BEQ     loc_FFD45088\n"
              "MOV     R0, #1\n"
              "MOV     R1, R0\n"
              "LDMFD   SP!, {R4,LR}\n"
              "B       sub_FFD43578\n"
    "loc_FFD45088:\n"
              "BL      sub_FFD47160\n"
              "TST     R0, #1\n"
              "MOV     R2, R4\n"
              "MOV     R1, #1\n"
              "BEQ     loc_FFD450A4\n"
              "LDMFD   SP!, {R4,LR}\n"
              "B       sub_FFD43578\n"
    "loc_FFD450A4:\n"
              "BL      sub_FFD85D18\n"
              "BL      sub_FFC146EC\n"
              "LDR     R2, =0x8F3C4\n"
              "ADD     R3, R4, R4,LSL#1\n"
              "STR     R0, [R2,R3,LSL#5]\n"
              "MOV     R0, R4\n"
              "BL      sub_FFD48B10\n"
              "BL      sub_FFD47664\n"
              "BL      sub_FFD47600\n"
              "MOV     R0, R4\n"

              "BL      sub_FFD483A4_my\n"
              "BL      capt_seq_hook_raw_here\n"

             // "BL      sub_FFD483A4\n"

              "MOV     R2, R4\n"
              "MOV     R1, #1\n"
              "BL      sub_FFD43578\n"
              "LDMFD   SP!, {R4,LR}\n"
              "B       sub_FFD4859C\n"
  );
}


void __attribute__((naked,noinline)) capt_seq_task()
{
  asm volatile (
          "STMFD   SP!, {R4,LR}\n"
          "SUB     SP, SP, #4\n"
          "MOV     R4, SP\n"
          "B       loc_FFD455BC\n"
    "loc_FFD45464:\n"
          "LDR     R2, [SP,#0xC-0xC]\n"
          "LDR     R3, [R2]\n"
          "MOV     R0, R2\n"
          "CMP     R3, #0x15\n"
          "LDRLS   PC, [PC,R3,LSL#2]\n"
          "B       loc_FFD45590\n"
          ".long loc_FFD454D4\n"
          ".long loc_FFD454E0\n"
          ".long loc_FFD454E8\n"
          ".long loc_FFD454F8\n"
          ".long loc_FFD454F0\n"
          ".long loc_FFD45500\n"
          ".long loc_FFD45508\n"
          ".long loc_FFD45514\n"
          ".long loc_FFD4551C\n"
          ".long loc_FFD45528\n"
          ".long loc_FFD45530\n"
          ".long loc_FFD45538\n"
          ".long loc_FFD45540\n"
          ".long loc_FFD45548\n"
          ".long loc_FFD45550\n"
          ".long loc_FFD4555C\n"
          ".long loc_FFD45564\n"
          ".long loc_FFD4556C\n"
          ".long loc_FFD45574\n"
          ".long loc_FFD45580\n"
          ".long loc_FFD45588\n"
          ".long loc_FFD455A4\n"
    "loc_FFD454D4:\n"
          "BL      sub_FFD46DB8\n"
          "BL      shooting_expo_param_override\n"   // +
        //  "BL	 handle_is_off\n"
          "BL      sub_FFD4311C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD454E0:\n"
     			//"BL      sub_FFD45048\n"
          "BL      sub_FFD45048_my\n"
					"B       loc_FFD455A0\n"
    "loc_FFD454E8:\n"
          "BL      sub_FFD47150\n"
          "B       loc_FFD455A0\n"
    "loc_FFD454F0:\n"
          "BL      sub_FFD4601C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD454F8:\n" //shooting but. rel.
          "BL      sub_FFD46454\n"
       //   "BL	 handle_is_on\n"            //+
          "B       loc_FFD455A0\n"
    "loc_FFD45500:\n"
          "BL      sub_FFD46464\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45508:\n"
          "BL      sub_FFD46E9C\n"
          "BL      sub_FFD4311C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45514:\n"
          "BL      sub_FFD45154\n"
          "B       loc_FFD455A0\n"
    "loc_FFD4551C:\n"
          "BL      sub_FFD46F04\n"
          "BL      sub_FFD4311C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45528:\n"
          "BL      sub_FFD46454\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45530:\n"
          "BL      sub_FFD476A4\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45538:\n"
          "BL      sub_FFD479E8\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45540:\n"
          "BL      sub_FFD47A6C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45548:\n"
          "BL      sub_FFD47B5C\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45550:\n"
          "MOV     R0, #0\n"
          "BL      sub_FFD47C24\n"
          "B       loc_FFD455A0\n"
    "loc_FFD4555C:\n"
          "BL      sub_FFD47D90\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45564:\n"
          "BL      sub_FFD47E24\n"
          "B       loc_FFD455A0\n"
    "loc_FFD4556C:\n"
          "BL      sub_FFD47EE0\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45574:\n"
          "MOV     R0, #1\n"
          "BL      sub_FFD47C24\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45580:\n"
          "BL      sub_FFD47FCC\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45588:\n"
          "BL      sub_FFD48020\n"
          "B       loc_FFD455A0\n"
    "loc_FFD45590:\n"
          "MOV     R1, #0x36C\n"
          "LDR     R0, =0xFFD44DD4\n"
          "ADD     R1, R1, #1\n"
          "BL      sub_FFC03AE8\n"
    "loc_FFD455A0:\n"
          "LDR     R2, [SP,#0xC-0xC]\n"
    "loc_FFD455A4:\n"
          "LDR     R3, =0x64D64\n"
          "LDR     R1, [R2,#4]\n"
          "LDR     R0, [R3]\n"
          "BL      sub_FFC0F9A8\n"
          "LDR     R0, [SP,#0xC-0xC]\n"
          "BL      sub_FFD44E50\n"
    "loc_FFD455BC:\n"
          "LDR     R3, =0x64D68\n"
          "MOV     R1, R4\n"
          "LDR     R0, [R3]\n"
          "MOV     R2, #0\n"
          "BL      sub_FFC100C0\n"
          "TST     R0, #1\n"
          "BEQ     loc_FFD45464\n"
          "MOV     R1, #0x2A4\n"
          "LDR     R0, =0xFFD44DD4\n"
          "ADD     R1, R1, #3\n"
          "BL      sub_FFC03AE8\n"
          "BL      _ExitTask\n"
          "BL      sub_FFC1161C\n"
          "ADD     SP, SP, #4\n"
          "LDMFD   SP!, {R4,PC}\n"
  );
}
