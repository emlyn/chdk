#include "luascript.h"
#include "../lib/ubasic/camera_functions.h"
#include "kbd.h"
#include "platform.h"
#include "script.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "conf.h"
#include "shot_histogram.h"
#include "ubasic.h"
#include "stdlib.h"
#include "raw.h"
#include "raw_merge.h"
#include "levent.h"
#include "console.h"
#include "action_stack.h"

#include "../lib/lua/lstate.h"	// for L->nCcalls, baseCcalls

lua_State* L;
lua_State* Lt;
int lua_keep_result;

void *lua_consume_result()
{
  lua_State* r = L;
  L = 0;
  return r;
}

void lua_script_reset()
{
  if ( !lua_keep_result )
  {
    lua_close( L );
    L = 0;
  }
  Lt = 0;
}

static void lua_count_hook(lua_State *L, lua_Debug *ar)
{
  if( L->nCcalls <= L->baseCcalls )
    lua_yield( L, 0 );
}

int lua_script_start( char const* script )
{
  lua_keep_result = 0;
  L = lua_open();
  luaL_openlibs( L );
  register_lua_funcs( L );

  Lt = lua_newthread( L );
  lua_setfield( L, LUA_REGISTRYINDEX, "Lt" );
  if( luaL_loadstring( Lt, script ) != 0 ) {
    script_console_add_line( lua_tostring( Lt, -1 ) );
    lua_script_reset();
    return 0;
  }
  lua_sethook(Lt, lua_count_hook, LUA_MASKCOUNT, 1000 );
  return 1;
}

#ifdef OPT_CURVES
#include "curves.h"

static int luaCB_set_curve_state( lua_State* L )
{
  int value;
  value=luaL_checknumber( L, 1 );
  curve_set_mode(value);
  return 0;
}
#endif

static int luaCB_set_aflock(lua_State* L) 
{
  int val = luaL_checknumber(L, 1);
  if (val>0) DoAFLock();  // 1: enable AFLock
  else UnlockAF();       // 0: disable unlock AF
  return 0;
}


static int luaCB_shoot( lua_State* L )
{
  action_push(AS_SHOOT);
  return lua_yield( L, 0 );
}

static int luaCB_sleep( lua_State* L )
{
  action_push_delay( luaL_checknumber( L, 1 ) );
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
  console_clear();
  return 0;
}

static int luaCB_set_console_layout( lua_State* L )
{
  console_set_layout(luaL_checknumber( L, 1 ),luaL_checknumber( L, 2 ),luaL_checknumber( L, 3 ),luaL_checknumber( L, 4 ));
  return 0;
}

static int luaCB_set_console_autoredraw( lua_State* L )
{
  console_set_autoredraw(luaL_checknumber(L,1));
  return 0;
}

static int luaCB_console_redraw( lua_State* L )
{
  console_redraw();
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
  lua_pushnumber( L, shooting_get_user_tv96() );
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

static int luaCB_get_parameter_data( lua_State* L )
{
  extern long* FlashParamsTable[]; 

  unsigned size;
  unsigned id = luaL_checknumber( L, 1 );
  unsigned val;

  if (id >= get_flash_params_count()) {
    // return nil
    return 0;
  }

  size = FlashParamsTable[id][1]>>16;
  if (size == 0) {
    // return nil
    return 0;
  }
  if (size >= 1 && size <= 4) {
    val = 0;
    get_parameter_data( id, &val, size );
    lua_pushlstring( L, (char *)&val, size );
    // for convenience, params that fit in a number are returned in one as a second result
    lua_pushnumber( L, val );
    return 2;
  }
  else {
    char *buf = malloc(size);
    if(!buf) {
      luaL_error( L, "malloc failed in luaCB_get_parameter_data" );
    }
    get_parameter_data( id, buf, size );
    lua_pushlstring( L, buf, size );
    free(buf);
    return 1;
  }
}

static int luaCB_get_flash_params_count( lua_State* L )
{
  lua_pushnumber( L, get_flash_params_count() );
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
    to2 = lua_tonumber( L, 3 );
  camera_set_led(to, to1, to2);
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
  camera_set_nr(luaL_checknumber( L, 1 ));
  return 0;
}

static int luaCB_get_raw_nr( lua_State* L )
{
  lua_pushnumber( L, camera_get_nr() );
  return 1;
}

static int luaCB_set_raw( lua_State* L )
{
  camera_set_raw(luaL_checknumber( L, 1 ));
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
  camera_wait_click(timeout);
  return lua_yield( L, 0 );
}

static int luaCB_is_pressed( lua_State* L )
{
  lua_pushboolean( L, camera_is_pressed(luaL_checkstring( L, 1 )));
  return 1;
}

static int luaCB_is_key( lua_State* L )
{
  lua_pushboolean( L, camera_is_clicked(luaL_checkstring( L, 1 )));
  return 1;
}

#if CAM_HAS_JOGDIAL
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
  if(md_init_motion_detector(
    columns, rows, pixel_measure_mode, detection_timeout, 
    measure_interval, threshold, draw_grid, 0,
    clipping_region_mode,
    clipping_region_column1, clipping_region_row1,
    clipping_region_column2, clipping_region_row2,
    parameters, pixels_step, msecs_before_trigger
  ))
    return lua_yield(L, 0);
  else
    return luaL_error( L, "md_init_motion_detector failed" );
}

static int luaCB_autostarted( lua_State* L )
{
  lua_pushboolean( L, camera_get_script_autostart() );
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

// optional parameter is 0 for soft shutdown (default) or 1 for hard/immediate
static int luaCB_shut_down( lua_State* L )
{
  if ( luaL_optnumber(L,1,0) == 1 )
  {
    shutdown();
  } else {
  camera_shutdown_in_a_second();
  }
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
  lua_pushnumber( L, shooting_get_drive_mode() );
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
  if (shot_histogram_isenabled()) lua_pushnumber( L, shot_histogram_get_range(from, to) );
  else lua_pushnumber( L, -1 ); // TODO should probably return nil 
  return 1;
}

static int luaCB_shot_histo_enable( lua_State* L )
{
  shot_histogram_set(luaL_checknumber( L, 1 ));
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

/*
  val=peek(address[,size])
  return the value found at address in memory, or nil if address or size is invalid
  size is optional 1=byte 2=halfword 4=word. defaults is 4
*/
static int luaCB_peek( lua_State* L )
{
  unsigned addr = luaL_checknumber(L,1);
  unsigned size = luaL_optnumber(L, 2, 4);
  switch(size) {
    case 1: 
      lua_pushnumber( L, *(unsigned char *)(addr) );
    break;
    case 2:
      if (addr & 0x1) {
        lua_pushnil(L);
      }
      else {
        lua_pushnumber( L, *(unsigned short *)(addr) );
      }
    break;
    case 4:
      if (addr & 0x3) {
        lua_pushnil(L);
      }
      else {
        lua_pushnumber( L, *(unsigned *)(addr) );
      }
    break;
    default:
      lua_pushnil(L);

  }
  return 1;
}

/*
  status=poke(address,value[,size])
  writes value to address in memory
  size is optional 1=byte 2=halfword 4=word. defaults is 4
  returns true, or nil if address or size is invalid
*/
static int luaCB_poke( lua_State* L )
{
  unsigned addr = luaL_checknumber(L,1);
  unsigned val = luaL_checknumber(L,2);
  unsigned size = luaL_optnumber(L, 3, 4);
  int status = 0;
  switch(size) {
    case 1: 
        *(unsigned char *)(addr) = (unsigned char)val;
        status=1;
    break;
    case 2:
      if (!(addr & 0x1)) {
        *(unsigned short *)(addr) = (unsigned short)val;
        status=1;
      }
    break;
    case 4:
      if (!(addr & 0x3)) {
        *(unsigned *)(addr) = val;
        status=1;
      }
    break;
  }
  if(status) {
    lua_pushboolean(L,1);
  }
  else {
    lua_pushnil(L);
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
  lua_createtable(L, 0, 8);
  set_string_field( L,"platform", PLATFORM );
  set_string_field( L,"platsub", PLATFORMSUB );
  set_string_field( L,"version", HDK_VERSION );
  set_string_field( L,"build_number", BUILD_NUMBER );
  set_string_field( L,"build_date", __DATE__ );
  set_string_field( L,"build_time", __TIME__ );
#ifndef CAM_DRYOS
  set_string_field( L,"os", "vxworks" );
#else
  set_string_field( L,"os", "dryos" );
#endif
  lua_pushnumber( L, PLATFORMID );
  lua_setfield(L, -2, "platformid");
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

// Enable/disable LCD back light (input argument 1/0)
static int luaCB_set_backlight( lua_State* L )
{
  int val = (luaL_checknumber(L,1));

  if (val > 0) TurnOnBackLight();
  else TurnOffBackLight();
  return 0;
}

// get the string or number passed in index and return it as an event id
static unsigned levent_id_from_lua_arg( lua_State* L, int index)
{
  unsigned event_id;
  if (lua_type(L, index) == LUA_TSTRING) {
    const char *ev_name = lua_tostring(L, index);
  	event_id = levent_id_for_name(ev_name);
    if (event_id == 0) {
        return luaL_error( L, "bad event name '%s'", ev_name );
    }
  }
  // could check here if it is in the table, but even valid ones can crash
  // so we avoid searching the table if given a number
  else if (lua_type(L,index) == LUA_TNUMBER){
  	event_id = lua_tonumber(L,index);
  }
  else {
    return luaL_error( L, "expected event name or id" );
  }
  return event_id;
}

/*
  get a value where boolean or 0/!0 are accepted for on/off.
  normal lua toboolean will convert 0 to true, but ubasic and c users 
  will expect 0 to be off
  intentional HACK: numbers greater than 1 are returned as is
*/
static unsigned on_off_value_from_lua_arg( lua_State* L, int index)
{
  if( lua_isboolean(L,index) ) {
  	return lua_toboolean(L,index);
  }
  else {
  	return luaL_checknumber(L,index); 
  }
}

/*
  return the index of an event, given it's name or event id
*/
static unsigned levent_index_from_id_lua_arg( lua_State* L, int index )
{
  if (lua_type(L, index) == LUA_TSTRING) {
  	return levent_index_for_name(lua_tostring(L, index));
  }
  else if (lua_type(L,index) == LUA_TNUMBER){
  	return levent_index_for_id(lua_tonumber(L,index));
  }
  else {
    return luaL_error( L, "expected string or number" );
  }
}

/*
  name,id,param = get_levent_def(event)
  event is an event id (number) or name (string)
  returns nil if event is not found
*/
static int luaCB_get_levent_def( lua_State* L )
{
  unsigned event_index = levent_index_from_id_lua_arg(L,1);
  if (event_index == LEVENT_INVALID_INDEX) {
    lua_pushnil(L);
    return 1;
  }
  lua_pushstring(L, levent_table[event_index].name);
  lua_pushnumber(L, levent_table[event_index].id);
  lua_pushnumber(L, levent_table[event_index].param);
  return 3;
}

/*
  index=get_levent_index(event)
  event is an event id (number) or name (string)
  returns index or nil if not found
*/
static int luaCB_get_levent_index( lua_State* L )
{
  unsigned event_index = levent_index_from_id_lua_arg(L,1);
  if (event_index == LEVENT_INVALID_INDEX) {
    lua_pushnil(L);
  }
  else {
    lua_pushnumber(L, event_index);
  }
  return 1;
}

/*
  name,id,param = get_levent_def_by_index(event_index)
  event_index is number index into the event table
  returns nil if event is not found
*/
static int luaCB_get_levent_def_by_index( lua_State* L )
{
  unsigned i = luaL_checknumber(L,1);
  if(i >= levent_count()) {
  	lua_pushnil(L);
    return 1;
  }
  lua_pushstring(L, levent_table[i].name);
  lua_pushnumber(L, levent_table[i].id);
  lua_pushnumber(L, levent_table[i].param);
  return 3;
}

/*
  post_levent_*(event[,unk])
  post the event with PostLogicalEventToUI or PostLogicaEventForNotPowerType
  This sends the event. The difference between functions isn't clear.
  event is an event id (number) or name (string).
  unk is an optional number whose meaning is unknown, defaults to zero. 
    Based on code, other values would probably be a pointer.
	This is NOT the 3rd item in the event table.
*/
static int luaCB_post_levent_to_ui( lua_State* L )
{
  unsigned event_id,arg;

  event_id = levent_id_from_lua_arg(L,1);
  arg = luaL_optnumber(L, 2, 0);
  PostLogicalEventToUI(event_id,arg);
  return 0;
}

static int luaCB_post_levent_for_npt( lua_State* L )
{
  unsigned event_id,arg;

  event_id = levent_id_from_lua_arg(L,1);
  arg = luaL_optnumber(L, 2, 0);
  PostLogicalEventForNotPowerType(event_id,arg);
  return 0;
}

/*
  set_levent_active(event,state)
  event is an event id (number) or name (string)
  state is a numeric or boolean state. true or non zero numbers turn on zero, false or nil turn off
  exact meaning is unknown, but it has something to do with the delivery of the specified event.
*/
static int luaCB_set_levent_active( lua_State* L )
{
  unsigned event_id;
  unsigned state;

  event_id = levent_id_from_lua_arg(L,1);
  state = on_off_value_from_lua_arg(L,2);
  SetLogicalEventActive(event_id,state);
  return 0;
}

/*
  set_levent_script_mode(state)
  state is numeric or boolean state. true or non zero numbers turn on zero, false or nil turn off
  exact meaning is unknown, but it has something to do with the behavior of events and/or SetLogicalEventActive.
*/
static int luaCB_set_levent_script_mode( lua_State* L )
{
  SetScriptMode(on_off_value_from_lua_arg(L,1));
  return 0;
}

/* 
  result=set_capture_mode_canon(value)
  where value is a valid PROPCASE_SHOOTING_MODE value for the current camera
  result is true if the camera is in rec mode
*/
static int luaCB_set_capture_mode_canon( lua_State* L )
{
  int modenum = luaL_checknumber(L,1);
  // if the value as negative, assume it is a mistakenly sign extended PROPCASE_SHOOTING_MODE value
  if(modenum < 0) 
    modenum &= 0xFFFF;
  lua_pushboolean( L, shooting_set_mode_canon(modenum) );
  return 1;
}

/*
 result=set_capture_mode(modenum)
 where modenum is a valid CHDK modemap value
 result is true if modenum is a valid modemap value, otherwise false
*/
static int luaCB_set_capture_mode( lua_State* L )
{
  int modenum = luaL_checknumber(L,1);
  lua_pushboolean( L, shooting_set_mode_chdk(modenum) );
  return 1;
}

/*
 result=is_capture_mode_valid(modenum)
 where modenum is a valid CHDK modemap value
 result is true if modenum is a valid modemap value, otherwise false
*/
static int luaCB_is_capture_mode_valid( lua_State* L )
{
  int modenum = luaL_checknumber(L,1);
  lua_pushboolean( L, shooting_mode_chdk2canon(modenum) != -1 );
  return 1;
}

/* 
  set_record(state)
  if state is 0 (or false) the camera is set to play mode. If 1 or true, the camera is set to record mode.
  NOTE: this only begins the mode change. Script should wait until get_mode() reflects the change,
  before doing anything that requires the new mode. e.g.
  set_record(true)
  while not get_mode() do
  	sleep(10)
  end
*/
static int luaCB_set_record( lua_State* L )
{
  if(on_off_value_from_lua_arg(L,1)) {
    levent_set_record();
  }
  else {
    levent_set_play();
  }
  return 0;
}

// switch mode (0 = playback, 1 = record)
// only for when USB is connected
static int luaCB_switch_mode_usb( lua_State* L )
{
  int mode = luaL_checknumber(L,1);

  if ( mode != 0 && mode != 1 )
  {
    return 0;
  }

  return switch_mode_usb(mode);
}

/*
pack the lua args into a buffer to pass to the native code calling functions 
currently only handles strings/numbers
start is the stack index of the first arg
*/
#ifdef OPT_LUA_CALL_NATIVE
static int pack_native_args( lua_State* L, unsigned start, unsigned *argbuf)
{
  unsigned i;
  unsigned end = lua_gettop(L);

  for(i = start; i <= end; i++,argbuf++) {
    if (lua_type(L, i) == LUA_TSTRING) {
        *argbuf=(unsigned)lua_tostring( L, i);
    }
    else if (lua_type(L, i) == LUA_TNUMBER) {
        *argbuf=lua_tonumber( L, i);
    }
    else {
      return 0;
    }
  }
  return 1;
}

/*
Native function call interface. Can be used to call canon eventprocs or arbitrary
pointers.

NOTE: this is preliminary, interface may change in later versions!
All arguments must be strings or numbers.
If the function expects to modify it's arguments via a pointer,
then you must provide a number that is a valid pointer. 

You can use the "AllocateMemory" eventproc to obtain buffers.

If the function tries to write to a string passed from lua, Bad Things may happen.

This is potentially dangerous, functions exist which can destroy the onboard firmware.
*/

/*
result=call_func_ptr(ptr,...)
ptr: address of a valid ARM or Thumb function, which uses the normal C calling convention.
result: R0 value after the call returns
*/
static int luaCB_call_func_ptr( lua_State* L)
{
  unsigned *argbuf=NULL;
  unsigned i;
  unsigned n_args = lua_gettop(L)-1;
  void *fptr;

  fptr=(void *)luaL_checknumber( L, 1 );

  if (n_args) {
    argbuf=malloc(n_args * 4);
    if(!argbuf) {
      return luaL_error( L, "malloc fail" );
    }
    if(!pack_native_args(L, 2, argbuf)) {
      free(argbuf);
      return luaL_error( L, "expected string or number" );
    }
  }
  
  lua_pushnumber( L, call_func_ptr(fptr, argbuf, n_args) );
  free(argbuf);
  return 1;
}

/* 
Call an event procedure

result=call_event_proc("EventprocName",...)
result is the value returned by ExecuteEventProcedure, which is -1 if the eventproc is not found, 
or the eventproc return value (which could also be -1)
NOTE:
Many eventprocs are not registered by default, but can be loaded by calling another event proc
Some useful ones are
SystemEventInit
	includes AllocateMemory, FreeMemory, sprintf, memcpy, Fut functions, log ...
UI_RegistDebugEventProc
	includes capture mode functions, PTM_ functions and much more 
RegisterProductTestEvent
	includes PT_ functions

Others:
RegisterShootSeqEvent
RegisterNRTableEvent
*/

// grab from lowlevel
extern unsigned _ExecuteEventProcedure(const char *name,...);
static int luaCB_call_event_proc( lua_State* L )
{
  const char *evpname;
  unsigned *argbuf;
  unsigned i;
  unsigned n_args = lua_gettop(L);

  evpname=luaL_checkstring( L, 1 );

  argbuf=malloc(n_args * 4);
  if (!argbuf) {
    return luaL_error( L, "malloc fail" );
  }

  // event proc name is first arg
  *argbuf = (unsigned)evpname;
  
  if(!pack_native_args(L,2,argbuf+1)) {
    free(argbuf);
    return luaL_error( L, "expected string or number" );
  }
  
  lua_pushnumber( L, call_func_ptr(_ExecuteEventProcedure,argbuf,n_args) );
  free(argbuf);
  return 1;
}

#endif // OPT_LUA_CALL_NATIVE

/*
result = reboot(["filename"])
returns false on failure, does not return on success
see lib/armutil/reboot.c for details
*/
static int luaCB_reboot( lua_State* L )
{
	lua_pushboolean(L, reboot(luaL_optstring( L, 1, NULL )));
	return 1;
}

void register_lua_funcs( lua_State* L )
{
#define FUNC( X )			\
  lua_pushcfunction( L, luaCB_##X );	\
  lua_setglobal( L, #X )

  FUNC(shoot);
  FUNC(sleep);
  FUNC(cls);
  FUNC(set_console_layout);
  FUNC(set_console_autoredraw);
  FUNC(console_redraw);

  lua_pushlightuserdata( L, action_push_click );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "click" );

  lua_pushlightuserdata( L, action_push_press );
  lua_pushcclosure( L, luaCB_keyfunc, 1 );
  lua_setglobal( L, "press" );

  lua_pushlightuserdata( L, action_push_release );
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
  FUNC(get_flash_params_count);
  FUNC(get_parameter_data);

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
#ifdef CAM_HAS_JOGDIAL
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
  FUNC(set_backlight);
   FUNC(set_aflock);
#ifdef OPT_CURVES
   FUNC(set_curve_state);
#endif
// get levent definition by name or id, nil if not found
   FUNC(get_levent_def);
// get levent definition by index, nil if out of range
   FUNC(get_levent_def_by_index);
// get levent index from name or ID
   FUNC(get_levent_index);
   FUNC(post_levent_to_ui);
   FUNC(post_levent_for_npt);
   FUNC(set_levent_active);
   FUNC(set_levent_script_mode);

   FUNC(set_capture_mode);
   FUNC(set_capture_mode_canon);
   FUNC(is_capture_mode_valid);

   FUNC(set_record);

   FUNC(switch_mode_usb);

#ifdef OPT_LUA_CALL_NATIVE
   FUNC(call_event_proc);
   FUNC(call_func_ptr);
#endif
   FUNC(reboot);
}
