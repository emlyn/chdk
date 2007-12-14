#ifdef TEST

#include <stdio.h>

static int tv=0, av=0, zoom=0, focus=0, iso=0, raw=0, raw_nr=0,autostart=0; 

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
void exit_alt()
{
    printf("*** exit alt ***\n");

}











#endif
