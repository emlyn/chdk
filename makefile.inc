VER=test2-pre11

PLATFORM=a610
PLATFORMSUB=100e

#PLATFORM=a620
#PLATFORMSUB=100f

#PLATFORM=a630
#PLATFORMSUB=100c

#PLATFORM=a640
#PLATFORMSUB=100b

#PLATFORM=a710
#PLATFORMSUB=100a

#PLATFORM=s3is
#PLATFORMSUB=100a

include $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc

SILENT=SILENT

##########################################################################
##########################################################################
##########################################################################

ifndef OSTYPE
  HOSTPLATFORM:=$(shell uname -s | head -c 5)
  ifeq ($(HOSTPLATFORM),MINGW)
    OSTYPE = Windows
    EXE = .exe
    SH = sh
    DEVNULL = NUL
    SORT = $(dir $(shell which uniq.exe | sed s/\\\\/\\\//g))/sort.exe
  else
    ifeq ($(HOSTPLATFORM),Linux)
      OSTYPE = Linux
      EXE =
      SH =
      DEVNULL = /dev/null
      SORT = sort
    else
      OSTYPE = Other
      EXE =
      SH =
      DEVNULL = /dev/null
      SORT = sort
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

PAKWIF=$(topdir)tools/pakwif$(EXE)

##########################################################################

export PATH+=:/opt/arm/bin

CC=arm-elf-gcc
OBJCOPY=arm-elf-objcopy
OBJDUMP=arm-elf-objdump
STRIP=arm-elf-strip
NM=arm-elf-nm
AR=arm-elf-ar
RANLIB=arm-elf-ranlib
SIZE=arm-elf-size

# -msoft-float is used per default but object files are marked as hard-float
CTHUMB=-mthumb

CFLAGS=-fno-inline -O2 -fno-strict-aliasing
CFLAGS+=-mthumb-interwork
CFLAGS+=-I$(topdir)include $(PLFLAGS) $(CPPFLAGS)
CFLAGS+=-DPLATFORM=\"$(PLATFORM)\" -DPLATFORMSUB=\"$(PLATFORMSUB)\" -DHDK_VERSION=\"$(VER)\"
CFLAGS+=-Wall -Wno-unused -Wno-format
LDFLAGS=-L$(topdir)lib/math -L$(topdir)lib/font
LDFLAGS+=-L$(topdir)lib/libc -L$(topdir)lib/ubasic
LDFLAGS+=-L$(topdir)platform/$(PLATFORM) -L$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)

##########################################################################

default: all

.c.o:
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
.S.o:
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
%.a:
	@echo $^ \-\> $@
	$(AR) rcs $@ $^

clean-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Cleaning in $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" clean || exit 1; \
	done

all-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Entering to $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" || exit 1; \
	    echo \<\< Leaving $(FOLDER)$$i; \
	done

.$(SILENT):
