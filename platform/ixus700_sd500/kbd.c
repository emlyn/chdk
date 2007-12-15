#include "lolevel.h"
#include "platform.h"
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
                 "STMFD   SP!, {R4,LR}\n"
		 "B	  mykbd_task_proceed_2\n"
	);
}




void __attribute__((noinline)) mykbd_task_proceed_2()
{
    asm volatile(
"loc_FF828ED8:\n"
                 "MOV     R0, #0xA\n"
                 "BL      _SleepTask\n"
                 "BL      wrap_kbd_p1_f\n"
                 "CMP     R0, #1\n"
                 "BNE     loc_FF828ED8\n"
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
//    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
//    kbd_prev_state[2] = kbd_new_state[2];

    asm volatile(
                 "STMFD   SP!, {R4-R10,LR}\n"
                 "LDR     R4, =physw_status-0x10\n"
                 "SUB     SP, SP, #0x18\n"
                 "BL      _kbd_p1_1\n"
                 "BL      _kbd_p1_2\n"
                 "MOV     R0, #0x32\n"
                 "BL      _kbd_p1_3\n"
                 "MOV     R0, R4\n"
                 "BL      _platformsub_kbd_fetch_data_my\n"
                 "B       _kbd_p1_f_cont\n"

    );
    return 0; // shut up the compiler
}



long my_kbd_read_keys(long x)
{
 
 kbd_new_state[1]=x & 0xFFFF;
 if (kbd_process() == 0) return x; else return (kbd_new_state[1]&~0x2FFE) | (kbd_mod_state & 0x2FFE);
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
    kbd_mod_state |= 0x2FFE;
}

long kbd_is_key_pressed(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_new_state[1] & keymap[i].canonkey) == 0) ? 1:0;
	}
    }
    return 0;
}

long kbd_is_key_clicked(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_prev_state[1] & keymap[i].canonkey) != 0) &&
		    ((kbd_new_state[1] & keymap[i].canonkey) == 0);
	}
    }
    return 0;
}

long kbd_get_pressed_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if ((kbd_new_state[1] & keymap[i].canonkey) == 0){
	    return keymap[i].hackkey;
	}
    }
    return 0;
}

long kbd_get_clicked_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (((kbd_prev_state[1] & keymap[i].canonkey) != 0) &&
	    ((kbd_new_state[1] & keymap[i].canonkey) == 0)){
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
  return 0;
}

#define USB_MASK 0x40

int usb_power_status_override(int status){
 // for clear USB power flag  - return status &~USB_MASK;
 // for get USB power flag read status & USB_MASK
 return status;
}



static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ KEY_UP	, 0x00000020 },
	{ KEY_DOWN	, 0x00000040 },
	{ KEY_LEFT	, 0x00000080 },
	{ KEY_RIGHT	, 0x00000100 },
	{ KEY_SET	, 0x00000200 },
	{ KEY_SHOOT_FULL, 0x00000006 }, // note 3 here!
	{ KEY_SHOOT_HALF, 0x00000002 },
	{ KEY_ZOOM_IN	, 0x00000008 },
	{ KEY_ZOOM_OUT	, 0x00000010 },
	{ KEY_MENU	, 0x00000400 },
	{ KEY_DISPLAY	, 0x00000800 },
	{ KEY_PRINT	, 0x00002000 },
//	{ KEY_ERASE	, 0x00000800 },
//        { KEY_DUMMY	, 0x10000000 },
	{ 0, 0 }
};

int get_usb_power(int edge) {return usb_power;}
