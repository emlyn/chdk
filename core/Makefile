topdir=../

include $(topdir)makefile.inc

# warning: library order matters!
LDLIBS= -lfont -lplatform -lplatformsub -lubasic -lmath  -lc -lgcc
#LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,--no-define-common,-EL,-T,$(topdir)tools/link.RAM
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,-T,$(topdir)tools/link.RAM
LDOPTS+=-Wl,-N,-Ttext,$(MEMISOSTART)

all: main.bin

OBJS=entry.o main.o gui.o kbd.o conf.o histogram.o

main.bin: main.elf
	$(OBJDUMP) -z -d main.elf > main.dump
	$(OBJCOPY) -O binary main.elf main.bin

main.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^   $(LDLIBS) $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && exit 1 || exit 0

clean:
	rm -f *.o *.a main.bin main.elf main.dump core.h main.elf.syms
 