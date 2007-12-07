
void ubasic_camera_press(const char *s);
void ubasic_camera_release(const char *s);
void ubasic_camera_wait_click(int timeout);
int ubasic_camera_is_clicked(const char *s);
void ubasic_camera_click(const char *s);
void ubasic_camera_sleep(long v);
void ubasic_camera_shoot();
int md_detect_motion(void);
int md_get_cell_diff(int column, int row);
int md_init_motion_detector();
void ubasic_camera_set_raw(int mode);
void ubasic_camera_get_raw();
void ubasic_camera_set_nr(int to);
int ubasic_camera_get_nr();
void shooting_set_prop(int id, int v);
int shooting_get_prop(int id);
long stat_get_vbatt();
void ubasic_set_led(int led, int state, int bright);
int shooting_get_day_seconds();
int shooting_get_tick_count();
int ubasic_camera_script_autostart();
int get_usb_power();
void ubasic_camera_set_script_autostart(int state);
void exit_alt();
//#include "../../core/motion_detector.h"




