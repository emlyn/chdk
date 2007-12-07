#ifndef CORE_H
#define CORE_H

void core_spytask();

void core_hook_task_create(void *tcb);
void core_hook_task_delete(void *tcb);

long kbd_process();

void gui_init();

void core_rawdata_available();

#define NOISE_REDUCTION_AUTO_CANON      (0)
#define NOISE_REDUCTION_OFF             (1)
#define NOISE_REDUCTION_ON              (2)

long core_get_noise_reduction_value();

#endif

