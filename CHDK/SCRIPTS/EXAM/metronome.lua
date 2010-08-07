--metronome.lua    a script for the musicians by Kettmeister from the german forum
--plays a sound and lights the print led at a given interval
--[[
@title metronome
@param a beats/min
@default a 60
]]

i=0
j=1
print("press 'SET' to start")
while (j==1) do
        wait_click(100)
        if is_pressed "set" then -- start
                count=get_tick_count()+(60000/a)
                j=0
        end
end

cls()
print("press 'MENU' to end")
print(a.." beats/min")
j=1

while(j==1) do
        if(get_tick_count()>count) then
                count=get_tick_count()+(60000/a)
                play_sound (4)
                if i==0 then
                        set_led(8, 1)
                        i=1
                else
                        set_led(8, 0)
                        i=0
                end
        end

        wait_click(1)
        if is_pressed "menu" then --  end
                set_led(8, 0)
                j=0
        end
end