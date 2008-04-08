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
extern long _MoveZoomLensWithPoint(short *pos);
extern long _SetZoomActuatorSpeedPercent(short *perc);
extern volatile long zoom_busy;
extern long _GetFocusLensCurrentPosition();
extern long _GetFocusLensSubjectDistance();
extern long _GetFocusLensSubjectDistanceFromLens();
extern void _MoveFocusLensToDistance(short *dist); 
extern void _PutInNdFilter();
extern void _PutOutNdFilter();
extern volatile long focus_busy;
extern long _GetCurrentAvValue();
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

long _SetEventFlag(void *flag, long what);
long _CheckAnyEventFlag(void *flag, long mask, long *res);
long _GetEventFlagValue(void *flag, long *res);

long _ReceiveMessageQueue(void *msgq, long *dst, long unk1 /* maybe size? */);

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
extern int _Remove(const char *name);

extern long _Fopen_Fut(const char *filename, const char *mode);
extern void _Fclose_Fut(long file);
extern long _Fread_Fut(void *buf, long elsize, long count, long f);
extern long _Fwrite_Fut(const void *buf, long elsize, long count, long f);
extern long _Fseek_Fut(long file, long offset, long whence);
extern long _Fflush_Fut(long file);
extern int _rename(const char *oldname, const char *newname);

extern int _isdigit(int c);
extern int _isspace(int c);
extern int _isalpha(int c);
extern int _isupper(int c);

extern long _strlen(const char *s);
extern int _strcmp(const char *s1, const char *s2);
extern int _strncmp(const char *s1, const char *s2, long n);
extern char *_strchr(const char *s, int c);
extern char *_strcpy(char *dest, const char *src);
extern char *_strncpy(char *dest, const char *src, long n);
extern char *_strcat(char *dest, const char *app);
extern char *_strrchr(const char *s, int c);
extern char *_strpbrk(const char *s, const char *accept);

extern long _strtol(const char *nptr, char **endptr, int base);

extern int _vsprintf(char *buf, const char *fmt, __builtin_va_list va_list);

extern void *_malloc(long size);
extern void _free(void *p);
extern void *_AllocateUncacheableMemory(long size);
extern void _FreeUncacheableMemory(void *p);

extern void *_memcpy(void *dest, const void *src, long n);
extern void *_memset(void *s, int c, int n);
extern int _memcmp(const void *s1, const void *s2, long n);

extern void _qsort (void *__base, int __nelem, int __size, int (*__cmp)(const void *__e1, const void *__e2));

/* VxWorks */
extern long _taskLock();
extern long _taskUnlock();
extern int _taskCreateHookAdd (void *createHook);
extern int _taskDeleteHookAdd (void *deleteHook);
extern long _iosDevAdd(void*,void*,int);
extern long _iosDrvInstall(void*,void*,void*,void*,void*,void*,void*);
extern void _GiveSemaphore(int sem);

/* misc */
extern const char aPhysw;
extern long physw_run;
extern long _kbd_p1_f();
extern void _kbd_p2_f();
extern void _kbd_pwr_on();
extern void _kbd_pwr_off();
extern void _kbd_read_keys_r2(void*p);
extern long physw_status[3], physw_copy[3];

void __attribute__((naked,noinline)) mykbd_task();
extern void capt_seq_task();
extern void movie_record_task();
extern void init_file_modules_task();

void kbd_fetch_data(long *dst);

extern long playrec_mode; //used on S-series only

extern void *led_table;
extern void _UniqueLedOn(void *addr, long brightness);
extern void _UniqueLedOff(void *addr);
struct led_control {int led_num; int action; int brightness; int blink_count;};
extern int _PostLEDMessage(struct led_control *);


extern long _LockMainPower();
extern long _UnlockMainPower();
extern void _SetAutoShutdownTime(int t);


/* math */
extern int _rand(void);
extern void* _srand(unsigned int seed);

extern double __log(double x);
extern double __log10(double x);
extern double __pow(double x, double y);
extern double __sqrt(double x);

/* time */
extern int _utime(char *file, void *newTimes);
extern unsigned long _time(unsigned long *timer);
extern void *_localtime(const unsigned long *_tod);
extern void *_LocalTime(const unsigned long *_tod, void * t_m); // DRYOS

/* file */
extern void *_opendir(const char* name);
extern void *_readdir(void *d);
extern int _ReadFastDir(void *d, void* dd); // DRYOS
extern int   _closedir(void *d);
extern void  _rewinddir(void *d);
extern int   _stat(char *name, void *pStat);
extern unsigned long _GetDrive_ClusterSize(int drive);
extern unsigned long _GetDrive_TotalClusters(int drive);
extern unsigned long _GetDrive_FreeClusters(int drive);
extern int _WriteSDCard(unsigned int drive, unsigned int start_sect, unsigned int num_sect, void *buf);
extern void _UnsetZoomForMovie(void);

#endif
