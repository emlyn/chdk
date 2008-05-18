#ifdef TEST

#include <stdio.h>

static int tv=0, av=0, zoom=0, focus=0, iso=0, raw=0, raw_nr=0,autostart=0; 

#define MODE_REC                0x0100

void ubasic_camera_press(const char *s)
{
    printf("*** button press '%s' ***\n",s);
}

void ubasic_camera_release(const char *s)
{
    printf("*** button release '%s' ***\n",s);
}

void ubasic_camera_click(const char *s)
{
    printf("*** button click '%s' ***\n",s);
}

void ubasic_camera_sleep(int v)
{
    printf("*** sleep %d ***\n",v);
}

void ubasic_camera_shoot()
{
    printf("*** shoot ***\n");
}

void ubasic_camera_wait_click(int t)
{
    printf("*** wait_click %d ***\n", t);
}

int ubasic_camera_is_clicked(const char *s)
{
    printf("*** is_key '%s' ***\n", s);
    return 1;
}

int shooting_get_tv()
{
    return tv;
}

void shooting_set_tv(int v)
{
    tv = v;
    printf("*** set tv %d ***\n",v);
}

void shooting_set_tv_rel(int v)
{
    tv += v;
    printf("*** set tv rel %d ***\n",v);
}

int shooting_get_av()
{
    return av;
}

void shooting_set_av(int v)
{
    av = v;
    printf("*** set av %d ***\n",v);
}

void shooting_set_av_rel(int v)
{
    av += v;
    printf("*** set av rel %d ***\n",v);
}

int shooting_get_zoom()
{
    return zoom;
}

void shooting_set_zoom(int v)
{
    zoom = v;
    printf("*** set zoom %d ***\n",v);
}

void shooting_set_zoom_rel(int v)
{
    zoom += v;
    printf("*** set zoom rel %d ***\n",v);
}

void shooting_set_zoom_speed(int v)
{
    printf("*** set zoom speed %d ***\n",v);
}

int shooting_get_focus()
{
    return focus;
}

void shooting_set_focus(int v)
{
    focus = v;
    printf("*** set focus %d ***\n",v);
}

int shooting_get_iso()
{
    return iso;
}

void shooting_set_iso(int v)
{
    iso = v;
    printf("*** set iso %d ***\n",v);
}
//ARM Begin
int shooting_get_iso_real()
{
  return iso;
}
//ARM End
void script_console_add_line(const char *str) {
    printf(">>> %s\n", str);
}

void script_console_clear() {
    printf("*** clear console ***\n");
}
int md_detect_motion(void)
{
	return 0;
}
int md_get_cell_diff(int column, int row)
{
	return 0;
}
int md_init_motion_detector()
{
	return 0;
}
void ubasic_camera_set_nr(to) 
{
	raw_nr = to;
    printf("*** set raw nr %d ***\n",raw_nr);
};

int ubasic_camera_get_nr(to) 
{
	return raw_nr;
};

void ubasic_camera_set_raw(int mode)
{
	raw = mode;
    printf("*** set raw %d ***\n",raw);
}

int ubasic_camera_get_raw()
{
	return raw;
}
void shooting_set_prop(int id, int v)
{
    printf("*** set prop %d %d ***\n",id, v);
}
int shooting_get_prop(int id)
{
	return 0;
}
long stat_get_vbatt()
{
	return 4085;
}
void ubasic_set_led(int led, int state, int bright)
{
    printf("*** set led %d %d %d ***\n",led, state, bright);
}
int shooting_get_day_seconds()
{
	return 0;
}

int shooting_get_tick_count()
{
	return 0;
}
int ubasic_camera_script_autostart()
{
	return 0;
}
void ubasic_camera_set_script_autostart(int state)
{
	autostart = state;
    printf("*** set autostart %d ***\n",autostart);
}
int get_usb_power(int edge)
{
	return 0;
}
int GetTotalCardSpaceKb()
{
	return 0;
}
int GetFreeCardSpaceKb()
{
	return 0;
}

int GetJpgCount()
{
    printf("*** GetJpgCount ***\n");
    return 0;
}

int GetRawCount()
{
    printf("*** GetRawCount ***\n");
    return 0;
}

void exit_alt()
{
    printf("*** exit alt ***\n");

}

void shooting_set_user_tv_by_id(int v)
{
    printf("*** shooting_set_user_tv_by_id %d ***\n", v);
}

void shooting_set_user_tv_by_id_rel(int v)
{
    printf("*** shooting_set_user_tv_by_id_rel %d ***\n", v);
}

void shooting_set_sv96(short sv96, short is_now)
{
    printf("*** shooting_set_sv96 %d %d ***\n", sv96, is_now);
}

short shooting_get_av96()
{
    printf("*** shooting_get_av96 ***\n");
    return 0;
}

short shooting_get_user_av96()
{
    printf("*** shooting_get_user_av96 ***\n");
    return 0;
}

int shooting_get_user_av_id()
{
    printf("*** shooting_get_user_av_id ***\n");
    return 0;
}

void shooting_set_av96(short v,short is_now)
{
    printf("*** shooting_set_av96 %d %d ***\n", v, is_now);
}

void shooting_set_av96_direct(short v, short is_now)
{
    printf("*** shooting_set_av96_direct %d %d ***\n", v, is_now);
}

void shooting_set_user_av96(short v)
{
    printf("*** shooting_set_user_av96 %d ***\n", v);
}

void shooting_set_user_av_by_id(int v)
{
    printf("*** shooting_set_user_av_by_id %d ***\n", v);
}

void shooting_set_user_av_by_id_rel(int v)
{
    printf("*** shooting_set_user_av_by_id_rel %d ***\n", v);
}

int shooting_get_subject_distance()
{
    printf("*** shooting_get_subject_distance ***\n");
    return 1000;
}

int shooting_get_near_limit_of_acceptable_sharpness()
{
    printf("*** shooting_get_near_limit_of_acceptable_sharpness ***\n");
    return 500;
}

int shooting_get_far_limit_of_acceptable_sharpness()
{
    printf("*** shooting_get_far_limit_of_acceptable_sharpness ***\n");
    return 1500;
}

int shooting_get_depth_of_field()
{
    printf("*** shooting_get_depth_of_field ***\n");
    return 1000;
}

int shooting_get_hyperfocal_distance()
{
    printf("*** shooting_get_hyperfocal_distance ***\n");
    return 1000;
}

int mode_get()
{
    printf("*** mode_get ***\n");
    return MODE_REC;
}

short shooting_get_focus_mode()
{
    printf("*** shooting_get_focus_mode ***\n");
    return 0;
}

short shooting_get_iso_market()
{
    printf("*** shooting_get_iso_market ***\n");
    return 100;
}

short shooting_get_bv96()
{
    printf("*** shooting_get_bv96 ***\n");
    return 32;
}

short shooting_get_sv96()
{
    printf("*** shooting_get_sv96 ***\n");
    return 32;
}

void shooting_set_iso_real(short iso, short is_now)
{
    printf("*** shooting_set_iso_real %d %d ***\n", iso, is_now);
}

int shooting_get_iso_mode()
{
    printf("*** shooting_get_iso_mode ***\n");
    return 0;
}

void shooting_set_iso_mode(int v)
{
    printf("*** shooting_set_iso_mode %d ***\n", v);
}

void shooting_set_nd_filter_state(short v, short is_now)
{
    printf("*** shooting_set_nd_filter_state %d %d ***\n", v, is_now);
}

void camera_shutdown_in_a_second()
{
    printf("*** camera_shutdown_in_a_second ***\n");
}

short shooting_get_tv96()
{
    printf("*** shooting_get_tv96 ***\n");
    return 0;
}

short shooting_get_user_tv96()
{
    printf("*** shooting_get_user_tv96 ***\n");
    return 0;
}

int shooting_get_user_tv_id()
{
    printf("*** shooting_get_user_tv_id ***\n");
    return 0;
}

void shooting_set_tv96(short v, short is_now)
{
    printf("*** shooting_set_tv96 %d %d ***\n", v, is_now);
}

void shooting_set_shutter_speed_ubasic(int t, short is_now)
{
    printf("*** shooting_set_shutter_speed_ubasic %d %d ***\n", t, is_now);
}

void shooting_set_tv96_direct(short v, short is_now)
{
    printf("*** shooting_set_tv96_direct %d %d ***\n", v, is_now);
}

void shooting_set_user_tv96(short v)
{
    printf("*** shooting_set_user_tv96 %d ***\n", v);
}







#endif
