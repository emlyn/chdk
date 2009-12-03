#!build time optional components - comment out the features you dont want to have in your build
OPT_LUA_IOLIB=1
OPT_LUA_OSLIB=1
OPT_GAME_REVERSI=1
OPT_GAME_SOKOBAN=1
OPT_GAME_CONNECT4=1
OPT_GAME_MASTERMIND=1
OPT_CURVES=1
OPT_TEXTREADER=1
OPT_CALENDAR=1
OPT_DEBUGGING=1
OPT_EDGEOVERLAY=1
OPT_LUA_STRLIB=1
#OPT_MD_DEBUG=1
# needs proper fi2.inc in platform/ !!! see http://chdk.setepontos.com/index.php/topic,2995.0.html
#OPT_FI2=1
# if enabled, compiler will produce a lot of warnings, maybe not always correct ones, see http://chdk.setepontos.com/index.php/topic,2509.msg32191.html#msg32191
#OPT_WARNINGS=1
# If enabled (and reference binaries are present in /tools), compiler will generate function signatures
OPT_GEN_SIGS=1
# If enabled (and firmware binaries are present) compiler will update "stubs_entry.S"
OPT_GEN_STUBS=1
# Shall ubasic be compiled into build? not done yet
#!OPT_UBASIC=1
# Shall lua support be compiled into build? not done yet
#!OPT_LUA=1
# the symbols / not done yet
#!OPT_SYMBOLS=1
# for people who won't use lang files at all / not done yet
#!OPT_LANGUAGEINTERFACE=1
