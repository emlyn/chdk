topdir=../

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

# warning: library order matters!
LDLIBS= -lgcc
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,$(MEMISOSTART)

all: main.bin

OPT_OBJS=
ifdef OPT_GAME_REVERSI
CFLAGS+=-DOPT_GAME_REVERSI
OPT_OBJS+=gui_reversi.o
endif
ifdef OPT_GAME_SOKOBAN
CFLAGS+=-DOPT_GAME_SOKOBAN
OPT_OBJS+=gui_sokoban.o
endif
ifdef OPT_GAME_CONNECT4
CFLAGS+=-DOPT_GAME_CONNECT4
OPT_OBJS+=gui_4wins.o
endif
ifdef OPT_GAME_MASTERMIND
CFLAGS+=-DOPT_GAME_MASTERMIND
OPT_OBJS+=gui_mastermind.o
endif
ifdef OPT_CURVES
CFLAGS+=-DOPT_CURVES
OPT_OBJS+=curves.o
endif
ifdef OPT_TEXTREADER
CFLAGS+=-DOPT_TEXTREADER
OPT_OBJS+=gui_read.o 
endif
ifdef OPT_CALENDAR
CFLAGS+=-DOPT_CALENDAR
OPT_OBJS+=gui_calendar.o 
endif
ifdef OPT_DEBUGGING
# global in root makefile.inc
#CFLAGS+=-DOPT_DEBUGGING
OPT_OBJS+=gui_debug.o gui_bench.o 
endif
ifdef OPT_EDGEOVERLAY
CFLAGS+=-DOPT_EDGEOVERLAY
OPT_OBJS+=edgeoverlay.o 
endif
ifdef OPT_MD_DEBUG
CFLAGS+=-DOPT_MD_DEBUG
endif 
OBJS=entry.o nothumb.o main.o gui_draw.o gui_menu.o gui_palette.o gui_mbox.o \
     gui_fselect.o gui.o kbd.o conf.o \
     histogram.o gui_batt.o gui_space.o gui_osd.o script.o raw.o \
     gui_lang.o gui_mpopup.o gui_grid.o motion_detector.o raw_merge.o \
     luascript.o shot_histogram.o dng.o $(OPT_OBJS)

gui.o: FORCE

FORCE:

nothumb.o: nothumb.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -marm -nostdinc -c -o $@ $<

main.bin: main.elf
	@echo $< \-\> $@
	$(OBJDUMP) -z -d main.elf > main.dump
	$(OBJCOPY) -O binary main.elf main.bin

main.elf: $(OBJS) $(topdir)platform/$(PLATFORM)/libplatform.a \
          $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/libplatformsub.a \
          $(topdir)lib/font/libfont.a $(topdir)lib/math/libmath.a \
          $(topdir)lib/ubasic/libubasic.a $(topdir)lib/lang/liblang.a \
          $(topdir)lib/lua/liblua.a
	@echo \-\> $@
	$(CC) $(CFLAGS) -o $@ --start-group $^  $(LDLIBS) --end-group $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && echo "error: unresolved symbols in $@ (see $@.syms)" && exit 1 || exit 0

	$(SIZE) $@ | tee $(topdir)size.txt
	@printf " %s-%s (%s, #%s): MEMISOSIZE used: 0x%s\n" \
   $(PLATFORM) $(PLATFORMSUB) $(PLATFORMOS) $(PLATFORMID) \
   `tail -c16 $(topdir)size.txt | head -c6` >> $(topdir)bin/caminfo.txt
	rm -f $(topdir)size.txt

clean:
	rm -f $(OBJS) main.bin main.elf main.dump main.elf.syms

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
