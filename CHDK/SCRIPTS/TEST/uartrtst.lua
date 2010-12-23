--[[
@title UART redirect Test (UARTRTST.LOG)
requires CHDK built with native function call support
--]]

if (type(call_event_proc) ~= "function" ) then
    error("ERROR: requires CHDK build with native function call support.")
end

-- include lualib module (uartr.lua)
uartr=require("uartr")

-- redirect UART to specific file
uartr.start("A/UARTRTST.LOG", 1)

-- redirect UART to random filesname like "00014540.log"
--uartr.start()

-- Short delay to avoid trouble, ToDo: really necessary ?
sleep(100)

-- os.date() return something like "Sat Dec  4 01:54:01 2010"
call_event_proc("Printf", os.date().." UART redirect Test (uartrtst.lua) OK\n");

-- Short delay to avoid trouble, ToDo: really necessary ?
sleep(100)

uartr.stop()
