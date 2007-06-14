#include "platform.h"
#include "core.h"
#include "lolevel.h"

#if 0

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

static long (*prev_hhandler)(long a);
static long raw_save_stage;


static void myhook1(long a)
{
    // only this caller allowed
    if (__builtin_return_address(0) == hook_raw_ret_addr()){
	raw_save_stage = RAWDATA_AVAILABLE;
	core_rawdata_available();
	while (raw_save_stage != RAWDATA_SAVED){
	    _SleepTask(10);
	}
	raw_save_stage = 0;
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

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}
#endif

