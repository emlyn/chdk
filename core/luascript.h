#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include "lua.h"

void *lua_consume_result();
void lua_script_reset();
int lua_script_start( char const* script );
extern void register_lua_funcs( lua_State* L );

extern lua_State* L;
extern lua_State* Lt;
extern int lua_keep_result;

#endif
