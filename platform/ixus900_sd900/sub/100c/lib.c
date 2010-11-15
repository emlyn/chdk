#include "platform.h"
//#include "keyboard.h"

/********** hook_raw_fptr() & hook_raw_ret_addr()
ROM:FF8EB058 loc_FF8EB058
ROM:FF8EB058                 LDR     R5, =0x36344
ROM:FF8EB05C                 MOV     R2, #0
ROM:FF8EB060                 MOV     R1, #0x220000
ROM:FF8EB064                 LDR     R0, [R5]
ROM:FF8EB068                 BL      unknown_libname_21
ROM:FF8EB06C                 MOV     R1, #0x220000
ROM:FF8EB070                 LDR     R0, [R5]
ROM:FF8EB074                 BL      ClearEventFlag
ROM:FF8EB078                 LDR     R3, =0x3635C
ROM:FF8EB07C                 LDR     R2, =0x36358      ; <--- hook_raw_fptr()
ROM:FF8EB080                 LDR     R0, [R3]
ROM:FF8EB084                 MOV     LR, PC
ROM:FF8EB088                 LDR     PC, [R2]
ROM:FF8EB08C                 BL      sub_FF8EABF0      ; <--- hook_raw_ret_addr() points here
ROM:FF8EB090                 LDR     R3, =0x58A4
***********/
// obsolete
/*
void *hook_raw_fptr() {
    return (void*)0x36358;   // ROM:FF8EB07C
}
void *hook_raw_ret_addr() {
    return (void*)0xFF8EB08C;   // ROM:FF8EB08C
}
*/


/*********** hook_raw_image_addr()
search for string "ImgPrcssBuf.c:156", raw buffer table is right above sub

ROM:FF99865C                 LDR     LR, =0xFF9985B8   ; <--- raw buffer table
ROM:FF998660                 LDR     R3, =0x6BC0
ROM:FF998664                 LDR     R2, =0x6BC4       ; <---

ROM:FF9985B8 raw_buffer_table
...
ROM:FF9985D8                 DCD 0x113D38D2
ROM:FF9985DC                 DCD 0x1082C320            ; <---
ROM:FF9985E0                 DCD 0x1088B440
ROM:FF9985E4                 DCD 0x1278AE32
ROM:FF9985E8                 DCD 0x11BE3880            ; <---
ROM:FF9985EC                 DCD 0x114D36C0
***********/
char *hook_raw_image_addr() {
    // return (char*)(0x1082C320);   // 0x1082C000 + 0x320 does not work
    return (char*)(*(int*)0x6BC4 ? 0x11BE3880 : 0x1082C320);    // looks like SD900 has volatile RAW buffer like G7 / G9 / A650
}

/*********** hook_raw_size()
look near string "A/%08x.CRW"

ROM:FF8E41CC                 MOVL    R7, 0x1082C000
ROM:FF8E41D4                 MOV     R3, #0xC50000     ; <---
ROM:FF8E41D8                 ADD     R7, R7, #0x320
ROM:FF8E41DC                 ADD     R3, R3, #0x8700   ; <---

ROM:FF8E41EC                 MOV     R2, R7
ROM:FF8E41F0                 ADD     R3, R3, #0x58     ; <---

or

ROM:FFB15300                 MOV     R1, 0xC58758
ROM:FFB1530C                 LDR     R0, =aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
***********/
long hook_raw_size() {
    return 0xC58758;   // 0xC50000 + 0x8700 + 0x58
}

/*********** vid_get_bitmap_fb()
look near string "BmpDDev.c"

ROM:FF95A884                 MOV     R3, #0x10000000   ; <---
ROM:FF95A888                 ADD     R3, R3, #0x360000   ; <---
ROM:FF95A88C                 ADD     R3, R3, #0x1000   ; <---
ROM:FF95A890                 CMP     R0, R3
ROM:FF95A894                 STR     LR, [SP,#-4]!
ROM:FF95A898                 MOV     R2, #0
ROM:FF95A89C                 MOV     R1, #0xF6
ROM:FF95A8A0                 LDR     R0, =aBmpddev_c
***********/
void *vid_get_bitmap_fb() {
    return (void*)0x10361000;   // 0x10000000 + 0x360000 + 0x1000 , same as SD800 / SD1000
}

/*********** vid_get_viewport_live_fb()
OLD !!!

ROM:FFB133D8 loc_FFB133D8
ROM:FFB133D8                 BL      sub_FF8BE30C
ROM:FFB133DC                 LDR     R2, =0x1065B130   ; <--- this plus below
ROM:FFB133E0                 MOVL    R3, 0x8B380       ; <---
ROM:FFB133E8                 MOV     R1, R2
ROM:FFB133EC                 STMIA   R4, {R2,R3}
ROM:FFB133F0                 LDR     R0, =aVramAddressP
ROM:FFB133F4                 BL      sub_FFB08E8C
ROM:FFB133F8                 LDR     R1, [R4,#4]
ROM:FFB133FC                 LDR     R0, =aVramSize0xX
ROM:FFB13400                 BL      sub_FFB08E8C
ROM:FFB13404                 MOV     R0, #0
ROM:FFB13408                 LDMFD   SP!, {R4-R7,PC}
***********/
/*
void *vid_get_viewport_live_fb() {   // live picture buffer (shoot not pressed)
    return (void*)0x106E64B0;   // 0x1065B130 + 0x8B380
}
*/

/*********** vid_get_viewport_live_fb()
ROM:FF8BB124 loc_FF8BB124
ROM:FF8BB124                 LDR     R3, =0x55D4   ; <---
ROM:FF8BB128                 LDR     R2, =0x55BC   ; <---
ROM:FF8BB12C                 LDRB    R0, [R3]
ROM:FF8BB130                 LDR     R1, [R2,R0,LSL#2]
ROM:FF8BB134                 MOV     R0, #0
ROM:FF8BB138                 BL      loc_FF88E5D4
***********/
void *vid_get_viewport_live_fb() {   // live picture buffer (shoot not pressed)
    //return (void*)0x106E64B0;   // 0x1065B130 + 0x8B380
    void **fb = (void **)0x55BC;
    unsigned char buff = *((unsigned char*)0x55D4);
    if(buff == 0) {
        buff = 2;
    } else {
        buff--;
    }
    return fb[buff];
}

/*********** vid_get_viewport_fb
look near string "VRAM Address  : %p"

ROM:FFB133D8 loc_FFB133D8
ROM:FFB133D8                 BL      sub_FF8BE30C
ROM:FFB133DC                 LDR     R2, =0x1065B130   ; <---
ROM:FFB133E0                 MOVL    R3, 0x8B380
ROM:FFB133E8                 MOV     R1, R2
ROM:FFB133EC                 STMIA   R4, {R2,R3}
ROM:FFB133F0                 LDR     R0, =aVramAddressP
ROM:FFB133F4                 BL      sub_FFB08E8C
ROM:FFB133F8                 LDR     R1, [R4,#4]
ROM:FFB133FC                 LDR     R0, =aVramSize0xX
ROM:FFB13400                 BL      sub_FFB08E8C
ROM:FFB13404                 MOV     R0, #0
ROM:FFB13408                 LDMFD   SP!, {R4-R7,PC}
***********/
void *vid_get_viewport_fb() {   // live picture buffer (shoot half-pressed)
    return (void*)0x1065B130;   // ROM:FFB133DC
}

/*********** vid_get_viewport_fb_d()
look near string "ImagePlayer.c"

ROM:FF95C314                 LDR     R1, =0x74028    ; <---
ROM:FF95C318                 ADD     R3, R3, R3,LSL#2
***********/
void *vid_get_viewport_fb_d() {   // picture buffer (play mode)
    return (void*)(*(int*)0x74028);   // ROM:FF95C354
}

long vid_get_bitmap_screen_width() {
    return 360;
}

long vid_get_bitmap_screen_height() {
    return 240;
}

long vid_get_viewport_height() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:230;
}

/*********** camera_jpeg_count_str()
search for DCB "9999",0

ROM:FFAA77B0 dword_FFAA77B0  DCD 0x98E0
ROM:FFAA7130 a9999           DCB "9999",0
ROM:FFAA7135                 DCB    0
ROM:FFAA7136                 DCB    0
ROM:FFAA7137                 DCB    0
ROM:FFAA7138 aD_0            DCB "%d",0
ROM:FFAA713B                 DCB    0
ROM:FFAA713C sub_FFAA713C
ROM:FFAA713C                 MOV     R3, #0x2700
ROM:FFAA7140                 MOV     R2, R0
ROM:FFAA7144                 STMFD   SP!, {R4,LR}
ROM:FFAA7148                 ADD     R3, R3, #0xE
ROM:FFAA714C                 LDR     R4, =0x818C8      ; <---
ROM:FFAA7150                 CMP     R2, R3
ROM:FFAA7154                 LDR     R1, =a9999
ROM:FFAA7158                 MOV     R0, R4
ROM:FFAA715C                 BLS     loc_FFAA7168
ROM:FFAA7160                 BL      sprintf
ROM:FFAA7164                 B       loc_FFAA7178
***********/
char *camera_jpeg_count_str() {
    return (char*)0x818C8;   // ROM:FFAA714C
}

long vid_get_bitmap_buffer_width() {
    return 360;
}

long vid_get_bitmap_buffer_height() {
    return 240;
}
