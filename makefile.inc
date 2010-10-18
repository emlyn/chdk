VER=CHDK

PLATFORM=ixus130_sd1400
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

ifdef OPT_PTP
CFLAGS+=-DOPT_PTP
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
		echo \>\> Entering $(FOLDER)$$i; \
		$(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" || exit 1; \
		echo \<\< "Leaving " $(FOLDER)$$i; \
	done

depend-recursive:
	@for i in $(SUBDIRS); do \
		echo \>\> Entering $(FOLDER)$$i; \
		$(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" depend || exit 1; \
		echo \<\< "Leaving " $(FOLDER)$$i; \
	done

ifdef SILENT
.SILENT:
endif
