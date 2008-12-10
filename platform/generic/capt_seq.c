// generic capt_seq fuctions

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

// some cams use different values
// note: many cams ROM also accepts a value of 3, meaning unknown
#ifndef NR_ON
#define NR_ON (2)
#endif
#ifndef NR_OFF
#define NR_OFF (1)
#endif

static long raw_save_stage;
volatile long shutter_open_time=0; // for DNG EXIF creation

void __attribute__((naked,noinline)) capt_seq_hook_raw_here()
{
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");

    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available();
    while (raw_save_stage != RAWDATA_SAVED){
	_SleepTask(10);
    }

 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}


void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}

void __attribute__((naked,noinline)) capt_seq_hook_set_nr()
{
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");
    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
        // leave it alone
        break;
    case NOISE_REDUCTION_OFF:
        *nrflag = NR_OFF;
        break;
    case NOISE_REDUCTION_ON:
        *nrflag = NR_ON;
        break;
    };

 shutter_open_time=_time((void*)0); 

 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}

