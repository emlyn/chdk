#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include "lua.h"

void lua_script_reset();
int lua_script_start( char const* script,int is_ptp );
void lua_script_error( lua_State* L,int runtime );
void lua_script_finish( lua_State* L );
extern void register_lua_funcs( lua_State* L );
// run the "restore" function at the end of a script
void lua_run_restore();

extern lua_State* L;
extern lua_State* Lt;

#endif
