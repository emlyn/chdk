topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = lang.o

all: liblang.a

liblang.a: $(OBJS)

clean:
	rm -f $(OBJS) liblang.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc

