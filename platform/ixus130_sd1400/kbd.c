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
static int usb_power=0;
static int remote_key, remote_count;
static int shoot_counter=0;
#define DELAY_TIMEOUT 10000

#define KEYS_MASK0 (0x0000000C)     // physw_status[0]
// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK1 (0x00000000)     // physw_status[1], override 0xF0 (keys) + 0xF00 (feather)
#define KEYS_MASK2 (0x000003FD)     // physw_status[2]
//static long alt_mode_key_mask = 0x00000000;   // we use two Keys, no need to override
#define SD_READONLY_FLAG (0x20000)  // SD-Card Lock Status (locked / unlocked)
#define USB_MASK (0x80000)          // USB-Power (triggered around 3,5V)

volatile int jogdial_stopped=0;

long __attribute__((naked)) wrap_kbd_p1_f();

static void __attribute__((noinline)) mykbd_task_proceed() {
    while (physw_run) {
        _SleepTask(10);

        if (wrap_kbd_p1_f() == 1) {   // autorepeat ?
            _kbd_p2_f();
        }
    }
}

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline)) mykbd_task() {
    mykbd_task_proceed();
    _ExitTask();
}

// ROM:FF83484C, like SX110
long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
    asm volatile(
                "STMFD   SP!, {R1-R5,LR}\n"
                "MOV     R4, #0\n"
                "BL      _kbd_read_keys\n"       // replaces kbd_fetch_data()
                "BL      my_kbd_read_keys\n"     // +
                "B       _kbd_p1_f_cont\n"       // continue at ROM:FF834858
    );
    return 0;   // shut up the compiler
}

// like SX110
void my_kbd_read_keys() {
    kbd_prev_state[0] = kbd_new_state[0];
    //kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];   // nothing to override

    // The following three lines replace the call to kbd_fetch_data()
    kbd_new_state[0] = physw_status[0];
    //kbd_new_state[1] = physw_status[1];
    kbd_new_state[2] = physw_status[2];

    if (kbd_process() == 0) {
        // we read keyboard state with _kbd_read_keys()

        jogdial_stopped=0;
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]);
        //physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]);
        physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]);

        //if ((jogdial_stopped==0) && !state_kbd_script_run) {
        //    jogdial_stopped=1;
        //    get_jogdial_direction();
        //}
        //else if (jogdial_stopped && state_kbd_script_run)
        //    jogdial_stopped=0;
    }

    remote_key = (physw_status[2] & USB_MASK)==USB_MASK;
    if (remote_key)
        remote_count += 1;
    else if (remote_count) {
        usb_power = remote_count;
        remote_count = 0;
    }

    if (conf.remote_enable) {
        physw_status[2] = physw_status[2] & ~(SD_READONLY_FLAG | USB_MASK);   // override USB and SD-Card Readonly Bits
    }
    else
        physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;   // override SD-Card Readonly Bit
}

int get_usb_power(int edge) {
    int x;

    if (edge) return remote_key;
    x = usb_power;
    usb_power = 0;
    return x;
}

void kbd_key_press(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key){
            kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release_all() {
    kbd_mod_state[0] |= KEYS_MASK0;
    kbd_mod_state[1] |= KEYS_MASK1;
    kbd_mod_state[2] |= KEYS_MASK2;
}

long kbd_is_key_pressed(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key) {
            return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
        }
    }
    return 0;
}

long kbd_is_key_clicked(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key){
            return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
                ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
        }
    }
    return 0;
}

long kbd_get_pressed_key() {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_get_clicked_key() {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) && ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
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

#ifdef CAM_USE_ZOOM_FOR_MF
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
#endif

// ROM:FF861F98
//int Get_JogDial(void) {
//    return (*(int*)0xC0240104)>>16;     // 0xC0240000 + 0x104
//}

//static int new_jogdial=0, old_jogdial=0;

//long get_jogdial_direction(void) {
//    old_jogdial=new_jogdial;
//    new_jogdial=Get_JogDial();
//
//    if (old_jogdial<new_jogdial) {
//        //return JOGDIAL_LEFT;
//        return JOGDIAL_RIGHT;
//    } else if (old_jogdial>new_jogdial) {
//        return JOGDIAL_LEFT;
//        //return JOGDIAL_RIGHT;
//    } else {
//        return 0;
//    }
//}

// Base values in Play Mode
// physw_status[0] = 0x[123]800[159d]dde   // 1 (Mode Switch: Auto)
// physw_status[1] = 0xc[01]3c464[26ae]    // 2
// physw_status[2] = 0x00848ffd            // 3
// Mode Switch:
// physw_status[0] 0xe (0x1) Auto Mode
// physw_status[0] 0xf (0x0) Photo Mode
// physw_status[0] 0xd (0x2) Video Mode
// physw_status[2] 0x20000 SD-Card READONLY ???
static KeyMap keymap[] = {
    { 2, KEY_UP         , 0x00000080 },
    { 2, KEY_DOWN       , 0x00000040 },
    { 2, KEY_LEFT       , 0x00000010 },
    { 2, KEY_RIGHT      , 0x00000020 },
    { 0, KEY_SET        , 0x00000004 },
    { 2, KEY_SHOOT_FULL , 0x00000300 },   // 0x00000200(KEY_SHOOT_FULL) + 0x00000100 (KEY_SHOOT_HALF)
    { 2, KEY_SHOOT_HALF , 0x00000100 },
    { 2, KEY_ZOOM_IN    , 0x00000004 },
    { 2, KEY_ZOOM_OUT   , 0x00000008 },
    { 2, KEY_MENU       , 0x00000001 },
    { 0, KEY_PRINT      , 0x0000000C },   // ALT Key workaround: KEY_DISP + KEY_SET (camera has no print key)
    { 0, 0, 0 }
};

// generic function
// called from capt_seq.c at sub_FF9686A8_my()
void wait_until_remote_button_is_released(void) {
    int count1;
    int count2;
    int tick,tick2,tick3;
    int nSW;
    int prev_usb_power,cur_usb_power;
    static int nMode;

    asm volatile ("STMFD SP!, {R0-R11,LR}\n");   // store R0-R11 and LR in stack

    //debug_led(1);
    tick = get_tick_count();
    tick2 = tick;
    static long usb_physw[3];
    if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| (shooting_get_drive_mode()==1) || ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))
    //if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))   // synch mode enable so wait for USB to disconnect
    {
        // ------ add by Masuji SUTO (start) --------------
        nMode = 0;
        usb_physw[2] = 0;   // makes sure USB bit is cleared.
        _kbd_read_keys_r2(usb_physw);
        if((usb_physw[2] & USB_MASK)==USB_MASK) nMode=1;
        // ------ add by Masuji SUTO (end)   --------------
        if(conf.ricoh_ca1_mode && conf.remote_enable) {
            if(shooting_get_drive_mode() == 1 && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING) {   //continuous-shooting mode
                if(conf.bracket_type>2) {
                    if(shoot_counter<2) shutter_int=3;
                    shoot_counter--;
                } else {
                    prev_usb_power=0;
                    nSW = 0;
                    do {
                        usb_physw[2] = 0;   // makes sure USB bit is cleared.
                        _kbd_read_keys_r2(usb_physw);
                        cur_usb_power = (usb_physw[2] & USB_MASK)==USB_MASK;
                        if(cur_usb_power) {
                            if(!prev_usb_power) {
                                tick2 = get_tick_count();
                                prev_usb_power=cur_usb_power;
                            } else {
                                if((int)get_tick_count()-tick2>1000) {debug_led(0);}
                            }
                        } else {
                            if(prev_usb_power) {
                                tick3 = (int)get_tick_count()-tick2;
                                if(nSW==10) {
                                    if(tick3>50) shutter_int=1;
                                        nSW=20;
                                }
                                if(nSW==0 && tick3>0) {
                                    if(tick3<50) {
                                    nSW=10;
                                    } else {
                                        if(tick3>1000) shutter_int=1;
                                            nSW=20;
                                    }
                                }
                                prev_usb_power=cur_usb_power;
                            }
                        }
                        if((int)get_tick_count()-tick >= DELAY_TIMEOUT) { nSW=20;shutter_int=2; }
                    }
                    while(nSW<20);
                }
            }   // continuous-shooting mode
            else {   //nomal mode
                shoot_counter=0;
                if(conf.bracket_type>2) {
                    shoot_counter=(conf.bracket_type-2)*2;
                }
                do {
                    usb_physw[2] = 0;    // makes sure USB bit is cleared.
                    _kbd_read_keys_r2(usb_physw);
                }
                //while(((usb_physw[2] & USB_MASK)==USB_MASK) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
                while (((((usb_physw[2] & USB_MASK)!=USB_MASK) && (nMode==0)) || (((usb_physw[2] & USB_MASK)==USB_MASK) && (nMode==1))) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
            }
        } else {
            do {
                usb_physw[2] = 0;   // makes sure USB bit is cleared.
               _kbd_read_keys_r2(usb_physw);
            }
           while ((usb_physw[2]&USB_MASK) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
        }
    }

    if (conf.synch_delay_enable && conf.synch_delay_value>0) {   // if delay is switched on and greater than 0
        for (count1=0;count1<conf.synch_delay_value+(conf.synch_delay_coarse_value*1000);count1++) {   // wait delay_value * 0.1ms
            for (count2=0;count2<1400;count2++) {   // delay approx. 0.1ms
            }
        }
    }

    //debug_led(0);
    asm volatile ("LDMFD SP!, {R0-R11,LR}\n");   // restore R0-R11 and LR from stack
}
