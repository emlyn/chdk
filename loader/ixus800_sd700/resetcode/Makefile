topdir=../../../

include $(topdir)makefile.inc

# warning: library order matters!
LDLIBS=
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,--no-define-common,-EL,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,$(RESTARTSTART)

all: main.bin

OBJS=entry.o main.o

main.bin: main.elf
	@echo $< \-\> $@
	$(OBJDUMP) -z -d main.elf > main.dump
	$(OBJCOPY) -O binary main.elf main.bin

main.elf: $(OBJS)
	@echo \-\> $@
	$(CC) $(CFLAGS) -o $@ $^   $(LDLIBS) $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && exit 1 || exit 0

clean: clean-recursive
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms

distclean: distclean-recursive
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms

include $(topdir)bottom.inc
