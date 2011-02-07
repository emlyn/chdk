#include "kbd.h"
#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "action_stack.h"
#include "camera.h"
#include "histogram.h"
#include "gui_lang.h"
#include "console.h"
#include "lang.h"
#include "gui_lang.h"

long kbd_last_clicked;
int state_kbd_script_run;
int kbd_blocked;
static long delay_target_ticks;
static int soft_half_press = 0;
static int key_pressed;

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

#if defined(CAMERA_ixus960_sd950)
static int nFirst=1;
#endif

#if defined(CAMERA_a450) || defined(CAMERA_ixus50_sd400) || defined(CAMERA_ixusizoom_sd30) || defined(CAMERA_ixus40_sd300) || defined(CAMERA_ixus55_sd450) || defined(CAMERA_ixus60_sd600) || defined(CAMERA_ixus65_sd630) || defined(CAMERA_ixus70_sd1000) || defined(CAMERA_ixus700_sd500) || defined(CAMERA_ixus750_sd550) || defined(CAMERA_ixus850_sd800) || defined(CAMERA_ixus900_sd900) || defined(CAMERA_ixus75_sd750) || defined(CAMERA_a470) || defined(CAMERA_ixus90_sd790) || defined(CAMERA_ixus100_sd780) || defined(CAMERA_a480) || defined(CAMERA_d10) || defined(CAMERA_ixus85_sd770) || defined(CAMERA_ixus95_sd1200)

#define ZSTEP_TABLE_SIZE 7
static int nTxtbl[]={0,1,2,3,4,5,6};
#endif

#if defined(CAMERA_s2is) || defined(CAMERA_s3is) || defined(CAMERA_s5is) || defined(CAMERA_sx10) || defined(CAMERA_sx1)  || defined(CAMERA_sx20)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,11,25,41,64,86,105,128};
#endif

#if defined(CAMERA_sx30)
#define ZSTEP_TABLE_SIZE 11
static int nTxtbl[]={0,20,40,60,80,100,120,140,160,180,200};
#endif

#if defined(CAMERA_tx1)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,18,43,55,76,93,113,124};
#endif

#if defined(CAMERA_a430) || defined(CAMERA_a460) || defined(CAMERA_a530) || defined (CAMERA_a540) || defined(CAMERA_a550) || defined(CAMERA_a560) || defined(CAMERA_a570) || defined(CAMERA_a590) ||defined(CAMERA_ixus860_sd870) || defined(CAMERA_ixus960_sd950) || defined(CAMERA_ixus80_sd1100) || defined(CAMERA_ixus970_sd890) || defined(CAMERA_ixus980_sd990) || defined (CAMERA_ixus130_sd1400)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,1,2,3,4,5,6,7};
#endif


#if defined(CAMERA_a610) ||  defined(CAMERA_a620) || defined(CAMERA_a630) || defined(CAMERA_a640) || defined(CAMERA_ixus800_sd700) || defined(CAMERA_ixus950_sd850)
#define ZSTEP_TABLE_SIZE 9
static int nTxtbl[]={0,1,2,3,4,5,6,7,8};
#endif

#if defined (CAMERA_a700) || defined(CAMERA_a710) || defined (CAMERA_a720) || defined (CAMERA_a2000) 
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,2,4,6,8,10,12,14};
#endif

#if defined(CAMERA_a650) || defined(CAMERA_g7) || defined(CAMERA_g9)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,2,4,6,8,10,12,13};
#endif
// ------ add by Masuji SUTO (end)   --------------
#if defined(CAMERA_sx100is) || defined(CAMERA_sx110is)
#define ZSTEP_TABLE_SIZE 8
static int nTxtbl[]={0,3,6,9,13,16,20,23};
#endif

#if defined(CAMERA_ixus870_sd880)
#define ZSTEP_TABLE_SIZE 10
static int nTxtbl[]={0,1,2,3,4,5,6,7,8,9};
#endif

#if defined(CAMERA_sx200is)
#define ZSTEP_TABLE_SIZE 7
static int nTxtbl[]={0,16,32,62,78,102,125};
#endif

#if defined(CAMERA_g11) || defined(CAMERA_g12)
#define ZSTEP_TABLE_SIZE 14
static int nTxtbl[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
#endif
#if defined(CAMERA_s90)
#define ZSTEP_TABLE_SIZE 10
static int nTxtbl[]={0,1,2,3,4,5,6,7,8,9};
#endif

#ifdef OPT_SCRIPTING
// remote autostart
void script_autostart()
{
    kbd_blocked = 1;
    gui_kbd_enter();
    console_clear(); 
    script_console_add_line("***Autostart***"); //lang_str(LANG_CONSOLE_TEXT_STARTED));
    script_start_gui( 1 );
}
#endif

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

/*------------------- Alex scriptless remote additions start --------------------*/
static int remoteHalfShutter=0, remoteFullShutter=0, remoteShooting=0, remoteClickTimer=0;
#define REMOTE_MAX_CLICK_LENGTH	50
/*-------------------- Alex scriptless remote additions end ---------------------*/

/* 
    main kb processing
    this monster needs to be broken up and documented, remote stuff should go in it's own functions
*/
long kbd_process()
{
/* Alternative keyboard mode stated/exited by pressing print key.
 * While running Alt. mode shoot key will start a script execution.
 */
    static int nCER=0;
// ------ modif by Masuji SUTO (start) --------------

    unsigned int mmode;
    unsigned int nCrzpos,i;
    unsigned int drmode = 0;

    if(conf.ricoh_ca1_mode && conf.remote_enable) {
        drmode = shooting_get_drive_mode();
        mmode = mode_get();
        mplay = (mmode&MODE_MASK)==MODE_PLAY;
//      mvideo= ((mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_STD || (mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_SPEED || (mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_COMPACT ||(mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_MY_COLORS || (mmode&MODE_SHOOTING_MASK)==MODE_VIDEO_COLOR_ACCENT);
        mvideo=MODE_IS_VIDEO(mmode);
    }
    // deals with alt-mode switch and delay emulation
    if (key_pressed) {
        if (kbd_is_key_pressed(conf.alt_mode_button)
                || ((key_pressed >= CAM_EMUL_KEYPRESS_DELAY)
                && (key_pressed < CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION))) {
            if (key_pressed <= CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION) 
                key_pressed++;
            if (key_pressed == CAM_EMUL_KEYPRESS_DELAY) 
                kbd_key_press(conf.alt_mode_button);
            else if (key_pressed == +CAM_EMUL_KEYPRESS_DELAY+CAM_EMUL_KEYPRESS_DURATION) 
                kbd_key_release(conf.alt_mode_button);
            return 1;
        } else if (kbd_get_pressed_key() == 0) {
            if (key_pressed != 100 && (key_pressed < CAM_EMUL_KEYPRESS_DELAY)) {
                kbd_blocked = 1-kbd_blocked;
                if (kbd_blocked) 
                    gui_kbd_enter();
                else
                    gui_kbd_leave();
            }
            key_pressed = 0;
            return 1;
        }
        return 1;
    }
       
    // auto iso shift
    if (kbd_is_key_pressed(KEY_SHOOT_HALF) && kbd_is_key_pressed(conf.alt_mode_button)) 
        return 0;

    if (kbd_is_key_pressed(conf.alt_mode_button)) {
        if (conf.ricoh_ca1_mode && conf.remote_enable)
            conf.synch_enable=1;
        key_pressed = 1;
        kbd_key_release_all();          
        return 1;
    }

    // deals with the rest
    if (kbd_blocked && nRmt==0) {
/*------------------- Alex scriptless remote additions start --------------------*/
        if (remoteShooting) {
            if (remoteHalfShutter) {
                if (get_usb_power(1)) {
                    if (remoteClickTimer < REMOTE_MAX_CLICK_LENGTH) {
                        remoteHalfShutter=0;
                        remoteFullShutter=1;
                        kbd_key_press(KEY_SHOOT_FULL);
                    }
                    return 1;
                } else {
                    --remoteClickTimer;
                    if ( remoteClickTimer == 0 ) {
                        kbd_key_release_all();
                        remoteHalfShutter=0;
                        remoteShooting=0;
                        kbd_blocked=0;
                        return 0;
                    }
                }
            }

            if (remoteFullShutter) {
                if (get_usb_power(1)) {
                    return 1;
                } else {
                    kbd_key_release_all();
                    remoteFullShutter=0;
                    remoteShooting=0;
                    kbd_blocked=0;
                    return 0;
                }
            }
        }
/*-------------------- Alex scriptless remote additions end ---------------------*/
#ifdef OPT_SCRIPTING
        if (kbd_is_key_pressed(KEY_SHOOT_FULL)) {
            key_pressed = 100;
            if (!state_kbd_script_run) {
                script_start_gui(0);
            } else if (state_kbd_script_run == 2 || state_kbd_script_run == 3) {
                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_INTERRUPTED));
                script_end();
            }
#ifdef OPT_LUA
            else if (L) {
                state_kbd_script_run = 2;
				lua_run_restore();
                script_console_add_line(lang_str(LANG_CONSOLE_TEXT_INTERRUPTED));
                script_end();
            }
#endif
#ifdef OPT_UBASIC
            else {
                state_kbd_script_run = 2;
                if (jump_label("restore") == 0) {
                    script_console_add_line(lang_str(LANG_CONSOLE_TEXT_INTERRUPTED));
                    script_end();
                }
            }
#endif
        }
#endif

        action_stack_process_all();
        if (!state_kbd_script_run)
            gui_kbd_process();
    } else {
#ifndef SYNCHABLE_REMOTE_NOT_ENABLED
        if(conf.ricoh_ca1_mode && conf.remote_enable) {
// ------ add by Masuji SUTO (start) --------------
            if(nWt>0) {
                nWt--;
                return 1;
            }
#if defined(CAMERA_ixus960)
            if(nFirst==1) {
                if(nSW==0) {
                    nSW=1;
                    nWt=10;
                    kbd_key_release_all();
                    kbd_key_press(KEY_SHOOT_HALF); 
                    soft_half_press = 1;
                    set_key_press(1);
                    return 1;
                } else if(nSW==1) {
                    nSW=2;
                    nWt=10;
                    kbd_key_release(KEY_SHOOT_HALF); 
                    soft_half_press = 0;
                    set_key_press(1);
                    return 1;
                } else if(nSW==2) {
                    set_key_press(0);
                    nWt=10;
                    nSW=0;
                    nFirst=0;
                    return 1;
                }
            }
#endif // CAMERA_ixus960
            if (kbd_is_key_pressed(KEY_SHOOT_FULL))
                conf.synch_enable=0;
            if (kbd_is_key_pressed(KEY_SHOOT_HALF) && nTxzoom>0) {
                nCount2=0;
                nTxzoom=0;
                nReczoom=0;
                nTxvideo=0;
                debug_led(0);
            }
            if (mplay && (kbd_is_key_pressed(KEY_LEFT) || kbd_is_key_pressed(KEY_RIGHT))) {
                nPlyname=KEY_LEFT;
                if(kbd_is_key_pressed(KEY_RIGHT))
                    nPlyname=KEY_RIGHT;
            }
            if (kbd_is_key_pressed(KEY_VIDEO)) {
                nCount2=0;
                nTxzoom=0;
                nReczoom=0;
                nTxvideo++;
                if(nTxvideo<50) {
                    kbd_key_release_all();
                    debug_led(1);
                } else {
                    debug_led(0);
                    return 0;
                }
                return 1;
            }
            else if(nTxvideo>49)
                nTxvideo=0;
            if (kbd_is_key_pressed(KEY_ZOOM_IN) || kbd_is_key_pressed(KEY_ZOOM_OUT)) {
                nCount2=0;
                nTxvideo=0;
                if(kbd_is_key_pressed(KEY_ZOOM_IN)) {
                    if(nTxzname==KEY_ZOOM_IN)
                        nTxzoom++;
                    else
                        nTxzoom=1;
                    nTxzname=KEY_ZOOM_IN;
                } else {
                    if(nTxzname==KEY_ZOOM_OUT)
                        nTxzoom++;
                    else
                        nTxzoom=1;
                    nTxzname=KEY_ZOOM_OUT;
                }
                if(nTxzoom<50) {
                    kbd_key_release_all();
                    debug_led(1);
                } else {
                    debug_led(0);
                    return 0;
                }
                return 1;
            }
            if(!get_usb_power(1) && nSW<100 && nCount==0 && nTxzoom>0) {
                nCount2++;
                if(nCount2>conf.zoom_timeout*100) {
                    if(nTxzoom>0) {
                        nTxzoom=0;
                        nReczoom=0;
                        debug_led(0);
                    }
                    nCount2=0;
                }
                return 1;
            }
            if(get_usb_power(1) && nSW<100 && nCount==0) {
                nCount2=0;
                kbd_key_release_all();
                conf.synch_enable=1;
            }
            if(get_usb_power(1) && nSW<100 && nCount==0) {
                kbd_key_release_all();
                conf.synch_enable=1;
            }
            if(get_usb_power(1) && nSW<100 && nCount<6) {
                nCount++;
                return 1;
            }
            if(nCount>0 && nSW<100) {
                if(mplay) {
                    if(get_usb_power(1))
                        return 1;
                    kbd_key_release_all();
                    kbd_key_press(nPlyname);
                    set_key_press(1);
                    nCount=0;
                    nCa=2;
                    nSW=101;
                    nWt=5;
                    return 1;
                }
                if(nTxvideo>49)
                    nTxvideo=0;
                if(nCount<5)
                    nCa=1;                //for Richo remote switch CA-1
                else
                    nCa=2;                                //for hand made remote switch

                nCount=0;
//              debug_led(1);
                nSW=109;
            }

// -------------------------------------------------------------  hand made switch  --------------

            if(nCa==2) {
                if(nSW==101) {
                    kbd_key_release_all();
                    set_key_press(0);
                    nWt=50;
                    nSW=0;
                    nCa=0;
                    return 1;
                }                                       
                if(nSW==109) {
//                  nSW=110;
                    nCER=0;
                    if(nTxzoom>0 && conf.remote_zoom_enable) {
                        if(nTxzoom<100) {
                            nIntzpos=lens_get_zoom_point();
                            for(i=0;i<ZSTEP_TABLE_SIZE;i++) {
                                if(nIntzpos<=nTxtbl[i]) {
                                    if(i>0) {
                                        if(abs(nTxtbl[i]-nIntzpos)<=abs(nTxtbl[i-1]-nIntzpos))
                                            nTxtblcr=i;
                                        else
                                            nTxtblcr=i-1;
                                    }
                                    else nTxtblcr=i;
                                    i=ZSTEP_TABLE_SIZE;
                                }
                            }
                            if(nTxzname==KEY_ZOOM_IN) {
                                nTxtblcr++;
                                if(nTxtblcr>(ZSTEP_TABLE_SIZE-1))
                                    nTxtblcr=(ZSTEP_TABLE_SIZE-1);
                            } else {
                                nTxtblcr--;
                                if(nTxtblcr<0)
                                    nTxtblcr=0;
                            }
                            nSW=108;
                            return 1;
                        }
                        nTxzoom=0;
                        nReczoom=0;
                    }
                    if(nTxvideo>0 && conf.remote_zoom_enable) {
                        nSW=121;
                        return 1;
                    }
                    nSW=110;
                    nWt=2;
                    kbd_key_release_all();
                    kbd_key_press(KEY_SHOOT_HALF); 
//                  key_pressed = 1;
//                  kbd_blocked = 1;
//                  nRmt=1;
                    soft_half_press = 1;
                    set_key_press(1);
                    return 1;
                }
                if(nTxzoom>0 && nSW==108 && conf.remote_zoom_enable) {
                    nCrzpos=lens_get_zoom_point();
                    if(nIntzpos!=nCrzpos) {
                        nReczoom=0;
                    }
                    if(nIntzpos==nCrzpos && nCER>50) {
                        if(!get_usb_power(1)) {
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
                    if(nReczoom==0 && ((nTxzname==KEY_ZOOM_IN && nCrzpos>=nTxtbl[nTxtblcr]) 
                            || (nTxzname==KEY_ZOOM_OUT && nCrzpos<=nTxtbl[nTxtblcr]))) {
                        if(get_usb_power(1)) {
                            i=1;
                            if(nTxzname==KEY_ZOOM_IN) {
                                nTxtblcr++;
                                if(nTxtblcr>(ZSTEP_TABLE_SIZE-1)) {
                                    nTxtblcr=(ZSTEP_TABLE_SIZE-1);
                                    nTxzname=KEY_ZOOM_OUT;
                                }
                            } else {
                                nTxtblcr--;
                                if(nTxtblcr<0){
                                    nTxtblcr=0;
                                    nTxzname=KEY_ZOOM_IN;
                                }
                            }
                            if(i==1)
                                return 1;
                        }
                        kbd_key_release_all();
                        set_key_press(0);
                        nTxzoom=1;
//                      lens_set_zoom_speed(25);
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

                if(nTxvideo>0 && nSW==121) {
                    if(!get_usb_power(1)) {
                        nWt=10;
                        kbd_key_press(KEY_VIDEO);
                        set_key_press(1);
                        nSW=122;
                    }
                    return 1;
                }
                if(nTxvideo>0 && nSW==122) {
                    nWt=10;
                    kbd_key_release(KEY_VIDEO);
                    set_key_press(1);
                    nSW=123;
                    return 1;
                }
                if(nTxvideo>0 && nSW==123) {
                    set_key_press(0);
                    nWt=50;
                    nSW=0;
                    nCa=0;
                    nTxvideo=0;
                    debug_led(0);
                    return 1;
                }

                if(nSW==110) {
                    if (shooting_in_progress() || mvideo || nCER>100) {
                        state_expos_recalculated = 0;
                        histogram_restart();
                        nCER=0;
                        nSW=111;
                    } else {
                        nCER++;return 1;
                    }
                }
                if(nSW==111) {
                    if (state_expos_recalculated || nCER>100) {
                        state_expos_under = under_exposed;
                        state_expos_over = over_exposed;
                        nCER=0;
                        nSW=112;
                        //presynch();
                    } else {
                        nCER++;
                        return 1;
                    }
                }
                if(nSW==112) {
                    if (shooting_is_flash_ready() || nCER>10) {
                        nCER=0;
                        nSW=113;
                    } else {
                        nCER++;
                        return 1;
                    }
                }
                if(nSW==113) {
                    if(get_usb_power(1) && !mvideo)
                        nSW=114;
                    else if(!get_usb_power(1) && mvideo)
                        nSW=114;
                    else
                        return 1;
                }
                if(nTxzoom>0 && nSW==120 && conf.remote_zoom_enable) {
                    nCrzpos=lens_get_zoom_point();
                    if((nTxzname==KEY_ZOOM_IN && nCrzpos<=nTxtbl[nTxtblcr]) 
                            || (nTxzname==KEY_ZOOM_OUT && nCrzpos>=nTxtbl[nTxtblcr])) {
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
                    if(nTxzname==KEY_ZOOM_IN)
                        kbd_key_press(KEY_ZOOM_OUT); 
                    else
                        kbd_key_press(KEY_ZOOM_IN); 
                    set_key_press(1);
                    return 1;
                }

                if(nSW==114) {
                    nSW=115;
                    nWt=2;
                    shutter_int=0;
                    kbd_key_press(KEY_SHOOT_FULL); 
                    set_key_press(1);
//                  kbd_blocked = 1;
//                  nRmt=1;
                    nCount=0;
                    return 1;
                }
                if(nSW==115) {
//                  debug_led(0);
                    if(drmode==1 && shutter_int==0) {
                        return 1;
                    }
                    nSW=116;
                    nWt=2;
                    kbd_key_release(KEY_SHOOT_FULL); 
                    set_key_press(1);
                    soft_half_press = 0;
//                  kbd_blocked = 1;
//                  nRmt=1;
                    return 1;
                }
                if(!get_usb_power(1) && nSW==116) {
                    set_key_press(0);
//                  kbd_blocked = 0;
//                  key_pressed = 0;
                    nWt=50;
                    nSW=0;
//                  nRmt=0;
                    nCa=0;
                    //postsynch();
                    return 1;
                }
            }

// -------------------------------------------------------------  Ricoh remote switch CA-1 --------------
            if(nCa==1) {
                if(get_usb_power(1) && nSW>108 && nSW<120) {
                    nCount++;
                }
                if(nSW==109) {
//                  nSW=110;
                    nCER=0;
                    if(nTxzoom>0 && conf.remote_zoom_enable) {
                        if(nTxzoom<100) {
                            nIntzpos=lens_get_zoom_point();
                            for(i=0;i<ZSTEP_TABLE_SIZE;i++) {
                                if(nIntzpos<=nTxtbl[i]) {
                                    if(i>0) {
                                        if(abs(nTxtbl[i]-nIntzpos)<=abs(nTxtbl[i-1]-nIntzpos))
                                            nTxtblcr=i;
                                        else
                                            nTxtblcr=i-1;
                                    }
                                    else
                                        nTxtblcr=i;
                                    i=ZSTEP_TABLE_SIZE;
                                }
                            }
                            if(nTxzname==KEY_ZOOM_IN) {
                                nTxtblcr++;
                                if(nTxtblcr>(ZSTEP_TABLE_SIZE-1))
                                    nTxtblcr=(ZSTEP_TABLE_SIZE-1);
                            }
                            else {
                                nTxtblcr--;
                                if(nTxtblcr<0)
                                    nTxtblcr=0;
                            }
                            nSW=113;
                            return 1;
                        }
                        nTxzoom=0;
                        nReczoom=0;
                    }
                    if(nTxvideo>0 && conf.remote_zoom_enable) {
                        nSW=121;
                        return 1;
                    }
                    nSW=110;
                    nWt=2;
                    kbd_key_release_all();
                    kbd_key_press(KEY_SHOOT_HALF); 
//                  debug_led(1);
                    soft_half_press = 1;
                    set_key_press(1);
//                  key_pressed = 1;
//                  kbd_blocked = 1;
//                  nRmt=1;
                    return 1;
                }
                if(nTxvideo>0 && nSW==121) {
                    if(get_usb_power(1)) {
                        nWt=10;
                        kbd_key_press(KEY_VIDEO);
                        set_key_press(1);
                        nSW=122;
                    }
                    return 1;
                }
                if(nTxvideo>0 && nSW==122) {
                    nWt=10;
                    kbd_key_release(KEY_VIDEO);
                    set_key_press(1);
                    nSW=123;
                    return 1;
                }
                if(nTxvideo>0 && nSW==123) {
                    set_key_press(0);
                    nWt=100;
                    nCount=0;
                    nSW=0;
                    nCa=0;
                    nTxvideo=0;
                    debug_led(0);
                    return 1;
                }

                if(nSW==110) {
                    if (shooting_in_progress() || mvideo || nCER>100) {
//                      debug_led(0);
                        state_expos_recalculated = 0;
                        histogram_restart();
                        nCER=0;
                        nSW=111;
                    } else {
                        nCER++;
                        return 1;
                    }
                }
                if(nSW==111) {
                    if (state_expos_recalculated || nCER>100) {
                        state_expos_under = under_exposed;
                        state_expos_over = over_exposed;
                        nCER=0;
                        nSW=112;
                        //presynch();
                    } else {
                        nCER++;
                        return 1;
                    }
                }
                if(nSW==112) {
                    if (shooting_is_flash_ready() || nCER>10) {
                        nCER=0;
                        nSW=113;
                    } else {
                        nCER++;
                        return 1;
                    }
                }
                if(nTxzoom>0 && nSW==114 && conf.remote_zoom_enable) {
                    nCrzpos=lens_get_zoom_point();
                    if(nIntzpos!=nCrzpos) {
                        nReczoom=0;
                    }
                    if(nIntzpos==nCrzpos && nCER>50) {
                        if(nCount>0) {
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
                    if(nReczoom==0 && ((nTxzname==KEY_ZOOM_IN && nCrzpos>=nTxtbl[nTxtblcr]) 
                                || (nTxzname==KEY_ZOOM_OUT && nCrzpos<=nTxtbl[nTxtblcr]))) {
                        if(nCount==0) {
                            i=1;
                            if(nTxzname==KEY_ZOOM_IN){
                                nTxtblcr++;
                                if(nTxtblcr>(ZSTEP_TABLE_SIZE-1)){
                                    nTxtblcr=(ZSTEP_TABLE_SIZE-1);
                                    nTxzname=KEY_ZOOM_OUT;
                                }
                            } else {
                                nTxtblcr--;
                                if(nTxtblcr<0) {
                                    nTxtblcr=0;
                                    nTxzname=KEY_ZOOM_IN;
                                }
                            }
                            if(i==1)
                                return 1;
                        }
                        kbd_key_release_all();
                        set_key_press(0);
                        nTxzoom=1;
//                      lens_set_zoom_speed(25);
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
                if(nTxzoom>0 && nSW==115 && conf.remote_zoom_enable) {
                    if(nCount==0)
                        return 1;
                    nCrzpos=lens_get_zoom_point();
                    if((nTxzname==KEY_ZOOM_IN && nCrzpos<=nTxtbl[nTxtblcr])
                            || (nTxzname==KEY_ZOOM_OUT && nCrzpos>=nTxtbl[nTxtblcr])) {
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
                    if(nTxzname==KEY_ZOOM_IN)
                        kbd_key_press(KEY_ZOOM_OUT); 
                    else
                        kbd_key_press(KEY_ZOOM_IN); 
                    set_key_press(1);
                    return 1;
                }

                if(get_usb_power(1)) {
                    return 1;
                }
                if(nCount>0 && nSW==113) {
                    if(nCount<9) {
                        if(nTxzoom>0 && conf.remote_zoom_enable) {
                            kbd_key_release_all();
                            set_key_press(0);
                            nTxzoom=0;
                            nReczoom=0;
                            nSW=0;
                            nCa=0;
                            nCount=0;
                            nWt=10;
//                          lens_set_zoom_speed(100);
                            debug_led(0);
                            return 1;
                        }
                        nSW=125;
                        nWt=10;
                        kbd_key_release(KEY_SHOOT_HALF); 
                        soft_half_press = 0;
                        set_key_press(1);
//                      kbd_blocked = 1;
//                      nRmt=1;
                        nCount=0;
                        return 1;
                    } else {
                        if(nTxzoom>0 && conf.remote_zoom_enable) {
                            nCount=0;
                            nSW=114;
                            return 1;
                        }
                        nSW=124;
                        nWt=2;
                        shutter_int=0;
//                      debug_led(0);
                        kbd_key_press(KEY_SHOOT_FULL); 
                        set_key_press(1);
//                      kbd_blocked = 1;
//                      nRmt=1;
                        nCount=0;
                        return 1;
                    }
                }
                if(nSW==124) {
//                  debug_led(0);
                    if(drmode==1 && shutter_int==0) {
                        return 1;
                    }
                    nSW=125;
                    nWt=2;
                    kbd_key_release(KEY_SHOOT_FULL);
                    soft_half_press = 0;
                    set_key_press(1);
//                  kbd_blocked = 1;
//                  nRmt=1;
                    return 1;
                }
                if(!get_usb_power(1) && nSW==125) {
                    set_key_press(0);
//                  kbd_blocked = 0;
//                  key_pressed = 0;
                    nWt=50;
                    nSW=0;
//                  nRmt=0;
                    nCa=0;
                    //postsynch();
                    return 1;
                }
            }
// ------ add by Masuji SUTO (end)   --------------
        } // ricoh_ca1_mode
#endif // ifndef SYNCHABLE_REMOTE_NOT_ENABLED
/*------------------- Alex scriptless remote additions start --------------------*/
        if (conf.remote_enable && !conf.ricoh_ca1_mode && key_pressed != 2 && get_usb_power(1)) {
            remoteShooting = 1;
            kbd_blocked = 1;
            kbd_key_release_all();
            remoteClickTimer = REMOTE_MAX_CLICK_LENGTH;
            if (shooting_get_focus_mode()) {
                remoteFullShutter = 1;
                kbd_key_press(KEY_SHOOT_FULL);
            } else {
                remoteHalfShutter = 1;
                kbd_key_press(KEY_SHOOT_HALF);
            }
            return 1;
        }
/*-------------------- Alex scriptless remote additions end ---------------------*/
#ifdef CAM_USE_ZOOM_FOR_MF
        if (conf.use_zoom_mf && kbd_use_zoom_as_mf()) {
            return 1;
        }
#endif // ifdef CAM_USE_ZOOM_FOR_MF
        if ((conf.fast_ev || conf.fast_movie_control || conf.fast_movie_quality_control) 
                && kbd_use_up_down_left_right_as_fast_switch()) {
            return 1;
        }
        other_kbd_process(); // processed other keys in not <alt> mode 
    }

    return kbd_blocked;
}

int kbd_is_blocked() {
	return kbd_blocked;
}

void kbd_set_block(int bEnableBlock) {
    kbd_blocked = bEnableBlock ? 1 : 0;
}

long kbd_use_up_down_left_right_as_fast_switch() {
    static long key_pressed = 0; // ??? static masking a global
    int m=mode_get(); 
    int mode_video = MODE_IS_VIDEO(m) || (movie_status > 1);
    int ev_video=0;
    int jogdial;

#if CAM_EV_IN_VIDEO
    ev_video=get_ev_video_avail(); 
#endif

    if (!(kbd_is_key_pressed(KEY_UP)) && !(kbd_is_key_pressed(KEY_DOWN))) key_pressed = 0;

    if (canon_shoot_menu_active!=0 || (m&MODE_MASK) != MODE_REC)
        return 0;

#if !CAM_HAS_JOGDIAL
    if (kbd_is_key_pressed(KEY_UP) && ((m&MODE_SHOOTING_MASK) != MODE_M) && !mode_video) {
        if (conf.fast_ev && key_pressed == 0) {
            shooting_set_prop(PROPCASE_EV_CORRECTION_1,shooting_get_prop(PROPCASE_EV_CORRECTION_1)+(conf.fast_ev_step+1)*16);
            shooting_set_prop(PROPCASE_EV_CORRECTION_2,shooting_get_prop(PROPCASE_EV_CORRECTION_2)+(conf.fast_ev_step+1)*16);
            EnterToCompensationEVF();
            key_pressed = KEY_UP;
                
            return 1;
        }

    } 

    if (kbd_is_key_pressed(KEY_DOWN) && ((m&MODE_SHOOTING_MASK) != MODE_M) && !mode_video) {
        if (conf.fast_ev && key_pressed == 0) {
            kbd_key_release_all();
            shooting_set_prop(PROPCASE_EV_CORRECTION_1,shooting_get_prop(PROPCASE_EV_CORRECTION_1)-(conf.fast_ev_step+1)*16);
            shooting_set_prop(PROPCASE_EV_CORRECTION_2,shooting_get_prop(PROPCASE_EV_CORRECTION_2)-(conf.fast_ev_step+1)*16);
            key_pressed = KEY_DOWN;
            EnterToCompensationEVF();
            return 1;
        }
    } 

#else
    jogdial=get_jogdial_direction();

    if (conf.fast_ev &&kbd_is_key_pressed(KEY_SHOOT_HALF) && (jogdial==JOGDIAL_RIGHT) && ((m&MODE_SHOOTING_MASK) != MODE_M) && !mode_video) {
            shooting_set_prop(PROPCASE_EV_CORRECTION_1,shooting_get_prop(PROPCASE_EV_CORRECTION_1)+(conf.fast_ev_step+1)*16);
            shooting_set_prop(PROPCASE_EV_CORRECTION_2,shooting_get_prop(PROPCASE_EV_CORRECTION_2)+(conf.fast_ev_step+1)*16);
            EnterToCompensationEVF();
        }

    if (conf.fast_ev &&kbd_is_key_pressed(KEY_SHOOT_HALF) && (jogdial==JOGDIAL_LEFT) && ((m&MODE_SHOOTING_MASK) != MODE_M) && !mode_video) {
            shooting_set_prop(PROPCASE_EV_CORRECTION_1,shooting_get_prop(PROPCASE_EV_CORRECTION_1)-(conf.fast_ev_step+1)*16);
            shooting_set_prop(PROPCASE_EV_CORRECTION_2,shooting_get_prop(PROPCASE_EV_CORRECTION_2)-(conf.fast_ev_step+1)*16);
            EnterToCompensationEVF();
        }
     

#endif

    if (kbd_is_key_pressed(KEY_UP) && mode_video && movie_status == 4 ) {
        if (conf.fast_movie_quality_control && key_pressed == 0) {
            if (conf.video_mode==0) {
#if !CAM_VIDEO_QUALITY_ONLY
                conf.video_bitrate+=1;
                if (conf.video_bitrate>=VIDEO_BITRATE_STEPS)
                    conf.video_bitrate=VIDEO_BITRATE_STEPS-1;
                shooting_video_bitrate_change(conf.video_bitrate);
                movie_reset = 1;
#endif
            }    
            else if (conf.video_mode==1) {
                conf.video_quality+=1;
                if (conf.video_quality>VIDEO_MAX_QUALITY)
                    conf.video_quality=VIDEO_MAX_QUALITY;
                movie_reset = 1;
            }              
            key_pressed = KEY_UP;
            return 1;
        }
    } 
    
    if (kbd_is_key_pressed(KEY_DOWN) && mode_video && movie_status == 4) {
        if (conf.fast_movie_quality_control && key_pressed == 0) {
            if (conf.video_mode==0) {                
#if !CAM_VIDEO_QUALITY_ONLY
                conf.video_bitrate-=1;
                if (conf.video_bitrate<0)
                    conf.video_bitrate=0;

                shooting_video_bitrate_change(conf.video_bitrate);
                movie_reset = 1;
#endif
            }
            else if (conf.video_mode==1) {
                conf.video_quality-=1;
                if (conf.video_quality<1)
                    conf.video_quality=1;
                movie_reset = 1;
            }          
            key_pressed = KEY_DOWN;
            return 1;
        }
    } 
    
    if (kbd_is_key_pressed(KEY_LEFT) && mode_video && (movie_status == 4) && !ev_video) {
        if (conf.fast_movie_control && key_pressed == 0) {
            movie_status = VIDEO_RECORD_STOPPED;
            key_pressed = KEY_LEFT;
            return 1;
        }
    } 
	// reyalp - HACK for cams that can do video in any mode
	// note that this means this will probably run whenever you press right
    if (kbd_is_key_pressed(KEY_RIGHT) &&
#ifndef CAM_HAS_VIDEO_BUTTON 
            mode_video &&
#endif
	        (movie_status == 1) && !ev_video) {
        // BUG this doesn't know whether recording was stopped or paused.
        if (conf.fast_movie_control && key_pressed == 0) {
            movie_status = VIDEO_RECORD_IN_PROGRESS;
            movie_reset = 1;
            key_pressed = KEY_RIGHT;
            return 1;
        }
    } 

    return 0;
}
