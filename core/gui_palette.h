#ifndef GUI_PALETTE_H
#define GUI_PALETTE_H

#include "gui.h"

//-------------------------------------------------------------------

#define PALETTE_MODE_DEFAULT    0
#define PALETTE_MODE_SELECT     1

//-------------------------------------------------------------------
extern void gui_palette_init(int mode, color st_color, void (*on_select)(color clr));
extern void gui_palette_kbd_process();
extern void gui_palette_draw();

//-------------------------------------------------------------------
#endif
