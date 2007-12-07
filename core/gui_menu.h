#ifndef GUI_MENU_H
#define GUI_MENU_H

//-------------------------------------------------------------------
#define MENUITEM_MASK           0x000f
#define MENUITEM_BOOL           1
#define MENUITEM_INT            2
#define MENUITEM_SUBMENU        3
#define MENUITEM_PROC           4
#define MENUITEM_UP             5
#define MENUITEM_TEXT           6
#define MENUITEM_SEPARATOR      7
#define MENUITEM_ENUM           8
#define MENUITEM_COLOR_BG       9
#define MENUITEM_COLOR_FG       10

#define MENUITEM_F_MASK         0x00f0
#define MENUITEM_F_UNSIGNED     0x0010
#define MENUITEM_F_MIN          0x0020
#define MENUITEM_F_MAX          0x0040
#define MENUITEM_F_MINMAX       0x0060

#define MENUITEM_ARG_MASK       0x0f00
#define MENUITEM_ARG_INC        0x0100
#define MENUITEM_ARG_ADDR_INC   0x0200
#define MENUITEM_ARG_CALLBACK   0x0300

#define MENU_MINMAX(min, max)   (((max)<<16)|(min))

//-------------------------------------------------------------------
typedef struct {
    int                 text;
    int                 type;
    int                 *value;
    int                 arg;
} CMenuItem;

typedef struct {
    int                 title;
    void                (*on_change)(unsigned int item);
    const CMenuItem     *menu;
} CMenu;


//-------------------------------------------------------------------
extern void gui_menu_init(CMenu *menu_ptr);
extern void gui_menu_kbd_process();
extern void gui_menu_draw();

//-------------------------------------------------------------------
#endif
