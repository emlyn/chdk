#include "platform.h"
#include "core.h"
#include "lolevel.h"

static long (*prev_hhandler)(long a);

static void myhook1(long a)
{
    // only this caller allowed
    if (__builtin_return_address(0) == hook_raw_ret_addr()){
	core_save_raw_file();
    }
    prev_hhandler(a);
}


void hook_raw_install()
{
    long *p = hook_raw_fptr();

    _taskLock();
    if ((*p) != (long)myhook1){
	prev_hhandler = (void*)*p;
	*p=(long)myhook1;
    }
    _taskUnlock();
}

