--[[
@title char input
@param f key delay
@default f 200
]]

key_delay = f
output=""

function button()
 local x = 0
 repeat
 wait_click(key_delay)
  if is_pressed "remote" then
   key = "REMOTE"
   x = 1
  end
  if is_pressed "set" then
   key = "SET"
   x = 1
  end
  if is_pressed "erase" then
   key = "ERASE"
   x = 1
  end
  if is_pressed "display" then
   key = "DISP."
   x = 1
  end
  if is_pressed "menu" then
   key = "MENU"
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
  if is_pressed "left" then
   key = "LEFT"
   x = 1
  end
  if is_pressed "right" then
   key = "RIGHT"
   x = 1
  end
  if is_pressed "zoom_in" then
   key = "ZOOM_IN"
   x = 1
  end
  if is_pressed "zoom_out" then
   key = "ZOOM_OUT"
   x = 1
  end
 until  x == 1
 set_led (8,1)
 sleep (10)
 set_led (8,0)
end

function tabToStr()
	output=table.concat(word)
end

function input()

	abc_lower = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p",
								"q","r","s","t","u","v","w","x","y","z"}
	abc_upper = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P",
								"Q","R","S","T","U","V","W","X","Y","Z"}
	abc_spec = {"0","1","2","3","4","5","6","7","8","9",",",".","-",";",":","_",
							"/",".JPG",".CRW",".CR2",".THM",".WAV",".LUA",".BAS",".TXT"," "}
	word = {}
	a=0
	b=0
	actChar=""
	repeat
		print("[<-][->][SET] [+/-][MENU]")
		print("[ZOOM in/out]  [UP][DOWN]")
		button()
		cls()
		if key == "RIGHT" then a=a+1 end
		if key == "LEFT" then a=a-1 end
		if key == "UP" then b=b+1 end
		if key == "DOWN" then a=1 end
		if key == "ZOOM_IN" then a=a+5 end
		if key == "ZOOM_OUT" then a=a-5 end
		if a >= 27 then a=1 end
		if a <= 0  then a=26 end
		if b>=3 then b=0 end
		if b==0 then
			actChar=abc_lower[a]
			char_info="lower case"
		end
		if b==1 then
			actChar=abc_upper[a]
			char_info="upper case"
		end
		if b==2 then
			actChar=abc_spec[a]
			char_info="special char"
		end
		print(char_info..": "..actChar)
		if key == "SET" then table.insert(word,actChar) end
		if key == "ERASE" then table.remove(word) end
		tabToStr()
		print("input: "..output)
		print (" ")
	until key == "MENU"
end

function make_dir(dirname)
	os.mkdir(dirname)
end


x=0
repeat
  input()
  cls()
  print("INPUT: "..output)
  print("[SET]  new input")
  print("[DISP] make dir and stop")
  print("[MENU] stop")
  button()
  if key == "SET" then cls() end
  if key == "DISP." then
	  dir = "A/"..output
	  make_dir(dir)
	  print "ready"
	  sleep(3000)
	  x=1
  end
  if key == "MENU" then
		print "ready"
	  sleep(3000)
	  x=1
  end
until x==1

--[[

***possible commands***

function make_dir(dirname)
	os.mkdir(dirname)
end

function delete_dir(dirname)
	os.remove(dirname)
end

function rename_file(old_filename, new_filename)
	os.rename(old_filename, new_filename)
end

function delete_file(filename)
	os.remove(filename)
end

***missing commands***

-os.list_dir

]]
