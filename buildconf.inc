#!build time optional components - comment out the features you dont want to have in your build
OPT_GAME_REVERSI=1
OPT_GAME_SOKOBAN=1
OPT_GAME_CONNECT4=1
OPT_GAME_MASTERMIND=1
OPT_CURVES=1
OPT_TEXTREADER=1
OPT_CALENDAR=1
OPT_DEBUGGING=1
OPT_EDGEOVERLAY=1

# Scripting components
OPT_UBASIC=1
OPT_LUA=1
OPT_LUA_STRLIB=1
OPT_LUA_IOLIB=1
OPT_LUA_OSLIB=1
#allow Lua to call arbitrary ROM functions and eventprocs
# WARNING: This is DANGEROUS. e.g. call_event_proc("EraseSectorOfRom",...)
# NOTE: the interface for this may change in the future, to support better support buffers etc
#OPT_LUA_CALL_NATIVE=1

# experimental - allocate memory from alternate heap. Default 2MB from EXMEM_RAMDISK
# See exmem_malloc_init in generic/wrappers.c
#OPT_EXMEM_MALLOC=1
# experimental PTP/USB interface
#OPT_PTP=1
#OPT_MD_DEBUG=1
# require correct FI2 keys in platform/fi2.inc , see http://chdk.wikia.com/wiki/For_Developers/fi2offsets and http://chdk.setepontos.com/index.php/topic,2995.0.html
#OPT_FI2=1
# if enabled, compiler will produce a lot of warnings, maybe not always correct ones, see http://chdk.setepontos.com/index.php/topic,2509.msg32191.html#msg32191
#OPT_WARNINGS=1
# If enabled (and reference binaries are present in /tools), compiler will generate function signatures
OPT_GEN_SIGS=1
# If enabled (and firmware binaries are present) compiler will update "stubs_entry.S"
OPT_GEN_STUBS=1
# the symbols / not done yet
#!OPT_SYMBOLS=1
# for people who won't use lang files at all / not done yet
#!OPT_LANGUAGEINTERFACE=1
