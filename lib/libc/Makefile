topdir=../../

include $(topdir)makefile.inc

OBJS = issmth.o strncmp.o strtol.o strchr.o

all: libc.a

libc.a: $(OBJS)

clean:
	rm -f $(OBJS) libc.a
