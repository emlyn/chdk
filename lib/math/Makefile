topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = ef_log.o ef_sqrt.o

all: libmath.a

libmath.a: $(OBJS)

ef_log.o: ef_log.c fdlibm.h

clean:
	rm -f $(OBJS) libmath.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
