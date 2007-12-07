#include "font.h"
#include "stdlib.h"
#include "codepages.h"
#include "font_8x16_uni.h"

//-------------------------------------------------------------------
#define DEFAULT_SYMBOL          0xFFFD

//-------------------------------------------------------------------
unsigned char current_font[256][16];

//-------------------------------------------------------------------
static int font_find_data (int charcode) {
    int i=0;

    while (font_data[i].charcode != -1) {
        if (font_data[i].charcode == charcode) 
            return i;
        ++i;
    }
    return -1;
}

//-------------------------------------------------------------------
static void font_init_data(const unsigned short *src, int st, int num) {
    int i, n;

    for (i=0; i<num; ++i) {
        n = font_find_data(src[i]);
        if (n==-1) {
            n = font_find_data(DEFAULT_SYMBOL);
        }
        memcpy(current_font[st+i], font_data[n].data, 16);
    }
}

//-------------------------------------------------------------------
void font_init() {
    font_init_data(cp_common, 0, 128);
//    font_init_data(codepages[FONT_CP_WIN_1251], 128, 128);
}

//-------------------------------------------------------------------
void font_set(int codepage) {
    font_init_data(codepages[codepage], 128, 128);
}

//-------------------------------------------------------------------
