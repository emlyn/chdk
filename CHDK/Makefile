topdir=../
include $(topdir)makefile.inc

GENLUA=LUALIB/GEN/propset1.lua LUALIB/GEN/propset2.lua LUALIB/GEN/propset3.lua LUALIB/GEN/modelist.lua
# generate some lua files from CHDK source
all: $(GENLUA)

LUALIB/GEN/propset1.lua:  $(topdir)include/propset1.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/propset2.lua:  $(topdir)include/propset2.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/propset3.lua:  $(topdir)include/propset3.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/modelist.lua:  $(topdir)include/modelist.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_modelist_lua.sed < $< > $@

clean:
	rm -f $(GENLUA)

include $(topdir)bottom.inc
