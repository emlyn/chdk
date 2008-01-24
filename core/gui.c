#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "ubasic.h"
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
#include "gui_debug.h"
#include "gui_fselect.h"
#include "gui_batt.h"
#include "gui_osd.h"
#include "gui_read.h"
#include "gui_calendar.h"
#include "gui_bench.h"
#include "gui_grid.h"
#include "histogram.h"
#include "script.h"
#include "motion_detector.h"
#include "raw.h"

//-------------------------------------------------------------------

#define OPTIONS_AUTOSAVE
#define SPLASH_TIME               20

//shortcuts
//------------------------------------------------------------------
// #define KEY_NONE (KEY_DUMMY+1)

#if   defined(CAMERA_ixus700_sd500) || defined(CAMERA_ixus800_sd700) || defined(CAMERA_a560)
 #define SHORTCUT_TOGGLE_RAW      KEY_DISPLAY
 #define SHORTCUT_TOGGLE_HISTO    KEY_DOWN
 #define SHORTCUT_TOGGLE_ZEBRA    KEY_MENU
 #define SHORTCUT_TOGGLE_OSD      KEY_RIGHT

#elif defined(CAMERA_g7)  
 #define SHORTCUT_TOGGLE_RAW      KEY_ERASE
 #define SHORTCUT_TOGGLE_HISTO    KEY_DOWN
 #define SHORTCUT_TOGGLE_ZEBRA    KEY_LEFT
 #define SHORTCUT_TOGGLE_OSD      KEY_RIGHT

#else
 #define SHORTCUT_TOGGLE_RAW      KEY_ERASE
 #define SHORTCUT_TOGGLE_HISTO    KEY_UP
 #define SHORTCUT_TOGGLE_ZEBRA    KEY_LEFT
 #define SHORTCUT_TOGGLE_OSD      KEY_RIGHT
#endif


// forward declarations
//-------------------------------------------------------------------
extern void dump_memory();

static void gui_draw_osd();
static void gui_draw_splash();

// Menu procs
//-------------------------------------------------------------------
static void gui_show_build_info(int arg);
static void gui_show_memory_info(int arg);
static void gui_draw_palette(int arg);
static void gui_draw_reversi(int arg);
static void gui_draw_sokoban(int arg);
static void gui_draw_debug(int arg);
static void gui_draw_bench(int arg);
static void gui_draw_fselect(int arg);
static void gui_draw_osd_le(int arg);
static void gui_load_script(int arg);
static void gui_draw_read(int arg);
static void gui_draw_read_last(int arg);
static void gui_draw_load_menu_rbf(int arg);
static void gui_draw_load_rbf(int arg);
static void gui_draw_calendar(int arg);
static void gui_draw_load_lang(int arg);
static void gui_menuproc_mkbootdisk(int arg);
#ifndef OPTIONS_AUTOSAVE
static void gui_menuproc_save(int arg);
#endif
static void gui_menuproc_reset(int arg);
static void gui_grid_lines_load(int arg);
static void gui_raw_develop(int arg);
static const char* gui_histo_mode_enum(int change, int arg);
static const char* gui_histo_layout_enum(int change, int arg);
static const char* gui_zebra_mode_enum(int change, int arg);
static const char* gui_zebra_draw_osd_enum(int change, int arg);
static const char* gui_font_enum(int change, int arg);
static const char* gui_raw_prefix_enum(int change, int arg);
static const char* gui_raw_ext_enum(int change, int arg);
static const char* gui_raw_nr_enum(int change, int arg);
static const char* gui_reader_codepage_enum(int change, int arg);
static const char* gui_zoom_value_enum(int change, int arg);
static const char* gui_dof_show_value_enum(int change, int arg);
#if defined(CAMERA_s2is) || defined(CAMERA_s3is) || defined(CAMERA_g7)
static const char* gui_alt_mode_button_enum(int change, int arg);
#endif
static const char* gui_alt_power_enum(int change, int arg);
static const char* gui_video_mode_enum(int change, int arg);
static const char* gui_video_bitrate_enum(int change, int arg);
static const char* gui_tv_bracket_values_enum(int change, int arg);
static const char* gui_av_bracket_values_enum(int change, int arg);
static const char* gui_iso_bracket_koef_enum(int change, int arg);
static const char* gui_subj_dist_bracket_koef_enum(int change, int arg);
static const char* gui_bracket_type_enum(int change, int arg);
static const char* gui_av_override_enum(int change, int arg);
static const char* gui_iso_override_koef_enum(int change, int arg);
static const char* gui_tv_override_koef_enum(int change, int arg);
static const char* gui_subj_dist_override_value_enum(int change, int arg);
static const char* gui_subj_dist_override_koef_enum(int change, int arg);
static const char* gui_tv_exposure_order_enum(int change, int arg);
static const char* gui_av_exposure_order_enum(int change, int arg);
static const char* gui_iso_exposure_order_enum(int change, int arg);
//static const char* gui_tv_enum(int change, int arg);


// Menu callbacks
//-------------------------------------------------------------------
static void cb_step_25();
static void cb_perc();
static void cb_volts();
static void cb_battery_menu_change(unsigned int item);
static void cb_zebra_restore_screen();
static void cb_zebra_restore_osd();

// Menu definition
//-------------------------------------------------------------------
static CMenuItem script_submenu_items_top[] = {
    {LANG_MENU_SCRIPT_LOAD,             MENUITEM_PROC,                      (int*)gui_load_script },
    {LANG_MENU_SCRIPT_DELAY,            MENUITEM_INT|MENUITEM_F_UNSIGNED,   &conf.script_shoot_delay },
	// remote autostart
	{LANG_MENU_SCRIPT_AUTOSTART,		MENUITEM_BOOL,						&conf.script_startup },
#if !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560) && !defined (CAMERA_a700)
	{LANG_MENU_SCRIPT_REMOTE_ENABLE,	MENUITEM_BOOL,						&conf.remote_enable},
#endif
    {LANG_MENU_SCRIPT_CURRENT,          MENUITEM_SEPARATOR },
    {(int)script_title,                 MENUITEM_TEXT },
    {LANG_MENU_SCRIPT_PARAMS,           MENUITEM_SEPARATOR }
};

static CMenuItem script_submenu_items_bottom[] = {
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};

static CMenuItem script_submenu_items[sizeof(script_submenu_items_top)/sizeof(script_submenu_items_top[0])+SCRIPT_NUM_PARAMS+
                               sizeof(script_submenu_items_bottom)/sizeof(script_submenu_items_bottom[0])];
static CMenu script_submenu = { LANG_MENU_SCRIPT_TITLE, NULL, script_submenu_items };


static CMenuItem games_submenu_items[] = {
    {LANG_MENU_GAMES_REVERSI,           MENUITEM_PROC,  (int*)gui_draw_reversi },
    {LANG_MENU_GAMES_SOKOBAN,           MENUITEM_PROC,  (int*)gui_draw_sokoban },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu games_submenu = { LANG_MENU_GAMES_TITLE, NULL, games_submenu_items };


static CMenuItem reader_submenu_items[] = {
    {LANG_MENU_READ_OPEN_NEW,           MENUITEM_PROC,    (int*)gui_draw_read },
    {LANG_MENU_READ_OPEN_LAST,          MENUITEM_PROC,    (int*)gui_draw_read_last },
    {LANG_MENU_READ_SELECT_FONT,        MENUITEM_PROC,    (int*)gui_draw_load_rbf },
    {LANG_MENU_READ_CODEPAGE,           MENUITEM_ENUM,    (int*)gui_reader_codepage_enum },
    {LANG_MENU_READ_WORD_WRAP,          MENUITEM_BOOL,    &conf.reader_wrap_by_words },
    {LANG_MENU_READ_AUTOSCROLL,         MENUITEM_BOOL,    &conf.reader_autoscroll },
    {LANG_MENU_READ_AUTOSCROLL_DELAY,   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.reader_autoscroll_delay, MENU_MINMAX(0, 60) },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu reader_submenu = { LANG_MENU_READ_TITLE, NULL, reader_submenu_items };


static CMenuItem misc_submenu_items[] = {
    {LANG_MENU_MISC_FILE_BROWSER,       MENUITEM_PROC,    (int*)gui_draw_fselect },
    {LANG_MENU_MISC_CALENDAR,           MENUITEM_PROC,    (int*)gui_draw_calendar },
    {LANG_MENU_MISC_TEXT_READER,        MENUITEM_SUBMENU, (int*)&reader_submenu },
    {LANG_MENU_MISC_GAMES,              MENUITEM_SUBMENU, (int*)&games_submenu },
#if defined(CAMERA_a610) || defined(CAMERA_a620) || defined(CAMERA_a630) || defined(CAMERA_a640) || defined (CAMERA_s2is) || defined (CAMERA_s3is) || defined (CAMERA_s5is)
    {LANG_MENU_MISC_FLASHLIGHT,         MENUITEM_BOOL,    &conf.flashlight },
#endif
    {LANG_MENU_MISC_SHOW_SPLASH,        MENUITEM_BOOL,    &conf.splash_show },
#if !defined(CAMERA_g7) && !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560)
    {LANG_MENU_MISC_ZOOM_FOR_MF,        MENUITEM_BOOL,    &conf.use_zoom_mf },
#endif
#if defined(CAMERA_s2is) || defined(CAMERA_s3is) || defined(CAMERA_g7)
    {LANG_MENU_MISC_ALT_BUTTON,         MENUITEM_ENUM,    (int*)gui_alt_mode_button_enum },
#endif
    {LANG_MENU_MISC_DISABLE_LCD_OFF,    MENUITEM_ENUM,    (int*)gui_alt_power_enum },
    {LANG_MENU_MISC_PALETTE,            MENUITEM_PROC,    (int*)gui_draw_palette },
    {LANG_MENU_MISC_BUILD_INFO,         MENUITEM_PROC,    (int*)gui_show_build_info },
    {LANG_MENU_MISC_MEMORY_INFO,        MENUITEM_PROC,    (int*)gui_show_memory_info },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}, // for swap part. menu
    {0},
};
static CMenu misc_submenu = { LANG_MENU_MISC_TITLE, NULL, misc_submenu_items };


static CMenuItem debug_submenu_items[] = {
    {LANG_MENU_DEBUG_SHOW_PROPCASES,    MENUITEM_BOOL,          &debug_propcase_show },
    {LANG_MENU_DEBUG_SHOW_PARAMETER_DATA,        MENUITEM_BOOL,          &debug_pardata_show },
    {LANG_MENU_DEBUG_PROPCASE_PAGE,     MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,   &debug_propcase_page, MENU_MINMAX(0, 128) },
    {LANG_MENU_DEBUG_SHOW_MISC_VALS,    MENUITEM_BOOL,          &debug_vals_show },
    {LANG_MENU_DEBUG_MEMORY_BROWSER,    MENUITEM_PROC,          (int*)gui_draw_debug },
    {LANG_MENU_DEBUG_BENCHMARK,         MENUITEM_PROC,          (int*)gui_draw_bench },
    {LANG_MENU_DEBUG_DUMP_RAM,          MENUITEM_BOOL,          &conf.ns_enable_memdump },
    {LANG_MENU_DEBUG_MAKE_BOOTABLE,     MENUITEM_PROC, 	    	(int*)gui_menuproc_mkbootdisk },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu debug_submenu = { LANG_MENU_DEBUG_TITLE, NULL, debug_submenu_items };


static int voltage_step;
static CMenuItem battery_submenu_items[] = {
    {LANG_MENU_BATT_VOLT_MAX,           MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf.batt_volts_max,   (int)&voltage_step },
    {LANG_MENU_BATT_VOLT_MIN,           MENUITEM_INT|MENUITEM_ARG_ADDR_INC,     &conf.batt_volts_min,   (int)&voltage_step },
    {LANG_MENU_BATT_STEP_25,            MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_step_25,     (int)cb_step_25 },	
    {(int)"",                           MENUITEM_SEPARATOR },
    {LANG_MENU_BATT_SHOW_PERCENT,       MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_perc_show,   (int)cb_perc },
    {LANG_MENU_BATT_SHOW_VOLTS,         MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,    &conf.batt_volts_show,  (int)cb_volts },
    {LANG_MENU_BATT_SHOW_ICON,          MENUITEM_BOOL,                          &conf.batt_icon_show },	
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu battery_submenu = { LANG_MENU_BATT_TITLE, cb_battery_menu_change, battery_submenu_items };

//ARM begin
static CMenuItem dof_submenu_items[] = {
	  {LANG_MENU_OSD_SHOW_DOF_CALC,            MENUITEM_ENUM,      (int*)gui_dof_show_value_enum },
	  {LANG_MENU_DOF_SUBJ_DIST_AS_NEAR_LIMIT,  MENUITEM_BOOL,      &conf.dof_subj_dist_as_near_limit},
	  {LANG_MENU_DOF_USE_EXIF_SUBJ_DIST,       MENUITEM_BOOL,      &conf.dof_use_exif_subj_dist},	  
	  {LANG_MENU_DOF_SUBJ_DIST_IN_MISC,        MENUITEM_BOOL,      &conf.dof_subj_dist_in_misc},	 
	  {LANG_MENU_DOF_NEAR_LIMIT_IN_MISC,       MENUITEM_BOOL,      &conf.dof_near_limit_in_misc},	
      {LANG_MENU_DOF_FAR_LIMIT_IN_MISC,        MENUITEM_BOOL,			 &conf.dof_far_limit_in_misc},	
      {LANG_MENU_DOF_HYPERFOCAL_IN_MISC,       MENUITEM_BOOL,      &conf.dof_hyperfocal_in_misc},				
      {LANG_MENU_DOF_DEPTH_LIMIT_IN_MISC,      MENUITEM_BOOL,      &conf.dof_depth_in_misc},			
	  {LANG_MENU_BACK,                    	   MENUITEM_UP },
    {0}
};
static CMenu dof_submenu = { LANG_MENU_DOF_TITLE, /*cb_dof_menu_change*/ NULL, dof_submenu_items };

static CMenuItem values_submenu_items[] = {
	  {LANG_MENU_OSD_SHOW_MISC_VALUES,           MENUITEM_BOOL,      &conf.show_values },
	 // {LANG_MENU_VALUES_SHOW_IN_REVIEW,   MENUITEM_BOOL,      &conf.values_show_in_review},
	  {LANG_MENU_VALUES_SHOW_ZOOM,               MENUITEM_BOOL,      &conf.values_show_zoom},	
	  {LANG_MENU_OSD_ZOOM_VALUE,                 MENUITEM_ENUM,      (int*)gui_zoom_value_enum },	
      {LANG_MENU_VALUES_SHOW_REAL_APERTURE,      MENUITEM_BOOL,      &conf.values_show_real_aperture},		
      {LANG_MENU_VALUES_SHOW_REAL_ISO,           MENUITEM_BOOL,      &conf.values_show_real_iso},			
      {LANG_MENU_VALUES_SHOW_MARKET_ISO,         MENUITEM_BOOL,      &conf.values_show_market_iso},				
  	  {LANG_MENU_SHOW_ISO_ONLY_IN_AUTOISO_MODE,  MENUITEM_BOOL,	     &conf.values_show_iso_only_in_autoiso_mode},			
      {LANG_MENU_VALUES_SHOW_EV_SETED, 			 MENUITEM_BOOL,	     &conf.values_show_ev_seted},
      {LANG_MENU_VALUES_SHOW_EV_MEASURED,        MENUITEM_BOOL,		 &conf.values_show_ev_measured},				
      {LANG_MENU_VALUES_SHOW_BV_SETED,			 MENUITEM_BOOL,	     &conf.values_show_bv_seted},					
      {LANG_MENU_VALUES_SHOW_BV_MEASURED,   	 MENUITEM_BOOL,	     &conf.values_show_bv_measured},					
      {LANG_MENU_VALUES_SHOW_OVEREXPOSURE,	     MENUITEM_BOOL,      &conf.values_show_overexposure},	
#if !defined(CAMERA_a570) && !defined(CAMERA_a560) && !defined(CAMERA_a720)
      {LANG_MENU_SHOW_CANON_OVEREXPOSURE,	     MENUITEM_BOOL,      &conf.values_show_canon_overexposure},							
#endif      
      {LANG_MENU_VALUES_SHOW_LUMINANCE,  	     MENUITEM_BOOL,      &conf.values_show_luminance},							
	  {LANG_MENU_BACK,                           MENUITEM_UP },
    {0}
};
static CMenu values_submenu = { LANG_MENU_OSD_VALUES_TITLE, /*cb_values_menu_change*/ NULL, values_submenu_items };

static CMenuItem video_submenu_items[] = {
	  {LANG_MENU_VIDEO_MODE,              MENUITEM_ENUM,    (int*)gui_video_mode_enum}, 
      {LANG_MENU_VIDEO_BITRATE,           MENUITEM_ENUM,    (int*)gui_video_bitrate_enum}, 
      {LANG_MENU_VIDEO_QUALITY,           MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.video_quality, MENU_MINMAX(1, 99)}, 
      {LANG_MENU_BACK,                    MENUITEM_UP },
      {0}
};
static CMenu video_submenu = { LANG_MENU_VIDEO_PARAM_TITLE, NULL, video_submenu_items };

static CMenuItem bracketing_in_continuous_submenu_items[] = {
	  {LANG_MENU_TV_BRACKET_VALUE,             MENUITEM_ENUM,    (int*)gui_tv_bracket_values_enum },
#if !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560)	  
	  {LANG_MENU_AV_BRACKET_VALUE,             MENUITEM_ENUM,    (int*)gui_av_bracket_values_enum },
#endif
	  {LANG_MENU_ISO_BRACKET_VALUE,            MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.iso_bracket_value, MENU_MINMAX(0, 100)}, 
	  {LANG_MENU_ISO_BRACKET_KOEF,             MENUITEM_ENUM,    (int*)gui_iso_bracket_koef_enum},
#if !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560)	  	  
	  {LANG_MENU_SUBJ_DIST_BRACKET_VALUE,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX, &conf.subj_dist_bracket_value, MENU_MINMAX(0, 100)}, 
	  {LANG_MENU_SUBJ_DIST_BRACKET_KOEF,       MENUITEM_ENUM,    (int*)gui_subj_dist_bracket_koef_enum},
#endif	  
	  {LANG_MENU_BRACKET_TYPE,                 MENUITEM_ENUM,    (int*)gui_bracket_type_enum },
      {LANG_MENU_BACK,                         MENUITEM_UP },
      {0}
};
static CMenu bracketing_in_continuous_submenu = { LANG_MENU_BRACKET_IN_CONTINUOUS_TITLE, NULL, bracketing_in_continuous_submenu_items };


static CMenuItem exposure_submenu_items[] = {
	  {LANG_MENU_RECALC_EXPOSURE,         MENUITEM_BOOL,    &conf.recalc_exposure},
	  {LANG_MENU_TV_EXPOSURE_ORDER,       MENUITEM_ENUM,    (int*)gui_tv_exposure_order_enum},
	  {LANG_MENU_AV_EXPOSURE_ORDER,       MENUITEM_ENUM,    (int*)gui_av_exposure_order_enum},
	  {LANG_MENU_ISO_EXPOSURE_ORDER,	  MENUITEM_ENUM,    (int*)gui_iso_exposure_order_enum},
	  {LANG_MENU_BACK,                    MENUITEM_UP },
      {0}
};
static CMenu exposure_submenu = { LANG_MENU_EXPOSURE_TITLE, NULL, exposure_submenu_items };

static CMenuItem operation_submenu_items[] = {
	  {LANG_MENU_OVERRIDE_TV_VALUE,        MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.tv_override_value, MENU_MINMAX(0, 100)}, 
	  {LANG_MENU_OVERRIDE_TV_KOEF,         MENUITEM_ENUM,    (int*)gui_tv_override_koef_enum},
#if !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560)
	  {LANG_MENU_OVERRIDE_AV_VALUE,        MENUITEM_ENUM,    (int*)gui_av_override_enum },
#endif
	  {LANG_MENU_OVERRIDE_ISO_VALUE,	   MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.iso_override_value, MENU_MINMAX(0, 800)}, 
	  {LANG_MENU_OVERRIDE_ISO_KOEF,        MENUITEM_ENUM,    (int*)gui_iso_override_koef_enum},
 	 // {LANG_MENU_OVERRIDE_SUBJ_DIST_VALUE, MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.subj_dist_override_value, MENU_MINMAX(0, 500)}, 
#if !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560)	  	   	 
      {LANG_MENU_OVERRIDE_SUBJ_DIST_VALUE, MENUITEM_ENUM,    (int*)gui_subj_dist_override_value_enum},
	  {LANG_MENU_OVERRIDE_SUBJ_DIST_KOEF,  MENUITEM_ENUM,    (int*)gui_subj_dist_override_koef_enum},
#endif	  
	  {LANG_MENU_BRACKET_IN_CONTINUOUS,	   MENUITEM_SUBMENU, (int*)&bracketing_in_continuous_submenu }, 
	  {LANG_MENU_CLEAR_OVERRIDE_VALUES,    MENUITEM_BOOL,    (int*)&conf.clear_override},
      //{LANG_MENU_EXPOSURE,                 MENUITEM_SUBMENU,    (int*)&exposure_submenu },
	  {LANG_MENU_BACK,                     MENUITEM_UP },
     {0}
};
static CMenu operation_submenu = { LANG_MENU_OPERATION_PARAM_TITLE, NULL, operation_submenu_items };

//END ARM

static CMenuItem grid_submenu_items[] = {
    {LANG_MENU_SHOW_GRID,               MENUITEM_BOOL,		&conf.show_grid_lines },
    {LANG_MENU_GRID_LOAD,               MENUITEM_PROC,		(int*)gui_grid_lines_load },
    {LANG_MENU_GRID_CURRENT,            MENUITEM_SEPARATOR },
    {(int)grid_title,                   MENUITEM_TEXT },
    {(int)"",                           MENUITEM_SEPARATOR },
    {LANG_MENU_GRID_FORCE_COLOR,        MENUITEM_BOOL,          &conf.grid_force_color },
    {LANG_MENU_GRID_COLOR_LINE,         MENUITEM_COLOR_FG,      (int*)&conf.grid_color },
    {LANG_MENU_GRID_COLOR_FILL,         MENUITEM_COLOR_BG,      (int*)&conf.grid_color },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu grid_submenu = { LANG_MENU_GRID_TITLE, NULL, grid_submenu_items };


static CMenuItem visual_submenu_items[] = {
    {LANG_MENU_VIS_LANG,                MENUITEM_PROC,      (int*)gui_draw_load_lang },
    {LANG_MENU_VIS_OSD_FONT,            MENUITEM_ENUM,      (int*)gui_font_enum },
    {LANG_MENU_VIS_MENU_FONT,           MENUITEM_PROC,      (int*)gui_draw_load_menu_rbf },
    {LANG_MENU_VIS_COLORS,              MENUITEM_SEPARATOR },
    {LANG_MENU_VIS_OSD_TEXT,            MENUITEM_COLOR_FG,  (int*)&conf.osd_color },
    {LANG_MENU_VIS_OSD_BKG,             MENUITEM_COLOR_BG,  (int*)&conf.osd_color },
    {LANG_MENU_VIS_HISTO,               MENUITEM_COLOR_FG,  (int*)&conf.histo_color },
    {LANG_MENU_VIS_HISTO_BKG,           MENUITEM_COLOR_BG,  (int*)&conf.histo_color },
    {LANG_MENU_VIS_HISTO_BORDER,        MENUITEM_COLOR_FG,  (int*)&conf.histo_color2 },
    {LANG_MENU_VIS_HISTO_MARKERS,       MENUITEM_COLOR_BG,  (int*)&conf.histo_color2 },
    {LANG_MENU_VIS_ZEBRA_UNDER,         MENUITEM_COLOR_BG,  (int*)&conf.zebra_color },
    {LANG_MENU_VIS_ZEBRA_OVER,          MENUITEM_COLOR_FG,  (int*)&conf.zebra_color },
    {LANG_MENU_VIS_BATT_ICON,           MENUITEM_COLOR_FG,  (int*)&conf.batt_icon_color },
    {LANG_MENU_VIS_MENU_TEXT,           MENUITEM_COLOR_FG,  (int*)&conf.menu_color },
    {LANG_MENU_VIS_MENU_BKG,            MENUITEM_COLOR_BG,  (int*)&conf.menu_color },
    {LANG_MENU_VIS_READER_TEXT,         MENUITEM_COLOR_FG,  (int*)&conf.reader_color },
    {LANG_MENU_VIS_READER_BKG,          MENUITEM_COLOR_BG,  (int*)&conf.reader_color },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu visual_submenu = { LANG_MENU_VIS_TITLE, NULL, visual_submenu_items };


static CMenuItem osd_submenu_items[] = {
    {LANG_MENU_OSD_SHOW,                MENUITEM_BOOL,      &conf.show_osd },
    {LANG_MENU_OSD_SHOW_STATES,         MENUITEM_BOOL,      &conf.show_state },
    
    {LANG_MENU_OSD_SHOW_CLOCK,          MENUITEM_BOOL,      &conf.show_clock },
    {LANG_MENU_OSD_LAYOUT_EDITOR,       MENUITEM_PROC,      (int*)gui_draw_osd_le },
    //ARM begin
    {LANG_MENU_OSD_VALUES,  	    	MENUITEM_SUBMENU,   (int*)&values_submenu },
    {LANG_MENU_OSD_DOF_CALC,            MENUITEM_SUBMENU,   (int*)&dof_submenu },
    //ARM end
    {LANG_MENU_OSD_BATT_PARAMS,         MENUITEM_SUBMENU,   (int*)&battery_submenu },
    {LANG_MENU_OSD_GRID_PARAMS,         MENUITEM_SUBMENU,   (int*)&grid_submenu },
    {LANG_MENU_OSD_SHOW_IN_REVIEW,      MENUITEM_BOOL,      &conf.show_osd_in_review},
#ifndef OPTIONS_AUTOSAVE
    {LANG_MENU_MAIN_SAVE_OPTIONS,       MENUITEM_PROC,      (int*)gui_menuproc_save },
#endif
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu osd_submenu = { LANG_MENU_OSD_TITLE, NULL, osd_submenu_items };


static CMenuItem histo_submenu_items[] = {
    {LANG_MENU_HISTO_SHOW,              MENUITEM_BOOL,      &conf.show_histo },
    {LANG_MENU_HISTO_LAYOUT,            MENUITEM_ENUM,      (int*)gui_histo_layout_enum },
    {LANG_MENU_HISTO_MODE,              MENUITEM_ENUM,      (int*)gui_histo_mode_enum },
    {LANG_MENU_HISTO_EXP,               MENUITEM_BOOL,       &conf.show_overexp },
    {LANG_MENU_HISTO_IGNORE_PEAKS,      MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.histo_ignore_boundary,   MENU_MINMAX(0, 32)},
    {LANG_MENU_HISTO_MAGNIFY,           MENUITEM_BOOL,       &conf.histo_auto_ajust },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu histo_submenu = { LANG_MENU_HISTO_TITLE, NULL, histo_submenu_items };


static CMenuItem raw_submenu_items[] = {
    {LANG_MENU_RAW_SAVE,                MENUITEM_BOOL,      &conf.save_raw },
    {LANG_MENU_RAW_NOISE_REDUCTION,     MENUITEM_ENUM,      (int*)gui_raw_nr_enum },
    {LANG_MENU_RAW_FIRST_ONLY,          MENUITEM_BOOL,      &conf.raw_save_first_only },
    {LANG_MENU_RAW_SAVE_IN_DIR,         MENUITEM_BOOL,      &conf.raw_in_dir },
    {LANG_MENU_RAW_PREFIX,              MENUITEM_ENUM,      (int*)gui_raw_prefix_enum },
    {LANG_MENU_RAW_EXTENSION,           MENUITEM_ENUM,      (int*)gui_raw_ext_enum },
    {LANG_MENU_RAW_DEVELOP,             MENUITEM_PROC,      (int*)gui_raw_develop },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu raw_submenu = { LANG_MENU_RAW_TITLE, NULL, raw_submenu_items };


static CMenuItem zebra_submenu_items[] = {
    {LANG_MENU_ZEBRA_DRAW,              MENUITEM_BOOL,                            &conf.zebra_draw },
    {LANG_MENU_ZEBRA_MODE,              MENUITEM_ENUM,                            (int*)gui_zebra_mode_enum },
    {LANG_MENU_ZEBRA_UNDER,             MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zebra_under,   MENU_MINMAX(0, 32)},
    {LANG_MENU_ZEBRA_OVER,              MENUITEM_INT|MENUITEM_F_UNSIGNED|MENUITEM_F_MINMAX,  &conf.zebra_over,    MENU_MINMAX(0, 32)},
    {LANG_MENU_ZEBRA_RESTORE_SCREEN,    MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,      &conf.zebra_restore_screen,     (int)cb_zebra_restore_screen },
    {LANG_MENU_ZEBRA_RESTORE_OSD,       MENUITEM_BOOL|MENUITEM_ARG_CALLBACK,      &conf.zebra_restore_osd,        (int)cb_zebra_restore_osd },
    {LANG_MENU_ZEBRA_DRAW_OVER,         MENUITEM_ENUM,                            (int*)gui_zebra_draw_osd_enum },
    {LANG_MENU_BACK,                    MENUITEM_UP },
    {0}
};
static CMenu zebra_submenu = { LANG_MENU_ZEBRA_TITLE, NULL, zebra_submenu_items };


static CMenuItem root_menu_items[] = {
    {LANG_MENU_OPERATION_PARAM,         MENUITEM_SUBMENU,   (int*)&operation_submenu },
    {LANG_MENU_MAIN_OSD_PARAM,          MENUITEM_SUBMENU,   (int*)&osd_submenu },
#if !defined (CAMERA_a720)
    {LANG_MENU_VIDEO_PARAM,             MENUITEM_SUBMENU,   (int*)&video_submenu },
#endif
    {LANG_MENU_MAIN_RAW_PARAM,          MENUITEM_SUBMENU,   (int*)&raw_submenu },
    {LANG_MENU_MAIN_HISTO_PARAM,        MENUITEM_SUBMENU,   (int*)&histo_submenu },
    {LANG_MENU_MAIN_ZEBRA_PARAM,        MENUITEM_SUBMENU,   (int*)&zebra_submenu },
    {LANG_MENU_MAIN_SCRIPT_PARAM,       MENUITEM_SUBMENU,   (int*)&script_submenu },
    {LANG_MENU_MAIN_VISUAL_PARAM,       MENUITEM_SUBMENU,   (int*)&visual_submenu },
    {LANG_MENU_MAIN_MISC,               MENUITEM_SUBMENU,   (int*)&misc_submenu },
    {LANG_MENU_MAIN_DEBUG,              MENUITEM_SUBMENU,   (int*)&debug_submenu },
    {LANG_MENU_MAIN_RESET_OPTIONS,      MENUITEM_PROC,      (int*)gui_menuproc_reset },
#ifndef OPTIONS_AUTOSAVE
    {LANG_MENU_MAIN_SAVE_OPTIONS,       MENUITEM_PROC,      (int*)gui_menuproc_save },
#endif
    {0}
};

static CMenuItem swap_menuitem={(int)"Swap partitions",      MENUITEM_PROC,      (int*)swap_partitions };

static CMenu root_menu = { LANG_MENU_MAIN_TITLE, NULL, root_menu_items };

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

//-------------------------------------------------------------------
const char* gui_histo_mode_enum(int change, int arg) {
    static const char* modes[]={ "Linear", "Log" };

    conf.histo_mode+=change;
    if (conf.histo_mode<0)
        conf.histo_mode=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.histo_mode>=(sizeof(modes)/sizeof(modes[0])))
        conf.histo_mode=0;

    histogram_set_mode(conf.histo_mode);

    return modes[conf.histo_mode];
}

//-------------------------------------------------------------------
const char* gui_histo_layout_enum(int change, int arg) {
    static const char* modes[]={ "RGB", "Y", "RGB Y",  "R G B", "RGB all", "Y all", "Blend", "Blend Y"};

    conf.histo_layout+=change;
    if (conf.histo_layout<0)
        conf.histo_layout=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.histo_layout>=(sizeof(modes)/sizeof(modes[0])))
        conf.histo_layout=0;

    if (conf.histo_layout==OSD_HISTO_LAYOUT_Y || conf.histo_layout==OSD_HISTO_LAYOUT_Y_argb) {
        histogram_set_main(HISTO_Y);
    } else {
        histogram_set_main(HISTO_RGB);
    }

    return modes[conf.histo_layout];
}

//-------------------------------------------------------------------
const char* gui_font_enum(int change, int arg) {
    static const char* fonts[]={ "Win1250", "Win1251", "Win1252", "Win1254", "Win1257"};

    conf.font_cp+=change;
    if (conf.font_cp<0)
        conf.font_cp=(sizeof(fonts)/sizeof(fonts[0]))-1;
    else if (conf.font_cp>=(sizeof(fonts)/sizeof(fonts[0])))
        conf.font_cp=0;

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
    static const char* prefixes[]={ "IMG_", "CRW_", "SND_"};

    conf.raw_prefix+=change;
    if (conf.raw_prefix<0)
        conf.raw_prefix=(sizeof(prefixes)/sizeof(prefixes[0]))-1;
    else if (conf.raw_prefix>=(sizeof(prefixes)/sizeof(prefixes[0])))
        conf.raw_prefix=0;

    return prefixes[conf.raw_prefix];
}

//-------------------------------------------------------------------
const char* gui_raw_ext_enum(int change, int arg) {
    static const char* exts[]={ ".JPG", ".CRW", ".CR2", ".THM", ".WAV"};

    conf.raw_ext+=change;
    if (conf.raw_ext<0)
        conf.raw_ext=(sizeof(exts)/sizeof(exts[0]))-1;
    else if (conf.raw_ext>=(sizeof(exts)/sizeof(exts[0])))
        conf.raw_ext=0;

    return exts[conf.raw_ext];
}

//-------------------------------------------------------------------
const char* gui_raw_nr_enum(int change, int arg) {
    static const char* modes[]={ "Auto", "Off", "On"};

    conf.raw_nr+=change;
    if (conf.raw_nr<0)
        conf.raw_nr=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.raw_nr>=(sizeof(modes)/sizeof(modes[0])))
        conf.raw_nr=0;

    return modes[conf.raw_nr];
}

//-------------------------------------------------------------------
const char* gui_reader_codepage_enum(int change, int arg) {
    static const char* cps[]={ "Win1251", "DOS"};

    conf.reader_codepage+=change;
    if (conf.reader_codepage<0)
        conf.reader_codepage=(sizeof(cps)/sizeof(cps[0]))-1;
    else if (conf.reader_codepage>=(sizeof(cps)/sizeof(cps[0])))
        conf.reader_codepage=0;

    return cps[conf.reader_codepage];
}

//-------------------------------------------------------------------
const char* gui_zebra_mode_enum(int change, int arg) {
    static const char* modes[]={ "Blink 1", "Blink 2", "Blink 3", "Solid", "Zebra 1", "Zebra 2" };

    conf.zebra_mode+=change;
    if (conf.zebra_mode<0)
        conf.zebra_mode=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.zebra_mode>=(sizeof(modes)/sizeof(modes[0])))
        conf.zebra_mode=0;

    return modes[conf.zebra_mode];
}

//-------------------------------------------------------------------
const char* gui_zebra_draw_osd_enum(int change, int arg) {
    static const char* modes[]={ "Nothing", "Histo", "OSD" };

    conf.zebra_draw_osd+=change;
    if (conf.zebra_draw_osd<0)
        conf.zebra_draw_osd=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.zebra_draw_osd>=(sizeof(modes)/sizeof(modes[0])))
        conf.zebra_draw_osd=0;

    return modes[conf.zebra_draw_osd];
}

//-------------------------------------------------------------------
const char* gui_zoom_value_enum(int change, int arg) {
    static const char* modes[]={ "X", "FL", "EFL" };

    conf.zoom_value+=change;
    if (conf.zoom_value<0)
        conf.zoom_value=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.zoom_value>=(sizeof(modes)/sizeof(modes[0])))
        conf.zoom_value=0;

    return modes[conf.zoom_value];
}
//ARM Begin
const char* gui_dof_show_value_enum(int change, int arg) {
    static const char* modes[]={ "Dont", "Separate", "In Misc" };

    conf.show_dof+=change;
    if (conf.show_dof<0)
        conf.show_dof=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.show_dof>=(sizeof(modes)/sizeof(modes[0])))
        conf.show_dof=0;

    return modes[conf.show_dof];
}
//ARM End

//-------------------------------------------------------------------
#if defined(CAMERA_s2is) || defined(CAMERA_s3is) || defined(CAMERA_g7)
const char* gui_alt_mode_button_enum(int change, int arg) {
#if defined(CAMERA_s2is) || defined(CAMERA_s3is)
    static const char* names[]={ "Shrtcut", "Flash", "Timer", "ISO", "Video" };
    static const int keys[]={ KEY_PRINT, KEY_FLASH, KEY_TIMER, KEY_ISO, KEY_VIDEO };
#else
    static const char* names[]={ "Print", "FE"};
    static const int keys[]={ KEY_PRINT, KEY_MICROPHONE };
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
    static const char* modes[]={ "No", "Alt", "Script" };

    conf.alt_prevent_shutdown+=change;
    if (conf.alt_prevent_shutdown<0)
        conf.alt_prevent_shutdown=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.alt_prevent_shutdown>=(sizeof(modes)/sizeof(modes[0])))
        conf.alt_prevent_shutdown=0;

    return modes[conf.alt_prevent_shutdown];
}
const char* gui_video_mode_enum(int change, int arg) {
    static const char* modes[]={ "Bitrate", "Quality"};

    conf.video_mode+=change;
    if (conf.video_mode<0)
        conf.video_mode=(sizeof(modes)/sizeof(modes[0]))-1;
    else if (conf.video_mode>=(sizeof(modes)/sizeof(modes[0])))
        conf.video_mode=0;

    return modes[conf.video_mode];
}

//-------------------------------------------------------------------
const char* gui_video_bitrate_enum(int change, int arg) {
    static const char* modes[]={ "0.25x", "0.5x","0.75x", "1x", "1.25x", "1.5x", "1.75x", "2x", "2.5x", "3x"};

    conf.video_bitrate+=change;
    if (conf.video_bitrate<0)
        conf.video_bitrate=sizeof(modes)/sizeof(modes[0])-1;
    else if (conf.video_bitrate>=(sizeof(modes)/sizeof(modes[0])))
        conf.video_bitrate=0;

    shooting_video_bitrate_change(conf.video_bitrate);

    return modes[conf.video_bitrate];
}


//-------------------------------------------------------------------
const char* gui_tv_bracket_values_enum(int change, int arg) {
    static const char* modes[]={ "Off", "1/3 EV","2/3 EV", "1 EV", "1 1/3Ev", "1 2/3Ev", "2 Ev"};

    conf.tv_bracket_value+=change;
    if (conf.tv_bracket_value<0)
        conf.tv_bracket_value=sizeof(modes)/sizeof(modes[0])-1;
    else if (conf.tv_bracket_value>=(sizeof(modes)/sizeof(modes[0])))
        conf.tv_bracket_value=0;

    return modes[conf.tv_bracket_value]; 
}

const char* gui_av_bracket_values_enum(int change, int arg) {
    static const char* modes[]={ "Off", "1/3 EV","2/3 EV", "1 EV", "1 1/3Ev", "1 2/3Ev", "2 Ev"};

    conf.av_bracket_value+=change;
    if (conf.av_bracket_value<0)
        conf.av_bracket_value=sizeof(modes)/sizeof(modes[0])-1;
    else if (conf.av_bracket_value>=(sizeof(modes)/sizeof(modes[0])))
        conf.av_bracket_value=0;

    return modes[conf.av_bracket_value]; 
}

const char* gui_subj_dist_bracket_koef_enum(int change, int arg) {
    static const char* modes[]={"Off", "1", "10","100","1000"};

    conf.subj_dist_bracket_koef+=change;
    if (conf.subj_dist_bracket_koef<0)
        conf.subj_dist_bracket_koef=sizeof(modes)/sizeof(modes[0])-1;
    else if (conf.subj_dist_bracket_koef>=(sizeof(modes)/sizeof(modes[0])))
        conf.subj_dist_bracket_koef=0;
    
    return modes[conf.subj_dist_bracket_koef]; 
}

const char* gui_iso_bracket_koef_enum(int change, int arg) {
    static const char* modes[]={ "Off","1", "10","100"};

    conf.iso_bracket_koef+=change;
    if (conf.iso_bracket_koef<0)
        conf.iso_bracket_koef=sizeof(modes)/sizeof(modes[0])-1;
    else if (conf.iso_bracket_koef>=(sizeof(modes)/sizeof(modes[0])))
        conf.iso_bracket_koef=0;
    
    return modes[conf.iso_bracket_koef]; 
}

const char* gui_bracket_type_enum(int change, int arg) {
    static const char* modes[]={ "+/-", "-","+"};

    conf.bracket_type+=change;
    if (conf.bracket_type<0)
        conf.bracket_type=0;
    else if (conf.bracket_type>=(sizeof(modes)/sizeof(modes[0])))
        conf.bracket_type=sizeof(modes)/sizeof(modes[0])-1;

    return modes[conf.bracket_type]; 
}

const char* gui_tv_override_koef_enum(int change, int arg) {
    static const char* modes[]={"Off", "1/100K", "1/10000", "1/1000","1/100","1/10", "1","10","100"};

    conf.tv_override_koef+=change;
    if (conf.tv_override_koef<0)
        conf.tv_override_koef=sizeof(modes)/sizeof(modes[0])-1;
    else if (conf.tv_override_koef>=(sizeof(modes)/sizeof(modes[0])))
        conf.tv_override_koef=0;
    
    return modes[conf.tv_override_koef]; 
}

const char* gui_iso_override_koef_enum(int change, int arg) {
    static const char* modes[]={ "Off","1", "10","100"};

    conf.iso_override_koef+=change;
    if (conf.iso_override_koef<0)
        conf.iso_override_koef=0;
    else if (conf.iso_override_koef>=(sizeof(modes)/sizeof(modes[0])))
        conf.iso_override_koef=sizeof(modes)/sizeof(modes[0])-1;
    
    return modes[conf.iso_override_koef]; 
}

const char* gui_subj_dist_override_value_enum(int change, int arg) {
	static const int koef[] = {0, 1,10,100,1000};
    static char buf[8];
    conf.subj_dist_override_value+=(change*koef[conf.subj_dist_override_koef]);
    if (conf.subj_dist_override_value<0)
        conf.subj_dist_override_value=65500;
    else if (conf.subj_dist_override_value>65500)
        conf.subj_dist_override_value=0;
    sprintf(buf, "%d", (int)conf.subj_dist_override_value);
    return buf; 
}


const char* gui_subj_dist_override_koef_enum(int change, int arg) {
    static const char* modes[]={ "Off","1", "10","100","1000"};

    conf.subj_dist_override_koef+=change;
    if (conf.subj_dist_override_koef<0) conf.subj_dist_override_koef=0;
    else if (conf.subj_dist_override_koef>=(sizeof(modes)/sizeof(modes[0])))
        conf.subj_dist_override_koef=sizeof(modes)/sizeof(modes[0])-1;
    
    return modes[conf.subj_dist_override_koef]; 
}

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

/*const char* gui_tv_enum(int change, int arg) {
    static const char* modes[]={ "Off", "20\"","25\"", "30\"", "40\"", "50\"", "65\""};

    conf.tv_override+=change;
    if (conf.tv_override<0)
        conf.tv_override=0;
    else if (conf.tv_override>=(sizeof(modes)/sizeof(modes[0])))
        conf.tv_override=sizeof(modes)/sizeof(modes[0])-1;

    return modes[conf.tv_override]; 
}*/

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



//-------------------------------------------------------------------
void gui_update_script_submenu() {
    register int p=0, i;

    for (i=0; i<sizeof(script_submenu_items_top)/sizeof(script_submenu_items_top[0]); ++p, ++i) {
        script_submenu_items[p]=script_submenu_items_top[i];
    }
    for (i=0; i<SCRIPT_NUM_PARAMS; ++i) {
        if (script_params[i][0]) {
            script_submenu_items[p].text=(int)script_params[i];
            script_submenu_items[p].type=MENUITEM_INT;
            script_submenu_items[p].value=&conf.ubasic_vars[i];
            ++p;
        }
    }
    for (i=0; i<sizeof(script_submenu_items_bottom)/sizeof(script_submenu_items_bottom[0]); ++p, ++i) {
        script_submenu_items[p]=script_submenu_items_bottom[i];
    }
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
    gui_splash = (conf.splash_show)?SPLASH_TIME:0;
    gui_lang_init();
    draw_init();

    exposition_thresh = screen_size/500;
    voltage_step = (conf.batt_step_25)?25:1;
    load_bad_pixels_list("A/CHDK/badpixel");
}

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

//-------------------------------------------------------------------
void gui_redraw()
{
    enum Gui_Mode gui_mode_old;
    static int show_script_console=0;

    if (gui_splash) {
        if (gui_splash>(SPLASH_TIME-4)) {
            gui_draw_splash();
        } else if (gui_splash==1 && (mode_get()&MODE_MASK) == gui_splash_mode && (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT)) {
            draw_restore();
        }
        --gui_splash;
    }

    gui_in_redraw = 1;
    gui_mode_old = gui_mode;

    switch (gui_mode) {
        case GUI_MODE_MENU:
            gui_menu_draw();
            draw_txt_string(20, 14, "<CNF>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            break;
        case GUI_MODE_ALT:
            gui_draw_osd();
            draw_txt_string(20, 14, "<ALT>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            if ((mode_get()&MODE_MASK) == MODE_REC) {
                draw_txt_string(0, 14, script_title, MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
                if (state_kbd_script_run) show_script_console=5;
                if (show_script_console) {
                    --show_script_console;
                    md_draw_grid();
                    script_console_draw();
                }
            }
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
        case GUI_MODE_REVERSI:
            gui_reversi_draw();
            break;
        case GUI_MODE_SOKOBAN:
            gui_sokoban_draw();
            break;
        case GUI_MODE_DEBUG:
            gui_debug_draw();
            break;
        case GUI_MODE_FSELECT:
            gui_fselect_draw();
            break;
        case GUI_MODE_READ:
            gui_read_draw();
            break;
        case GUI_MODE_OSD:
            gui_osd_draw();
//            draw_txt_string(20, 14, "<OSD>", MAKE_COLOR(COLOR_ALT_BG, COLOR_FG));
            break;
        case GUI_MODE_CALENDAR:
            gui_calendar_draw();
            break;
        case GUI_MODE_BENCH:
            gui_bench_draw();
            break;
        case GUI_MODE_MPOPUP:
            gui_mpopup_draw();
            break;
        default:
            break;
    }
    
    gui_in_redraw = 0;
    if ((gui_mode_old != gui_mode && (gui_mode_old != GUI_MODE_NONE && gui_mode_old != GUI_MODE_ALT) && (gui_mode != GUI_MODE_MBOX && gui_mode != GUI_MODE_MPOPUP)) || gui_restore) {
        gui_restore = 0;
        if (gui_mode != GUI_MODE_REVERSI && gui_mode != GUI_MODE_SOKOBAN)
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
                gui_menu_init(&root_menu);
#if defined (CAMERA_g7) || defined (CAMERA_a710)
                if (get_part_count()==2){
                 int misc_menu_count;
                 misc_menu_count=sizeof(misc_submenu_items)/sizeof(misc_submenu_items[0]);
                 if (misc_submenu_items[misc_menu_count-2].text==0){
                  misc_submenu_items[misc_menu_count-2]=misc_submenu_items[misc_menu_count-3];
                  misc_submenu_items[misc_menu_count-3]=swap_menuitem;
                 }
                }
#endif
                gui_mode = GUI_MODE_MENU;
                draw_restore();
                break;
            case GUI_MODE_MENU:
#ifdef OPTIONS_AUTOSAVE
                conf_save_new_settings_if_changed();
#endif
                gui_mode = GUI_MODE_ALT;
                draw_restore();
                break;
            case GUI_MODE_PALETTE:
            case GUI_MODE_REVERSI:
            case GUI_MODE_SOKOBAN:
            case GUI_MODE_DEBUG:
            case GUI_MODE_OSD:
            case GUI_MODE_CALENDAR:
            case GUI_MODE_BENCH:
                draw_restore();
                gui_mode = GUI_MODE_MENU;
                break;
            case GUI_MODE_FSELECT:
                gui_fselect_kbd_process();
                break;
            case GUI_MODE_READ:
                gui_read_kbd_process();
                draw_restore();
                gui_mode = GUI_MODE_MENU;
                break;
            default:
                break;
        }
        return;
    }
    
    switch (gui_mode) {
        case GUI_MODE_ALT:
            if (kbd_is_key_clicked(SHORTCUT_TOGGLE_RAW)) {
                if (conf.ns_enable_memdump) {
                    dump_memory();
                } else {
                    conf.save_raw = !conf.save_raw;
                    draw_restore();
                }
            } else if (kbd_is_key_clicked(KEY_SET)) {
                gui_menu_init(&script_submenu);
                gui_mode = GUI_MODE_MENU;
                draw_restore();
            } else {
#if !defined(CAMERA_g7) && !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined (CAMERA_a560)
			  if (shooting_get_focus_mode()){ 
				if (kbd_is_key_clicked(KEY_RIGHT)) {
				  gui_subj_dist_override_koef_enum(1,0);
                  gui_osd_draw_state();
                  shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
				  }
				else if (kbd_is_key_clicked(KEY_LEFT)) 
				  {
				  gui_subj_dist_override_koef_enum(-1,0);
                  gui_osd_draw_state();
                  shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
				  }
				else  
				switch (kbd_get_autoclicked_key()) {
				  case KEY_ZOOM_IN:
                  gui_subj_dist_override_value_enum(1,0);
                  gui_osd_draw_state();
                  shooting_set_focus(shooting_get_subject_distance_override_value(),SET_NOW);
                  break;
                 case KEY_ZOOM_OUT:
                  gui_subj_dist_override_value_enum(-1,0);
                  gui_osd_draw_state();
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
    	case GUI_MODE_REVERSI:
            gui_reversi_kbd_process();
            break;
    	case GUI_MODE_SOKOBAN:
            gui_sokoban_kbd_process();
            break;
    	case GUI_MODE_DEBUG:
            gui_debug_kbd_process();
            break;
    	case GUI_MODE_FSELECT:
            gui_fselect_kbd_process();
            break;
    	case GUI_MODE_READ:
            gui_read_kbd_process();
            break;
    	case GUI_MODE_OSD:
            gui_osd_kbd_process();
            break;
    	case GUI_MODE_CALENDAR:
            gui_calendar_kbd_process();
            break;
    	case GUI_MODE_BENCH:
            gui_bench_kbd_process();
            break;
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
    if ((conf.alt_prevent_shutdown == ALT_PREVENT_SHUTDOWN_ALT && !state_kbd_script_run) 
        || conf.alt_prevent_shutdown == ALT_PREVENT_SHUTDOWN_ALT_SCRIPT) {
        disable_shutdown();
    }
    gui_mode = GUI_MODE_ALT;
}

//-------------------------------------------------------------------
void gui_kbd_leave()
{
    // XXX restore palette
#ifdef OPTIONS_AUTOSAVE
    conf_save_new_settings_if_changed();
#endif
    ubasic_error = 0;
    draw_restore();
    if (gui_mode == GUI_MODE_READ && !rbf_load(conf.menu_rbf_file))
        rbf_load_from_8x16(current_font);
    rbf_set_codepage(FONT_CP_WIN);
    enable_shutdown();
    gui_mode = GUI_MODE_NONE;
}

//-------------------------------------------------------------------
extern long physw_status[3];
extern long GetPropertyCase(long opt_id, void *buf, long bufsize);
//extern int xxxx, eeee;
//-------------------------------------------------------------------
void gui_draw_osd() {
    unsigned int m, n = 0, mode_photo;
    coord x;
    static int flashlight = 0, zebra = 0, zebra_init = 0, pressed = 0;
    static int half_disp_press_old=0;
    int half_disp_press;

    m = mode_get();

    if (conf.flashlight && (m&MODE_SCREEN_OPENED) && (m&MODE_SCREEN_ROTATED) && (gui_mode==GUI_MODE_NONE /* || gui_mode==GUI_MODE_ALT */)) {
        draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
        flashlight = 1;
    }
    if (flashlight) {
        if ((!((m&MODE_SCREEN_OPENED) && (m&MODE_SCREEN_ROTATED))) || (gui_mode!=GUI_MODE_NONE /* && gui_mode!=GUI_MODE_ALT */)) {
            flashlight = 0;
            draw_restore();
        }
        return;
    }
    
    if (kbd_is_key_pressed(KEY_SHOOT_HALF)) {
        if (kbd_is_key_pressed(SHORTCUT_TOGGLE_ZEBRA)) {
            if (!pressed) {
                conf.zebra_draw = !conf.zebra_draw;
                if (zebra && !conf.zebra_draw) {
                    zebra = 0;
                    draw_restore();
                }
                pressed = 1;
            }
        }
         else if (kbd_is_key_pressed(SHORTCUT_TOGGLE_HISTO)) {
            if (!pressed) {
                conf.show_histo = !conf.show_histo;
                if (!conf.show_histo) {
                    draw_restore();
                }
                pressed = 1;
            }
        } else if (kbd_is_key_pressed(SHORTCUT_TOGGLE_OSD)) {
            if (!pressed) {
                conf.show_osd = !conf.show_osd;
                if (!conf.show_osd) {
                    draw_restore();
                }
                pressed = 1;
            }
        } else {
            pressed = 0;
        }
    } else {
        pressed = 0;
    }
    
    mode_photo = (m&MODE_MASK) == MODE_PLAY || 
                 !((m&MODE_SHOOTING_MASK)==MODE_VIDEO_STD || 
				 (m&MODE_SHOOTING_MASK)==MODE_VIDEO_SPEED ||  
				 (m&MODE_SHOOTING_MASK)==MODE_VIDEO_COMPACT ||
				 (m&MODE_SHOOTING_MASK)==MODE_VIDEO_MY_COLORS || 
				 (m&MODE_SHOOTING_MASK)==MODE_VIDEO_COLOR_ACCENT || 
				 (m&MODE_SHOOTING_MASK)==MODE_STITCH);

    half_disp_press=mode_photo && kbd_is_key_pressed(KEY_SHOOT_HALF) && kbd_is_key_pressed(KEY_DISPLAY);
    if (half_disp_press && ! half_disp_press_old) draw_restore();
    half_disp_press_old=half_disp_press;
    if (half_disp_press) return;

    if (conf.zebra_draw && gui_mode==GUI_MODE_NONE && kbd_is_key_pressed(KEY_SHOOT_HALF) && mode_photo) {
        if (!zebra_init) {
            zebra_init = 1;
            gui_osd_zebra_init();
        }
        zebra = gui_osd_draw_zebra();
    }
    if (zebra_init && !kbd_is_key_pressed(KEY_SHOOT_HALF)) {
        zebra_init = 0;
    }
    if (zebra) {
        if (!kbd_is_key_pressed(KEY_SHOOT_HALF)) {
            zebra = 0;
            draw_restore();
        }
        return;
    }
    
    if (conf.show_histo && (gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && kbd_is_key_pressed(KEY_SHOOT_HALF) && (mode_photo || (m&MODE_SHOOTING_MASK)==MODE_STITCH)) {
        gui_osd_draw_histo();
    }

    if (!(conf.show_osd && (canon_menu_active==(int)&canon_menu_active-4) && (canon_shoot_menu_active==0)))  return;
    
    if (((m&MODE_MASK) == MODE_REC) && ((recreview_hold==0) || (conf.show_osd_in_review)) ) {
//        m &= MODE_SHOOTING_MASK;
//        if (m==MODE_SCN_WATER || m==MODE_SCN_NIGHT || m==MODE_SCN_CHILD || m==MODE_SCN_PARTY || m==MODE_STITCH ||
//            m==MODE_SCN_GRASS || m==MODE_SCN_SNOW  || m==MODE_SCN_BEACH || m==MODE_SCN_FIREWORK || m==MODE_VIDEO)
//            ++n;

        if (conf.show_grid_lines) {
            gui_grid_draw_osd(1);
        }
        if ((gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && (kbd_is_key_pressed(KEY_SHOOT_HALF) || (state_kbd_script_run) || (shooting_get_focus_mode())) && (mode_photo || (m&MODE_SHOOTING_MASK)==MODE_STITCH)) {
        	 
           if (conf.show_dof!=DOF_DONT_SHOW) gui_osd_calc_dof();
           
           if (conf.show_dof==DOF_SHOW_IN_DOF) gui_osd_draw_dof();  
           
           if (conf.values_show_real_iso || conf.values_show_market_iso || conf.values_show_ev_seted || conf.values_show_ev_measured || conf.values_show_bv_measured || conf.values_show_bv_seted || conf.values_show_overexposure || conf.values_show_canon_overexposure) gui_osd_calc_expo_param();           	           
           
           if (conf.show_state) gui_osd_draw_state();
        }
        else if (conf.show_state) gui_osd_draw_state();

	    if (conf.show_values) gui_osd_draw_values();
    }

    if (recreview_hold==0) gui_batt_draw_osd();
    
    if ((conf.show_clock) && (recreview_hold==0)) {
        gui_osd_draw_clock();
    }

#if defined (CAMERA_ixus700_sd500) || defined (CAMERA_ixus800_sd700)
    if (gui_mode==GUI_MODE_NONE && kbd_is_key_pressed(KEY_SHOOT_HALF) && ((m&MODE_MASK)==MODE_REC)&&((m&MODE_SHOOTING_MASK))!=MODE_VIDEO_STD) {    
     strcpy(osd_buf,shooting_get_tv_str());
     strcat(osd_buf,"\"  ");
     strcat(osd_buf,shooting_get_av_str());
     draw_txt_string(22-strlen(osd_buf)/2, 14, osd_buf, conf.osd_color);
    }
#endif

    if (debug_vals_show) {
//        long v=get_file_counter();
//	sprintf(osd_buf, "1:%03d-%04d  ", (v>>18)&0x3FF, (v>>4)&0x3FFF);
//	sprintf(osd_buf, "1:%d, %08X  ", xxxx, eeee);
	sprintf(osd_buf, "1:%8x  ", physw_status[0]);
	draw_txt_string(28, 10, osd_buf, conf.osd_color);

	sprintf(osd_buf, "2:%8x  ", physw_status[1]);
	draw_txt_string(28, 11, osd_buf, conf.osd_color);

	sprintf(osd_buf, "3:%8x  ", physw_status[2]);
	draw_txt_string(28, 12, osd_buf, conf.osd_color);

//      sprintf(osd_buf, "4:%8x  ", vid_get_viewport_fb_d());
        sprintf(osd_buf, "4:%8x  ", get_usb_power(1));
	draw_txt_string(28, 13, osd_buf, conf.osd_color);
    }

   {
	static char sbuf[100];
    int r,i, p, len;
    if (debug_propcase_show){

	for (i=0;i<10;i++){
	    r = 0;
	    p = debug_propcase_page*10+i;
	    get_property_case(p, &r, 4);
	    sprintf(sbuf, "%3d: %d              ", p, r);sbuf[20]=0;
	    draw_string(64,16+16*i,sbuf, conf.osd_color);
	}
    }

if (debug_pardata_show){
        extern long* FlashParamsTable[]; 
	char s[30];
	int count;

	for (i=0;i<10;i++){
	    r = 0;
	    p = debug_propcase_page*10+i;
	    if (p>=get_flash_params_count())  sprintf(sbuf, "%3d: This parameter does not exists", p);
	    else   {
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

    sprintf(buf, lang_str(LANG_MSG_BUILD_INFO_TEXT), HDK_VERSION, BUILD_NUMBER, __DATE__, __TIME__, PLATFORM, PLATFORMSUB);
    gui_mbox_init(LANG_MSG_BUILD_INFO_TITLE, (int)buf, MBOX_FUNC_RESTORE|MBOX_TEXT_LEFT, NULL);
}

//-------------------------------------------------------------------
void gui_show_memory_info(int arg) {
    static char buf[64];
    int size, l_size, d;
    char* ptr;

    size = 16;
    while (1) {
        ptr= malloc(size);
        if (ptr) {
            free(ptr);
            size <<= 1;
        } else
            break;
    }

    l_size = size;
    size >>= 1;
    d=1024;
    while (d) {
        ptr = malloc(size);
        if (ptr) {
            free(ptr);
            d = l_size-size;
            if (d<0) d=-d;
            l_size = size;
            size += d>>1;
        } else {
            d = size-l_size;
            if (d<0) d=-d;
            l_size = size;
            size -= d>>1;
        }
        
    }
    
    sprintf(buf, lang_str(LANG_MSG_MEMORY_INFO_TEXT), size-1);
    gui_mbox_init(LANG_MSG_MEMORY_INFO_TITLE, (int)buf, MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
}

//-------------------------------------------------------------------
void gui_draw_reversi(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE,
                      MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
        return;
    }
    gui_mode = GUI_MODE_REVERSI;
    gui_reversi_init();
}

//-------------------------------------------------------------------
void gui_draw_sokoban(int arg) {
    if ((mode_get()&MODE_MASK) != MODE_PLAY) {
        gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE,
                      MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, NULL);
        return;
    }
    gui_mode = GUI_MODE_SOKOBAN;
    gui_sokoban_init();
}

//-------------------------------------------------------------------
void gui_draw_debug(int arg) {
//    gui_debug_init(0x2510);
//    gui_debug_init(0x127E0);
//    gui_debug_init(0x7F5B8);
//    gui_debug_init(malloc(16));
    gui_debug_init((void*)0xB054);
}

//-------------------------------------------------------------------
void gui_draw_bench(int arg) {
    gui_mode = GUI_MODE_BENCH;
    gui_bench_init();
}

//-------------------------------------------------------------------
void gui_draw_splash() {
    coord w, h, x, y;
    static const char *text[] = {
        "CHDK Firmware '" HDK_VERSION ", #" BUILD_NUMBER "'" , 
        "Build: " __DATE__ " " __TIME__ ,
        "Camera: " PLATFORM " - " PLATFORMSUB };
    int i, l;
    color cl = MAKE_COLOR((gui_splash_mode==MODE_REC)?0xDA:0xD9, COLOR_WHITE);

    gui_splash_mode = (mode_get()&MODE_MASK);

    h=sizeof(text)/sizeof(text[0])*FONT_HEIGHT+8;
    w=0;
    for (i=0; i<sizeof(text)/sizeof(text[0]); ++i) {
        l=strlen(text[i]);
        if (l>w) w=l;
    }
    w=w*FONT_WIDTH+10;

    x = (screen_width-w)>>1; y = (screen_height-h)>>1;
    draw_filled_rect(x, y, x+w, y+h, cl);
    for (i=0; i<sizeof(text)/sizeof(text[0]); ++i) {
        draw_string(x+((w-strlen(text[i])*FONT_WIDTH)>>1), y+i*FONT_HEIGHT+4, text[i], cl);
    }
}

//-------------------------------------------------------------------
void gui_draw_fselect(int arg) {
    gui_fselect_init(LANG_STR_FILE_BROWSER, "A", NULL);
}

//-------------------------------------------------------------------
static void gui_load_script_selected(const char *fn) {
    if (fn)
        script_load(fn);
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

//-------------------------------------------------------------------
void gui_menuproc_mkbootdisk(int arg) {
    mark_filesystem_bootable();
}

//-------------------------------------------------------------------
void gui_draw_calendar(int arg) {
    gui_mode = GUI_MODE_CALENDAR;
    gui_calendar_init();
}

//-------------------------------------------------------------------
static void gui_draw_rbf_selected(const char *fn) {
    if (fn) {
        strcpy(conf.reader_rbf_file, fn);
    }
}
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

//-------------------------------------------------------------------
