# USB ID: 04a9:3148
PLATFORMID=12616

PLATFORMOS=dryos

MEMBASEADDR=0x1900
RESTARTSTART=0x50000
#MEMISOSTART=0x9B610 // Does not work (if I recall correctly). Offset by 0x10000. Comment kept for future reference.
MEMISOSTART=0xAB610
MEMISOSIZE=0x40000
ROMBASEADDR=0xff810000

TARGET_PRIMARY=$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/PRIMARY.BIN

PLFLAGS=-DMEMBASEADDR=$(MEMBASEADDR) -DMEMISOSTART=$(MEMISOSTART) -DMEMISOSIZE=$(MEMISOSIZE)
PLFLAGS+=-DRESTARTSTART=$(RESTARTSTART)