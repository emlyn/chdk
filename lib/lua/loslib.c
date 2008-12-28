/*
** $Id: loslib.c,v 1.19.1.3 2008/01/18 16:38:18 roberto Exp $
** Standard Operating System library
** See Copyright Notice in lua.h
*/

#if 0
#include <errno.h>
#include <locale.h>
#endif
#include <stdlib.h>
#include <string.h>
#ifdef HOST_LUA
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <utime.h>
#endif

#define loslib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


static int os_pushresult (lua_State *L, int i, const char *filename) {
  int en = errno;  /* calls to Lua API may change this value */
  if (i) {
    lua_pushboolean(L, 1);
    return 1;
  }
  else {
    lua_pushnil(L);
    lua_pushfstring(L, "%s: %s", filename, strerror(en));
    lua_pushinteger(L, en);
    return 3;
  }
}


#if 0
static int os_execute (lua_State *L) {
  lua_pushinteger(L, system(luaL_optstring(L, 1, NULL)));
  return 1;
}
#endif


static int os_remove (lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  return os_pushresult(L, remove(filename) == 0, filename);
}


static int os_rename (lua_State *L) {
  const char *fromname = luaL_checkstring(L, 1);
  const char *toname = luaL_checkstring(L, 2);
  return os_pushresult(L, rename(fromname, toname) == 0, fromname);
}


// TODO
#if 0
static int os_tmpname (lua_State *L) {
  char buff[LUA_TMPNAMBUFSIZE];
  int err;
  lua_tmpnam(buff, err);
  if (err)
    return luaL_error(L, "unable to generate a unique filename");
  lua_pushstring(L, buff);
  return 1;
}
#endif

#if 0
static int os_getenv (lua_State *L) {
  lua_pushstring(L, getenv(luaL_checkstring(L, 1)));  /* if NULL push nil */
  return 1;
}
#endif

#if 0
static int os_clock (lua_State *L) {
  lua_pushnumber(L, ((lua_Number)clock())/(lua_Number)CLOCKS_PER_SEC);
  return 1;
}
#endif


/*
** {======================================================
** Time/Date operations
** { year=%Y, month=%m, day=%d, hour=%H, min=%M, sec=%S,
**   wday=%w+1, yday=%j, isdst=? }
** =======================================================
*/

static void setfield (lua_State *L, const char *key, int value) {
  lua_pushinteger(L, value);
  lua_setfield(L, -2, key);
}

static void setboolfield (lua_State *L, const char *key, int value) {
  if (value < 0)  /* undefined? */
    return;  /* does not set field */
  lua_pushboolean(L, value);
  lua_setfield(L, -2, key);
}

static int getboolfield (lua_State *L, const char *key) {
  int res;
  lua_getfield(L, -1, key);
  res = lua_isnil(L, -1) ? -1 : lua_toboolean(L, -1);
  lua_pop(L, 1);
  return res;
}


static int getfield (lua_State *L, const char *key, int d) {
  int res;
  lua_getfield(L, -1, key);
  if (lua_isnumber(L, -1))
    res = (int)lua_tointeger(L, -1);
  else {
    if (d < 0)
      return luaL_error(L, "field " LUA_QS " missing in date table", key);
    res = d;
  }
  lua_pop(L, 1);
  return res;
}


static int os_date (lua_State *L) {
  const char *s = luaL_optstring(L, 1, "%c");
  time_t t = luaL_opt(L, (time_t)luaL_checknumber, 2, time(NULL));
  struct tm *stm;
  if (*s == '!') {  /* UTC? */
  #if 0
  // reyalp - we have no idea about timezones, so just eat the !
  // and use local time
  // TODO some cams may be timezone/dst aware ?
    stm = gmtime(&t);
  #endif
    stm = localtime(&t);
    s++;  /* skip `!' */
  }
  else
    stm = localtime(&t);
  if (stm == NULL)  /* invalid date? */
    lua_pushnil(L);
  else if (strcmp(s, "*t") == 0) {
    lua_createtable(L, 0, 9);  /* 9 = number of fields */
    setfield(L, "sec", stm->tm_sec);
    setfield(L, "min", stm->tm_min);
    setfield(L, "hour", stm->tm_hour);
    setfield(L, "day", stm->tm_mday);
    setfield(L, "month", stm->tm_mon+1);
    setfield(L, "year", stm->tm_year+1900);
    setfield(L, "wday", stm->tm_wday+1);
    setfield(L, "yday", stm->tm_yday+1);
    setboolfield(L, "isdst", stm->tm_isdst);
  }
  else {
    char cc[3];
    luaL_Buffer b;
    cc[0] = '%'; cc[2] = '\0';
    luaL_buffinit(L, &b);
    for (; *s; s++) {
      if (*s != '%' || *(s + 1) == '\0')  /* no conversion specifier? */
        luaL_addchar(&b, *s);
      else {
        size_t reslen;
        char buff[200];  /* should be big enough for any conversion result */
        cc[1] = *(++s);
        reslen = strftime(buff, sizeof(buff), cc, stm);
        luaL_addlstring(&b, buff, reslen);
      }
    }
    luaL_pushresult(&b);
  }
  return 1;
}


static int os_time (lua_State *L) {
  time_t t;
  if (lua_isnoneornil(L, 1))  /* called without args? */
    t = time(NULL);  /* get current time */
  else {
    struct tm ts;
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_settop(L, 1);  /* make sure table is at the top */
    ts.tm_sec = getfield(L, "sec", 0);
    ts.tm_min = getfield(L, "min", 0);
    ts.tm_hour = getfield(L, "hour", 12);
    ts.tm_mday = getfield(L, "day", -1);
    ts.tm_mon = getfield(L, "month", -1) - 1;
    ts.tm_year = getfield(L, "year", -1) - 1900;
    ts.tm_isdst = getboolfield(L, "isdst");
    t = mktime(&ts);
  }
  if (t == (time_t)(-1))
    lua_pushnil(L);
  else
    lua_pushnumber(L, (lua_Number)t);
  return 1;
}


#if 0
static int os_difftime (lua_State *L) {
  lua_pushnumber(L, difftime((time_t)(luaL_checknumber(L, 1)),
                             (time_t)(luaL_optnumber(L, 2, 0))));
  return 1;
}
#endif
static int os_difftime (lua_State *L) {
  lua_pushnumber(L, (time_t)(luaL_checknumber(L, 1) - (time_t)(luaL_optnumber(L, 2, 0))));
  return 1;
}

/* }====================================================== */


#if 0
static int os_setlocale (lua_State *L) {
  static const int cat[] = {LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY,
                      LC_NUMERIC, LC_TIME};
  static const char *const catnames[] = {"all", "collate", "ctype", "monetary",
     "numeric", "time", NULL};
  const char *l = luaL_optstring(L, 1, NULL);
  int op = luaL_checkoption(L, 2, "all", catnames);
  lua_pushstring(L, setlocale(cat[op], l));
  return 1;
}
#endif

#if 0
static int os_exit (lua_State *L) {
  exit(luaL_optint(L, 1, EXIT_SUCCESS));
}
#endif

// reyalp added
static int os_mkdir (lua_State *L) {
  const char *dirname = luaL_checkstring(L, 1);
#if defined(HOST_LUA) && !defined(_WIN32)
  return os_pushresult(L, mkdir(dirname,0777) == 0, dirname);
#else
  return os_pushresult(L, mkdir(dirname) == 0, dirname);
#endif
}

/*
  syntax
    t=os.listdir("name",[showall])
  returns array of filenames, or nil, strerror, errno
  if showall is true, t includes ".", ".." and deleted entries
  NOTE except for the root directory, names ending in / will not work
*/
static int os_listdir (lua_State *L) {
  DIR *dir;
  struct dirent *de;
  const char *dirname = luaL_checkstring(L, 1);
  int all=lua_toboolean(L, 2);
  int i=1;
  dir = opendir(dirname);
  if(!dir) 
    return os_pushresult(L, 0 , dirname);
  lua_newtable(L); 
  while((de = readdir(dir))) {
	if(!all && (/*de->d_name[0] == 0xE5 ||*/ (strcmp(de->d_name,".")==0) || (strcmp(de->d_name,"..")==0)))
      continue;
  	lua_pushinteger(L, i);
  	lua_pushstring(L, de->d_name);
	lua_settable(L,-3);
	++i;
  }
  closedir(dir);
  return 1;
}

// t = stat("name")
// nil,strerror,errno on fail
static int os_stat (lua_State *L) {
  struct stat st;
  const char *name = luaL_checkstring(L, 1);
  int result = stat(name,&st);
  if (result==0) {
    lua_createtable(L, 0, 11);  /* = number of fields */
    // don't expose the fields that aren't useful
	// but leave them commented out for reference
    setfield(L,"dev",st.st_dev);		/* device ID number */
//    setfield(L,"ino",st.st_ino);		/* no inodes in fat, always -1 */
    setfield(L,"mode",st.st_mode);	/* file mode (see below) */
//    setfield(L,"nlink",st.st_nlink);	/* dryos 0, vxworks 1 */
//    setfield(L,"uid",st.st_uid);		/* no users or groups on fat */
//    setfield(L,"gid",st.st_gid);		/* " */
#if !CAM_DRYOS
// doesn't appear useful, I wasn't able to stat any special files
//    setfield(L,"rdev",st.st_rdev);	/* device ID, only if special file */
#endif
    setfield(L,"size",st.st_size);	/* size of file, in bytes */
    setfield(L,"atime",st.st_atime);	/* time of last access */
    setfield(L,"mtime",st.st_mtime);	/* time of last modification */
    setfield(L,"ctime",st.st_ctime);	/* time of last change of file status */
#ifdef HOST_LUA
// fill in some sane values if we aren't running on the camera
// from chdk stdlib
#define DOS_ATTR_DIRECTORY      0x10            /* entry is a sub-directory */
    setfield(L,"blksize",512); 
    setfield(L,"blocks",(st.st_size/512) + (st.st_size%512)?1:0); 
    if ( S_ISDIR(st.st_mode) ) {
      setfield(L,"attrib",DOS_ATTR_DIRECTORY);
      setboolfield(L,"is_dir",1);
      setboolfield(L,"is_file",0);
    }
    else {
      setboolfield(L,"is_dir",0);
      setfield(L,"attrib",0);
      if S_ISREG(st.st_mode) {
        setboolfield(L,"is_file",1);
      }
    }
#else
    setfield(L,"blksize",st.st_blksize); /* This is NOT the dos sector size. Appears to be 512 on all I've tested! */
    setfield(L,"blocks",st.st_blocks);   /* number of blocks required to store file. May not be the same as size on disk, per above*/
    setfield(L,"attrib",st.st_attrib);	/* file attribute byte (dosFs only) */
	// for convenience
	// note volume labels are neither file nor directory
	setboolfield(L,"is_dir",st.st_attrib & DOS_ATTR_DIRECTORY);
	setboolfield(L,"is_file",!(st.st_attrib & (DOS_ATTR_DIRECTORY | DOS_ATTR_VOL_LABEL)));
#endif
#if 0
    setfield(L,"reserved1",st.reserved1);
    setfield(L,"reserved2",st.reserved2);
    setfield(L,"reserved3",st.reserved3);
    setfield(L,"reserved4",st.reserved4);
    setfield(L,"reserved5",st.reserved5);
    setfield(L,"reserved6",st.reserved6);
#endif
    return 1;
  }
  else {
    int en = errno;
    lua_pushnil(L);
    lua_pushfstring(L, "%s: %s", name, strerror(en));
    lua_pushinteger(L, en);
    return 3;
  }
}

// utime(name,[modtime,[actime]])
// true | nil,strerror, errno
// current time used for missing or nil args
static int os_utime (lua_State *L) {
  const char *name = luaL_checkstring(L, 1);
  struct utimbuf t;
  t.modtime = luaL_optnumber(L, 2, time(NULL));
  t.actime = luaL_optnumber(L, 3, time(NULL));
  return os_pushresult(L, utime(name,&t) == 0, name);
}

static const luaL_Reg syslib[] = {
#if 0
  {"clock",     os_clock},
#endif
  {"date",      os_date},
  {"difftime",  os_difftime},
#if 0
  {"execute",   os_execute},
  {"exit",      os_exit},
  {"getenv",    os_getenv},
#endif
  {"mkdir",     os_mkdir}, // reyalp - NOT STANDARD
  {"listdir",   os_listdir}, // reyalp - NOT STANDARD
  {"stat",      os_stat}, // reyalp - NOT STANDARD
  {"utime",     os_utime}, // reyalp - NOT STANDARD
  {"remove",    os_remove},
  {"rename",    os_rename},
#if 0
  {"setlocale", os_setlocale},
#endif
  {"time",      os_time},
#if 0
  {"tmpname",   os_tmpname},
#endif
  {NULL, NULL}
};

/* }====================================================== */



LUALIB_API int luaopen_os (lua_State *L) {
  luaL_register(L, LUA_OSLIBNAME, syslib);
  return 1;
}

