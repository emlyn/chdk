topdir=../../

include $(topdir)makefile.inc

all: libmath.a

libmath.a: ef_log.o ef_sqrt.o

ef_log.o: ef_log.c fdlibm.h

clean:
	rm -f *.o *.a
