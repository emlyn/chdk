curdir=./
topdir=../../

include $(topdir)makefile.inc
SUBDIRS=resetcode

LDLIBS=
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,--no-define-common,-EL,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,$(MEMBASEADDR)

CPPFLAGS+=-I.

CORE_FILE=$(topdir)core/main.bin
RESET_FILE=$(curdir)resetcode/main.bin

CPPFLAGS+=-DCORE_FILE=\"$(CORE_FILE)\"
CPPFLAGS+=-DRESET_FILE=\"$(RESET_FILE)\"

all: all-recursive main.bin

OBJS=entry.o main.o blobs.o

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
	rm -f reboot_core.h copy_and_reset.h

blobs.o: $(RESET_FILE) $(CORE_FILE)

include $(topdir)bottom.inc
