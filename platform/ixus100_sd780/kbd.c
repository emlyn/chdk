#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "stdlib.h"
#include "gui.h"
#include "../../core/gui_draw.h"

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
static int aCount=0;
extern long aHookList[];
extern long aHookNum;

#define DELAY_TIMEOUT 10000

#define KEYS_MASK0 (0x0000000F)
#define KEYS_MASK1 (0x00094800)
#define KEYS_MASK2 (0x00007041)

#define SD_READONLY_FLAG (0x20000)  // 1 << 0x11
#define SD_READONLY_REG 2

#define USB_MASK (0x40000)

volatile int jogdial_stopped=0;

void kbd_fetch_data(long*);
long kbd_get_held_key();

long __attribute__((naked)) wrap_kbd_p1_f() ;

void wait_until_remote_button_is_released(void)
{
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
if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| (shooting_get_drive_mode()==1) || ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))
// if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable)                                         // synch mode enable so wait for USB to disconnect
  {
// ------ add by Masuji SUTO (start) --------------
        nMode=0;
        usb_physw[2] = 0;                                             // makes sure USB bit is cleared.
        _kbd_read_keys_r2(usb_physw);
        if((usb_physw[2] & USB_MASK)==USB_MASK) nMode=1;
// ------ add by Masuji SUTO (end)   --------------

if(conf.ricoh_ca1_mode && conf.remote_enable)
{
	if(shooting_get_drive_mode() ==1 && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){			//continuous-shooting mode
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
            usb_physw[2] = 0;                                             // makes sure USB bit is cleared.
           _kbd_read_keys_r2(usb_physw);
           }
 //  while(((usb_physw[2] & USB_MASK)==USB_MASK) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
// ------ modif by Masuji SUTO (start) --------------
        while(((((usb_physw[2] & USB_MASK)!=USB_MASK) && (nMode==0)) || (((usb_physw[2] & USB_MASK)==USB_MASK) && (nMode==1))) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
// ------ modif by Masuji SUTO (end)   --------------
 	}
 }

else
   {

      do
          {
            usb_physw[2] = 0;                                             // makes sure USB bit is cleared.
           _kbd_read_keys_r2(usb_physw);

           }
        while((usb_physw[2]&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));
    }

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

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline))
mykbd_task()
{
    mykbd_task_proceed();

    _ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{

    asm volatile(
                "STMFD   SP!, {R1-R5,LR}\n"
                "MOV     R4, #0\n"
                "BL      my_kbd_read_keys\n"
               	"B	 _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}
void save_rom_log() {
	asm volatile(
		"mov r0, #0 \n"
		"mov r1, #1 \n"
		"stmdb sp!, {r0, r1, lr}\n"
		"mov r0, sp\n"
		"BL =0xFF922E14\n"  //GetLogToFile
		"ldmia sp!, {r0, r1, lr}\n"
	);
}

void dumpProps() {
	short int avv;
	int i;
	char aStr[50];
	long l;

	l=Fopen_Fut("A/PropDmp.txt","a");
	for (i=0;i<300;i++){
		_GetPropertyCase(i, &avv, sizeof(avv));	// 23 for DiGiC III
		sprintf(aStr,"[%3d]=(%8x)\n",i,avv);
		Fwrite_Fut(aStr,1,strlen(aStr),l);
	}
	Fflush_Fut(l);
	Fclose_Fut(l);
}

int dump1900_SD780() {

	#define START_ADDRESS     0x1900
	#define FWSIZE            0x30

	long l;
	int j,k;
	int* myPtr, myPtr2;
	char sampleChr[64];

	myPtr = (int*)aHookList;

	//myPtr2 = (int*)*myPtr;

	//l=(void*)Fopen_Fut("A/0x1900.bin","ab");
	//Fwrite_Fut(START_ADDRESS,1,FWSIZE,l);
	//Fwrite_Fut(0xFF814EC8,1,16,l);
	//Fflush_Fut(l);
	//Fclose_Fut(l);
	j=0;

	l=Fopen_Fut("A/aHookList.txt","ab");

	while (j<aHookNum)
	{
		j++;
		myPtr=(int*)aHookList[j];
		myPtr=myPtr-0x18;
		for (k=0;k<FWSIZE;k++)
		{
			if ((*myPtr > 0xff810000) && (*myPtr < 0xFFA00000))
			{
				sprintf(sampleChr,"loc:%8x - data:%8x - *data:%16s\n",myPtr,*myPtr,*myPtr);
			}
			else
			{
				sprintf(sampleChr,"loc:%8x - data:%8x - *data:unsafe\n",myPtr,*myPtr);//*myPtr);
			}
			Fwrite_Fut(sampleChr,1,63,l);
			myPtr++;
		}
		sprintf(sampleChr,"Next Hook\n",myPtr,*myPtr,*myPtr);
		Fwrite_Fut(sampleChr,1,63,l);
		Fflush_Fut(l);
	}
	Fflush_Fut(l);
	Fclose_Fut(l);
	return 0;

//myPtr = (int*)0x1984;
//*myPtr = jF;
//myPtr = (int*)0x197C;
//*myPtr = jF;
	//		int fd;

		//	script_console_add_line(buf);
		//	script_console_draw();

		//char filen=malloc(16);
		//int i;
		//for (i=0x4; i>0; i = i << 1) {
		//	sprintf(filen, "A/crash_%i_.log", i);
		//	fd = open("A/crash.log", O_WRONLY|O_CREAT|O_APPEND, 0777);
		//	write(fd, buf, len);
		//	close(jF);
}




//int dumpFW_SD780() {
//
//#define MIN_ADDRESS     0xFF800000
//#define FW_SIZE         0x7FFFFF
//#define START_SECTOR    2048
//
//char j[]="A/test.bin";
//char k[]="wb";
//void* l;
//
//l=(void*)Fopen_Fut("A/test.bin","w");
//Fwrite_Fut(MIN_ADDRESS,1,FW_SIZE,l);
//Fflush_Fut(l);
//Fclose_Fut(l);
//
////		wr=(f_w)*(unsigned int*)(0xFF903B38);
////
////	int i;
////	unsigned long sa;
////
////	sa = MIN_ADDRESS;
////	i=wr(1,2048,FW_SIZE/512,sa);
////	debug_led(1);
////	while(1);
//	return 0;
//}





void my_kbd_read_keys()
{

	static char osd_buf[64];
    volatile long *mmio2 = (void*)0xE240;  //VERIFY_SD780 - Used to override long held DISP - Needs to be #DEFINE
	int isHeldDisp = 0;

	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];
	kbd_fetch_data(kbd_new_state);

//    short xA;
//	char aC[64];
//    get_property_case(223, &xA, sizeof(xA));
//	sprintf(aC,"223 - (%8x)",xA);
//	draw_txt_string(15, 5, aC, conf.osd_color);
//    get_property_case(102, &xA, sizeof(xA));
//	sprintf(aC,"102 - (%8x)",xA);
//	draw_txt_string(15, 6, aC, conf.osd_color);

/*
	sprintf(aC,"physw_run - (%8x)",physw_run);
	draw_txt_string(1, 3, aC, conf.osd_color);
	sprintf(aC,"zoom_busy - (%8x)",zoom_busy);
	draw_txt_string(1, 4, aC, conf.osd_color);
	sprintf(aC,"focus_busy - (%8x)",focus_busy);
	draw_txt_string(1, 5, aC, conf.osd_color);
	sprintf(aC,"canon_menu_active - (%8x)",canon_menu_active);
	draw_txt_string(1, 6, aC, conf.osd_color);
	sprintf(aC,"canon_shoot_menu_active - (%8x)",canon_shoot_menu_active);
	draw_txt_string(1, 7, aC, conf.osd_color);
	sprintf(aC,"recreview_hold - (%8x)",recreview_hold);
	draw_txt_string(1, 8, aC, conf.osd_color);
	sprintf(aC,"some_flag_for_af_scan - (%8x)",some_flag_for_af_scan);
	draw_txt_string(1, 9, aC, conf.osd_color);
*/

/*
	sprintf(osd_buf, "1:       %8x  --> %8x", physw_status[0],kbd_new_state[0]);
	draw_txt_string(20, 10, osd_buf, conf.osd_color);

	sprintf(osd_buf, "2:       %8x  --> %8x", physw_status[1],kbd_new_state[1]);
	draw_txt_string(20, 11, osd_buf, conf.osd_color);

	sprintf(osd_buf, "3:       %8x  --> %8x", physw_status[2],kbd_new_state[2]);
	draw_txt_string(20, 12, osd_buf, conf.osd_color);
	msleep(500);
*/
	if (kbd_get_held_key() == KEY_PRINT) {
		draw_txt_string(26, 14, "<DISP>", conf.osd_color);
		isHeldDisp=1;
	}
	if (kbd_get_pressed_key() == KEY_UP) {
//		 volatile long *aVar = (void*)0x5AD8;
//		 volatile long *aVar2 = (void*)0x13614;
//		 char aStr2[64];
//		 sprintf(aStr2,"[ x = %d ]",*(long*)(aVar+0x40));
//		 draw_txt_string(15, 10, aStr2, conf.osd_color);
	}

//		 sprintf(aStr2,"[ y = %d ]",*(long*)(aVar-0x40));
//		 draw_txt_string(15, 11, aStr2, conf.osd_color);
//		 sprintf(aStr2,"[ z = %d ]",*(long*)(aVar2+0x1C));
//		 draw_txt_string(15, 12, aStr2, conf.osd_color);
//		 sprintf(aStr2,"[ a = %d ]",*(long*)(aVar2-0x20));
//		 draw_txt_string(15, 13, aStr2, conf.osd_color);
//	}
//	    short int avv;
//	    char aStr[50];
//
//	    _GetPropertyCase(PROPCASE_AV, &avv, sizeof(avv));	// 23 for DiGiC III
//	    sprintf(aStr,"[ AV = %d ]",avv);
//		draw_txt_string(26, 14, aStr, conf.osd_color);
//		}
//

//		gui_compare_props(1);
//		msleep(5000);
		//dumpProps();
//		_ShowAllTaskInfo();
		//_qprintf("*");
		//dump1900_SD780();
		//_qprintf("1");
		//dump1900_SD780();
		//_qprintf("34");
		//dump1900_SD780();
		//_qprintf("s123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890b");
		//dump1900_SD780();
		//short jV;
		//_GetPropertyCase(149, &jV, sizeof(jV));
		//jV=jV-20;
		//_SetPropertyCase(149, &jV, sizeof(jV));
		//draw_txt_string(27, 12, "dumpProps()", conf.osd_color);
//		}
/*	if (kbd_get_pressed_key() == KEY_DOWN) {
    short xA[301];
    int iS;
    int iL;


    for (iS=0;iS<300;iS++)
    {
    	get_property_case(iS, &xA[iS], sizeof(xA[iS]));
    }
    iL=1;
    for (iS=0;iS<300;iS=iS+20)
    {
    	char outStr[128];
    	sprintf(outStr,"[%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d|%3d]\n",xA[iS],xA[iS+1],xA[iS+2],xA[iS+3],xA[iS+4],xA[iS+5],xA[iS+6],xA[iS+7],xA[iS+8],xA[iS+9],xA[iS+10],xA[iS+11],xA[iS+12],xA[iS+13],xA[iS+14],xA[iS+15],xA[iS+16],xA[iS+17],xA[iS+18],xA[iS+19]);
    	draw_txt_string(1, iL, outStr, conf.osd_color);
    	iL++;
    }
	}*/


//	if (kbd_get_pressed_key() == KEY_DOWN) {
/*
#define PROPCASE_DRIVE_MODE					102
#define PROPCASE_FOCUS_MODE					133
#define PROPCASE_FLASH_MODE    		        143
#define PROPCASE_FLASH_FIRE				122
#define PROPCASE_FLASH_MANUAL_OUTPUT    141
#define PROPCASE_FLASH_ADJUST_MODE       	121
#define PROPCASE_USER_TV       				264
#define PROPCASE_TV	        				262
#define PROPCASE_USER_AV      					26
#define PROPCASE_AV            				23
#define PROPCASE_MIN_AV       					25
#define PROPCASE_SV            				247
#define PROPCASE_DELTA_SV      				79
#define PROPCASE_SV_MARKET     				246
#define PROPCASE_BV            				34
#define PROPCASE_SUBJECT_DIST1 				245
#define PROPCASE_SUBJECT_DIST2 				65
#define PROPCASE_ISO_MODE		    			149
#define PROPCASE_SHOOTING      				206
#define PROPCASE_IS_FLASH_READY      			208
#define PROPCASE_OVEREXPOSURE 					103
#define PROPCASE_SHOOTING_MODE					49
#define PROPCASE_IS_MODE					    145
#define PROPCASE_QUALITY				        57
#define PROPCASE_RESOLUTION				        218
#define PROPCASE_EV_CORRECTION_1				107
#define PROPCASE_EV_CORRECTION_2				207
#define PROPCASE_ORIENTATION_SENSOR			219
#define PROPCASE_DIGITAL_ZOOM_STATE                            94
#define PROPCASE_DIGITAL_ZOOM_POSITION                         95
#define PROPCASE_DISPLAY_MODE                         105
#define PROPCASE_BRACKET_MODE                         29
#define PROPCASE_FLASH_SYNC_CURTAIN			64
#define PROPCASE_METERING_MODE				155
#define PROPCASE_WB_ADJ                               269
#define PROPCASE_ASPECT_RATIO          294
#define ZOOM_OPTICAL_MIN         1
#define ZOOM_OPTICAL_MAX         2
#define ZOOM_OPTICAL_MEDIUM      3
#define ZOOM_OPTICAL_IN          4
#define ZOOM_OPTICAL_OUT         5
#define ZOOM_OPTICAL_REACHED_MIN 7

#define ZOOM_DIGITAL_MAX         9
#define ZOOM_DIGITAL_MEDIUM      10
#define ZOOM_DIGITAL_IN          11
#define ZOOM_DIGITAL_OUT         12
#define ZOOM_DIGITAL_REACHED_MAX 13
*/



//	    get_property_case(PROPCASE_DIGITAL_ZOOM_STATE, &x, sizeof(x));
//	    if (x) {
//	     get_property_case(PROPCASE_DIGITAL_ZOOM_POSITION, &x, sizeof(x));
//	     if (x==0) zoom_status=ZOOM_OPTICAL_MEDIUM;
//	    }
		//dump1900_SD780();
		//draw_txt_string(27, 9, "_DownKey", conf.osd_color);
//		}
	if (kbd_get_pressed_key() == KEY_UP) {



		//shooting_get_drive_mode();
		//draw_txt_string(conf.temp_pos.x-10, conf.temp_pos.y, "dumpProps()", conf.osd_color);
		//draw_string(conf.temp_pos.x, conf.temp_pos.y, osd_buf, conf.osd_color);
	}
//	if (kbd_get_pressed_key() == KEY_UP) {
		//_UnsetZoomForMovie();
		//_HdmiRegDump();_EdidDump();
		//_drvInfo();
		//_blah();
		//dump1900_SD780();
		//_MoveIrisFullClose(1);
		//draw_txt_string(27, 12, "_ShowAllTaskInfo()", conf.osd_color);
//		}
//	if (kbd_get_pressed_key() == KEY_RIGHT) {
//		_PutInNdFilter();
//		draw_txt_string(27, 12, "NdIn", conf.osd_color);
//		}

	if (isHeldDisp != 1)
	{
		if (kbd_process() == 0)
		{
			physw_status[0] = kbd_new_state[0];
			physw_status[1] = kbd_new_state[1];
			physw_status[2] = (physw_status[2]  & (~KEYS_MASK2)) |
			(kbd_new_state[2] & KEYS_MASK2);
			physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;
		}
		else
		{
		// override keys
			physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |
					  (kbd_mod_state[0] & KEYS_MASK0);
			physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) |
					  (kbd_mod_state[1] & KEYS_MASK1);
			physw_status[2] = (physw_status[2]  & (~KEYS_MASK2)) |
						(kbd_mod_state[2] & KEYS_MASK2);  //fix needed as below
			physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;

		//	physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |
		//			  (kbd_mod_state[2] & KEYS_MASK2);
		//	if ((jogdial_stopped==0) && !state_kbd_script_run){
		//                jogdial_stopped=1;
		//                get_jogdial_direction();
		//        }
		//	else if (jogdial_stopped && state_kbd_script_run)
		//                jogdial_stopped=0;
		//
		}
	}
	else
	{
//		draw_txt_string(26, 14, "      ", conf.osd_color);
		isHeldDisp = 0;
		*mmio2 = *mmio2 & ~(0x00000040);
	}
/*
    _kbd_read_keys_r2(physw_status);

//    physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;


    remote_key = (physw_status[2] & USB_MASK)==USB_MASK;
      if (remote_key)  remote_count += 1;
      else if (remote_count) {
         usb_power = remote_count;
         remote_count = 0;
      }

    if (conf.remote_enable) {
      physw_status[2] = physw_status[2] & ~(SD_READONLY_FLAG | USB_MASK);
     }
    else physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;

    //_kbd_pwr_off();
*/
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
	    ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)){
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

long kbd_get_held_key() {
    static long last_kbd_time = 0, press_count = 0;
    register long key, t;

    key=kbd_get_clicked_key();
    if (key) {
        last_kbd_key = key;
        press_count = 0;
        last_kbd_time = get_tick_count();
        return 0;
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


static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */

	//SD780 - Keymap
	{ 0, KEY_UP		    , 0x00000008 },
	{ 0, KEY_DOWN		, 0x00000004 },
	{ 0, KEY_LEFT		, 0x00000001 },
	{ 0, KEY_RIGHT		, 0x00000002 },


	{ 1, KEY_SET		, 0x00004000 },
//	{ 1, KEY_PLAY		, 0x00080000 },  //SD780 Play button
	{ 1, KEY_MENU		, 0x00000800 },
//	{ 1, KEY_POWER		, 0x00010000 },  //SD780 Power button

	//xxxf --> xxxd when in movie mode by switch
	//xxxxxxx4 --> xxxxxxx5 when in lens extended recording mode


	{ 2, KEY_SHOOT_FULL	, 0x00001001 },
	{ 2, KEY_SHOOT_HALF	, 0x00000001 },
	{ 2, KEY_ZOOM_IN	, 0x00004000 },
	{ 2, KEY_ZOOM_OUT	, 0x00002000 },
	{ 2, KEY_PRINT		, 0x00000040 }, //doesn't exist
	{ 2, KEY_DISPLAY	, 0x00000040 }, //swapped for print atm
										//We will see if I can make KEY_DISPLAY a long KEY_DISPLAY...
	{ 0, 0, 0 }
};


void kbd_fetch_data(long *dst)
{
	//SD780 0xFF8431EC GetKbdState
    volatile long *mmio0 = (void*)0xc0220200;
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = *mmio0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 & 0xffff;
}
