#ifndef _VXWORKS_
#define _VXWORKS_
/******************************************************************************/
/**             VxWorks 5.5, kernel WIND version 2.6                         **/
/**             Internal VxWorks kernel data types and constants             **/
/******************************************************************************/
#define TASK_STATE_READY    0
#define TASK_STATE_SUSPEND  1
#define TASK_STATE_PENDING  2
#define TASK_STATE_DELAY    4
#define TASK_STATE_DEAD     8
/******************************************************************************/
// Task context
struct context_t
{
    unsigned int r[13];
    unsigned int sp;
    unsigned int lr;
    unsigned int pc;
    unsigned int cpsr;
};
typedef struct context_t context_t;
/******************************************************************************/
// Task control block
struct task_t
{
    unsigned int unknown1[13];
    char *name;
    unsigned int options;
    unsigned int state;
    unsigned int priority;
    unsigned int unknown2[12];
    void *entry;
    void *stack_base;
    void *stack_limit;
    void *stack_end;
    unsigned int error_num;
    unsigned int exit_code;
    unsigned int unknown3[7];
    void *task_std_fp[3];           // pointers to FILE structures
    unsigned int task_std_fd[3];    // std file descriptors
    unsigned int unknown4[24];
    context_t context;
    unsigned int unknown5[11];
};
typedef struct task_t task_t;
/******************************************************************************/
#endif
