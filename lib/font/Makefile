topdir=../../

include $(topdir)makefile.inc

OBJS = font_8x16.o

all: libfont.a

libfont.a: $(OBJS)

font_8x16.o: font_8x16.c

clean:
	rm -f $(OBJS) libfont.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
