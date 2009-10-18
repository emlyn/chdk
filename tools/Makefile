topdir=../

SKIPBUILDRULES=1

include $(topdir)makefile.inc

OBJS=pakwif.o finsig.o gensig.o dumpchk.o dancingbits.o

ifdef OPT_FI2
  SUBDIRS=packfi2
endif

all: pakwif$(EXE) finsig$(EXE) dancingbits$(EXE)

%.o: %.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -DPLATFORMOS_$(PLATFORMOS) -c -o $@ $<

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

dumpchk$(EXE): dumpchk.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

dancingbits$(EXE): dancingbits.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

clean:
	rm -f pakwif$(EXE) finsig$(EXE) $(OBJS)
#	if [ -s sig_ref_vxworks_1.bin ] && [ -s sig_ref_vxworks_2.bin ] && [ -s sig_ref_vxworks_3.bin ] ; then \
#	  rm -f signatures_vxworks.h ; \
#	fi
#	if [ -s sig_ref_dryos_1.bin ] ; then \
#	  rm -f signatures_dryos.h ; \
#	fi

distclean: clean
#	rm -f signatures.h


signatures_vxworks.h: gensig$(EXE) gensigs.sh sig_ref_vxworks_1.txt sig_ref_vxworks_1.bin sig_ref_vxworks_2.txt sig_ref_vxworks_2.bin sig_ref_vxworks_3.txt sig_ref_vxworks_3.bin
	@echo \-\> $@
	if [ -s sig_ref_vxworks_1.bin ] && [ -s sig_ref_vxworks_2.bin ] && [ -s sig_ref_vxworks_3.bin ] ; then \
	  $(SH) ./gensigs.sh $(SORT) vxworks "1 2 3" > signatures_vxworks.h ; \
	else \
	  echo CAUTION! \'signatures_vxworks.h\' is not updated due to \'sig_ref_vxworks_1.bin\` or \'sig_ref_vxworks_2.bin\` or \'sig_ref_vxworks_3.bin\` is empty! ; \
	  touch signatures_vxworks.h ; \
	fi

signatures_dryos.h: gensig$(EXE) gensigs.sh sig_ref_dryos_1.txt sig_ref_dryos_1.bin sig_ref_dryos_2.txt sig_ref_dryos_2.bin sig_ref_dryos_3.txt sig_ref_dryos_3.bin
	@echo \-\> $@
	if [ -s sig_ref_dryos_1.bin ] && [ -s sig_ref_dryos_2.bin ] && [ -s sig_ref_dryos_3.bin ] ; then \
	  $(SH) ./gensigs.sh $(SORT) dryos "1 2 3" > signatures_dryos.h ; \
	else \
	  echo CAUTION! \'signatures_dryos.h\' is not updated due to \'sig_ref_dryos_1.bin\` is empty! ; \
	  touch signatures_dryos.h ; \
	fi

sig_ref_vxworks_1.bin:
	touch sig_ref_vxworks_1.bin

sig_ref_vxworks_2.bin:
	touch sig_ref_vxworks_2.bin

sig_ref_vxworks_3.bin:
	touch sig_ref_vxworks_3.bin

sig_ref_dryos_1.bin:
	touch sig_ref_dryos_1.bin

sig_ref_dryos_2.bin:
	touch sig_ref_dryos_2.bin

sig_ref_dryos_3.bin:
	touch sig_ref_dryos_3.bin

finsig.o: finsig.c signatures_$(PLATFORMOS).h

include $(topdir)bottom.inc

