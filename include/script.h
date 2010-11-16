#ifndef SCRIPT_H
#define SCRIPT_H

//-------------------------------------------------------------------
#define SCRIPT_DEFAULT_FILENAME     "A/SCRIPT.BAS"
#define SCRIPT_NUM_PARAMS           26
#define SCRIPT_DATA_PATH            "A/CHDK/DATA/"

//-------------------------------------------------------------------
extern const char *script_source_str;

extern char script_title[36];
extern char script_params[SCRIPT_NUM_PARAMS][28];
extern int script_param_order[SCRIPT_NUM_PARAMS];
extern int auto_redraw;

//-------------------------------------------------------------------
extern void script_load(const char *fn, int saved_params);
extern void script_console_clear();
extern void script_console_add_line(const char *str);
extern void script_console_draw(int drawing);
extern void script_print_screen_init();
extern void script_print_screen_end();
extern void script_print_screen_statement(int val);
extern int load_params_values(const char *fn, int update_vars, int read_param_set);
extern void save_params_values(int unconditional);
extern void script_console_set_layout(int x1, int y1, int x2, int y2);
extern void script_console_set_autoredraw(int value);
extern void script_console_redraw();
//-------------------------------------------------------------------

extern void lua_script_exec(char *script, int keep_result);
extern void lua_script_wait();
extern void *lua_get_result();
#endif
