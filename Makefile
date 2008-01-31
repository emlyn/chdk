topdir=./
srcdir=./

include makefile.inc

ifndef NO_INC_BUILD
BUILD_NUMBER := $(shell expr $(BUILD_NUMBER) + 1)
endif

SUBDIRS=tools lib platform core loader

all: all-recursive

clean: clean-recursive

distclean: distclean-recursive

fir: version firsub

firsub: all
	@echo \-\> $(PLATFORM)-$(PLATFORMSUB).FIR
	cp $(topdir)loader/$(PLATFORM)/main.bin $(topdir)/bin/main.bin
ifndef NOZERO100K
ifeq ($(OSTYPE),Windows)
	zero | dd bs=1k count=100 >> $(topdir)/bin/main.bin 2> $(DEVNULL)
else
	dd if=/dev/zero bs=1k count=100 >> $(topdir)/bin/main.bin 2> $(DEVNULL)
endif
endif
	$(PAKWIF) $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR \
	     $(topdir)/bin/main.bin\
	    $(PLATFORMID) 0x01000101
	mv $(topdir)/bin/main.bin $(topdir)/bin/DISKBOOT.BIN
	@echo "**** Firmware creation completed successfully"

upload: fir
	@echo Uploading...
	cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR $(topdir)bin/PS.FIR
	/home/vitalyb/Projects/ch/libptp2-1.1.0/src/ptpcam -u -m 0xbf01 --filename $(topdir)bin/PS.FIR

infoline:
	@echo "**** BUILDING HDK-$(VER), #$(BUILD_NUMBER) FOR $(PLATFORM)-$(PLATFORMSUB)"

version: FORCE
	echo "**** Build: $(BUILD_NUMBER)"
	echo "BUILD_NUMBER := $(BUILD_NUMBER)" > version.inc

FORCE:

firzip: version firzipsub

firzipsub: infoline clean firsub
	@echo \-\> $(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip
	rm -f $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR $(topdir)bin/PS.FIR
	LANG=C echo -e "hdk-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:`date -R`" | \
	    zip -9jc $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/PS.FIR > $(DEVNULL)
	zip -9j $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
	rm -f $(topdir)bin/PS.FIR
	rm -f $(topdir)bin/DISKBOOT.BIN

batch-zip: version
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100f NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a620 PLATFORMSUB=100f NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a630 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a640 PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a700 PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a710 PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100f NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=s3is PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100i NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100j NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=a540 PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a560 PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=s80  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=ixus850_sd800  PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300   PLATFORMSUB=100k NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=ixus65_sd630   PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000  PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000  PLATFORMSUB=102a NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=ixusW_sd430    PLATFORMSUB=110a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a720 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	@echo "**** All firmwares created successfully"

batch-clean:
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100e NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100f NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a620 PLATFORMSUB=100f NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a630 PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a640 PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a700 PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a710 PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100e NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100f NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=s3is PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100i NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100j NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=a540 PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a560 PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=100e NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=101a NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=s80  PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=101b NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=ixus850_sd800   PLATFORMSUB=100e NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300   PLATFORMSUB=100k NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400   PLATFORMSUB=101a NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=ixus65_sd630   PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000  PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000  PLATFORMSUB=102a NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=ixusW_sd430    PLATFORMSUB=110a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a720 PLATFORMSUB=100c NO_INC_BUILD=1 clean

.PHONY: fir upload
