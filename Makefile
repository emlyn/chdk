topdir=./
srcdir=./

include makefile.inc

#ifndef NO_INC_BUILD
#BUILD_NUMBER := $(shell expr $(BUILD_NUMBER) + 1)
#endif

SUBDIRS=tools lib platform core loader CHDK

all: all-recursive

clean: clean-recursive

distclean: distclean-recursive

fir: version firsub

firsub: all
	mkdir -p  $(topdir)bin
	cp $(topdir)loader/$(PLATFORM)/main.bin  $(topdir)bin/main.bin
ifndef NOZERO100K
ifeq ($(OSTYPE),Windows)
	zero | dd bs=1k count=100 >>  $(topdir)bin/main.bin 2> $(DEVNULL)
else
	dd if=/dev/zero bs=1k count=100 >>  $(topdir)bin/main.bin 2> $(DEVNULL)
endif
endif
ifdef PLATFORMOS
  ifeq ($(PLATFORMOS),vxworks)
	@echo \-\> PS.FIR
	$(PAKWIF) $(topdir)bin/PS.FIR \
	      $(topdir)bin/main.bin\
	    $(PLATFORMID) 0x01000101
  endif
  ifeq ($(PLATFORMOS),dryos)
ifdef OPT_FI2
	@echo \-\> PS.FI2
	$(PAKFI2)  $(topdir)bin/main.bin -p $(PLATFORMID) -key $(FI2KEY) -iv $(FI2IV)  $(topdir)bin/PS.FI2
endif
  endif
endif
ifdef NEED_ENCODED_DISKBOOT
	@echo dance \-\> DISKBOOT.BIN ver $(NEED_ENCODED_DISKBOOT)
	$(ENCODE_DISKBOOT) $(topdir)bin/main.bin  $(topdir)bin/DISKBOOT.BIN $(NEED_ENCODED_DISKBOOT) 
	rm  $(topdir)bin/main.bin
else
	mv  $(topdir)bin/main.bin  $(topdir)bin/DISKBOOT.BIN
endif
	@echo "**** Firmware creation completed successfully"

upload: fir
	@echo Uploading...
	cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR $(topdir)bin/PS.FIR
	/home/vitalyb/Projects/ch/libptp2-1.1.0/src/ptpcam -u -m 0xbf01 --filename $(topdir)bin/PS.FIR

infoline:
	@echo "**** GCC $(GCC_VERSION) : BUILDING CHDK-$(VER), #$(BUILD_NUMBER) FOR $(PLATFORM)-$(PLATFORMSUB)"

version: FORCE
	echo "**** Build: $(BUILD_NUMBER)"
#	echo "BUILD_NUMBER := $(BUILD_NUMBER)" > version.inc

FORCE:

firzip: version firzipsub

firzipsub: infoline clean firsub
	@echo \-\> $(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip
	rm -f $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip
	LANG=C echo -e "CHDK-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:$(BUILD_NUMBER) date:`date -R`" | \
	    zip -9jz $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
ifdef PLATFORMOS
  ifeq ($(PLATFORMOS),vxworks)
	zip -9j $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/PS.FIR > $(DEVNULL)
	rm -f $(topdir)bin/PS.FIR
  endif
  ifeq ($(PLATFORMOS),dryos)
  ifdef OPT_FI2
	zip -9j $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/PS.FI2 > $(DEVNULL)
	rm -f $(topdir)bin/PS.FI2
  endif
  endif
endif
	rm -f $(topdir)bin/DISKBOOT.BIN

firzipsubcomplete: infoline clean firsub
	@echo \-\> $(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip
	rm -f $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip
	@echo \-\> $(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip
	rm -f $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip
	LANG=C echo -e "CHDK-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:$(BUILD_NUMBER) date:`date -R`" | \
	zip -9jz $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
	LANG=C echo -e "CHDK-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:$(BUILD_NUMBER) date:`date -R`" | \
	zip -9jz $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/SYMBOLS/*  > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/BOOKS/*  > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/CURVES/*  > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/DATA/*  > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/FONTS/*  > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/GAMES/*   > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/GRIDS/* > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/LANG/*   > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/LUALIB/*   > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/LUALIB/GEN/*   > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/SCRIPTS/*  > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/SCRIPTS/examples/* 	 > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/SCRIPTS/TEST/* 	 > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)CHDK/syscurves.CVF 	 > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)doc/changelog.txt  > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)doc/changelog.txt  > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)tools/vers.req  > $(DEVNULL)
	cat $(topdir)doc/1_intro.txt  $(topdir)platform/$(PLATFORM)/notes.txt $(topdir)doc/2_installation.txt $(topdir)doc/3_faq.txt $(topdir)doc/4_urls.txt $(topdir)doc/5_gpl.txt $(topdir)doc/6_ubasic_copyright.txt > $(topdir)doc/readme.txt
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)doc/readme.txt  > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)doc/readme.txt  > $(DEVNULL)

ifdef PLATFORMOS
  ifeq ($(PLATFORMOS),vxworks)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)bin/PS.FIR > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/PS.FIR > $(DEVNULL)
	rm -f $(topdir)bin/PS.FIR
  endif
  ifeq ($(PLATFORMOS),dryos)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)doc/readme.txt  > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)doc/readme.txt  > $(DEVNULL)
ifdef OPT_FI2
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-full.zip $(topdir)bin/PS.FI2 > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER).zip $(topdir)bin/PS.FI2 > $(DEVNULL)
	rm -f $(topdir)bin/PS.FI2
endif
  endif
endif
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
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100i NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100j NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100d NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100i NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a530 PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a540 PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a560 PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a590 PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a590 PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=s80  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus850_sd800   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus860_sd870   PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=102b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus950_sd850   PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub	
	$(MAKE) -s --no-print-directory PLATFORM=ixus980_sd990   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub	
	$(MAKE) -s --no-print-directory PLATFORM=ixus980_sd990   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub	
	$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300    PLATFORMSUB=100k NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300    PLATFORMSUB=100j NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400    PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400    PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100d NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus65_sd630    PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=102a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=102a NO_INC_BUILD=1 firzipsub
	#$(MAKE) -s --no-print-directory PLATFORM=ixusW_sd430     PLATFORMSUB=110a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a720 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a650 PLATFORMSUB=100d NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a450 PLATFORMSUB=100d NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a460 PLATFORMSUB=100d NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a550 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=s5is PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=s5is PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=tx1  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=tx1  PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx100is  PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx100is  PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus750_sd550  PLATFORMSUB=100f NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus750_sd550  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus60_sd600  PLATFORMSUB=100a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus60_sd600  PLATFORMSUB=100d NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus960_sd950  PLATFORMSUB=100d NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus80_sd1100  PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus80_sd1100  PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixusizoom_sd30  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=101a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=102b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=103a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx1 PLATFORMSUB=200h NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx1 PLATFORMSUB=201a NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100f NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=100e NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=101b NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=102c NO_INC_BUILD=1 firzipsub
	$(MAKE) -s --no-print-directory PLATFORM=sx110is  PLATFORMSUB=100b NO_INC_BUILD=1 firzipsub
	@echo "**** All firmwares created successfully"
	@echo "**** Copying duplicate Firmwares"
	cp $(topdir)bin/$(VER)-a610-100e-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-a610-100d-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-s2is-100g-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-s2is-100i-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-ixus800_sd700-101b-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus800_sd700-101a-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-ixus850_sd800-100e-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus850_sd800-100d-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-ixus70_sd1000-101b-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus70_sd1000-101a-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-ixus75_sd750-101a-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus75_sd750-101b-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-ixus80_sd1100-101a-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus80_sd1100-101b-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-ixus970_sd890-100c-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus970_sd890-100d-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-g9-100g-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-g9-100f-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-g9-100i-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-g9-100h-$(BUILD_NUMBER).zip
	cp $(topdir)bin/$(VER)-a470-101b-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-a470-101a-$(BUILD_NUMBER).zip
	mv $(topdir)bin/$(VER)-sx1-200h-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-sx1-200h-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-sx1-201a-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-sx1-201a-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-sx10-100c-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-sx10-100c-$(BUILD_NUMBER)_BETA.zip	
	mv $(topdir)bin/$(VER)-sx10-101b-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-sx10-101b-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-sx10-102b-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-sx10-102b-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-sx10-103a-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-sx10-103a-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-ixus980_sd990-100e-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus980_sd990-100e-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-ixus980_sd990-101b-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus980_sd990-101b-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-ixus870_sd880-100e-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus870_sd880-100e-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-ixus870_sd880-101a-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus870_sd880-101a-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/$(VER)-ixus870_sd880-102b-$(BUILD_NUMBER).zip $(topdir)bin/$(VER)-ixus870_sd880-102b-$(BUILD_NUMBER)_BETA.zip
	@echo "**** Done Copying duplicate Firmwares"
	@echo "**** Summary of memisosizes"
	cat $(topdir)bin/caminfo.txt
	rm -f $(topdir)bin/caminfo.txt   > $(DEVNULL)

batch-zip-complete: version
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a610 PLATFORMSUB=100f NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a620 PLATFORMSUB=100f NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a630 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a640 PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a700 PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a710 PLATFORMSUB=100a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100f NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=s2is PLATFORMSUB=100g NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=s3is PLATFORMSUB=100a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100g NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100i NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100j NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100d NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100g NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100i NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a530 PLATFORMSUB=100a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a540 PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a560 PLATFORMSUB=100a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a590 PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a590 PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	#$(MAKE) -s --no-print-directory PLATFORM=s80  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus850_sd800   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus860_sd870   PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=102b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus950_sd850   PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete	
	$(MAKE) -s --no-print-directory PLATFORM=ixus980_sd990   PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete	
	$(MAKE) -s --no-print-directory PLATFORM=ixus980_sd990   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete	
	$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300    PLATFORMSUB=100k NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300    PLATFORMSUB=100j NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400    PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400    PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100d NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus65_sd630    PLATFORMSUB=100a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=102a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=102a NO_INC_BUILD=1 firzipsubcomplete
	#$(MAKE) -s --no-print-directory PLATFORM=ixusW_sd430     PLATFORMSUB=110a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a720 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a650 PLATFORMSUB=100d NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a450 PLATFORMSUB=100d NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a460 PLATFORMSUB=100d NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a550 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=s5is PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=s5is PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=tx1  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=tx1  PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx100is  PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx100is  PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus750_sd550  PLATFORMSUB=100f NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus750_sd550  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus60_sd600  PLATFORMSUB=100a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus60_sd600  PLATFORMSUB=100d NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus960_sd950  PLATFORMSUB=100d NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus80_sd1100  PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus80_sd1100  PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixusizoom_sd30  PLATFORMSUB=100g NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=101a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=102b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=103a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx1 PLATFORMSUB=200h NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx1 PLATFORMSUB=201a NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100f NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=100e NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=101b NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=102c NO_INC_BUILD=1 firzipsubcomplete
	$(MAKE) -s --no-print-directory PLATFORM=sx110is  PLATFORMSUB=100b NO_INC_BUILD=1 firzipsubcomplete
	@echo "**** All zipfiles including firmwares and extra stuff created successfully"
	@echo "**** Copying duplicate Firmwares"
	cp $(topdir)bin/a610-100e-$(BUILD_NUMBER)-full.zip $(topdir)bin/a610-100d-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/a610-100e-$(BUILD_NUMBER).zip $(topdir)bin/a610-100d-$(BUILD_NUMBER).zip
	cp $(topdir)bin/s2is-100g-$(BUILD_NUMBER)-full.zip $(topdir)bin/s2is-100i-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/s2is-100g-$(BUILD_NUMBER).zip $(topdir)bin/s2is-100i-$(BUILD_NUMBER).zip
	cp $(topdir)bin/ixus800_sd700-101b-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus800_sd700-101a-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/ixus800_sd700-101b-$(BUILD_NUMBER).zip $(topdir)bin/ixus800_sd700-101a-$(BUILD_NUMBER).zip
	cp $(topdir)bin/ixus850_sd800-100e-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus850_sd800-100d-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/ixus850_sd800-100e-$(BUILD_NUMBER).zip $(topdir)bin/ixus850_sd800-100d-$(BUILD_NUMBER).zip
	cp $(topdir)bin/ixus70_sd1000-101b-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus70_sd1000-101a-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/ixus70_sd1000-101b-$(BUILD_NUMBER).zip $(topdir)bin/ixus70_sd1000-101a-$(BUILD_NUMBER).zip
	cp $(topdir)bin/ixus75_sd750-101a-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus75_sd750-101b-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/ixus75_sd750-101a-$(BUILD_NUMBER).zip $(topdir)bin/ixus75_sd750-101b-$(BUILD_NUMBER).zip
	cp $(topdir)bin/ixus80_sd1100-101a-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus80_sd1100-101b-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/ixus80_sd1100-101a-$(BUILD_NUMBER).zip $(topdir)bin/ixus80_sd1100-101b-$(BUILD_NUMBER).zip
	cp $(topdir)bin/ixus970_sd890-100c-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus970_sd890-100d-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/ixus970_sd890-100c-$(BUILD_NUMBER).zip $(topdir)bin/ixus970_sd890-100d-$(BUILD_NUMBER).zip
	cp $(topdir)bin/g9-100g-$(BUILD_NUMBER)-full.zip $(topdir)bin/g9-100f-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/g9-100g-$(BUILD_NUMBER).zip $(topdir)bin/g9-100f-$(BUILD_NUMBER).zip
	cp $(topdir)bin/g9-100i-$(BUILD_NUMBER)-full.zip $(topdir)bin/g9-100h-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/g9-100i-$(BUILD_NUMBER).zip $(topdir)bin/g9-100h-$(BUILD_NUMBER).zip
	cp $(topdir)bin/a470-101b-$(BUILD_NUMBER)-full.zip $(topdir)bin/a470-101a-$(BUILD_NUMBER)-full.zip
	cp $(topdir)bin/a470-101b-$(BUILD_NUMBER).zip $(topdir)bin/a470-101a-$(BUILD_NUMBER).zip
	mv $(topdir)bin/sx1-200h-$(BUILD_NUMBER)-full.zip $(topdir)bin/sx1-200h-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/sx1-200h-$(BUILD_NUMBER).zip $(topdir)bin/sx1-200h-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/sx1-201a-$(BUILD_NUMBER)-full.zip $(topdir)bin/sx1-201a-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/sx1-201a-$(BUILD_NUMBER).zip $(topdir)bin/sx1-201a-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/sx10-100c-$(BUILD_NUMBER)-full.zip $(topdir)bin/sx10-100c-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/sx10-100c-$(BUILD_NUMBER).zip $(topdir)bin/sx10-100c-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/sx10-101b-$(BUILD_NUMBER)-full.zip $(topdir)bin/sx10-101b-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/sx10-101b-$(BUILD_NUMBER).zip $(topdir)bin/sx10-101b-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/sx10-102b-$(BUILD_NUMBER)-full.zip $(topdir)bin/sx10-102b-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/sx10-102b-$(BUILD_NUMBER).zip $(topdir)bin/sx10-102b-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/sx10-103a-$(BUILD_NUMBER)-full.zip $(topdir)bin/sx10-103a-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/sx10-103a-$(BUILD_NUMBER).zip $(topdir)bin/sx10-103a-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/ixus980_sd990-100e-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus980_sd990-100e-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/ixus980_sd990-100e-$(BUILD_NUMBER).zip $(topdir)bin/ixus980_sd990-100e-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/ixus980_sd990-101b-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus980_sd990-101b-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/ixus980_sd990-101b-$(BUILD_NUMBER).zip $(topdir)bin/ixus980_sd990-101b-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/ixus870_sd880-100e-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus870_sd880-100e-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/ixus870_sd880-100e-$(BUILD_NUMBER).zip $(topdir)bin/ixus870_sd880-100e-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/ixus870_sd880-101a-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus870_sd880-101a-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/ixus870_sd880-101a-$(BUILD_NUMBER).zip $(topdir)bin/ixus870_sd880-101a-$(BUILD_NUMBER)_BETA.zip
	mv $(topdir)bin/ixus870_sd880-102b-$(BUILD_NUMBER)-full.zip $(topdir)bin/ixus870_sd880-102b-$(BUILD_NUMBER)-full_BETA.zip
	mv $(topdir)bin/ixus870_sd880-102b-$(BUILD_NUMBER).zip $(topdir)bin/ixus870_sd880-102b-$(BUILD_NUMBER)_BETA.zip
	@echo "**** Done Copying duplicate Firmwares"
	@echo "**** Summary of memisosizes"
	cat $(topdir)bin/caminfo.txt
	rm -f $(topdir)bin/caminfo.txt   > $(DEVNULL)



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
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100e NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100i NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g7   PLATFORMSUB=100j NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100d NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=g9   PLATFORMSUB=100i NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a530 PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a540 PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a560 PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=100e NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a570 PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a590 PLATFORMSUB=100e NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a590 PLATFORMSUB=101b NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=s80  PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus700_sd500   PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus800_sd700   PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus850_sd800   PLATFORMSUB=100e NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus860_sd870   PLATFORMSUB=100c NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=100e NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=101a NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=ixus870_sd880   PLATFORMSUB=102b NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=ixus950_sd850   PLATFORMSUB=100c NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=ixus980_sd990   PLATFORMSUB=100e NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=ixus980_sd990   PLATFORMSUB=101b NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300    PLATFORMSUB=100k NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus40_sd300    PLATFORMSUB=100j NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400    PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus50_sd400    PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus55_sd450    PLATFORMSUB=100d NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus65_sd630    PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus70_sd1000   PLATFORMSUB=102a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus75_sd750   PLATFORMSUB=102a NO_INC_BUILD=1 clean
	#$(MAKE) -s --no-print-directory PLATFORM=ixusW_sd430     PLATFORMSUB=110a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a720 PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a650 PLATFORMSUB=100d NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a450 PLATFORMSUB=100d NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a460 PLATFORMSUB=100d NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a550 PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=s5is PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=s5is PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=tx1  PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=tx1  PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=sx100is  PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=sx100is  PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus750_sd550  PLATFORMSUB=100f NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus750_sd550  PLATFORMSUB=100g NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus60_sd600  PLATFORMSUB=100a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus60_sd600  PLATFORMSUB=100d NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus960_sd950  PLATFORMSUB=100d NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus80_sd1100  PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus80_sd1100  PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixusizoom_sd30  PLATFORMSUB=100g NO_INC_BUILD=1 clean	
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=101a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=sx10 PLATFORMSUB=102b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=sx1 PLATFORMSUB=200h NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=sx1 PLATFORMSUB=201a NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=ixus970_sd890  PLATFORMSUB=100f NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=101b NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=a470  PLATFORMSUB=102c NO_INC_BUILD=1 clean
	$(MAKE) -s --no-print-directory PLATFORM=sx110is  PLATFORMSUB=100b NO_INC_BUILD=1 clean

.PHONY: fir upload
