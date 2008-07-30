#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "camera.h"
#include "lang.h"
#include "ubasic.h"
#include "histogram.h"
#include "script.h"
#include "gui_lang.h"
#include "motion_detector.h"

static int keyid_by_name (const char *n);


#define SCRIPT_END              0
#define SCRIPT_CLICK            1
#define SCRIPT_SHOOT            2
#define SCRIPT_SLEEP            3
#define SCRIPT_PRESS            4
#define SCRIPT_RELEASE          5
#define SCRIPT_PR_WAIT_SAVE     6
#define SCRIPT_WAIT_SAVE        7
#define SCRIPT_WAIT_FLASH       8
#define SCRIPT_WAIT_EXPHIST     9
#define SCRIPT_PR_WAIT_EXPHIST  10
#define SCRIPT_WAIT_CLICK       11
#define SCRIPT_MOTION_DETECTOR  12

#define KBD_STACK_SIZE 24

static long kbd_int_stack[KBD_STACK_SIZE];
static int kbd_int_stack_ptr;

#define KBD_STACK_PUSH(v) kbd_int_stack[kbd_int_stack_ptr++] = (v);
#define KBD_STACK_PREV(p) (kbd_int_stack[kbd_int_stack_ptr-(p)])

static int kbd_blocked;
static int key_pressed;
int state_kbd_script_run;
static long delay_target_ticks;
static long kbd_last_clicked;

static void kbd_sched_delay(long msec)
{
    KBD_STACK_PUSH(msec);
    KBD_STACK_PUSH(SCRIPT_SLEEP);
}


void kbd_sched_motion_detector(){
    KBD_STACK_PUSH(SCRIPT_MOTION_DETECTOR);
}

static void kbd_sched_press(long key)
{
// WARNING stack program flow is reversed
    kbd_sched_delay(20);

    KBD_STACK_PUSH(key);
    KBD_STACK_PUSH(SCRIPT_PRESS);
}

static void kbd_sched_release(long key)
{
// WARNING stack program flow is reversed
    kbd_sched_delay(20);

    KBD_STACK_PUSH(key);
    KBD_STACK_PUSH(SCRIPT_RELEASE);
}

void md_kbd_sched_immediate_shoot(int no_release)
{
    kbd_int_stack_ptr-=1;// REMOVE MD ITEM
  
    // stack operations are reversed!
    if (!no_release)  // only release shutter if allowed
    {
      kbd_sched_release(KEY_SHOOT_FULL);
      kbd_sched_delay(20);
    }
    KBD_STACK_PUSH(SCRIPT_MOTION_DETECTOR); // it will removed right after exit from this function
    kbd_key_press(KEY_SHOOT_FULL); // not a stack operation... pressing right now
}


static void kbd_sched_click(long key)
{
// WARNING stack program flow is reversed
    kbd_sched_release(key);
    kbd_sched_press(key);
}

static void kbd_sched_wait_click(int timeout)
{
// WARNING stack program flow is reversed
    KBD_STACK_PUSH(timeout);
    KBD_STACK_PUSH(SCRIPT_WAIT_CLICK);
}

void kbd_sched_shoot()
{
// WARNING stack program flow is reversed

    kbd_sched_delay(conf.script_shoot_delay*100);// XXX FIXME find out how to wait to jpeg save finished

    KBD_STACK_PUSH(SCRIPT_WAIT_SAVE);

    KBD_STACK_PUSH(KEY_SHOOT_FULL);
    KBD_STACK_PUSH(SCRIPT_RELEASE);

    kbd_sched_delay(20);

    KBD_STACK_PUSH(KEY_SHOOT_FULL);
    KBD_STACK_PUSH(SCRIPT_PRESS);

    KBD_STACK_PUSH(SCRIPT_WAIT_FLASH);
    KBD_STACK_PUSH(SCRIPT_WAIT_EXPHIST);
    KBD_STACK_PUSH(SCRIPT_PR_WAIT_EXPHIST);

    kbd_sched_delay(10);

    KBD_STACK_PUSH(KEY_SHOOT_HALF);
    KBD_STACK_PUSH(SCRIPT_PRESS);

    KBD_STACK_PUSH(SCRIPT_PR_WAIT_SAVE);

}

void script_start()
{
    int i;

    state_kbd_script_run = 1;
    delay_target_ticks = 0;
    kbd_int_stack_ptr = 0;
    kbd_last_clicked = 0;
    kbd_key_release_all();
    ubasic_init(state_ubasic_script);

    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        ubasic_set_variable(i, conf.ubasic_vars[i]);
    }

    if (conf.alt_prevent_shutdown != ALT_PREVENT_SHUTDOWN_ALT_SCRIPT) {
        enable_shutdown();
    }
}

void script_end()
{
    ubasic_end();
    if (conf.alt_prevent_shutdown != ALT_PREVENT_SHUTDOWN_NO) {
        disable_shutdown();
    }
    kbd_key_release_all();
    state_kbd_script_run = 0;
    vid_bitmap_refresh();
}

void process_script()
{
    long t;

    // process stack operations
    if (kbd_int_stack_ptr){
	switch (KBD_STACK_PREV(1)){

	case SCRIPT_MOTION_DETECTOR:
			if(md_detect_motion()==0){
				kbd_int_stack_ptr-=1;
			}
			return;

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
	    state_expos_recalculated = 0;
	    histogram_stop();

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
	case SCRIPT_WAIT_EXPHIST:{
	    if (state_expos_recalculated) {
		kbd_int_stack_ptr-=1; // pop op.
		state_expos_under = under_exposed;
		state_expos_over = over_exposed;
	    }
	    return;
	}
	case SCRIPT_PR_WAIT_EXPHIST: {
	    if (shooting_in_progress()) {
		state_expos_recalculated = 0;
		histogram_restart();
		kbd_int_stack_ptr-=1; // pop op.
	    }
	    return;
	}
        case SCRIPT_WAIT_CLICK: {
            t = get_tick_count();
	    if (delay_target_ticks == 0){
		/* setup timer */
		delay_target_ticks = t+((KBD_STACK_PREV(2))?KBD_STACK_PREV(2):86400000);
	    } else {
                kbd_last_clicked = kbd_get_clicked_key();
                if (kbd_last_clicked || delay_target_ticks <= t) {
                    if (!kbd_last_clicked) 
                        kbd_last_clicked=0xFFFF;
        	    delay_target_ticks = 0;
                    kbd_int_stack_ptr-=2; // pop op.
                }
	    }
	    return;
	}
	default:
	    /*finished();*/
	    script_end();
	}
    }

    ubasic_run();

    if (ubasic_finished()) {
        script_console_add_line(lang_str(LANG_CONSOLE_TEXT_FINISHED));
	script_end();
    }    
}

void ubasic_camera_press(const char *s)
{
    long k = keyid_by_name(s);
    if (k > 0) {
	kbd_sched_press(k);
    } else {
	ubasic_error = 3;
    }
}

void ubasic_camera_release(const char *s)
{
    long k = keyid_by_name(s);
    if (k > 0) {
	kbd_sched_release(k);
    } else {
	ubasic_error = 3;
    }
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

void ubasic_camera_wait_click(int timeout)
{
    kbd_sched_wait_click(timeout);
}

int ubasic_camera_is_clicked(const char *s)
{
    long k = keyid_by_name(s);
    if (k==0xFF) return get_usb_power(1);
	if (k > 0) {
        return (kbd_last_clicked == k);
    } else {
	ubasic_error = 3;
    }
    return 0;
}


void ubasic_camera_sleep(long v)
{
    kbd_sched_delay(v);
}

void ubasic_camera_shoot()
{
    kbd_sched_shoot();
}
// remote autostart
void script_autostart()
{
	auto_started = 1;
	kbd_blocked = 1;
	gui_kbd_enter();
	script_console_clear(); 
	script_console_add_line("***Autostart***"); //lang_str(LANG_CONSOLE_TEXT_STARTED));
	script_start();
}
void exit_alt()
{
	    kbd_blocked = 0;
	    gui_kbd_leave();
}

long kbd_process()
{
/* Alternative keyboard mode stated/exited by pressing print key.
 * While running Alt. mode shoot key will start a script execution.
 */

	if (kbd_blocked){
	if (key_pressed){
            if (kbd_is_key_pressed(conf.alt_mode_button)) {
                ++key_pressed;
                if (key_pressed==CAM_EMUL_KEYPRESS_DELAY) {
                    kbd_key_press(conf.alt_mode_button);
                } else if (key_pressed==(CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION)) {
                    kbd_key_release(conf.alt_mode_button);
                    key_pressed = 2;
        	    kbd_blocked = 0;
//        	    gui_kbd_leave();
                }
            } else if (kbd_get_pressed_key() == 0) {
                if (key_pressed!=100)
                    gui_kbd_enter();
        	key_pressed = 0;
            }    
	    return 1;
	}

	if (kbd_is_key_pressed(conf.alt_mode_button)){
	    key_pressed = 2;
	    kbd_blocked = 0;
	    gui_kbd_leave();
	    return 1;
	}

	if (kbd_is_key_pressed(KEY_SHOOT_FULL)){
	    key_pressed = 100;
	    if (!state_kbd_script_run){
                script_console_clear();
                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_STARTED));
		script_start();
	    } else {
                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_INTERRUPTED));
		script_end();
	    }
	}

	if (state_kbd_script_run)
	    process_script();
	else {
	    gui_kbd_process();
	}
    } else {

        //if (kbd_is_key_pressed(KEY_SHOOT_HALF) && kbd_is_key_pressed(conf.alt_mode_button)) return 0;

	if (!key_pressed && kbd_is_key_pressed(conf.alt_mode_button)){
	    kbd_blocked = 1;
	    key_pressed = 1;
	    kbd_key_release_all();
//	    gui_kbd_enter();
	    return 1;
	} else 
	if ((key_pressed == 2) && !kbd_is_key_pressed(conf.alt_mode_button)){
	    key_pressed = 0;
	}
	
	if (conf.use_zoom_mf && kbd_use_zoom_as_mf()) {
	    return 1;
	}

	other_kbd_process(); // processed other keys in not <alt> mode
    }

    return kbd_blocked;
}

static const struct Keynames {
    int keyid;
    char *keyname;
} keynames[] = {
    { KEY_UP,           "up"         },
    { KEY_DOWN,         "down"       },
    { KEY_LEFT,         "left"       },
    { KEY_RIGHT,        "right"      },
    { KEY_SET,          "set"        },
    { KEY_SHOOT_HALF,   "shoot_half" },
    { KEY_SHOOT_FULL,   "shoot_full" },
    { KEY_ZOOM_IN,      "zoom_in"    },
    { KEY_ZOOM_OUT,     "zoom_out"   },
    { KEY_MENU,         "menu"       },
    { KEY_DISPLAY,      "display"    },
    { KEY_PRINT,        "print"      },
    { KEY_ERASE,        "erase"      },
    { KEY_ISO,          "iso"        },
    { KEY_FLASH,        "flash"      },
    { KEY_MF,           "mf"         },
    { KEY_MACRO,        "macro"      },
    { KEY_VIDEO,        "video"      },
    { KEY_TIMER,        "timer"      },
    { KEY_EXPO_CORR,    "expo_corr"  },
    { KEY_MICROPHONE,   "fe"         },
    { KEY_FACE,         "face"       },
    { 0xFF,             "remote"     },
    { 0xFFFF,           "no_key"     },
};

static int keyid_by_name (const char *n)
{
    int i;
    for (i=0;i<sizeof(keynames)/sizeof(keynames[0]);i++)
	if (strcmp(keynames[i].keyname,n) == 0)
	    return keynames[i].keyid;
    return 0;
}

int kbd_is_blocked() {
	return kbd_blocked;
}
