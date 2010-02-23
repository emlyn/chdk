#ifndef _DRYOS_R31_
#define _DRYOS_R31_
/******************************************************************************/
/**              DRYOS version 2.3, release #0031                            **/
/**              DRYOS version 2.3, release #0039                            **/
/**              Internal DryOS kernel data types and constants              **/
/******************************************************************************/
#define TASK_STATE_READY    0
#define TASK_STATE_WAIT     1
#define TASK_STATE_SUSPEND  2
/******************************************************************************/
// Task context
struct context_t
{
    unsigned int cpsr;
    unsigned int r[13];
    unsigned int lr;
    unsigned int pc;
};
typedef struct context_t context_t;
/******************************************************************************/
// Task control block
struct task_t
{
    unsigned int unknown1[2];
    unsigned int priority;
    void *entry;
    unsigned int argument;
    unsigned int unknown2[2];
    void *stack_addr;
    unsigned int stack_size;
    char *name;
    unsigned int unknown3[6];
    unsigned int task_id;
    unsigned char unknown4[5];
    unsigned char state;
    unsigned char unknown5[6];
    context_t *context;         // SP value, context stored on the stack
};
typedef struct task_t task_t;
/******************************************************************************/
#endif
