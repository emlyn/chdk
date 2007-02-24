#ifndef CORE_H
#define CORE_H

void core_spytask();

void core_hook_task_create(void *tcb);
void core_hook_task_delete(void *tcb);

long kbd_process();

void gui_init();

#endif

