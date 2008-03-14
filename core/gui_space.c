#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_batt.h"
#include "gui_space.h"
//-------------------------------------------------------------------

static char osd_buf[32];

//-------------------------------------------------------------------

unsigned long get_space_perc() {
    return GetFreeCardSpaceKb()*100/GetTotalCardSpaceKb();
}

static void gui_space_draw_icon () {
    coord x;
    int perc = get_space_perc();
    color cl = (GetFreeCardSpaceKb()/1024<=15)?conf.osd_color_warn:(conf.space_color&0xFF);
       // space icon / bar
    draw_rect(conf.space_icon_pos.x+1,    conf.space_icon_pos.y+1,     conf.space_icon_pos.x+1+102, conf.space_icon_pos.y+1+5,  cl);
    draw_line(conf.space_icon_pos.x+1-1,    conf.space_icon_pos.y+1-1, conf.space_icon_pos.x+1-1,    conf.space_icon_pos.y+1+6, COLOR_BLACK);  // l
    draw_line(conf.space_icon_pos.x+1-1,    conf.space_icon_pos.y+1-1,   conf.space_icon_pos.x+1+103, conf.space_icon_pos.y+1-1,   COLOR_BLACK);  // t
    draw_line(conf.space_icon_pos.x+1-1,    conf.space_icon_pos.y+1+6,  conf.space_icon_pos.x+1+103, conf.space_icon_pos.y+1+6,  COLOR_BLACK);  // b
    draw_line(conf.space_icon_pos.x+1+103, conf.space_icon_pos.y+1-1,   conf.space_icon_pos.x+1+103, conf.space_icon_pos.y+1+6,  COLOR_BLACK);  // r
    
    // space bar fill
    x=conf.space_icon_pos.x+100-perc;
    if (x<=conf.space_icon_pos.x+1) x=conf.space_icon_pos.x+1;
    if (x>conf.space_icon_pos.x+100) x=conf.space_icon_pos.x+100;
    draw_filled_rect(conf.space_icon_pos.x+1+1, conf.space_icon_pos.y+1+1, x-1, conf.space_icon_pos.y+1+4, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_BLACK));
    draw_filled_rect(x, conf.space_icon_pos.y+1+1, conf.space_icon_pos.x+1+102, conf.space_icon_pos.y+1+4, MAKE_COLOR(cl, cl));
}


//-------------------------------------------------------------------
static void gui_space_draw_percent(){
    color cl = (GetFreeCardSpaceKb()/1024<=15)?conf.osd_color_warn:conf.osd_color;
    sprintf(osd_buf, "%3d%%", get_space_perc());
    osd_buf[5]=0;
    draw_string(conf.space_txt_pos.x, conf.space_txt_pos.y, osd_buf, cl);
}

//-------------------------------------------------------------------
static void gui_space_draw_mb() {
    color cl = (GetFreeCardSpaceKb()/1024<=15)?conf.osd_color_warn:conf.osd_color;
  sprintf(osd_buf, "%3d%M",GetFreeCardSpaceKb()/1024 );
    osd_buf[5]=0;
    draw_string(conf.space_txt_pos.x, conf.space_txt_pos.y, osd_buf, cl);
}


//-------------------------------------------------------------------

void gui_space_draw_osd() {
    if (conf.space_icon_show)   {
        gui_space_draw_icon();
    }
    if (conf.space_perc_show)  {
        gui_space_draw_percent();
    } else if (conf.space_mb_show) {
        gui_space_draw_mb();
    }
}
