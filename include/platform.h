#ifndef PLATFORM_H
#define PLATFORM_H

#define SSID_INVALID (-32767)
#define ASID_INVALID (-32767)

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

long get_tick_count();

/******************************************************************/

void kbd_key_press(long key);
void kbd_key_release(long key);
void kbd_key_release_all();
long kbd_is_key_pressed(long key);
long kbd_is_key_clicked(long key);
long kbd_get_pressed_key();
long kbd_get_clicked_key();

/******************************************************************/

void *vid_get_bitmap_fb();
long vid_get_bitmap_width();
long vid_get_bitmap_height();
void *vid_get_viewport_fb();

/******************************************************************/

void *hook_raw_fptr();
void *hook_raw_ret_addr();
char *hook_raw_image_addr();
long hook_raw_size();

/******************************************************************/

long lens_get_zoom_pos();
void lens_set_zoom_pos(long newpos);
long lens_get_zoom_point();
void lens_set_zoom_point(long newpt);
long lens_get_focus_pos();
void lens_set_focus_pos(long newpos);

/******************************************************************/

int shooting_in_progress();

int shooting_get_tv();
void shooting_set_tv(int v);
void shooting_set_tv_rel(int v);
const ShutterSpeed *shooting_get_tv_line();

int shooting_get_av();
void shooting_set_av(int v);
void shooting_set_av_rel(int v);

/******************************************************************/

long stat_get_vbatt();

/******************************************************************/
void __attribute__((noreturn)) shutdown();
void debug_led(int state);
#define started() debug_led(1)
#define finished() debug_led(0)

#endif
