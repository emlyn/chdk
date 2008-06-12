#ifndef SCRIPT_H
#define SCRIPT_H

//-------------------------------------------------------------------
#define SCRIPT_DEFAULT_FILENAME	    "A/SCRIPT.BAS"
#define SCRIPT_NUM_PARAMS           26

//-------------------------------------------------------------------
extern const char *state_ubasic_script;

extern char script_title[36];
extern char script_params[SCRIPT_NUM_PARAMS][28];

//-------------------------------------------------------------------
extern void script_load(const char *fn);
extern void script_console_clear();
extern void script_console_add_line(const char *str);
extern void script_console_draw();
extern void script_print_screen_init();
extern void script_print_screen_end();
extern void script_print_screen_statement(int val);

//-------------------------------------------------------------------
#endif
