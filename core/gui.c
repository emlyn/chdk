#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "camera.h"
#include "font.h"
#include "lang.h"
#include "gui.h"
#include "gui_lang.h"
#include "gui_draw.h"
#include "gui_menu.h"
#include "gui_palette.h"
#include "gui_mbox.h"
#include "gui_mpopup.h"
#include "gui_reversi.h"
#include "gui_sokoban.h"
#include "gui_4wins.h"
#include "gui_mastermind.h"
#include "console.h"
#ifdef OPT_DEBUGGING
#include "gui_debug.h"
#endif
#include "gui_fselect.h"
#include "gui_batt.h"
#include "gui_space.h"
#include "gui_osd.h"
#ifdef OPT_TEXTREADER
	#include "gui_read.h"
#endif
#ifdef OPT_CALENDAR
	#include "gui_calendar.h"
#endif
#ifdef OPT_DEBUGGING
#include "gui_bench.h"
#endif
#include "gui_grid.h"
#include "histogram.h"
#include "motion_detector.h"
#include "raw.h"
#ifdef OPT_CURVES
	#include "curves.h"
#endif
#ifdef OPT_EDGEOVERLAY
	#include "edgeoverlay.h"
#endif
#ifdef OPT_SCRIPTING
    #include "script.h"
    int script_params_has_changed=0;
#endif
//-------------------------------------------------------------------

#define OPTIONS_AUTOSAVE
#define SPLASH_TIME               20

//shortcuts
//------------------------------------------------------------------
// #define KEY_NONE (KEY_DUMMY+1)

#if !CAM_HAS_ERASE_BUTTON
//Alt mode
 #define SHORTCUT_TOGGLE_RAW          KEY_DISPLAY
 #define SHORTCUT_MF_TOGGLE           KEY_UP
//Half press shoot button
 #define SHORTCUT_TOGGLE_HISTO        KEY_DOWN
 #define SHORTCUT_TOGGLE_ZEBRA        KEY_MENU
 #define SHORTCUT_TOGGLE_OSD          KEY_RIGHT
 #define SHORTCUT_DISABLE_OVERRIDES   KEY_LEFT
//Alt mode & Manual mode
 #define SHORTCUT_SET_INFINITY        KEY_DISPLAY
 #define SHORTCUT_SET_HYPERFOCAL      KEY_DOWN
 // For models without ZOOM_LEVER  (#if !CAM_HAS_ZOOM_LEVER)
 // SHORTCUT_SET_INFINITY is not used
 // KEY_DISPLAY is used for gui_subj_dist_override_koef_enum;
 // KEY_LEFT/KEY_RIGHT is used for gui_subj_dist_override_value_enum (because of no separate ZOOM_IN/OUT)

#elif defined(CAMERA_g7) || defined(CAMERA_sx10) || defined(CAMERA_sx1) || defined(CAMERA_sx20) || defined(CAMERA_sx30)
//Alt mode
 #define SHORTCUT_TOGGLE_RAW          KEY_ERASE
//Half press shoot button
 #define SHORTCUT_TOGGLE_HISTO        KEY_DOWN
 #define SHORTCUT_TOGGLE_ZEBRA        KEY_LEFT
 #define SHORTCUT_TOGGLE_OSD          KEY_RIGHT
 #define SHORTCUT_DISABLE_OVERRIDES   KEY_UP
//Alt mode & Manual mode
 #define SHORTCUT_SET_INFINITY        KEY_UP
 #define SHORTCUT_SET_HYPERFOCAL      KEY_DOWN

#elif defined(CAMERA_sx100is) ||defined(CAMERA_sx110is)
//Alt mode
 #define SHORTCUT_TOGGLE_RAW          KEY_ERASE
//Half press shoot button
 #define SHORTCUT_TOGGLE_HISTO        KEY_UP
 #define SHORTCUT_TOGGLE_ZEBRA        KEY_DOWN
 #define SHORTCUT_TOGGLE_OSD          KEY_RIGHT
 #define SHORTCUT_DISABLE_OVERRIDES   KEY_LEFT
//Alt mode & Manual mode
 #define SHORTCUT_SET_INFINITY        KEY_UP
 #define SHORTCUT_SET_HYPERFOCAL      KEY_DOWN

 #else

//Alt mode
 #define SHORTCUT_TOGGLE_RAW          KEY_ERASE
//Half press shoot button
 #define SHORTCUT_TOGGLE_HISTO        KEY_UP
 #define SHORTCUT_TOGGLE_ZEBRA        KEY_LEFT
 #define SHORTCUT_TOGGLE_OSD          KEY_RIGHT
 #define SHORTCUT_DISABLE_OVERRIDES   KEY_DOWN
//Alt mode & Manual mode
 #define SHORTCUT_SET_INFINITY        KEY_UP
 #define SHORTCUT_SET_HYPERFOCAL      KEY_DOWN
 #ifndef CAM_HAS_MANUAL_FOCUS
 #define SHORTCUT_MF_TOGGLE           KEY_DISPLAY
 #endif
#endif


// forward declarations
//-------------------------------------------------------------------
extern void dump_memory();
// both from platform/generic/shooting.c
extern const char* tv_override[];
extern const int tv_override_amount;
extern const int tv_override_zero_shift;


static void gui_draw_osd();

static void gui_draw_splash(char* logo, int logo_size);

void user_menu_save();
void user_menu_restore();
// Menu procs
//-------------------------------------------------------------------
static void gui_show_build_info(int arg);
static void gui_show_memory_info(int arg);
static void gui_draw_palette(int arg);
static void gui_draw_reversi(int arg);
static void gui_draw_sokoban(int arg);
static void gui_draw_4wins(int arg);
static void gui_draw_mastermind(int arg);
#ifdef OPT_DEBUGGING
	static void gui_draw_debug(int arg);
	static void gui_draw_bench(int arg);
#endif
static void gui_draw_fselect(int arg);
static void gui_draw_osd_le(int arg);
#ifdef OPT_TEXTREADER
static void gui_draw_read(int arg);
static void gui_draw_read_last(int arg);
#endif
static void gui_draw_load_menu_rbf(int arg);
static void gui_draw_load_symbol_rbf(int arg);		//AKA
#ifdef OPT_TEXTREADER
	static void gui_draw_load_rbf(int arg);
#endif
#ifdef OPT_CALENDAR
static void gui_draw_calendar(int arg);
#endif
static void gui_draw_load_lang(int arg);
static void gui_menuproc_mkbootdisk(int arg);
#ifdef OPT_DEBUGGING
void gui_compare_props(int arg);
#endif
#ifndef OPTIONS_AUTOSAVE
static void gui_menuproc_save(int arg);
#endif
static void gui_menuproc_reset(int arg);
static void gui_grid_lines_load(int arg);
static void gui_raw_develop(int arg);
#ifdef OPT_DEBUGGING
static void gui_menuproc_break_card(int arg);
#endif
static void gui_menuproc_swap_partitions(int arg);
static void gui_menuproc_reset_files(int arg);
#ifdef OPT_CURVES
	static void gui_load_curve_selected(const char *fn);
	static void gui_load_curve(int arg);
#endif
static const char* gui_histo_show_enum(int change, int arg);
static const char* gui_histo_mode_enum(int change, int arg);
static const char* gui_temp_mode_enum(int change, int arg);
static const char* gui_histo_layout_enum(int change, int arg);
static const char* gui_zebra_mode_enum(int change, int arg);
static const char* gui_zebra_draw_osd_enum(int change, int arg);
static const char* gui_font_enum(int change, int arg);
static const char* gui_raw_prefix_enum(int change, int arg);
static const char* gui_raw_ext_enum(int change, int arg);
static const char* gui_sub_batch_prefix_enum(int change, int arg);
static const char* gui_sub_batch_ext_enum(int change, int arg);

static const char* gui_raw_nr_enum(int change, int arg);
static const char* gui_autoiso_shutter_enum(int change, int arg);
#ifdef OPT_TEXTREADER
	static const char* gui_reader_codepage_enum(int change, int arg);
#endif
static const char* gui_zoom_value_enum(int change, int arg);
static const char* gui_show_values_enum(int change, int arg);
static const char* gui_dof_show_value_enum(int change, int arg);
#if CAM_ADJUSTABLE_ALT_BUTTON
static const char* gui_alt_mode_button_enum(int change, int arg);
#endif
static const char* gui_alt_power_enum(int change, int arg);
static const char* gui_video_mode_enum(int change, int arg);
static const char* gui_fast_ev_step(int change, int arg);
#if CAM_QUALITY_OVERRIDE
static const char* gui_fast_image_quality(int change, int arg);
#endif
static const char* gui_video_bitrate_enum(int change, int arg);
static const char* gui_tv_bracket_values_enum(int change, int arg);
static const char* gui_av_bracket_values_enum(int change, int arg);
static const char* gui_iso_bracket_koef_enum(int change, int arg);
static const char* gui_subj_dist_bracket_koef_enum(int change, int arg);
static const char* gui_bracket_type_enum(int change, int arg);
static const char* gui_av_override_enum(int change, int arg);
#if ZOOM_OVERRIDE
static const char* gui_zoom_override_enum(int change, int arg);
#endif
static const char* gui_iso_override_koef_enum(int change, int arg);
static const char* gui_tv_override_koef_enum(int change, int arg);
static const char* gui_tv_override_value_enum(int change, int arg);
static const char* gui_tv_enum_type_enum(int change, int arg);
static const char* gui_subj_dist_override_value_enum(int change, int arg);
static const char* gui_subj_dist_override_koef_enum(int change, int arg);
/*
static const char* gui_tv_exposure_order_enum(int change, int arg);
static const char* gui_av_exposure_order_enum(int change, int arg);
static const char* gui_iso_exposure_order_enum(int change, int arg);
*/
static const char* gui_nd_filter_state_enum(int change, int arg);
//static const char* gui_tv_enum(int change, int arg);
const char* gui_user_menu_show_enum(int change, int arg);
static const char* gui_hide_osd_enum(int change, int arg);
static const char* gui_show_clock_enum(int change, int arg);
static const char* gui_clock_format_enum(int change, int arg);
static const char* gui_clock_indicator_enum(int change, int arg);
static const char* gui_clock_halfpress_enum(int change, int arg);
static const char* gui_space_bar_enum(int change, int arg);
static const char* gui_space_bar_size_enum(int change, int arg);
static const char* gui_space_bar_width_enum(int change, int arg);
static const char* gui_space_warn_type_enum(int change, int arg);
static const char* gui_bad_pixel_enum(int change, int arg);
static const char* gui_video_af_key_enum(int change, int arg);
static const char* gui_show_movie_time(int change, int arg);
static const char* gui_override_disable_enum(int change, int arg);
#ifdef OPT_CURVES
	static const char* gui_conf_curve_enum(int change, int arg);
#endif
#ifdef OPT_DEBUGGING
	static const char* gui_debug_shortcut_enum(int change, int arg);
	static const char* gui_debug_display_enum(int change, int arg);
	static void gui_debug_shortcut(void);
#endif

#ifdef OPT_EDGEOVERLAY
static void gui_menuproc_edge_save(int arg);
static void gui_menuproc_edge_load(int arg);
static const char* gui_edge_pano_enum(int change, int arg);
#endif

#ifdef OPT_SCRIPTING
static void gui_load_script(int arg);
static void gui_load_script_default(int arg);
static const char* gui_script_autostart_enum(int change, int arg);
static const char* gui_script_param_set_enum(int change, int arg);
#endif

void rinit();


// Menu callbacks
//-------------------------------------------------------------------
static void cb_step_25();
static void cb_perc();
static void cb_volts();
static void cb_space_perc();
static void cb_space_mb();
static void cb_battery_menu_change(unsigned int item);
static void cb_zebra_restore_screen();
static void cb_zebra_restore_osd();
#if DNG_SUPPORT
static void cb_change_dng();
void gui_menuproc_badpixel_create(int arg);
#endif
#if defined (DNG_EXT_FROM)
static void cb_change_dng_usb_ext();
#endif

// for memory info, duplicated from lowlevel
extern const char _start,_end;

#ifdef OPT_DEBUGGING
static int debug_tasklist_start;
static int debug_display_direction=1;
#endif
// Menu definition
//-------------------------------------------------------------------
static CMenuItem remote_submenu_items[] = {
    {0x71,LANG_MENU_REMOTE_ENABLE,            MENUITEM_BOOL,                    &conf.remote_enable},
    {0x0,LANG_MENU_SYNCHABLE_REMOTE,          MENUITEM_SEPARATOR },
	{0x71,LANG_MENU_SYNCHABLE_REMOTE_ENABLE,  MENUITEM_BOOL,                    &conf.ricoh_ca1_mode            },
    {0x5c,LANG_MENU_SYNCH_ENABLE,             MENUITEM_BOOL,                    &conf.synch_enable              },
    {0x5c,LANG_MENU_SYNCH_DELAY_ENABLE,       MENUITEM_BOOL,                    &conf.synch_delay_enable        },
    {0x5c,LANG_MENU_SYNCH_DELAY_VALUE,        MENUITEM_INT|MENUITEM_F_UNSIGNED, &conf.synch_delay_value         },
    {0x5c,LANG_MENU_SYNCH_DELAY_COARSE_VALUE, MENUITEM_INT|MENUITEM_F_UNSIGNED, &conf.synch_delay_coarse_value  },
    {0x5c,LANG_MENU_REMOTE_ZOOM_ENABLE,       MENUITEM_BOOL,                    &conf.remote_zoom_enable        },
    {0x5f,LANG_MENU_REMOTE_ZOOM_TIMEOUT,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.zoom_timeout, MENU_MINMAX(2,10)},
    {0x51,LANG_MENU_BACK,                     MENUITEM_UP },
    {0}
};
static CMenu remote_submenu = {0x86,LANG_MENU_REMOTE_PARAM_TITLE, NULL, remote_submenu_items };


#ifdef OPT_SCRIPTING
static CMenuItem script_submenu_items_top[] = {
    {0x35,LANG_MENU_SCRIPT_LOAD,             MENUITEM_PROC,                      (int*)gui_load_script },
    {0x5f,LANG_MENU_SCRIPT_DELAY,            MENUITEM_INT|MENUITEM_F_UNSIGNED,   &conf.script_shoot_delay },
	// remote autostart
	{0x5f,LANG_MENU_SCRIPT_AUTOSTART,		MENUITEM_ENUM,						(int*)gui_script_autostart_enum },

#if CAM_REMOTE
    {0x86,LANG_MENU_REMOTE_PARAM,            MENUITEM_SUBMENU,   (int*)&remote_submenu },
	//{0x71,LANG_MENU_SCRIPT_REMOTE_ENABLE,	MENUITEM_BOOL,						&conf.remote_enable},
#endif
    {0x5d,LANG_MENU_SCRIPT_DEFAULT_VAL,     MENUITEM_PROC,                      (int*)gui_load_script_default },
    {0x5e,LANG_MENU_SCRIPT_PARAM_SET,     MENUITEM_ENUM,                         (int*)gui_script_param_set_enum },
    {0x5c,LANG_MENU_SCRIPT_PARAM_SAVE,             MENUITEM_BOOL,                    &conf.script_param_save              },
    {0x0,(int)script_title,                 MENUITEM_SEPARATOR },
//    {0x0,LANG_MENU_SCRIPT_CURRENT,          MENUITEM_SEPARATOR },
//    {0x0,(int)script_title,                 MENUITEM_TEXT },
//    {0x0,LANG_MENU_SCRIPT_PARAMS,           MENUITEM_SEPARATOR }
};

static CMenuItem script_submenu_items_bottom[] = {
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};

static CMenuItem script_submenu_items[sizeof(script_submenu_items_top)/sizeof(script_submenu_items_top[0])+SCRIPT_NUM_PARAMS+
                               sizeof(script_submenu_items_bottom)/sizeof(script_submenu_items_bottom[0])];
static CMenu script_submenu = {0x27,LANG_MENU_SCRIPT_TITLE, NULL, script_submenu_items };
#endif

static CMenuItem games_submenu_items[] = {
#ifdef OPT_GAME_REVERSI
    {0x38,LANG_MENU_GAMES_REVERSI,           MENUITEM_PROC,  (int*)gui_draw_reversi },
#endif
#ifdef OPT_GAME_SOKOBAN
    {0x38,LANG_MENU_GAMES_SOKOBAN,           MENUITEM_PROC,  (int*)gui_draw_sokoban },
#endif
#ifdef OPT_GAME_CONNECT4
    {0x38,LANG_MENU_GAMES_CONNECT4,             MENUITEM_PROC,  (int*)gui_draw_4wins },
#endif
#ifdef OPT_GAME_MASTERMIND
    {0x38,LANG_MENU_GAMES_MASTERMIND,           MENUITEM_PROC,  (int*)gui_draw_mastermind },
#endif
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu games_submenu = {0x38,LANG_MENU_GAMES_TITLE, NULL, games_submenu_items };

static CMenuItem autoiso_submenu_items[] = {
    {0x5c,LANG_MENU_AUTOISO_ENABLED,          MENUITEM_BOOL,	&conf.autoiso_enable},
    {0x5f,LANG_MENU_AUTOISO_MIN_SHUTTER,   MENUITEM_ENUM,    (int*)gui_autoiso_shutter_enum },
    {0x5f,LANG_MENU_AUTOISO_USER_FACTOR,   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_user_factor, MENU_MINMAX(1, 8)  },
#if CAM_HAS_IS
    {0x5f,LANG_MENU_AUTOISO_IS_FACTOR,       MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_is_factor, MENU_MINMAX(1, 8)  },
#endif
    {0x5f,LANG_MENU_AUTOISO_MAX_ISO_HI,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_max_iso_hi, MENU_MINMAX(20, 160)  },
    {0x5f,LANG_MENU_AUTOISO_MAX_ISO_AUTO, MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_max_iso_auto, MENU_MINMAX(10, 80)  },
    {0x5f,LANG_MENU_AUTOISO_MIN_ISO,           MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.autoiso_min_iso, MENU_MINMAX(1, 20)  },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu autoiso_submenu = {0x2d,LANG_MENU_AUTOISO_TITLE, NULL, autoiso_submenu_items };


#ifdef OPT_TEXTREADER
static CMenuItem reader_submenu_items[] = {
    {0x35,LANG_MENU_READ_OPEN_NEW,           MENUITEM_PROC,    (int*)gui_draw_read },
    {0x35,LANG_MENU_READ_OPEN_LAST,          MENUITEM_PROC,    (int*)gui_draw_read_last },
    {0x35,LANG_MENU_READ_SELECT_FONT,        MENUITEM_PROC,    (int*)gui_draw_load_rbf },
    {0x5f,LANG_MENU_READ_CODEPAGE,           MENUITEM_ENUM,    (int*)gui_reader_codepage_enum },
    {0x5c,LANG_MENU_READ_WORD_WRAP,          MENUITEM_BOOL,    &conf.reader_wrap_by_words },
    {0x5c,LANG_MENU_READ_AUTOSCROLL,         MENUITEM_BOOL,    &conf.reader_autoscroll },
    {0x5f,LANG_MENU_READ_AUTOSCROLL_DELAY,   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.reader_autoscroll_delay, MENU_MINMAX(0, 60) },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu reader_submenu = {0x37,LANG_MENU_READ_TITLE, NULL, reader_submenu_items };
#endif

#ifdef OPT_DEBUGGING
static CMenuItem debug_submenu_items[] = {
    {0x5c,LANG_MENU_DEBUG_DISPLAY,           MENUITEM_ENUM,          (int*)gui_debug_display_enum },
    {0x2a,LANG_MENU_DEBUG_PROPCASE_PAGE,     MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &conf.debug_propcase_page, MENU_MINMAX(0, 128) },
    {0x2a,LANG_MENU_DEBUG_TASKLIST_START,    MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &debug_tasklist_start, MENU_MINMAX(0, 63) },
    {0x5c,LANG_MENU_DEBUG_SHOW_MISC_VALS,    MENUITEM_BOOL,          &conf.debug_misc_vals_show },
    {0x2a,LANG_MENU_DEBUG_MEMORY_BROWSER,    MENUITEM_PROC,          (int*)gui_draw_debug },
    {0x2a,LANG_MENU_DEBUG_BENCHMARK,         MENUITEM_PROC,          (int*)gui_draw_bench },
    {0x5c,LANG_MENU_DEBUG_SHORTCUT_ACTION,   MENUITEM_ENUM,          (int*)gui_debug_shortcut_enum },
    {0x5c,LANG_MENU_RAW_TIMER,               MENUITEM_BOOL,          &conf.raw_timer },
#ifdef OPT_LUA
    {0x5c,LANG_MENU_LUA_RESTART,             MENUITEM_BOOL,          &conf.debug_lua_restart_on_error },
#endif
#if CAM_MULTIPART
    {0x33,LANG_MENU_DEBUG_CREATE_MULTIPART , MENUITEM_PROC, 	    	(int*)gui_menuproc_break_card },
#endif
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu debug_submenu = {0x2a,LANG_MENU_DEBUG_TITLE, NULL, debug_submenu_items };
#endif


static CMenuItem misc_submenu_items[] = {
    {0x35,LANG_MENU_MISC_FILE_BROWSER,       MENUITEM_PROC,    (int*)gui_draw_fselect },
#ifdef OPT_CALENDAR
    {0x36,LANG_MENU_MISC_CALENDAR,           MENUITEM_PROC,    (int*)gui_draw_calendar },
#endif
#ifdef OPT_TEXTREADER
    {0x37,LANG_MENU_MISC_TEXT_READER,        MENUITEM_SUBMENU, (int*)&reader_submenu },
#endif
#if defined (OPT_GAME_REVERSI) || (OPT_GAME_SOKOBAN || (OPT_GAME_CONNECT4) || OPT_GAME_MASTERMIND)
    {0x38,LANG_MENU_MISC_GAMES,              MENUITEM_SUBMENU, (int*)&games_submenu },
#endif
#if CAM_SWIVEL_SCREEN
    {0x28,LANG_MENU_MISC_FLASHLIGHT,         MENUITEM_BOOL,    &conf.flashlight },
#endif
    {0x5c,LANG_MENU_MISC_SHOW_SPLASH,        MENUITEM_BOOL,    &conf.splash_show },
		{0x5c,LANG_MENU_MISC_START_SOUND,        MENUITEM_BOOL,    &conf.start_sound },
#if CAM_USE_ZOOM_FOR_MF
    {0x59,LANG_MENU_MISC_ZOOM_FOR_MF,        MENUITEM_BOOL,    &conf.use_zoom_mf },
#endif
#if CAM_ADJUSTABLE_ALT_BUTTON
    {0x22,LANG_MENU_MISC_ALT_BUTTON,         MENUITEM_ENUM,    (int*)gui_alt_mode_button_enum },
#endif
    {0x5d,LANG_MENU_MISC_DISABLE_LCD_OFF,    MENUITEM_ENUM,    (int*)gui_alt_power_enum },
    {0x65,LANG_MENU_MISC_PALETTE,            MENUITEM_PROC,    (int*)gui_draw_palette },
    {0x80,LANG_MENU_MISC_BUILD_INFO,         MENUITEM_PROC,    (int*)gui_show_build_info },
    {0x80,LANG_MENU_MISC_MEMORY_INFO,        MENUITEM_PROC,    (int*)gui_show_memory_info },
    {0x33,LANG_MENU_DEBUG_MAKE_BOOTABLE,     MENUITEM_PROC,    (int*)gui_menuproc_mkbootdisk },
#if CAM_MULTIPART
    {0x33,LANG_MENU_DEBUG_SWAP_PART,         MENUITEM_PROC, 	    	(int*)gui_menuproc_swap_partitions },
#endif
    {0x2b,LANG_MENU_MAIN_RESET_OPTIONS,      MENUITEM_PROC,      (int*)gui_menuproc_reset },
#ifdef OPT_DEBUGGING
    {0x2a,LANG_MENU_MAIN_DEBUG,              MENUITEM_SUBMENU,   (int*)&debug_submenu },
#endif
    {0x86,LANG_MENU_REMOTE_PARAM,            MENUITEM_SUBMENU,   (int*)&remote_submenu },
#if defined (DNG_EXT_FROM)
    {0x71,LANG_MENU_DNG_VIA_USB,        MENUITEM_BOOL | MENUITEM_ARG_CALLBACK, &conf.dng_usb_ext , (int)cb_change_dng_usb_ext},
#endif
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0},
};
static CMenu misc_submenu = {0x29,LANG_MENU_MISC_TITLE, NULL, misc_submenu_items };

static int voltage_step;
static CMenuItem battery_submenu_items[] = {
    {0x66,LANG_MENU_BATT_VOLT_MAX,           MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf.batt_volts_max,   (int)&voltage_step },
    {0x67,LANG_MENU_BATT_VOLT_MIN,           MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf.batt_volts_min,   (int)&voltage_step },
    {0x68,LANG_MENU_BATT_STEP_25,            MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_step_25,     (int)cb_step_25 },
    {0x0,(int)"",                           MENUITEM_SEPARATOR },
    {0x73,LANG_MENU_BATT_SHOW_PERCENT,       MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_perc_show,   (int)cb_perc },
    {0x73,LANG_MENU_BATT_SHOW_VOLTS,         MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_volts_show,  (int)cb_volts },
    {0x32,LANG_MENU_BATT_SHOW_ICON,          MENUITEM_BOOL,                          &conf.batt_icon_show },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu battery_submenu = {0x32,LANG_MENU_BATT_TITLE, cb_battery_menu_change, battery_submenu_items };

static CMenuItem space_submenu_items[] = {
    {0x5c,LANG_MENU_SPACE_SHOW_ICON,         MENUITEM_BOOL,                          &conf.space_icon_show },
    {0x69,LANG_MENU_SPACE_SHOW_BAR,      MENUITEM_ENUM,                       (int*)gui_space_bar_enum },
    {0x6a,LANG_MENU_SPACE_BAR_SIZE,      MENUITEM_ENUM,                       (int*)gui_space_bar_size_enum },
    {0x6b,LANG_MENU_SPACE_BAR_WIDTH,      MENUITEM_ENUM,                       (int*)gui_space_bar_width_enum },
    {0x5c,LANG_MENU_SPACE_SHOW_PERCENT,      MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.space_perc_show,   (int)cb_space_perc },
    {0x5c,LANG_MENU_SPACE_SHOW_MB,           MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.space_mb_show,  (int)cb_space_mb },
    {0x5f,LANG_MENU_SPACE_WARN_TYPE,      MENUITEM_ENUM,                       (int*)gui_space_warn_type_enum },
    {0x58,LANG_MENU_SPACE_WARN_PERCENT,     MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &conf.space_perc_warn, MENU_MINMAX(1, 99) },
    {0x58,LANG_MENU_SPACE_WARN_MB,     MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &conf.space_mb_warn, MENU_MINMAX(1, 4000) },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu space_submenu = {0x33,LANG_MENU_OSD_SPACE_PARAMS_TITLE, NULL, space_submenu_items};

static CMenuItem dof_submenu_items[] = {
	  {0x5f,LANG_MENU_OSD_SHOW_DOF_CALC,            MENUITEM_ENUM,      (int*)gui_dof_show_value_enum },
	  {0x5c,LANG_MENU_DOF_SUBJ_DIST_AS_NEAR_LIMIT,  MENUITEM_BOOL,      &conf.dof_subj_dist_as_near_limit},
	  {0x5c,LANG_MENU_DOF_USE_EXIF_SUBJ_DIST,       MENUITEM_BOOL,      &conf.dof_use_exif_subj_dist},
	  {0x5c,LANG_MENU_DOF_SUBJ_DIST_IN_MISC,        MENUITEM_BOOL,      &conf.dof_subj_dist_in_misc},
	  {0x5c,LANG_MENU_DOF_NEAR_LIMIT_IN_MISC,       MENUITEM_BOOL,      &conf.dof_near_limit_in_misc},
      {0x5c,LANG_MENU_DOF_FAR_LIMIT_IN_MISC,        MENUITEM_BOOL,			 &conf.dof_far_limit_in_misc},
      {0x5c,LANG_MENU_DOF_HYPERFOCAL_IN_MISC,       MENUITEM_BOOL,      &conf.dof_hyperfocal_in_misc},
      {0x5c,LANG_MENU_DOF_DEPTH_LIMIT_IN_MISC,      MENUITEM_BOOL,      &conf.dof_depth_in_misc},
#if !CAM_DRYOS
      {0x5c,LANG_MENU_DOF_DIST_FROM_LENS,           MENUITEM_BOOL,      &conf.dof_dist_from_lens},
#endif
	  {0x51,LANG_MENU_BACK,                    	   MENUITEM_UP },
    {0}
};
static CMenu dof_submenu = {0x31,LANG_MENU_DOF_TITLE, /*cb_dof_menu_change*/ NULL, dof_submenu_items };

static CMenuItem values_submenu_items[] = {
	  {0x5f,LANG_MENU_OSD_SHOW_MISC_VALUES,           MENUITEM_ENUM,      (int*)gui_show_values_enum },
	 // {0x43,LANG_MENU_VALUES_SHOW_IN_REVIEW,   MENUITEM_BOOL,      &conf.values_show_in_review},
	  {0x5c,LANG_MENU_SHOW_VALUES_IN_VIDEO,           MENUITEM_BOOL,      &conf.show_values_in_video},
	  {0x5c,LANG_MENU_VALUES_SHOW_ZOOM,               MENUITEM_BOOL,      &conf.values_show_zoom},
	  {0x5f,LANG_MENU_OSD_ZOOM_VALUE,                 MENUITEM_ENUM,      (int*)gui_zoom_value_enum },
	  {0x60,LANG_MENU_OSD_ZOOM_SCALE,                 MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zoom_scale,   MENU_MINMAX(0, 1000)},
      {0x62,LANG_MENU_VALUES_SHOW_REAL_APERTURE,      MENUITEM_BOOL,      &conf.values_show_real_aperture},
      {0x74,LANG_MENU_VALUES_SHOW_REAL_ISO,           MENUITEM_BOOL,      &conf.values_show_real_iso},
      {0x74,LANG_MENU_VALUES_SHOW_MARKET_ISO,         MENUITEM_BOOL,      &conf.values_show_market_iso},
  	  {0x2d,LANG_MENU_SHOW_ISO_ONLY_IN_AUTOISO_MODE,  MENUITEM_BOOL,	     &conf.values_show_iso_only_in_autoiso_mode},
      {0x5c,LANG_MENU_VALUES_SHOW_EV_SETED, 			 MENUITEM_BOOL,	     &conf.values_show_ev_seted},
      {0x5c,LANG_MENU_VALUES_SHOW_EV_MEASURED,        MENUITEM_BOOL,		 &conf.values_show_ev_measured},
      {0x5c,LANG_MENU_VALUES_SHOW_BV_SETED,			 MENUITEM_BOOL,	     &conf.values_show_bv_seted},
      {0x5c,LANG_MENU_VALUES_SHOW_BV_MEASURED,   	 MENUITEM_BOOL,	     &conf.values_show_bv_measured},
      {0x5c,LANG_MENU_VALUES_SHOW_OVEREXPOSURE,	     MENUITEM_BOOL,      &conf.values_show_overexposure},
      {0x5c,LANG_MENU_SHOW_CANON_OVEREXPOSURE,	     MENUITEM_BOOL,      &conf.values_show_canon_overexposure},
      {0x5c,LANG_MENU_VALUES_SHOW_LUMINANCE,  	     MENUITEM_BOOL,      &conf.values_show_luminance},
	  {0x51,LANG_MENU_BACK,                           MENUITEM_UP },
    {0}
};
static CMenu values_submenu = {0x28,LANG_MENU_OSD_VALUES_TITLE, /*cb_values_menu_change*/ NULL, values_submenu_items };

static CMenuItem clock_submenu_items[] = {
    {0x5f,LANG_MENU_OSD_SHOW_CLOCK,          MENUITEM_ENUM,      (int*)gui_show_clock_enum },
    {0x6d,LANG_MENU_OSD_CLOCK_FORMAT,          MENUITEM_ENUM,      (int*)gui_clock_format_enum },
    {0x6c,LANG_MENU_OSD_CLOCK_INDICATOR,          MENUITEM_ENUM,      (int*)gui_clock_indicator_enum },
    {0x6e,LANG_MENU_OSD_CLOCK_HALFPRESS,          MENUITEM_ENUM,      (int*)gui_clock_halfpress_enum },
    {0x51,LANG_MENU_BACK,                           MENUITEM_UP },
    {0}
};
static CMenu clock_submenu = {0x34,LANG_MENU_OSD_CLOCK_PARAMS_TITLE, NULL, clock_submenu_items };


static CMenuItem video_submenu_items[] = {
#if CAM_CHDK_HAS_EXT_VIDEO_MENU
	  {0x23,LANG_MENU_VIDEO_MODE,              MENUITEM_ENUM,    (int*)gui_video_mode_enum},
#if !CAM_VIDEO_QUALITY_ONLY
      {0x5e,LANG_MENU_VIDEO_BITRATE,           MENUITEM_ENUM,    (int*)gui_video_bitrate_enum},
#endif
      {0x60,LANG_MENU_VIDEO_QUALITY,           MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.video_quality, MENU_MINMAX(1, 99)},
      {0x5c,LANG_MENU_CLEAR_VIDEO_VALUES,    MENUITEM_BOOL,    (int*)&conf.clear_video},
#endif
#if CAM_VIDEO_CONTROL
      {0x5c,LANG_MENU_FAST_SWITCH_VIDEO,   MENUITEM_BOOL,  &conf.fast_movie_control},
#endif
#if CAM_CHDK_HAS_EXT_VIDEO_MENU
      {0x5c,LANG_MENU_FAST_SWITCH_QUALITY_VIDEO,   MENUITEM_BOOL,  &conf.fast_movie_quality_control},
#endif
#if CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
      {0x5c,LANG_MENU_OPTICAL_ZOOM_IN_VIDEO,   MENUITEM_BOOL,  &conf.unlock_optical_zoom_for_video},
#endif
#if CAM_CAN_MUTE_MICROPHONE
      {0x83,LANG_MENU_MUTE_ON_ZOOM,   MENUITEM_BOOL,  &conf.mute_on_zoom},
#endif
#if CAM_AF_SCAN_DURING_VIDEO_RECORD
      {0x82,LANG_MENU_VIDEO_AF_KEY,   MENUITEM_ENUM,    (int*)gui_video_af_key_enum},
#endif
		{0x5c,LANG_MENU_OSD_SHOW_VIDEO_TIME,         MENUITEM_ENUM,      (int*)gui_show_movie_time },
    {0x60,LANG_MENU_OSD_SHOW_VIDEO_REFRESH,             MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.show_movie_refresh,   MENU_MINMAX(1, 20)},
      {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
      {0}
};
static CMenu video_submenu = {0x23,LANG_MENU_VIDEO_PARAM_TITLE, NULL, video_submenu_items };

static CMenuItem bracketing_in_continuous_submenu_items[] = {
	  {0x63,LANG_MENU_TV_BRACKET_VALUE,             MENUITEM_ENUM,    (int*)gui_tv_bracket_values_enum },
#if CAM_HAS_IRIS_DIAPHRAGM
	  {0x62,LANG_MENU_AV_BRACKET_VALUE,             MENUITEM_ENUM,    (int*)gui_av_bracket_values_enum },
#endif
#if CAM_CAN_SD_OVERRIDE
	  {0x5e,LANG_MENU_SUBJ_DIST_BRACKET_VALUE,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.subj_dist_bracket_value, MENU_MINMAX(0, 100)},
	  {0x5f,LANG_MENU_SUBJ_DIST_BRACKET_KOEF,       MENUITEM_ENUM,    (int*)gui_subj_dist_bracket_koef_enum},
#endif
	  {0x74,LANG_MENU_ISO_BRACKET_VALUE,            MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.iso_bracket_value, MENU_MINMAX(0, 100)},
	  {0x5f,LANG_MENU_ISO_BRACKET_KOEF,             MENUITEM_ENUM,    (int*)gui_iso_bracket_koef_enum},
	  {0x60,LANG_MENU_BRACKET_TYPE,                 MENUITEM_ENUM,    (int*)gui_bracket_type_enum },
	  {0x5b,LANG_MENU_CLEAR_BRACKET_VALUES,        MENUITEM_BOOL,        (int*)&conf.clear_bracket},
     {0x5c,LANG_MENU_BRACKETING_ADD_RAW_SUFFIX,                MENUITEM_BOOL,      &conf.bracketing_add_raw_suffix },
      {0x51,LANG_MENU_BACK,                         MENUITEM_UP },
      {0}
};
static CMenu bracketing_in_continuous_submenu = {0x2c,LANG_MENU_BRACKET_IN_CONTINUOUS_TITLE, NULL, bracketing_in_continuous_submenu_items };


/*
static CMenuItem exposure_submenu_items[] = {
	  {0x59,LANG_MENU_RECALC_EXPOSURE,         MENUITEM_BOOL,    &conf.recalc_exposure},
	  {0x63,LANG_MENU_TV_EXPOSURE_ORDER,       MENUITEM_ENUM,    (int*)gui_tv_exposure_order_enum},
	  {0x62,LANG_MENU_AV_EXPOSURE_ORDER,       MENUITEM_ENUM,    (int*)gui_av_exposure_order_enum},
	  {0x74,LANG_MENU_ISO_EXPOSURE_ORDER,	   MENUITEM_ENUM,    (int*)gui_iso_exposure_order_enum},
	  {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
      {0}
};
static CMenu exposure_submenu = {0x2a,LANG_MENU_EXPOSURE_TITLE, NULL, exposure_submenu_items };
*/

// "Extra Photo Operations" Menu
static CMenuItem operation_submenu_items[] = {
      {0x5f,LANG_MENU_OVERRIDE_DISABLE,         MENUITEM_ENUM,    (int*)gui_override_disable_enum},//&conf.override_disable },
      {0x5c,LANG_MENU_OVERRIDE_DISABLE_ALL,     MENUITEM_BOOL,    &conf.override_disable_all },
	  {0x61,LANG_MENU_OVERRIDE_TV_VALUE,        MENUITEM_ENUM,    (int*)gui_tv_override_value_enum},
	  {0x5f,LANG_MENU_OVERRIDE_TV_KOEF,         MENUITEM_ENUM,    (int*)gui_tv_override_koef_enum},
 	  {0x59,LANG_MENU_TV_ENUM_TYPE,             MENUITEM_ENUM,    (int*)gui_tv_enum_type_enum},
#if CAM_HAS_IRIS_DIAPHRAGM
	  {0x62,LANG_MENU_OVERRIDE_AV_VALUE,        MENUITEM_ENUM,    (int*)gui_av_override_enum },
#endif
#if CAM_HAS_ND_FILTER
      {0x5f,LANG_MENU_OVERRIDE_ND_FILTER,       MENUITEM_ENUM,    (int*)gui_nd_filter_state_enum },
#endif
#if CAM_CAN_SD_OVERRIDE
      {0x5e,LANG_MENU_OVERRIDE_SUBJ_DIST_VALUE, MENUITEM_ENUM,    (int*)gui_subj_dist_override_value_enum},
	  {0x5f,LANG_MENU_OVERRIDE_SUBJ_DIST_KOEF,  MENUITEM_ENUM,    (int*)gui_subj_dist_override_koef_enum},
#endif
	  {0x74,LANG_MENU_OVERRIDE_ISO_VALUE,	   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.iso_override_value, MENU_MINMAX(0, 800)},
	  {0x5f,LANG_MENU_OVERRIDE_ISO_KOEF,        MENUITEM_ENUM,    (int*)gui_iso_override_koef_enum},
#if ZOOM_OVERRIDE
    {0x5c,LANG_MENU_OVERRIDE_ZOOM,         MENUITEM_BOOL,    &conf.zoom_override},
    {0x5f,LANG_MENU_OVERRIDE_ZOOM_VALUE,	  MENUITEM_ENUM,    (int*)gui_zoom_override_enum },

	  {0x5c,LANG_MENU_CLEAR_ZOOM_OVERRIDE_VALUES,    MENUITEM_BOOL,    (int*)&conf.clear_zoom_override},
#endif
	  {0x2c,LANG_MENU_BRACKET_IN_CONTINUOUS,	   MENUITEM_SUBMENU, (int*)&bracketing_in_continuous_submenu },
	  {0x2d,LANG_MENU_AUTOISO,                  MENUITEM_SUBMENU, (int*)&autoiso_submenu },
      //{LANG_MENU_EXPOSURE,               MENUITEM_SUBMENU, (int*)&exposure_submenu },
	  {0x5b,LANG_MENU_CLEAR_OVERRIDE_VALUES,    MENUITEM_BOOL,    (int*)&conf.clear_override},

      {0x5c,LANG_MENU_MISC_FAST_EV,         MENUITEM_BOOL,    &conf.fast_ev },
      {0x5f,LANG_MENU_MISC_FAST_EV_STEP,    MENUITEM_ENUM,    (int*)gui_fast_ev_step },
#if CAM_REAR_CURTAIN
      {0x5c, LANG_MENU_REAR_CURTAIN, MENUITEM_BOOL, &conf.flash_sync_curtain },
#endif
 	  {0x5c, LANG_MENU_FLASH_MANUAL_OVERRIDE, MENUITEM_BOOL,   &conf.flash_manual_override},
    {0x5f, LANG_MENU_FLASH_VIDEO_OVERRIDE_POWER,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.flash_video_override_power, MENU_MINMAX(0, 2)},
#if CAM_HAS_VIDEO_BUTTON
    {0x5c, LANG_MENU_FLASH_VIDEO_OVERRIDE, MENUITEM_BOOL,   &conf.flash_video_override},
#endif
#if CAM_QUALITY_OVERRIDE
    {0x5c,LANG_MENU_MISC_IMAGE_QUALITY,    MENUITEM_ENUM,    (int*)gui_fast_image_quality },
#endif
    {0x51,LANG_MENU_BACK,                     MENUITEM_UP },
    {0}
};
static CMenu operation_submenu = {0x21,LANG_MENU_OPERATION_PARAM_TITLE, NULL, operation_submenu_items };

#ifdef OPT_EDGEOVERLAY
static CMenuItem edge_overlay_submenu_items[] = {
    {0x5c,LANG_MENU_EDGE_OVERLAY_ENABLE,     MENUITEM_BOOL,          &conf.edge_overlay_enable },
    {0x5c,LANG_MENU_EDGE_FILTER,     MENUITEM_BOOL,          &conf.edge_overlay_filter },
    {0x5f,LANG_MENU_EDGE_PANO,     MENUITEM_ENUM,          (int*)gui_edge_pano_enum },
    {0x5e,LANG_MENU_EDGE_PANO_OVERLAP,   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.edge_overlay_pano_overlap, MENU_MINMAX(0, 100)},
    {0x5c,LANG_MENU_EDGE_SHOW,     MENUITEM_BOOL,          &conf.edge_overlay_show },
    {0x5e,LANG_MENU_EDGE_OVERLAY_TRESH,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.edge_overlay_thresh, MENU_MINMAX(0, 255)},
    {0x65,LANG_MENU_EDGE_OVERLAY_COLOR,      MENUITEM_COLOR_FG,      (int*)&conf.edge_overlay_color },
    {0x5c,LANG_MENU_EDGE_PLAY,			MENUITEM_BOOL,		&conf.edge_overlay_play }, //does not work on cams like s-series, which dont have a real "hardware" play/rec switch, need a workaround, probably another button
    {0x33,LANG_MENU_EDGE_SAVE,			MENUITEM_PROC,		(int*)gui_menuproc_edge_save },
    {0x5c,LANG_MENU_EDGE_ZOOM,     MENUITEM_BOOL,          &conf.edge_overlay_zoom },
    {0x33,LANG_MENU_EDGE_LOAD,			MENUITEM_PROC,		(int*)gui_menuproc_edge_load },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu edge_overlay_submenu = {0x7f,LANG_MENU_EDGE_OVERLAY_TITLE, NULL, edge_overlay_submenu_items };
#endif

static CMenuItem grid_submenu_items[] = {
    {0x2f,LANG_MENU_SHOW_GRID,               MENUITEM_BOOL,		&conf.show_grid_lines },
    {0x35,LANG_MENU_GRID_LOAD,               MENUITEM_PROC,		(int*)gui_grid_lines_load },
    {0x0,LANG_MENU_GRID_CURRENT,            MENUITEM_SEPARATOR },
    {0x0,(int)grid_title,                   MENUITEM_TEXT },
    {0x0,(int)"",                           MENUITEM_SEPARATOR },
    {0x5c,LANG_MENU_GRID_FORCE_COLOR,        MENUITEM_BOOL,          &conf.grid_force_color },
    {0x65,LANG_MENU_GRID_COLOR_LINE,         MENUITEM_COLOR_FG,      (int*)&conf.grid_color },
    {0x65,LANG_MENU_GRID_COLOR_FILL,         MENUITEM_COLOR_BG,      (int*)&conf.grid_color },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu grid_submenu = {0x2f,LANG_MENU_GRID_TITLE, NULL, grid_submenu_items };

static CMenuItem visual_submenu_items[] = {
    {0x35,LANG_MENU_VIS_LANG,                MENUITEM_PROC,      (int*)gui_draw_load_lang },
    {0x5f,LANG_MENU_VIS_OSD_FONT,            MENUITEM_ENUM,      (int*)gui_font_enum },
    {0x35,LANG_MENU_VIS_MENU_FONT,           MENUITEM_PROC,      (int*)gui_draw_load_menu_rbf },
    {0x35,LANG_MENU_VIS_MENU_SYMBOL_FONT,    MENUITEM_PROC,      (int*)gui_draw_load_symbol_rbf },
    {0x80,LANG_MENU_RESET_FILES		 ,         MENUITEM_PROC, 	   (int*)gui_menuproc_reset_files },
    {0x0,LANG_MENU_VIS_COLORS,              MENUITEM_SEPARATOR },
    {0x65,LANG_MENU_VIS_OSD_TEXT,            MENUITEM_COLOR_FG,  (int*)&conf.osd_color },
    {0x65,LANG_MENU_VIS_OSD_BKG,             MENUITEM_COLOR_BG,  (int*)&conf.osd_color },
    {0x65,LANG_MENU_VIS_OSD_WARNING,         MENUITEM_COLOR_FG,  (int*)&conf.osd_color_warn },
    {0x65,LANG_MENU_VIS_OSD_WARNING_BKG,     MENUITEM_COLOR_BG,  (int*)&conf.osd_color_warn },
    {0x65,LANG_MENU_VIS_HISTO,               MENUITEM_COLOR_FG,  (int*)&conf.histo_color },
    {0x65,LANG_MENU_VIS_HISTO_BKG,           MENUITEM_COLOR_BG,  (int*)&conf.histo_color },
    {0x65,LANG_MENU_VIS_HISTO_BORDER,        MENUITEM_COLOR_FG,  (int*)&conf.histo_color2 },
    {0x65,LANG_MENU_VIS_HISTO_MARKERS,       MENUITEM_COLOR_BG,  (int*)&conf.histo_color2 },
    {0x65,LANG_MENU_VIS_ZEBRA_UNDER,         MENUITEM_COLOR_BG,  (int*)&conf.zebra_color },
    {0x65,LANG_MENU_VIS_ZEBRA_OVER,          MENUITEM_COLOR_FG,  (int*)&conf.zebra_color },
    {0x65,LANG_MENU_VIS_BATT_ICON,           MENUITEM_COLOR_FG,  (int*)&conf.batt_icon_color },
    {0x65,LANG_MENU_VIS_SPACE_ICON,          MENUITEM_COLOR_FG,  (int*)&conf.space_color },
    {0x65,LANG_MENU_VIS_SPACE_ICON_BKG,      MENUITEM_COLOR_BG,  (int*)&conf.space_color },
    {0x65,LANG_MENU_VIS_MENU_TEXT,           MENUITEM_COLOR_FG,  (int*)&conf.menu_color },
    {0x65,LANG_MENU_VIS_MENU_BKG,            MENUITEM_COLOR_BG,  (int*)&conf.menu_color },
    {0x65,LANG_MENU_VIS_MENU_TITLE_TEXT,     MENUITEM_COLOR_FG,  (int*)&conf.menu_title_color },
    {0x65,LANG_MENU_VIS_MENU_TITLE_BKG,      MENUITEM_COLOR_BG,  (int*)&conf.menu_title_color },
    {0x65,LANG_MENU_VIS_MENU_CURSOR_TEXT,    MENUITEM_COLOR_FG,  (int*)&conf.menu_cursor_color },
    {0x65,LANG_MENU_VIS_MENU_CURSOR_BKG,     MENUITEM_COLOR_BG,  (int*)&conf.menu_cursor_color },
    {0x65,LANG_MENU_VIS_MENU_SYMBOL_TEXT,    MENUITEM_COLOR_FG,  (int*)&conf.menu_symbol_color },
    {0x65,LANG_MENU_VIS_MENU_SYMBOL_BKG,     MENUITEM_COLOR_BG,  (int*)&conf.menu_symbol_color },
    {0x65,LANG_MENU_VIS_READER_TEXT,         MENUITEM_COLOR_FG,  (int*)&conf.reader_color },
    {0x65,LANG_MENU_VIS_READER_BKG,          MENUITEM_COLOR_BG,  (int*)&conf.reader_color },
    {0x65,LANG_MENU_VIS_OSD_OVERRIDE,         MENUITEM_COLOR_FG,  (int*)&conf.osd_color_override },
    {0x65,LANG_MENU_VIS_OSD_OVERRIDE_BKG,     MENUITEM_COLOR_BG,  (int*)&conf.osd_color_override },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu visual_submenu = {0x28,LANG_MENU_VIS_TITLE, NULL, visual_submenu_items };

/*
 * 1 extra entry for the "Main menu" and 1 for null when the menu is full with user selections
 * Compiler will zero init remaining portion of array so no there is no hidden relationship between
 * this structure and the value of USER_MENU_ITEMS. The value of USER_MENU_ITEMS can be anything you
 * wish and everything automagically works.
*/

static CMenuItem user_submenu_items[USER_MENU_ITEMS + 2] = {
	{0x20,LANG_MENU_MAIN_TITLE,     MENUITEM_PROC,  (int*)rinit}
};

static CMenu user_submenu = {0x2e,LANG_MENU_USER_MENU, NULL, user_submenu_items };

static CMenuItem raw_state_submenu_items[] = {
    {0x5c,LANG_MENU_OSD_SHOW_RAW_STATE,      MENUITEM_BOOL,      &conf.show_raw_state },
    {0x5c,LANG_MENU_OSD_SHOW_REMAINING_RAW,  MENUITEM_BOOL,      &conf.show_remaining_raw },
    {0x60,LANG_MENU_OSD_RAW_TRESHOLD,        MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.remaining_raw_treshold,   MENU_MINMAX(0, 200)},
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};

static CMenu raw_state_submenu = {0x24,LANG_MENU_OSD_RAW_STATE_PARAMS_TITLE, NULL, raw_state_submenu_items };


static CMenuItem osd_submenu_items[] = {
    {0x5c,LANG_MENU_OSD_SHOW,                MENUITEM_BOOL,      &conf.show_osd },
    {0x5c,LANG_MENU_OSD_HIDE_PLAYBACK,       MENUITEM_ENUM,      (int*)gui_hide_osd_enum },
    {0x81,LANG_MENU_VIS_MENU_CENTER,         MENUITEM_BOOL,	    &conf.menu_center },
    {0x81,LANG_MENU_SELECT_FIRST_ENTRY,         MENUITEM_BOOL,	    &conf.menu_select_first_entry },
    {0x64,LANG_MENU_VIS_SYMBOL,             MENUITEM_BOOL,	    &conf.menu_symbol_enable },
    {0x2e,LANG_MENU_USER_MENU,  	    		MENUITEM_SUBMENU,   (int*)&user_submenu},
    {0x5f,LANG_MENU_USER_MENU_ENABLE,		MENUITEM_ENUM,      (int*)gui_user_menu_show_enum },
    {0x5c,LANG_MENU_USER_MENU_AS_ROOT,       MENUITEM_BOOL,      &conf.user_menu_as_root },
    {0x5f,LANG_MENU_OSD_SHOW_STATES,         MENUITEM_BOOL,      &conf.show_state },
    {0x5f,LANG_MENU_OSD_SHOW_TEMP,         MENUITEM_ENUM,      (int*)gui_temp_mode_enum },
    {0x59,LANG_MENU_OSD_TEMP_FAHRENHEIT,      MENUITEM_BOOL,      &conf.temperature_unit},
    {0x72,LANG_MENU_OSD_LAYOUT_EDITOR,       MENUITEM_PROC,      (int*)gui_draw_osd_le },
    {0x2f,LANG_MENU_OSD_GRID_PARAMS,         MENUITEM_SUBMENU,   (int*)&grid_submenu },
    {0x22,LANG_MENU_OSD_VALUES,  	    	MENUITEM_SUBMENU,   (int*)&values_submenu },
    {0x31,LANG_MENU_OSD_DOF_CALC,            MENUITEM_SUBMENU,   (int*)&dof_submenu },
    {0x24,LANG_MENU_OSD_RAW_STATE_PARAMS,    MENUITEM_SUBMENU,   (int*)&raw_state_submenu },
    {0x32,LANG_MENU_OSD_BATT_PARAMS,         MENUITEM_SUBMENU,   (int*)&battery_submenu },
    {0x33,LANG_MENU_OSD_SPACE_PARAMS,        MENUITEM_SUBMENU,   (int*)&space_submenu },
    {0x34,LANG_MENU_OSD_CLOCK_PARAMS,	 	MENUITEM_SUBMENU,   (int*)&clock_submenu },
    {0x59,LANG_MENU_OSD_SHOW_IN_REVIEW,      MENUITEM_BOOL,      &conf.show_osd_in_review},
#ifndef OPTIONS_AUTOSAVE
    {0x5c,LANG_MENU_MAIN_SAVE_OPTIONS,       MENUITEM_PROC,      (int*)gui_menuproc_save },
#endif
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};

static CMenu osd_submenu = {0x22,LANG_MENU_OSD_TITLE, NULL, osd_submenu_items };

static CMenuItem histo_submenu_items[] = {
    {0x5f,LANG_MENU_HISTO_SHOW,              MENUITEM_ENUM,      (int*)gui_histo_show_enum },
    {0x6f,LANG_MENU_HISTO_LAYOUT,            MENUITEM_ENUM,      (int*)gui_histo_layout_enum },
    {0x5f,LANG_MENU_HISTO_MODE,              MENUITEM_ENUM,      (int*)gui_histo_mode_enum },
    {0x5c,LANG_MENU_HISTO_EXP,               MENUITEM_BOOL,       &conf.show_overexp },
    {0x70,LANG_MENU_HISTO_IGNORE_PEAKS,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.histo_ignore_boundary,   MENU_MINMAX(0, 32)},
    {0x5c,LANG_MENU_HISTO_MAGNIFY,           MENUITEM_BOOL,       &conf.histo_auto_ajust },
    {0x5c,LANG_MENU_HISTO_SHOW_EV_GRID,      MENUITEM_BOOL,       &conf.histo_show_ev_grid },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu histo_submenu = {0x25,LANG_MENU_HISTO_TITLE, NULL, histo_submenu_items };

static CMenuItem raw_exceptions_submenu_items[] = {
    #if defined CAM_HAS_VIDEO_BUTTON
     {0x5c,LANG_MENU_RAW_SAVE_IN_VIDEO,                MENUITEM_BOOL,      &conf.save_raw_in_video },
    #endif
    #if defined(CAMERA_s3is)
    	{0x5c,LANG_MENU_RAW_SAVE_IN_SPORTS,                MENUITEM_BOOL,      &conf.save_raw_in_sports },
    #endif
    {0x5c,LANG_MENU_RAW_SAVE_IN_BURST,                MENUITEM_BOOL,      &conf.save_raw_in_burst },
    {0x5c,LANG_MENU_RAW_SAVE_IN_TIMER,                MENUITEM_BOOL,      &conf.save_raw_in_timer },
    {0x5c,LANG_MENU_RAW_SAVE_IN_EDGEOVERLAY,          MENUITEM_BOOL,      &conf.save_raw_in_edgeoverlay },
    {0x5c,LANG_MENU_RAW_SAVE_IN_AUTO,                 MENUITEM_BOOL,      &conf.save_raw_in_auto },
		#if CAM_BRACKETING
    	{0x5c,LANG_MENU_RAW_SAVE_IN_EV_BRACKETING,                MENUITEM_BOOL,      &conf.save_raw_in_ev_bracketing },
		#endif
    {0x5c,LANG_MENU_RAW_WARN,                MENUITEM_BOOL,      &conf.raw_exceptions_warn },
    {0x51,LANG_MENU_BACK,                           MENUITEM_UP },
    {0}
};
static CMenu raw_exceptions_submenu = {0x59,LANG_MENU_OSD_RAW_EXCEPTIONS_PARAMS_TITLE, NULL, raw_exceptions_submenu_items };


static CMenuItem raw_submenu_items[] = {
    {0x5c,LANG_MENU_RAW_SAVE,                MENUITEM_BOOL,      &conf.save_raw },
    {0x59,LANG_MENU_OSD_RAW_EXCEPTIONS_PARAMS,	 	MENUITEM_SUBMENU,   (int*)&raw_exceptions_submenu },
    {0x5f,LANG_MENU_RAW_NOISE_REDUCTION,     MENUITEM_ENUM,      (int*)gui_raw_nr_enum },
    {0x5c,LANG_MENU_RAW_FIRST_ONLY,          MENUITEM_BOOL,      &conf.raw_save_first_only },
    {0x5c,LANG_MENU_RAW_SAVE_IN_DIR,         MENUITEM_BOOL,      &conf.raw_in_dir },
    {0x5f,LANG_MENU_RAW_PREFIX,              MENUITEM_ENUM,      (int*)gui_raw_prefix_enum },
    {0x5f,LANG_MENU_RAW_EXTENSION,           MENUITEM_ENUM,      (int*)gui_raw_ext_enum },
    {0x5f,LANG_MENU_SUB_PREFIX,              MENUITEM_ENUM,      (int*)gui_sub_batch_prefix_enum },
    {0x5f,LANG_MENU_SUB_EXTENSION,           MENUITEM_ENUM,      (int*)gui_sub_batch_ext_enum },
//  {0x60,LANG_MENU_SUB_IN_DARK_VALUE,       MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.sub_in_dark_value, MENU_MINMAX(0, 1023)},
//  {0x60,LANG_MENU_SUB_OUT_DARK_VALUE,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.sub_out_dark_value, MENU_MINMAX(0, 1023)},
    {0x2a,LANG_MENU_RAW_DEVELOP,             MENUITEM_PROC,      (int*)gui_raw_develop },
    {0x5c,LANG_MENU_BAD_PIXEL_REMOVAL,       MENUITEM_ENUM,      (int*)gui_bad_pixel_enum },
#if DNG_SUPPORT
    {0x5c,LANG_MENU_DNG_FORMAT,              MENUITEM_BOOL | MENUITEM_ARG_CALLBACK, &conf.dng_raw , (int)cb_change_dng },
    {0x5c,LANG_MENU_RAW_DNG_EXT,             MENUITEM_BOOL,      &conf.raw_dng_ext},
    {0x2a,LANG_MENU_BADPIXEL_CREATE,         MENUITEM_PROC,      (int*)gui_menuproc_badpixel_create },
#endif
    {0x5c,LANG_MENU_RAW_CACHED,              MENUITEM_BOOL,      &conf.raw_cache },
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu raw_submenu = {0x24,LANG_MENU_RAW_TITLE, NULL, raw_submenu_items };


static CMenuItem zebra_submenu_items[] = {
    {0x5c,LANG_MENU_ZEBRA_DRAW,              MENUITEM_BOOL,                            &conf.zebra_draw },
    {0x5f,LANG_MENU_ZEBRA_MODE,              MENUITEM_ENUM,                            (int*)gui_zebra_mode_enum },
    {0x58,LANG_MENU_ZEBRA_UNDER,             MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zebra_under,   MENU_MINMAX(0, 32)},
    {0x57,LANG_MENU_ZEBRA_OVER,              MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zebra_over,    MENU_MINMAX(0, 32)},
    {0x28,LANG_MENU_ZEBRA_RESTORE_SCREEN,    MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,      &conf.zebra_restore_screen,     (int)cb_zebra_restore_screen },
    {0x5c,LANG_MENU_ZEBRA_RESTORE_OSD,       MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,      &conf.zebra_restore_osd,        (int)cb_zebra_restore_osd },
    {0x5f,LANG_MENU_ZEBRA_DRAW_OVER,         MENUITEM_ENUM,                            (int*)gui_zebra_draw_osd_enum },
    {0x5c,LANG_MENU_ZEBRA_MULTICHANNEL,      MENUITEM_BOOL,                            &conf.zebra_multichannel},
    {0x51,LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu zebra_submenu = {0x26,LANG_MENU_ZEBRA_TITLE, NULL, zebra_submenu_items };

#ifdef OPT_CURVES
static CMenuItem curve_submenu_items[] = {
    {0x5f,LANG_MENU_CURVE_ENABLE,        MENUITEM_ENUM,      (int*)gui_conf_curve_enum },
    {0x35,LANG_MENU_CURVE_LOAD,          MENUITEM_PROC,      (int*)gui_load_curve },
    {0x51,LANG_MENU_BACK,                MENUITEM_UP },
    {0}
};
static CMenu curve_submenu = {0x85,LANG_MENU_CURVE_PARAM_TITLE, NULL, curve_submenu_items };
#endif

static CMenuItem root_menu_items[] = {
    {0x21,LANG_MENU_OPERATION_PARAM,         MENUITEM_SUBMENU,   (int*)&operation_submenu },
    {0x23,LANG_MENU_VIDEO_PARAM,             MENUITEM_SUBMENU,   (int*)&video_submenu },
    {0x24,LANG_MENU_MAIN_RAW_PARAM,          MENUITEM_SUBMENU,   (int*)&raw_submenu },
#ifdef OPT_EDGEOVERLAY
    {0x7f,LANG_MENU_EDGE_OVERLAY,         MENUITEM_SUBMENU,   (int*)&edge_overlay_submenu },
#endif
#ifdef OPT_CURVES
    {0x85,LANG_MENU_CURVE_PARAM,             MENUITEM_SUBMENU,   (int*)&curve_submenu },
#endif
    {0x25,LANG_MENU_MAIN_HISTO_PARAM,        MENUITEM_SUBMENU,   (int*)&histo_submenu },
    {0x26,LANG_MENU_MAIN_ZEBRA_PARAM,        MENUITEM_SUBMENU,   (int*)&zebra_submenu },
    {0x22,LANG_MENU_MAIN_OSD_PARAM,          MENUITEM_SUBMENU,   (int*)&osd_submenu },
    {0x28,LANG_MENU_MAIN_VISUAL_PARAM,       MENUITEM_SUBMENU,   (int*)&visual_submenu },
#ifdef OPT_SCRIPTING
    {0x27,LANG_MENU_MAIN_SCRIPT_PARAM,       MENUITEM_SUBMENU,   (int*)&script_submenu },
#endif
    {0x29,LANG_MENU_MAIN_MISC,               MENUITEM_SUBMENU,   (int*)&misc_submenu },
#ifndef OPTIONS_AUTOSAVE
    {0x33,LANG_MENU_MAIN_SAVE_OPTIONS,       MENUITEM_PROC,      (int*)gui_menuproc_save },
#endif
    {0}
};

static CMenu root_menu = {0x20,LANG_MENU_MAIN_TITLE, NULL, root_menu_items };

static int gui_user_menu_flag;

void rinit(){
	gui_menu_init(&root_menu);
}

//-------------------------------------------------------------------
void
mod_user_menu(CMenuItem curr_menu_item, int* cur_memnu_item_indx, int mod) {
int i;
CMenuItem tmp_menu_item;
	switch(mod) {

		case 0:
			/*
			 * Delete user menu entry by sliding all the lower valid/existing entries up.
			 */

			if (*cur_memnu_item_indx == 0) /* don't allow deleting "user menu" */
				break;
 			for(i = *cur_memnu_item_indx; user_submenu_items[i].text; i++) {
 				user_submenu_items[i] = user_submenu_items[i+1];
 			}

 			/*
 			 * there were no valid entries below this one, so
 			 * the index pointer must be decremented.
 			 */
 			if(!user_submenu_items[*cur_memnu_item_indx].text)
 				*cur_memnu_item_indx -= 1;

 			break;

 		case 1:
 			/*
 			 * Insert new Item at end of existing entries
 			 */
 			for(i = 1; i < USER_MENU_ITEMS + 1; i++) {
 				if(!user_submenu_items[i].text) {
 					user_submenu_items[i] = curr_menu_item;
 					break;
				}
 			}
 			break;

 		case 2:
 			/*
 			 * Move entry up
 			 */

 			if((*cur_memnu_item_indx > 1)) {
 				tmp_menu_item = user_submenu_items[*cur_memnu_item_indx -1];
 				user_submenu_items[*cur_memnu_item_indx -1] = user_submenu_items[*cur_memnu_item_indx];
 				user_submenu_items[*cur_memnu_item_indx] = tmp_menu_item;
 				*cur_memnu_item_indx -=1;
 			}
 			break;

 		case 3:
 			/*
 			 * Move entry down below next entry if next entry is not empty
 			 */
 			if (*cur_memnu_item_indx == 0) /* don't allow moving "user menu" */
 				break;
 			if((*cur_memnu_item_indx < (USER_MENU_ITEMS)) && (user_submenu_items[*cur_memnu_item_indx +1].text)) {
 				tmp_menu_item = user_submenu_items[*cur_memnu_item_indx +1];
 				user_submenu_items[*cur_memnu_item_indx + 1] = user_submenu_items[*cur_memnu_item_indx];
 				user_submenu_items[*cur_memnu_item_indx] = tmp_menu_item;
 				*cur_memnu_item_indx +=1;
 			}
 			break;

 	}
}

//-------------------------------------------------------------------
void cb_step_25() {
    voltage_step = (conf.batt_step_25)?25:1;
}

void cb_perc() {
    conf.batt_volts_show=0;
}

void cb_volts() {
    conf.batt_perc_show=0;
}

void cb_space_perc() {
    conf.space_mb_show=0;
}

void cb_space_mb() {
    conf.space_perc_show=0;
}

void cb_battery_menu_change(unsigned int item) {
    switch (item) {
        case 0: //Voltage MAX
            if (conf.batt_volts_max<conf.batt_volts_min+25) {
                conf.batt_volts_min = conf.batt_volts_max-25;
            }
            break;
        case 1: //Voltage MIN
            if (conf.batt_volts_min>conf.batt_volts_max-25) {
                conf.batt_volts_max = conf.batt_volts_min+25;
            }
            break;
        default:
            break;
    }
}

void cb_zebra_restore_screen() {
    if (!conf.zebra_restore_screen)
        conf.zebra_restore_osd = 0;
}

void cb_zebra_restore_osd() {
    if (conf.zebra_restore_osd)
        conf.zebra_restore_screen = 1;
}

#if DNG_SUPPORT
void cb_change_dng(){
 int old=conf.dng_raw;
 conf_change_dng();
 if ((old==1) && (conf.dng_raw==0)) gui_mbox_init(LANG_ERROR, LANG_CANNOT_OPEN_BADPIXEL_FILE, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
}

void gui_menuproc_badpixel_create(int arg) {
    create_badpixel_bin();
}
#endif

#if defined (DNG_EXT_FROM)
void cb_change_dng_usb_ext(){
 if (conf.dng_usb_ext) change_ext_to_dng(); else change_ext_to_default();
}
#endif

/*
common code for "enum" menu items that just take a list of string values and don't require any special setters
would be better to have another menu item type that does this by default
save memory by eliminating dupe code
*/
static void gui_enum_value_change(int *value, int change, unsigned num_items) {
    *value+=change;
    if (*value<0)
        *value = num_items-1;
    else if (*value>=num_items)
        *value = 0;
}
static const char* gui_change_simple_enum(int* value, int change, const char** items, unsigned num_items) {
	gui_enum_value_change(value, change, num_items);
    return items[*value];
}

//-------------------------------------------------------------------
#ifdef OPT_CURVES
const char* gui_conf_curve_enum(int change, int arg) {
    static const char* modes[]={ "None", "Custom", "+1EV", "+2EV", "Auto DR" };

    gui_enum_value_change(&conf.curve_enable,change,sizeof(modes)/sizeof(modes[0]));

	if(change)
		curve_init_mode();
    return modes[conf.curve_enable];
}
#endif

#ifdef OPT_SCRIPTING
//-------------------------------------------------------------------
const char* gui_script_autostart_enum(int change, int arg) {
    static const char* modes[]={ "Off", "On", "Once"};
	return gui_change_simple_enum(&conf.script_startup,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
const char* gui_script_param_set_enum(int change, int arg) {
    static const char* modes[]={ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    if (change != 0) {
        if (conf.script_param_save) {
            save_params_values(0);
        }
		gui_enum_value_change(&conf.script_param_set,change,sizeof(modes)/sizeof(modes[0]));

        if (!load_params_values(conf.script_file, 1, 0))
            script_load(conf.script_file, 0);
        gui_update_script_submenu();
    }

    return modes[conf.script_param_set];
}

//-------------------------------------------------------------------
void gui_update_script_submenu() {
    register int p=0, i;

    for (i=0; i<sizeof(script_submenu_items_top)/sizeof(script_submenu_items_top[0]); ++p, ++i) {
        script_submenu_items[p]=script_submenu_items_top[i];
    }
    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        if (script_param_order[i]) {
            script_submenu_items[p].symbol=0x0;
            script_submenu_items[p].text=(int)script_params[script_param_order[i]-1];
            script_submenu_items[p].type=MENUITEM_INT;
            script_submenu_items[p].value=&conf.ubasic_vars[script_param_order[i]-1];
            ++p;
        }
    }
    for (i=0; i<sizeof(script_submenu_items_bottom)/sizeof(script_submenu_items_bottom[0]); ++p, ++i) {
        script_submenu_items[p]=script_submenu_items_bottom[i];
    }
}

//-------------------------------------------------------------------
static void gui_load_script_selected(const char *fn) {
    if (fn)
        script_load(fn, 1);
}

void gui_load_script(int arg) {
    DIR   *d;
    char  *path="A/CHDK/SCRIPTS";

    // if exists "A/CHDK/SCRIPTS" go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_STR_SELECT_SCRIPT_FILE, path, gui_load_script_selected);
}

void gui_load_script_default(int arg) {
    script_load(conf.script_file, 0);
    if (conf.script_param_save) {
        save_params_values(1);
    }
}
#endif

//-------------------------------------------------------------------
const char* gui_override_disable_enum(int change, int arg) {
    static const char* modes[]={ "Off", "On", "Disabled"};
	return gui_change_simple_enum(&conf.override_disable,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
const char* gui_histo_mode_enum(int change, int arg) {
    static const char* modes[]={ "Linear", "Log" };

	gui_enum_value_change(&conf.histo_mode,change,sizeof(modes)/sizeof(modes[0]));

    histogram_set_mode(conf.histo_mode);

    return modes[conf.histo_mode];
}

//-------------------------------------------------------------------
const char* gui_temp_mode_enum(int change, int arg) {
    static const char* modes[]={ "Off", "Optical","CCD","Battery","all" };
	return gui_change_simple_enum(&conf.show_temp,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
const char* gui_histo_layout_enum(int change, int arg) {
    static const char* modes[]={ "RGB", "Y", "RGB Y",  "R G B", "RGB all", "Y all", "Blend", "Blend Y"};

	gui_enum_value_change(&conf.histo_layout,change,sizeof(modes)/sizeof(modes[0]));

    if (conf.histo_layout==OSD_HISTO_LAYOUT_Y || conf.histo_layout==OSD_HISTO_LAYOUT_Y_argb) {
        histogram_set_main(HISTO_Y);
    } else {
        histogram_set_main(HISTO_RGB);
    }

    return modes[conf.histo_layout];
}

//-------------------------------------------------------------------
const char* gui_font_enum(int change, int arg) {
    static const char* fonts[]={ "Win1250", "Win1251", "Win1252", "Win1253", "Win1254", "Win1257"};

	gui_enum_value_change(&conf.font_cp,change,sizeof(fonts)/sizeof(fonts[0]));

    if (change != 0) {
        font_set(conf.font_cp);
        if (!rbf_load(conf.menu_rbf_file))
            rbf_load_from_8x16(current_font);
        rbf_set_codepage(FONT_CP_WIN);
        gui_menu_init(NULL);
    }

    return fonts[conf.font_cp];
}

//-------------------------------------------------------------------
const char* gui_raw_prefix_enum(int change, int arg) {
	return gui_change_simple_enum(&conf.raw_prefix,change,img_prefixes,NUM_IMG_PREFIXES);
}

//-------------------------------------------------------------------
const char* gui_raw_ext_enum(int change, int arg) {
	return gui_change_simple_enum(&conf.raw_ext,change,img_exts,NUM_IMG_EXTS);
}

//-------------------------------------------------------------------
const char* gui_sub_batch_prefix_enum(int change, int arg) {
	return gui_change_simple_enum(&conf.sub_batch_prefix,change,img_prefixes,NUM_IMG_PREFIXES);
}

//-------------------------------------------------------------------
const char* gui_sub_batch_ext_enum(int change, int arg) {
	return gui_change_simple_enum(&conf.sub_batch_ext,change,img_exts,NUM_IMG_EXTS);
}

//-------------------------------------------------------------------
const char* gui_raw_nr_enum(int change, int arg) {
    static const char* modes[]={ "Auto", "Off", "On"};
	return gui_change_simple_enum(&conf.raw_nr,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
#ifdef OPT_TEXTREADER
const char* gui_reader_codepage_enum(int change, int arg) {
    static const char* cps[]={ "Win1251", "DOS"};
	return gui_change_simple_enum(&conf.reader_codepage,change,cps,sizeof(cps)/sizeof(cps[0]));
}
#endif
//-------------------------------------------------------------------
const char* gui_autoiso_shutter_enum(int change, int arg) {
    static const char* shutter[]={ "Auto", "1/8s", "1/15s", "1/30s", "1/60s", "1/125s", "1/250s", "1/500s", "1/1000s"};
	return gui_change_simple_enum(&conf.autoiso_shutter,change,shutter,sizeof(shutter)/sizeof(shutter[0]));
}

//-------------------------------------------------------------------
const char* gui_zebra_mode_enum(int change, int arg) {
    static const char* modes[]={ "Blink 1", "Blink 2", "Blink 3", "Solid", "Zebra 1", "Zebra 2" };
	return gui_change_simple_enum(&conf.zebra_mode,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
const char* gui_zebra_draw_osd_enum(int change, int arg) {
    static const char* modes[]={ "Nothing", "Histo", "OSD" };
	return gui_change_simple_enum(&conf.zebra_draw_osd,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
const char* gui_zoom_value_enum(int change, int arg) {
    static const char* modes[]={ "X", "FL", "EFL" };
	return gui_change_simple_enum(&conf.zoom_value,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_show_values_enum(int change, int arg) {
    static const char* modes[]={ "Don't", "Always", "Shoot" };
	return gui_change_simple_enum(&conf.show_values,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_nd_filter_state_enum(int change, int arg) {
    static const char* modes[]={ "Off", "In", "Out" };
	return gui_change_simple_enum(&conf.nd_filter_state,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_dof_show_value_enum(int change, int arg) {
    static const char* modes[]={ "Don't", "Separate", "In Misc" };
	return gui_change_simple_enum(&conf.show_dof,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_histo_show_enum(int change, int arg) {
    static const char* modes[]={ "Don't", "Always", "Shoot" };
	return gui_change_simple_enum(&conf.show_histo,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_show_clock_enum(int change, int arg) {
    static const char* modes[]={ "Don't", "Normal", "Seconds"};
	return gui_change_simple_enum(&conf.show_clock,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_hide_osd_enum(int change, int arg) {
    static const char* modes[]={ "Don't", "In Playback", "On Disp Press", "both"};
	return gui_change_simple_enum(&conf.hide_osd,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_clock_format_enum(int change, int arg) {
    static const char* modes[]={ "24h", "12h"};
	return gui_change_simple_enum(&conf.clock_format,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_clock_indicator_enum(int change, int arg) {
    static const char* modes[]={ "PM", "P","."};
	return gui_change_simple_enum(&conf.clock_indicator,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_clock_halfpress_enum(int change, int arg) {
    static const char* modes[]={ "Full", "Seconds","Don't"};
	return gui_change_simple_enum(&conf.clock_halfpress,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_space_bar_enum(int change, int arg) {
    static const char* modes[]={ "Don't", "Horizontal", "Vertical"};
	return gui_change_simple_enum(&conf.space_bar_show,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_space_bar_size_enum(int change, int arg) {
    static const char* modes[]={ "1/4", "1/2", "1"};
	return gui_change_simple_enum(&conf.space_bar_size,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_space_bar_width_enum(int change, int arg) {
    static const char* modes[]={ "1", "2", "3","4","5","6","7","8","9","10"};
	return gui_change_simple_enum(&conf.space_bar_width,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_space_warn_type_enum(int change, int arg) {
    static const char* modes[]={ "Percent", "MB", "Don't"};
	return gui_change_simple_enum(&conf.space_warn_type,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_show_movie_time(int change, int arg) {
    static const char* modes[]={ "Don't", "hh:mm:ss", "KB/s","both"};
	return gui_change_simple_enum(&conf.show_movie_time,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
#if CAM_ADJUSTABLE_ALT_BUTTON
const char* gui_alt_mode_button_enum(int change, int arg) {
#if defined(CAMERA_s2is) || defined(CAMERA_s3is) || defined(CAMERA_s5is)
    static const char* names[]={ "Shrtcut", "Flash", "Timer", "ISO", "Video" };
    static const int keys[]={ KEY_PRINT, KEY_FLASH, KEY_TIMER, KEY_ISO, KEY_VIDEO };
#elif defined(CAMERA_g7)
    static const char* names[]={ "Print", "FE"};
    static const int keys[]={ KEY_PRINT, KEY_MICROPHONE };
#elif defined(CAMERA_g9)
    static const char* names[]={ "Print", "FE"};
    static const int keys[]={ KEY_PRINT,  KEY_MICROPHONE };
#elif defined(CAMERA_a650)
    static const char* names[]={ "Print", "ISO"};
    static const int keys[]={ KEY_PRINT, KEY_ISO };
#elif defined(CAMERA_sx100is) || defined(CAMERA_sx110is)
    static const char* names[]={ "Print", "Face"};
    static const int keys[]={ KEY_PRINT, KEY_FACE };
#elif defined(CAMERA_sx10) || defined(CAMERA_sx1) || defined(CAMERA_sx20) || defined(CAMERA_sx30)
    static const char* names[]={ "Shrtcut", "Flash", "Video"};
    static const int keys[]={ KEY_PRINT, KEY_FLASH, KEY_VIDEO };
#elif defined(CAMERA_a570) || defined(CAMERA_a590) || defined(CAMERA_a720)
    static const char* names[]={ "Print", "Display"};
    static const int keys[] = {KEY_PRINT, KEY_DISPLAY};
#else
    #error camera alt-buttons not defined
#endif
    int i;

    for (i=0; i<sizeof(names)/sizeof(names[0]); ++i) {
        if (conf.alt_mode_button==keys[i]) {
            break;
        }
    }

    i+=change;
    if (i<0)
        i=(sizeof(names)/sizeof(names[0]))-1;
    else if (i>=(sizeof(names)/sizeof(names[0])))
        i=0;

    conf.alt_mode_button = keys[i];
    kbd_set_alt_mode_key_mask(conf.alt_mode_button);
    return names[i];
}
#endif

//-------------------------------------------------------------------
const char* gui_alt_power_enum(int change, int arg) {
// Script option is retained even if scripting is disabled, otherwise conf values will change
// Equivalent to ALT
    static const char* modes[]={ "Never", "Alt", "Script", "Always" };
	gui_enum_value_change(&conf.alt_prevent_shutdown,change,sizeof(modes)/sizeof(modes[0]));

	conf_update_prevent_shutdown();

    return modes[conf.alt_prevent_shutdown];
}
const char* gui_fast_ev_step(int change, int arg) {
    static const char* modes[]={"1/6 Ev","1/3 Ev","1/2 Ev", "2/3 Ev","5/6 Ev","1 Ev","1 1/6 Ev","1 1/3 Ev","1 1/2 Ev", "1 2/3 Ev","1 5/6 Ev","2 Ev","2 1/6 Ev","2 1/3 Ev","2 1/2 Ev", "2 2/3 Ev","2 5/6 Ev","3 Ev","3 1/6 Ev","3 1/3 Ev","3 1/2 Ev", "3 2/3 Ev","3 5/6 Ev","4 Ev"};
	return gui_change_simple_enum(&conf.fast_ev_step,change,modes,sizeof(modes)/sizeof(modes[0]));
}
#if CAM_QUALITY_OVERRIDE
const char* gui_fast_image_quality(int change, int arg) {
    static const char* modes[]={"sup.fine","fine","normal","off"};
	return gui_change_simple_enum(&conf.fast_image_quality,change,modes,sizeof(modes)/sizeof(modes[0]));
}
#endif

const char* gui_video_mode_enum(int change, int arg) {
#if !CAM_VIDEO_QUALITY_ONLY
    static const char* modes[]={ "Bitrate", "Quality"};
#else
    static const char* modes[]={ "Default", "Quality"};
#endif
	return gui_change_simple_enum(&conf.video_mode,change,modes,sizeof(modes)/sizeof(modes[0]));
}

//-------------------------------------------------------------------
const char* gui_video_bitrate_enum(int change, int arg) {
	gui_enum_value_change(&conf.video_bitrate,change,VIDEO_BITRATE_STEPS);

    shooting_video_bitrate_change(conf.video_bitrate);

    return video_bitrate_strings[conf.video_bitrate];
}


//-------------------------------------------------------------------
const char* gui_tv_bracket_values_enum(int change, int arg) {
    static const char* modes[]={ "Off", "1/3 Ev","2/3 Ev", "1 Ev", "1 1/3Ev", "1 2/3Ev", "2 Ev", "2 1/3Ev", "2 2/3Ev", "3 Ev", "3 1/3Ev", "3 2/3Ev", "4 Ev"};
	return gui_change_simple_enum(&conf.tv_bracket_value,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_av_bracket_values_enum(int change, int arg) {
    static const char* modes[]={ "Off", "1/3 Ev","2/3 Ev", "1 Ev", "1 1/3Ev", "1 2/3Ev", "2 Ev", "2 1/3Ev", "2 2/3Ev", "3 Ev", "3 1/3Ev", "3 2/3Ev", "4 Ev"};
	return gui_change_simple_enum(&conf.av_bracket_value,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_subj_dist_bracket_koef_enum(int change, int arg) {
    static const char* modes[]={"Off", "1", "10","100","1000"};
	return gui_change_simple_enum(&conf.subj_dist_bracket_koef,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_iso_bracket_koef_enum(int change, int arg) {
    static const char* modes[]={ "Off","1", "10","100"};
	return gui_change_simple_enum(&conf.iso_bracket_koef,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_bracket_type_enum(int change, int arg) {
    static const char* modes[]={ "+/-", "-","+"};
	return gui_change_simple_enum(&conf.bracket_type,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_tv_override_koef_enum(int change, int arg) {
    static const char* modes[]={"Off", "1/100K", "1/10000", "1/1000","1/100","1/10", "1","10","100"};

    conf.tv_override_koef+=change;
   if (conf.tv_enum_type) {
     if (conf.tv_override_koef<0)  conf.tv_override_koef=6;
     else if (conf.tv_override_koef>6) conf.tv_override_koef=0;
     else if (conf.tv_override_koef==1)	 conf.tv_override_koef=6;
     else if (conf.tv_override_koef==5)	 conf.tv_override_koef=0;
     else if (conf.tv_override_koef!=0 && conf.tv_override_koef!=6) conf.tv_override_koef=6;
     }
   else {
    if (conf.tv_override_koef<0)
        conf.tv_override_koef=sizeof(modes)/sizeof(modes[0])-1;
    else if (conf.tv_override_koef>=(sizeof(modes)/sizeof(modes[0])))
        conf.tv_override_koef=0;
    }

    return modes[conf.tv_override_koef];
}

const char* gui_tv_override_value_enum(int change, int arg) {
	/*
    static const char* modes[]={
    // add very long time exposures as approximately powers of 2, adding 15 exposures
    "2048","1625","1290","1024","812","645","512","406","322","256","203","161","128","101","80",
		"64","50.8", "40.3", "32", "25.4","20","16", "12.7", "10","8", "6.3","5","4","3.2", "2.5","2", "1.6", "1.3", "1", "0.8", "0.6", "0.5", "0.4", "0.3", "1/4", "1/5", "1/6", "1/8", "1/10", "1/13", "1/15", "1/20", "1/25", "1/30", "1/40", "1/50", "1/60", "1/80", "1/100", "1/125", "1/160", "1/200", "1/250", "1/320", "1/400", "1/500", "1/640","1/800", "1/1000", "1/1250", "1/1600","1/2000","1/2500","1/3200","1/4000", "1/5000", "1/6400", "1/8000", "1/10000", "1/12500", "1/16000", "1/20000", "1/25000", "1/32000", "1/40000", "1/50000", "1/64000","1/80000", "1/100k"};
		*/
    static char *buf;

	// XXX This array above is redundant with platform/generic/shooting.c, this should be avoided!
    conf.tv_override_value+=change;
    if (conf.tv_enum_type) {
       if (conf.tv_override_value<0) {
          conf.tv_override_value=tv_override_amount-1;
        }
       else if ((unsigned)conf.tv_override_value>=(tv_override_amount))
         conf.tv_override_value=0;
       return tv_override[conf.tv_override_value];
     }
     else
      {
       if (conf.tv_override_value<0) {
          conf.tv_override_value=100;
        }
       else if (conf.tv_override_value>100)  conf.tv_override_value=0;
       if(!buf) buf=malloc(4);
       if(!buf) return "";
       sprintf(buf, "%d",  conf.tv_override_value);
       return buf;
      }
}

const char* gui_tv_enum_type_enum(int change, int arg) {
    static const char* modes[]={"Factor", "Ev Step"};

    gui_enum_value_change(&conf.tv_enum_type,change,sizeof(modes)/sizeof(modes[0]));
    if (change) {
        conf.tv_override_koef=6;
        if (conf.tv_enum_type)
            conf.tv_override_value=tv_override_zero_shift;
        else conf.tv_override_value=1;
    }
    return modes[conf.tv_enum_type];
}


const char* gui_iso_override_koef_enum(int change, int arg) {
    static const char* modes[]={ "Off","1", "10","100"};
	return gui_change_simple_enum(&conf.iso_override_koef,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_subj_dist_override_value_enum(int change, int arg) {
	static const int koef[] = {0, 1,10,100,1000};
    static char buf[8];
    conf.subj_dist_override_value+=(change*koef[conf.subj_dist_override_koef]);
    if (conf.subj_dist_override_value<0)
        conf.subj_dist_override_value=MAX_DIST;
    else if (conf.subj_dist_override_value>MAX_DIST)
        conf.subj_dist_override_value=0;
    sprintf(buf, "%d", (int)conf.subj_dist_override_value);
    return buf;
}


const char* gui_subj_dist_override_koef_enum(int change, int arg) {
    static const char* modes[]={ "Off","1", "10","100","1000"};
	return gui_change_simple_enum(&conf.subj_dist_override_koef,change,modes,sizeof(modes)/sizeof(modes[0]));
}

/*
const char* gui_tv_exposure_order_enum(int change, int arg) {
    static const char* modes[]={ "Off", "1","2", "3"};

    conf.tv_exposure_order+=change;
    if (conf.tv_exposure_order<0)
        conf.tv_exposure_order=0;
    else if (conf.tv_exposure_order>=(sizeof(modes)/sizeof(modes[0])))
        conf.tv_exposure_order=sizeof(modes)/sizeof(modes[0])-1;
    if((conf.tv_exposure_order>0) && (conf.av_exposure_order==conf.tv_exposure_order))
     {
       conf.av_exposure_order=0;
     }
    if((conf.tv_exposure_order>0) && (conf.iso_exposure_order==conf.tv_exposure_order))
     {
       conf.iso_exposure_order=0;
     }

    return modes[conf.tv_exposure_order];
}

const char* gui_av_exposure_order_enum(int change, int arg) {
    static const char* modes[]={ "Off", "1","2", "3"};

    conf.av_exposure_order+=change;
    if (conf.av_exposure_order<0)
        conf.av_exposure_order=0;
    else if (conf.av_exposure_order>=(sizeof(modes)/sizeof(modes[0])))
        conf.av_exposure_order=sizeof(modes)/sizeof(modes[0])-1;
    if((conf.av_exposure_order>0) && (conf.tv_exposure_order==conf.av_exposure_order))
     {
       conf.tv_exposure_order=0;
     }
    if((conf.av_exposure_order>0) && (conf.iso_exposure_order==conf.av_exposure_order))
     {
       conf.iso_exposure_order=0;
     }
    return modes[conf.av_exposure_order];
}

const char* gui_iso_exposure_order_enum(int change, int arg) {
    static const char* modes[]={ "Off", "1","2", "3"};

    conf.iso_exposure_order+=change;
    if (conf.iso_exposure_order<0)
        conf.iso_exposure_order=0;
    else if (conf.iso_exposure_order>=(sizeof(modes)/sizeof(modes[0])))
        conf.iso_exposure_order=sizeof(modes)/sizeof(modes[0])-1;
    if((conf.iso_exposure_order>0) && (conf.tv_exposure_order==conf.iso_exposure_order))
     {
       conf.tv_exposure_order=0;
     }
    if((conf.iso_exposure_order>0) && (conf.av_exposure_order==conf.iso_exposure_order))
     {
       conf.av_exposure_order=0;
     }

    return modes[conf.iso_exposure_order];
}
*/
const char* gui_av_override_enum(int change, int arg) {
    static char buf[8];
    short prop_id;
    conf.av_override_value+=change;
    if (conf.av_override_value<0) conf.av_override_value=shooting_get_aperture_sizes_table_size()+6;
    else if (conf.av_override_value>shooting_get_aperture_sizes_table_size()+6) conf.av_override_value=0;
    if (conf.av_override_value == 0)  return "Off";
    else {
     short prop_id=shooting_get_aperture_from_av96(shooting_get_av96_override_value());
	 sprintf(buf, "%d.%02d", (int)prop_id/100, (int)prop_id%100 );
	 return buf;
	}
}

#if ZOOM_OVERRIDE
const char* gui_zoom_override_enum(int change, int arg) {
    static char buf[3];
    conf.zoom_override_value+=change;
    if (conf.zoom_override_value<0) conf.zoom_override_value=zoom_points-1;
    else if (conf.zoom_override_value>zoom_points-1) conf.zoom_override_value=0;
		sprintf(buf,"%i",conf.zoom_override_value);
		return buf;
}
#endif

const char* gui_user_menu_show_enum(int change, int arg) {
    static const char* modes[]={ "Off", "On","On Direct", "Edit" };

	if (conf.user_menu_enable == 3) user_menu_save();
	return gui_change_simple_enum(&conf.user_menu_enable,change,modes,sizeof(modes)/sizeof(modes[0]));
}

const char* gui_video_af_key_enum(int change, int arg){
#if CAMERA_g12
    static const char* names[]={ "", "Shutter", "Set", "AE Lock"};
    static const int keys[]={0, KEY_SHOOT_HALF, KEY_SET, KEY_AE_LOCK };
#else
    static const char* names[]={ "", "Shutter", "Set"};
    static const int keys[]={0, KEY_SHOOT_HALF, KEY_SET };
#endif
    int i;

    for (i=0; i<sizeof(names)/sizeof(names[0]); ++i) {
        if (conf.video_af_key==keys[i]) {
            break;
        }
    }

    i+=change;
    if (i<0)
        i=(sizeof(names)/sizeof(names[0]))-1;
    else if (i>=(sizeof(names)/sizeof(names[0])))
        i=0;

    conf.video_af_key = keys[i];
    return names[i];
}

const char* gui_bad_pixel_enum(int change, int arg) {
    int modes[]={LANG_MENU_BAD_PIXEL_OFF, LANG_MENU_BAD_PIXEL_INTERPOLATION, LANG_MENU_BAD_PIXEL_RAW_CONVERTER};
	return lang_str((int)gui_change_simple_enum(&conf.bad_pixel_removal,change,(const char **)modes,sizeof(modes)/sizeof(modes[0])));
}

//-------------------------------------------------------------------

void raw_fselect_cb(const char * filename){
 struct stat st;
 if (!filename) return;
 stat((char*)filename,&st);
 if (st.st_size!=hook_raw_size()) return;
 gui_mbox_init((int)"", LANG_RAW_DEVELOP_MESSAGE, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
 raw_prepare_develop((char*)filename);
}

//-------------------------------------------------------------------
void gui_raw_develop(int arg){
 int m=mode_get();
 gui_fselect_init(LANG_RAW_DEVELOP_SELECT_FILE, "A/DCIM", raw_fselect_cb);
}

//-------------------------------------------------------------------

static void gui_menuproc_reset_files(int arg){
conf.lang_file[0] = 0;
conf.menu_symbol_rbf_file[0] = 0;
conf.menu_rbf_file[0] = 0;
conf_save();
gui_mbox_init(LANG_INFORMATION, LANG_MENU_RESTART_CAMERA, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);

}

//-------------------------------------------------------------------
#ifdef OPT_DEBUGGING
#define TASKLIST_MAX_LINES 12 // probably as much as will fit on screen
#define TASKLIST_NUM_TASKS 64 // should be enough ?
static void gui_debug_draw_tasklist(void) {
#ifndef CAM_DRYOS
    int tasklist[TASKLIST_NUM_TASKS]; // max number of tasks we will look at
    char buf[40]; // a single line of the list
    int n_tasks,n_show_tasks,show_start;
    const char *name;
    int i;
    n_tasks = task_id_list_get(tasklist,sizeof(tasklist)/sizeof(tasklist[0]));
    show_start = debug_tasklist_start;
    n_show_tasks = n_tasks - show_start;
    // auto adjust to show the last N tasks
    if(n_show_tasks < TASKLIST_MAX_LINES) {
        show_start = n_tasks - TASKLIST_MAX_LINES;
        if(show_start<0)
            show_start = 0;
         n_show_tasks = n_tasks - show_start;
    }
    else if( n_show_tasks > TASKLIST_MAX_LINES ) {
        n_show_tasks = TASKLIST_MAX_LINES;
    }
    sprintf(buf,"%d-%d of %d tasks %c",show_start,show_start+n_show_tasks,n_tasks,debug_display_direction > 0?'+':'-');
    draw_string(64,0,buf, conf.osd_color);
    for( i = 0;  i < n_show_tasks; i++ ) {
        // TODO get full task info
        name = task_name(tasklist[show_start+i]);
        if ( !name || !*name ) {
            name = "(unknown)";
        }
        sprintf(buf,"%10s %8X",name,tasklist[show_start+i]);
        draw_string(64,16+16*i,buf, conf.osd_color);
    }
#endif //CAM_DRYOS
}

#define DEBUG_DISPLAY_NONE 0
#define DEBUG_DISPLAY_PROPS 1
#define DEBUG_DISPLAY_PARAMS 2
#define DEBUG_DISPLAY_TASKS 3
static const char * gui_debug_shortcut_enum(int change, int arg) {
    static const char* modes[]={ "None", "DmpRAM", "Page", "CmpProps"};
	return gui_change_simple_enum(&conf.debug_shortcut_action,change,modes,sizeof(modes)/sizeof(modes[0]));
}

static const char * gui_debug_display_enum(int change, int arg) {
    static const char* modes[]={ "None", "Props", "Params", "Tasks"};
	return gui_change_simple_enum(&conf.debug_display,change,modes,sizeof(modes)/sizeof(modes[0]));
}

static void gui_debug_shortcut(void) {
    static int lastcall = -1;
    int t=get_tick_count();
    if ( lastcall != -1) {
        if (t-lastcall <= 400)
            debug_display_direction = -debug_display_direction;
    }
    lastcall=t;
    switch(conf.debug_shortcut_action) {
        case 1:
            dump_memory();
        break;
        case 2:
            if(conf.debug_display == DEBUG_DISPLAY_TASKS) {
                debug_tasklist_start += debug_display_direction*(TASKLIST_MAX_LINES-2); // a little intentional overlap
                if(debug_tasklist_start >= TASKLIST_NUM_TASKS || debug_tasklist_start < 0)
                    debug_tasklist_start = 0;
            }
            else if (conf.debug_display == DEBUG_DISPLAY_PROPS || conf.debug_display == DEBUG_DISPLAY_PARAMS) {
                conf.debug_propcase_page += debug_display_direction*1;
                if(conf.debug_propcase_page > 128 || conf.debug_propcase_page < 0)
                    conf.debug_propcase_page = 0;
            }
        break;
        case 3:
            gui_compare_props(1);
        break;
    }
}

//-------------------------------------------------------------------
#endif

#if CAM_MULTIPART
void card_break_proc(unsigned int btn){
 if (btn==MBOX_BTN_YES) create_partitions();
}


#ifdef OPT_DEBUGGING
static void gui_menuproc_break_card(int arg){
 gui_mbox_init(LANG_WARNING, LANG_PARTITIONS_CREATE_WARNING, MBOX_BTN_YES_NO|MBOX_DEF_BTN2|MBOX_TEXT_CENTER, card_break_proc);
}
#endif

static void gui_menuproc_swap_partitions(int arg){
 if (get_part_count()<2) gui_mbox_init(LANG_ERROR, LANG_ONLY_ONE_PARTITION, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
 else
 	{
 		swap_partitions();
 		gui_mbox_init(LANG_INFORMATION, LANG_SOKOBAN_MSG_FINISH_TITLE, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
 	}
}
#endif

//-------------------------------------------------------------------
static volatile enum Gui_Mode gui_mode;
static volatile int gui_restore;
static volatile int gui_in_redraw;
static int gui_splash, gui_splash_mode;
static char osd_buf[32];
#ifdef OPTIONS_AUTOSAVE
static Conf old_conf;
#endif

//-------------------------------------------------------------------
void gui_init()
{

    gui_mode = GUI_MODE_NONE;
    gui_restore = 0;
    gui_in_redraw = 0;
    if (conf.start_sound>0)
    {
    	play_sound(4);
    }
    gui_splash = (conf.splash_show)?SPLASH_TIME:0;
    user_menu_restore();
    gui_lang_init();
    draw_init();

    exposition_thresh = screen_size/500;
    voltage_step = (conf.batt_step_25)?25:1;
    load_bad_pixels_list("A/CHDK/badpixel");
    load_bad_pixels_list("A/CHDK/badpixel.txt");
#ifdef OPT_CURVES
	// initialize curves, loading files if required by current mode
	curve_init_mode();
#endif
#if ZOOM_OVERRIDE
// reyalp - need to do this in capt_seq
//		if (conf.zoom_override) shooting_set_zoom(conf.zoom_override_value);
#endif
}

//-------------------------------------------------------------------
#ifdef OPT_CURVES
static void gui_load_curve_selected(const char *fn) {
	if (fn) {
		// TODO we could sanity check here, but curve_set_type should fail gracefullish
		strcpy(conf.curve_file,fn);
		if(conf.curve_enable == 1)
			curve_init_mode();
	}
}

//-------------------------------------------------------------------
void gui_load_curve(int arg) {
    DIR   *d;
    char  *path = CURVE_DIR;

    // if exists CURVE_DIR go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_STR_SELECT_CURVE_FILE, path, gui_load_curve_selected);
}

#endif
//-------------------------------------------------------------------
enum Gui_Mode gui_get_mode() {
    return gui_mode;
}

//-------------------------------------------------------------------
void gui_set_mode(enum Gui_Mode mode) {
    gui_mode = mode;
}

//-------------------------------------------------------------------
void gui_force_restore() {
    gui_restore = gui_in_redraw;
}

static void gui_handle_splash(void) {
	static char *logo = NULL;
    static int logo_size;
    if (gui_splash) {
		static int need_logo=1; // don't use logo ptr, since we don't want to keep re-trying
		if(need_logo) {
    		const char *logo_name="A/CHDK/DATA/logo.dat";
            FILE *fd;
            struct stat st;
			need_logo=0;
            if (stat(logo_name,&st) == 0) {
				logo_size=st.st_size;
				logo=malloc(logo_size);
				if(logo) {
					fd = fopen(logo_name, "rb");
					if(fd){
						fread(logo,1,logo_size,fd);
						fclose(fd);
					}
					else {
						free(logo);
						logo=NULL;
					}
            	}
			}
		}
        if (gui_splash>(SPLASH_TIME-4)) {
            gui_draw_splash(logo,logo_size);
           //	conf.show_osd = 0;
        } else if (gui_splash==1 && (mode_get()&MODE_MASK) == gui_splash_mode && (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT)) {
            draw_restore();
           // conf.show_osd = 1; //had to uncomment in order to fix a bug with disappearing osd...
        }
        --gui_splash;
		if(!gui_splash) {
			free(logo);
		}
    }
}

//-------------------------------------------------------------------
void gui_redraw()
{
    enum Gui_Mode gui_mode_old;
    static int show_md_grid=0;

	gui_handle_splash();

    gui_in_redraw = 1;
    gui_mode_old = gui_mode;

    #if CAM_USES_ASPECT_CORRECTION //nandoide sept-2009
    //the different modes arises because games are designed on a 360x240 basis and are difficult to downscale to 320x240
    if (gui_mode == GUI_MODE_REVERSI || gui_mode == GUI_MODE_SOKOBAN || gui_mode == GUI_MODE_4WINS || gui_mode == GUI_MODE_MASTERMIND) {
      draw_set_environment(aspect_xcorrection_games_360, aspect_ycorrection_games_360, GAMES_SCREEN_WIDTH, GAMES_SCREEN_HEIGHT);
   } else { //default
//      draw_set_environment(NULL, NULL, SCREENX, SCREENY);
      draw_set_environment(NULL, NULL, vid_get_bitmap_screen_width(), vid_get_bitmap_screen_height());
   }
    #endif
    switch (gui_mode) {
        case GUI_MODE_MENU:
            gui_menu_draw();
//            draw_txt_string(20, 14, "<CNF>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            break;
        case GUI_MODE_ALT:
            gui_draw_osd();
            draw_txt_string(20, 14, "<ALT>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
#ifdef OPT_SCRIPTING
            if ((mode_get()&MODE_MASK) == MODE_REC) {
                draw_txt_string(0, 14, script_title, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
                if (state_kbd_script_run) show_md_grid=5;
                if (show_md_grid) {
                    --show_md_grid;
                    md_draw_grid();
                }
            }
#endif
            console_draw();
            break;
        case GUI_MODE_NONE:
            gui_draw_osd();
            break;
        case GUI_MODE_PALETTE:
            gui_palette_draw();
            break;
        case GUI_MODE_MBOX:
            gui_mbox_draw();
            break;
#ifdef OPT_GAME_REVERSI
        case GUI_MODE_REVERSI:
            gui_reversi_draw();
            break;
#endif
#ifdef OPT_GAME_SOKOBAN
        case GUI_MODE_SOKOBAN:
            gui_sokoban_draw();
            break;
#endif
#ifdef OPT_GAME_CONNECT4
        case GUI_MODE_4WINS:
            gui_4wins_draw();
            break;
#endif
#ifdef OPT_GAME_MASTERMIND
        case GUI_MODE_MASTERMIND:
            gui_mastermind_draw();
            break;
#endif
#ifdef OPT_DEBUGGING
        case GUI_MODE_DEBUG:
            gui_debug_draw();
            break;
#endif
        case GUI_MODE_FSELECT:
            gui_fselect_draw();
            break;
#ifdef OPT_TEXTREADER
        case GUI_MODE_READ:
            gui_read_draw();
            break;
#endif
        case GUI_MODE_OSD:
            gui_osd_draw();
//            draw_txt_string(20, 14, "<OSD>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            break;
#ifdef OPT_CALENDAR
        case GUI_MODE_CALENDAR:
            gui_calendar_draw();
            break;
#endif
#ifdef OPT_DEBUGGING
        case GUI_MODE_BENCH:
            gui_bench_draw();
            break;
#endif
        case GUI_MODE_MPOPUP:
            gui_mpopup_draw();
            break;
        default:
            break;
    }

    gui_in_redraw = 0;
    if ((gui_mode_old != gui_mode && (gui_mode_old != GUI_MODE_NONE && gui_mode_old != GUI_MODE_ALT) && (gui_mode != GUI_MODE_MBOX && gui_mode != GUI_MODE_MPOPUP)) || gui_restore) {
        gui_restore = 0;
        if (gui_mode != GUI_MODE_REVERSI && gui_mode != GUI_MODE_SOKOBAN && gui_mode != GUI_MODE_4WINS && gui_mode != GUI_MODE_MASTERMIND)
            draw_restore();
    }
}

#ifdef OPTIONS_AUTOSAVE
//-------------------------------------------------------------------
static inline void conf_store_old_settings() {
    old_conf=conf;
}

//-------------------------------------------------------------------
static inline int conf_save_new_settings_if_changed() {
    if (memcmp(&old_conf, &conf, sizeof(Conf)) != 0) {
		user_menu_save();
        conf_save();
        conf_store_old_settings();
        return 1;
    }
    return 0;
}
#endif


//-------------------------------------------------------------------
void gui_kbd_process()
{
    int clicked_key;

    if (kbd_is_key_clicked(KEY_MENU)){
        switch (gui_mode) {
            case GUI_MODE_ALT:
				if (conf.user_menu_as_root && (conf.user_menu_enable != 0)) {
				if (kbd_is_key_pressed(KEY_SHOOT_HALF))
					gui_menu_init(&root_menu);
				else
                gui_menu_init(&user_submenu);
				}
				else {
				if ((conf.user_menu_enable != 0) && kbd_is_key_pressed(KEY_SHOOT_HALF))
					gui_menu_init(&user_submenu);
				else
                gui_menu_init(&root_menu);
				}
                gui_mode = GUI_MODE_MENU;
                draw_restore();
                break;
            case GUI_MODE_MENU:
#ifdef OPTIONS_AUTOSAVE
                conf_save_new_settings_if_changed();
#endif
				if (gui_user_menu_flag) {
	                gui_mode = GUI_MODE_MENU;
					gui_user_menu_flag = 0;
					gui_menu_init(&root_menu);
				}
				else
                gui_mode = GUI_MODE_ALT;
                draw_restore();
                break;
            case GUI_MODE_PALETTE:
            case GUI_MODE_REVERSI:
            case GUI_MODE_SOKOBAN:
            case GUI_MODE_4WINS:
			case GUI_MODE_MASTERMIND:
#ifdef OPT_DEBUGGING
            case GUI_MODE_DEBUG:
#endif
            case GUI_MODE_OSD:
#ifdef OPT_CALENDAR
            case GUI_MODE_CALENDAR:
#endif
            case GUI_MODE_BENCH:
                draw_restore();
                gui_mode = GUI_MODE_MENU;
                break;
            case GUI_MODE_FSELECT:
                gui_fselect_kbd_process();
                break;
#ifdef OPT_TEXTREADER
            case GUI_MODE_READ:
                gui_read_kbd_process();
                draw_restore();
                gui_mode = GUI_MODE_MENU;
                break;
#endif
            default:
                break;
        }
        return;
    }

    switch (gui_mode) {
        case GUI_MODE_ALT:
            if (kbd_is_key_clicked(SHORTCUT_TOGGLE_RAW)) {
                if (conf.debug_shortcut_action > 0) {
#ifdef OPT_DEBUGGING
					gui_debug_shortcut();
#endif
}
#if !CAM_HAS_ERASE_BUTTON && CAM_CAN_SD_OVERRIDE
                if (!shooting_get_common_focus_mode())
#else
				else
#endif
				   {conf.save_raw = !conf.save_raw;
                    draw_restore();
                   }
#if !CAM_HAS_ERASE_BUTTON && CAM_CAN_SD_OVERRIDE
				else {
   #if CAM_HAS_ZOOM_LEVER
               conf.subj_dist_override_value=MAX_DIST;
               shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
   #else
               if (conf.subj_dist_override_koef==4)
                  gui_subj_dist_override_koef_enum(-3,0);
               else
                  gui_subj_dist_override_koef_enum(1,0);
   #endif
				}
#endif
#ifdef OPT_SCRIPTING
            } else if (kbd_is_key_clicked(KEY_SET)) {
                gui_menu_init(&script_submenu);
                gui_mode = GUI_MODE_MENU;
                draw_restore();
#endif
            } else {
#if !CAM_HAS_MANUAL_FOCUS && CAM_CAN_SD_OVERRIDE
	          	if (kbd_is_key_clicked(SHORTCUT_MF_TOGGLE)) {
			      if (conf.subj_dist_override_koef>0)
				     conf.subj_dist_override_koef=0;
			      else conf.subj_dist_override_koef=1;
			      draw_restore();
			     }
                else if (shooting_get_common_focus_mode())
#elif CAM_CAN_SD_OVERRIDE
               if (shooting_get_common_focus_mode())
#endif

#if CAM_CAN_SD_OVERRIDE
			  {
  #if CAM_HAS_ZOOM_LEVER
				if (kbd_is_key_clicked(KEY_RIGHT)) {
				  gui_subj_dist_override_koef_enum(1,0);
    #if !CAM_HAS_MANUAL_FOCUS
                  if (conf.subj_dist_override_koef==0) conf.subj_dist_override_koef=1;
    #endif
                  shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
				  }
				else if (kbd_is_key_clicked(KEY_LEFT))
				  {
				  gui_subj_dist_override_koef_enum(-1,0);
    #if !CAM_HAS_MANUAL_FOCUS
                  if (conf.subj_dist_override_koef==0) conf.subj_dist_override_koef=1;
    #endif
                  shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
				  }
				else if (kbd_is_key_clicked(SHORTCUT_SET_INFINITY))
 				  {
				  conf.subj_dist_override_value=MAX_DIST;
                  shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
				  }
				else
  #endif
				if (kbd_is_key_clicked(SHORTCUT_SET_HYPERFOCAL))
				  {
				  int m=mode_get()&MODE_SHOOTING_MASK;
				  if ((m==MODE_M) || (m==MODE_AV))
				    conf.subj_dist_override_value=(int)shooting_get_hyperfocal_distance_f(shooting_get_aperture_from_av96(shooting_get_user_av96()),get_focal_length(lens_get_zoom_point()));
				  else conf.subj_dist_override_value=(int)shooting_get_hyperfocal_distance();
                  shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
				  }
				else
                  switch (kbd_get_autoclicked_key()) {
  #if CAM_HAS_ZOOM_LEVER
                    case KEY_ZOOM_IN:
  #else
                    case KEY_RIGHT:
  #endif
                        gui_subj_dist_override_value_enum(1,0);
                        shooting_set_focus(shooting_get_subject_distance_override_value(),SET_NOW);
                        break;
  #if CAM_HAS_ZOOM_LEVER
                    case KEY_ZOOM_OUT:
  #else
                    case KEY_LEFT:
  #endif
                        gui_subj_dist_override_value_enum(-1,0);
                        shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
                        break;
            	  }
              }
#endif
            }
            break;
    	case GUI_MODE_MENU:
            gui_menu_kbd_process();
            break;
    	case GUI_MODE_PALETTE:
            gui_palette_kbd_process();
            break;
    	case GUI_MODE_MBOX:
            gui_mbox_kbd_process();
            break;
#ifdef OPT_GAME_REVERSI
    	case GUI_MODE_REVERSI:
            gui_reversi_kbd_process();
            break;
#endif
#ifdef OPT_GAME_SOKOBAN
    	case GUI_MODE_SOKOBAN:
            gui_sokoban_kbd_process();
            break;
#endif
#ifdef OPT_GAME_CONNECT4
    	case GUI_MODE_4WINS:
            gui_4wins_kbd_process();
            break;
#endif
#ifdef OPT_GAME_MASTERMIND
    	case GUI_MODE_MASTERMIND:
            gui_mastermind_kbd_process();
            break;
#endif
#ifdef OPT_DEBUGGING
    	case GUI_MODE_DEBUG:
            gui_debug_kbd_process();
            break;
#endif
    	case GUI_MODE_FSELECT:
            gui_fselect_kbd_process();
            break;
#ifdef OPT_TEXTREADER
    	case GUI_MODE_READ:
            gui_read_kbd_process();
            break;
#endif
    	case GUI_MODE_OSD:
            gui_osd_kbd_process();
            break;
#ifdef OPT_CALENDAR
    	case GUI_MODE_CALENDAR:
            gui_calendar_kbd_process();
            break;
#endif
#ifdef OPT_DEBUGGING
    	case GUI_MODE_BENCH:
            gui_bench_kbd_process();
            break;
#endif
        case GUI_MODE_MPOPUP:
            gui_mpopup_kbd_process();
             break;
        default:
            break;
    }
}

//-------------------------------------------------------------------
void gui_kbd_enter()
{
    // XXX set custom palette
#ifdef OPTIONS_AUTOSAVE
    conf_store_old_settings();
#endif
    gui_mode = GUI_MODE_ALT;

	conf_update_prevent_shutdown();

    vid_turn_off_updates();

	gui_user_menu_flag = 0;
	if (conf.user_menu_enable == 2) {
		gui_menu_init(&user_submenu);
		gui_mode = GUI_MODE_MENU;
		draw_restore();
		gui_user_menu_flag = 1;
	}

}

//-------------------------------------------------------------------
void gui_kbd_leave()
{
    // XXX restore palette
#ifdef OPTIONS_AUTOSAVE
    conf_save_new_settings_if_changed();
#endif
#ifdef OPT_UBASIC
    ubasic_error = UBASIC_E_NONE;
#endif
    draw_restore();
    if (gui_mode == GUI_MODE_READ && !rbf_load(conf.menu_rbf_file))
        rbf_load_from_8x16(current_font);
    rbf_set_codepage(FONT_CP_WIN);
    vid_turn_on_updates();
    gui_mode = GUI_MODE_NONE;

	conf_update_prevent_shutdown();
}
//-------------------------------------------------------------------

void other_kbd_process(){
 int key;
#if CAM_AF_SCAN_DURING_VIDEO_RECORD

 if (movie_status==VIDEO_RECORD_IN_PROGRESS) {
  if (kbd_is_key_clicked(conf.video_af_key)) MakeAFScan();
 }

#endif

#if CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
 // return from digital to optical zoom in video
#if CAM_HAS_ZOOM_LEVER
   key=KEY_ZOOM_OUT;
#else
   key=KEY_DOWN;
#endif
    if (conf.unlock_optical_zoom_for_video && (movie_status==VIDEO_RECORD_IN_PROGRESS) &&  kbd_is_key_clicked(key)){
     short x;
     get_property_case(PROPCASE_DIGITAL_ZOOM_STATE, &x, sizeof(x));
     if (x) {
      get_property_case(PROPCASE_DIGITAL_ZOOM_POSITION, &x, sizeof(x));
#if defined (CAMERA_s90) || defined (CAMERA_s95)
	  if (x==0) zoom_status=ZOOM_OPTICAL_MAX; //ERR99: No zoom back from digital to optical zoom possible if set to medium
#elif defined (CAMERA_sx30)	|| defined (CAMERA_g12)		// can't find, crashes camera *******
#else
	  if (x==0) zoom_status=ZOOM_OPTICAL_MEDIUM;
#endif

     }
    }
#endif

#if CAM_EV_IN_VIDEO
 if ((movie_status==VIDEO_RECORD_IN_PROGRESS) && !kbd_is_key_pressed(KEY_SHOOT_HALF)){
  #if CAM_HAS_ERASE_BUTTON
  if (kbd_is_key_clicked(KEY_ERASE)){
  #else
  #if !defined (CAMERA_a480)
  if (kbd_is_key_clicked(KEY_DISPLAY)){
  #else
  if (kbd_is_key_clicked(KEY_MENU)){
  #endif
  #endif
   set_ev_video_avail(!get_ev_video_avail());
  }
  if (get_ev_video_avail()) {
   if (kbd_is_key_clicked(KEY_LEFT)) {
    set_ev_video(get_ev_video()-1);
   }
   if (kbd_is_key_clicked(KEY_RIGHT)){
    set_ev_video(get_ev_video()+1);
   }
  }
 }
#endif
}

void gui_draw_debug_vals_osd() {
#ifdef OPT_DEBUGGING
  if (conf.debug_misc_vals_show) {
        //        long v=get_file_counter();
        //	sprintf(osd_buf, "1:%03d-%04d  ", (v>>18)&0x3FF, (v>>4)&0x3FFF);
        //	sprintf(osd_buf, "1:%d, %08X  ", xxxx, eeee);
        
        extern long physw_status[3];
        sprintf(osd_buf, "0:%8x  ", physw_status[0] & ~0x3000d000);
        draw_txt_string(48,  6, osd_buf, conf.osd_color);

        sprintf(osd_buf, "1:%8x  ", physw_status[1] & ~0x0331300e);
        draw_txt_string(48,  7, osd_buf, conf.osd_color);

        sprintf(osd_buf, "2:%8x  ", physw_status[2]);
        draw_txt_string(48,  8, osd_buf, conf.osd_color);

        //      sprintf(osd_buf, "4:%8x  ", vid_get_viewport_fb_d());
        
        sprintf(osd_buf, "u:%8x  ", get_usb_power(1));
        draw_txt_string(48,  9, osd_buf, conf.osd_color);

        sprintf(osd_buf, "1:%8x  ", (void*) (*(int*)conf.mem_view_addr_init));
        draw_txt_string(48, 10, osd_buf, conf.osd_color);

    extern volatile long focus_busy;
        sprintf(osd_buf, "f:%8x  ", focus_busy);
        draw_txt_string(48, 11, osd_buf, conf.osd_color);

    extern volatile long zoom_busy;
        sprintf(osd_buf, "z:%8x  ", zoom_busy);
        draw_txt_string(48, 12, osd_buf, conf.osd_color);

        // some cameras missing zoom_status
        //#if 0
        sprintf(osd_buf, "t:%8x  ", zoom_status);
        draw_txt_string(28, 13, osd_buf, conf.osd_color);
        //#endif

    }
    {
        static char sbuf[100];
        int r,i, p, len;
        if (conf.debug_display == DEBUG_DISPLAY_PROPS){

            for (i=0;i<10;i++){
                r = 0;
                p = conf.debug_propcase_page*10+i;
                get_property_case(p, &r, 4);
                sprintf(sbuf, "%3d: %d              ", p, r);
                sbuf[20]=0;
                draw_string(64,16+16*i,sbuf, conf.osd_color);
            }
        }

        if (conf.debug_display == DEBUG_DISPLAY_PARAMS){
            extern long* FlashParamsTable[];
            char s[30];
            int count;

            for (i=0;i<10;i++){
                r = 0;
                p = conf.debug_propcase_page*10+i;
                if (p>=get_flash_params_count()) {
                    sprintf(sbuf, "%3d: This parameter does not exists", p);
                } else  {
                    len=FlashParamsTable[p][1]>>16;
                    if ((len==1)||(len==2)||(len==4)){
                        get_parameter_data(p, &r, len);
                        sprintf(sbuf, "%3d: %30d :%2d ", p, r,len);
                    }
                    else {
                        if (len>=sizeof(s)) count=sizeof(s)-1; else count=len;
                        get_parameter_data(p, &s, count);
                        s[count]=0;
                        sprintf(sbuf, "%3d: %30s :%2d ", p, s,len);
                    }
                }
                draw_string(16,16+16*i,sbuf, conf.osd_color);
            }
        }
    }

    if(conf.debug_display == DEBUG_DISPLAY_TASKS) {
            gui_debug_draw_tasklist();
    }
#endif
}
//-------------------------------------------------------------------
//extern int xxxx, eeee;
//-------------------------------------------------------------------
void gui_draw_osd() {
    unsigned int m, /*n = 0,*/ mode_photo, mode_video;
    coord x;
#if CAM_SWIVEL_SCREEN
    static int flashlight = 0;
#endif
    static int pressed = 0;
    static int half_disp_press_old=0;
    int half_disp_press;
    int need_restore = 0;
    m = mode_get();

// uncomment if you want debug values always on top
	gui_draw_debug_vals_osd();

#if CAM_SWIVEL_SCREEN
    if (conf.flashlight && (m&MODE_SCREEN_OPENED) && (m&MODE_SCREEN_ROTATED) && (gui_mode==GUI_MODE_NONE /* || gui_mode==GUI_MODE_ALT */)) {
        draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
        flashlight = 1;
    }
    if (flashlight) {
        if ((!((m&MODE_SCREEN_OPENED) && (m&MODE_SCREEN_ROTATED))) || (gui_mode!=GUI_MODE_NONE /* && gui_mode!=GUI_MODE_ALT */)) {
            flashlight = 0;
			need_restore = 1;
        } else {
			return;
		}
    }
#endif

    if (kbd_is_key_pressed(KEY_SHOOT_HALF)) {
        if (kbd_is_key_pressed(SHORTCUT_TOGGLE_ZEBRA)) {
            if (!pressed) {
                conf.zebra_draw = !conf.zebra_draw;
                if (!conf.zebra_draw) {
					need_restore = 1;
                }
                pressed = 1;
            }
        } else if (kbd_is_key_pressed(SHORTCUT_TOGGLE_HISTO)) {
            if (!pressed) {
                if (++conf.show_histo>SHOW_HALF) conf.show_histo=0;
                if (!conf.show_histo) {
					need_restore = 1;
                }
                pressed = 1;
            }
        } else if (kbd_is_key_pressed(SHORTCUT_TOGGLE_OSD)) {
            if (!pressed) {
                conf.show_osd = !conf.show_osd;
                if (!conf.show_osd) {
					need_restore = 1;
                }
                pressed = 1;
            }
        } else if (kbd_is_key_pressed(SHORTCUT_DISABLE_OVERRIDES)) {
             if (!pressed) {
                 if (conf.override_disable < 2) conf.override_disable = !conf.override_disable;
                 if (!conf.show_osd) {
					need_restore = 1;
                 }
                 pressed = 1;
             }
        } else {
            pressed = 0;
        }
    } else {
        pressed = 0;
    }

	// TODO some of the ifs below should probably use this
	mode_video = MODE_IS_VIDEO(m);

    mode_photo = (m&MODE_MASK) == MODE_PLAY ||
                 !( mode_video ||
				 (m&MODE_SHOOTING_MASK)==MODE_STITCH);

    half_disp_press=mode_photo && kbd_is_key_pressed(KEY_SHOOT_HALF) && kbd_is_key_pressed(KEY_DISPLAY);
    if (half_disp_press && ! half_disp_press_old)
		need_restore = 1;
    half_disp_press_old=half_disp_press;

	if (need_restore)
		draw_restore();

    if (half_disp_press)
		return;

	if (gui_osd_draw_zebra(conf.zebra_draw && gui_mode==GUI_MODE_NONE &&
							kbd_is_key_pressed(KEY_SHOOT_HALF) && mode_photo &&
							!state_kbd_script_run)) {// no zebra when script running, to save mem
		return; // if zebra drawn, we're done
	}
#if !CAM_SHOW_OSD_IN_SHOOT_MENU
      if (!(conf.show_osd && (canon_menu_active==(int)&canon_menu_active-4) && (canon_shoot_menu_active==0)))  return;
#else
      if (!(conf.show_osd && (canon_menu_active==(int)&canon_menu_active-4) /*&& (canon_shoot_menu_active==0)*/ ))  return;
#endif


    if ((gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && (
     (kbd_is_key_pressed(KEY_SHOOT_HALF) && ((conf.show_histo==SHOW_HALF)/* || (m&MODE_MASK) == MODE_PLAY*/)) ||
     ((conf.show_histo==SHOW_ALWAYS)  &&  !((m&MODE_MASK) == MODE_PLAY) && (recreview_hold==0))
    ) &&
    (mode_photo || (m&MODE_SHOOTING_MASK)==MODE_STITCH)) {
        gui_osd_draw_histo();
    }

    if ((m&MODE_MASK) == MODE_REC && (recreview_hold==0 || conf.show_osd_in_review) ) {
        if (conf.show_grid_lines) {
            gui_grid_draw_osd(1);
        }
        if ((gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && (((kbd_is_key_pressed(KEY_SHOOT_HALF) || (state_kbd_script_run) || (shooting_get_common_focus_mode())) && (mode_photo || (m&MODE_SHOOTING_MASK)==MODE_STITCH )) || ((mode_video || movie_status > 1) && conf.show_values_in_video) )) {

           if (conf.show_dof!=DOF_DONT_SHOW) gui_osd_calc_dof();

           if (conf.show_dof==DOF_SHOW_IN_DOF) gui_osd_draw_dof();

           if (conf.values_show_real_iso || conf.values_show_market_iso || conf.values_show_ev_seted || conf.values_show_ev_measured || conf.values_show_bv_measured || conf.values_show_bv_seted || conf.values_show_overexposure || conf.values_show_canon_overexposure || conf.values_show_luminance) gui_osd_calc_expo_param();
        }
        if (conf.show_state) gui_osd_draw_state();
        if (conf.save_raw && conf.show_raw_state && !mode_video && (!kbd_is_key_pressed(KEY_SHOOT_HALF))) gui_osd_draw_raw_info();

	    if ((conf.show_values==SHOW_ALWAYS && mode_photo) || ((mode_video || movie_status > 1)&& conf.show_values_in_video) || ((kbd_is_key_pressed(KEY_SHOOT_HALF) || (recreview_hold==1)) && (conf.show_values==SHOW_HALF)))
		   gui_osd_draw_values(1);
        else if  (shooting_get_common_focus_mode() && mode_photo && conf.show_values && !(conf.show_dof==DOF_SHOW_IN_DOF) )
           gui_osd_draw_values(2);
	    else if  (conf.show_values==SHOW_HALF)
		   gui_osd_draw_values(0);
    }


    if ((recreview_hold==0) &&  (!kbd_is_key_pressed(KEY_SHOOT_HALF) &&  (  ((m&MODE_MASK) == MODE_REC) || (!((m&MODE_MASK) == MODE_REC) &&  !((conf.hide_osd == 1) || (conf.hide_osd == 3)) )) && !(((conf.hide_osd == 2) || (conf.hide_osd == 3))&& (shooting_get_prop(PROPCASE_DISPLAY_MODE) == 1))))   {
        gui_batt_draw_osd();
        gui_space_draw_osd();
        if (conf.fast_ev && !mode_video && (m&MODE_MASK) == MODE_REC ) gui_osd_draw_ev();
    }

    if ((conf.show_clock) && (recreview_hold==0) &&  ((!kbd_is_key_pressed(KEY_SHOOT_HALF) &&  (  ((m&MODE_MASK) == MODE_REC) || (!((m&MODE_MASK) == MODE_REC) &&  !((conf.hide_osd == 1) || (conf.hide_osd == 3)) )) && !(((conf.hide_osd == 2) || (conf.hide_osd == 3))&& (shooting_get_prop(PROPCASE_DISPLAY_MODE) == 1)))|| (conf.clock_halfpress==0) )) {
        gui_osd_draw_clock(0,0,0);
    }
    else if ((conf.show_clock) && (recreview_hold==0) &&  kbd_is_key_pressed(KEY_SHOOT_HALF) && conf.clock_halfpress==1) {
        gui_osd_draw_seconds();
    }

    if ((conf.show_temp>0) && (recreview_hold==0) &&  ((!kbd_is_key_pressed(KEY_SHOOT_HALF) &&  (  ((m&MODE_MASK) == MODE_REC) || (!((m&MODE_MASK) == MODE_REC) &&  !((conf.hide_osd == 1) || (conf.hide_osd == 3)) )) && !(((conf.hide_osd == 2) || (conf.hide_osd == 3))&& (shooting_get_prop(PROPCASE_DISPLAY_MODE) == 1)) )|| (conf.clock_halfpress==0) )) {
        gui_osd_draw_temp();
    }
    if (conf.show_movie_time > 0 && (mode_video || movie_status > 1)) {
        gui_osd_draw_movie_time_left();
    }

#if CAM_DRAW_EXPOSITION
    if (gui_mode==GUI_MODE_NONE && kbd_is_key_pressed(KEY_SHOOT_HALF) && ((m&MODE_MASK)==MODE_REC) && ((m&MODE_SHOOTING_MASK))!=MODE_VIDEO_STD && (m&MODE_SHOOTING_MASK)!=MODE_VIDEO_COMPACT) {
     strcpy(osd_buf,shooting_get_tv_str());
     strcat(osd_buf,"\"  F");
     strcat(osd_buf,shooting_get_av_str());
     draw_txt_string(22-strlen(osd_buf)/2, 14, osd_buf, conf.osd_color);
    }
#endif

#if CAM_EV_IN_VIDEO
    if (movie_status==VIDEO_RECORD_IN_PROGRESS) gui_osd_draw_ev_video(get_ev_video_avail());
#endif

	gui_draw_debug_vals_osd();

#ifdef OPT_UBASIC
    if (ubasic_error){
	const char *msg;
        if (ubasic_error >= UBASIC_E_ENDMARK) {
            msg = ubasic_errstrings[UBASIC_E_UNKNOWN_ERROR];
        } else {
	    msg = ubasic_errstrings[ubasic_error];
	}
	sprintf(osd_buf, "uBASIC:%d %s ", ubasic_linenumber(), msg);
	draw_txt_string(0, 0, osd_buf, MAKE_COLOR(COLOR_RED, COLOR_YELLOW));
    }
#endif
}

#ifndef OPTIONS_AUTOSAVE
//-------------------------------------------------------------------
void gui_menuproc_save(int arg)
{
    conf_save();
}
#endif

//-------------------------------------------------------------------
static void gui_menuproc_reset_selected(unsigned int btn) {
    if (btn==MBOX_BTN_YES)
        conf_load_defaults();
}

void gui_menuproc_reset(int arg)
{
    gui_mbox_init(LANG_MSG_RESET_OPTIONS_TITLE,
                  LANG_MSG_RESET_OPTIONS_TEXT,
                  MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER|MBOX_BTN_YES_NO|MBOX_DEF_BTN2, gui_menuproc_reset_selected);
}

//-------------------------------------------------------------------
void gui_draw_palette(int arg) {
    draw_restore();
    gui_palette_init(PALETTE_MODE_DEFAULT, 0x00, NULL);
    gui_mode = GUI_MODE_PALETTE;
}

//-------------------------------------------------------------------
void gui_show_build_info(int arg) {
    static char buf[192];
    static char comp[64];

#ifdef __GNUC__
# ifndef __GNUC_PATCHLEVEL__
# define __GNUC_PATCHLEVEL 0
# endif
    sprintf(comp, "GCC %d.%d.%d", __GNUC__ ,__GNUC_MINOR__,__GNUC_PATCHLEVEL__ );
#else
    sprintf(comp, "UNKNOWN" );
#endif
    sprintf(buf, lang_str(LANG_MSG_BUILD_INFO_TEXT), HDK_VERSION, BUILD_NUMBER, __DATE__, __TIME__, PLATFORM, PLATFORMSUB, comp);
gui_mbox_init(LANG_MSG_BUILD_INFO_TITLE, (int)buf, MBOX_FUNC_RESTORE|MBOX_TEXT_LEFT, NULL);
}

//-------------------------------------------------------------------
void gui_show_memory_info(int arg) {
    static char buf[96];    // buffer size was 64, size increased for none english language

    sprintf(buf, lang_str(LANG_MSG_MEMORY_INFO_TEXT), core_get_free_memory(), MEMISOSIZE, &_start, &_end);
    gui_mbox_init(LANG_MSG_MEMORY_INFO_TITLE, (int)buf, MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
}

//-------------------------------------------------------------------
#ifdef OPT_GAME_REVERSI
void gui_draw_reversi(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE,
                      MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
        return;
    }

    #if CAM_USES_ASPECT_CORRECTION //nandoide sept-2009
      draw_set_environment(aspect_xcorrection_games_360, aspect_ycorrection_games_360, GAMES_SCREEN_WIDTH, GAMES_SCREEN_HEIGHT);
    #endif
    gui_mode = GUI_MODE_REVERSI;
    gui_reversi_init();
}
#endif

//-------------------------------------------------------------------
#ifdef OPT_GAME_SOKOBAN
void gui_draw_sokoban(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE,
                      MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
        return;
    }
    #if CAM_USES_ASPECT_CORRECTION //nandoide sept-2009
      draw_set_environment(aspect_xcorrection_games_360, aspect_ycorrection_games_360, GAMES_SCREEN_WIDTH, GAMES_SCREEN_HEIGHT);
    #endif
    if ( gui_sokoban_init() )
        gui_mode = GUI_MODE_SOKOBAN;
}
#endif
//-------------------------------------------------------------------
#ifdef OPT_GAME_CONNECT4
void gui_draw_4wins(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE,
                      MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
        return;
    }
    #if CAM_USES_ASPECT_CORRECTION //nandoide sept-2009
      draw_set_environment(aspect_xcorrection_games_360, aspect_ycorrection_games_360, GAMES_SCREEN_WIDTH, GAMES_SCREEN_HEIGHT);
    #endif
    if ( gui_4wins_init() )
        gui_mode = GUI_MODE_4WINS;
}
#endif
//-------------------------------------------------------------------
#ifdef OPT_GAME_MASTERMIND
void gui_draw_mastermind(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE,
                      MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
        return;
    }
    #if CAM_USES_ASPECT_CORRECTION //nandoide sept-2009
     draw_set_environment(aspect_xcorrection_games_360, aspect_ycorrection_games_360, GAMES_SCREEN_WIDTH, GAMES_SCREEN_HEIGHT);
    #endif
   if ( gui_mastermind_init() )
        gui_mode = GUI_MODE_MASTERMIND;
}
#endif
//-------------------------------------------------------------------
#ifdef OPT_DEBUGGING
void gui_draw_debug(int arg) {
//    gui_debug_init(0x2510);
//    gui_debug_init(0x127E0);
//    gui_debug_init(0x7F5B8);
//    gui_debug_init(malloc(16));
    gui_debug_init((void*)conf.mem_view_addr_init);
}
#endif
//-------------------------------------------------------------------
#ifdef OPT_DEBUGGING
void gui_draw_bench(int arg) {
    gui_mode = GUI_MODE_BENCH;
    gui_bench_init();
}
#endif
//-------------------------------------------------------------------

void gui_draw_splash(char* logo, int logo_size) {
    coord w, h, x, y;
    static const char *text[] = {
        "CHDK Firmware '" HDK_VERSION " " BUILD_NUMBER "'" ,
        "Build: " __DATE__ " " __TIME__ ,
        "Camera: " PLATFORM " - " PLATFORMSUB };
    int i, l;
    color cl = MAKE_COLOR(COLOR_RED, COLOR_WHITE);

    gui_splash_mode = (mode_get()&MODE_MASK);

    h=sizeof(text)/sizeof(text[0])*FONT_HEIGHT+8;
    w=0;
    for (i=0; i<sizeof(text)/sizeof(text[0]); ++i) {
        l=strlen(text[i]);
        if (l>w) w=l;
    }
    w=w*FONT_WIDTH+10;

    x = (screen_width-w)>>1; y = ((screen_height-h)>>1) + 20;
    draw_filled_round_rect(x, y, x+w, y+h, MAKE_COLOR(COLOR_RED, COLOR_RED));
    for (i=0; i<sizeof(text)/sizeof(text[0]); ++i) {
        draw_string(x+((w-strlen(text[i])*FONT_WIDTH)>>1), y+i*FONT_HEIGHT+4, text[i], cl);
    }
    if(logo){
      int pos;
      int mx=0;
      int my=0;
      int offset_x = (screen_width-150)>>1;
      int offset_y = ((screen_height-84)>>1) - 42;
      const color color_lookup[8] = {COLOR_BLACK,
	  								COLOR_SPLASH_RED/*0x2E redish*/,
									COLOR_RED,
									COLOR_GREY /*0x3D*/,
									COLOR_SPLASH_GREY /*0x1F*/,
									COLOR_SPLASH_PINK /*0x21 pinkish*/,
									COLOR_TRANSPARENT /*0x00*/,
									COLOR_WHITE /*0x11*/};
      for(pos=0; pos<logo_size; pos++){
          char data = logo[pos];
          color c = color_lookup[(data>>5) & 0x07];
          for(i=0; i<(data&0x1F)+1; i++){
              if (c!=0x00){
                  draw_pixel(offset_x+mx,offset_y+my,c);
              }
              if (mx==149){
                  mx=0;
                  my++;
              }else{
                  mx++;
              }
          }
      }
    }
}

//-------------------------------------------------------------------
void gui_draw_fselect(int arg) {
    gui_fselect_init(LANG_STR_FILE_BROWSER, "A", NULL);
}

//-------------------------------------------------------------------
static void gui_grid_lines_load_selected(const char *fn) {
    if (fn)
        grid_lines_load(fn);
}
void gui_grid_lines_load(int arg) {
    DIR   *d;
    char  *path="A/CHDK/GRIDS";

    // if exists "A/CHDK/GRIDS" go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_STR_SELECT_GRID_FILE, path, gui_grid_lines_load_selected);
}

//-------------------------------------------------------------------
void gui_draw_osd_le(int arg) {
    gui_mode = GUI_MODE_OSD;
    gui_osd_init();
}

//-------------------------------------------------------------------
#ifdef OPT_TEXTREADER
static void gui_draw_read_selected(const char *fn) {
    if (fn) {
        if (!rbf_load(conf.reader_rbf_file))
            rbf_load_from_8x16(current_font);
        rbf_set_codepage(conf.reader_codepage);
        gui_mode = GUI_MODE_READ;
        gui_read_init(fn);
    }
}
void gui_draw_read(int arg) {
    DIR   *d;
    char  *path="A/CHDK/BOOKS";

    // if exists "A/CHDK/BOOKS" go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }
    gui_fselect_init(LANG_STR_SELECT_TEXT_FILE, path, gui_draw_read_selected);
}

//-------------------------------------------------------------------
void gui_draw_read_last(int arg) {
    int fd;

    fd = open(conf.reader_file, O_RDONLY, 0777);
    if (fd >= 0) {
        close(fd);
        gui_draw_read_selected(conf.reader_file);
    } else {
        gui_draw_read(arg);
    }
}
#endif

//-------------------------------------------------------------------
void gui_menuproc_mkbootdisk(int arg) {
    mark_filesystem_bootable();
}

#ifdef OPT_EDGEOVERLAY
static void gui_load_edge_selected( const char* fn ) {
    if( fn )
	load_edge_overlay(fn);
}

void gui_menuproc_edge_save(int arg) {
    save_edge_overlay();
}

void gui_menuproc_edge_load(int arg) {
    DIR   *d;
    char  *path = EDGE_SAVE_DIR;
    const char* fn;

    // if exists, go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_MENU_EDGE_LOAD, path, gui_load_edge_selected);
}
#endif

//-------------------------------------------------------------------
#ifdef OPT_CALENDAR
void gui_draw_calendar(int arg) {
    gui_mode = GUI_MODE_CALENDAR;
    gui_calendar_init();
}
#endif
//-------------------------------------------------------------------
static void gui_draw_rbf_selected(const char *fn) {
    if (fn) {
        strcpy(conf.reader_rbf_file, fn);
    }
}
#ifdef OPT_TEXTREADER
void gui_draw_load_rbf(int arg) {
    DIR   *d;
    char  *path="A/CHDK/FONTS";

    // if exists "A/CHDK/FONTS" go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_STR_SELECT_FONT_FILE, path, gui_draw_rbf_selected);
}
#endif
//-------------------------------------------------------------------
static void gui_draw_menu_rbf_selected(const char *fn) {
    if (fn) {
        strcpy(conf.menu_rbf_file, fn);
        if (!rbf_load(conf.menu_rbf_file))
            rbf_load_from_8x16(current_font);
        rbf_set_codepage(FONT_CP_WIN);
        gui_menu_init(NULL);
    }
}
void gui_draw_load_menu_rbf(int arg) {
    DIR   *d;
    char  *path="A/CHDK/FONTS";

    // if exists "A/CHDK/FONTS" go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_STR_SELECT_FONT_FILE, path, gui_draw_menu_rbf_selected);
}

//-------------------------------------------------------------------
static void gui_draw_symbol_rbf_selected(const char *fn) {
    if (fn) {
        strcpy(conf.menu_symbol_rbf_file, fn);
        if(!rbf_load_symbol(conf.menu_symbol_rbf_file)) conf.menu_symbol_enable=0;		//AKA
        gui_menu_init(NULL);
    }
}
void gui_draw_load_symbol_rbf(int arg) {
    DIR   *d;
    char  *path="A/CHDK/SYMBOLS";

    // if exists "A/CHDK/FONTS" go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_STR_SELECT_SYMBOL_FILE, path, gui_draw_symbol_rbf_selected);
}

//-------------------------------------------------------------------
static void gui_draw_lang_selected(const char *fn) {
    if (fn) {
        strcpy(conf.lang_file, fn);
        lang_load_from_file(conf.lang_file);
        gui_menu_init(NULL);
    }
}
void gui_draw_load_lang(int arg) {
    DIR   *d;
    char  *path="A/CHDK/LANG";

    // if exists "A/CHDK/LANG" go into
    d=opendir(path);
    if (d) {
        closedir(d);
    } else {
        path="A";
    }

    gui_fselect_init(LANG_STR_SELECT_LANG_FILE, path, gui_draw_lang_selected);
}

int find_mnu(CMenu *curr_menu, int mnu, int count)
{
	int gui_menu_curr_item;

	gui_menu_curr_item = 0;
	while(curr_menu->menu[gui_menu_curr_item].text) {
		if (curr_menu->menu[gui_menu_curr_item].text == mnu){
			user_submenu_items[count] = curr_menu->menu[gui_menu_curr_item];
			return 1;
		}
		if ((curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK) == MENUITEM_SUBMENU)
			if (curr_menu->menu[gui_menu_curr_item].text != LANG_MENU_USER_MENU)
				if (find_mnu((CMenu*)(curr_menu->menu[gui_menu_curr_item].value), mnu, count)) return 1;
		gui_menu_curr_item++;
	}
	return 0;
}

void user_menu_save() {
    int x;
	for (x=0; x<USER_MENU_ITEMS; x++) {
		/*
		 * First entry in user_submenu_items is reserved for the "Main Menu"
 		 * conf.user_menu_vars only traks/saves the real user entries.
 		 */
 		conf.user_menu_vars[x] = user_submenu_items[x+1].text;
	}
}

void user_menu_restore() {
     int x;
 	for (x=0; x<USER_MENU_ITEMS; x++) {
 		/*
 		 * First entry in user_submenu_items is reserved for the "Main Menu"
 		 * conf.user_menu_vars only traks/saves the real user entries.
 		 */
 		find_mnu(&root_menu, conf.user_menu_vars[x], x+1);
 	}
}

#ifdef OPT_EDGEOVERLAY
static const char* gui_edge_pano_enum(int change, int arg)
{
    static const char* modes[]={ "Off", "Right", "Down", "Left", "Up", "Free"};
	return gui_change_simple_enum(&conf.edge_overlay_pano,change,modes,sizeof(modes)/sizeof(modes[0]));
}
#endif

#ifdef OPT_DEBUGGING

void gui_compare_props(int arg)
{
	#define NUM_PROPS 512
	// never freed, but not allocated unless prop compare is used once
	static int *props = NULL;
	char buf[64];
	int i;
	int p;
	int c;

	if( props )
	{ // we have previous data set! do a comparison
		c = 0;
		for( i = 0; i < NUM_PROPS; ++i )
		{
			p = shooting_get_prop(i);
			if( props[i] != p )
			{
				++c;
				sprintf(buf,"%4d is %8d was %8d",i,p,props[i]);
				draw_string(16,16*c,buf,MAKE_COLOR(COLOR_BLACK,COLOR_YELLOW));
			}
			props[i] = p;
			if( c == 12 )
			{
				++c;
				sprintf(buf,"%s","Waiting 15 Seconds");
				draw_string(16,16*c,buf,MAKE_COLOR(COLOR_BLACK,COLOR_YELLOW));
				msleep(15000);
				c = 0;
			}
		}
		++c;
		sprintf(buf,"%s","Press <ALT> to leave");
		draw_string(16,16*c,buf,MAKE_COLOR(COLOR_BLACK,COLOR_YELLOW));
	}
	else
	{
	// no previous data was set so we save the data initially
		props = (int *)malloc(NUM_PROPS*sizeof(int));
		if(props) {
			for( i = 0; i < NUM_PROPS; ++i )
			{
				props[i] = shooting_get_prop(i);
			}
		}
	}
}

#endif
