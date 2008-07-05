#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_debug.h"


//-------------------------------------------------------------------
static void *addr;
static char debug_to_draw;
static char buf[32];
static long dummy=0;
static unsigned int step;

//-------------------------------------------------------------------
#define SCREEN_COLOR            0xF7

//-------------------------------------------------------------------
void gui_debug_init(void *st_addr) {
    addr = st_addr;
    debug_to_draw = 1;
    step = 4;
    gui_set_mode(GUI_MODE_DEBUG);
}

//-------------------------------------------------------------------
static void gui_debug_draw_values(const coord y, void* addr) {
    int i;

    if (!(addr<(void*)0x2000000 || addr>(void*)0xFFC00000)) { addr = &dummy; };

    sprintf(buf, "0x%08X (%10u)", *((unsigned int*)addr), *((unsigned int*)addr));
    draw_txt_string(10, y, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    sprintf(buf, "0x%04X (%5hu)", *((unsigned short*)addr), *((unsigned short*)addr));
    draw_txt_string(10, y+1, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    sprintf(buf, "0x%02X (%3hu)", *((unsigned char*)addr), *((unsigned char*)addr));
    draw_txt_string(10, y+2, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

//    sprintf(buf, "0x%lf", *((double*)addr));
//    draw_txt_string(10, y+3, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));

    for (i=0; i<30; ++i) {
        if (*((char*)(addr+i))) buf[i]=*((char*)(addr+i));
        else break;
    }
    while (i<30) {
        buf[i++]=' ';
    }
    buf[i]=0;
    draw_txt_string(10, y+4, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
}

//-------------------------------------------------------------------
void gui_debug_draw() {
    switch (debug_to_draw) {
        case 1:
            draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
            draw_txt_string(1, 0, "Address:", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(25, 0, "Incr:", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(1, 1, "Values:",  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 2, "DWORD  :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 3, "WORD   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 4, "BYTE   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 5, "DOUBLE :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 6, "STRING :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(1, 7, "Dereferencing:",  MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 8, "DWORD  :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 9, "WORD   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 10, "BYTE   :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 11, "DOUBLE :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
            draw_txt_string(2, 12, "STRING :", MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

            debug_to_draw = 0;
            break;
        default:
            sprintf(buf, "0x%08X", addr);
            draw_txt_string(10, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            sprintf(buf, "0x%08X", step);
            draw_txt_string(31, 0, buf, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
            gui_debug_draw_values(2, addr);
            gui_debug_draw_values(8, *((void**)addr));

            debug_to_draw = 0;
            break;
    }
}

//-------------------------------------------------------------------
void gui_debug_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
    case KEY_DOWN:
        break;
    case KEY_UP:
        break;
    case KEY_LEFT:
        addr-=step;
        break;
    case KEY_RIGHT:
        addr+=step;
        break;
    case KEY_DISPLAY:
        switch (step) {
            case 0x00000004: step = 0x00000010; break;
            case 0x10000000: step = 0x00000004; break;
            default: step<<=4; break;
        }
        break;
    }
}

//-------------------------------------------------------------------
