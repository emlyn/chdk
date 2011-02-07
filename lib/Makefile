topdir=../
include $(topdir)makefile.inc

SUBDIRS=font math lang armutil

ifdef OPT_LUA
SUBDIRS+=lua
endif

ifdef OPT_UBASIC
SUBDIRS+=ubasic
endif

include $(topdir)bottom.inc
