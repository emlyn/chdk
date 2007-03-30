topdir=./
srcdir=./

include makefile.inc

SUBDIRS=tools lib platform core loader

all: all-recursive

clean: clean-recursive

fir: all
	@echo \-\> $(PLATFORM)-$(PLATFORMSUB).FIR
	cp $(topdir)loader/$(PLATFORM)/main.bin $(topdir)/bin/main.bin
ifeq ($(OSTYPE),Windows)
	zero | dd bs=1k count=100 >> $(topdir)/bin/main.bin 2> $(DEVNULL)
else
	dd if=/dev/zero bs=1k count=100 >> $(topdir)/bin/main.bin 2> $(DEVNULL)
endif
	$(PAKWIF) $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR \
	     $(topdir)/bin/main.bin\
	    $(PLATFORMID)
	rm $(topdir)/bin/main.bin
	@echo "**** Firmware creation completed successfully"

upload: fir
	@echo Uploading...
	cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR $(topdir)bin/PS.FIR
	/home/vitalyb/Projects/ch/libptp2-1.1.0/src/ptpcam -u -m 0xbf01 --filename $(topdir)bin/PS.FIR

infoline:
	@echo "**** BUILDING HDK-$(VER) FOR $(PLATFORM)-$(PLATFORMSUB)"

firzip: infoline clean all fir
	@echo \-\> $(VER)-$(PLATFORM)-$(PLATFORMSUB).zip
	rm -f $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB).zip
	cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR $(topdir)bin/PS.FIR
	LANG=C echo -e "hdk-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:`date -R`" | \
	    zip -9jc $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB).zip $(topdir)bin/PS.FIR > $(DEVNULL)
	rm -f $(topdir)bin/PS.FIR

batch-zip:
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100e firzip
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100f firzip
	$(MAKE) -s --no-print-directory PLATFORM=a620 PLATFORMSUB=100f firzip
	$(MAKE) -s --no-print-directory PLATFORM=a630 PLATFORMSUB=100c firzip
	$(MAKE) -s --no-print-directory PLATFORM=a640 PLATFORMSUB=100b firzip
	$(MAKE) -s --no-print-directory PLATFORM=a710 PLATFORMSUB=100a firzip
	@echo "**** All firmwares created successfully"

batch-clean:
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100e clean
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100f clean
	$(MAKE) -s --no-print-directory PLATFORM=a620 PLATFORMSUB=100f clean
	$(MAKE) -s --no-print-directory PLATFORM=a630 PLATFORMSUB=100c clean
	$(MAKE) -s --no-print-directory PLATFORM=a640 PLATFORMSUB=100b clean
	$(MAKE) -s --no-print-directory PLATFORM=a710 PLATFORMSUB=100a clean

.PHONY: fir upload
