topdir=../

include $(topdir)makefile.inc

all: pakwif$(EXE) finsig$(EXE) hexdmplt$(EXE)

pakwif$(EXE): pakwif.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o pakwif$(EXE) pakwif.c

gensig$(EXE): gensig.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o gensig$(EXE) gensig.c

hexdmplt$(EXE): hexdmplt.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o hexdmplt$(EXE) hexdmplt.c

finsig$(EXE): finsig.c signatures.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o finsig$(EXE) finsig.c

clean:
	rm -f pakwif$(EXE) gensig$(EXE) finsig$(EXE) hexdmplt$(EXE)
	if [ -s sig_ref.bin ] ; then \
	  rm -f signatures.h ; \
	fi

signatures.h: gensig$(EXE) gensigs.sh sig_ref_1.txt sig_ref_1.bin sig_ref_2.txt sig_ref_2.bin
	@echo \-\> $@
	if [ -s sig_ref_1.bin ] && [ -s sig_ref_2.bin ] ; then \
	  $(SH) ./gensigs.sh > signatures.h ; \
	else \
	  echo CAUTION! \'signatures.h\' is not uptated due to \'sig_ref_1.bin\` or \'sig_ref_2.bin\` is empty! ; \
	  touch signatures.h ; \
	fi

sig_ref_1.bin:
	touch sig_ref_1.bin

sig_ref_2.bin:
	touch sig_ref_2.bin
