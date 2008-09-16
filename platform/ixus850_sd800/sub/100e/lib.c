#include "platform.h"
#include "keyboard.h"

/***********
ROM:FF8EBD04 loc_FF8EBD04                            ; CODE XREF: sub_FF8EBA14+288j
ROM:FF8EBD04                                         ; sub_FF8EBA14+2A8j
ROM:FF8EBD04                 LDR     R5, =unk_4BB44
ROM:FF8EBD08                 MOV     R2, #0
ROM:FF8EBD0C                 MOV     R1, #0x220000
ROM:FF8EBD10                 LDR     R0, [R5]
ROM:FF8EBD14                 BL      unknown_libname_21 ; "Canon A-Series Firmware"
ROM:FF8EBD18                 MOV     R1, #0x220000
ROM:FF8EBD1C                 LDR     R0, [R5]
ROM:FF8EBD20                 BL      ClearEventFlag
ROM:FF8EBD24                 LDR     R3, =unk_4BB5C
ROM:FF8EBD28                 LDR     R2, =0x4BB58 <-- hook_raw_fptr
ROM:FF8EBD2C                 LDR     R0, [R3]
ROM:FF8EBD30                 MOV     LR, PC
ROM:FF8EBD34                 LDR     PC, [R2]
ROM:FF8EBD38                 BL      nullsub_46 <-- hook_raw_ret_addr points here
ROM:FF8EBD3C                 LDR     R3, =unk_5840
***********/

void *hook_raw_fptr()
{
    return (void*)0x4BB58; // find on "taskcreate_ImageSensorTask" 
}

void *hook_raw_ret_addr()
{
    return (void*)0xFF9B8524; // BL      nullsub_46
}

/***********
ROM:FF8E5128                 MOVL    R7, 0x10F00000  ; This plus the 0x600 from below is raw_img_addr
ROM:FF8E5130                 MOV     R3, #0x8C0000
ROM:FF8E5134                 ADD     R7, R7, #0x600
ROM:FF8E5138                 ADD     R3, R3, #0xAE00
ROM:FF8E513C                 ADD     R8, SP, #0x16C+var_168
...
ROM:FF8E5148                 MOV     R2, R7          ; raw_image_addr = 0x10F00600
ROM:FF8E514C                 ADD     R3, R3, #0x10   ; raw_size = 0x8CAE10
***********/

char *hook_raw_image_addr()
{
    return (char*)(0x10F00600);	// 0x10F00000 + 0x600 (find on "A/%08.CRW")
}

long hook_raw_size()
{
    return 0x8CAE10; //7mpx (0x8C0000 + 0xAE00 + 0x10)(find on "A/%08x.CRW")
}

/***************
ROM:FFB19720 loc_FFB19720                            ; CODE XREF: sub_FFB196D4+34j
ROM:FFB19720                 BL      sub_FF8BF204
ROM:FFB19724                 LDR     R2, =0x106571F0
ROM:FFB19728                 MOVL    R3, 0x7E900
ROM:FFB19730                 MOV     R1, R2
ROM:FFB19734                 STMIA   R4, {R2,R3}
ROM:FFB19738                 LDR     R0, =aVramAddressP
ROM:FFB1973C                 BL      sub_FFB0F1E8
ROM:FFB19740                 LDR     R1, [R4,#4]
ROM:FFB19744                 LDR     R0, =aVramSize0xX
ROM:FFB19748                 BL      sub_FFB0F1E8
ROM:FFB1974C                 MOV     R0, #0
ROM:FFB19750                 LDMFD   SP!, {R4-R7,PC}
ROM:FFB19750 ; End of function sub_FFB196D4
ROM:FFB19750
ROM:FFB19750 ; ---------------------------------------------------------------------------
ROM:FFB19754 viewport_fb     DCD 0x106571F0          ; DATA XREF: sub_FFB196D4+50r
ROM:FFB19758 off_FFB19758    DCD aVramAddressP       ; DATA XREF: sub_FFB196D4+64r
ROM:FFB19758                                         ; "VRAM Address  : %p\r"
ROM:FFB1975C off_FFB1975C    DCD aVramSize0xX        ; DATA XREF: sub_FFB196D4+70r
ROM:FFB1975C                                         ; "VRAM Size     : 0x%x\r"

***************/

void *vid_get_viewport_live_fb()
{
//    return (void*)0; // 0x106571F0 + 0x7E900
    void **fb=(void **)0x5564;
    unsigned char buff = *((unsigned char*)0x5574);
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}

/***********
ROM:FF960DC0                 MOVL    R3, 0x10360000
ROM:FF960DC8                 LDR     LR, =unk_67E0
ROM:FF960DCC                 MOV     R12, #0x2D0
ROM:FF960DD0                 MOV     R2, #0xF0 ; '='
ROM:FF960DD4                 ADD     R3, R3, #0x1000
***********/

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;	// 0x10360000 + 0x1000, see after "BmpDDev.c" in sub_FF960E00
}

/***********
ROM:FFB19720                 BL      sub_FF8BF204
ROM:FFB19724                 LDR     R2, =0x106571F0
ROM:FFB19728                 MOVL    R3, 0x7E900
ROM:FFB19730                 MOV     R1, R2
***********/

void *vid_get_viewport_fb()
{
    return (void*)0x106571F0;	// see after "VRAM Address  : %p" in loc_FFB19720
}

/***********
ROM:FF962874                 LDR     R1, =0x89818
ROM:FF962878                 ADD     R3, R3, R3,LSL#2
***********/

void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)0x89818); // see before "ImagePlayer.c" at loc_FF962874
}

long vid_get_bitmap_screen_width()
{
    return 360;
}

long vid_get_bitmap_screen_height()
{
    return 240;
}

long vid_get_viewport_height()
{
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}

/*****************
ROM:FFAA77B4 a9999           DCB "9999",0            ; DATA XREF: ROM:off_FFAA7824o
ROM:FFAA77B9                 DCB    0
ROM:FFAA77BA                 DCB    0
ROM:FFAA77BB                 DCB    0
ROM:FFAA77BC aD_0            DCB "%d",0              ; DATA XREF: ROM:off_FFAA7828o
ROM:FFAA77BF                 DCB    0
ROM:FFAA77C0
ROM:FFAA77C0 ; =============== S U B R O U T I N E =======================================
ROM:FFAA77C0
ROM:FFAA77C0
ROM:FFAA77C0 sub_FFAA77C0                            ; CODE XREF: sub_FFAA79F0+D4p
ROM:FFAA77C0                 MOV     R3, #0x2700
ROM:FFAA77C4                 MOV     R2, R0
ROM:FFAA77C8                 STMFD   SP!, {R4,LR}
ROM:FFAA77CC                 ADD     R3, R3, #0xE
ROM:FFAA77D0                 LDR     R4, =unk_96F80
ROM:FFAA77D4                 CMP     R2, R3
ROM:FFAA77D8                 LDR     R1, =a9999
ROM:FFAA77DC                 MOV     R0, R4
ROM:FFAA77E0                 BLS     loc_FFAA77EC
*****************/

char *camera_jpeg_count_str()
{
    return (char*)0x96F80;
}


long vid_get_bitmap_buffer_width() { return 360; }

long vid_get_bitmap_buffer_height() { return 240; }

void _EnterToCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
void _ExitFromCompensationEVF() {} // Dummy function. To be removed after stub is found. See stubs_entry_2.S.
