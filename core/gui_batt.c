#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_batt.h"
//-------------------------------------------------------------------

static char osd_buf[32];

//-------------------------------------------------------------------
static long get_batt_average() {
    #define VOLTS_N         100
    static unsigned short   volts[VOLTS_N] = {0};
    static unsigned int     n = 0, rn = 0;
    static unsigned long    volt_aver = 0;

    volt_aver-=volts[n];
    volts[n]=(unsigned short)stat_get_vbatt();
    volt_aver+=volts[n];
    if (++n>rn) rn=n;
    if (n>=VOLTS_N) n=0;
    return volt_aver/rn;
}

//-------------------------------------------------------------------
unsigned long get_batt_perc() {
    unsigned long v;

    v = get_batt_average();
    if (v>conf.batt_volts_max) v=conf.batt_volts_max;
    if (v<conf.batt_volts_min) v=conf.batt_volts_min;
    return (v-conf.batt_volts_min)*100/(conf.batt_volts_max-conf.batt_volts_min);
}

//-------------------------------------------------------------------
static void gui_batt_draw_icon () {
    coord x;
    int perc = get_batt_perc();
    color cl = (perc<=10)?conf.osd_color_warn:(conf.batt_icon_color&0xFF);

    // battery icon
    draw_rect(conf.batt_icon_pos.x+3-1,    conf.batt_icon_pos.y+1,     conf.batt_icon_pos.x+3+25+1, conf.batt_icon_pos.y+1+10,  cl);
    draw_rect(conf.batt_icon_pos.x+3-3,    conf.batt_icon_pos.y+1+2,   conf.batt_icon_pos.x+3-2,    conf.batt_icon_pos.y+1+8,   cl);
    draw_line(conf.batt_icon_pos.x+3-4,    conf.batt_icon_pos.y+1+2-1, conf.batt_icon_pos.x+3-4,    conf.batt_icon_pos.y+1+8+1, COLOR_BLACK);  // l
    draw_line(conf.batt_icon_pos.x+3-2,    conf.batt_icon_pos.y+1-1,   conf.batt_icon_pos.x+3+25+2, conf.batt_icon_pos.y+1-1,   COLOR_BLACK);  // t
    draw_line(conf.batt_icon_pos.x+3-2,    conf.batt_icon_pos.y+1+11,  conf.batt_icon_pos.x+3+25+2, conf.batt_icon_pos.y+1+11,  COLOR_BLACK);  // b
    draw_line(conf.batt_icon_pos.x+3+25+2, conf.batt_icon_pos.y+1-1,   conf.batt_icon_pos.x+3+25+2, conf.batt_icon_pos.y+1+10,  COLOR_BLACK);  // r

    // battery fill
    x=conf.batt_icon_pos.x+3+1+25-(perc/4);
    if (x<=conf.batt_icon_pos.x+3) x=conf.batt_icon_pos.x+3+1;
    if (x>conf.batt_icon_pos.x+3+25+1) x=conf.batt_icon_pos.x+3+25+1;
    draw_filled_rect(conf.batt_icon_pos.x+3, conf.batt_icon_pos.y+1+1, x-1, conf.batt_icon_pos.y+1+9, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_BLACK));
    draw_filled_rect(x, conf.batt_icon_pos.y+1+1, conf.batt_icon_pos.x+3+25, conf.batt_icon_pos.y+1+9, MAKE_COLOR(cl, cl));
}

//-------------------------------------------------------------------
static void gui_batt_draw_charge() {
    int perc = get_batt_perc();
    color cl = (perc<=10)?conf.osd_color_warn:conf.osd_color;
    sprintf(osd_buf, "%3d%%", perc);
    osd_buf[5]=0;
    draw_string(conf.batt_txt_pos.x, conf.batt_txt_pos.y, osd_buf, cl);
}

//-------------------------------------------------------------------
static void gui_batt_draw_volts() {
    unsigned long v;

    v = get_batt_average();
    sprintf(osd_buf, "%ld.%03ld", v/1000, v%1000);
    osd_buf[5]=0;
    draw_string(conf.batt_txt_pos.x, conf.batt_txt_pos.y, osd_buf, conf.osd_color);
}

//-------------------------------------------------------------------
void gui_batt_draw_osd() {
    if (conf.batt_perc_show) {
        gui_batt_draw_charge();
    } else if (conf.batt_volts_show) {
        gui_batt_draw_volts();
    }

    if (conf.batt_icon_show) {
        gui_batt_draw_icon();
    }
}

//-------------------------------------------------------------------
