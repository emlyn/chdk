--[[
@title set rec/play demo
@param a 0=play 1=rec
@default a 0
--]]

new_mode=a==1
curr_mode=get_mode()
print("record: ",tostring(curr_mode))
print("set record to:",tostring(new_mode))
sleep(1000)
set_record(new_mode)
sleep(2000)
curr_mode=get_mode()
print("record: ",tostring(curr_mode))
sleep(1000)
