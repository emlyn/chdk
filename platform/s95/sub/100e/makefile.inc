# S95 PID = 3212 (hex)
PLATFORMID=12818

PLATFORMOS=dryos

# address where wif or diskboot code will be loaded by camera
MEMBASEADDR=0x1900

# size of memory region for CHDK
RESTARTSTART=0x50000

# points to the start of the memory pool used by the firmware 
MEMISOSTART=0x16EE30

# start of firmware
ROMBASEADDR=0xff810000

NEED_ENCODED_DISKBOOT=5

PLFLAGS=-DMEMBASEADDR=$(MEMBASEADDR) -DMEMISOSTART=$(MEMISOSTART) -DMEMISOSIZE=$(MEMISOSIZE)
PLFLAGS+=-DRESTARTSTART=$(RESTARTSTART)

KEYSYS=d4b
