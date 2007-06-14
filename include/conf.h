#ifndef CONF_H
#define CONF_H

extern int conf_show_osd;
extern int conf_save_raw;
extern int conf_force_nr_off;
extern int conf_script_shoot_delay;
extern int conf_show_histo;
extern int conf_ubasic_var_a;
extern int conf_ubasic_var_b;
extern int conf_ubasic_var_c;

extern int confns_enable_memdump;


#define SHOOTING_PROGRESS_NONE 0
#define SHOOTING_PROGRESS_STARTED 1
#define SHOOTING_PROGRESS_PROCESSING 2
#define SHOOTING_PROGRESS_DONE 3

extern int state_kbd_script_run;
extern int state_shooting_progress;
extern int state_save_raw_nth_only;
extern int state_expos_recalculated;
extern const char *state_ubasic_script;
extern int state_expos_under;
extern int state_expos_over;

extern int state_debug1;
extern int debug_propcase_show;
extern int debug_propcase_page;
extern int debug_vals_show;

extern void conf_save();
extern void conf_restore();

#endif
