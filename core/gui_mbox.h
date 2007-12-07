#ifndef GUI_MBOX_H
#define GUI_MBOX_H

//-------------------------------------------------------------------
#define MBOX_BTN_MASK           0x00FF
#define MBOX_BTN_OK             0x0001
#define MBOX_BTN_YES            0x0002
#define MBOX_BTN_NO             0x0004
#define MBOX_BTN_CANCEL         0x0008
#define MBOX_BTN_YES_NO         0x0006
#define MBOX_BTN_YES_NO_CANCEL  0x000E

#define MBOX_TEXT_MASK          0x0300
#define MBOX_TEXT_LEFT          0x0000
#define MBOX_TEXT_CENTER        0x0100
#define MBOX_TEXT_RIGHT         0x0200

#define MBOX_FUNC_MASK          0x0C00
#define MBOX_FUNC_RESTORE       0x0400

#define MBOX_DEF_MASK           0x3000
#define MBOX_DEF_BTN1           0x0000
#define MBOX_DEF_BTN2           0x1000
#define MBOX_DEF_BTN3           0x2000

//-------------------------------------------------------------------
extern void gui_mbox_init(int title, int msg, const unsigned int flags, void (*on_select)(unsigned int btn));
extern void gui_mbox_kbd_process();
extern void gui_mbox_draw();

//-------------------------------------------------------------------
#endif
