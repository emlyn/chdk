#ifndef GUI_MPOPUP_H
#define GUI_MPOPUP_H

//-------------------------------------------------------------------
#define MPOPUP_MASK             0x07FF
#define MPOPUP_CANCEL           0x0800
#define MPOPUP_CUT              0x0001
#define MPOPUP_COPY             0x0002
#define MPOPUP_PASTE            0x0004
#define MPOPUP_DELETE           0x0008
#define MPOPUP_SELINV           0x0010
#define MPOPUP_RAW_ADD		0x0020
#define MPOPUP_RAW_AVERAGE	0x0040
#define MPOPUP_PURGE            0x0080
#define MPOPUP_SUBTRACT         0x0100
#define MPOPUP_RAW_DEVELOP      0x0200
#define MPOPUP_DNG_TO_CRW       0x0400

//-------------------------------------------------------------------
extern void gui_mpopup_init(const unsigned int flags, void (*on_select)(unsigned int actn));
extern void gui_mpopup_kbd_process();
extern void gui_mpopup_draw();

extern void gui_browser_progress_show(const char* msg, const unsigned int perc);

//-------------------------------------------------------------------
#endif
