VER=CHDK

PLATFORM=s3is
PLATFORMSUB=100a

#PLATFORM=a620
#PLATFORMSUB=100f

#PLATFORM=a610
#PLATFORMSUB=100e

#PLATFORM=ixus40_sd300
#PLATFORMSUB=100k

#PLATFORM=ixus40_sd300
#PLATFORMSUB=100j

#PLATFORM=sx100is
#PLATFORMSUB=100c

#PLATFORM=sx10
#PLATFORMSUB=101a

#PLATFORM=sx1
#PLATFORMSUB=200h

#PLATFORM=sx100is
#PLATFORMSUB=100b

#PLATFORM=sx110is
#PLATFORMSUB=100b

#PLATFORM=sx200is
#PLATFORMSUB=100c
# note, 100d compatible with 100c

#PLATFORM=ixus50_sd400
#PLATFORMSUB=101a

#PLATFORM=ixus50_sd400
#PLATFORMSUB=101b

#PLATFORM=ixus750_sd550
#PLATFORMSUB=100f

#PLATFORM=ixus750_sd550
#PLATFORMSUB=100g

#PLATFORM=a640
#PLATFORMSUB=100b

#PLATFORM=a700
#PLATFORMSUB=100b

#PLATFORM=a710
#PLATFORMSUB=100a

#PLATFORM=s2is
#PLATFORMSUB=100e

#PLATFORM=s2is
#PLATFORMSUB=100f

#PLATFORM=s2is
#PLATFORMSUB=100g

#PLATFORM=g7
#PLATFORMSUB=100e

#PLATFORM=g7
#PLATFORMSUB=100g

#PLATFORM=g7
#PLATFORMSUB=100i

#PLATFORM=g7
#PLATFORMSUB=100j

#PLATFORM=g9
#PLATFORMSUB=100d

#PLATFORM=g9
#PLATFORMSUB=100g

#PLATFORM=a530
#PLATFORMSUB=100a

#PLATFORM=a540
#PLATFORMSUB=100b

#PLATFORM=a560
#PLATFORMSUB=100a

#PLATFORM=a570
#PLATFORMSUB=101a

#PLATFORM=a570
#PLATFORMSUB=100e

#PLATFORM=a610
#PLATFORMSUB=100f

#PLATFORM=ixus700_sd500
#PLATFORMSUB=101a

#PLATFORM=ixus700_sd500
#PLATFORMSUB=101b

#PLATFORM=ixus800_sd700
#PLATFORMSUB=100b

#PLATFORM=ixus800_sd700
#PLATFORMSUB=101b

#PLATFORM=a720
#PLATFORMSUB=100c

#PLATFORM=ixus850_sd800
#PLATFORMSUB=100e

#PLATFORM=ixus860_sd870
#PLATFORMSUB=100c

#PLATFORM=ixus870_sd880
#PLATFORMSUB=100e

#PLATFORM=ixus870_sd880
#PLATFORMSUB=101a

#PLATFORM=ixus870_sd880
#PLATFORMSUB=102b

#PLATFORM=ixus80_sd1100
#PLATFORMSUB=100c

#PLATFORM=ixus80_sd1100
#PLATFORMSUB=101a

#PLATFORM=ixus950_sd850
#PLATFORMSUB=100c

#PLATFORM=ixus55_sd450
#PLATFORMSUB=100b

#PLATFORM=ixus55_sd450
#PLATFORMSUB=100c

#PLATFORM=ixus55_sd450
#PLATFORMSUB=100d

#PLATFORM=ixus60_sd600
#PLATFORMSUB=100a

#PLATFORM=ixus60_sd600
#PLATFORMSUB=100d

#PLATFORM=ixus70_sd1000
#PLATFORMSUB=100c

#PLATFORM=ixus70_sd1000
#PLATFORMSUB=101b

#PLATFORM=ixus70_sd1000
#PLATFORMSUB=102a

#PLATFORM=a650
#PLATFORMSUB=100d

#PLATFORM=a450
#PLATFORMSUB=100d

#PLATFORM=a460
#PLATFORMSUB=100d

#PLATFORM=a550
#PLATFORMSUB=100c

#PLATFORM=a590
#PLATFORMSUB=100e

#PLATFORM=a590
#PLATFORMSUB=101b

#PLATFORM=a630
#PLATFORMSUB=100c

#PLATFORM=s5is
#PLATFORMSUB=101a

#PLATFORM=s5is
#PLATFORMSUB=101b

#PLATFORM=ixus65_sd630
#PLATFORMSUB=100a

#PLATFORM=tx1
#PLATFORMSUB=100g

#PLATFORM=tx1
#PLATFORMSUB=101b

#PLATFORM=ixus960_sd950
#PLATFORMSUB=100d

#PLATFORM=ixus970_sd890
#PLATFORMSUB=100b

#PLATFORM=ixus970_sd890
#PLATFORMSUB=100c

#PLATFORM=ixus970_sd890
#PLATFORMSUB=100f

#PLATFORM=ixus75_sd750
#PLATFORMSUB=100b

#PLATFORM=ixus75_sd750
#PLATFORMSUB=101a

#PLATFORM=ixus75_sd750
#PLATFORMSUB=102a

#PLATFORM=ixusizoom_sd30
#PLATFORMSUB=100g

#PLATFORM=a470
#PLATFORMSUB=102c

#PLATFORM=a470
#PLATFORMSUB=101b

#PLATFORM=ixus980_sd990
#PLATFORMSUB=100e

#PLATFORM=ixus980_sd990
#PLATFORMSUB=101b

#PLATFORM=a2000
#PLATFORMSUB=100c

#PLATFORM=ixus100_sd780
#PLATFORMSUB=100c

#PLATFORM=ixus90_sd790
#PLATFORMSUB=100c

#PLATFORM=ixus90_sd790
#PLATFORMSUB=100d

#PLATFORM=g11 
#PLATFORMSUB=100f

#PLATFORM=g11 
#PLATFORMSUB=100j

#PLATFORM=g11 
#PLATFORMSUB=100l

#PLATFORM=sx20
#PLATFORMSUB=102b

PLATFORM=ixus85_sd770
PLATFORMSUB=100a

PLATFORM=ixus95_sd1200
PLATFORMSUB=100c

MEMISOSIZE="(&_end-&_start)"
# override this on the command line or in buildconf to use PRIMARY.BIN from a different tree
# should be an absolute path
PRIMARY_ROOT=$(topdir)platform
include $(topdir)buildconf.inc
# optional local version of buildconf.inc, not in SVN so it can be used in autobuilds
# and to avoid getting accidentally included in svn diffs
# you may also set your default camera here
-include $(topdir)localbuildconf.inc
include $(topdir)version.inc
include $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc
ifdef OPT_FI2
include $(topdir)/platform/fi2.inc
endif

SILENT=SILENT

NOZERO100K=TRUE

##########################################################################
##########################################################################
##########################################################################

ESED = sed -r

# keep sort order consistent
export LC_ALL=C

ifndef OSTYPE
  HOSTPLATFORM:=$(patsubst MINGW%,MINGW,$(shell uname -s))
  ifeq ($(HOSTPLATFORM),MINGW)
    OSTYPE = Windows
    EXE = .exe
    SH = sh
    DEVNULL = NUL
	OLDSEPARATOR = \\\\
	NEWSEPARATOR = /
	SORT := $(dir $(shell which uniq.exe | sed 's_$(OLDSEPARATOR)_$(NEWSEPARATOR)_g'))/sort.exe
  else
    ifeq ($(HOSTPLATFORM),Linux)
      OSTYPE = Linux
      EXE =
      SH =
      DEVNULL = /dev/null
      SORT = sort
    else
      ifeq ($(HOSTPLATFORM),Darwin)
        OSTYPE = Darwin
        EXE =
        SH =
        DEVNULL = /dev/null
        SORT = sort
        ESED = sed -E
      else
        OSTYPE = Other
        EXE =
        SH =
        DEVNULL = /dev/null
        SORT = sort
      endif
    endif
  endif
else
  EXE =
  SH =
  DEVNULL = /dev/null
  SORT = sort
endif

##########################################################################
##########################################################################
##########################################################################

HOSTCC=gcc
HOSTCFLAGS=-g -O2 -Wall
HOSTAR=ar

PAKWIF=$(topdir)tools/pakwif$(EXE)
PAKFI2=$(topdir)tools/packfi2/fi2enc$(EXE)
ENCODE_DISKBOOT=$(topdir)tools/dancingbits$(EXE)

##########################################################################

CC=arm-elf-gcc
OBJCOPY=arm-elf-objcopy
OBJDUMP=arm-elf-objdump
STRIP=arm-elf-strip
NM=arm-elf-nm
AR=arm-elf-ar
RANLIB=arm-elf-ranlib
SIZE=arm-elf-size

GCC_VERSION=$(shell $(CC) -dumpversion)
GCC_VERSION_MAJOR=$(firstword $(subst ., ,$(GCC_VERSION)))

# -msoft-float is used per default but object files are marked as hard-float
CFLAGS=-fno-inline -Os -fno-strict-aliasing
# flags for gcc v4
# CFLAGS+=-mcpu=arm946e-s
# for gcc v3, we use to allow use of strd etc
ifeq ($(GCC_VERSION_MAJOR),3)
    CFLAGS+=-march=armv5te
else
    ifeq ($(GCC_VERSION_MAJOR),4)
        # TODO should be -mcpu, but breaks things ATM
        CFLAGS+=-mtune=arm946e-s
    endif
endif


CTHUMB=-mthumb
CFLAGS+=-mthumb-interwork
CFLAGS+=-I$(topdir)include $(PLFLAGS) $(CPPFLAGS)
CFLAGS+=-DPLATFORM=\"$(PLATFORM)\" -DPLATFORMSUB=\"$(PLATFORMSUB)\" -DPLATFORMID=$(PLATFORMID) -DHDK_VERSION=\"$(VER)\" -DBUILD_NUMBER=\"$(BUILD_NUMBER)\" -DCAMERA_$(PLATFORM)=1
CFLAGS+=-Wall -Wno-unused -Wno-format
LDFLAGS=-L$(topdir)lib/math -L$(topdir)lib/font
LDFLAGS+=-L$(topdir)lib/libc -L$(topdir)lib/ubasic
LDFLAGS+=-L$(topdir)platform/$(PLATFORM) -L$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)

ifdef OPT_DEBUGGING
CFLAGS+=-DOPT_DEBUGGING
endif

ifdef OPT_WARNINGS
     ifeq ($(GCC_VERSION_MAJOR),3)
           CFLAGS+=-Wwrite-strings -Wsign-compare -Wunused -Wno-unused-parameter
           HOSTCFLAGS+=-Wwrite-strings -Wsign-compare -Wunused -Wno-unused-parameter
     endif
     ifeq ($(GCC_VERSION_MAJOR),4)
           CFLAGS+=-Wextra -fdiagnostics-show-option -Wno-missing-field-initializers -Wunused -Wno-unused-parameter
           #HOSTCFLAGS+=-Wextra -fdiagnostics-show-option -Wno-missing-field-initializers -Wunused -Wno-unused-parameter
     endif
endif

##########################################################################

default: all

ifndef SKIPBUILDRULES

%.o: %.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
%.o: %.S
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
%.a:
	@echo $^ \-\> $@
	$(AR) rcs $@ $^

.dep/%.d: %.c .dep
	$(CC) $(CFLAGS) -M $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

.dep/%.d: %.S .dep
	$(CC) $(CFLAGS) -M $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

endif

all: all-recursive
clean: clean-recursive
distclean: distclean-recursive

.dep:
	mkdir .dep

clean-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Cleaning in $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" clean || exit 1; \
	done

distclean-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Distcleaning in $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" distclean || exit 1; \
	done

all-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Entering to $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" || exit 1; \
	    echo \<\< Leaving $(FOLDER)$$i; \
	done

depend-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Entering to $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" depend || exit 1; \
	    echo \<\< Leaving $(FOLDER)$$i; \
	done

ifdef SILENT
.SILENT:
endif
