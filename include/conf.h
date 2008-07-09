#ifndef CONF_H
#define CONF_H

#include "gui.h"
#include "script.h"

#define USER_MENU_ITEMS 14

typedef struct {
    unsigned short  x, y;
} OSD_pos;

typedef struct {
    int save_raw;
    int save_raw_in_video;
    int raw_in_dir;
    int raw_prefix;
    int raw_ext;
    int raw_save_first_only; //for series shooting
    int raw_nr;

    int show_osd;
    int hide_osd_in_playback;
    int show_osd_in_review;
    int script_shoot_delay;
    int show_histo;
    int ubasic_vars[SCRIPT_NUM_PARAMS];
    char script_file[100];

    int show_dof;
    int batt_volts_max;
    int batt_volts_min;
    int batt_step_25;
    int batt_perc_show;
    int batt_volts_show;
    int batt_icon_show;
    int space_bar_show;
    int space_bar_size;
    int space_bar_width;
    int space_icon_show;
    int show_clock;
    int clock_format;
    int clock_indicator;
    int clock_halfpress;
    int space_perc_show;
    int space_mb_show;
    int space_perc_warn;
    int space_mb_warn;
    int space_warn_type;
    int show_movie_time;
    int show_movie_refresh;


    int zoom_value;

    int show_state;
    int show_remaining_raw;
    int remaining_raw_treshold;
    int show_raw_state;
    int show_values;
    int show_values_in_video;
    int show_overexp;

    int histo_mode;
    int histo_auto_ajust;
    int histo_ignore_boundary;
    int histo_layout;
    int histo_show_ev_grid;

    int zebra_draw;
    int zebra_mode;
    int zebra_restore_screen;
    int zebra_restore_osd;
    int zebra_over;
    int zebra_under;
    int zebra_draw_osd;
    int zebra_multichannel;

    OSD_pos histo_pos;
    OSD_pos dof_pos;
    OSD_pos batt_icon_pos;
    OSD_pos space_icon_pos;
    OSD_pos space_hor_pos;
    OSD_pos space_ver_pos;
    OSD_pos batt_txt_pos;
    OSD_pos space_txt_pos;
    OSD_pos mode_state_pos;
    OSD_pos mode_raw_pos;
    OSD_pos values_pos;
    OSD_pos clock_pos;
    OSD_pos mode_video_pos;
    OSD_pos mode_ev_pos;

    color histo_color;
    color histo_color2; // markers/border
    color osd_color;
    color osd_color_warn;
    color batt_icon_color;
    color space_color;
    color menu_color;
    color menu_title_color;
    color menu_cursor_color;
    color menu_symbol_color;
    int menu_center;
    int menu_symbol_enable;
    color reader_color;
    color zebra_color; // under/over
    color grid_color;
    color osd_color_override;

    int font_cp;
    char menu_rbf_file[100];
    char menu_symbol_rbf_file[100];

    char lang_file[100];

    char reader_file[100];
    int  reader_pos;
    int  reader_autoscroll;
    int  reader_autoscroll_delay;
    char reader_rbf_file[100];
    int  reader_codepage;
    int  reader_wrap_by_words;

    int sokoban_level;

    int flashlight;
    int fast_ev;
    int fast_ev_step;
    int splash_show;

    int use_zoom_mf;
    long alt_mode_button; //for S-series
    int alt_prevent_shutdown;

    int show_grid_lines;
    char grid_lines_file[100];
    int grid_force_color;

    int video_mode;
    int video_quality;
    int video_bitrate;
      
    int tv_bracket_value;
    int av_bracket_value;
    int iso_bracket_value;
    int iso_bracket_koef;
    int subj_dist_bracket_value;
    int subj_dist_bracket_koef;
    int bracket_type;
    int clear_bracket;
    int clear_video;
    int override_disable;
    int override_disable_all;


    int tv_override_value;
    int tv_override_koef;
    int tv_enum_type;
    int av_override_value;
    
    int nd_filter_state;
    
    int iso_override_value;
    int iso_override_koef;
    int subj_dist_override_value;
    int subj_dist_override_koef;
    int clear_override;
    
    int autoiso_enable;
    int autoiso_shutter;
    int autoiso_user_factor;
    int autoiso_is_factor;
    int autoiso_max_iso_hi;
    int autoiso_max_iso_auto;
    int autoiso_min_iso;

    int recalc_exposure;
    int tv_exposure_order;
    int av_exposure_order;
    int iso_exposure_order;

    int dof_subj_dist_as_near_limit;
    int dof_use_exif_subj_dist;
    int dof_subj_dist_in_misc;
    int dof_near_limit_in_misc;
    int dof_far_limit_in_misc;
    int dof_hyperfocal_in_misc;
    int dof_depth_in_misc;
    int dof_dist_from_lens;
    
    
    int values_show_in_review;
    int values_show_zoom;
    int values_show_real_aperture;		
    int values_show_real_iso;
    int values_show_market_iso;
    int values_show_iso_only_in_autoiso_mode;
    int values_show_ev_seted;
    int values_show_ev_measured;
    int values_show_bv_measured;
    int values_show_bv_seted;
    int values_show_overexposure;
    int values_show_canon_overexposure;
    int values_show_luminance;

    int ns_enable_memdump;
    int script_startup;			// remote autostart
    int remote_enable;			// remote enable
    int user_menu_enable;
    int user_menu_vars[USER_MENU_ITEMS];
    int user_menu_as_root;
    int zoom_scale;
    int unlock_optical_zoom_for_video;
    int mute_on_zoom;
    int bad_pixel_removal;
    int video_af_key;
    
    char curve_file[100];
    int curve_enable;
    
    int edge_overlay_enable;
    int edge_overlay_thresh;
    color edge_overlay_color;

    int synch_enable;
    int ricoh_ca1_mode;
    int synch_delay_enable;
    int synch_delay_value;
    int synch_delay_coarse_value;

    int script_param_set;
    
    long mem_view_addr_init;
} Conf;

extern Conf conf;

#define ALT_PREVENT_SHUTDOWN_NO         0
#define ALT_PREVENT_SHUTDOWN_ALT        1
#define ALT_PREVENT_SHUTDOWN_ALT_SCRIPT 2

#define SHOOTING_PROGRESS_NONE          0
#define SHOOTING_PROGRESS_STARTED       1
#define SHOOTING_PROGRESS_PROCESSING    2
#define SHOOTING_PROGRESS_DONE          3

extern int state_kbd_script_run;
extern int state_shooting_progress;
extern int state_save_raw_nth_only;
extern int state_expos_recalculated;
extern int state_expos_under;
extern int state_expos_over;

extern int state_debug1;
extern int debug_propcase_show;
extern int debug_propcase_page;
extern int debug_vals_show;
extern int debug_pardata_show;
extern void script_autostart();				// remote autostart
extern void conf_save();
extern void conf_restore();
extern void conf_load_defaults();
extern int shutter_int;

#endif
