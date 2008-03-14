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

static void gui_space_draw_spacebar_horizontal () {
    coord x;
    color cl = conf.space_color&0xFF;
    int perc = get_space_perc(),height = 2;
    float size = 0;
    if (conf.space_warn_type == 0){
    cl = (perc<=conf.space_perc_warn)?conf.osd_color_warn:(conf.space_color&0xFF);
    }
    if (conf.space_warn_type == 1){
    cl = (GetFreeCardSpaceKb()/1024<=conf.space_mb_warn)?conf.osd_color_warn:conf.osd_color;
    }
    if (conf.space_warn_type == 2){
    cl = conf.space_color&0xFF;
    }
       // space icon / bar
    height = conf.space_bar_width+1;
    if (conf.space_bar_size == 0){
    size = screen_width/4-4;
           if (conf.space_hor_pos.x>(screen_width-size)){
            conf.space_hor_pos.x = screen_width-size;
        }    
    }
    if (conf.space_bar_size == 1){
    size = screen_width/2-4;
           if (conf.space_hor_pos.x>(screen_width-size)){
            conf.space_hor_pos.x = screen_width-size;
        }
    }
     if (conf.space_bar_size == 2){
    size = screen_width-4;
        if (conf.space_hor_pos.x>(screen_width-size)){
            conf.space_hor_pos.x = 0;
        }
    }
    if (conf.space_hor_pos.y > (screen_height-height-3)){
            conf.space_hor_pos.y = screen_height-height-3;
    }
    draw_rect(conf.space_hor_pos.x+1,    conf.space_hor_pos.y+1,     conf.space_hor_pos.x+1+size+2, conf.space_hor_pos.y+1+height+1,  cl);
    draw_line(conf.space_hor_pos.x+1-1,    conf.space_hor_pos.y+1-1, conf.space_hor_pos.x+1-1,    conf.space_hor_pos.y+1+height+2, COLOR_BLACK);  // l
    draw_line(conf.space_hor_pos.x+1-1,    conf.space_hor_pos.y+1-1,   conf.space_hor_pos.x+1+size+3, conf.space_hor_pos.y+1-1,   COLOR_BLACK);  // t
    draw_line(conf.space_hor_pos.x+1-1,    conf.space_hor_pos.y+1+height+2,  conf.space_hor_pos.x+1+size+3, conf.space_hor_pos.y+1+height+2,  COLOR_BLACK);  // b
    draw_line(conf.space_hor_pos.x+1+size+3, conf.space_hor_pos.y+1-1,   conf.space_hor_pos.x+1+size+3, conf.space_hor_pos.y+1+height+2,  COLOR_BLACK);  // r
    
    // space bar fill
        
    x=conf.space_hor_pos.x+size-(perc/(100/size));
    if (x<=conf.space_hor_pos.x+1) x=conf.space_hor_pos.x+1;
    if (x>conf.space_hor_pos.x+size) x=conf.space_hor_pos.x+size;
    draw_filled_rect(conf.space_hor_pos.x+1+1, conf.space_hor_pos.y+1+1, x-1, conf.space_hor_pos.y+1+height, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_BLACK));
    draw_filled_rect(x, conf.space_hor_pos.y+1+1, conf.space_hor_pos.x+1+size+2, conf.space_hor_pos.y+1+height, MAKE_COLOR(cl, cl));
}


static void gui_space_draw_spacebar_vertical () {
    coord y;
    color cl = conf.space_color&0xFF;
    int perc = get_space_perc(), width = 2;
    float size = 0;
    if (conf.space_warn_type == 0){
    cl = (perc<=conf.space_perc_warn)?conf.osd_color_warn:(conf.space_color&0xFF);
    }
    if (conf.space_warn_type == 1){
    cl = (GetFreeCardSpaceKb()/1024<=conf.space_mb_warn)?conf.osd_color_warn:conf.osd_color;
    }
    if (conf.space_warn_type == 2){
    cl = conf.space_color&0xFF;
    }
    
       // space icon / bar
    width = conf.space_bar_width+1;
    if (conf.space_bar_size == 0){
    size = screen_height/4-4;
         if (conf.space_ver_pos.y>(screen_height-size)){
            conf.space_ver_pos.y = screen_height-size;
        }
    }
    if (conf.space_bar_size == 1){
    size = screen_height/2-4;
       if (conf.space_ver_pos.y>(screen_height-size)){
            conf.space_ver_pos.y = screen_height-size;
        }
    }
     if (conf.space_bar_size == 2){
    size = screen_height-4;
        if (conf.space_ver_pos.y>(screen_height-size)){
            conf.space_ver_pos.y = 0;
        }
    }
    if (conf.space_ver_pos.x > (screen_width-width-3)){
            conf.space_ver_pos.x = screen_width-width-3;
    }
    draw_rect(conf.space_ver_pos.x+1,    conf.space_ver_pos.y+1,     conf.space_ver_pos.x+1+width+1, conf.space_ver_pos.y+1+size+2,  cl);
    draw_line(conf.space_ver_pos.x+1-1,    conf.space_ver_pos.y+1-1, conf.space_ver_pos.x+1-1,    conf.space_ver_pos.y+1+5, COLOR_BLACK);  // l
    
    draw_line(conf.space_ver_pos.x+1-1,    conf.space_ver_pos.y+1-1, conf.space_ver_pos.x+1+width+2,    conf.space_ver_pos.y+1-1, COLOR_BLACK);  // t
    draw_line(conf.space_ver_pos.x+1-1,    conf.space_ver_pos.y+1+size+3, conf.space_ver_pos.x+1+width+2,    conf.space_ver_pos.y+1+size+3, COLOR_BLACK);   // b
    
    draw_line(conf.space_ver_pos.x+1+width+2, conf.space_ver_pos.y+1-1,   conf.space_ver_pos.x+1+width+2, conf.space_ver_pos.y+1+size+3,  COLOR_BLACK);  // r
    
    // space bar fill
        
    y=conf.space_ver_pos.y+size-(perc/(100/size));
    if (y<=conf.space_ver_pos.y+1) y=conf.space_ver_pos.y+1;
    if (y>conf.space_ver_pos.y+size) y=conf.space_ver_pos.y+size;
    draw_filled_rect(conf.space_ver_pos.x+1+1, conf.space_ver_pos.y+1+1, conf.space_ver_pos.x+1+width, y-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_BLACK));
    draw_filled_rect(conf.space_ver_pos.x+1+1, y, conf.space_ver_pos.x+1+width, conf.space_ver_pos.y+1+size+2, MAKE_COLOR(cl, cl));
}

static void gui_space_draw_icon () {
    coord x;
    color cl = conf.space_color&0xFF;
    int perc = get_space_perc();
    if (conf.space_warn_type == 0){
    cl = (perc<=conf.space_perc_warn)?conf.osd_color_warn:(conf.space_color&0xFF);
    }
    if (conf.space_warn_type == 1){
    cl = (GetFreeCardSpaceKb()/1024<=conf.space_mb_warn)?conf.osd_color_warn:conf.osd_color;
    }
    if (conf.space_warn_type == 2){
    cl = conf.space_color&0xFF;
    }
    int i;
    int le = 23;//length
    int wi = 15;//width
 
    draw_line(conf.space_icon_pos.x+5,      conf.space_icon_pos.y,       conf.space_icon_pos.x+le,     conf.space_icon_pos.y,       COLOR_BLACK);  // outer top
    draw_line(conf.space_icon_pos.x+6,      conf.space_icon_pos.y+1,     conf.space_icon_pos.x+le-1,   conf.space_icon_pos.y+1,     MAKE_COLOR(cl, cl));  // inner top
    draw_line(conf.space_icon_pos.x,        conf.space_icon_pos.y+5,     conf.space_icon_pos.x,        conf.space_icon_pos.y+wi,    COLOR_BLACK);  // outer left
    draw_line(conf.space_icon_pos.x+1,      conf.space_icon_pos.y+6,     conf.space_icon_pos.x+1,      conf.space_icon_pos.y+wi-1,  MAKE_COLOR(cl, cl));  // inner left
    draw_line(conf.space_icon_pos.x,        conf.space_icon_pos.y+wi,    conf.space_icon_pos.x+le,     conf.space_icon_pos.y+wi,    COLOR_BLACK);  // outer bottom
    draw_line(conf.space_icon_pos.x+1,      conf.space_icon_pos.y+wi-1,  conf.space_icon_pos.x+le-1,   conf.space_icon_pos.y+wi-1,  MAKE_COLOR(cl, cl));  // inner bottom
    draw_line(conf.space_icon_pos.x+le,     conf.space_icon_pos.y,       conf.space_icon_pos.x+le,     conf.space_icon_pos.y+wi,    COLOR_BLACK);  // outer right
    draw_line(conf.space_icon_pos.x+le-1,   conf.space_icon_pos.y+1,     conf.space_icon_pos.x+le-1,   conf.space_icon_pos.y+wi-1,  MAKE_COLOR(cl, cl));  // inner right
    draw_line(conf.space_icon_pos.x+5,      conf.space_icon_pos.y,       conf.space_icon_pos.x,        conf.space_icon_pos.y+5,     COLOR_BLACK);  // edge
    draw_line(conf.space_icon_pos.x+5,      conf.space_icon_pos.y+1,     conf.space_icon_pos.x+1,      conf.space_icon_pos.y+5,     MAKE_COLOR(cl, cl));  // edge
    draw_line(conf.space_icon_pos.x+6,      conf.space_icon_pos.y+1,     conf.space_icon_pos.x+1,      conf.space_icon_pos.y+6,     MAKE_COLOR(cl, cl));  // edge
 
    // memory fill
    x=le-(perc*(le-3)/100)-2;
    if (x>5) draw_line(conf.space_icon_pos.x+6,      conf.space_icon_pos.y+2,     conf.space_icon_pos.x+x,      conf.space_icon_pos.y+2,     COLOR_BLACK);
    if (x>2) draw_line(conf.space_icon_pos.x+x+1,    conf.space_icon_pos.y+2,     conf.space_icon_pos.x+le-2,   conf.space_icon_pos.y+2,     MAKE_COLOR(cl, cl));
    else     draw_line(conf.space_icon_pos.x+4,      conf.space_icon_pos.y+2,     conf.space_icon_pos.x+le-2,   conf.space_icon_pos.y+2,     MAKE_COLOR(cl, cl));
    for(i=3;i<7;i++){                                                                                                                                               //          /--------------|
        if (x>7-i) draw_pixel(conf.space_icon_pos.x+8-i,     conf.space_icon_pos.y+i,     COLOR_BLACK);                                                             //        /  1st for loop  |
        if (x>7-i) draw_pixel(conf.space_icon_pos.x+x,       conf.space_icon_pos.y+i,     COLOR_BLACK);                                                             //      /__________________|
        draw_line(conf.space_icon_pos.x+x+1,                 conf.space_icon_pos.y+i,     conf.space_icon_pos.x+le-2,     conf.space_icon_pos.y+i,     MAKE_COLOR(cl, cl));//     |                   |
    }                                                                                                                                                               //     |     2nd for loop  |
    for(i=7;i<wi-2;i++){                                                                                                                                            //     |                   |
        if (x>1) draw_pixel(conf.space_icon_pos.x+2,         conf.space_icon_pos.y+i,     COLOR_BLACK);                                                             //     |-------------------|
        if (x>1) draw_pixel(conf.space_icon_pos.x+x,         conf.space_icon_pos.y+i,     COLOR_BLACK);
        draw_line(conf.space_icon_pos.x+x+1,                 conf.space_icon_pos.y+i,     conf.space_icon_pos.x+le-2,     conf.space_icon_pos.y+i,     MAKE_COLOR(cl, cl));
    }
    if (x>1) draw_line(conf.space_icon_pos.x+2,      conf.space_icon_pos.y+wi-2,    conf.space_icon_pos.x+x,      conf.space_icon_pos.y+wi-2,    COLOR_BLACK);
    draw_line(conf.space_icon_pos.x+x+1,             conf.space_icon_pos.y+wi-2,    conf.space_icon_pos.x+le-2,   conf.space_icon_pos.y+wi-2,    MAKE_COLOR(cl, cl));
}


//-------------------------------------------------------------------
static void gui_space_draw_percent(){
    int perc = get_space_perc();
    color cl = conf.space_color&0xFF;
    if (conf.space_warn_type == 0){
    cl = (perc<=conf.space_perc_warn)?conf.osd_color_warn:(conf.space_color&0xFF);
    }
    if (conf.space_warn_type == 1){
    cl = (GetFreeCardSpaceKb()/1024<=conf.space_mb_warn)?conf.osd_color_warn:conf.osd_color;
    }
    if (conf.space_warn_type == 2){
    cl = conf.space_color&0xFF;
    }
    sprintf(osd_buf, "%3d%%", get_space_perc());
    osd_buf[5]=0;
    draw_string(conf.space_txt_pos.x, conf.space_txt_pos.y, osd_buf, cl);
}

//-------------------------------------------------------------------
static void gui_space_draw_mb() {
    int perc = get_space_perc();
    color cl = conf.space_color&0xFF;
    if (conf.space_warn_type == 0){
    cl = (perc<=conf.space_perc_warn)?conf.osd_color_warn:(conf.space_color&0xFF);
    }
    if (conf.space_warn_type == 1){
    cl = (GetFreeCardSpaceKb()/1024<=conf.space_mb_warn)?conf.osd_color_warn:conf.osd_color;
    }
    if (conf.space_warn_type == 2){
    cl = conf.space_color&0xFF;
    }
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
  if (conf.space_bar_show==1)  {
        gui_space_draw_spacebar_horizontal();
    }
  if (conf.space_bar_show==2) {
        gui_space_draw_spacebar_vertical();
    }
}
