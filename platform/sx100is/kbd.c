#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"

typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;


static long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state[3];

static long last_kbd_key = 0;
static long alt_mode_key_mask = 0x10000000;
static int usb_power=0;
static int remote_key, remote_count;


#define KEYS_MASK0 (0x0000000C)
#define KEYS_MASK1 (0x1F1F0300)
#define KEYS_MASK2 (0x00000000)

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)
#define USB_MASK (0x40000)


#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

static KeyMap keymap[] = {
	/* tiny bug: key order matters. see kbd_get_pressed_key()
	 * for example
	 */
	{ 1, KEY_PRINT    , 0x10000000 },
	{ 1, KEY_ZOOM_IN  , 0x00000100 }, 
	{ 1, KEY_ZOOM_OUT , 0x00000200 }, 
	{ 1, KEY_RIGHT    , 0x00100000 },
	{ 1, KEY_UP       , 0x00020000 },
	{ 1, KEY_DOWN     , 0x00080000 },
	{ 1, KEY_MENU     , 0x02000000 },
	{ 1, KEY_DISPLAY  , 0x04000000 },
	{ 1, KEY_SET      , 0x00010000 },
	{ 1, KEY_ERASE    , 0x01000000 },
	{ 1, KEY_LEFT     , 0x00040000 },
	{ 1, KEY_FACE     , 0x08000000 },

	{ 0, KEY_SHOOT_FULL, 0x0000000C }, 
	{ 0, KEY_SHOOT_HALF, 0x00000004 },

	{ 0, 0 }
};


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
		"STMFD   SP!, {R1-R5,LR}\n"
		"MOV     R4, #0\n"
		"BL      _kbd_read_keys\n"
		"BL      my_kbd_read_keys\n"
		"B       _kbd_p1_f_cont\n"
	);
	return 0; // shut up the compiler
}


void my_kbd_read_keys()
{
	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	// The following three lines replace the call to kbd_fetch_data
	kbd_new_state[0] = physw_status[0];
	kbd_new_state[1] = physw_status[1];
	kbd_new_state[2] = physw_status[2];


	if (kbd_process() == 0){
		// leave it alone...
		// keyboard state is already good so nothing needs to happen

		// But do override the alt mode key
		physw_status[1] |= alt_mode_key_mask;
	} else {
		// override keys
		physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]); // Only overrides shoot-button... off, batt and modeswitch are still enabled.
		physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]); // Overrides everything except mode-dial (0xF)
		physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]); // Currently overrides nothing
	}

	remote_key = (physw_status[2] & USB_MASK)==USB_MASK;
		if (remote_key) 
			remote_count += 1;
		else if (remote_count) {
			usb_power = remote_count;
			remote_count = 0;
		}
	if (conf.remote_enable) {
		physw_status[2] = physw_status[2] & ~(SD_READONLY_FLAG | USB_MASK);
		// As much as I'd like to immediately shoot, this trigger is intended for use in scripts, so don't shoot here.
		//if(remote_key) physw_status[0] &= ~(0x3); // Shoot!
	} else {
		physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;
	}
}



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
		    ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
			return keymap[i].hackkey;
		}
	}
	return 0;
}



void kbd_fetch_data(long *dst)
{
    // This seems to be very different from the other cameras I've seen.
    // Keyboard data seems to be largely unavailable around 0xC0220200 (or in
    // the entire 0xC0200000 range even), everything seems to happen in
    // physw_status. Because of this (physw_status already filled), this function
    // need not be called on S5IS. Candidate for removal if everyone agrees.
    volatile long *mmio0 = (void*)0x10C1C;
    volatile long *mmio1 = (void*)0x10C20;
    volatile long *mmio2 = (void*)0x10C24;

    dst[0] = *mmio0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 ;
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
	static long zoom_key_pressed = 0;

	if (kbd_is_key_pressed(KEY_ZOOM_IN) && kbd_is_key_pressed(KEY_MF) && (mode_get()&MODE_MASK) == MODE_REC) {

		if (shooting_get_focus_mode()) {
			kbd_key_release_all();
			kbd_key_press(KEY_UP);
			kbd_key_press(KEY_MF);
			zoom_key_pressed = KEY_ZOOM_IN;
			return 1;
		}
	} else {
		if (zoom_key_pressed==KEY_ZOOM_IN) {
			kbd_key_release(KEY_UP);
			kbd_key_release(KEY_MF);
			zoom_key_pressed = 0;
			return 1;
		}
	}

	if (kbd_is_key_pressed(KEY_ZOOM_OUT) && kbd_is_key_pressed(KEY_MF)  && (mode_get()&MODE_MASK) == MODE_REC) {
		if (shooting_get_focus_mode()) {
			kbd_key_release_all();
			kbd_key_press(KEY_DOWN);
			kbd_key_press(KEY_MF);
			zoom_key_pressed = KEY_ZOOM_OUT;
			return 1;
		}
	} else {
		if (zoom_key_pressed==KEY_ZOOM_OUT) {
			kbd_key_release(KEY_DOWN);
			kbd_key_release(KEY_MF);
			zoom_key_pressed = 0;
			return 1;
		}
	}
	return 0;
}

int get_usb_power(int edge)
{
	int x;

	if (edge) return remote_key;
	x = usb_power;
	usb_power = 0;
	return x;
}
