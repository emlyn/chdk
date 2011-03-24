#include "console.h"
#include "stdlib.h"
#include "platform.h"
#include "camera.h"
#include "conf.h"
#include "kbd.h"
#include "keyboard.h"
#include "histogram.h"
#include "action_stack.h"

typedef struct _action_stack
{
    int (*action_process)(long p);
    long stack[ACTION_STACK_SIZE];
    int stack_ptr;
    long comp_id;
    unsigned long delay_target_ticks;
} action_stack_t;

static action_stack_t** action_stacks = NULL;
static int active_stack = -1;
static int num_stacks = 0;
static long task_comp_id = 1;

// Returns true if the task denoted by comp_id has finished execution.
// comp_id is returned by action_stack_create().
int action_stack_is_finished(long comp_id)
{
    int i;
    for (i = 0; i < num_stacks; ++i)
    {
        if (action_stacks[i]->comp_id == comp_id)
            return 0;
    }
    
    return 1;
}

// Starts a new action stack with initial stack entry p.
// The action stack is alive as long as its stack has entries.
long action_stack_create(action_process proc_func, long p)
{
    // Cap the maximum number of action_stacks
    if (num_stacks == MAX_ACTION_STACKS)
        return -1;
        
    // Initialize new action stack
    action_stack_t** tmp = (action_stack_t**)malloc(sizeof(action_stack_t*) * (num_stacks + 1));
    memcpy(tmp, action_stacks, sizeof(action_stack_t*) * num_stacks);

    tmp[num_stacks] = (action_stack_t*)malloc(sizeof(action_stack_t));
    
    action_stack_t* stack = tmp[num_stacks];
    stack->action_process = proc_func;
    stack->stack_ptr = 0;
    stack->comp_id = task_comp_id;
    stack->delay_target_ticks = 0;
    stack->stack[0] = p;    

    action_stack_t** old = action_stacks;
    action_stacks = tmp;
    ++num_stacks;
    
    if (old != NULL)
        free(old);
        
    // Increment task_comp_id, handle wraparound, 
    // and do not take values already in use
    do
    {
        ++task_comp_id;
        if (task_comp_id < 0)
            task_comp_id = 0;
    } while( !action_stack_is_finished(task_comp_id) );
	return stack->comp_id; 
}

static void action_stack_finish(int task_id)
{
    action_stack_t** tmp = NULL;
    if (num_stacks > 1)
        tmp = (action_stack_t**)malloc(sizeof(action_stack_t*) * (num_stacks - 1));
    
    int src_index, dst_index;
    for (src_index = 0, dst_index = 0; src_index < num_stacks; ++src_index)
    {
        if (src_index != task_id)
        {
            tmp[dst_index] = action_stacks[src_index];
            ++dst_index;
        }
        else
        {
            free(action_stacks[src_index]);
        }
    }
        
    action_stack_t** old = action_stacks;
    --num_stacks;
    action_stacks = tmp;
    free(old);
}

// Can only be called from an action stack
void action_pop()
{
    if (active_stack == -1)
        return;
    
    --(action_stacks[active_stack]->stack_ptr);
}

// Can only be called from an action stack
void action_push_delay(long msec)
{
    action_push(msec);
    action_push(AS_SLEEP);
}

// Can only be called from an action stack
void action_push_press(long key)
{
    // WARNING stack program flow is reversed
    action_push_delay(20);
    action_push(key);
    action_push(AS_PRESS);
}

// Can only be called from an action stack
void action_push_release(long key)
{
    // WARNING stack program flow is reversed
    action_push_delay(20);
    action_push(key);
    action_push(AS_RELEASE);
}

void action_push_click(long key)
{
// WARNING stack program flow is reversed
    action_push_release(key);
    action_push_press(key);
}

void action_wait_for_click(int timeout)
{
    action_push(timeout);
    action_push(AS_WAIT_CLICK);
}

// Can only be called from an action stack
void action_push(long p)
{
    if (active_stack == -1)
        return;

    action_stack_t* task = action_stacks[active_stack];
    task->stack[++task->stack_ptr] = p;    
}

// Can only be called from an action stack
long action_get_prev(int p)
{
    if (active_stack == -1)
        return 0;

    action_stack_t* task = action_stacks[active_stack];
    return task->stack[task->stack_ptr-(p-1)];
}

// handle initializing and checking a timeout value on the stack
// p is the how far up the stack the timout value is
// returns zero if the timeout has not expired, 1 if it has
// does not pop the delay value off the stack or clear the delay value
int action_process_delay(int p)
{
    int t = get_tick_count();
    // FIXME take care if overflow occurs
    if (action_stacks[active_stack]->delay_target_ticks == 0)
    {
        /* setup timer */
        action_stacks[active_stack]->delay_target_ticks = t+action_get_prev(p);
        return 0;
    }
    if (action_stacks[active_stack]->delay_target_ticks <= t)
    {
        return 1;
    }
    return 0;
}

void action_clear_delay(void)
{
    action_stacks[active_stack]->delay_target_ticks = 0;
}

// Defines some standard operations. Returns false if it could not process anything.
// Can only be called from an action stack
int action_stack_standard(long p)
{        
    long t;
    
    switch (p)
    {
    case AS_PRESS:
        kbd_key_press(action_get_prev(2));
        action_pop();
        action_pop();
        break;
    case AS_RELEASE:
        kbd_key_release(action_get_prev(2));
        action_pop();
        action_pop();
        break;
    case AS_SLEEP:
        if(action_process_delay(2))
        {
            action_clear_delay();
            action_pop();
            action_pop();
        }
        break;
    case AS_PR_WAIT_SAVE:
        state_shooting_progress = SHOOTING_PROGRESS_NONE;
        state_expos_recalculated = 0;
        histogram_stop();

        action_pop();
        break;
    case AS_WAIT_SAVE:
        if (state_shooting_progress == SHOOTING_PROGRESS_DONE)
            action_pop();
        break;
    case AS_WAIT_FLASH:
        if (shooting_is_flash_ready())
            action_pop();
        break;
    case AS_WAIT_EXPHIST:
        if (state_expos_recalculated)
        {
            state_expos_under = under_exposed;
            state_expos_over = over_exposed;
            action_pop();
        }
        break;
    case AS_PR_WAIT_EXPHIST:
        if (shooting_in_progress() || MODE_IS_VIDEO(mode_get()))
        {
            state_expos_recalculated = 0;
            histogram_restart();
            action_pop();
        }
        break;
    case AS_WAIT_CLICK:
        if(action_process_delay(2) || (kbd_last_clicked = kbd_get_clicked_key()))
        {
            if (!kbd_last_clicked) 
                kbd_last_clicked=0xFFFF;
            action_clear_delay();
            action_pop();
            action_pop();
        }
        break;
    case AS_SHOOT:
        // Initiate a shoot. Remember that stack program flow is reversed!
        action_pop();

        action_push_delay(conf.script_shoot_delay*100);// XXX FIXME find out how to wait to jpeg save finished

        action_push(AS_WAIT_SAVE);

        action_push_release(KEY_SHOOT_HALF);
        action_push_release(KEY_SHOOT_FULL);

        action_push_press(KEY_SHOOT_FULL);

        action_push(AS_WAIT_FLASH);
        action_push(AS_WAIT_EXPHIST);
        action_push(AS_PR_WAIT_EXPHIST);

        action_push_press(KEY_SHOOT_HALF);

        action_push(AS_PR_WAIT_SAVE);
    default:
        return 0;
    }
    
    return 1;
}

static void action_stack_process(int task_id)
{
    action_stack_t* stack = action_stacks[task_id];
    if (stack->stack_ptr > -1)
    {
        long stack_arg = action_get_prev(1);
        if (stack->action_process)
            stack->action_process(stack_arg);
        else
            action_stack_standard(stack_arg);
    }
    else
    {
        action_stack_finish(task_id);
    }
}

void action_stack_process_all()
{
    int i;
    for (i = num_stacks - 1; i >= 0; --i)
    {
        active_stack = i;
        action_stack_process(i);
    }
    
    active_stack = -1;
}
