#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
#include "font.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_palette.h"
#include "gui_menu.h"
#include "gui_lang.h"

//-------------------------------------------------------------------
#define MENUSTACK_MAXDEPTH  4

//-------------------------------------------------------------------
typedef struct {
    CMenu       *menu;
    int         curpos;
    int         toppos;
} CMenuStacked;

//-------------------------------------------------------------------

static CMenu        *curr_menu;
static CMenuStacked gui_menu_stack[MENUSTACK_MAXDEPTH];
static unsigned int gui_menu_stack_ptr;
static int          gui_menu_curr_item;
static int          gui_menu_top_item;
static int          gui_menu_redraw;
static int          gui_menu_add_item = 0;

static int          count;
static coord        x, y, w, num_lines;
static int          len_bool, len_int, len_enum, len_space, len_br1, len_br2, cl_rect;
static int          int_incr, incr_modified;
static int          c, j;
static unsigned char *item_color;

//-------------------------------------------------------------------
static void gui_menu_set_curr_menu(CMenu *menu_ptr, int top_item, int curr_item) {
    curr_menu = menu_ptr;
    gui_menu_top_item = top_item;
    gui_menu_curr_item = curr_item;
}

//-------------------------------------------------------------------
void gui_menu_init(CMenu *menu_ptr) {
    if (menu_ptr) {
        gui_menu_set_curr_menu(menu_ptr, 0, 0);
        gui_menu_stack_ptr = 0;
    }
    
    num_lines = screen_height/rbf_font_height()-1;
    w = screen_width-30-30;
    x = (screen_width-w)>>1;
    len_bool = rbf_str_width("\x95");
    len_int = rbf_str_width("99999");
    len_enum = rbf_str_width("WUBfS3a");
    len_space = rbf_char_width(' ');
    len_br1 = rbf_char_width('[');
    len_br2 = rbf_char_width(']');
    cl_rect = rbf_font_height() - 4;
    int_incr = 1;
    
    gui_menu_redraw=2;
}

//-------------------------------------------------------------------
static void gui_menu_color_selected(color clr) {
    *item_color = (unsigned char)(clr&0xFF);
    gui_menu_redraw=2;
    draw_restore();
    gui_force_restore();
}

//-------------------------------------------------------------------
static void gui_menu_back() {
    if (gui_menu_stack_ptr > 0){
        gui_menu_stack_ptr--;
        gui_menu_set_curr_menu(gui_menu_stack[gui_menu_stack_ptr].menu, gui_menu_stack[gui_menu_stack_ptr].toppos, gui_menu_stack[gui_menu_stack_ptr].curpos);
        gui_menu_redraw=2;
        draw_restore();
        gui_force_restore();
    }
}

//-------------------------------------------------------------------
void gui_menu_kbd_process() {
static char sbuf[7];
    switch (kbd_get_autoclicked_key()) {
#if CAM_HAS_ERASE_BUTTON
        case KEY_ERASE:
#else    
        case KEY_SHOOT_HALF:
#endif
		if (conf.user_menu_enable == 3) {
			if (curr_menu->title != LANG_MENU_USER_MENU)
				add_user_menu(curr_menu->menu[gui_menu_curr_item],&gui_menu_add_item, 0);
			else
				add_user_menu(curr_menu->menu[gui_menu_curr_item],&gui_menu_add_item, 1);
	            gui_menu_redraw=1;
		}
		break;
        case KEY_UP:
			if (kbd_is_key_pressed(KEY_SHOOT_HALF) || kbd_is_key_pressed(KEY_ZOOM_IN) || kbd_is_key_pressed(KEY_ZOOM_OUT)) c=4; else c=1;
            for (j=0;j<c;++j){
            do {
                if (gui_menu_curr_item>0) {
                    if (gui_menu_curr_item-1==gui_menu_top_item && gui_menu_top_item>0) 
                        --gui_menu_top_item;
                    --gui_menu_curr_item;
                } else {
                    int i;
                    while (curr_menu->menu[gui_menu_curr_item+1].text)
                        ++gui_menu_curr_item;
                    gui_menu_top_item = gui_menu_curr_item - num_lines +1;
                    if (gui_menu_top_item<0) gui_menu_top_item=0;
                }
            } while ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_TEXT || 
                     (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_SEPARATOR);
            int_incr = 1;
            gui_menu_redraw=1;
            if (curr_menu->title == LANG_MENU_USER_MENU) gui_menu_add_item = gui_menu_curr_item;
			}
            break;
        case KEY_DOWN:
			if (kbd_is_key_pressed(KEY_SHOOT_HALF) || kbd_is_key_pressed(KEY_ZOOM_IN) || kbd_is_key_pressed(KEY_ZOOM_OUT)) c=4; else c=1;
            for (j=0;j<c;++j){
            do {
                if (curr_menu->menu[gui_menu_curr_item+1].text) {
                    int i;
                    for (i=0; i<num_lines-1 && curr_menu->menu[gui_menu_top_item+i].text; ++i);
                    if (i==num_lines-1 && curr_menu->menu[gui_menu_top_item+i].text 
                        && gui_menu_top_item+i-1==gui_menu_curr_item && curr_menu->menu[gui_menu_top_item+i+1].text)
                        ++gui_menu_top_item;
                    ++gui_menu_curr_item;
                } else {
                    gui_menu_curr_item = gui_menu_top_item = 0;
                }
            } while ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_TEXT || 
                     (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_SEPARATOR);
            int_incr = 1;
            gui_menu_redraw=1;
            if (curr_menu->title == LANG_MENU_USER_MENU) gui_menu_add_item = gui_menu_curr_item;
			}
            break;
        case KEY_LEFT:
            if (gui_menu_curr_item>=0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK) {
                    case MENUITEM_INT:
						{
						if (kbd_is_key_pressed(KEY_ZOOM_OUT)) {
						int_incr=10;
						incr_modified=1;
						}
						if (kbd_is_key_pressed(KEY_ZOOM_IN)) {
						int_incr=100;
						incr_modified=1;
						}
						if (kbd_is_key_pressed(KEY_SHOOT_HALF)) {
						int_incr=1000;
						incr_modified=1;
						}
						}
                        switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) {
                            case MENUITEM_ARG_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) -= curr_menu->menu[gui_menu_curr_item].arg;
                                break;
                            case MENUITEM_ARG_ADDR_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) -= *(int *)(curr_menu->menu[gui_menu_curr_item].arg);
                                break;
                            default:
                                *(curr_menu->menu[gui_menu_curr_item].value) -= int_incr;
                                break;
                        }
                        if (*(curr_menu->menu[gui_menu_curr_item].value) < -9999) 
                            *(curr_menu->menu[gui_menu_curr_item].value) = -9999;
                        if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_UNSIGNED) {
                            if (*(curr_menu->menu[gui_menu_curr_item].value) < 0) 
                                *(curr_menu->menu[gui_menu_curr_item].value) = 0;
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MIN) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) < (unsigned short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (unsigned short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF);
                            }
                        } else {
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MIN) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) < (short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (short)(curr_menu->menu[gui_menu_curr_item].arg & 0xFFFF);
                            }
                        }
                        if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) == MENUITEM_ARG_CALLBACK && curr_menu->menu[gui_menu_curr_item].arg) {
                            ((void (*)())(curr_menu->menu[gui_menu_curr_item].arg))();
                        }
                        if (curr_menu->on_change) {
                            curr_menu->on_change(gui_menu_curr_item);
                        }
                        if (incr_modified) {
						int_incr=1;
						incr_modified=0;
						draw_string(FONT_WIDTH*2,0,"    ", MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
						}
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_ENUM:
                        if (curr_menu->menu[gui_menu_curr_item].value) {
							int c;
							if (kbd_is_key_pressed(KEY_SHOOT_HALF)) c=3;
							else if (kbd_is_key_pressed(KEY_ZOOM_IN)) c=6;
							else if (kbd_is_key_pressed(KEY_ZOOM_OUT)) c=3;
							else c=1;
							((const char* (*)(int change, int arg))(curr_menu->menu[gui_menu_curr_item].value))(-c, curr_menu->menu[gui_menu_curr_item].arg);
                        }
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_UP:
                        gui_menu_back();
                        break;
                }
            } else {
                gui_menu_back();
            }
            break;
        case KEY_RIGHT:
            if (gui_menu_curr_item>=0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK){
                    case MENUITEM_INT:
						{
						if (kbd_is_key_pressed(KEY_ZOOM_OUT)) {
						int_incr=10;
						incr_modified=1;
						}
						if (kbd_is_key_pressed(KEY_ZOOM_IN)) {
						int_incr=100;
						incr_modified=1;
						}
						if (kbd_is_key_pressed(KEY_SHOOT_HALF)) {
						int_incr=1000;
						incr_modified=1;
						}
						}
                        switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) {
                            case MENUITEM_ARG_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) += curr_menu->menu[gui_menu_curr_item].arg;
                                break;
                            case MENUITEM_ARG_ADDR_INC:
                                *(curr_menu->menu[gui_menu_curr_item].value) += *(int *)(curr_menu->menu[gui_menu_curr_item].arg);
                                break;
                            default:
                                *(curr_menu->menu[gui_menu_curr_item].value) += int_incr;
                                break;
                        }
                        if (*(curr_menu->menu[gui_menu_curr_item].value) > 99999) 
                            *(curr_menu->menu[gui_menu_curr_item].value) = 99999;
                        if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_UNSIGNED) {
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MAX) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) > (unsigned short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (unsigned short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF);
                            }
                        } else {
                            if ( curr_menu->menu[gui_menu_curr_item].type & MENUITEM_F_MAX) {
                                if (*(curr_menu->menu[gui_menu_curr_item].value) > (short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF)) 
                                    *(curr_menu->menu[gui_menu_curr_item].value) = (short)((curr_menu->menu[gui_menu_curr_item].arg>>16) & 0xFFFF);
                            }
                        }
                        if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) == MENUITEM_ARG_CALLBACK && curr_menu->menu[gui_menu_curr_item].arg) {
                            ((void (*)())(curr_menu->menu[gui_menu_curr_item].arg))();
                        }
                        if (curr_menu->on_change) {
                            curr_menu->on_change(gui_menu_curr_item);
                        }
                        if (incr_modified) {
						int_incr=1;
						incr_modified=0;
						draw_string(FONT_WIDTH*2,0,"    ", MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
						}
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_ENUM:
                        if (curr_menu->menu[gui_menu_curr_item].value) {
							int c;
							if (kbd_is_key_pressed(KEY_SHOOT_HALF)) c=3;
							else if (kbd_is_key_pressed(KEY_ZOOM_IN)) c=6;
							else if (kbd_is_key_pressed(KEY_ZOOM_OUT)) c=3;
							else c=1;
							((const char* (*)(int change, int arg))(curr_menu->menu[gui_menu_curr_item].value))(+c, curr_menu->menu[gui_menu_curr_item].arg);
                        }
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_SUBMENU:
                        gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
                        gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
                        gui_menu_stack[gui_menu_stack_ptr].toppos = gui_menu_top_item;
                        gui_menu_set_curr_menu((CMenu*)(curr_menu->menu[gui_menu_curr_item].value), 0, 0);
                        gui_menu_stack_ptr++;
                        // FIXME check on stack overrun;
                        if (gui_menu_stack_ptr > MENUSTACK_MAXDEPTH){
                            draw_txt_string(0, 0, "E1", MAKE_COLOR(COLOR_RED, COLOR_YELLOW));
                            gui_menu_stack_ptr = 0;
                        }
                        gui_menu_redraw=2;
                        draw_restore();
                        gui_force_restore();
                        break;
                }
            }
            break;
        case KEY_SET:
            if (gui_menu_curr_item>=0) {
                switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK){
                    case MENUITEM_INT:
                        switch (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) {
							default:
                                if (kbd_is_key_pressed(KEY_SHOOT_HALF)) *(curr_menu->menu[gui_menu_curr_item].value) = 0;
								break;
						}
						gui_menu_redraw=1;
						break;
                    case MENUITEM_BOOL:
                        *(curr_menu->menu[gui_menu_curr_item].value) =
                                !(*(curr_menu->menu[gui_menu_curr_item].value));
                        if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_ARG_MASK) == MENUITEM_ARG_CALLBACK && curr_menu->menu[gui_menu_curr_item].arg) {
                            ((void (*)())(curr_menu->menu[gui_menu_curr_item].arg))();
                        }
                        if (curr_menu->on_change) {
                            curr_menu->on_change(gui_menu_curr_item);
                        }
                        gui_menu_redraw=1;
                        break;
                    case MENUITEM_PROC:
                    	if (curr_menu->menu[gui_menu_curr_item].value) {
                            ((void (*)(int arg))(curr_menu->menu[gui_menu_curr_item].value))(curr_menu->menu[gui_menu_curr_item].arg);
                            if (curr_menu->on_change) {
                                curr_menu->on_change(gui_menu_curr_item);
                            }
                            //gui_menu_set_curr_menu(curr_menu, 0, 0); // restore this if it causes problems
                            gui_menu_redraw=2;
                        }
                        break;
                    case MENUITEM_SUBMENU:
                        gui_menu_stack[gui_menu_stack_ptr].menu = curr_menu;
                        gui_menu_stack[gui_menu_stack_ptr].curpos = gui_menu_curr_item;
                        gui_menu_stack[gui_menu_stack_ptr].toppos = gui_menu_top_item;
                        gui_menu_set_curr_menu((CMenu*)(curr_menu->menu[gui_menu_curr_item].value), 0, 0);
                        gui_menu_stack_ptr++;
                        // FIXME check on stack overrun;
                        if (gui_menu_stack_ptr > MENUSTACK_MAXDEPTH){
                            draw_txt_string(0, 0, "E1", MAKE_COLOR(COLOR_RED, COLOR_YELLOW));
                            gui_menu_stack_ptr = 0;
                        }
                        gui_menu_redraw=2;
                        draw_restore();
                        gui_force_restore();
                        break;
                    case MENUITEM_UP:
                        gui_menu_back();
                        break;
                    case MENUITEM_COLOR_FG:
                    case MENUITEM_COLOR_BG:
                        draw_restore();
                        item_color=((unsigned char*)(curr_menu->menu[gui_menu_curr_item].value)) + (((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?1:0);
                        gui_palette_init(PALETTE_MODE_SELECT, (*item_color)&0xFF, gui_menu_color_selected);
                        gui_set_mode(GUI_MODE_PALETTE);
                        gui_menu_redraw=2;
                        break;
                    case MENUITEM_ENUM:
                        if (curr_menu->menu[gui_menu_curr_item].value) {
                            ((const char* (*)(int change, int arg))(curr_menu->menu[gui_menu_curr_item].value))(+1, curr_menu->menu[gui_menu_curr_item].arg);
                        }
                        gui_menu_redraw=1;
                        break;
                }
            }
            break;

#if CAM_HAS_ZOOM_LEVER
        case KEY_ZOOM_IN:
            if (int_incr >= 10){
                int_incr /= 10;
            }
            sprintf(sbuf, "±%d",int_incr);
            draw_string(FONT_WIDTH*2,0,"    ", MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
            draw_string(0,0,sbuf,MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG));
            break;

        case KEY_ZOOM_OUT:
            if (int_incr <= 1000){
                int_incr *= 10;
            }
            sprintf(sbuf, "±%d",int_incr);
            draw_string(0,0,sbuf,MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG));
            break;

        case KEY_DISPLAY:
            if (gui_menu_stack_ptr > 0){
                gui_menu_stack_ptr--;
                gui_menu_set_curr_menu(gui_menu_stack[gui_menu_stack_ptr].menu, gui_menu_stack[gui_menu_stack_ptr].toppos, gui_menu_stack[gui_menu_stack_ptr].curpos);
                gui_menu_redraw=2;
                draw_restore();
                gui_force_restore();
            }
            break;
#else
        case KEY_DISPLAY:
            if (conf.user_menu_enable == 3 && curr_menu->title == LANG_MENU_USER_MENU) {
               if (gui_menu_stack_ptr > 0){
                  gui_menu_stack_ptr--;
                  gui_menu_set_curr_menu(gui_menu_stack[gui_menu_stack_ptr].menu, gui_menu_stack[gui_menu_stack_ptr].toppos, gui_menu_stack[gui_menu_stack_ptr].curpos);
                  gui_menu_redraw=2;
                  draw_restore();
                  gui_force_restore();
               }
            }
            else {
               if (int_incr <= 1000){
                  int_incr *= 10;
               }
               else {
                  int_incr = 1;
               }
               sprintf(sbuf, "±%d",int_incr);
               if (int_incr == 1) {
                  draw_string(FONT_WIDTH*2,0,"    ", MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
               }
               draw_string(0,0,sbuf,MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG));
               break;
            }
#endif
    }
}

//-------------------------------------------------------------------
void gui_menu_draw_initial() { 
    color cl=conf.menu_title_color>>8; 
    unsigned char wplus=0; 

    for (count=0; curr_menu->menu[count].text; ++count); 
    if (count>num_lines) {
      y = ((screen_height-(num_lines-1)*rbf_font_height())>>1);
      wplus=8; 
      // scrollbar background 
      draw_filled_rect((x+w), y, (x+w)+wplus, y+num_lines*rbf_font_height()-1, MAKE_COLOR((conf.menu_color>>8)&0xFF, (conf.menu_color>>8)&0xFF)); 
    } else {
      if (conf.menu_center) {
        y = (screen_height-(count-1)*rbf_font_height())>>1; 
      } else {
        y = ((screen_height-(num_lines-1)*rbf_font_height())>>1);  
      }
    }
    if (conf.menu_symbol_enable)
      rbf_draw_string_center_len(x, y-rbf_font_height(), w+wplus, curr_menu->symbol, lang_str(curr_menu->title), conf.menu_title_color);
    else
      rbf_draw_string_center_len(x, y-rbf_font_height(), w+wplus, 0x0, lang_str(curr_menu->title), conf.menu_title_color);    
//    if (cl!=COLOR_FG) 
//      draw_line(x,y-1,x+w-1+wplus,y-1,COLOR_FG); 
}
//-------------------------------------------------------------------
void gui_menu_draw() {
    static char tbuf[64];
    int imenu, i, j, yy, xx, symbol_width;
    color cl, cl_symbol;
    const char *ch = "";

    if (gui_menu_redraw) {
        if (gui_menu_redraw==2)
            gui_menu_draw_initial();

        gui_menu_redraw=0;

        for (imenu=gui_menu_top_item, i=0, yy=y; curr_menu->menu[imenu].text && i<num_lines; ++imenu, ++i, yy+=rbf_font_height()){
            cl = (gui_menu_curr_item==imenu)?conf.menu_cursor_color:conf.menu_color;
            cl_symbol=(gui_menu_curr_item==imenu)?MAKE_COLOR((cl>>8)&0xFF,(conf.menu_symbol_color>>8)&0xFF):conf.menu_symbol_color; //color 8Bit=Hintergrund 8Bit=Vordergrund
            xx = x;

            switch (curr_menu->menu[imenu].type & MENUITEM_MASK) {
            case MENUITEM_BOOL:
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_char(xx, yy, ' ', cl_symbol);
                  xx+=symbol_width=rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
                  symbol_width+=len_space;
                } else {
                  symbol_width=0;
                }
                xx+=rbf_draw_char(xx, yy, ' ', cl);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-len_space-len_br1-len_bool-len_br2-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
                xx+=rbf_draw_string(xx, yy, " [", cl);
                xx+=rbf_draw_string_len(xx, yy, len_bool, (*(curr_menu->menu[imenu].value))?"\x95":"", cl);
                rbf_draw_string(xx, yy, "] ", cl);
                break;
            case MENUITEM_INT:
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_char(xx, yy, ' ', cl_symbol);
                  xx+=symbol_width=rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
                  symbol_width+=len_space;
                } else {
                  symbol_width=0;
                }
                xx+=rbf_draw_char(xx, yy, ' ', cl);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-len_space-len_br1-len_int-len_br2-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
                xx+=rbf_draw_string(xx, yy, " [", cl);
                sprintf(tbuf, "%d", *(curr_menu->menu[imenu].value));
                xx+=rbf_draw_string_right_len(xx, yy, len_int, tbuf, cl);
                rbf_draw_string(xx, yy, "] ", cl);
                break;
            case MENUITEM_SUBMENU:
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_char(xx, yy, ' ', cl_symbol);
                  xx+=symbol_width=rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
                  symbol_width+=len_space+symbol_width;
                  sprintf(tbuf, "%s", lang_str(curr_menu->menu[imenu].text));
                } else {
                  sprintf(tbuf, "%s ->", lang_str(curr_menu->menu[imenu].text));
                  symbol_width=0;
                }
                xx+=rbf_draw_char(xx, yy, ' ', cl);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-len_space-symbol_width, tbuf, cl);
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_symbol(xx, yy, 0x52, cl_symbol);
                  rbf_draw_char(xx, yy, ' ', cl_symbol);
                } else rbf_draw_char(xx, yy, ' ', cl);
                break;
            case MENUITEM_UP:
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_char(xx, yy, ' ', cl_symbol);
                  xx+=symbol_width=rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
                  symbol_width+=len_space;
                  sprintf(tbuf, "%s", lang_str(curr_menu->menu[imenu].text));
                } else {
                  symbol_width=0;
                  sprintf(tbuf, "<- %s", lang_str(curr_menu->menu[imenu].text));
                }
                xx+=rbf_draw_char(xx, yy, ' ', cl);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-len_space-symbol_width, tbuf, cl);
                rbf_draw_char(xx, yy, ' ', cl);
                break;
            case MENUITEM_PROC:
            case MENUITEM_TEXT:
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_char(xx, yy, ' ', cl_symbol);
                  xx+=symbol_width=rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
                  symbol_width+=len_space;
                } else {
                  symbol_width=0;
                }
                xx+=rbf_draw_char(xx, yy, ' ', cl);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
                rbf_draw_char(xx, yy, ' ', cl);
                break;
            case MENUITEM_SEPARATOR:
                if (lang_str(curr_menu->menu[imenu].text)[0]) {
                    j = rbf_str_width(lang_str(curr_menu->menu[imenu].text));
                    xx+=(w-j-len_space*2)>>1;

                    (conf.menu_symbol_enable)?rbf_draw_char(x, yy, ' ', cl_symbol):rbf_draw_char(x, yy, ' ', cl);
                    draw_filled_rect(x+len_space, yy, xx-1, yy+rbf_font_height()/2-1, MAKE_COLOR(cl>>8, cl>>8));
                    draw_line(x+len_space, yy+rbf_font_height()/2, xx-1, yy+rbf_font_height()/2, cl);
                    draw_filled_rect(x+len_space, yy+rbf_font_height()/2+1, xx-1, yy+rbf_font_height()-1, MAKE_COLOR(cl>>8, cl>>8));

                    xx+=rbf_draw_char(xx, yy, ' ', cl);
                    xx+=rbf_draw_string(xx, yy, lang_str(curr_menu->menu[imenu].text), cl);
                    xx+=rbf_draw_char(xx, yy, ' ', cl);
                    
                    draw_filled_rect(xx, yy, x+w-len_space-1, yy+rbf_font_height()/2-1, MAKE_COLOR(cl>>8, cl>>8));
                    draw_line(xx, yy+rbf_font_height()/2, x+w-1-len_space, yy+rbf_font_height()/2, cl);
                    draw_filled_rect(xx, yy+rbf_font_height()/2+1, x+w-len_space-1, yy+rbf_font_height()-1, MAKE_COLOR(cl>>8, cl>>8));
                    rbf_draw_char(x+w-len_space, yy, ' ', cl);
                } else {
                    rbf_draw_char(x, yy, ' ', cl);
                    draw_filled_rect(x+len_space, yy, x+w-len_space-1, yy+rbf_font_height()/2-1, MAKE_COLOR(cl>>8, cl>>8));
                    draw_line(x+len_space, yy+rbf_font_height()/2, x+w-1-len_space, yy+rbf_font_height()/2, cl);
                    draw_filled_rect(x+len_space, yy+rbf_font_height()/2+1, x+w-len_space-1, yy+rbf_font_height()-1, MAKE_COLOR(cl>>8, cl>>8));
                    rbf_draw_char(x+w-len_space, yy, ' ', cl);
                }
                break;
            case MENUITEM_COLOR_FG:
            case MENUITEM_COLOR_BG:
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_char(xx, yy, ' ', cl_symbol);
                  xx+=symbol_width=rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
                  symbol_width+=len_space;
                } else {
                  symbol_width=0;
                }
                xx+=rbf_draw_char(xx, yy, ' ', cl);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
                draw_filled_round_rect(x+w-1-cl_rect-2-len_space, yy+2, x+w-1-2-len_space, yy+rbf_font_height()-1-2, 
                                 MAKE_COLOR(((*(curr_menu->menu[imenu].value))>>(((curr_menu->menu[imenu].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?8:0))&0xFF, 
                                            ((*(curr_menu->menu[imenu].value))>>(((curr_menu->menu[imenu].type & MENUITEM_MASK)==MENUITEM_COLOR_BG)?8:0))&0xFF));
                break;
            case MENUITEM_ENUM:
                if (curr_menu->menu[imenu].value) {
                    ch=((const char* (*)(int change, int arg))(curr_menu->menu[imenu].value))(0, curr_menu->menu[imenu].arg);
                }
                if (conf.menu_symbol_enable) {
                  xx+=rbf_draw_char(xx, yy, ' ', cl_symbol);
                  xx+=symbol_width=rbf_draw_symbol(xx, yy, curr_menu->menu[imenu].symbol, cl_symbol);
                  symbol_width+=len_space;
                } else {
                  symbol_width=0;
                }
                xx+=rbf_draw_char(xx, yy, ' ', cl);
                xx+=rbf_draw_string_len(xx, yy, w-len_space-len_space-len_br1-len_enum-len_br2-len_space-symbol_width, lang_str(curr_menu->menu[imenu].text), cl);
                xx+=rbf_draw_string(xx, yy, " [", cl);
                xx+=rbf_draw_string_right_len(xx, yy, len_enum, ch, cl);
                rbf_draw_string(xx, yy, "] ", cl);
                break;
            }
        }
        
        // scrollbar
        if (count>num_lines) {
            i=num_lines*rbf_font_height()-1 -1;           // full height
            j=i*num_lines/count;                    // bar height
            if (j<20) j=20;
            i=(i-j)*((gui_menu_curr_item<0)?0:gui_menu_curr_item)/(count-1);   // top pos
            draw_filled_round_rect((x+w)+2, y+1, 
                             (x+w)+6, y+1+i, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_round_rect((x+w)+2, y+i+j, 
                             (x+w)+6, y+num_lines*rbf_font_height()-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_round_rect((x+w)+2, y+1+i, 
                             (x+w)+6, y+i+j, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
//        } else {
//            draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1, 
//                             (x+w)*FONT_WIDTH+6, (y+count)*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
        }
    }
}









