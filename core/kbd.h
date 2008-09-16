#ifndef KBD_H
#define KBD_H

//-------------------------------------------------------------------
void kbd_sched_shoot();
void kbd_sched_click(long key);
void kbd_sched_press(long key);
void kbd_sched_release(long key);
void kbd_sched_delay(long msec);
int keyid_by_name (const char *n);

//-------------------------------------------------------------------
#endif
