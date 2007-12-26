#include "lolevel.h"
#include "platform.h"

void msleep(long msec)
{
    _SleepTask(msec);
}

void task_lock()
{
    _taskLock();
}

void task_unlock()
{
    _taskUnlock();
}

long get_property_case(long id, void *buf, long bufsize)
{
    return _GetPropertyCase(id, buf, bufsize);
}

long set_property_case(long id, void *buf, long bufsize)
{
    return _SetPropertyCase(id, buf, bufsize);
}

void remount_filesystem()
{
    _Unmount_FileSystem();
    _Mount_FileSystem();
}


void mark_filesystem_bootable()
{
    _UpdateMBROnFlash(0, 0x40, "BOOTDISK");
}

void vid_bitmap_refresh()
{
    _RefreshPhysicalScreen(1);
}


long get_parameter_data(long id, void *buf, long bufsize)
{
    return _GetParameterData(id|0x4000, buf, bufsize);
}

long set_parameter_data(long id, void *buf, long bufsize)
{
    return _SetParameterData(id|0x4000, buf, bufsize);
}

long lens_get_zoom_pos()
{
    return _GetZoomLensCurrentPosition();
}

void lens_set_zoom_pos(long newpos)
{
}

long lens_get_zoom_point()
{
    return _GetZoomLensCurrentPoint();
}

void lens_set_zoom_point(long newpt)
{
    if (newpt < 0) {
        newpt = 0;
    } else if (newpt >= zoom_points) {
        newpt = zoom_points-1;
    }
    _MoveZoomLensWithPoint((short*)&newpt);
    while (zoom_busy);
}

void lens_set_zoom_speed(long newspd)
{
    if (newspd < 5) {
        newspd = 5;
    } else if (newspd > 100) {
        newspd = 100;
    }
    _SetZoomActuatorSpeedPercent((short*)&newspd);
}

void lens_set_focus_pos(long newpos)
{
 #if !defined(CAMERA_ixus700_sd500) 
    _MoveFocusLensToDistance((short*)&newpos);
    //while (focus_busy);
    while ((shooting_is_flash_ready()!=1) || (focus_busy));
    newpos = _GetFocusLensSubjectDistance();
    _SetPropertyCase(65, &newpos, sizeof(newpos));
    _SetPropertyCase(66, &newpos, sizeof(newpos));
 #endif
}

long stat_get_vbatt()
{
    return _VbattGet();
}


long get_tick_count()
{
    long t;
    _GetSystemTime(&t);
    return t;
}

/*int creat (const char *name, int flags)
{
    return _creat(name, flags);
}*/
int open (const char *name, int flags, int mode )
{
    return _Open(name, flags, mode);
}
int close (int fd)
{
    return _Close(fd);
}
int write (int fd, void *buffer, long nbytes)
{
    return _Write(fd, buffer, nbytes);
}
int read (int fd, void *buffer, long nbytes)
{
    return _Read(fd, buffer, nbytes);
}
int lseek (int fd, long offset, int whence)
{
    return _lseek(fd, offset, whence); /* yes, it's lower-case lseek here since Lseek calls just lseek (A610) */
}
long mkdir(const char *dirname)
{
    return _mkdir(dirname);
}

int remove(const char *name) {
    return _Remove(name);
}

int isdigit(int c) {
    return _isdigit(c);
}

int isspace(int c) {
    return _isspace(c);
}

int isalpha(int c) {
    return _isalpha(c);
}

int isupper(int c) {
    return _isupper(c);
}

long strlen(const char *s) {
    return _strlen(s);
}

int strcmp(const char *s1, const char *s2) {
    return _strcmp(s1, s2);
}

int strncmp(const char *s1, const char *s2, long n) {
    return _strncmp(s1, s2, n);
}

char *strchr(const char *s, int c) {
    return _strchr(s, c);
}

char *strcpy(char *dest, const char *src) {
    return _strcpy(dest, src);
}

char *strncpy(char *dest, const char *src, long n) {
    return _strncpy(dest, src, n);
}

char *strcat(char *dest, const char *app) {
    return _strcat(dest, app);
}

char *strrchr(const char *s, int c) {
    return _strrchr(s, c);
}

long strtol(const char *nptr, char **endptr, int base) {
    return _strtol(nptr, endptr, base);
}

char *strpbrk(const char *s, const char *accept) {
    return _strpbrk(s, accept);
}

long sprintf(char *s, const char *st, ...)
{
    long res;
    __builtin_va_list va;
    __builtin_va_start(va, st);
    res = _vsprintf(s, st, va);
    __builtin_va_end(va);
    return res;
}

unsigned long time(unsigned long *timer) {
    return _time(timer);
}

int utime(char *file, void *newTimes) {
    return _utime(file, newTimes);
}

void *localtime(const unsigned long *_tod) {
    return _localtime(_tod);
}

double _log(double x) {
    return __log(x);
}

double _log10(double x) {
    return __log10(x);
}

double _pow(double x, double y) {
    return __pow(x, y);
}

double _sqrt(double x) {
    return __sqrt(x);
}

void *malloc(long size) {
    return _malloc(size);
}

void free(void *p) {
    return _free(p);
}

void *memcpy(void *dest, const void *src, long n) {
    return _memcpy(dest, src, n);
}

void *memset(void *s, int c, int n) {
    return _memset(s, c, n);
}

int memcmp(const void *s1, const void *s2, long n) {
    return _memcmp(s1, s2, n);
}

int rand(void) {
    return _rand();
}

void *srand(unsigned int seed) {
    return _srand(seed);
}

void qsort(void *__base, int __nelem, int __size, int (*__cmp)(const void *__e1, const void *__e2)) {
    _qsort(__base, __nelem, __size, __cmp);
}

void *opendir(const char* name) {
    return _opendir(name);
}

void* readdir(void *d) {
    return _readdir(d);
}

int closedir(void *d) {
    return _closedir(d);
}

void rewinddir(void *d) {
    return _rewinddir(d);
}

int stat(char *name, void *pStat) {
    return _stat(name, pStat);
}

void *umalloc(long size) {
    return _AllocateUncacheableMemory(size);
}

void ufree(void *p) {
    return _FreeUncacheableMemory(p);
}

static int shutdown_disabled = 0;
void disable_shutdown() {
    if (!shutdown_disabled) {
        _LockMainPower();
        shutdown_disabled = 1;
    }
}

void enable_shutdown() {
    if (shutdown_disabled) {
        _UnlockMainPower();
        shutdown_disabled = 0;
    }
}

long Fopen_Fut(const char *filename, const char *mode){
 return _Fopen_Fut(filename,mode);
}

void Fclose_Fut(long file){
 _Fclose_Fut(file);
}

long Fread_Fut(void *buf, long elsize, long count, long f){
 return _Fread_Fut(buf,  elsize,  count, f);
}

long Fwrite_Fut(const void *buf, long elsize, long count, long f){
  return _Fwrite_Fut(buf, elsize, count, f);
}

long Fseek_Fut(long file, long offset, long whence){
 return  _Fseek_Fut(file, offset, whence);
}

int rename(const char *oldname, const char *newname){
 return _rename(oldname, newname);
}

unsigned int GetFreeCardSpaceKb(void){
 return (_GetDrive_FreeClusters(0)*(_GetDrive_ClusterSize(0)>>9))>>1;
}

unsigned int GetTotalCardSpaceKb(void){
 return (_GetDrive_TotalClusters(0)*(_GetDrive_ClusterSize(0)>>9))>>1;
}
