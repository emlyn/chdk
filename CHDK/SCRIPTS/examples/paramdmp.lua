--[[ 
dump parameters from internal flash memory
NOTE:
parameter ids may vary between cameras, so scripts
using them will not be portable
--]]
logfile=io.open("A/paramdmp.log","wb")
for i=0,get_flash_params_count()-1 do
	s,n = get_parameter_data(i)
	logfile:write(i,": ")
	if s then
		-- string as hex
		for j=1,s:len() do
			logfile:write(string.format("0x%02x ",s:byte(j)))
		end
		-- string quoted
		logfile:write(string.format("[%q]",s))
		-- as number, if available
		if n then
			logfile:write(string.format(" 0x%x %d",n,n))
		end
	else
		logfile:write("nil")
	end
	logfile:write("\n")
end
logfile:close()

