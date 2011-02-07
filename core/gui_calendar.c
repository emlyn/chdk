#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_calendar.h"

//-------------------------------------------------------------------
#define TITLE_COLOR             (MAKE_COLOR(COLOR_BLACK, COLOR_WHITE))
#define CALENDAR_COLOR          (MAKE_COLOR(COLOR_GREY, COLOR_WHITE))
#define WEEKEND_COLOR           (MAKE_COLOR(0x6E, COLOR_RED))

//-------------------------------------------------------------------
static int need_redraw;
static int cal_year, cal_month;
static coord cal_x, cal_y, cal_w, cal_h;
static int months[] = {LANG_CALENDAR_JANUARY, LANG_CALENDAR_FEBRUARY, LANG_CALENDAR_MARCH,
                       LANG_CALENDAR_APRIL, LANG_CALENDAR_MAY, LANG_CALENDAR_JUNE,
                       LANG_CALENDAR_JULY, LANG_CALENDAR_AUGUST, LANG_CALENDAR_SEPTEMBER,
                       LANG_CALENDAR_OCTOBER, LANG_CALENDAR_NOVEMBER, LANG_CALENDAR_DECEMBER};
static int days[] = {LANG_CALENDAR_MON, LANG_CALENDAR_TUE, LANG_CALENDAR_WED, LANG_CALENDAR_THU,
                     LANG_CALENDAR_FRI, LANG_CALENDAR_SAT, LANG_CALENDAR_SUN};
//-------------------------------------------------------------------
static void calendar_goto_today() {
    unsigned long t;
    struct tm *ttm;

    t = time(NULL);
    ttm = localtime(&t);
    cal_year = 1900+ttm->tm_year;
    cal_month = ttm->tm_mon;
}

//-------------------------------------------------------------------
static int calendar_days_in_month(int month, int year) {
    switch (month) {
        case 2: 
            return ((year%4==0 && year%100!=0) || year%400==0)?29:28;
        case 4: case 6: case 9: case 11:
            return 30;
        default:
            return 31;
    }
}
//-------------------------------------------------------------------
static int calendar_day_of_week(int day /*1-31*/, int month /*1-12*/, int year) {
    register int a;

    a = (14 - month) / 12;
    year -= a;
    month += a*12 - 2;

    return (((7000 + day + year + year/4 - year/100 + year/400 + 31*month/12) % 7) + 6) % 7;
}

//-------------------------------------------------------------------
static void gui_calendar_initial_draw() {
    int x, i;

    draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
    draw_txt_string(1, 0, lang_str(LANG_CALENDAR_TODAY), MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
    draw_rect(cal_x-3, cal_y-3, cal_x+cal_w+2, cal_y+cal_h+2, CALENDAR_COLOR);
    draw_filled_rect(cal_x-1, cal_y-1, cal_x+cal_w, cal_y+FONT_HEIGHT+8, TITLE_COLOR);
    draw_filled_rect(cal_x-1, cal_y+FONT_HEIGHT+8, cal_x+cal_w, cal_y+cal_h, CALENDAR_COLOR);

    draw_filled_rect(cal_x+cal_w-FONT_WIDTH*4*2, cal_y+FONT_HEIGHT+8+1, cal_x+cal_w-1, cal_y+cal_h-1, MAKE_COLOR(((WEEKEND_COLOR)>>8), ((WEEKEND_COLOR)>>8)));
    for (x=cal_x+FONT_WIDTH/2, i=0; i<7; x+=FONT_WIDTH*4, ++i) {
        draw_string(x, cal_y+4+FONT_HEIGHT+4+4, lang_str(days[i]), (i<5)?CALENDAR_COLOR:WEEKEND_COLOR);
    }
}

//-------------------------------------------------------------------
void gui_calendar_init() {
    calendar_goto_today();
    cal_w = FONT_WIDTH*4*7;
    cal_h = 4+FONT_HEIGHT+4+4+FONT_HEIGHT+4+(FONT_HEIGHT+4)*6;
    cal_x = (screen_width-cal_w)/2;
    cal_y = FONT_HEIGHT+(screen_height-FONT_HEIGHT-cal_h)/2;
    gui_calendar_initial_draw();
    need_redraw = 1;
}

//-------------------------------------------------------------------
void gui_calendar_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
        case KEY_UP:
            ++cal_year;
            need_redraw = 1;
            break;
        case KEY_DOWN:
            if (cal_year>1) --cal_year;
            need_redraw = 1;
            break;
        case KEY_LEFT:
            if (--cal_month<0) {
                cal_month=11;
                --cal_year;
            }
            need_redraw = 1;
            break;
        case KEY_RIGHT:
            if (++cal_month>11) {
                cal_month=0;
                ++cal_year;
            }
            need_redraw = 1;
            break;
      #if CAM_HAS_ERASE_BUTTON
        case KEY_ERASE:
      #else
        case KEY_DISPLAY:
      #endif
            calendar_goto_today();
            need_redraw = 1;
            break;
    }
}

//-------------------------------------------------------------------
void gui_calendar_draw() {
    int x, y;
    static char str[32];
    int w, d, i;
    unsigned long t;
    static struct tm *ttm;

    t = time(NULL);
    ttm = localtime(&t);
    sprintf(str, " %2u %s %04u  %2u:%02u:%02u   ", ttm->tm_mday, lang_str(months[ttm->tm_mon]), 1900+ttm->tm_year, ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
    draw_txt_string(8, 0, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

    if (need_redraw) {
        need_redraw = 0;
        
        i = strlen(lang_str(months[cal_month]));
        x = cal_x + (cal_w-FONT_WIDTH*2-FONT_WIDTH*4-FONT_WIDTH*2-i*FONT_WIDTH)/2;
        y = cal_y + 4;
        draw_filled_rect(cal_x+FONT_WIDTH, y, cal_x+cal_w-FONT_WIDTH-FONT_WIDTH*4-FONT_WIDTH, y+FONT_HEIGHT, MAKE_COLOR(((TITLE_COLOR)>>8), ((TITLE_COLOR)>>8)));
        draw_string(x+FONT_WIDTH, y, lang_str(months[cal_month]), TITLE_COLOR);
        
        sprintf(str, "%04d", cal_year);
        draw_string(cal_x+cal_w-FONT_WIDTH*2-FONT_WIDTH*4, y, str, TITLE_COLOR);

        d = calendar_days_in_month(cal_month+1, cal_year);
        w = calendar_day_of_week(1, cal_month+1, cal_year);

        y += FONT_HEIGHT+4+4;

        y += FONT_HEIGHT+4;
        for (x=0; x<w; ++x) {
            draw_string(cal_x+x*FONT_WIDTH*4, y, "    ", (x<5)?CALENDAR_COLOR:WEEKEND_COLOR);
        }
        
        for (i=1; i<=d; ++i) {
            sprintf(str, " %2d ", i);
            draw_string(cal_x+x*FONT_WIDTH*4, y, str, (x<5)?CALENDAR_COLOR:WEEKEND_COLOR);
            
            if (++x>6) {
              x=0;
              y += FONT_HEIGHT+4;
            }
        }
        for (; y<cal_y+cal_h; y += FONT_HEIGHT+4, x=0) {
            for (; x<7; ++x) {
                draw_string(cal_x+x*FONT_WIDTH*4, y, "    ", (x<5)?CALENDAR_COLOR:WEEKEND_COLOR);
            }
        }
    }
}

