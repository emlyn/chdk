#include "lolevel.h"
#include "platform.h"

#if defined (CAMERA_a720)
#define _U	0x01	/* upper */
#define _L	0x02	/* lower */
#define _D	0x04	/* digit */
#define _C	0x08	/* cntrl */
#define _P	0x10	/* punct */
#define _S	0x20	/* white space (space/lf/tab) */
#define _X	0x40	/* hex digit */
#define _SP	0x80	/* hard space (0x20) */
unsigned char _ctype[] = {
_C,_C,_C,_C,_C,_C,_C,_C,			/* 0-7 */
_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,		/* 8-15 */
_C,_C,_C,_C,_C,_C,_C,_C,			/* 16-23 */
_C,_C,_C,_C,_C,_C,_C,_C,			/* 24-31 */
_S|_SP,_P,_P,_P,_P,_P,_P,_P,			/* 32-39 */
_P,_P,_P,_P,_P,_P,_P,_P,			/* 40-47 */
_D,_D,_D,_D,_D,_D,_D,_D,			/* 48-55 */
_D,_D,_P,_P,_P,_P,_P,_P,			/* 56-63 */
_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,	/* 64-71 */
_U,_U,_U,_U,_U,_U,_U,_U,			/* 72-79 */
_U,_U,_U,_U,_U,_U,_U,_U,			/* 80-87 */
_U,_U,_U,_P,_P,_P,_P,_P,			/* 88-95 */
_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,	/* 96-103 */
_L,_L,_L,_L,_L,_L,_L,_L,			/* 104-111 */
_L,_L,_L,_L,_L,_L,_L,_L,			/* 112-119 */
_L,_L,_L,_P,_P,_P,_P,_C,			/* 120-127 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 128-143 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 144-159 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 160-175 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 176-191 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 192-207 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 208-223 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		/* 224-239 */
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		/* 240-255 */ 
#endif

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
#if !defined (CAMERA_ixus700_sd500) && !defined (CAMERA_ixus800_sd700) && !defined(CAMERA_a560) 
    _MoveFocusLensToDistance((short*)&newpos);
    //while (focus_busy);
    while ((shooting_is_flash_ready()!=1) || (focus_busy));
    newpos = _GetFocusLensSubjectDistance();
    _SetPropertyCase(PROPCASE_SUBJECT_DIST1, &newpos, sizeof(newpos));
    _SetPropertyCase(PROPCASE_SUBJECT_DIST2, &newpos, sizeof(newpos));
#endif
}

long stat_get_vbatt()
{
    return _VbattGet();
}


long get_tick_count()
{
long t;
#if !defined(CAMERA_a720)
    _GetSystemTime(&t);
    return t;
#else
    return (int)_GetSystemTime(&t);
#endif
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
#if !defined(CAMERA_a720)  
    return _isdigit(c);
#else
    return _ctype[c]&_D;
#endif
}

int isspace(int c) {
#if !defined(CAMERA_a720)  
    return _isspace(c);
#else
    return _ctype[c]&_S;
#endif

}

int isalpha(int c) {
#if !defined(CAMERA_a720)  
    return _isalpha(c);
#else
    return _ctype[c]&(_U|_L);
#endif
}

int isupper(int c) {
#if !defined(CAMERA_a720)  
    return _isupper(c);
#else
    return _ctype[c]&_U;
#endif

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
#if !defined(CAMERA_a720)   
    return _strpbrk(s, accept);
#else
    const char *sc1,*sc2;

    for( sc1 = s; *sc1 != '\0'; ++sc1) {
     for( sc2 = accept; *sc2 != '\0'; ++sc2) {
      if (*sc1 == *sc2) return (char *) sc1;
     }
    }
return (void*)0;
#endif
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
#if !defined (CAMERA_a720)
    return _localtime(_tod);
#else
#warning  do something with this!  - sizeof(x[]) must be >= sizeof(struct tm)
  static int x[9];
  return _LocalTime(_tod, &x);   
#endif
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
# if !defined (CAMERA_a720)
    return _readdir(d);
#else
#warning  do something with this!  - sizeof(de[]) must be >= sizeof(struct dirent)
  static char de[40];
  _ReadFastDir(d, &de);
  return de[0]? &de : (void*)0;
#endif
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

#if defined(CAMERA_g7) || defined(CAMERA_a710)
static char mbr_buf[512];
int mbr_read(char* mbr_sector, unsigned long drive_total_sectors, unsigned long *part_start_sector,  unsigned long *part_length){
// return value: 1 - success, 0 - fail
 
 int offset=0x10; // points to partition #2
 int valid;
  
 if ((mbr_sector[0x1FE]!=0x55) || (mbr_sector[0x1FF]!=0xAA)) return 0; // signature check 

 _memcpy(mbr_buf,mbr_sector,512);

 while(offset>=0) {
 
  *part_start_sector=(*(unsigned short*)(mbr_sector+offset+0x1C8)<<16) | *(unsigned short*)(mbr_sector+offset+0x1C6); 
  *part_length=(*(unsigned short*)(mbr_sector+offset+0x1CC)<<16) | *(unsigned short*)(mbr_sector+offset+0x1CA); 

  valid= (*part_start_sector) && (*part_length) &&
         (*part_start_sector<=drive_total_sectors) && 
         (*part_start_sector+*part_length<=drive_total_sectors) &&
         ((mbr_sector[offset+0x1BE]==0) || (mbr_sector[offset+0x1BE]==0x80)); // status: 0x80 (active) or 0 (non-active)

  if (valid && (mbr_sector[0x1C2+offset]==0x0B)) break;   // FAT32 secondary partition

  offset-=0x10;

 }

 return valid;
}

int get_part_count(void){
 unsigned long part_start_sector, part_length;
 char part_status, part_type;
 int i;
 int count=0;
 for (i=0; i<=1;i++){
  part_start_sector=(*(unsigned short*)(mbr_buf+i*16+0x1C8)<<16) | *(unsigned short*)(mbr_buf+i*16+0x1C6); 
  part_length=(*(unsigned short*)(mbr_buf+i*16+0x1CC)<<16) | *(unsigned short*)(mbr_buf+i*16+0x1CA); 
  part_status=mbr_buf[i*16+0x1BE];
  part_type=mbr_buf[0x1C2+i*16];
  if ( part_start_sector && part_length && part_type && ((part_status==0) || (part_status==0x80)) ) count++;
 }
 return count;
}

void swap_partitions(void){
 int i;
 char c;
 for(i=0;i<16;i++){
  c=mbr_buf[i+0x1BE];
  mbr_buf[i+0x1BE]=mbr_buf[i+0x1CE];
  mbr_buf[i+0x1CE]=c;
 }
 _WriteSDCard(0,0,1,&mbr_buf);
}

#endif
