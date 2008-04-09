topdir=../../../../

include $(topdir)makefile.inc

CFLAGS+=-DLOW_LEVEL

all: libplatformsub.a

TARGET_PRIMARY = PRIMARY.BIN
OBJS=boot.o stubs_min.o stubs_auto.o stubs_entry.o lib.o stubs_entry_2.o capt_seq.o movie_rec.o

libplatformsub.a: $(OBJS)

clean:
	rm -f $(OBJS) libplatformsub.a stubs_entry.S.err stubs_not_found_names.err

distclean: clean
	rm -f stubs_entry.S stubs_auto.S
	rm -rf .dep


stubs_auto.S: boot.c capt_seq.c movie_rec.c
	@echo $< \-\> $@
ifeq ($(OSTYPE),Windows)
	cat $^ | \
	    grep -E 'B.*[[:space:]]+sub_[0-9A-Fa-f]' | \
	    sed 's/.*sub_\\([0-9A-Fa-f]*\\).*/\\1/' | \
	    $(SORT) | uniq | \
	    awk 'BEGIN {print "/* THIS FILE IS GENERATED */\n#include \"stubs_asm.h\"\n"} \
		{printf("STUB(%s)\n",$$1)}' > stubs_auto.S
else	
	cat $^ | \
	    grep 'B.*[[:space:]]*sub_[0-9A-Fa-f]' | \
	    sed 's/.*sub_\([0-9A-Fa-f]*\).*/\1/' | \
	    $(SORT) | uniq | \
	    awk 'BEGIN {print "/* THIS FILE IS GENERATED */\n#include \"stubs_asm.h\"\n"} \
		{printf("STUB(%s)\n",$$1)}' > stubs_auto.S
endif

stubs_entry.S: $(TARGET_PRIMARY) $(topdir)tools/signatures_$(PLATFORMOS).h
	@echo \-\> $@
	rm -f stubs_entry.S.err
	if [ -s $(TARGET_PRIMARY) ] ; then \
	  $(topdir)tools/finsig $(TARGET_PRIMARY) $(ROMBASEADDR) > stubs_entry.S ; \
	else \
	  echo CAUTION! \'stubs_entry.S\' is not uptated due to target firmware binary not found! ; \
	  touch stubs_entry.S ; \
	fi ; \
	if [ "X`grep 'ERROR' stubs_entry.S`" != "X" ] ; then \
	  grep "ERROR" stubs_entry.S | sed -r "s/\/\/ ERROR: ([^ ]+) is not found.*/\1/" | $(SORT) | uniq > stubs_nf.names ; \
	  grep -E "NH?STUB" stubs_entry_2.S | sed -r "s/ *NH?STUB\( *([^ ,]+).*/\1/" | $(SORT) | uniq > stubs_mn.names ; \
	  comm -23 stubs_nf.names stubs_mn.names > stubs_not_found_names.err ; \
	  rm -f stubs_nf.names stubs_mn.names ; \
	  if [ -s stubs_not_found_names.err ] ; then \
	    echo ERROR! There are unresolved addresses in \'stubs_entry.S\' \($(PLATFORM)-$(PLATFORMSUB)\) for the following names: ; \
	    cat stubs_not_found_names.err ; \
	    echo Please, add them into \'stubs_entry_2.S\' manually! ; \
	    mv stubs_entry.S stubs_entry.S.err ; \
	    exit 1 ; \
	  fi ; \
	  rm -f stubs_not_found_names.err ; \
	fi

$(TARGET_PRIMARY):
	touch $(TARGET_PRIMARY)

include $(topdir)bottom.inc

