#ifndef LOLEVEL_H
#define LOLEVEL_H

#ifndef LOW_LEVEL
#error File can be included when platform is built only!
#endif

#ifndef __arm__
#error File can be included in ARM mode only!
#endif

/* Canon stuff */
extern long *_GetSystemTime(long *t);
extern long _GetZoomLensCurrentPosition();
extern long _GetZoomLensCurrentPoint();
extern long _GetFocusLensCurrentPosition();
extern long _GetFocusLensSubjectDistance();
extern long _GetFocusLensSubjectDistanceFromLens();
extern long _GetCurrentTargetDistance();
extern long _GetPropertyCase(long opt_id, void *buf, long bufsize);
extern long _SetPropertyCase(long opt_id, void *buf, long bufsize);
extern long _IsStrobeChargeCompleted();
extern long _VbattGet();
extern void _RefreshPhysicalScreen(long f);
extern void _Unmount_FileSystem();
extern void _Mount_FileSystem();
extern void _SleepTask(long msec);
extern int _CreateTask (const char *name, int prio, int stack_size /*?*/, 
    void *entry, long parm /*?*/);
extern void _SleepTask(long msec);
extern void __attribute__((noreturn)) _ExitTask();
extern long _GetPropertyCase(long opt_id, void *buf, long bufsize);
extern long _SetPropertyCase(long opt_id, void *buf, long bufsize);
extern long _IsStrobeChargeCompleted();

/* Canon stuff with nonoriginal naming */
extern long _GetParameterData(long id, void *buf, long size);
extern long _SetParameterData(long id, void *buf, long size);
extern void _UpdateMBROnFlash(int driveno, long offset, char *str);

/* standart C library */
//extern int _creat (const char *name, int flags);
extern int _open (const char *name, int flags, int mode );
extern int _close (int fd);
extern int _write (int fd, void *buffer, long nbytes);
extern int _read (int fd, void *buffer, long nbytes);
extern int _lseek (int fd, long offset, int whence);
extern long _mkdir(const char *dirname);

extern int _Open (const char *name, int flags, int mode );
extern int _Close (int fd);
extern int _Write (int fd, void *buffer, long nbytes);
extern int _Read (int fd, void *buffer, long nbytes);
extern int _Lseek (int fd, long offset, int whence);

extern int _strcmp(const char *s1, const char *s2);
extern int _strncmp(const char *s1, const char *s2, long n);
extern long _strlen(const char *s);
extern void *_memcpy(void *dest, const void *src, long n);
extern int _vsprintf(char *buf, const char *fmt, __builtin_va_list va_list);

/* VxWorks */
extern long _taskLock();
extern long _taskUnlock();
extern int _taskCreateHookAdd (void *createHook);
extern int _taskDeleteHookAdd (void *deleteHook);
extern long _iosDevAdd(void*,void*,int);
extern long _iosDrvInstall(void*,void*,void*,void*,void*,void*,void*);

/* misc */
extern const char aPhysw;
extern long physw_run;
extern long _kbd_p1_f();
extern void _kbd_p2_f();
extern void _kbd_pwr_on();
extern void _kbd_pwr_off();
extern void _kbd_read_keys_r2(void*p);
extern long physw_status[3];
void __attribute__((naked,noinline))
    mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf);

void kbd_fetch_data(long *dst);

/* math */
extern double __log(double x);
extern double __log10(double x);
extern double __pow(double x, double y);
extern double __sqrt(double x);

#endif
