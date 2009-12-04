topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = camera_functions.o tokenizer.o ubasic.o

all: libubasic.a

libubasic.a: $(OBJS)

UBASIC_TEST_CFLAGS=-g -Wall -DUBASIC_TEST -DCAMERA_$(PLATFORM) -DPLATFORMID=$(PLATFORMID)
ifdef UBASIC_DEBUG
	UBASIC_TEST_CFLAGS+=-DDEBUG=1
endif

check:
	gcc $(UBASIC_TEST_CFLAGS) -o ubasic_test$(EXE) $(OBJS:.o=.c) run-ubasic.c

clean:
	rm -f $(OBJS) libubasic.a ubasic_test$(EXE)

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
