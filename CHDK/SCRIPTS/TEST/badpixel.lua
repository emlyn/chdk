--[[
@title Create badpixel.bin
]]
 
function get_bad_count()
 a=get_raw()
 set_raw(255)
 set_tv96_direct(96)
 shoot()
 b=get_raw()
 set_raw(a)
 return b
end

repeat
  if get_mode() == false then
    cls()
    print("Run in Record mode!")
    sleep(3000)
    cls()
    exit_alt()
    sleep(1000)
  end
until get_mode() == true
cls()
print("Wait please... ")
print("This takes a few seconds!")
print("Don't panic!!")
sleep(3000)
x1=get_bad_count()
x2=get_bad_count()
if (x1==x2) then
 print("Bad pixel count: ", x1)
 print("press SET to save file,")
 print("or other key to exit")
 wait_click(0)
 if is_pressed "set" then 
  os.remove("A/CHDK/badpixel.bin") 
  os.rename("A/CHDK/bad_tmp.bin", "A/CHDK/badpixel.bin") 
  print("File is saved.");
 end
 os.remove("A/CHDK/bad_tmp.bin")
else
 print("Try this script again...")
end
