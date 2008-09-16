#include "stdlib.h"
#include "gui.h"
#include "font.h"
#include "../../core/gui_draw.h"
#include "../../include/conf.h"

//-------------------------------------------------------------------
#define RBF_HDR_SIZE       0x74
#define RBF_MAX_NAME       64

//-------------------------------------------------------------------
static const char *RBF_HDR_MAGIC = "\xE0\x0E\xF0\x0D\x03\x00\x00\x00";

static const char tbl_dos2win[] = {
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0x2D, 0x2D, 0x2D, 0xA6, 0x2B, 0xA6, 0xA6, 0xAC, 0xAC, 0xA6, 0xA6, 0xAC, 0x2D, 0x2D, 0x2D, 0xAC,
    0x4C, 0x2B, 0x54, 0x2B, 0x2D, 0x2B, 0xA6, 0xA6, 0x4C, 0xE3, 0xA6, 0x54, 0xA6, 0x3D, 0x2B, 0xA6,
    0xA6, 0x54, 0x54, 0x4C, 0x4C, 0x2D, 0xE3, 0x2B, 0x2B, 0x2D, 0x2D, 0x2D, 0x2D, 0xA6, 0xA6, 0x2D,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
    0xA8, 0xB8, 0xAA, 0xBA, 0xAF, 0xBF, 0xA1, 0xA2, 0xB0, 0x95, 0xB7, 0x76, 0xB9, 0xA4, 0xA6, 0xA0
};

static struct font {
     char name[RBF_MAX_NAME];
     int width, height;
     int points;
     int intline;
     int charFirst, charCount;
     char wTable[256];
     char *cTable[256];
     int maxWidth;
     int descent;
     int charLast;
     int charSize;
     int _wmapAddr;
     int _cmapAddr;
     int _unknown4;
} rbf_symbol_font, rbf_font;
static int need_free    = 0;
static int rbf_codepage = FONT_CP_WIN; 

//-------------------------------------------------------------------
static int dos2win(int ch) {
    if (ch<0x80) return ch;
    else         return tbl_dos2win[ch-0x80];
}

//-------------------------------------------------------------------
int rbf_load(char *file) {
/*
    name         - name of font (max 64 characters)
    width        - font element width in pixels
    height       - font element height in pixels
    points       - font size in points
    charFirst    - ASCII code of first char, presents in font
    charCount    - count of chars containing in font
    cTable       - List of chars. Element of list is a bytecode string,
                   contains pixels representation  of char
    wTable       - List of character widths. Elements of list
                   is width of char 
    intline      - Interline spasing
    maxWidth     - width of widhest char in pixels
    descent      - font descent
    '''
*/        

    int fd;
    char buf[8];
    int i;

    fd = open(file, O_RDONLY, 0777);
    if (fd>=0 && read(fd, &buf, 8)==8 /* Magic number */ && memcmp(&buf, RBF_HDR_MAGIC, 8)==0) {

        read(fd, &rbf_font.name, RBF_MAX_NAME);
        read(fd, &rbf_font.charSize , 4);
        read(fd, &rbf_font.points   , 4);
        read(fd, &rbf_font.height   , 4);
        read(fd, &rbf_font.maxWidth , 4);
        read(fd, &rbf_font.charFirst, 4);
        read(fd, &rbf_font.charLast , 4);
        read(fd, &rbf_font._unknown4, 4);
        read(fd, &rbf_font._wmapAddr, 4);
        read(fd, &rbf_font._cmapAddr, 4);
        read(fd, &rbf_font.descent  , 4);
        read(fd, &rbf_font.intline  , 4);

        rbf_font.width = 8 * rbf_font.charSize / rbf_font.height;
        rbf_font.charCount = rbf_font.charLast - rbf_font.charFirst + 1;

        for (i=0; i<256; ++i) {
            rbf_font.wTable[i]=0; 
            if (need_free && rbf_font.cTable[i]) {
                free(rbf_font.cTable[i]);
            }
            rbf_font.cTable[i]=NULL;
        }
        need_free = 0;

        lseek(fd, rbf_font._wmapAddr, SEEK_SET);
        for (i=rbf_font.charFirst; i<=rbf_font.charLast; ++i) {
            read(fd, &rbf_font.wTable[i], 1);
        }

        lseek(fd, rbf_font._cmapAddr, SEEK_SET);
        for (i=rbf_font.charFirst; i<=rbf_font.charLast; ++i) {
            rbf_font.cTable[i]=malloc(rbf_font.charSize);
            read(fd, rbf_font.cTable[i], rbf_font.charSize);
        }
        need_free = 1;

        close(fd);
        conf.menu_symbol_enable=(rbf_font.height>=rbf_symbol_font.height);
        return 1;
    }

    return 0;
}

//-------------------------------------------------------------------
#define maxSymbols 128
int rbf_load_symbol(char *file) {

    int fd;
    char buf[8];
    int i;

    fd = open(file, O_RDONLY, 0777);
    if (fd>=0 && read(fd, &buf, 8)==8 /* Magic number */ && memcmp(&buf, RBF_HDR_MAGIC, 8)==0) {

        read(fd, &rbf_symbol_font.name, RBF_MAX_NAME);
        read(fd, &rbf_symbol_font.charSize , 4);
        read(fd, &rbf_symbol_font.points   , 4);
        read(fd, &rbf_symbol_font.height   , 4);
        read(fd, &rbf_symbol_font.maxWidth , 4);
        read(fd, &rbf_symbol_font.charFirst, 4);
        read(fd, &rbf_symbol_font.charLast , 4);
        read(fd, &rbf_symbol_font._unknown4, 4);
        read(fd, &rbf_symbol_font._wmapAddr, 4);
        read(fd, &rbf_symbol_font._cmapAddr, 4);
        read(fd, &rbf_symbol_font.descent  , 4);
        read(fd, &rbf_symbol_font.intline  , 4);

        rbf_symbol_font.width = 8 * rbf_symbol_font.charSize / rbf_symbol_font.height;
        rbf_symbol_font.charLast=maxSymbols+32;
        rbf_symbol_font.charCount = rbf_symbol_font.charLast - rbf_symbol_font.charFirst + 1;

        for (i=0; i<maxSymbols; ++i) {
            rbf_symbol_font.wTable[i]=0; 
            if (need_free && rbf_symbol_font.cTable[i]) {
                free(rbf_symbol_font.cTable[i]);
            }
            rbf_symbol_font.cTable[i]=NULL;
        }
        need_free = 0;

        lseek(fd, rbf_symbol_font._wmapAddr, SEEK_SET);
        for (i=rbf_symbol_font.charFirst; i<=rbf_symbol_font.charLast; ++i) {
            read(fd, &rbf_symbol_font.wTable[i], 1);
        }

        lseek(fd, rbf_symbol_font._cmapAddr, SEEK_SET);
        for (i=rbf_symbol_font.charFirst; i<=rbf_symbol_font.charLast; ++i) {
            rbf_symbol_font.cTable[i]=malloc(rbf_symbol_font.charSize);
            read(fd, rbf_symbol_font.cTable[i], rbf_symbol_font.charSize);
        }
        need_free = 1;

        close(fd);
        conf.menu_symbol_enable=(rbf_font.height>=rbf_symbol_font.height);
        return 1;
    }

    return 0;
}

//-------------------------------------------------------------------
static void rbf_assign_char_8x16(char **dst, char *font_ch, int height) {
    int c, b;

    *dst=malloc(height);
    for (c=0; c<height; ++c) {
        (*dst)[c]=0;
        for (b=0; b<8; ++b)
            (*dst)[c]=((*dst)[c]<<1)|(((font_ch[c])>>b)&1);
    }
}

//-------------------------------------------------------------------
void rbf_load_from_8x16(unsigned char font[256][16]) {
    int i, c, b;

    rbf_font.charSize  = 16;
    rbf_font.height    = 16;
    rbf_font.maxWidth  = 8;
    rbf_font.charFirst = 0;
    rbf_font.charLast  = 255;

    rbf_font.width = 8 * rbf_font.charSize / rbf_font.height;
    rbf_font.charCount = rbf_font.charLast - rbf_font.charFirst + 1;

    for (i=0; i<256; ++i) {
        rbf_font.wTable[i]=8; 
        if (need_free && rbf_font.cTable[i]) {
            free(rbf_font.cTable[i]);
        }
        rbf_font.cTable[i]=NULL;
    }
    need_free = 0;
    
    for (i=0; i<256; ++i) {
        rbf_assign_char_8x16(&rbf_font.cTable[i], font[i], rbf_font.height);
    }
    need_free = 1;
}

//-------------------------------------------------------------------
void rbf_set_codepage(int codepage) {
    rbf_codepage = codepage;
}

//-------------------------------------------------------------------
int rbf_font_height() {
    return rbf_font.height;
}
//-------------------------------------------------------------------
int rbf_symbol_height() {
    return rbf_symbol_font.height;
}

//-------------------------------------------------------------------
int rbf_char_width(int ch) {
    switch (rbf_codepage) {
        case FONT_CP_WIN: 
            break;
        case FONT_CP_DOS: 
            ch = dos2win(ch); 
            break;
    }
    return rbf_font.wTable[ch];
}

//-------------------------------------------------------------------
int rbf_symbol_width(int ch) {
    return rbf_symbol_font.wTable[ch];
}

//-------------------------------------------------------------------
int rbf_str_width(const char *str) {
    int l=0;

    while (*str)
        l+=rbf_char_width(*str++);

    return l;
}

//-------------------------------------------------------------------
int rbf_draw_char(int x, int y, int ch, color cl) {
    int xx, yy;

    switch (rbf_codepage) {
        case FONT_CP_WIN: 
            break;
        case FONT_CP_DOS: 
            ch = dos2win(ch); 
            break;
    }

    if (rbf_font.cTable[ch]) {
        for (yy=0; yy<rbf_font.height; ++yy) {
            for (xx=0; xx<rbf_font.wTable[ch]; ++xx) {
                draw_pixel(x+xx ,y+yy, (rbf_font.cTable[ch][yy*rbf_font.width/8+xx/8] & (1<<(xx%8)))? cl&0xff : cl>>8);
            }
        }
    }
    return rbf_font.wTable[ch];
}

//-------------------------------------------------------------------
int rbf_draw_symbol(int x, int y, int ch, color cl) {
    int xx, yy, space=0;

    if (rbf_font.height<rbf_symbol_font.height || ch==0x0) return 0;
    if (rbf_symbol_font.cTable[ch]) {
      if (rbf_font.height>rbf_symbol_font.height) {
        space=(rbf_font.height-rbf_symbol_font.height)/2;
        draw_filled_rect(x, y, x+rbf_symbol_width(ch), y+space, MAKE_COLOR(cl>>8, cl>>8));
        y+=space;
      }
      for (yy=0; yy<rbf_symbol_font.height; ++yy) {
        for (xx=0; xx<rbf_symbol_font.wTable[ch]; ++xx) {
          draw_pixel(x+xx ,y+yy, (rbf_symbol_font.cTable[ch][yy*rbf_symbol_font.width/8+xx/8] & (1<<(xx%8)))? cl&0xff : cl>>8);
        }
      }
      if (rbf_font.height>rbf_symbol_font.height) draw_filled_rect(x, y+yy, x+rbf_symbol_width(ch), y-space+rbf_font.height-1, MAKE_COLOR(cl>>8, cl>>8));
    }
    return rbf_symbol_font.wTable[ch];
}

//-------------------------------------------------------------------
int rbf_draw_string(int x, int y, const char *str, color cl) {
    int l=0;

    while (*str)
        l+=rbf_draw_char(x+l, y, *str++, cl);

    return l;
}

//-------------------------------------------------------------------
// Draw a string colored 'c1' with the character at string-position 'c' colored 'c2'.
int rbf_draw_string_c(int x, int y, const char *str, color c1, int c, color c2) {
     int l=0, i=0;

     while (*str) {
          l+=rbf_draw_char(x+l, y, *str++, (i==c)?c2:c1);
          ++i;
     }
     return l;
}

//-------------------------------------------------------------------
int rbf_draw_string_len(int x, int y, int len, const char *str, color cl) {
    int l=0, yy;

    while (*str && l+rbf_char_width(*str)<=len)
        l+=rbf_draw_char(x+l, y, *str++, cl);

    for (; l<len; ++l) {
        for (yy=y; yy<y+rbf_font.height; ++yy) {
            draw_pixel(x+l, yy, cl>>8);
        }
    }

    return l;
}

//-------------------------------------------------------------------
int rbf_draw_string_right_len(int x, int y, int len, const char *str, color cl) {
    int l=0, i, yy;
    const char *s=str;

    while (*s && l+rbf_char_width(*s)<=len)
        l+=rbf_char_width(*s++);
    l=len-l;

    for (i=l-1; i>=0; --i) {
        for (yy=y; yy<y+rbf_font.height; ++yy) {
            draw_pixel(x+i, yy, cl>>8);
        }
    }

    while (*str && l+rbf_char_width(*str)<=len)
        l+=rbf_draw_char(x+l, y, *str++, cl);

    return l;
}
//-------------------------------------------------------------------
int rbf_draw_string_center_len(int x, int y, int len, char symbol, const char *str, color cl) { 
    int l=0, strLen=0, i, yy, rund=2; 
    const char *s=str; 

    while (*s && l+rbf_char_width(*s)<=len) 
        l+=rbf_char_width(*s++);
    if (symbol!=0x0 && rbf_font_height()>=rbf_symbol_height()) strLen=l+rbf_symbol_width(symbol); else strLen=l;
    l=(len-strLen)/2; 

    for (i=0; i<=l; i++) {
        for (yy=y+rund; yy<y+rbf_font.height; ++yy) {
            draw_pixel(x+i, yy, cl>>8);
            draw_pixel(x+len-i-1, yy, cl>>8);
        }
        if (rund>0) rund--;
    }
    if (symbol!=0x0 && conf.menu_symbol_enable) {
      l+=rbf_draw_symbol(x+l,y,symbol,cl);
      l+=rbf_draw_char(x+l, y, ' ', cl);
    }
    while (*str && l+rbf_char_width(*str)<=len) 
        l+=rbf_draw_char(x+l, y, *str++, cl); 

    return l; 
} 
//-------------------------------------------------------------------
