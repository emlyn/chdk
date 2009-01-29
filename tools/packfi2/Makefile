topdir=../../

SKIPBUILDRULES=1

include $(topdir)makefile.inc

OBJS=fi2enc.o aes128.o compress.o deflate.o crc32.o zutil.o adler32.o trees.o

all: fi2enc$(EXE)

%.o: %.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -DPLATFORMOS_$(PLATFORMOS) -c -o $@ $<

.dep/%.d: %.c .dep
	$(HOSTCC) $(HOSTCFLAGS) -MM $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

fi2enc$(EXE): $(OBJS)
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

clean:
	rm -f fi2enc$(EXE) $(OBJS)

distclean: clean

include $(topdir)bottom.inc

