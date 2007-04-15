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

#define KEYS_MASK1 (0x1d3f6000)
#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

extern void _platformsub_kbd_fetch_data(long*);
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

    _platformsub_kbd_fetch_data(kbd_new_state);

    if (kbd_process() == 0){
	// leave it alone...
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = kbd_new_state[2];
#if 0
	kbd_mod_state = kbd_new_state[1];
#endif
    } else {
	// override keys
#if 0
	physw_status[2] = kbd_mod_state;
#else
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) |
			  (kbd_mod_state & KEYS_MASK1);
	physw_status[2] = kbd_new_state[2];
#endif
    }

    _kbd_read_keys_r2(physw_status);
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
  kbd_mod_state |= KEYS_MASK1;
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

static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ KEY_UP	, 0x00020000 },
	{ KEY_DOWN	, 0x00080000 },
	{ KEY_LEFT	, 0x00010000 },
	{ KEY_RIGHT	, 0x00040000 },
	{ KEY_SET	, 0x00100000 },
//	{ KEY_SHOOT_FULL, 0x00000000 },
//	{ KEY_SHOOT_HALF, 0x00000000 },
	{ KEY_ZOOM_IN	, 0x10000000 },
	{ KEY_ZOOM_IN	, 0x08000000 },
	{ KEY_ZOOM_OUT	, 0x01000000 },
	{ KEY_ZOOM_OUT	, 0x05000000 },
	{ KEY_MENU	, 0x00200000 },
	{ KEY_DISPLAY	, 0x00002000 },
	{ KEY_PRINT	, 0x00004000 },
	{ KEY_ERASE	, 0x04000000 },
	{ 0, 0 }
};

