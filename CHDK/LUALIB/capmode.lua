--[[
module to control capture modes
Modes names may be found in CHDK/LUALIB/GEN/modelist.lua.
These are the same as the enum values in include/modelist.h, minus the MODE_ prefix

capmode public members:
	mode_to_name: table mapping CHDK mode numbers to names.
	name_to_mode: table mapping names to CHDK mode numbers.
	get(): 
		return: current CHDK mode number, or 0 if in play or the current mode is not in the modemap
	get_name(): 
		return: string name of the current CHDK mode, "UNKNOWN" if the mode isn't in the mode map, or "PLAY" 
	get_canon(): 
		return: the SHOOTING_MODE prop value of the current mode
	set(modeid): Set the current capture mode
		modeid: is a mode number or name
		return: true if the mode is in the cameras modemap and the camera is in rec mode, otherwise false
	valid(modeid): Check if modeid is in the modemap
		modeid: mode number or name
		return: returns true if mode the mode is in the cameras modemap, otherwise false
usage:
	capmode=require("capmode")
	print("mode#",cap_mode.get(),"name",capmode.get_name(),"prop",capmode.get_canon())
	if capmode.valid("M") then
		capmode.set("M")
	end
--]]
local props=require("propcase")
local capmode={}
-- load list generated from CHDK source
-- id->name mapping
local mode_to_name=require("GEN/modelist")
-- name-> id mapping
local name_to_mode={}

capmode.mode_to_name=mode_to_name
capmode.name_to_mode=name_to_mode

for mode_num,mode_name in ipairs(mode_to_name) do
	name_to_mode[mode_name]=mode_num
end


local function get_mode_arg(mode)
	if tonumber(mode) then
		return tonumber(mode)
	elseif type(mode) == "string" and name_to_mode[mode] then
		return name_to_mode[mode]
	end
--	implicit return nil
end

capmode.set = function(mode)
	local modenum=get_mode_arg(mode)
	if modenum then
		return set_capture_mode(modenum)
	end
	return false
end

capmode.valid = function(mode)
	local modenum=get_mode_arg(mode)
	if modenum then
		return is_capture_mode_valid(modenum)
	end
	return false
end

-- return the current CHDK mode value, or 0 if play
capmode.get = function()
	local isrec,_,m=get_mode()
	if isrec then
		return bitand(m,0xFF)
	else
		return 0
	end
end

-- return the name of the current CHDK mode
capmode.get_name = function()
	if get_mode() then
		local name=mode_to_name[capmode.get()]
		if name then
			return name
		else
			return "UNKNOWN"
		end
	else
		return "PLAY"
	end
end

-- return the current canon mode value
capmode.get_canon = function()
	return bitand(get_prop(props.SHOOTING_MODE),0xFFFF)
end

return capmode;
