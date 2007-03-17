topdir=../../../../

include $(topdir)makefile.inc

all: libplatformsub.a

OBJS=boot.o stubs_min.o stubs_auto.o stubs_entry.o lib.o stubs_entry_2.o

libplatformsub.a: $(OBJS)

clean:
	rm -f *.o *.a

stubs_auto.S: boot.c
# UNIX shell magick )
	cat $< | \
	    grep 'BL\?[[:space:]]*sub_[0-9A-Fa-f]' | \
	    sed 's/.*sub_\([0-9A-Fa-f]*\).*/\1/' | \
	    sort | uniq | \
	    awk 'BEGIN {print "/* THIS FILE IS GENERATED */\n#include \"stubs_asm.h\"\n"} \
		{printf("STUB(%s)\n",$$1)}' > stubs_auto.S

stubs_entry.S:
	$(topdir)tools/finsig $(TARGET_PRIMARY) $(ROMBASEADDR) > stubs_entry.S
