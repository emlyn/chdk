#include "platform.h"
#include "core.h"
#include "keyboard.h"

/* VxWorks stuff */
extern long sysMemTopPtr;
extern long sysPhysMemTopPtr;
extern int taskCreateHookAdd (void *createHook);
extern int taskDeleteHookAdd (void *deleteHook);

/* Canon stuff */
extern int CreateTask (const char *name, int prio, int stack_size /*?*/, 
    void *entry, long parm /*?*/);
extern long CreateTaskStrict(const char *taskname, long a, long b, void *func, long d);
extern void SleepTask(long msec);
extern void __attribute__((noreturn)) ExitTask();
extern long *GetSystemTime(long *t);
extern long GetZoomLensCurrentPosition();
extern long GetZoomLensCurrentPoint();
extern long GetFocusLensCurrentPosition();
extern long GetFocusLensSubjectDistance();
extern long GetFocusLensSubjectDistanceFromLens();
extern long GetPropertyCase(long opt_id, void *buf, long bufsize);
extern long SetPropertyCase(long opt_id, void *buf, long bufsize);
extern void RefreshPhysicalScreen(long f);
extern long IsStrobeChargeCompleted();

extern long GetParameterData(long id, long unk, void *buf, long size);
extern long SetParameterData(long id, long unk, void *buf, long size);

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

extern void boot();
extern void *get_parameter_data_magic_pointer();

/*
 *
 *
 *
 *
 *
 *
 *
 *
 */

void mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf);

void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}

static int stop_hooking;
static void (*taskprev)(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9);


static void task_start_hook(
    long p0,    long p1,    long p2,    long p3,    long p4,
    long p5,    long p6,    long p7,    long p8,    long p9)
{

    CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);

    taskprev(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
}

int my_ncmp(const char *s1, const char *s2, long len)
{
    int i;
    for (i=0;i<len;i++){
	if (s1[i] != s2[i])
	    return 1;
    }
    return 0;
}

void createHook (void *pNewTcb)
{
    char *name = (char*)(*(long*)((char*)pNewTcb+0x34));
    long *entry = (long*)((char*)pNewTcb+0x74);

    // always hook first task creation
    // to create SpyProc
    if (!stop_hooking){
	taskprev = (void*)(*entry);
	*entry = (long)task_start_hook;
	stop_hooking = 1;
    } else {
	// hook/replace another tasks
	if (my_ncmp(name, "tPhySw", 6) == 0){
	    *entry = (long)mykbd_task;
	}
	core_hook_task_create(pNewTcb);
    }
}

void deleteHook (void *pTcb)
{
    core_hook_task_delete(pTcb);
}

/*
 * Startup
 * Initialize .data and .bss segments & erase other memory.
 * boot() call setups create|delete task hooks.
 *
 *
 *
 *
 *
 */

void startup()
{
    long *bss = &wrs_kernel_bss_start;
    long *ptr;

    // sanity check
    if ((long)&wrs_kernel_bss_end > (MEMISOSTART + MEMISOSIZE)){
	started();
	shutdown();
    }

    // initialize .bss senment
    while (bss<&wrs_kernel_bss_end)
	*bss++ = 0;

    // fill memory with this magic value so we could see what
    // parts of memory were or not used
    
    // update:
    // this seems to be required for unknown reason
    // or else sryproc startup will fail from
    // time to time...
    for (ptr=(void*)MEMBASEADDR;((long)ptr)<MEMISOSTART;ptr+=4){
	ptr[0]=0x55555555;
	ptr[1]=0x55555555;
	ptr[2]=0x55555555;
	ptr[3]=0x55555555;
    }

    boot();
}

/*
 * Keyboard handling
 *
 *
 *
 *
 *
 *
 *
 */

long get_tick_count()
{
    long t;
    GetSystemTime(&t);
    return t;
}


/****************/

extern const char aPhysw;
extern long physw_run;
extern long kbd_p1_f();
extern void kbd_p2_f();

#define NEW_SS (0x2000)

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

long __attribute__((naked)) wrap_kbd_p1_f() ;

static void __attribute__((noinline)) mykbd_task_proceed()
{
    while (physw_run){
	SleepTask(10);

	if (wrap_kbd_p1_f() == 1){ // autorepeat ?
	    kbd_p2_f();
	}
    }
}

void __attribute__((naked,noinline))
mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf)
{
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     *	function arguments destroyed;
     *	function CAN NOT return properly;
     *	MUST NOT call or use stack variables before stack
     *	is setup properly;
     *
     */

    register int i;
    register long *newstack;

#ifndef MALLOCD_STACK
    newstack = (void*)kbd_stack;
#else
    newstack = malloc(NEW_SS);
#endif

    for (i=0;i<NEW_SS/4;i++)
	newstack[i]=0xdededede;

    asm volatile (
	"MOV	SP, %0"
	:: "r"(((char*)newstack)+NEW_SS)
	: "memory"
    );

    mykbd_task_proceed();

    /* function can be modified to restore SP here...
     */

    ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{

    asm volatile(
                "STMFD   SP!, {R4-R7,LR}\n"
                "SUB     SP, SP, #0xC\n"
                "BL      my_kbd_read_keys\n"
		"B	 kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}

extern void kbd_pwr_on();
extern void kbd_pwr_off();
extern void kbd_read_keys_r2(void*p);
extern long physw_status[3];

static long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state;

void my_kbd_read_keys()
{
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    kbd_pwr_on();
    kbd_new_state[0] = 0;
    kbd_new_state[1] = *mmio1;
    kbd_new_state[2] = *mmio2 & 0xffff;

#if 0
    if ((new_state[2] & 0x00001000 /* print button */) == 0 )
	started();
    else
	finished();
#endif

    if (kbd_process() == 0){
	// leave it alone...
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = kbd_new_state[2];
#if 1
	kbd_mod_state = kbd_new_state[2];
#endif
    } else {
	// override keys
#if 1
	physw_status[2] = kbd_mod_state;
#else
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = (kbd_new_state[2] & (~0x1fff)) |
			  (kbd_mod_state & 0x1fff);
#endif
    }

    kbd_read_keys_r2(physw_status); // have no idea what's that
    
    kbd_pwr_off();
}

/****************/

static struct {
	long hackkey;
	long canonkey;
} keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ KEY_UP	, 0x00000001 },
	{ KEY_DOWN	, 0x00000002 },
	{ KEY_LEFT	, 0x00000008 },
	{ KEY_RIGHT	, 0x00000004 },
	{ KEY_SET	, 0x00000800 },
	{ KEY_SHOOT_FULL, 0x00000030 }, // note 3 here!
	{ KEY_SHOOT_HALF, 0x00000010 },
	{ KEY_ZOOM_IN	, 0x00000040 },
	{ KEY_ZOOM_OUT	, 0x00000080 },
	{ KEY_MENU	, 0x00000200 },
	{ KEY_DISPLAY	, 0x00000400 },
	{ KEY_PRINT	, 0x00001000 },
	{ KEY_ERASE	, 0x00000100 },
};

#define KEYSCNT (sizeof(keymap)/sizeof(keymap[0]))

void kbd_key_press(long key)
{
    int i;
    for (i=0;i<KEYSCNT;i++){
	if (keymap[i].hackkey == key){
	    kbd_mod_state &= ~keymap[i].canonkey;
	    return;
	}
    }
}

void kbd_key_release(long key)
{
    int i;
    for (i=0;i<KEYSCNT;i++){
	if (keymap[i].hackkey == key){
	    kbd_mod_state |= keymap[i].canonkey;
	    return;
	}
    }
}

void kbd_key_release_all()
{
    kbd_mod_state |= 0x1fff;
}

long kbd_is_key_pressed(long key)
{
    int i;
    for (i=0;i<KEYSCNT;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_new_state[2] & keymap[i].canonkey) == 0) ? 1:0;
	}
    }
    return 0;
}

long kbd_is_key_clicked(long key)
{
    int i;
    for (i=0;i<KEYSCNT;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
		    ((kbd_new_state[2] & keymap[i].canonkey) == 0);
	}
    }
    return 0;
}

long kbd_get_pressed_key()
{
    int i;
    for (i=0;i<KEYSCNT;i++){
	if ((kbd_new_state[2] & keymap[i].canonkey) == 0){
	    return keymap[i].hackkey;
	}
    }
    return 0;
}

long kbd_get_clicked_key()
{
    int i;
    for (i=0;i<KEYSCNT;i++){
	if (((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
	    ((kbd_new_state[2] & keymap[i].canonkey) == 0)){
	    return keymap[i].hackkey;
	}
    }
    return 0;
}

void *vid_get_bitmap_fb()
{
    return (void*)0x10361000;
}

void *vid_get_viewport_fb()
{
    return (void*)0x105f25e0;
}

long vid_get_bitmap_width()
{
    return 360;
}

long vid_get_bitmap_height()
{
    return 240;
}

/*******************************************************************/

long lens_get_zoom_pos()
{
    return GetZoomLensCurrentPosition();
}

void lens_set_zoom_pos(long newpos)
{
}

long lens_get_zoom_point()
{
    return GetZoomLensCurrentPoint();
}

void lens_set_zoom_point(long newpt)
{
}

long lens_get_focus_pos()
{
    return GetFocusLensSubjectDistance();
}

void lens_set_focus_pos(long newpos)
{
}

long stat_get_vbatt()
{
    return VbattGet();
}

/*******************************************************************/

const ApertureSize aperture_sizes_table[] = {
    {  9, 288, "2.8", },
    { 10, 320, "3.2", },
    { 11, 352, "3.5", },
    { 12, 384, "4.0", },
    { 13, 416, "4.5", },
    { 14, 448, "5.0", },
    { 15, 480, "5.6", },
    { 16, 512, "6.3", },
    { 17, 544, "7.1", },
    { 18, 576, "8.0", },
};

const ShutterSpeed shutter_speeds_table[] = {
    {-13, -384, "15", 15000000  },
    {-12, -352, "13", 13000000  },
    {-11, -320, "10", 10000000  },
    {-9, -288, "8", 8000000  },
    {-8, -256, "6", 6000000  },
    {-7, -224, "5", 5000000  },
    {-6, -192, "4", 4000000  },
    {-5, -160, "3.2", 3200000  },
    {-4, -128, "2.5", 2500000  },
    {-3, -96 , "2", 2000000  },
    {-2, -64 , "1.6", 1600000  },
    {-1, -32 , "1.3", 1300000  },
    { 0, 0, "1", 1000000  },
    { 1, 32, "0.8", 800000 },
    { 2, 64, "0.6", 600000 },
    { 3, 96, "0.5", 500000 },
    { 4, 128, "0.4", 400000 },
    { 5, 160, "0.3", 300000 },
    { 6, 192, "1/4", 250000 },
    { 7, 224, "1/5", 200000 },
    { 8, 256, "1/6", 166667 },
    { 9, 288, "1/8", 125000 },
    {10, 320, "1/10", 100000 },
    {11, 352, "1/13",  76923 },
    {12, 384, "1/15",  66667 },
    {13, 416, "1/20",  50000 },
    {14, 448, "1/25",  40000 },
    {15, 480, "1/30",  33333 },
    {16, 512, "1/40",  25000 },
    {17, 544, "1/50",  20000 },
    {18, 576, "1/60",  16667 },
    {19, 608, "1/80",  12500 },
    {20, 640, "1/100",  10000 },
    {21, 672, "1/125",   8000 },
    {22, 704, "1/160",   6250 },
    {23, 736, "1/200",   5000 },
    {24, 768, "1/250",   4000 },
    {25, 800, "1/320",   3125 },
    {26, 832, "1/400",   2500 },
    {27, 864, "1/500",   2000 },
    {28, 896, "1/640",   1563 },
    {30, 928, "1/800",   1250 },
    {31, 960, "1/1000",   1000 },
    {32, 992, "1/1250",    800 },
    {33, 1021, "1/1600",    625 },
    {34, 1053, "1/2000",    500 },
    {35, 1084, "1/2500",    400 },
};

#define SS_SIZE (sizeof(shutter_speeds_table)/sizeof(shutter_speeds_table[0]))
#define SSID_MIN (shutter_speeds_table[0].id)
#define SSID_MAX (shutter_speeds_table[SS_SIZE-1].id)

#define AS_SIZE (sizeof(aperture_sizes_table)/sizeof(aperture_sizes_table[0]))
#define ASID_MIN (aperture_sizes_table[0].id)
#define ASID_MAX (aperture_sizes_table[AS_SIZE-1].id)

int shooting_get_tv()
{
    short int tvv;
    long i;
    GetPropertyCase(40, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id == tvv)
	    return shutter_speeds_table[i].id;
    }
    return 0;
}

const ShutterSpeed *shooting_get_tv_line()
{
    short int tvv;
    long i;
    GetPropertyCase(40, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id == tvv)
	    return &shutter_speeds_table[i];
    }
    return 0;

}

void shooting_set_tv(int v)
{
    long i;
//    if ((v<SSID_MIN) || (v>SSID_MAX))
//	return;


    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].id == v){
	    short int vv = shutter_speeds_table[i].prop_id;
	    SetPropertyCase(40, &vv, sizeof(vv));
	    return;
	}
    }

}

void shooting_set_tv_rel(int v)
{
    int cv = shooting_get_tv();
    shooting_set_tv(cv+v);
}

int shooting_get_av()
{
    short int avv;
    long i;
    GetPropertyCase(39, &avv, sizeof(avv));
    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == avv)
	    return aperture_sizes_table[i].id;
    }
    return 0;
}

void shooting_set_av(int v)
{
    long i;

//    if ((v<ASID_MIN) || (v>ASID_MAX))
//	return;

    for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].id == v){
	    short int vv = aperture_sizes_table[i].prop_id;
	    SetPropertyCase(39, &vv, sizeof(vv));
	    return;
	}
    }
}

void shooting_set_av_rel(int v)
{
    int cv = shooting_get_av();
    shooting_set_av(cv+v);
}

int shooting_in_progress()
{
    int t = 0;
    GetPropertyCase(205, &t, 4);
    return t != 0;
}

int shooting_is_flash_ready()
{
    int t = 0;
/* well, I'm not sure what's exactly is happening here
 * but it works for a610-100e
 */
    GetPropertyCase(204, &t, 4);
    if (t == 3){
	GetPropertyCase(221, &t, 4);
	return (t==1) && IsStrobeChargeCompleted();
    }
    return 1;
}

void vid_bitmap_refresh()
{
    RefreshPhysicalScreen(1);
}


long get_parameter_data(long id, void *buf, long bufsize)
{
    long *magic = get_parameter_data_magic_pointer();
    return GetParameterData(id, magic[1], buf, bufsize);
}

long set_parameter_data(long id, void *buf, long bufsize)
{
    long *magic = get_parameter_data_magic_pointer();
    return SetParameterData(id, magic[1], buf, bufsize);
}

