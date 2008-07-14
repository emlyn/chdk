#include "kbd.h"
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
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luascript.h"
#include "../lib/lua/lstate.h"	// for L->nCcalls, baseCcalls


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

// ------ add by Masuji SUTO (start) --------------
static int mvideo,mplay;
static int nSW=0;
static int nRmt=0;
static int nWt=0;
static int nCount=0;
static int nCa=0;
static int nCount2=0;
static int nTxvideo=0;
static int nTxzoom=0;
static int nTxzname=KEY_ZOOM_IN;
static int nPlyname=KEY_LEFT;
static int nIntzpos;
static int nReczoom=0;
static int nTxtblcr=0;
int shutter_int=0;

#if defined(CAMERA_a450) || defined(CAMERA_ixus50_sd400) || defined(CAMERA_ixus55_sd450) || defined(CAMERA_ixus65_sd630) || defined(CAMERA_ixus70_sd1000) || defined(CAMERA_ixus700_sd500) || defined(CAMERA_ixus850_sd800)
#define ZSTEP_TABLE_SIZE 7
static int nTxtbl[]={0,1,2,3,4,5,6};
#endif

#if defined(CAMERA_s2is) || defined(CAMERA_s3is) || defined(CAMERA_s5is)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,11,25,41,64,86,105,128};
#endif

#if defined(CAMERA_tx1)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,18,43,55,76,93,113,124};
#endif

#if defined(CAMERA_a460) || defined(CAMERA_a530) || defined (CAMERA_a540) || defined(CAMERA_a550) || defined(CAMERA_a560) || defined(CAMERA_a570) || defined(CAMERA_ixus860_sd870)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,1,2,3,4,5,6,7};
#endif


#if defined(CAMERA_a610) ||  defined(CAMERA_a620) || defined(CAMERA_a630) || defined(CAMERA_a640) || defined(CAMERA_ixus800_sd700) || defined(CAMERA_ixus950_sd850)
#define ZSTEP_TABLE_SIZE 9
static int nTxtbl[]={0,1,2,3,4,5,6,7,8};
#endif

#if defined (CAMERA_a700) || defined(CAMERA_a710) || defined (CAMERA_a720)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,2,4,6,8,10,12,14};
#endif

#if defined(CAMERA_a650) || defined(CAMERA_g7)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,2,4,6,8,10,12,13};
#endif
// ------ add by Masuji SUTO (end)   --------------
#if defined(CAMERA_sx100is)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,3,6,9,13,16,20,23};
#endif

void kbd_sched_delay(long msec)
{
    KBD_STACK_PUSH(msec);
    KBD_STACK_PUSH(SCRIPT_SLEEP);
}


void kbd_sched_motion_detector(){
    KBD_STACK_PUSH(SCRIPT_MOTION_DETECTOR);
}

void kbd_sched_press(long key)
{
// WARNING stack program flow is reversed
    kbd_sched_delay(20);

    KBD_STACK_PUSH(key);
    KBD_STACK_PUSH(SCRIPT_PRESS);
}

void kbd_sched_release(long key)
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


void kbd_sched_click(long key)
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

static lua_State* L, *Lt;

static int is_lua()
{
  int len;
  char const* s;
  s = conf.script_file;
  len = strlen( s );
  return len >= 4 && ( s[len-1] == 'a' || s[len-1] == 'A' )
    && ( s[len-2] == 'u' || s[len-2] == 'U' )
    && ( s[len-3] == 'l' || s[len-3] == 'L' )
    && s[len-4] == '.';
}

static void lua_count_hook(lua_State *L, lua_Debug *ar)
{
  if( L->nCcalls <= L->baseCcalls )
    lua_yield( L, 0 );
}

static int lua_script_start( char const* script )
{
  L = lua_open();
  luaL_openlibs( L );
  register_lua_funcs( L );

  Lt = lua_newthread( L );
  lua_setfield( L, LUA_REGISTRYINDEX, "Lt" );
  if( luaL_loadstring( Lt, script ) != 0 ) {
    script_console_add_line( lua_tostring( Lt, -1 ) );
    lua_close( L );
    L = 0;
    Lt = 0;
    return 0;
  }
  lua_sethook(Lt, lua_count_hook, LUA_MASKCOUNT, 1000 );
  return 1;
}


static void script_start( int autostart )
{
    int i;

    shot_histogram_enabled = 0;
    if (autostart) auto_started = 1; else auto_started = 0;
    delay_target_ticks = 0;
    kbd_int_stack_ptr = 0;
    kbd_last_clicked = 0;
    /*if (!autostart)*/ kbd_key_release_all();

    script_console_clear();
    script_print_screen_init();

    save_params_values(0);

    if( autostart )
      script_console_add_line("***Autostart***");
    else
      script_console_add_line(lang_str(LANG_CONSOLE_TEXT_STARTED));

    if( is_lua() ) {
      
      if( !lua_script_start(state_ubasic_script) ) {
    script_print_screen_end();
    return;
      }
      for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
    if( script_params[i][0] ) {
    char var = 'a'+i;
    lua_pushlstring( L, &var, 1 );
    lua_pushnumber( L, conf.ubasic_vars[i] );
    lua_settable( L, LUA_GLOBALSINDEX );
    }
      }
    }
    else {
      ubasic_init(state_ubasic_script);

      for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        ubasic_set_variable(i, conf.ubasic_vars[i]);
      }
    }

    state_kbd_script_run = 1;

    if (conf.alt_prevent_shutdown != ALT_PREVENT_SHUTDOWN_ALT_SCRIPT) {
        enable_shutdown();
    }
}

void script_end()
{
    script_print_screen_end();
    if( L ) {
      lua_close( L );
      L = 0;
      Lt = 0;
    }
    else {
      ubasic_end();
    }

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
    int Lres;

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
	    if (shooting_in_progress() || mvideo) {
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

    if( L ) {
      Lres = lua_resume( Lt, 0 );

      if (Lres != LUA_YIELD && Lres != 0) {
	script_console_add_line( lua_tostring( Lt, -1 ) );
      }

      if (Lres != LUA_YIELD) {
        script_console_add_line(lang_str(LANG_CONSOLE_TEXT_FINISHED));
	script_end();
      }    
    } 
    else {
      ubasic_run();
      if (ubasic_finished()) {
	script_console_add_line(lang_str(LANG_CONSOLE_TEXT_FINISHED));
 	script_end();
      }    
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

int ubasic_camera_is_pressed(const char *s)
{
    long k = keyid_by_name(s);
    if (k==0xFF) return get_usb_power(1);
	if (k > 0) {
        return (kbd_is_key_pressed(k));
    } else {
	ubasic_error = 3;
    }
    return 0;
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
	kbd_blocked = 1;
	gui_kbd_enter();
	script_console_clear(); 
	script_console_add_line("***Autostart***"); //lang_str(LANG_CONSOLE_TEXT_STARTED));
	script_start( 1 );
}
void exit_alt()
{
	    kbd_blocked = 0;
	    gui_kbd_leave();
}

// ------ add by Masuji SUTO (start) --------------
void set_key_press(int nSet)
{
	key_pressed = nSet;
	kbd_blocked = nSet;
	nRmt = nSet;
}
// ------ add by Masuji SUTO (end) --------------

long kbd_process()
{
/* Alternative keyboard mode stated/exited by pressing print key.
 * While running Alt. mode shoot key will start a script execution.
 */
static int nCER=0;
// ------ modif by Masuji SUTO (start) --------------

unsigned int mmode;
unsigned int nCrzpos,i;
unsigned int drmode;

   if(conf.ricoh_ca1_mode)
  {
	drmode = shooting_get_drive_mode();
	mmode = mode_get();
	mplay = (mmode&MODE_MASK)==MODE_PLAY;
	mvideo= ((mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_STD || (mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_SPEED || (mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_COMPACT ||(mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_MY_COLORS || (mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_COLOR_ACCENT);
  }
       // deals with alt-mode switch and delay emulation
        if (key_pressed)
        {
                if (kbd_is_key_pressed(conf.alt_mode_button) ||
                        ((key_pressed >= CAM_EMUL_KEYPRESS_DELAY) && 
                         (key_pressed < CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION)))
                {
                        if (key_pressed <= CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION) 
                                key_pressed++;
                        if (key_pressed == CAM_EMUL_KEYPRESS_DELAY) 
                                kbd_key_press(conf.alt_mode_button);
                        else if (key_pressed == +CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION) 
                                kbd_key_release(conf.alt_mode_button);
                        return 1;
                } else 
                if (kbd_get_pressed_key() == 0)
                {
                        if (key_pressed != 100 && (key_pressed < CAM_EMUL_KEYPRESS_DELAY))
                        {
                                kbd_blocked = 1-kbd_blocked;
                                if (kbd_blocked) gui_kbd_enter(); else gui_kbd_leave();
                        }
                        key_pressed = 0;
                        return 1;
                }
                return 1;
        }
       
       // auto iso shift
        if (kbd_is_key_pressed(KEY_SHOOT_HALF) && kbd_is_key_pressed(conf.alt_mode_button)) return 0;
        
        if (kbd_is_key_pressed(conf.alt_mode_button))
        {
                if (conf.ricoh_ca1_mode) conf.synch_enable=1;
                key_pressed = 1;
                kbd_key_release_all();          
                return 1;
        }

        // deals with the rest
        if (kbd_blocked && nRmt==0)
        {
                if (kbd_is_key_pressed(KEY_SHOOT_FULL))
                {
                        key_pressed = 100;
                        if (!state_kbd_script_run)
                        {
                                script_start(0);
                        } else if (L || state_kbd_script_run == 2)
                        {
                                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_INTERRUPTED));
                                script_end();
                        } else
                        {
                            state_kbd_script_run = 2;
                            if (jump_label("restore") == 0)
                            {
                                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_INTERRUPTED));
                                script_end();
                            }
                        }
                }

                if (state_kbd_script_run) 
                        process_script(); else
                        gui_kbd_process();
        } else
        {

#ifndef SCRIPTLESS_REMOTE_NOT_ENABLED
if(conf.ricoh_ca1_mode)
{

// ------ add by Masuji SUTO (start) --------------
if(nWt>0) {nWt--;return 1;}
if (kbd_is_key_pressed(KEY_SHOOT_FULL)) conf.synch_enable=0;
	if (kbd_is_key_pressed(KEY_SHOOT_HALF) && nTxzoom>0) {
		nCount2=0;
		nTxzoom=0;
		nReczoom=0;
		nTxvideo=0;
		debug_led(0);
		}
	if (mplay && (kbd_is_key_pressed(KEY_LEFT) || kbd_is_key_pressed(KEY_RIGHT))){
		nPlyname=KEY_LEFT;
		if(kbd_is_key_pressed(KEY_RIGHT)) nPlyname=KEY_RIGHT;
		}
	if (kbd_is_key_pressed(KEY_VIDEO)){
		nCount2=0;
		nTxzoom=0;
		nReczoom=0;
		nTxvideo++;
		if(nTxvideo<50){
			kbd_key_release_all();
			debug_led(1);
			}
		else {
			debug_led(0);
			return 0;
			}
		return 1;
		}
	else if(nTxvideo>49) nTxvideo=0;
	if (kbd_is_key_pressed(KEY_ZOOM_IN) || kbd_is_key_pressed(KEY_ZOOM_OUT)){
		nCount2=0;
		nTxvideo=0;
		if(kbd_is_key_pressed(KEY_ZOOM_IN)) {
			if(nTxzname==KEY_ZOOM_IN) nTxzoom++;
			else nTxzoom=1;
			nTxzname=KEY_ZOOM_IN;
			}
		else {
			if(nTxzname==KEY_ZOOM_OUT) nTxzoom++;
			else nTxzoom=1;
			nTxzname=KEY_ZOOM_OUT;
			}
		if(nTxzoom<50){
			kbd_key_release_all();
			debug_led(1);
			}
		else {
			debug_led(0);
			return 0;
			}
		return 1;
		}
	if(!get_usb_power(1) && nSW<100 && nCount==0 && nTxzoom>0) {
		nCount2++;
		if(nCount2>1000){
			if(nTxzoom>0){
				nTxzoom=0;
				nReczoom=0;
				debug_led(0);
				}
			nCount2=0;
			}
		return 1;
		}
	if(get_usb_power(1) && nSW<100 && nCount==0) {nCount2=0;kbd_key_release_all();conf.synch_enable=1;}

	
	if(get_usb_power(1) && nSW<100 && nCount==0) {kbd_key_release_all();conf.synch_enable=1;}
	if(get_usb_power(1) && nSW<100 && nCount<6){
		nCount++;
		return 1;
		}
	if(nCount>0 && nSW<100){
		if(mplay) {
			if(get_usb_power(1)) return 1;
			kbd_key_release_all();
			kbd_key_press(nPlyname);
			set_key_press(1);
			nCount=0;
			nCa=2;
			nSW=101;
			nWt=5;
			return 1;
			}
		if(nTxvideo>49) nTxvideo=0;
		if(nCount<5) nCa=1;		//for Richo remote switch CA-1
		else nCa=2;				//for hand made remote switch
		nCount=0;
//		debug_led(1);
		nSW=109;
		}

// -------------------------------------------------------------  hand made switch  --------------

	if(nCa==2){
     		if(nSW==101){
			kbd_key_release_all();
			set_key_press(0);
			nWt=50;
			nSW=0;
			nCa=0;
			return 1;
			}                                       
		if(nSW==109){
		//	nSW=110;
			nCER=0;
			if(nTxzoom>0){
				if(nTxzoom<100){
					nIntzpos=lens_get_zoom_point();
					for(i=0;i<ZSTEP_TABLE_SIZE;i++){
						if(nIntzpos<=nTxtbl[i]){
							if(i>0){
								if(abs(nTxtbl[i]-nIntzpos)<=abs(nTxtbl[i-1]-nIntzpos)) nTxtblcr=i;
								else nTxtblcr=i-1;
								}
							else nTxtblcr=i;
							i=ZSTEP_TABLE_SIZE;
							}
						}
					if(nTxzname==KEY_ZOOM_IN){
						nTxtblcr++;
						if(nTxtblcr>(ZSTEP_TABLE_SIZE-1)) nTxtblcr=(ZSTEP_TABLE_SIZE-1);
						}
					else{
						nTxtblcr--;
						if(nTxtblcr<0) nTxtblcr=0;
						}
					nSW=108;
					return 1;
					}
				nTxzoom=0;
				nReczoom=0;
				}
			if(nTxvideo>0) {nSW=121;return 1;}
                                    nSW=110;
			nWt=2;
			kbd_key_release_all();
			kbd_key_press(KEY_SHOOT_HALF); 
		//	key_pressed = 1;
		//	kbd_blocked = 1;
		//	nRmt=1;
                  set_key_press(1);
			return 1;
			}
			if(nTxzoom>0 && nSW==108){
				nCrzpos=lens_get_zoom_point();
				if(nIntzpos!=nCrzpos) {nReczoom=0;}
				if(nIntzpos==nCrzpos && nCER>50){
					if(!get_usb_power(1)){
						kbd_key_release_all();
						set_key_press(0);
						nTxzoom=1;
						nSW=0;
						nCount=0;
						nWt=10;
						nReczoom=1;
						return 1;
						}
					}
				if(nReczoom==0 && ((nTxzname==KEY_ZOOM_IN && nCrzpos>=nTxtbl[nTxtblcr]) || (nTxzname==KEY_ZOOM_OUT && nCrzpos<=nTxtbl[nTxtblcr]))){
					if(get_usb_power(1)){
						i=1;
						if(nTxzname==KEY_ZOOM_IN){
							nTxtblcr++;
							if(nTxtblcr>(ZSTEP_TABLE_SIZE-1)) {nTxtblcr=(ZSTEP_TABLE_SIZE-1);i=0;}
							}
						else{
							nTxtblcr--;
							if(nTxtblcr<0) {nTxtblcr=0;i=0;}
							}
						if(i==1) return 1;
						}
					kbd_key_release_all();
					set_key_press(0);
					nTxzoom=1;
	//				lens_set_zoom_speed(25);
					nSW=120;
					nWt=5;
					return 1;
					}
				kbd_key_release_all();
				kbd_key_press(nTxzname); 
				set_key_press(1);
				nCER++;
				return 1;
				}
				
		if(nTxvideo>0 && nSW==121){
			if(!get_usb_power(1)) {
				nWt=10;
				kbd_key_press(KEY_VIDEO);
				set_key_press(1);
				nSW=122;
				}
			return 1;
			}
		if(nTxvideo>0 && nSW==122){
			nWt=10;
			kbd_key_release(KEY_VIDEO);
			set_key_press(1);
			nSW=123;
			return 1;
			}
		if(nTxvideo>0 && nSW==123){
			set_key_press(0);
			nWt=50;
			nSW=0;
			nCa=0;
			nTxvideo=0;
			debug_led(0);
			return 1;
			}

		if(nSW==110){
			if (shooting_in_progress() || mvideo || nCER>100) {
				state_expos_recalculated = 0;
				histogram_restart();
				nCER=0;
				nSW=111;
			    }
			else {nCER++;return 1;}
			}
		if(nSW==111){
			if (state_expos_recalculated || nCER>100) {
				state_expos_under = under_exposed;
				state_expos_over = over_exposed;
				nCER=0;
				nSW=112;
                        //presynch();
			    }
			else {nCER++;return 1;}
			}
		if(nSW==112){
		    if (shooting_is_flash_ready() || nCER>10){
				nCER=0;
				nSW=113;
			    }
			else {nCER++;return 1;}
			}
		if(nSW==113){
			if(get_usb_power(1) && !mvideo) nSW=114;
			else if(!get_usb_power(1) && mvideo) nSW=114;
			else return 1;
			}
		if(nTxzoom>0 && nSW==120){
			nCrzpos=lens_get_zoom_point();
			if((nTxzname==KEY_ZOOM_IN && nCrzpos<=nTxtbl[nTxtblcr]) || (nTxzname==KEY_ZOOM_OUT && nCrzpos>=nTxtbl[nTxtblcr])){
				kbd_key_release_all();
				set_key_press(0);
				nTxzoom=1;
				lens_set_zoom_speed(100);
				nSW=0;
				nCount=0;
				nWt=10;
				return 1;
				}
			lens_set_zoom_speed(5);
			kbd_key_release_all();
			if(nTxzname==KEY_ZOOM_IN) kbd_key_press(KEY_ZOOM_OUT); 
			else kbd_key_press(KEY_ZOOM_IN); 
			set_key_press(1);
			return 1;
			}

		if(nSW==114){
			nSW=115;
			nWt=2;
                  shutter_int=0;
			kbd_key_press(KEY_SHOOT_FULL); 
                                    set_key_press(1);
		//	kbd_blocked = 1;
		//	nRmt=1;
			nCount=0;
			return 1;
			}
		if(nSW==115){
	//		debug_led(0);
			if(drmode==1 && shutter_int==0){
				return 1;
				}
			nSW=116;
			nWt=2;
			kbd_key_release(KEY_SHOOT_FULL); 
                                    set_key_press(1);
		//	kbd_blocked = 1;
		//	nRmt=1;
			return 1;
			}
		if(!get_usb_power(1) && nSW==116) {
                                    set_key_press(0);
		//	kbd_blocked = 0;
		//	key_pressed = 0;
			nWt=50;
			nSW=0;
		//	nRmt=0;
			nCa=0;
                  //postsynch();
			return 1;
			}
		}

// -------------------------------------------------------------  Ricoh remote switch CA-1 --------------
	if(nCa==1){
		if(get_usb_power(1) && nSW>108 && nSW<120){
			nCount++;
			}
		if(nSW==109){
		//	nSW=110;
			nCER=0;
			if(nTxzoom>0){
				if(nTxzoom<100){
					nIntzpos=lens_get_zoom_point();
					for(i=0;i<ZSTEP_TABLE_SIZE;i++){
						if(nIntzpos<=nTxtbl[i]){
							if(i>0){
								if(abs(nTxtbl[i]-nIntzpos)<=abs(nTxtbl[i-1]-nIntzpos)) nTxtblcr=i;
								else nTxtblcr=i-1;
								}
							else nTxtblcr=i;
							i=ZSTEP_TABLE_SIZE;
							}
						}
					if(nTxzname==KEY_ZOOM_IN){
						nTxtblcr++;
						if(nTxtblcr>(ZSTEP_TABLE_SIZE-1)) nTxtblcr=(ZSTEP_TABLE_SIZE-1);
						}
					else{
						nTxtblcr--;
						if(nTxtblcr<0) nTxtblcr=0;
						}
					nSW=113;
					return 1;
					}
				nTxzoom=0;
				nReczoom=0;
				}
			if(nTxvideo>0) {nSW=121;return 1;}
                  nSW=110;
			nWt=2;
			kbd_key_release_all();
			kbd_key_press(KEY_SHOOT_HALF); 
//			debug_led(1);
                                    set_key_press(1);
		//	key_pressed = 1;
		//	kbd_blocked = 1;
		//	nRmt=1;
			return 1;
			}
		if(nTxvideo>0 && nSW==121){
			if(get_usb_power(1)) {
				nWt=10;
				kbd_key_press(KEY_VIDEO);
				set_key_press(1);
				nSW=122;
				}
			return 1;
			}
		if(nTxvideo>0 && nSW==122){
			nWt=10;
			kbd_key_release(KEY_VIDEO);
			set_key_press(1);
			nSW=123;
			return 1;
			}
		if(nTxvideo>0 && nSW==123){
			set_key_press(0);
			nWt=100;
			nCount=0;
			nSW=0;
			nCa=0;
			nTxvideo=0;
			debug_led(0);
			return 1;
			}

		if(nSW==110){
			if (shooting_in_progress() || mvideo || nCER>100) {
//				debug_led(0);
				state_expos_recalculated = 0;
				histogram_restart();
				nCER=0;
				nSW=111;
			    }
			else {nCER++;return 1;}
			}
		if(nSW==111){
			if (state_expos_recalculated || nCER>100) {
				state_expos_under = under_exposed;
				state_expos_over = over_exposed;
				nCER=0;
				nSW=112;
                        //presynch();
			    }
			else {nCER++;return 1;}
			}
		if(nSW==112){
		    if (shooting_is_flash_ready() || nCER>10){
				nCER=0;
				nSW=113;
			    }
			else {nCER++;return 1;}
			}
		if(nTxzoom>0 && nSW==114){
			nCrzpos=lens_get_zoom_point();
			if(nIntzpos!=nCrzpos) {nReczoom=0;}
			if(nIntzpos==nCrzpos && nCER>50){
				if(nCount>0){
					kbd_key_release_all();
					set_key_press(0);
					nTxzoom=1;
					nSW=0;
					nCount=0;
					nWt=10;
					nReczoom=1;
					return 1;
					}
				}
			if(nReczoom==0 && ((nTxzname==KEY_ZOOM_IN && nCrzpos>=nTxtbl[nTxtblcr]) || (nTxzname==KEY_ZOOM_OUT && nCrzpos<=nTxtbl[nTxtblcr]))){
				if(nCount==0){
					i=1;
					if(nTxzname==KEY_ZOOM_IN){
						nTxtblcr++;
						if(nTxtblcr>(ZSTEP_TABLE_SIZE-1)) {nTxtblcr=(ZSTEP_TABLE_SIZE-1);i=0;}
						}
					else{
						nTxtblcr--;
						if(nTxtblcr<0) {nTxtblcr=0;i=0;}
						}
					if(i==1) return 1;
					}
				kbd_key_release_all();
				set_key_press(0);
				nTxzoom=1;
//				lens_set_zoom_speed(25);
				nSW=115;
				nWt=5;
				return 1;
				}
			kbd_key_release_all();
			kbd_key_press(nTxzname); 
			set_key_press(1);
			nCER++;
			return 1;
			}
		if(nTxzoom>0 && nSW==115){
			if(nCount==0) return 1;
			nCrzpos=lens_get_zoom_point();
			if((nTxzname==KEY_ZOOM_IN && nCrzpos<=nTxtbl[nTxtblcr]) || (nTxzname==KEY_ZOOM_OUT && nCrzpos>=nTxtbl[nTxtblcr])){
				kbd_key_release_all();
				set_key_press(0);
				nTxzoom=1;
				lens_set_zoom_speed(100);
				nSW=0;
				nCount=0;
				nWt=10;
				return 1;
				}
			lens_set_zoom_speed(5);
			kbd_key_release_all();
			if(nTxzname==KEY_ZOOM_IN) kbd_key_press(KEY_ZOOM_OUT); 
			else kbd_key_press(KEY_ZOOM_IN); 
			set_key_press(1);
			return 1;
			}


		if(get_usb_power(1)){
			return 1;
			}
		if(nCount>0 && nSW==113){
			if(nCount<9){
				if(nTxzoom>0){
					kbd_key_release_all();
					set_key_press(0);
					nTxzoom=0;
					nReczoom=0;
					nSW=0;
					nCa=0;
					nCount=0;
					nWt=10;
//					lens_set_zoom_speed(100);
					debug_led(0);
					return 1;
					}
				nSW=125;
				nWt=10;
				kbd_key_release(KEY_SHOOT_HALF); 
	                                    set_key_press(1);
			//	kbd_blocked = 1;
			//	nRmt=1;
				nCount=0;
				return 1;
				}
			else{
				if(nTxzoom>0){
					nCount=0;
					nSW=114;
					return 1;
					}
				nSW=124;
				nWt=2;
                        shutter_int=0;
//				debug_led(0);
				kbd_key_press(KEY_SHOOT_FULL); 
                                                set_key_press(1);
			//	kbd_blocked = 1;
			//	nRmt=1;
				nCount=0;
				return 1;
				}
			}
		if(nSW==124){
	//		debug_led(0);
			if(drmode==1 && shutter_int==0){
				return 1;
				}
			nSW=125;
			nWt=2;
			kbd_key_release(KEY_SHOOT_FULL);
                  set_key_press(1);
		//	kbd_blocked = 1;
		//	nRmt=1;
			return 1;
			}
		if(!get_usb_power(1) && nSW==125) {
                                    set_key_press(0);
		//	kbd_blocked = 0;
		//	key_pressed = 0;
			nWt=50;
			nSW=0;
		//	nRmt=0;
			nCa=0;
                  //postsynch();
			return 1;
			}
		}

// ------ add by Masuji SUTO (end)   --------------

} // ricoh_ca1_mode
#endif

                if (conf.use_zoom_mf && kbd_use_zoom_as_mf()) {
                    return 1;
                }
                if (conf.fast_ev && kbd_use_up_down_as_fast_ev()) {
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
    { 0xFF,             "remote"     },
	{ 0xFFFF,           "no_key"     },
};

int keyid_by_name (const char *n)
{
    int i;
    for (i=0;i<sizeof(keynames)/sizeof(keynames[0]);i++)
	if (strcmp(keynames[i].keyname,n) == 0)
	    return keynames[i].keyid;
    return 0;
}

long kbd_use_up_down_as_fast_ev() {
    static long key_pressed = 0;
if (!(kbd_is_key_pressed(KEY_UP)) && !(kbd_is_key_pressed(KEY_DOWN))) key_pressed = 0;
    if (kbd_is_key_pressed(KEY_UP) && (mode_get()&MODE_MASK) == MODE_REC &&  ((mode_get()&MODE_SHOOTING_MASK) != MODE_M) &&  ((mode_get()&MODE_SHOOTING_MASK) != MODE_VIDEO_STD) && movie_status<4 && (canon_shoot_menu_active==0)) {

        if (conf.fast_ev && key_pressed == 0) {
#if (CAM_PROPSET == 1) 
            shooting_set_prop(25,shooting_get_prop(25)+(conf.fast_ev_step+1)*16);
            shooting_set_prop(26,shooting_get_prop(26)+(conf.fast_ev_step+1)*16);
#elif (CAM_PROPSET == 2)
            shooting_set_prop(107,shooting_get_prop(107)+(conf.fast_ev_step+1)*16);
            shooting_set_prop(207,shooting_get_prop(207)+(conf.fast_ev_step+1)*16);
#endif
            key_pressed = KEY_UP;
            return 1;
        }

    } 
    if (kbd_is_key_pressed(KEY_DOWN) && (mode_get()&MODE_MASK) == MODE_REC &&  ((mode_get()&MODE_SHOOTING_MASK) != MODE_M) && ((mode_get()&MODE_SHOOTING_MASK) != MODE_VIDEO_STD) && movie_status<4 && (canon_shoot_menu_active==0)) {

            
        if (conf.fast_ev && key_pressed == 0) {
            kbd_key_release_all();
#if (CAM_PROPSET == 1)
            shooting_set_prop(25,shooting_get_prop(25)-(conf.fast_ev_step+1)*16);
            shooting_set_prop(26,shooting_get_prop(26)-(conf.fast_ev_step+1)*16);
#elif (CAM_PROPSET == 2)
            shooting_set_prop(107,shooting_get_prop(107)-(conf.fast_ev_step+1)*16);
            shooting_set_prop(207,shooting_get_prop(207)-(conf.fast_ev_step+1)*16);
#endif
            key_pressed = KEY_DOWN;
            return 1;
        }

    } 
    return 0;
}
