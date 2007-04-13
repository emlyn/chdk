#ifndef STDLIB_H
#define STDLIB_H

#define NULL		((void*)0)

#define SEEK_CUR        1
#define SEEK_END        2

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2
#define O_TRUNC         0x400
#define O_CREAT         0x200

extern long sprintf(char *s, const char *st, ...);
extern long strtol(const char *nptr, char **endptr, int base);
#define atoi(n) strtol((n),NULL,0)

extern int isdigit(int c);
extern int isspace(int c);
extern int isalpha(int c);
extern int isupper(int c);

extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, long n);
extern char *strchr(const char *s, int c);
extern long strlen(const char *s);

extern void *memcpy(void *dest, const void *src, long n);

extern int creat (const char *name, int flags);
extern int open (const char *name, int flags, int mode );
extern int close (int fd);
extern int write (int fd, void *buffer, long nbytes);
extern int read (int fd, void *buffer, long nbytes);
extern int lseek (int fd, long offset, int whence);
extern long mkdir(const char *dirname);

extern void msleep(long msec);
extern long task_lock();
extern long task_unlock();

#endif
