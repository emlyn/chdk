#ifndef CONF_H
#define CONF_H

extern int conf_show_osd;
extern int conf_save_raw;
extern int conf_script_shoot_delay;
extern int conf_show_histo;
extern int conf_raw_fileno;
extern int conf_ubasic_var_a;
extern int conf_ubasic_var_b;
extern int conf_ubasic_var_c;

#define SHOOTING_PROGRESS_NONE 0
#define SHOOTING_PROGRESS_STARTED 1
#define SHOOTING_PROGRESS_PROCESSING 2
#define SHOOTING_PROGRESS_DONE 3

extern int state_kbd_script_run;
extern int state_shooting_progress;
extern int state_save_raw_nth_only;
extern char *state_ubasic_script;

extern int state_debug1;
extern int debug_propcase_show;
extern int debug_propcase_page;

extern void conf_save(int force);
extern void conf_restore();

#endif
