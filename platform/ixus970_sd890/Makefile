curdir=./
topdir=../../

include $(topdir)makefile.inc

CFLAGS+=-DLOW_LEVEL

SUBDIRS=sub

all: all-recursive libplatform.a

OBJS=main.o lib.o wrappers.o kbd.o shooting.o
# stubs_init.o

kbd.o: kbd.c
lib.o: lib.c
main.o: main.c
shooting.o: shooting.c
wrappers.o: wrappers.c ../generic/wrappers.c

libplatform.a: $(OBJS)

clean: clean-recursive
	rm -f $(OBJS) libplatform.a

