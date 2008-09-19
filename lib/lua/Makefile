topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB) -DSTDIO_COMPAT_FILE -DFS_USE_FUT

LUA_OPTLIB_OBJS=

ifdef CHDK_LUA_IOLIB
CFLAGS+=-DCHDK_LUA_IOLIB
LUA_OPTLIB_OBJS+=liolib.o
endif

ifdef CHDK_LUA_OSLIB
CFLAGS+=-DCHDK_LUA_OSLIB
LUA_OPTLIB_OBJS+=loslib.o
endif

ifdef CHDK_LUA_STRLIB
CFLAGS+=-DCHDK_LUA_STRLIB
LUA_OPTLIB_OBJS+=lstrlib.o
endif

OBJS = setjmp.o \
       \
       lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o \
       lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o \
       lundump.o lvm.o lzio.o \
       \
       lauxlib.o lbaselib.o ldblib.o ltablib.o lmathlib.o \
	   $(LUA_OPTLIB_OBJS) loadlib.o linit.o

all: liblua.a

liblua.a: $(OBJS)

check:

clean:
	rm -f $(OBJS) liblua.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
