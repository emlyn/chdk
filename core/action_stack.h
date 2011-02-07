#ifndef _ACTION_STACK_H
#define _ACTION_STACK_H

#define ACTION_STACK_SIZE 24
#define MAX_ACTION_STACKS 5

enum STANDARD_ACTIONS
{
    AS_NOOP = 1024,
    AS_SHOOT,
    AS_SLEEP,
    AS_PRESS,
    AS_RELEASE,
    AS_PR_WAIT_SAVE,
    AS_WAIT_SAVE,
    AS_WAIT_FLASH,
    AS_WAIT_EXPHIST,
    AS_PR_WAIT_EXPHIST,
    AS_WAIT_CLICK,
    AS_SCRIPT_RUN,
    AS_MOTION_DETECTOR
};

typedef int (*action_process)(long p);

long action_stack_create(action_process proc_func, long p);
void action_push(long p);
void action_push_delay(long msec);
void action_push_press(long key);
void action_push_release(long key);
void action_push_click(long key);
void action_wait_for_click(int timeout);
void action_pop();
long action_get_prev(int p);
int action_stack_standard(long p);
void action_stack_process_all();
int action_stack_is_finished(long comp_id);

#endif // _ACTION_STACK_H

