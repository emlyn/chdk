#ifndef GUI_H
#define GUI_H

typedef unsigned int    coord;
typedef unsigned short 	color;

#define MAKE_COLOR(bg, fg)	((color)((((char)(bg))<<8)|((char)(fg))))

enum Gui_Mode { GUI_MODE_NONE = 0,
                GUI_MODE_ALT,
                GUI_MODE_MENU,
                GUI_MODE_PALETTE,
                GUI_MODE_MBOX,
                GUI_MODE_REVERSI,
                GUI_MODE_SOKOBAN,
                GUI_MODE_DEBUG,
                GUI_MODE_FSELECT,
                GUI_MODE_READ,
                GUI_MODE_OSD,
                GUI_MODE_CALENDAR,
                GUI_MODE_BENCH,
                GUI_MODE_MPOPUP,
                GUI_MODE_4WINS };

extern void gui_redraw();
extern void gui_force_restore();

extern void draw_pixel(coord x, coord y, color cl);

extern enum Gui_Mode gui_get_mode();
extern void gui_set_mode(enum Gui_Mode mode);
extern void gui_update_script_submenu();
#endif
