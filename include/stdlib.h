#include "camera.h"

#ifndef STDLIB_H
#define STDLIB_H

#define NULL		((void*)0)

#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2


#if !CAM_DRYOS

#define O_TRUNC         0x400
#define O_CREAT         0x200

struct	stat
    {
    unsigned long	st_dev;		/* device ID number */
    unsigned long	st_ino;		/* file serial number */
    unsigned short	st_mode;	/* file mode (see below) */
    short		st_nlink;	/* number of links to file */
    short		st_uid;		/* user ID of file's owner */
    short		st_gid;		/* group ID of file's group */
    unsigned long	st_rdev;	/* device ID, only if special file */
    unsigned long	st_size;	/* size of file, in bytes */
    unsigned long	st_atime;	/* time of last access */
    unsigned long	st_mtime;	/* time of last modification */
    unsigned long	st_ctime;	/* time of last change of file status */
    long		st_blksize;
    long		st_blocks;
    unsigned char	st_attrib;	/* file attribute byte (dosFs only) */
    int			reserved1;	/* reserved for future use */
    int			reserved2;	/* reserved for future use */
    int			reserved3;	/* reserved for future use */
    int			reserved4;	/* reserved for future use */
    int			reserved5;	/* reserved for future use */
    int			reserved6;	/* reserved for future use */
};

#else

#define O_TRUNC         0x200
#define O_CREAT         0x100

struct	stat
    {
    unsigned long	st_dev;		//?
    unsigned long	st_ino;		//?	
    unsigned short	st_mode;	//?	
    short		st_nlink;	//?	
    short		st_uid;		//?	
    short		st_gid;		//?	
    unsigned long	st_atime;	//?	
    unsigned long	st_mtime;	//?	
    unsigned long	st_ctime;	//?	
    unsigned long	st_size;	
    long		st_blksize;	//?
    long		st_blocks;	//?
    unsigned char	st_attrib;
    int			reserved1;	//	
    int			reserved2;	//
    int			reserved3;	//
    int			reserved4;	//
    int			reserved5;	//
    int			reserved6;	//
};

#endif

extern int rand(void);
extern void* srand(unsigned int seed);

extern void qsort (void *__base, int __nelem, int __size, int (*__cmp)(const void *__e1, const void *__e2));

extern int isdigit(int c);
extern int isspace(int c);
extern int isalpha(int c);
extern int isupper(int c);

extern long sprintf(char *s, const char *st, ...);

extern long strlen(const char *s);
extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, long n);
extern char *strchr(const char *s, int c);
extern char *strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, long n);
extern char *strcat(char *dest, const char *app);
extern char *strrchr(const char *s, int c);
extern char *strpbrk(const char *s, const char *accept);

extern long strtol(const char *nptr, char **endptr, int base);
#define atoi(n) strtol((n),NULL,0)

extern void *malloc(long size);
extern void free(void *p);
extern void *umalloc(long size);
extern void ufree(void *p);

extern void *memcpy(void *dest, const void *src, long n);
extern void *memset(void *s, int c, int n);
extern int memcmp(const void *s1, const void *s2, long n);


extern void SleepTask(long msec);
extern long taskLock();
extern long taskUnlock();

extern long Fopen_Fut(const char *filename, const char *mode);
extern long Fclose_Fut(long file);
extern long Fread_Fut(void *buf, long elsize, long count, long f);
extern long Fwrite_Fut(const void *buf, long elsize, long count, long f);
extern long Fseek_Fut(long file, long offset, long whence);
// TODO can we just use these all the time ?
extern long RenameFile_Fut(const char *oldname, const char *newname);
extern long MakeDirectory_Fut(const char *name);
extern long DeleteFile_Fut(const char *name);
extern long Feof_Fut(long file);
extern long Fflush_Fut(long file);
extern char *Fgets_Fut(char *buf, int n, long f);

extern int creat (const char *name, int flags);
extern int open (const char *name, int flags, int mode );
extern int close (int fd);
extern int write (int fd, const void *buffer, long nbytes);
extern int read (int fd, void *buffer, long nbytes);
extern int lseek (int fd, long offset, int whence);
extern long mkdir(const char *dirname);

#ifdef STDIO_COMPAT_FILE
// don't use this directly unless you absolutely need to
// don't EVER try to create one yourself, as this isn't the full structure.
typedef struct FILE_S {
    int fd;         // used by Read/Write
    unsigned len;   // +4 verfied in Fseek_FileStream
    int unk0;       // +8
    unsigned pos;   // +0xC verified in Fseek_FileStream
    // unk1;        // +0x10 
    // unk2;        // +0x14
    // io_buf;      // +0x18 32k uncached allocated in Fopen_FileStream
    // unk3;        // +0x20 related to StartFileAccess_Sem
    // ...name
} FILE;
static inline FILE *fopen(const char *filename, const char *mode) {
    return (FILE *)Fopen_Fut(filename,mode);
}
static inline long fclose(FILE *f) {
    return Fclose_Fut((long)f);
}
static inline long fread(void *buf, long elsize, long count, FILE *f) {
    return Fread_Fut(buf,elsize,count,(long)f);
}
static inline long fwrite(const void *buf, long elsize, long count, FILE *f) {
    return Fwrite_Fut(buf,elsize,count,(long)f);
}
static inline long fseek(FILE *file, long offset, long whence) {
    return Fseek_Fut((long)file,offset,whence);
}
static inline long fflush(FILE *file) {
    return Fflush_Fut((long)file);
}
static inline long feof(FILE *file) {
    return Feof_Fut((long)file);
}
static inline long ftell(FILE *file) {
    if(!file) return -1;
    return file->pos;
}
static inline char *fgets(char *buf, int n, FILE *f) {
    return Fgets_Fut(buf,n,(int)f);
}
#else
#define fopen(a,b) Fopen_Fut(a,b)
#define fclose(a) Fclose_Fut(a)
#define fread(a,b,c,d) Fread_Fut(a,b,c,d)
#define fwrite(a,b,c,d) Fwrite_Fut(a,b,c,d)
#define fseek(a,b,c) Fseek_Fut(a,b,c)
#define fflush(a) Fflush_Fut(a)
#define feof(a) Feof_Fut(a)
typedef long FILE;
#endif //STDIO_COMPAT
#define fdelete(a) DeleteFile_Fut(a)
/**
 * No STUBS!
 * You can't use these two directly from THUMB code (core), only from platform.
 */
extern int fprintf(FILE *fd, char*buf, ...);
extern int printf(char *buf, ...);

extern void msleep(long msec);
extern long task_lock();
extern long task_unlock();
extern const char *task_name(int id);
int task_id_list_get(int *idlist,int size);
extern const char *strerror(int num);
// on vxworks we could find the actual errno, but this is easier to automate sig
// doesn't exist on dryos, but we stub it
extern int errnoOfTaskGet(int tid);
#define errno (errnoOfTaskGet(0))

#define DOS_ATTR_RDONLY         0x01            /* read-only file */
#define DOS_ATTR_HIDDEN         0x02            /* hidden file */
#define DOS_ATTR_SYSTEM         0x04            /* system file */
#define DOS_ATTR_VOL_LABEL      0x08            /* volume label (not a file) */
#define DOS_ATTR_DIRECTORY      0x10            /* entry is a sub-directory */
#define DOS_ATTR_ARCHIVE        0x20            /* file subject to archiving */

#if !CAM_DRYOS
struct dirent {
    char                name[100];
};
#else
struct dirent {
    char                name[13];
    unsigned long	unk1;
    unsigned char 	attrib;
    unsigned long 	size;
    unsigned long	time1;
    unsigned long	time2;
    unsigned long	time3;
};
#endif

typedef struct {
    unsigned int        fd;
    unsigned int        loc;
    struct dirent       dir;
} DIR;



extern DIR*           opendir (const char* name);
extern struct dirent* readdir (DIR*);
extern int            closedir (DIR*);
extern void           rewinddir (DIR*);
extern int            stat (char *name, struct stat *pStat);


struct tm
	{
	int tm_sec;	/* seconds after the minute	- [0, 59] */
	int tm_min;	/* minutes after the hour	- [0, 59] */
	int tm_hour;	/* hours after midnight		- [0, 23] */
	int tm_mday;	/* day of the month		- [1, 31] */
	int tm_mon;	/* months since January		- [0, 11] */
	int tm_year;	/* years since 1900	*/
	int tm_wday;	/* days since Sunday		- [0, 6] */
	int tm_yday;	/* days since January 1		- [0, 365] */
	int tm_isdst;	/* Daylight Saving Time flag */
	};

typedef unsigned long time_t;

extern struct tm * localtime(const unsigned long *_tod);

extern int rename(const char *oldname, const char *newname);
extern int chdir(char *pathname);
extern int remove(const char *name);
#ifdef FS_USE_FUT
#define mkdir(x) MakeDirectory_Fut(x)
#define rename(x,y) RenameFile_Fut(x,y)
#define remove(x) DeleteFile_Fut(x)
#endif
struct utimbuf {
    unsigned long actime;       /* set the access time */
    unsigned long modtime;      /* set the modification time */
};

extern int utime(char *file, struct utimbuf *newTimes);
extern unsigned long time(unsigned long *timer);
extern long strftime(char *s, unsigned long maxsize, const char *format, const struct tm *timp);
extern time_t mktime(struct tm *timp);

static inline int abs( int v ) {
  return v<0 ? -v : v;
}

#endif
