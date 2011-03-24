#ifndef SCRIPT_H
#define SCRIPT_H

//-------------------------------------------------------------------
#define SCRIPT_DEFAULT_FILENAME     "A/SCRIPT.BAS"
#define SCRIPT_NUM_PARAMS           26
#define SCRIPT_DATA_PATH            "A/CHDK/DATA/"

#ifdef OPT_UBASIC
#include "ubasic.h"
#endif

#ifdef OPT_LUA
#include "../core/luascript.h"
#endif

//-------------------------------------------------------------------
extern const char *script_source_str;

extern char script_title[36];
extern char script_params[SCRIPT_NUM_PARAMS][28];
extern int script_param_order[SCRIPT_NUM_PARAMS];

//-------------------------------------------------------------------
extern void script_load(const char *fn, int saved_params);
extern void script_console_add_line(const char *str);
extern void script_print_screen_init();
extern void script_print_screen_end();
extern void script_print_screen_statement(int val);
extern int load_params_values(const char *fn, int update_vars, int read_param_set);
extern void save_params_values(int unconditional);
//-------------------------------------------------------------------

long script_stack_start();
int script_is_running();
void script_end();
long script_start_gui( int autostart );

int script_key_is_pressed( int keyid );
int script_key_is_clicked( int keyid );
int script_keyid_by_name( const char *name );
#ifdef OPT_LUA
long script_start_ptp( char *script );
#endif
void script_wait_and_end();

#endif
