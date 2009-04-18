#ifndef GUI_DRAW_H
#define GUI_DRAW_H
//-------------------------------------------------------------------

#if CAM_BITMAP_PALETTE==1
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0x11
#define COLOR_RED           0x22
#define COLOR_GREY          0x3F
#define COLOR_GREEN         0x55
#define COLOR_BLUE_LT       0xDD
#define COLOR_BLUE          0xDF
#define COLOR_YELLOW        0xEE
#define COLOR_BLACK         0xFF
//#define COLOR_BG            0x0F
#define COLOR_BG            0x44
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        0xD4
#define COLOR_SPLASH_RED    0x2E
#define COLOR_SPLASH_PINK   0x21
#define COLOR_SPLASH_GREY   0x1F
#elif CAM_BITMAP_PALETTE==2
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0xD3
#define COLOR_RED           0x64
#define COLOR_GREY          0x12
#define COLOR_GREEN         0xC4
#define COLOR_BLUE_LT       0x6A
#define COLOR_BLUE          0x87
#define COLOR_YELLOW        0x44
#define COLOR_BLACK         0xFF
//#define COLOR_BG            0x0F
#define COLOR_BG            0x22 
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        0x22
#define COLOR_SPLASH_RED    0x58
#define COLOR_SPLASH_PINK   0x4C
#define COLOR_SPLASH_GREY   0x16
#else
#error CAM_BITMAP_PALETTE not defined
#endif

#define FONT_WIDTH          8
#define FONT_HEIGHT         16

//-------------------------------------------------------------------
extern unsigned int         screen_width, screen_height, screen_size;
extern unsigned int         screen_buffer_width, screen_buffer_height, screen_buffer_size;

//-------------------------------------------------------------------
void draw_init();
void draw_set_draw_proc(void (*pixel_proc)(unsigned int offset, color cl));

extern color draw_get_pixel(coord x, coord y);

extern void draw_line(coord x1, coord y1, coord x2, coord y2, color cl);

// draw frame
extern void draw_rect(coord x1, coord y1, coord x2, coord y2, color cl);
extern void draw_round_rect(coord x1, coord y1, coord x2, coord y2, color cl);
// color: hi_byte - BG; lo_byte - FG
extern void draw_filled_rect(coord x1, coord y1, coord x2, coord y2, color cl);
extern void draw_filled_round_rect(coord x1, coord y1, coord x2, coord y2, color cl);

extern void draw_char(coord x, coord y, const char ch, color cl);
extern void draw_string(coord x, coord y, const char *s, color cl);

extern void draw_txt_rect(coord col, coord row, unsigned int length, unsigned int height, color cl);
extern void draw_txt_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl);
extern void draw_txt_filled_rect(coord col, coord row, unsigned int length, unsigned int height, color cl);
extern void draw_txt_filled_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl);
extern void draw_txt_string(coord col, coord row, const char *str, color cl);
extern void draw_txt_char(coord col, coord row, const char ch, color cl);

extern void draw_clear();
extern void draw_restore();

extern void draw_fill(coord x, coord y, color cl_fill, color cl_bound);
extern void draw_circle(coord x, coord y, const unsigned int r, color cl);
extern void draw_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl);
extern void draw_filled_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl);


//-------------------------------------------------------------------
#endif
