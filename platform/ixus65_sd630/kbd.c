#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"

#define KEY_MASK 0x17FF

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#define FEATURE_FEATHER 1

typedef struct {
    long hackkey;
    long canonkey;
} KeyMap;

long kbd_new_state[3];
long kbd_prev_state[3];
long kbd_mod_state = KEY_MASK;
long debug_kbd_state_diff;

static KeyMap keymap[];
static long last_kbd_key = 0;
static int usb_power=0;

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

long __attribute__((naked)) wrap_kbd_p1_f() ;

static void __attribute__((noinline)) hook_kbd_task_proceed()
{
    while (physw_run){
        _SleepTask(5);

        if (wrap_kbd_p1_f() == 1) // Readout key state via camera function
        {
            _kbd_p2_f();
        }

    }
}

void __attribute__((naked,noinline)) mykbd_task()
{
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     *  function arguments destroyed;
     *  function CAN NOT return properly;
     *  MUST NOT call or use stack variables before stack
     *  is setup properly;
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
        "MOV    SP, %0"
        :: "r"(((char*)newstack)+NEW_SS)
        : "memory"
    );

    hook_kbd_task_proceed();

    /* function can be modified to restore SP here...
     */

    _ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{

    asm volatile(
                "STMFD   SP!, {R4-R7,LR}\n"
                "SUB     SP, SP, #0xC\n"
                "BL      _kbd_read_keys\n"
                "BL      hook_kbd_handle_keys\n"
                "B       _kbd_p1_f_cont\n"        // Continue original function execution
    );
    return 0; // shut up the compiler
}

#if FEATURE_FEATHER
extern int touch_keys_angle;
extern int * touch_keys_sema;
int touch_keys_sema_stored;
#endif

#define IN(base, value) ((value < base + 20) && (value > base - 20))

/**
 * Handles and forwards key settings to key processing routines
 */
void hook_kbd_handle_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    kbd_new_state[0] = physw_status[0];
    kbd_new_state[1] = physw_status[1];
    kbd_new_state[2] = physw_status[2];

/*
    int key_emu = 0;
    int canonkey = 0;
    int i;

    if (IN(250, touch_keys_angle)) {
        key_emu = KEY_RIGHT;
    }
    if (IN(450, touch_keys_angle)) {
        key_emu = KEY_DOWN;
    }
    if (IN(675, touch_keys_angle)) {
        key_emu = KEY_LEFT;
    }
    if (IN(870, touch_keys_angle)) {
        key_emu = KEY_UP;
    }
    
    if (key_emu != 0) {
        for (i=0; keymap[i].hackkey; i++){
            if (keymap[i].hackkey == key_emu) {
                canonkey = keymap[i].canonkey;
                break;;
            }
        }
    }

    if (canonkey != 0) {
        kbd_new_state[2] = kbd_new_state[2] & ~canonkey;
    }
*/
    
    if (kbd_process() == 0){
        // leave it ...
#if FEATURE_FEATHER
        if (*touch_keys_sema == 0) {
            *touch_keys_sema = touch_keys_sema_stored;
        }
#endif
    } else {
        // Drop platform keys to none, and simulate ordered key presses
        physw_status[2] = (physw_status[2] & (~KEY_MASK)) | (kbd_mod_state & KEY_MASK);
#if FEATURE_FEATHER
        if (*touch_keys_sema != 0) {
            touch_keys_sema_stored = *touch_keys_sema;
            *touch_keys_sema = 0;
        }
        // We still need this sema when simulating key presses
        if (kbd_mod_state != KEY_MASK) {
            *touch_keys_sema = touch_keys_sema_stored;
        }
#endif
    }

    // Drop SD readonly status
    physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;

}

/****************/


void kbd_key_press(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            kbd_mod_state &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            kbd_mod_state |= keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release_all()
{
    kbd_mod_state |= KEY_MASK;
}

long kbd_is_key_pressed(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            return ((kbd_new_state[2] & keymap[i].canonkey) == 0) ? 1:0;
        }
    }
    return 0;
}

long kbd_is_key_clicked(long key)
{
    int i;
    
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            return ((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
                    ((kbd_new_state[2] & keymap[i].canonkey) == 0);
        }
    }
    return 0;
}

long kbd_get_pressed_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if ((kbd_new_state[2] & keymap[i].canonkey) == 0){
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_get_clicked_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
            ((kbd_new_state[2] & keymap[i].canonkey) == 0)){
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
            if (t-last_kbd_time > ( press_count ? KBD_REPEAT_DELAY : KBD_INITIAL_DELAY) ) {
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

    if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(12, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_RIGHT);
            zoom_key_pressed = KEY_ZOOM_IN;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_IN) {
            kbd_key_release(KEY_RIGHT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    if (kbd_is_key_pressed(KEY_ZOOM_OUT) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(12, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_LEFT);
            zoom_key_pressed = KEY_ZOOM_OUT;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_OUT) {
            kbd_key_release(KEY_LEFT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    return 0;
}

int get_usb_power(int edge)
{
	return usb_power;
}

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
//	{ KEY_ERASE	, 0x00000800 },
	{ KEY_DUMMY	, 0x00001000 },
	{ 0, 0 }
};
