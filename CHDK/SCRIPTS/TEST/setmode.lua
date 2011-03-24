--[[
@title set cap mode test
@param a 0=batch 1=menu 2=single
@default a 0
@param b batch: 0=valid only 1=all
@default b 0
@param c single: 0=by prop 1=by CHDK
@default c 0
@param d single: mode value
@default d 0
--]]
action=a
batchtype=b
singletype=c
reqmode=d

capmode=require("capmode")

function printf(...)
	print(string.format(...))
end

function get_rec_str()
	local isrec,isvid=get_mode()
	if isrec then
		if isvid then
			return "VID"
		else
			return "STL"
		end
	else
		return "PLY"
	end
end

function print_status()
	printf("%s %d %d %s",capmode.get_name(),capmode.get(),capmode.get_canon(),get_rec_str())
end

function check_one()
	local methodstr, oldmode, newmode, status, status_str
	-- we continue even if not in rec, to test error handling
	if not get_mode() then
		print("WARNING: not in rec mode")
	end
	print_status()
	if singletype == 0 then
		methodstr="canon"
		oldmode=capmode.get_canon()
		status=set_capture_mode_canon(reqmode)
		newmode=capmode.get_canon()
	else
		methodstr="chdk"
		oldmode=capmode.get()
		if not capmode.valid(reqmode) then
			printf("%d not valid",reqmode)
		end
		-- we continue even if not valid, to test error handling
		status=capmode.set(reqmode)
		newmode=capmode.get()
	end
	if status then
		status_str="OK"
	else
		status_str="FAIL"
	end
	printf("%s %d->%d %s",methodstr,oldmode,reqmode,status_str)
	if newmode ~= reqmode then
		printf("ERROR req %d got %d",reqmode,newmode)
	end
	print_status()
end

function log_printf(...)
	log:write(string.format(...))
end
function log_status()
	log_printf("%20s %3d %5d %s",capmode.get_name(),capmode.get(),capmode.get_canon(),get_rec_str())
end

fail_count=0
function log_rec_change(rec)
	local start_tick, end_tick, status_str, sleep_count
	if rec then
		log:write("SET RECORD                   | ")
	else
		log:write("SET PLAY                     | ")
	end
	start_tick=get_tick_count()
	set_record(rec)
	sleep_count = 0
	-- set_record just posts the message, needs time to finish
	while  sleep_count < 1000 do
		if (rec and get_mode()) or not ( rec or get_mode()) then
			break
		end
		sleep(10)
		sleep_count = sleep_count + 1
	end
	end_tick=get_tick_count()
	log_status()
	if (rec and get_mode()) or not (rec or get_mode()) then
		status_str="OK"
	else
		status_str="FAIL"
		fail_count = fail_count + 1
	end
	log_printf(" %4dms sleep %d %s\n",end_tick - start_tick, sleep_count, status_str)
end

function log_mode_change(id)
	local start_tick, end_tick, status, status_str
	log_printf("TRY %20s %3d | ",tostring(capmode.mode_to_name[id]),id)
	start_tick=get_tick_count()
	status=capmode.set(id)
	end_tick=get_tick_count()
	if status then
		if capmode.get() ~= id then
			status_str=string.format("CHANGE FAIL req %3d got %3d",id,capmode.get())
			fail_count = fail_count + 1
		else
			status_str="OK"
		end
	else
		status_str=string.format("SET %3d FAIL",id)
		fail_count = fail_count + 1
	end
	if not capmode.valid(id) then
		status_str = status_str .. " INVALID"
	end
	log_status()
	log_printf(" %4dms %s\n",end_tick - start_tick,status_str)
end

function check_all_chdk()
	local logname="A/setmode.log"
	local was_play
	printf("BATCH: log %s",logname)
	log=io.open(logname,"wb")
	if not log then
		error("open log failed")
	end
	local bi=get_buildinfo()
	log_printf("%s %s %s %s %s %s %s 0x%x\n",
				bi.platform,bi.platsub,bi.version,bi.build_number,
				bi.build_date,bi.build_time,bi.os,bi.platformid)
	
	log:write("START                        | ")
	log_status()
	log:write("\n")
	if not get_mode() then
		was_play=true
		log_rec_change(true)
	end
	original_mode=capmode.get()
	for id,_ in ipairs(capmode.mode_to_name) do
		if capmode.valid(id) or batchtype > 0 then
			log_mode_change(id)
			-- camera seems to handle mode change spam fine
			--sleep(500)
		end
	end
	log_mode_change(original_mode)
	if was_play then
		log_rec_change(false)
	end
	log:close()
	-- need this to see display if we switched back to play
	sleep(1000)
	if fail_count == 0 then
		print("PASS")
	else
		printf("%d FAILED check log",fail_count)
	end
end

function domenu()
	local i=1
	local mainmenu={}
	for id,name in ipairs(capmode.mode_to_name) do
		if capmode.valid(id) then
			mainmenu[i] = {name=name,id=id}
			i = i + 1
		end
	end
	local curmenu=mainmenu
	local curitem=1
	local lastitem=table.maxn(curmenu)
	while true do
		local sel=curmenu[curitem]
		-- demonstrates flicker free redraw
		set_console_autoredraw(0)
		cls()
		print("[/\\][\\/] [SET]")
		print_status()
		if curitem > 1  then
			printf("|%s",curmenu[curitem-1].name)
		else
			print("--------------------")
		end
		printf(">%s",sel.name)
		if curmenu[curitem+1] then
			printf("|%s",curmenu[curitem+1].name)
		else
			print("--------------------")
		end
		console_redraw()
		set_console_autoredraw(1)
		wait_click(5000)
		if is_pressed("down") then
			if curmenu[curitem+1] then
				curitem = curitem + 1
			else
				curitem = 1
			end
		elseif is_pressed("up") then
			if curitem > 1 then
				curitem = curitem - 1
			else
				curitem = lastitem
			end
		elseif is_pressed("set") then
			if capmode.set(sel.id) then 
				if capmode.get() == sel.id then
					print("OK")
				else
					printf("FAIL: set %d got %d",sel.id,capmode.get())
				end
			else
				printf("FAIL: set %d",sel.id)
			end
			print_status()
			print("press a key")
			wait_click(10000)
		elseif is_pressed("menu") then
			break
		end
	end
end

if action == 0 then
	check_all_chdk()
	print("press a key")
	wait_click(10000)
elseif action == 1 then
	domenu()
else
	check_one()
	print("press a key")
	wait_click(10000)
end

