
#include <stdlib.h>

#include "../generic/kbd.c"

static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ KEY_UP	, 0x00000001 },
	{ KEY_DOWN	, 0x00000002 },
	{ KEY_LEFT	, 0x00000008 },
	{ KEY_RIGHT	, 0x00000004 },
	{ KEY_SET	, 0x00000100 },
	{ KEY_SHOOT_FULL, 0x00000030 }, // note 3 here!
	{ KEY_SHOOT_HALF, 0x00000010 },
	{ KEY_ZOOM_IN	, 0x00000040 },
	{ KEY_ZOOM_OUT	, 0x00000080 },
	{ KEY_MENU	, 0x00000200 },
	{ KEY_DISPLAY	, 0x00000400 },
	{ KEY_PRINT	, 0x00001000 },
	{ KEY_ERASE	, 0x00000800 },
        { KEY_DUMMY	, 0x00001000 },
	{ 0, 0 }
};

extern void dbg_log(char *str);
void kbd_fetch_data(long *dst)
{
    volatile long *mmio0 = (void*)0xc0220200;
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = *mmio0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 & 0xffff;
/*
    static long old[3] = {0,0,0};

    if (old[0] != dst[0] || old[1] != dst[1] || old[2] != dst[2]) {
      char str[300];

      sprintf(str, "dst[0] = 0x%08X, dst[1] = 0x%08X, dst[2] = 0x%08X\n", dst[0], dst[1], dst[2]);

      dbg_log(str);

      old[0] = dst[0];
      old[1] = dst[1];
      old[2] = dst[2];
    }
*/
}

