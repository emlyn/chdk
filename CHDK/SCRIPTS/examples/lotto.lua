--Example lua script that generates random numbers in various ways. idea & code by PhyrePhoX and msl
--[[
@title lotto demo
@param n how many
@default n 6
@param s min
@default s 1
@param r max
@default r 49
@param e exclusive 1=on
@default e 1
@param o sort
@default o 1
@param z sound 1=on
@default z 1
]]

--The comment block above will be read as parameters. 

--Declare a function for key request with led and sound feedback

function button()                               -- declare function
	local x = 0                                   -- local variable only valid for this function
	repeat                                        -- start loop
		wait_click(150)                             -- wait for key klick
		if is_pressed "set" then                    -- check which key ist pressed
			key = "SET"
			x = 1
		end
		if is_pressed "menu" then
			key = "MENU"
			x = 1
		end
	until  x == 1                                 -- end of loop
	set_led (8,1)                                 -- led feedback
	sleep (10)
	set_led (8,0)
	if sound == 1 then play_sound(4) end          -- sound feedback if set, and if camera is NOT muted
end

--Start script

--Declare usefull variable names for the parameter variables

count     = n
min       = s
max       = r
exclusive = e
order     = o
sound     = z

--Check parameters, if wrong ending the script

if (min >= max) then
	print("Wrong params, dummy!;-)")
	wait_click(0)
else
	if ((exclusive == 1) and ((max - min + 1)<count)) then
		print("Wrong params, dummy!;-)")
		wait_click(0)
	else

--If parameters ok start the main loop to throw the dice

		repeat
			result= {}                                -- create a table for result
			if exclusive == 1 then                    -- if exclusive is set
				array = {}                              -- create a table for mix
				for i = min, max do                     -- loop for fill the table
					array[i] = i
				end
				for i = min, max do                     -- loop for mix the table
					rnd = math.random(min, max)           -- create a random number
					buffer = array[i]                     -- change a number in the table
					array[i] = array[rnd]
					array[rnd] = buffer
				end
				for c=1, count do                       -- loop for output the result
					result[c] = array[c]
				end
			else
				for i = min, max do                     -- loop for no exclusive result
					result[i] = math.random(min, max)     -- create a random number
				end
			end

--Output the result

			if order == 1 then table.sort(result) end -- order result if set
			output = table.concat(result,", ")        -- create a string of the table
   			print("dice [SET]     end [MENU]")        -- output in console
			print()
			print(output)                             -- print a string variable
			button()                                  -- call the function
			cls()                                     -- clear the console
		until key == "MENU"                         -- end of loop if pressed "MENU"
	end                                             -- "SET" repeat the loop
end

--All functions, conditions and loops (except repeat) will closing with end

--For more Lua informations look here: http://chdk.wikia.com/wiki/LUA
-- thanks to MSL!
