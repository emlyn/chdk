#include "platform.h"

// SD780/SD1200 - Search for "CRAW BUFF SIZE" and "CrwAddress %lx"
long hook_raw_size()
{
/*
loc_FFCC787C                            ; CODE XREF: sub_FFCC7834+3Cj
ROM:FFCC787C                 LDR     R2, =0xE88
ROM:FFCC7880                 LDR     R1, =0x40F30D7C
ROM:FFCC7884                 SUB     R3, R2, #0x3B4
ROM:FFCC7888                 ADR     R0, aCrwaddressLxCr ;
    " CrwAddress %lx, CrwSize H %ld V %ld\r"
... much later ...
ROM:FFE3A79C                 BL      sub_FFCC8B88
ROM:FFE3A7A0                 LDR     R1, =0xEC04F0
ROM:FFE3A7A4                 ADR     R0, aCrawBuffSizeP ; "CRAW BUFF SIZE  %p"
*/
    // Look at R2 and R3 before the BL.
    // R2 = 0xE88, R3 = 0xE88 - 0x3B4 == 0xAD4
    // And CRAW BUFF SIZE, 0xEC04F0
    // (0xEC04F0 * 8 bits) / 0xE88 / 0xAD4 == 12 bit RAW
    // 3720 x 948
    return 0xEC04F0;
}

//VERIFY_SD780 - - Search for "A/%08x.CRW" and find nearby the hex value found for hook_raw_size.
//VERIFY_SD780 - - Above this is the second value...only value????
//VERIFY_SD1200
char *hook_raw_image_addr()
{
	//VERIFY_SD780 ImgProcBuf 0x2968+0x18????
    //return (char *) 0x40F30D7C;     // SD1200 found at 0xFFD86024
	return (char*) (*(int*)(0x2890) ? 0x424B358C : 0x40F30D7C);
}


//VERIFY_SD780 - Search for ; LOCATION: LiveImage.c:0
    // There are a few. This one has ~4 vars and calls TakeSemaphore early
    // - First LDR (LDR     R4, =0x3F50)
//VERIFY_SD780 - - Find the **fb lower in function.
//VERIFY_SD780 - Original location SD780: 0xFF8B02F4 SD1200: 0xFFC95230
//VERIFY_SD780 - Have doubts...
//VERIFY_SD1200
void *vid_get_viewport_live_fb()
{
    void **fb=(void **)0x40E4; // SD1200 from 0xFFC953B4 Really not sure about this.
    unsigned char buff = *((unsigned char*)0x3F50); // SD1200 from 0xFFC95230
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}


//SD780/SD1200 - - Search for ; LOCATION: BmpDDev.c:138 - First big LDR
//Same on SD780 and SD1200
void *vid_get_bitmap_fb()
{
    return (void*)0x403F1000; // SD1200 from 0xFFCADC08
}


//SD780/SD1200 - - Search for "VRAM Address"
void *vid_get_viewport_fb()
{
    return (void *)0x4076F088; // SD1200 from 0xFFE38210
}

// Search for regex "ADR     R1, _sub_.*__SlideEffect.c
// Go into the sub two jumps above that line.
// SD990/SD1200 is simple. SD780 does more...
/* SD1200
 ROM:FFC41BA8 sub_FFC41BA8                            
 ROM:FFC41BA8                 LDR     R0, =0x2658
 ROM:FFC41BAC                 LDR     R0, [R0,#0x54]
 ROM:FFC41BB0                 BX      LR
 */
void *vid_get_viewport_fb_d()
{
    return (void*)(*(int*)(0x2658 + 0x54));
}


// note real width is 720, report 360 for aspect adjustment
long vid_get_bitmap_screen_width()
{
    return 360;
}

long vid_get_bitmap_screen_height()
{
    return 240;
}

int vid_get_viewport_width()
{
    return 360;
}

long vid_get_viewport_height()
{
    return 240;
}

//SD780 - - Search for "9999", LDR above use of "9999"
char *camera_jpeg_count_str()
{
    return (char *)0x2F1D4;  //SD1200 from 0xFFD57DC0
}

/* SD1200:
 * FFCADBF4                 MOV     R0, #0x2D0 ; 0x2D0 == 720
 * FFCADBF8                 MOV     R1, #0xF0  ;  0xF0 == 240
*/

long vid_get_bitmap_buffer_width() { return 720; }
long vid_get_bitmap_buffer_height() { return 240; }

