#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"
#include "lang.h"
#include "../core/gui_lang.h"

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

//get some vxworks defines for semaphore stuff
#define STATUS int
#define BOOL   int
#define OK    0
#define ERROR (-1)

#define SEM_Q_FIFO           0x0
#define SEM_Q_PRIORITY       0x1
#define SEM_DELETE_SAFE      0x4
#define SEM_INVERSION_SAFE   0x8
#define SEM_OPTION_MASK     (SEM_Q_FIFO|SEM_Q_PRIORITY|SEM_DELETE_SAFE|SEM_INVERSION_SAFE)

#define NO_WAIT         0
#define WAIT_FOREVER    (-1)

typedef enum {

	SEM_EMPTY =0,
	SEM_FULL =1

} SEM_B_STATE;

typedef int SEM_ID; 
extern SEM_ID _semBCreate(int options, SEM_B_STATE initialState);
extern STATUS _TakeSemaphore(SEM_ID, int);
//extern STATUS _GiveSemaphore(SEM_ID);
SEM_ID semBinary;


// #define KBD_REQUEST_IDLE 0
// #define KBD_REQUEST_GUI_KBD_PROCESS (1<<0)
// #define KBD_REQUEST_GUI_KBD_ENTER (1<<1)
// #define KBD_REQUEST_GUI_KBD_LEAVE (1<<2)
// #define KBD_REQUEST_SCRIPT_START (1<<3)
// #define KBD_REQUEST_SCRIPT_PROCESS (1<<4)
// #define KBD_REQUEST_SCRIPT_END (1<<5)

// static long kbd_newdata_available=KBD_REQUEST_IDLE;



// static int kbd_data_process_request=0;
// static int kbd_data_process_request_done=0;
static int kbd_data_process_request_data=0;

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#define USB_MASK 0x40 
#define USB_REG 1

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

// extern void _platformsub_kbd_fetch_data(long*);
long __attribute__((naked)) wrap_kbd_p1_f();
void __attribute__((naked,noinline)) mykbd_task_proceed_2();

//KBD HACK
// long kbd_process_copy();
// static int key_pressed;
// extern void script_start();
// extern void script_end();
// extern void process_script();
extern void msleep(long);
// static int kbd_blocked;


// extern void h_kbd_p2_f();


static void __attribute__((noinline)) mykbd_task_proceed()
	{
    asm volatile
		(
		"STMFD	SP!, {R4-R8,LR}\n"
		"B	  mykbd_task_proceed_2\n"
		);
	}

void __attribute__((noinline)) mykbd_task_proceed_2()
	{
    asm volatile
		(
				"LDR	R3, =0x20F8\n"
				"SUB	SP, SP,	#8\n"
				"LDR	R2, [R3]\n"
				"CMP	R2, #2\n"
				"BNE	loc_FF830870\n"
				"LDR	R6, =0x11AC8\n"
				"MOV	R8, SP\n"
				"ADD	R7, SP,	#0x20-0x1C\n"

		"loc_FF83075C:\n"
				"MOV	R0, R8\n"
				"BL		_GetSystemTime\n"
				"LDR	R1, =wrap_kbd_p1_f\n" // Replaced call to my own function...
				"LDR	R0, [SP,#0x20-0x20]\n"
				"MOV	R3, R7\n"
				"ADD	R0, R0,	#0xA\n"
				"MOV	R2, R1\n"
				"BL		_SetTimerWhen\n"
				"CMP	R0, #0x15\n"
				"MVN	R3, R0\n"
				"ANDNE	R0, R3,	#1\n"
				"MOVEQ	R0, #1\n"
				"CMP	R0, #0\n"
				"BNE	loc_FF8307A8\n"
				"MOV	R2, #0x1F0\n"
				"LDR	R0, =0xFF8306F4\n"   //aError_tHtimer1
				"LDR	R1, =0xFF830000\n"   //=aPhyswmngr_c
				"ADD	R2, R2,	#2\n"
				"BL		sub_FF814C10\n"

		"loc_FF8307A8:\n"
				"LDR	R3, =0x11B20\n"
				"LDR	R4, =0x117A8\n"
				"LDR	R5, =0x11AE0\n"
				"LDR	R0, [R3]\n"
				"MOV	R1, #0\n"
				"BL		_TakeSemaphore\n"
				"LDR	R2, [R4,#8]\n"
				"LDR	R3, [R5,#0x2C]\n"
				"TST	R2, R3\n"
				"BEQ	loc_FF8307E0\n"
				"LDR	R0, =0x11A28\n"
				"LDR	R1, [R6,#0xC]\n"
				"BL		sub_FF830C5C\n"
				"LDR	R2, [R4,#8]\n"

		"loc_FF8307E0:\n"
				"LDR	R3, [R5,#0x20]\n"
				"TST	R2, R3\n"
				"BEQ	loc_FF8307F8\n"
				"LDR	R0, =0x119D8\n"
				"LDR	R1, [R6,#8]\n"
				"BL		sub_FF830C5C\n"

		"loc_FF8307F8:\n"
				"LDR	R0, [R4,#4]\n"
				"LDR	R3, [R5,#0x10]\n"
				"TST	R0, R3\n"
				"BEQ	loc_FF830818\n"
				"LDR	R0, =0x11988\n"
				"LDR	R1, [R6,#4]\n"
				"BL		sub_FF830D10\n"
				"LDR	R0, [R4,#4]\n"

		"loc_FF830818:\n"
				"LDR	R1, [R5,#4]\n"
				"LDR	R2, [R4,#8]\n"
				"LDR	R3, [R5,#8]\n"
				"AND	R1, R0,	R1\n"
				"AND	R2, R2,	R3\n"
				"ORRS	R1, R1,	R2\n"
				"BEQ	loc_FF830844\n"
				"LDR	R0, =0x11938\n"
				"LDR	R1, [R6]\n"
				"BL		sub_FF830C5C\n"
				"LDR	R0, [R4,#4]\n"

		"loc_FF830844:\n"
				"LDR	R3, [R5,#0x34]\n"
				"TST	R0, R3\n"
				"BEQ	loc_FF83085C\n"
				"LDR	R0, =0x11A78\n"
				"LDR	R1, [R6,#0x10]\n"
				"BL		sub_FF830C5C\n"

		"loc_FF83085C:\n"
				"BL		sub_FF8310C8\n"
				"LDR	R3, =0x20F8\n"
				"LDR	R2, [R3]\n"
				"CMP	R2, #2\n"
				"BEQ	loc_FF83075C\n"

		"loc_FF830870:\n"
				"LDR	R3, =0x11B1C\n"
				"LDR	R1, =0x20F8\n"
				"MOV	R2, #3\n"
				"LDR	R0, [R3]\n"
				"STR	R2, [R1]\n"
				"BL		sub_FF823144\n"
				"BL		_ExitTask\n"
				"ADD	SP, SP,	#8\n"
				"LDMFD	SP!, {R4-R8,PC}\n"
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

    asm volatile
		(
		"MOV	SP, %0"
		:: "r"(((char*)newstack)+NEW_SS)
		: "memory"
		);
    
    //create semaphore, empty = not available
     semBinary = _semBCreate(SEM_Q_FIFO|SEM_INVERSION_SAFE, SEM_EMPTY);
    //lock until 2nd rtask frees it
    //_TakeSemaphore(semBinary,WAIT_FOREVER);

    mykbd_task_proceed();

	/* function can be modified to restore SP here...*/

    _ExitTask();
	}



long __attribute__((naked,noinline)) wrap_kbd_p1_f()
	{
	//    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
	//    kbd_prev_state[2] = kbd_new_state[2];

    asm volatile
		(
				"STMFD	SP!, {R4,R5,LR}\n"
				"LDR	R3, =0x20F4\n"
				"SUB	SP, SP,	#8\n"
				"LDR	R2, [R3]\n"
				"CMP	R2, #1\n"
				"BEQ	loc_FF830914\n"
				"MOV	R2, #0x210\n"
				"LDR	R0, =0xFF8308D0\n"
				"LDR	R1, =0xFF830000\n"
				"ADD	R2, R2,	#3\n"
				"BL	sub_FF814C10\n"

		"loc_FF830914:\n"
				"LDR	R1, =0x2108\n"
				"LDR	R2, [R1]\n"
				"ADD	R3, R2,	#0x32\n"
				"BIC	R4, R3,	#0xFF000000\n"
				"BIC	R4, R4,	#0xF00000\n"
				"CMP	R2, R4\n"
				"BCS	loc_FF830954\n"
				"MOV	R5, R1\n"

		"loc_FF830934:\n"
				"BL		_GetCurrentMachineTime\n"
				"CMP	R0, R4\n"
				"BCS	loc_FF830984\n"
				"BL		_GetCurrentMachineTime\n"
				"LDR	R3, [R5]\n"
				"CMP	R3, R0\n"
				"BCC	loc_FF830934\n"
				"B		loc_FF830984\n"

		"loc_FF830954:\n"
				"LDR	R2, =0x2108\n"
				"LDR	R3, [R2]\n"
				"CMP	R3, R4\n"
				"BLS	loc_FF830984\n"
				"MOV	R5, R2\n"

		"loc_FF830968:\n"
				"BL		_GetCurrentMachineTime\n"
				"CMP	R0, R4\n"
				"BCC	loc_FF830968\n"
				"BL		_GetCurrentMachineTime\n"
				"LDR	R3, [R5]\n"
				"CMP	R3, R0\n"
				"BCC	loc_FF830968\n"

		"loc_FF830984:\n"
				"LDR	R4, =0x117A8\n"
				"MOV	R0, R4\n"
				"BL		platformsub_kbd_fetch_data_my\n" // Replaced to a call to my own function..
				"BL		sub_FF830AB4\n"
				"BL		sub_FF830B1C\n"
				"LDR	R3, =0x20F4\n"
				"MOV	R2, #0\n"
				"STR	R2, [R3]\n"
				"BL		sub_FF83103C\n"
				"LDR	R3, [R4]\n"
				"CMP	R3, #0\n"
				"BNE	loc_FF8309CC\n"
				"LDR	R3, [R4,#4]\n"
				"CMP	R3, #0\n"
				"BNE	loc_FF8309CC\n"
				"LDR	R3, [R4,#8]\n"
				"CMP	R3, #0\n"
				"BEQ	loc_FF830A0C\n"

		"loc_FF8309CC:\n"
				"LDR	R3, =0x117A8\n" // Address of key structure physw_status[]
				"ADD	R1, R3,	#0xC\n"
				"LDMIA	R1, {R1,R12}\n"
				"LDR	R2, [R3,#0x14]\n"
				"LDMIA	R3, {R0,LR}\n"
				"LDR	R4, [R3,#8]\n"
				"LDR	R5, =0x11B20\n"
				"EOR	R1, R1,	R0\n"
				"EOR	R12, R12, LR\n"
				"EOR	R2, R2,	R4\n"
				"LDR	R0, [R5]\n"
				"STR	R2, [R3,#0x14]\n"
				"STR	R1, [R3,#0xC]\n"
				"STR	R12, [R3,#0x10]\n"
				"BL		sub_FF823144\n"
				"B		loc_FF830A54\n"

		"loc_FF830A0C:\n"
				"CMP	R0, #1\n"
				"BEQ	loc_FF830A24\n"
				"LDR	R3, =0x20F8\n"
				"LDR	R2, [R3]\n"
				"CMP	R2, #2\n"
				"BEQ	loc_FF830A34\n"

		"loc_FF830A24:\n"
				"LDR	R3, =0x11B20\n"
				"LDR	R0, [R3]\n"
				"BL		sub_FF823144\n"
				"B		loc_FF830A54\n"

		"loc_FF830A34:\n"
				"MOV	R0, SP\n"
				"BL		_GetSystemTime\n"
				"LDR	R1, =wrap_kbd_p1_f\n" // Replaced with a call to my own function ---------------------------------------------------------------------
				"LDR	R0, [SP,#0x14-0x14]\n"
				"MOV	R2, R1\n"
				"ADD	R0, R0,	#0xA\n"
				"ADD	R3, SP,	#0x14-0x10\n"
				"BL		_SetTimerWhen\n"

		"loc_FF830A54:\n"
				"ADD	SP, SP,	#8\n"
				"LDMFD	SP!, {R4,R5,PC}\n"
		);
    return 0; // shut up the compiler
}


long my_kbd_read_keys(long x){
	kbd_new_state[1]=x & 0xFFFF;
  
  //give semaphore away
  _GiveSemaphore(semBinary);
  //this should allow other tasks to grab it: (maybe not necessary)
  msleep(0);
  
  //take semaphore again
  //volatile long *p2; p2=(void*) 0xc02200D8; *p2=0x46;
  _TakeSemaphore(semBinary, WAIT_FOREVER); 
  //*p2=0;
  
  //data is now in kbd_data_process_request_data :)
  
  //if (kbd_process_copy() == 0)
  if (kbd_data_process_request_data == 0){
		return x;
  }else{
    return (kbd_new_state[1]&~0x2FFE) | (kbd_mod_state & 0x2FFE);
  }
		
}

/*asm volatile 
				(
				// Will turn one LED on to know I'm here....
				"STMFD	SP!, {R1-R3}\n"
				"MOV	R1, #0x220000\n"
				"ORR	R3, R1, #0xEC\n"
				"ORR	R1, R3, #0xC0000000\n"
				"MOV	R2,	#0x46\n"
				"STR	R2, [R1]\n"
				"LDMFD	SP!, {R1-R3}\n"
				);
			*/
			
void __attribute__((naked,noinline)) platformsub_kbd_fetch_data_my()
	{
	asm volatile 
		(
		"STMFD	SP!, {R4-R7,LR}\n"
		"MOV	R12, #0x220000\n"
		"ORR	R3, R12, #0x204\n"
		"SUB	SP, SP,	#0xC\n"
		"ORR	R3, R3,	#0xC0000000\n"
		//"LDR     R2, [R3]\n"

		//**********************************************************
		//WE HAVE READ 0xC0220204
		//SEND IT TO usb_power_status_override():
		"MOV     R4, R0\n"
		"LDR     R0, [R3]\n" 
		"STMFD   SP!, {R1-R11}\n"  
		"BL      usb_power_status_override\n"
		"LDMFD   SP!, {R1-R11}\n"
		"MOV     R2, R0\n"
		"MOV     R0, R4\n"
		"MOV     R12, #0x220000\n"	//restore R12
		//EOF CUSTOM CODE
		//**********************************************************
	
		//this is original code, process data somehow
		"LDR	LR, =0x11B30\n"
		"LDR	R3, [R0,#0x28]\n"
		"LDR	R4, [R0,#0x1C]\n"
		"LDR	R5, [LR,#8]\n"
		"LDR	R1, [LR,#0xC]\n"
		"EOR	R2, R2,	R3\n"
		"AND	R2, R2,	R4\n"
		"LDR	R3, [R0,#0x10]\n"
		"EOR	R7, R2,	R1\n"
		"EOR	R6, R2,	R5\n"
		"ORR	R1, R6,	R7\n"
		"EOR	R3, R3,	R2\n"
		"BIC	R3, R3,	R1\n"
		"STR	R3, [R0,#4]\n"
		"STR	R2, [LR,#8]\n"
		"STR	R2, [SP,#0x20-0x1C]\n"
		"STR	R5, [LR,#0xC]\n"
		"ORR	R3, R12, #0x208\n"
		"ORR	R3, R3,	#0xC0000000\n"
		"LDR	R1, [R3]\n" // The data read goes into R1 here...
		
		//my code inserted there to fool around with the keyboard data values...
        "MOV	R2, R0\n"
        "MOV	R0, R1\n" // Pass the keyboard data (in R1) to my function via R0
        "STMFD	SP!, {R1-R11}\n"
        "BL		my_kbd_read_keys\n"
        "LDMFD	SP!, {R1-R11}\n"
        "MOV	R1,R0\n"
        "MOV	R0,R2\n" // restore registers
		"MOV	R12, #0x220000\n"
        "LDR	LR, =0x11B30\n"
		
		// Original code continues
		"MOV	R2, #0xFF00\n"
		"ADD	R2, R2, #0xFF\n"
		"AND	R1, R1,	R2\n"
		"STR	R1, [SP,#0x20-0x18]\n"
		"ADD	R12, R12, #0x3000\n"
		"ADD	R2, R12, #0xC000001C\n"
		"LDR	R3, [R2]\n"
		"AND	R3, R3,	#1\n"
		"ORR	R1, R1,	R3,LSL#16\n"
		"STR	R1, [SP,#0x20-0x18]\n"
		"ADD	R12, R12, #0xC0000024\n"
		"LDR	R3, [R12]\n"
		"LDR	R2, [R0,#0x2C]\n"
    //"AND	R3, R3,	#1\n"
		"AND  R3, R3, #0\n"    // - clear SD card R/O flag
		"ORR	R1, R1,	R3,LSL#17\n"
		"LDR	R12, [R0,#0x20]\n"
		"LDR	R4, [LR,#0x10]\n"
		"EOR	R1, R1,	R2\n"
		"LDR	R2, [LR,#0x14]\n"
		"AND	R1, R1,	R12\n"
		"LDR	R3, [R0,#0x14]\n"
		"EOR	R7, R1,	R2\n"
		"EOR	R6, R1,	R4\n"
		"ORR	R2, R6,	R7\n"
		"EOR	R3, R3,	R1\n"
		"BIC	R3, R3,	R2\n"
		"STR	R3, [R0,#8]\n"
		"STR	R1, [LR,#0x10]\n"
		"STR	R4, [LR,#0x14]\n"
		"STR	R1, [SP,#0x20-0x18]\n"
		"ADD	SP, SP,	#0xC\n"
		"LDMFD	SP!, {R4-R7,PC}\n"
		);
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
    kbd_mod_state |= 0x2FFF;
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
#if !defined (CAMERA_ixus700)
    static long v;
    static long zoom_key_pressed = 0;
    if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(12, &v, 4);
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
        get_property_case(12, &v, 4);
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
#endif
    return 0;
}


int usb_power_status_override(int status){
 // for clear USB power flag  - return status &~USB_MASK;
 // for get USB power flag read status & USB_MASK
	
	if (conf.remote_enable) {
		remote_key = (status & USB_MASK)==USB_MASK;
		if (remote_key) 
			remote_count += 1;
		else if (remote_count) {
			usb_power = remote_count;
			remote_count = 0;
		}
		return status &~USB_MASK;
	}
 return status;
}

int get_usb_power(int edge)
{
	int x;

	if (edge) return remote_key;
	x = usb_power;
	usb_power = 0;
	return x;
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

//hack to get a second thread for the keyboard:
//purpose: check if kbd_new_data flag is set 
void kbd_process_task()
{
    while(1){
        //try to get semaphore
        //volatile long *p; p=(void*) 0xc02200E4; *p=0x46;
        _TakeSemaphore(semBinary, WAIT_FOREVER);
        //*p=0x0;
        
        //process data & store result
        kbd_data_process_request_data = kbd_process(); //kbd_process_copy();
        
        //give semaphore
        //volatile long *p2; p2=(void*) 0xc02200E0; *p2=0x46;
        _GiveSemaphore(semBinary);
        //*p2=0x0;
        
        //sleep to allow other task to grab it
        msleep(10);
    }
}
