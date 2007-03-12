#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"

static int keyid_by_name (const char *n);


#define SCRIPT_END	0
#define SCRIPT_CLICK	1
#define SCRIPT_SHOOT	2
#define SCRIPT_SLEEP	3
#define SCRIPT_PRESS	4
#define SCRIPT_RELEASE	5
#define SCRIPT_PR_WAIT_SAVE	6
#define SCRIPT_WAIT_SAVE	7
#define SCRIPT_WAIT_FLASH	8


#define KBD_STACK_SIZE 24

static long kbd_int_stack[KBD_STACK_SIZE];
static int kbd_int_stack_ptr;

#define KBD_STACK_PUSH(v) kbd_int_stack[kbd_int_stack_ptr++] = (v);
#define KBD_STACK_PREV(p) (kbd_int_stack[kbd_int_stack_ptr-(p)])

static int kbd_blocked;
static int key_pressed;
int state_kbd_script_run;
static long delay_target_ticks;

static void kbd_sched_delay(long msec)
{
    KBD_STACK_PUSH(msec);
    KBD_STACK_PUSH(SCRIPT_SLEEP);
}

static void kbd_sched_click(long key)
{
// WARNING stack program flow is reversed
    kbd_sched_delay(20);

    KBD_STACK_PUSH(key);
    KBD_STACK_PUSH(SCRIPT_RELEASE);

    kbd_sched_delay(20);

    KBD_STACK_PUSH(key);
    KBD_STACK_PUSH(SCRIPT_PRESS);
}

void kbd_sched_shoot()
{
// WARNING stack program flow is reversed

    kbd_sched_delay(conf_script_shoot_delay*100);// XXX FIXME find out how to wait to jpeg save finished

    KBD_STACK_PUSH(SCRIPT_WAIT_SAVE);

    KBD_STACK_PUSH(KEY_SHOOT_FULL);
    KBD_STACK_PUSH(SCRIPT_RELEASE);

    kbd_sched_delay(20);

    KBD_STACK_PUSH(KEY_SHOOT_FULL);
    KBD_STACK_PUSH(SCRIPT_PRESS);

    KBD_STACK_PUSH(SCRIPT_WAIT_FLASH);

    kbd_sched_delay(10);

    KBD_STACK_PUSH(KEY_SHOOT_HALF);
    KBD_STACK_PUSH(SCRIPT_PRESS);

    KBD_STACK_PUSH(SCRIPT_PR_WAIT_SAVE);

}

void script_start()
{
    state_kbd_script_run = 1;
    delay_target_ticks = 0;
    kbd_key_release_all();
    ubasic_init(state_ubasic_script);

    ubasic_set_variable('a' - 'a', conf_ubasic_var_a);
    ubasic_set_variable('b' - 'a', conf_ubasic_var_b);
    ubasic_set_variable('c' - 'a', conf_ubasic_var_c);
}

void script_end()
{
    state_kbd_script_run = 0;
}

void process_script()
{
    long t;

    // process stack operations
    if (kbd_int_stack_ptr){
	switch (KBD_STACK_PREV(1)){
	case SCRIPT_PRESS:
	    kbd_key_press(KBD_STACK_PREV(2));
	    kbd_int_stack_ptr-=2; // pop op.
	    return;
	case SCRIPT_RELEASE:
	    kbd_key_release(KBD_STACK_PREV(2));
	    kbd_int_stack_ptr-=2; // pop op.
	    return;
	case SCRIPT_SLEEP:
	    t = get_tick_count();
	    // FIXME take care if overflow occurs
	    if (delay_target_ticks == 0){
		/* setup timer */
		delay_target_ticks = t+KBD_STACK_PREV(2);
	    } else {
		if (delay_target_ticks <= t){
		    delay_target_ticks = 0;
		    kbd_int_stack_ptr-=2; // pop sleep op.
		}
	    }
	    return;
	case SCRIPT_PR_WAIT_SAVE:
	    state_shooting_progress = SHOOTING_PROGRESS_NONE;

	    kbd_int_stack_ptr-=1; // pop op.
	    return;
	case SCRIPT_WAIT_SAVE:{
	    if (state_shooting_progress == SHOOTING_PROGRESS_DONE)
		kbd_int_stack_ptr-=1; // pop op.
	    return;
	}
	case SCRIPT_WAIT_FLASH:{
	    if (shooting_is_flash_ready())
		kbd_int_stack_ptr-=1; // pop op.
	    return;
	}
	default:
	    /*finished();*/
	    script_end();
	}
    }

    ubasic_run();

    if (ubasic_finished())
	script_end();
}

void ubasic_camera_click(const char *s)
{
    long k = keyid_by_name(s);
    if (k > 0) {
	kbd_sched_click(k);
    } else {
	ubasic_error = 3;
    }
}

void ubasic_camera_sleep(long v)
{
    kbd_sched_delay(v);
}

void ubasic_camera_shoot()
{
    kbd_sched_shoot();
}

long kbd_process()
{
/* Alternative keyboard mode stated/exited by pressing print key.
 * While running Alt. mode shoot key will start a script execution.
 */

    if (kbd_blocked){
	if (key_pressed){
	    if (kbd_get_pressed_key() == 0)
		key_pressed = 0;
	    return 1;
	}

	if (kbd_is_key_pressed(KEY_PRINT)){
	    key_pressed = 2;
	    kbd_blocked = 0;
	    gui_kbd_leave();
	    return 1;
	}

	if (kbd_is_key_pressed(KEY_SHOOT_FULL)){
	    key_pressed = 1;
	    if (!state_kbd_script_run){
		script_start();
	    } else {
		script_end();
	    }
	}

	if (state_kbd_script_run)
	    process_script();
	else {
	    gui_kbd_process();
	}
    } else {
	if (!key_pressed && kbd_is_key_pressed(KEY_PRINT)){
	    kbd_blocked = 1;
	    key_pressed = 1;
	    kbd_key_release_all();
	    gui_kbd_enter();
	    return 1;
	} else 
	if ((key_pressed == 2) && !kbd_is_key_pressed(KEY_PRINT)){
	    key_pressed = 0;
	}
    }

    return kbd_blocked;
}

const struct Keynames {
    int keyid;
    char *keyname;
} keynames[] = {
    { KEY_UP, "up" },
    { KEY_DOWN, "down" },
    { KEY_LEFT, "left" },
    { KEY_RIGHT, "right" },
    { KEY_SET, "set" },
    { KEY_SHOOT_HALF, "shoot_half" },
    { KEY_SHOOT_FULL, "shoot_full" },
    { KEY_ZOOM_IN, "zoom_in" },
    { KEY_ZOOM_OUT, "zoom_out" },
    { KEY_MENU, "menu" },
    { KEY_DISPLAY, "display" },
    { KEY_PRINT, "print" },
    { KEY_ERASE, "erase" },
};

int keyid_by_name (const char *n)
{
    int i;
    for (i=0;i<sizeof(keynames)/sizeof(keynames[0]);i++)
	if (strcmp(keynames[i].keyname,n) == 0)
	    return keynames[i].keyid;
    return 0;
}
