topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = setjmp.o \
       \
       lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o \
       lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o \
       lundump.o lvm.o lzio.o \
       \
       lauxlib.o lbaselib.o ldblib.o ltablib.o lmathlib.o loadlib.o linit.o

all: liblua.a

liblua.a: $(OBJS)

check:

clean:
	rm -f $(OBJS) liblua.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
