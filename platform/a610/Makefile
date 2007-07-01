curdir=./
topdir=../../

include $(topdir)makefile.inc

CFLAGS+=-DLOW_LEVEL

SUBDIRS=sub

all: all-recursive libplatform.a

OBJS=main.o lib.o wrappers.o kbd.o shooting.o
# stubs_init.o

libplatform.a: $(OBJS)

clean: clean-recursive
	rm -f $(OBJS) libplatform.a

distclean: distclean-recursive
	rm -f $(OBJS:.o=.d) $(OBJS) libplatform.a

include $(topdir)bottom.inc
