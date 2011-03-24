#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
	//return _GetFocusLensSubjectDistance();    // returns plaintext, calls GetCurrentTargetDistance to get value
	return _GetCurrentTargetDistance();
}

long lens_get_focus_pos_from_lens()
{
	return _GetCurrentTargetDistance();
	//return _GetFocusLensSubjectDistanceFromLens();
}

long lens_get_target_distance()
{
	return _GetCurrentTargetDistance();
}

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
// these tiny inlines provide type safety, and should optimize away

typedef struct
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
}stat_type;

#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2

/*
int _stat(char *name, void *pStat) {
	int fd;
	int size;
	stat_type *tmp=pStat;
    fd=open(name, O_RDONLY, 0777);
    if(fd>=0)
    	{
			size=lseek(fd,0,SEEK_END);
			lseek(fd,0,SEEK_SET);
			tmp->st_size=size;
			close(fd);

			return 0;
		}
	else
	return -1;
}
*/

/*
int _rename(const char *oldname, const char *newname)
{
	//FILE * fd_old;
	//FILE *fd_new;
	int fd_old,fd_new;

	char * buffer;
	int size_read;

	fd_old = Fopen_Fut(oldname, "r+b");
	if(!fd_old)return -1;

	fd_new = Fopen_Fut(newname, "w+b");
	buffer=malloc(10000);

	while(1)
		{
			size_read=Fread_Fut(buffer,1,10000,fd_old);
			Fwrite_Fut(buffer,size_read,1,fd_new);
			if(size_read!=10000)break;
		}

	Fclose_Fut(fd_new);
	Fclose_Fut(fd_old);
	free(buffer);
	remove(oldname);
	return 1;
}

long _RenameFile_Fut(const char *oldname, const char *newname)
{
	return _rename(oldname, newname);
}
*/
/*
char *_strncpy(char *dest, const char *src, long n) {

	int i;
	char c=0;//to get rid of compiler warning
	int finished=0;
	for(i=0;i<n;i++)
		{
			if(!finished)
				{
					c=src[i];
					if(!c)
					finished=1;
				}

			dest[i]=c;
		}
	return dest;
}
*/
/*
char *_strrchr(const char *s, int c) {

	char *last_occurance=0;
	while(1)
		{
			if(*s==c)last_occurance=(char*)s;
			else
			if(!*s)
				{
					return last_occurance;
				}
			s++;
		}

}
*/
/*
char * _strcat(char *dest, const char *src)
{
    strcpy(dest + strlen(dest), src);
    return dest;
}
*/

