#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEY_UP		1
#define KEY_DOWN	2
#define KEY_LEFT	3
#define KEY_RIGHT	4
#define KEY_SET		5
#define KEY_SHOT_HALF	6
#define KEY_SHOT_FULL	7
#define KEY_ZOOM_IN	8
#define KEY_ZOOM_OUT	9
#define KEY_MENU	10
#define KEY_DISPLAY	11
#define KEY_PRINT	12
#define KEY_ERASE	13

extern void gui_kbd_process();
extern void gui_kbd_enter();
extern void gui_kbd_leave();

#endif

