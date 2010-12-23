--[[
Module to control UART redirection. 
Creates A/UARTR.REQ as needed

DryOS only, requires native calls enabled

usage
uartr=require("uartr")
uartr.start([ filename[,replace] ])
... stuff that outputs to camera console, including Printf eventproc ...
uartr.stop()

if filename is omitted, the cameras automatic naming is used (numbered with tick when redirect was started)

if filename is given, the boolean replace may be set to remove any existing file of that name before starting

]]
-- local table to contain module
local uartr = {}
local req_file_name = "A/UARTR.REQ"
local initialized = false

local function initialize() 
	if initialized then
		return
	end	
	if (type(call_event_proc) ~= "function" ) then
		error("your CHDK does not support native calls")
	end

	if (call_event_proc("System.Create") == -1) then
		error("System.Create failed")
	end

	if (not os.stat(req_file_name)) then
		local req_file = io.open(req_file_name,"wb")
		if( not req_file ) then
			error("failed to open " .. req_file_name)
		end
		req_file:write("\119\033\206\130") --0x77 0x21 0xce 0x82
		req_file:close()
	end

	initialized = true
end

uartr.start=function(name,replace)
	initialize()
	if type(name) ~= "string" then
		call_event_proc("StartRedirectUART",0,0) -- auto buffer size, auto file name
	else
		if replace then
			os.remove(name)
		end
		call_event_proc("StartRedirectUART",0,name) -- auto buffer size, our file name
	end
	sleep(10) -- a yield appears to be needed before redirection is active
	call_event_proc("Printf","uartr.lua: start UART redirection\n");
end

uartr.stop = function()
	initialize()
	call_event_proc("Printf","uartr.lua: stop UART redirection\n");
	call_event_proc("StopRedirectUART")
end

return uartr
