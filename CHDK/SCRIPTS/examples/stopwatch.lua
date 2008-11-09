--stopwatch.lua    by Kettmeister & msl from the german forum
--[[ 
@title stopwatch 
@param a split time (1)/lap time(0) 
@default a 1 
]] 

--declare functions

--formating output (thx fbonomi)
function format_nn(n)
	r=tostring(n)
	if n<10 then
		r= "0" .. n
	end 
	return r
end

--get stop time and print
function to_time()
	if(a==0) then							-- lap time 
		ztime=(get_tick_count()-count_a)/1000 
		count_a=get_tick_count() 
	else											-- split time 
		ztime=(get_tick_count()-count_a)/1000 
	end
	s = ztime % 60
	m = (ztime / 60) % 60
	h = (ztime / 3600) % 24
	print("> "..format_nn(h)..":"..format_nn(m)..":"..format_nn(s))  
end 

--start script

if (a~=1 and a~=0) then a=1 end 

i=1 
ztime=0 
count_a=0 

cls()
print("[SET] start")

while(i==1) do 
	wait_click(0) 
	if is_pressed "set" then	-- started 
		count_a=get_tick_count()
		cls()
		print("[SET] time     [MENU] end")
		print()  
		print("started") 
		i=0 
	end 
end
 
i=1 
while(i==1) do
	wait_click(0) 
	if is_pressed "set" then	-- take time
		cls()
		print("[SET] time     [MENU] end")
		print() 
		to_time()									 
	end 
	if is_pressed "menu" then	-- end
		cls() 
		to_time() 
		print("finished")
		sleep(3000) 
		i=0 
	end     
end