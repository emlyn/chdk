#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_mbox.h"


//-------------------------------------------------------------------
static enum Gui_Mode 	gui_mbox_mode_old;
static const char*	mbox_title;
static const char* 	mbox_msg;
static char 		mbox_to_draw;
static unsigned int     mbox_flags;
#define MAX_LINES       8
#define MAX_WIDTH       35
#define SPACING_TITLE   4
#define SPACING_BTN     4
static struct {
        unsigned int    flag;
        int             text;
} buttons[] = {
        { MBOX_BTN_OK,          LANG_MBOX_BTN_OK    },
        { MBOX_BTN_YES,         LANG_MBOX_BTN_YES   },
        { MBOX_BTN_NO,          LANG_MBOX_BTN_NO    },
        { MBOX_BTN_CANCEL,      LANG_MBOX_BTN_CANCEL}
};
#define BUTTON_SIZE     6
#define BUTTONSNUM      (sizeof(buttons)/sizeof(buttons[0]))
#define MAX_BUTTONS     3
static int      mbox_buttons[MAX_BUTTONS], mbox_buttons_num, mbox_button_active;
static coord    mbox_buttons_x, mbox_buttons_y;
#define BUTTON_SEP      18
static void (*mbox_on_select)(unsigned int btn);

//-------------------------------------------------------------------
void gui_mbox_init(int title, int msg, const unsigned int flags, void (*on_select)(unsigned int btn)) {
    int i;

    mbox_buttons_num = 0;
    for (i=0; i<BUTTONSNUM && mbox_buttons_num<MAX_BUTTONS; ++i) {
        if (flags & MBOX_BTN_MASK & buttons[i].flag)
            mbox_buttons[mbox_buttons_num++] = i;
    }
    if (mbox_buttons_num == 0)
        mbox_buttons[mbox_buttons_num++] = 0; // Add button "Ok" if there is no buttons

    switch (flags & MBOX_DEF_MASK) {
        case MBOX_DEF_BTN1: mbox_button_active = 0; break;
        case MBOX_DEF_BTN2: mbox_button_active = 1; break;
        case MBOX_DEF_BTN3: mbox_button_active = 2; break;
        default: mbox_button_active = 0; break;
    }

    gui_mbox_mode_old = gui_get_mode();
    mbox_title = lang_str(title);
    mbox_msg = lang_str(msg);
    mbox_to_draw = 1;
    mbox_flags = flags;
    mbox_on_select = on_select;
    gui_set_mode(GUI_MODE_MBOX);
}

//-------------------------------------------------------------------
unsigned int gui_mbox_result() {
    return buttons[mbox_buttons[mbox_button_active]].flag;
}

//-------------------------------------------------------------------
static void gui_mbox_draw_buttons() {
    int i;
    coord x = mbox_buttons_x;
    color cl;

    for (i=0; i<mbox_buttons_num; ++i) {
        cl = MAKE_COLOR((mbox_button_active==i)?COLOR_RED:COLOR_BLACK, COLOR_WHITE);
        draw_rect(x-1, mbox_buttons_y-1, x+BUTTON_SIZE*FONT_WIDTH+3, mbox_buttons_y+FONT_HEIGHT+3, COLOR_BLACK); //shadow
        draw_filled_rect(x-2, mbox_buttons_y-2, x+BUTTON_SIZE*FONT_WIDTH+2, mbox_buttons_y+FONT_HEIGHT+2, cl);
        draw_string(x+(((BUTTON_SIZE-strlen(lang_str(buttons[mbox_buttons[i]].text)))*FONT_WIDTH)>>1), mbox_buttons_y, lang_str(buttons[mbox_buttons[i]].text), cl);
        x+=BUTTON_SIZE*FONT_WIDTH+BUTTON_SEP;
    }
}

//-------------------------------------------------------------------
void gui_mbox_draw() {
    if (mbox_to_draw) {
        char c[MAX_LINES][MAX_WIDTH+1];
        const char *p=mbox_msg;
        coord x=0, y=0, d;
        unsigned int w, h=0, l=0, bw=(mbox_buttons_num*BUTTON_SIZE*FONT_WIDTH+(mbox_buttons_num-1)*BUTTON_SEP);
        color cl_t =((mode_get()&MODE_MASK) == MODE_PLAY)?MAKE_COLOR(0xAA, COLOR_WHITE):MAKE_COLOR(0xDF, COLOR_WHITE);

        w =strlen(mbox_title);
        if (w > MAX_WIDTH) w = MAX_WIDTH;
        while (*p) {
            if (*p == '\n') {
                c[h++][l] = 0;
                l=0;
                if (h == MAX_LINES) break;
            } else {
                if (l < MAX_WIDTH) {
                    c[h][l++]=*p;
                    if (l > w) w = l;
                }
            }
            ++p;
        }
        w+=2;
        if (h<MAX_LINES)
            c[h++][l] = 0;
        if (bw+BUTTON_SEP>w*FONT_WIDTH) 
            w=(bw+BUTTON_SEP)/FONT_WIDTH+1;
    
        x = ((44-w)>>1)*FONT_WIDTH; y = ((12-h)>>1)*FONT_HEIGHT;
        draw_rect(x-3, y-3, x+w*FONT_WIDTH+5, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+8, COLOR_BLACK); //shadow
        draw_rect(x-2, y-2, x+w*FONT_WIDTH+6, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+9, COLOR_BLACK); //shadow
        draw_rect(x-1, y-1, x+w*FONT_WIDTH+7, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+10, COLOR_BLACK); //shadow
        draw_filled_rect(x-4, y-4, x+w*FONT_WIDTH+4, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+7, MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // main box
        draw_filled_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+FONT_HEIGHT+2, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title
        draw_rect(x-2, y-2, x+w*FONT_WIDTH+2, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+5, COLOR_WHITE); //border
        draw_rect(x-3, y-3, x+w*FONT_WIDTH+3, y+(h+2)*FONT_HEIGHT+SPACING_BTN+2+SPACING_TITLE+6, COLOR_WHITE); //border
//        draw_line(x-2, y+FONT_HEIGHT+2, x+w*FONT_WIDTH+2, y+FONT_HEIGHT+2, COLOR_WHITE);
    
        l = strlen(mbox_title);
        draw_string(x+((w-l)>>1)*FONT_WIDTH, y, mbox_title, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title text
        y+=FONT_HEIGHT+2+SPACING_TITLE;
    
        mbox_buttons_x = x+((w*FONT_WIDTH-bw)>>1);
        mbox_buttons_y = y+h*FONT_HEIGHT+SPACING_BTN;

        while (h) {
            l = strlen(c[--h]);
            switch (mbox_flags & MBOX_TEXT_MASK) {
                case MBOX_TEXT_LEFT:    d = FONT_WIDTH; break;
                case MBOX_TEXT_CENTER:  d = ((w-l)>>1)*FONT_WIDTH; break;
                case MBOX_TEXT_RIGHT:   d = (w-l-1)*FONT_WIDTH; break;
                default:                d = FONT_WIDTH; break;
            }
            draw_string(x+d, y+h*FONT_HEIGHT, c[h], MAKE_COLOR(COLOR_GREY, COLOR_WHITE)); // text
        }

        gui_mbox_draw_buttons();

        mbox_to_draw = 0;
    }
}

//-------------------------------------------------------------------
void gui_mbox_kbd_process() {
    switch (kbd_get_clicked_key() | get_jogdial_direction()) {
    case JOGDIAL_LEFT:
    case KEY_LEFT:
        if (mbox_button_active > 0) --mbox_button_active;
        else mbox_button_active = mbox_buttons_num-1;
        gui_mbox_draw_buttons();
        break;
    case JOGDIAL_RIGHT:
    case KEY_RIGHT:
        if (mbox_button_active < mbox_buttons_num-1) ++mbox_button_active;
        else mbox_button_active = 0;
        gui_mbox_draw_buttons();
        break;
    case KEY_SET:
        kbd_reset_autoclicked_key();
        gui_set_mode(gui_mbox_mode_old);
        if (mbox_flags & MBOX_FUNC_RESTORE)
            draw_restore();
        if (mbox_on_select) 
            mbox_on_select(buttons[mbox_buttons[mbox_button_active]].flag);
        break;
    }
}

//-------------------------------------------------------------------
