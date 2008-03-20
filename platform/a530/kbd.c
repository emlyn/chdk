#include "../generic/kbd.c"

static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ KEY_UP	, 0x00000001 },//4057FE
	{ KEY_DOWN	, 0x00000002 },//4057FD
	{ KEY_LEFT	, 0x00000008 },	//4057F7
	{ KEY_RIGHT	, 0x00000004 },	//4057FB
	{ KEY_SET	, 0x00000100 },	//4056FF
	{ KEY_SHOOT_FULL, 0x00000030 }, // 4057CF note 3 here!
	{ KEY_SHOOT_HALF, 0x00000010 },	//4057EF
	{ KEY_ZOOM_IN	, 0x00000040 },	//4057BF
	{ KEY_ZOOM_OUT	, 0x00000080 },	//40577F
	{ KEY_MENU	, 0x00000200 },	//4055FF
	{ KEY_DISPLAY	, 0x00000400 },	//4053FF
	{ KEY_PRINT	, 0x00001000 },	//4047FF
	{ KEY_ERASE	, 0x00000800 },
        //{ KEY_DUMMY	, 0x00001000 },
	{ 0, 0 }
};

void kbd_fetch_data(long *dst)
{
    volatile long *mmio0 = (void*)0xc0220200;
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = *mmio0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 & 0xffff;
}
