--[[
@title Tv mode universal
@param a integer value  [Tv]
@default a 0
@param b key delay [ms]
@default b 80
@param c shoot delay [s]
@default c 0
]]
 
function print_Tv()
	tv_output = {"64s","50s","40s","32s","25s","20s","15s","13s","10s","8s","6s",
	"5s","4s","3.2s","2.5s","2s","1.6s","1.3s","1s","0.8s","0.6s","0.5s","0.4s",
	"0.3s","1/4s","1/5s","1/6s","1/8s","1/10s","1/13s","1/15s","1/20s","1/25s",
	"1/30s","1/40s","1/50s","1/60s","1/80s","1/100s","1/125s","1/160s","1/200s",
	"1/250s","1/320s","1/400s","1/500s","1/640s","1/800s","1/1000s","1/1250s",
	"1/1600s","1/2000s","1/2500s","1/3200s","1/4000s","1/5000s","1/6400s",
	"1/8000s","1/10000s"}
	print_tv = "Tv  : "..tv_output[tv_input+19]
end 

function mf_mode()
	mf_output = {"normal","macro","","infinite"}
	print_mf = "focus: "..mf_output[mf_input]
end

function button()
	local x = 0
	repeat
		wait_click(key_delay)
		if is_pressed "remote" then
		  key = "SET"
		  x = 1
		end
		if is_pressed "set" then
			key = "SET"
			x = 1
		end
		if is_pressed "menu" then
			key = "MENU"
			x = 1
		end
		if is_pressed "display" then
			key = "DISP"
			x = 1
		end
		if is_pressed "left" then
			key = "LEFT"
			x = 1
		end
		if is_pressed "right" then
			key = "RIGHT"
			x = 1
		end
		if is_pressed "up" then
			key = "UP"
			x = 1
		end
		if is_pressed "down" then
			key = "DOWN"
			x = 1
		end
	until  x == 1
	set_led (8,1)
	sleep (10)
	set_led (8,0)
end 

--script start

if a < -18 then a = -18 end
if a > 40 then a = 40 end
if b < 50 then b = 50 end
if c < 0 then c = 0 end

repeat
	if get_mode() == false then
		cls()
		print("No record mode!")
		print("Stop for changing.")
		sleep(3000)
		exit_alt()
		sleep(2000)
	end
until get_mode() == true

tv_input = a
key_delay = b
shoot_delay = c
max_zoom = get_zoom_steps()
zoom = get_zoom()

repeat
	if get_propset() == 2 then
		mf_input = get_prop(6)+1
	else
		mf_input = get_prop(11)+1
	end
	cls()
	print_Tv()
	mf_mode()
	print("[<-][->]  ",print_tv)
	print("[Up][Down] zoom:",zoom.."/".. max_zoom)
	print("[DISP.]  ",print_mf)
	print("[SET] [Remote]   shoot")
	print("[MENU]           end")
	button()
	
	if key == "DISP" then
		mf_input = mf_input + 1
		if mf_input == 3 then mf_input = 4 end
		if mf_input == 5 then mf_input = 1 end
		if get_propset() == 2 then
			set_prop(6,mf_input-1)
		else
			set_prop(11,mf_input-1)
		end
	end
	if mf_input == 2 then
		set_zoom(0)
	else
		if key == "UP"  then
			zoom = zoom + 1
			if zoom > max_zoom then zoom = max_zoom end
			set_zoom(zoom)
		end
		if key == "DOWN" then
			zoom = zoom - 1
			if zoom < 0 then zoom = 0 end
			set_zoom(zoom)
		end
	end
	if key == "RIGHT" then tv_input = tv_input + 1 end
	if key == "LEFT" then tv_input = tv_input - 1 end
	if tv_input > 40 then tv_input = -18 end
	if tv_input < -18 then tv_input = 40 end
	if key == "SET" then
		if shoot_delay > 0 then
			cls()
			print("wait "..shoot_delay.." s")
			sleep(shoot_delay * 1000) 
		end
		TV = tv_input * 32
		press "shoot_half"
		repeat
		      until get_shooting() == true
		if get_propset() == 2 then
			set_prop(262,TV)
		else
			set_prop(69,TV)
		end
		press "shoot_full"
		release "shoot_full"
		release "shoot_half"
	end
until key == "MENU"
