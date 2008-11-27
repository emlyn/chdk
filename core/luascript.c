#include "luascript.h"
#include "../lib/ubasic/camera_functions.h"
#include "kbd.h"
#include "platform.h"
#include "script.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "../include/conf.h"
#include "shot_histogram.h"
#include "ubasic.h"
#include "stdlib.h"
#include "raw.h"
#include "raw_merge.h"

static int luaCB_shoot( lua_State* L )
{
  kbd_sched_shoot();
  return lua_yield( L, 0 );
}

static int luaCB_sleep( lua_State* L )
{
  kbd_sched_delay( luaL_checknumber( L, 1 ) );
  return lua_yield( L, 0 );
}

// for press,release and click
static int luaCB_keyfunc( lua_State* L )
{
  long k = keyid_by_name( luaL_checkstring( L, 1 ) );
  if (k > 0 ) {
    void* func = lua_touserdata( L, lua_upvalueindex(1) );
    ((void(*)(long))func)( k );
  }
  else
    luaL_error( L, "unknown key" );
  return lua_yield( L, 0 );
}

static int luaCB_cls( lua_State* L )
{
  script_console_clear();
  return 0;
}

static int luaCB_get_av96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_av96() );
  return 1;
}

static int luaCB_get_bv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_bv96() );
  return 1;
}

static int luaCB_get_day_seconds( lua_State* L )
{
  lua_pushnumber( L, shooting_get_day_seconds() );
  return 1;
}

static int luaCB_get_disk_size( lua_State* L )
{
  lua_pushnumber( L, GetTotalCardSpaceKb() );
  return 1;
}

static int luaCB_get_dof( lua_State* L )
{
  lua_pushnumber( L, shooting_get_depth_of_field() );
  return 1;
}

static int luaCB_get_far_limit( lua_State* L )
{
  lua_pushnumber( L, shooting_get_far_limit_of_acceptable_sharpness() );
  return 1;
}

static int luaCB_get_free_disk_space( lua_State* L )
{
  lua_pushnumber( L, GetFreeCardSpaceKb() );
  return 1;
}

static int luaCB_get_focus( lua_State* L )
{
  lua_pushnumber( L, shooting_get_subject_distance() );
  return 1;
}

static int luaCB_get_hyp_dist( lua_State* L )
{
  lua_pushnumber( L, shooting_get_hyperfocal_distance() );
  return 1;
}

static int luaCB_get_iso_market( lua_State* L )
{
  lua_pushnumber( L, shooting_get_iso_market() );
  return 1;
}

static int luaCB_get_iso_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_iso_mode() );
  return 1;
}

static int luaCB_get_iso_real( lua_State* L )
{
  lua_pushnumber( L, shooting_get_iso_real() );
  return 1;
}

static int luaCB_get_jpg_count( lua_State* L )
{
  lua_pushnumber( L, GetJpgCount() );
  return 1;
}

static int luaCB_get_near_limit( lua_State* L )
{
  lua_pushnumber( L, shooting_get_near_limit_of_acceptable_sharpness() );
  return 1;
}

static int luaCB_get_prop( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop( luaL_checknumber( L, 1 ) ) );
  return 1;
}

static int luaCB_get_raw_count( lua_State* L )
{
  lua_pushnumber( L, GetRawCount() );
  return 1;
}

static int luaCB_get_sv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_sv96() );
  return 1;
}

static int luaCB_get_tick_count( lua_State* L )
{
  lua_pushnumber( L, shooting_get_tick_count() );
  return 1;
}

static int luaCB_get_exp_count( lua_State* L )
{
  lua_pushnumber( L, get_exposure_counter() );
  return 1;
}

static int luaCB_get_tv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_tv96() );
  return 1;
}

static int luaCB_get_user_av_id( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_av_id() );
  return 1;
}

static int luaCB_get_user_av96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_av96() );
  return 1;
}

static int luaCB_get_user_tv_id( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_tv_id() );
  return 1;
}

static int luaCB_get_user_tv96( lua_State* L )
{
  lua_pushnumber( L, shooting_get_user_tv_id() );
  return 1;
}

static int luaCB_get_vbatt( lua_State* L )
{
  lua_pushnumber( L, stat_get_vbatt() );
  return 1;
}

static int luaCB_get_zoom( lua_State* L )
{
  lua_pushnumber( L, shooting_get_zoom() );
  return 1;
}

static int luaCB_set_av96_direct( lua_State* L )
{
  shooting_set_av96_direct( luaL_checknumber( L, 1 ), SET_LATER );
  return 0;
}

static int luaCB_set_av96( lua_State* L )
{
  shooting_set_av96( luaL_checknumber( L, 1 ), SET_LATER );
  return 0;
}

static int luaCB_set_focus( lua_State* L )
{
    int to = luaL_checknumber( L, 1 );
    int m=mode_get()&MODE_SHOOTING_MASK;
    int mode_video=MODE_IS_VIDEO(m);

#if CAM_HAS_MANUAL_FOCUS
    if (shooting_get_focus_mode() || (mode_video)) shooting_set_focus(to, SET_NOW);
    else shooting_set_focus(to, SET_LATER);
#else
    if (mode_video) shooting_set_focus(to, SET_NOW);
    else shooting_set_focus(to, SET_LATER);    
#endif    
  return 0;
}

static int luaCB_set_iso_mode( lua_State* L )
{
  shooting_set_iso_mode( luaL_checknumber( L, 1 ) );
  return 0;
}

static int luaCB_set_iso_real( lua_State* L )
{
  shooting_set_iso_real( luaL_checknumber( L, 1 ), SET_LATER);
  return 0;
}

static int luaCB_set_led( lua_State* L )
{
  int to, to1, to2;
  to = luaL_checknumber( L, 1 );
  to1 = luaL_checknumber( L, 2 );
  to2 = 200;
  if( lua_isnumber( L, 3 ) )
    to = lua_tonumber( L, 3 );
  ubasic_set_led(to, to1, to2);
  return 0;
}

static int luaCB_set_nd_filter( lua_State* L )
{
  shooting_set_nd_filter_state( luaL_checknumber( L, 1 ), SET_LATER);
  return 0;
}

static int luaCB_set_prop( lua_State* L )
{
  int to, to1;
  to = luaL_checknumber( L, 1 );
  to1 = luaL_checknumber( L, 2 );
  shooting_set_prop(to, to1);
  return 0;
}

static int luaCB_set_raw_nr( lua_State* L )
{
  ubasic_camera_set_nr(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_get_raw_nr( lua_State* L )
{
  lua_pushnumber( L, ubasic_camera_get_nr() );
  return 1;
}

static int luaCB_set_raw( lua_State* L )
{
  ubasic_camera_set_raw(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_get_raw( lua_State* L )
{
  lua_pushnumber( L, conf.save_raw );
  return 1;
}

static int luaCB_set_sv96( lua_State* L )
{
  shooting_set_sv96(luaL_checknumber( L, 1 ), SET_LATER);
  return 0;
}

static int luaCB_set_tv96_direct( lua_State* L )
{
  shooting_set_tv96_direct(luaL_checknumber( L, 1 ), SET_LATER);
  return 0;
}

static int luaCB_set_tv96( lua_State* L )
{
  shooting_set_tv96(luaL_checknumber( L, 1 ), SET_LATER);
  return 0;
}

static int luaCB_set_user_av_by_id_rel( lua_State* L )
{
  shooting_set_user_av_by_id_rel(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_av_by_id( lua_State* L )
{
  shooting_set_user_av_by_id(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_av96( lua_State* L )
{
  shooting_set_user_av96(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_tv_by_id_rel( lua_State* L )
{
  shooting_set_user_tv_by_id_rel(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_tv_by_id( lua_State* L )
{
  shooting_set_user_tv_by_id(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_user_tv96( lua_State* L )
{
  shooting_set_user_tv96(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_zoom_speed( lua_State* L )
{
  shooting_set_zoom_speed(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_zoom_rel( lua_State* L )
{
  shooting_set_zoom_rel(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_set_zoom( lua_State* L )
{
  shooting_set_zoom(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_wait_click( lua_State* L )
{
  int timeout = luaL_optnumber( L, 1, 0 );
  ubasic_camera_wait_click(timeout);
  return lua_yield( L, 0 );
}

static int luaCB_is_pressed( lua_State* L )
{
  lua_pushboolean( L, ubasic_camera_is_pressed(luaL_checkstring( L, 1 )));
  return 1;
}

static int luaCB_is_key( lua_State* L )
{
  lua_pushboolean( L, ubasic_camera_is_clicked(luaL_checkstring( L, 1 )));
  return 1;
}

#if defined (CAMERA_g7) || defined (CAMERA_sx100is) || defined (CAMERA_g9)
static int luaCB_wheel_right( lua_State* L )
{
  JogDial_CW();
  return 0;
}

static int luaCB_wheel_left( lua_State* L )
{
  JogDial_CCW();
  return 0;
}
#endif

static int luaCB_md_get_cell_diff( lua_State* L )
{
  lua_pushnumber( L, md_get_cell_diff(luaL_checknumber(L,1),
				      luaL_checknumber(L,2)));
  return 1;
}

static int luaCB_md_detect_motion( lua_State* L )
{
  int columns = (luaL_optnumber(L,1,6));
  int rows = (luaL_optnumber(L,2,4));
  int pixel_measure_mode = (luaL_optnumber(L,3,1));
  int detection_timeout = (luaL_optnumber(L,4,10000));
  int measure_interval = (luaL_optnumber(L,5,7));
  int threshold = (luaL_optnumber(L,6,10));
  int draw_grid = (luaL_optnumber(L,7,1));
   // arg 8 is the return value in ubasic. We
   // ignore it here. - AUJ
  int clipping_region_mode = (luaL_optnumber(L,9,0));
  int clipping_region_column1 = (luaL_optnumber(L,10,0));
  int clipping_region_row1 = (luaL_optnumber(L,11,0));
  int clipping_region_column2 = (luaL_optnumber(L,12,0));
  int clipping_region_row2 = (luaL_optnumber(L,13,0));
  int parameters = (luaL_optnumber(L,14,1));
  int pixels_step = (luaL_optnumber(L,15,6));
  int msecs_before_trigger = (luaL_optnumber(L,16,0));
  ubasic_set_variable(0, 0);
  md_init_motion_detector(
    columns, rows, pixel_measure_mode, detection_timeout, 
    measure_interval, threshold, draw_grid, 0,
    clipping_region_mode,
    clipping_region_column1, clipping_region_row1,
    clipping_region_column2, clipping_region_row2,
    parameters, pixels_step, msecs_before_trigger
  );

  return lua_yield(L, 0);
}

static int luaCB_autostarted( lua_State* L )
{
  lua_pushboolean( L, ubasic_camera_script_autostart() );
  return 1;
}

static int luaCB_get_autostart( lua_State* L )
{
  lua_pushnumber( L, conf.script_startup );
  return 1;
}

static int luaCB_set_autostart( lua_State* L )
{
  int to;
  to = luaL_checknumber( L, 1 );
  if ( to >= 0 && to <= 2 ) conf.script_startup = to;
  conf_save();
  return 0;
}

static int luaCB_get_usb_power( lua_State* L )
{
  if (luaL_optnumber( L, 1, 0 )) lua_pushnumber( L, get_usb_power(1) );
  else lua_pushnumber( L, get_usb_power(0) );
  return 1;
}

static int luaCB_exit_alt( lua_State* L )
{
  exit_alt();
  return 0;
}

static int luaCB_shut_down( lua_State* L )
{
  camera_shutdown_in_a_second();
  return 0;
}

static int luaCB_print_screen( lua_State* L )
{
  
  if (lua_isboolean( L, 1 ))
    script_print_screen_statement( lua_toboolean( L, 1 ) );
  else
    script_print_screen_statement( luaL_checknumber( L, 1 )+10000 );
  return 0;
}

static int luaCB_get_movie_status( lua_State* L )
{
  lua_pushnumber( L, movie_status );
  return 1;
}

static int luaCB_set_movie_status( lua_State* L )
{
  int to;
  switch(luaL_checknumber( L, 1 )) {
    case 1:
      if (movie_status == 4) {
        movie_status = 1;
      }
    break;
    case 2:
      if (movie_status == 1) {
        movie_status = 4;
      }
    break;
    case 3:
      if (movie_status == 1 || movie_status == 4) {
        movie_status = 5;
      }
    break;
  }
  return 0;
}

static int luaCB_get_drive_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop(PROPCASE_DRIVE_MODE) );
  return 1;
}

static int luaCB_get_focus_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop(PROPCASE_FOCUS_MODE) );
  return 1;
}

static int luaCB_get_flash_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop(PROPCASE_FLASH_MODE) );
  return 1;
}

static int luaCB_get_shooting( lua_State* L )
{
  lua_pushboolean( L, shooting_get_prop(PROPCASE_SHOOTING) );
  return 1;
}

static int luaCB_get_flash_ready( lua_State* L )
{
  lua_pushboolean( L, shooting_get_prop(PROPCASE_IS_FLASH_READY) );
  return 1;
}

static int luaCB_get_IS_mode( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop(PROPCASE_IS_MODE) );
  return 1;
}

static int luaCB_get_orientation_sensor( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop(PROPCASE_ORIENTATION_SENSOR) );
  return 1;
}

static int luaCB_get_zoom_steps( lua_State* L )
{
  lua_pushnumber( L, zoom_points );
  return 1;
}

static int luaCB_get_nd_present( lua_State* L )
{
  int to;
  #if !CAM_HAS_ND_FILTER
  to = 0;
  #endif
  #if CAM_HAS_ND_FILTER && !CAM_HAS_IRIS_DIAPHRAGM
  to = 1;
  #endif
  #if CAM_HAS_ND_FILTER && CAM_HAS_IRIS_DIAPHRAGM
  to = 2;
  #endif
  lua_pushnumber( L, to );
  return 1;
}

static int luaCB_get_propset( lua_State* L )
{
  lua_pushnumber( L, CAM_PROPSET );
  return 1;
}

static int luaCB_get_ev( lua_State* L )
{
  lua_pushnumber( L, shooting_get_prop(PROPCASE_EV_CORRECTION_1) );
  return 1;
}

static int luaCB_set_ev( lua_State* L )
{
  int to;
  to = luaL_checknumber( L, 1 );
  shooting_set_prop(PROPCASE_EV_CORRECTION_1, to);
  shooting_set_prop(PROPCASE_EV_CORRECTION_2, to);
  return 0;
}

static int luaCB_get_histo_range( lua_State* L )
{
  int from = (luaL_checknumber(L,1));
  int to = (luaL_checknumber(L,2));
  if (shot_histogram_enabled) lua_pushnumber( L, (unsigned short)shot_histogram_get_range(from, to) );
  else lua_pushnumber( L, -1 );
  return 1;
}

static int luaCB_shot_histo_enable( lua_State* L )
{
  shot_histogram_enabled = luaL_checknumber( L, 1 );
  return 0;
}

static int luaCB_play_sound( lua_State* L )
{
  play_sound(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_get_temperature( lua_State* L )
{
  int which = (luaL_checknumber( L, 1 ));
  int temp = -100; // do something insane if users passes bad value
  switch (which)
  {
    case 0:
      temp = get_optical_temp(); 
      break;
    case 1:
      temp = get_ccd_temp(); 
      break;
    case 2:
      temp = get_battery_temp();
      break;
  }
  lua_pushnumber( L, temp );
  return 1;
}

static int luaCB_get_time( lua_State* L )
{
  int r = -1;
  unsigned long t2 = time(NULL);
  static struct tm *ttm;
  ttm = localtime(&t2);
  const char *t = luaL_checkstring( L, 1 );
  if (strncmp("s", t, 1)==0) r = ( L, ttm->tm_sec );
  else if (strncmp("m", t, 1)==0) r = ( L, ttm->tm_min );
  else if (strncmp("h", t, 1)==0) r = ( L, ttm->tm_hour );
  else if (strncmp("D", t, 1)==0) r = ( L, ttm->tm_mday );
  else if (strncmp("M", t, 1)==0) r = ( L, ttm->tm_mon+1 );
  else if (strncmp("Y", t, 1)==0) r = ( L, 1900+ttm->tm_year );
  lua_pushnumber( L, r );
  return 1;
}

static int luaCB_peek( lua_State* L )
{
  int addr = (luaL_checknumber(L,1));
  // must be alligned
  if (addr & 0x3) {
  	lua_pushnil(L);
  }
  else {
    lua_pushnumber( L, *(unsigned *)(addr) );
  }
  return 1;
}

static int luaCB_poke( lua_State* L )
{
  int addr = (luaL_checknumber(L,1));
  int val = (luaL_checknumber(L,2));
  if (addr & 0x3) {
  	lua_pushnil(L);
  }
  else {
    *(unsigned *)(addr) = val;
    lua_pushboolean(L,1);
  }
  return 1;
}

static int luaCB_bitand( lua_State* L )
{
  int v1 = (luaL_checknumber(L,1));
  int v2 = (luaL_checknumber(L,2));
  lua_pushnumber( L, v1 & v2 );
  return 1;
}

static int luaCB_bitor( lua_State* L )
{
  int v1 = (luaL_checknumber(L,1));
  int v2 = (luaL_checknumber(L,2));
  lua_pushnumber( L, v1 | v2 );
  return 1;
}

static int luaCB_bitxor( lua_State* L )
{
  int v1 = (luaL_checknumber(L,1));
  int v2 = (luaL_checknumber(L,2));
  lua_pushnumber( L, v1 ^ v2 );
  return 1;
}

static int luaCB_bitshl( lua_State* L )
{
  int val = (luaL_checknumber(L,1));
  unsigned shift = (luaL_checknumber(L,2));
  lua_pushnumber( L, val << shift );
  return 1;
}

static int luaCB_bitshri( lua_State* L )
{
  int val = (luaL_checknumber(L,1));
  unsigned shift = (luaL_checknumber(L,2));
  lua_pushnumber( L, val >> shift );
  return 1;
}

static int luaCB_bitshru( lua_State* L )
{
  unsigned val = (luaL_checknumber(L,1));
  unsigned shift = (luaL_checknumber(L,2));
  lua_pushnumber( L, val >> shift );
  return 1;
}

static int luaCB_bitnot( lua_State* L )
{
  unsigned val = (luaL_checknumber(L,1));
  lua_pushnumber( L, ~val );
  return 1;
}

static void set_string_field(lua_State* L, const char *key, const char *val)
{
  lua_pushstring(L, val);
  lua_setfield(L, -2, key);
}

static int luaCB_get_buildinfo( lua_State* L )
{
  lua_createtable(L, 0, 6);  /* 6 = number of fields */
  set_string_field( L,"platform", PLATFORM );
  set_string_field( L,"platsub", PLATFORMSUB );
  set_string_field( L,"version", HDK_VERSION );
  set_string_field( L,"build_number", BUILD_NUMBER );
  set_string_field( L,"build_date", __DATE__ );
  set_string_field( L,"build_time", __TIME__ );
  return 1;
}

static int luaCB_get_mode( lua_State* L )
{
  int m = mode_get();
  lua_pushboolean( L, (m&MODE_MASK) != MODE_PLAY );
  lua_pushboolean( L, MODE_IS_VIDEO(m) );
  lua_pushnumber( L, m );
  return 3;
}

// TODO sanity check file ?
static int luaCB_set_raw_develop( lua_State* L )
{
  raw_prepare_develop(luaL_optstring( L, 1, NULL ));
  return 0;
}

static int luaCB_raw_merge_start( lua_State* L )
{
  int op = luaL_checknumber(L,1);
  if (op == RAW_OPERATION_SUM || op == RAW_OPERATION_AVERAGE) {
    raw_merge_start(op);
  }
  else {
    return luaL_argerror(L,1,"invalid raw merge op");
  }
  return 0;
}

// TODO sanity check file ?
static int luaCB_raw_merge_add_file( lua_State* L )
{
  raw_merge_add_file(luaL_checkstring( L, 1 ));
  return 0;
}

static int luaCB_raw_merge_end( lua_State* L )
{
  raw_merge_end();
  return 0;
}

void register_lua_funcs( lua_State* L )
{
#define FUNC( X )			\
  lua_pushcfunction( L, luaCB_##X );	\
  lua_setglobal( L, #X )

  FUNC(shoot);
  FUNC(sleep);
  FUNC(cls);

  lua_pushlightuserdata( L, kbd_sched_click );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "click" );

  lua_pushlightuserdata( L, kbd_sched_press );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "press" );

  lua_pushlightuserdata( L, kbd_sched_release );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "release" );

  FUNC(get_av96);
  FUNC(get_av96);
  FUNC(get_bv96);
  FUNC(get_day_seconds);
  FUNC(get_disk_size);
  FUNC(get_dof);
  FUNC(get_far_limit);
  FUNC(get_free_disk_space);
  FUNC(get_focus);
  FUNC(get_hyp_dist);
  FUNC(get_iso_market);
  FUNC(get_iso_mode);
  FUNC(get_iso_real);
  FUNC(get_jpg_count);
  FUNC(get_near_limit);
  FUNC(get_prop);
  FUNC(get_raw_count);
  FUNC(get_raw_nr);
  FUNC(get_raw);
  FUNC(get_sv96);
  FUNC(get_tick_count);
  FUNC(get_tv96);
  FUNC(get_user_av_id);
  FUNC(get_user_av96);
  FUNC(get_user_tv_id);
  FUNC(get_user_tv96);
  FUNC(get_vbatt);
  FUNC(get_zoom);
  FUNC(get_exp_count);

  FUNC(set_av96_direct);
  FUNC(set_av96);
  FUNC(set_focus);
  FUNC(set_iso_mode);
  FUNC(set_iso_real);
  FUNC(set_led);
  FUNC(set_nd_filter);
  FUNC(set_prop);
  FUNC(set_raw_nr);
  FUNC(set_raw);
  FUNC(set_sv96);
  FUNC(set_tv96_direct);
  FUNC(set_tv96);
  FUNC(set_user_av_by_id_rel);
  FUNC(set_user_av_by_id);
  FUNC(set_user_av96);
  FUNC(set_user_tv_by_id_rel);
  FUNC(set_user_tv_by_id);
  FUNC(set_user_tv96);
  FUNC(set_zoom_speed);
  FUNC(set_zoom_rel);
  FUNC(set_zoom);

  FUNC(wait_click);
  FUNC(is_pressed);
  FUNC(is_key);
#if defined (CAMERA_g7) || defined (CAMERA_sx100is)
  FUNC(wheel_right);
  FUNC(wheel_left);
#endif
  FUNC(md_get_cell_diff);
  FUNC(md_detect_motion);
  FUNC(autostarted);
  FUNC(get_autostart);
  FUNC(set_autostart);
  FUNC(get_usb_power);
  FUNC(exit_alt);
  FUNC(shut_down);
  FUNC(print_screen);

  FUNC(get_focus_mode);
  FUNC(get_propset);
  FUNC(get_zoom_steps);
  FUNC(get_drive_mode);
  FUNC(get_flash_mode);
  FUNC(get_shooting);
  FUNC(get_flash_ready);
  FUNC(get_IS_mode);
  FUNC(set_ev);
  FUNC(get_ev);
  FUNC(get_orientation_sensor);
  FUNC(get_nd_present);
  FUNC(get_movie_status);
  FUNC(set_movie_status);
  
  FUNC(get_histo_range);
  FUNC(shot_histo_enable);
  FUNC(play_sound);
  FUNC(get_temperature);
  FUNC(peek);
  FUNC(poke);
  FUNC(bitand);
  FUNC(bitor);
  FUNC(bitxor);
  FUNC(bitshl);
  FUNC(bitshri);
  FUNC(bitshru);
  FUNC(bitnot);

  FUNC(get_time);

  FUNC(get_buildinfo);
  FUNC(get_mode);
  
  FUNC(set_raw_develop);
  // NOTE these functions normally run in the spytask.
  // called from lua they will run from kbd task instead
  FUNC(raw_merge_start);
  FUNC(raw_merge_add_file);
  FUNC(raw_merge_end);
}
