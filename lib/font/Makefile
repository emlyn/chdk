topdir=../../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = font_8x16.o rbf_font.o

all: libfont.a

libfont.a: $(OBJS)

font_8x16.o: font_8x16.c codepages.h font_8x16_uni.h

clean:
	rm -f $(OBJS) libfont.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
