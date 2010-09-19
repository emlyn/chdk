topdir=../../

include $(topdir)makefile.inc

OBJS = reversebytes.o callfunc.o reboot.o

all: libarmutil.a

libarmutil.a: $(OBJS)

clean:
	rm -f $(OBJS) libarmutil.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
