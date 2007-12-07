#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "lang.h"
#include "ubasic.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_palette.h"

//-------------------------------------------------------------------
static volatile int full_palette;
static color cl;
static volatile char counter;
static int palette_mode;
static void (*palette_on_select)(color clr);
static int gui_palette_redraw;

#define COUNTER_N 100

//-------------------------------------------------------------------
void gui_palette_init(int mode, color st_color, void (*on_select)(color clr)) {
    full_palette = (mode!=PALETTE_MODE_SELECT);
    cl = st_color;
    palette_mode = mode;
    palette_on_select = on_select;
    counter = COUNTER_N;
    gui_palette_redraw = 1;
}

//-------------------------------------------------------------------
void gui_palette_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
    case KEY_DOWN:
    	if (!full_palette) {
            cl = ((((cl>>4)+1)<<4)|(cl&0x0f))&0xFF;
            gui_palette_redraw = 1;
        }
        break;
    case KEY_UP:
    	if (!full_palette) {
            cl = ((((cl>>4)-1)<<4)|(cl&0x0f))&0xFF;
            gui_palette_redraw = 1;
        }
        break;
    case KEY_LEFT:
    	if (!full_palette) {
            cl = ((((cl&0x0f)-1)&0x0f)|(cl&0xf0))&0xFF;
            gui_palette_redraw = 1;
        }
        break;
    case KEY_RIGHT:
    	if (!full_palette) {
            cl = ((((cl&0x0f)+1)&0x0f)|(cl&0xf0))&0xFF;
            gui_palette_redraw = 1;
        }
        break;
    case KEY_SET:
        if (palette_mode!=PALETTE_MODE_SELECT) {
            full_palette = !full_palette;
            counter = 0;
            gui_palette_redraw = 1;
        } else {
            if (palette_on_select) 
                palette_on_select(cl);
           gui_set_mode(GUI_MODE_MENU);
        }
        break;
    }
}

//-------------------------------------------------------------------
void gui_palette_draw() {
    unsigned int x, y;
    char f=0;
    color c;
    static char buf[64];

    switch (palette_mode) {
        case PALETTE_MODE_DEFAULT:
            if (full_palette) {
                if (!counter || counter == COUNTER_N) {
                    for (y=0; y<screen_height; ++y) {
                        for (x=0; x<screen_width; ++x) {
                            c = ((y*16/screen_height)<<4)|(x*16/screen_width);
                            draw_pixel(x, y, c);
                        }
                    }
                    if (counter) {
                        draw_txt_string(6, 7, lang_str(LANG_PALETTE_TEXT_1), MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
                        draw_txt_string(6, 8, lang_str(LANG_PALETTE_TEXT_2), MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
                    }
                }
                if (counter)
                    --counter;
                f=1;
            }
            
            if (!full_palette) {
                sprintf(buf, " %s: 0x%02X ", lang_str(LANG_PALETTE_TEXT_COLOR), cl);
                draw_txt_string(0, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
                draw_filled_rect(20, 20, screen_width-20, screen_height-20, MAKE_COLOR(cl, COLOR_WHITE));
                sprintf(buf, lang_str(LANG_PALETTE_TEXT_SELECT_COLOR), "\x18\x19\x1b\x1a");
                draw_txt_string(0, 14, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            }
            break;
        case PALETTE_MODE_SELECT:
            if (gui_palette_redraw) {
                #define CELL_SIZE   13
                #define BORDER_SIZE 8
                #define CELL_ZOOM   5
                draw_string(screen_width-29*FONT_WIDTH, 0, "    Use \x18\x19\x1b\x1a to change color ", MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
                sprintf(buf, " %s: 0x%02hX    ", lang_str(LANG_PALETTE_TEXT_COLOR), (unsigned char)cl);
                draw_txt_string(0, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
                for (y=0; y<16; ++y) {
                    for (x=0; x<16; ++x) {
                        c = (y<<4)|x;
                        draw_filled_rect(BORDER_SIZE+x*CELL_SIZE, BORDER_SIZE+y*CELL_SIZE+FONT_HEIGHT, BORDER_SIZE+(x+1)*CELL_SIZE, BORDER_SIZE+(y+1)*CELL_SIZE+FONT_HEIGHT, MAKE_COLOR(c, COLOR_BLACK));
                    }
                }
                draw_filled_rect(0, FONT_HEIGHT, screen_width-1, FONT_HEIGHT+BORDER_SIZE-1, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); //top
                draw_filled_rect(0, FONT_HEIGHT+BORDER_SIZE+16*CELL_SIZE+1, screen_width-1, FONT_HEIGHT+BORDER_SIZE+16*CELL_SIZE+BORDER_SIZE, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); //bottom
                draw_filled_rect(0, FONT_HEIGHT+BORDER_SIZE, BORDER_SIZE-1, FONT_HEIGHT+BORDER_SIZE+16*CELL_SIZE, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); //left
                draw_filled_rect(BORDER_SIZE+16*CELL_SIZE+1, FONT_HEIGHT+BORDER_SIZE, BORDER_SIZE+16*CELL_SIZE+BORDER_SIZE, FONT_HEIGHT+BORDER_SIZE+16*CELL_SIZE, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); //middle
                draw_filled_rect(screen_width-BORDER_SIZE, FONT_HEIGHT+BORDER_SIZE, screen_width-1, FONT_HEIGHT+BORDER_SIZE+16*CELL_SIZE, MAKE_COLOR(COLOR_GREY, COLOR_GREY)); //right

                y=(cl>>4)&0x0F; x=cl&0x0F;
                draw_filled_rect(BORDER_SIZE+x*CELL_SIZE-CELL_ZOOM, FONT_HEIGHT+BORDER_SIZE+y*CELL_SIZE-CELL_ZOOM, BORDER_SIZE+(x+1)*CELL_SIZE+CELL_ZOOM, FONT_HEIGHT+BORDER_SIZE+(y+1)*CELL_SIZE+CELL_ZOOM, MAKE_COLOR(cl, COLOR_RED)); //selected
                draw_rect(BORDER_SIZE+x*CELL_SIZE-CELL_ZOOM-1, FONT_HEIGHT+BORDER_SIZE+y*CELL_SIZE-CELL_ZOOM-1, BORDER_SIZE+(x+1)*CELL_SIZE+CELL_ZOOM+1, FONT_HEIGHT+BORDER_SIZE+(y+1)*CELL_SIZE+CELL_ZOOM+1, COLOR_RED); //selected
                draw_filled_rect(BORDER_SIZE+16*CELL_SIZE+BORDER_SIZE+1, FONT_HEIGHT+BORDER_SIZE, screen_width-BORDER_SIZE-1, FONT_HEIGHT+BORDER_SIZE+16*CELL_SIZE, MAKE_COLOR(cl, COLOR_WHITE));
                gui_palette_redraw = 0;
            }
            break;
    }
}

