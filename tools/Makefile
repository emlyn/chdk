topdir=../

SKIPBUILDRULES=1

include $(topdir)makefile.inc

OBJS=pakwif.o finsig.o

all: pakwif$(EXE) finsig$(EXE)

%.o: %.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

.dep/%.d: %.c .dep
	$(HOSTCC) $(HOSTCFLAGS) -MM $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

pakwif$(EXE): pakwif.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

finsig$(EXE): finsig.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

gensig$(EXE): gensig.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^


clean:
	rm -f pakwif$(EXE) finsig$(EXE) $(OBJS)
#	if [ -s sig_ref.bin ] ; then \
#	  rm -f signatures.h ; \
#	fi

distclean: clean
#	rm -f signatures.h


signatures.h: gensig$(EXE) gensigs.sh sig_ref_1.txt sig_ref_1.bin sig_ref_2.txt sig_ref_2.bin
	@echo \-\> $@
	if [ -s sig_ref_1.bin ] && [ -s sig_ref_2.bin ] ; then \
	  $(SH) ./gensigs.sh $(SORT) > signatures.h ; \
	else \
	  echo CAUTION! \'signatures.h\' is not uptated due to \'sig_ref_1.bin\` or \'sig_ref_2.bin\` is empty! ; \
	  touch signatures.h ; \
	fi

sig_ref_1.bin:
	touch sig_ref_1.bin

sig_ref_2.bin:
	touch sig_ref_2.bin

finsig.o: signatures.h

include $(topdir)bottom.inc

