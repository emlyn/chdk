#ifndef PLATFORM_H
#define PLATFORM_H

#include "camera.h"

#define SSID_INVALID (-32767)
#define ASID_INVALID (-32767)

#define MODE_MASK               0x0300
#define MODE_REC                0x0100
#define MODE_PLAY               0x0200

#define MODE_SHOOTING_MASK      0x00FF

enum {
MODE_AUTO               =1,
MODE_P                  ,
MODE_TV                 ,
MODE_AV                 ,
MODE_M                  ,
MODE_PORTRAIT           ,
MODE_NIGHT              ,
MODE_LANDSCAPE          ,
MODE_VIDEO_STD          ,
MODE_VIDEO_SPEED        ,
MODE_VIDEO_COMPACT      ,
MODE_VIDEO_MY_COLORS    ,
MODE_VIDEO_COLOR_ACCENT ,
MODE_STITCH             ,
MODE_MY_COLORS          ,
MODE_SCN_WATER          ,
MODE_SCN_NIGHT          ,
MODE_SCN_CHILD          ,
MODE_SCN_PARTY          ,
MODE_SCN_GRASS          ,
MODE_SCN_SNOW           ,
MODE_SCN_BEACH          ,
MODE_SCN_FIREWORK       ,
MODE_SCN_COLOR_ACCENT   ,
MODE_VIDEO_HIRES        ,
MODE_SCN_AQUARIUM       ,
MODE_COLOR_ACCENT       ,
MODE_SCN_NIGHT1         ,
MODE_SCN_ISO_3200       ,
MODE_SCN_SPORT          ,
MODE_SCN_KIDS_PETS      ,
MODE_INDOOR             ,
MODE_KIDS_PETS          ,
MODE_NIGHT_SNAPSHOT     ,
MODE_DIGITAL_MACRO      ,
MODE_SCN_FOLIAGE        ,
MODE_VIDEO_TIME_LAPSE   ,
MODE_SCN_INDOOR         ,
MODE_SCN_PORTRAIT       ,
MODE_SUPER_MACRO        ,
MODE_VIDEO_PORTRAIT     ,
MODE_VIDEO_NIGHT        ,
MODE_VIDEO_INDOOR       ,
MODE_VIDEO_FOLIAGE      ,
MODE_VIDEO_SNOW         ,
MODE_VIDEO_BEACH        ,
MODE_VIDEO_AQUARIUM     ,
MODE_VIDEO_SUPER_MACRO  ,
MODE_VIDEO_STITCH       ,
MODE_VIDEO_MANUAL       ,
MODE_SPORTS							,
};

#if CAM_PROPSET == 2     // most digic3 cameras
 #define PROPCASE_DRIVE_MODE					102
 #define PROPCASE_FOCUS_MODE					133
 #define PROPCASE_FLASH_MODE    		        143
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
 #define PROPCASE_EV_CORRECTION_1				107
 #define PROPCASE_EV_CORRECTION_2				207
 #define PROPCASE_ORIENTATION_SENSOR			219
 #define PROPCASE_DIGITAL_ZOOM_STATE                            94
 #define PROPCASE_DIGITAL_ZOOM_POSITION                         95
 #define PROPCASE_DISPLAY_MODE                         105
 #define PROPCASE_BRACKET_MODE                         278 //fictional value! need to find out!
#elif CAM_PROPSET == 1   // most digic2 cameras
 #define PROPCASE_DRIVE_MODE    				6
 #define PROPCASE_FOCUS_MODE    				12
 #define PROPCASE_FLASH_MODE       				16
// need corresponding values for propset2!!!
// #define PROPCASE_FLASH_ADJUST_MODE       	15
// #define PROPCASE_FLASH_CORRECTION               28      
// #define PROPCASE_FLASH_MANUAL_OUTPUT    29
//  #define PROPCASE_FOCUS_OK           67
 #define PROPCASE_USER_TV       				40
 #define PROPCASE_TV	        				69
 #define PROPCASE_USER_AV       				39
 #define PROPCASE_AV            				68
 #define PROPCASE_MIN_AV        				77
 #define PROPCASE_SV            				73
 #define PROPCASE_DELTA_SV      				70
 #define PROPCASE_SV_MARKET     				72
 #define PROPCASE_BV            				71
 #define PROPCASE_ISO_MODE      				21
 #define PROPCASE_SUBJECT_DIST1 				65
 #define PROPCASE_SUBJECT_DIST2 				66
 #define PROPCASE_SHOOTING     					205
 #define PROPCASE_IS_FLASH_READY   				221
 #define PROPCASE_OVEREXPOSURE 					76
 #define PROPCASE_SHOOTING_MODE					0
 #define PROPCASE_IS_MODE				        229
 #define PROPCASE_EV_CORRECTION_1				25
 #define PROPCASE_EV_CORRECTION_2				26
 #define PROPCASE_ORIENTATION_SENSOR			37
 #define PROPCASE_DIGITAL_ZOOM_STATE                            58
 #define PROPCASE_DIGITAL_ZOOM_POSITION                         57
 #define PROPCASE_DISPLAY_MODE                         181
 #define PROPCASE_BRACKET_MODE                         36 //missing for dryos!
#else
 #error unknown camera processor
#endif


#define MAX_DIST 65535

//********************
//char * get_debug();
//********************

#define MODE_SCREEN_MASK        0x0C00
#define MODE_SCREEN_OPENED      0x0400
#define MODE_SCREEN_ROTATED     0x0800

#define AS_SIZE (sizeof(aperture_sizes_table)/sizeof(aperture_sizes_table[0]))
#define ASID_MIN (aperture_sizes_table[0].id)
#define ASID_MAX (aperture_sizes_table[AS_SIZE-1].id)

/* Keyboard repeat and initial delays */
#define KBD_REPEAT_DELAY  140
#define KBD_INITIAL_DELAY 300

// Video recording current status constants, see movie_status variable 
#define VIDEO_RECORD_NEVER_STARTED 0  
#define VIDEO_RECORD_STOPPED 1  
#define VIDEO_RECORD_IN_PROGRESS 4

//Optical & digital zoom status constants, see zoom_status variable 
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

typedef struct {
    short id; // hacks id
    short prop_id; // Canons id
    char name[8];
    short shutter_dfs_value; // shutter speed to use dark frame substraction
} ISOTable;

typedef struct {
    short id; // hacks id
    short prop_id; // Canons id
    char name[8];
    long usec;
} ShutterSpeed;

typedef struct {
    short id; // hacks id
    short prop_id; // Canons id
    char name[8];
} ApertureSize;

typedef struct {
    short av96;
    short dav96;
    short av96_step;
    short tv96;
    short dtv96;
    short tv96_step;
    short sv96;
    short dsv96;
    short sv96_step;
    short iso;
    short diso;
    short iso_step;
    short subj_dist;
    short dsubj_dist;
    short subj_dist_step;
    short shoot_counter;
    short type;
} EXPO_BRACKETING_VALUES;

#define SET_NOW      1
#define SET_LATER    0

#define SHOW_ALWAYS    1
#define SHOW_HALF      2


typedef struct {
    short av96;
    short tv96;
    short sv96;
    short subj_dist;
    short nd_filter;
} PHOTO_PARAM;

typedef struct {
    int    subject_distance;
    int     near_limit;
    int     far_limit;
    int     hyperfocal_distance;
    int     depth_of_field;
    int     lens_to_focal_plane_width;
} DOF_TYPE;

typedef struct {
    short av96;
    short tv96;
    short sv96;
    short iso;
    short sv96_market;
    short iso_market;
    short bv96_measured;
    short bv96_seted;//Ev96_internal-Sv96
    short ev96_seted; //Tv96+Av96
    short ev96_measured; //Bv96+Sv96
    short dev96;// Ev96_external-Ev96_internal
    short dev96_canon;// Canon OverExposure
    int b; //average scene luminance 
} EXPO_TYPE;

typedef struct {
    float value; 
    char fraction[10];
} shutter_speed;


/******************************************************************/

int get_focal_length(int zp);
int get_effective_focal_length(int zp);
int get_zoom_x(int zp);

/******************************************************************/

long get_tick_count();

void remount_filesystem();
void mark_filesystem_bootable();

/******************************************************************/

long get_parameter_data(long id, void *buf, long bufsize);
long set_parameter_data(long id, void *buf, long bufsize);

long get_property_case(long id, void *buf, long bufsize);
long set_property_case(long id, void *buf, long bufsize);

long get_file_counter();
long get_exposure_counter();
long get_file_next_counter();
long get_target_dir_num();
long get_target_file_num();

/******************************************************************/

void kbd_key_press(long key);
void kbd_key_release(long key);
void kbd_key_release_all();
long kbd_is_key_pressed(long key);
long kbd_is_key_clicked(long key);
long kbd_get_pressed_key();
long kbd_get_clicked_key();
long kbd_get_autoclicked_key();
void kbd_reset_autoclicked_key();
long kbd_use_zoom_as_mf();
long kbd_use_up_down_left_right_as_fast_switch();
void kbd_set_alt_mode_key_mask(long key);
int get_usb_power(int edge);
/******************************************************************/

long vid_is_bitmap_shown();
void *vid_get_bitmap_fb();
long vid_get_bitmap_screen_width();
long vid_get_bitmap_screen_height();
long vid_get_bitmap_buffer_width();
long vid_get_bitmap_buffer_height();
void *vid_get_viewport_fb();
void *vid_get_viewport_fb_d();
void *vid_get_viewport_live_fb();
void vid_bitmap_refresh();
long vid_get_viewport_height();

/******************************************************************/

void *hook_raw_fptr();
void *hook_raw_ret_addr();
char *hook_raw_image_addr();
long hook_raw_size();
void hook_raw_install();
void hook_raw_save_complete();

/******************************************************************/

long lens_get_zoom_pos();
void lens_set_zoom_pos(long newpos);
long lens_get_zoom_point();
void lens_set_zoom_point(long newpt);
void lens_set_zoom_speed(long newspd); //for S-series
long lens_get_focus_pos();
long lens_get_focus_pos_from_lense();
void lens_set_focus_pos(long newpos);
long lens_get_target_distance();

/******************************************************************/

int shooting_in_progress();
int shooting_is_flash();
int shooting_is_flash_ready();
short shooting_get_flash_mode();


/******************************************************************/
int shooting_get_user_tv_id();
char* shooting_get_tv_str();
short shooting_get_tv96_from_shutter_speed(float t);
short shooting_get_tv96();
void shooting_set_tv96(short v, short is_now);
void shooting_set_tv96_direct(short v, short is_now);
void shooting_set_shutter_speed_ubasic(int t, short is_now);
short shooting_get_user_tv96();
void shooting_set_user_tv96(short v);
float shooting_get_shutter_speed_from_tv96(short tv);
float shooting_get_shutter_speed_override_value();
const char * shooting_get_tv_override_value();
const char * shooting_get_tv_bracket_value();
const char * shooting_get_bracket_type();
void shooting_set_user_tv_by_id(int v);
void shooting_set_user_tv_by_id_rel(int v);
const ShutterSpeed *shooting_get_tv_line();
/******************************************************************/
short shooting_get_aperture_sizes_table_size();
short shooting_get_aperture_sizes_table_prop_id(short i);
short shooting_get_max_aperture_sizes_table_prop_id();
short shooting_get_aperture_from_av96(short av96);
int shooting_get_user_av_id();
char* shooting_get_av_str();
void shooting_set_user_av_by_id(int v);
short shooting_get_av96();
void shooting_set_av96(short v,short is_now);
void shooting_set_av96_direct(short v, short is_now);
short shooting_get_user_av96();
void shooting_set_user_av96(short v);
void shooting_set_user_av_by_id_rel(int v);
short shooting_get_real_aperture();
short shooting_get_min_real_aperture();
short shooting_get_av96_override_value();
const char * shooting_get_av_bracket_value();
void shooting_set_nd_filter_state(short v, short is_now);
/******************************************************************/
int shooting_get_day_seconds();
int shooting_get_tick_count();
/******************************************************************/
void shooting_set_prop(int id, int v);
int shooting_get_prop(int id);
/******************************************************************/
extern int circle_of_confusion;
/******************************************************************/
extern const int zoom_points;
int shooting_get_zoom();
void shooting_set_zoom(int v);
void shooting_set_zoom_rel(int v);
void shooting_set_zoom_speed(int v);
/******************************************************************/
int shooting_get_focus();
void shooting_set_focus(int v, short is_now);
short shooting_get_focus_mode();
int shooting_get_hyperfocal_distance();
int shooting_get_hyperfocal_distance_f(int av, int fl);
int shooting_get_near_limit_of_acceptable_sharpness();
int shooting_get_far_limit_of_acceptable_sharpness();
int shooting_get_depth_of_field();
int shooting_get_subject_distance();
int shooting_get_subject_distance_override_value();
int shooting_get_subject_distance_bracket_value();
int shooting_get_subject_distance_override_koef();
int shooting_get_lens_to_focal_plane_width();
short shooting_get_drive_mode();
short shooting_can_focus();
short shooting_get_common_focus_mode();
/******************************************************************/
int shooting_get_iso_mode();
void shooting_set_iso_mode(int v);
short shooting_get_sv96();
short shooting_get_svm96();
short shooting_get_iso_market();
short shooting_get_iso_real();
void shooting_set_iso_real(short iso, short is_now);
//void shooting_set_iso_market(short isom);
//void shooting_set_iso_real_delta_from_base(short diso);
void shooting_set_sv96(short sv96, short is_now);
short shooting_get_iso_override_value();
short shooting_get_iso_bracket_value();
/******************************************************************/
short shooting_get_canon_overexposure_value();
short shooting_get_bv96();
int shooting_get_luminance();
//const char* shooting_get_flash_light_value();
/******************************************************************/
int shooting_get_canon_subject_distance();
int shooting_get_exif_subject_dist();
/******************************************************************/
void shooting_expo_param_override();
void shooting_bracketing(void);

void shooting_video_bitrate_change(int v);
extern int auto_started;
void shooting_tv_bracketing();
void shooting_av_bracketing();
void shooting_iso_bracketing();
/******************************************************************/
void clear_values();
/******************************************************************/


int mode_get();

/******************************************************************/

long stat_get_vbatt();
long get_vbatt_min();
long get_vbatt_max();
void ubasic_camera_set_raw(int mode);
void ubasic_camera_set_nr(int mode);
int ubasic_camera_get_nr();
int ubasic_camera_script_autostart();
void ubasic_camera_set_script_autostart();
void exit_alt();
void camera_shutdown_in_a_second(void); 

extern int shot_histogram_enabled;

void disable_shutdown();
void enable_shutdown();

void JogDial_CW(void);
void JogDial_CCW(void);
void change_video_tables(int a, int b);
int get_flash_params_count(void);

/******************************************************************/
void __attribute__((noreturn)) shutdown();
void ubasic_set_led(int led, int state, int bright);
void debug_led(int state);
/****************************************/
extern int canon_menu_active;  
extern char canon_shoot_menu_active;  
extern int recreview_hold;

extern int movie_status;
unsigned int GetFreeCardSpaceKb(void);
unsigned int GetTotalCardSpaceKb(void);

void swap_partitions(void);
int get_part_count(void);
void create_partitions(void);
extern char * camera_jpeg_count_str();

unsigned int GetJpgCount(void);
unsigned int GetRawCount(void);

void MakeAFScan(void); 
extern int movie_status; 
extern int zoom_status;

void wait_until_remote_button_is_released(void);
short shooting_get_ev_correction1();

#define started() debug_led(1)
#define finished() debug_led(0)

#endif
