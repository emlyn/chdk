#include "lolevel.h"

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
}

long lens_get_focus_pos()
{
    return _GetFocusLensSubjectDistance();
}

void lens_set_focus_pos(long newpos)
{
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

long sprintf(char *s, const char *st, ...)
{
    long res;
    __builtin_va_list va;
    __builtin_va_start(va, st);
    res = _vsprintf(s, st, va);
    __builtin_va_end(va);
    return res;
}
