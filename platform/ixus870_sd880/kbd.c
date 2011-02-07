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
static long alt_mode_key_mask = 0x00000800; // key_print
static int usb_power=0;
static int remote_key, remote_count;
static int shoot_counter=0;
extern void _platformsub_kbd_fetch_data(long*);

#define DELAY_TIMEOUT 10000

// each mask should be the xor of all key values in the corresponding group
#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 (0x00000FFF)

#define NEW_SS (0x2000)

// from sub_FF846198 (via aSdProtect (just above it))
// LDR  R1, =dword_FFAD6F20     R1 = 0xFFAD6F20 = a
// MOV  R3, #1                  R3 = 1
// LDRB R2, [R1,#0x114]         R2 = a[0x114] = 0x51
// LDRB R1, [R1,#0x114]         R1 = a[0x114] = 0x51
// MOV  R2, R2,LSR#5            R2 = 0x51 >> 5 = 2 = SD_READONLY_REG
// LDR  R0, [R0,R2,LSL#2]       R0 = R0[2] = b[2]
// AND  R1, R1, #0x1F           R1 = 0x51 & 0x1F = 0x11
// AND  R0, R0, R3,LSL R1       R0 = b[2] & (1 << 0x11)
// MOV  R0, R0,LSR R1           R0 = (b[2] & (1 << 0x11)) >> 0x11
// AND  R0, R0, #1              R0 = ((b[2] & (1 << 0x11)) >> 0x11) & 0x1
// BX   LR                      return
#define SD_READONLY_FLAG (0x20000)  // 1 << 0x11
#define SD_READONLY_REG 2

#define USB_MASK (0x40000)
#define USB_REG 2               // idx in physw_status


#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif


static KeyMap keymap[] = {
	/* tiny bug: key order matters. see kbd_get_pressed_key()
	 * for example
         * KEY_SHOOT_FULL and KEY_SHOOT_HALF overlap and the first has precedence
	 */

        // (note: key is in group i if it changes a bit in physw_status[i])
        // group, CHDK key      , mask
	{ 2, KEY_SHOOT_FULL	, 0x00000003 },
	{ 2, KEY_SHOOT_HALF	, 0x00000001 },

	{ 2, KEY_UP		, 0x00000080 },
	{ 2, KEY_DOWN		, 0x00000040 },
	{ 2, KEY_LEFT		, 0x00000010 },
	{ 2, KEY_RIGHT		, 0x00000020 },
	{ 2, KEY_SET		, 0x00000100 },
	{ 2, KEY_ZOOM_IN	, 0x00000004 },
	{ 2, KEY_ZOOM_OUT	, 0x00000008 },
	{ 2, KEY_MENU		, 0x00000400 },
	{ 2, KEY_DISPLAY	, 0x00000200 },
	{ 2, KEY_PRINT	 	, 0x00000800 },
       	{ 0, 0, 0 }
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
if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))  // synch mode enable so wait for USB to disconnect
  {
// ------ add by Masuji SUTO (start) --------------
        nMode=0;
        usb_physw[USB_REG] = 0;                                             // makes sure USB bit is cleared.
        _kbd_read_keys_r2(usb_physw);
        if((usb_physw[USB_REG] & USB_MASK)==USB_MASK) nMode=1;
// ------ add by Masuji SUTO (end)   --------------
     if(conf.ricoh_ca1_mode && conf.remote_enable)
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
				usb_physw[USB_REG] = 0;                                             // makes sure USB bit is cleared.
				_kbd_read_keys_r2(usb_physw);
				cur_usb_power = (usb_physw[USB_REG] & USB_MASK)==USB_MASK;
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
		else{		// normal mode
			shoot_counter=0;
			if(conf.bracket_type>2){
				shoot_counter=(conf.bracket_type-2)*2;
				}
        do
           {
         //  _platformsub_kbd_fetch_data(x);
           usb_physw[USB_REG] = 0;
          _kbd_read_keys_r2(usb_physw);            
           }

// ------ modif by Masuji SUTO (start) --------------
    while(((((usb_physw[USB_REG] & USB_MASK)!=USB_MASK) && (nMode==0)) || (((usb_physw[USB_REG] & USB_MASK)==USB_MASK) && (nMode==1))) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
// ------ modif by Masuji SUTO (end)   --------------
	}
       } // ricoh ca-1 mode

else

       {
         do
          {
         //  _platformsub_kbd_fetch_data(x);
           usb_physw[USB_REG] = 0;
          _kbd_read_keys_r2(usb_physw);           
           }
        while((usb_physw[USB_REG]&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));

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
  int i;
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
        // first three lines from kbd_p1_f plus a jump to the fourth
	asm volatile(
		"STMFD   SP!, {R1-R5,LR}\n"
		"MOV     R4, #0\n"
		"BL      my_kbd_read_keys\n"
		"B       _kbd_p1_f_cont\n"
	);
	return 0; // shut up the compiler
}

volatile int jogdial_stopped=0;

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
          physw_status[2] |= alt_mode_key_mask;
          jogdial_stopped=0;

	} else {
		// override keys
 	physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |
			  (kbd_mod_state[0] & KEYS_MASK0);

	physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) |
			  (kbd_mod_state[1] & KEYS_MASK1);

	physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |
			  (kbd_mod_state[2] & KEYS_MASK2);

	if ((jogdial_stopped==0) && !state_kbd_script_run){ jogdial_stopped=1; get_jogdial_direction(); }
	else if (jogdial_stopped && state_kbd_script_run) jogdial_stopped=0; 

	}
	
	_kbd_read_keys_r2(physw_status);

	remote_key = (physw_status[USB_REG] & USB_MASK)==USB_MASK;
		if (remote_key) 
			remote_count += 1;
		else if (remote_count) {
			usb_power = remote_count;
			remote_count = 0;
		}
	if (conf.remote_enable) {
#if USB_REG == SD_READONLY_REG
		physw_status[USB_REG] = physw_status[USB_REG] & ~(SD_READONLY_FLAG | USB_MASK);
#else
		physw_status[USB_REG] = physw_status[USB_REG] & ~USB_MASK;
		physw_status[SD_READONLY_REG] = physw_status[SD_READONLY_REG] & ~SD_READONLY_FLAG;
#endif
	} else {
		physw_status[SD_READONLY_REG] = physw_status[SD_READONLY_REG] & ~SD_READONLY_FLAG;
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


int get_usb_power(int edge)
{
	int x;

	if (edge) return remote_key;
	x = usb_power;
	usb_power = 0;
	return x;
}

long kbd_use_zoom_as_mf() {
 return 0;
}

static int new_jogdial=0, old_jogdial=0;

int Get_JogDial(void){
 // address from sub above aJogdail (sub_FF84B8D8)
 return (*(int*)0xC0240104)>>16;
}

long get_jogdial_direction(void) {
 // XXX this seems to have a overflow bug: old=MIN_INT, new = old-1 = MAX_INT  ->  old-1 < old < new = old - 1
 // not likely to happen though (very long runs with a bias for tuning one direction; bias is probably to the right due to menus)
 old_jogdial=new_jogdial;
 new_jogdial=Get_JogDial();
 if (old_jogdial<new_jogdial) return JOGDIAL_RIGHT; 
 else if (old_jogdial>new_jogdial) return JOGDIAL_LEFT;
 else return 0;
}
