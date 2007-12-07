#ifndef FONT_H
#define FONT_H

#include "gui.h"

//-------------------------------------------------------------------
#define FONT_CP_WIN     0
#define FONT_CP_DOS     1

#define  FONT_CP_WIN_1250       0
#define  FONT_CP_WIN_1251       1
#define  FONT_CP_WIN_1252       2
#define  FONT_CP_WIN_1254       3
#define  FONT_CP_WIN_1257       4

//-------------------------------------------------------------------
extern unsigned char current_font[256][16];

//-------------------------------------------------------------------
extern void font_init();
extern void font_set(int codepage);

extern int rbf_load(char *file);
extern void rbf_load_from_8x16(unsigned char font[256][16]);
extern int rbf_font_height();
extern int rbf_char_width(int ch);
extern int rbf_str_width(const char *str);
extern void rbf_set_codepage(int codepage);
extern int rbf_draw_char(int x, int y, int ch, color cl);
extern int rbf_draw_string(int x, int y, const char *str, color cl);
extern int rbf_draw_string_c(int x, int y, const char *str, color cl1, int c, color cl2);
extern int rbf_draw_string_len(int x, int y, int len, const char *str, color cl);
extern int rbf_draw_string_right_len(int x, int y, int len, const char *str, color cl);

//-------------------------------------------------------------------
#endif

