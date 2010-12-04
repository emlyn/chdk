--[[
@title UART redirect Test (UARTRTST.LOG)
requires CHDK built with native function call support
--]]

-- include lualib module (uartr.lua)
uartr=require("uartr")

-- redirect UART to specific file
uartr.start("A/UARTRTST.LOG", 1)

-- redirect UART to random filesname like "00014540.log"
--uartr.start()

-- os.date() return something like "Sat Dec  4 01:54:01 2010"
call_event_proc("Printf", os.date().." UART redirect Test (uartrtst.lua) OK\n");

uartr.stop()
