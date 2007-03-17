curdir=./
topdir=../../

include $(topdir)makefile.inc

SUBDIRS=sub

all: all-recursive libplatform.a

OBJS=main.o lib.o
# stubs_init.o

libplatform.a: $(OBJS)

clean: clean-recursive
	rm -f *.o *.a

