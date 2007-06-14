topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = camera_functions.o tokenizer.o ubasic.o

all: libubasic.a

libubasic.a: $(OBJS)

check:
	gcc -Wall -DTEST -o test$(EXE) *.c

clean:
	rm -f $(OBJS) libubasic.a test$(EXE)

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
