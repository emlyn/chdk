#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"

typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;


static long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state[3];
static KeyMap keymap[];
static long last_kbd_key = 0;
static long alt_mode_key_mask = 0x00000800;
static int usb_power=0;
static int remote_key, remote_count;

#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 (0x0FFF)

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#define FEATURE_FEATHER 0
#define USB_MASK (0x40000)
#define USB_REG 2 

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

void kbd_fetch_data(long*);

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
	"MOV	SP, %0\n"
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
                "STMFD   SP!, {R1-R5,LR}\n"
                "MOV     R4, #0\n"
                "BL      my_kbd_read_keys\n" 
				//"BL      _kbd_read_keys\n"
               	"B	 _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}

#if FEATURE_FEATHER
extern int touch_keys_angle;
extern int * touch_keys_sema;
int touch_keys_sema_stored;
#endif

//extern void touch_wheel_print_on();
//extern void touch_wheel_print_off();

volatile int jogdial_stopped=0;

void my_kbd_read_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    _kbd_pwr_on();

    kbd_fetch_data(kbd_new_state);

    if (kbd_process() == 0){
		// leave it alone...
		physw_status[0] = kbd_new_state[0];
		physw_status[1] = kbd_new_state[1];
		physw_status[2] = kbd_new_state[2] | alt_mode_key_mask;
		jogdial_stopped=0;

#if FEATURE_FEATHER
        if (*touch_keys_sema == 0) {
            *touch_keys_sema = touch_keys_sema_stored;
        }
#endif
    } else {
		// override keys
		physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |
				  (kbd_mod_state[0] & KEYS_MASK0);

		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) |
				  (kbd_mod_state[1] & KEYS_MASK1);

		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |
				  (kbd_mod_state[2] & KEYS_MASK2);

		if ((jogdial_stopped==0) && !state_kbd_script_run) {
			jogdial_stopped=1; get_jogdial_direction();
		} else if (jogdial_stopped && state_kbd_script_run) {
			jogdial_stopped=0;
		}

#if FEATURE_FEATHER
        if (*touch_keys_sema != 0) {
            touch_keys_sema_stored = *touch_keys_sema;
            *touch_keys_sema = 0;
        }
        // We still need this sema when simulating key presses
        if (/*kbd_mod_state[0] != KEYS_MASK0 || kbd_mod_state[1] != KEYS_MASK1 || */kbd_mod_state[2] != KEYS_MASK2) {
            *touch_keys_sema = touch_keys_sema_stored;
        }
#endif
    }

    _kbd_read_keys_r2(physw_status);

//    physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;


    remote_key = (physw_status[2] & USB_MASK)==USB_MASK;

    if (conf.remote_enable) {
      remote_key = (physw_status[2] & USB_MASK)==USB_MASK;
      if (remote_key)  remote_count += 1;
      else if (remote_count) {
         usb_power = remote_count;
         remote_count = 0;
      }
      physw_status[2] = physw_status[2] & ~(SD_READONLY_FLAG | USB_MASK);
     }
    else physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;

    _kbd_pwr_off();
}


int get_usb_power(int edge)
{
	int x;

	if (edge) return remote_key;
	x = usb_power;
	usb_power = 0;
	return x;
        return 0;
}

/****************/


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


static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ 2, KEY_UP  		, 0x00000080 }, 
	{ 2, KEY_DOWN		, 0x00000040 }, 
	{ 2, KEY_LEFT		, 0x00000010 }, 
	{ 2, KEY_RIGHT		, 0x00000020 }, 
	{ 2, KEY_SET		, 0x00000100 }, 
	{ 2, KEY_SHOOT_FULL	, 0x00000003 },
	{ 2, KEY_SHOOT_HALF	, 0x00000001 }, 
	{ 2, KEY_ZOOM_IN	, 0x00000004 }, 
	{ 2, KEY_ZOOM_OUT	, 0x00000008 }, 
	{ 2, KEY_MENU		, 0x00000400 }, 
	{ 2, KEY_DISPLAY	, 0x00000200 }, 
	{ 2, KEY_PRINT		, 0x00000800 }, 
	{ 0, 0, 0 }
};

static int new_jogdial=0, old_jogdial=0;

int Get_JogDial(void)
{
	// ??? \todo 0xC0240000+0x104 @ FF842A44  // address from sub above aJogdail (sub_FF84B8D8)
	return (*(int*)0xC0240104)>>16;
}

long get_jogdial_direction(void)
{
	old_jogdial=new_jogdial;
	new_jogdial=Get_JogDial();

	if (old_jogdial<new_jogdial) {
		return JOGDIAL_LEFT;
	} else if (old_jogdial>new_jogdial) {
		return JOGDIAL_RIGHT;
	} else {
		return 0;
	}
}

void kbd_fetch_data(long *dst)
{
    volatile long *mmio0 = (void*)0xc0220200;
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = *mmio0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 & 0xffff;
}
