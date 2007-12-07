#include "stdlib.h"
#include "lang.h"

//-------------------------------------------------------------------

static char **strings = NULL;
static int count = 0;

//-------------------------------------------------------------------
void lang_init(int num) {
    int i;

    if (strings) {
       for (i=0; i<count; ++i)
           if (strings[i]) ufree(strings[i]);
       ufree(strings);
       count = 0;
    }

    ++num;
    strings = umalloc(num*sizeof(char*));
    if (strings) {
        memset(strings, 0, num*sizeof(char*));
        count = num;
    }

}

//-------------------------------------------------------------------
static void lang_add_string(int num, const char *str) {
    int f=0;
    char *p;

    if (strings && num<count) {
       if (strings[num]) ufree(strings[num]);
       p = strings[num] = umalloc(strlen(str)+1);
       if (p) {
           for (; *str; ++str) {
                if (f) {
                    if (*str == '"' || *str == '\\') *(p-1)=*str;
                    else if (*str == 'n') *(p-1)='\n';
                    else *p++=*str;
                    f = 0;
                } else {
                    *p++=*str;
                    if (*str == '\\') {
                        f = 1;
                    }
                }
           }
           *p=0;
       }
    }
}

//-------------------------------------------------------------------
void lang_load_from_mem(char *buf) {
    char *p, *s, *e;
    int i;
    
    e = buf-1;
    while(e) {
        p = e+1;
        while (*p && (*p=='\r' || *p=='\n')) ++p;
        i = strtol(p, &e, 0);
        if (e!=p) {
            p = e;
            e = strpbrk(p, "\r\n");
            if (e) *e=0;
            while (*p && *p!='\"') ++p;
            if (*p) ++p;
            s = p;
            while (*p && (*p!='\"' || *(p-1)=='\\')) ++p;
            *p=0;
            lang_add_string(i, s);
        } else { //skip invalid line
            e = strpbrk(p, "\r\n");
            if (e) *e=0;
        }
    }
}

//-------------------------------------------------------------------
void lang_load_from_file(const char *filename) {
    int f, size;
    static struct stat st;
    char *buf;

    f = open(filename, O_RDONLY, 0777);
    if (f>=0) {
        size = (stat((char*)filename, &st)==0)?st.st_size:0;
        if (size) {
            buf = umalloc(size+1);
            if (buf) {
                size = read(f, buf, size);
                buf[size]=0;
                lang_load_from_mem(buf);
                ufree(buf);
            }
        }
        close(f);
    }
}

//-------------------------------------------------------------------
char* lang_str(int str) {
    if (str && str<0x1000) {
        return (strings && str<count && strings[str])?strings[str]:"";
    } else { // not ID, just char*
        return (char*)str;
    }
}
