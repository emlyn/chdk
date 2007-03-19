curdir=./
topdir=../../

include $(topdir)makefile.inc

SUBDIRS=resetcode

# warning: library order matters!
LDLIBS=
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,--no-define-common,-EL,-T,$(topdir)tools/link.RAM
LDOPTS+=-Wl,-N,-Ttext,$(MEMBASEADDR)

CPPFLAGS+=-I.

all: all-recursive main.bin

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
	rm -f reboot_core.h copy_and_reset.h

reboot_core.h: $(topdir)core/main.bin
	@echo $< \-\> $@
ifeq ($(OSTYPE),Windows)
	$(topdir)tools/hexdmplt  $< $@
else
	hexdump -v -e '1/4 "0x%08x, " "\n" ' $< > $@
endif

copy_and_reset.h: $(curdir)resetcode/main.bin
	@echo $< \-\> $@
ifeq ($(OSTYPE),Windows)
	$(topdir)tools/hexdmplt  $< $@
else
	hexdump -v -e '1/4 "0x%08x, " "\n" ' $< > $@
endif

main.c: reboot_core.h copy_and_reset.h
main.o: main.c reboot_core.h copy_and_reset.h
