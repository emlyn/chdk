#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEY_UP            1
#define KEY_DOWN          2
#define KEY_LEFT          3
#define KEY_RIGHT         4
#define KEY_SET           5
#define KEY_SHOOT_HALF    6
#define KEY_SHOOT_FULL    7
#define KEY_ZOOM_IN       8
#define KEY_ZOOM_OUT      9
#define KEY_MENU          10
#define KEY_DISPLAY       11
#define KEY_PRINT         12    // S-series: Shortcut
#define KEY_ERASE         13    // S-series: Func
#define KEY_ISO           14    // S-series
#define KEY_FLASH         15    // S-series
#define KEY_MF            16    // S-series
#define KEY_MACRO         17    // S-series
#define KEY_VIDEO         18    // S-series
#define KEY_TIMER         19    // S-series
#define KEY_EXPO_CORR     20    // G-series
#define KEY_MICROPHONE    21
#define KEY_FACE          22    // SX100IS
#define KEY_DUMMY         23    // dummy key for pressing to disable energy saving in alt mode

// SX30
#define KEY_ZOOM_IN1	  24	// SX30 has three zoom speeds each way
#define KEY_ZOOM_IN2	  25
#define KEY_ZOOM_IN3	  26
#define KEY_ZOOM_OUT1	  27
#define KEY_ZOOM_OUT2	  28
#define KEY_ZOOM_OUT3	  29
#define	KEY_ZOOM_ASSIST	  30	// SX30 new button

// G12
#define	KEY_AE_LOCK		  31	// G12 AE/FE Lock button
#define	KEY_METERING	  32	// G12 metering mode button

#define JOGDIAL_LEFT      100
#define JOGDIAL_RIGHT     101

extern void gui_kbd_process();
extern void gui_kbd_enter();
extern void gui_kbd_leave();
extern void other_kbd_process();

#endif
