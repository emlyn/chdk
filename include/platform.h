#ifndef PLATFORM_H
#define PLATFORM_H

#define SSID_INVALID (-32767)
#define ASID_INVALID (-32767)

#define MODE_MASK               0x0300
#define MODE_REC                0x0100
#define MODE_PLAY               0x0200

#define MODE_SHOOTING_MASK      0x00FF
#define MODE_AUTO               1
#define MODE_P                  2
#define MODE_TV                 3
#define MODE_AV                 4
#define MODE_M                  5
#define MODE_PORTRAIT           6
#define MODE_NIGHT              7
#define MODE_LANDSCAPE          8
#define MODE_VIDEO              9
#define MODE_STITCH             10
#define MODE_MY_COLORS          11
#define MODE_SCN_WATER          12
#define MODE_SCN_NIGHT          13
#define MODE_SCN_CHILD          14
#define MODE_SCN_PARTY          15
#define MODE_SCN_GRASS          16
#define MODE_SCN_SNOW           17
#define MODE_SCN_BEACH          18
#define MODE_SCN_FIREWORK       19
#define MODE_SCN_COLOR_ACCENT   20

#define MODE_SCREEN_MASK        0x0C00
#define MODE_SCREEN_OPENED      0x0400
#define MODE_SCREEN_ROTATED     0x0800

typedef struct {
    short int id; // hacks id
    short int prop_id; // Canons id
    char name[8];
    short int shutter_dfs_value; // shutter speed to use dark frame substraction
} ISOTable;

typedef struct {
    short int id; // hacks id
    short int prop_id; // Canons id
    char name[8];
    long usec;
} ShutterSpeed;

typedef struct {
    short int id; // hacks id
    short int prop_id; // Canons id
    char name[8];
} ApertureSize;

/******************************************************************/

extern const int dof_tbl[], dof_tbl_size;

/******************************************************************/

long get_tick_count();

void remount_filesystem();
void mark_filesystem_bootable();

/******************************************************************/

long get_parameter_data(long id, void *buf, long bufsize);
long set_parameter_data(long id, void *buf, long bufsize);

long get_property_case(long id, void *buf, long bufsize);
long set_property_case(long id, void *buf, long bufsize);

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

/******************************************************************/

long vid_is_bitmap_shown();
void *vid_get_bitmap_fb();
long vid_get_bitmap_width();
long vid_get_bitmap_height();
void *vid_get_viewport_fb();
void *vid_get_viewport_live_fb();
void vid_bitmap_refresh();

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
long lens_get_focus_pos();
void lens_set_focus_pos(long newpos);

long lens_get_target_distance();

/******************************************************************/

int shooting_in_progress();
int shooting_is_flash_ready();

int shooting_get_tv();
void shooting_set_tv(int v);
void shooting_set_tv_rel(int v);
const ShutterSpeed *shooting_get_tv_line();

int shooting_get_av();
void shooting_set_av(int v);
void shooting_set_av_rel(int v);

int shooting_get_real_av();
long shooting_get_current_mode();

/******************************************************************/

long stat_get_vbatt();

/******************************************************************/

long vbatt_get_min();
long vbatt_get_max();

/******************************************************************/
void __attribute__((noreturn)) shutdown();
void debug_led(int state);
#define started() debug_led(1)
#define finished() debug_led(0)

#endif
