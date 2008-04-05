#include "platform.h"
#include "keyboard.h"
#include "conf.h"
#include "histogram.h"
#include "font.h"
#include "camera.h"
#include "raw.h"
#include "gui_draw.h"
#include "gui_osd.h"
#include "gui_grid.h"
#include "core.h"
#include "stdlib.h"
#include "script.h"

//-------------------------------------------------------------------
#define CONF_FILE  "A/CHDK/CHDK.CFG"
#define CONF_MAGICK_VALUE (0x33204741)

#define CONF_INFO(id, param, type, def, func) { id, sizeof( param ), &param , type, {def}, func }
#define CONF_DEF_PTR    1
#define CONF_DEF_VALUE  2

//-------------------------------------------------------------------
typedef struct {
    unsigned short      id;
    unsigned short      size;
    void                *var;
    int                 type;
    union {
        void            *ptr;
        int             i;
        color           cl;
    };
    void                (*func)();
} ConfInfo;

//-------------------------------------------------------------------
Conf conf;

int state_shooting_progress = SHOOTING_PROGRESS_NONE;
int state_save_raw_nth_only;
int state_expos_recalculated;
int state_expos_under;
int state_expos_over;
int auto_started;

int state_debug1;
int debug_propcase_show;
int debug_propcase_page;
int debug_vals_show;
int debug_pardata_show;

//-------------------------------------------------------------------
static int def_ubasic_vars[SCRIPT_NUM_PARAMS] = {0};
static int def_batt_volts_max, def_batt_volts_min;
static OSD_pos def_histo_pos, def_dof_pos, def_batt_icon_pos, def_space_icon_pos, def_space_hor_pos, def_space_ver_pos, def_batt_txt_pos, def_space_txt_pos, 
               def_mode_state_pos, def_mode_raw_pos, def_values_pos, def_clock_pos;
static int def_user_menu_vars[10] = {0};

static void conf_change_script_file();
static void conf_change_histo_mode();
static void conf_change_histo_layout();
static void conf_change_font_cp();
static void conf_change_menu_rbf_file();
static void conf_change_alt_mode_button();
static void conf_change_grid_file();
static void conf_change_video_bitrate();

void ubasic_camera_set_raw(int mode)
{
    conf.save_raw = mode;
}

void ubasic_camera_set_nr(int mode)
{
	// "Auto", "Off", "On"
    conf.raw_nr = mode;
}
int ubasic_camera_script_autostart()
{	
	// 1 = Autostarted
	return auto_started;
}

void ubasic_camera_set_script_autostart(int state)
{	
	// 1 = Autostarted
	auto_started = state;
}

int ubasic_camera_get_nr()
{
	// "Auto", "Off", "On"
    return conf.raw_nr;
}


void clear_values()
{	
	if (conf.clear_override)
	{
	 conf.av_override_value=0;
	 conf.tv_override_koef=0;
	 conf.subj_dist_override_koef=0;
	 conf.iso_override_koef=0;
	 conf.nd_filter_state=0;
	}
	if (conf.clear_bracket)
	{
	 conf.av_bracket_value=0;
	 conf.tv_bracket_value=0;
	 conf.iso_bracket_koef=0;
	 conf.subj_dist_bracket_koef=0;
	}
}

static const ConfInfo conf_info[] = {
/* !!! Do NOT change ID for items defined already! Append a new one at the end! !!! */
    CONF_INFO(  1, conf.show_osd,               CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO(  2, conf.save_raw,               CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(  3, conf.script_shoot_delay,     CONF_DEF_VALUE, i:20, NULL),
    CONF_INFO(  4, conf.show_histo,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(  5, conf.ubasic_vars,            CONF_DEF_PTR,   ptr:&def_ubasic_vars, NULL),
    CONF_INFO(  6, conf.script_file,            CONF_DEF_PTR,   ptr:"", conf_change_script_file),
    CONF_INFO(  7, conf.show_dof,               CONF_DEF_VALUE, i:DOF_DONT_SHOW, NULL),
    CONF_INFO(  8, conf.batt_volts_max,         CONF_DEF_PTR,   ptr:&def_batt_volts_max, NULL),
    CONF_INFO(  9, conf.batt_volts_min,         CONF_DEF_PTR,   ptr:&def_batt_volts_min, NULL),
    CONF_INFO( 10, conf.batt_step_25,           CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 11, conf.batt_perc_show,         CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 12, conf.batt_volts_show,        CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 13, conf.batt_icon_show,         CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 14, conf.show_state,             CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 15, conf.show_values,            CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 16, conf.show_overexp,           CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 17, conf.histo_mode,             CONF_DEF_VALUE, i:HISTO_MODE_LINEAR, conf_change_histo_mode),
    CONF_INFO( 18, conf.histo_auto_ajust,       CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 19, conf.histo_ignore_boundary,  CONF_DEF_VALUE, i:4, NULL),
    CONF_INFO( 20, conf.histo_layout,           CONF_DEF_VALUE, i:OSD_HISTO_LAYOUT_A, conf_change_histo_layout),
    CONF_INFO( 21, conf.histo_pos,              CONF_DEF_PTR,   ptr:&def_histo_pos, NULL),
    CONF_INFO( 22, conf.dof_pos,                CONF_DEF_PTR,   ptr:&def_dof_pos, NULL),
    CONF_INFO( 23, conf.batt_icon_pos,          CONF_DEF_PTR,   ptr:&def_batt_icon_pos, NULL),
    CONF_INFO( 24, conf.batt_txt_pos,           CONF_DEF_PTR,   ptr:&def_batt_txt_pos , NULL),
    CONF_INFO( 25, conf.mode_state_pos,         CONF_DEF_PTR,   ptr:&def_mode_state_pos , NULL),
    CONF_INFO( 26, conf.values_pos,             CONF_DEF_PTR,   ptr:&def_values_pos , NULL),
    CONF_INFO( 27, conf.histo_color,            CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_WHITE), NULL),
    CONF_INFO( 28, conf.osd_color,              CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG), NULL),
    CONF_INFO( 29, conf.batt_icon_color,        CONF_DEF_VALUE, cl:COLOR_WHITE, NULL),
    CONF_INFO( 30, conf.menu_color,             CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG), NULL),
    CONF_INFO( 31, conf.reader_color,           CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_GREY, COLOR_WHITE), NULL),
//  32 is not used anymore
    CONF_INFO( 33, conf.flashlight,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 34, conf.ns_enable_memdump,      CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 35, conf.raw_in_dir,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 36, conf.raw_prefix,             CONF_DEF_VALUE, i:RAW_PREFIX_CRW, NULL),
    CONF_INFO( 37, conf.raw_ext,                CONF_DEF_VALUE, i:RAW_EXT_CRW, NULL),
    CONF_INFO( 38, conf.reader_file,            CONF_DEF_PTR,   ptr:"", conf_change_script_file),
    CONF_INFO( 39, conf.reader_pos,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 40, conf.sokoban_level,          CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 41, conf.show_clock,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 42, conf.clock_pos,              CONF_DEF_PTR,   ptr:&def_clock_pos , NULL),
    CONF_INFO( 43, conf.reader_autoscroll,      CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 44, conf.reader_autoscroll_delay,CONF_DEF_VALUE, i:5, NULL),
    CONF_INFO( 45, conf.reader_rbf_file,        CONF_DEF_PTR,   ptr:"", NULL),
    CONF_INFO( 46, conf.reader_codepage,        CONF_DEF_VALUE, i:FONT_CP_WIN, NULL),
    CONF_INFO( 47, conf.splash_show,            CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 48, conf.histo_color2,           CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_RED, COLOR_WHITE), NULL),
    CONF_INFO( 49, conf.zebra_draw,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 50, conf.zebra_mode,             CONF_DEF_VALUE, i:ZEBRA_MODE_BLINKED_2, NULL),
    CONF_INFO( 51, conf.zebra_restore_screen,   CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 52, conf.zebra_restore_osd,      CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 53, conf.zebra_over,             CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO( 54, conf.zebra_under,            CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 55, conf.zebra_color,            CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_RED, COLOR_RED), NULL),
    CONF_INFO( 56, conf.zebra_draw_osd,         CONF_DEF_VALUE, i:ZEBRA_DRAW_HISTO, NULL),
//  57 is not used anymore
    CONF_INFO( 58, conf.zoom_value,             CONF_DEF_VALUE, i:ZOOM_SHOW_X, NULL),
    CONF_INFO( 59, conf.use_zoom_mf,            CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 60, conf.raw_save_first_only,    CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 61, conf.reader_wrap_by_words,   CONF_DEF_VALUE, i:0, NULL),
//  62 is not used anymore
    CONF_INFO( 63, conf.alt_mode_button,        CONF_DEF_VALUE, i:KEY_PRINT, conf_change_alt_mode_button),
    CONF_INFO( 64, conf.lang_file,              CONF_DEF_PTR,   ptr:"", NULL),
    CONF_INFO( 65, conf.font_cp,                CONF_DEF_VALUE, i:FONT_CP_WIN_1251, conf_change_font_cp),
    CONF_INFO( 66, conf.menu_rbf_file,          CONF_DEF_PTR,   ptr:"", conf_change_menu_rbf_file),
    CONF_INFO( 67, conf.alt_prevent_shutdown,   CONF_DEF_VALUE, i:ALT_PREVENT_SHUTDOWN_ALT, NULL),
    CONF_INFO( 68, conf.show_grid_lines,        CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 69, conf.grid_lines_file,        CONF_DEF_PTR,   ptr:"", conf_change_grid_file),
    CONF_INFO( 70, conf.raw_nr,                 CONF_DEF_VALUE, i:NOISE_REDUCTION_AUTO_CANON, NULL),
    CONF_INFO( 71, conf.grid_force_color,       CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO( 72, conf.grid_color,             CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG), NULL),

    CONF_INFO( 80, conf.dof_subj_dist_as_near_limit, CONF_DEF_VALUE, i:0, NULL),	
    CONF_INFO( 81, conf.dof_use_exif_subj_dist,  CONF_DEF_VALUE, i:0, NULL),	
    CONF_INFO( 82, conf.dof_subj_dist_in_misc,   CONF_DEF_VALUE, i:1, NULL),		
    CONF_INFO( 83, conf.dof_near_limit_in_misc,  CONF_DEF_VALUE, i:1, NULL),	
    CONF_INFO( 84, conf.dof_far_limit_in_misc,   CONF_DEF_VALUE, i:1, NULL),		
    CONF_INFO( 85, conf.dof_hyperfocal_in_misc,  CONF_DEF_VALUE, i:1, NULL),			
    CONF_INFO( 86, conf.dof_depth_in_misc,       CONF_DEF_VALUE, i:0, NULL),

	CONF_INFO( 87, conf.values_show_in_review,   CONF_DEF_VALUE, i:0, NULL),					
    CONF_INFO( 88, conf.values_show_zoom,        CONF_DEF_VALUE, i:1, NULL),		
    CONF_INFO( 89, conf.values_show_real_aperture, CONF_DEF_VALUE, i:0, NULL),		
    CONF_INFO( 90, conf.values_show_real_iso,    CONF_DEF_VALUE, i:1, NULL),				
    CONF_INFO( 91, conf.values_show_market_iso,  CONF_DEF_VALUE, i:0, NULL),	
    CONF_INFO( 92, conf.values_show_iso_only_in_autoiso_mode, CONF_DEF_VALUE, i:0, NULL),			
    CONF_INFO( 93, conf.values_show_ev_seted,      CONF_DEF_VALUE, i:0, NULL),			
    CONF_INFO( 94, conf.values_show_ev_measured,      CONF_DEF_VALUE, i:0, NULL),				
    CONF_INFO( 95, conf.values_show_bv_measured,      CONF_DEF_VALUE, i:0, NULL),					
    CONF_INFO( 96, conf.values_show_bv_seted,      CONF_DEF_VALUE, i:0, NULL),						
    CONF_INFO( 97, conf.values_show_overexposure,  CONF_DEF_VALUE, i:0, NULL),							
    CONF_INFO( 98, conf.values_show_luminance,   CONF_DEF_VALUE, i:0, NULL),						

    CONF_INFO( 99, conf.video_mode,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(100, conf.video_quality,          CONF_DEF_VALUE, i:84,NULL),
    CONF_INFO(101, conf.video_bitrate,          CONF_DEF_VALUE, i:3, conf_change_video_bitrate),
    
    CONF_INFO(102, conf.tv_override_value,		    CONF_DEF_VALUE, i:0, NULL),	
    CONF_INFO(103, conf.tv_override_koef,		CONF_DEF_VALUE, i:0, NULL),	

    CONF_INFO(104, conf.av_override_value,			CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(105, conf.iso_override_value,			CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(106, conf.iso_override_koef,		CONF_DEF_VALUE, i:0, NULL),
    
    CONF_INFO(107, conf.subj_dist_override_value,		CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(108, conf.subj_dist_override_koef,	CONF_DEF_VALUE, i:0, NULL),
    
    CONF_INFO(109, conf.tv_bracket_value,	      CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(110, conf.av_bracket_value,		  CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(111, conf.iso_bracket_value,		  CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(112, conf.iso_bracket_koef,	      CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(113, conf.subj_dist_bracket_value,  CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(114, conf.subj_dist_bracket_koef,   CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(115, conf.bracket_type,		 	  CONF_DEF_VALUE, i:0, NULL),
    
    CONF_INFO(116, conf.recalc_exposure,		  CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(117, conf.tv_exposure_order,		   CONF_DEF_VALUE, i:2, NULL),
    CONF_INFO(118, conf.av_exposure_order,				CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO(119, conf.iso_exposure_order,				CONF_DEF_VALUE, i:3, NULL),
    
    CONF_INFO(120, conf.script_startup,         CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(121, conf.remote_enable,         CONF_DEF_VALUE, i:0, NULL),
    
    CONF_INFO(122, conf.values_show_canon_overexposure,  CONF_DEF_VALUE, i:0, NULL),							
    CONF_INFO(123, conf.clear_override,  CONF_DEF_VALUE, i:1, NULL),							
    
    CONF_INFO(124, conf.show_osd_in_review,  CONF_DEF_VALUE, i:0, NULL),							
    
    CONF_INFO(125, conf.dof_dist_from_lens,  CONF_DEF_VALUE, i:0, NULL),
    
    CONF_INFO(126, conf.clear_bracket,  CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO(127, conf.zebra_multichannel,  CONF_DEF_VALUE, i:0, NULL),							

    CONF_INFO(128, conf.nd_filter_state,  CONF_DEF_VALUE, i:0, NULL),							
    CONF_INFO(129, conf.histo_show_ev_grid,  CONF_DEF_VALUE, i:0, NULL),							
    
    CONF_INFO(130, conf.osd_color_warn,   CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_RED), NULL),
    CONF_INFO(131, conf.space_color,              CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_BG, COLOR_FG), NULL),
    CONF_INFO(132, conf.space_icon_show,         CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO(133, conf.space_icon_pos,          CONF_DEF_PTR, ptr:&def_space_icon_pos, NULL),
    CONF_INFO(134, conf.space_perc_show,         CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(135, conf.space_mb_show,        CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO(136, conf.space_txt_pos,           CONF_DEF_PTR,   ptr:&def_space_txt_pos , NULL),
    CONF_INFO(137, conf.show_remaining_raw,             CONF_DEF_VALUE, i:1, NULL),
    CONF_INFO(138, conf.mode_raw_pos,         CONF_DEF_PTR,   ptr:&def_mode_raw_pos , NULL),
    CONF_INFO(139, conf.show_raw_state,  CONF_DEF_VALUE, i:1, NULL),
    
    CONF_INFO(140, conf.show_values_in_video, CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(141, conf.tv_enum_type, CONF_DEF_VALUE, i:1, NULL),

    CONF_INFO(142, conf.user_menu_enable,  CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(143, conf.user_menu_vars,    CONF_DEF_PTR,   ptr:&def_user_menu_vars, NULL),
    CONF_INFO(144, conf.zoom_scale,  CONF_DEF_VALUE, i:100, NULL), 
    CONF_INFO(145, conf.space_bar_show,  CONF_DEF_VALUE, i:1, NULL), 
    CONF_INFO(146, conf.space_bar_size,  CONF_DEF_VALUE, i:1, NULL), 
    CONF_INFO(147, conf.space_ver_pos,          CONF_DEF_PTR, ptr:&def_space_ver_pos, NULL),
    CONF_INFO(148, conf.space_hor_pos,          CONF_DEF_PTR, ptr:&def_space_hor_pos, NULL),   
    CONF_INFO(149, conf.space_bar_width,  CONF_DEF_VALUE, i:2, NULL), 
    CONF_INFO(150, conf.space_perc_warn,         CONF_DEF_VALUE, i:10, NULL),
    CONF_INFO(151, conf.space_mb_warn,        CONF_DEF_VALUE, i:20, NULL),
    CONF_INFO(152, conf.space_warn_type,         CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(153, conf.remaining_raw_treshold,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(154, conf.unlock_optical_zoom_for_video,  CONF_DEF_VALUE, i:0, NULL), 
    CONF_INFO(155, conf.clock_format,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(156, conf.clock_indicator,             CONF_DEF_VALUE, i:0, NULL),
    CONF_INFO(157, conf.clock_halfpress,             CONF_DEF_VALUE, i:1, NULL),
    
    CONF_INFO(158, conf.autoiso_enable,  CONF_DEF_VALUE, i:0, NULL),	
    CONF_INFO(159, conf.autoiso_shutter,  CONF_DEF_VALUE, i:0, NULL),	
    CONF_INFO(160, conf.autoiso_user_factor,  CONF_DEF_VALUE, i:5, NULL),	
    CONF_INFO(161, conf.autoiso_is_factor,  CONF_DEF_VALUE, i:2, NULL),	
    CONF_INFO(162, conf.autoiso_max_iso_hi,  CONF_DEF_VALUE, i:55, NULL),	
    CONF_INFO(163, conf.autoiso_max_iso_auto,  CONF_DEF_VALUE, i:35, NULL),	
    CONF_INFO(164, conf.autoiso_min_iso,  CONF_DEF_VALUE, i:5, NULL),	

    CONF_INFO(165, conf.menu_title_color,         CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_WHITE, COLOR_BLACK), NULL),
    CONF_INFO(166, conf.menu_cursor_color,         CONF_DEF_VALUE, cl:MAKE_COLOR(COLOR_SELECTED_BG, COLOR_SELECTED_FG), NULL),
    CONF_INFO(167, conf.menu_center,         CONF_DEF_VALUE, i:1, NULL),
};
#define CONF_NUM (sizeof(conf_info)/sizeof(conf_info[0]))

//-------------------------------------------------------------------
static void conf_change_histo_mode() {
    histogram_set_mode(conf.histo_mode);
}

static void conf_change_histo_layout() {
    if (conf.histo_layout==OSD_HISTO_LAYOUT_Y || conf.histo_layout==OSD_HISTO_LAYOUT_Y_argb) {
        histogram_set_main(HISTO_Y);
    } else {
        histogram_set_main(HISTO_RGB);
    }
}

static void conf_change_font_cp() {
    font_init();
    font_set(conf.font_cp);
}

static void conf_change_script_file() {
    script_load(conf.script_file);
}

static void conf_change_menu_rbf_file() {
    if (!rbf_load(conf.menu_rbf_file))
        rbf_load_from_8x16(current_font);
    rbf_set_codepage(FONT_CP_WIN);
}

static void conf_change_alt_mode_button() {
#if CAM_ADJUSTABLE_ALT_BUTTON
    kbd_set_alt_mode_key_mask(conf.alt_mode_button);
#else
    conf.alt_mode_button = KEY_PRINT;
#endif
}

static void conf_change_grid_file() {
    grid_lines_load(conf.grid_lines_file);
}

static void conf_change_video_bitrate() {
    shooting_video_bitrate_change(conf.video_bitrate);
 }

//-------------------------------------------------------------------
static void conf_init_defaults() {
    // init some defaults values
    def_batt_volts_max = get_vbatt_max();
    def_batt_volts_min = get_vbatt_min();
    def_histo_pos.x = 45;
    def_histo_pos.y = vid_get_bitmap_height()-HISTO_HEIGHT-40;
    def_dof_pos.x = 90;
    def_dof_pos.y = 45;
    def_batt_icon_pos.x = 178;
    def_batt_icon_pos.y = 0;
    def_batt_txt_pos.x=178;
    def_batt_txt_pos.y=1*FONT_HEIGHT;
    def_space_icon_pos.x = vid_get_bitmap_width()-100;
    def_space_icon_pos.y = 0;
    def_space_ver_pos.x = vid_get_bitmap_width()-7;
    def_space_ver_pos.y = 0;
    def_space_hor_pos.x = 0;
    def_space_hor_pos.y = vid_get_bitmap_height()-7;
    def_space_txt_pos.x=128;
    def_space_txt_pos.y=0;
    def_mode_state_pos.x=35;
    def_mode_state_pos.y=0;
    def_mode_raw_pos.x=vid_get_bitmap_width()-7*FONT_WIDTH-2;
    def_mode_raw_pos.y=vid_get_bitmap_height()-3*FONT_HEIGHT-2;
    def_values_pos.x=vid_get_bitmap_width()-9*FONT_WIDTH;
    def_values_pos.y=30;
    def_clock_pos.x=vid_get_bitmap_width()-5*FONT_WIDTH-2;
    def_clock_pos.y=0;
}

//-------------------------------------------------------------------
void conf_load_defaults() {
    register int i;

    for (i=0; i<CONF_NUM; ++i) {
        switch (conf_info[i].type) {
            case CONF_DEF_VALUE:
                memcpy(conf_info[i].var, &(conf_info[i].i), conf_info[i].size);
                break;
            case CONF_DEF_PTR:
                memcpy(conf_info[i].var, conf_info[i].ptr, conf_info[i].size);
                break;
        }
        if (conf_info[i].func) {
            conf_info[i].func();
        }
    }
}

//-------------------------------------------------------------------
void conf_save() {
    static const long t=CONF_MAGICK_VALUE;
    register int i;
    int fd;
    static char buf[sizeof(t)+CONF_NUM*(sizeof(conf_info[0].id)+sizeof(conf_info[0].size))+sizeof(conf)];
    char *p=buf;

    fd = open(CONF_FILE, O_WRONLY|O_CREAT|O_TRUNC, 0777); 
    if (fd>=0){
        memcpy(p, &t, sizeof(t));
        p+=sizeof(t);
        for (i=0; i<CONF_NUM; ++i) {
            memcpy(p, &(conf_info[i].id), sizeof(conf_info[i].id));
            p+=sizeof(conf_info[i].id);
            memcpy(p, &(conf_info[i].size), sizeof(conf_info[i].size));
            p+=sizeof(conf_info[i].size);
            memcpy(p, conf_info[i].var, conf_info[i].size);
            p+=conf_info[i].size;
        }

        write(fd, buf, p-buf);
        close(fd);
    }
}

//-------------------------------------------------------------------
void conf_restore() {
    int fd, rcnt, i;
    long t;
    unsigned short id, size;
    void *ptr;

    conf_init_defaults();

    conf_load_defaults();

    fd = open(CONF_FILE, O_RDONLY, 0777); 
    if (fd>=0){
        // read magick value
        rcnt = read(fd, &t, sizeof(t));
        if (rcnt==sizeof(t) && t==CONF_MAGICK_VALUE) {
            while (1) {
                rcnt = read(fd, &id, sizeof(id));
                if (rcnt!=sizeof(id)) break;

                rcnt = read(fd, &size, sizeof(size));
                if (rcnt!=sizeof(size)) break;

                for (i=0; i<CONF_NUM; ++i) {
                    if (conf_info[i].id==id && conf_info[i].size==size) {
                        ptr=umalloc(size);
                        if (ptr) {
                            rcnt = read(fd, ptr, size);
                            if (rcnt == size) {
                               memcpy(conf_info[i].var, ptr, size);
                               if (conf_info[i].func) {
                                   conf_info[i].func();
                               }
                            }
                            ufree(ptr);
                        }
                        break;
                    }
                }
                if (i == CONF_NUM) { // unknown id, just skip data
                    lseek(fd, size, SEEK_CUR);
                }
            }
        }
	close(fd);
    }
}

//-------------------------------------------------------------------
