topdir=../

include $(topdir)makefile.inc

all: pakwif$(EXE) finsig$(EXE) hexdmplt$(EXE)

pakwif$(EXE): pakwif.c
	$(HOSTCC) $(HOSTCFLAGS) -o pakwif$(EXE) pakwif.c

gensig$(EXE): gensig.c
	$(HOSTCC) $(HOSTCFLAGS) -o gensig$(EXE) gensig.c

hexdmplt$(EXE): hexdmplt.c
	$(HOSTCC) $(HOSTCFLAGS) -o hexdmplt$(EXE) hexdmplt.c

finsig$(EXE): finsig.c signatures.h
	$(HOSTCC) $(HOSTCFLAGS) -o finsig$(EXE) finsig.c

clean:
	rm -f pakwif$(EXE) gensig$(EXE) finsig$(EXE) hexdmplt$(EXE) signatures.h 

signatures.h: gensig$(EXE) gensigs.sh
	$(SH) ./gensigs.sh > signatures.h

