#include "camera.h"
#include "lolevel.h"
#include "platform.h"
#include "conf.h"
#include "math.h"

#if CAM_DRYOS
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

#ifndef CAM_DRYOS
void task_lock()
{
    _taskLock();
}

void task_unlock()
{
    _taskUnlock();
}

const char *task_name(int id)
{
    return _taskName(id);
}

int task_id_list_get(int *idlist,int size)
{
    return _taskIdListGet(idlist,size);
}
#endif

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

void __attribute__((weak)) vid_bitmap_refresh()
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
    if (newpt==0) zoom_status=ZOOM_OPTICAL_MIN;
    else if (newpt >= zoom_points) zoom_status=ZOOM_OPTICAL_MAX;
    else zoom_status=ZOOM_OPTICAL_MEDIUM; 
    _SetPropertyCase(PROPCASE_OPTICAL_ZOOM_POSITION, &newpt, sizeof(newpt));
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
    _MoveFocusLensToDistance((short*)&newpos);
    //while (focus_busy);
    while ((shooting_is_flash_ready()!=1) || (focus_busy));
    newpos = _GetFocusLensSubjectDistance();
    _SetPropertyCase(PROPCASE_SUBJECT_DIST1, &newpos, sizeof(newpos));
    _SetPropertyCase(PROPCASE_SUBJECT_DIST2, &newpos, sizeof(newpos));
}

void play_sound(unsigned sound)
{
	static const int sounds[]={ 0x2001, //startup sound
                                0x2002, //shutter sound
                                0x2003, //button press sound
                                0x2004, //self-timer sound
                                0xC211, //short beep
                                50000,  // AF confirmation 
                                0xC507, // error beep imo
                                0x400D, // LONG ERROR BEEP CONTINIUOUS- warning, cannot be stopped (yet)
                            };
    if(sound >= sizeof(sounds)/sizeof(sounds[0]))
        return;

    _PT_PlaySound(sounds[sound], 0);
}

long stat_get_vbatt()
{
    return _VbattGet();
}

int get_battery_temp()
{
    return _GetBatteryTemperature();
}

int get_ccd_temp()
{
    return _GetCCDTemperature();
}

int get_optical_temp()
{
    return _GetOpticalTemperature();
}

long get_tick_count()
{
long t;
#if !CAM_DRYOS
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
#ifdef CAM_DRYOS_2_3_R39
    if(name[0]!='A')return -1;
#endif
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

int errnoOfTaskGet(int tid) {
#if !CAM_DRYOS
    return _errnoOfTaskGet(tid);
#else
    return 0;
#endif
}

int isdigit(int c) {
#if !CAM_DRYOS
    return _isdigit(c);
#else
    return _ctype[c]&_D;
#endif
}

int isspace(int c) {
#if !CAM_DRYOS
    return _isspace(c);
#else
    return _ctype[c]&_S;
#endif

}

int isalpha(int c) {
#if !CAM_DRYOS
    return _isalpha(c);
#else
    return _ctype[c]&(_U|_L);
#endif
}

int isupper(int c) {
#if !CAM_DRYOS
    return _isupper(c);
#else
    return _ctype[c]&_U;
#endif

}

int islower(int c) {
#if !CAM_DRYOS
    return _islower(c);
#else
    return _ctype[c]&_L;
#endif

}

int ispunct(int c) {
#if !CAM_DRYOS
    return _ispunct(c);
#else
    return _ctype[c]&_P;
#endif
}

int isxdigit(int c) {
#if !CAM_DRYOS
    return _isxdigit(c);
#else
    return _ctype[c]&(_X|_D);
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

unsigned long strtoul(const char *nptr, char **endptr, int base) {
#if CAM_DRYOS
    return (unsigned long)_strtolx(nptr, endptr, base, 0);
#else
    return _strtoul(nptr, endptr, base);
#endif
}

char *strpbrk(const char *s, const char *accept) {
#if !CAM_DRYOS
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

// strerror exists on vxworks cams, 
// but it does about the same thing as this
const char *strerror(int en) {
#if !CAM_DRYOS
    static char msg[20];
    sprintf(msg,"errno 0x%X",en);
    return msg;
#else
    return "error";
#endif
}

int tolower(int c) {
#if !CAM_DRYOS
	return _tolower(c);
#else
	return isupper(c) ? c - 'A' + 'a' : c;
#endif
}

int toupper(int c) {
#if !CAM_DRYOS
	return _toupper(c);
#else
	return islower(c) ? c - 'a' + 'A' : c;
#endif
}

unsigned long time(unsigned long *timer) {
    return _time(timer);
}

int utime(char *file, void *newTimes) {
#if !CAM_DRYOS
  return _utime(file, newTimes);
#else
 int res=0;
 int fd;
 fd = _open(file, 0, 0);

#ifdef CAM_DRYOS_2_3_R39
   if (fd>=0) {
       _close(fd);
       res=_SetFileTimeStamp(file, ((int*)newTimes)[0] , ((int*)newTimes)[1]);
   }
#else
     if (fd>=0) {
      res=_SetFileTimeStamp(fd, ((int*)newTimes)[0] , ((int*)newTimes)[1]);
      _close(fd);
     }
     // return value compatibe with utime: ok=0 fail=-1
#endif
  return (res)?0:-1;
#endif
}

void *localtime(const unsigned long *_tod) {
#if !CAM_DRYOS
    return _localtime(_tod);
#else
// for DRYOS cameras do something with this!  - sizeof(x[]) must be >= sizeof(struct tm) :  'static int x[9];'
  static int x[9];
  return _LocalTime(_tod, &x);   
#endif
}

long strftime(char *s, unsigned long maxsize, const char *format, /*const struct tm*/ void *timp) {
	return _strftime(s,maxsize,format,timp);
}

/*time_t*/ long mktime(/*struct tm*/ void *timp) {
#if !CAM_DRYOS
	return _mktime(timp);
#else
	int timp_ext[10]; // struct tm + a ptr
	_memcpy(timp_ext,timp,9*sizeof(int));
	timp_ext[9]=0;
	long retval = _mktime_ext(&timp_ext);
	_memcpy(timp,timp_ext,9*sizeof(int));
	return retval;
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

void *memchr(const void *s, int c, int n) {
#if !CAM_DRYOS
	return _memchr(s,c,n);
#else
	while (n-- > 0) {
		if (*(char *)s == c)
			return (void *)s;
		s++;
	}
	return (void *)0;
#endif
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
# if !CAM_DRYOS
    return _readdir(d);
#else
// for DRYOS cameras  A650, A720  do something with this!  - sizeof(de[]) must be >= sizeof(struct dirent): 'static char de[40];'
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
void camera_shutdown_in_a_second(void){
int i;
//#if CAM_DRYOS
//#else
_SetAutoShutdownTime(1); // 1 sec
for (i=0;i<200;i++) _UnlockMainPower(); // set power unlock counter to 200 or more, because every keyboard function call try to lock power again ( if "Disable LCD off" menu is "alt" or "script"). 
//#endif
}
long MakeDirectory_Fut(const char *dirname) {
 return _MakeDirectory_Fut(dirname,-1); // meaning of second arg is not clear, firmware seems to use -1
}

long Fopen_Fut(const char *filename, const char *mode){
 return _Fopen_Fut(filename,mode);
}

long Fclose_Fut(long file){
 return _Fclose_Fut(file);
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

long Feof_Fut(long file) {
 return _Feof_Fut(file);
}

long Fflush_Fut(long file) {
 return _Fflush_Fut(file);
}

char *Fgets_Fut(char *buf, int n, long f) {
 return _Fgets_Fut(buf,n,f);
}

long RenameFile_Fut(const char *oldname, const char *newname) {
 return _RenameFile_Fut(oldname, newname);
}

int rename(const char *oldname, const char *newname){
 // doesn't appear to work on a540
 return _rename(oldname, newname);
}

long DeleteFile_Fut(const char *name) {
 return _DeleteFile_Fut(name);
}

unsigned int GetFreeCardSpaceKb(void){
 return (_GetDrive_FreeClusters(0)*(_GetDrive_ClusterSize(0)>>9))>>1;
}

unsigned int GetTotalCardSpaceKb(void){
 return (_GetDrive_TotalClusters(0)*(_GetDrive_ClusterSize(0)>>9))>>1;
}


unsigned int GetJpgCount(void){

 return strtol(camera_jpeg_count_str(),((void*)0),0);
}

unsigned int GetRawCount(void){
 return GetFreeCardSpaceKb()/((hook_raw_size() / 1024)+GetFreeCardSpaceKb()/GetJpgCount());

}

void EnterToCompensationEVF(void)
{
  _EnterToCompensationEVF();
}

void ExitFromCompensationEVF()
{
  _ExitFromCompensationEVF();
}

void TurnOnBackLight(void)
{
  _TurnOnBackLight();
}

void TurnOffBackLight(void)
{
  _TurnOffBackLight();
}

void DoAFLock(void)
{
  _DoAFLock();
}

void UnlockAF(void)
{
  _UnlockAF();
}

#if CAM_MULTIPART

#define SECTOR_SIZE 512
static char *mbr_buf=(void*)0;
static unsigned long drive_sectors;

int mbr_read(char* mbr_sector, unsigned long drive_total_sectors, unsigned long *part_start_sector,  unsigned long *part_length){
// return value: 1 - success, 0 - fail
// called only in VxWorks
 
 int offset=0x10; // points to partition #2
 int valid;
  
 if ((mbr_sector[0x1FE]!=0x55) || (mbr_sector[0x1FF]!=0xAA)) return 0; // signature check 

 mbr_buf=_AllocateUncacheableMemory(SECTOR_SIZE);
 _memcpy(mbr_buf,mbr_sector,SECTOR_SIZE);
 drive_sectors=drive_total_sectors;

 while(offset>=0) {
 
  *part_start_sector=(*(unsigned short*)(mbr_sector+offset+0x1C8)<<16) | *(unsigned short*)(mbr_sector+offset+0x1C6); 
  *part_length=(*(unsigned short*)(mbr_sector+offset+0x1CC)<<16) | *(unsigned short*)(mbr_sector+offset+0x1CA); 

  valid= (*part_start_sector) && (*part_length) &&
         (*part_start_sector<=drive_total_sectors) && 
         (*part_start_sector+*part_length<=drive_total_sectors) &&
         ((mbr_sector[offset+0x1BE]==0) || (mbr_sector[offset+0x1BE]==0x80)); // status: 0x80 (active) or 0 (non-active)

  if (valid && ((mbr_sector[0x1C2+offset]==0x0B) || (mbr_sector[0x1C2+offset]==0x0C))) break;   // FAT32 secondary partition

  offset-=0x10;

 }

 return valid;
}


int mbr_read_dryos(unsigned long drive_total_sectors, char* mbr_sector ){
// Called only in DRYOS
 mbr_buf=_AllocateUncacheableMemory(SECTOR_SIZE);
 _memcpy(mbr_buf,mbr_sector,SECTOR_SIZE);
 drive_sectors=drive_total_sectors;
 return drive_total_sectors;
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
 _WriteSDCard(0,0,1,mbr_buf);
}

void create_partitions(void){
 unsigned long start, length;
 char type;

 _memset(mbr_buf,0,SECTOR_SIZE);
 
 start=1; length=2*1024*1024/SECTOR_SIZE; //2 Mb
 type=1; // FAT primary
 mbr_buf[0x1BE + 4]=type;
 mbr_buf[0x1BE + 8]=start;   mbr_buf[0x1BE + 9]=start>>8;   mbr_buf[0x1BE + 10]=start>>16;  mbr_buf[0x1BE + 11]=start>>24;
 mbr_buf[0x1BE + 12]=length; mbr_buf[0x1BE + 13]=length>>8; mbr_buf[0x1BE + 14]=length>>16; mbr_buf[0x1BE + 15]=length>>24;

 start=start+length; length=drive_sectors-start-1; 
 type=0x0B;  //FAT32 primary;
 mbr_buf[0x1CE + 4]=type;
 mbr_buf[0x1CE + 8]=start;   mbr_buf[0x1CE + 9]=start>>8;   mbr_buf[0x1CE + 10]=start>>16;  mbr_buf[0x1CE + 11]=start>>24;
 mbr_buf[0x1CE + 12]=length; mbr_buf[0x1CE + 13]=length>>8; mbr_buf[0x1CE + 14]=length>>16; mbr_buf[0x1CE + 15]=length>>24;

 mbr_buf[0x1FE]=0x55; mbr_buf[0x1FF]=0xAA; // signature;

 _WriteSDCard(0,0,1,mbr_buf);
}

#endif

int mute_on_zoom(int x){
 static int old_busy=0;
 int busy=zoom_busy||focus_busy;
 if (old_busy!=busy) {
  if (busy) {
#if CAM_CAN_MUTE_MICROPHONE
   if (conf.mute_on_zoom) _TurnOffMic();
#endif
   }
   else {
#if CAM_CAN_MUTE_MICROPHONE
  if (conf.mute_on_zoom) _TurnOnMic();
#endif
#if CAM_EV_IN_VIDEO
  if (get_ev_video_avail()) set_ev_video_avail(0);
#endif
  }
  old_busy=busy;
 }
 return x; // preserve R0 if called from assembler
}


#if CAM_AF_SCAN_DURING_VIDEO_RECORD
void MakeAFScan(void){
 int a=0, save;
 if (zoom_busy || focus_busy) return;
 save=some_flag_for_af_scan;
 some_flag_for_af_scan=0;
#if CAM_AF_SCAN_DURING_VIDEO_RECORD == 2
 parameter_for_af_scan=3;
#endif
 _MakeAFScan(&a, 3);
 some_flag_for_af_scan=save;
 _ExpCtrlTool_StartContiAE(0,0);
}
#endif

long __attribute__((weak)) get_jogdial_direction(void){
 return 0;
}

#if defined (DNG_EXT_FROM)

#define DNG_EXT_TO ".DNG"

typedef int(*p_some_f)(char*, int);

extern p_some_f some_f_for_dng;  // camera variable!
extern char* second_ext_for_dng; // camera variable!

p_some_f default_some_f;         
char *   default_second_ext;     

char *_strstr (const char *s1, const char *s2)
{
  const char *p = s1;
  const int len = _strlen (s2);

  for (; (p = _strchr (p, *s2)) != 0; p++)
    {
      if (_strncmp (p, s2, len) == 0)
	return (char *)p;
    }
  return (0);
}


int my_some_f(char *s, int x){
  char *f;
  f=_strstr(s, DNG_EXT_FROM);
  if (f) _memcpy(f, DNG_EXT_TO, sizeof(DNG_EXT_TO)-1);
  return default_some_f(s, x);
}

void save_ext_for_dng(void){
 default_some_f=some_f_for_dng;
 default_second_ext=second_ext_for_dng;
}

void change_ext_to_dng(void){
 some_f_for_dng=my_some_f;
 second_ext_for_dng=DNG_EXT_TO; 
}

void change_ext_to_default(void){
 some_f_for_dng=default_some_f;
 second_ext_for_dng=default_second_ext;
}

#endif


static long drv_struct[16];

long dh_err()
{
    return -1;
}

void drv_self_hide()
{
#if !CAM_DRYOS
    long drvnum;
    
    drvnum = _iosDrvInstall(dh_err,dh_err,dh_err,dh_err,dh_err,dh_err,dh_err);
    if (drvnum >= 0)
	_iosDevAdd(drv_struct, "A/DISKBOOT.BIN", drvnum);
#endif
}

void drv_self_unhide(){
#if !CAM_DRYOS
 _iosDevDelete(drv_struct);
#endif
}

int  apex2us(int apex_tv){
#if CAM_EXT_TV_RANGE
/*
 Extended Tv, by barberofcivil, http://chdk.setepontos.com/index.php/topic,4392.0.html
 Explanation by reyalP:
 In every port, the original shutter overrides (as opposed to super long exposure) worked by
 setting the propcase values at some point after auto-exposure has happened (except in manual
 modes, where the manual control propcases may be used instead). The Canon code previously took
 these values unchanged for short exposures. In newer cameras, like on the SX10 / SD980, the value
 is changed, apparently some time after it has been retrieved from the propcase. We know this is
 the case, because the propcase value itself doesn't get clamped to the allowed range (if it did,
 barberofcivil's code wouldn't work).
*/
	short tv;
	tv = shooting_get_tv96();
	if (tv<-576 || tv!=apex_tv) return 1000000.0*pow(2.0, -tv/96.0);
	else return _apex2us(apex_tv);
#else
	return 0;
#endif
}

void PostLogicalEventForNotPowerType(unsigned id, unsigned x) {
	_PostLogicalEventForNotPowerType(id,x);
}

void PostLogicalEventToUI(unsigned id, unsigned x) {
	_PostLogicalEventToUI(id,x);
}

void SetLogicalEventActive(unsigned id, unsigned state) {
	_SetLogicalEventActive(id, state);
}

void SetScriptMode(unsigned mode) {
	_SetScriptMode(mode);
}

// TODO this belongs lib.c, but not all cameras include it
// same as bitmap width for most cameras, override in platform/sub/lib.c as needed
int __attribute__((weak)) vid_get_viewport_width() {
	return vid_get_bitmap_screen_width();
}

void __attribute__((weak)) vid_turn_off_updates()
{
}

void __attribute__((weak)) vid_turn_on_updates()
{
}

// use _GetFocusLensSubjectDistance for this on dryos, vx functions are basically equivlent
// not used in CHDK currently for either OS
#ifdef CAM_DRYOS
long __attribute__((weak)) _GetCurrentTargetDistance()
{
	return _GetFocusLensSubjectDistance();
}
#endif

