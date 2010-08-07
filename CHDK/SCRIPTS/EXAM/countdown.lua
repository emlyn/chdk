--countdown.lua    by Kettmeister from the german forum
--uses sound, in order to hear it the camera musnt be muted
--[[
@title countdown
@param a hours
@default a 0
@param b minutes
@default b 1
@param c secunds
@default c 0
]]

sec=0
minu=0
hour=0
i=1
print("press 'SET' to start")
while (i==1) do
        wait_click(100)
        if is_pressed "set" then -- take time
                time_end=os.time() + a*3600 + b*60 + c
                i=0
        end
end
       
while(os.time()<time_end) do
        hour=(time_end-os.time())/3600
        minu=((time_end-os.time())-hour*3600) / 60
        sec=time_end-os.time()-((hour*3600)+(minu*60))
        cls()
        print("Noch "..hour..":"..minu..":"..sec)
        sleep(100)
end

cls()
print("press 'MENU' to stop")
i=1
while(i==1) do
        wait_click(250)
        if is_pressed "menu" then --  end
                set_led(8, 0)
                i=0
        end
        play_sound (4)
end    
print("END")