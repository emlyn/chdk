#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"

typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;


static long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state[3];
long physw_copy[3];
static KeyMap keymap[];
static long last_kbd_key = 0;
static long alt_mode_key_mask = 0x00004000;

#define KEYS_MASK0 (0x00000003)
#define KEYS_MASK1 (0x5f7f7038)
#define KEYS_MASK2 (0x00000000)

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

extern void _platformsub_kbd_fetch_data(long*);
long __attribute__((naked)) wrap_kbd_p1_f();
void __attribute__((naked,noinline)) mykbd_task_proceed_2();
extern void h_kbd_p2_f();


static void __attribute__((noinline)) mykbd_task_proceed()
{
    asm volatile(
                 "STMFD   SP!, {R4-R6,LR}\n"
                 "SUB     SP, SP, #4\n"
                 "ADD     R6, SP, #2\n"
		 "B	  mykbd_task_proceed_2\n"
	);
}


void mykbd_task_proceed_2()
{
    asm volatile(
  "loc_FF82934C:"
                 "MOV     R0, #0xA\n"
                 "BL      _SleepTask\n"
                 "BL      wrap_kbd_p1_f\n"
                 "MOV     R5, R0\n"
                 "CMP     R5, #1\n"
	         "BNE     loc_FF82934C\n"
		 "B	  h_kbd_p2_f\n"
	);
}


void __attribute__((naked,noinline))
mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf)
{
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     *	function arguments destroyed;
     *	function CAN NOT return properly;
     *	MUST NOT call or use stack variables before stack
     *	is setup properly;
     *
     */

    register int i;
    register long *newstack;

#ifndef MALLOCD_STACK
    newstack = (void*)kbd_stack;
#else
    newstack = malloc(NEW_SS);
#endif

    for (i=0;i<NEW_SS/4;i++)
	newstack[i]=0xdededede;

    asm volatile (
	"MOV	SP, %0"
	:: "r"(((char*)newstack)+NEW_SS)
	: "memory"
    );

    mykbd_task_proceed();

    /* function can be modified to restore SP here...
     */

    _ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    asm volatile(
                "STMFD   SP!, {R4-R10,LR}\n"
                "LDR     R4, =physw_status-0x30\n"
                "MOV     R0, R4\n"
                "SUB     SP, SP, #0x18\n"
                "BL      my_kbd_read_keys\n"
    );

//    physw_status[0] = physw_status[0] & ~SD_READONLY_FLAG;

    asm volatile(
		"B	 _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}


void __attribute__((naked,noinline)) my_kbd_read_keys()
{
    asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n"
                "LDR     R3, =kbd_const_1\n"
                "SUB     SP, SP, #0x18\n"
                "MOV     R5, R0\n"
                "ADD     R0, SP, #0x0C\n"
                "LDR     R4, [R3]\n"
                "BL      _platformsub_kbd_fetch_data\n"
                "ADD     R0, SP, #0x0C\n"
                "BL      my_kbd_read_keys_cont\n"
		"B	 _kbd_read_keys_r2\n"
    );
}


void my_kbd_read_keys_cont(long *canon_key_state)
{
    kbd_new_state[0] = canon_key_state[0];
    kbd_new_state[1] = canon_key_state[1];
    kbd_new_state[2] = canon_key_state[2];

    kbd_new_state[0] = kbd_new_state[0] & ~SD_READONLY_FLAG;

    physw_copy[0] = kbd_new_state[0];
    physw_copy[1] = kbd_new_state[1];
    physw_copy[2] = kbd_new_state[2];

    if (kbd_process() == 0){
	// leave it alone...
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = kbd_new_state[2];
        physw_status[1] |= alt_mode_key_mask;
    } else {
	// override keys
	physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |
			  (kbd_mod_state[0] & KEYS_MASK0);

	physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) |
			  (kbd_mod_state[1] & KEYS_MASK1);

	physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |
			  (kbd_mod_state[2] & KEYS_MASK2);
    }

    canon_key_state[0] = physw_status[0];
    canon_key_state[1] = physw_status[1];
    canon_key_state[2] = physw_status[2];
}


/****************/

void kbd_set_alt_mode_key_mask(long key)
{
    int i;
    for (i=0; keymap[i].hackkey; ++i) {
	if (keymap[i].hackkey == key) {
	    alt_mode_key_mask = keymap[i].canonkey;
	    return;
	}
    }
}

void kbd_key_press(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
	    return;
	}
    }
}

void kbd_key_release(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
	    return;
	}
    }
}

void kbd_key_release_all()
{
  kbd_mod_state[0] |= KEYS_MASK0;
  kbd_mod_state[1] |= KEYS_MASK1;
  kbd_mod_state[2] |= KEYS_MASK2;
}

long kbd_is_key_pressed(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
	}
    }
    return 0;
}

long kbd_is_key_clicked(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
		    ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
	}
    }
    return 0;
}

long kbd_get_pressed_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0){
	    return keymap[i].hackkey;
	}
    }
    return 0;
}

long kbd_get_clicked_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
	    ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)){
	    return keymap[i].hackkey;
	}
    }
    return 0;
}

void kbd_reset_autoclicked_key() {
    last_kbd_key = 0;
}

long kbd_get_autoclicked_key() {
    static long last_kbd_time = 0, press_count = 0;
    register long key, t;

    key=kbd_get_clicked_key();
    if (key) {
        last_kbd_key = key;
        press_count = 0;
        last_kbd_time = get_tick_count();
        return key;
    } else {
        if (last_kbd_key && kbd_is_key_pressed(last_kbd_key)) {
            t = get_tick_count();
            if (t-last_kbd_time>((press_count)?175:500)) {
                ++press_count;
                last_kbd_time = t;
                return last_kbd_key;
            } else {
                return 0;
            }
        } else {
            last_kbd_key = 0;
            return 0;
        }
    }
}

long kbd_use_zoom_as_mf() {
    static long v;
    static long zoom_key_pressed = 0;

    if (kbd_is_key_pressed(KEY_ZOOM_IN) && kbd_is_key_pressed(KEY_MF) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(12, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_MF);
            kbd_key_press(KEY_UP);
            zoom_key_pressed = KEY_ZOOM_IN;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_IN) {
            kbd_key_release(KEY_UP);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    if (kbd_is_key_pressed(KEY_ZOOM_OUT) && kbd_is_key_pressed(KEY_MF) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(12, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_MF);
            kbd_key_press(KEY_DOWN);
            zoom_key_pressed = KEY_ZOOM_OUT;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_OUT) {
            kbd_key_release(KEY_DOWN);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    return 0;
}

static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ 1, KEY_UP		, 0x00020000 },
	{ 1, KEY_DOWN		, 0x00080000 },
	{ 1, KEY_LEFT		, 0x00010000 },
	{ 1, KEY_RIGHT		, 0x00040000 },
	{ 1, KEY_SET		, 0x00100000 },
	{ 0, KEY_SHOOT_FULL	, 0x00000003 },
	{ 0, KEY_SHOOT_HALF	, 0x00000001 },
	{ 1, KEY_ZOOM_IN	, 0x10000000 },
	{ 1, KEY_ZOOM_IN	, 0x18000000 },
	{ 1, KEY_ZOOM_OUT	, 0x01000000 },
	{ 1, KEY_ZOOM_OUT	, 0x05000000 },
	{ 1, KEY_MENU		, 0x00200000 },
	{ 1, KEY_DISPLAY	, 0x00002000 },
	{ 1, KEY_PRINT		, 0x00004000 },
	{ 1, KEY_ERASE		, 0x00400000 },
        { 1, KEY_ISO		, 0x00001000 },
        { 1, KEY_FLASH		, 0x00000008 },
        { 1, KEY_MF		, 0x00000010 },
        { 1, KEY_MACRO		, 0x00000020 },
        { 1, KEY_VIDEO		, 0x40000000 },
        { 1, KEY_TIMER		, 0x02000000 },
//        { 1, KEY_DUMMY   	, 0x00000000 },
	{ 0, 0, 0 }
};
