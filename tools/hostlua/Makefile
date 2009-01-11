topdir=../../

SKIPBUILDRULES=1

include $(topdir)makefile.inc

LUA_SRC=$(topdir)lib/lua

HOSTCFLAGS+=-DHOST_LUA -DLUA_ANSI -I./include


%.o: $(LUA_SRC)/%.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

.dep/%.d: $(LUA_SRC)/%.c .dep
	$(HOSTCC) $(HOSTCFLAGS) -MM $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

%.a:
	@echo $^ \-\> $@
	$(HOSTAR) rcs $@ $^

# these are always built for hostlua, you can hide them from scripts by setting 
# the corresponding globals to nil
LUA_OPTLIB_OBJS=

HOSTCFLAGS+=-DOPT_LUA_IOLIB
LUA_OPTLIB_OBJS+=liolib.o

HOSTCFLAGS+=-DOPT_LUA_OSLIB
LUA_OPTLIB_OBJS+=loslib.o

HOSTCFLAGS+=-DOPT_LUA_STRLIB
LUA_OPTLIB_OBJS+=lstrlib.o

COMMON_OBJS = lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o \
	lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o \
	lundump.o lvm.o lzio.o \
       \
       lauxlib.o lbaselib.o ldblib.o ltablib.o lmathlib.o \
	   $(LUA_OPTLIB_OBJS) loadlib.o linit.o

OBJS=$(COMMON_OBJS)

LUA_T=	lua$(EXE)
LUA_O=	lua.o

LUAC_T=	luac$(EXE)
LUAC_O=	luac.o print.o

LUA_A=liblua.a

all: $(LUA_A) $(LUA_T) $(LUAC_T)


$(LUA_A): $(OBJS)

$(LUA_T): $(LUA_O) $(LUA_A)
	@echo $< \-\> $@
	$(HOSTCC) -o $@ $(HOSTCFLAGS) $(LUA_O) $(LUA_A)

$(LUAC_T): $(LUAC_O) $(LUA_A)
	@echo $< \-\> $@
	$(HOSTCC) -o $@ $(HOSTCFLAGS) $(LUAC_O) $(LUA_A)


check:

clean:
	rm -f $(OBJS) $(LUA_A) $(LUA_T) $(LUAC_T)

distclean: clean
	rm -f $(OBJS:.o=.d)


include $(topdir)bottom.inc
