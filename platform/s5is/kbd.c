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
static long alt_mode_key_mask = 0x00000040;
static int alt_mode_led=0;
static int usb_power=0;
static int remote_key, remote_count;
static int shoot_counter=0;
#define DELAY_TIMEOUT 10000


#define KEYS_MASK0 (0x00000003)
#define KEYS_MASK1 (0x7F3F7860)
#define KEYS_MASK2 (0x00000000)

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)
#define USB_MASK (0x200000)
#define USB_REG 2


#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif


static KeyMap keymap[] = {
	/* tiny bug: key order matters. see kbd_get_pressed_key()
	 * for example
	 */
// physw_status[1] total mask: 0x7F3F7860
//	{ 1, ??           , 0x80000000 }, // Default 0, unused?
	{ 1, KEY_MACRO    , 0x40000000 }, 
	{ 1, KEY_MF       , 0x20000000 }, 
	{ 1, KEY_ZOOM_IN  , 0x10000000 }, // Zoom_in_fast  = 0x08000000 | 0x10000000
//	{ 1, KEY_ZOOMFIN  , 0x08000000 }, // Not defined in CHDK
//	{ 1, KEY_ZOOMFOUT , 0x04000000 }, // Not defined in CHDK
	{ 1, KEY_TIMER    , 0x02000000 }, 
	{ 1, KEY_ZOOM_OUT , 0x01000000 }, // Zoom_out_fast = 0x04000000 | 0x01000000
//	{ 1, ??           , 0x00800000 }, // Default 0, unused?
//	{ 1, ??           , 0x00400000 }, // Default 1, unused?
	{ 1, KEY_RIGHT    , 0x00200000 }, 
	{ 1, KEY_UP       , 0x00100000 }, 
	{ 1, KEY_DOWN     , 0x00080000 }, 
	{ 1, KEY_MENU     , 0x00040000 }, 
	{ 1, KEY_DISPLAY  , 0x00020000 }, 
	{ 1, KEY_SET      , 0x00010000 }, 
//	{ 1, ??           , 0x00008000 }, // Default 0, unused?
	{ 1, KEY_ERASE    , 0x00004000 }, 
	{ 1, KEY_VIDEO    , 0x00002000 }, 
	{ 1, KEY_LEFT     , 0x00001000 }, 
	{ 1, KEY_ISO      , 0x00000800 }, 
//	{ 1, ??           , 0x00000400 }, // Default 1, unused?
//	{ 1, KEY_DISP_ROTA, 0x00000200 }, // Indicates whether or not display is rotated, not defined, though used in CHDK
//   { 1, KEY_DISP_OPEN, 0x00000100 }, // Indicates whether or not display is attached to body (i.e. not 'opened'), not defined, though used in CHDK
//	{ 1, ??           , 0x00000080 }, // Default 0, unused?
	{ 1, KEY_PRINT    , 0x00000040 }, 
	{ 1, KEY_FLASH    , 0x00000020 }, 
//	{ 1, KEY_FL_RAISED, 0x00000010 }, // Indicates whether or not the flash is raised, not defined in CHDK
//	{ 1, KEY_MODE_DIAL, 0x0000000F }, // Listed for completeness of the keymap
//   { 1, MODE_DIAL_P         , 0x00000007 },
//   { 1, MODE_DIAL_TV        , 0x00000003 },
//   { 1, MODE_DIAL_AV        , 0x00000002 },
//   { 1, MODE_DIAL_M         , 0x00000006 },
//   { 1, MODE_DIAL_C         , 0x00000004 },
//   { 1, MODE_DIAL_AUTO      , 0x0000000F },
//   { 1, MODE_DIAL_PORTRAIT  , 0x0000000E },
//   { 1, MODE_DIAL_LANDSCAPE , 0x0000000A },
//   { 1, MODE_DIAL_NIGHT     , 0x0000000B },
//   { 1, MODE_DIAL_SPORTS    , 0x00000009 },
//   { 1, MODE_DIAL_SPECIAL   , 0x00000001 },
//   { 1, MODE_DIAL_STITCH    , 0x00000005 },
//   { 1, MODE_DIAL_MOVIE     , 0x0000000D },
//   { 1, MODE_DIAL_EMPTY     , 0x0000000C },
// 0 and 8 appear to be unused


// physw_status[0] // 6 listed keys seem to fully cover [0], though some appear to use negative logic so can't be certain.
//	{ 0, KEY_OFF       , 0x00020000 }, // Not defined in CHDK
//	{ 0, KEY_OPEN_BATT , 0x00008000 }, // Indicates whether or not the battery compartment is about to be opened (slider is a button). Camera does not retract lens, though, shame. Not defined in CHDK
//	{ 0, KEY_M_DISPLAY , 0x00000008 }, // Switch to display mode, not defined in CHDK (negative? Default 0, 1 when switching)
//	{ 0, KEY_M_SHOOT   , 0x00000004 }, // Switch to shoot mode, not defined in CHDK (negative? Default 0, 1 when switching)
//	{ 0, KEY_SHOOT_FULL, 0x00000002 }, // Listed for completeness, this is the 'single' key.
	{ 0, KEY_SHOOT_FULL, 0x00000003 }, // This is SHOOT_FULL | SHOOT_HALF.
	{ 0, KEY_SHOOT_HALF, 0x00000001 }, 


// physw_status[2]
//	{ 2, USB_ATTACH    , 0x00200000 }, // 0 = no USB, 1 = USB attached
//	{ 2, FLASH_ATTACH  , 0x00080000 }, // 0 = no flash, 1 = Hotshoe external flash attached
//   { 2, TVOUT_ATTACH  , 0x00040000 }, // 1 = no tvout, 0 = tvout attached
//	{ 2, SD_LOCK       , 0x00020000 }, // 0 = unlocked, 1 = locked


// I don't really remember whether or not this is correct, listed for completeness
// Shoot mode   = (*((long *)0xC0220200) & 0xD) == 0xD
// Display mode = (*((long *)0xC0220200) & 0xD) == 0x0

	{ 0, 0 }
};


long __attribute__((naked)) wrap_kbd_p1_f() ;

void wait_until_remote_button_is_released(void)
{

long x[3];
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
tick = get_tick_count();
tick2 = tick;
static long usb_physw[3];
if (conf.synch_enable && (!shooting_get_drive_mode()|| ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))  // synch mode enable so wait for USB to disconnect
  {
// ------ add by Masuji SUTO (start) --------------
        nMode=0;
        usb_physw[2] = 0;                                             // makes sure USB bit is cleared.
        _kbd_read_keys_r2(usb_physw);
        if((usb_physw[2] & USB_MASK)==USB_MASK) nMode=1;
// ------ add by Masuji SUTO (end)   --------------
     if(conf.ricoh_ca1_mode)
     {
	if(shooting_get_drive_mode()==1 && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){			//continuous-shooting mode
		if(conf.bracket_type>2){
			if(shoot_counter<2) shutter_int=3;
			shoot_counter--;
			}
		else{
			prev_usb_power=0;
			nSW = 0;
			do
				{     
				usb_physw[2] = 0;                                             // makes sure USB bit is cleared.
				_kbd_read_keys_r2(usb_physw);
				cur_usb_power = (usb_physw[2] & USB_MASK)==USB_MASK;
				if(cur_usb_power){
					if(!prev_usb_power){
						tick2 = get_tick_count();
						prev_usb_power=cur_usb_power;
						}
					else{
						if((int)get_tick_count()-tick2>1000) {debug_led(0);}
						}
					}
				else{
					if(prev_usb_power){
						tick3 = (int)get_tick_count()-tick2;
						if(nSW==10) {
							if(tick3>50) shutter_int=1;
							nSW=20;
							}
						if(nSW==0 && tick3>0) {
							if(tick3<50) {
							nSW=10;
							}
						else{
							if(tick3>1000) shutter_int=1;
								nSW=20;
							}
						}
						prev_usb_power=cur_usb_power;
						}
					}
				if((int)get_tick_count()-tick >= DELAY_TIMEOUT) {nSW=20;shutter_int=2;}
				}
			 while(nSW<20);
			 }
		} 		//continuous-shooting mode 
		else{		//nomal mode 
			shoot_counter=0;
			if(conf.bracket_type>2){
				shoot_counter=(conf.bracket_type-2)*2;
				}
        do
           {
         //  _platformsub_kbd_fetch_data(x);
           usb_physw[2] = 0;
          _kbd_read_keys_r2(usb_physw);            
           }

// ------ modif by Masuji SUTO (start) --------------
    while(((((usb_physw[2] & USB_MASK)!=USB_MASK) && (nMode==0)) || (((usb_physw[2] & USB_MASK)==USB_MASK) && (nMode==1))) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
// ------ modif by Masuji SUTO (end)   --------------
	}
       } // ricoh ca-1 mode

else

       {
         do
          {
         //  _platformsub_kbd_fetch_data(x);
           usb_physw[2] = 0;
          _kbd_read_keys_r2(usb_physw);           
           }
        while((usb_physw[2]&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));

        }

  } // synch enable


if (conf.synch_delay_enable && conf.synch_delay_value>0)       // if delay is switched on and greater than 0
  {
    for (count1=0;count1<conf.synch_delay_value+(conf.synch_delay_coarse_value*1000);count1++) // wait delay_value * 0.1ms
    {
      for (count2=0;count2<1400;count2++)            // delay approx. 0.1ms
        {
        }
     }
  }

debug_led(0);

asm volatile ("LDMFD SP!, {R0-R11,LR}\n"); // restore R0-R11 and LR from stack
}

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
	if (conf.remote_enable) {
		physw_status[2] = physw_status[2] & ~(SD_READONLY_FLAG | USB_MASK);
		// As much as I'd like to immediately shoot, this trigger is intended for use in scripts, so don't shoot here.
		//if(remote_key) physw_status[0] &= ~(0x3); // Shoot!
	} else {
		physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;
	}

}



/****************/

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
	kbd_mod_state[0] |= 0xFFFFFFFF;
	kbd_mod_state[1] |= 0xFFFFFFFF;
	kbd_mod_state[2] |= 0xFFFFFFFF;
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
    volatile long *mmio0 = (void*)0x11ABC;
    volatile long *mmio1 = (void*)0x11AC0;
    volatile long *mmio2 = (void*)0x11AC4;

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
	return remote_key;
}
