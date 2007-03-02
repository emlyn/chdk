VER=pre7

#PLATFORM=a610
#PLATFORMSUB=100e

#PLATFORM=a620
#PLATFORMSUB=100f

PLATFORM=a710
PLATFORMSUB=100a

include $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc

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
  else
    ifeq ($(HOSTPLATFORM),Linux)
      OSTYPE = Linux
      EXE =
      SH =
      DEVNULL = /dev/null
    else
      OSTYPE = Other
      EXE =
      SH =
     DEVNULL = /dev/null
    endif
  endif
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

CFLAGS=-fno-inline -O2 -Wall -Wno-unused -mtune=arm946e-s -fno-strict-aliasing -msoft-float
CFLAGS+=-I$(topdir)include $(PLFLAGS) $(CPPFLAGS)
LDFLAGS=-L$(topdir)lib/math -L$(topdir)lib/font
LDFLAGS+=-L$(topdir)lib/libc -L$(topdir)lib/ubasic
LDFLAGS+=-L$(topdir)platform/$(PLATFORM) -L$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)

##########################################################################

default: all

.c.o:
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
.S.o:
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
%.a:
	$(AR) rcs $@ $^

clean-recursive:
	@for i in $(SUBDIRS); do \
	    $(MAKE) -C $$i clean || exit 1; \
	done

all-recursive:
	@for i in $(SUBDIRS); do \
	    $(MAKE) -C $$i || exit 1; \
	done
