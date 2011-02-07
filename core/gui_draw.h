#ifndef GUI_DRAW_H
#define GUI_DRAW_H
//-------------------------------------------------------------------

// Moved from gui_bench.c, gui_debug.c, gui_calendar.c, gui_reversi.c & gui_sokoban.c so it can be overridden
// Default value is white in SX30 & G12 palette making white text hard to read
#define SCREEN_COLOR            0xF7

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
#define COLOR_BG            0x44
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        0xD4
#define COLOR_SPLASH_RED    0x2E
#define COLOR_SPLASH_PINK   0x21
#define COLOR_SPLASH_GREY   0x1F
// colors for blended histo
#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_RED
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_GREEN
#define COLOR_HISTO_BG      COLOR_BLUE_LT
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RB      0x66
#define COLOR_HISTO_RB_PLAY 0xE2
#define COLOR_HISTO_B_PLAY  0xCC
#define COLOR_HISTO_BG_PLAY 0x99
#define COLOR_HISTO_RG_PLAY 0x66
#elif CAM_BITMAP_PALETTE==2 // sd990
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0xD3
#define COLOR_RED           0x64
#define COLOR_GREY          0x12
#define COLOR_GREEN         0xC4
#define COLOR_BLUE_LT       0x6A
#define COLOR_BLUE          0x87
#define COLOR_YELLOW        0x44
#define COLOR_BLACK         0xFF
#define COLOR_BG            0x22 
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        0x22
#define COLOR_SPLASH_RED    0x58
#define COLOR_SPLASH_PINK   0x4C
#define COLOR_SPLASH_GREY   0x16
// colors for blended histo 
// many of these probably wrong on this cam
#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_RED
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_GREEN
#define COLOR_HISTO_BG      COLOR_BLUE_LT
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RB      0x66
#define COLOR_HISTO_RB_PLAY 0xE2
#define COLOR_HISTO_B_PLAY  0xCC
#define COLOR_HISTO_BG_PLAY 0x99
#define COLOR_HISTO_RG_PLAY 0x66
#elif CAM_BITMAP_PALETTE==3 // sx200
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0x01
#define COLOR_RED           0x2B
#define COLOR_GREY          0x17
#define COLOR_GREEN         0x99
#define COLOR_BLUE_LT       0x2D
#define COLOR_BLUE          0x3B
#define COLOR_YELLOW        0x9A
#define COLOR_BLACK         0xFF
#define COLOR_BG            0x81
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        COLOR_GREY
#define COLOR_SPLASH_RED    0x29
#define COLOR_SPLASH_PINK   0x1E
#define COLOR_SPLASH_GREY   0x16
// colors for blended histo
#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_HISTO_R
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_HISTO_G
#define COLOR_HISTO_BG      COLOR_BLUE_LT
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RB      COLOR_BLACK // there isn't purplish on this cam I guess
#define COLOR_HISTO_RB_PLAY COLOR_HISTO_RB
#define COLOR_HISTO_B_PLAY  COLOR_HISTO_B
#define COLOR_HISTO_BG_PLAY COLOR_BLUE_LT
#define COLOR_HISTO_RG_PLAY COLOR_YELLOW
#elif CAM_BITMAP_PALETTE==4 // g11
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0x01
#define COLOR_RED           0x2B
#define COLOR_GREY          0x17
#define COLOR_GREEN         0x99
#define COLOR_BLUE_LT       0xA9
#define COLOR_BLUE          0xA1
#define COLOR_YELLOW        0x9A
#define COLOR_BLACK         0xFF
#define COLOR_BG            0x61
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        COLOR_GREY
#define COLOR_SPLASH_RED    0x29
#define COLOR_SPLASH_PINK   0x1E
#define COLOR_SPLASH_GREY   0x16
// colors for blended histo
#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_HISTO_R
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_HISTO_G
#define COLOR_HISTO_BG      COLOR_BLUE_LT
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RB      COLOR_BLACK // there isn't purplish on this cam I guess
#define COLOR_HISTO_RB_PLAY COLOR_HISTO_RB
#define COLOR_HISTO_B_PLAY  COLOR_HISTO_B
#define COLOR_HISTO_BG_PLAY COLOR_BLUE_LT
#define COLOR_HISTO_RG_PLAY COLOR_YELLOW
#elif CAM_BITMAP_PALETTE==5 //(Based on sd990)
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0xD3
#define COLOR_RED           0x6A
#define COLOR_GREY          0x12
#define COLOR_GREEN         0xBF
#define COLOR_BLUE_LT       0x7C
#define COLOR_BLUE          0x90
#define COLOR_YELLOW        0x53
#define COLOR_BLACK         0xFF
#define COLOR_BG            0x22
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        0x22
#define COLOR_SPLASH_RED    0x72
#define COLOR_SPLASH_PINK   0x5C
#define COLOR_SPLASH_GREY   0x16
#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_RED
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_GREEN
#define COLOR_HISTO_BG      COLOR_BLUE_LT
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RB      0x72
#define COLOR_HISTO_RB_PLAY COLOR_HISTO_RB
#define COLOR_HISTO_B_PLAY  COLOR_HISTO_B
#define COLOR_HISTO_BG_PLAY COLOR_BLUE_LT
#define COLOR_HISTO_RG_PLAY COLOR_YELLOW
#elif CAM_BITMAP_PALETTE==6 //(sx20)
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0x01
#define COLOR_RED           0x2B
#define COLOR_GREY          0x0F
#define COLOR_GREEN         0xA9
#define COLOR_BLUE_LT       0x2D
#define COLOR_BLUE          0x3B
#define COLOR_YELLOW        0x8B
#define COLOR_BLACK         0xFF
#define COLOR_BG            0xFE
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   COLOR_RED
#define COLOR_SELECTED_FG   COLOR_WHITE
#define COLOR_ALT_BG        COLOR_BG
#define COLOR_SPLASH_RED    COLOR_RED
#define COLOR_SPLASH_PINK   0xEA
#define COLOR_SPLASH_GREY   0x16
#define COLOR_HISTO_R       COLOR_RED
#define COLOR_HISTO_R_PLAY  COLOR_RED
#define COLOR_HISTO_B       COLOR_BLUE
#define COLOR_HISTO_G       COLOR_GREEN
#define COLOR_HISTO_G_PLAY  COLOR_GREEN
#define COLOR_HISTO_BG      COLOR_BLUE_LT
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RB      COLOR_RED
#define COLOR_HISTO_RB_PLAY COLOR_HISTO_RB
#define COLOR_HISTO_B_PLAY  COLOR_HISTO_B
#define COLOR_HISTO_BG_PLAY COLOR_BLUE_LT
#define COLOR_HISTO_RG_PLAY COLOR_YELLOW
#elif CAM_BITMAP_PALETTE==7 //(sx30, g12)
#define COLOR_TRANSPARENT   0x00
#define COLOR_WHITE         0x01
#define COLOR_RED           0x1e
#define COLOR_GREY          0x1a
#define COLOR_GREEN         0x17
#define COLOR_BLUE_LT       0x10
#define COLOR_BLUE          0x14
#define COLOR_YELLOW        0x16
#define COLOR_BLACK         0x1d
#define COLOR_BG            0x62
#define COLOR_FG            COLOR_WHITE
#define COLOR_SELECTED_BG   0x0e
#define COLOR_SELECTED_FG   COLOR_BLACK
#define COLOR_ALT_BG        COLOR_BG
#define COLOR_SPLASH_RED    COLOR_RED
#define COLOR_SPLASH_PINK   0x1e			// Orange
#define COLOR_SPLASH_GREY   0x16
#define COLOR_HISTO_R       0x66
#define COLOR_HISTO_R_PLAY  0xA0
#define COLOR_HISTO_B       0x61
#define COLOR_HISTO_B_PLAY  0xA2
#define COLOR_HISTO_G       0x5F
#define COLOR_HISTO_G_PLAY	0xA1
#define COLOR_HISTO_BG      COLOR_BLUE_LT
#define COLOR_HISTO_RG      COLOR_YELLOW
#define COLOR_HISTO_RB      COLOR_RED
#define COLOR_HISTO_RB_PLAY COLOR_HISTO_RB
#define COLOR_HISTO_BG_PLAY COLOR_BLUE_LT
#define COLOR_HISTO_RG_PLAY COLOR_YELLOW
#undef SCREEN_COLOR
#define SCREEN_COLOR            0x1D
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


#if CAM_USES_ASPECT_CORRECTION //nandoide sept-2009 
void draw_set_aspect_xcorrection_proc(unsigned int (*xcorrection_proc)(unsigned int x));
void draw_set_aspect_ycorrection_proc(unsigned int (*ycorrection_proc)(unsigned int y));
unsigned int aspect_xcorrection_games_360(unsigned int x);
unsigned int aspect_ycorrection_games_360(unsigned int y);
void draw_set_environment(unsigned int (*xcorrection_proc)(unsigned int x), 
                                       unsigned int (*ycorrection_proc)(unsigned int y),
                                       int screenx, int screeny );
#endif

//-------------------------------------------------------------------
#endif
