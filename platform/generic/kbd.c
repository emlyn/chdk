#include "lolevel.h"
#include "platform.h"
#include "conf.h"
#include "core.h"
#include "keyboard.h"

volatile long *mmio0 = (void*)0xc0220200;		// Definition of input addresses
volatile long *mmio1 = (void*)0xc0220204;
volatile long *mmio2 = (void*)0xc0220208;
volatile long *mmio3 = (void*)0xc022020C;

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
static int shoot_counter=0;
#define DELAY_TIMEOUT 10000

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#if defined(CAMERA_a710) || defined(CAMERA_a700)
#define USB_MASK 8
#define USB_REG 0
#endif

#if defined(CAMERA_a630) || defined(CAMERA_a640) || defined(CAMERA_a610) || defined(CAMERA_a620) || defined(CAMERA_ixus800_sd700) || defined(CAMERA_ixus65_sd630) || defined(CAMERA_ixus850_sd800) || defined(CAMERA_ixus900_sd900) || defined (CAMERA_ixus70_sd1000) || defined (CAMERA_ixus950_sd850)
#define USB_MASK 0x8000000
#define USB_REG 1
#endif

#if defined(CAMERA_a430) || defined(CAMERA_a530) || defined(CAMERA_a540)
#define USB_MASK 0x4000
#define USB_REG 2
#endif

#if defined(CAMERA_g11)
#define USB_MASK 0x100000
#define USB_REG 2
#endif

#if defined(CAMERA_s90)
#define USB_MASK (0x200000)
#define USB_REG 2
#endif

long get_mmio(void)
{
long x;	

#if defined(CAMERA_a530) || defined(CAMERA_a540)
    x = (long)*mmio2;
#endif
	
#if defined(CAMERA_a610) || defined(CAMERA_a620) || defined(CAMERA_a630) || defined(CAMERA_a640) || defined(CAMERA_ixus800_sd700) 
        x = (long)*mmio1;
#endif

#if defined(CAMERA_a710) || defined(CAMERA_a700)
        x = (long)*mmio0;
#endif
	
return x;	
}

#if defined(CAMERA_a530) || defined(CAMERA_a540) || defined(CAMERA_a610) || defined(CAMERA_a620) || defined(CAMERA_a630) || defined(CAMERA_a640) || defined(CAMERA_a700)|| defined(CAMERA_a710) || defined (CAMERA_ixus800_sd700)  
void wait_until_remote_button_is_released(void)
{
long x;
int count1;
int count2;
int tick,tick2,tick3;
int nSW;
int prev_usb_power,cur_usb_power;

// ------ add by Masuji SUTO (start) --------------
    static int nMode;
// ------ add by Masuji SUTO (end)   --------------
asm volatile ("STMFD SP!, {R0-R11,LR}\n"); // store R0-R11 and LR in stack


debug_led(1);
tick=get_tick_count();
tick2 = tick;

 if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| (shooting_get_drive_mode()==1) || ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))

// if(conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable)                                              // synch mode enable so wait for USB to disconnect
  {
if(conf.ricoh_ca1_mode && conf.remote_enable)
{
   nMode=0;
	x=get_mmio();

    if(x&USB_MASK) nMode=1;
// ------ add by Masuji SUTO (end)   --------------
} // ricoh_ca1_mode


if(conf.ricoh_ca1_mode && conf.remote_enable)
    {
	if(shooting_get_drive_mode()==1 && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){			//continuous-shooting mode
		if(conf.bracket_type>2){                          // alternating
			if(shoot_counter<2) shutter_int=3;
			shoot_counter--;
			}
		else{                                              // lighter/darker
			prev_usb_power=0;
			nSW = 0;
			do
				{     
				x=get_mmio();
				cur_usb_power = x&USB_MASK;
				if(cur_usb_power)
                            {
					if(!prev_usb_power)
                                   {
						 tick2 = get_tick_count();
						 prev_usb_power=cur_usb_power;
						}
					   else
                                    {
						 if((int)get_tick_count()-tick2>1000) {debug_led(0);}
						}
					}
				else{
					if(prev_usb_power)
                                {
						tick3 = (int)get_tick_count()-tick2;
						if(nSW==10) 
                                         {
							 if(tick3>50) shutter_int=1;
							 nSW=20;
							}
						if(nSW==0 && tick3>0) 
                                          {
							 if(tick3<50) 
                                             {
							    nSW=10;
							   }
						       else
                                             {
							      if(tick3>1000) shutter_int=1;
								nSW=20;
							    }
						         }
						      prev_usb_power=cur_usb_power;
						}
					  } // else

				           if((int)get_tick_count()-tick >= DELAY_TIMEOUT) {nSW=20;shutter_int=2;}
				      }

			        while(nSW<20);
			 }    // lighter/darker

		  } 		//continuous-shooting mode
 
		 else{		//nomal mode 
			shoot_counter=0;
			if(conf.bracket_type>2)
                       {
				shoot_counter=(conf.bracket_type-2)*2;
				}
           do
             x=get_mmio();

//   while((x&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));
 
// ------ modif by Masuji SUTO (start) --------------
        while(((!(x&USB_MASK) && (nMode==0)) || ((x&USB_MASK) && (nMode==1))) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));
// ------ modif by Masuji SUTO (end)   --------------
}
} // ricoh ca1 mode

else
{
   do
   x=get_mmio();

   while((x&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));
}


if (conf.synch_delay_enable && conf.synch_delay_value>0)                                // if delay is switched on and greater than 0
  {
    for (count1=0;count1<conf.synch_delay_value+(conf.synch_delay_coarse_value*1000);count1++) // wait delay_value * 0.1ms
    {
      for (count2=0;count2<1400;count2++)            // delay approx. 0.1ms
        {
        }
     }
  }
}
debug_led(0);


asm volatile ("LDMFD SP!, {R0-R11,LR}\n"); // restore R0-R11 and LR from stack
}

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
    }
    remote_key = (kbd_new_state[USB_REG] & USB_MASK)==USB_MASK;

			if (remote_key) 
				remote_count += 1;
			else if (remote_count) {
				usb_power = remote_count;
				remote_count = 0;
			}
#endif
#if defined(USB_MASK) && defined(USB_REG)
		if (conf.remote_enable) {

#if !defined(CAMERA_a530) && !defined(CAMERA_a540)
        physw_status[USB_REG] = kbd_new_state[USB_REG] & ~USB_MASK;
#endif
        }

#endif


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
    static long zoom_key_pressed = 0;

    if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {

        if (shooting_get_focus_mode()) {
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
        if (shooting_get_focus_mode()) {
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

