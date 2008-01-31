#include "lolevel.h"
#include "platform.h"
#include "conf.h"
#include "core.h"
#include "keyboard.h"

typedef struct {
	long hackkey;
	long canonkey;
} KeyMap;


static long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state;
static KeyMap keymap[];
static long last_kbd_key = 0;
static int usb_power=0;
static int remote_key, remote_count;

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)
#if defined(CAMERA_a710)
#define USB_MASK 8
#define USB_REG 0
#endif

#if defined(CAMERA_a630) || defined(CAMERA_a640) || defined(CAMERA_a610) || defined(CAMERA_a620) || defined(CAMERA_ixus800_sd700) || defined(CAMERA_ixus850_sd800) || defined(CAMERA_ixus70_sd1000)
#define USB_MASK 0x8000000
#define USB_REG 1
#endif


#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

long __attribute__((naked)) wrap_kbd_p1_f() ;

static void __attribute__((noinline)) mykbd_task_proceed()
{
    while (physw_run){
	_SleepTask(10);

	if (wrap_kbd_p1_f() == 1){ // autorepeat ?
	    _kbd_p2_f();
	}
    }
}

void __attribute__((naked,noinline)) mykbd_task()
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

    asm volatile(
                "STMFD   SP!, {R4-R7,LR}\n"
                "SUB     SP, SP, #0xC\n"
                "BL      my_kbd_read_keys\n"
		"B	 _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}


void my_kbd_read_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    _kbd_pwr_on();

    kbd_fetch_data(kbd_new_state);

#if 0
    if ((new_state[2] & 0x00001000 /* print button */) == 0 )
	started();
    else
	finished();
#endif


    if (kbd_process() == 0){
	// leave it alone...
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = kbd_new_state[2];
#if 0
	kbd_mod_state = kbd_new_state[2];
#endif
    } else {
	// override keys
#if 0
	physw_status[2] = kbd_mod_state;
#else
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = (kbd_new_state[2] & (~0x1fff)) |
			  (kbd_mod_state & 0x1fff);
#endif
#if defined(USB_MASK) && defined(USB_REG)
		if (conf.remote_enable) {
	physw_status[USB_REG] = kbd_new_state[USB_REG] & ~USB_MASK;
remote_key = (kbd_new_state[USB_REG] & USB_MASK)==USB_MASK;

			if (remote_key) 
				remote_count += 1;
			else if (remote_count) {
				usb_power = remote_count;
				remote_count = 0;
			}
		}
#endif
    }

    _kbd_read_keys_r2(physw_status);
    physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;

    _kbd_pwr_off();

}
int get_usb_power(int edge)
{
	int x;

	if (edge) return remote_key;
	x = usb_power;
	usb_power = 0;
	return x;
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
    kbd_mod_state |= 0x1fff;
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

    if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
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
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
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



