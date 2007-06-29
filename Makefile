topdir=./
srcdir=./

include makefile.inc

SUBDIRS=tools lib platform core loader

all: all-recursive

clean: clean-recursive

distclean: distclean-recursive

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
	mv $(topdir)/bin/main.bin $(topdir)/bin/DISKBOOT.BIN
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
	zip -9j $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB).zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
	rm -f $(topdir)bin/PS.FIR
	rm -f $(topdir)bin/DISKBOOT.BIN

batch-zip:
	$(MAKE) SILENT=$(SILENT) PLATFORM=a610 PLATFORMSUB=100e firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=a610 PLATFORMSUB=100f firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=a620 PLATFORMSUB=100f firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=a630 PLATFORMSUB=100c firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=a640 PLATFORMSUB=100b firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=a710 PLATFORMSUB=100a firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=s2is PLATFORMSUB=100e firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=s2is PLATFORMSUB=100f firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=s2is PLATFORMSUB=100g firzip
	$(MAKE) SILENT=$(SILENT) PLATFORM=s3is PLATFORMSUB=100a firzip
	@echo "**** All firmwares created successfully"

batch-clean:
	$(MAKE) SILENT=$(SILENT) PLATFORM=a610 PLATFORMSUB=100e clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=a610 PLATFORMSUB=100f clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=a620 PLATFORMSUB=100f clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=a630 PLATFORMSUB=100c clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=a640 PLATFORMSUB=100b clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=a710 PLATFORMSUB=100a clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=s2is PLATFORMSUB=100e clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=s2is PLATFORMSUB=100f clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=s2is PLATFORMSUB=100g clean
	$(MAKE) SILENT=$(SILENT) PLATFORM=s3is PLATFORMSUB=100a clean


.PHONY: fir upload
