topdir=../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

# warning: library order matters!
LDLIBS=-lc -lgcc
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,$(MEMISOSTART)

all: main.bin

OBJS=entry.o main.o gui.o kbd.o conf.o histogram.o

main.bin: main.elf
	@echo $< \-\> $@
	$(OBJDUMP) -z -d main.elf > main.dump
	$(OBJCOPY) -O binary main.elf main.bin

main.elf: $(OBJS) \
          $(topdir)lib/font/libfont.a $(topdir)lib/math/libmath.a $(topdir)lib/ubasic/libubasic.a \
          $(topdir)platform/$(PLATFORM)/libplatform.a \
          $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/libplatformsub.a
	@echo \-\> $@
	$(CC) $(CFLAGS) -o $@ --start-group $^  $(LDLIBS) --end-group $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && exit 1 || exit 0
	$(SIZE) $@

clean:
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
